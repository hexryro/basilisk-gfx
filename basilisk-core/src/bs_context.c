
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

#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#include <dwmapi.h>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan.h>
#endif

#include <time.h>
#include <assert.h>

#include <basilisk-core.h>
#include <bs_internal.h>
#include <uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <uiribbon.h>

static void _bs_createSurface() {
    VkResult result = VK_SUCCESS;

    if (_bs_instance_->extensions.surface_type == BS_SURFACE_TYPE_WIN32) {
        VkWin32SurfaceCreateInfoKHR ci = {
            .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
            .hinstance = GetModuleHandle(0),
            .hwnd = _bs_context_->hwnd,
        };

        result = vkCreateWin32SurfaceKHR(_bs_instance_->instance, &ci, NULL, &_bs_context_->surface);
    }
    else if (_bs_instance_->extensions.surface_type == BS_SURFACE_TYPE_HEADLESS) {
        VkHeadlessSurfaceCreateInfoEXT ci = {
            .sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT,
        };

        result = vkCreateHeadlessSurfaceEXT(_bs_instance_->instance, &ci, NULL, &_bs_context_->surface);
    }
    else {
        _bs_warnF("Surface type %d is not supported", _bs_instance_->extensions.surface_type);
    }

    if (result != VK_SUCCESS) {
        _bs_warnF("Failed to create surface for window \"%s\" (Vulkan result = %d)", _bs_context_->title, result);
    }
}

BSAPI void _bs_queryProcedures(bs_Procedure* procedures, int count, void* dll_handle, unsigned char* destination) {
#define BS_STRING_GEN_2(TYPE, FUNC, ...) { .size = sizeof(TYPE), .func = #FUNC, __VA_OPT__(.is_required = __VA_ARGS__) },

    for (int i = 0; i < count; i++) {
        void* data = dll_handle == 0 ?
            (void*)vkGetDeviceProcAddr(_bs_instance_->device, procedures[i].func) :
            (void*)GetProcAddress(dll_handle, procedures[i].func);

        if (data)
            memcpy(destination, &data, procedures[i].size);
        else if (procedures[i].is_required) {
            _bs_warnF("Failed to query procedure \"%s\"", procedures[i].func);
        }

        destination += procedures[i].size;
    }
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

static void _bs_readQueueFamilies(bs_PhysicalDevice* physical_device) {
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
        result = vkGetPhysicalDeviceSurfaceSupportKHR(physical_device->vk_device, i, _bs_context_->surface, &supports_present);
        if (result != VK_SUCCESS) {
            BS_CRITICAL_VULKAN_ERROR("vkGetPhysicalDeviceSurfaceSupportKHR", result, "");
            continue;
        }

        queue_family->queue_flags = queue_families[i].queueFlags;
        queue_family->queue_count = queue_families[i].queueCount;
        queue_family->supports_present = supports_present;

        if (supports_present)
            physical_device->supports_present = true;
    }
}

static void _bs_readSurfaceFormats(bs_PhysicalDevice* physical_device) {
    VkResult result;

    bs_U32 surface_formats_count;
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device->vk_device, _bs_context_->surface, &surface_formats_count, NULL);
    if (result != VK_SUCCESS) {
        BS_CRITICAL_VULKAN_ERROR("vkGetPhysicalDeviceSurfaceFormatsKHR", result, "");
        return;
    }

    if (surface_formats_count == 0)
        return;

    VkSurfaceFormatKHR* formats = bs_alloca(surface_formats_count * sizeof(VkSurfaceFormatKHR));
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device->vk_device, _bs_context_->surface, &surface_formats_count, formats);
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

static void _bs_preparePhysicalDevice() {
    VkResult result;

    bs_U32 num_devices = 0;
    vkEnumeratePhysicalDevices(_bs_instance_->instance, &num_devices, NULL);
    if (num_devices == 0) {
        _bs_critical(BS_CONSTANT_STRING("No GPU with Vulkan support was found"));
        return;
    }

    VkPhysicalDevice* devices = bs_alloca(num_devices * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(_bs_instance_->instance, &num_devices, devices);

    _bs_ensureSize(&_bs_physical_devices_, num_devices);

    assert(BS_MAX_PHYSICAL_DEVICE_NAME_SIZE == VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);

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

        _bs_readQueueFamilies(physical_device);
        _bs_readSurfaceFormats(physical_device);

       // VkSurfaceCapabilitiesKHR capabilities;
       // vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, _bs_context_->surface, &capabilities);

    }

    for (int i = 0; i < _bs_physical_devices_.count; i++) {
        bs_PhysicalDevice* physical_device = _bs_fetchUnit(&_bs_physical_devices_, i);
        _bs_logPhysicalDeviceInfo(physical_device);
    }
}

