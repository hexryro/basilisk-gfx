
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

#include "basilisk-core.gen.h"
#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_WAYLAND_KHR
#endif

#include <vulkan.h>
#include <vulkan/vulkan_core.h>

#include <basilisk-core.h>
#include <bs_internal.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <threads.h>

bs_Args _bs_args_ = { 0 };
bs_Features _bs_features_ = { 0 };
bs_Props _bs_props_ = { 0 };
bs_Procs _bs_procs_ = { 0 };
bs_Config _bs_config_ = {
    .attributes.unit_size = sizeof(bs_AttributeType),
};

_Thread_local bs_Scope _bs_scope_ = { 0 };

bs_Instance* _bs_instance_ = NULL;
bs_Callbacks _bs_callbacks_ = { 0 };

bs_List _bs_physical_devices_ = { .unit_size = sizeof(bs_PhysicalDevice) };

BSAPI bs_Instance* _bs_instance() { return _bs_instance_; }
BSAPI bs_Args* _bs_args() { return &_bs_args_; }
BSAPI bs_Features* _bs_features() { return &_bs_features_; }
BSAPI bs_Props* _bs_props() { return &_bs_props_; }
BSAPI bs_Config* _bs_config() { return &_bs_config_; }
BSAPI bs_Callbacks* _bs_callbacks() { return &_bs_callbacks_; }
BSAPI bs_Scope* _bs_scope() { return &_bs_scope_; }

BSAPI void _bsi_nameHandleN(bs_U64 handle, bs_U32 type, char* name, int name_length) {
    PFN_vkSetDebugUtilsObjectNameEXT pfn_vkSetDebugUtilsObjectNameEXT =
        (PFN_vkSetDebugUtilsObjectNameEXT)vkGetDeviceProcAddr(_bs_instance_->device, "vkSetDebugUtilsObjectNameEXT");

    const VkDebugUtilsObjectNameInfoEXT name_i = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
        .pNext = NULL,
        .objectType = type,
        .objectHandle = handle,
        .pObjectName = name,
    };

    pfn_vkSetDebugUtilsObjectNameEXT(_bs_instance_->device, &name_i);
}

BSAPI struct VkCommandBuffer_T* _bsi_fetchCommands(bs_Queue* queue) {
    if (queue->flags & BS_QUEUE_SINGLE_TIMES_BIT)
        _bs_resetQueue(queue);

    int swap = _bs_queueSwap(queue);
    return queue->_[swap].command_buffer;
}

BSAPI struct VkDevice_T* _bsi_fetchDevice() {
    return _bs_instance_->device;
}

 /**
  Begin Comment
  */
BSAPI void _val_bs_beginComment(bs_Queue* queue, char* message, int message_len) {
    BS_VALIDATE(_bs_procs_.vkCmdBeginDebugUtilsLabelEXT != NULL, , );
    _bs_beginCommentN(queue, message, message_len);
}

BSAPI void _bs_beginCommentN(bs_Queue* queue, char* message, int message_len) {
    VkDebugUtilsLabelEXT label = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pLabelName = message,
        .color = { 0.3f, 0.3f, 0.9f, 1.0f }, // todo param
    };

    VkCommandBuffer commands = _bsi_fetchCommands(queue);
//    _bs_procs.vkCmdInsertDebugUtilsLabelEXT(commands, &label);
    _bs_procs_.vkCmdBeginDebugUtilsLabelEXT(commands, &label);
}

 /**
  End Comment
  */
BSAPI void _val_bs_endComment(bs_Queue* queue) {
    BS_VALIDATE(_bs_procs_.vkCmdEndDebugUtilsLabelEXT != NULL, , );
    _bs_endComment(queue);
}

BSAPI void _bs_endComment(bs_Queue* queue) {
    VkCommandBuffer commands = _bsi_fetchCommands(queue);
    _bs_procs_.vkCmdEndDebugUtilsLabelEXT(commands);
}

BSAPI void _bs_parseArgs(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--use-validation-layers") == 0) _bs_args_.use_validation_layers = true;
    }
}

BSAPI void _bs_configureQueuesCount(bs_U32 count) {
    _bs_config_.queues_count = count;
}



  /*==============================================================================
   * Instance
   *============================================================================*/

const char* validation_layers[] = {
    "VK_LAYER_KHRONOS_validation"
};

static VKAPI_ATTR VkBool32 VKAPI_CALL _bs_debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* data,
    void* param)
{
    static bs_String* message;

    if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        message = _bs_stringF(message, "Message name: %s\n", data->pMessageIdName ? data->pMessageIdName : "N/A\n");
        message = _bs_appendStringF(message, "Message: %s\n", data->pMessage);

        if (data->objectCount > 0) {
            for (uint32_t i = 0; i < data->objectCount; i++) {
                const VkDebugUtilsObjectNameInfoEXT* obj = &data->pObjects[i];
                message = _bs_appendStringF(message, "Object %d:\n", i);
                message = _bs_appendStringF(message, "  Handle: 0x%llx\n", (unsigned long long)obj->objectHandle);
                message = _bs_appendStringF(message, "  Type:   %s\n", bs_serializeVkObjectType((bs_VkObjectType)obj->objectType));
                if (obj->pObjectName)
                    message = _bs_appendStringF(message, "  Name:   %s\n", obj->pObjectName);
            }
        }

        _bs_warnN(message->value, message->len);
    }
    else {
        _bs_warnF("%s", data->pMessage);
    }

    // _bs_free(message);

    return VK_FALSE;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL _bs_reportCallback(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT type,
    uint64_t object,
    size_t location,
    int32_t code,
    const char* prefix,
    const char* message,
    void* param) {

 //   _bs_infoF("%s\n", message);
    return VK_FALSE;
}

static bool _bs_checkValidationLayerSupport() {
    bs_U32 num_layers;
    vkEnumerateInstanceLayerProperties(&num_layers, NULL);

    VkLayerProperties* layers = _bs_malloc(num_layers * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&num_layers, layers);

    bool found_all = true;
    int num_validation_layers = sizeof(validation_layers) / sizeof(const char *);
    for(int i = 0; i < num_validation_layers; i++) {
        bool found = false;

        for(int j = 0; j < num_layers; j++) {
            if (strcmp(validation_layers[i], layers[j].layerName) == 0) {
                found = true;
                break;
            }
	    }

        if (!found) {
            _bs_warnF("Vulkan validation layer %s is not supported", validation_layers[i]);
            found_all = false;
        }
    }

    _bs_free(layers);
    return found_all;
}

static inline bool _bs_addInstanceExtension(const char** extensions, bs_U32* extensions_count, const char* name, VkExtensionProperties* available_extensions, bs_U32 available_extensions_count) {
    for (bs_U32 i = 0; i < available_extensions_count; i++) {
        if (strcmp(name, available_extensions[i].extensionName) == 0) {
            extensions[(*extensions_count)++] = available_extensions[i].extensionName;
            return true;
        }
    }

    return false;
}

static void _bs_prepareInstance() {
    VkResult result;

    if (_bs_args_.use_validation_layers)
        _bs_args_.use_validation_layers = _bs_checkValidationLayerSupport();

    const char* extensions[16];
    bs_U32 extensions_count = 0;

    bs_U32 available_extensions_count = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &available_extensions_count, NULL);
    VkExtensionProperties* available_extensions = malloc(available_extensions_count * sizeof(VkExtensionProperties));
    vkEnumerateInstanceExtensionProperties(NULL, &available_extensions_count, available_extensions);

#define BS_ADD_INSTANCE_EXTENSION(name) \
    _bs_addInstanceExtension(extensions, &extensions_count, name, available_extensions, available_extensions_count)

#ifdef _WIN32
    if (BS_ADD_INSTANCE_EXTENSION(VK_KHR_WIN32_SURFACE_EXTENSION_NAME))
         _bs_instance_->extensions.surface_type = BS_SURFACE_TYPE_WIN32;
#elif __linux__
    if (BS_ADD_INSTANCE_EXTENSION(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME))
        _bs_instance_->extensions.surface_type = BS_SURFACE_TYPE_WAYLAND;
    //else if (BS_ADD_INSTANCE_EXTENSION(VK_KHR_XLIB_SURFACE_EXTENSION_NAME))
//        _bs_instance_->extensions.surface_type = BS_SURFACE_TYPE_X11;
#endif
    else if (BS_ADD_INSTANCE_EXTENSION(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME)) {
        _bs_warnF("Only off-screen rendering is available");
        _bs_instance_->extensions.surface_type = BS_SURFACE_TYPE_HEADLESS;
    }
    else {
        _bs_warnF("No instance surface extension found");
    }
    BS_ADD_INSTANCE_EXTENSION(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    BS_ADD_INSTANCE_EXTENSION(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    BS_ADD_INSTANCE_EXTENSION(VK_KHR_SURFACE_EXTENSION_NAME);
    BS_ADD_INSTANCE_EXTENSION(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);

    VkApplicationInfo app_i = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "",
        .applicationVersion = VK_MAKE_API_VERSION(0, 1, 4, 0),
        .pEngineName = "BASILISK",
        .engineVersion = VK_MAKE_API_VERSION(0, 1, 4, 0),
        .apiVersion = VK_API_VERSION_1_4,
    };

    const VkValidationFeatureEnableEXT enabled_features[] = {
        VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
     //   VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
       // VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
    };

    VkValidationFeaturesEXT features = {
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
        .pEnabledValidationFeatures = enabled_features,
        .enabledValidationFeatureCount = sizeof(enabled_features) / sizeof(VkValidationFeatureEnableEXT),
        .pNext = NULL,
    };

    VkInstanceCreateInfo ci = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_i,
        .enabledExtensionCount = extensions_count,
        .ppEnabledExtensionNames = extensions,
        .ppEnabledLayerNames = validation_layers,
        .enabledLayerCount = _bs_args_.use_validation_layers ? sizeof(validation_layers) / sizeof(const char*) : 0,
     //  .pNext = &features,
    };

    result = vkCreateInstance(&ci, NULL, &_bs_instance_->instance);
    if (result != VK_SUCCESS) {
        _bs_criticalF("Failed to create instance (Vulkan result %d)", result);
        return;
    }

    free(available_extensions);

    VkDebugUtilsMessengerEXT messenger = { 0 };
    const VkDebugUtilsMessengerCreateInfoEXT debug_ci = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = _bs_debugCallback,
    };

    PFN_vkCreateDebugUtilsMessengerEXT create_messenger =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_bs_instance_->instance, "vkCreateDebugUtilsMessengerEXT");

    PFN_vkCreateDebugReportCallbackEXT create_reporter =
        (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(_bs_instance_->instance, "vkCreateDebugReportCallbackEXT");

    if (create_messenger)
        create_messenger(_bs_instance_->instance, &debug_ci, NULL, &messenger);

    VkDebugReportCallbackCreateInfoEXT report_ci = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
        .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT,
        .pfnCallback = _bs_reportCallback,
    };

    VkDebugReportCallbackEXT reporter = { 0 };
    if (create_reporter)
        create_reporter(_bs_instance_->instance, &report_ci, NULL, &reporter);
}

void _bs_findExecutablePaths();
void _bs_iniLogger();
BSAPI void _bs_ini() {
    _bs_instance_ = _bs_calloc(1, sizeof(bs_Instance));
    _bs_instance_->log = _bs_stringN(_bs_instance_->log, "", 0);
    _bs_instance_->fixed_time = 0.025;

    _bs_iniLogger();

    _bs_configureAttribute("bs_Position", BS_FORMAT_R32_SFLOAT);
    _bs_configureAttribute("bs_Texture", BS_FORMAT_R32_SFLOAT);
    _bs_configureAttribute("bs_Color", BS_FORMAT_R8_UNORM);
    _bs_configureAttribute("bs_Normal", BS_FORMAT_R32_SFLOAT);
    _bs_configureAttribute("bs_Bone", BS_FORMAT_R32_SINT);
    _bs_configureAttribute("bs_Weight", BS_FORMAT_R32_SFLOAT);

    _bs_findExecutablePaths();
    _bs_prepareInstance();
}



  /*==============================================================================
   * Rendering logic
   *============================================================================*/

static inline bs_U32 _bs_queryMemoryType(bs_U32 filter, VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties mem_props;
    vkGetPhysicalDeviceMemoryProperties(_bs_instance_->physical_device->vk_device, &mem_props);

    for (bs_U32 i = 0; i < mem_props.memoryTypeCount; i++) {
        if ((filter & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props) {
            return i;
        }
    }

    return 0;
}

static void _bs_clearAttachment(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, VkImageAspectFlags aspect_flags, VkClearValue value) {
    VkCommandBuffer commands = _bsi_fetchCommands(queue);

    VkClearAttachment clear_attachment = {
        .aspectMask = aspect_flags,
        .clearValue = value,
        .colorAttachment = index,
    };

    VkClearRect rectangle = {
        .layerCount = 1,
        .rect = {
            .extent = {
                .width = dim.x,
                .height = dim.y,
            },
        },
    };

    vkCmdClearAttachments(commands, 1, &clear_attachment, 1, &rectangle);
}

BSAPI void _bs_clearStencil(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, bs_U32 value) {
    _bs_clearAttachment(queue, index, dim, VK_IMAGE_ASPECT_STENCIL_BIT, (VkClearValue) {.depthStencil.stencil = value });
}

BSAPI void _bs_clearDepth(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, float value) {
    _bs_clearAttachment(queue, index, dim, VK_IMAGE_ASPECT_DEPTH_BIT, (VkClearValue) { .depthStencil.depth = value });
}

BSAPI void _bs_clearDepthStencil(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, float depth_value, bs_U32 stencil_value) {
    _bs_clearAttachment(queue, index, dim, VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT, (VkClearValue) {
        .depthStencil = {
            .depth = depth_value,
            .stencil = stencil_value,
        }
    });
}

BSAPI void _bs_clearColor(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, const bs_vec4* color) {
    // TODO: union needs to match the attachment format
    _bs_clearAttachment(queue, index, dim, VK_IMAGE_ASPECT_COLOR_BIT, (VkClearValue) {
        .color.float32 = {
            [0] = color->x, [1] = color->y, [2] = color->z, [3] = color->w,
        }
    });
}

BSAPI void _bs_stencilReference(bs_Queue* queue, bs_StencilFaceFlag face, bs_U32 reference) {
    VkCommandBuffer commands = _bsi_fetchCommands(queue);
    vkCmdSetStencilReference(commands, (VkStencilFaceFlags)face, reference);
}

BSAPI void _bs_cull(bs_Queue* queue, bs_CullFlags flags) {
    VkCommandBuffer commands = _bsi_fetchCommands(queue);
    vkCmdSetCullMode(commands, flags);
}

BSAPI void _bs_setLineWidth(bs_Queue* queue, float width) {
    VkCommandBuffer commands = _bsi_fetchCommands(queue);
    vkCmdSetLineWidth(commands, width);
}



  /*==============================================================================
   * Buffer
   *============================================================================*/

BSAPI bool _bs_bufferIsMapped(bs_Buffer* buffer) {
    return buffer->_->data;
}

static void _bs_nameBuffer(bs_Object* object, const char* name) {
    int name_length = strlen(name);
    object->buffer->flags |= BS_BUFFER_IS_NAMED;
    for (int i = 0; i < object->buffer->head.swaps_count; i++)
        bsi_nameHandleN((bs_U64)object->buffer->_[i].vk_buffer, VK_OBJECT_TYPE_BUFFER, name, name_length);
}

 /**
  Create buffer view
  */
BSAPI bs_Result _bs_bufferView(bs_Buffer* buffer, bs_Format format, bs_U64 start, bs_U64 count) {
    VkResult result;

    VkBufferViewCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
        .format = (VkFormat)format,
        .offset = start,
        .range = count,
    };

    for (int i = 0; i < buffer->head.swaps_count; i++) {
        info.buffer = buffer->_[i].vk_buffer;

        VkBufferView view;
        result = vkCreateBufferView(_bs_instance_->device, &info, NULL, &view);

        if (result != VK_SUCCESS) {
            BS_WARN_VULKAN_ERROR("vkCreateBufferView", result, "");
            return bs_convertVulkanResult(result);
        }

        buffer->_[i].vk_buffer_view = view;
    }

    return BS_RESULT_OK;
}

 /**
  Create Buffer
  */
