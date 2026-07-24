
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

static void _bsgfx_createRenderers() {
   /**
    high resolution renderer
    */
    bs_Object* hi_res = BS_RENDERER(BSGFX_RENDERERS, BSGFX_RENDERER_HI_RES, BS_OBJECT_HAS_SWAPS_BIT);
    if (bs_renderer(hi_res, BS_RENDERER_AUTO_RESIZE_BIT) == BS_RESULT_OK) {

        bs_ivec2 resolution = bs_resolution();
        bs_Object* hi_res_0_depth = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_HI_RES_0_DEPTH, 0);
        if (bs_image(hi_res_0_depth, resolution, 0, BS_FORMAT_D32_SFLOAT_S8_UINT, BS_IMAGE_ATTACHMENT_BIT) == BS_RESULT_OK) {

            /** subpass 0 */
            bs_output(hi_res->renderer, (bs_Output) {
                .subpass = 0,
                .image = bs_context()->swapchain_image->image,
                .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
                .store_op = BS_ATTACHMENT_STORE_OP_STORE,
                .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
                .new_layout = BS_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            });

            bs_output(hi_res->renderer, (bs_Output) {
                .subpass = 0,
                .image = hi_res_0_depth->image,
                .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
                .store_op = BS_ATTACHMENT_STORE_OP_STORE,
                .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
                .new_layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            });

            /** dependencies */
            bs_dependency(hi_res->renderer, -1, 0, BS_DEPENDENCY_BY_REGION_BIT,
                BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | BS_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
                BS_ACCESS_MEMORY_READ_BIT,
                BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT);

            bs_renderPass(hi_res->renderer);
            bs_framebuffer(hi_res->renderer, bs_resolution());
        }
    }

   /** 
    low resolution renderer 
    */
    bs_Object* lo_res = BS_RENDERER(BSGFX_RENDERERS, BSGFX_RENDERER_LO_RES, BS_OBJECT_HAS_SWAPS_BIT);

    if (bs_renderer(lo_res, 0) == BS_RESULT_OK) {

        bs_ivec2 resolution = bs_resolution();
        resolution.x /= BSGFX_PIXEL_SCALE;
        resolution.y /= BSGFX_PIXEL_SCALE;

       /** attachments */
        bs_Object* lo_res_0_depth = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH, 0);
        bs_Object* lo_res_0_color = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_COLOR, 0);
        bs_Object* lo_res_0_normal = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_NORMAL, 0);
        bs_Object* lo_res_0_position = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_POSITION, 0);
        bs_Object* lo_res_0_index = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_INDEX, 0);
        bs_Object* lo_res_0_flags = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_FLAGS, 0);
        bs_Object* lo_res_0_position_local = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_VERTEX, 0);
        bs_Object* lo_res_1_color = BS_IMAGE(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_1_COLOR, 0);

        bs_image(lo_res_0_depth, resolution, 0, BS_FORMAT_D32_SFLOAT_S8_UINT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);
        bs_image(lo_res_0_color, resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);
        bs_image(lo_res_0_normal, resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);
        bs_image(lo_res_0_position, resolution, 0, BS_FORMAT_R32G32B32A32_SFLOAT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT);
        bs_image(lo_res_0_index, resolution, 0, BS_FORMAT_R32_UINT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT);
        bs_image(lo_res_0_flags, resolution, 0, BS_FORMAT_R32_UINT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT);
        bs_image(lo_res_0_position_local, resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_INPUT_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);
        bs_image(lo_res_1_color, resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);

        bs_Image* subpass_0_outputs[] = {
            [BSGFX_LO_SUBPASS_0_OUT_COLOR] = lo_res_0_color->image,
            [BSGFX_LO_SUBPASS_0_OUT_NORMAL] = lo_res_0_normal->image,
            [BSGFX_LO_SUBPASS_0_OUT_INDEX] = lo_res_0_index->image,
            [BSGFX_LO_SUBPASS_0_OUT_FLAGS] = lo_res_0_flags->image,
            [BSGFX_LO_SUBPASS_0_OUT_POSITION] = lo_res_0_position->image,
            [BSGFX_LO_SUBPASS_0_OUT_POSITION_LOCAL] = lo_res_0_position_local->image,
            lo_res_0_depth,
        };

        int subpass_0_inputs[] = {
            [BSGFX_LO_SUBPASS_0_IN_COLOR] = BSGFX_LO_SUBPASS_0_OUT_COLOR,
            [BSGFX_LO_SUBPASS_0_IN_NORMAL] = BSGFX_LO_SUBPASS_0_OUT_NORMAL,
            [BSGFX_LO_SUBPASS_0_IN_INDEX] = BSGFX_LO_SUBPASS_0_OUT_INDEX,
            [BSGFX_LO_SUBPASS_0_IN_FLAGS] = BSGFX_LO_SUBPASS_0_OUT_FLAGS,
            [BSGFX_LO_SUBPASS_0_IN_POSITION] = BSGFX_LO_SUBPASS_0_OUT_POSITION,
        };

       /** subpass 0 */
        // todo only general in debug

        for (int i = 0; i < sizeof(subpass_0_outputs) / sizeof(*subpass_0_outputs); i++) {
            bs_output(lo_res->renderer, (bs_Output) {
                .subpass = 0,
                .image = subpass_0_outputs[i],
                .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
                .store_op = BS_ATTACHMENT_STORE_OP_STORE,
                .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
                .new_layout = BS_IMAGE_LAYOUT_GENERAL,
            });
        }

        for (int i = 0; i < sizeof(subpass_0_inputs) / sizeof(*subpass_0_inputs); i++) {
            bs_input(lo_res->renderer, (bs_Input) {
                .subpass = 0, 
                .parent_subpass = 0, 
                .attachment = subpass_0_inputs[i],
                .flags = BS_INPUT_AWAIT_WRITE
            });
        }

        /** subpass 1 */
        int subpass_1_inputs[] = {
            [BSGFX_LO_SUBPASS_1_IN_COLOR] = BSGFX_LO_SUBPASS_0_OUT_COLOR,
            [BSGFX_LO_SUBPASS_1_IN_NORMAL] = BSGFX_LO_SUBPASS_0_OUT_NORMAL,
            [BSGFX_LO_SUBPASS_1_IN_INDEX] = BSGFX_LO_SUBPASS_0_OUT_INDEX,
            [BSGFX_LO_SUBPASS_1_IN_FLAGS] = BSGFX_LO_SUBPASS_0_OUT_FLAGS,
            [BSGFX_LO_SUBPASS_1_IN_POSITION] = BSGFX_LO_SUBPASS_0_OUT_POSITION,
        };

        for (int i = 0; i < sizeof(subpass_1_inputs) / sizeof(*subpass_1_inputs); i++) {
            bs_input(lo_res->renderer, (bs_Input) {
                .subpass = 1, 
                .parent_subpass = 0, 
                .attachment = subpass_1_inputs[i], 
                .flags = BS_INPUT_AWAIT_WRITE
            });
        }

        bs_output(lo_res->renderer, (bs_Output) {
            .subpass = 1,
            .image = lo_res_1_color,
            .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
            .store_op = BS_ATTACHMENT_STORE_OP_STORE,
            .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
            .new_layout = BS_IMAGE_LAYOUT_GENERAL,
        });

        /** dependencies */
        bs_dependency(lo_res->renderer, -1, 0, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | BS_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
            BS_ACCESS_MEMORY_READ_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT);

        // this throws a validation error but the entire engine depends on it (only when developing though)
        // some bitching about BS_DEPENDENCY_BY_REGION_BIT yadayadayada
        bs_dependency(lo_res->renderer, 0, 0, 0,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | BS_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);

        bs_dependency(lo_res->renderer, 1, 1, 0,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);

        bs_dependency(lo_res->renderer, 0, 1, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);

        bs_dependency(lo_res->renderer, 0, -1, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_MEMORY_READ_BIT);

        bs_dependency(lo_res->renderer, 1, -1, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_MEMORY_READ_BIT);

        bs_renderPass(lo_res->renderer);
        bs_framebuffer(lo_res->renderer, resolution);

        bs_buffer(BS_BUFFER(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS, false), 2 * lo_res->renderer->num_outputs * 4,
            BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
            BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            0);

        bs_buffer(BS_BUFFER(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_SCREENSHOT, false), BSGFX_SCREENSHOT_DIMENSIONS.x * BSGFX_SCREENSHOT_DIMENSIONS.y * lo_res->renderer->num_outputs * 4,
            BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
            BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            0);
    }
}