static void _bs_queryPhysicalDevice(VkQueueFlags required_flags, bool supports_present, bs_PhysicalDevice** out_device, bs_QueueFamily** out_queue_family) {
    *out_device = *out_queue_family = NULL;

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

    _bs_critical(BS_CONSTANT_STRING("No GPU with graphics and present support was found"));
}


static void _bs_prepareLogicalDevice() {
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
    vkGetPhysicalDeviceFeatures2(_bs_context_->physical_device->vk_device, &features2);

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
    vk_result = vkEnumerateDeviceExtensionProperties(_bs_context_->physical_device->vk_device, NULL, &total_extensions_count, NULL);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkEnumerateDeviceExtensionProperties", vk_result, "");
    }

    VkExtensionProperties* props = _bs_calloc(total_extensions_count, sizeof(VkExtensionProperties));
    vk_result = vkEnumerateDeviceExtensionProperties(_bs_context_->physical_device->vk_device, NULL, &total_extensions_count, props);
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

    vkGetPhysicalDeviceProperties2(_bs_context_->physical_device->vk_device, &device_properties);

    _bs_props_.shader_group_handle_size = ray_tracing_pipeline_properties.shaderGroupHandleSize;
    _bs_props_.shader_group_base_alignment = ray_tracing_pipeline_properties.shaderGroupBaseAlignment;
    _bs_props_.min_acceleration_structure_scratch_offset_alignment = accel_struct_properties.minAccelerationStructureScratchOffsetAlignment;
    /**
    Creation
    */
    float queue_priority = 1.0;
    VkDeviceQueueCreateInfo queue_ci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = _bs_queueFamily(BS_QUEUE_GRAPHICS_BIT),
        .queueCount = 1,
        .pQueuePriorities = &queue_priority,
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

    vk_result = vkCreateDevice(_bs_context_->physical_device->vk_device, &ci, NULL, &_bs_instance_->device);
    if (vk_result != VK_SUCCESS) {
        BS_CRITICAL_VULKAN_ERROR("vkCreateDevice", vk_result, "");
    }

    //_bs_nameHandlef((bs_U64)_bs_instance->_.graphics_queue, VK_OBJECT_TYPE_QUEUE, "graphics queue");
    //_bs_nameHandlef((bs_U64)_bs_instance->_.compute_queue, VK_OBJECT_TYPE_QUEUE, "compute queue");
}

static void _bs_prepareCommands() {
    VkCommandPoolCreateInfo pool_ci = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = _bs_queueFamily(BS_QUEUE_GRAPHICS_BIT),
    };

    VkResult result = vkCreateCommandPool(_bs_instance_->device, &pool_ci, NULL, &_bs_instance_->command_pool);
    if (result != VK_SUCCESS) {
        BS_CRITICAL_VULKAN_ERROR("vkCreateCommandPool", result, "");
    }
}



  /*==============================================================================
   * Swapchain
   *============================================================================*/

static void _bs_querySwapchainFormat(VkFormat candidates[], int candidates_count) {

    for (int i = 0; i < candidates_count; i++) {
        VkFormat candidate = candidates[i];

        for (int j = 0; j < _bs_context_->physical_device->surface_formats.count; j++) {
            bs_SurfaceFormat* surface_format = bs_fetchUnit(&_bs_context_->physical_device->surface_formats, j);

            if ((bs_Format)candidate == surface_format->format) {
                _bs_context_->surface_format = *surface_format;
                return;
            }
        }
    }

    _bs_critical(BS_CONSTANT_STRING("Failed to query swapchain surface format"));
}