BSAPI bs_Result _bs_buffer(bs_Object* object, size_t num_bytes, bs_BufferUsageFlags usage_flags, bs_MemoryPropertyFlags memory_flags, bs_BufferBits flags) {
    VkResult result;

    if (!object->buffer)
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY))
        return BS_RESULT_OK;

    bs_Buffer* buffer = object->buffer;
    _bs_destroyBuffer(buffer);

    if (object->flags & BS_OBJECT_HAS_SWAPS_BIT)
        flags |= BSI_BUFFER_SWAPS_BIT;

    buffer->memory_flags = memory_flags;
    buffer->usage_flags = usage_flags;
    buffer->flags = flags;
    buffer->num_bytes = num_bytes;

    if (usage_flags & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT && num_bytes > 65536) {
        _bs_warnF("Buffer %d of size %d exceeds maximum UBO size of 65536 bytes", buffer->head.id, num_bytes);
        return BS_RESULT_GENERAL_ERROR;
    }

    VkBufferCreateInfo buffer_i = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = num_bytes,
        .usage = usage_flags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VkMemoryAllocateFlagsInfo alloc_flags_info = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
    };

    if (buffer_i.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT) {
        alloc_flags_info.flags |= VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;
    }

    for (int i = 0; i < buffer->head.swaps_count; i++) {
        result = vkCreateBuffer(
            _bs_instance_->device,
            &buffer_i,
            NULL,
            &buffer->_[i].vk_buffer);

        if (result != VK_SUCCESS)
            return _bs_convertVulkanResult(result);
    }

    VkMemoryRequirements mem_req;
    vkGetBufferMemoryRequirements(
        _bs_instance_->device,
        buffer->_->vk_buffer,
        &mem_req);

    VkMemoryAllocateInfo alloc_i = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = mem_req.size,
        .memoryTypeIndex = _bs_queryMemoryType(mem_req.memoryTypeBits, memory_flags),
        .pNext = &alloc_flags_info
    };

    for (int i = 0; i < buffer->head.swaps_count; i++) {
        result = vkAllocateMemory(
            _bs_instance_->device,
            &alloc_i,
            NULL,
            &buffer->_[i].memory);

        if (result != VK_SUCCESS)
            return _bs_convertVulkanResult(result);

        result = vkBindBufferMemory(
            _bs_instance_->device,
            buffer->_[i].vk_buffer,
            buffer->_[i].memory,
            0);

        if (result != VK_SUCCESS)
            return _bs_convertVulkanResult(result);
    }

    if (flags & BS_BUFFER_PRE_MAP)
        _bs_mapBuffer(object->buffer, BS_U32_MAX);

    const char* name = _bs_idName(object->head->source_id, object->head->id);
    _bs_nameBuffer(object, name);

    return BS_RESULT_OK;
}

BSAPI bs_Result _val_bs_buffer(bs_Object* object, size_t num_bytes, bs_BufferUsageFlags usage_flags, bs_MemoryPropertyFlags memory_flags, bs_BufferBits flags) {
    BS_VALIDATE(num_bytes > 0, BS_RESULT_VALIDATION_ERROR, );
  //  BS_VALIDATE_OBJECT_TYPE(object, BS_OBJECT_BUFFER, BS_RESULT_VALIDATION_ERROR);

    return _bs_buffer(object, num_bytes, usage_flags, memory_flags, flags);
}

 /**
  Buffer Map
  */
BSAPI void* _val_bs_bufferMap(bs_Buffer* buffer) {
    BS_VALIDATE(_bs_bufferIsMapped(buffer) == true, NULL,);

    return _bs_bufferMap(buffer);
}

BSAPI void* _bs_bufferMap(bs_Buffer* buffer) {
    int swap = (buffer->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;
    return buffer->_[swap].data;
}

BSAPI bs_Result _bs_mapBuffer(bs_Buffer* buffer, bs_U32 num_bytes) {
    if (buffer->_->data)
        return BS_RESULT_OK;

    if (num_bytes == BS_U32_MAX)
        num_bytes = buffer->num_bytes;
    else if (num_bytes > buffer->num_bytes)
        return BS_RESULT_OUT_OF_BOUNDS;

    for (int i = 0; i < buffer->head.swaps_count; i++) {
        VkResult result = vkMapMemory(_bs_instance_->device, buffer->_[i].memory, 0, buffer->num_bytes, 0, (void**)&buffer->_[i].data);
        if (result != VK_SUCCESS) {
            return _bs_convertVulkanResult(result);
        }
    }

    return BS_RESULT_OK;
}

BSAPI void _bs_unmapBuffer(bs_Buffer* buffer) {
    if (!_bs_bufferIsMapped(buffer))
        return;

    for (int i = 0; i < buffer->head.swaps_count; i++) {
        vkUnmapMemory(_bs_instance_->device, buffer->_[i].memory);
        buffer->_[i].data = NULL;
    }
}

BSAPI void _bs_stageNull(bs_Buffer* buffer) {
    memset(_bs_bufferMap(buffer), 0, buffer->num_bytes);
}

 /**
  Stage list
  */
BSAPI void _val_bs_stageList(bs_Buffer* buffer, bs_List* list) {
    BS_VALIDATE(_bs_bufferIsMapped(buffer),,);
    BS_VALIDATE((list->count * list->unit_size) < buffer->num_bytes,,);

    _bs_stageList(buffer, list);
}

BSAPI void _bs_stageList(bs_Buffer* buffer, bs_List* list) {
    bs_U32 size = list->count * list->unit_size;
    memcpy(_bs_bufferMap(buffer), list->data, size);
}

 /**
  Stage image data
  */
BSAPI void _bs_stageImage(bs_Buffer* buffer, int channels_count, bs_ivec2 dim, const char* data) {
    bs_U32 size = dim.x * dim.y * channels_count;

    memcpy(_bs_bufferMap(buffer), data, size);
}

BSAPI void _bs_destroyBuffer(bs_Buffer* buffer) {
    _bs_unmapBuffer(buffer);

    for (int i = 0; i < buffer->head.swaps_count; i++) {
        if (buffer->_[i].vk_buffer)
            vkDestroyBuffer(_bs_instance_->device, buffer->_[i].vk_buffer, NULL);
        if (buffer->_[i].memory)
            vkFreeMemory(_bs_instance_->device, buffer->_[i].memory, NULL);
        buffer->_[i].vk_buffer = VK_NULL_HANDLE;
        buffer->_[i].memory = VK_NULL_HANDLE;
    }

    if (buffer->flags & BSI_BUFFER_IS_BOUND) {
      //  _bs_bindBuffer(buffer->bind_set, buffer->binding, NULL);
     //   _bs_pushDescriptors();
    }

    _bs_resetObject(&buffer->head, sizeof(bs_Buffer));
}

 /**
  Buffer to buffer copy
  */
BSAPI void _val_bs_copyAsync(bs_Queue* queue, bs_Buffer* src, bs_Buffer* dst, bs_U32 dst_offset, bs_U32 src_offset, bs_U32 num_bytes) {
    int src_swap = (src->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;
    int dst_swap = (dst->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;

    BS_VALIDATE(src->_[src_swap].vk_buffer != NULL,,);
    BS_VALIDATE(dst->_[dst_swap].vk_buffer != NULL,,);

    if (num_bytes == BS_U32_MAX)
        num_bytes = BS_MIN(dst->num_bytes, src->num_bytes);

    BS_VALIDATE(num_bytes > 0,,);
    BS_VALIDATE(num_bytes < src->num_bytes, , );

    _bs_copyAsync(queue, src, dst, dst_offset, src_offset, num_bytes);
}

BSAPI void _bs_copyAsync(bs_Queue* queue, bs_Buffer* src, bs_Buffer* dst, bs_U32 dst_offset, bs_U32 src_offset, bs_U32 num_bytes) {
    if (num_bytes == BS_U32_MAX)
        num_bytes = BS_MIN(dst->num_bytes, src->num_bytes);

    VkBufferCopy copy_region = {
        .srcOffset = src_offset,
        .dstOffset = dst_offset,
        .size = num_bytes
    };

    int src_swap = (src->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;
    int dst_swap = (dst->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;

    VkCommandBuffer commands = _bsi_fetchCommands(queue);
    vkCmdCopyBuffer(commands, src->_[src_swap].vk_buffer, dst->_[dst_swap].vk_buffer, 1, &copy_region);

    if (queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(queue, 0, NULL);
        _bs_stallQueue(queue);
    }
}

 /**
  Buffer memset
  */
BSAPI void _bs_setBufferAsync(bs_Queue* queue, bs_Buffer* buffer, bs_U32 offset, bs_U32 num_bytes, bs_U32 value) {
    VkCommandBuffer commands = _bsi_fetchCommands(queue);
    int swap = buffer->flags & BSI_BUFFER_SWAPS_BIT ? _bs_scope_.context->frame : 0;
    vkCmdFillBuffer(commands, buffer->_[swap].vk_buffer, offset, num_bytes, value);
    if (queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(queue, 0, NULL);
        vkQueueWaitIdle(queue->queue);
    }
}

static VkDeviceAddress _bs_bufferAddress(VkBuffer buffer) {
    VkBufferDeviceAddressInfo info = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
        .buffer = buffer,
    };

    VkDeviceAddress address = vkGetBufferDeviceAddress(_bs_instance_->device, &info);

    assert(address);
    assert((address & 0xFF) == 0);
    return address;
}



  /*==============================================================================
   * Batch Population
   *============================================================================*/

BSAPI void _bs_populateVertexDeclaration(bs_VertexDeclaration* declaration, bs_Attribute* attributes, int attributes_count) {
    for (int i = 0, offset = 0; i < declaration->attributes_count; i++) {
        declaration->attributes[i].source_offset = offset;
        offset += declaration->attributes[i].source_size;
    }

    for (int i = 0; i < declaration->attributes_count;) {
        bs_U64 hash = _bs_stringHash(declaration->attributes[i].attribute_name);
        bs_Attribute* attribute = NULL;

        for (int j = 0; j < attributes_count; j++) {
            bs_Attribute* a = attributes + j;
            if (a->name_hash == hash) {
                attribute = a;
                break;
            }
        }

        if (!attribute)
            declaration->attributes[i] = declaration->attributes[--declaration->attributes_count];
        else
            declaration->attributes[i++].destination_offset = attribute->offset;
    }

    //declaration->populated = true;
}

BSAPI void _bs_batchVertex(void* decl, const void* source) {
    bs_VertexDeclaration* declaration = decl;
    unsigned char* src = source;
    unsigned char* dst = declaration->batch->vertices.data + *declaration->offset * declaration->batch->vertices.unit_size;

    for (int i = 0; i < declaration->attributes_count; i++) {
        memcpy(
            dst + declaration->attributes[i].destination_offset,
            src + declaration->attributes[i].source_offset,
            declaration->attributes[i].source_size);
    }

    (*declaration->offset)++;
}

BSAPI bs_Range _bs_batchRange(bs_Batch* batch, bs_U32 offset) {
    return (bs_Range) {
        .offset = offset,
        .num = batch->indices.count - offset,
    };
}

BSAPI void _bs_ensureBatchSize(bs_Batch* batch, bs_U32 num_indices, bs_U32 num_vertices) {
    _bs_ensureSize(&batch->vertices, num_vertices);
    if (num_indices != 0)
        _bs_ensureSize(&batch->indices, num_indices);
}

BSAPI void _bs_pushIndex(bs_Batch* batch, int index) {
    bs_List* indices = &batch->indices;

    index += batch->vertices.count;
    memcpy(indices->data + indices->count * indices->unit_size, &index, indices->unit_size);

    indices->count++;
}

BSAPI void _bs_pushIndices(bs_Batch* batch, int indices[], int indices_count) {
    for (int i = 0; i < indices_count; i++) {
        int value = indices[i];
        _bs_pushIndex(batch, value);
    }
}

// vertex
/*
static inline void _bs_batchVertex(bs_Batch* batch, bs_U32* offset, const bs_Vertex* vertex) {
    bs_U32 num_bytes = 0;
    bs_U8* src = vertex;
    float* dst = batch->vertices.data + *offset * batch->vertices.unit_size;

    for (int i = 0; i < batch->attributes_count; i++) {
        bs_Attribute* attribute = batch->attributes + i;

        memcpy(dst + num_bytes / 4, src + attribute->offset, attribute->size);
        num_bytes += attribute->size;
    }

    (*offset)++;
}
*/

// cube
BSAPI void _bs_batchCube(bs_Batch* batch, bs_U32* offset, bs_RGBA color) {
    //if (smooth_shade) {
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(-1.0, -1.0, 1.0), .color = color, .normal = BS_V3(-1.0, -1.0, 1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(1.0, -1.0, 1.0), .color = color, .normal = BS_V3(1.0, -1.0, 1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(-1.0, 1.0, 1.0), .color = color, .normal = BS_V3(-1.0, 1.0, 1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(1.0, 1.0, 1.0), .color = color, .normal = BS_V3(1.0, 1.0, 1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(-1.0, -1.0, -1.0), .color = color, .normal = BS_V3(-1.0, -1.0, -1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(1.0, -1.0, -1.0), .color = color, .normal = BS_V3(1.0, -1.0, -1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(-1.0, 1.0, -1.0), .color = color, .normal = BS_V3(-1.0, 1.0, -1.0) });
    //    _bs_batchVertex(batch, offset, &(bs_Vertex) { .position.xyz = BS_V3(1.0, 1.0, -1.0), .color = color, .normal = BS_V3(1.0, 1.0, -1.0) });
    //
    //}
    //else {

    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec3, bs_Normal,
        bs_vec2, bs_Texture,
        bs_RGBA, bs_Color
    );

    // top
    _bs_batchVertex(&declaration, &(bs_Vertex){.bs_Position = { -1,  1, -1 }, .bs_Color = color, .bs_Normal = { 0, 1, 0 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex){.bs_Position = { -1,  1,  1 }, .bs_Color = color, .bs_Normal = { 0, 1, 0 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex){.bs_Position = { 1,  1, -1 }, .bs_Color = color, .bs_Normal = { 0, 1, 0 }, .bs_Texture = { 1, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex){.bs_Position = { -1,  1,  1 }, .bs_Color = color, .bs_Normal = { 0, 1, 0 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex){.bs_Position = { 1,  1,  1 }, .bs_Color = color, .bs_Normal = { 0, 1, 0 }, .bs_Texture = { 1, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex){.bs_Position = { 1,  1, -1 }, .bs_Color = color, .bs_Normal = { 0, 1, 0 }, .bs_Texture = { 1, 1 } });
    // bottom
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1,  1 }, .bs_Color = color, .bs_Normal = { 0, -1, 0 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1, -1 }, .bs_Color = color, .bs_Normal = { 0, -1, 0 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1, -1 }, .bs_Color = color, .bs_Normal = { 0, -1, 0 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1,  1 }, .bs_Color = color, .bs_Normal = { 0, -1, 0 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1,  1 }, .bs_Color = color, .bs_Normal = { 0, -1, 0 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1, -1 }, .bs_Color = color, .bs_Normal = { 0, -1, 0 }, .bs_Texture = { 1, 0 } });
    // left
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1,  1 }, .bs_Color = color, .bs_Normal = { -1, 0, 0 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1,  1,  1 }, .bs_Color = color, .bs_Normal = { -1, 0, 0 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1,  1, -1 }, .bs_Color = color, .bs_Normal = { -1, 0, 0 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1, -1 }, .bs_Color = color, .bs_Normal = { -1, 0, 0 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1,  1 }, .bs_Color = color, .bs_Normal = { -1, 0, 0 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1,  1, -1 }, .bs_Color = color, .bs_Normal = { -1, 0, 0 }, .bs_Texture = { 0, 1 } });
    // right
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1,  1 }, .bs_Color = color, .bs_Normal = { 1, 0, 0 }, .bs_Texture = { 1, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1,  1 }, .bs_Color = color, .bs_Normal = { 1, 0, 0 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1, -1 }, .bs_Color = color, .bs_Normal = { 1, 0, 0 }, .bs_Texture = { 1, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1,  1 }, .bs_Color = color, .bs_Normal = { 1, 0, 0 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1, -1 }, .bs_Color = color, .bs_Normal = { 1, 0, 0 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1, -1 }, .bs_Color = color, .bs_Normal = { 1, 0, 0 }, .bs_Texture = { 1, 1 } });
    // front
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1,  1,  1 }, .bs_Color = color, .bs_Normal = { 0, 0, 1 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1,  1 }, .bs_Color = color, .bs_Normal = { 0, 0, 1 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1,  1 }, .bs_Color = color, .bs_Normal = { 0, 0, 1 }, .bs_Texture = { 1, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1,  1 }, .bs_Color = color, .bs_Normal = { 0, 0, 1 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1,  1 }, .bs_Color = color, .bs_Normal = { 0, 0, 1 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1,  1 }, .bs_Color = color, .bs_Normal = { 0, 0, 1 }, .bs_Texture = { 1, 1 } });
    // back
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1, -1 }, .bs_Color = color, .bs_Normal = { 0, 0, -1 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1,  1, -1 }, .bs_Color = color, .bs_Normal = { 0, 0, -1 }, .bs_Texture = { 0, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1, -1 }, .bs_Color = color, .bs_Normal = { 0, 0, -1 }, .bs_Texture = { 1, 1 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1, -1, -1 }, .bs_Color = color, .bs_Normal = { 0, 0, -1 }, .bs_Texture = { 1, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { -1, -1, -1 }, .bs_Color = color, .bs_Normal = { 0, 0, -1 }, .bs_Texture = { 0, 0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { 1,  1, -1 }, .bs_Color = color, .bs_Normal = { 0, 0, -1 }, .bs_Texture = { 1, 1 } });
}

