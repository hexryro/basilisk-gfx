
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

#define BSGFX_TRANSPARENT_OPTIONS                                   \
    .src_alpha_factor = BS_BLEND_FACTOR_SRC_ALPHA,                  \
    .dst_alpha_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,        \
    .src_color_factor = BS_BLEND_FACTOR_SRC_ALPHA,                  \
    .dst_color_factor = BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,        \
    .color_op = BS_BLEND_OP_ADD,                                    \
    .alpha_op = BS_BLEND_OP_ADD

static void _bsmod_renderDepthlessLines() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_line_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_LINE_LIST;
    hash.skip_depth_test = true;

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_beginComment(BS_CONSTANT_STRING("[BSMOD] Lines (Depthless)"));

        bs_setLineWidth(4.0);
        bs_pushConstant(pipeline, 0, sizeof(poser()->camera.result), &poser()->camera.result);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_LINE_DEPTHLESS], pipeline);
        bs_setLineWidth(1.0);

        bs_endComment();
    }
}

static void _bsmod_renderLines() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_line_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_LINE_LIST;

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_beginComment(BS_CONSTANT_STRING("[BSMOD] Lines"));

        bs_setLineWidth(4.0);
        bs_pushConstant(pipeline, 0, sizeof(poser()->camera.result), &poser()->camera.result);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_LINE], pipeline);
        bs_setLineWidth(1.0);

        bs_endComment();
    }
}

static void _bsmod_renderPoints() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_point_instanced();
    hash.shaders[1] = $fs_bsgfx_color();
    hash.topology_type = BS_PRIMITIVE_TOPOLOGY_POINT_LIST;
    hash.skip_depth_test = true;

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(poser()->camera.result), &poser()->camera.result);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_POINT], pipeline);
    }
}

static void _bsmod_renderCones() {
    if (!bs_exists(BSGFX_ATLASES, BSGFX_ATLAS_ANY))
        return;

    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    bs_beginComment(BS_CONSTANT_STRING("Cones"));

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

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_CONE_MESH], pipeline);
    }
}

static void _bsmod_renderPreviousPass() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_color_percentage();
    hash.shaders[1] = $fs_bsgfx_lo_res_ui_post_0();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
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
            .resolution = BS_V2_MUL_S(BS_IV2_TO_V2(bs_resolution()), 0.5),
        };

        bs_m4Inverse(&poser()->camera.proj, &push_const.inv_proj);

        //  bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)->batch, pipeline, 6, 6, 0, 1);
    }
}

static void _bsmod_renderUIPost() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_color_percentage();
    hash.shaders[1] = $fs_bsgfx_lo_res_ui_post_0();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
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
            .resolution = BS_V2_MUL_S(BS_IV2_TO_V2(bs_resolution()), 0.5),
        };
        bs_m4Inverse(&poser()->camera.proj, &push_const.inv_proj);

        //  bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)->batch, pipeline, 6, 6, 0, 1);
    }
}

static void _bsmod_renderSelectedTile() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_tile_static();
    hash.shaders[1] = $fs_bsgfx_tile_selected();
    hash.skip_depth_test = true;

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
        } push_const = {
            .camera = poser()->camera.result,
        };

        bs_beginComment(BS_CONSTANT_STRING("Selected Tiles"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bs_render(bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_TILE)->batch, pipeline, 0, BS_U32_MAX, 0, 1);

        bs_endComment();
    }
}

static void _bsmod_renderTiles() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_tile_screen();
    bsgfx_requiredForTransparency(&hash);
    hash.stencil_front = (bs_StencilOperation) {
        .fail_op = BS_STENCIL_OP_KEEP,
        .pass_op = BS_STENCIL_OP_KEEP,
        .depth_fail_op = BS_STENCIL_OP_KEEP,
        .compare_op = BS_COMPARE_OP_EQUAL,
        .compare_mask = 0xFF,
        .write_mask = 0x00,
        .reference = 2, // TODO
    };

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(poser()->screen_camera.result), &poser()->screen_camera.result);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_TILE_ICON], pipeline);
    }
}

static void _bsmod_renderFontSubtype(int subtype, bsgfx_Id font_id, bs_Shader* fragment_shader) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    // bs_Object* font_object = bs_fetch(BSGFX_FONTS, font_id)->head;
    bs_Shader* vertex_shader = $vs_bsgfx_quad_instanced();

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = vertex_shader;
    hash.shaders[1] = fragment_shader;
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_pushConstant(pipeline, 0, sizeof(poser()->screen_camera.result), &poser()->screen_camera.result);
        bsgfx_renderSubtype(subtype, pipeline);
    }
}

