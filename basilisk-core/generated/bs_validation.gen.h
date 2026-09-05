
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

 /**
  This file was generated from basilisk-gfx.com

  It is not recommended to make changes to this file as it will be lost if
  the code is regenerated.
  */

#ifndef BS_VALIDATION_H
#define BS_VALIDATION_H

#include <basilisk-core.h>
#include <bs_internal.h>

static inline bs_FunctionTable* _val_bs_getFunctions() {
    static bs_FunctionTable functions;

#ifdef _WIN32
#define bs_getProcAddress(module, name) GetProcAddress(module, name)
    HMODULE module = NULL;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_val_bs_getFunctions),
        &module);

#else
    Dl_info module_info;
    void *module = NULL;
    dladdr((void *)(&_val_bs_getFunctions), &module_info);
    module = dlopen(module_info.dli_fname, RTLD_LAZY);
#define bs_getProcAddress(module, name) dlsym(module, name)
#endif
    functions.bs_callbacks = (PFN_bs_callbacks)bs_getProcAddress(module, "_val_bs_callbacks");
    functions.bs_scope = (PFN_bs_scope)bs_getProcAddress(module, "_val_bs_scope");
    functions.bs_writeLogFile = (PFN_bs_writeLogFile)bs_getProcAddress(module, "_val_bs_writeLogFile");
    functions.bs_v2Mid = (PFN_bs_v2Mid)bs_getProcAddress(module, "_val_bs_v2Mid");
    functions.bs_v3Mid = (PFN_bs_v3Mid)bs_getProcAddress(module, "_val_bs_v3Mid");
    functions.bs_m4x3 = (PFN_bs_m4x3)bs_getProcAddress(module, "_val_bs_m4x3");
    functions.bs_eulToQ = (PFN_bs_eulToQ)bs_getProcAddress(module, "_val_bs_eulToQ");
    functions.bs_qToEul = (PFN_bs_qToEul)bs_getProcAddress(module, "_val_bs_qToEul");
    functions.bs_rotateAabb = (PFN_bs_rotateAabb)bs_getProcAddress(module, "_val_bs_rotateAabb");
    functions.bs_fitAabb = (PFN_bs_fitAabb)bs_getProcAddress(module, "_val_bs_fitAabb");
    functions.bs_quad = (PFN_bs_quad)bs_getProcAddress(module, "_val_bs_quad");
    functions.bs_linearTosRGB = (PFN_bs_linearTosRGB)bs_getProcAddress(module, "_val_bs_linearTosRGB");
    functions.bs_sRGBToLinear = (PFN_bs_sRGBToLinear)bs_getProcAddress(module, "_val_bs_sRGBToLinear");
    functions.bs_linearV3TosRGB = (PFN_bs_linearV3TosRGB)bs_getProcAddress(module, "_val_bs_linearV3TosRGB");
    functions.bs_sRGBToLinearV3 = (PFN_bs_sRGBToLinearV3)bs_getProcAddress(module, "_val_bs_sRGBToLinearV3");
    functions.bs_rgbV4ToUChar = (PFN_bs_rgbV4ToUChar)bs_getProcAddress(module, "_val_bs_rgbV4ToUChar");
    functions.bs_rgbUCharToV4 = (PFN_bs_rgbUCharToV4)bs_getProcAddress(module, "_val_bs_rgbUCharToV4");
    functions.bs_hsvToRgb = (PFN_bs_hsvToRgb)bs_getProcAddress(module, "_val_bs_hsvToRgb");
    functions.bs_rgbToHsv = (PFN_bs_rgbToHsv)bs_getProcAddress(module, "_val_bs_rgbToHsv");
    functions.bs_convertYyjsonResult = (PFN_bs_convertYyjsonResult)bs_getProcAddress(module, "_val_bs_convertYyjsonResult");
    functions.bs_convertVulkanResult = (PFN_bs_convertVulkanResult)bs_getProcAddress(module, "_val_bs_convertVulkanResult");
    functions.bs_convertWin32Error = (PFN_bs_convertWin32Error)bs_getProcAddress(module, "_val_bs_convertWin32Error");
    functions.bs_serializeWin32Error = (PFN_bs_serializeWin32Error)bs_getProcAddress(module, "_val_bs_serializeWin32Error");
    functions.bs_convertErrno = (PFN_bs_convertErrno)bs_getProcAddress(module, "_val_bs_convertErrno");
    functions.bs_serializeErrno = (PFN_bs_serializeErrno)bs_getProcAddress(module, "_val_bs_serializeErrno");
    functions.bs_playSound = (PFN_bs_playSound)bs_getProcAddress(module, "_val_bs_playSound");
    functions.bs_sound = (PFN_bs_sound)bs_getProcAddress(module, "_val_bs_sound");
    functions.bs_iniAudio = (PFN_bs_iniAudio)bs_getProcAddress(module, "_val_bs_iniAudio");
    functions.bs_rayVsObb = (PFN_bs_rayVsObb)bs_getProcAddress(module, "_val_bs_rayVsObb");
    functions.bs_sphereVsPoint = (PFN_bs_sphereVsPoint)bs_getProcAddress(module, "_val_bs_sphereVsPoint");
    functions.bs_sphereVsObbTest = (PFN_bs_sphereVsObbTest)bs_getProcAddress(module, "_val_bs_sphereVsObbTest");
    functions.bs_sphereVsObb = (PFN_bs_sphereVsObb)bs_getProcAddress(module, "_val_bs_sphereVsObb");
    functions.bs_rectangleVsPoint = (PFN_bs_rectangleVsPoint)bs_getProcAddress(module, "_val_bs_rectangleVsPoint");
    functions.bs_lineVsLine = (PFN_bs_lineVsLine)bs_getProcAddress(module, "_val_bs_lineVsLine");
    functions.bs_populateVertexDeclaration = (PFN_bs_populateVertexDeclaration)bs_getProcAddress(module, "_val_bs_populateVertexDeclaration");
    functions.bs_beginComment = (PFN_bs_beginComment)bs_getProcAddress(module, "_val_bs_beginComment");
    functions.bs_endComment = (PFN_bs_endComment)bs_getProcAddress(module, "_val_bs_endComment");
    functions.bs_swapchainImage = (PFN_bs_swapchainImage)bs_getProcAddress(module, "_val_bs_swapchainImage");
    functions.bs_clearStencil = (PFN_bs_clearStencil)bs_getProcAddress(module, "_val_bs_clearStencil");
    functions.bs_clearDepth = (PFN_bs_clearDepth)bs_getProcAddress(module, "_val_bs_clearDepth");
    functions.bs_clearDepthStencil = (PFN_bs_clearDepthStencil)bs_getProcAddress(module, "_val_bs_clearDepthStencil");
    functions.bs_clearColor = (PFN_bs_clearColor)bs_getProcAddress(module, "_val_bs_clearColor");
    functions.bs_stencilReference = (PFN_bs_stencilReference)bs_getProcAddress(module, "_val_bs_stencilReference");
    functions.bs_cull = (PFN_bs_cull)bs_getProcAddress(module, "_val_bs_cull");
    functions.bs_setLineWidth = (PFN_bs_setLineWidth)bs_getProcAddress(module, "_val_bs_setLineWidth");
    functions.bs_batchSize = (PFN_bs_batchSize)bs_getProcAddress(module, "_val_bs_batchSize");
    functions.bs_render = (PFN_bs_render)bs_getProcAddress(module, "_val_bs_render");
    functions.bs_barrier = (PFN_bs_barrier)bs_getProcAddress(module, "_val_bs_barrier");
    functions.bs_rayTrace = (PFN_bs_rayTrace)bs_getProcAddress(module, "_val_bs_rayTrace");
    functions.bs_rayTracer = (PFN_bs_rayTracer)bs_getProcAddress(module, "_val_bs_rayTracer");
    functions.bs_accelerateAabb = (PFN_bs_accelerateAabb)bs_getProcAddress(module, "_val_bs_accelerateAabb");
    functions.bs_accelerateBatch = (PFN_bs_accelerateBatch)bs_getProcAddress(module, "_val_bs_accelerateBatch");
    functions.bs_build = (PFN_bs_build)bs_getProcAddress(module, "_val_bs_build");
    functions.bs_destroyRayTracer = (PFN_bs_destroyRayTracer)bs_getProcAddress(module, "_val_bs_destroyRayTracer");
    functions.bs_dispatchAsync = (PFN_bs_dispatchAsync)bs_getProcAddress(module, "_val_bs_dispatchAsync");
    functions.bs_bufferView = (PFN_bs_bufferView)bs_getProcAddress(module, "_val_bs_bufferView");
    functions.bs_buffer = (PFN_bs_buffer)bs_getProcAddress(module, "_val_bs_buffer");
    functions.bs_bufferIsMapped = (PFN_bs_bufferIsMapped)bs_getProcAddress(module, "_val_bs_bufferIsMapped");
    functions.bs_bufferMap = (PFN_bs_bufferMap)bs_getProcAddress(module, "_val_bs_bufferMap");
    functions.bs_mapBuffer = (PFN_bs_mapBuffer)bs_getProcAddress(module, "_val_bs_mapBuffer");
    functions.bs_unmapBuffer = (PFN_bs_unmapBuffer)bs_getProcAddress(module, "_val_bs_unmapBuffer");
    functions.bs_stageNull = (PFN_bs_stageNull)bs_getProcAddress(module, "_val_bs_stageNull");
    functions.bs_stageList = (PFN_bs_stageList)bs_getProcAddress(module, "_val_bs_stageList");
    functions.bs_stageImage = (PFN_bs_stageImage)bs_getProcAddress(module, "_val_bs_stageImage");
    functions.bs_destroyBuffer = (PFN_bs_destroyBuffer)bs_getProcAddress(module, "_val_bs_destroyBuffer");
    functions.bs_copyAsync = (PFN_bs_copyAsync)bs_getProcAddress(module, "_val_bs_copyAsync");
    functions.bs_setBufferAsync = (PFN_bs_setBufferAsync)bs_getProcAddress(module, "_val_bs_setBufferAsync");
    functions.bs_batch = (PFN_bs_batch)bs_getProcAddress(module, "_val_bs_batch");
    functions.bs_queryAttribute = (PFN_bs_queryAttribute)bs_getProcAddress(module, "_val_bs_queryAttribute");
    functions.bs_canPushBatch = (PFN_bs_canPushBatch)bs_getProcAddress(module, "_val_bs_canPushBatch");
    functions.bs_batchIsIndexed = (PFN_bs_batchIsIndexed)bs_getProcAddress(module, "_val_bs_batchIsIndexed");
    functions.bs_minimizeBatch = (PFN_bs_minimizeBatch)bs_getProcAddress(module, "_val_bs_minimizeBatch");
    functions.bs_pushBatch = (PFN_bs_pushBatch)bs_getProcAddress(module, "_val_bs_pushBatch");
    functions.bs_unpushBatch = (PFN_bs_unpushBatch)bs_getProcAddress(module, "_val_bs_unpushBatch");
    functions.bs_destroyBatch = (PFN_bs_destroyBatch)bs_getProcAddress(module, "_val_bs_destroyBatch");
    functions.bs_ensureBatchSize = (PFN_bs_ensureBatchSize)bs_getProcAddress(module, "_val_bs_ensureBatchSize");
    functions.bs_batchVertex = (PFN_bs_batchVertex)bs_getProcAddress(module, "_val_bs_batchVertex");
    functions.bs_batchRange = (PFN_bs_batchRange)bs_getProcAddress(module, "_val_bs_batchRange");
    functions.bs_pushIndex = (PFN_bs_pushIndex)bs_getProcAddress(module, "_val_bs_pushIndex");
    functions.bs_pushIndices = (PFN_bs_pushIndices)bs_getProcAddress(module, "_val_bs_pushIndices");
    functions.bs_batchCube = (PFN_bs_batchCube)bs_getProcAddress(module, "_val_bs_batchCube");
    functions.bs_pushCube = (PFN_bs_pushCube)bs_getProcAddress(module, "_val_bs_pushCube");
    functions.bs_batchCone = (PFN_bs_batchCone)bs_getProcAddress(module, "_val_bs_batchCone");
    functions.bs_pushCone = (PFN_bs_pushCone)bs_getProcAddress(module, "_val_bs_pushCone");
    functions.bs_batchQuad = (PFN_bs_batchQuad)bs_getProcAddress(module, "_val_bs_batchQuad");
    functions.bs_pushQuad = (PFN_bs_pushQuad)bs_getProcAddress(module, "_val_bs_pushQuad");
    functions.bs_batchTriangle = (PFN_bs_batchTriangle)bs_getProcAddress(module, "_val_bs_batchTriangle");
    functions.bs_pushTriangle = (PFN_bs_pushTriangle)bs_getProcAddress(module, "_val_bs_pushTriangle");
    functions.bs_batchLine = (PFN_bs_batchLine)bs_getProcAddress(module, "_val_bs_batchLine");
    functions.bs_pushLine = (PFN_bs_pushLine)bs_getProcAddress(module, "_val_bs_pushLine");
    functions.bs_batchPoint = (PFN_bs_batchPoint)bs_getProcAddress(module, "_val_bs_batchPoint");
    functions.bs_pushPoint = (PFN_bs_pushPoint)bs_getProcAddress(module, "_val_bs_pushPoint");
    functions.bs_batchAabb = (PFN_bs_batchAabb)bs_getProcAddress(module, "_val_bs_batchAabb");
    functions.bs_pushAabb = (PFN_bs_pushAabb)bs_getProcAddress(module, "_val_bs_pushAabb");
    functions.bs_batchSphere = (PFN_bs_batchSphere)bs_getProcAddress(module, "_val_bs_batchSphere");
    functions.bs_pushSphere = (PFN_bs_pushSphere)bs_getProcAddress(module, "_val_bs_pushSphere");
    functions.bs_batchPyramid = (PFN_bs_batchPyramid)bs_getProcAddress(module, "_val_bs_batchPyramid");
    functions.bs_pushPyramid = (PFN_bs_pushPyramid)bs_getProcAddress(module, "_val_bs_pushPyramid");
    functions.bs_batchBipyramid = (PFN_bs_batchBipyramid)bs_getProcAddress(module, "_val_bs_batchBipyramid");
    functions.bs_pushBipyramid = (PFN_bs_pushBipyramid)bs_getProcAddress(module, "_val_bs_pushBipyramid");
    functions.bs_batchPrimitive = (PFN_bs_batchPrimitive)bs_getProcAddress(module, "_val_bs_batchPrimitive");
    functions.bs_pushPrimitive = (PFN_bs_pushPrimitive)bs_getProcAddress(module, "_val_bs_pushPrimitive");
    functions.bs_batchMesh = (PFN_bs_batchMesh)bs_getProcAddress(module, "_val_bs_batchMesh");
    functions.bs_pushMesh = (PFN_bs_pushMesh)bs_getProcAddress(module, "_val_bs_pushMesh");
    functions.bs_batchModel = (PFN_bs_batchModel)bs_getProcAddress(module, "_val_bs_batchModel");
    functions.bs_pushModel = (PFN_bs_pushModel)bs_getProcAddress(module, "_val_bs_pushModel");
    functions.bs_autoResizeRenderer = (PFN_bs_autoResizeRenderer)bs_getProcAddress(module, "_val_bs_autoResizeRenderer");
    functions.bs_renderer = (PFN_bs_renderer)bs_getProcAddress(module, "_val_bs_renderer");
    functions.bs_output = (PFN_bs_output)bs_getProcAddress(module, "_val_bs_output");
    functions.bs_input = (PFN_bs_input)bs_getProcAddress(module, "_val_bs_input");
    functions.bs_dependency = (PFN_bs_dependency)bs_getProcAddress(module, "_val_bs_dependency");
    functions.bs_renderPass = (PFN_bs_renderPass)bs_getProcAddress(module, "_val_bs_renderPass");
    functions.bs_framebuffer = (PFN_bs_framebuffer)bs_getProcAddress(module, "_val_bs_framebuffer");
    functions.bs_runPass = (PFN_bs_runPass)bs_getProcAddress(module, "_val_bs_runPass");
    functions.bs_rendererIsDynamic = (PFN_bs_rendererIsDynamic)bs_getProcAddress(module, "_val_bs_rendererIsDynamic");
    functions.bs_beginRender = (PFN_bs_beginRender)bs_getProcAddress(module, "_val_bs_beginRender");
    functions.bs_endRender = (PFN_bs_endRender)bs_getProcAddress(module, "_val_bs_endRender");
    functions.bs_destroyRenderer = (PFN_bs_destroyRenderer)bs_getProcAddress(module, "_val_bs_destroyRenderer");
    functions.bs_resizeRenderer = (PFN_bs_resizeRenderer)bs_getProcAddress(module, "_val_bs_resizeRenderer");
    functions.bs_queueFamily = (PFN_bs_queueFamily)bs_getProcAddress(module, "_val_bs_queueFamily");
    functions.bs_present = (PFN_bs_present)bs_getProcAddress(module, "_val_bs_present");
    functions.bs_acquire = (PFN_bs_acquire)bs_getProcAddress(module, "_val_bs_acquire");
    functions.bs_queueSwap = (PFN_bs_queueSwap)bs_getProcAddress(module, "_val_bs_queueSwap");
    functions.bs_enqueue = (PFN_bs_enqueue)bs_getProcAddress(module, "_val_bs_enqueue");
    functions.bs_queue = (PFN_bs_queue)bs_getProcAddress(module, "_val_bs_queue");
    functions.bs_destroyQueue = (PFN_bs_destroyQueue)bs_getProcAddress(module, "_val_bs_destroyQueue");
    functions.bs_stallGPU = (PFN_bs_stallGPU)bs_getProcAddress(module, "_val_bs_stallGPU");
    functions.bs_stallQueue = (PFN_bs_stallQueue)bs_getProcAddress(module, "_val_bs_stallQueue");
    functions.bs_stall = (PFN_bs_stall)bs_getProcAddress(module, "_val_bs_stall");
    functions.bs_poll = (PFN_bs_poll)bs_getProcAddress(module, "_val_bs_poll");
    functions.bs_image = (PFN_bs_image)bs_getProcAddress(module, "_val_bs_image");
    functions.bs_transition = (PFN_bs_transition)bs_getProcAddress(module, "_val_bs_transition");
    functions.bs_peekPng = (PFN_bs_peekPng)bs_getProcAddress(module, "_val_bs_peekPng");
    functions.bs_loadPngData = (PFN_bs_loadPngData)bs_getProcAddress(module, "_val_bs_loadPngData");
    functions.bs_loadPng = (PFN_bs_loadPng)bs_getProcAddress(module, "_val_bs_loadPng");
    functions.bs_peekFile = (PFN_bs_peekFile)bs_getProcAddress(module, "_val_bs_peekFile");
    functions.bs_savePng = (PFN_bs_savePng)bs_getProcAddress(module, "_val_bs_savePng");
    functions.bs_encodePng = (PFN_bs_encodePng)bs_getProcAddress(module, "_val_bs_encodePng");
    functions.bs_destroyImage = (PFN_bs_destroyImage)bs_getProcAddress(module, "_val_bs_destroyImage");
    functions.bs_resizeImage = (PFN_bs_resizeImage)bs_getProcAddress(module, "_val_bs_resizeImage");
    functions.bs_queryImageIndexHash = (PFN_bs_queryImageIndexHash)bs_getProcAddress(module, "_val_bs_queryImageIndexHash");
    functions.bs_queryImageIndex = (PFN_bs_queryImageIndex)bs_getProcAddress(module, "_val_bs_queryImageIndex");
    functions.bs_copyImageToBufferAsync = (PFN_bs_copyImageToBufferAsync)bs_getProcAddress(module, "_val_bs_copyImageToBufferAsync");
    functions.bs_copyBufferToImage = (PFN_bs_copyBufferToImage)bs_getProcAddress(module, "_val_bs_copyBufferToImage");
    functions.bs_blit = (PFN_bs_blit)bs_getProcAddress(module, "_val_bs_blit");
    functions.bs_loadImage = (PFN_bs_loadImage)bs_getProcAddress(module, "_val_bs_loadImage");
    functions.bs_isStencilFormat = (PFN_bs_isStencilFormat)bs_getProcAddress(module, "_val_bs_isStencilFormat");
    functions.bs_isDepthFormat = (PFN_bs_isDepthFormat)bs_getProcAddress(module, "_val_bs_isDepthFormat");
    functions.bs_hasAlpha = (PFN_bs_hasAlpha)bs_getProcAddress(module, "_val_bs_hasAlpha");
    functions.bs_destroySampler = (PFN_bs_destroySampler)bs_getProcAddress(module, "_val_bs_destroySampler");
    functions.bs_sampler = (PFN_bs_sampler)bs_getProcAddress(module, "_val_bs_sampler");
    functions.bs_loadAtlas = (PFN_bs_loadAtlas)bs_getProcAddress(module, "_val_bs_loadAtlas");
    functions.bs_atlasCoordinates = (PFN_bs_atlasCoordinates)bs_getProcAddress(module, "_val_bs_atlasCoordinates");
    functions.bs_mirrorUV = (PFN_bs_mirrorUV)bs_getProcAddress(module, "_val_bs_mirrorUV");
    functions.bs_flipUV = (PFN_bs_flipUV)bs_getProcAddress(module, "_val_bs_flipUV");
    functions.bs_atlasSize = (PFN_bs_atlasSize)bs_getProcAddress(module, "_val_bs_atlasSize");
    functions.bs_queryAtlasHash = (PFN_bs_queryAtlasHash)bs_getProcAddress(module, "_val_bs_queryAtlasHash");
    functions.bs_queryAtlas = (PFN_bs_queryAtlas)bs_getProcAddress(module, "_val_bs_queryAtlas");
    functions.bs_destroyAtlas = (PFN_bs_destroyAtlas)bs_getProcAddress(module, "_val_bs_destroyAtlas");
    functions.bs_loadAtlasMemory = (PFN_bs_loadAtlasMemory)bs_getProcAddress(module, "_val_bs_loadAtlasMemory");
    functions.bs_parseArgs = (PFN_bs_parseArgs)bs_getProcAddress(module, "_val_bs_parseArgs");
    functions.bs_configureQueuesCount = (PFN_bs_configureQueuesCount)bs_getProcAddress(module, "_val_bs_configureQueuesCount");
    functions.bs_ini = (PFN_bs_ini)bs_getProcAddress(module, "_val_bs_ini");
    functions.bs_queryProcedures = (PFN_bs_queryProcedures)bs_getProcAddress(module, "_val_bs_queryProcedures");
    functions.bs_queueSemaphore = (PFN_bs_queueSemaphore)bs_getProcAddress(module, "_val_bs_queueSemaphore");
    functions.bs_acquisitionSemaphore = (PFN_bs_acquisitionSemaphore)bs_getProcAddress(module, "_val_bs_acquisitionSemaphore");
    functions.bs_resetQueue = (PFN_bs_resetQueue)bs_getProcAddress(module, "_val_bs_resetQueue");
    functions.bs_pushQueue = (PFN_bs_pushQueue)bs_getProcAddress(module, "_val_bs_pushQueue");
    functions.bsi_nameHandle = (PFN_bsi_nameHandle)bs_getProcAddress(module, "_val_bsi_nameHandle");
    functions.bs_beginEnumeration = (PFN_bs_beginEnumeration)bs_getProcAddress(module, "_val_bs_beginEnumeration");
    functions.bs_enumerateJson = (PFN_bs_enumerateJson)bs_getProcAddress(module, "_val_bs_enumerateJson");
    functions.bs_jsonRoot = (PFN_bs_jsonRoot)bs_getProcAddress(module, "_val_bs_jsonRoot");
    functions.bs_ensureJsonMutable = (PFN_bs_ensureJsonMutable)bs_getProcAddress(module, "_val_bs_ensureJsonMutable");
    functions.bs_jsonCopy = (PFN_bs_jsonCopy)bs_getProcAddress(module, "_val_bs_jsonCopy");
    functions.bs_saveJson = (PFN_bs_saveJson)bs_getProcAddress(module, "_val_bs_saveJson");
    functions.bs_emptyJson = (PFN_bs_emptyJson)bs_getProcAddress(module, "_val_bs_emptyJson");
    functions.bs_emptyJsonArray = (PFN_bs_emptyJsonArray)bs_getProcAddress(module, "_val_bs_emptyJsonArray");
    functions.bs_json = (PFN_bs_json)bs_getProcAddress(module, "_val_bs_json");
    functions.bs_loadJson = (PFN_bs_loadJson)bs_getProcAddress(module, "_val_bs_loadJson");
    functions.bs_destroyJson = (PFN_bs_destroyJson)bs_getProcAddress(module, "_val_bs_destroyJson");
    functions.bs_parseJsonValue = (PFN_bs_parseJsonValue)bs_getProcAddress(module, "_val_bs_parseJsonValue");
    functions.bs_fetchJson = (PFN_bs_fetchJson)bs_getProcAddress(module, "_val_bs_fetchJson");
    functions.bs_deleteJson = (PFN_bs_deleteJson)bs_getProcAddress(module, "_val_bs_deleteJson");
    functions.bs_ensureJson = (PFN_bs_ensureJson)bs_getProcAddress(module, "_val_bs_ensureJson");
    functions.bs_jsonValueFromObject = (PFN_bs_jsonValueFromObject)bs_getProcAddress(module, "_val_bs_jsonValueFromObject");
    functions.bs_jsonValueFromRoot = (PFN_bs_jsonValueFromRoot)bs_getProcAddress(module, "_val_bs_jsonValueFromRoot");
    functions.bs_jsonValueFromBool = (PFN_bs_jsonValueFromBool)bs_getProcAddress(module, "_val_bs_jsonValueFromBool");
    functions.bs_jsonValueFromInteger = (PFN_bs_jsonValueFromInteger)bs_getProcAddress(module, "_val_bs_jsonValueFromInteger");
    functions.bs_jsonValueFromFloat = (PFN_bs_jsonValueFromFloat)bs_getProcAddress(module, "_val_bs_jsonValueFromFloat");
    functions.bs_jsonValueFromString = (PFN_bs_jsonValueFromString)bs_getProcAddress(module, "_val_bs_jsonValueFromString");
    functions.bs_jsonValueFromStringPointer = (PFN_bs_jsonValueFromStringPointer)bs_getProcAddress(module, "_val_bs_jsonValueFromStringPointer");
    functions.bs_jsonValueFromDateTime = (PFN_bs_jsonValueFromDateTime)bs_getProcAddress(module, "_val_bs_jsonValueFromDateTime");
    functions.bs_jsonObject = (PFN_bs_jsonObject)bs_getProcAddress(module, "_val_bs_jsonObject");
    functions.bs_jsonArray = (PFN_bs_jsonArray)bs_getProcAddress(module, "_val_bs_jsonArray");
    functions.bs_jsonVec2 = (PFN_bs_jsonVec2)bs_getProcAddress(module, "_val_bs_jsonVec2");
    functions.bs_jsonVec3 = (PFN_bs_jsonVec3)bs_getProcAddress(module, "_val_bs_jsonVec3");
    functions.bs_jsonVec4 = (PFN_bs_jsonVec4)bs_getProcAddress(module, "_val_bs_jsonVec4");
    functions.bs_jsonRGBA = (PFN_bs_jsonRGBA)bs_getProcAddress(module, "_val_bs_jsonRGBA");
    functions.bs_logSection = (PFN_bs_logSection)bs_getProcAddress(module, "_val_bs_logSection");
    functions.bs_logEndOfSection = (PFN_bs_logEndOfSection)bs_getProcAddress(module, "_val_bs_logEndOfSection");
    functions.bs_logWithTimestamp = (PFN_bs_logWithTimestamp)bs_getProcAddress(module, "_val_bs_logWithTimestamp");
    functions.bs_log = (PFN_bs_log)bs_getProcAddress(module, "_val_bs_log");
    functions.bs_info = (PFN_bs_info)bs_getProcAddress(module, "_val_bs_info");
    functions.bs_warn = (PFN_bs_warn)bs_getProcAddress(module, "_val_bs_warn");
    functions.bs_critical = (PFN_bs_critical)bs_getProcAddress(module, "_val_bs_critical");
    functions.bs_instance = (PFN_bs_instance)bs_getProcAddress(module, "_val_bs_instance");
    functions.bs_args = (PFN_bs_args)bs_getProcAddress(module, "_val_bs_args");
    functions.bs_features = (PFN_bs_features)bs_getProcAddress(module, "_val_bs_features");
    functions.bs_props = (PFN_bs_props)bs_getProcAddress(module, "_val_bs_props");
    functions.bs_config = (PFN_bs_config)bs_getProcAddress(module, "_val_bs_config");
    functions.bs_system = (PFN_bs_system)bs_getProcAddress(module, "_val_bs_system");
    functions.bs_createThread = (PFN_bs_createThread)bs_getProcAddress(module, "_val_bs_createThread");
    functions.bs_formatStringLength = (PFN_bs_formatStringLength)bs_getProcAddress(module, "_val_bs_formatStringLength");
    functions.bs_checkStringPool = (PFN_bs_checkStringPool)bs_getProcAddress(module, "_val_bs_checkStringPool");
    functions.bs_stringAlloc = (PFN_bs_stringAlloc)bs_getProcAddress(module, "_val_bs_stringAlloc");
    functions.bs_emptyString = (PFN_bs_emptyString)bs_getProcAddress(module, "_val_bs_emptyString");
    functions.bs_string = (PFN_bs_string)bs_getProcAddress(module, "_val_bs_string");
    functions.bs_toUpper = (PFN_bs_toUpper)bs_getProcAddress(module, "_val_bs_toUpper");
    functions.bs_toLower = (PFN_bs_toLower)bs_getProcAddress(module, "_val_bs_toLower");
    functions.bs_hash = (PFN_bs_hash)bs_getProcAddress(module, "_val_bs_hash");
    functions.bs_stringHash = (PFN_bs_stringHash)bs_getProcAddress(module, "_val_bs_stringHash");
    functions.bs_startsWith = (PFN_bs_startsWith)bs_getProcAddress(module, "_val_bs_startsWith");
    functions.bs_endsWith = (PFN_bs_endsWith)bs_getProcAddress(module, "_val_bs_endsWith");
    functions.bs_lastChar = (PFN_bs_lastChar)bs_getProcAddress(module, "_val_bs_lastChar");
    functions.bs_stringContainsChar = (PFN_bs_stringContainsChar)bs_getProcAddress(module, "_val_bs_stringContainsChar");
    functions.bs_workingDirectory = (PFN_bs_workingDirectory)bs_getProcAddress(module, "_val_bs_workingDirectory");
    functions.bs_setWorkingDirectory = (PFN_bs_setWorkingDirectory)bs_getProcAddress(module, "_val_bs_setWorkingDirectory");
    functions.bs_executablePath = (PFN_bs_executablePath)bs_getProcAddress(module, "_val_bs_executablePath");
    functions.bs_appdataPath = (PFN_bs_appdataPath)bs_getProcAddress(module, "_val_bs_appdataPath");
    functions.bs_shortenString = (PFN_bs_shortenString)bs_getProcAddress(module, "_val_bs_shortenString");
    functions.bs_appendChar = (PFN_bs_appendChar)bs_getProcAddress(module, "_val_bs_appendChar");
    functions.bs_removeCharRange = (PFN_bs_removeCharRange)bs_getProcAddress(module, "_val_bs_removeCharRange");
    functions.bs_insertChar = (PFN_bs_insertChar)bs_getProcAddress(module, "_val_bs_insertChar");
    functions.bs_appendPath = (PFN_bs_appendPath)bs_getProcAddress(module, "_val_bs_appendPath");
    functions.bs_replaceCharOccurrences = (PFN_bs_replaceCharOccurrences)bs_getProcAddress(module, "_val_bs_replaceCharOccurrences");
    functions.bs_strndup = (PFN_bs_strndup)bs_getProcAddress(module, "_val_bs_strndup");
    functions.bs_strnlen = (PFN_bs_strnlen)bs_getProcAddress(module, "_val_bs_strnlen");
    functions.bs_strsep = (PFN_bs_strsep)bs_getProcAddress(module, "_val_bs_strsep");
    functions.bs_memmem = (PFN_bs_memmem)bs_getProcAddress(module, "_val_bs_memmem");
    functions.bs_alignUp = (PFN_bs_alignUp)bs_getProcAddress(module, "_val_bs_alignUp");
    functions.bs_widen = (PFN_bs_widen)bs_getProcAddress(module, "_val_bs_widen");
    functions.bs_unwiden = (PFN_bs_unwiden)bs_getProcAddress(module, "_val_bs_unwiden");
    functions.bs_charStringV = (PFN_bs_charStringV)bs_getProcAddress(module, "_val_bs_charStringV");
    functions.bs_free = (PFN_bs_free)bs_getProcAddress(module, "_val_bs_free");
    functions.bs_malloc = (PFN_bs_malloc)bs_getProcAddress(module, "_val_bs_malloc");
    functions.bs_calloc = (PFN_bs_calloc)bs_getProcAddress(module, "_val_bs_calloc");
    functions.bs_realloc = (PFN_bs_realloc)bs_getProcAddress(module, "_val_bs_realloc");
    functions.bs_listContains = (PFN_bs_listContains)bs_getProcAddress(module, "_val_bs_listContains");
    functions.bs_fetchUnit = (PFN_bs_fetchUnit)bs_getProcAddress(module, "_val_bs_fetchUnit");
    functions.bs_fetchLast = (PFN_bs_fetchLast)bs_getProcAddress(module, "_val_bs_fetchLast");
    functions.bs_ensureSize = (PFN_bs_ensureSize)bs_getProcAddress(module, "_val_bs_ensureSize");
    functions.bs_erase = (PFN_bs_erase)bs_getProcAddress(module, "_val_bs_erase");
    functions.bs_pushBack = (PFN_bs_pushBack)bs_getProcAddress(module, "_val_bs_pushBack");
    functions.bs_pushBackList = (PFN_bs_pushBackList)bs_getProcAddress(module, "_val_bs_pushBackList");
    functions.bs_destroyList = (PFN_bs_destroyList)bs_getProcAddress(module, "_val_bs_destroyList");
    functions.bs_seekList = (PFN_bs_seekList)bs_getProcAddress(module, "_val_bs_seekList");
    functions.bs_minimizeList = (PFN_bs_minimizeList)bs_getProcAddress(module, "_val_bs_minimizeList");
    functions.bs_list = (PFN_bs_list)bs_getProcAddress(module, "_val_bs_list");
    functions.bs_guidToString = (PFN_bs_guidToString)bs_getProcAddress(module, "_val_bs_guidToString");
    functions.bs_stringToGuid = (PFN_bs_stringToGuid)bs_getProcAddress(module, "_val_bs_stringToGuid");
    functions.bs_sameGuid = (PFN_bs_sameGuid)bs_getProcAddress(module, "_val_bs_sameGuid");
    functions.bs_guid = (PFN_bs_guid)bs_getProcAddress(module, "_val_bs_guid");
    functions.bs_guidIsNull = (PFN_bs_guidIsNull)bs_getProcAddress(module, "_val_bs_guidIsNull");
    functions.bs_numDigits = (PFN_bs_numDigits)bs_getProcAddress(module, "_val_bs_numDigits");
    functions.bs_directoryExists = (PFN_bs_directoryExists)bs_getProcAddress(module, "_val_bs_directoryExists");
    functions.bs_fileExtension = (PFN_bs_fileExtension)bs_getProcAddress(module, "_val_bs_fileExtension");
    functions.bs_fileExtensionIs = (PFN_bs_fileExtensionIs)bs_getProcAddress(module, "_val_bs_fileExtensionIs");
    functions.bs_fileName = (PFN_bs_fileName)bs_getProcAddress(module, "_val_bs_fileName");
    functions.bs_appendFile = (PFN_bs_appendFile)bs_getProcAddress(module, "_val_bs_appendFile");
    functions.bs_saveFile = (PFN_bs_saveFile)bs_getProcAddress(module, "_val_bs_saveFile");
    functions.bs_convertWin32Path = (PFN_bs_convertWin32Path)bs_getProcAddress(module, "_val_bs_convertWin32Path");
    functions.bs_ensureDirectory = (PFN_bs_ensureDirectory)bs_getProcAddress(module, "_val_bs_ensureDirectory");
    functions.bs_fileModifiedDate = (PFN_bs_fileModifiedDate)bs_getProcAddress(module, "_val_bs_fileModifiedDate");
    functions.bs_setFileModifiedDate = (PFN_bs_setFileModifiedDate)bs_getProcAddress(module, "_val_bs_setFileModifiedDate");
    functions.bs_fullPath = (PFN_bs_fullPath)bs_getProcAddress(module, "_val_bs_fullPath");
    functions.bs_fileExists = (PFN_bs_fileExists)bs_getProcAddress(module, "_val_bs_fileExists");
    functions.bs_toLong = (PFN_bs_toLong)bs_getProcAddress(module, "_val_bs_toLong");
    functions.bs_toULong = (PFN_bs_toULong)bs_getProcAddress(module, "_val_bs_toULong");
    functions.bs_toDouble = (PFN_bs_toDouble)bs_getProcAddress(module, "_val_bs_toDouble");
    functions.bs_model = (PFN_bs_model)bs_getProcAddress(module, "_val_bs_model");
    functions.bs_destroyModel = (PFN_bs_destroyModel)bs_getProcAddress(module, "_val_bs_destroyModel");
    functions.bs_interpolateRotation = (PFN_bs_interpolateRotation)bs_getProcAddress(module, "_val_bs_interpolateRotation");
    functions.bs_interpolateTranslation = (PFN_bs_interpolateTranslation)bs_getProcAddress(module, "_val_bs_interpolateTranslation");
    functions.bs_interpolateScale = (PFN_bs_interpolateScale)bs_getProcAddress(module, "_val_bs_interpolateScale");
    functions.bs_boneTransform = (PFN_bs_boneTransform)bs_getProcAddress(module, "_val_bs_boneTransform");
    functions.bs_bonePosition = (PFN_bs_bonePosition)bs_getProcAddress(module, "_val_bs_bonePosition");
    functions.bs_transformBone = (PFN_bs_transformBone)bs_getProcAddress(module, "_val_bs_transformBone");
    functions.bs_blendPose = (PFN_bs_blendPose)bs_getProcAddress(module, "_val_bs_blendPose");
    functions.bs_bone = (PFN_bs_bone)bs_getProcAddress(module, "_val_bs_bone");
    functions.bs_fabrik = (PFN_bs_fabrik)bs_getProcAddress(module, "_val_bs_fabrik");
    functions.bs_bindPose = (PFN_bs_bindPose)bs_getProcAddress(module, "_val_bs_bindPose");
    functions.bs_keyframePosition = (PFN_bs_keyframePosition)bs_getProcAddress(module, "_val_bs_keyframePosition");
    functions.bs_keyframeRotation = (PFN_bs_keyframeRotation)bs_getProcAddress(module, "_val_bs_keyframeRotation");
    functions.bs_keyframeScale = (PFN_bs_keyframeScale)bs_getProcAddress(module, "_val_bs_keyframeScale");
    functions.bs_loadAnimation = (PFN_bs_loadAnimation)bs_getProcAddress(module, "_val_bs_loadAnimation");
    functions.bs_queryBoneId = (PFN_bs_queryBoneId)bs_getProcAddress(module, "_val_bs_queryBoneId");
    functions.bs_queryArmature = (PFN_bs_queryArmature)bs_getProcAddress(module, "_val_bs_queryArmature");
    functions.bs_queryBone = (PFN_bs_queryBone)bs_getProcAddress(module, "_val_bs_queryBone");
    functions.bs_queryMesh = (PFN_bs_queryMesh)bs_getProcAddress(module, "_val_bs_queryMesh");
    functions.bs_queryMeshHash = (PFN_bs_queryMeshHash)bs_getProcAddress(module, "_val_bs_queryMeshHash");
    functions.bs_queryMaterial = (PFN_bs_queryMaterial)bs_getProcAddress(module, "_val_bs_queryMaterial");
    functions.bs_idName = (PFN_bs_idName)bs_getProcAddress(module, "_val_bs_idName");
    functions.bs_resetObject = (PFN_bs_resetObject)bs_getProcAddress(module, "_val_bs_resetObject");
    functions.bs_object = (PFN_bs_object)bs_getProcAddress(module, "_val_bs_object");
    functions.bs_packages = (PFN_bs_packages)bs_getProcAddress(module, "_val_bs_packages");
    functions.bs_objectSources = (PFN_bs_objectSources)bs_getProcAddress(module, "_val_bs_objectSources");
    functions.bs_destroyResource = (PFN_bs_destroyResource)bs_getProcAddress(module, "_val_bs_destroyResource");
    functions.bs_queryResource = (PFN_bs_queryResource)bs_getProcAddress(module, "_val_bs_queryResource");
    functions.bs_queryPackage = (PFN_bs_queryPackage)bs_getProcAddress(module, "_val_bs_queryPackage");
    functions.bs_loadResource = (PFN_bs_loadResource)bs_getProcAddress(module, "_val_bs_loadResource");
    functions.bs_loadPackage = (PFN_bs_loadPackage)bs_getProcAddress(module, "_val_bs_loadPackage");
    functions.bs_configureSource = (PFN_bs_configureSource)bs_getProcAddress(module, "_val_bs_configureSource");
    functions.bs_exists = (PFN_bs_exists)bs_getProcAddress(module, "_val_bs_exists");
    functions.bs_fetch = (PFN_bs_fetch)bs_getProcAddress(module, "_val_bs_fetch");
    functions.bs_shouldLoadId = (PFN_bs_shouldLoadId)bs_getProcAddress(module, "_val_bs_shouldLoadId");
    functions.bs_shader = (PFN_bs_shader)bs_getProcAddress(module, "_val_bs_shader");
    functions.bs_destroyShader = (PFN_bs_destroyShader)bs_getProcAddress(module, "_val_bs_destroyShader");
    functions.bs_computePipeline = (PFN_bs_computePipeline)bs_getProcAddress(module, "_val_bs_computePipeline");
    functions.bs_destroyComputePipeline = (PFN_bs_destroyComputePipeline)bs_getProcAddress(module, "_val_bs_destroyComputePipeline");
    functions.bs_queryPipeline = (PFN_bs_queryPipeline)bs_getProcAddress(module, "_val_bs_queryPipeline");
    functions.bs_pipelineHash = (PFN_bs_pipelineHash)bs_getProcAddress(module, "_val_bs_pipelineHash");
    functions.bs_pipeline = (PFN_bs_pipeline)bs_getProcAddress(module, "_val_bs_pipeline");
    functions.bs_destroyPipeline = (PFN_bs_destroyPipeline)bs_getProcAddress(module, "_val_bs_destroyPipeline");
    functions.bs_pushConstant = (PFN_bs_pushConstant)bs_getProcAddress(module, "_val_bs_pushConstant");
    functions.bs_rayTracingPipeline = (PFN_bs_rayTracingPipeline)bs_getProcAddress(module, "_val_bs_rayTracingPipeline");
    functions.bs_loadBindings = (PFN_bs_loadBindings)bs_getProcAddress(module, "_val_bs_loadBindings");
    functions.bs_binding = (PFN_bs_binding)bs_getProcAddress(module, "_val_bs_binding");
    functions.bs_bindImage = (PFN_bs_bindImage)bs_getProcAddress(module, "_val_bs_bindImage");
    functions.bs_bindImages = (PFN_bs_bindImages)bs_getProcAddress(module, "_val_bs_bindImages");
    functions.bs_bindBuffer = (PFN_bs_bindBuffer)bs_getProcAddress(module, "_val_bs_bindBuffer");
    functions.bs_bindBuffers = (PFN_bs_bindBuffers)bs_getProcAddress(module, "_val_bs_bindBuffers");
    functions.bs_bindAccelerationStructure = (PFN_bs_bindAccelerationStructure)bs_getProcAddress(module, "_val_bs_bindAccelerationStructure");
    functions.bs_bindAccelerationStructures = (PFN_bs_bindAccelerationStructures)bs_getProcAddress(module, "_val_bs_bindAccelerationStructures");
    functions.bs_pushDescriptors = (PFN_bs_pushDescriptors)bs_getProcAddress(module, "_val_bs_pushDescriptors");
    functions.bs_pushBindings = (PFN_bs_pushBindings)bs_getProcAddress(module, "_val_bs_pushBindings");
    functions.bs_queryBindSet = (PFN_bs_queryBindSet)bs_getProcAddress(module, "_val_bs_queryBindSet");
    functions.bs_queryBinding = (PFN_bs_queryBinding)bs_getProcAddress(module, "_val_bs_queryBinding");
    functions.bs_configureAttribute = (PFN_bs_configureAttribute)bs_getProcAddress(module, "_val_bs_configureAttribute");
    functions.bs_timeZoneBias = (PFN_bs_timeZoneBias)bs_getProcAddress(module, "_val_bs_timeZoneBias");
    functions.bs_dateTime = (PFN_bs_dateTime)bs_getProcAddress(module, "_val_bs_dateTime");
    functions.bs_totalSeconds = (PFN_bs_totalSeconds)bs_getProcAddress(module, "_val_bs_totalSeconds");
    functions.bs_isLaterThan = (PFN_bs_isLaterThan)bs_getProcAddress(module, "_val_bs_isLaterThan");
    functions.bs_windowCursorPosition = (PFN_bs_windowCursorPosition)bs_getProcAddress(module, "_val_bs_windowCursorPosition");
    functions.bs_windowPosition = (PFN_bs_windowPosition)bs_getProcAddress(module, "_val_bs_windowPosition");
    functions.bs_screenCursorPosition = (PFN_bs_screenCursorPosition)bs_getProcAddress(module, "_val_bs_screenCursorPosition");
    functions.bs_inputDown = (PFN_bs_inputDown)bs_getProcAddress(module, "_val_bs_inputDown");
    functions.bs_inputHeld = (PFN_bs_inputHeld)bs_getProcAddress(module, "_val_bs_inputHeld");
    functions.bs_inputDownOnce = (PFN_bs_inputDownOnce)bs_getProcAddress(module, "_val_bs_inputDownOnce");
    functions.bs_inputUpOnce = (PFN_bs_inputUpOnce)bs_getProcAddress(module, "_val_bs_inputUpOnce");
    functions.bs_charDown = (PFN_bs_charDown)bs_getProcAddress(module, "_val_bs_charDown");
    functions.bs_charDownOnce = (PFN_bs_charDownOnce)bs_getProcAddress(module, "_val_bs_charDownOnce");
    functions.bs_charUpOnce = (PFN_bs_charUpOnce)bs_getProcAddress(module, "_val_bs_charUpOnce");
    functions.bs_contextInputDown = (PFN_bs_contextInputDown)bs_getProcAddress(module, "_val_bs_contextInputDown");
    functions.bs_contextInputDownOnce = (PFN_bs_contextInputDownOnce)bs_getProcAddress(module, "_val_bs_contextInputDownOnce");
    functions.bs_contextInputUpOnce = (PFN_bs_contextInputUpOnce)bs_getProcAddress(module, "_val_bs_contextInputUpOnce");
    functions.bs_contextCharDown = (PFN_bs_contextCharDown)bs_getProcAddress(module, "_val_bs_contextCharDown");
    functions.bs_contextCharDownOnce = (PFN_bs_contextCharDownOnce)bs_getProcAddress(module, "_val_bs_contextCharDownOnce");
    functions.bs_contextCharUpOnce = (PFN_bs_contextCharUpOnce)bs_getProcAddress(module, "_val_bs_contextCharUpOnce");
    functions.bs_scroll = (PFN_bs_scroll)bs_getProcAddress(module, "_val_bs_scroll");
    functions.bs_resizeWindow = (PFN_bs_resizeWindow)bs_getProcAddress(module, "_val_bs_resizeWindow");
    functions.bs_moveWindow = (PFN_bs_moveWindow)bs_getProcAddress(module, "_val_bs_moveWindow");
    functions.bs_window = (PFN_bs_window)bs_getProcAddress(module, "_val_bs_window");
    functions.bs_swapchain = (PFN_bs_swapchain)bs_getProcAddress(module, "_val_bs_swapchain");
    functions.bs_showWindow = (PFN_bs_showWindow)bs_getProcAddress(module, "_val_bs_showWindow");
    functions.bs_hideWindow = (PFN_bs_hideWindow)bs_getProcAddress(module, "_val_bs_hideWindow");
    functions.bs_device = (PFN_bs_device)bs_getProcAddress(module, "_val_bs_device");
    functions.bs_tick = (PFN_bs_tick)bs_getProcAddress(module, "_val_bs_tick");
    functions.bs_exit = (PFN_bs_exit)bs_getProcAddress(module, "_val_bs_exit");
    functions.bs_setCursor = (PFN_bs_setCursor)bs_getProcAddress(module, "_val_bs_setCursor");
    functions.bs_deltaTime = (PFN_bs_deltaTime)bs_getProcAddress(module, "_val_bs_deltaTime");
    functions.bs_pause = (PFN_bs_pause)bs_getProcAddress(module, "_val_bs_pause");
    functions.bs_advance = (PFN_bs_advance)bs_getProcAddress(module, "_val_bs_advance");
    functions.bs_elapsedTime = (PFN_bs_elapsedTime)bs_getProcAddress(module, "_val_bs_elapsedTime");
    functions.bs_resolution = (PFN_bs_resolution)bs_getProcAddress(module, "_val_bs_resolution");
    functions.bs_titleWindow = (PFN_bs_titleWindow)bs_getProcAddress(module, "_val_bs_titleWindow");
    functions.bs_inFixedTick = (PFN_bs_inFixedTick)bs_getProcAddress(module, "_val_bs_inFixedTick");
    functions.bs_setTargetFramerate = (PFN_bs_setTargetFramerate)bs_getProcAddress(module, "_val_bs_setTargetFramerate");
    functions.bs_timer = (PFN_bs_timer)bs_getProcAddress(module, "_val_bs_timer");
    functions.bs_checkTimer = (PFN_bs_checkTimer)bs_getProcAddress(module, "_val_bs_checkTimer");
    functions.bs_copyToClipboard = (PFN_bs_copyToClipboard)bs_getProcAddress(module, "_val_bs_copyToClipboard");
    functions.bs_appendString = (PFN_bs_appendString)bs_getProcAddress(module, "_val_bs_appendString");
    functions.bs_foreachFile = (PFN_bs_foreachFile)bs_getProcAddress(module, "_val_bs_foreachFile");
    functions.bs_foreachDirectory = (PFN_bs_foreachDirectory)bs_getProcAddress(module, "_val_bs_foreachDirectory");
    functions.bs_numFiles = (PFN_bs_numFiles)bs_getProcAddress(module, "_val_bs_numFiles");
    functions.bs_numDirectories = (PFN_bs_numDirectories)bs_getProcAddress(module, "_val_bs_numDirectories");
    functions.bs_openFile = (PFN_bs_openFile)bs_getProcAddress(module, "_val_bs_openFile");
    functions.bs_closeFile = (PFN_bs_closeFile)bs_getProcAddress(module, "_val_bs_closeFile");
    functions.bs_loadFile = (PFN_bs_loadFile)bs_getProcAddress(module, "_val_bs_loadFile");
    functions.bs_loadFileChunk = (PFN_bs_loadFileChunk)bs_getProcAddress(module, "_val_bs_loadFileChunk");
    functions.bs_deleteFile = (PFN_bs_deleteFile)bs_getProcAddress(module, "_val_bs_deleteFile");
    functions.bs_deleteDirectoryContents = (PFN_bs_deleteDirectoryContents)bs_getProcAddress(module, "_val_bs_deleteDirectoryContents");
    functions.bs_deleteDirectory = (PFN_bs_deleteDirectory)bs_getProcAddress(module, "_val_bs_deleteDirectory");

    #undef bs_getProcAddress
#ifndef _WIN32
    dlclose(module);
#endif
    return &functions;
}

#endif
