
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
#include <bsgfx_cache.h>
#include <../bsgfx_contracts.h>



  /*==============================================================================
   * Helpers
   *============================================================================*/

static const bsgfx_TileAxis _bsgfx_tile_axes[6] = {
    {
        .normal = { -1,  0,  0 },
        .right = {  0,  0,  1 },
        .up = {  0,  1,  0 },
        .start_sign = { -1, -1, -1 },
        .width_axis = 2,
        .height_axis = 1
    },
    {
        .normal = {  1,  0,  0 },
        .right = {  0,  0, -1 },
        .up = {  0,  1,  0 },
        .start_sign = {  1, -1,  1 },
        .width_axis = 2,
        .height_axis = 1
    },
    {
        .normal = {  0, -1,  0 },
        .right = {  1,  0,  0 },
        .up = {  0,  0,  1 },
        .start_sign = { -1, -1, -1 },
        .width_axis = 0,
        .height_axis = 2
    },
    {
        .normal = {  0,  1,  0 },
        .right = {  1,  0,  0 },
        .up = {  0,  0, -1 },
        .start_sign = { -1,  1,  1 },
        .width_axis = 0,
        .height_axis = 2
    },
    {
        .normal = {  0,  0, -1 },
        .right = { -1,  0,  0 },
        .up = {  0,  1,  0 },
        .start_sign = {  1, -1, -1 },
        .width_axis = 0,
        .height_axis = 1
    },
    {
        .normal = {  0,  0,  1 },
        .right = {  1,  0,  0 },
        .up = {  0,  1,  0 },
        .start_sign = { -1, -1,  1 },
        .width_axis = 0,
        .height_axis = 1
    }
};

BSGFXAPI const bsgfx_TileAxis* _bsgfx_tileAxes() {
    return _bsgfx_tile_axes;
}

 /**
  Tile Coordinate
  */
BSGFXAPI void _val_bsgfx_tileCoordinate(const bsgfx_Primitive* primitive, int axis, int index, bs_ivec2* out) {
    BSGFX_VALIDATE((index - primitive->first_tile) >= 0,,);

    _bsgfx_tileCoordinate(primitive, axis, index, out);
}

BSGFXAPI void _bsgfx_tileCoordinate(const bsgfx_Primitive* primitive, int axis, int index, bs_ivec2* out) {
    int local = index - primitive->first_tile;

    for (int a = 0; a < axis; a++) {
        bsgfx_TileAxis* ax_prev = &_bsgfx_tile_axes[a];

        int w_prev = (int)(primitive->scale.a[ax_prev->width_axis] * 2.0f);
        int h_prev = (int)(primitive->scale.a[ax_prev->height_axis] * 2.0f);

        local -= (w_prev * h_prev);
    }

    bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

    int width = (int)(primitive->scale.a[ax->width_axis] * 2.0f);

    *out = BS_IV2(local % width, local / width);
}

 /**
  Tile Axis
  */
BSGFXAPI void _val_bsgfx_tileAxis(const bsgfx_Primitive* primitive, int index, int* out) {
    BSGFX_VALIDATE((index - primitive->first_tile) >= 0, , );

    _bsgfx_tileAxis(primitive, index, out);
}

BSGFXAPI void _bsgfx_tileAxis(const bsgfx_Primitive* primitive, int index, int* out) {
    int local = index - primitive->first_tile;

    for (int axis = 0; axis < 6; axis++) {
        bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

        int width = (int)(primitive->scale.a[ax->width_axis] * 2.0f);
        int height = (int)(primitive->scale.a[ax->height_axis] * 2.0f);

        int count = width * height;

        if (local < count) {
            *out = axis;
            return;
        }

        local -= count;
    }

    *out = -1;
}

 /**
  Tile Index
  */
BSGFXAPI void _val_bsgfx_tileIndex(const bsgfx_Primitive* primitive, int axis, int x, int y, bs_U32* out) {
    *out = 0;
    BSGFX_VALIDATE(axis < 6,,);

    _bsgfx_tileIndex(primitive, axis, x, y, out);
}

