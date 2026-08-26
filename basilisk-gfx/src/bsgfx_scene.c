
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

#include <bsgfx_cache.h>
#include <bsgfx_internal.h>
#include <bsgfx_internal.gen.h>

#include <assert.h>

#include <basilisk-core.h>

void _bsgfx_allocateMaterials();
static void _bsgfx_loadResources() {
    bs_Result result;

    bs_Queue* queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;

    bs_Object* jonts_buffer = BS_BUFFER(BSGFX_BUFFERS, BSGFX_BUFFER_JOINTS, false);
    result = bs_buffer(jonts_buffer,
        1024 * sizeof(bs_mat4),  // TODO Resize
        BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result == BS_RESULT_OK && bs_mapBuffer(jonts_buffer->buffer, BS_U32_MAX) == BS_RESULT_OK) {
        bs_bindBuffer(BSGFX_SET_JOINTS, BSGFX_BINDING_JOINTS, jonts_buffer->buffer);
    }
    
    // batches
    bs_Object* screen_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_SCREEN, 0);
    bs_Object* volume_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_COMPUTED, BS_OBJECT_HAS_SWAPS_BIT);
    bs_Object* prefab_volume_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_PREFAB_SHADOWS, 0);
    bs_Object* volume_screen_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_SCREEN, 0);
    bs_Object* line_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_LINE_INSTANCED, 0);
    bs_Object* point_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_POINT_INSTANCED, 0);
    bs_Object* sphere_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_SPHERE_INSTANCED, 0);
    bs_Object* quad_instance_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_QUAD_INSTANCED, 0);
    bs_Object* mesh_instance_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED, 0);
    bs_Object* bone_instance_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_BONE_INSTANCED, 0);

    bs_batch(screen_batch, sizeof(bs_U32), $vs_bsgfx_color_percentage(), 0);
    bs_batch(volume_batch, 0, $vs_bsgfx_volume(), 0);
    bs_batch(prefab_volume_batch, 0, $vs_bsgfx_volume(), 0);
    bs_batch(volume_screen_batch, sizeof(bs_U32), $vs_bsgfx_color_percentage(), 0);
    bs_batch(line_batch, sizeof(bs_U32), $vs_bsgfx_line_instanced(), 0);
    bs_batch(point_batch, sizeof(bs_U32), $vs_bsgfx_point_instanced(), 0);
    bs_batch(sphere_batch, sizeof(bs_U32), $vs_bsgfx_mesh_instanced(), 0);
    bs_batch(quad_instance_batch, sizeof(bs_U32), $vs_bsgfx_quad_instanced(), 0);
    bs_batch(mesh_instance_batch, sizeof(bs_U32), $vs_bsgfx_mesh_instanced(), 0);
    bs_batch(bone_instance_batch, sizeof(bs_U32), $vs_bsgfx_bone_instanced(), BS_BATCH_RAY_TRACEABLE);

    if (mesh_instance_batch && bs_canPushBatch(mesh_instance_batch->batch)) {
        _bsgfx_instanceType(sizeof(bsgfx_MeshInstance), BSGFX_SET_MESH_INSTANCES, BSGFX_BINDING_MESH_INSTANCES, &_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH]);
        _bsgfx_instanceType(sizeof(bsgfx_MeshInstance), BSGFX_SET_MESH_STATIC_INSTANCES, BSGFX_BINDING_MESH_STATIC_INSTANCES, &_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH_STATIC]);
    }

    if (sphere_batch && bs_canPushBatch(sphere_batch->batch)) {
        bs_Range cone_range = bs_pushCone(sphere_batch->batch, 10, 2.0, 1.0, BS_WHITE);
        bs_Range sphere_range = bs_pushSphere(sphere_batch->batch, (bs_vec3) { 0 }, 1.0, 8, 8, BS_WHITE);

        _bsgfx_subtype(_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH], sphere_batch->batch, 0, cone_range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_CONE_MESH]);
        _bsgfx_subtype(_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH], sphere_batch->batch, 0, sphere_range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_SPHERE_MESH]);
    }

    bs_Quad quad;
    bs_quad(&(bs_vec3) { 0 }, & (bs_vec2) { 1.0, 1.0 }, & quad);

    result = _bsgfx_instanceType(sizeof(bsgfx_QuadInstance), BSGFX_SET_QUAD_INSTANCES, BSGFX_BINDING_QUAD_INSTANCES, &_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_QUAD]);

    if (result == BS_RESULT_OK) {

        if (quad_instance_batch && bs_canPushBatch(quad_instance_batch->batch)) {

            bs_Range range = bs_pushQuad(quad_instance_batch->batch, &quad, BS_WHITE);

            bsgfx_InstanceType* quad_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_QUAD];
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_CORNER_GRADIENT]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_UI]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_STENCIL]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_HUE]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_ALPHA]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_DITHER]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_QUAD_MATERIAL_TEXTURE]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_TILE]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_TILE_2]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_TILE_ICON]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_64_HI]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_256_HI]);
            _bsgfx_subtype(quad_instance_type, quad_instance_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_FONT]);

            bs_pushBatch(queue, quad_instance_batch->batch, BS_U32_MAX, BS_U32_MAX);
        }
    }

    // TODO: Shadow volume rewrite
    /*
    if (bs_canPushBatch(volume_batch->batch)) {
        bs_ensureBatchSize(volume_batch->batch, 0, BSGFX_NUM_SHADOW_VERTICES);

        bs_pushQuad(volume_screen_batch->batch, &quad, BSGFX_SHADOW_COLOR);

        bs_pushBatch(queue, volume_batch->batch, 0, BSGFX_NUM_SHADOW_VERTICES);
        bs_bindBuffer(BSGFX_SET_VOLUME_OUT_VERTICES, BSGFX_BINDING_VOLUME_OUT_VERTICES, volume_batch->batch->vertex_buffer->buffer);
    }
    */

    if (bs_canPushBatch(screen_batch->batch)) {
        bs_pushQuad(screen_batch->batch, &quad, BS_WHITE);
        bs_pushQuad(screen_batch->batch, &quad, BS_WHITE);
       // const float offset = 0.75;
       // bs_pushQuad(screen_batch, bs_quad(BS_V3(0.125, 0.125, 0.0), bs_v2V1(offset)), BS_WHITE);
        bs_pushBatch(queue,screen_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    bs_Object* mesh_volume_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED, true);
    result = bs_batch(mesh_volume_batch, 0, $vs_bsgfx_volume(), 0);

    // TODO: Shadow volume rewrite
    /*
    if (result == BS_RESULT_OK && bs_canPushBatch(mesh_volume_batch->batch)) {
        bs_pushBatch(queue, mesh_volume_batch->batch, 0, BSGFX_PRE_COMPUTED_VOLUME_SIZE);
      //  bs_bindBuffer(BSGFX_SET_VOLUME_OUT_VERTICES, BSGFX_BINDING_VOLUME_OUT_VERTICES_MESH_TYPE, mesh_volume_batch->batch->vertex_buffer->buffer);
    }
    */

    //bs_loadAllResources(BSGFX_RESOURCE_SCRIPT, 0);
    //bsgfx_loadModels(NULL, 0);
    //bsgfx_loadMinimap();
    _bsgfx_allocateMaterials();

  //  _bsgfx_loadMaterials();

    bs_ivec2 resolution = bs_resolution(bs_scope()->context);
    resolution.x /= BSGFX_PIXEL_SCALE;
    resolution.y /= BSGFX_PIXEL_SCALE;

    if (bs_exists(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED)) {
        if (bs_canPushBatch(mesh_instance_batch->batch)) {
            bs_Range box_range = bs_pushCube(mesh_instance_batch->batch, BS_WHITE);
            bs_Range sphere_range = bs_pushSphere(mesh_instance_batch->batch, BS_V3(0, 0, 0), 1.0, 16, 16, BS_WHITE);
            bs_Range sphere_high_quality_range = bs_pushSphere(mesh_instance_batch->batch, BS_V3(0, 0, 0), 1.0, 64, 64, BS_WHITE);

            bsgfx_InstanceType* mesh_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH];

            _bsgfx_subtype(mesh_instance_type, mesh_instance_batch->batch, BSGFX_SUBTYPE_HAS_SHADOWS, box_range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_PRIMITIVE_BOX]);
            _bsgfx_subtype(mesh_instance_type, mesh_instance_batch->batch, BSGFX_SUBTYPE_HAS_SHADOWS, sphere_range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_PRIMITIVE_SPHERE]);
        }
    }

    /*
    bs_Object* ray_trace_output = BS_IMAGE(-1, 0, 0);

    if (bs_exists(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST) &&
        bs_image(ray_trace_output, resolution, 0, BS_FORMAT_R32G32B32A32_SFLOAT, BS_IMAGE_USAGE_STORAGE_BIT) == BS_RESULT_OK) 
    {
        bs_transition(ray_trace_output->image, 0, BS_IMAGE_LAYOUT_UNDEFINED, BS_IMAGE_LAYOUT_GENERAL);
        bs_bindImage(BSGFX_SET_RAY_TRACE_OUTPUT, BSGFX_BINDING_RAY_TRACE_OUTPUT, ray_trace_output->image, bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler, BS_IMAGE_LAYOUT_GENERAL);
    }

    bs_RayTracer* ray_tracer = bs_rayTracer(BSGFX_RAY_TRACER_MAIN, 0, $rgen_main(), $rmiss_main(), NULL)->ray_tracer;
    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
        bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);
        bs_Aabb aabb = {
            .min = bs_v3Add(primitive->position, bs_v3MulS(primitive->scale, -1)),
            .max = bs_v3Add(primitive->position, primitive->scale),
        };
        bs_accelerateAabb(ray_tracer, aabb);
    }
    bs_accelerateBatch(ray_tracer, bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_TEST)->batch);
    bs_build(ray_tracer);

    bs_bindAccelerationStructure(BSGFX_SET_ACCELERATION_STRUCTURE, BSGFX_BINDING_ACCELERATION_STRUCTURE, ray_tracer);
    */

    if (bone_instance_batch->batch && bs_canPushBatch(bone_instance_batch->batch)) {
        _bsgfx_instanceType(sizeof(bsgfx_BoneInstance), BSGFX_SET_BONE_INSTANCES, BSGFX_BINDING_BONE_INSTANCES, &_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_BONE]);
    }

    if (mesh_instance_batch && bs_canPushBatch(mesh_instance_batch->batch)) {
        bs_Range pyramid = bs_pushBipyramid(mesh_instance_batch->batch, (bs_vec3) { 0 }, 0.75, 1.0, BS_WHITE);
        bsgfx_InstanceType* mesh_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH];

        _bsgfx_subtype(mesh_instance_type, mesh_instance_batch->batch, BSGFX_SUBTYPE_HAS_SHADOWS, pyramid, &_bsgfx_subtypes_[BSGFX_SUBTYPE_BIPYRAMID]);
    }

    if (point_batch && bs_canPushBatch(point_batch->batch)) {
        result = _bsgfx_instanceType(sizeof(bsgfx_PointInstance), BSGFX_SET_POINT_INSTANCES, BSGFX_BINDING_POINT_INSTANCES, &_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_POINT]);

        if (result == BS_RESULT_OK) {
            bsgfx_InstanceType* mesh_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_MESH];

            bs_Range range = bs_pushPoint(point_batch->batch, (bs_vec3) { 0 }, BS_WHITE);

            _bsgfx_subtype(mesh_instance_type, point_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_POINT]);
        }
    }

    if (line_batch && bs_canPushBatch(line_batch->batch)) {
        result = _bsgfx_instanceType(sizeof(bsgfx_LineInstance), BSGFX_SET_LINE_INSTANCES, BSGFX_BINDING_LINE_INSTANCES, &_bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_LINE]);

        if (result == BS_RESULT_OK) {
            bs_Range range = bs_pushLine(line_batch->batch, (bs_vec3) { 0 }, BS_V3(0, 1.0, 0.0), BS_WHITE);

            bsgfx_InstanceType* line_instance_type = _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_LINE];

            _bsgfx_subtype(line_instance_type, line_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_LINE_2D]);
            _bsgfx_subtype(line_instance_type, line_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_LINE]);
            _bsgfx_subtype(line_instance_type, line_batch->batch, 0, range, &_bsgfx_subtypes_[BSGFX_SUBTYPE_LINE_DEPTHLESS]);
        }
    }

     /**
      Load level after bsgfx resources, before bindings and subtype creation
      */
    if (_bsgfx_callbacks_.loadScene)
        _bsgfx_callbacks_.loadScene();

    if (bs_exists(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED)) { 
        mesh_instance_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED);
        if (bs_canPushBatch(mesh_instance_batch->batch)) {
            bs_pushBatch(queue, mesh_instance_batch->batch, BS_U32_MAX, BS_U32_MAX);
            bs_bindBuffer(BSGFX_SET_VOLUME_IN_VERTICES, BSGFX_BINDING_VOLUME_IN_VERTICES_MESH, mesh_instance_batch->batch->vertex_buffer->buffer);
            bs_bindBuffer(BSGFX_SET_VOLUME_IN_INDICES, BSGFX_BINDING_VOLUME_IN_INDICES_MESH, mesh_instance_batch->batch->index_buffer->buffer);
            //bs_bindBuffer(BSGFX_SET_VOLUME_IN_VERTICES, BSGFX_BINDING_VOLUME_IN_VERTICES_MESH_TYPE, mesh_instance_batch->batch->vertex_buffer->buffer);
            //bs_bindBuffer(BSGFX_SET_VOLUME_IN_INDICES, BSGFX_BINDING_VOLUME_IN_INDICES_MESH_TYPE, mesh_instance_batch->batch->index_buffer->buffer);
        }

    }

    if (point_batch && bs_canPushBatch(point_batch->batch)) {
        bs_pushBatch(queue, point_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    if (line_batch && bs_canPushBatch(line_batch->batch)) {
        bs_pushBatch(queue, line_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    if (bone_instance_batch && bs_canPushBatch(bone_instance_batch->batch)) {
        bs_pushBatch(queue, bone_instance_batch->batch, BS_U32_MAX, BS_U32_MAX);
       // bs_bindBuffer(BSGFX_SET_VOLUME_IN_VERTICES, BSGFX_BINDING_VOLUME_IN_VERTICES_BONE, bone_instance_batch->batch->vertex_buffer->buffer);
       // bs_bindBuffer(BSGFX_SET_VOLUME_IN_INDICES, BSGFX_BINDING_VOLUME_IN_INDICES_BONE, bone_instance_batch->batch->index_buffer->buffer);
    }

    bs_pushBindings();
    bs_pushDescriptors();
    // _bsgfx_preComputeInstanceVolumes();
}

BSGFXAPI void _bsgfx_loadScene(const char* name) {
    bs_logSectionF("Scene \"%s\"", name);

    _bsgfx_current_scene_ = (bsgfx_Scene){
        .name = name,
        .name_hash = bs_stringHash(name),
    };

	_bsgfx_loadResources();

   // if (_bsgfx_procs_.bsmod_onLoad)
   //     bs_runSingle(_bsgfx_procs_.bsmod_onLoad);

    //bs_runSingle(_bsgfx_computePrefabShadows);

    //bs_logObjectDiff();
    //bs_logUnchangedObjects();
    //bs_logBindings();

    if (_bsgfx_prefab_model_) {
        bs_Object* queue_object = BS_QUEUE(-1, 0, 0);
        if (bs_queue(queue_object, 0, BS_QUEUE_COMPUTE_BIT) == BS_RESULT_OK) {
            bs_enqueue(queue_object->queue, _bsgfx_computePrefabShadows);
            bs_stallGPU();
        }
        
        //bsgfx_computePrefabShadows();

    }

    bs_logEndOfSection();

}