void _bsgfx_allocateMaterials();
static void _bsgfx_loadResources() {
    bs_Result result;

    bs_queue(BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS, BS_OBJECT_HAS_SWAPS_BIT), BS_QUEUE_GRAPHICS_BIT);
    bs_queue(BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_COMPUTE, BS_OBJECT_HAS_SWAPS_BIT), BS_QUEUE_COMPUTE_BIT);

    bs_sampler(BS_SAMPLER(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST, 0), BS_FILTER_NEAREST, 0);
    bs_sampler(BS_SAMPLER(BSGFX_SAMPLERS, BSGFX_SAMPLER_LINEAR, 0), BS_FILTER_LINEAR, 0);

    bs_Object* jonts_buffer = BS_BUFFER(BSGFX_BUFFERS, BSGFX_BUFFER_JOINTS, false);
    result = bs_buffer(jonts_buffer,
        BSGFX_MAX_NUM_JOINTS * sizeof(bs_mat4), 
        BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result == BS_RESULT_OK && bs_mapBuffer(jonts_buffer->buffer, BS_U32_MAX) == BS_RESULT_OK) {
        bs_bindBuffer(BSGFX_SET_JOINTS, BSGFX_BINDING_JOINTS, jonts_buffer->buffer);
    }

    _bsgfx_iniInstances();
    
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
        _bsgfx_instanceType(BSGFX_INSTANCE_TYPE_MESH, BSGFX_MESH_INSTANCE_COUNT, BSGFX_SET_MESH_INSTANCES, BSGFX_BINDING_MESH_INSTANCES);
        _bsgfx_instanceType(BSGFX_INSTANCE_TYPE_MESH_STATIC, BSGFX_MESH_STATIC_INSTANCE_COUNT, BSGFX_SET_MESH_STATIC_INSTANCES, BSGFX_BINDING_MESH_STATIC_INSTANCES);
    }

    if (sphere_batch && bs_canPushBatch(sphere_batch->batch)) {
        bs_Range cone_range = bs_pushCone(sphere_batch->batch, 10, 2.0, 1.0, BS_WHITE);
        bs_Range sphere_range = bs_pushSphere(sphere_batch->batch, (bs_vec3) { 0 }, 1.0, 8, 8, BS_WHITE);

        _bsgfx_subtypes_[BSGFX_SUBTYPE_CONE_MESH] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, sphere_batch->batch, 0, cone_range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_SPHERE_MESH] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, sphere_batch->batch, 0, sphere_range);
    }

    bs_Quad quad;
    bs_quad(&(bs_vec3) { 0 }, & (bs_vec2) { 1.0, 1.0 }, & quad);

    if (quad_instance_batch && bs_canPushBatch(quad_instance_batch->batch)) {
        _bsgfx_instanceType(BSGFX_INSTANCE_TYPE_QUAD, BSGFX_QUAD_INSTANCE_COUNT, BSGFX_SET_QUAD_INSTANCES, BSGFX_BINDING_QUAD_INSTANCES);

        bs_Range range = bs_pushQuad(quad_instance_batch->batch, &quad, BS_WHITE);

        _bsgfx_subtypes_[BSGFX_SUBTYPE_CORNER_GRADIENT] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_UI] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_UI_STENCIL] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_HUE] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_ALPHA] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_DITHER] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_QUAD_MATERIAL_TEXTURE] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_TILE] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_TILE_2] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_TILE_ICON] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_64_HI] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_256_HI] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instance_batch->batch, 0, range);

       // if (_bsgfx_procs_.bsmod_onCreateQuadSubtypes)
       //     _bsgfx_procs_.bsmod_onCreateQuadSubtypes(range);

        bs_pushBatch(quad_instance_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    if (bs_canPushBatch(volume_batch->batch)) {
        bs_ensureBatchSize(volume_batch->batch, 0, BSGFX_NUM_SHADOW_VERTICES);

        bs_pushQuad(volume_screen_batch->batch, &quad, BSGFX_SHADOW_COLOR);

        bs_pushBatch(volume_batch->batch, 0, BSGFX_NUM_SHADOW_VERTICES);
        bs_bindBuffer(BSGFX_SET_VOLUME_OUT_VERTICES, BSGFX_BINDING_VOLUME_OUT_VERTICES, volume_batch->batch->vertex_buffer->buffer);
    }

    if (bs_canPushBatch(screen_batch->batch)) {
        bs_pushQuad(screen_batch->batch, &quad, BS_WHITE);
        bs_pushQuad(screen_batch->batch, &quad, BS_WHITE);
       // const float offset = 0.75;
       // bs_pushQuad(screen_batch, bs_quad(BS_V3(0.125, 0.125, 0.0), bs_v2V1(offset)), BS_WHITE);
        bs_pushBatch(screen_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    bs_Object* mesh_volume_batch = BS_BATCH(BSGFX_BATCHES, BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED, true);
    result = bs_batch(mesh_volume_batch, 0, $vs_bsgfx_volume(), 0);

    if (result == BS_RESULT_OK && bs_canPushBatch(mesh_volume_batch->batch)) {
        bs_pushBatch(mesh_volume_batch->batch, 0, BSGFX_PRE_COMPUTED_VOLUME_SIZE);
      //  bs_bindBuffer(BSGFX_SET_VOLUME_OUT_VERTICES, BSGFX_BINDING_VOLUME_OUT_VERTICES_MESH_TYPE, mesh_volume_batch->batch->vertex_buffer->buffer);
    }

    //bs_loadAllResources(BSGFX_RESOURCE_SCRIPT, 0);
    //bsgfx_loadModels(NULL, 0);
    //bsgfx_loadMinimap();
    _bsgfx_allocateMaterials();

  //  _bsgfx_loadMaterials();

    bs_ivec2 resolution = bs_resolution();
    resolution.x /= BSGFX_PIXEL_SCALE;
    resolution.y /= BSGFX_PIXEL_SCALE;

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
        _bsgfx_instanceType(BSGFX_INSTANCE_TYPE_BONE, BSGFX_BONE_INSTANCE_COUNT, BSGFX_SET_BONE_INSTANCES, BSGFX_BINDING_BONE_INSTANCES);
    }

    if (mesh_instance_batch && bs_canPushBatch(mesh_instance_batch->batch)) {
        bs_Range pyramid = bs_pushBipyramid(mesh_instance_batch->batch, (bs_vec3) { 0 }, 0.75, 1.0, BS_WHITE);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_BIPYRAMID] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, mesh_instance_batch->batch, BSGFX_SUBTYPE_HAS_SHADOWS, pyramid);
    }

    if (point_batch && bs_canPushBatch(point_batch->batch) && bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)) {
        _bsgfx_instanceType(BSGFX_INSTANCE_TYPE_POINT, BSGFX_POINT_INSTANCE_COUNT, BSGFX_SET_POINT_INSTANCES, BSGFX_BINDING_POINT_INSTANCES);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_POINT] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_POINT, point_batch->batch, 0, bs_pushPoint(point_batch->batch, (bs_vec3) { 0 }, BS_WHITE));
    }

    if (line_batch && bs_canPushBatch(line_batch->batch) && bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)) {
        _bsgfx_instanceType(BSGFX_INSTANCE_TYPE_LINE, BSGFX_LINE_INSTANCE_COUNT, BSGFX_SET_LINE_INSTANCES, BSGFX_BINDING_LINE_INSTANCES);

        bs_Range range = bs_pushLine(line_batch->batch, (bs_vec3) { 0 }, BS_V3(0, 1.0, 0.0), BS_WHITE);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_LINE_2D] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_LINE, line_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_LINE] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_LINE, line_batch->batch, 0, range);
        _bsgfx_subtypes_[BSGFX_SUBTYPE_LINE_DEPTHLESS] = _bsgfx_subtype(BSGFX_INSTANCE_TYPE_LINE, line_batch->batch, 0, range);
    }

     /**
      Load level after bsgfx resources, before bindings and subtype creation
      */
    if (_bsgfx_callbacks_.loadScene)
        _bsgfx_callbacks_.loadScene();

    if (_bsgfx_prefab_model_ && bs_exists(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED)) { // _bsgfx_prefab_model_ is temp
        mesh_instance_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED);
        if (bs_canPushBatch(mesh_instance_batch->batch)) {
            bs_pushBatch(mesh_instance_batch->batch, BS_U32_MAX, BS_U32_MAX);
            bs_bindBuffer(BSGFX_SET_VOLUME_IN_VERTICES, BSGFX_BINDING_VOLUME_IN_VERTICES_MESH, mesh_instance_batch->batch->vertex_buffer->buffer);
            bs_bindBuffer(BSGFX_SET_VOLUME_IN_INDICES, BSGFX_BINDING_VOLUME_IN_INDICES_MESH, mesh_instance_batch->batch->index_buffer->buffer);
            //bs_bindBuffer(BSGFX_SET_VOLUME_IN_VERTICES, BSGFX_BINDING_VOLUME_IN_VERTICES_MESH_TYPE, mesh_instance_batch->batch->vertex_buffer->buffer);
            //bs_bindBuffer(BSGFX_SET_VOLUME_IN_INDICES, BSGFX_BINDING_VOLUME_IN_INDICES_MESH_TYPE, mesh_instance_batch->batch->index_buffer->buffer);
        }

    }

    if (point_batch && bs_canPushBatch(point_batch->batch)) {
        bs_pushBatch(point_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    if (line_batch && bs_canPushBatch(line_batch->batch)) {
        bs_pushBatch(line_batch->batch, BS_U32_MAX, BS_U32_MAX);
    }

    if (bone_instance_batch && bs_canPushBatch(bone_instance_batch->batch)) {
        bs_pushBatch(bone_instance_batch->batch, BS_U32_MAX, BS_U32_MAX);
       // bs_bindBuffer(BSGFX_SET_VOLUME_IN_VERTICES, BSGFX_BINDING_VOLUME_IN_VERTICES_BONE, bone_instance_batch->batch->vertex_buffer->buffer);
       // bs_bindBuffer(BSGFX_SET_VOLUME_IN_INDICES, BSGFX_BINDING_VOLUME_IN_INDICES_BONE, bone_instance_batch->batch->index_buffer->buffer);
    }

    _bsgfx_createRenderers();

    if (bs_exists(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)) {
        bs_Sampler* sampler = bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler;
        bs_Image* lo_res_color_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_COLOR)->image;
        bs_Image* lo_res_normal_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_NORMAL)->image;
        bs_Image* lo_res_index_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_INDEX)->image;
        bs_Image* lo_res_flags_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_FLAGS)->image;
        bs_Image* lo_res_vertex_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_VERTEX)->image;
        bs_Image* lo_res_depth_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image;
        bs_Image* lo_res_position_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_POSITION)->image;
        bs_Image* lo_res_result_image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_1_COLOR)->image;

        if (lo_res_color_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_COLOR_ATTACHMENT, lo_res_color_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_COLOR_INPUT, lo_res_color_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_normal_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_NORMAL_ATTACHMENT, lo_res_normal_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_NORMAL_INPUT, lo_res_normal_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_index_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_INDEX_ATTACHMENT, lo_res_index_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_INDEX_INPUT, lo_res_index_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_flags_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_FLAGS_ATTACHMENT, lo_res_flags_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_FLAGS_INPUT, lo_res_flags_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_vertex_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_VERTEX_ATTACHMENT, lo_res_vertex_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_position_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_POSITION_ATTACHMENT, lo_res_position_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_POSITION_INPUT, lo_res_position_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_depth_image) {
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_DEPTH_ATTACHMENT, lo_res_depth_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
//            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_0_DEPTH_INPUT, lo_res_depth_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
        }
        if (lo_res_result_image)
            bs_bindImage(BSGFX_SET_LO_RES_0, BSGFX_BINDING_LO_RES_1_COLOR_ATTACHMENT, lo_res_result_image, sampler, BS_IMAGE_LAYOUT_GENERAL);
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

    bs_Scope scope = *bs_getScope();
    bs_setScope(&(bs_Scope) { 0 });

	bs_load(_bsgfx_loadResources);

   // if (_bsgfx_procs_.bsmod_onLoad)
   //     bs_runSingle(_bsgfx_procs_.bsmod_onLoad);

    //bs_runSingle(_bsgfx_computePrefabShadows);

    //bs_logObjectDiff();
    //bs_logUnchangedObjects();
    //bs_logBindings();

    if (_bsgfx_prefab_model_) {
        bs_Object* queue_object = BS_QUEUE(-1, 0, 0);
        if (bs_queue(queue_object, BS_QUEUE_COMPUTE_BIT) == BS_RESULT_OK) {
            bs_enqueue(queue_object->queue, _bsgfx_computePrefabShadows);
            bs_stallGPU();
        }
        
        //bsgfx_computePrefabShadows();

    }

   // _bsgfx_despawnAllItems();
    bs_setScope(&scope);

    bs_logEndOfSection();

}