BSGFXAPI void _bsgfx_tileIndex(const bsgfx_Primitive* primitive, int axis, int x, int y, bs_U32* out) {
    float sx = primitive->scale.x;
    float sy = primitive->scale.y;
    float sz = primitive->scale.z;

    bs_vec3 scale_vec = { sx, sy, sz };

    bs_U32 index = primitive->first_tile;

    for (int a = 0; a < axis; a++) {
        bsgfx_TileAxis* ax_prev = &_bsgfx_tile_axes[a];

        int w_prev = (int)(scale_vec.a[ax_prev->width_axis] * 2.0f);
        int h_prev = (int)(scale_vec.a[ax_prev->height_axis] * 2.0f);

        index += (w_prev * h_prev);
    }

    bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

    int width = (int)(scale_vec.a[ax->width_axis] * 2.0f);
    int height = (int)(scale_vec.a[ax->height_axis] * 2.0f);

    if (x < 0 || x >= width || y < 0 || y >= height) {
        *out = index;
        return;
    }

    index += (y * width + x);

    *out = index;
}

BSGFXAPI void _bsgfx_tilePosition(const bsgfx_Primitive* primitive, int axis, int x, int y, bs_vec3* out) {
    bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

    bs_vec3 right, up, start;
    bs_qRotateV3(&primitive->rotation, &ax->right, &right);
    bs_qRotateV3(&primitive->rotation, &ax->up, &up);
    bs_qRotateV3(&primitive->rotation, &(bs_vec3) {
        ax->start_sign.x * primitive->scale.x,
        ax->start_sign.y * primitive->scale.y,
        ax->start_sign.z * primitive->scale.z
    }, &start);

    bs_v3Add(&start, &primitive->position, &start);

    bs_vec3 tile_origin = start;
    bs_vec3 right_scaled;
    bs_v3MulS(&right, (float)x, &right_scaled);
    bs_v3Add(&tile_origin, &right_scaled, &tile_origin);
    bs_vec3 up_scaled;
    bs_v3MulS(&up, (float)y, &up_scaled);
    bs_v3Add(&tile_origin, &up_scaled, &tile_origin);

    *out = tile_origin;
}

BSGFXAPI void _bsgfx_tileRotation(int axis, bs_vec4* out) {
    bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

    bs_vec3 right = ax->right;
    bs_vec3 up = ax->normal;
    bs_vec3 forward;
    bs_v3Cross(&right, &up, &forward);

    bs_mat3 m = {
        right.x, up.x, forward.x,
        right.y, up.y, forward.y,
        right.z, up.z, forward.z
    };

    bs_m3ToQ(&m, out);
}

BSGFXAPI void _bsgfx_tileEulerRotation(int axis, bs_vec3* out) {
    switch (axis) {
    case 0: *out = BS_V3(0, 90, 0); break;
    case 1: *out = BS_V3(0, -90, 0); break;
    case 2: *out = BS_V3(90, 0, 0); break;
    case 3: *out = BS_V3(0, 0, 0); break;
    case 4: *out = BS_V3(0, 90, 0); break;
    case 5: *out = BS_V3(0, 0, 0); break;
    }

    *out = BS_V3(0, 0, 0);
}



  /*==============================================================================
   * Batching
   *============================================================================*/

BSGFXAPI void _bsgfx_batchTile(const bs_Batch* batch, const bs_U32* offset, const bs_Quad* quad, bs_vec3 normal, bs_U32 index, int image_index) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec3, bs_Normal,
        bs_vec3, bs_Texture,
        uint, bsgfx_Index
    );

    bs_batchVertex(&declaration, &(bs_Vertex) { quad->a, normal, BS_V3(quad->ca.x, quad->ca.y, image_index), index });
    bs_batchVertex(&declaration, &(bs_Vertex) { quad->b, normal, BS_V3(quad->cb.x, quad->cb.y, image_index), index });
    bs_batchVertex(&declaration, &(bs_Vertex) { quad->c, normal, BS_V3(quad->cc.x, quad->cc.y, image_index), index });
    bs_batchVertex(&declaration, &(bs_Vertex) { quad->d, normal, BS_V3(quad->cd.x, quad->cd.y, image_index), index });
}

BSGFXAPI void _bsgfx_pushTile(const bs_Batch* batch, const bs_Quad* quad, bs_vec3 normal, bs_U32 index, int image_index, bs_Range* out_range) {
    int index_offset = batch->indices.count;

    int indices[] = {
        1, 2, 0, 2, 1, 3
    };

    bs_ensureBatchSize(batch, 6, 4);
    bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bsgfx_batchTile(batch, &batch->vertices.count, quad, normal, index, image_index);

    *out_range = bs_batchRange(batch, index_offset);
}

