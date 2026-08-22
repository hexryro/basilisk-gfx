
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
#include <stddef.h>

static bsgfx_PrefabMetadata* _bsgfx_prefabs = NULL;
static int _bsgfx_prefabs_count = 0;

static int bs_comparePrefabZ(const int* a_id, const int* b_id) {
    bsgfx_Type* type = _bsgfx_types_ + BSGFX_TYPE_PREFAB;
    bsgfx_Prefab* a = type->mapped + *a_id;
    bsgfx_Prefab* b = type->mapped + *b_id;

    if (a->position.z == b->position.z) return 0;
    else if (a->position.z < b->position.z) return -1;
    else return 1;
}

static int bs_compareRawPrefabZ(const int* a_id, const int* b_id) {
    bsgfx_Type* type = _bsgfx_types_ + BSGFX_TYPE_PREFAB;
    bsgfx_RawPrefab* a = type->unmapped + *a_id;
    bsgfx_RawPrefab* b = type->unmapped + *b_id;

    if (a->position.z == b->position.z) return 0;
    else if (a->position.z < b->position.z) return -1;
    else return 1;
}

enum {
    BSGFX_SHADOW_COMPUTATION_MESH,
    BSGFX_SHADOW_COMPUTATION_BONE,
    BSGFX_SHADOW_COMPUTATION_MESH_TYPE,
    BSGFX_SHADOW_COMPUTATION_MESH_TEXTURED,
};

static inline void _bsgfx_awaitComputeWrite(bs_Queue* queue) {
    bs_barrier(queue, 0,
        BS_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        BS_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        BS_ACCESS_SHADER_WRITE_BIT,
        BS_ACCESS_SHADER_READ_BIT);
}

BSGFXAPI void _bsgfx_computePrefabShadows(bs_Queue* queue) {
    if (!_bsgfx_prefab_model_)
        return;
    return;
    /*

    bs_setBufferAsync(queue,
        bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer,
        offsetof(bsgfx_Instantiator, computed_volume_vertices),
        BSGFX_NUM_VOLUME_COMPUTATIONS * sizeof(unsigned int), 0);

    // Reset shadow geometry
    bs_Object* prefab_shadows = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_PREFAB_SHADOWS);

    bs_copyAsync(queue,
        prefab_shadows->batch->staging_buffer->buffer,
        prefab_shadows->batch->vertex_buffer->buffer,
        0, 0, BS_U32_MAX);

    bs_barrier(queue, 0,
        BS_PIPELINE_STAGE_TRANSFER_BIT,
        BS_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        BS_ACCESS_TRANSFER_WRITE_BIT,
        BS_ACCESS_SHADER_READ_BIT);

    struct {
        bs_vec3 light_direction;
        int id;
        int subtype_offset;
        int subtype_count;
        int include_flag;
        int exclude_flag;
    } push_constant = { 0 };

    push_constant.light_direction = _poser_->sun_direction;
    push_constant.subtype_offset = 0;
    push_constant.subtype_count = -1;

    push_constant.id = BSGFX_SHADOW_COMPUTATION_MESH;
    push_constant.include_flag = BSGFX_SUBTYPE_HAS_SHADOWS;
    push_constant.exclude_flag = BSGFX_SUBTYPE_HAS_FINE_SHADOWS;

    bs_Pipeline* pipeline;
    bs_Result result = bs_computePipeline($cs_bsgfx_mesh_volume(), 0, &pipeline);

    if (result == BS_RESULT_OK) {
        _bsgfx_awaitComputeWrite(queue);

        bs_pushConstant(queue, pipeline, 0, sizeof(push_constant), &push_constant);
        bs_dispatchAsync(queue, pipeline, 1, 1, 1);
    }
    */
}

BSGFXAPI void _val_bsgfx_renderPrefabShadowVolumes(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(bs_exists(BSGFX_BATCHES, BSGFX_BATCH_PREFAB_SHADOWS),,);
    BSGFX_VALIDATE(bs_exists(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_SCREEN),,);

    _bsgfx_renderPrefabShadowVolumes(scope, queue);
}

