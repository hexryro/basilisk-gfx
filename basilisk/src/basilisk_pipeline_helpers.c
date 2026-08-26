
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

#include <basilisk-mod.h>
#include <bsmod_cache.h>
#include <basilisk_pipeline.h>

void basilisk_renderDepthlessLines(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_line_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_LINE_LIST;
    hash.skip_depth_test = true;

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        bs_beginCommentN(queue, BS_CONSTANT_STRING("[BSMOD] Lines (Depthless)"));

        bs_setLineWidth(queue, 4.0);
        bs_pushConstant(queue, pipeline, 0, sizeof(poser()->camera.result), &poser()->camera.result);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE_DEPTHLESS], pipeline);
        bs_setLineWidth(queue, 1.0);

        bs_endComment(queue);
    }
}

void basilisk_renderLines(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_line_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_LINE_LIST;

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        bs_beginCommentN(queue, BS_CONSTANT_STRING("[BSMOD] Lines"));

        bs_setLineWidth(queue, 4.0);
        bs_pushConstant(queue, pipeline, 0, sizeof(poser()->camera.result), &poser()->camera.result);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_LINE], pipeline);
        bs_setLineWidth(queue, 1.0);

        bs_endComment(queue);
    }
}

void basilisk_renderPoints(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_point_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_POINT_LIST;
    hash.skip_depth_test = true;

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(queue, pipeline, 0, sizeof(poser()->camera.result), &poser()->camera.result);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_POINT], pipeline);
    }
}

void basilisk_renderCones(bs_RendererScope* scope, bs_Queue* queue) {
    if (!bs_exists(BSGFX_ATLASES, BSGFX_ATLAS_ANY))
        return;

    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    bs_beginCommentN(queue, BS_CONSTANT_STRING("Cones"));

    bs_Object* atlas_object = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY);

    struct {
        bs_mat4 camera;
        bs_vec4 uv;
    } mesh_push_const = {
        .camera = poser()->camera.result,
        .uv = bs_atlasCoordinates(atlas_object->atlas, bs_queryAtlas(atlas_object->atlas, "white")),
    };

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_instanced();
    hash.shaders[1] = $fs_bsgfx_model();
    hash.skip_depth_test = true;

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(queue, pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_CONE_MESH], pipeline);
    }
}

void basilisk_renderUIPost(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_color_percentage();
    hash.shaders[1] = $fs_bsgfx_lo_res_ui_post_0();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 inv_proj;
            bs_vec3 selected_color;
            float elapsed;
            bs_vec3 light_direction;
            float pad;
            bs_vec2 resolution;
        } push_const = {
            .selected_color = BS_V3(1.0, 1.0, 1.0),
            .elapsed = bs_elapsedTime(),
            .light_direction = poser()->sun_direction,
            .resolution = BS_V2_MUL_S(BS_IV2_TO_V2(bs_resolution(bs_scope()->context)), 0.5),
        };
        bs_m4Inverse(&poser()->camera.proj, &push_const.inv_proj);

        bs_Batch* screen_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)->batch;

        //  bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bs_render(queue, screen_batch, pipeline, 6, 6, 0, 1);
    }
}

void basilisk_renderSelectedTile(bs_RendererScope* scope, bs_Queue* queue) {
    return; // TODO: $fs_bsgfx_tile_selected needs to compile
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_tile_static();
    hash.shaders[1] = $fs_bsgfx_tile_selected();
    hash.skip_depth_test = true;

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
        } push_const = {
            .camera = poser()->camera.result,
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("Selected Tiles"));

        bs_Batch* tile_batch = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_TILE)->batch;

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bs_render(queue, tile_batch, pipeline, 0, BS_U32_MAX, 0, 1);

        bs_endComment(queue);
    }
}

void basilisk_renderTiles(bs_RendererScope* scope, bs_Queue* queue) {
    return; // TODO: $fs_bsgfx_tile_screen needs to compile
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_tile_screen();
    bsgfx_requiredForTransparency(&hash);
    hash.stencil_front = (bs_StencilOperation){
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
        .reference = 2, // TODO
    };

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(queue, pipeline, 0, sizeof(poser()->screen_camera.result), &poser()->screen_camera.result);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_TILE_ICON], pipeline);
    }
}

void basilisk_renderPrefabOutlines(bs_RendererScope* scope, bs_Queue* queue) {
    if (!bs_exists(BSGFX_ATLASES, BSGFX_ATLAS_ANY))
        return;

    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_mesh_instanced();
    hash.shaders[0] = $fs_bsgfx_model();
    hash.polygon_type = BS_POLYGON_MODE_LINE;
    hash.skip_depth_test = true;
    hash.cull_type = bsgfx_settings()->cull_backfaces ? BS_CULL_MODE_BACK_BIT : BS_CULL_MODE_NONE;

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        bs_beginCommentN(queue, BS_CONSTANT_STRING("Prefabs"));

        bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
        struct {
            bs_mat4 camera;
            bs_vec4 uv;
        } mesh_push_const = {
            .camera = poser()->camera.result,
            .uv = $BSGFX_ATLAS_ANY_white()->coords,
        };

        bs_pushConstant(queue, pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        bsgfx_renderPrefabs(queue, pipeline, BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE);

        bs_endComment(queue);
    }

}

void basilisk_renderRoundedQuads(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_atlas_rounded();
    bsgfx_requiredForTransparency(&hash);
    hash.stencil_front = (bs_StencilOperation){
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
    };

    hash.stencil_back = (bs_StencilOperation){
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
    };

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context)),
            .border_radius = 5.0,
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("Rounded Quads"));

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_ATLAS_ICON], pipeline);

        bs_endComment(queue);
    }
}

void basilisk_renderUI(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_ui();
  //  bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context)),
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("UI"));

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_UI], pipeline);

        bs_endComment(queue);
    }
}

void basilisk_renderFontSubtype(bs_RendererScope* scope, bs_Queue* queue, bsgfx_InstanceSubtype* subtype, bsgfx_Id font_id, bs_Shader* fragment_shader) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    // bs_Object* font_object = bs_fetch(BSGFX_FONTS, font_id)->head;
    bs_Shader* vertex_shader = $vs_bsgfx_quad_rounded_instanced();

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = vertex_shader;
    hash.shaders[1] = fragment_shader;
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        bs_pushConstant(queue, pipeline, 0, sizeof(poser()->screen_camera.result), &poser()->screen_camera.result);
        bsgfx_renderSubtype(queue, subtype, pipeline);
    }
}

void basilisk_renderUISolid(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_ui_color();
   // bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context)),
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("UI (Color only)"));

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_UI_COLOR], pipeline);

        bs_endComment(queue);
    }
}

void basilisk_renderUIStencil(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_ui();
    bsgfx_requiredForTransparency(&hash);

    hash.stencil_front = (bs_StencilOperation){
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
        .reference = 2, // TODO
    };

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context)),
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("UI Stencil"));

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_UI_STENCIL], pipeline);

        bs_endComment(queue);
    }
}

void basilisk_renderDither(bs_RendererScope* scope, bs_Queue* queue) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_dither();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context)),
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("Dither"));

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_DITHER], pipeline);

        bs_endComment(queue);
    }
}