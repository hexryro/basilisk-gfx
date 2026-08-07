
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
#include <basilisk.h>

/**
 Low Resolution Subpass 0
 Renders pixelated geometry
 Writes to
   BSGFX_IMAGE_LO_RES_DEPTH
   BSGFX_IMAGE_LO_RES_COLOR
   BSGFX_IMAGE_LO_RES_NORMAL
   BSGFX_IMAGE_LO_RES_POSITION
   BSGFX_IMAGE_LO_RES_INDEX
 */
static void _bsgfx_loResSubpass0() {
}

/**
 Low Resolution Subpass 1
 Used for post processing
 Writes to BSGFX_IMAGE_LO_RES_RESULT
 */
static void _bsgfx_loResSubpass1() {
    bs_beginCommentN(BS_CONSTANT_STRING("Low Resolution Subpass 1"));

    if (bs_exists(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)) {
        bs_barrier(0,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            BS_ACCESS_SHADER_READ_BIT);

        bs_PipelineHash hash = bsgfx_defaultPipelineHash();
        hash.shaders[0] = $vs_bsgfx_color_percentage();
        hash.shaders[1] = $fs_bsgfx_hilight();

        bs_Pipeline* pipeline;
        if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
            struct {
                float offset_x;
                float offset_y;
                float elapsed;
                //   int noise;
            } push_const = {
                .offset_x = poser()->world_camera.position.x / (bs_resolution().x / BSGFX_PIXEL_SCALE),
                .offset_y = poser()->world_camera.position.y / (bs_resolution().y / BSGFX_PIXEL_SCALE),
                .elapsed = bs_elapsedTime(),
                //   .noise = _bsgfx_queryTexture(512, "noise_00"),
            };

            bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
            bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)->batch, pipeline, 0, 6, 0, 1);
        }
    }

    bs_endComment();


}

 /**
  High Resolution Subpass 0
  Writes to the swapchain (or whatever)
  */
static void basilisk_hiResSubpass0() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    bs_beginCommentN(BS_CONSTANT_STRING("High Resolution Subpass 0"));

    bs_Renderer* renderer = bs_fetch(BASILISK_RENDERERS, BASILISK_RENDERER_MAIN)->renderer;
    bs_clearColor(0, bs_resolution(), BS_RGBA(75, 75, 75, 255));

    basilisk_renderDepthlessLines();
    basilisk_renderPoints();
    basilisk_renderCones();
    basilisk_renderSelectedTile();
    basilisk_renderRoundedQuads();
    bsgfx_renderColorPickers();
    basilisk_renderUISolid();
    basilisk_renderUI();

    int package = bs_queryPackage("content/basilisk-fonts.bpak");

    if (package >= 0) {
        bs_Resource* resource = NULL;
        bs_queryResource(package, BS_RESOURCE_FONT, "project/fonts/segoeui.ttf", &resource);
        if (resource && resource->model) {
            bsgfx_Font* font = resource->model;
            basilisk_renderFontSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_FONT], 0, $fs_bsgfx_font_small());
        }
    }
    basilisk_renderUIStencil();
    basilisk_renderDither();



  //  bs_clearDepth(0, bs_fetch(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH)->image->dim, 1.0);
    basilisk_renderTiles();
    bsgfx_renderPrimitives(poser()->screen_camera.result);

    /*
   // Final post processing step on the BSGFX_IMAGE_LO_RES_RESULT
    if (bs_exists(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)) {
        hash = bsgfx_defaultPipelineHash();
        bsgfx_requiredForTransparency(&hash);
        hash.shaders[0] = $vs_bsgfx_color_percentage();
        hash.shaders[1] = $fs_bsgfx_pixelation();

        if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
            bs_beginCommentN(BS_CONSTANT_STRING("Post processing"));

            bs_ivec2 resolution = bs_resolution();
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
                .resolution = { resolution.x, resolution.y },
            };
            bs_m4Inverse(&poser()->camera.proj, &push_const.inv_proj);

            bs_pushConstant(pipeline, 0, sizeof(push_const), &push_const);
            bs_render(bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_SCREEN)->batch, pipeline, 0, 6, 0, 1);

            bs_endComment();
        }
    }
    */

    bsgfx_renderColorPickers();

    /**
     Textures
     */
    hash = bsgfx_defaultPipelineHash();
    bsgfx_requiredForTransparency(&hash);
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_256_hi_res();

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(pipeline, 0, sizeof(poser()->screen_camera.result), &poser()->screen_camera.result);
        bsgfx_renderSubtype(bsgfx_subtypes()[BSGFX_SUBTYPE_256_HI], pipeline);
    }

    bsgfx_renderAtlasIcons();
    bsgfx_renderTileIcons();

    bs_endComment();
}

static void basilisk_graphicsPipe() {
    if (bs_exists(BASILISK_RENDERERS, BASILISK_RENDERER_MAIN)) {
        bs_Renderer* hi_res_renderer = bs_fetch(BASILISK_RENDERERS, BASILISK_RENDERER_MAIN)->renderer;
        bs_Callback callbacks[] = {
            basilisk_hiResSubpass0,
        };
        bs_runPass(hi_res_renderer, callbacks, sizeof(callbacks) / sizeof(*callbacks));
    }
}

void basilisk_pipeline() {
    if (!bs_exists(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS))
        return;

    bs_Queue* graphics_queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS)->queue;
    bs_setScope(&(bs_Scope) { 0 });

    bs_acquire();

    bs_awaitAcquisition();
    bs_enqueue(graphics_queue, basilisk_graphicsPipe);

    bs_stall(graphics_queue);

    bs_Queue* user_queue = NULL;
    if (bsgfx_callbacks()->queue)
        user_queue = bsgfx_callbacks()->queue();

    bs_Queue* last_queue = user_queue ? user_queue : graphics_queue;
    bs_Queue* wait_queues[] = {
        last_queue
    };

    bs_present(last_queue, wait_queues, sizeof(wait_queues) / sizeof(*wait_queues));
}

void basilisk_createRenderers() {
    bs_Object* hi_res = BS_RENDERER(BASILISK_RENDERERS, BASILISK_RENDERER_MAIN, BS_OBJECT_HAS_SWAPS_BIT);
    if (bs_renderer(hi_res, BS_RENDERER_AUTO_RESIZE_BIT) == BS_RESULT_OK) {

        bs_ivec2 resolution = bs_resolution();
        bs_Object* hi_res_0_depth = BS_IMAGE(BASILISK_IMAGES, BASILISK_IMAGE_MAIN_OUTPUT_DEPTH, 0);
        if (bs_image(hi_res_0_depth, resolution, 0, BS_FORMAT_D32_SFLOAT_S8_UINT, BS_IMAGE_ATTACHMENT_BIT) == BS_RESULT_OK) {

             bs_output(hi_res->renderer, (bs_Output) {
                .subpass = 0,
                .image = hi_res_0_depth->image,
                .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
                .store_op = BS_ATTACHMENT_STORE_OP_STORE,
                .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
                .new_layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            });

            bs_output(hi_res->renderer, (bs_Output) {
                .subpass = 0,
                .image = bs_context()->swapchain_image->image,
                .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
                .store_op = BS_ATTACHMENT_STORE_OP_STORE,
                .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
                .new_layout = BS_IMAGE_LAYOUT_PRESENT_SRC_KHR,
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
}