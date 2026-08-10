
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

#include <math.h>
#include <assert.h>

/*
#ifdef _DEBUG
#include <GFSDK_Aftermath_GpuCrashDump.h>
#endif
*/

void _bsgfx_onDeviceLost() {
    /*
#ifdef _DEBUG
    GFSDK_Aftermath_CrashDump_Status status = 0;
    _bsgfx_checkGFSDK(GFSDK_Aftermath_GetCrashDumpStatus(&status));

    bs_Timer timer = bs_timer();
    const double timeout_seconds = 60.0;

    while (status != GFSDK_Aftermath_CrashDump_Status_CollectingDataFailed &&
        status != GFSDK_Aftermath_CrashDump_Status_Finished &&
        timer.seconds < timeout_seconds)
    {
        Sleep(50);
        _bsgfx_checkGFSDK(GFSDK_Aftermath_GetCrashDumpStatus(&status));
        bs_checkTimer(&timer);
    }
#endif
*/
    //bs_critical(BS_CONSTANT_STRING("Device lost"));
}

BSGFXAPI bs_PipelineHash _bsgfx_defaultPipelineHash() {
    return (bs_PipelineHash) {
        .depth_comparison = BS_COMPARE_OP_LESS,
        .cull_type = BS_CULL_MODE_BACK_BIT,
        .topology_type = BS_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,

        .src_color_factor = BS_BLEND_FACTOR_SRC_ALPHA,
        .dst_color_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,

        .src_alpha_factor = BS_BLEND_FACTOR_ONE,
        .dst_alpha_factor = BS_BLEND_FACTOR_ZERO,
    };
}

BSGFXAPI void _bsgfx_requiredForShadowVolumes(bs_PipelineHash* inout) {
    inout->stencil_front = (bs_StencilOperation) {
        .fail_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .compare_mask = 0xFF,
        .compare_op = BS_COMPARE_OP_LESS_OR_EQUAL,
        .write_mask = 0xFF,
    };

    inout->stencil_back = (bs_StencilOperation) {
        .fail_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .compare_mask = 0xFF,
        .compare_op = BS_COMPARE_OP_LESS_OR_EQUAL,
        .write_mask = 0xFF,
    };

    inout->cull_type = BS_CULL_MODE_NONE;
}

BSGFXAPI void _bsgfx_requiredForStencilShadows(bs_PipelineHash* inout) {
    inout->stencil_front = (bs_StencilOperation){
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .fail_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
    };

    inout->depth_comparison = BS_COMPARE_OP_ALWAYS;
}

BSGFXAPI void _bsgfx_requiredForTransparency(bs_PipelineHash* inout) {
    inout->src_color_factor = BS_BLEND_FACTOR_SRC_ALPHA;
    inout->dst_color_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    inout->color_op = BS_BLEND_OP_ADD;
    inout->src_alpha_factor = BS_BLEND_FACTOR_ONE;
    inout->dst_alpha_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    inout->alpha_op = BS_BLEND_OP_ADD;
}



  /*==============================================================================
   * Render Pipe
   *============================================================================*/

BSGFXAPI void _bsgfx_renderPrimitiveTiles() {
    if (!bs_exists(BSGFX_BATCHES, BSGFX_BATCH_PRIMITIVE_TILES))
        return;

    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_tile_static();
    hash.shaders[1] = $fs_bsgfx_tile();

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) != BS_RESULT_OK)
        return;

    struct {
        bs_mat4 camera;
    } push_const = {
        .camera = _poser_->camera.result,
    };

    bs_beginCommentN(BS_CONSTANT_STRING("Tiles"));

    bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
    bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_PRIMITIVE_TILES)->batch, pipeline, 0, BS_U32_MAX, 0, 1);
    _bsgfx_renderPrimitives(_poser_->camera.result);

    bs_endComment();
}

BSGFXAPI void _bsgfx_renderAtlas() {
    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    _bsgfx_requiredForStencilShadows(&hash);

    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_atlas();

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) != BS_RESULT_OK)
        return;

    bs_beginCommentN(BS_CONSTANT_STRING("Atlas"));

    bs_pushConstant(pipeline, 0, sizeof(_poser_->world_camera.result), &_poser_->world_camera.result);
    _bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS], pipeline);

    bs_endComment();
}

BSGFXAPI void _bsgfx_renderPoints() {
    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_point_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_POINT_LIST;

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(_poser_->camera.result), &_poser_->camera.result);
        _bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_POINT], pipeline);
    }
}