BSGFXAPI void _bsgfx_renderPrefabShadowVolumes(bs_RendererScope* scope, bs_Queue* queue) {
    /*
    bs_Pipeline* pipeline;
    bs_PipelineHash hash;

    bs_beginCommentN(queue, BS_CONSTANT_STRING("Shadow Volumes"));

    bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
    bsgfx_Instantiator* metadata = bs_bufferMap(metadata_buffer);

    int count = metadata->computed_volume_vertices[BSGFX_SHADOW_COMPUTATION_MESH];

    if (count > BSGFX_NUM_SHADOW_VERTICES) {
        bs_warnF("Compute shader generated %d/%d vertices", count, BSGFX_NUM_SHADOW_VERTICES);
        return;
    }

    hash = bsgfx_defaultPipelineHash();
    _bsgfx_requiredForShadowVolumes(&hash);
    hash.shaders[0] = $vs_bsgfx_volume();
    hash.shaders[1] = $fs_bsgfx_volume();

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        bs_Batch* prefab_shadows_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_PREFAB_SHADOWS)->batch;

        bs_pushConstant(queue, pipeline, 0, sizeof(_poser_->camera.result), &_poser_->camera.result);
        bs_render(queue, prefab_shadows_batch, pipeline, 0, count, 0, 1);

        bs_barrier(queue, 0,
            BS_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);
    }

    hash = bsgfx_defaultPipelineHash();
    _bsgfx_requiredForShadowVolumes(&hash);

    hash.shaders[0] = $vs_bsgfx_color_percentage();
    hash.shaders[1] = $fs_bsgfx_volume_screen();

    hash.skip_depth_write = true;

    hash.stencil_front = (bs_StencilOperation){
        .compare_op = BS_COMPARE_OP_NOT_EQUAL,
        .compare_mask = 0xFF,
    };

    hash.attachments[3].skip_write = true; // position // TODO: don't hardcode

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        bs_pushConstant(queue, pipeline, 0, sizeof(bs_vec4), &BSGFX_RGBA(BSGFX_SHADOW_COLOR.r, BSGFX_SHADOW_COLOR.g, BSGFX_SHADOW_COLOR.b, BSGFX_SHADOW_COLOR.a));
        bs_render(queue, bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_SCREEN)->batch, pipeline, 0, BS_U32_MAX, 0, 1);
    }

    bs_endComment(queue);
    */
}

static void _bsgfx_mapPrefab(bsgfx_RawPrefab* unmapped, bsgfx_Prefab* mapped) {
    bs_Model* model = _bsgfx_prefab_model_;
    bs_Mesh* mesh = bs_queryMeshHash(model, unmapped->name_hash);

    int mesh_id = mesh ? mesh - model->meshes : -1;

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

    bsgfx_Material* material = unmapped->material_hash ? _bsgfx_queryMaterialHash(unmapped->material_hash) : 0;

    *mapped = (bsgfx_Prefab){
        .position = unmapped->position,
        .material_id = material ? material->id : 0,
        .mesh_id = mesh_id,
        .scale = unmapped->scale,
        .guid = unmapped->guid,
        .texture_id = unmapped->texture_hash ? bs_queryAtlasHash(atlas, unmapped->texture_hash) : -1,
        .z_order = unmapped->z_order,
        .flags = unmapped->flags,
        .shadow_subtype = -1,
    };

    bs_eulToQ(&unmapped->rotation, &mapped->rotation);
}

static void _bsgfx_destroyPrefabVarieties() {
    bs_Model* model = _bsgfx_prefab_model_;


    if (_bsgfx_prefabs) {
        for (int i = 0; i < _bsgfx_prefabs_count; i++) {
            if (_bsgfx_prefabs[i].varieties)
                bs_free(_bsgfx_prefabs[i].varieties);
        }
        bs_free(_bsgfx_prefabs);
    }
}

/*
static void _bsgfx_loadPrefabVarieties() {
    bs_Model* model = _bsgfx_prefab_model_;
    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
    bs_Json json = bs_loadJson("resources/meshes.json");

    _bsgfx_prefabs = bs_calloc(model->meshes_count, sizeof(*_bsgfx_prefabs));
    _bsgfx_prefabs_count = model->meshes_count;

    for (int i = 0; i < model->meshes_count; i++) {
        bs_JsonValue mesh = bs_fetchJson(&json, BS_JSON_UNDEFINED, model->meshes[i].name);
        if (mesh.type != BS_JSON_OBJECT)
            continue;

        bs_Json root = bs_jsonRoot(&json, mesh.as_object);
        bs_JsonValue varieties = bs_fetchJson(&root, BS_JSON_ARRAY, "varieties");

        _bsgfx_prefabs[i].varieties = bs_malloc(varieties.size * sizeof(bsgfx_PrefabVariety));
        _bsgfx_prefabs[i].variety_count = varieties.size;

        for (int j = 0; j < varieties.size; j++) {
            bs_Json variety = bs_jsonRoot(&root, varieties.as_array.as_objects[j]);
            double texture_hash_double = bs_fetchJson(&variety, BS_JSON_NUMBER, "textureHash").as_number;
            bs_U64 texture_hash;
            memcpy(&texture_hash, &texture_hash_double, sizeof(bs_U64));

            _bsgfx_prefabs[i].varieties[j] = (bsgfx_PrefabVariety){
                .texture_id = bs_queryAtlasHash(atlas, texture_hash, NULL),
            };
        }
    }

    bs_destroyJson(&json);
}
*/

