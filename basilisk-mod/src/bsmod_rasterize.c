
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

typedef struct {
    int instance_id;
    int subtype;
    int category;
    char* name;
    bs_Image* image;
    bs_Image* scaled_image;
    bs_Image* depth_image;
    bs_Buffer* buffer;
    bs_Renderer* renderer;
    bs_PipelineHash pipeline_hash;
    size_t push_constant_size;
    char push_constant[128];
} bsmod_Rasterization;

static bs_List _bsmod_rasterizations = { .unit_size = sizeof(bsmod_Rasterization), .increment = 32 };
static bs_ivec2 render_size = { 0 };
static bs_ivec2 output_size = { 0 };
static void _bsmod_renderToImage() {

}

BSMODAPI void _bsmod_beginRasterize(bs_ivec2 _render_size, bs_ivec2 _output_size) {
    render_size = _render_size;
    output_size = _output_size;

    bs_pushDescriptors();
    bsgfx_resetInstances();
    _bsmod_rasterizations.count = 0;
}

static void _bsmod_destroyRasterizer(bsmod_Rasterization* rasterization) {
    if (rasterization->renderer)
        bs_destroyRenderer(rasterization->renderer);
    if (rasterization->image)
        bs_destroyImage(rasterization->image);
    if (rasterization->scaled_image)
        bs_destroyImage(rasterization->scaled_image);
    if (rasterization->depth_image)
        bs_destroyImage(rasterization->depth_image);
    if (rasterization->buffer)
        bs_destroyImage(rasterization->buffer);
}

 /**
  Rasterize Instance
  */
BSMODAPI bs_Result _val_bsmod_rasterizeInstance(
    bs_Queue* queue,
    bs_PipelineHash pipeline_hash,
    int subtype,
    int instance_id,
    int category,
    char* name,
    int width,
    int height,
    size_t push_constant_size,
    unsigned char* push_constant) 
{
    if (!bsgfx_validateSubtype("MOD", subtype))
        return BS_RESULT_VALIDATION_ERROR;

    if (!bsgfx_validateInstanceType("MOD", instance_id))
        return BS_RESULT_VALIDATION_ERROR;

    // BSGFX_VALIDATE(push_constant_size < BS_MAX_PUSH_CONSTANT_SIZE,); // TODO: check _bs_settings_ or something

    return _bsmod_rasterizeInstance(queue, pipeline_hash, subtype, instance_id, category, name, width, height, push_constant_size, push_constant);
}

BSMODAPI bs_Result _bsmod_rasterizeInstance(
    bs_Queue* queue,
    bs_PipelineHash pipeline_hash,
    int subtype, 
    int instance_id, 
    int category,
    char* name, 
    int width, 
    int height, 
    size_t push_constant_size, 
    unsigned char* push_constant) 
{
    bs_Result result;

    bsmod_Rasterization* rasterization = bs_pushBack(&_bsmod_rasterizations, &(bsmod_Rasterization) {
        .instance_id = instance_id,
        .subtype = subtype,
        .pipeline_hash = pipeline_hash,
        .name = strdup(name),
        .category = category,
        .push_constant_size = push_constant_size,
    });

    memcpy(rasterization->push_constant, push_constant, push_constant_size);

    bs_Object* renderer_object = BS_RENDERER(-1, 0, 0);
    bs_Object* image_object = BS_IMAGE(-1, 0, 0);
    bs_Object* scaled_image_object = BS_IMAGE(-1, 0, 0);
    bs_Object* depth_image_object = BS_IMAGE(-1, 0, 0);
    bs_Object* buffer_object = BS_BUFFER(-1, 0, 0);

    rasterization->renderer = renderer_object->renderer;
    rasterization->image = image_object->image;
    rasterization->scaled_image = scaled_image_object->image;
    rasterization->depth_image = depth_image_object->image;
    rasterization->buffer = buffer_object->buffer;

    result = bs_renderer(renderer_object, 0);
    if (result != BS_RESULT_OK) goto fail;

    result = bs_image(image_object, render_size, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);
    if (result != BS_RESULT_OK) goto fail;

    result = bs_image(scaled_image_object, output_size, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT | BS_IMAGE_USAGE_TRANSFER_DST_BIT);
    if (result != BS_RESULT_OK) goto fail;

    result = bs_image(depth_image_object, render_size, 0, BS_FORMAT_D32_SFLOAT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);
    if (result != BS_RESULT_OK) goto fail;

    result = bs_buffer(buffer_object, rasterization->scaled_image->dim.x * rasterization->scaled_image->dim.y * 4,
        BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT, 0);
    if (result != BS_RESULT_OK) goto fail;

    bs_transition(queue, rasterization->image, 0, BS_IMAGE_LAYOUT_UNDEFINED, BS_IMAGE_LAYOUT_GENERAL);
    bs_transition(queue, rasterization->scaled_image, 0, BS_IMAGE_LAYOUT_UNDEFINED, BS_IMAGE_LAYOUT_GENERAL);

    bs_output(rasterization->renderer, (bs_Output) {
        .subpass = 0,
        .image = rasterization->image,
        .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
        .new_layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        .flags = 0
    });

    bs_output(rasterization->renderer, (bs_Output) {
        .subpass = 0,
        .image = rasterization->depth_image,
        .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
        .new_layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        .flags = 0
    });

    rasterization->renderer->dim = rasterization->image->dim;

    return BS_RESULT_OK;
fail:
    _bsmod_destroyRasterizer(rasterization);
    return result;
}

