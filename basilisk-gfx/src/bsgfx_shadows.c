
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

enum {
    BSGFX_SHADOW_COMPUTATION_MESH,
    BSGFX_SHADOW_COMPUTATION_BONE,
    BSGFX_SHADOW_COMPUTATION_MESH_TYPE,
    BSGFX_SHADOW_COMPUTATION_MESH_TEXTURED,
};



  /*==============================================================================
   * Initialization
   *============================================================================*/



  /*==============================================================================
   * Robust Shadow Volume Computation
   *============================================================================*/

static inline void _bsgfx_awaitComputeWrite() {
    bs_barrier(0,
        BS_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        BS_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        BS_ACCESS_SHADER_WRITE_BIT,
        BS_ACCESS_SHADER_READ_BIT);
}

BSGFXAPI void _bsgfx_computeShadowVolumes() {
    /*
    bs_setBufferAsync(
        bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer,
        offsetof(bsgfx_InstanceMetadata, computed_volume_vertices),
        BSGFX_NUM_VOLUME_COMPUTATIONS * sizeof(unsigned int), 0);

    bs_setBufferAsync(
        bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer,
        offsetof(bsgfx_InstanceMetadata, computed_subtype_volume_vertices),
        BSGFX_MAX_NUM_SUBTYPES * sizeof(int), 0);

    // Reset shadow geometry to 0's
    bs_copyAsync(
        bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_COMPUTED)->batch->staging_buffer->buffer,
        bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_COMPUTED)->batch->vertex_buffer->buffer,
        0, 0, BS_U32_MAX);

    bs_copyAsync(
        bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED)->batch->staging_buffer->buffer,
        bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED)->batch->vertex_buffer->buffer,
        0, 0, BS_U32_MAX);

    bs_barrier(0,
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

    if (_poser_->current_level != BSGFX_SCENE_MENU) {
        bs_Pipeline* pipeline = bs_computePipeline($cs_mesh_volume(), 0);

        push_constant.id = BSGFX_SHADOW_COMPUTATION_MESH;
        push_constant.include_flag = BSGFX_SUBTYPE_HAS_SHADOWS;
        push_constant.exclude_flag = BSGFX_SUBTYPE_HAS_FINE_SHADOWS;

        _bsgfx_awaitComputeWrite();
        bs_pushConstant(pipeline, 0, sizeof(push_constant), &push_constant);
        bs_dispatchAsync(pipeline, 1, 1, 1);
    }

    if (_poser_->current_level != BSGFX_SCENE_MENU) {
        bs_Pipeline* pipeline = bs_computePipeline($cs_bone_volume(), 0);

        push_constant.id = BSGFX_SHADOW_COMPUTATION_MESH;
        push_constant.include_flag = BSGFX_SUBTYPE_HAS_SHADOWS;
        push_constant.exclude_flag = BSGFX_SUBTYPE_HAS_FINE_SHADOWS;

        _bsgfx_awaitComputeWrite();
        bs_pushConstant(pipeline, 0, sizeof(push_constant), &push_constant);
        bs_dispatchAsync(pipeline, 1, 1, 1);
    }

    if (_poser_->current_level != BSGFX_SCENE_MENU) {
        bs_Pipeline* pipeline = bs_computePipeline($cs_textured_volume(), 0);

        push_constant.id = BSGFX_SHADOW_COMPUTATION_MESH_TEXTURED;
        push_constant.include_flag = BSGFX_SUBTYPE_HAS_FINE_SHADOWS;
        push_constant.exclude_flag = 0;

        _bsgfx_awaitComputeWrite();
        bs_pushConstant(pipeline, 0, sizeof(push_constant), &push_constant);
        bs_dispatchAsync(pipeline, 1, 1, 1);
    }
    */
}



  /*==============================================================================
   * Render Robust Stencil Shadow Volumes
   *============================================================================*/

#define BSGFX_STENCIL_SHADOW_VOLUME_OPTIONS                                             \
    .stencil_front = {                                                                  \
        .depth_fail_op = BS_STENCIL_OP_INCREMENT_AND_WRAP,                              \
        .compare_op = BS_COMPARE_OP_ALWAYS,                                             \
        .compare_mask = 0xFF,                                                           \
        .write_mask = 0xFF,                                                             \
    },                                                                                  \
    .stencil_back = {                                                                   \
        .depth_fail_op = BS_STENCIL_OP_DECREMENT_AND_WRAP,                              \
        .compare_op = BS_COMPARE_OP_ALWAYS,                                             \
        .compare_mask = 0xFF,                                                           \
        .write_mask = 0xFF,                                                             \
    },                                                                                  \
    .cull_type = BS_CULL_MODE_NONE,                                                     \
    .clamp_depth = true,                                                                \
    .skip_depth_write = true,                                                           \
    .attachments = {                                                                    \
        [0] = {.skip_write = true },                                                    \
        [3] = {.skip_write = true },                                     /* position */ \
    }                                                                                   \