BSGFXAPI bsgfx_PrefabMetadata* _bsgfx_prefabMetadata(int mesh_id) {
    return &_bsgfx_prefabs[mesh_id];
}

BSGFXAPI void _val_bsgfx_loadPrefabs(int package_id, bs_Model* model) {
    BSGFX_VALIDATE(bs_exists(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED),,);
    BSGFX_VALIDATE(bs_exists(BSGFX_ATLASES, BSGFX_ATLAS_ANY),,);

    _bsgfx_loadPrefabs(package_id, model);
}

BSGFXAPI void _bsgfx_loadPrefabs(int package_id, bs_Model* model) {
    bs_Batch* batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED)->batch;

    _bsgfx_prefab_model_ = model;

    bs_Batch* volume_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED)->batch;
    _bsgfx_destroyPrefabVarieties();

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

    bsgfx_InstanceType* mesh_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH];
    bsgfx_InstanceType* static_mesh_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH_STATIC];

    if (bs_canPushBatch(batch)) {
        static int* cached_subtypes;
        static int cached_subtypes_count;
        int cached_subtype_offset = 0;

        if (!cached_subtypes) {
            cached_subtypes_count = model->meshes_count * BSGFX_PREFAB_SUBTYPE_COUNT + model->primitives_count + 1; // + 1 for the whole model
            cached_subtypes = bs_malloc(cached_subtypes_count * sizeof(int));
            memset(cached_subtypes, -1, cached_subtypes_count * sizeof(int));
        }

        model->extra = cached_subtypes + cached_subtype_offset++;

        for (int i = 0; i < model->meshes_count; i++) {
            bs_Mesh* mesh = model->meshes + i;
            bs_Range range = { .offset = batch->indices.count };

            for (int j = 0; j < mesh->primitives_count; j++) {
                bs_Primitive* primitive = mesh->primitives + j;

                bs_Range primitive_range = bs_pushPrimitive(batch, primitive);
                range.num += primitive_range.num;

                primitive->extra = cached_subtypes + cached_subtype_offset++;
                if (primitive->extra[BSGFX_PREFAB_SUBTYPE_PRIMITIVE] >= 0)
                    _bsgfx_deleteSubtype(primitive->extra[BSGFX_PREFAB_SUBTYPE_PRIMITIVE]);

                _bsgfx_subtype(static_mesh_instance_type, batch, 0, primitive_range, &primitive->extra[BSGFX_PREFAB_SUBTYPE_PRIMITIVE]);
            }

            mesh->extra = cached_subtypes + cached_subtype_offset;
            for (int j = 0; j < BSGFX_PREFAB_SUBTYPE_COUNT; j++) {
                bsgfx_InstanceSubtype* subtype = mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH];
                if (subtype != NULL)
                    _bsgfx_deleteSubtype(subtype);
            }

            _bsgfx_subtype(static_mesh_instance_type, batch, BSGFX_SUBTYPE_HAS_SHADOWS, range, mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH]);
            _bsgfx_subtype(mesh_instance_type, batch, 0, range, mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE]);
            _bsgfx_subtype(mesh_instance_type, batch, BSGFX_SUBTYPE_HAS_SHADOWS | BSGFX_SUBTYPE_HAS_FINE_SHADOWS, range, mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH_TEXTURED]);
            _bsgfx_subtype(mesh_instance_type, batch, 0, range, mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH_HI_RES_SCREEN]);
            _bsgfx_subtype(mesh_instance_type, batch, 0, range, mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH_LO_RES_SCREEN]);
            _bsgfx_subtype(static_mesh_instance_type, volume_batch, 0, (bs_Range) { 0 }, mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH_VOLUME]);
            cached_subtype_offset += BSGFX_PREFAB_SUBTYPE_COUNT;

        }

        // sktchy
