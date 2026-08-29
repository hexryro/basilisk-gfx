
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
  High Resolution Subpass 0
  Writes to the swapchain
  */
_Thread_local bs_RGBA _clear_color_;

static void basilisk_hiResSubpass0(bs_RendererScope* scope) {
    bs_Queue* queue = scope->queue;

    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    bs_beginCommentN(queue, BS_CONSTANT_STRING("High Resolution Subpass 0"));

    bs_vec4 clear_color = bs_rgbUCharToV4(_clear_color_);
    clear_color.xyz = bs_sRGBToLinearV3(&clear_color.xyz);

    bs_clearColor(queue, 0, bs_resolution(bs_scope()->context), &clear_color);

    basilisk_renderDepthlessLines(scope, queue);
    basilisk_renderPoints(scope, queue);
    basilisk_renderCones(scope, queue);
    basilisk_renderSelectedTile(scope, queue);
    basilisk_renderRoundedQuads(scope, queue);
    bsgfx_renderColorPickers(scope, queue);
    basilisk_renderUISolid(scope, queue);
    basilisk_renderUI(scope, queue);

    basilisk_renderFontSubtype(scope, queue, bsgfx_subtypes()[BSGFX_SUBTYPE_FONT], 0, $fs_bsgfx_font_small());

    basilisk_renderUIStencil(scope, queue);
    basilisk_renderDither(scope, queue);

  //  bs_clearDepth(0, bs_fetch(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH)->image->dim, 1.0);
    basilisk_renderTiles(scope, queue);
    bsgfx_renderPrimitives(scope, queue, bsgfx_app()->screen_camera.result);

    bsgfx_renderColorPickers(scope, queue);

    /**
     Textures
     */
    hash = bsgfx_defaultPipelineHash();
    bsgfx_requiredForTransparency(&hash);
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_256_hi_res();

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {

        bs_pushConstant(queue, pipeline, 0, sizeof(bsgfx_app()->screen_camera.result), &bsgfx_app()->screen_camera.result);
        bsgfx_renderSubtype(queue, bsgfx_subtypes()[BSGFX_SUBTYPE_256_HI], pipeline);
    }

    bsgfx_renderAtlasIcons(scope, queue);
    bsgfx_renderTileIcons(scope, queue);

    bs_endComment(queue);
}

void basilisk_pipeline(bs_Queue* queue, bs_Renderer* renderer, bs_RGBA clear_color) {
    if (!bs_exists(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS))
        return;

    _clear_color_ = clear_color;
    bs_acquire();

    if (bs_resetQueue(queue) == BS_RESULT_OK) {
        bs_SubpassFunction callbacks[] = {
            basilisk_hiResSubpass0,
        };
        bs_runPass(queue, renderer, callbacks, sizeof(callbacks) / sizeof(*callbacks));

        bs_WaitSemaphore wait_semaphores[] = {
            bs_acquisitionSemaphore(),
        };
        int wait_semaphores_count = sizeof(wait_semaphores) / sizeof(*wait_semaphores);
        bs_pushQueue(queue, wait_semaphores_count, wait_semaphores);
    }
    bs_stall(queue);

    bs_Queue* user_queue = NULL;
    if (bsgfx_callbacks()->queue)
        user_queue = bsgfx_callbacks()->queue();

    bs_Queue* last_queue = user_queue ? user_queue : queue;
    bs_Queue* wait_queues[] = {
        last_queue
    };

    bs_present(last_queue, wait_queues, sizeof(wait_queues) / sizeof(*wait_queues));
}

void basilisk_createHiResRenderer(bs_Context* context, int id) {
    bs_Object* hi_res = BS_RENDERER(BASILISK_RENDERERS, id, BS_OBJECT_HAS_SWAPS_BIT);
    if (bs_renderer(hi_res, 0) == BS_RESULT_OK) {
        bs_autoResizeRenderer(hi_res->renderer, context);

        bs_ivec2 resolution = bs_resolution(context);
        bs_Object* hi_res_0_depth = BS_IMAGE(-1, -1, 0);
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
                .image = context->swapchain_image->image,
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
            hi_res->renderer->_->framebuffer;
            bs_renderPass(hi_res->renderer);
            bs_framebuffer(hi_res->renderer, bs_resolution(context));
        }
    }
}

void basilisk_createRenderers() {
    basilisk_createHiResRenderer(bs_fetch(BSGFX_CONTEXTS, BSGFX_CONTEXT_MAIN)->context, BASILISK_RENDERER_MAIN);
    if (bs_exists(BASILISK_CONTEXTS, BASILISK_CONTEXT_MENU))
        basilisk_createHiResRenderer(bs_fetch(BASILISK_CONTEXTS, BASILISK_CONTEXT_MENU)->context, BASILISK_RENDERER_MENU_CONTEXT);
    if (bs_exists(BASILISK_CONTEXTS, BASILISK_CONTEXT_TITLE_BAR))
        basilisk_createHiResRenderer(bs_fetch(BASILISK_CONTEXTS, BASILISK_CONTEXT_TITLE_BAR)->context, BASILISK_RENDERER_TITLE_BAR);
}