static void _bs_querySwapchainMode(VkPresentModeKHR candidates[], int candidates_count) {
    bs_U32 num_modes = 0;
    VkPresentModeKHR result = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(_bs_context_->physical_device->vk_device, _bs_context_->surface, &num_modes, NULL);
    VkPresentModeKHR* modes = bs_alloca(num_modes * sizeof(VkPresentModeKHR));
    vkGetPhysicalDeviceSurfacePresentModesKHR(_bs_context_->physical_device->vk_device, _bs_context_->surface, &num_modes, modes);

    for (int i = 0; i < candidates_count; i++) {
        VkPresentModeKHR candidate = candidates[i];

        for (int j = 0; j < num_modes; j++) {
            VkPresentModeKHR mode = modes[j];
            if (candidate == mode) {
                _bs_context_->present_mode = (bs_PresentMode)mode;
                return;
            }
        }
    }

    _bs_critical(BS_CONSTANT_STRING("Failed to query swapchain present mode"));
}

static void _bs_prepareSwapchain() {
    VkResult result;

    const VkPresentModeKHR modes[] = {
        VK_PRESENT_MODE_IMMEDIATE_KHR,
        VK_PRESENT_MODE_FIFO_KHR,
        VK_PRESENT_MODE_MAILBOX_KHR,
        VK_PRESENT_MODE_FIFO_RELAXED_KHR,

        VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
        VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR,
        VK_PRESENT_MODE_FIFO_LATEST_READY_KHR,
        VK_PRESENT_MODE_FIFO_LATEST_READY_EXT,
    };

    const VkFormat formats[] = {
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_R8G8B8A8_SRGB,
        VK_FORMAT_B8G8R8A8_SRGB,
    };

    _bs_querySwapchainMode(modes, sizeof(modes) / sizeof(*modes));
    _bs_querySwapchainFormat(formats, sizeof(formats) / sizeof(*formats));

    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_bs_context_->physical_device->vk_device, _bs_context_->surface, &capabilities);

    const bool same_family = true; // TODO: this shouldn't always be true

    _bs_context_->swapchain_image = _bs_context_->swapchain_image ? _bs_context_->swapchain_image : NULL;

    bs_ivec2 resolution = { capabilities.minImageExtent.width, capabilities.minImageExtent.height };
    bs_Image image = {
        .head = {
            .type = BS_OBJECT_IMAGE
        },
        .flags = BS_IMAGE_SWAPS_BIT,
        .format = _bs_context_->surface_format.format,
        .dim = resolution,
    };

    const int frames_in_flight_target = 2;
    const int frames_in_flight_max = 3;

    _bs_context_->frames_in_flight = bs_clamp(frames_in_flight_target, capabilities.minImageCount, frames_in_flight_max);

    VkSwapchainCreateInfoKHR swapchain_ci = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = _bs_context_->surface,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .minImageCount = _bs_context_->frames_in_flight,
        .imageExtent = { resolution.x, resolution.y },
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = same_family ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,
        .queueFamilyIndexCount = same_family ? 0 : 2,
        .pQueueFamilyIndices = same_family ? NULL : NULL,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .clipped = VK_TRUE,
        .preTransform = capabilities.currentTransform,
        .presentMode = (VkPresentModeKHR)_bs_context_->present_mode,
        .imageFormat = (VkFormat)_bs_context_->surface_format.format,
        .imageColorSpace = (VkColorSpaceKHR)_bs_context_->surface_format.color_space,
    };

    result = vkCreateSwapchainKHR(_bs_instance_->device, &swapchain_ci, NULL, &_bs_context_->swapchain);
    if (result != VK_SUCCESS) {
        _bs_warnF("Failed to create swapchain for window \"%s\"", _bs_context_->title);
        return;
    }

    /**
     Swapchain images
     */
    VkImage images[3];
    vkGetSwapchainImagesKHR(_bs_instance_->device, _bs_context_->swapchain, &_bs_context_->frames_in_flight, images);
    _bs_infoF("Swapchain\n  Format: %d\n  Mode: %d\n  Images: %d", swapchain_ci.imageFormat, swapchain_ci.presentMode, _bs_context_->frames_in_flight);

    if (_bs_context_->swapchain_image == NULL)
        _bs_context_->swapchain_image = BS_OBJECT(bs_Image, -1, 0, _bs_context_->frames_in_flight, BS_OBJECT_HAS_SWAPS_BIT, BS_OBJECT_IMAGE);

    memcpy(_bs_context_->swapchain_image->image, &image, sizeof(image));

    /**
     Swapchain image views
     */
    for (int i = 0; i < _bs_context_->frames_in_flight; i++) {
        _bs_context_->swapchain_image->image->_[i].vk_image = images[i];

        VkImageViewCreateInfo image_view_ci = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = _bs_context_->swapchain_image->image->_[i].vk_image,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = (VkFormat)_bs_context_->surface_format.format,
            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.levelCount = 1,
            .subresourceRange.layerCount = 1,
        };

        result = vkCreateImageView(_bs_instance_->device, &image_view_ci, NULL, &_bs_context_->swapchain_image->image->_[i].vk_image_view);
        if (result != VK_SUCCESS) {
            _bs_warnF("Failed to create swapchain image view for window \"%s\"", _bs_context_->title);
        }
    }

    /**
     Swapchain semaphores
     */
    VkSemaphoreCreateInfo semaphore_ci = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    for (int i = 0; i < _bs_context_->frames_in_flight; i++) {
        result = vkCreateSemaphore(_bs_instance_->device, &semaphore_ci, NULL, &_bs_context_->_[i].semaphore);
        if (result != VK_SUCCESS) {
            _bs_warnF("Failed to create swapchain semaphore for window \"%s\"", _bs_context_->title);
        }
    }
}



  /*==============================================================================
   * Window
   *============================================================================*/

