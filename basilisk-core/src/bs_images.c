
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

// STD
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <windows.h>
#include <winreg.h>
#include <assert.h>

#include <basilisk-core.h>
#include <bs_internal.h>
#include <vulkan.h>

#include <lodepng/lodepng.h>

BSAPI bool _bs_isStencilFormat(bs_Format format) {
    return
        format == BS_FORMAT_D32_SFLOAT_S8_UINT ||
        format == BS_FORMAT_D24_UNORM_S8_UINT ||
        format == BS_FORMAT_D16_UNORM_S8_UINT;
}

BSAPI bool _bs_isDepthFormat(bs_Format format) {
    return _bs_isStencilFormat(format) ||
        format == BS_FORMAT_D16_UNORM || format == BS_FORMAT_D32_SFLOAT;
}

BSAPI bool _bs_hasAlpha(bs_Format format) {
    return
        format == BS_FORMAT_R8G8B8A8_UNORM ||
        format == BS_FORMAT_R8G8B8A8_SNORM ||
        format == BS_FORMAT_R8G8B8A8_USCALED ||
        format == BS_FORMAT_R8G8B8A8_SSCALED ||
        format == BS_FORMAT_R8G8B8A8_UINT ||
        format == BS_FORMAT_R8G8B8A8_SINT ||
        format == BS_FORMAT_R8G8B8A8_SRGB ||
        format == BS_FORMAT_B8G8R8A8_UNORM ||
        format == BS_FORMAT_B8G8R8A8_SNORM ||
        format == BS_FORMAT_B8G8R8A8_USCALED ||
        format == BS_FORMAT_B8G8R8A8_SSCALED ||
        format == BS_FORMAT_B8G8R8A8_UINT ||
        format == BS_FORMAT_B8G8R8A8_SINT ||
        format == BS_FORMAT_B8G8R8A8_SRGB;
}

BSAPI int _bs_imageSwapsCount(bs_Image* image) {
    return image->flags & BS_IMAGE_SWAPS_BIT ? _bs_context_->frames_in_flight : 1;
}

BSAPI void _val_bs_transition(bs_Image* image, int index, bs_ImageLayout old_layout, bs_ImageLayout new_layout) {
    BS_VALIDATE(old_layout != new_layout,,);
    BS_VALIDATE(index == 0 || index < image->num_indices,,);
    _bs_transition(image, index, old_layout, new_layout);
}

