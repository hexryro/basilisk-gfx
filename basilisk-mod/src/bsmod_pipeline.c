
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


/*
static void _bsmod_renderGradients() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_edge_gradient();
    bsgfx_requiredForTransparency(&hash);
    hash.stencil_front = (bs_StencilOperation) {
        .fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .depth_fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .compare_op = BS_COMPARE_OP_ALWAYS,
        .compare_mask = 0xFF,
        .write_mask = 0xFF,
    };

    hash.stencil_back = (bs_StencilOperation) {
        .fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .depth_fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
        .compare_op = BS_COMPARE_OP_ALWAYS,
        .compare_mask = 0xFF,
        .write_mask = 0xFF,
    };

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
        } push_const = {
            .camera = bsgfx_app()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context)),
        };

        bs_beginCommentN(BS_CONSTANT_STRING("Gradients"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_CORNER_GRADIENT], pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderMeshSubtypes() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_instanced_2d();
    hash.shaders[1] = $fs_bsgfx_model();
    hash.stencil_front = (bs_StencilOperation){
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
        .reference = 2, // TODO:
    };

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float z;
        } push_const = {
            .camera = bsgfx_app()->screen_camera.result,
            .z = 50 // todo
        };

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderPrefabs(pipeline, BSGFX_PREFAB_SUBTYPE_MESH_HI_RES_SCREEN);
    }
}

static void _bsmod_renderMaterialTextureQuads() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_material_texture();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_beginCommentN(BS_CONSTANT_STRING("Material Texture Quad"));

        struct {
            bs_mat4 camera;
        } push_const = {
            .camera = bsgfx_app()->screen_camera.result,
        };

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_QUAD_MATERIAL_TEXTURE], pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderIcons(const char* comment, int binding, int subtype) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsmod_material_icon();
    bsgfx_requiredForTransparency(&hash);

    if (_bsmod_instance_grid_menu_) {
        hash.stencil_front = (bs_StencilOperation){
            .fail_op = BS_STENCIL_OP_KEEP,
            .pass_op = BS_STENCIL_OP_KEEP,
            .depth_fail_op = BS_STENCIL_OP_KEEP,
            .compare_op = BS_COMPARE_OP_EQUAL,
            .compare_mask = 0xFF,
            .write_mask = 0x00,
            .reference = 2, // TODO:
        };
    }

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_beginComment(comment, strlen(comment));

        struct {
            bs_mat4 camera;
            int atlas_binding;
        } push_const = {
            .camera = bsgfx_app()->screen_camera.result,
            .atlas_binding = binding,
        };

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(subtype, pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderTileIcons() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_tile_screen();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(bs_mat4), &bsgfx_app()->screen_camera.result);
        bsgfx_renderSubtype(_bsmod_subtypes_[BSMOD_SUBTYPE_TILE_ICON], pipeline);
    }
}

static void _bsmod_renderPrefabs() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_instanced();
    hash.shaders[1] = $fs_bsgfx_model();
    hash.cull_type = bsgfx_settings()->cull_backfaces ? BS_CULL_MODE_BACK_BIT : BS_CULL_MODE_NONE;

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_beginCommentN(BS_CONSTANT_STRING("Prefabs"));

        bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

        struct {
            bs_mat4 camera;
            bs_vec4 uv;
        } mesh_push_const = {
            .camera = bsgfx_app()->camera.result,
            .uv = bs_atlasCoordinates(atlas, bs_queryAtlas(atlas, "white")),
        };

        bs_pushConstant(pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        bsgfx_renderPrefabs(pipeline, BSGFX_PREFAB_SUBTYPE_MESH);

        bs_endComment();
    }
}

/*
static void _bsmod_onRenderUI() {
    bs_pushDescriptors();

    _bsmod_renderPreviousPass();
    _bsmod_renderDepthlessLines();
    _bsmod_renderPoints();
    _bsmod_renderCones();
    _bsmod_renderSelectedTile();
    if (bsgfx_prefabModel())
        _bsmod_renderPrefabOutlines();
    _bsmod_renderGradients();
    _bsmod_renderRoundedQuads();
    bsgfx_renderColorPickers();
    _bsmod_renderUISolid();
    _bsmod_renderUI();
    _bsmod_renderUIStencil();
    _bsmod_renderMaterialTextureQuads();
    _bsmod_renderDither();
    _bsmod_renderFontSubtype(_bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS], BSGFX_FONT_ARIAL_16, $fs_bsgfx_font_arial());
    bs_clearDepth(0, bs_fetch(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH)->image->dim, 1.0);
    _bsmod_renderTiles();
    if (bsgfx_prefabModel())
        _bsmod_renderMeshSubtypes();
    bsgfx_renderPrimitives(bsgfx_app()->screen_camera.result);

    _bsmod_renderIcons("Material Icons", BSMOD_ATLAS_ICONS_MATERIALS_BINDING, _bsmod_subtypes_[BSMOD_SUBTYPE_MATERIAL_ICON]);
    _bsmod_renderIcons("Primitive Icons", BSMOD_ATLAS_ICONS_PRIMITIVES_BINDING, _bsmod_subtypes_[BSMOD_SUBTYPE_PRIMITIVE_ICON]);
    _bsmod_renderIcons("Prefab Icons", BSMOD_ATLAS_ICONS_PREFABS_BINDING, _bsmod_subtypes_[BSMOD_SUBTYPE_PREFAB_ICON]);
    _bsmod_renderTileIcons();
}

static void _bsmod_onRender3D() {
    if (bsgfx_prefabModel()) {
        _bsmod_renderPrefabs();
    }
    _bsmod_renderLines();
    _bsmod_renderBillboards();
}

static void _bsmod_runRenderPass() {
    // bsgfx_processCursorReads();
     //bsgfx_fenceCapture();
    bs_pushDescriptors();

    bsgfx_resetInstances();
    _bsmod_onTick();
    bsgfx_tickInstances();

    bs_Image* src_depth = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_LO_RES_0_DEPTH)->image;
    bs_Image* dst_depth = bs_fetch(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH_3D)->image;

    bs_blit((bs_BlitOperation) {
        .source = src_depth,
        .destination = dst_depth,
        .source_layout = BS_IMAGE_LAYOUT_GENERAL,
        .destination_layout = BS_IMAGE_LAYOUT_GENERAL,
        .source_scale = src_depth->dim,
        .destination_scale = dst_depth->dim,
    });

    const bs_Callback callbacks_2d[] = { _bsmod_onRenderUI };
    const bs_Callback callbacks_3d[] = { _bsmod_onRender3D };

    bs_runPass(bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER)->renderer, callbacks_2d, sizeof(callbacks_2d) / sizeof(*callbacks_2d));

    //bs_transition(dst_depth, 0, BS_IMAGE_LAYOUT_PRESENT_SRC_KHR, BS_IMAGE_LAYOUT_GENERAL);
    bs_runPass(bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER_3D)->renderer, callbacks_3d, sizeof(callbacks_3d) / sizeof(*callbacks_3d));

    //bs_Renderer* lo_res_overlay_renderer = bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER)->renderer;
    //if (lo_res_overlay_renderer) {
        //        bs_runPass(lo_res_overlay_renderer,
        //            bsgfx_loResUISubpass0,
        //            NULL);
    //}
}
*/

BSMODAPI bs_Queue* _bsmod_onQueue() {
    bs_Result result;

    bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS)->queue;
   // bs_Queue* bsgfx_queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS)->queue;

   // bs_awaitQueue(bsgfx_queue, BS_PIPELINE_STAGE_VERTEX_INPUT_BIT);
   // bs_enqueue(queue, _bsmod_runRenderPass);

  //  result = bs_stall(queue);
    //if (result == BS_RESULT_DEVICE_LOST)
    //    bsgfx_onDeviceLost();

    if (bs_inputDownOnce(BS_KEY_G))
        _bsmod_queueRasterize(BSMOD_CONTENT_PATH, "material_icons", _bsmod_rasterizeMaterialIcons);

    if (bs_inputDownOnce(BS_KEY_K))
        _bsmod_queueRasterize(BSMOD_CONTENT_PATH, "primitive_icons", _bsmod_rasterizePrimitiveIcons);

    if (bs_inputDownOnce(BS_KEY_L))
        _bsmod_queueRasterize(BSMOD_CONTENT_PATH, "prefab_icons", _bsmod_rasterizePrefabIcons);

    _bsmod_pollRasterizer();

    return queue;
}