BSAPI bs_Result _bs_timeZoneBias(int* out) {
#ifdef _WIN32
	TIME_ZONE_INFORMATION info = { 0 };

	DWORD time_zone_id = 0;
	if ((time_zone_id = GetTimeZoneInformation(&info)) == TIME_ZONE_ID_INVALID) {
		_bs_warnF("GetTimeZoneInformation failed (GetLastError() = %d)", GetLastError());
		return _bs_convertWin32Error(GetLastError());
	}

	*out = info.Bias / 60;

	return BS_RESULT_OK;
#else
	return BS_RESULT_NOT_SUPPORTED;
#endif
}

BSAPI bs_I64 _bs_totalSeconds(const bs_DateTime* date_time) {
	return (bs_I64)mktime(&(struct tm) {
		.tm_year = date_time->years - 1900,
		.tm_mon = date_time->months - 1,
		.tm_mday = date_time->days,
		.tm_hour = date_time->hours,
		.tm_min = date_time->minutes,
		.tm_sec = date_time->seconds,
	});
}

BSAPI bs_DateTime _bs_dateTime() {
#ifdef _WIN32
    SYSTEMTIME time;
    GetSystemTime(&time);

    return (bs_DateTime) {
        .years = time.wYear,
        .months = time.wMonth,
        .days = time.wDay,
        .hours = time.wHour,
        .minutes = time.wMinute,
        .seconds = time.wSecond,
        .milliseconds = time.wMilliseconds,
        .day_of_week = time.wDayOfWeek
    };
#else
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    time_t t = ts.tv_sec;
    struct tm tm;

    gmtime_r(&t, &tm);

    return (bs_DateTime) {
        .years = tm.tm_year + 1900,
        .months = tm.tm_mon + 1,
        .days = tm.tm_mday,
        .hours = tm.tm_hour,
        .minutes = tm.tm_min,
        .seconds = tm.tm_sec,
        .milliseconds = (int)(ts.tv_nsec / 1000000),
        .day_of_week = tm.tm_wday
    };
#endif
}

BSAPI bool _bs_isLaterThan(const bs_DateTime* a, const bs_DateTime* b) {
	return _bs_totalSeconds(a) - _bs_totalSeconds(b) > 0;
}

BSAPI void _bs_setCursor(bs_CursorIcon icon) {
	_bs_warnF("_bs_setCursor has not been implemented yet");
	/*
	if (_bs_context_->cursor_icons[icon].handle == NULL)
		_bs_context_->cursor_icons[icon].handle = LoadCursor(NULL, _bs_wnd.cursor_icons[icon].id);

	if (_bs_wnd.cursor_icon == icon)
		return;

	_bs_wnd.cursor_icon = icon;
	*/
}

BSAPI void _bs_resizeWindow(bs_U32 width, bs_U32 height) {
//	bsi_resizeObjects();
}