//        _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_MESH_KEY_SPHERE, BSGFX_BATCH_MESH_INSTANCED, 0, bs_pushSphere(batch, (bs_vec3) { 0 }, 1.0, 8, 8, BS_WHITE), true);
//        bs_Model* skateboard = bs_fetch(BS_SOURCE_GFX, BSGFX_MODEL_SKATEBOARD).model;
//        bs_Range skateboard_range = bs_pushMesh(batch, bs_queryMesh(skateboard, "board"));
//        _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_MODEL_SKATEBOARD, BSGFX_BATCH_MESH_INSTANCED, _bsgfx_subtypes[BSGFX_SUBTYPE_HAS_SHADOWS, skateboard_range, true);
//        _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_VOLUME_DOWN_KEY + BSGFX_MODEL_SKATEBOARD, BSGFX_BATCH_MESH_INSTANCED, _bsgfx_subtypes[BSGFX_SUBTYPE_HAS_SHADOWS, skateboard_range, true);
//        _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_MESH_KEY_SKATEBOARD_WHEELS, BSGFX_BATCH_MESH_INSTANCED, _bsgfx_subtypes[BSGFX_SUBTYPE_HAS_SHADOWS, bs_pushMesh(batch, bs_queryMesh(skateboard, "wheels")), true);

        bs_Quad plane;
        bs_quad(&BS_V3(0, 0, 0), &BS_V2(1, 1), &plane);
        _bsgfx_subtype(mesh_instance_type, batch, BSGFX_SUBTYPE_HAS_SHADOWS, bs_pushQuad(batch, &plane, BS_WHITE), &_bsgfx_subtypes_[BSGFX_SUBTYPE_PLANE_MESH]);
    }

    _bsgfx_type(
        BSGFX_TYPE_PREFAB,
        package_id,
        BSGFX_PREFAB_VERSION,
        "prefabs", "prefab",
        sizeof(bsgfx_RawPrefab), sizeof(bsgfx_Prefab), _bsgfx_mapPrefab,
        0, 0, 0, 0);

   // _bsgfx_instancePrefabs();

    //bsgfx_loadPrefabVarieties();

}

BSGFXAPI void _bsgfx_prefabTransform(bsgfx_Prefab* prefab, bs_mat4* out) {
    bs_mat4 m = BS_MAT4_IDENTITY;

    bs_m4Translate(&m, &prefab->position, &m);
    bs_m4Rotate(&m, &prefab->rotation, &m);
    bs_m4Scale(&m, &prefab->scale, &m);

    *out = m;
}

BSGFXAPI int _bsgfx_instancePrefabModel(int mesh_id, bs_mat4 transform, bsgfx_PrefabSubtype prefab_subtype, int material_id) {
    bs_Mesh* mesh = _bsgfx_prefab_model_->meshes + mesh_id;
    bsgfx_InstanceSubtype* subtype = mesh->extra[prefab_subtype];
    return _bsgfx_instantiate(subtype, &transform, sizeof(bs_mat4), BSGFX_ID_IS_PREFAB, 0, 0, material_id);
}

 /**
  Instance Prefab
  */
BSGFXAPI int _val_bsgfx_instancePrefab(int id, bsgfx_PrefabSubtype prefab_subtype) {
    BSGFX_VALIDATE(_bsgfx_prefab_model_ != NULL, 0,);
    bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, id);
    BSGFX_VALIDATE(prefab->mesh_id >= 0, 0,);

    return _bsgfx_instancePrefab(id, prefab_subtype);
}

BSGFXAPI int _bsgfx_instancePrefab(int id, bsgfx_PrefabSubtype prefab_subtype) {
    bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, id);
    bsgfx_RawPrefab* raw_prefab = _bsgfx_getRaw(BSGFX_TYPE_PREFAB, id);

    bs_Mesh* mesh = _bsgfx_prefab_model_->meshes + prefab->mesh_id;

    bs_mat4 transform;
    _bsgfx_prefabTransform(prefab, &transform);

    bsgfx_InstanceSubtype* subtype = mesh->extra[prefab_subtype];
    int material = prefab->material_id;
    int texture = prefab->texture_id;
    int quad_instance_offset = -1;

    bs_U32 flags = BSGFX_ID_IS_PREFAB;

    if (texture >= 0) {
        bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

        bs_vec2 size = bs_atlasSize(atlas, texture);

        bs_mat4 quad_transform = BS_MAT4_IDENTITY;
        bs_vec3 quad_translation = BS_V3(
            prefab->position.x * BSGFX_TILE_SIZE.x / 2.0,
            -(prefab->position.z - prefab->position.y) * BSGFX_TILE_SIZE.y / 2.0,
            prefab->position.z);

        bs_m4Translate(&quad_transform, &quad_translation, &quad_transform);
        bs_m4Scale(&quad_transform, &BS_V3(size.x, size.y, 0.0), &quad_transform);

        if (prefab_subtype != BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE) { // TODO: improve
            bs_vec4 coords = bs_atlasCoordinates(atlas, texture);
            if (!(raw_prefab->flags & BSGFX_PREFAB_HIDDEN)) {
                bs_mat4x3 mat = bs_m4x3(&quad_transform);
                if (raw_prefab->flags & BSGFX_PREFAB_WRITE_POSITION)
                    quad_instance_offset = _bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT], mat, coords, flags, id, 0);
                else
                    quad_instance_offset = _bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT], mat, coords, flags, id, 0);
            }
        }
    }

    //if (_bsgfx_procs_.bsmod_isSelected && _bsgfx_procs_.bsmod_isSelected(BSGFX_TYPE_PREFAB, id))
    //    flags |= BSGFX_ID_SELECTED;
    return _bsgfx_instantiate(subtype, &transform, sizeof(bs_mat4), flags, quad_instance_offset, id, material);
}