static void _bsmod_renderPrefabOutlines() {
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

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        bs_beginComment(BS_CONSTANT_STRING("Prefabs"));

        bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
        struct {
            bs_mat4 camera;
            bs_vec4 uv;
        } mesh_push_const = {
            .camera = poser()->camera.result,
            .uv = $BSGFX_ATLAS_ANY_white()->coords,
        };

        bs_pushConstant(pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        bsgfx_renderPrefabs(pipeline, BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE);

        bs_endComment();
    }

}

static void _bsmod_renderRoundedQuads() {
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

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution()),
            .border_radius = 5.0,
        };

        bs_beginComment(BS_CONSTANT_STRING("Rounded Quads"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_ATLAS_ICON], pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderUI() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_ui();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution()),
        };

        bs_beginComment(BS_CONSTANT_STRING("UI"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_UI], pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderUISolid() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_ui_color();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution()),
        };

        bs_beginComment(BS_CONSTANT_STRING("UI (Color only)"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_UI_COLOR], pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderUIStencil() {
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

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution()),
        };

        bs_beginComment(BS_CONSTANT_STRING("UI Stencil"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_UI_STENCIL], pipeline);

        bs_endComment();
    }
}

static void _bsmod_renderDither() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
    hash.shaders[1] = $fs_bsgfx_dither();
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            float elapsed;
            float padding;
            bs_vec2 resolution;
            float border_radius;
        } push_const = {
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution()),
        };

        bs_beginComment(BS_CONSTANT_STRING("Dither"));

        bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_DITHER], pipeline);

        bs_endComment();
    }
}


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
            .camera = poser()->screen_camera.result,
            .elapsed = bs_elapsedTime(),
            .resolution = BS_IV2_TO_V2(bs_resolution()),
        };

        bs_beginComment(BS_CONSTANT_STRING("Gradients"));

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
            .camera = poser()->screen_camera.result,
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
        bs_beginComment(BS_CONSTANT_STRING("Material Texture Quad"));

        struct {
            bs_mat4 camera;
        } push_const = {
            .camera = poser()->screen_camera.result,
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
            .camera = poser()->screen_camera.result,
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

        bs_pushConstant(pipeline, 0, sizeof(bs_mat4), &poser()->screen_camera.result);
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
        bs_beginComment(BS_CONSTANT_STRING("Prefabs"));

        bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;

        struct {
            bs_mat4 camera;
            bs_vec4 uv;
        } mesh_push_const = {
            .camera = poser()->camera.result,
            .uv = bs_atlasCoordinates(atlas, bs_queryAtlas(atlas, "white")),
        };

        bs_pushConstant(pipeline, 0, sizeof(mesh_push_const), &mesh_push_const);
        bsgfx_renderPrefabs(pipeline, BSGFX_PREFAB_SUBTYPE_MESH);

        bs_endComment();
    }
}

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
    bsgfx_renderPrimitives(poser()->screen_camera.result);

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

BSMODAPI bs_Queue* _bsmod_onQueue() {
    bs_Result result;

    bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS)->queue;
    bs_Queue* bsgfx_queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS)->queue;

    bs_awaitQueue(bsgfx_queue, BS_PIPELINE_STAGE_VERTEX_INPUT_BIT);
    bs_enqueue(queue, _bsmod_runRenderPass);

    result = bs_stall(queue);
    //if (result == BS_RESULT_DEVICE_LOST)
    //    bsgfx_onDeviceLost();

    if (bs_keyDownOnce(BS_KEY_G))
        _bsmod_queueRasterize(BSMOD_CONTENT_PATH, "material_icons", _bsmod_rasterizeMaterialIcons);

    if (bs_keyDownOnce(BS_KEY_K))
        _bsmod_queueRasterize(BSMOD_CONTENT_PATH, "primitive_icons", _bsmod_rasterizePrimitiveIcons);

    if (bs_keyDownOnce(BS_KEY_L))
        _bsmod_queueRasterize(BSMOD_CONTENT_PATH, "prefab_icons", _bsmod_rasterizePrefabIcons);

    _bsmod_pollRasterizer();

    return queue;
}