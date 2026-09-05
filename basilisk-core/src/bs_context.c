
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
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <uiribbon.h>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan.h>

#elif defined(__linux__)

#define VK_USE_PLATFORM_WAYLAND_KHR
#include <vulkan.h>

#endif

#include <vulkan.h>

#include <time.h>
#include <assert.h>

#include <basilisk-core.h>
#include <bs_internal.h>

static void _bs_createSurface() {
    VkResult result = VK_SUCCESS;

    #ifdef _WIN32
    if (_bs_instance_->extensions.surface_type == BS_SURFACE_TYPE_WIN32) {
        VkWin32SurfaceCreateInfoKHR ci = {
            .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
            .hinstance = GetModuleHandle(0),
            .hwnd = _bs_scope_.context->hwnd,
        };

        result = vkCreateWin32SurfaceKHR(_bs_instance_->instance, &ci, NULL, &_bs_scope_.context->surface);
    }
    #elif defined(__linux__)
    if (_bs_instance_->extensions.surface_type == BS_SURFACE_TYPE_WAYLAND) {
        VkWaylandSurfaceCreateInfoKHR ci = {
            .sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
        };

        result = vkCreateWaylandSurfaceKHR(_bs_instance_->instance, &ci, NULL, &_bs_scope_.context->surface);
    }
    #else
    if (0) { }
    #endif
    else if (_bs_instance_->extensions.surface_type == BS_SURFACE_TYPE_HEADLESS) {
        VkHeadlessSurfaceCreateInfoEXT ci = {
            .sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT,
        };

        result = vkCreateHeadlessSurfaceEXT(_bs_instance_->instance, &ci, NULL, &_bs_scope_.context->surface);
    }
    else {
        _bs_warnF("Surface type %d is not supported", _bs_instance_->extensions.surface_type);
    }

    if (result != VK_SUCCESS) {
        _bs_warnF("Failed to create surface for window \"%s\" (Vulkan result = %d)", _bs_scope_.context->title, result);
    }
}

BSAPI void _bs_queryProcedures(bs_Procedure* procedures, int count, void* dll_handle, void* dst) {
    unsigned char* destination = dst;
#define BS_STRING_GEN_2(TYPE, FUNC, ...) { .size = sizeof(TYPE), .func = #FUNC, __VA_OPT__(.is_required = __VA_ARGS__) },
#ifdef _WIN32
    for (int i = 0; i < count; i++) {
        void* data = dll_handle == 0 ?
            (void*)vkGetDeviceProcAddr(_bs_instance_->device, procedures[i].func) :
            (void*)GetProcAddress(dll_handle, procedures[i].func);

        if (data)
            memcpy(destination, &data, procedures[i].size);
        else if (procedures[i].is_required)
            _bs_warnF("Failed to query procedure \"%s\"", procedures[i].func);

        destination += procedures[i].size;
    }
#else
    bs_log("_bs_queryProcedures not implemented");
#endif
}



  /*==============================================================================
   * Physical Device
   *============================================================================*/

static inline const char* _bs_physicalDeviceTypeName(VkPhysicalDeviceType type) {
    switch (type) {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER: return "Other";
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return "Integrated";
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return "Discrete";
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return "Virtual";
    case VK_PHYSICAL_DEVICE_TYPE_CPU: return "CPU";
    default: return "Unknown";
    }
}

static void _bs_logPhysicalDeviceInfo(bs_PhysicalDevice* physical_device) {
    _bs_logF("Device \"%s\":\n", physical_device->name);
    _bs_logF("    API version: %d.%d.%d\n",
        VK_API_VERSION_MAJOR(physical_device->api_version),
        VK_API_VERSION_MINOR(physical_device->api_version),
        VK_API_VERSION_PATCH(physical_device->api_version)
    );
    _bs_logF("    Type: %s\n", _bs_physicalDeviceTypeName(physical_device->type));

    for (int i = 0; i < physical_device->queue_families.count; i++) {
        bs_QueueFamily* family = _bs_fetchUnit(&physical_device->queue_families, i);
        _bs_logF("    Family %d queues count: %d ", i, family->queue_count);
        _bs_logF("Graphics %s, Compute %s, Transfer %s, Sparse binding %s\n",
            (family->queue_flags & VK_QUEUE_GRAPHICS_BIT) ? "[X]" : "[ ]",
            (family->queue_flags & VK_QUEUE_COMPUTE_BIT) ? "[X]" : "[ ]",
            (family->queue_flags & VK_QUEUE_TRANSFER_BIT) ? "[X]" : "[ ]",
            (family->queue_flags & VK_QUEUE_SPARSE_BINDING_BIT) ? "[X]" : "[ ]"
        );
    }

    for (int i = 0; i < physical_device->surface_formats.count; i++) {
        bs_SurfaceFormat* surface_format = _bs_fetchUnit(&physical_device->surface_formats, i);

        _bs_logF("    Format %s color space %s\n",
            bs_serializeFormat(surface_format->format),
            bs_serializeColorSpace(surface_format->color_space)
        );
    }
}

static void _bs_readQueueFamilies(bs_PhysicalDevice* physical_device, VkSurfaceKHR surface) {
    VkResult result;

    bs_U32 families_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device->vk_device, &families_count, NULL);
    VkQueueFamilyProperties* queue_families = bs_alloca(families_count * sizeof(VkQueueFamilyProperties));

    physical_device->queue_families = _bs_list(sizeof(VkQueueFamilyProperties), 0);
    bs_ensureSize(&physical_device->queue_families, families_count);

    vkGetPhysicalDeviceQueueFamilyProperties(physical_device->vk_device, &families_count, queue_families);

    int actual_count = 0;
    for (bs_U32 i = 0; i < families_count; i++) {
        bs_QueueFamily* queue_family = _bs_pushBack(&physical_device->queue_families, NULL);

        VkBool32 supports_present = false;
        if (surface != VK_NULL_HANDLE) {
            result = vkGetPhysicalDeviceSurfaceSupportKHR(physical_device->vk_device, i, surface, &supports_present);
            if (result != VK_SUCCESS) {
                BS_CRITICAL_VULKAN_ERROR("vkGetPhysicalDeviceSurfaceSupportKHR", result, "");
                continue;
            }
        }

        queue_family->index = i;
        queue_family->queue_flags = queue_families[i].queueFlags;
        queue_family->queue_count = queue_families[i].queueCount;
        queue_family->supports_present = supports_present;

        if (supports_present)
            physical_device->supports_present = true;
    }
}

