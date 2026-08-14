
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

BSMODAPI bool _bsmod_instancePrimitivePreview(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering) {
    float scale = 0.25; // todo figure out AABB fitting with rotation instead

    bs_vec4 rotation;
    bs_eulToQ(&BS_V3_TO_RADIANS(BS_V3(-45, -45, 45)), &rotation);

    bs_mat4 transform = BS_MAT4_IDENTITY;
    float s = widget->grid.size.x * scale;
    bs_m4Translate(&transform, &BS_V3(position->x + widget->grid.size.x / 2.0, position->y + widget->grid.size.y / 2.0, 0.0), &transform);
    bs_m4Rotate(&transform, &rotation, &transform);
    bs_m4Scale(&transform, &BS_V3(s, s, s), &transform);

    int subtype = bsgfx_primitiveSubtype(id);
    bsgfx_instancePrimitive(subtype, transform, 0, 0, 0);

    return true;
}



  /*==============================================================================
   * Dragging Icon
   *============================================================================*/

BSMODAPI void _bsmod_onDragPrimitive(bsmod_DraggingParams params) {
    if (_bsmod_.hovering.tile < 0 || _bsmod_.hovering.primitive < 0)
        return;

    bsgfx_Primitive* hovering_primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, _bsmod_.hovering.primitive);

    bs_ivec2 coords;
    bsgfx_tileCoordinate(hovering_primitive, _bsmod_.hovering.tile_axis, _bsmod_.hovering.tile, &coords);

    bs_vec3 tile_position;
    bsgfx_tilePosition(hovering_primitive, _bsmod_.hovering.tile_axis, coords.x, coords.y, &tile_position);

    bs_vec4 rotation;
    bsgfx_tileRotation(_bsmod_.hovering.tile_axis, &rotation);

    bs_vec3 euler_rotation;
    bsgfx_tileEulerRotation(_bsmod_.hovering.tile_axis, &euler_rotation);

    bs_qMulQ(&hovering_primitive->rotation, &rotation, &rotation);

    bs_mat4 matrix = BS_MAT4_IDENTITY;
    bs_m4Translate(&matrix, &tile_position, &matrix);
    bs_m4Rotate(&matrix, &rotation, &matrix);

    int subtype = bsgfx_primitiveSubtype(_bsmod_.dragging_id);
    bsgfx_instancePrimitive(subtype, matrix, 0, 0, $bsmod_light_blue()->id);

    if (bs_leftClickUpOnce()) {
        bsgfx_RawPrimitive* primitive = _bsmod_add(BSGFX_TYPE_PRIMITIVE, &(bsgfx_RawPrimitive) {
            .position = tile_position,
            .rotation = euler_rotation,
            .scale = { 1, 1, 1 },
            .type = _bsmod_.dragging_id,
            .guid = bs_guid(),
        });
        _bsmod_saveTypeN(BSGFX_TYPE_PRIMITIVE, BS_CONSTANT_STRING("Created primitive"));
    }
}



  /*==============================================================================
   * Rasterizing Icons
   *============================================================================*/

#include <float.h>

BSMODAPI void _bsmod_rasterizePrimitiveIcons() {
  //  bs_Queue* single_times_queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_SINGLE_TIMES)->queue;
    bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS)->queue;

    bs_Pipeline* pipeline;
    bs_PipelineHash hash;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsmod_mesh_instanced();
    hash.shaders[1] = $fs_bsmod_rasterize();

    if (bs_pipeline(NULL, queue, &hash, &pipeline) == BS_RESULT_OK) {
        const width = 70;

        const bs_ivec2 render_size = { width * 2, width * 2 };
        const bs_ivec2 output_size = { width, width };

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

        bs_vec4 rotation;
        bs_eulToQ(&BS_V3_TO_RADIANS(BS_V3(15.0, 30.0, -15.0)), &rotation);

        for (int i = 0; i < BSGFX_PRIMITIVE_TYPE_COUNT; i++) {
            int subtype = bsgfx_primitiveSubtype(i);

            bs_Aabb aabb = { .min = { -1, -1, -1 }, .max = { 1, 1, 1 },};

            const float sphere_padding = 12.0;
            bs_mat4 transform;
            if (i == BSGFX_PRIMITIVE_TYPE_SPHERE) {
                transform = BS_MAT4_IDENTITY;
                float s = render_size.x / 2.0 - sphere_padding;
                bs_m4Translate(&transform, &BS_V3(render_size.x / 2, render_size.y / 2, 0.0), &transform);
                bs_m4Rotate(&transform, &rotation, &transform);
                bs_m4Scale(&transform, &BS_V3(s, s, s), &transform);
            }
            else
                bs_fitAabb(&aabb, &BS_IV2_TO_V2(render_size), &rotation, &transform);

            push_const.color = material->contract->color;
            push_const.material_texture_size = material->contract->image_binding;
            push_const.material_texture_id = material->contract->image;
            push_const.model = bs_m4x3(&transform);

            instance = bsgfx_instancePrimitive(subtype, transform, 0, 0, 0);
            _bsmod_rasterizeInstance(queue, hash, subtype, instance, material->category, material->name, render_size.x, render_size.y, sizeof(push_const), &push_const);
        }

        _bsmod_endRasterize(queue);
    }
}