BSGFXAPI void _bsgfx_renderLines(const bs_mat4* camera, int subtype, bool skip_depth_test) {
    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_line_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_LINE_LIST;
    hash.skip_depth_test = skip_depth_test;

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(bs_mat4), camera);
        _bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_LINE], pipeline);
    }
}

BSGFXAPI void _bsgfx_renderLineModel(const bs_mat4* camera, int subtype, bool skip_depth_test) {
    if (!bs_exists(BSGFX_ATLASES, BSGFX_ATLAS_ANY))
        return;

    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_LINE_LIST;
    hash.skip_depth_test = skip_depth_test;

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

        int white = bs_queryAtlas(atlas, "white"); // TODO: cache

        struct {
            bs_mat4 camera;
            bs_vec4 uv;
        } mesh_push_const = {
            .camera = *camera,
            .uv = bs_atlasCoordinates(atlas, white),
        };

        bs_pushConstant(pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        _bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_SPHERE_MESH], pipeline);
    }
}

BSGFXAPI void _bsgfx_renderAtlasIcons() {
    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    _bsgfx_requiredForTransparency(&hash);
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_atlas();

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) != BS_RESULT_OK)
        return;

    struct {
        bs_mat4 camera;
        float elapsed;
        float padding;
        bs_vec2 resolution;
    } push_const = {
        .camera = _poser_->screen_camera.result,
        .elapsed = bs_elapsedTime(),
        .resolution = BS_IV2_TO_V2(bs_resolution()),
    };

    bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
    _bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON], pipeline);
}

BSGFXAPI void _bsgfx_renderTileIcons() {
    bs_PipelineHash hash = _bsgfx_defaultPipelineHash();
    _bsgfx_requiredForTransparency(&hash);
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_tile_screen();

    bs_Pipeline* pipeline;
    if (bs_pipeline(&hash, &pipeline) != BS_RESULT_OK)
        return;

    bs_pushConstant(pipeline, 0, sizeof(_poser_->screen_camera.result), &_poser_->screen_camera.result);
    _bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_TILE_ICON], pipeline);
}


 /*==============================================================================
  * Graphics Pipeline
  *============================================================================*/

/*
static void _bsgfx_rayTrace() {
    if (!bs_exists(BSGFX_RAY_TRACERS, BSGFX_RAY_TRACER_MAIN))
        return;

    bs_Object* ray_tracer = bs_fetch(BSGFX_RAY_TRACERS, BSGFX_RAY_TRACER_MAIN);
    bs_RayTracePipelineHash hash = {
        //   .ray_gen_shader = $rgen_main(),
        //   .miss_shader = $rmiss_main(),
        .ray_tracer = ray_tracer->ray_tracer,
    };

    bs_Pipeline* ray_trace_pipeline;
    if (bs_rayTracingPipeline(&hash, &ray_trace_pipeline))
        return;

    bs_ivec2 resolution = bs_resolution();
    resolution.x /= BSGFX_PIXEL_SCALE;
    resolution.y /= BSGFX_PIXEL_SCALE;
    bs_rayTrace(tracer, ray_trace_pipeline, resolution.x, resolution.y, 1);
}
*/


BSGFXAPI void _bsgfx_swapBufferBindings() {
    bs_List* sources = bs_objectSources();

    for (int i = 0; i < BSGFX_BUFFERS_COUNT; i++) {
        bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, i)->buffer;
        if (!buffer)
            continue;

        if (!(buffer->flags & BSI_BUFFER_IS_BOUND))
            continue;

        if (!(buffer->flags & BSI_BUFFER_SWAPS_BIT))
            continue;

        bs_bindBuffer(buffer->bind_set, buffer->binding, buffer);
    }

    for (int i = 0; i < BSGFX_BATCHES_COUNT; i++) {
        bs_Batch* batch = bs_fetch(BSGFX_BATCHES, i)->batch;
        if (!batch)
            continue;

        if (!(batch->flags & BSI_BATCH_SWAPS_BIT))
            continue;

        if (bs_canPushBatch(batch))
            continue;

        if (batch->vertex_buffer->buffer && batch->vertex_buffer->buffer->flags & BSI_BUFFER_IS_BOUND)
            bs_bindBuffer(batch->vertex_buffer->buffer->bind_set, batch->vertex_buffer->buffer->binding, batch->vertex_buffer->buffer);

        if (batch->index_buffer->buffer && batch->index_buffer->buffer->flags & BSI_BUFFER_IS_BOUND)
            bs_bindBuffer(batch->index_buffer->buffer->bind_set, batch->index_buffer->buffer->binding, batch->index_buffer->buffer);
    }

    bs_pushDescriptors();
}