BSAPI void _bs_transition(bs_Image* image, int index, bs_ImageLayout old_layout, bs_ImageLayout new_layout) {
    VkResult result;
    VkCommandBuffer commands = bsi_fetchCommands();

    VkPipelineStageFlags src_stage;
    VkPipelineStageFlags dst_stage;

    VkImageMemoryBarrier barrier = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .oldLayout = (VkImageLayout)old_layout,
        .newLayout = (VkImageLayout)new_layout,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image->_->vk_image,
        .subresourceRange = {
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = index,
            .layerCount = 1,
        }
    };

    if (_bs_isDepthFormat(image->format)) {
        barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_DEPTH_BIT;

        if (_bs_isStencilFormat(image->format))
            barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
    }
    else {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }

    if (old_layout == BS_IMAGE_LAYOUT_UNDEFINED && new_layout == BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_UNDEFINED && new_layout == BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_UNDEFINED && new_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        src_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dst_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_UNDEFINED && new_layout == BS_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        dst_stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_GENERAL && new_layout == BS_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_GENERAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_UNDEFINED && new_layout == BS_IMAGE_LAYOUT_GENERAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (old_layout == BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && new_layout == BS_IMAGE_LAYOUT_GENERAL) {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        src_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else {
        _bs_warnF("Unknown layout transition %s -> %s", bs_serializeImageLayout(old_layout), bs_serializeImageLayout(new_layout));
    }

    vkCmdPipelineBarrier(
        commands,
        src_stage, dst_stage,
        0,
        0, NULL,
        0, NULL,
        1, &barrier);

    if (_bs_scope_.queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(_bs_scope_.queue);
        result = vkQueueWaitIdle(_bs_scope_.queue->queue);
    }
}

static inline bs_Result _bs_queryMemoryType(bs_U32 filter, VkMemoryPropertyFlags props, bs_U32* out) {
    VkPhysicalDeviceMemoryProperties mem_props;
    vkGetPhysicalDeviceMemoryProperties(_bs_context_->physical_device->vk_device, &mem_props);

    for (bs_U32 i = 0; i < mem_props.memoryTypeCount; i++) {
        if ((filter & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props) {
            *out = i;
            return BS_RESULT_OK;
        }
    }

    return BS_RESULT_FAILED_TO_QUERY;
}

 /** TODO: this doesn't use swaps atm */
static bs_Result _bs_prepareImage(bs_U32 source_id, bs_U32 id, bs_Image* image, VkImageUsageFlags usage_flags, VkImageAspectFlags aspect_flags) {
    VkResult vk_result;
    bs_Result result;

    image->aspect_flags = aspect_flags;
    image->usage_flags = usage_flags;

   /**
    Create Vulkan image
    */
    VkImageCreateInfo image_ci = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .extent = {
            .width = image->dim.x,
            .height = image->dim.y,
            .depth = 1,
        },
        .mipLevels = 1,
        .arrayLayers = image->num_indices == 0 ? 1 : image->num_indices,
        .format = (VkFormat)image->format,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = usage_flags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .samples = VK_SAMPLE_COUNT_1_BIT,
    };

    vk_result = vkCreateImage(_bs_instance_->device, &image_ci, NULL, &image->_->vk_image);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateImage", vk_result, "(%d, %d)", source_id, id);
        return _bs_convertVulkanResult(vk_result);
    }

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(
        _bs_instance_->device, 
        image->_->vk_image,
        &mem_req);
    
    bs_U32 memory_type = 0;
    result = _bs_queryMemoryType(mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &memory_type);
    if (result != BS_RESULT_OK) {
        _bs_warnF("Failed to query memory type for image (%d, %d)", source_id, id);
        return result;
    }

    VkMemoryAllocateInfo alloc_i = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = mem_req.size,
        .memoryTypeIndex = memory_type,
    };

    vk_result = vkAllocateMemory(_bs_instance_->device, &alloc_i, NULL, &image->_->vk_memory);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkAllocateMemory", result, "(%d, %d)", source_id, id);
        return _bs_convertVulkanResult(vk_result);
    }

    vk_result = vkBindImageMemory(_bs_instance_->device, image->_->vk_image, image->_->vk_memory, 0);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkBindImageMemory", result, "(%d, %d)", source_id, id);
        return _bs_convertVulkanResult(vk_result);
    }

   /**
    Create Vulkan image view
    */
    VkImageViewType view_type;
    // todo 1d, 3d
    if (image->num_indices > 0)
        view_type = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    else
        view_type = VK_IMAGE_VIEW_TYPE_2D;

    VkImageViewCreateInfo image_view_ci = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = image->_->vk_image,
        .viewType = view_type,
        .format = (VkFormat)image->format,
        .subresourceRange.aspectMask = image->aspect_flags,
        .subresourceRange.levelCount = 1,
        .subresourceRange.layerCount = image->num_indices == 0 ? 1 : image->num_indices,
    };

    vk_result = vkCreateImageView(_bs_instance_->device, &image_view_ci, NULL, &image->_->vk_image_view);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateImageView", result, "(%d, %d)", source_id, id);
        return _bs_convertVulkanResult(vk_result);
    }

    return BS_RESULT_OK;
}

static bs_Result _bs_depthImage(bs_Object* object, bs_ivec2 dim, int num_indices, bs_Format format, bs_U32 flags) {
    bs_Image* image = object->image;

    bs_U32 num_swaps = flags & BS_IMAGE_SWAPS_BIT ? _bs_context_->frames_in_flight : 1;

    _bs_prepareImage(image->head.source_id, image->head.id, image,
        (flags & BS_IMAGE_ATTACHMENT_BIT       ? VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT : 0) |
        (flags & BS_IMAGE_INPUT_ATTACHMENT_BIT ? VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT         : 0) |
        (flags & BS_IMAGE_USAGE_TRANSFER_DST_BIT ? VK_IMAGE_USAGE_TRANSFER_DST_BIT : 0) |
        (flags & BS_IMAGE_USAGE_TRANSFER_SRC_BIT ? VK_IMAGE_USAGE_TRANSFER_SRC_BIT : 0) |
        VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_IMAGE_ASPECT_DEPTH_BIT);

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_image(bs_Object* object, bs_ivec2 dim, int num_indices, bs_Format format, bs_U32 flags) {
    if (!object)
        return BS_RESULT_INVALID_PARAM;

    if (!object->image)
        return BS_RESULT_OK;

    bs_Image* image = object->image;

    if (!image) 
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY)) 
        return BS_RESULT_OK;

    _bs_destroyImage(image);

    image->dim = dim;
    image->flags = flags;
    image->format = format;
    image->num_indices = num_indices;

    if (num_indices > 0)
        image->indices = _bs_calloc(num_indices, sizeof(bs_ImageIndex));

    if (_bs_isDepthFormat(format)) 
        return _bs_depthImage(object, dim, num_indices, format, flags);

    int num_swaps = flags & BS_IMAGE_SWAPS_BIT ? _bs_context_->frames_in_flight : 1;
    _bs_prepareImage(image->head.source_id, image->head.id, image,
        (flags & BS_IMAGE_ATTACHMENT_BIT            ? VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT : 0) |
        (flags & BS_IMAGE_INPUT_ATTACHMENT_BIT      ? VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT : 0) |
        (flags & BS_IMAGE_USAGE_TRANSFER_DST_BIT    ? VK_IMAGE_USAGE_TRANSFER_DST_BIT : 0) | 
        (flags & BS_IMAGE_USAGE_TRANSFER_SRC_BIT    ? VK_IMAGE_USAGE_TRANSFER_SRC_BIT : 0) |
        (flags & BS_IMAGE_USAGE_STORAGE_BIT         ? VK_IMAGE_USAGE_STORAGE_BIT : 0) |
        VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_IMAGE_ASPECT_COLOR_BIT);

    return BS_RESULT_OK;
}



  /*==============================================================================
   * PNG
   *============================================================================*/