BSAPI bs_Range _bs_pushCube(bs_Batch* batch, bs_RGBA color) {
    int index_offset = batch->indices.count;
    _bs_ensureBatchSize(batch, BS_NUM_CUBE_INDICES, BS_NUM_CUBE_VERTICES);
    //if (smooth_shade)
    //    _bs_pushIndexV(batch, BS_NUM_CUBE_INDICES,
    //        // top
    //        6, 2, 7,
    //        2, 3, 7,
    //        // bottom
    //        0, 4, 5,
    //        1, 0, 5,
    //        // öeft
    //        0, 2, 6,
    //        4, 0, 6,
    //        // right
    //        3, 1, 7,
    //        1, 5, 7,
    //        // front
    //        2, 0, 3,
    //        0, 1, 3,
    //        // back
    //        4, 6, 7,
    //        5, 4, 7);
    //else

    int indices[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
    };

    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));

    _bs_batchCube(batch, &batch->vertices.count, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI void _bs_batchCone(bs_Batch* batch, bs_U32* offset, int segments, float height, float radius, bs_RGBA color) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) {
        .bs_Position = { 0 },
        .bs_Texture = { 0.5, 0.0 },
    });

    for (int i = 0, n = segments - 1; i < segments; i++) {
        float ratio = (float)i / n;
        float r = ratio * BS_2PI;
        float x = cos(r) * radius;
        float z = sin(r) * radius;

        _bs_batchVertex(&declaration, &(bs_Vertex) {
            .bs_Position = { x, 0.0, z },
            .bs_Texture = { ratio, 0.0 },
        });
    }

    _bs_batchVertex(&declaration, &(bs_Vertex) {
        .bs_Position = { 0.0, height, 0.0 },
        .bs_Texture = { 0.5, 1.0 },
    });
}

BSAPI void _bs_batchPyramid(
    bs_Batch* batch, bs_U32* offset,
    bs_vec3 pos, float width, float height, bs_RGBA color
) {
    float half = width * 0.5f;

    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x - half, pos.y, pos.z - half }, .bs_Texture = { 0.0, 0.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x + half, pos.y, pos.z - half }, .bs_Texture = { 1.0, 0.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x + half, pos.y, pos.z + half }, .bs_Texture = { 1.0, 1.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x - half, pos.y, pos.z + half }, .bs_Texture = { 0.0, 1.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x, pos.y + height, pos.z }, .bs_Texture = { 0.5, 0.5 } });
}

BSAPI void _bs_batchBipyramid(
    bs_Batch* batch, bs_U32* offset,
    bs_vec3 pos, float width, float height, bs_RGBA color
) {
    float half = width * 0.5f;

    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x - half, pos.y, pos.z - half }, .bs_Texture = { 0.0, 0.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x + half, pos.y, pos.z - half }, .bs_Texture = { 1.0, 0.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x + half, pos.y, pos.z + half }, .bs_Texture = { 1.0, 1.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x - half, pos.y, pos.z + half }, .bs_Texture = { 0.0, 1.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x, pos.y + height, pos.z }, .bs_Texture = { 0.5, 0.0 } });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = { pos.x, pos.y - height, pos.z }, .bs_Texture = { 0.5, 1.0 } });
}

BSAPI void _bs_batchQuad(bs_Batch* batch, bs_U32* offset, const bs_Quad* quad, bs_RGBA color) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture,
        bs_RGBA, bs_Color
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) { quad->a, quad->ca, color });
    _bs_batchVertex(&declaration, &(bs_Vertex) { quad->b, quad->cb, color });
    _bs_batchVertex(&declaration, &(bs_Vertex) { quad->c, quad->cc, color });
    _bs_batchVertex(&declaration, &(bs_Vertex) { quad->d, quad->cd, color });
}

BSAPI void _bs_batchTriangle(bs_Batch* batch, bs_U32* offset, bs_vec3 a, bs_vec3 b, bs_vec3 c, bs_RGBA color) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture,
        bs_RGBA, bs_Color
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = a, .bs_Texture = BS_V2(0.0, 0.0), .bs_Color = color });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = b, .bs_Texture = BS_V2(1.0, 0.0), .bs_Color = color });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = c, .bs_Texture = BS_V2(0.0, 1.0), .bs_Color = color });
}

BSAPI void _bs_batchLine(bs_Batch* batch, bs_U32* offset, bs_vec3 a, bs_vec3 b, bs_RGBA color) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture,
        bs_RGBA, bs_Color
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = a, .bs_Texture = BS_V2(0.0, 0.0), .bs_Color = color });
    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = b, .bs_Texture = BS_V2(1.0, 0.0), .bs_Color = color });
}

BSAPI void _bs_batchPoint(bs_Batch* batch, bs_U32* offset, bs_vec3 pos, bs_RGBA color) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture,
        bs_RGBA, bs_Color
    );

    _bs_batchVertex(&declaration, &(bs_Vertex) { .bs_Position = pos, .bs_Color = color });
}

BSAPI void _bs_batchAabb(bs_Batch* batch, bs_U32* offset, bs_Aabb* aabb, bs_RGBA color) {
    // top
    _bs_batchLine(batch, offset, aabb->min, BS_V3(aabb->max.x, aabb->min.y, aabb->min.z), color);
    _bs_batchLine(batch, offset, aabb->min, BS_V3(aabb->min.x, aabb->min.y, aabb->max.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->max.x, aabb->min.y, aabb->max.z), BS_V3(aabb->max.x, aabb->min.y, aabb->min.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->max.x, aabb->min.y, aabb->max.z), BS_V3(aabb->min.x, aabb->min.y, aabb->max.z), color);
    // bottom
    _bs_batchLine(batch, offset, aabb->max, BS_V3(aabb->min.x, aabb->max.y, aabb->max.z), color);
    _bs_batchLine(batch, offset, aabb->max, BS_V3(aabb->max.x, aabb->max.y, aabb->min.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->min.x, aabb->max.y, aabb->min.z), BS_V3(aabb->min.x, aabb->max.y, aabb->max.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->min.x, aabb->max.y, aabb->min.z), BS_V3(aabb->max.x, aabb->max.y, aabb->min.z), color);
    // sides
    _bs_batchLine(batch, offset, aabb->min, BS_V3(aabb->min.x, aabb->max.y, aabb->min.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->min.x, aabb->min.y, aabb->max.z), BS_V3(aabb->min.x, aabb->max.y, aabb->max.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->max.x, aabb->min.y, aabb->min.z), BS_V3(aabb->max.x, aabb->max.y, aabb->min.z), color);
    _bs_batchLine(batch, offset, BS_V3(aabb->max.x, aabb->min.y, aabb->max.z), BS_V3(aabb->max.x, aabb->max.y, aabb->max.z), color);
}

BSAPI void _bs_batchSphere(bs_Batch* batch, bs_U32* offset, bs_vec3 position, float radius, bs_U32 lats, bs_U32 longs, bs_RGBA color) {
    BS_VERTEX_DECLARATION(
        declaration, batch, offset,
        bs_vec3, bs_Position,
        bs_vec3, bs_Normal,
        bs_vec2, bs_Texture,
        bs_RGBA, bs_Color
    );

    float length_inverse = 1.0 / radius;
    float sector_step = 2.0 * BS_PI / lats;
    float stack_step = BS_PI / longs;

    for (int i = 0; i <= longs; i++) {
        float stack_angle = BS_PI / 2.0 - i * stack_step;
        bs_vec3 v;
        float xy = radius * cosf(stack_angle);
        v.z = radius * sinf(stack_angle);

        for (int j = 0; j <= lats; j++) {
            float sector_angle = j * sector_step;
            v.x = xy * cosf(sector_angle);
            v.y = xy * sinf(sector_angle);

            bs_Vertex vertex = {
                .bs_Texture = { (float)j / lats, (float)i / longs },
                .bs_Color = color,
            };

            bs_v3Add(&position, &v, &vertex.bs_Position);
            bs_v3MulS(&v, length_inverse, &vertex.bs_Normal);

            _bs_batchVertex(&declaration, &vertex);
        }
    }
}

BSAPI void _bs_batchPrimitive(
    bs_Batch* batch, bs_U32* offset, bs_Primitive* primitive
) {
    _bs_warnN(BS_CONSTANT_STRING("_bs_batchPrimitive has not been implemented\n"));
}

BSAPI void _bs_batchMesh(bs_Batch* batch, bs_U32* offset, bs_Mesh* mesh) {
    _bs_warnN(BS_CONSTANT_STRING("_bs_batchMesh has not been implemented\n"));
}

