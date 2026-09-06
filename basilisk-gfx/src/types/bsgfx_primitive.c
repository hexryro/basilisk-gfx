
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

#include <bsgfx_internal.h>
#include <../bsgfx_contracts.h>
#include <bsgfx_cache.h>

BSGFXAPI void _bsgfx_primitivePosition(const bsgfx_RawPrimitive* primitive, bs_vec3* out) {
    bs_vec4 q;
    bs_eulToQ(&BS_V3_TO_RADIANS(primitive->rotation), &q);

    bs_vec3 rotated_scale;
    bs_qRotateV3(&q, &primitive->scale, &rotated_scale);

    bs_v3Add(&primitive->position, &rotated_scale, out);
}

static void _bsgfx_mapPrimitive(void* u, void* m) {
    bsgfx_RawPrimitive* unmapped = u;
    bsgfx_Primitive* mapped = m;

    mapped->collision = unmapped->collision;
    mapped->guid = unmapped->guid;
    mapped->scale = unmapped->scale;
    mapped->flags = unmapped->flags;
    mapped->type = unmapped->type;

    _bsgfx_primitivePosition(unmapped, &mapped->position);

    bs_eulToQ(&BS_V3_TO_RADIANS(unmapped->rotation), &mapped->rotation);

    switch (unmapped->type) {
    case BSGFX_PRIMITIVE_TYPE_BOX: mapped->subtype_index = BSGFX_SUBTYPE_PRIMITIVE_BOX; break;
    case BSGFX_PRIMITIVE_TYPE_SPHERE: mapped->subtype_index = BSGFX_SUBTYPE_PRIMITIVE_SPHERE; break;
    }
}

BSGFXAPI void _bsgfx_loadPrimitives(int package_id) {
    _bsgfx_type(
        BSGFX_TYPE_PRIMITIVE,
        package_id,
        BSGFX_PRIMITIVE_VERSION,
        "primitives", "primitive",
        sizeof(bsgfx_RawPrimitive), sizeof(bsgfx_Primitive), _bsgfx_mapPrimitive,
        0, 0, 0, 0);

    bs_U32 index = 0;

    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);

        if (primitive->type != BSGFX_PRIMITIVE_TYPE_BOX)
            continue;

        primitive->first_tile = index;
        for (int j = 0; j < 6; j++) {
            bsgfx_TileAxis* ax = &_bsgfx_tileAxes()[j];

            int width = (int)(primitive->scale.a[ax->width_axis] * 2.0f);
            int height = (int)(primitive->scale.a[ax->height_axis] * 2.0f);

            index += width * height;
        }
        primitive->last_tile = index;
    }

   // _bsgfx_instancePrimitives();
}

BSGFXAPI bsgfx_InstanceSubtype* _bsgfx_primitiveSubtype(bsgfx_PrimitiveType type) {
    switch (type) {
    case BSGFX_PRIMITIVE_TYPE_BOX: return _bsgfx_subtypes_[BSGFX_SUBTYPE_PRIMITIVE_BOX];
    case BSGFX_PRIMITIVE_TYPE_SPHERE: return _bsgfx_subtypes_[BSGFX_SUBTYPE_PRIMITIVE_SPHERE];
    }

    return NULL;
}

BSGFXAPI int _bsgfx_instancePrimitive(bsgfx_InstanceSubtype* subtype, bs_mat4 transform, bs_U32 flags, int id, int material) {
    return bsgfx_instantiate(subtype, &transform, sizeof(bs_mat4), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_queryTilePrimitive(int tile_id) {
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);
        if (tile_id >= primitive->first_tile && tile_id <= primitive->last_tile) {
            return i;
        }
    }

    return -1;
}

BSGFXAPI void _bsgfx_instancePrimitives() {
    if (!bs_exists(BSGFX_ATLASES, BSGFX_ATLAS_ANY))
        return;

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

    int white = $BSGFX_ATLAS_ANY_white()->id;
    bs_vec4 white_coords = bs_atlasCoordinates(atlas, white);
    int red_material = $red_material()->id;

    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);
        if (primitive->flags & BSGFX_PRIMITIVE_HIDDEN)
            continue;

        bs_mat4 transform = BS_MAT4_IDENTITY;
        bs_m4Translate(&transform, &primitive->position, &transform);
        bs_m4Rotate(&transform, &primitive->rotation, &transform);
        bs_m4Scale(&transform, &primitive->scale, &transform);

        bs_U32 flags = BSGFX_ID_HIGHLIGHT | BSGFX_ID_IS_PRIMITIVE;

        //if (_bsgfx_procs_.bsmod_isSelected && _bsgfx_procs_.bsmod_isSelected(BSGFX_TYPE_PRIMITIVE, i))
        //    flags |= BSGFX_ID_SELECTED;

        //if (primitive->type == BSGFX_PRIMITIVE_TYPE_BOX) // tiles are rendered over these
        //    continue;

        _bsgfx_instantiate(_bsgfx_subtypes_[primitive->subtype_index], &transform, sizeof(bs_mat4), flags, 0, i, 0);
    }
}

BSGFXAPI void _bsgfx_renderPrimitives(bs_RendererScope* scope, bs_Queue* queue, bs_mat4 camera) {
    bs_PipelineHash hash;
    struct {
        bs_mat4 camera;
    } push_const = {
        .camera = camera,
    };

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_static_instanced();
    hash.shaders[1] = $fs_bsgfx_model();
    hash.stencil_front = (bs_StencilOperation) {
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
        .reference = 2, // TODO:
    };

    bs_Pipeline* pipeline;
    bs_pipeline(scope, queue, &hash, &pipeline);

    bs_pushConstant(queue, pipeline, 0, sizeof(&push_const), &push_const);
    _bsgfx_renderSubtype(queue, _bsgfx_subtypes_[BSGFX_SUBTYPE_PRIMITIVE_BOX], pipeline);
    _bsgfx_renderSubtype(queue, _bsgfx_subtypes_[BSGFX_SUBTYPE_PRIMITIVE_SPHERE], pipeline);
}

BSGFXAPI int _bsgfx_queryPrimitive(bs_GUID* guid) {
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);
        if (bs_sameGuid(guid, &primitive->guid))
            return i;
    }

    char guid_buffer[37];
    bs_guidToString(guid, guid_buffer);

    return -1;
}