BSAPI bs_Result _bs_encodePng(size_t* out_size, const unsigned char* data, bs_ivec2 size, bs_PngType type, unsigned char** out) {
    int result = 0;

    switch (type) {
    case BS_PNG_RGB: result = lodepng_encode24(out, out_size, data, size.x, size.y); break;
    case BS_PNG_RGBA: result = lodepng_encode32(out, out_size, data, size.x, size.y); break;
    };

    if (result != 0) {
        char* error = lodepng_error_text(result);
        _bs_warn(error);
        return BS_RESULT_FAILED_TO_ENCODE;
    }

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_savePngN(char* data, bs_ivec2 dim, bs_PngType type, char* path, int path_length) {
    int error = 0;

    switch (type) {
    case BS_PNG_GREY: error = lodepng_encode_file(path, data, dim.x, dim.y, LCT_GREY, 8); break;
    case BS_PNG_RGB: error = lodepng_encode_file(path, data, dim.x, dim.y, LCT_RGB, 8); break;
    case BS_PNG_GREY_ALPHA: error = lodepng_encode_file(path, data, dim.x, dim.y, LCT_GREY_ALPHA, 8); break;
    case BS_PNG_RGBA: error = lodepng_encode_file(path, data, dim.x, dim.y, LCT_RGBA, 8); break;
    default:
        _bs_warnF("Unsupported bs_PngType %d for png \"%s\"", type, path);
    };

    if (error != 0) {
        _bs_warnF("Failed to save png \"%s\", lodepng error:\n%s", path, lodepng_error_text(error));
        return BS_RESULT_FAILED_TO_WRITE;
    }

    _bs_infoF("Saved a PNG of size %d x %d to %s", dim.x, dim.y, path);

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_peekPngN(bs_PngData* out_png_data, char* path, int path_length) {
    unsigned error;
    unsigned char* data = NULL;

    LodePNGState state;
    lodepng_state_init(&state);

    error = lodepng_load_file(&data, out_png_data->size, path);
    if (error) {
        _bs_warnF("Failed to read png file \"%s\", lodepng error:\n%s", path, lodepng_error_text(error));
        return BS_RESULT_FAILED_TO_READ;
    }

    error = lodepng_inspect(out_png_data->width, out_png_data->height, &state, data, out_png_data->size);
    if (error) {
        _bs_warnF("Failed to inspect png \"%s\", lodepng error:\n%s", path, lodepng_error_text(error));
        free(data);
        return BS_RESULT_FAILED_TO_INSPECT;
    }

    free(data);
    return BS_RESULT_OK;
}

 /**
  Load PNG Data
  */
BSAPI bs_Result _val_bs_loadPngData(char* data, size_t size, int channels_count, bs_PngData* out) {
    BS_VALIDATE(channels_count == 3 || channels_count == 4, BS_RESULT_VALIDATION_ERROR,);
    return _bs_loadPngData(data, size, channels_count, out);
}

BSAPI bs_Result _bs_loadPngData(char* data, size_t size, int channels_count, bs_PngData* out) {
    int error = 0;
    switch (channels_count) {
    case 3: error = lodepng_decode24(&out->data, &out->width, &out->height, data, size); break;
    case 4: error = lodepng_decode32(&out->data, &out->width, &out->height, data, size); break;
    default: 
        _bs_warnF("Failed to load png data, unsupported channels_count %d", channels_count);
        return BS_RESULT_INVALID_PARAM;
    }

    if (error) {
        _bs_warnF("Failed to load png data, lodepng error:\n%s", lodepng_error_text(error));
        free(data);
        return BS_RESULT_FAILED_TO_INSPECT;
    }

    out->size = out->width * out->height * out->channels_count;

    return BS_RESULT_OK;
}

 /**
  Load PNG
  */
BSAPI bs_Result _bs_loadPng(const char* path, int channels_count, bs_PngData* out) {
    unsigned char* image_data = NULL;
    int error = 0;

    switch (channels_count) {
    case 3: error = lodepng_decode24_file(&out->data, &out->width, &out->height, path); break;
    case 4: error = lodepng_decode32_file(&out->data, &out->width, &out->height, path); break;
    default: 
        _bs_warnF("Failed to load png file \"%s\", unsupported channels_count %d", path, channels_count);
        return BS_RESULT_INVALID_PARAM;
    }

    if (error) {
        _bs_warnF("Failed to load png file \"%s\", lodepng error:\n%s", path, lodepng_error_text(error));
        return BS_RESULT_FAILED_TO_READ;
    }

    out->size = out->width * out->height * out->channels_count;

    return BS_RESULT_OK;
}



  /*==============================================================================
   * Image Creation
   *============================================================================*/


BSAPI void _bs_destroyImage(bs_Image* image) {
    bs_U32 num_swaps = image->flags & BS_IMAGE_SWAPS_BIT ? _bs_context_->frames_in_flight : 1;
    for (int i = 0; i < num_swaps; i++) {
        vkDestroyImageView(_bs_instance_->device, image->_[i].vk_image_view, NULL);
        vkDestroyImage(_bs_instance_->device, image->_[i].vk_image, NULL);
        vkFreeMemory(_bs_instance_->device, image->_[i].vk_memory, NULL);
        image->_[i].vk_image_view = image->_[i].vk_image = image->_[i].vk_memory = 0;
    }

    _bs_resetObject(&image->head, sizeof(bs_Image));
}

BSAPI bs_Result _bs_resizeImage(bs_Image* image, bs_ivec2 dim, int num_indices) {
    _bs_destroyImage(image);

    image->dim = dim;
    image->num_indices = num_indices;
    return _bs_prepareImage(image->head.source_id, image->head.id, image, image->usage_flags, image->aspect_flags);
}

BSAPI bs_Result _bs_queryImageIndexHash(bs_Image* image, bs_U64 name_hash, int* out) {
    for (int i = 0; i < image->num_indices; i++) {
        bs_ImageIndex* index = image->indices + i;
        if (index->name_hash == name_hash) {
            *out = i;
            return BS_RESULT_OK;
        }
    }

    return BS_RESULT_FAILED_TO_QUERY;
}

BSAPI bs_Result _bs_queryImageIndex(bs_Image* image, char* name, int* out) {
    return _bs_queryImageIndexHash(image, _bs_stringHash(name), out);
}



  /*==============================================================================
   * Sampler
   *============================================================================*/

BSAPI int _bs_samplerSwapsCount(bs_Sampler* sampler) {
    return sampler->flags & BS_SAMPLER_SWAPS_BIT ? _bs_context_->frames_in_flight : 1;
}

BSAPI void _bs_destroySampler(bs_Sampler* sampler) {
    vkDestroySampler(_bs_instance_->device, sampler->_->vk_sampler, NULL);

    _bs_resetObject(&sampler->head, sizeof(bs_Sampler));
}

BSAPI bs_Result _val_bs_sampler(bs_Object* object, bs_ImageFilter filter, bs_SamplerBits flags) {
  //  BS_VALIDATE_OBJECT_TYPE(object, BS_OBJECT_SAMPLER, BS_RESULT_VALIDATION_ERROR);
    return _bs_sampler(object, filter, flags);
}

BSAPI bs_Result _bs_sampler(bs_Object* object, bs_ImageFilter filter, bs_SamplerBits flags) {
    VkResult result;
    bs_Sampler* sampler = object->sampler;

    if (!sampler) 
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY)) 
        return BS_RESULT_OK;

    _bs_destroySampler(sampler);

    sampler->filter = filter;
    sampler->flags = flags;

    VkPhysicalDeviceProperties properties = { 0 };
    vkGetPhysicalDeviceProperties(_bs_context_->physical_device->vk_device, &properties);

    VkSamplerCreateInfo sampler_i = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = (VkFilter)filter,
        .minFilter = (VkFilter)filter,
        .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        //.anisotropyEnable = VK_TRUE,
        .maxAnisotropy = sampler_i.anisotropyEnable ? properties.limits.maxSamplerAnisotropy : 1.0,
        .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        .unnormalizedCoordinates = VK_FALSE,
        .compareEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_ALWAYS,
        .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
        .mipLodBias = 0.0f,
        .minLod = 0.0f,
        .maxLod = 0.0f,
    };

    result = vkCreateSampler(_bs_instance_->device, &sampler_i, NULL, &sampler->_->vk_sampler);
    if (result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateSampler", result, "(%d, %d)", sampler->head.source_id, sampler->head.id);
        return _bs_convertVulkanResult(result);
    }

    return BS_RESULT_OK;
}