static void _bs_readSurfaceFormats(bs_PhysicalDevice* physical_device, VkSurfaceKHR surface) {
    VkResult result;

    bs_U32 surface_formats_count;
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device->vk_device, surface, &surface_formats_count, NULL);
    if (result != VK_SUCCESS) {
        BS_CRITICAL_VULKAN_ERROR("vkGetPhysicalDeviceSurfaceFormatsKHR", result, "");
        return;
    }

    if (surface_formats_count == 0)
        return;

    VkSurfaceFormatKHR* formats = bs_alloca(surface_formats_count * sizeof(VkSurfaceFormatKHR));
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device->vk_device, surface, &surface_formats_count, formats);
    if (result != VK_SUCCESS) {
        BS_CRITICAL_VULKAN_ERROR("vkGetPhysicalDeviceSurfaceFormatsKHR", result, "");
        return;
    }

    physical_device->surface_formats = bs_list(sizeof(VkSurfaceFormatKHR), 0);
    bs_ensureSize(&physical_device->surface_formats, surface_formats_count);

    for (int i = 0; i < surface_formats_count; i++) {
        bs_SurfaceFormat* surface_format = _bs_pushBack(&physical_device->surface_formats, NULL);
        surface_format->color_space = (bs_ColorSpace)formats[i].colorSpace;
        surface_format->format = (bs_Format)formats[i].format;
    }
}

// static void _bs_readMemoryTypes(bs_PhysicalDevice* physical_device) {
//     VkPhysicalDeviceMemoryProperties props;
//     vkGetPhysicalDeviceMemoryProperties(physical_device->vk_device, &props);
//
// }

static void _bs_preparePhysicalDevice(bs_Context* context) {
    VkResult result;

    bs_U32 num_devices = 0;
    vkEnumeratePhysicalDevices(_bs_instance_->instance, &num_devices, NULL);
    if (num_devices == 0) {
        _bs_criticalN(BS_CONSTANT_STRING("No GPU with Vulkan support was found"));
        return;
    }

    VkPhysicalDevice* devices = bs_alloca(num_devices * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(_bs_instance_->instance, &num_devices, devices);

    _bs_ensureSize(&_bs_physical_devices_, num_devices);

    assert(BS_MAX_PHYSICAL_DEVICE_NAME_SIZE == VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);

    VkSurfaceKHR surface = context ? context->surface : VK_NULL_HANDLE;

    int chosen = 0;
    for(int i = 0; i < num_devices; i++) {
        bs_PhysicalDevice* physical_device = _bs_pushBack(&_bs_physical_devices_, NULL);
        VkPhysicalDevice device = devices[i];

        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(device, &props);

        physical_device->vk_device = device;
        physical_device->type = props.deviceType;
        physical_device->api_version = props.apiVersion;
        memcpy(physical_device->name, props.deviceName, BS_MAX_PHYSICAL_DEVICE_NAME_SIZE);

        _bs_readQueueFamilies(physical_device, surface);
        _bs_readSurfaceFormats(physical_device, surface);

       // VkSurfaceCapabilitiesKHR capabilities;
       // vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _bs_scope_.context->surface, &capabilities);

    }

    for (int i = 0; i < _bs_physical_devices_.count; i++) {
        bs_PhysicalDevice* physical_device = _bs_fetchUnit(&_bs_physical_devices_, i);
        _bs_logPhysicalDeviceInfo(physical_device);
    }
}

static void _bs_queryPhysicalDevice(VkQueueFlags required_flags, bool supports_present, bs_PhysicalDevice** out_device, bs_QueueFamily** out_queue_family) {
    *out_device = NULL;
    *out_queue_family = NULL;

    for (int i = 0; i < _bs_physical_devices_.count; i++) {
        bs_PhysicalDevice* physical_device = _bs_fetchUnit(&_bs_physical_devices_, i);

        for (int j = 0; j < physical_device->queue_families.count; j++) {
            bs_QueueFamily* queue_family = _bs_fetchUnit(&physical_device->queue_families, j);

            if (queue_family->queue_flags & required_flags && queue_family->supports_present == supports_present) {
                *out_queue_family = queue_family;
                *out_device = physical_device;
                _bs_infoF("Physical device \"%s\", queue family %d was picked", physical_device->name, j);
                return;
            }
        }
    }

    _bs_criticalN(BS_CONSTANT_STRING("No GPU with graphics and present support was found"));
}

static void _bs_prepareLogicalDevice(bs_PhysicalDevice* physical_device) {
    VkResult vk_result;

    // todo shouldnt this all be in the physical device creation
   /**
    Features & Extensions
    */
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR rt_pipeline_features = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR, .pNext = NULL };
    VkPhysicalDevice16BitStorageFeatures _16_bit_storage_features = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES, .pNext = NULL };
    VkPhysicalDeviceDynamicRenderingFeaturesKHR dynamic_rendering_features = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES_KHR, .pNext = &_16_bit_storage_features };
    //VkPhysicalDeviceAccelerationStructureFeaturesKHR as_features = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR, .pNext = &dynamic_rendering_features };
    //VkPhysicalDeviceVulkan11Features features11 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES, .pNext = &as_features };
    VkPhysicalDeviceVulkan12Features features12 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, .pNext = &dynamic_rendering_features };
    VkPhysicalDeviceFeatures2 features2 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &features12 };
    VkPhysicalDeviceFeatures* features = &features2.features;
    vkGetPhysicalDeviceFeatures2(physical_device->vk_device, &features2);

   /**
    NVIDIA Aftermath
    */

    VkDeviceDiagnosticsConfigCreateInfoNV aftermath_ci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV,
        .flags =
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV |
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV |
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV |
            VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_ERROR_REPORTING_BIT_NV,
    };

    if (!features->depthClamp) _bs_warnF("Depth clamp is not supported");
    if (!features->fillModeNonSolid) _bs_warnF("Fill mode non solid is not supported");
    if (!features->independentBlend) _bs_warnF("Independent blend is not supported");
    if (!features->shaderInt64) _bs_warnF("64 bit integers are not supported");
    if (!features->robustBufferAccess) _bs_warnF("Robust buffer access is not supported");
    _bs_features_.independent_blend = features->independentBlend;

    const char* extensions[] = {
        "VK_KHR_swapchain",
        "VK_KHR_dynamic_rendering",
        //
        "VK_KHR_shader_non_semantic_info",
        "VK_KHR_ray_tracing_pipeline",
        "VK_KHR_acceleration_structure",
        "VK_KHR_deferred_host_operations",
        "VK_EXT_descriptor_indexing",
       // "VK_KHR_get_physical_device_properties2",
        "VK_KHR_shader_float_controls",
        "VK_KHR_spirv_1_4",
#ifdef _DEBUG
      //  "VK_NV_device_diagnostics_config"
      //  "VK_NV_ray_tracing_validation",
#endif
    };
    int extensions_count = sizeof(extensions) / sizeof(const char*);
    bool supported_extensions[sizeof(extensions) / sizeof(const char*)] = { 0 };

    bs_U32 total_extensions_count = 0;
    vk_result = vkEnumerateDeviceExtensionProperties(physical_device->vk_device, NULL, &total_extensions_count, NULL);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkEnumerateDeviceExtensionProperties", vk_result, "");
    }

    VkExtensionProperties* props = _bs_calloc(total_extensions_count, sizeof(VkExtensionProperties));
    vk_result = vkEnumerateDeviceExtensionProperties(physical_device->vk_device, NULL, &total_extensions_count, props);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkEnumerateDeviceExtensionProperties", vk_result, "");
    }

    for (int i = 0; i < extensions_count; i++) {
        for (int j = 0; j < total_extensions_count; j++) {
            if (strcmp(props[j].extensionName, extensions[i]) == 0) {
                supported_extensions[i] = true;
                break;
            }
        }
    }

    //_bs_features.ray_tracing =
    //    as_features.accelerationStructure;

    for (int i = 0; i < extensions_count; i++) {
        if (!supported_extensions[i]) {
            if (_bs_features_.ray_tracing && i >= 1 && i <= 8) // todo something about this
                _bs_features_.ray_tracing = false;

            _bs_warnF("Extension \"%s\" is not supported", extensions[i]);
        }
    }

    _bs_free(props);

   /**
    Properties
    */
    VkPhysicalDeviceAccelerationStructurePropertiesKHR accel_struct_properties = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR,
    };

    VkPhysicalDeviceRayTracingPipelinePropertiesKHR ray_tracing_pipeline_properties = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR,
        .pNext = &accel_struct_properties
    };

    VkPhysicalDeviceProperties2 device_properties = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
       // .pNext = &ray_tracing_pipeline_properties
    };

    vkGetPhysicalDeviceProperties2(physical_device->vk_device, &device_properties);

    _bs_props_.shader_group_handle_size = ray_tracing_pipeline_properties.shaderGroupHandleSize;
    _bs_props_.shader_group_base_alignment = ray_tracing_pipeline_properties.shaderGroupBaseAlignment;
    _bs_props_.min_acceleration_structure_scratch_offset_alignment = accel_struct_properties.minAccelerationStructureScratchOffsetAlignment;

   /**
    Creation
    */
    if (_bs_config_.queues_count == 0)
        _bs_config_.queues_count = 1;

    if (_bs_config_.queues_count > _bs_instance_->queue_family->queue_count) {
        bs_warnF("Requested %d queues, but queue family %d only has %d", _bs_config_.queues_count, _bs_instance_->queue_family->index, _bs_instance_->queue_family->queue_count);
        _bs_config_.queues_count = _bs_instance_->queue_family->queue_count;
    }

    float* queue_priorities = bs_alloca(_bs_config_.queues_count * sizeof(float));
    for (int i = 0; i < _bs_config_.queues_count; i++)
        queue_priorities[i] = 1.0;

    VkDeviceQueueCreateInfo queue_ci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = _bs_instance_->queue_family->index,
        .queueCount = _bs_config_.queues_count,
        .pQueuePriorities = queue_priorities,
    };

    VkDeviceCreateInfo ci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &features2,
        .pQueueCreateInfos = &queue_ci,
        .queueCreateInfoCount = 1,
      //  .pEnabledFeatures = features,
        .enabledExtensionCount = extensions_count,
        .ppEnabledExtensionNames = extensions,
        //.ppEnabledLayerNames = validation_layers,
        //.enabledLayerCount = _bs_args_.use_validation_layers ? sizeof(validation_layers) / sizeof(const char*) : 0,
    };

    vk_result = vkCreateDevice(physical_device->vk_device, &ci, NULL, &_bs_instance_->device);
    if (vk_result != VK_SUCCESS) {
        BS_CRITICAL_VULKAN_ERROR("vkCreateDevice", vk_result, "");
    }

    //_bs_nameHandlef((bs_U64)_bs_instance->_.graphics_queue, VK_OBJECT_TYPE_QUEUE, "graphics queue");
    //_bs_nameHandlef((bs_U64)_bs_instance->_.compute_queue, VK_OBJECT_TYPE_QUEUE, "compute queue");
}



  /*==============================================================================
   * Swapchain
   *============================================================================*/

