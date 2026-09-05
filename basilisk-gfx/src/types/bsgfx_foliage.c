
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
/*
static void _bsgfx_mapFoliage(const bsgfx_RawFoliage* unmapped, bsgfx_Foliage* mapped) {
    *mapped = (bsgfx_Foliage){
        .density = unmapped->density,
        .guid = unmapped->guid,
        .textures_count = unmapped->textures_count,
    };

    for (int i = 0; i < mapped->textures_count; i++) {
        mapped->textures[i] = (struct bsgfx_FoliageTexture){
            //.id =  unmapped->textures[i].texture_hash,
            .color = unmapped->textures[i].color,
        };
    }
}

static void _bsgfx_loadFoliage(bsgfx_Foliage* foliage, bs_String* binary) {
    bs_Batch* batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_FOLIAGE)->batch;
    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

    bs_vec3* vertices = binary->value;
    int num_vertices = binary->len / sizeof(bs_vec3) / 2;
    bs_vec3* normals = binary->value + num_vertices * sizeof(float) * 3;

    for (int i = 0; i < foliage->textures_count; i++) {
        int texture = foliage->textures[i].id;
        bs_vec2 atlas_size = bs_atlasSize(atlas, texture);
        bs_v2DivV1(&atlas_size, BSGFX_TILE_SIZE.x * 2.0 / BSGFX_PIXEL_SCALE, &foliage->textures[i].size);
        foliage->textures[i].coords = bs_atlasCoordinates(atlas, texture, 0);
    }

    if (foliage->textures_count <= 0)
        return;

    BS_VERTEX_DECLARATION(
        declaration, batch, &batch->vertices.count,
        bs_vec4, bs_Position,
        bs_vec3, bs_Normal,
        bs_vec3, bs_Texture,
        bs_RGBA, bs_Color
    );

    //	bs_mat4 transform = bs_transform(position, rotation, scale);
    bs_mat3 rotation = bs_qToMat3(bs_qFromRadians(BS_V3(bs_radians(0), bs_radians(0), bs_radians(-45))));
    for (int i = 0; i < num_vertices; i++) {
        int texture = bs_randRangeI(0, foliage->textures_count - 1);
        bs_vec4 coords = foliage->textures[texture].coords;
        bs_vec2 size = foliage->textures[texture].size;

        bs_Quad q = bs_quad(BS_V3(-size.x / 2.0, size.y / 2.0, 0.0), size);
        bs_m3MulV3(&rotation, &q.a, &q.a);
        bs_m3MulV3(&rotation, &q.b, &q.b);
        bs_m3MulV3(&rotation, &q.c, &q.c);
        bs_m3MulV3(&rotation, &q.d, &q.d);
        bs_vec3 offset_75 = BS_V3(0, 0, .75);
        bs_vec3 moved_position;
        bs_v3Add(&vertices[i], &offset_75, &moved_position);
        bs_moveQuad(&q, moved_position);

        if (normals[i].z < -0.1) {
            q.cb = BS_V2(coords.x, coords.w);
            q.ca = BS_V2(coords.z, coords.w);
            q.cd = BS_V2(coords.x, coords.y);
            q.cc = BS_V2(coords.z, coords.y);
        }
        else {
            q.cb = BS_V2(coords.x, coords.y);
            q.ca = BS_V2(coords.z, coords.y);
            q.cd = BS_V2(coords.x, coords.w);
            q.cc = BS_V2(coords.z, coords.w);
        }

        float random = bs_randRange(0, atlas->mapped[foliage->textures[texture].id].split);
        bs_ensureBatchSize(batch, 6, 4);
        bs_pushIndexV(batch, 6, 1, 2, 0, 2, 1, 3);
        bs_batchVertex(&declaration, &(bs_Vertex) {.bs_Position = bs_v4V3(q.a, foliage->textures[texture].id), .bs_Texture = bs_v3V2(q.ca, random), .bs_Normal = normals[i], .bs_Color = BS_WHITE });
        bs_batchVertex(&declaration, &(bs_Vertex) {.bs_Position = bs_v4V3(q.b, foliage->textures[texture].id), .bs_Texture = bs_v3V2(q.cb, random), .bs_Normal = normals[i], .bs_Color = BS_WHITE });
        bs_batchVertex(&declaration, &(bs_Vertex) {.bs_Position = bs_v4V3(q.c, foliage->textures[texture].id), .bs_Texture = bs_v3V2(q.cc, random), .bs_Normal = normals[i], .bs_Color = BS_WHITE });
        bs_batchVertex(&declaration, &(bs_Vertex) {.bs_Position = bs_v4V3(q.d, foliage->textures[texture].id), .bs_Texture = bs_v3V2(q.cd, random), .bs_Normal = normals[i], .bs_Color = BS_WHITE });
    }
}

void _bsgfx_loadFoliages(int package_id) {
    bs_except(BSX_FAILED_TO_QUERY);
    _bsgfx_type(
        BSGFX_TYPE_FOLIAGE,
        BSGFX_FOLIAGE_VERSION,
        package_id,
        "foliages", "foliage",
        sizeof(bsgfx_RawFoliage), sizeof(bsgfx_Foliage), _bsgfx_mapFoliage,
        offsetof(bsgfx_RawFoliage, textures_count), offsetof(bsgfx_Foliage, textures_count),
        sizeof(struct bsgfx_RawFoliageTexture), sizeof(struct bsgfx_FoliageTexture));
    if (bs_caught())
        return;

    int level_name_len = strlen(_bsgfx_current_scene.name);
    char* path = bs_charStringF("resources/levels/%s/foliage/XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.bin", _bsgfx_current_scene.name);
    bs_Batch* batch = bs_batch(BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_FOLIAGE, 0), sizeof(bs_U32), $vs_bsgfx_foliage(), BS_BATCH_FORCE_DESTROY)->batch;

    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_FOLIAGE); i++) {
        bsgfx_Foliage* foliage = _bsgfx_get(BSGFX_TYPE_FOLIAGE, i);

        char* start = path + sizeof("resources/levels/foliage/") + level_name_len;
        bs_guidToString(&foliage->guid, start);
        strcpy(start + 36, ".bin");

        bs_except(BSX_FAILED_TO_QUERY);
        _bsgfx_queryPrimitive(&foliage->guid);
        if (bs_caught()) {
            bs_warnF("%s does not belong to any primitive!\n", path);
            continue;
        }

        bs_String* binary = bs_loadFile(path);
        if (!binary) {
            bs_warnF("%s does not exist!\n", path);
            continue;
        }

        _bsgfx_loadFoliage(foliage, binary);
        bs_free(binary);
    }

    bs_free(path);

    bs_pushBatch(batch, BS_U32_MAX, BS_U32_MAX);
}

int _bsgfx_queryFoliage(bs_GUID* guid) {
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_FOLIAGE); i++) {
        bsgfx_Foliage* foliage = _bsgfx_get(BSGFX_TYPE_FOLIAGE, i);
        if (bs_sameGuid(&foliage->guid, guid))
            return i;
    }

    char str[37];
    bs_guidToString(guid, str);
    bs_throwBasiliskF(BSX_FAILED_TO_QUERY, "Foliage %s", str);

    return -1;
}

*/