BSAPI void _val_bs_copyImageToBufferAsync(bs_Image* image, bs_Buffer* buffer, int image_index, bs_ImageLayout layout, bs_U64 buffer_offset, bs_ivec2 offset, bs_ivec2 dim) {
    int channels_count = _bs_hasAlpha(image->format) ? 4 : 3;
    BS_VALIDATE((dim.x * dim.y * channels_count) <= (buffer->num_bytes - buffer_offset),,);

    _bs_copyImageToBufferAsync(image, buffer, image_index, layout, buffer_offset, offset, dim);
}

BSAPI void _bs_copyImageToBufferAsync(bs_Image* image, bs_Buffer* buffer, int image_index, bs_ImageLayout layout, bs_U64 buffer_offset, bs_ivec2 offset, bs_ivec2 dim) {
    VkCommandBuffer commands = bsi_fetchCommands();
    int image_swap = (image->flags & BS_IMAGE_SWAPS_BIT) ? _bs_context_->frame : 0;
    int buffer_swap = (buffer->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_context_->frame : 0;

    VkBufferImageCopy copy = {
        .bufferOffset = buffer_offset,
        .imageOffset = {
            .x = offset.x,
            .y = image->dim.y - offset.y - dim.y,
        },
        .imageExtent = {
            .width = dim.x,
            .height = dim.y,
            .depth = 1,
        },
        .imageSubresource = {
            .aspectMask = _bs_isDepthFormat(image->format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT,
            .layerCount = 1,
            .baseArrayLayer = image_index,
        },
    };

//    if (copy.imageOffset.y < 0 || (copy.imageExtent.height + copy.imageOffset.y) > image->dim.y ||
//        copy.imageOffset.x < 0 || (copy.imageExtent.width + copy.imageOffset.x) > image->dim.x) 
//    {
//        _bs_throwBasilisk(BSXI_INTERNAL | BSX_OUT_OF_BOUNDS);
//        return;
//    }

    vkCmdCopyImageToBuffer(commands, image->_[image_swap].vk_image, layout, buffer->_[buffer_swap].vk_buffer, 1, &copy);
}

BSAPI void _bs_copyBufferToImage(bs_Buffer* buffer, bs_Image* image, int index, bs_ImageLayout layout) {
    VkCommandBuffer commands = bsi_fetchCommands();

    VkBufferImageCopy region = {
        .imageSubresource = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .mipLevel = 0,
            .baseArrayLayer = index,
            .layerCount = 1,
        },
        .imageExtent.depth = 1,
        .imageExtent.width = image->dim.x,
        .imageExtent.height = image->dim.y,
    };

    vkCmdCopyBufferToImage(
        commands,
        buffer->flags & BSI_BUFFER_SWAPS_BIT ? buffer->_[_bs_context_->frame].vk_buffer : buffer->_->vk_buffer,
        image->flags & BS_IMAGE_SWAPS_BIT ? image->_[_bs_context_->frame].vk_image : image->_->vk_image,
        layout,
        1,
        &region);

    if (_bs_scope_.queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(_bs_scope_.queue);
        vkQueueWaitIdle(_bs_scope_.queue->queue);
    }
}

static VkImageAspectFlags _bs_imageAspectFlags(bs_Image* image) {
    if (_bs_isDepthFormat(image->format)) {
        if (_bs_isStencilFormat(image->format))
            return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

        return VK_IMAGE_ASPECT_DEPTH_BIT;
    }

    return VK_IMAGE_ASPECT_COLOR_BIT;
}

BSAPI void _bs_blit(bs_BlitOperation operation)  {
    VkCommandBuffer commands = bsi_fetchCommands();

    VkImageBlit region = {
        .srcSubresource = {
            .aspectMask = _bs_imageAspectFlags(operation.source),
            .mipLevel = 0,
            .baseArrayLayer = 0,
            .layerCount = 1,
        },
        .srcOffsets[0] = { 0, 0, 0 },
        .srcOffsets[1] = { operation.source_scale.x, operation.source_scale.y, 1 },

        .dstSubresource = {
            .aspectMask = _bs_imageAspectFlags(operation.destination),
            .mipLevel = 0,
            .baseArrayLayer = 0,
            .layerCount = 1,
        },
        .dstOffsets[0] = { 0, 0, 0 },
        .dstOffsets[1] = { operation.destination_scale.x, operation.destination_scale.y, 1 },
    };

    vkCmdBlitImage(
        commands,
        operation.source->flags & BS_IMAGE_SWAPS_BIT ? operation.source->_[_bs_context_->frame].vk_image : operation.source->_->vk_image,
        operation.source_layout,
        operation.destination->flags & BS_IMAGE_SWAPS_BIT ? operation.destination->_[_bs_context_->frame].vk_image : operation.destination->_->vk_image,
        operation.destination_layout,
        1, &region,
        VK_FILTER_NEAREST
    );
}



  /*==============================================================================
   * Image File Format
   *============================================================================*/

static inline bs_Format _bs_getFormat(bs_Format base_format, int channels_count) {
    switch (base_format) {
    case BS_FORMAT_R8_SRGB: 
        switch (channels_count) {
        case 1: return BS_FORMAT_R8_SRGB;
        case 2: return BS_FORMAT_R8G8_SRGB;
        case 3: return BS_FORMAT_R8G8B8_SRGB;
        case 4: return BS_FORMAT_R8G8B8A8_SRGB;
        }
        break;
    case BS_FORMAT_R8_UNORM:
        switch (channels_count) {
        case 1: return BS_FORMAT_R8_SRGB;
        case 2: return BS_FORMAT_R8G8_SRGB;
        case 3: return BS_FORMAT_R8G8B8_SRGB;
        case 4: return BS_FORMAT_R8G8B8A8_SRGB;
        }
        break;
    }

    _bs_warnF("Failed to get image format, base format %d has no support for %d channels", bs_serializeFormat(base_format), channels_count);
}

BSAPI bs_Result _val_bs_loadImage(bs_Object* object, int package_id, bs_ImageBits flags, char* resource_name, char* resource_name_length) {
   // BS_VALIDATE_OBJECT_TYPE(object, BS_OBJECT_IMAGE, BS_RESULT_OK);

    return _bs_loadImageN(object, package_id, flags, resource_name, resource_name_length);
}

BSAPI bs_Result _bs_loadImageN(bs_Object* object, int package_id, bs_ImageBits flags, char* path, int path_length) {
    bs_Result result;

    if (!object->image)
        return BS_RESULT_OK;

    bs_Resource* resource;
    result = _bs_loadResourceN(package_id, 0, BS_RESOURCE_IMAGE, &resource, path, path_length);
    if (result != BS_RESULT_OK)
        return result;

    bs_BiffHeader* header = resource->data->value;
    if (header->magic != BS_BIFF_MAGIC) {
        _bs_destroyResource(resource);
        return BS_RESULT_CORRUPTED;
    }

    if (header->version != 1) {
        _bs_destroyResource(resource);
        return BS_RESULT_NOT_SUPPORTED;
    }

    if (header->channels_count != 4) {
        _bs_destroyResource(resource);
        return BS_RESULT_NOT_IMPLEMENTED;
    }

    bs_Format format = _bs_getFormat(BS_FORMAT_R8_UNORM, header->channels_count);
    result = _bs_image(object, (bs_ivec2) { header->width, header->height }, header->images_count, format, flags);
    if (result != BS_RESULT_OK) {
       // _bs_destroyResource(resource); // TODO: try uncomment
        return result;
    }

    unsigned char* data = resource->data->value + sizeof(bs_BiffHeader);

    bs_Buffer* buffer = BS_BUFFER(-1, 0, 0)->buffer;
    result = _bs_buffer(buffer, header->width * header->height * header->channels_count,
        BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result != BS_RESULT_OK) {
        // TODO: try uncomment
        // _bs_destroyResource(resource);
        // _bs_destroyImage(object->image);
        return result;
    }

    result = _bs_mapBuffer(buffer, BS_U32_MAX);
    if (result != BS_RESULT_OK) {
        // TODO: try uncomment
        // _bs_destroyResource(resource);
        // _bs_destroyImage(object->image);
        return result;
    }

    for (int i = 0; i < header->images_count; i++) {
        bs_BiffPointer* pointer = data;
        data += sizeof(bs_BiffPointer);
        char* name = data;
        int name_length = strlen(name);
        data += sizeof("\n");

        unsigned char* bmp = resource->data->value + pointer->offset;

        object->image->indices[i].name = strdup(name);
        object->image->indices[i].name_hash = _bs_stringHash(name);

        _bs_stageImage(buffer, header->channels_count, object->image->dim, bmp);
        _bs_transition(object->image, i, BS_IMAGE_LAYOUT_UNDEFINED, BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        _bs_copyBufferToImage(buffer, object->image, i, BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        _bs_transition(object->image, i, BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        data += pointer->name_length;
    }

   //_bs_destroyBuffer(buffer);

    resource->image = object->image;

    return BS_RESULT_OK;
}



  /*==============================================================================
   * Atlas File Format
   *============================================================================*/

static bs_vec4 _bs_calculateAtlasCoordinates(bs_Atlas* atlas, int texture_id, int frame) {
    bs_AtlasTexture* mapped = atlas->mapped + texture_id;

    float width = (float)mapped->w / (float)atlas->image->dim.x;
    width /= (float)mapped->split;

    return BS_V4(
        (float)mapped->x / (float)atlas->image->dim.x + width * (float)(frame % mapped->split),
        (float)mapped->y / (float)atlas->image->dim.y,
        width,
        (float)mapped->h / (float)atlas->image->dim.y);
}

 /**
  Atlas coordinates
  */
BSAPI bs_vec4 _val_bs_atlasCoordinates(bs_Atlas* atlas, int texture_id) {
    BS_VALIDATE(texture_id >= 0, (bs_vec4) { 0 },);
    BS_VALIDATE(texture_id < atlas->count, (bs_vec4) { 0 },);

    return _bs_atlasCoordinates(atlas, texture_id);
}

BSAPI bs_vec4 _bs_atlasCoordinates(bs_Atlas* atlas, int texture_id) {
    bs_AtlasTexture* mapped = atlas->mapped + texture_id;
    return mapped->coords;
}

 /**
  Mirror UV coordinates (horizontal)
  */
BSAPI bs_vec4 _bs_mirrorUV(bs_vec4 uv) {
    return BS_V4(uv.x + uv.z, uv.y, -uv.z, uv.w);
}

 /**
  Flip UV coordinates (vertical)
  */
BSAPI bs_vec4 _bs_flipUV(bs_vec4 uv) {
#define EPSILON 0.00001f // scuffed
    return BS_V4(uv.x, uv.y + uv.w + EPSILON, uv.z, -uv.w);
}

 /**
  Atlas size
  */
BSAPI bs_vec2 _val_bs_atlasSize(bs_Atlas* atlas, int texture) {
    BS_VALIDATE(texture >= 0, (bs_vec2) { 0 },);
    BS_VALIDATE(texture < atlas->count, (bs_vec2) { 0 },);
    BS_VALIDATE(atlas->buffer != NULL, (bs_vec2) { 0 }, );
    BS_VALIDATE(_bs_bufferIsMapped(atlas->buffer), (bs_vec2) { 0 }, );
    BS_VALIDATE(atlas->mapped != NULL, (bs_vec2) { 0 }, );

    return _bs_atlasSize(atlas, texture);
}

BSAPI bs_vec2 _bs_atlasSize(bs_Atlas* atlas, int texture) {
    return BS_V2(atlas->mapped[texture].w / atlas->mapped[texture].split, atlas->mapped[texture].h);
}

BSAPI int _bs_queryAtlasHash(bs_Atlas* atlas, bs_U64 hash) {
    for (int i = 0; i < atlas->count; i++) {
        if (atlas->unmapped[i].name_hash == hash) {
            return i;
        }
    }

    return -1;
}

BSAPI int _bs_queryAtlas(bs_Atlas* atlas, const char* name) {
    return _bs_queryAtlasHash(atlas, _bs_stringHash(name));
}

BSAPI void _bs_destroyAtlas(bs_Atlas* atlas) {
    if (atlas->image)
        _bs_destroyImage(atlas->image);

    _bs_resetObject(&atlas->head, sizeof(bs_Atlas));

    //if (atlas->buffer)
    //	_bs_destroyBuffer(atlas->buffer);
}

BSAPI bs_Result _val_bs_loadAtlasMemory(bs_Object* object, int package_id, char* resource_name, char* data, bs_U32 flags) {
 //   BS_VALIDATE_OBJECT_TYPE(object, BS_OBJECT_ATLAS, BS_RESULT_VALIDATION_ERROR);

    return _bs_loadAtlasMemory(object, package_id, resource_name, data, flags);
}

BSAPI bs_Result _bs_loadAtlasMemory(bs_Object* object, int package_id, char* resource_name, char* data, bs_U32 flags) {
    bs_Result result;

    if (!object->atlas) 
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY)) 
        return BS_RESULT_OK;

    bs_Atlas* atlas = object->atlas;

    bs_Image* old_image = atlas->image;
    bs_Buffer* old_buffer = atlas->buffer;
    unsigned char* old_mapped = atlas->mapped;

    _bs_destroyAtlas(object->atlas);

    bs_BatlHeader* header = data;
    if (header->magic != BS_BATL_MAGIC) {
        _bs_warnF("Atlas resource \"%s\" is corrupted, invalid magic number", resource_name);
        return BS_RESULT_CORRUPTED;
    }

    if (header->version != 1) {
        _bs_warnF("Atlas resource \"%s\" has an unsupported version (%d)", resource_name, header->version);
        return BS_RESULT_NOT_SUPPORTED;
    }

    if (header->channels_count != 4 && header->channels_count != 1) {
        _bs_warnF("Atlas resource \"%s\" has an unsupported amount of channels (%d)", resource_name, header->channels_count);
        return BS_RESULT_NOT_SUPPORTED;
    }


   /**
    Create image
    */
    bs_Object* image_object = BS_IMAGE(-1, 0, flags & BS_ATLAS_FORCE_CREATE);
    bs_U32 swaps_count = flags & BS_IMAGE_SWAPS_BIT ? _bs_context_->frames_in_flight : 1;
    atlas->image = image_object->image;
    atlas->image->num_indices = header->pages_count;
    atlas->image->flags = flags;
    atlas->image->format = _bs_getFormat(BS_FORMAT_R8_UNORM, header->channels_count);
    atlas->image->dim = BS_IV2(header->width, header->height);

    result = _bs_prepareImage(atlas->image->head.source_id, atlas->image->head.id, atlas->image,
        (flags & BS_IMAGE_ATTACHMENT_BIT ? VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT : 0) |
        (flags & BS_IMAGE_INPUT_ATTACHMENT_BIT ? VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT : 0) |
        VK_IMAGE_USAGE_TRANSFER_DST_BIT |
        VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_IMAGE_ASPECT_COLOR_BIT);

    if (result != BS_RESULT_OK) {
        _bs_destroyAtlas(object->atlas);
        return result;
    }

    //atlas->name = strdup(resource_name);
    atlas->count = header->images_count;
    atlas->unmapped = _bs_malloc(atlas->count * sizeof(*atlas->unmapped));

    if (!old_buffer) {
        bs_Object* buffer_object = BS_BUFFER(-1, 0, 0);
        atlas->buffer = buffer_object->buffer;
        result = _bs_buffer(buffer_object, atlas->count * sizeof(*atlas->mapped),
            BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
            BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            0);
        if (result != BS_RESULT_OK) {
            return result;
        }

        //atlas->mapped = _bs_malloc(atlas->count * sizeof(*atlas->mapped));
        //memset(atlas->mapped, 0, atlas->count * sizeof(*atlas->mapped));
        result = _bs_mapBuffer(atlas->buffer, atlas->count * sizeof(*atlas->mapped));
        atlas->mapped =_bs_bufferMap(atlas->buffer);
        if (result != BS_RESULT_OK) {
            _bs_warnF("Failed to map buffer for atlas \"%s\"", resource_name);
            return result;
        }
    }
    else {
        atlas->mapped = old_mapped;
        atlas->buffer = old_buffer;
    }

    unsigned char* offset = data + sizeof(bs_BatlHeader);
    for (int i = 0; i < atlas->count; i++) {
        bs_BatlImage* pointer = offset;
        offset += sizeof(bs_BatlImage);
        char* name = offset;
        offset += pointer->name_length + sizeof("\n");

        atlas->unmapped[i].name = strdup(name);
        atlas->unmapped[i].name_hash = _bs_stringHash(name);
        atlas->unmapped[i].category = pointer->category;
        atlas->mapped[i].x = pointer->x,
        atlas->mapped[i].y = atlas->image->dim.y - pointer->y - pointer->h;
        atlas->mapped[i].w = pointer->w,
        atlas->mapped[i].h = pointer->h,
        atlas->mapped[i].split = 1;
        atlas->mapped[i].coords = _bs_calculateAtlasCoordinates(atlas, i, 0);
        atlas->mapped[i].flags = pointer->flags;
    }

    bs_U32 size = header->width * header->height * header->channels_count;

    bs_Object* staging_buffer_object = BS_BUFFER(-1, 0, 0);
    result = _bs_buffer(staging_buffer_object, size,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyAtlas(object->atlas);
        return result;
    }

    result = _bs_mapBuffer(staging_buffer_object->buffer, size);
    if (result != BS_RESULT_OK) {
        _bs_destroyAtlas(object->atlas);
        return result;
    }

    const size_t page_size = header->width * header->height * header->channels_count;
 
    for (int i = 0; i < header->pages_count; i++) {
        _bs_stageImage(staging_buffer_object->buffer, header->channels_count, BS_IV2(header->width, header->height), offset);

        _bs_transition(atlas->image, i, BS_IMAGE_LAYOUT_UNDEFINED, BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        _bs_copyBufferToImage(staging_buffer_object->buffer, atlas->image, i, BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        _bs_transition(atlas->image, i, BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        offset += page_size;
    }
    _bs_unmapBuffer(staging_buffer_object->buffer);

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_loadAtlasN(bs_Object* object, int package_id, bs_U32 flags, char* path, int path_length) {
    bs_Result result;

    bs_Resource* resource;
    result = _bs_loadResourceN(package_id, 0, BS_RESOURCE_ATLAS, &resource, path, path_length);
    if (result != BS_RESULT_OK)
        return result;

    result = _bs_loadAtlasMemory(object, package_id, path, resource->data->value, flags);
    if (result != BS_RESULT_OK)
        return result;

    resource->atlas = object->atlas;
    return result;
}
