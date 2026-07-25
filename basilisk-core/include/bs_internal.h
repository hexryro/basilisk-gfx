
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

#ifndef BS_INTERNAL_H
#define BS_INTERNAL_H

#include <bs_internal.gen.h>

#define BS_FOREACH_PROC(X) \
    X(PFN_vkCmdInsertDebugUtilsLabelEXT, vkCmdInsertDebugUtilsLabelEXT) \
    X(PFN_vkCmdBeginDebugUtilsLabelEXT, vkCmdBeginDebugUtilsLabelEXT) \
    X(PFN_vkCmdEndDebugUtilsLabelEXT, vkCmdEndDebugUtilsLabelEXT) \
    X(PFN_vkCmdBeginRenderingKHR, vkCmdBeginRenderingKHR) \
    X(PFN_vkCmdEndRenderingKHR, vkCmdEndRenderingKHR) \
    X(PFN_vkCmdTraceRaysKHR, vkCmdTraceRaysKHR) \
    X(PFN_vkGetAccelerationStructureBuildSizesKHR, vkGetAccelerationStructureBuildSizesKHR) \
    X(PFN_vkCreateAccelerationStructureKHR, vkCreateAccelerationStructureKHR) \
    X(PFN_vkCmdBuildAccelerationStructuresKHR, vkCmdBuildAccelerationStructuresKHR) \
    X(PFN_vkGetAccelerationStructureDeviceAddressKHR, vkGetAccelerationStructureDeviceAddressKHR) \
    X(PFN_vkGetRayTracingShaderGroupHandlesKHR, vkGetRayTracingShaderGroupHandlesKHR) \
    X(PFN_vkDestroyAccelerationStructureKHR, vkDestroyAccelerationStructureKHR) \
    X(PFN_vkCreateRayTracingPipelinesKHR, vkCreateRayTracingPipelinesKHR) \

#define BS_STRUCT_GEN(TYPE, FUNC, ...) TYPE FUNC;

typedef struct bs_Procs bs_Procs;
extern struct bs_Procs {
    BS_FOREACH_PROC(BS_STRUCT_GEN)
} _bs_procs_;

BSAPI void _bs_writeLogger(
    bs_Library library,
    bs_MessageLevel level,
    bs_Result result,
    int code,
    const char* function,
    const char* file,
    int line,
    const char* message, ...);

#ifdef _WIN32
#define BS_WARN_WIN32_PATH(function, path)                           \
    _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_VALIDATION_ERROR, _bs_convertWin32Error(GetLastError()), GetLastError(), __func__, __FILE__, __LINE__, "%s %s", function, path)
#endif

#define BS_WARN_ERRNO_PATH(function, path)                           \
    _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_VALIDATION_ERROR, _bs_convertErrno(errno), errno, __func__, __FILE__, __LINE__, "%s %s", function, path)

#define BS_VALIDATE(condition, ret, format, ...)                     \
    if (!(condition)) {                                              \
        if (_bs_callbacks_.error) _bs_callbacks_.error();            \
        _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_VALIDATION_ERROR, BS_RESULT_VALIDATION_ERROR, BS_RESULT_VALIDATION_ERROR, __func__, __FILE__, __LINE__, "%s" format, #condition __VA_OPT__(, ) __VA_ARGS__); \
        return ret;                                                  \
    }

#define BS_WARN_VULKAN_ERROR(function, code, format, ...)            \
    _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_VALIDATION_ERROR, _bs_convertVulkanResult(code), code, __func__, __FILE__, __LINE__, format __VA_OPT__(, ) __VA_ARGS__)

#define BS_CRITICAL_VULKAN_ERROR(function, code, format, ...)        \
    _bs_criticalF(format __VA_OPT__(, ) __VA_ARGS__)

#define BS_VALIDATE_OBJECT_TYPE(object, source_id, _return)          \
    BS_VALIDATE(((bs_ObjectSource*)bs_fetchUnit(bs_objectSources(), source_id))->type == source_id, _return,,)

#define BS_WARN_INVALID_MAGIC(resource_type, path)                   \
    _bs_criticalF("Invalid magic for %s \"%s\"", resource_type, path)
   // _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_CRITICAL_ERROR, BS_RESULT_CORRUPTED, BS_RESULT_CORRUPTED, __func__, __FILE__, __LINE__, "Invalid magic for %s \"%s\"", resource_type, path)

#define BS_WARN_UNSUPPORTED_VERSION(resource_type, path)             \
    _bs_criticalF("Unsupported version for %s \"%s\"", resource_type, path)
   // _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_CRITICAL_ERROR, BS_RESULT_CORRUPTED, BS_RESULT_CORRUPTED, __func__, __FILE__, __LINE__, "Unsupported version for %s \"%s\"", resource_type, path)

#define BS_WARN_YYJSON_ERROR(function, code, format, ...)            \
    _bs_criticalF(format __VA_OPT__(, ) __VA_ARGS__)
   // _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_CRITICAL_ERROR, _bs_convertYyjsonError(code), code, __func__, __FILE__, __LINE__, format __VA_OPT__(, ) __VA_ARGS__)

#endif