static void _bs_querySwapchainFormat(VkFormat candidates[], int candidates_count) {

    for (int i = 0; i < candidates_count; i++) {
        VkFormat candidate = candidates[i];

        for (int j = 0; j < _bs_instance_->physical_device->surface_formats.count; j++) {
            bs_SurfaceFormat* surface_format = bs_fetchUnit(&_bs_instance_->physical_device->surface_formats, j);

            if ((bs_Format)candidate == surface_format->format) {
                _bs_scope_.context->surface_format = *surface_format;
                return;
            }
        }
    }

    _bs_criticalN(BS_CONSTANT_STRING("Failed to query swapchain surface format"));
}

static void _bs_querySwapchainMode(VkPresentModeKHR candidates[], int candidates_count) {
    bs_U32 num_modes = 0;
    VkPresentModeKHR result = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(_bs_instance_->physical_device->vk_device, _bs_scope_.context->surface, &num_modes, NULL);
    VkPresentModeKHR* modes = bs_alloca(num_modes * sizeof(VkPresentModeKHR));
    vkGetPhysicalDeviceSurfacePresentModesKHR(_bs_instance_->physical_device->vk_device, _bs_scope_.context->surface, &num_modes, modes);

    for (int i = 0; i < candidates_count; i++) {
        VkPresentModeKHR candidate = candidates[i];

        for (int j = 0; j < num_modes; j++) {
            VkPresentModeKHR mode = modes[j];
            if (candidate == mode) {
                _bs_scope_.context->present_mode = (bs_PresentMode)mode;
                return;
            }
        }
    }

    _bs_criticalN(BS_CONSTANT_STRING("Failed to query swapchain present mode"));
}