BSGFXAPI void _bsgfx_renderShadowVolumes() {
    /*
    bs_beginComment("Shadow Volumes");

    bs_Pipeline* volume_pipeline = bs_pipeline(&(bs_PipelineHash) {
        .shaders = {
            $vs_bsgfx_volume(),
            $fs_bsgfx_volume(),
        },
        BSGFX_STENCIL_SHADOW_VOLUME_OPTIONS
    });

    bs_Pipeline* volume_mesh_instanced_pipeline = bs_pipeline(&(bs_PipelineHash) {
        .shaders = {
            $vs_bsgfx_volume_mesh_instanced(),
            $fs_bsgfx_volume(),
        },
        BSGFX_STENCIL_SHADOW_VOLUME_OPTIONS
    });

    bs_Pipeline* volume_screen_pipeline = bs_pipeline(&(bs_PipelineHash) {
        .shaders = {
            $vs_bsgfx_color_percentage(),
            $fs_bsgfx_volume_screen(),
        },
        .skip_depth_write = true,
        .stencil_front = {
            .compare_op = BS_COMPARE_OP_NOT_EQUAL,
            .compare_mask = 0xFF,
        },
        .attachments = {
            [3] = {.skip_write = true }, // position
        }
    });

    bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
    bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

    int count = metadata->computed_volume_vertices[BSGFX_SHADOW_COMPUTATION_MESH];

    if (count > BSGFX_NUM_SHADOW_VERTICES)
        bs_throwBasiliskF(BSX_OUT_OF_BOUNDS, "Compute shader generated %d/%d vertices", count, BSGFX_NUM_SHADOW_VERTICES);

    bs_pushConstant(volume_pipeline, 0, sizeof(_poser_->camera.result), &_poser_->camera.result);
    bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_COMPUTED)->batch, volume_pipeline, 0, count, 0, 1);

    bs_barrier(0,
        BS_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
        BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
        BS_ACCESS_SHADER_READ_BIT);

    bs_pushConstant(volume_screen_pipeline, 0, sizeof(bs_vec4), &BSGFX_RGBA(BSGFX_SHADOW_COLOR.r, BSGFX_SHADOW_COLOR.g, BSGFX_SHADOW_COLOR.b, BSGFX_SHADOW_COLOR.a));
    bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_SCREEN)->batch, volume_screen_pipeline, 0, BS_U32_MAX, 0, 1);

    bs_endComment();
    */
}

static int _bsgfx_comparePrefabDepths(const bsgfx_Prefab** ap, const bsgfx_Prefab** bp) {
    const bsgfx_Prefab* a = *ap, * b = *bp;
    if (a->position.z != b->position.z)
        return (a->position.z < b->position.z) ? -1 : 1;
    else return 0;
}



  /*==============================================================================
   * Robust Stencil Shadow Volumes (Fine)
   *============================================================================*/