BSAPI void _bs_batchModel(bs_Batch* batch, bs_U32* offset, bs_Model* model) {
    _bs_warnN(BS_CONSTANT_STRING("_bs_batchModel has not been implemented\n"));
}



  /*==============================================================================
   * Batch Pushes
   *============================================================================*/

static inline void _bs_quadTextureCoords(bs_Quad* q, bs_vec2 offset, bs_vec2 coords) {
    q->ca = BS_V2(offset.x, offset.y);
    q->cb = BS_V2(coords.x, offset.y);
    q->cc = BS_V2(offset.x, coords.y);
    q->cd = BS_V2(coords.x, coords.y);
}

BSAPI bs_Range _bs_pushQuad(
    bs_Batch* batch, const bs_Quad* quad, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    const int indices[] = { 1, 2, 0, 2, 1, 3 };

    _bs_ensureBatchSize(batch, 6, 4);
    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bs_batchQuad(batch, &batch->vertices.count, quad, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushTriangle(
    bs_Batch* batch, bs_vec3 a, bs_vec3 b, bs_vec3 c, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    const int indices[] = { 0, 1, 2 };

    _bs_ensureBatchSize(batch, 3, 3);
    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bs_batchTriangle(batch, &batch->vertices.count, a, b, c, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushLine(
    bs_Batch* batch, bs_vec3 a, bs_vec3 b, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    const int indices[] = { 2, 0, 1 };

    _bs_ensureBatchSize(batch, 2, 2);
    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bs_batchLine(batch, &batch->vertices.count, a, b, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushPoint(
    bs_Batch* batch, bs_vec3 pos, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    const int indices[] = { 1, 0 };

    _bs_ensureBatchSize(batch, 1, 1);
    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bs_batchPoint(batch, &batch->vertices.count, pos, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushAabb(
    bs_Batch* batch, bs_Aabb* aabb, bs_RGBA color
) {
    int index_offset = batch->indices.count;

    _bs_ensureBatchSize(batch, 24, 24);
    for (bs_U32 i = 0; i < 24; i++)
        _bs_pushIndex(batch, i);
    _bs_batchAabb(batch, &batch->vertices.count, aabb, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushSphere(
    bs_Batch* batch, bs_vec3 position, float radius, bs_U32 lats, bs_U32 longs, bs_RGBA color
) {
    int index_offset = batch->indices.count;

    _bs_ensureBatchSize(batch, lats * longs * 3 * 2, (lats + 1) * (longs + 1));

    for (int i = 0; i < longs; ++i) {
        int k1 = i * (lats + 1);
        int k2 = k1 + lats + 1;

        for (int j = 0; j < lats; ++j, ++k1, ++k2) {
            if (i != 0) {
                const int indices[] = { k1, k2, k1 + 1 };
                _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
            }

            if (i != (longs - 1)) {
                const int indices[] = { k1 + 1, k2, k2 + 1 };
                _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
            }
        }
    }

    _bs_batchSphere(batch, &batch->vertices.count, position, radius, lats, longs, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushPyramid(
    bs_Batch* batch, bs_vec3 pos, float width, float height, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    int num_vertices = 5; // 4 base + 1 apex
    int num_indices = 18; // 6 triangles (2 for base + 4 sides) * 3

    _bs_ensureBatchSize(batch, num_indices, num_vertices);

    const int indices[] = {
        0, 1, 2,
        0, 2, 3,

        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,
    };

    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bs_batchPyramid(batch, &batch->vertices.count, pos, width, height, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushBipyramid(
    bs_Batch* batch, bs_vec3 pos, float width, float height, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    int num_vertices = 6; // 4 base + top + bottom
    int num_indices = 24; // 8 triangles * 3

    _bs_ensureBatchSize(batch, num_indices, num_vertices);

    const int indices[] = {
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,

        1, 0, 5,
        2, 1, 5,
        3, 2, 5,
        0, 3, 5,
    };

    _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    _bs_batchBipyramid(batch, &batch->vertices.count, pos, width, height, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushCone(
    bs_Batch* batch, int segments, float height, float radius, bs_RGBA color
) {
    int index_offset = batch->indices.count;
    int num_indices = (segments * 1) * 3;
    int num_vertices = segments + 2;

    _bs_ensureBatchSize(batch, num_indices, num_vertices);

    for (int i = 0, n = segments - 1; i < n; i++) {
        const int indices[] = { 0, i + 1, i + 2 };
        _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    }

    for (int i = 0, n = segments - 1; i < n; i++) {
        const int indices[] = { i + 1, segments + 1, i + 2 };
        _bs_pushIndices(batch, indices, sizeof(indices) / sizeof(*indices));
    }

    _bs_batchCone(batch, &batch->vertices.count, segments, height, radius, color);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushPrimitive(
    bs_Batch* batch, bs_Primitive* primitive
) {
    bs_U32* increment = &batch->vertices.count;
    int index_offset = batch->indices.count;

    BS_VERTEX_DECLARATION(
        declaration, batch, increment,
        bs_vec3, bs_Position,
        bs_vec2, bs_Texture,
        bs_vec3, bs_Normal,
      //  bs_RGBA, bs_Color,
        bs_ivec4, bs_Bone,
        bs_vec4, bs_Weight
    );

    _bs_ensureBatchSize(batch, primitive->num_indices, primitive->num_vertices);
    _bs_pushIndices(batch, primitive->indices, primitive->num_indices);

    float* vertex = primitive->vertices;
    for(int i = 0; i < primitive->num_vertices; i++, vertex += primitive->vertex_size) {
        _bs_batchVertex(&declaration, &(bs_Vertex) {
            .bs_Position = *(bs_vec3*)(vertex),
            .bs_Texture = *(bs_vec2*)(vertex + primitive->texture_offset),
            .bs_Normal = *(bs_vec3*)(vertex + primitive->normal_offset),
         //   .bs_Color = BS_WHITE,
            .bs_Bone = *(bs_ivec4*)(vertex + primitive->bone_offset),
            .bs_Weight = *(bs_vec4*)(vertex + primitive->weight_offset),
        });
    }

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushMesh(bs_Batch* batch, bs_Mesh* mesh) {
    int index_offset = batch->indices.count;

    for(int i = 0; i < mesh->primitives_count; i++)
        _bs_pushPrimitive(batch, mesh->primitives + i);

    return _bs_batchRange(batch, index_offset);
}

BSAPI bs_Range _bs_pushModel(bs_Batch* batch, bs_Model* model) {
    int index_offset = batch->indices.count;

    for(int i = 0; i < model->meshes_count; i++)
        _bs_pushMesh(batch, model->meshes + i);

    return _bs_batchRange(batch, index_offset);
}

/*
void _bs_pushGlyph(bs_Batch* batch, bsgfx_Font* font, bs_Glyph* glyph, bs_vec3 pos, bs_RGBA col, float scale) {
    pos.y += (float)glyph->y_min * font->scale;

    bs_Quad quad = _bs_quad(pos, bs_v2MulV1(BS_V2(glyph->width, BS_TTF_DIM), scale));
    _bs_quadTextureCoords(&quad, glyph->tex_offset, glyph->tex_coord);
    _bs_pushQuad(batch, quad, col, NULL);
}

void _bs_pushText(bs_Batch* batch, bsgfx_Font* font, bs_vec3 pos, bs_RGBA col, float scale, const char* text, va_list args) {
    bs_Range batch_part = (bs_Range){ batch->indices.num_units, 0 };

    char buf[512];
    int len = vsprintf(buf, text, args);

    float original_x = pos.x;
    for (int i = 0; i < len; i++) {
        bs_Glyph* glyph = _bs_glyph(font, buf[i]);

        switch (buf[i]) {
        case ' ': pos.x += BS_TTF_DIM * scale / 3.0; break;
        case '\n': {
            pos.y -= BS_TTF_DIM * scale;
            pos.x = original_x;
        } break;
        default: {
            if (buf[i] != ' ') {
                _bs_pushGlyph(batch, font, glyph, pos, col, scale);
                pos.x += (float)glyph->long_hor_metric.advance_width * font->scale * scale;
            }
        } break;
        }
    }
}
*/



  /*==============================================================================
   * Batches
   *============================================================================*/

BSAPI bs_Attribute* _bs_queryAttributeN(bs_Batch* batch, char* name, int name_length) {
    bs_U64 name_hash = _bs_stringHash(name);
    for (int i = 0; i < batch->attributes_count; i++) {
        bs_Attribute* attribute = batch->attributes + i;

        if (attribute->name_hash == name_hash) {
            return attribute;
        }
    }

    return NULL;
}

static void _bs_nameBatch(bs_Object* object, const char* name) {
}

BSAPI bs_Result _val_bs_batch(bs_Object* object, int index_size, bs_Shader* shader, bs_BatchBits flags) {
 //   BS_VALIDATE_OBJECT_TYPE(object, BS_OBJECT_BATCH, BS_RESULT_VALIDATION_ERROR);
    BS_VALIDATE(shader->num_attributes > 0, BS_RESULT_VALIDATION_ERROR,);

    return _bs_batch(object, index_size, shader, flags);
}

BSAPI bs_Result _bs_batch(bs_Object* object, int index_size, bs_Shader* shader, bs_BatchBits flags) {
    bs_Batch* batch = object->batch;

    if (!batch)
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY))
        return BS_RESULT_OK;

    _bs_destroyBatch(batch);

    bs_U32 vertex_size = 0;
    for (int i = 0; i < shader->num_attributes; i++)
        vertex_size += shader->attributes[i].size;

    if (object->flags & BS_OBJECT_HAS_SWAPS_BIT)
        flags |= BSI_BATCH_SWAPS_BIT;

    batch->flags = flags | BS_BATCH_IS_CREATED;
    batch->attributes = shader->attributes;
    batch->attributes_count = shader->num_attributes;
#define BS_BATCH_INCR_BY 256
    batch->vertices = _bs_list(vertex_size, BS_BATCH_INCR_BY);
    batch->indices = _bs_list(index_size, BS_BATCH_INCR_BY);

    return BS_RESULT_OK;
}

BSAPI bool _bs_canPushBatch(bs_Batch* batch) {
    return (batch->flags & (BS_BATCH_IS_PUSHED | BS_BATCH_IS_CREATED));
}

BSAPI bool _bs_batchIsIndexed(bs_Batch* batch) {
    return batch->indices.unit_size > 0;
}

BSAPI void _bs_minimizeBatch(bs_Batch* batch) {
    _bs_minimizeList(&batch->vertices);
    _bs_minimizeList(&batch->indices);
}

static struct bs_BatchBindings {
    bs_U32 vertex_binding, index_binding, staging_binding;
    bs_U32 vertex_bind_set, index_bind_set, staging_bind_set;
    bool vertex_was_bound, index_was_bound, staging_was_bound;
} _bs_batchBindings(bs_Batch* batch) {
    struct bs_BatchBindings bindings = { 0 };

    if (batch->vertex_buffer && (bindings.vertex_was_bound = batch->vertex_buffer->buffer->flags & BSI_BUFFER_IS_BOUND)) {
        bindings.vertex_binding = batch->vertex_buffer->buffer->binding;
        bindings.vertex_bind_set = batch->vertex_buffer->buffer->bind_set;
    }

    if (batch->index_buffer && (bindings.index_was_bound = batch->index_buffer->buffer->flags & BSI_BUFFER_IS_BOUND)) {
        bindings.index_binding = batch->index_buffer->buffer->binding;
        bindings.index_bind_set = batch->index_buffer->buffer->bind_set;
    }

    if (batch->staging_buffer && (bindings.staging_was_bound = batch->staging_buffer->buffer->flags & BSI_BUFFER_IS_BOUND)) {
        bindings.staging_binding = batch->staging_buffer->buffer->binding;
        bindings.staging_bind_set = batch->staging_buffer->buffer->bind_set;
    }

    return bindings;
};

BSAPI bs_Result _bs_pushBatch(bs_Queue* queue, bs_Batch* batch, bs_U32 num_indices, bs_U32 num_vertices) {
    bs_Result result;

    if (num_indices == BS_U32_MAX)
        num_indices = batch->indices.count;

    if (num_vertices == BS_U32_MAX)
        num_vertices = batch->vertices.count;

    bs_U32 vertex_size = num_vertices * batch->vertices.unit_size;
    bs_U32 index_size = num_indices * batch->indices.unit_size;
    struct bs_BatchBindings bindings = _bs_batchBindings(batch);

    if (vertex_size == 0) {
        _bs_destroyBatch(batch);
        return BS_RESULT_ZERO_ALLOC;
    }

    bs_U32 object_flags = (batch->flags & BSI_BATCH_SWAPS_BIT) ? BS_OBJECT_HAS_SWAPS_BIT : 0;
    bs_BufferUsageFlags usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

    if (batch->flags & BS_BATCH_RAY_TRACEABLE)
        usage_flags |= VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;

   /**
    Staging buffer
    */
    batch->staging_buffer = BS_BUFFER(-1, 0, object_flags);
    result = _bs_buffer(batch->staging_buffer, BS_MAX(vertex_size, index_size),
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyBatch(batch);
        return result;
    }

    _bs_mapBuffer(batch->staging_buffer->buffer, vertex_size);

//    if (bindings.staging_was_bound)
//        _bs_bindBuffer(bindings.staging_bind_set, bindings.staging_binding, batch->staging_buffer->buffer, BS_DESCRIPTOR_TYPE_STORAGE_BUFFER);

   /**
    Vertex buffer
    */
    batch->vertex_buffer = BS_BUFFER(-1, 0, object_flags);
    result = _bs_buffer(batch->vertex_buffer, vertex_size,
        usage_flags | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyBatch(batch);
        return result;
    }

    _bs_stageList(batch->staging_buffer->buffer, &batch->vertices);
    _bs_copyAsync(queue, batch->staging_buffer->buffer, batch->vertex_buffer->buffer, 0, 0, BS_U32_MAX);

//    if (bindings.vertex_was_bound)
//        _bs_bindBuffer(bindings.vertex_bind_set, bindings.vertex_binding, batch->vertex_buffer->buffer);

   /**
    Index buffer
    */
    if (batch->indices.count != 0) {
        _bs_stageList(batch->staging_buffer->buffer, &batch->indices);

        batch->index_buffer = BS_BUFFER(-1, 0, object_flags);
        result = _bs_buffer(batch->index_buffer, index_size,
            usage_flags | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            0);

        if (result != BS_RESULT_OK) {
            _bs_destroyBatch(batch);
            return result;
        }

        _bs_copyAsync(queue, batch->staging_buffer->buffer, batch->index_buffer->buffer, 0, 0, BS_U32_MAX);
    }

//    if (bindings.index_was_bound)
//        _bs_bindBuffer(bindings.index_bind_set, bindings.index_binding, batch->index_buffer->buffer);

    if (!(batch->flags & BS_BATCH_KEEP_DATA)) {
        _bs_destroyList(&batch->vertices);
        _bs_destroyList(&batch->indices);
    }

//    if (bindings.vertex_was_bound || bindings.index_was_bound || bindings.staging_was_bound)
//        _bs_pushDescriptors();

    batch->flags |= BS_BATCH_IS_PUSHED;

    return result;
}

BSAPI void _bs_unpushBatch(bs_Batch* batch) {
    _bs_destroyBatch(batch);
    batch->vertices.count = 0;
    batch->indices.count = 0;

    // If uncomment beware of the _bs_destroyBatch memset

   // if (!(batch->flags & BS_BATCH_KEEP_DATA)) {
      //  batch->vertices = vertices;
      //  batch->indices = indices;
   // }
}

BSAPI int _bs_batchSize(bs_Batch* batch) {
    return (batch->indices.unit_size == 0) ? batch->vertices.count : batch->indices.count;
}

BSAPI void _bs_render(bs_Queue* queue, bs_Batch* batch, bs_Pipeline* pipeline, bs_U32 vertex_offset, bs_U32 vertex_count, bs_U32 instance_offset, bs_U32 instance_count) {
    VkDeviceSize offsets[] = { 0 };
    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);

    int batch_size = _bs_batchSize(batch);
    vertex_count = vertex_count == BS_U32_MAX ? batch_size : vertex_count;
    if (vertex_count == 0) return;
    if (instance_offset < 0) return;
    if (instance_count <= 0) return;
    if (!batch->vertex_buffer) return;

    bs_U32 vertex_swap = (batch->vertex_buffer->buffer->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;

    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->vk_pipeline);
    if (pipeline->num_bind_sets != 0) {
        vkCmdBindDescriptorSets(
            command_buffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            pipeline->vk_layout,
            0, pipeline->num_bind_sets, _bs_instance_->sets, 0, NULL
        );
    }

    vkCmdBindVertexBuffers(command_buffer, 0, 1, &batch->vertex_buffer->buffer->_[vertex_swap].vk_buffer, offsets);

    if (!_bs_batchIsIndexed(batch)) {
        vkCmdDraw(command_buffer, vertex_count, instance_count, vertex_offset, instance_offset);
    } else {
        bs_U32 index_swap = (batch->index_buffer->buffer->flags & BSI_BUFFER_SWAPS_BIT) ? _bs_scope_.context->frame : 0;
        vkCmdBindIndexBuffer(command_buffer, batch->index_buffer->buffer->_[index_swap].vk_buffer, 0, VK_INDEX_TYPE_UINT32);
        vkCmdDrawIndexed(command_buffer, vertex_count, instance_count, vertex_offset, 0, instance_offset);
    }
}

BSAPI void _bs_destroyBatch(bs_Batch* batch) {
    assert(batch != NULL);

    batch->flags &= ~(BS_BATCH_IS_PUSHED);

    if (batch->index_buffer && batch->indices.unit_size)
        _bs_destroyBuffer(batch->index_buffer->buffer);
    if (batch->vertex_buffer)
        _bs_destroyBuffer(batch->vertex_buffer->buffer);
    if (batch->staging_buffer)
        _bs_destroyBuffer(batch->staging_buffer->buffer);

    if (!(batch->flags & BS_BATCH_KEEP_DATA)) {
        _bs_destroyList(&batch->vertices);
        _bs_destroyList(&batch->indices);
    }
}



  /*==============================================================================
   * Renderer
   *============================================================================*/

static void _bs_nameRenderer(bs_Object* object, const char* name) {
    int name_length = strlen(name);

    bsi_nameHandleN((bs_U64)object->renderer->render_pass, VK_OBJECT_TYPE_RENDER_PASS, name, name_length);
    for (int i = 0; i < object->renderer->head.swaps_count; i++) {
        bsi_nameHandleN((bs_U64)object->renderer->_[i].framebuffer, VK_OBJECT_TYPE_FRAMEBUFFER, name, name_length);
    }
}

BSAPI void _val_bs_autoResizeRenderer(bs_Renderer* renderer, bs_Context* context) {
    if (renderer->head.source_id < 0)
        bs_criticalN(BS_CONSTANT_STRING("Renderer cannot be auto resized without id"));

    return _bs_autoResizeRenderer(renderer, context);
}

BSAPI void _bs_autoResizeRenderer(bs_Renderer* renderer, bs_Context* context) {
    renderer->context = context;
}

BSAPI bs_Result _bs_renderer(bs_Object* object, bs_RendererBits flags) {
    assert(object != NULL);
    bs_Renderer* renderer = object->renderer;

    if (!renderer)
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY))
        return BS_RESULT_OK;

    _bs_destroyRenderer(renderer);

    if (object->flags & BS_OBJECT_HAS_SWAPS_BIT)
        flags |= BSI_RENDERER_HAS_SWAPS_BIT;

    renderer->flags = flags;
    renderer->inputs = bs_list(sizeof(bs_Input), 8);
    renderer->outputs = bs_list(sizeof(bs_Output), 8);
    renderer->dependencies = bs_list(sizeof(VkSubpassDependency), 8);

    return BS_RESULT_OK;
}

 /**
  Output
  */
BSAPI void _val_bs_output(bs_Renderer* renderer, bs_Output output) {
    BS_VALIDATE(output.image->head.type == BS_OBJECT_IMAGE, , );

    _bs_output(renderer, output);
}

BSAPI void _bs_output(bs_Renderer* renderer, bs_Output output) {
    renderer->subpasses_count = BS_MAX(renderer->subpasses_count, output.subpass + 1);
    _bs_pushBack(&renderer->outputs, &output);
}

 /**
  Input
  */
BSAPI void _val_bs_input(bs_Renderer* renderer, bs_Input input) {
    _bs_input(renderer, input);
}

BSAPI void _bs_input(bs_Renderer* renderer, bs_Input input) {
    renderer->subpasses_count = BS_MAX(renderer->subpasses_count, input.subpass + 1);
    _bs_pushBack(&renderer->inputs, &input);
}

 /**
  Dependency
  */
BSAPI void _val_bs_dependency(bs_Renderer* renderer, bs_U32 src_subpass, bs_U32 dst_subpass, bs_DependencyFlags flags, bs_PipelineStage src_stage, bs_PipelineStage dst_stage, bs_AccessMask src_access, bs_AccessMask dst_access) {
    _bs_dependency(renderer, src_subpass, dst_subpass, flags, src_stage, dst_stage, src_access, dst_access);
}

BSAPI void _bs_dependency(bs_Renderer* renderer, bs_U32 src_subpass, bs_U32 dst_subpass, bs_DependencyFlags flags, bs_PipelineStage src_stage, bs_PipelineStage dst_stage, bs_AccessMask src_access, bs_AccessMask dst_access) {
    _bs_pushBack(&renderer->dependencies, &(VkSubpassDependency) {
        .srcSubpass = src_subpass,
        .dstSubpass = dst_subpass,
        .srcStageMask = src_stage,
        .dstStageMask = dst_stage,
        .srcAccessMask = src_access,
        .dstAccessMask = dst_access,
        .dependencyFlags = flags
    });
}

static int _bs_sortInputs(const void* a, const void* b) {
    bs_Input* input_a = (bs_Input*)a;
    bs_Input* input_b = (bs_Input*)b;

    if (input_a->subpass != input_b->subpass)
        return (input_a->subpass < input_b->subpass) ? -1 : 1;
    else return 0;
}

static int _bs_sortOutputs(const void* a, const void* b) {
    bs_Output* output_a = (bs_Output*)a;
    bs_Output* output_b = (bs_Output*)b;

    bool is_depth_a = _bs_isDepthFormat(output_a->image->format);
    bool is_depth_b = _bs_isDepthFormat(output_b->image->format);

    if (output_a->subpass != output_b->subpass)
        return (output_a->subpass < output_b->subpass) ? -1 : 1;
    else if (is_depth_a != is_depth_b)
        return is_depth_a ? 1 : -1;
    else return (output_a->attachment < output_b->attachment) ? -1 : 1;
}

BSAPI void _val_bs_renderPass(bs_Renderer* renderer) {
    BS_VALIDATE(!renderer->render_pass, , "Renderer (%d) already has a render pass\n", renderer->head.id);

    _bs_renderPass(renderer);
}

BSAPI bs_Result _bs_renderPass(bs_Renderer* renderer) {
    qsort(renderer->inputs.data, renderer->inputs.count, sizeof(bs_Input), _bs_sortInputs);
    qsort(renderer->outputs.data, renderer->outputs.count, sizeof(bs_Output), _bs_sortOutputs);

    const size_t subpasses_size = renderer->subpasses_count * sizeof(VkSubpassDescription);
    const size_t attachments_size = renderer->outputs.count * sizeof(VkAttachmentDescription);
    const size_t attachment_references_size = renderer->outputs.count * sizeof(VkAttachmentReference);
    const size_t input_references_size = renderer->inputs.count * sizeof(VkAttachmentReference);

    VkSubpassDescription* subpasses = bs_alloca(subpasses_size);
    VkAttachmentDescription* attachments = bs_alloca(attachments_size);
    VkAttachmentReference* attachment_references = bs_alloca(attachment_references_size);
    VkAttachmentReference* input_references = bs_alloca(input_references_size);

    memset(subpasses, 0, subpasses_size);

    for (int i = 0; i < renderer->outputs.count; i++) {
        bs_Output* output = _bs_fetchUnit(&renderer->outputs, i);

        bool is_stencil = _bs_isStencilFormat(output->image->format);
        bool is_depth = _bs_isDepthFormat(output->image->format);

        attachments[i] = (VkAttachmentDescription) {
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = (VkAttachmentLoadOp)output->load_op,
            .storeOp = (VkAttachmentStoreOp)output->store_op,
            .stencilLoadOp = is_stencil ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = is_stencil ? VK_ATTACHMENT_STORE_OP_DONT_CARE : VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .format = (VkFormat)output->image->format,
            .initialLayout = (VkImageLayout)output->old_layout,
            .finalLayout = (VkImageLayout)output->new_layout,
        };

        VkSubpassDescription* subpass = subpasses + output->subpass;
        VkAttachmentReference* reference = attachment_references + i;

        if (is_depth) {
            *reference = (VkAttachmentReference) {
                .attachment = i,
                .layout = output->new_layout == BS_IMAGE_LAYOUT_GENERAL ? VK_IMAGE_LAYOUT_GENERAL :
                    (is_stencil ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL : VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL)
            };

            subpass->pDepthStencilAttachment = reference;
            renderer->flags |= (1 << output->subpass);
        }
        else {
            if (!subpass->pColorAttachments)
                subpass->pColorAttachments = reference;

            *reference = (VkAttachmentReference) {
                .attachment = i,
                .layout = output->new_layout == BS_IMAGE_LAYOUT_GENERAL ? VK_IMAGE_LAYOUT_GENERAL : VK_IMAGE_LAYOUT_GENERAL
            };

            subpass->colorAttachmentCount++;
        }
    }

    for (int i = 0; i < renderer->inputs.count; i++) {
        bs_Input* input = _bs_fetchUnit(&renderer->inputs, i);

        VkSubpassDescription* subpass = subpasses + input->subpass;
        VkAttachmentReference* reference = input_references + i;

        bs_Output* output = _bs_fetchUnit(&renderer->outputs, input->attachment);

        *reference = (VkAttachmentReference) {
            .attachment = input->attachment,
            .layout = input->subpass == output->subpass ? VK_IMAGE_LAYOUT_GENERAL : VK_IMAGE_LAYOUT_GENERAL
        };

        if (!subpass->pInputAttachments)
            subpass->pInputAttachments = reference;

        subpass->inputAttachmentCount++;
    }

    VkRenderPassCreateInfo render_pass_ci = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = renderer->outputs.count,
        .pAttachments = attachments,
        .subpassCount = renderer->subpasses_count,
        .pSubpasses = subpasses,
        .dependencyCount = renderer->dependencies.count,
        .pDependencies = (VkSubpassDependency*)renderer->dependencies.data,
    };

    VkResult result = vkCreateRenderPass(_bs_instance_->device, &render_pass_ci, NULL, &renderer->render_pass);

    if (result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateRenderPass", result, "");
        return _bs_convertVulkanResult(result);
    }

    const char* id_name = renderer->head.id == 0 ? NULL : _bs_idName(renderer->head.source_id, renderer->head.id);
    if (id_name)
        bsi_nameHandleF((bs_U64)renderer->render_pass, VK_OBJECT_TYPE_RENDER_PASS, "(%d) renderer " BS_PRINT_CYAN "%s" BS_PRINT_RESET, renderer->head.id, id_name);

    return BS_RESULT_OK;
}

BSAPI void _val_bs_framebuffer(bs_Renderer* renderer, bs_ivec2 dim) {
    BS_VALIDATE(renderer->_->framebuffer == NULL,, "Renderer \"%s\" already has a framebuffer", renderer->head.name);
    BS_VALIDATE(renderer->render_pass != NULL,,);

    _bs_framebuffer(renderer, dim);
}

BSAPI bs_Result _bs_framebuffer(bs_Renderer* renderer, bs_ivec2 dim) {
    VkResult vk_result;

    VkImageView* vk_views = bs_alloca(renderer->outputs.count * sizeof(VkImageView));
    renderer->dim = dim;

    for (int i = 0; i < renderer->head.swaps_count; i++) {
        for (int j = 0; j < renderer->outputs.count; j++) {
            bs_Output* output = _bs_fetchUnit(&renderer->outputs, j);

            int swap = output->image->flags & BS_IMAGE_SWAPS_BIT ? i : 0;
            vk_views[j] = output->image->_[swap].vk_image_view;
        }

        VkFramebufferCreateInfo framebuf_ci = {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = renderer->render_pass,
            .attachmentCount = renderer->outputs.count,
            .pAttachments = vk_views,
            .width = renderer->dim.x,
            .height = renderer->dim.y,
            .layers = 1,
        };

        vk_result = vkCreateFramebuffer(_bs_instance_->device, &framebuf_ci, NULL, &renderer->_[i].framebuffer);
        if (vk_result != VK_SUCCESS) {
            BS_WARN_VULKAN_ERROR("vkCreateFramebuffer", vk_result, "");
            return _bs_convertVulkanResult(vk_result);
        }
    }

    return BS_RESULT_OK;
}

BSAPI bool _bs_rendererIsDynamic(bs_Renderer* renderer) {
    return renderer->render_pass == NULL;
}

BSAPI bs_RendererScope _val_bs_beginRender(bs_Queue* queue, bs_Renderer* renderer) {
    if (renderer->render_pass) {
        BS_VALIDATE(_bs_procs_.vkCmdBeginRenderingKHR != NULL, (bs_RendererScope) { 0 },);
        BS_VALIDATE(_bs_procs_.vkCmdEndRenderingKHR != NULL, (bs_RendererScope) { 0 },);
    }

    return _bs_beginRender(queue, renderer);
}

BSAPI bs_RendererScope _bs_beginRender(bs_Queue* queue, bs_Renderer* renderer) {
    //_bs_scope_.renderer = renderer;

    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);

    VkClearValue* clear_values = bs_alloca(renderer->outputs.count * sizeof(VkClearValue));
    memset(clear_values, 0, renderer->outputs.count * sizeof(VkClearValue));

    for (int i = 0; i < renderer->outputs.count; i++) {
        bs_Output* output = _bs_fetchUnit(&renderer->outputs, i);

        if (_bs_isDepthFormat(output->image->format))
            clear_values[i].depthStencil.depth = 1.0;
        else
            clear_values[i].color.float32[3] = 1.0;
    }

    if (renderer->render_pass) {
        VkRenderPassBeginInfo render_pass_i = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .renderPass = renderer->render_pass,
            .framebuffer = renderer->_[_bs_scope_.context->image_index].framebuffer,
            .renderArea.extent = {
                .width = renderer->dim.x,
                .height = renderer->dim.y,
            },
            .clearValueCount = renderer->outputs.count,
            .pClearValues = clear_values,
        };

        vkCmdBeginRenderPass(command_buffer, &render_pass_i, VK_SUBPASS_CONTENTS_INLINE);
    }
    else {
        VkRenderingAttachmentInfo* attachments = bs_alloca(renderer->outputs.count * sizeof(VkRenderingAttachmentInfo));
        VkRenderingAttachmentInfo* depth_attachment = NULL;
        int color_attachments_count = renderer->outputs.count;

        for (int i = 0; i < renderer->outputs.count; i++) {
            bs_Output* output = _bs_fetchUnit(&renderer->outputs, i);

            attachments[i] = (VkRenderingAttachmentInfo){
                .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
                .imageView = output->image->_[output->image->flags & BS_IMAGE_SWAPS_BIT ? _bs_scope_.context->image_index : 0].vk_image_view,
                .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            };

            if (_bs_isDepthFormat(output->image->format)) {
                depth_attachment = attachments + i; // should only be 1
                color_attachments_count--;
            }
        }

        VkRenderingInfoKHR rendering_info = {
            .sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR,
            .renderArea = {
                .extent = {
                    .width = renderer->dim.x,
                    .height = renderer->dim.y,
                },
            },
            .layerCount = 1,
            .colorAttachmentCount = color_attachments_count,
            .pColorAttachments = attachments,
            .pDepthAttachment = depth_attachment,
            .pStencilAttachment = VK_NULL_HANDLE,
        };

        _bs_procs_.vkCmdBeginRenderingKHR(command_buffer, &rendering_info);
    }

    VkViewport viewport = {
        .x = 0.0f,
        .y = 0.0f,
        .width = renderer->dim.x,
        .height = renderer->dim.y,
        .minDepth = 0.0f,
        .maxDepth = 1.0f,
    };

    vkCmdSetViewport(command_buffer, 0, 1, &viewport);

    VkRect2D scissor = {
        .extent = {
            .width = renderer->dim.x,
            .height = renderer->dim.y,
        },
    };

    vkCmdSetScissor(command_buffer, 0, 1, &scissor);

    return (bs_RendererScope) {
        .renderer = renderer,
        .queue = queue,
        .subpass = 0,
    };
}

BSAPI void _bs_endRender(bs_Queue* queue, bs_Renderer* renderer) {
    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);
    if (renderer->render_pass) {
        //_bs_scope_.renderer = renderer;
        vkCmdEndRenderPass(command_buffer);
    }
    else {
        _bs_procs_.vkCmdEndRenderingKHR(command_buffer);
    }

    //_bs_scope_.renderer = NULL;
    //_bs_scope_.subpass = 0;
}

BSAPI void _val_bs_runPass(bs_Queue* queue, bs_Renderer* renderer, bs_SubpassFunction subpasses[], int subpasses_count) {
    BS_VALIDATE(subpasses_count <= renderer->subpasses_count,,);

    for (int i = 0; i < subpasses_count; i++) {
        BS_VALIDATE(subpasses[i] != NULL,,);
    }

    _bs_runPass(queue, renderer, subpasses, subpasses_count);
}

BSAPI void _bs_runPass(bs_Queue* queue, bs_Renderer* renderer, bs_SubpassFunction callbacks[], int callbacks_count) {
    _bs_beginRender(queue, renderer);
    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);

    if (renderer->render_pass) {
        for (int i = 0; i < renderer->subpasses_count; i++) {
            bs_SubpassFunction callback = callbacks[i];

            if (i != 0) {
                //_bs_scope_.subpass = i;
                vkCmdNextSubpass(command_buffer, VK_SUBPASS_CONTENTS_INLINE);
            }

            bs_RendererScope scope = {
                .queue = queue,
                .renderer = renderer,
                .subpass = i,
            };

            callback(&scope);
        }
    }
    else {
        bs_RendererScope scope = {
            .queue = queue,
            .renderer = renderer,
        };

        for (int i = 0; i < callbacks_count; i++)
            callbacks[i](&scope);
    }
    _bs_endRender(queue, renderer);
}

static void _bs_destroyFramebuffer(bs_Renderer* renderer) {
    for (int i = 0; i < renderer->head.swaps_count; i++) {
        vkDestroyFramebuffer(_bs_instance_->device, renderer->_[i].framebuffer, NULL);
        renderer->_[i].framebuffer = 0;
    }
}

BSAPI void _bs_destroyRenderer(bs_Renderer* renderer) {
    _bs_destroyList(&renderer->inputs);
    _bs_destroyList(&renderer->outputs);

    vkDestroyRenderPass(_bs_instance_->device, renderer->render_pass, NULL);
    renderer->render_pass = 0;

    _bs_destroyFramebuffer(renderer);

    _bs_resetObject(&renderer->head, sizeof(bs_Renderer));
}

BSAPI void _bs_resizeRenderer(bs_Renderer* renderer, bs_ivec2 dim) {
    renderer->dim = dim;

    _bs_destroyFramebuffer(renderer);
    _bs_framebuffer(renderer, dim);
}



  /*==============================================================================
   * Computation
   *============================================================================*/

BSAPI void _bs_dispatchAsync(bs_Queue* queue, bs_Pipeline* pipeline, bs_U32 x, bs_U32 y, bs_U32 z) {
    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);

    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline->vk_pipeline);
    vkCmdBindDescriptorSets(
        command_buffer,
        VK_PIPELINE_BIND_POINT_COMPUTE,
        pipeline->vk_layout,
        0, pipeline->num_bind_sets, _bs_instance_->sets, 0, NULL);

    vkCmdDispatch(command_buffer, x, y, z);

    if (queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(queue, 0, NULL);
        _bs_stallQueue(queue);
    }
}



  /*==============================================================================
   * Ray Tracing
   *============================================================================*/

static void _bs_nameRayTracer(bs_Object* object, const char* name) {
    int name_length = strlen(name);

    bsi_nameHandleN((bs_U64)object->ray_tracer->TLAS, VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, name, name_length);
    bsi_nameHandleN((bs_U64)object->ray_tracer->BLAS, VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, name, name_length);
}

BSAPI void _bs_rayTrace(bs_RayTracer* ray_tracer, bs_Pipeline* pipeline, bs_U32 width, bs_U32 height, bs_U32 depth) {
    _bs_warnF("_bs_rayTrace has not been implemented yet");
    /*
    VkCommandBuffer command_buffer = _bsi_fetchCommands();

    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipeline->vk_pipeline);
    if (pipeline->num_bind_sets != 0) {
        vkCmdBindDescriptorSets(
            command_buffer,
            VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
            pipeline->vk_layout,
            0, pipeline->num_bind_sets, _bs_instance_->sets, 0, NULL
        );
    }

    const int ray_gen_index = 0, miss_index = 1;

    VkDeviceAddress address = _bs_bufferAddress(pipeline->binding_table->_->vk_buffer);

    VkStridedDeviceAddressRegionKHR tables[4] = { 0 };
    int order[4] = { BS_RAY_GEN_SHADER, BS_MISS_SHADER, -1, -1 };

    if (ray_tracer->groups_count > 2) {
        _bs_warnF(BS_CONSTANT_STRING("Not implemented: ray_tracer->groups_count > 2\n"));
        return;
    }

    for (int i = 0; i < ray_tracer->groups_count; i++) {
        int map = 0;
        for (; map < 4; map++) {
            if (ray_tracer->_[i].shader->type == order[map])
                break;
        }

        tables[map] = (VkStridedDeviceAddressRegionKHR){
            .deviceAddress = address + ray_tracer->record_size * i,
            .size = ray_tracer->record_size,
            .stride = ray_tracer->record_size,
        };
    }

    _bs_procs_.vkCmdTraceRaysKHR(command_buffer, tables + 0, tables + 1, tables + 2, tables + 3, width, height, depth);
    */
}

BSAPI bs_Result _bs_rayTracer(bs_Object* object, bs_U32 flags, bs_Shader* shaders[], int shaders_count) {
    bs_RayTracer* ray_tracer = object->ray_tracer;

    if (!ray_tracer)
        return BS_RESULT_OK;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY))
        return BS_RESULT_OK;

    _bs_destroyRayTracer(ray_tracer);

    ray_tracer->aabbs = _bs_list(sizeof(VkAabbPositionsKHR), 128);
    ray_tracer->batches = _bs_list(sizeof(bs_Batch*), 16);
    ray_tracer->groups_count = shaders_count;

    for (int i = 0; i < shaders_count; i++) {
        bs_Shader* shader = shaders[i];

        object->ray_tracer->_[i] = (struct bs_ShaderGroup) {
            .shader = shader
        };
    }

    return BS_RESULT_OK;
}

BSAPI void _bs_accelerateAabb(bs_RayTracer* tracer, bs_Aabb aabb) {
    _bs_pushBack(&tracer->aabbs, &(VkAabbPositionsKHR) {
        .minX = aabb.min.x,
        .minY = aabb.min.y,
        .minZ = aabb.min.z,
        .maxX = aabb.max.x,
        .maxY = aabb.max.y,
        .maxZ = aabb.max.z,
    });
}

BSAPI void _bs_accelerateBatch(bs_RayTracer* tracer, bs_Batch* batch) {
    _bs_pushBack(&tracer->batches, &batch);
}

BSAPI void _bs_destroyRayTracer(bs_RayTracer* tracer) { // i'm already tracer
    _bs_procs_.vkDestroyAccelerationStructureKHR(_bs_instance_->device, tracer->BLAS, NULL);
    _bs_procs_.vkDestroyAccelerationStructureKHR(_bs_instance_->device, tracer->TLAS, NULL);
    tracer->BLAS = tracer->TLAS = NULL;

    memset(tracer, 0, sizeof(bs_RayTracer));
}

static bs_Result _bs_buildBLAS(bs_Queue* queue, bs_RayTracer* tracer, bs_Buffer* staging_buffer) {
    VkResult vk_result;
    bs_Result result;

    _bs_stageList(staging_buffer, &tracer->aabbs);
    bs_Object* aabb_buffer = BS_BUFFER(-1, 0, 0);
    result = _bs_buffer(aabb_buffer, tracer->aabbs.count * sizeof(VkAabbPositionsKHR),
        VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    _bs_copyAsync(queue, staging_buffer, aabb_buffer->buffer, 0, 0, BS_U32_MAX);

    _bsi_fetchCommands(queue);

    queue->flags &= ~BS_QUEUE_SINGLE_TIMES_BIT;

    bs_Batch* batch = *(bs_Batch**)_bs_fetchUnit(&tracer->batches, 0);

    VkAccelerationStructureGeometryKHR geometry = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR ,
        .geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        .geometry.triangles = {
            .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
            .vertexFormat = VK_FORMAT_R32G32B32_SFLOAT,
            .vertexData.deviceAddress = _bs_bufferAddress(batch->vertex_buffer->buffer->_->vk_buffer),
            .vertexStride = batch->vertices.unit_size,
            .indexType = VK_INDEX_TYPE_UINT32,
            .indexData.deviceAddress = _bs_bufferAddress(batch->index_buffer->buffer->_->vk_buffer),
            .maxVertex = batch->vertices.count - 1,
            .transformData = { 0 },
        },
        .flags = VK_GEOMETRY_OPAQUE_BIT_KHR,
    };

    VkAccelerationStructureGeometryKHR aabb_geometry = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR ,
        .geometryType = VK_GEOMETRY_TYPE_AABBS_KHR,
        .geometry.aabbs = {
            .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR,
            .stride = sizeof(VkAabbPositionsKHR),
            .data.deviceAddress = _bs_bufferAddress(aabb_buffer->buffer->_->vk_buffer),
        },
        .flags = VK_GEOMETRY_OPAQUE_BIT_KHR,
    };

    VkAccelerationStructureBuildRangeInfoKHR range_info = {
        .primitiveCount = batch->indices.count / 3,
    };

    VkAccelerationStructureBuildRangeInfoKHR aabb_range_info = {
        .primitiveCount = tracer->aabbs.count,
    };

    VkAccelerationStructureBuildGeometryInfoKHR build_info = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        .flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR,
        .geometryCount = 1,
        .pGeometries = &aabb_geometry,
        .mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        .type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
        .srcAccelerationStructure = VK_NULL_HANDLE,
    };

    VkAccelerationStructureBuildSizesInfoKHR size_info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
    _bs_procs_.vkGetAccelerationStructureBuildSizesKHR(
        _bs_instance_->device,
        VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
        &build_info,
        &aabb_range_info.primitiveCount,
        &size_info);

    bs_Object* BLAS_buffer_obj = BS_BUFFER(-1, 0, 0);
    tracer->BLAS_buffer = BLAS_buffer_obj->buffer;
    result = _bs_buffer(BLAS_buffer_obj, size_info.accelerationStructureSize,
        VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    VkAccelerationStructureCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        .type = build_info.type,
        .size = size_info.accelerationStructureSize,
        .buffer = tracer->BLAS_buffer->_->vk_buffer,
        .offset = 0,
    };

    result = _bs_convertVulkanResult(_bs_procs_.vkCreateAccelerationStructureKHR(_bs_instance_->device, &createInfo, NULL, &tracer->BLAS));
    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    bs_Object* BLAS_scratch_buffer_obj = BS_BUFFER(-1, 0, 0);
    tracer->BLAS_scratch_buffer = BLAS_scratch_buffer_obj->buffer;
    result = _bs_buffer(BLAS_scratch_buffer_obj, size_info.buildScratchSize,
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    build_info.dstAccelerationStructure = tracer->BLAS;
    build_info.scratchData.deviceAddress = _bs_bufferAddress(tracer->BLAS_scratch_buffer->_->vk_buffer);

    const VkAccelerationStructureBuildRangeInfoKHR* pRangeInfo = &aabb_range_info;

    _bs_procs_.vkCmdBuildAccelerationStructuresKHR(_bsi_fetchCommands(queue), 1, &build_info, &pRangeInfo);
    queue->flags |= BS_QUEUE_SINGLE_TIMES_BIT;

    _bs_pushQueue(queue, 0, NULL);
    _bs_stallQueue(queue);

    return BS_RESULT_OK;
}

static bs_Result _bs_buildTLAS(bs_Queue* queue, bs_RayTracer* tracer, bs_Buffer* staging_buffer) {
    bs_Result result;

    VkCommandBuffer cmds = _bsi_fetchCommands(queue);
    queue->flags &= ~BS_QUEUE_SINGLE_TIMES_BIT;

    VkAccelerationStructureDeviceAddressInfoKHR address_info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR };
    address_info.accelerationStructure = tracer->BLAS;
    VkDeviceAddress blasAddress = _bs_procs_.vkGetAccelerationStructureDeviceAddressKHR(_bs_instance_->device, &address_info);

    VkAccelerationStructureInstanceKHR instance = { 0 };
    const float rcpSqrt2 = sqrtf(0.5f);
    instance.transform.matrix[0][0] = -rcpSqrt2;
    instance.transform.matrix[0][2] = rcpSqrt2;
    instance.transform.matrix[1][1] = 1.0f;
    instance.transform.matrix[2][0] = -rcpSqrt2;
    instance.transform.matrix[2][2] = -rcpSqrt2;
    instance.instanceCustomIndex = 0;
    instance.mask = 0xFF;
    instance.instanceShaderBindingTableRecordOffset = 0;
    instance.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;
    instance.accelerationStructureReference = blasAddress;

    VkAccelerationStructureBuildRangeInfoKHR range_info = {
        .primitiveCount = 1,
    };

    bs_Object* instance_buffer_obj = BS_BUFFER(-1, 0, 0);
    bs_Buffer* instance_buffer = instance_buffer_obj->buffer;
    result = _bs_buffer(instance_buffer_obj, sizeof(instance),
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        BS_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    memcpy(staging_buffer->_->data, &instance, sizeof(instance));
    _bs_copyAsync(queue, staging_buffer, instance_buffer, 0, 0, sizeof(instance));

    VkBufferMemoryBarrier barrier = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
        .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
        .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .buffer = instance_buffer->_->vk_buffer,
        .offset = 0,
        .size = VK_WHOLE_SIZE
    };

    vkCmdPipelineBarrier(
        _bsi_fetchCommands(queue),
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
        0,
        0, NULL,
        1, &barrier,
        0, NULL
    );
    VkAccelerationStructureGeometryInstancesDataKHR instancesVk = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR,
        .arrayOfPointers = VK_FALSE,
        .data.deviceAddress = _bs_bufferAddress(instance_buffer->_->vk_buffer),
    };

    VkAccelerationStructureGeometryKHR geometry = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        .geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR,
        .geometry.instances = instancesVk,
    };

    VkAccelerationStructureBuildGeometryInfoKHR build_info = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR,
        .flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR,
        .geometryCount = 1,
        .pGeometries = &geometry,
        .mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
        .type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
        .srcAccelerationStructure = VK_NULL_HANDLE,
    };

    VkAccelerationStructureBuildSizesInfoKHR size_info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
    _bs_procs_.vkGetAccelerationStructureBuildSizesKHR(_bs_instance_->device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &build_info,
        &range_info.primitiveCount, &size_info);

    bs_Object* TLAS_buffer_obj = BS_BUFFER(-1, 0, 0);
    tracer->TLAS_buffer = TLAS_buffer_obj->buffer;
    result = _bs_buffer(TLAS_buffer_obj, size_info.accelerationStructureSize,
        VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        BS_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    VkAccelerationStructureCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
        .type = build_info.type,
        .size = size_info.accelerationStructureSize,
        .buffer = tracer->TLAS_buffer->_->vk_buffer,
        .offset = 0,
    };

    result = _bs_convertVulkanResult(_bs_procs_.vkCreateAccelerationStructureKHR(_bs_instance_->device, &createInfo, NULL, &tracer->TLAS));
    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    build_info.dstAccelerationStructure = tracer->TLAS;

    bs_Object* TLAS_scratch_buffer_obj = BS_BUFFER(-1, 0, 0);
    tracer->TLAS_scratch_buffer = TLAS_scratch_buffer_obj->buffer;
    result = _bs_buffer(
        TLAS_scratch_buffer_obj,
        size_info.buildScratchSize,
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, BS_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    build_info.scratchData.deviceAddress = _bs_bufferAddress(tracer->TLAS_scratch_buffer->_->vk_buffer);

    const VkAccelerationStructureBuildRangeInfoKHR* p_range_info = &range_info;

    _bs_procs_.vkCmdBuildAccelerationStructuresKHR(_bsi_fetchCommands(queue), 1, &build_info, &p_range_info);
    queue->flags |= BS_QUEUE_SINGLE_TIMES_BIT;

    _bs_pushQueue(queue, 0, NULL);
    _bs_stallQueue(queue);

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_build(bs_Queue* queue, bs_RayTracer* tracer) {
    bs_Object* staging_buffer_obj = BS_BUFFER(-1, 0, 0);
    bs_Buffer* staging_buffer = staging_buffer_obj->buffer;
    bs_Result result = _bs_buffer(staging_buffer_obj, BS_MAX(sizeof(VkAccelerationStructureInstanceKHR), tracer->aabbs.count * sizeof(VkAabbPositionsKHR)),
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    _bs_mapBuffer(staging_buffer, BS_U32_MAX);

    result = _bs_buildBLAS(queue, tracer, staging_buffer);
    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    result = _bs_buildTLAS(queue, tracer, staging_buffer);
    if (result != BS_RESULT_OK) {
        _bs_destroyRayTracer(tracer);
        return result;
    }

    return result;
}



  /*==============================================================================
   * Synchronization
   *============================================================================*/

BSAPI void _bs_barrier(bs_Queue* queue, bs_U32 dependency_flags, bs_U32 src_stage, bs_U32 dst_stage, bs_U32 src_access, bs_U32 dst_access) {
    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);

    vkCmdPipelineBarrier(
        command_buffer,
        src_stage, dst_stage,
        dependency_flags,
        1, &(VkMemoryBarrier) {
            .sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
            .srcAccessMask = src_access,
            .dstAccessMask = dst_access,
        },
        0, NULL, 0, NULL);

    if (queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(queue, 0, NULL);
        _bs_stallQueue(queue);
    }
}



  /*==============================================================================
   * Queues
   *============================================================================*/

static inline VkQueueFlags _bs_convertQueueFlags(bs_QueueBits flags) {
    return
        (flags & BS_QUEUE_GRAPHICS_BIT ? VK_QUEUE_GRAPHICS_BIT : 0) |
        (flags & BS_QUEUE_COMPUTE_BIT ? VK_QUEUE_COMPUTE_BIT : 0) |
        (flags & BS_QUEUE_TRANSFER_BIT ? VK_QUEUE_TRANSFER_BIT : 0);
}

BSAPI bs_I32 _bs_queueFamily(bs_QueueBits _bs_flags) {
    VkQueueFlagBits flags = _bs_convertQueueFlags(_bs_flags);

    bs_U32 num_families = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_bs_instance_->physical_device->vk_device, &num_families, NULL);
    VkQueueFamilyProperties* queue_families = _bs_calloc(num_families, sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(_bs_instance_->physical_device->vk_device, &num_families, queue_families);

    for (bs_U32 i = 0; i < num_families; i++) {
        if (!(queue_families[i].queueFlags & flags)) continue;
        if (!(flags & VK_QUEUE_GRAPHICS_BIT)) {
            _bs_free(queue_families);
            return i;
        }

        VkBool32 supports_present = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(_bs_instance_->physical_device->vk_device, i, _bs_scope_.context->surface, &supports_present);
        if (supports_present) {
            _bs_free(queue_families);
            return i;
        }
    }

    _bs_free(queue_families);
    return -1;
}

BSAPI int _bs_queueSwap(bs_Queue* queue) {
    return queue->flags & BSI_QUEUE_SWAPS_BIT ? _bs_scope_.context->image_index : 0;
}

static void _bs_nameQueue(bs_Object* object, const char* name) {
    int name_length = strlen(name);
    //object->queue->flags |= BS_QUEUE_IS_NAMED;

    //bsi_nameHandleN(object->queue->queue, VK_OBJECT_TYPE_QUEUE, name, name_length);

    for (int i = 0; i < object->queue->head.swaps_count; i++) {
        if (object->queue->_[i].fence)
            bsi_nameHandleN((bs_U64)object->queue->_[i].fence, VK_OBJECT_TYPE_FENCE, name, name_length);
        if (object->queue->_[i].semaphore)
            bsi_nameHandleN((bs_U64)object->queue->_[i].semaphore, VK_OBJECT_TYPE_SEMAPHORE, name, name_length);
        if (object->queue->_[i].command_buffer)
            bsi_nameHandleN((bs_U64)object->queue->_[i].command_buffer, VK_OBJECT_TYPE_COMMAND_BUFFER, name, name_length);
    }
}

static VkCommandPool _bs_ensureCommandPool() {
    static _Thread_local VkCommandPool command_pool;
    if (!command_pool) {
        VkCommandPoolCreateInfo pool_ci = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex = _bs_instance_->queue_family->index,
        };
        VkResult result = vkCreateCommandPool(_bs_instance_->device, &pool_ci, NULL, &command_pool);
        if (result != VK_SUCCESS) {
            BS_CRITICAL_VULKAN_ERROR("vkCreateCommandPool", result, "");
        }
        else {
            bs_logF("Created command pool");
        }
    }

    return command_pool;
}