static void _bs_prepareSwapchain() {
    VkResult result;

    const VkPresentModeKHR modes[] = {
        VK_PRESENT_MODE_FIFO_KHR,
        VK_PRESENT_MODE_IMMEDIATE_KHR,
        VK_PRESENT_MODE_MAILBOX_KHR,
        VK_PRESENT_MODE_FIFO_RELAXED_KHR,

        VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
        VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR,
        VK_PRESENT_MODE_FIFO_LATEST_READY_KHR,
        VK_PRESENT_MODE_FIFO_LATEST_READY_EXT,
    };

    const VkFormat formats[] = {
        VK_FORMAT_R8G8B8A8_SRGB,
        VK_FORMAT_B8G8R8A8_SRGB,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8A8_UNORM,
    };

    _bs_querySwapchainMode(modes, sizeof(modes) / sizeof(*modes));
    _bs_querySwapchainFormat(formats, sizeof(formats) / sizeof(*formats));

    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_bs_instance_->physical_device->vk_device, _bs_scope_.context->surface, &capabilities);

    const bool same_family = true; // TODO: this shouldn't always be true

    _bs_scope_.context->swapchain_image = _bs_scope_.context->swapchain_image ? _bs_scope_.context->swapchain_image : NULL;

    bs_ivec2 resolution = { capabilities.minImageExtent.width, capabilities.minImageExtent.height };
    bs_Image image = {
        .head = {
            .type = BS_OBJECT_IMAGE
        },
        .flags = BS_IMAGE_SWAPS_BIT,
        .format = _bs_scope_.context->surface_format.format,
        .dim = resolution,
    };

    const int frames_in_flight_target = 2;
    const int frames_in_flight_max = 3;

    _bs_scope_.context->frames_in_flight = bs_clamp(frames_in_flight_target, capabilities.minImageCount, frames_in_flight_max);

    _bs_instance_->max_frames_in_flight = BS_MAX(_bs_instance_->max_frames_in_flight, _bs_scope_.context->frames_in_flight);

    VkSwapchainCreateInfoKHR swapchain_ci = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = _bs_scope_.context->surface,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .minImageCount = _bs_scope_.context->frames_in_flight,
        .imageExtent = { resolution.x, resolution.y },
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = same_family ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,
        .queueFamilyIndexCount = same_family ? 0 : 2,
        .pQueueFamilyIndices = same_family ? NULL : NULL,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .clipped = VK_TRUE,
        .preTransform = capabilities.currentTransform,
        .presentMode = (VkPresentModeKHR)_bs_scope_.context->present_mode,
        .imageFormat = (VkFormat)_bs_scope_.context->surface_format.format,
        .imageColorSpace = (VkColorSpaceKHR)_bs_scope_.context->surface_format.color_space,
    };

    result = vkCreateSwapchainKHR(_bs_instance_->device, &swapchain_ci, NULL, &_bs_scope_.context->swapchain);
    if (result != VK_SUCCESS) {
        _bs_warnF("Failed to create swapchain for window \"%s\"", _bs_scope_.context->title);
        return;
    }

    bsi_nameHandle((bs_U64)_bs_scope_.context->swapchain, VK_OBJECT_TYPE_SWAPCHAIN_KHR, _bs_scope_.context->title);

    /**
     Swapchain images
     */
    VkImage images[3];
    vkGetSwapchainImagesKHR(_bs_instance_->device, _bs_scope_.context->swapchain, &_bs_scope_.context->frames_in_flight, images);
    _bs_infoF("Swapchain\n  Format: %d\n  Mode: %d\n  Images: %d", swapchain_ci.imageFormat, swapchain_ci.presentMode, _bs_scope_.context->frames_in_flight);

    if (_bs_scope_.context->swapchain_image == NULL)
        _bs_scope_.context->swapchain_image = BS_OBJECT(bs_Image, -1, 0, _bs_scope_.context->frames_in_flight, BS_OBJECT_HAS_SWAPS_BIT, BS_OBJECT_IMAGE);

    memcpy(_bs_scope_.context->swapchain_image->image, &image, sizeof(image));

    /**
     Swapchain image views
     */
    for (int i = 0; i < _bs_scope_.context->frames_in_flight; i++) {
        _bs_scope_.context->swapchain_image->image->_[i].vk_image = images[i];

        VkImageViewCreateInfo image_view_ci = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = _bs_scope_.context->swapchain_image->image->_[i].vk_image,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = (VkFormat)_bs_scope_.context->surface_format.format,
            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.levelCount = 1,
            .subresourceRange.layerCount = 1,
        };

        result = vkCreateImageView(_bs_instance_->device, &image_view_ci, NULL, &_bs_scope_.context->swapchain_image->image->_[i].vk_image_view);
        if (result != VK_SUCCESS) {
            _bs_warnF("Failed to create swapchain image view for window \"%s\"", _bs_scope_.context->title);
        }
    }

    /**
     Swapchain semaphores
     */
    VkSemaphoreCreateInfo semaphore_ci = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    for (int i = 0; i < _bs_scope_.context->frames_in_flight; i++) {
        result = vkCreateSemaphore(_bs_instance_->device, &semaphore_ci, NULL, &_bs_scope_.context->_[i].semaphore);
        if (result != VK_SUCCESS) {
            _bs_warnF("Failed to create swapchain semaphore for window \"%s\"", _bs_scope_.context->title);
        }
    }
}



  /*==============================================================================
   * Window
   *============================================================================*/

BSAPI void _bs_titleWindowN(bs_Context* context, char* name, int name_length) {
    context->title = name; // todo
}

BSAPI void _bs_setCursor(bs_CursorIcon icon) {
	_bs_warnF("_bs_setCursor has not been implemented yet");
	/*
	if (_bs_scope_.context->cursor_icons[icon].handle == NULL)
		_bs_scope_.context->cursor_icons[icon].handle = LoadCursor(NULL, _bs_wnd.cursor_icons[icon].id);

	if (_bs_wnd.cursor_icon == icon)
		return;

	_bs_wnd.cursor_icon = icon;
	*/
}

void _bs_resizeContext();