BSGFXAPI void _bsgfx_instancePrefabs() {
    int count = _bsgfx_count(BSGFX_TYPE_PREFAB);
    if (count <= 0) return;

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
    bs_Model* model = _bsgfx_prefab_model_;

    for (int i = 0; i < count; i++) {
        bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, i);

        bsgfx_PrefabSubtype subtype = BSGFX_PREFAB_SUBTYPE_MESH;
        if (prefab->flags & BSGFX_PREFAB_TEXTURED_SHADOWS)
            subtype = BSGFX_PREFAB_SUBTYPE_MESH_TEXTURED;
        _bsgfx_instancePrefab(i, subtype);
    }
}

BSGFXAPI void _bsgfx_renderPrefabs(bs_Queue* queue, bs_Pipeline* pipeline, int key_start) {
    assert(_bsgfx_prefab_model_);
    bs_Model* model = _bsgfx_prefab_model_;

    for (int i = 0; i < model->meshes_count; i++) {
        bs_Mesh* mesh = model->meshes + i;
        if (!mesh->extra)
            continue;
        bsgfx_InstanceSubtype* subtype = mesh->extra[key_start];
        _bsgfx_renderSubtype(queue, subtype, pipeline);
    }
}

/*
BSGFXAPI void _bsgfx_renderScenePrefabs(bs_Queue* queue) {
    if (!_bsgfx_prefab_model_)
        return;

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

    struct {
        bs_mat4 camera;
        bs_vec4 uv;
        bs_vec4 sun_direction;
    } mesh_push_const = {
        .camera = _poser_->camera.result,
        .uv = bs_atlasCoordinates(atlas, bs_queryAtlas(atlas, "white")),
        .sun_direction.xyz = _poser_->sun_direction,
    };

    bs_PipelineHash hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_static_instanced();
    hash.shaders[1] = $fs_bsgfx_model();
    hash.cull_type = _bsgfx_settings_.cull_backfaces ? BS_CULL_MODE_BACK_BIT : BS_CULL_MODE_NONE;

    bs_Pipeline* mesh_pipeline;
    if (bs_pipeline(queue, &hash, &mesh_pipeline) == BS_RESULT_OK) {
        bs_beginCommentN(queue, BS_CONSTANT_STRING("Prefabs"));

        bs_pushConstant(queue, mesh_pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        _bsgfx_renderPrefabs(queue, mesh_pipeline, BSGFX_PREFAB_SUBTYPE_MESH);

        bs_endComment(queue);
    }
}
*/

BSGFXAPI void _bsgfx_renderPrefabPrimitives(bs_Queue* queue, bs_Pipeline* pipeline, int key_start) {
    if (_bsgfx_count(BSGFX_TYPE_PREFAB) <= 0)
        return;

    bs_Model* model = _bsgfx_prefab_model_;

    for (int i = 0; i < model->meshes_count; i++) {
        bs_Mesh* mesh = model->meshes + i;

        for (int j = 0; j < mesh->primitives_count; j++) {
            bs_Primitive* primitive = mesh->primitives + j;
            bsgfx_InstanceSubtype* subtype = primitive->extra[key_start];
            _bsgfx_renderSubtype(queue, subtype, pipeline);
        }
    }
}

BSGFXAPI int _bsgfx_queryPrefabId(const bs_GUID* guid) {
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PREFAB); i++) {
        bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, i);
        if (bs_sameGuid(guid, &prefab->guid))
            return i;
    }

    return -1;
}

BSGFXAPI int _bsgfx_closestPrefab(bs_U64 mesh_name_hash, bs_vec3 position, float radius) {
    bs_Model* model = _bsgfx_prefab_model_;

    // todo use sweep data somehow
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PREFAB); i++) {
        bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, i);
        bs_Mesh* mesh = model->meshes + prefab->mesh_id;

        if (mesh->name_hash != mesh_name_hash)
            continue;

        if (bs_v3Distance(&prefab->position, &position) < radius)
            return i;
    }

    return -1;
}