BSAPI bs_Result _val_bs_queue(bs_Object* object, bs_U32 queue_index, bs_QueueBits flags) {
    BS_VALIDATE(queue_index < _bs_config_.queues_count, BS_RESULT_VALIDATION_ERROR,);

    return _bs_queue(object, queue_index, flags);
}

BSAPI bs_Result _bs_queue(bs_Object* object, bs_U32 queue_index, bs_QueueBits flags) {
    VkResult vk_result;
    bs_Queue* queue = object->queue;

    if (!queue) {
        return BS_RESULT_OK;
    }

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY)) {
        return BS_RESULT_OK;
    }

    _bs_destroyQueue(queue);

    if (object->flags & BS_OBJECT_HAS_SWAPS_BIT)
        flags |= BSI_QUEUE_SWAPS_BIT;

    queue->flags = flags;

    queue->family = _bs_instance_->queue_family->index;
    vkGetDeviceQueue(_bs_instance_->device, queue->family, queue_index, &queue->queue);

    VkCommandPool command_pool = _bs_ensureCommandPool();

   /**
    Command Buffers
    */
    VkCommandBufferAllocateInfo alloc_i = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = command_pool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = queue->head.swaps_count,
    };

    VkCommandBuffer command_buffer_result[3] = { 0 };
    vk_result = vkAllocateCommandBuffers(_bs_instance_->device, &alloc_i, command_buffer_result);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkAllocateCommandBuffers", vk_result, "");
        return _bs_convertVulkanResult(vk_result);
    }

    for (int i = 0; i < queue->head.swaps_count; i++)
        queue->_[i].command_buffer = command_buffer_result[i];

    if (flags & BS_QUEUE_SINGLE_TIMES_BIT)
        return BS_RESULT_OK;

   /**
    Semaphores / Fences
    */
    VkSemaphoreCreateInfo semaphore_ci = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    VkFenceCreateInfo fence_ci = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT,
    };

    for (int i = 0; i < queue->head.swaps_count; i++) {
        if (!(flags & BS_QUEUE_DONT_SIGNAL)) {
            vk_result = vkCreateSemaphore(_bs_instance_->device, &semaphore_ci, NULL, &object->queue->_[i].semaphore);
            if (vk_result != VK_SUCCESS) {
                BS_WARN_VULKAN_ERROR("vkCreateSemaphore", vk_result, "");
                return _bs_convertVulkanResult(vk_result);
            }

        }

        vk_result = vkCreateFence(_bs_instance_->device, &fence_ci, NULL, &object->queue->_[i].fence);
        if (vk_result != VK_SUCCESS) {
            BS_WARN_VULKAN_ERROR("vkCreateFence", vk_result, "");
            return _bs_convertVulkanResult(vk_result);
        }

        vk_result = vkResetFences(_bs_instance_->device, 1, &object->queue->_[i].fence);
        if (vk_result != VK_SUCCESS) {
            BS_WARN_VULKAN_ERROR("vkResetFences", vk_result, "");
            return _bs_convertVulkanResult(vk_result);
        }
    }

    /*
    if (queue->head.id != 0) {
        const char* name = _bs_idName(queue->head.source_id, queue->head.id);
        _bs_string_builder_ = _bs_stringF(_bs_string_builder_, BS_PRINT_COLOR("%s", BS_PRINT_BLUE_BRIGHT), name);
        bsi_nameHandle(object->queue->queue, VK_OBJECT_TYPE_QUEUE, _bs_string_builder_->value);

        for (int i = 0; i < num_swaps; i++) {
            if (!(flags & BS_QUEUE_DONT_SIGNAL)) {
                _bs_string_builder_ = _bs_stringF(_bs_string_builder_, BS_PRINT_COLOR("semaphore (swap %d) %s", BS_PRINT_BLUE_BRIGHT), i, name);
                bsi_nameHandle(object->queue->_[i].semaphore, VK_OBJECT_TYPE_SEMAPHORE, _bs_string_builder_->value);
            }

            _bs_string_builder_ = _bs_stringF(_bs_string_builder_, BS_PRINT_COLOR("fence (swap %d) %s", BS_PRINT_BLUE_BRIGHT), i, name);
            bsi_nameHandle(object->queue->_[i].fence, VK_OBJECT_TYPE_FENCE, _bs_string_builder_->value);
        }
    }
    */

    const char* name = _bs_idName(object->head->source_id, object->head->id);
    _bs_nameQueue(object, name);

    return BS_RESULT_OK;
}

