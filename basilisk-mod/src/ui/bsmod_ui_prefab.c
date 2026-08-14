
 /**
  MIT License
  
  Copyright (c) 2026 switch360hardflip <switch360hardflip@gmail.com>
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */ 

#include <bsmod_internal.h>
#include <bsmod_cache.h>

BSMODAPI void _bsmod_pushPrefabMenuWidgets(bs_List* widgets, bs_vec2 background_size) {
    bs_vec3 offset = { 8 + 16, 0, 0 };
    offset.z += BSGFX_BACKGROUND_Z_COUNT;

    const int name_padding = 4;

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .advance_flags = BSGFX_WIDGET_ADVANCE_APPLY_OFFSET,
        .offset = { 0.0, -16.0, 0.0 },
    });

    static bs_vec3 temp = { 0 }, rot = { 0 }, sca = { 1, 1, 1 };
    const float input_width = 64.0;
    _bsmod_pushVecNWidget(widgets, "Position", offset, input_width, &temp, 3);
    _bsmod_pushVecNWidget(widgets, "Rotation", offset, input_width, &rot, 3);
    _bsmod_pushVecNWidget(widgets, "Scale", offset, input_width, &sca, 3);
}

BSMODAPI bool _bsmod_instancePrefabPreview(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering) {
    bs_Model* model = bsgfx_prefabModel();
    bs_Atlas* atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->head;

    if (_bsmod_search_input_->len > 0 && strstr(model->meshes[id].name, _bsmod_search_input_->value) == NULL) {
        return false;
    }

    bs_vec4 rotation;
    bs_eulToQ(&BS_V3_TO_RADIANS(BS_V3(-45, -45, 45)), &rotation);

    const float scale = 1.0; // todo figure out AABB fitting with rotation instead
    bsgfx_instanceHiResMesh(
        model->meshes + id,
        &BS_V3(position->x + widget->grid.size.x / 2.0, position->y + widget->grid.size.x / 2.0, 0),
        //bsgfx_adjustPosition(BS_V3(position->x + widget->grid.size.x, position->y, 13), hovering, id),
        &rotation,
        widget->grid.size.x * scale,
        BSGFX_PREFAB_SUBTYPE_MESH_HI_RES_SCREEN,
        false);

    return true;
}



  /*==============================================================================
   * Dragging Icon
   *============================================================================*/

BSMODAPI void _bsmod_onDragPrefab(bsmod_DraggingParams params) {
    if (_bsmod_.hovering.tile < 0 || _bsmod_.hovering.primitive < 0)
        return;

    bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, _bsmod_.hovering.primitive);

    bs_ivec2 coords;
    bsgfx_tileCoordinate(primitive, _bsmod_.hovering.tile_axis, _bsmod_.hovering.tile, &coords);

    bs_vec3 tile_position;
    bsgfx_tilePosition(primitive, _bsmod_.hovering.tile_axis, coords.x, coords.y, &tile_position);

    bs_vec4 rotation;
    bsgfx_tileRotation(_bsmod_.hovering.tile_axis, &rotation);

    bs_vec3 euler_rotation;
    bsgfx_tileEulerRotation(_bsmod_.hovering.tile_axis, &euler_rotation);

    bs_qMulQ(&primitive->rotation, &rotation, &rotation);

    bs_mat4 matrix = BS_MAT4_IDENTITY;
    bs_m4Translate(&matrix, &tile_position, &matrix);
    bs_m4Rotate(&matrix, &rotation, &matrix);

    bsgfx_instancePrefabModel(_bsmod_.dragging_id, matrix, BSGFX_PREFAB_SUBTYPE_MESH, $bsmod_light_blue()->id);
    bs_Model* prefab_model = bsgfx_prefabModel();
    bs_Mesh* prefab_mesh = prefab_model->meshes + _bsmod_.dragging_id;

    if (bs_leftClickUpOnce()) {
        bsgfx_RawPrefab* prefab = _bsmod_add(BSGFX_TYPE_PREFAB, &(bsgfx_RawPrefab) {
            .position = tile_position,
            .rotation = euler_rotation,
            .scale = { 1, 1, 1 },
            .name_hash = prefab_mesh->name_hash,
        });
        _bsmod_saveTypeN(BSGFX_TYPE_PREFAB, BS_CONSTANT_STRING("Created prefab"));
    }
}


  /*==============================================================================
   * Rasterizing Icons
   *============================================================================*/

BSMODAPI void _bsmod_rasterizePrefabIcons() {
    bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS)->queue;

    bs_Pipeline* pipeline;
    bs_PipelineHash hash;

    const int width = 84;

    const bs_ivec2 render_size = { width * 2, width * 2 };
    const bs_ivec2 output_size = { width, width };

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsmod_mesh_instanced();
    hash.shaders[1] = $fs_bsmod_rasterize();

    if (bs_pipeline(NULL, queue, &hash, &pipeline) == BS_RESULT_OK) {

        bs_mat4 proj, view, camera;
        bs_orthographic(0, render_size.x, 0, render_size.y, -500.0, 500.0, &proj);
        bs_lookAt(&BS_V3(0, 0, 1), &BS_V3(0, 0, 0), &BS_V3(0, 1, 0), &view);
        bs_m4Mul(&proj, &view, &camera);

        struct {
            bs_mat4x3 camera;
            bs_mat4x3 model;
            bs_vec4 color;
            int material_texture_size;
            int material_texture_id;
        } push_const = {
            .camera = bs_m4x3(&camera),
        };

        int instance = 0;

        _bsmod_beginRasterize(render_size, output_size);

        bsgfx_Material* material = $bsmod_light_blue();

        bs_Model* model = bsgfx_prefabModel();

        int count = model->meshes_count;
        
        bs_vec4 rotation;
        bs_eulToQ(&BS_V3_TO_RADIANS(BS_V3(15.0, 30.0, -15.0)), &rotation);

        for (int i = 0; i < count; i++) {
            bs_Mesh* mesh = model->meshes + i;
            int subtype = mesh->extra[BSGFX_MODEL_SUBTYPE_DEFAULT];

            bs_mat4 transform;
            bs_fitAabb(&mesh->aabb, &BS_IV2_TO_V2(render_size), &rotation, &transform);

            push_const.color = material->contract->color;
            push_const.material_texture_size = material->contract->image_binding;
            push_const.material_texture_id = material->contract->image;
            push_const.model = bs_m4x3(&transform);

            instance = bsgfx_instancePrefabModel(i, transform, BSGFX_PREFAB_SUBTYPE_MESH, $bsmod_light_blue()->id);
            _bsmod_rasterizeInstance(queue, hash, subtype, instance, material->category, material->name, render_size.x, render_size.y, sizeof(push_const), &push_const);
        }

        _bsmod_endRasterize(queue);
    }
}