BSGFXAPI void _bsgfx_pushTileAt(
    const bs_Batch* batch,
    const bsgfx_Primitive* primitive,
    int axis,
    int x,
    int y,
    bs_U32 index,
    int image_index, 
    bs_U32* out)
{
    bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

    bs_vec3 right, up, normal, start;
    bs_qRotateV3(&primitive->rotation, &ax->right, &right);
    bs_qRotateV3(&primitive->rotation, &ax->up, &up);
    bs_qRotateV3(&primitive->rotation, &ax->normal, &normal);

    bs_qRotateV3(&primitive->rotation, &(bs_vec3) {
        ax->start_sign.x * primitive->scale.x,
        ax->start_sign.y * primitive->scale.y,
        ax->start_sign.z * primitive->scale.z
    }, &start);

    bs_v3Add(&start, &primitive->position, &start);

    bs_vec3 tile_origin = start;
    bs_vec3 right_scaled;
    bs_v3MulS(&right, (float)x, &right_scaled);
    bs_v3Add(&tile_origin, &right_scaled, &tile_origin);
    bs_vec3 up_scaled;
    bs_v3MulS(&up, (float)y, &up_scaled);
    bs_v3Add(&tile_origin, &up_scaled, &tile_origin);

    bs_vec3 a = tile_origin;
    bs_vec3 b;
    bs_v3Add(&a, &right, &b);
    bs_vec3 c;
    bs_v3Add(&a, &up, &c);
    bs_vec3 d;
    bs_v3Add(&c, &right, &d);

    bs_Quad quad = {
        .a = a, .b = b, .c = c, .d = d,
        .ca = { 0, 0 },
        .cb = { 1, 0 },
        .cc = { 0, 1 },
        .cd = { 1, 1 },
    };

    bs_U32 idx = bsgfx_index24(index, axis);
    bs_Range range;
    _bsgfx_pushTile(batch, &quad, normal, idx, image_index, &range);

    *out = index + 1;
}

static bs_U32 _bsgfx_pushTileAxis(
    bs_Batch* batch,
    bsgfx_Primitive* primitive,
    int axis,
    bs_U32 index)
{
    bsgfx_TileAxis* ax = &_bsgfx_tile_axes[axis];

    float sx = primitive->scale.x;
    float sy = primitive->scale.y;
    float sz = primitive->scale.z;

    bs_vec3 scale = { sx, sy, sz };

    int width = (int)(scale.a[ax->width_axis] * 2.0f);
    int height = (int)(scale.a[ax->height_axis] * 2.0f);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            _bsgfx_pushTileAt(batch, primitive, axis, x, y, index, 0, &index);
        }
    }

    return index;
}



  /*==============================================================================
   * Loading Tile Resources
   *============================================================================*/

static void _bsgfx_loadTileTextures(int package_id) {
    bs_Result result;

    if (_bsgfx_count(BSGFX_TYPE_PRIMITIVE) == 0) // todo better check
        return;

    bs_Queue* queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;

    bs_Object* tile_image = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_TILE, BS_OBJECT_FORCE_DESTROY);
    result = bs_loadImageN(
        queue,
        tile_image, 
        package_id, 
        BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_DST_BIT,
        BS_CONSTANT_STRING("textureArrays/tiles")
    );
    if (result != BS_RESULT_OK)
        return;

    // white image buffer
    bs_Object* staging_buffer = BS_BUFFER(-1, 0, 0);
    result = bs_buffer(staging_buffer, 
        BSGFX_TILE_SIZE.x * BSGFX_TILE_SIZE.y * 4,
        BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0
    );
    if (result != BS_RESULT_OK)
        return;

    result = bs_mapBuffer(staging_buffer, BS_U32_MAX);
    if (result != BS_RESULT_OK)
        return;

   // bs_foreachFile(_bsgfx_loadTileTexture, &offset, "textures/tiles/");

    result = bs_bindImages(BSGFX_SET_34_24, BSGFX_BINDING_34_24, &(bs_ImageDescriptor) {
        .image = tile_image->image,
        .sampler = bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler,
        .layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
    }, 1);
    if (result != BS_RESULT_OK)
        return;

    bs_destroyBuffer(staging_buffer);

    bs_infoN(BS_CONSTANT_STRING("Loaded tile textures\n"));
}