BSAPI void _bs_destroyQueue(bs_Queue* queue) {
    VkCommandPool command_pool = _bs_ensureCommandPool();

    for (int i = 0; i < queue->head.swaps_count; i++) {
        vkFreeCommandBuffers(_bs_instance_->device, command_pool, 1, &queue->_[i].command_buffer);
        if (queue->_[i].semaphore)
            vkDestroySemaphore(_bs_instance_->device, queue->_[i].semaphore, NULL);
    }

    _bs_resetObject(&queue->head, sizeof(bs_Queue));
}

bs_WaitSemaphore _bs_queueSemaphore(bs_Queue* queue, bs_PipelineStage stage) {
    int swap = _bs_queueSwap(queue);
    return (bs_WaitSemaphore) {
        .semaphore = queue->_[swap].semaphore,
        .stage = stage,
    };
}

bs_WaitSemaphore _bs_acquisitionSemaphore() {
    return (bs_WaitSemaphore) {
        .semaphore = _bs_scope_.context->_[_bs_scope_.context->frame].semaphore,
        .stage = BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    };
}

BSAPI void _bs_stallQueue(bs_Queue* queue) {
    vkQueueWaitIdle(queue->queue);
}

BSAPI void _bs_stallGPU() {
    vkDeviceWaitIdle(_bs_instance_->device);
}