BSAPI void _bs_maximizeWindow() {
#ifdef _WIN32
	ShowWindow(_bs_context_->hwnd, SW_SHOWMAXIMIZED);
#else
	_bs_warnF("_bs_maximizeWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_minimizeWindow() {
#ifdef _WIN32
	ShowWindow(_bs_context_->hwnd, SW_SHOWMINIMIZED);
#else
	_bs_warnF("_bs_minimizeWindow has not been implemented for this OS yet");
#endif
}

BSAPI void _bs_exit() {
    _bs_instance_->alive = false;
}

BSAPI void _bs_pause() {
    _bs_context_->paused = !_bs_context_->paused;
}

BSAPI void _val_bs_advance() {
    BS_VALIDATE(_bs_context_->paused == true,,);
    _bs_advance();
}

BSAPI void _bs_advance() {
    _bs_context_->advance = true;
}

BSAPI double _bs_deltaTime() {
//#ifdef _DEBUG
//	if (_bs_wnd.delta_time == 0.0)
//		_bs_throwBasiliskF(BSX_GENERAL, "Delta time is 0.0"); // some bug is ruining my life
//#endif
	return _bs_context_->delta_time;
}

BSAPI double _bs_elapsedTime() {
    return _bs_context_->time;
}

BSAPI bs_ivec2 _bs_resolution() {
    return _bs_context_->swapchain_image->image->dim;
}

BSAPI bs_vec2 _bs_cursorPosition() {
    bs_vec2 p = _bs_context_->cursor;
    p.y = _bs_context_->swapchain_image->image->dim.y - p.y;

    return p;

    bs_vec2 dim = { _bs_context_->swapchain_image->image->dim.x, _bs_context_->swapchain_image->image->dim.y };
    bs_vec2 pos;

    bs_v2Div(&_bs_context_->cursor, &dim, &pos);
	return BS_V2(pos.x, 1.0 - pos.y);
}

BSAPI bs_ivec2 _bs_windowPosition() {
#ifdef _WIN32
	RECT rectangle = { 0 };
	GetWindowRect(_bs_context_->hwnd, &rectangle);

	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	return (bs_ivec2) {
		rectangle.left,
		rectangle.bottom
	};

#elif defined(__linux__)
    Window child;
    int x, y;
    XTranslateCoordinates(
        _bs_context_->display,
        _bs_context_->window,
        DefaultRootWindow(_bs_context_->display),
        0, 0,
        &x, &y,
        &child
    );

    return (bs_ivec2) {
        .x = x,
        .y = y
    };

#elif defined(__APPLE__)
    _bs_warnF("_bs_windowPosition has not been implemented for macOS yet");
    return (bs_ivec2) { 0, 0 };
#else
    return (bs_ivec2) { 0, 0 };
#endif
}

BSAPI bs_vec2 _bs_screenCursorPosition() {
	return _bs_instance_->screen_cursor;
}

BSAPI void _bs_lockCursorPosition(bool value) {
    _bs_context_->lock_cursor_position = value;
}

// TODO: could probably done without an additional boolean
BSAPI void _bs_disableUserInputs(bool value) {
	_bs_io_.disable_inputs = value;
}

BSAPI bool _bs_keyHeld(bs_U32 code) {
	return !_bs_io_.disable_inputs && (code > BS_KEYS_COUNT ? false : BS_GET_BIT(_bs_io_.hold_keys, code));
}

BSAPI bool _bs_keyDown(bs_U32 code) {
	return !_bs_io_.disable_inputs && (code > BS_KEYS_COUNT ? false : BS_GET_BIT(_bs_io_.keys, code));
}

BSAPI bool _bs_keyDownOnce(bs_U32 code) {
	return !_bs_io_.disable_inputs && (code > BS_KEYS_COUNT ? false : (BS_GET_BIT(_bs_io_.keys, code) && !BS_GET_BIT(_bs_io_.keys_old, code)));
}

BSAPI bool _bs_keyUpOnce(bs_U32 code) {
	return !_bs_io_.disable_inputs && (code > BS_KEYS_COUNT ? false : (!BS_GET_BIT(_bs_io_.keys, code) && BS_GET_BIT(_bs_io_.keys_old, code)));
}

BSAPI bool _bs_charDown(unsigned char code) {
	return !_bs_io_.disable_inputs && BS_GET_BIT(_bs_io_.chars, code);
}

BSAPI bool _bs_charDownOnce(unsigned char code) {
	return !_bs_io_.disable_inputs && (code > BS_KEY_BYTES_COUNT ? false : (BS_GET_BIT(_bs_io_.chars, code) && !BS_GET_BIT(_bs_io_.chars_old, code)));
}

BSAPI bool _bs_charUpOnce(unsigned char code) {
	return !_bs_io_.disable_inputs && (code > BS_KEY_BYTES_COUNT ? false : (!BS_GET_BIT(_bs_io_.chars, code) && BS_GET_BIT(_bs_io_.chars_old, code)));
}

BSAPI bool _bs_middleClick() { return !_bs_io_.disable_inputs && _bs_io_.middle_clicked; }
BSAPI bool _bs_middleClickOnce() { return !_bs_io_.disable_inputs && _bs_io_.middle_clicked && !_bs_io_.middle_clicked_last; }
BSAPI bool _bs_middleClickUpOnce() { return !_bs_io_.disable_inputs && !_bs_io_.middle_clicked && _bs_io_.middle_clicked_last; }
BSAPI bool _bs_leftClick() { return !_bs_io_.disable_inputs && _bs_io_.left_clicked; }
BSAPI bool _bs_rightClick() { return !_bs_io_.disable_inputs && _bs_io_.right_clicked; }
BSAPI bool _bs_rightClickOnce() { return !_bs_io_.disable_inputs && _bs_io_.right_clicked && !_bs_io_.right_clicked_last; }
BSAPI bool _bs_leftClickOnce() { return !_bs_io_.disable_inputs && _bs_io_.left_clicked && !_bs_io_.left_clicked_last; }
BSAPI bool _bs_rightClickUpOnce() { return !_bs_io_.disable_inputs && !_bs_io_.right_clicked && _bs_io_.right_clicked_last; }
BSAPI bool _bs_leftClickUpOnce() { return !_bs_io_.disable_inputs && !_bs_io_.left_clicked && _bs_io_.left_clicked_last; }

BSAPI int _bs_scroll() {
	return _bs_io_.scroll;
}

BSAPI bs_Timer _bs_timer() {
    bs_Timer timer = { 0 };

#ifdef _WIN32
    QueryPerformanceFrequency(&timer.ticks_per_second);
    QueryPerformanceCounter(&timer.last_tick_count);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    timer.last_tick_count.quad_part =
        (long long)ts.tv_sec * 1000000000LL +
        (long long)ts.tv_nsec;

    timer.ticks_per_second.quad_part = 1000000000LL;
#endif

    return timer;
}

BSAPI void _bs_checkTimer(bs_Timer* timer) {
#ifdef _WIN32
	QueryPerformanceCounter(&timer->tick_count);
	bs_U64 elapsed_ticks = timer->tick_count.quad_part - timer->last_tick_count.quad_part;
	timer->microseconds = (elapsed_ticks * 1000000) / timer->ticks_per_second.quad_part;

#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    timer->tick_count.quad_part =
        (long long)ts.tv_sec * 1000000000LL +
        (long long)ts.tv_nsec;

    long long elapsed =
        timer->tick_count.quad_part -
        timer->last_tick_count.quad_part;

    timer->microseconds = (bs_U64)(elapsed / 1000LL);
#endif

    timer->seconds = timer->microseconds / 1000000.0;
}

BSAPI void _bs_titleWindow(char* name, int name_length) {
	_bs_context_->title = name; // todo
}

BSAPI bool _bs_inFixedTick() {
    return _bs_context_->in_fixed;
}

BSAPI void _bs_setTargetFramerate(int fps) {
    _bs_context_->target_frame_time = 1.0 / (double)fps;
}

BSAPI void _bs_tickWindow(bs_Callback tick, bs_Callback fixed_tick) {
   //  _bs_checkTimer(&_bs_context_->timer);
    double frame_start = _bs_context_->timer.seconds;

    _bs_io_.scroll = 0;
    memset(_bs_io_.chars, 0, sizeof(_bs_io_.chars));

#ifdef _WIN32
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        switch (msg.message) {
        case WM_QUIT: PostQuitMessage(0); _bs_instance_->alive = false; return;

        case WM_LBUTTONDOWN: _bs_io_.left_clicked = true; break;
        case WM_LBUTTONUP: _bs_io_.left_clicked = false; break;

        case WM_RBUTTONDOWN: _bs_io_.right_clicked = true; break;
        case WM_RBUTTONUP: _bs_io_.right_clicked = false; break;

        case WM_MBUTTONDOWN: _bs_io_.middle_clicked = true; break;
        case WM_MBUTTONUP: _bs_io_.middle_clicked = false; break;
        case WM_MOUSEWHEEL: {
            _bs_io_.scroll = (SHORT)HIWORD(msg.wParam) / 120.0;
        } break;
        case WM_CHAR: {
            if (msg.wParam < 256)
                BS_SET_BIT(_bs_io_.chars, (bs_U32)msg.wParam);
        } break;
        case WM_KEYDOWN: {
            if (msg.wParam < 256) {
                BS_SET_BIT(_bs_io_.keys, (bs_U32)msg.wParam);
                BS_SET_BIT(_bs_io_.hold_keys, (bs_U32)msg.wParam);
            }
        } break;
        case WM_KEYUP: {
            if (msg.wParam < 256)
                BS_CLEAR_BIT(_bs_io_.keys, (bs_U32)msg.wParam);
        } break;
        case WM_SYSKEYDOWN: {
            if (msg.wParam < 256)
                BS_SET_BIT(_bs_io_.keys, (bs_U32)msg.wParam);
        } break;
        case WM_SYSKEYUP: {
            if (msg.wParam < 256)
                BS_CLEAR_BIT(_bs_io_.keys, (bs_U32)msg.wParam);
        } break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (_bs_context_->title_bar_height > 0 && _bs_io_.left_clicked) {
        bs_ivec2 resolution = bs_resolution();
        bs_vec2 title_bar_position = { 0, resolution.y - _bs_context_->title_bar_height };
        bs_vec2 title_bar_dimensions = { resolution.x, _bs_context_->title_bar_height };
        bs_vec2 cursor = bs_cursorPosition();

        bool hovering_title_bar = _bs_rectangleVsPoint(&title_bar_position, &title_bar_dimensions, &cursor);

        if (hovering_title_bar) {
            ReleaseCapture();
            SendMessage(
                bs_context()->hwnd,
                WM_NCLBUTTONDOWN,
                HTCAPTION,
                0
            );
        }
    }

    if (_bs_leftClickOnce() || _bs_rightClickOnce() || _bs_middleClickOnce())
        SetCapture(_bs_context_->hwnd);
    if (_bs_leftClickUpOnce() || _bs_rightClickUpOnce() || _bs_middleClickUpOnce())
        ReleaseCapture();

    POINT p;
    if (GetCursorPos(&p)) {
        _bs_instance_->screen_cursor = BS_V2(p.x, p.y);
        if (ScreenToClient(_bs_context_->hwnd, &p))
            _bs_context_->cursor = BS_V2(p.x, p.y);
    }

    _bs_checkTimer(&_bs_context_->timer);
    _bs_context_->time = _bs_context_->timer.seconds;
    _bs_context_->active = _bs_context_->hwnd == GetForegroundWindow();

#endif

    if (BS_GET_BIT(_bs_io_.keys, BS_KEY_ALT) && BS_GET_BIT(_bs_io_.keys, BS_KEY_F4))
        _bs_exit();

    if (fixed_tick) {
        _bs_context_->in_fixed = true;
        for (int i = 0; _bs_context_->advance || (_bs_context_->elapsed_time < _bs_context_->time && i < 200 && !_bs_context_->paused); i++) {
            _bs_context_->new_time_index = !_bs_context_->new_time_index;
            _bs_context_->last_fixed_update_times[_bs_context_->new_time_index] = _bs_context_->fixed_time;

            _bs_context_->delta_time = _bs_context_->fixed_time;
            fixed_tick();
            _bs_context_->elapsed_time += _bs_context_->fixed_time;
            _bs_context_->advance = false;
        }
    }
    float newer_time = _bs_context_->last_fixed_update_times[_bs_context_->new_time_index];
    float older_time = _bs_context_->last_fixed_update_times[!_bs_context_->new_time_index];

    if (newer_time != older_time)
        _bs_context_->fixed_interpolation =
        (_bs_context_->time - newer_time) / (newer_time - older_time);
    else
        _bs_context_->fixed_interpolation = 1.0f;

    _bs_context_->delta_time = _bs_context_->time - _bs_context_->time_old;
    _bs_context_->in_fixed = false;

    tick();

    /*
    if (_bs_context_->active && !_bs_io_.disable_inputs && _bs_context_->lock_cursor_position) {
        bs_ivec2 window_pos = _bs_windowPosition(window);

        float center_x = (int)(window_pos.x + _bs_resolution(window).x * 0.5f);
        float center_y = (int)(window_pos.y - _bs_resolution(window).y * 0.5f);
        _bs_setCursorPosition(center_x, center_y);
    }
    */

    _bs_io_.scroll_old = _bs_io_.scroll;
    _bs_context_->time_old = _bs_context_->time;
    _bs_io_.left_clicked_last = _bs_io_.left_clicked;
    _bs_io_.right_clicked_last = _bs_io_.right_clicked;
    _bs_io_.middle_clicked_last = _bs_io_.middle_clicked;
    memset(_bs_io_.hold_keys, 0, sizeof(_bs_io_.hold_keys));
    memcpy(_bs_io_.keys_old, _bs_io_.keys, sizeof(_bs_io_.keys_old));
    memcpy(_bs_io_.chars_old, _bs_io_.chars, sizeof(_bs_io_.chars_old));

    _bs_checkTimer(&_bs_context_->timer);

    while ((_bs_context_->timer.seconds - frame_start) < _bs_context_->target_frame_time) {
        Sleep(0);
        _bs_checkTimer(&_bs_context_->timer);
    }
}

BSAPI void _bs_tick(bs_Callback tick, bs_Callback fixed_tick) {
    _bs_instance_->alive = true;
    _bs_context_->timer = _bs_timer();

    while (_bs_instance_->alive) {
        _bs_tickWindow(tick, fixed_tick);
    }
}

LRESULT CALLBACK _bs_windowProcedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    switch (msg) {
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
//		// SetCursor(_bs_context_->cursor_icons[_bs_wnd.cursor_icon].handle);
//	} break;
	default: return DefWindowProc(hwnd, msg, w_param, l_param);
    }
    return 0;
}

BSAPI void _bs_moveWindow(int x, int y) {
    bs_ivec2 resolution = _bs_resolution();
	SetWindowPos(_bs_context_->hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

 /**
  TODO: should probably build a system around this
  */
BSAPI void _bs_overrideTitleBar(int height) {
    bs_Context* context = _bs_context_;
    context->title_bar_height = height;

    SetWindowLong(context->hwnd, GWL_STYLE, 0);

    COLORREF DARK_COLOR = 0x00000000;
    BOOL SET_CAPTION_COLOR = SUCCEEDED(DwmSetWindowAttribute(
        context->hwnd, DWMWA_CAPTION_COLOR,
        &DARK_COLOR, sizeof(DARK_COLOR)));
    SetWindowLong(context->hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);

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

BSAPI bs_Result _bs_window(bs_Context* context, bs_U32 width, bs_U32 height, const char* title) {
    _bs_context_ = context;

    context->title = title;
    context->fixed_time = 0.025;
    context->dimensions = (bs_ivec2) { width, height };

    bs_Timer timer = _bs_timer();
    _bs_setTargetFramerate(60);

    const char class_name[] = "class";
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
        return _bs_convertWin32Error(GetLastError());
    }

    context->hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
	//	WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,
        class_name,
        title,
		WS_OVERLAPPEDWINDOW,
	//	WS_POPUP |WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hinstance, NULL);

    if (!context->hwnd) {
        BS_WARN_WIN32_PATH("CreateWindowEx", title);
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

     if (_bs_callbacks_.configureWindow)
         _bs_callbacks_.configureWindow();

     ShowWindow(context->hwnd, SW_SHOW);
     UpdateWindow(context->hwnd);

	 _bs_setCursor(BS_CURSOR_DEFAULT);

     _bs_createSurface();

     return BS_RESULT_OK;
 }

BSAPI void _bs_device(bs_Context* context, bs_PhysicalDevice* device) {
    if (device) {
        context->physical_device = device;
    }
    else {
        _bs_preparePhysicalDevice();
        _bs_queryPhysicalDevice(VK_QUEUE_GRAPHICS_BIT, true, &context->physical_device, &context->queue_family);
        _bs_prepareLogicalDevice();
        _bs_prepareCommands();

        bs_Procedure procedures[] = { BS_FOREACH_PROC(BS_STRING_GEN_2) };
        _bs_queryProcedures(procedures, sizeof(procedures) / sizeof(*procedures), 0, &_bs_procs_);
    }

    _bs_prepareSwapchain();
}