static void _bsgfx_mapTile(const bsgfx_RawTile* unmapped, bsgfx_Tile* mapped) {
    const int tile_count = _bsgfx_count(BSGFX_TYPE_TILE);

    bs_Image* image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_TILE)->image;

    *mapped = (bsgfx_Tile){
        .coords = unmapped->coords,
        .flags = unmapped->flags,
        .index = 0,
        .axis = unmapped->axis,
        .image_index = bs_queryImageIndexHash(image, unmapped->texture_hash, NULL),
        // .primitive = unmapped->primitive,
        // .tile_type = unmapped->tile_type,
    };

    int primitive_id = _bsgfx_queryPrimitive(&unmapped->primitive);
    if (primitive_id >= 0) {
        bsgfx_RawPrimitive* raw_primitive = _bsgfx_getRaw(BSGFX_TYPE_PRIMITIVE, primitive_id);
        bsgfx_RawPrimitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, primitive_id);
        _bsgfx_tileIndex(primitive, mapped->axis, mapped->coords.x, mapped->coords.y, &mapped->index);
    }
}

BSGFXAPI void _bsgfx_loadTiles(int package_id, bool force_destroy) {
    bs_Result result;

    _bsgfx_loadTileTextures(package_id);

    _bsgfx_type(
        BSGFX_TYPE_TILE,
        package_id,
        BSGFX_TILE_VERSION,
        "tiles", "tile",
        sizeof(bsgfx_RawTile), sizeof(bsgfx_Tile), _bsgfx_mapTile,
        0, 0, 0, 0);

    bs_Object* primitive_tiles_object = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_PRIMITIVE_TILES, force_destroy ? BS_OBJECT_FORCE_DESTROY : 0);
    result = bs_batch(primitive_tiles_object, sizeof(bs_U32), $vs_bsgfx_tile_static(), 0);
    if (result != BS_RESULT_OK)
        return;

    if (!bs_canPushBatch(primitive_tiles_object->batch))
        bs_unpushBatch(primitive_tiles_object->batch);

    int red_material = $red_material()->id;

    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_TILE); i++) {
        bsgfx_RawTile* raw_tile = _bsgfx_getRaw(BSGFX_TYPE_TILE, i);
        bsgfx_Tile* tile = _bsgfx_get(BSGFX_TYPE_TILE, i);
        int primitive_id = _bsgfx_queryPrimitive(&raw_tile->primitive);
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, primitive_id);

        bs_U32 tile_index;
        _bsgfx_pushTileAt(primitive_tiles_object->batch, primitive, tile->axis, tile->coords.x, tile->coords.y, tile->index, tile->image_index, &tile_index);
    }

    /*
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);

        if (primitive->type != BSGFX_PRIMITIVE_TYPE_BOX)
            continue;

        primitive->first_tile = index;
        for (int j = 0; j < _bsgfx_count(BSGFX_TYPE_TILE); j++) {
            bsgfx_RawTile* raw_tile = _bsgfx_getRaw(BSGFX_TYPE_TILE, j);
            bsgfx_Tile* tile = _bsgfx_get(BSGFX_TYPE_TILE, j);
            int tile_primitive_id = _bsgfx_queryPrimitive(&raw_tile->primitive);
            if (tile_primitive_id != i)
                continue;

            _bsgfx_pushTileAt(batch, primitive, tile->axis, tile->coords.x, tile->coords.y, tile->index, tile->image_index);
        }
        primitive->last_tile = index;
    }
    */

    bs_U32 index = 0;
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);

        if (primitive->type != BSGFX_PRIMITIVE_TYPE_BOX)
            continue;

        for (int j = 0; j < 6; j++) {
            index = _bsgfx_pushTileAxis(primitive_tiles_object->batch, primitive, j, index);
        }
    }

    bs_Queue* queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;
    bs_pushBatch(queue, primitive_tiles_object->batch, BS_U32_MAX, BS_U32_MAX);
}

BSGFXAPI void _bsgfx_instanceTiles() {

}