BSAPI bs_Result _bs_stall(bs_Queue* queue) {
    VkResult result;

    int swap = _bs_queueSwap(queue);

    result = vkWaitForFences(_bs_instance_->device, 1, &queue->_[swap].fence, VK_TRUE, BS_TIMEOUT);
    if (result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkWaitForFences", result, "");
        return _bs_convertVulkanResult(result);
    }

    result = vkResetFences(_bs_instance_->device, 1, &queue->_[swap].fence);
    if (result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkResetFences", result, "");
        return _bs_convertVulkanResult(result);
    }

    return true;
}

BSAPI bs_Result _bs_poll(bs_Queue* queue) {
    VkResult result;

    int swap = _bs_queueSwap(queue);
    result = vkGetFenceStatus(_bs_instance_->device, queue->_[swap].fence);

    if (result == VK_SUCCESS) {
        result = vkResetFences(_bs_instance_->device, 1, &queue->_[swap].fence);

        if (result != VK_SUCCESS) {
            BS_WARN_VULKAN_ERROR("vkResetFences", result, "");
            return _bs_convertVulkanResult(result);
        }

        return BS_RESULT_OK;
    }
    //else if (res == VK_NOT_READY)
    return BS_RESULT_WAITING;
}

BSAPI bs_Result _val_bs_resetQueue(bs_Queue* queue) {
    return _bs_resetQueue(queue);
}