BSAPI void _bs_resizeWindow(bs_Context* context, bs_U32 width, bs_U32 height) {
#ifdef _WIN32
    RECT rect;
    GetWindowRect(context->hwnd, &rect);

    SetWindowPos(
        context->hwnd,
        NULL,
        rect.left,
        rect.top,
        width,
        height,
        SWP_FRAMECHANGED | SWP_NOACTIVATE
    );

    bs_Context* previous_context = _bs_scope_.context;
    _bs_scope_.context = context;
    _bs_resizeContext();
    _bs_scope_.context = previous_context;
#else
    _bs_warnF("_bs_resizeWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_maximizeWindow(bs_Context* context) {
#ifdef _WIN32
	ShowWindow(context->hwnd, SW_SHOWMAXIMIZED);
#else
	_bs_warnF("_bs_maximizeWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_minimizeWindow(bs_Context* context) {
#ifdef _WIN32
	ShowWindow(context->hwnd, SW_SHOWMINIMIZED);
#else
	_bs_warnF("_bs_minimizeWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_hideWindow(bs_Context* context) {
#ifdef _WIN32
    if (context->hidden)
        return;

    context->hidden = true;
    ShowWindow(context->hwnd, SW_HIDE);
    bs_logF("Hiding window \"%s\"", context->title);
#else
    _bs_warnF("_bs_hideWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_showWindow(bs_Context* context) {
#ifdef _WIN32
    if (!context->hidden)
        return;

    context->hidden = false;
    if (context->window_type == BS_WINDOW_MENU)
        ShowWindow(context->hwnd, SW_SHOWNOACTIVATE);
    else
        ShowWindow(context->hwnd, SW_SHOW);

    bs_logF("Showing window \"%s\"", context->title);
#else
    _bs_warnF("_bs_showWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_exit() {
    _bs_instance_->alive = false;
}

BSAPI void _bs_pause() {
    _bs_instance_->paused = !_bs_instance_->paused;
}

BSAPI void _val_bs_advance() {
    BS_VALIDATE(_bs_instance_->paused == true,,);
    _bs_advance();
}

BSAPI void _bs_advance() {
    _bs_instance_->advance = true;
}

BSAPI double _bs_deltaTime() {
//#ifdef _DEBUG
//	if (_bs_wnd.delta_time == 0.0)
//		_bs_throwBasiliskF(BSX_GENERAL, "Delta time is 0.0"); // some bug is ruining my life
//#endif
	return _bs_instance_->delta_time;
}

BSAPI double _bs_elapsedTime() {
    return _bs_instance_->time;
}

BSAPI bs_ivec2 _val_bs_resolution(bs_Context* context) {
    BS_VALIDATE(context->swapchain_image != NULL, BS_IV2(0, 0),);

    return _bs_resolution(context);
}

BSAPI bs_ivec2 _bs_resolution(bs_Context* context) {
    return context->swapchain_image->image->dim;
}

BSAPI bs_vec2 _bs_windowCursorPosition(bs_Context* context) {
    bs_vec2 p = context->cursor;
    p.y = context->swapchain_image->image->dim.y - p.y;

    return p;

    bs_vec2 dim = { context->swapchain_image->image->dim.x, context->swapchain_image->image->dim.y };
    bs_vec2 pos;

    bs_v2Div(&context->cursor, &dim, &pos);
	return BS_V2(pos.x, 1.0 - pos.y);
}

BSAPI bs_ivec2 _bs_windowPosition(bs_Context* context) {
#ifdef _WIN32
	RECT rectangle = { 0 };
	GetWindowRect(context->hwnd, &rectangle);

	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	return (bs_ivec2) {
		rectangle.left,
		rectangle.bottom
	};

#elif defined(__linux__)
    return (bs_ivec2) {
        .x = 0,
        .y = 0
    };

#elif defined(__APPLE__)
    _bs_warnF("_bs_windowPosition has not been implemented for macOS yet");
    return (bs_ivec2) { 0, 0 };
#else
    return (bs_ivec2) { 0, 0 };
#endif
}



  /*==============================================================================
   * Inputs
   *============================================================================*/

const bool separate_message_thread = true; // temp

#ifdef _WIN32
static inline void bs_setBit(long A[], unsigned int k) {
    InterlockedOr(&A[k / 32U], 1L << (k % 32U));
}

static inline void bs_clearBit(long A[], unsigned int k) {
    InterlockedAnd(&A[k / 32U], ~(1L << (k % 32U)));
}

static inline int bs_getBit(long A[], unsigned int k) {
    long value = InterlockedCompareExchange(&A[k / 32U], 0, 0);
    return (value & (1L << (k % 32U))) != 0;
}

static inline int bs_testBit(long A[], unsigned int k) {
    long value = InterlockedCompareExchange(&A[k / 32U], 0, 0);
    return (value & (1L << (k % 32U))) != 0;
}

#define bs_atomicExchange(object, desired) InterlockedCompareExchange(object, desired)

#elif defined(__linux__)
#include <stdatomic.h>
static inline void bs_setBit(bs_U32 A[], unsigned int k) {
    atomic_fetch_or((_Atomic bs_U32 *)&A[k / 32U], 1L << (k % 32U));
}

static inline void bs_clearBit(bs_U32 A[], unsigned int k) {
    atomic_fetch_and((_Atomic bs_U32 *)&A[k / 32U], ~(1L << (k % 32U)));
}

static inline int bs_getBit(bs_U32 A[], unsigned int k) {
    bs_U32 value = atomic_load((_Atomic bs_U32 *)&A[k / 32U]);
    return (value & (1L << (k % 32U))) != 0;
}

static inline int bs_testBit(bs_U32 A[], unsigned int k) {
    bs_U32 value = atomic_load((_Atomic bs_U32 *)&A[k / 32U]);
    return (value & (1L << (k % 32U))) != 0;
}

#define bs_atomicExchange(object, desired) atomic_exchange(object, desired)

#endif

/*
static inline void bs_setBit(bs_I16 A[], unsigned int k) {
    InterlockedOr16(&A[k / 16U], (bs_I16)(1U << (k % 16U)));
}

static inline void bs_clearBit(bs_I16 A[], unsigned int k) {
    InterlockedAnd16(&A[k / 16U], (bs_I16)~(1U << (k % 16U)));
}

static inline int bs_getBit(bs_I16 A[], unsigned int k) {
    bs_I16 value = InterlockedCompareExchange16(&A[k / 16U], 0, 0);

    return (value & (bs_I16)(1U << (k % 16U))) != 0;
}

static inline int bs_testBit(bs_I16 A[], unsigned int k) {
    bs_I16 value = InterlockedCompareExchange16(&A[k / 16U], 0, 0);

    return (value & (bs_I16)(1U << (k % 16U))) != 0;
}
*/


BSAPI bs_vec2 _bs_screenCursorPosition() {
	return _bs_instance_->screen_cursor;
}

BSAPI bool _bs_contextKeyHeld(bs_Context* context, bs_U32 code) {
    return false;
}

BSAPI bool _bs_contextInputDown(bs_Context* context, bs_U32 code) {
    return bs_getBit(context->io.inputs_down, code);
}

BSAPI bool _bs_contextInputDownOnce(bs_Context* context, bs_U32 code) {
    return bs_getBit(context->io.inputs_down_once, code);
}

BSAPI bool _bs_contextInputUpOnce(bs_Context* context, bs_U32 code) {
    return bs_getBit(context->io.inputs_up_once, code);
}

BSAPI bool _bs_contextCharDown(bs_Context* context, unsigned char code) {
    return false;
}

BSAPI bool _bs_contextCharDownOnce(bs_Context* context, unsigned char code) {
    return false;
}

BSAPI bool _bs_contextCharUpOnce(bs_Context* context, unsigned char code) {
    return false;
}

BSAPI bool _bs_inputHeld(bs_U32 code) { return _bs_contextKeyHeld(_bs_scope_.context, code); }
BSAPI bool _bs_inputDown(bs_U32 code) { return _bs_contextInputDown(_bs_scope_.context, code); }
BSAPI bool _bs_inputDownOnce(bs_U32 code) { return _bs_contextInputDownOnce(_bs_scope_.context, code); }
BSAPI bool _bs_inputUpOnce(bs_U32 code) { return _bs_contextInputUpOnce(_bs_scope_.context, code); }

BSAPI bool _bs_charDown(unsigned char code) { return _bs_contextCharDown(_bs_scope_.context, code); }
BSAPI bool _bs_charDownOnce(unsigned char code) { return _bs_contextCharDownOnce(_bs_scope_.context, code); }
BSAPI bool _bs_charUpOnce(unsigned char code) { return _bs_contextCharUpOnce(_bs_scope_.context, code); }

BSAPI int _bs_scroll() {
	return _bs_scope_.context->io.scroll;
}

BSAPI bool _bs_inFixedTick() {
    return _bs_instance_->in_fixed;
}

BSAPI void _bs_setTargetFramerate(int fps) {
    _bs_instance_->target_frame_time = 1.0 / (double)fps;
}

 /**
  Ugly implementation
  */
static _Thread_local bool _hide_menu_windows_ = false;

static void _bs_hideMenuWindows(bs_List* contexts) {
    for (int i = 0; i < contexts->count; i++) {
        bs_Context* ctx = *(bs_Context**)_bs_fetchUnit(contexts, i);
        if (ctx->window_type == BS_WINDOW_MENU) {
            _bs_hideWindow(ctx);
        }
    }

    _hide_menu_windows_ = false;
}

BSAPI void _bs_tickContext(bs_Context* context, bs_ContextTickFunction tick) {
   // if (bs_getBit(context->io.keys, BS_KEY_ALT) && bs_getBit(context->io.keys, BS_KEY_F4))
   //     _bs_exit();

    #ifdef _WIN32
    context->active = context->hwnd == GetForegroundWindow();

    POINT p = { _bs_instance_->screen_cursor.x, _bs_instance_->screen_cursor.y };
    if (ScreenToClient(context->hwnd, &p))
        context->cursor = BS_V2(p.x, p.y);
    #endif

    if (separate_message_thread) {
        for (int i = 0; i < BS_KEY_BYTES_COUNT; i++) {
            context->io.inputs_up_once[i] = bs_atomicExchange(&context->io.input_up_events[i], 0);
        }

        for (int i = 0; i < BS_KEY_BYTES_COUNT; i++) {
            context->io.inputs_down_last[i] = context->io.inputs_down[i];
            context->io.inputs_down_once[i] = bs_atomicExchange(&context->io.input_down_events[i], 0);
        }

    } else {
        for (int i = 0; i < BS_KEY_BYTES_COUNT; i++) {
            context->io.inputs_up_once[i] = context->io.input_up_events[i];
            context->io.input_up_events[i] = 0;
        }

        for (int i = 0; i < BS_KEY_BYTES_COUNT; i++) {
            context->io.inputs_down_last[i] = context->io.inputs_down[i];
            context->io.inputs_down_once[i] = context->io.input_down_events[i];
            context->io.input_down_events[i] = 0;
        }
    }

    for (int i = 0; i < BS_KEY_BYTES_COUNT; i++) {
        context->io.inputs_down[i] |= context->io.inputs_down_once[i];
    }
    //context->io.scroll = 0;

    if (tick)
        tick(context);

    for (int i = 0; i < BS_KEY_BYTES_COUNT; i++) {
        context->io.inputs_down[i] &= ~context->io.inputs_up_once[i];
    }

    _bs_instance_->time_old = _bs_instance_->time;
}

static void _bs_renderTick(bs_Callback fixed_tick) {
    //  _bs_checkTimer(&_bs_instance_->timer);
    double frame_start = _bs_instance_->timer.seconds;

    if (fixed_tick) {
        _bs_instance_->in_fixed = true;
        for (int i = 0; _bs_instance_->advance || (_bs_instance_->elapsed_time < _bs_instance_->time && i < 200 && !_bs_instance_->paused); i++) {
            _bs_instance_->new_time_index = !_bs_instance_->new_time_index;
            _bs_instance_->last_fixed_update_times[_bs_instance_->new_time_index] = _bs_instance_->fixed_time;

            _bs_instance_->delta_time = _bs_instance_->fixed_time;
            fixed_tick();
            _bs_instance_->elapsed_time += _bs_instance_->fixed_time;
            _bs_instance_->advance = false;
        }
    }

    _bs_checkTimer(&_bs_instance_->timer);
    _bs_instance_->time = _bs_instance_->timer.seconds;

    float newer_time = _bs_instance_->last_fixed_update_times[_bs_instance_->new_time_index];
    float older_time = _bs_instance_->last_fixed_update_times[!_bs_instance_->new_time_index];

    if (newer_time != older_time)
        _bs_instance_->fixed_interpolation = (_bs_instance_->time - newer_time) / (newer_time - older_time);
    else
        _bs_instance_->fixed_interpolation = 1.0f;

    _bs_instance_->delta_time = _bs_instance_->time - _bs_instance_->time_old;
    _bs_instance_->in_fixed = false;

    #ifdef _WIN32
    POINT p;
    if (GetCursorPos(&p)) {
        _bs_instance_->screen_cursor = BS_V2(p.x, p.y);
    }
    #endif

    /**
        Cache contexts
        Should be improved maybe somehow
        */
    bs_List* object_sources = bs_objectSources();
    static bs_List contexts = { .unit_size = sizeof(bs_Context*), .increment = 4 };
    contexts.count = 0;

    for (int i = 0; i < object_sources->count; i++) {
        bs_ObjectSource* source = bs_fetchUnit(object_sources, i);
        if (source->type != BS_OBJECT_CONTEXT)
            continue;

        for (int j = 0; j < source->ids_count; j++) {
            if (!source->ids[j].object)
                continue;

            bs_pushBack(&contexts, &source->ids[j].object->context);
        }
    }

   /**
    Tick all contexts
    */
    for (int i = 0; i < contexts.count; i++) {
        bs_Context* ctx = *(bs_Context**)_bs_fetchUnit(&contexts, i);

        _bs_scope_.context = ctx;
        _bs_tickContext(ctx, ctx->tick);
        _bs_scope_.context = NULL;
    }
    _bs_checkTimer(&_bs_instance_->timer);

    #ifdef _WIN32
    while ((_bs_instance_->timer.seconds - frame_start) < _bs_instance_->target_frame_time) {
        Sleep(0);
        _bs_checkTimer(&_bs_instance_->timer);
    }
    #endif
}

static void _bs_startRenderTick(bs_Callback fixed_tick) {
    while (_bs_instance_->alive) {
        _bs_renderTick(fixed_tick);
    }
}

#ifdef _WIN32
static void _bs_handleMessageAtomic(bs_List* contexts, bs_Context* context, MSG msg) {
    switch (msg.message) {
    case WM_QUIT: PostQuitMessage(0); _bs_instance_->alive = false; return;

    case WM_LBUTTONDOWN:
        SetCapture(context->hwnd);
        bs_setBit(context->io.input_down_events, BS_LEFT_MOUSE_BUTTON);

        if (context->window_type != BS_WINDOW_MENU)
            _hide_menu_windows_ = true;
        break;
    case WM_LBUTTONUP:
        ReleaseCapture();
        bs_setBit(context->io.input_up_events, BS_LEFT_MOUSE_BUTTON);
        break;

    case WM_RBUTTONDOWN:
        SetCapture(context->hwnd);
        bs_setBit(context->io.input_down_events, BS_RIGHT_MOUSE_BUTTON);
        if (context->window_type != BS_WINDOW_MENU)
            _hide_menu_windows_ = true;
        break;
    case WM_RBUTTONUP:
        ReleaseCapture();
        bs_setBit(context->io.input_up_events, BS_RIGHT_MOUSE_BUTTON);
        break;

    case WM_MBUTTONDOWN:
        SetCapture(context->hwnd);
        bs_setBit(context->io.input_down_events, BS_MIDDLE_MOUSE_BUTTON);
        if (context->window_type != BS_WINDOW_MENU)
            _hide_menu_windows_ = true;
        break;
    case WM_MBUTTONUP:
        ReleaseCapture();
        bs_setBit(context->io.input_up_events, BS_MIDDLE_MOUSE_BUTTON);
        break;

    case WM_MOUSEWHEEL: {
        context->io.scroll = (SHORT)HIWORD(msg.wParam) / 120.0;
    } break;
    case WM_CHAR: {
     //   if (msg.wParam < BS_KEYS_COUNT)
     //       bs_setBit(context->io.chars, (bs_U32)msg.wParam);
    } break;
    case WM_KEYDOWN: {
        if (msg.wParam < BS_KEYS_COUNT)
            bs_setBit(context->io.input_down_events, (bs_U32)msg.wParam);
    } break;
    case WM_KEYUP: {
        if (msg.wParam < BS_KEYS_COUNT)
            bs_setBit(context->io.input_up_events, (bs_U32)msg.wParam);
       // if (msg.wParam < 256)
       //     bs_clearBit(context->io.key_events, (bs_U32)msg.wParam);
    } break;
    case WM_SYSKEYDOWN: {
        //if (msg.wParam < 256)
        //    bs_setBit(context->io.key_events, (bs_U32)msg.wParam);
    } break;
    case WM_SYSKEYUP: {
      // if (msg.wParam < 256)
      //     bs_clearBit(context->io.key_events, (bs_U32)msg.wParam);
    } break;
    case WM_NCLBUTTONDOWN:
    case WM_NCLBUTTONUP:
    case WM_NCLBUTTONDBLCLK:
    case WM_NCRBUTTONDOWN:
    case WM_NCRBUTTONUP:
    case WM_NCRBUTTONDBLCLK:
    case WM_NCMBUTTONDOWN:
    case WM_NCMBUTTONUP:
    case WM_NCMBUTTONDBLCLK:
        _hide_menu_windows_ = true;
        break;
    }

    if (_hide_menu_windows_)
        _bs_hideMenuWindows(contexts);
}
#endif

BSAPI void _bs_tick(bs_Callback fixed_tick) {
    _bs_instance_->alive = true;
    _bs_instance_->timer = _bs_timer();

    if (separate_message_thread)
        bs_createThread((bs_ThreadFunction)_bs_startRenderTick, fixed_tick);

    while (_bs_instance_->alive) {
       /**
        Cache contexts
        Should be improved maybe somehow
        */
        bs_List* object_sources = bs_objectSources();
        static bs_List contexts = { .unit_size = sizeof(bs_Context*), .increment = 4 };
        contexts.count = 0;

        for (int i = 0; i < object_sources->count; i++) {
            bs_ObjectSource* source = bs_fetchUnit(object_sources, i);
            if (source->type != BS_OBJECT_CONTEXT)
                continue;

            for (int j = 0; j < source->ids_count; j++) {
                if (!source->ids[j].object)
                    continue;

                bs_pushBack(&contexts, &source->ids[j].object->context);
            }
        }

       /**
        Message loop
        */
       #ifdef _WIN32
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            _bs_scope_.context = NULL;

            bs_Context* context = NULL;
            for (int i = 0; i < contexts.count; i++) {
                bs_Context* ctx = *(bs_Context**)bs_fetchUnit(&contexts, i);

                if (ctx->hwnd == msg.hwnd) {
                    context = ctx;
                    break;
                }
            }

            if (!context) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                continue;
            }

            //if (!separate_message_thread)
            _bs_handleMessageAtomic(&contexts, context, msg);

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        #endif

        if (!separate_message_thread) {
            _bs_renderTick(fixed_tick);
        }
        else {
            if (_hide_menu_windows_)
                _bs_hideMenuWindows(&contexts);
        }

        /*
        while ((_bs_instance_->timer.seconds - frame_start) < _bs_instance_->target_frame_time) {
            Sleep(0);
            _bs_checkTimer(&_bs_instance_->timer);
        }
        */
    }
}

static void _bs_updateWindowDPI(bs_Context* context) {
    #ifdef _WIN32
    UINT dpi = GetDpiForWindow(context->hwnd);

    context->border_size.x = GetSystemMetricsForDpi(SM_CXSIZEFRAME, dpi);
    context->border_size.y = GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi);
    #endif
}

#ifdef _WIN32
static LRESULT _bs_hitTestResize(bs_Context* context, bs_ivec2 pt, LRESULT fallback) {
    RECT rc;
    GetWindowRect(context->hwnd, &rc);

    const bool left = pt.x < rc.left + context->border_size.x;
    const bool right = pt.x >= rc.right - context->border_size.x;
    const bool top = pt.y < rc.top + context->border_size.y;
    const bool bottom = pt.y >= rc.bottom - context->border_size.y;

    if (top && left) return HTTOPLEFT;
    if (top && right) return HTTOPRIGHT;
    if (bottom && left) return HTBOTTOMLEFT;
    if (bottom && right) return HTBOTTOMRIGHT;
    if (top) return HTTOP;
    if (left) return HTLEFT;
    if (bottom) return HTBOTTOM;
    if (right) return HTRIGHT;

    return fallback;
}

LRESULT CALLBACK _bs_windowProcedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    bs_List* object_sources = bs_objectSources();
    bs_Context* context = NULL;

    for (int i = 0; i < object_sources->count; i++) {
        bs_ObjectSource* source = bs_fetchUnit(object_sources, i);
        if (source->type != BS_OBJECT_CONTEXT)
            continue;

        for (int j = 0; j < source->ids_count; j++) {
            if (!source->ids[j].object)
                continue;

            if (source->ids[j].object->context->hwnd == hwnd)
                context = source->ids[j].object->context;
        }
    }

    switch (msg) {
    case WM_ACTIVATE:
        if (LOWORD(w_param) == WA_INACTIVE)
            _hide_menu_windows_ = true;
        break;
    case WM_DPICHANGED:
        _bs_updateWindowDPI(context);
        return DefWindowProc(hwnd, msg, w_param, l_param);
    case WM_NCHITTEST:
        if (context) {
            if (context->window_type == BS_WINDOW_MENU)
                return HTCLIENT;
            else if (_bs_callbacks_.client_area_tick) {
                bs_ivec2 pt = {
                    GET_X_LPARAM(l_param),
                    GET_Y_LPARAM(l_param)
                };

                bs_NonClientArea non_client_area = _bs_callbacks_.client_area_tick(context, pt);

                switch (non_client_area) {
                case BS_CLIENT_AREA:
                    return _bs_hitTestResize(context, pt, HTCLIENT);
                case BS_NON_CLIENT_AREA_CAPTION_BUTTON:
                    return _bs_hitTestResize(context, pt, HTCLIENT);
                case BS_NON_CLIENT_AREA_CAPTION:
                    return _bs_hitTestResize(context, pt, HTCAPTION);
                }

                return HTCLIENT;
            }
        }

        return DefWindowProc(hwnd, msg, w_param, l_param);
    case WM_NCCALCSIZE:

        if (context && context->window_type == BS_WINDOW_NO_TITLE_BAR) {

            // https://handmade.network/forums/articles/t/9073-custom_window_title_bar_and_almost_correctly_drawing_windows_10_borders
            // int padding = GetSystemMetrics(SM_CXPADDEDBORDER);
            // TODO: dpi shit
            int padding = 0;
            int borderLR = GetSystemMetrics(SM_CXFRAME) + padding;
            int borderTB = GetSystemMetrics(SM_CYFRAME) + padding;

            RECT* rect = 0;

            if (w_param) {
                rect = ((NCCALCSIZE_PARAMS*)l_param)->rgrc;
            }
            else {
                rect = (RECT*)l_param;
            }

            rect->left += borderLR;
            rect->right -= borderLR;
            rect->bottom -= borderTB;

            if (IsZoomed(hwnd)) {
                rect->top += borderTB;
            }


            break;
        }
        else
            return DefWindowProc(hwnd, msg, w_param, l_param);
    case WM_MOUSEACTIVATE:

        if (context && context->window_type == BS_WINDOW_MENU)
            return MA_NOACTIVATE;
        else
            return MA_ACTIVATE;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
		return 0;
//	case WM_SETCURSOR: {
//		// SetCursor(_bs_scope_.context->cursor_icons[_bs_wnd.cursor_icon].handle);
//	} break;
	default: return DefWindowProc(hwnd, msg, w_param, l_param);
    }
    return 0;
}
#endif

BSAPI void _bs_moveWindow(bs_Context* context, int x, int y) {
    bs_ivec2 resolution = _bs_resolution(context);
    #ifdef _WIN32
	SetWindowPos(context->hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
	#endif
}

BSAPI bs_Result _bs_window(
    bs_Context* context,
    bs_Context* parent,
    bs_ContextTickFunction tick,
    bs_U32 width,
    bs_U32 height,
    const char* title,
    bs_WindowType type)
{
    _bs_scope_.context = context;

    context->hidden = true;
    context->tick = tick;
    context->title = title;
    context->dimensions = (bs_ivec2) { width, height };
    context->window_type = type;

    bs_Timer timer = _bs_timer();
    _bs_setTargetFramerate(120);

    #ifdef _WIN32
    const char* class_name = title;
    HINSTANCE hinstance = GetModuleHandle(0);

    HICON hicon = (HICON)LoadImage(
        NULL,
        "content/icon.ico",
        IMAGE_ICON,
        0, 0,
        LR_LOADFROMFILE | LR_DEFAULTSIZE
    );

    WNDCLASSEX wc = {
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_OWNDC,
        .lpfnWndProc = _bs_windowProcedure,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hinstance,
        .hIcon = hicon ? hicon : LoadIcon(NULL, IDI_APPLICATION),
        .hCursor = LoadCursor(NULL, IDC_ARROW),
		.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
		.lpszMenuName = NULL,
        .lpszClassName = class_name,
        //.hIconSm = LoadIcon(NULL, IDI_APPLICATION),
    };

    if (!RegisterClassEx(&wc)) {
        BS_WARN_WIN32_PATH("RegisterClassEx", title);
        _bs_scope_.context = NULL;
        return _bs_convertWin32Error(GetLastError());
    }

    DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    DWORD ex_style = 0;
    HWND parent_hwnd = NULL;

    if (parent) {
        parent_hwnd = parent->hwnd;
        style = WS_CHILD | WS_VISIBLE;
    }
    else if (type == BS_WINDOW_NO_TITLE_BAR) {
        style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }
    else if (type == BS_WINDOW_MENU) {
        style = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        ex_style = WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW;
    }

    context->hwnd = CreateWindowEx(
        ex_style,
        class_name,
        title,
        style,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        parent_hwnd, NULL, hinstance, NULL);

    if (!context->hwnd) {
        BS_WARN_WIN32_PATH("CreateWindowEx", title);
        _bs_scope_.context = NULL;
        return _bs_convertWin32Error(GetLastError());
    }

    PIXELFORMATDESCRIPTOR pixel_format_descriptor = {
        .nSize = sizeof(PIXELFORMATDESCRIPTOR),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cRedBits = 0, .cRedShift = 0, .cGreenBits = 0, .cGreenShift = 0, .cBlueBits = 0, .cBlueShift = 0,
        .cAlphaBits = 0,
        .cAlphaShift = 0,
        .cAccumBits = 0,
        .cAccumRedBits = 0, .cAccumGreenBits = 0, .cAccumBlueBits = 0, .cAccumAlphaBits = 0,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .cAuxBuffers = 0,
        .iLayerType = PFD_MAIN_PLANE,
        .dwLayerMask = 0, .dwVisibleMask = 0, .dwDamageMask = 0
    };

    HDC hdc = GetDC(context->hwnd);
    int pixel_format = ChoosePixelFormat(hdc, &pixel_format_descriptor);
    SetPixelFormat(hdc, pixel_format, &pixel_format_descriptor);
#endif

    _bs_createSurface();

    #ifdef _WIN32
    if (context->window_type == BS_WINDOW_NO_TITLE_BAR) {
        RECT rect;
        GetWindowRect(context->hwnd, &rect);

        SetWindowPos(
            context->hwnd,
            NULL,
            rect.left,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_FRAMECHANGED | SWP_NOACTIVATE
        );

        DWM_WINDOW_CORNER_PREFERENCE preference = DWMWCP_ROUND;

        DwmSetWindowAttribute(
            context->hwnd,
            DWMWA_WINDOW_CORNER_PREFERENCE,
            &preference,
            sizeof(preference)
        );
    }

    _bs_updateWindowDPI(context);
    #endif

    _bs_scope_.context = NULL;

    return BS_RESULT_OK;
 }

BSAPI void _bs_swapchain(bs_Context* context) {
    _bs_scope_.context = context;
    _bs_prepareSwapchain();
    _bs_scope_.context = NULL;
}

BSAPI void _bs_device(bs_Context* context, bs_PhysicalDevice* device) {
    _bs_scope_.context = context;

    _bs_preparePhysicalDevice(context);
    _bs_queryPhysicalDevice(VK_QUEUE_GRAPHICS_BIT, true, &_bs_instance_->physical_device, &_bs_instance_->queue_family);
    _bs_prepareLogicalDevice(_bs_instance_->physical_device);

    bs_Procedure procedures[] = { BS_FOREACH_PROC(BS_STRING_GEN_2) };
    _bs_queryProcedures(procedures, sizeof(procedures) / sizeof(*procedures), 0, &_bs_procs_);

    _bs_scope_.context = NULL;
}