BSGFXAPI void _bsgfx_renderFineShadowVolumes() {
    return;
    bs_beginCommentN(BS_CONSTANT_STRING("Shadow Volumes (Fine)"));

    bs_barrier(0,
        BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        BS_ACCESS_SHADER_READ_BIT);

    /**
     Pipelines
     */
    /*
    bs_PipelineHash hash;

    hash = (bs_PipelineHash){
        .shaders = {
            $vs_bsgfx_volume(),
            $fs_bsgfx_volume(),
        },
        BSGFX_STENCIL_SHADOW_VOLUME_OPTIONS
    };
    bs_Pipeline* volume_pipeline = bs_pipeline(&hash);

    hash = (bs_PipelineHash){
        .shaders = {
            $vs_bsgfx_color_percentage(),
            $fs_bsgfx_volume_texture(),
        },
        .skip_depth_write = true,
        .stencil_front = {
            .compare_op = BS_COMPARE_OP_NOT_EQUAL,
            .compare_mask = 0xFF,
        },
        .attachments = {
            [3] = {.skip_write = true }, // position
        }
    };
    bs_Pipeline* volume_screen_pipeline = bs_pipeline(&hash);

    hash = (bs_PipelineHash){
        .shaders = {
            $vs_bsgfx_mesh_instanced(),
            $fs_bsgfx_model(),
        },
        .cull_type = BS_CULL_MODE_NONE,
        // .stencil_front = {
        //     .compare_op = BS_COMPARE_OP_NOT_EQUAL,
        //     .compare_mask = 0xFF,
        // },
        //.skip_depth_write = true,
    };
    // TODO: screenshot reimplementation
    //if (_bsmod_.queue.screenshot)
    //    hash.attachments[0].skip_write = false;
    bs_Pipeline* mesh_pipeline = bs_pipeline(&hash);

    hash = (bs_PipelineHash){
        .shaders = {
            $vs_bsgfx_quad_instanced(),
            $fs_bsgfx_atlas(),
        },
        //  .attachments = {
        //      [1] = {.skip_write = true},
        //  },
        .skip_depth_write = true,
        .attachments[3].skip_write = true
    };
    bs_Pipeline* prefab_pipeline = bs_pipeline(&hash);

    bsgfx_InstanceMetadata* metadata = bs_bufferMap(bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer);
    int total_index_count = metadata->computed_volume_vertices[BSGFX_SHADOW_COMPUTATION_MESH_TEXTURED] / 2;
    const int volume_index_count = 8 * 3; // 8 triangles

    bs_clearStencil(0, bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image->dim, 0);

    bsgfx_InstanceBuffer* first_instance = bs_bufferMap(_poser_->instance_buffers[BSGFX_INSTANCE_TYPE_MESH]);
    bsgfx_InstanceSubtypeMetadata* atlas_prefab_subtype = metadata->instance_subtypes + _bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT];
    bs_Batch* atlas_prefab_batch = bs_fetch(atlas_prefab_subtype->batch_source_id, atlas_prefab_subtype->batch_id)->batch;

    struct {
        bs_mat4 camera;
        bs_vec4 color;
        bs_vec3 light_direction;
        int first_triangle;
        bs_vec4 uv;
        unsigned write_flags;
        int reserved;
    } volume_texture_const = {
        .camera = _poser_->camera.proj,
        .color = BSGFX_RGBA(BSGFX_SHADOW_COLOR.r, BSGFX_SHADOW_COLOR.g, BSGFX_SHADOW_COLOR.b, BSGFX_SHADOW_COLOR.a),
        .light_direction = _poser_->sun_direction,
        .first_triangle = 0,
        .write_flags = BSGFX_ID_IN_SHADOW
    };

    struct {
        bs_mat4 camera;
        bs_vec4 uv;
    } mesh_push_const = {
        .camera = _poser_->camera.result,
    };

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

    static bs_List sorted_prefabs = { .unit_size = sizeof(bsgfx_Prefab*), .increment = 32 };
    sorted_prefabs.count = 0;

    for (int i = 0, call = 0; i < total_index_count; i += volume_index_count, call++) {
        int instance_id = metadata->textured_volumes[metadata->textured_volumes_count - call].texture;
        bsgfx_InstanceBuffer* instance = first_instance + instance_id;
        int prefab_id = instance->header.id;
        bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, prefab_id);
        bs_pushBack(&sorted_prefabs, &prefab);
    }
    // qsort(sorted_prefabs.data, sorted_prefabs.count, sizeof(bsgfx_Prefab*), _bsgfx_comparePrefabDepths);

    int count = total_index_count / volume_index_count;

    for (int i = 0; i < sorted_prefabs.count; i++) {
        bsgfx_Prefab* prefab = bs_fetchUnit(&sorted_prefabs, i);
    }

    for (int i = count - 1; i >= 0; i--) {
        int offset = i * volume_index_count;
        int instance_id = metadata->textured_volumes[metadata->textured_volumes_count - i - 1].texture;
        bsgfx_InstanceBuffer* instance = first_instance + instance_id;

        int prefab_id = instance->header.id;
        bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, prefab_id);
        bsgfx_RawPrefab* raw_prefab = _bsgfx_getRaw(BSGFX_TYPE_PREFAB, prefab_id);

        if (!(raw_prefab->flags & BSGFX_PREFAB_TEXTURED_SHADOWS))
            continue;

        if (atlas->mapped[prefab->texture_id].flags & BS_ATLAS_TEXTURE_HAS_ALPHA && !(atlas->mapped[prefab->texture_id].flags & BS_ATLAS_TEXTURE_IS_SOLID))
            volume_texture_const.write_flags = BSGFX_ID_IN_SHADOW | BSGFX_ID_IN_SHADOW_TEXTURED;
        else
            volume_texture_const.write_flags = BSGFX_ID_IN_SHADOW;

        if (instance->header.bone_index == (uint)-1)
            continue;

        int index = BSGFX_NUM_SHADOW_VERTICES - total_index_count + offset;
        index = BSGFX_NUM_SHADOW_VERTICES - metadata->textured_volumes[metadata->textured_volumes_count - i - 1].start - volume_index_count;

        bs_clearStencil(0, bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image->dim, 0);

        bs_pushConstant(volume_pipeline, 0, sizeof(_poser_->camera.result), &_poser_->camera.result);
        bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_COMPUTED)->batch, volume_pipeline, index, volume_index_count, 0, 1);

        bs_barrier(0,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);

        volume_texture_const.uv = bs_atlasCoordinates(atlas, prefab->texture_id, 0),
            volume_texture_const.first_triangle = index;
        bs_pushConstant(volume_screen_pipeline, 0, sizeof(volume_texture_const), &volume_texture_const);
        bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_SCREEN)->batch, volume_screen_pipeline, 0, BS_U32_MAX, 0, 1);
    }

    for (int i = 0; i < count; i++) {
        int offset = i * volume_index_count;
        int instance_id = metadata->textured_volumes[metadata->textured_volumes_count - i - 1].texture;
        bsgfx_InstanceBuffer* instance = first_instance + instance_id;

        int prefab_id = instance->header.id;
        bsgfx_Prefab* prefab = _bsgfx_get(BSGFX_TYPE_PREFAB, prefab_id);
        bsgfx_RawPrefab* raw_prefab = _bsgfx_getRaw(BSGFX_TYPE_PREFAB, prefab_id);
        bs_Mesh* mesh = _bsgfx_prefab_model_->meshes + prefab->mesh_id;

        if (!(raw_prefab->flags & BSGFX_PREFAB_TEXTURED_SHADOWS))
            continue;

        if (atlas->mapped[prefab->texture_id].flags & BS_ATLAS_TEXTURE_HAS_ALPHA && !(atlas->mapped[prefab->texture_id].flags & BS_ATLAS_TEXTURE_IS_SOLID))
            volume_texture_const.write_flags = BSGFX_ID_IN_SHADOW | BSGFX_ID_IN_SHADOW_TEXTURED;
        else
            volume_texture_const.write_flags = BSGFX_ID_IN_SHADOW;

        if (instance->header.bone_index == (uint)-1)
            continue;

        int index = BSGFX_NUM_SHADOW_VERTICES - total_index_count + offset;
        index = BSGFX_NUM_SHADOW_VERTICES - metadata->textured_volumes[metadata->textured_volumes_count - i - 1].start - volume_index_count;

        bs_clearStencil(0, bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image->dim, 0);

        bs_pushConstant(volume_pipeline, 0, sizeof(_poser_->camera.result), &_poser_->camera.result);
        bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_COMPUTED)->batch, volume_pipeline, index, volume_index_count, 0, 1);

        bs_barrier(0,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);

        volume_texture_const.uv = bs_atlasCoordinates(atlas, prefab->texture_id, 0),
            volume_texture_const.first_triangle = index;
        bs_pushConstant(volume_screen_pipeline, 0, sizeof(volume_texture_const), &volume_texture_const);
        bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_VOLUME_SCREEN)->batch, volume_screen_pipeline, 0, BS_U32_MAX, 0, 1);
        if (i % 2 == 1) {
            int subtype_id = mesh->extra[BSGFX_PREFAB_SUBTYPE_MESH_TEXTURED];
            bsgfx_InstanceSubtypeMetadata* prefab_subtype = metadata->instance_subtypes + subtype_id;
            bs_Batch* prefab_batch = bs_fetch(prefab_subtype->batch_source_id, prefab_subtype->batch_id)->batch;

            mesh_push_const.uv = volume_texture_const.uv;
            bs_pushConstant(mesh_pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
            bs_render(prefab_batch, mesh_pipeline, prefab_subtype->index_offset, prefab_subtype->index_count, instance_id, 1);

            // bs_comment("pr %d", i);
            // bs_pushConstant(prefab_pipeline, 0, sizeof(poser->world_camera.result), &poser->world_camera.result);
            // bs_render(atlas_prefab_batch, prefab_pipeline, atlas_prefab_subtype->index_offset, atlas_prefab_subtype->index_count, instance->header.bone_index, 1);
        }

    }

    bs_clearStencil(0, bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image->dim, 0);

    bs_endComment();
    */
}