BSAPI bs_Result _bs_resetQueue(bs_Queue* queue) {
    VkResult result;

    int swap = _bs_queueSwap(queue);
    VkCommandBuffer command_buffer = queue->_[swap].command_buffer;
    VkCommandBufferBeginInfo ci = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = queue->flags & BS_QUEUE_SINGLE_TIMES_BIT ? VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT : 0,
    };

    result = vkResetCommandBuffer(command_buffer, 0);
    if (result != VK_SUCCESS) {
        return _bs_convertVulkanResult(result);
    }

    result = vkBeginCommandBuffer(command_buffer, &ci);
    if (result != VK_SUCCESS) {
        return _bs_convertVulkanResult(result);
    }

    return BS_RESULT_OK;
}

BSAPI bs_Result _val_bs_pushQueue(bs_Queue* queue, int wait_semaphore_count, bs_WaitSemaphore wait_stages[]) {
    return _bs_pushQueue(queue, wait_semaphore_count, wait_stages);
}

BSAPI bs_Result _bs_pushQueue(bs_Queue* queue, int wait_semaphores_count, bs_WaitSemaphore wait_semaphores[]) {
    VkResult result;

    int swap = _bs_queueSwap(queue);
    VkCommandBuffer command_buffer = queue->_[swap].command_buffer;

    result = vkEndCommandBuffer(command_buffer);
    if (result != VK_SUCCESS)
        return _bs_convertVulkanResult(result);

    VkPipelineStageFlags* stages = NULL;
    VkSemaphore* semaphores = NULL;

    if (wait_semaphores_count > 0) {
        stages = bs_alloca(wait_semaphores_count * sizeof(VkPipelineStageFlags));
        semaphores = bs_alloca(wait_semaphores_count * sizeof(VkSemaphore));

        for (int i = 0; i < wait_semaphores_count; i++) {
            semaphores[i] = wait_semaphores[i].semaphore;
            stages[i] = wait_semaphores[i].stage;
        }
    }

    VkSubmitInfo submit_i = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .signalSemaphoreCount = queue->_[swap].semaphore ? 1 : 0,
        .pSignalSemaphores = &queue->_[swap].semaphore,
        .commandBufferCount = 1,
        .pCommandBuffers = &command_buffer,
        .waitSemaphoreCount = wait_semaphores_count,
        .pWaitDstStageMask = stages,
        .pWaitSemaphores = semaphores
    };

    result = vkQueueSubmit(queue->queue, 1, &submit_i, queue->_[swap].fence);
    if (result != VK_SUCCESS)
        return _bs_convertVulkanResult(result);

    return BS_RESULT_OK;
}

BSAPI void _bs_enqueue(bs_Queue* queue, bs_Callback function) {
    if (_bs_resetQueue(queue) == BS_RESULT_OK) {
        if (function)
            function();
        _bs_pushQueue(queue, 0, NULL);
    }
}



  /*==============================================================================
   * Swapchain / Presentation
   *============================================================================*/

BSAPI bs_Image* _bs_swapchainImage() {
    return _bs_scope_.context->swapchain_image->image;
}

static void _bs_destroySwapchain() {
    bs_Image* swapchain_image = _bs_scope_.context->swapchain_image->image;

    for (int i = 0; i < _bs_scope_.context->frames_in_flight; i++) {
        vkDestroyImageView(_bs_instance_->device, swapchain_image->_[i].vk_image_view, NULL);
        swapchain_image->_[i].vk_image_view = 0;
    }

    vkDestroySwapchainKHR(_bs_instance_->device, _bs_scope_.context->swapchain, NULL);
    _bs_scope_.context->swapchain = 0;
}

typedef void(* bs_AutoResizeFunction)(bs_Object*);

/*
static void _bs_onAutoResizeImage(bs_Object* object) {
    bs_Image* image = object->image;

    if (image->context == _bs_scope_.context) {
        if (image == _bs_scope_.context->swapchain_image->image)
            return;

        bs_ivec2 resolution = bs_resolution(_bs_scope_.context);
        _bs_resizeImage(image, resolution, image->num_indices);
    }
}
*/
static void _bs_onAutoResizeRenderer(bs_Object* object) {
    bs_Renderer* renderer = object->renderer;

    if (renderer->context == _bs_scope_.context) {
        bs_ivec2 resolution = bs_resolution(_bs_scope_.context);

        for (int i = 0; i < renderer->outputs.count; i++) {
            bs_Output* output = _bs_fetchUnit(&renderer->outputs, i);
            bs_Image* image = output->image;

            if (image != _bs_scope_.context->swapchain_image->image)
                bs_resizeImage(image, resolution, image->num_indices);
        }

        _bs_resizeRenderer(renderer, resolution);
    }
}

static inline void _bs_autoResize(bs_ObjectType type, bs_AutoResizeFunction function) {
    bs_List* object_types = bs_objectSources();

    for (int i = 0; i < object_types->count; i++) {
        bs_ObjectSource* source = bs_fetchUnit(object_types, i);

        if (source->type == type) {
            for (int j = 0; j < source->ids_count; j++) {
                if (!source->ids[j].object)
                    continue;

                function(source->ids[j].object);
            }
        }
    }
}

static void _bs_resizeSwapchain() {
    bs_Context* ctx = _bs_scope_.context;

  //  bs_stallGPU();

    _bs_destroySwapchain();
    _bs_swapchain(_bs_scope_.context);

    _bs_scope_.context = ctx;
}

void _bs_resizeContext() {
    bs_logF("Resizing context \"%s\"", _bs_scope_.context->title);
    bs_ivec2 resolution = bs_resolution(_bs_scope_.context);
    _bs_resizeSwapchain();

    resolution = bs_resolution(_bs_scope_.context);

   /**
    Auto resize
    */
    //_bs_autoResize(BS_OBJECT_IMAGE, _bs_onAutoResizeImage);
    _bs_autoResize(BS_OBJECT_RENDERER, _bs_onAutoResizeRenderer);

    if (_bs_scope_.context->resize)
        _bs_scope_.context->resize(_bs_scope_.context);
}


// these functions should probably not be called by user
BSAPI void _bs_acquire() {
    if (_bs_scope_.context->image_acquired) return;

    VkResult result = vkAcquireNextImageKHR(
        _bs_instance_->device,
        _bs_scope_.context->swapchain,
        BS_U64_MAX,
        _bs_scope_.context->_[_bs_scope_.context->frame].semaphore,
        VK_NULL_HANDLE,
        &_bs_scope_.context->image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        _bs_resizeContext();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        BS_WARN_VULKAN_ERROR("vkAcquireNextImageKHR", result, "");
    }
}

/*
static void _bs_rebindImage(bs_Object object) {
    for (bs_U32 i = 0; i < BS_MAX_NUM_BIND_SETS; i++) {
        bs_BindSet* bind_set = _bs_queryBindSet(i);

        for (bs_U32 j = 0; j < bind_set->bindings.count; j++) {
            bs_Binding* binding = _bs_queryBinding(bind_set, j);
            if (!binding || binding->object.image) continue;
            if (binding->object.image == object.image)
                _bs_throwBasilisk(BSXI_INTERNAL | BSX_NOT_IMPLEMENTED); // todo
        }
    }
}

static void _bs_resizeImages() {
    for (int i = _bs_first(BS_IMAGE); i <= _bs_last(BS_IMAGE); i++) {
        bs_Object object = _bs_fetchNull(i);
        if (!object.image) continue;

        if (object.image->flags & BS_IMAGE_AUTO_RESIZE_BIT) {
            _bs_resizeImage(object.image, _bs_resolution(bs_scope()->context), object.image->num_indices);
            _bs_rebindImage(object);
        }
    }
}

static void _bs_resizeRenderers() {
    for (int i = _bs_first(BS_RENDERER); i <= _bs_last(BS_RENDERER); i++) {
        bs_Renderer* renderer = _bs_fetchNull(i)->renderer;
        if (renderer && renderer->flags & BS_RENDERER_AUTO_RESIZE_BIT)
            _bs_resizeRenderer(renderer, _bs_resolution(bs_scope()->context));
    }
}

void bsi_resizeObjects() {
    _bs_swapchain->resized = false;
    _bs_resizeSwapchain();
    _bs_resizeImages();
    _bs_pushDescriptors();
    _bs_resizeRenderers();

    if (_bs_instance->resize) _bs_instance->resize();
}
*/

BSAPI void _val_bs_present(bs_Queue* queue, bs_Queue* wait_queues[], int wait_queues_count) {
    for (int i = 0; i < wait_queues_count; i++) {
        BS_VALIDATE(wait_queues[i] != NULL,,);
        BS_VALIDATE(wait_queues[i]->head.type == BS_OBJECT_QUEUE,,);
    }

    _bs_present(queue, wait_queues, wait_queues_count);
}

BSAPI void _bs_present(bs_Queue* queue, bs_Queue* wait_queues[], int wait_queues_count) {
    VkSemaphore* wait_semaphores = NULL;

    if (wait_queues_count > 0) {
        wait_semaphores = bs_alloca(wait_queues_count * sizeof(VkSemaphore));

        for (int i = 0; i < wait_queues_count; i++) {
            bs_Queue* wait_queue = wait_queues[i];

            int swap = _bs_queueSwap(wait_queue);
            wait_semaphores[i] = wait_queue->_[swap].semaphore;
        }
    }

    VkPresentInfoKHR present_i = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = wait_queues_count,
        .pWaitSemaphores = wait_semaphores,
        .swapchainCount = 1,
        .pSwapchains = &_bs_scope_.context->swapchain,
        .pImageIndices = &_bs_scope_.context->image_index,
    };

    VkResult result = vkQueuePresentKHR(queue->queue, &present_i);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
        _bs_resizeContext();
    else if (result != VK_SUCCESS)
        _bs_warnN(BS_CONSTANT_STRING("Failed to present swapchain image"));

    _bs_scope_.context->frame = (_bs_scope_.context->frame + 1) % _bs_scope_.context->frames_in_flight;
    _bs_scope_.context->image_acquired = false;
}