BSMODAPI void _bsmod_endRasterize(bs_Queue* queue) {
    bs_Queue* single_times_queue = bs_fetch(BSMOD_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;
    //bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION)->queue;

    bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
    bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

    bsgfx_tickInstances();
    bs_pushDescriptors();

    for (int i = 0; i < _bsmod_rasterizations.count; i++) {
        bsmod_Rasterization* rasterization = bs_fetchUnit(&_bsmod_rasterizations, i);

        bs_RendererScope scope = bs_beginRender(queue, rasterization->renderer);

        struct bsgfx_InstanceSubtypeMetadata* subtype_metadata = metadata->instance_subtypes + rasterization->subtype;
        int index_offset = subtype_metadata->index_offset;
        int index_count = subtype_metadata->index_count;

        bs_Batch* batch = bs_fetch(subtype_metadata->batch_source_id, subtype_metadata->batch_id)->batch;

        bs_Pipeline* pipeline;
        if (bs_pipeline(&scope, queue, &rasterization->pipeline_hash, &pipeline) != BS_RESULT_OK)
            continue;

        bs_clearDepth(queue, 0, rasterization->depth_image->dim, 1.0);
        bs_pushConstant(queue, pipeline, 0, rasterization->push_constant_size, rasterization->push_constant);
        bs_render(queue, batch, pipeline, index_offset, index_count, rasterization->instance_id, 1);

        bs_endRender(queue, rasterization->renderer);
        
        bs_blit(queue, (bs_BlitOperation) {
            .source = rasterization->image, 
            .source_layout = BS_IMAGE_LAYOUT_GENERAL, 
            .source_scale = rasterization->image->dim, 
            .destination = rasterization->scaled_image, 
            .destination_layout = BS_IMAGE_LAYOUT_GENERAL, 
            .destination_scale = rasterization->scaled_image->dim,
        });

        bs_copyImageToBufferAsync(
            queue,
            rasterization->scaled_image,
            rasterization->buffer,
            0,
            BS_IMAGE_LAYOUT_GENERAL,
            0,
            BS_IV2(0, 0),
            rasterization->scaled_image->dim
        );
    }
}

static struct {
    const char* package;
    const char* name;
} _bsmod_queued_rasterization = { 0 };

BSMODAPI void _bsmod_queueRasterize(const char* package, const char* name, bs_Callback callback) {
    if (!bs_exists(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION))
        return;

    bs_Queue* post_queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION)->queue;
    bs_enqueue(post_queue, callback);

   // bs_except(BSX_DEVICE_LOST);
   // //bs_stall(post_queue);
   // if (bs_caught())
   //     bsgfx_onDeviceLost();

    _bsmod_queued_rasterization.package = package;
    _bsmod_queued_rasterization.name = name;
}

BSMODAPI void _bsmod_pollRasterizer() {
    if (!bs_exists(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION))
        return;

    bs_Queue* post_queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION)->queue;

    if (bs_poll(post_queue) != BS_RESULT_WAITING) { // idk if it should check BS_RESULT_OK or not
        bsmod_AtlasPacker packer = _bsmod_createAtlasPacker();

        for (int i = 0; i < _bsmod_rasterizations.count; i++) {
            bsmod_Rasterization* rasterization = bs_fetchUnit(&_bsmod_rasterizations, i);

            if (bs_mapBuffer(rasterization->buffer, BS_U32_MAX) == BS_RESULT_OK) {
                unsigned char* map = bs_bufferMap(rasterization->buffer);
                _bsmod_packAtlasTexture(
                    &packer,
                    map,
                    NULL,
                    NULL,
                    rasterization->scaled_image->dim.x,
                    rasterization->scaled_image->dim.y,
                    rasterization->category,
                    rasterization->name
                );
                bs_savePngF(map, BS_IV2(rasterization->scaled_image->dim.x, rasterization->scaled_image->dim.y), BS_PNG_RGBA, "test%d.png", i);
            }
        }

        _bsmod_packAtlas(&packer, 2048, 2048, 4, _bsmod_queued_rasterization.package, _bsmod_queued_rasterization.name, false);
        _bsmod_destroyAtlasPacker(&packer);
    }
}