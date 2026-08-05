
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

    HMODULE module = NULL;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_val_bs_getFunctions),
        &module);

    functions.bs_callbacks = (PFN_bs_callbacks)GetProcAddress(module, "_val_bs_callbacks");
    functions.bs_imageSwapsCount = (PFN_bs_imageSwapsCount)GetProcAddress(module, "_val_bs_imageSwapsCount");
    functions.bs_samplerSwapsCount = (PFN_bs_samplerSwapsCount)GetProcAddress(module, "_val_bs_samplerSwapsCount");
    functions.bs_bufferSwapsCount = (PFN_bs_bufferSwapsCount)GetProcAddress(module, "_val_bs_bufferSwapsCount");
    functions.bs_queueSwapsCount = (PFN_bs_queueSwapsCount)GetProcAddress(module, "_val_bs_queueSwapsCount");
    functions.bs_rendererSwapsCount = (PFN_bs_rendererSwapsCount)GetProcAddress(module, "_val_bs_rendererSwapsCount");
    functions.bs_writeLogFile = (PFN_bs_writeLogFile)GetProcAddress(module, "_val_bs_writeLogFile");
    functions.bs_v2Mid = (PFN_bs_v2Mid)GetProcAddress(module, "_val_bs_v2Mid");
    functions.bs_v3Mid = (PFN_bs_v3Mid)GetProcAddress(module, "_val_bs_v3Mid");
    functions.bs_m4x3 = (PFN_bs_m4x3)GetProcAddress(module, "_val_bs_m4x3");
    functions.bs_eulToQ = (PFN_bs_eulToQ)GetProcAddress(module, "_val_bs_eulToQ");
    functions.bs_qToEul = (PFN_bs_qToEul)GetProcAddress(module, "_val_bs_qToEul");
    functions.bs_v2CubicBezier = (PFN_bs_v2CubicBezier)GetProcAddress(module, "_val_bs_v2CubicBezier");
    functions.bs_v2QuadBezier = (PFN_bs_v2QuadBezier)GetProcAddress(module, "_val_bs_v2QuadBezier");
    functions.bs_v3CubicBezier = (PFN_bs_v3CubicBezier)GetProcAddress(module, "_val_bs_v3CubicBezier");
    functions.bs_v3QuadBezier = (PFN_bs_v3QuadBezier)GetProcAddress(module, "_val_bs_v3QuadBezier");
    functions.bs_rotateAabb = (PFN_bs_rotateAabb)GetProcAddress(module, "_val_bs_rotateAabb");
    functions.bs_fitAabb = (PFN_bs_fitAabb)GetProcAddress(module, "_val_bs_fitAabb");
    functions.bs_quad = (PFN_bs_quad)GetProcAddress(module, "_val_bs_quad");
    functions.bs_hsvToRgb = (PFN_bs_hsvToRgb)GetProcAddress(module, "_val_bs_hsvToRgb");
    functions.bs_rgbToHsv = (PFN_bs_rgbToHsv)GetProcAddress(module, "_val_bs_rgbToHsv");
    functions.bs_convertYyjsonResult = (PFN_bs_convertYyjsonResult)GetProcAddress(module, "_val_bs_convertYyjsonResult");
    functions.bs_convertVulkanResult = (PFN_bs_convertVulkanResult)GetProcAddress(module, "_val_bs_convertVulkanResult");
    functions.bs_convertWin32Error = (PFN_bs_convertWin32Error)GetProcAddress(module, "_val_bs_convertWin32Error");
    functions.bs_serializeWin32Error = (PFN_bs_serializeWin32Error)GetProcAddress(module, "_val_bs_serializeWin32Error");
    functions.bs_convertErrno = (PFN_bs_convertErrno)GetProcAddress(module, "_val_bs_convertErrno");
    functions.bs_serializeErrno = (PFN_bs_serializeErrno)GetProcAddress(module, "_val_bs_serializeErrno");
    functions.bs_playSound = (PFN_bs_playSound)GetProcAddress(module, "_val_bs_playSound");
    functions.bs_sound = (PFN_bs_sound)GetProcAddress(module, "_val_bs_sound");
    functions.bs_iniAudio = (PFN_bs_iniAudio)GetProcAddress(module, "_val_bs_iniAudio");
    functions.bs_rayVsObb = (PFN_bs_rayVsObb)GetProcAddress(module, "_val_bs_rayVsObb");
    functions.bs_sphereVsPoint = (PFN_bs_sphereVsPoint)GetProcAddress(module, "_val_bs_sphereVsPoint");
    functions.bs_sphereVsObbTest = (PFN_bs_sphereVsObbTest)GetProcAddress(module, "_val_bs_sphereVsObbTest");
    functions.bs_sphereVsObb = (PFN_bs_sphereVsObb)GetProcAddress(module, "_val_bs_sphereVsObb");
    functions.bs_rectangleVsPoint = (PFN_bs_rectangleVsPoint)GetProcAddress(module, "_val_bs_rectangleVsPoint");
    functions.bs_lineVsLine = (PFN_bs_lineVsLine)GetProcAddress(module, "_val_bs_lineVsLine");
    functions.bs_populateVertexDeclaration = (PFN_bs_populateVertexDeclaration)GetProcAddress(module, "_val_bs_populateVertexDeclaration");
    functions.bs_beginComment = (PFN_bs_beginComment)GetProcAddress(module, "_val_bs_beginComment");
    functions.bs_endComment = (PFN_bs_endComment)GetProcAddress(module, "_val_bs_endComment");
    functions.bs_swapchainImage = (PFN_bs_swapchainImage)GetProcAddress(module, "_val_bs_swapchainImage");
    functions.bs_clearStencil = (PFN_bs_clearStencil)GetProcAddress(module, "_val_bs_clearStencil");
    functions.bs_clearDepth = (PFN_bs_clearDepth)GetProcAddress(module, "_val_bs_clearDepth");
    functions.bs_clearDepthStencil = (PFN_bs_clearDepthStencil)GetProcAddress(module, "_val_bs_clearDepthStencil");
    functions.bs_clearColor = (PFN_bs_clearColor)GetProcAddress(module, "_val_bs_clearColor");
    functions.bs_stencilReference = (PFN_bs_stencilReference)GetProcAddress(module, "_val_bs_stencilReference");
    functions.bs_cull = (PFN_bs_cull)GetProcAddress(module, "_val_bs_cull");
    functions.bs_setLineWidth = (PFN_bs_setLineWidth)GetProcAddress(module, "_val_bs_setLineWidth");
    functions.bs_batchSize = (PFN_bs_batchSize)GetProcAddress(module, "_val_bs_batchSize");
    functions.bs_render = (PFN_bs_render)GetProcAddress(module, "_val_bs_render");
    functions.bs_barrier = (PFN_bs_barrier)GetProcAddress(module, "_val_bs_barrier");
    functions.bs_rayTrace = (PFN_bs_rayTrace)GetProcAddress(module, "_val_bs_rayTrace");
    functions.bs_rayTracer = (PFN_bs_rayTracer)GetProcAddress(module, "_val_bs_rayTracer");
    functions.bs_accelerateAabb = (PFN_bs_accelerateAabb)GetProcAddress(module, "_val_bs_accelerateAabb");
    functions.bs_accelerateBatch = (PFN_bs_accelerateBatch)GetProcAddress(module, "_val_bs_accelerateBatch");
    functions.bs_build = (PFN_bs_build)GetProcAddress(module, "_val_bs_build");
    functions.bs_destroyRayTracer = (PFN_bs_destroyRayTracer)GetProcAddress(module, "_val_bs_destroyRayTracer");
    functions.bs_dispatchAsync = (PFN_bs_dispatchAsync)GetProcAddress(module, "_val_bs_dispatchAsync");
    functions.bs_buffer = (PFN_bs_buffer)GetProcAddress(module, "_val_bs_buffer");
    functions.bs_bufferIsMapped = (PFN_bs_bufferIsMapped)GetProcAddress(module, "_val_bs_bufferIsMapped");
    functions.bs_bufferMap = (PFN_bs_bufferMap)GetProcAddress(module, "_val_bs_bufferMap");
    functions.bs_mapBuffer = (PFN_bs_mapBuffer)GetProcAddress(module, "_val_bs_mapBuffer");
    functions.bs_unmapBuffer = (PFN_bs_unmapBuffer)GetProcAddress(module, "_val_bs_unmapBuffer");
    functions.bs_stageNull = (PFN_bs_stageNull)GetProcAddress(module, "_val_bs_stageNull");
    functions.bs_stageList = (PFN_bs_stageList)GetProcAddress(module, "_val_bs_stageList");
    functions.bs_stageImage = (PFN_bs_stageImage)GetProcAddress(module, "_val_bs_stageImage");
    functions.bs_destroyBuffer = (PFN_bs_destroyBuffer)GetProcAddress(module, "_val_bs_destroyBuffer");
    functions.bs_copyAsync = (PFN_bs_copyAsync)GetProcAddress(module, "_val_bs_copyAsync");
    functions.bs_setBufferAsync = (PFN_bs_setBufferAsync)GetProcAddress(module, "_val_bs_setBufferAsync");
    functions.bs_batch = (PFN_bs_batch)GetProcAddress(module, "_val_bs_batch");
    functions.bs_queryAttribute = (PFN_bs_queryAttribute)GetProcAddress(module, "_val_bs_queryAttribute");
    functions.bs_canPushBatch = (PFN_bs_canPushBatch)GetProcAddress(module, "_val_bs_canPushBatch");
    functions.bs_batchIsIndexed = (PFN_bs_batchIsIndexed)GetProcAddress(module, "_val_bs_batchIsIndexed");
    functions.bs_minimizeBatch = (PFN_bs_minimizeBatch)GetProcAddress(module, "_val_bs_minimizeBatch");
    functions.bs_pushBatch = (PFN_bs_pushBatch)GetProcAddress(module, "_val_bs_pushBatch");
    functions.bs_unpushBatch = (PFN_bs_unpushBatch)GetProcAddress(module, "_val_bs_unpushBatch");
    functions.bs_destroyBatch = (PFN_bs_destroyBatch)GetProcAddress(module, "_val_bs_destroyBatch");
    functions.bs_ensureBatchSize = (PFN_bs_ensureBatchSize)GetProcAddress(module, "_val_bs_ensureBatchSize");
    functions.bs_batchVertex = (PFN_bs_batchVertex)GetProcAddress(module, "_val_bs_batchVertex");
    functions.bs_batchRange = (PFN_bs_batchRange)GetProcAddress(module, "_val_bs_batchRange");
    functions.bs_pushIndex = (PFN_bs_pushIndex)GetProcAddress(module, "_val_bs_pushIndex");
    functions.bs_pushIndices = (PFN_bs_pushIndices)GetProcAddress(module, "_val_bs_pushIndices");
    functions.bs_batchCube = (PFN_bs_batchCube)GetProcAddress(module, "_val_bs_batchCube");
    functions.bs_pushCube = (PFN_bs_pushCube)GetProcAddress(module, "_val_bs_pushCube");
    functions.bs_batchCone = (PFN_bs_batchCone)GetProcAddress(module, "_val_bs_batchCone");
    functions.bs_pushCone = (PFN_bs_pushCone)GetProcAddress(module, "_val_bs_pushCone");
    functions.bs_batchQuad = (PFN_bs_batchQuad)GetProcAddress(module, "_val_bs_batchQuad");
    functions.bs_pushQuad = (PFN_bs_pushQuad)GetProcAddress(module, "_val_bs_pushQuad");
    functions.bs_batchTriangle = (PFN_bs_batchTriangle)GetProcAddress(module, "_val_bs_batchTriangle");
    functions.bs_pushTriangle = (PFN_bs_pushTriangle)GetProcAddress(module, "_val_bs_pushTriangle");
    functions.bs_batchLine = (PFN_bs_batchLine)GetProcAddress(module, "_val_bs_batchLine");
    functions.bs_pushLine = (PFN_bs_pushLine)GetProcAddress(module, "_val_bs_pushLine");
    functions.bs_batchPoint = (PFN_bs_batchPoint)GetProcAddress(module, "_val_bs_batchPoint");
    functions.bs_pushPoint = (PFN_bs_pushPoint)GetProcAddress(module, "_val_bs_pushPoint");
    functions.bs_batchAabb = (PFN_bs_batchAabb)GetProcAddress(module, "_val_bs_batchAabb");
    functions.bs_pushAabb = (PFN_bs_pushAabb)GetProcAddress(module, "_val_bs_pushAabb");
    functions.bs_batchSphere = (PFN_bs_batchSphere)GetProcAddress(module, "_val_bs_batchSphere");
    functions.bs_pushSphere = (PFN_bs_pushSphere)GetProcAddress(module, "_val_bs_pushSphere");
    functions.bs_batchPyramid = (PFN_bs_batchPyramid)GetProcAddress(module, "_val_bs_batchPyramid");
    functions.bs_pushPyramid = (PFN_bs_pushPyramid)GetProcAddress(module, "_val_bs_pushPyramid");
    functions.bs_batchBipyramid = (PFN_bs_batchBipyramid)GetProcAddress(module, "_val_bs_batchBipyramid");
    functions.bs_pushBipyramid = (PFN_bs_pushBipyramid)GetProcAddress(module, "_val_bs_pushBipyramid");
    functions.bs_batchPrimitive = (PFN_bs_batchPrimitive)GetProcAddress(module, "_val_bs_batchPrimitive");
    functions.bs_pushPrimitive = (PFN_bs_pushPrimitive)GetProcAddress(module, "_val_bs_pushPrimitive");
    functions.bs_batchMesh = (PFN_bs_batchMesh)GetProcAddress(module, "_val_bs_batchMesh");
    functions.bs_pushMesh = (PFN_bs_pushMesh)GetProcAddress(module, "_val_bs_pushMesh");
    functions.bs_batchModel = (PFN_bs_batchModel)GetProcAddress(module, "_val_bs_batchModel");
    functions.bs_pushModel = (PFN_bs_pushModel)GetProcAddress(module, "_val_bs_pushModel");
    functions.bs_renderer = (PFN_bs_renderer)GetProcAddress(module, "_val_bs_renderer");
    functions.bs_output = (PFN_bs_output)GetProcAddress(module, "_val_bs_output");
    functions.bs_input = (PFN_bs_input)GetProcAddress(module, "_val_bs_input");
    functions.bs_dependency = (PFN_bs_dependency)GetProcAddress(module, "_val_bs_dependency");
    functions.bs_renderPass = (PFN_bs_renderPass)GetProcAddress(module, "_val_bs_renderPass");
    functions.bs_framebuffer = (PFN_bs_framebuffer)GetProcAddress(module, "_val_bs_framebuffer");
    functions.bs_runPass = (PFN_bs_runPass)GetProcAddress(module, "_val_bs_runPass");
    functions.bs_rendererIsDynamic = (PFN_bs_rendererIsDynamic)GetProcAddress(module, "_val_bs_rendererIsDynamic");
    functions.bs_beginRender = (PFN_bs_beginRender)GetProcAddress(module, "_val_bs_beginRender");
    functions.bs_endRender = (PFN_bs_endRender)GetProcAddress(module, "_val_bs_endRender");
    functions.bs_destroyRenderer = (PFN_bs_destroyRenderer)GetProcAddress(module, "_val_bs_destroyRenderer");
    functions.bs_resizeRenderer = (PFN_bs_resizeRenderer)GetProcAddress(module, "_val_bs_resizeRenderer");
    functions.bs_singleTimesQueue = (PFN_bs_singleTimesQueue)GetProcAddress(module, "_val_bs_singleTimesQueue");
    functions.bs_queueFamily = (PFN_bs_queueFamily)GetProcAddress(module, "_val_bs_queueFamily");
    functions.bs_present = (PFN_bs_present)GetProcAddress(module, "_val_bs_present");
    functions.bs_acquire = (PFN_bs_acquire)GetProcAddress(module, "_val_bs_acquire");
    functions.bs_queueSwap = (PFN_bs_queueSwap)GetProcAddress(module, "_val_bs_queueSwap");
    functions.bs_awaitQueue = (PFN_bs_awaitQueue)GetProcAddress(module, "_val_bs_awaitQueue");
    functions.bs_awaitAcquisition = (PFN_bs_awaitAcquisition)GetProcAddress(module, "_val_bs_awaitAcquisition");
    functions.bs_enqueue = (PFN_bs_enqueue)GetProcAddress(module, "_val_bs_enqueue");
    functions.bs_imageIndex = (PFN_bs_imageIndex)GetProcAddress(module, "_val_bs_imageIndex");
    functions.bs_queue = (PFN_bs_queue)GetProcAddress(module, "_val_bs_queue");
    functions.bs_destroyQueue = (PFN_bs_destroyQueue)GetProcAddress(module, "_val_bs_destroyQueue");
    functions.bs_stallGPU = (PFN_bs_stallGPU)GetProcAddress(module, "_val_bs_stallGPU");
    functions.bs_stallQueue = (PFN_bs_stallQueue)GetProcAddress(module, "_val_bs_stallQueue");
    functions.bs_stall = (PFN_bs_stall)GetProcAddress(module, "_val_bs_stall");
    functions.bs_poll = (PFN_bs_poll)GetProcAddress(module, "_val_bs_poll");
    functions.bs_enterSingle = (PFN_bs_enterSingle)GetProcAddress(module, "_val_bs_enterSingle");
    functions.bs_leaveSingle = (PFN_bs_leaveSingle)GetProcAddress(module, "_val_bs_leaveSingle");
    functions.bs_getScope = (PFN_bs_getScope)GetProcAddress(module, "_val_bs_getScope");
    functions.bs_setScope = (PFN_bs_setScope)GetProcAddress(module, "_val_bs_setScope");
    functions.bs_runSingle = (PFN_bs_runSingle)GetProcAddress(module, "_val_bs_runSingle");
    functions.bs_image = (PFN_bs_image)GetProcAddress(module, "_val_bs_image");
    functions.bs_transition = (PFN_bs_transition)GetProcAddress(module, "_val_bs_transition");
    functions.bs_peekPng = (PFN_bs_peekPng)GetProcAddress(module, "_val_bs_peekPng");
    functions.bs_loadPngData = (PFN_bs_loadPngData)GetProcAddress(module, "_val_bs_loadPngData");
    functions.bs_loadPng = (PFN_bs_loadPng)GetProcAddress(module, "_val_bs_loadPng");
    functions.bs_peekFile = (PFN_bs_peekFile)GetProcAddress(module, "_val_bs_peekFile");
    functions.bs_savePng = (PFN_bs_savePng)GetProcAddress(module, "_val_bs_savePng");
    functions.bs_encodePng = (PFN_bs_encodePng)GetProcAddress(module, "_val_bs_encodePng");
    functions.bs_destroyImage = (PFN_bs_destroyImage)GetProcAddress(module, "_val_bs_destroyImage");
    functions.bs_resizeImage = (PFN_bs_resizeImage)GetProcAddress(module, "_val_bs_resizeImage");
    functions.bs_queryImageIndexHash = (PFN_bs_queryImageIndexHash)GetProcAddress(module, "_val_bs_queryImageIndexHash");
    functions.bs_queryImageIndex = (PFN_bs_queryImageIndex)GetProcAddress(module, "_val_bs_queryImageIndex");
    functions.bs_copyImageToBufferAsync = (PFN_bs_copyImageToBufferAsync)GetProcAddress(module, "_val_bs_copyImageToBufferAsync");
    functions.bs_copyBufferToImage = (PFN_bs_copyBufferToImage)GetProcAddress(module, "_val_bs_copyBufferToImage");
    functions.bs_blit = (PFN_bs_blit)GetProcAddress(module, "_val_bs_blit");
    functions.bs_loadImage = (PFN_bs_loadImage)GetProcAddress(module, "_val_bs_loadImage");
    functions.bs_isStencilFormat = (PFN_bs_isStencilFormat)GetProcAddress(module, "_val_bs_isStencilFormat");
    functions.bs_isDepthFormat = (PFN_bs_isDepthFormat)GetProcAddress(module, "_val_bs_isDepthFormat");
    functions.bs_hasAlpha = (PFN_bs_hasAlpha)GetProcAddress(module, "_val_bs_hasAlpha");
    functions.bs_destroySampler = (PFN_bs_destroySampler)GetProcAddress(module, "_val_bs_destroySampler");
    functions.bs_sampler = (PFN_bs_sampler)GetProcAddress(module, "_val_bs_sampler");
    functions.bs_loadAtlas = (PFN_bs_loadAtlas)GetProcAddress(module, "_val_bs_loadAtlas");
    functions.bs_atlasCoordinates = (PFN_bs_atlasCoordinates)GetProcAddress(module, "_val_bs_atlasCoordinates");
    functions.bs_mirrorUV = (PFN_bs_mirrorUV)GetProcAddress(module, "_val_bs_mirrorUV");
    functions.bs_flipUV = (PFN_bs_flipUV)GetProcAddress(module, "_val_bs_flipUV");
    functions.bs_atlasSize = (PFN_bs_atlasSize)GetProcAddress(module, "_val_bs_atlasSize");
    functions.bs_queryAtlasHash = (PFN_bs_queryAtlasHash)GetProcAddress(module, "_val_bs_queryAtlasHash");
    functions.bs_queryAtlas = (PFN_bs_queryAtlas)GetProcAddress(module, "_val_bs_queryAtlas");
    functions.bs_destroyAtlas = (PFN_bs_destroyAtlas)GetProcAddress(module, "_val_bs_destroyAtlas");
    functions.bs_loadAtlasMemory = (PFN_bs_loadAtlasMemory)GetProcAddress(module, "_val_bs_loadAtlasMemory");
    functions.bs_parseArgs = (PFN_bs_parseArgs)GetProcAddress(module, "_val_bs_parseArgs");
    functions.bs_ini = (PFN_bs_ini)GetProcAddress(module, "_val_bs_ini");
    functions.bs_load = (PFN_bs_load)GetProcAddress(module, "_val_bs_load");
    functions.bs_queryProcedures = (PFN_bs_queryProcedures)GetProcAddress(module, "_val_bs_queryProcedures");
    functions.bsi_fetchCommands = (PFN_bsi_fetchCommands)GetProcAddress(module, "_val_bsi_fetchCommands");
    functions.bsi_fetchDevice = (PFN_bsi_fetchDevice)GetProcAddress(module, "_val_bsi_fetchDevice");
    functions.bs_resetQueue = (PFN_bs_resetQueue)GetProcAddress(module, "_val_bs_resetQueue");
    functions.bs_pushQueue = (PFN_bs_pushQueue)GetProcAddress(module, "_val_bs_pushQueue");
    functions.bsi_nameHandle = (PFN_bsi_nameHandle)GetProcAddress(module, "_val_bsi_nameHandle");
    functions.bs_beginEnumeration = (PFN_bs_beginEnumeration)GetProcAddress(module, "_val_bs_beginEnumeration");
    functions.bs_enumerateJson = (PFN_bs_enumerateJson)GetProcAddress(module, "_val_bs_enumerateJson");
    functions.bs_jsonRoot = (PFN_bs_jsonRoot)GetProcAddress(module, "_val_bs_jsonRoot");
    functions.bs_ensureJsonMutable = (PFN_bs_ensureJsonMutable)GetProcAddress(module, "_val_bs_ensureJsonMutable");
    functions.bs_jsonCopy = (PFN_bs_jsonCopy)GetProcAddress(module, "_val_bs_jsonCopy");
    functions.bs_saveJson = (PFN_bs_saveJson)GetProcAddress(module, "_val_bs_saveJson");
    functions.bs_emptyJson = (PFN_bs_emptyJson)GetProcAddress(module, "_val_bs_emptyJson");
    functions.bs_emptyJsonArray = (PFN_bs_emptyJsonArray)GetProcAddress(module, "_val_bs_emptyJsonArray");
    functions.bs_json = (PFN_bs_json)GetProcAddress(module, "_val_bs_json");
    functions.bs_loadJson = (PFN_bs_loadJson)GetProcAddress(module, "_val_bs_loadJson");
    functions.bs_destroyJson = (PFN_bs_destroyJson)GetProcAddress(module, "_val_bs_destroyJson");
    functions.bs_parseJsonValue = (PFN_bs_parseJsonValue)GetProcAddress(module, "_val_bs_parseJsonValue");
    functions.bs_fetchJson = (PFN_bs_fetchJson)GetProcAddress(module, "_val_bs_fetchJson");
    functions.bs_deleteJson = (PFN_bs_deleteJson)GetProcAddress(module, "_val_bs_deleteJson");
    functions.bs_ensureJson = (PFN_bs_ensureJson)GetProcAddress(module, "_val_bs_ensureJson");
    functions.bs_jsonValueFromObject = (PFN_bs_jsonValueFromObject)GetProcAddress(module, "_val_bs_jsonValueFromObject");
    functions.bs_jsonValueFromRoot = (PFN_bs_jsonValueFromRoot)GetProcAddress(module, "_val_bs_jsonValueFromRoot");
    functions.bs_jsonValueFromBool = (PFN_bs_jsonValueFromBool)GetProcAddress(module, "_val_bs_jsonValueFromBool");
    functions.bs_jsonValueFromInteger = (PFN_bs_jsonValueFromInteger)GetProcAddress(module, "_val_bs_jsonValueFromInteger");
    functions.bs_jsonValueFromFloat = (PFN_bs_jsonValueFromFloat)GetProcAddress(module, "_val_bs_jsonValueFromFloat");
    functions.bs_jsonValueFromString = (PFN_bs_jsonValueFromString)GetProcAddress(module, "_val_bs_jsonValueFromString");
    functions.bs_jsonValueFromStringPointer = (PFN_bs_jsonValueFromStringPointer)GetProcAddress(module, "_val_bs_jsonValueFromStringPointer");
    functions.bs_jsonValueFromDateTime = (PFN_bs_jsonValueFromDateTime)GetProcAddress(module, "_val_bs_jsonValueFromDateTime");
    functions.bs_jsonObject = (PFN_bs_jsonObject)GetProcAddress(module, "_val_bs_jsonObject");
    functions.bs_jsonArray = (PFN_bs_jsonArray)GetProcAddress(module, "_val_bs_jsonArray");
    functions.bs_jsonVec2 = (PFN_bs_jsonVec2)GetProcAddress(module, "_val_bs_jsonVec2");
    functions.bs_jsonVec3 = (PFN_bs_jsonVec3)GetProcAddress(module, "_val_bs_jsonVec3");
    functions.bs_jsonVec4 = (PFN_bs_jsonVec4)GetProcAddress(module, "_val_bs_jsonVec4");
    functions.bs_jsonRGBA = (PFN_bs_jsonRGBA)GetProcAddress(module, "_val_bs_jsonRGBA");
    functions.bs_logSection = (PFN_bs_logSection)GetProcAddress(module, "_val_bs_logSection");
    functions.bs_logEndOfSection = (PFN_bs_logEndOfSection)GetProcAddress(module, "_val_bs_logEndOfSection");
    functions.bs_logWithTimestamp = (PFN_bs_logWithTimestamp)GetProcAddress(module, "_val_bs_logWithTimestamp");
    functions.bs_log = (PFN_bs_log)GetProcAddress(module, "_val_bs_log");
    functions.bs_info = (PFN_bs_info)GetProcAddress(module, "_val_bs_info");
    functions.bs_warn = (PFN_bs_warn)GetProcAddress(module, "_val_bs_warn");
    functions.bs_critical = (PFN_bs_critical)GetProcAddress(module, "_val_bs_critical");
    functions.bs_instance = (PFN_bs_instance)GetProcAddress(module, "_val_bs_instance");
    functions.bs_args = (PFN_bs_args)GetProcAddress(module, "_val_bs_args");
    functions.bs_features = (PFN_bs_features)GetProcAddress(module, "_val_bs_features");
    functions.bs_props = (PFN_bs_props)GetProcAddress(module, "_val_bs_props");
    functions.bs_config = (PFN_bs_config)GetProcAddress(module, "_val_bs_config");
    functions.bs_scope = (PFN_bs_scope)GetProcAddress(module, "_val_bs_scope");
    functions.bs_context = (PFN_bs_context)GetProcAddress(module, "_val_bs_context");
    functions.bs_io = (PFN_bs_io)GetProcAddress(module, "_val_bs_io");
    functions.bs_system = (PFN_bs_system)GetProcAddress(module, "_val_bs_system");
    functions.bs_createThread = (PFN_bs_createThread)GetProcAddress(module, "_val_bs_createThread");
    functions.bs_formatStringLength = (PFN_bs_formatStringLength)GetProcAddress(module, "_val_bs_formatStringLength");
    functions.bs_checkStringPool = (PFN_bs_checkStringPool)GetProcAddress(module, "_val_bs_checkStringPool");
    functions.bs_stringAlloc = (PFN_bs_stringAlloc)GetProcAddress(module, "_val_bs_stringAlloc");
    functions.bs_emptyString = (PFN_bs_emptyString)GetProcAddress(module, "_val_bs_emptyString");
    functions.bs_string = (PFN_bs_string)GetProcAddress(module, "_val_bs_string");
    functions.bs_toUpper = (PFN_bs_toUpper)GetProcAddress(module, "_val_bs_toUpper");
    functions.bs_toLower = (PFN_bs_toLower)GetProcAddress(module, "_val_bs_toLower");
    functions.bs_hash = (PFN_bs_hash)GetProcAddress(module, "_val_bs_hash");
    functions.bs_stringHash = (PFN_bs_stringHash)GetProcAddress(module, "_val_bs_stringHash");
    functions.bs_startsWith = (PFN_bs_startsWith)GetProcAddress(module, "_val_bs_startsWith");
    functions.bs_endsWith = (PFN_bs_endsWith)GetProcAddress(module, "_val_bs_endsWith");
    functions.bs_lastChar = (PFN_bs_lastChar)GetProcAddress(module, "_val_bs_lastChar");
    functions.bs_stringContainsChar = (PFN_bs_stringContainsChar)GetProcAddress(module, "_val_bs_stringContainsChar");
    functions.bs_workingDirectory = (PFN_bs_workingDirectory)GetProcAddress(module, "_val_bs_workingDirectory");
    functions.bs_setWorkingDirectory = (PFN_bs_setWorkingDirectory)GetProcAddress(module, "_val_bs_setWorkingDirectory");
    functions.bs_executablePath = (PFN_bs_executablePath)GetProcAddress(module, "_val_bs_executablePath");
    functions.bs_appdataPath = (PFN_bs_appdataPath)GetProcAddress(module, "_val_bs_appdataPath");
    functions.bs_shortenString = (PFN_bs_shortenString)GetProcAddress(module, "_val_bs_shortenString");
    functions.bs_appendChar = (PFN_bs_appendChar)GetProcAddress(module, "_val_bs_appendChar");
    functions.bs_removeCharRange = (PFN_bs_removeCharRange)GetProcAddress(module, "_val_bs_removeCharRange");
    functions.bs_insertChar = (PFN_bs_insertChar)GetProcAddress(module, "_val_bs_insertChar");
    functions.bs_appendPath = (PFN_bs_appendPath)GetProcAddress(module, "_val_bs_appendPath");
    functions.bs_replaceCharOccurrences = (PFN_bs_replaceCharOccurrences)GetProcAddress(module, "_val_bs_replaceCharOccurrences");
    functions.bs_strndup = (PFN_bs_strndup)GetProcAddress(module, "_val_bs_strndup");
    functions.bs_strnlen = (PFN_bs_strnlen)GetProcAddress(module, "_val_bs_strnlen");
    functions.bs_strsep = (PFN_bs_strsep)GetProcAddress(module, "_val_bs_strsep");
    functions.bs_memmem = (PFN_bs_memmem)GetProcAddress(module, "_val_bs_memmem");
    functions.bs_alignUp = (PFN_bs_alignUp)GetProcAddress(module, "_val_bs_alignUp");
    functions.bs_widen = (PFN_bs_widen)GetProcAddress(module, "_val_bs_widen");
    functions.bs_unwiden = (PFN_bs_unwiden)GetProcAddress(module, "_val_bs_unwiden");
    functions.bs_charStringV = (PFN_bs_charStringV)GetProcAddress(module, "_val_bs_charStringV");
    functions.bs_free = (PFN_bs_free)GetProcAddress(module, "_val_bs_free");
    functions.bs_malloc = (PFN_bs_malloc)GetProcAddress(module, "_val_bs_malloc");
    functions.bs_calloc = (PFN_bs_calloc)GetProcAddress(module, "_val_bs_calloc");
    functions.bs_realloc = (PFN_bs_realloc)GetProcAddress(module, "_val_bs_realloc");
    functions.bs_listContains = (PFN_bs_listContains)GetProcAddress(module, "_val_bs_listContains");
    functions.bs_fetchUnit = (PFN_bs_fetchUnit)GetProcAddress(module, "_val_bs_fetchUnit");
    functions.bs_fetchLast = (PFN_bs_fetchLast)GetProcAddress(module, "_val_bs_fetchLast");
    functions.bs_ensureSize = (PFN_bs_ensureSize)GetProcAddress(module, "_val_bs_ensureSize");
    functions.bs_erase = (PFN_bs_erase)GetProcAddress(module, "_val_bs_erase");
    functions.bs_pushBack = (PFN_bs_pushBack)GetProcAddress(module, "_val_bs_pushBack");
    functions.bs_pushBackList = (PFN_bs_pushBackList)GetProcAddress(module, "_val_bs_pushBackList");
    functions.bs_destroyList = (PFN_bs_destroyList)GetProcAddress(module, "_val_bs_destroyList");
    functions.bs_seekList = (PFN_bs_seekList)GetProcAddress(module, "_val_bs_seekList");
    functions.bs_minimizeList = (PFN_bs_minimizeList)GetProcAddress(module, "_val_bs_minimizeList");
    functions.bs_list = (PFN_bs_list)GetProcAddress(module, "_val_bs_list");
    functions.bs_guidToString = (PFN_bs_guidToString)GetProcAddress(module, "_val_bs_guidToString");
    functions.bs_stringToGuid = (PFN_bs_stringToGuid)GetProcAddress(module, "_val_bs_stringToGuid");
    functions.bs_sameGuid = (PFN_bs_sameGuid)GetProcAddress(module, "_val_bs_sameGuid");
    functions.bs_guid = (PFN_bs_guid)GetProcAddress(module, "_val_bs_guid");
    functions.bs_guidIsNull = (PFN_bs_guidIsNull)GetProcAddress(module, "_val_bs_guidIsNull");
    functions.bs_numDigits = (PFN_bs_numDigits)GetProcAddress(module, "_val_bs_numDigits");
    functions.bs_directoryExists = (PFN_bs_directoryExists)GetProcAddress(module, "_val_bs_directoryExists");
    functions.bs_fileExtension = (PFN_bs_fileExtension)GetProcAddress(module, "_val_bs_fileExtension");
    functions.bs_fileExtensionIs = (PFN_bs_fileExtensionIs)GetProcAddress(module, "_val_bs_fileExtensionIs");
    functions.bs_fileName = (PFN_bs_fileName)GetProcAddress(module, "_val_bs_fileName");
    functions.bs_appendFile = (PFN_bs_appendFile)GetProcAddress(module, "_val_bs_appendFile");
    functions.bs_saveFile = (PFN_bs_saveFile)GetProcAddress(module, "_val_bs_saveFile");
    functions.bs_convertWin32Path = (PFN_bs_convertWin32Path)GetProcAddress(module, "_val_bs_convertWin32Path");
    functions.bs_ensureDirectory = (PFN_bs_ensureDirectory)GetProcAddress(module, "_val_bs_ensureDirectory");
    functions.bs_fileModifiedDate = (PFN_bs_fileModifiedDate)GetProcAddress(module, "_val_bs_fileModifiedDate");
    functions.bs_setFileModifiedDate = (PFN_bs_setFileModifiedDate)GetProcAddress(module, "_val_bs_setFileModifiedDate");
    functions.bs_fullPath = (PFN_bs_fullPath)GetProcAddress(module, "_val_bs_fullPath");
    functions.bs_fileExists = (PFN_bs_fileExists)GetProcAddress(module, "_val_bs_fileExists");
    functions.bs_toLong = (PFN_bs_toLong)GetProcAddress(module, "_val_bs_toLong");
    functions.bs_toULong = (PFN_bs_toULong)GetProcAddress(module, "_val_bs_toULong");
    functions.bs_toDouble = (PFN_bs_toDouble)GetProcAddress(module, "_val_bs_toDouble");
    functions.bs_model = (PFN_bs_model)GetProcAddress(module, "_val_bs_model");
    functions.bs_destroyModel = (PFN_bs_destroyModel)GetProcAddress(module, "_val_bs_destroyModel");
    functions.bs_interpolateRotation = (PFN_bs_interpolateRotation)GetProcAddress(module, "_val_bs_interpolateRotation");
    functions.bs_interpolateTranslation = (PFN_bs_interpolateTranslation)GetProcAddress(module, "_val_bs_interpolateTranslation");
    functions.bs_interpolateScale = (PFN_bs_interpolateScale)GetProcAddress(module, "_val_bs_interpolateScale");
    functions.bs_boneTransform = (PFN_bs_boneTransform)GetProcAddress(module, "_val_bs_boneTransform");
    functions.bs_bonePosition = (PFN_bs_bonePosition)GetProcAddress(module, "_val_bs_bonePosition");
    functions.bs_transformBone = (PFN_bs_transformBone)GetProcAddress(module, "_val_bs_transformBone");
    functions.bs_blendPose = (PFN_bs_blendPose)GetProcAddress(module, "_val_bs_blendPose");
    functions.bs_bone = (PFN_bs_bone)GetProcAddress(module, "_val_bs_bone");
    functions.bs_fabrik = (PFN_bs_fabrik)GetProcAddress(module, "_val_bs_fabrik");
    functions.bs_bindPose = (PFN_bs_bindPose)GetProcAddress(module, "_val_bs_bindPose");
    functions.bs_keyframePosition = (PFN_bs_keyframePosition)GetProcAddress(module, "_val_bs_keyframePosition");
    functions.bs_keyframeRotation = (PFN_bs_keyframeRotation)GetProcAddress(module, "_val_bs_keyframeRotation");
    functions.bs_keyframeScale = (PFN_bs_keyframeScale)GetProcAddress(module, "_val_bs_keyframeScale");
    functions.bs_loadAnimation = (PFN_bs_loadAnimation)GetProcAddress(module, "_val_bs_loadAnimation");
    functions.bs_queryBoneId = (PFN_bs_queryBoneId)GetProcAddress(module, "_val_bs_queryBoneId");
    functions.bs_queryArmature = (PFN_bs_queryArmature)GetProcAddress(module, "_val_bs_queryArmature");
    functions.bs_queryBone = (PFN_bs_queryBone)GetProcAddress(module, "_val_bs_queryBone");
    functions.bs_queryMesh = (PFN_bs_queryMesh)GetProcAddress(module, "_val_bs_queryMesh");
    functions.bs_queryMeshHash = (PFN_bs_queryMeshHash)GetProcAddress(module, "_val_bs_queryMeshHash");
    functions.bs_queryMaterial = (PFN_bs_queryMaterial)GetProcAddress(module, "_val_bs_queryMaterial");
    functions.bs_idName = (PFN_bs_idName)GetProcAddress(module, "_val_bs_idName");
    functions.bs_resetObject = (PFN_bs_resetObject)GetProcAddress(module, "_val_bs_resetObject");
    functions.bs_object = (PFN_bs_object)GetProcAddress(module, "_val_bs_object");
    functions.bs_packages = (PFN_bs_packages)GetProcAddress(module, "_val_bs_packages");
    functions.bs_objectSources = (PFN_bs_objectSources)GetProcAddress(module, "_val_bs_objectSources");
    functions.bs_destroyResource = (PFN_bs_destroyResource)GetProcAddress(module, "_val_bs_destroyResource");
    functions.bs_queryResource = (PFN_bs_queryResource)GetProcAddress(module, "_val_bs_queryResource");
    functions.bs_queryPackage = (PFN_bs_queryPackage)GetProcAddress(module, "_val_bs_queryPackage");
    functions.bs_loadResource = (PFN_bs_loadResource)GetProcAddress(module, "_val_bs_loadResource");
    functions.bs_loadPackage = (PFN_bs_loadPackage)GetProcAddress(module, "_val_bs_loadPackage");
    functions.bs_configureSource = (PFN_bs_configureSource)GetProcAddress(module, "_val_bs_configureSource");
    functions.bs_exists = (PFN_bs_exists)GetProcAddress(module, "_val_bs_exists");
    functions.bs_fetch = (PFN_bs_fetch)GetProcAddress(module, "_val_bs_fetch");
    functions.bs_shouldLoadId = (PFN_bs_shouldLoadId)GetProcAddress(module, "_val_bs_shouldLoadId");
    functions.bs_shader = (PFN_bs_shader)GetProcAddress(module, "_val_bs_shader");
    functions.bs_destroyShader = (PFN_bs_destroyShader)GetProcAddress(module, "_val_bs_destroyShader");
    functions.bs_computePipeline = (PFN_bs_computePipeline)GetProcAddress(module, "_val_bs_computePipeline");
    functions.bs_destroyComputePipeline = (PFN_bs_destroyComputePipeline)GetProcAddress(module, "_val_bs_destroyComputePipeline");
    functions.bs_queryPipeline = (PFN_bs_queryPipeline)GetProcAddress(module, "_val_bs_queryPipeline");
    functions.bs_pipelineHash = (PFN_bs_pipelineHash)GetProcAddress(module, "_val_bs_pipelineHash");
    functions.bs_pipeline = (PFN_bs_pipeline)GetProcAddress(module, "_val_bs_pipeline");
    functions.bs_destroyPipeline = (PFN_bs_destroyPipeline)GetProcAddress(module, "_val_bs_destroyPipeline");
    functions.bs_pushConstant = (PFN_bs_pushConstant)GetProcAddress(module, "_val_bs_pushConstant");
    functions.bs_rayTracingPipeline = (PFN_bs_rayTracingPipeline)GetProcAddress(module, "_val_bs_rayTracingPipeline");
    functions.bs_loadBindings = (PFN_bs_loadBindings)GetProcAddress(module, "_val_bs_loadBindings");
    functions.bs_binding = (PFN_bs_binding)GetProcAddress(module, "_val_bs_binding");
    functions.bs_bindImage = (PFN_bs_bindImage)GetProcAddress(module, "_val_bs_bindImage");
    functions.bs_bindImages = (PFN_bs_bindImages)GetProcAddress(module, "_val_bs_bindImages");
    functions.bs_bindBuffer = (PFN_bs_bindBuffer)GetProcAddress(module, "_val_bs_bindBuffer");
    functions.bs_bindBuffers = (PFN_bs_bindBuffers)GetProcAddress(module, "_val_bs_bindBuffers");
    functions.bs_bindAccelerationStructure = (PFN_bs_bindAccelerationStructure)GetProcAddress(module, "_val_bs_bindAccelerationStructure");
    functions.bs_bindAccelerationStructures = (PFN_bs_bindAccelerationStructures)GetProcAddress(module, "_val_bs_bindAccelerationStructures");
    functions.bs_pushDescriptors = (PFN_bs_pushDescriptors)GetProcAddress(module, "_val_bs_pushDescriptors");
    functions.bs_pushBindings = (PFN_bs_pushBindings)GetProcAddress(module, "_val_bs_pushBindings");
    functions.bs_queryBindSet = (PFN_bs_queryBindSet)GetProcAddress(module, "_val_bs_queryBindSet");
    functions.bs_queryBinding = (PFN_bs_queryBinding)GetProcAddress(module, "_val_bs_queryBinding");
    functions.bs_configureAttribute = (PFN_bs_configureAttribute)GetProcAddress(module, "_val_bs_configureAttribute");
    functions.bs_timeZoneBias = (PFN_bs_timeZoneBias)GetProcAddress(module, "_val_bs_timeZoneBias");
    functions.bs_dateTime = (PFN_bs_dateTime)GetProcAddress(module, "_val_bs_dateTime");
    functions.bs_totalSeconds = (PFN_bs_totalSeconds)GetProcAddress(module, "_val_bs_totalSeconds");
    functions.bs_isLaterThan = (PFN_bs_isLaterThan)GetProcAddress(module, "_val_bs_isLaterThan");
    functions.bs_cursorPosition = (PFN_bs_cursorPosition)GetProcAddress(module, "_val_bs_cursorPosition");
    functions.bs_windowPosition = (PFN_bs_windowPosition)GetProcAddress(module, "_val_bs_windowPosition");
    functions.bs_screenCursorPosition = (PFN_bs_screenCursorPosition)GetProcAddress(module, "_val_bs_screenCursorPosition");
    functions.bs_lockCursorPosition = (PFN_bs_lockCursorPosition)GetProcAddress(module, "_val_bs_lockCursorPosition");
    functions.bs_disableUserInputs = (PFN_bs_disableUserInputs)GetProcAddress(module, "_val_bs_disableUserInputs");
    functions.bs_middleClick = (PFN_bs_middleClick)GetProcAddress(module, "_val_bs_middleClick");
    functions.bs_middleClickOnce = (PFN_bs_middleClickOnce)GetProcAddress(module, "_val_bs_middleClickOnce");
    functions.bs_middleClickUpOnce = (PFN_bs_middleClickUpOnce)GetProcAddress(module, "_val_bs_middleClickUpOnce");
    functions.bs_leftClick = (PFN_bs_leftClick)GetProcAddress(module, "_val_bs_leftClick");
    functions.bs_rightClick = (PFN_bs_rightClick)GetProcAddress(module, "_val_bs_rightClick");
    functions.bs_rightClickOnce = (PFN_bs_rightClickOnce)GetProcAddress(module, "_val_bs_rightClickOnce");
    functions.bs_leftClickOnce = (PFN_bs_leftClickOnce)GetProcAddress(module, "_val_bs_leftClickOnce");
    functions.bs_rightClickUpOnce = (PFN_bs_rightClickUpOnce)GetProcAddress(module, "_val_bs_rightClickUpOnce");
    functions.bs_leftClickUpOnce = (PFN_bs_leftClickUpOnce)GetProcAddress(module, "_val_bs_leftClickUpOnce");
    functions.bs_keyDown = (PFN_bs_keyDown)GetProcAddress(module, "_val_bs_keyDown");
    functions.bs_keyHeld = (PFN_bs_keyHeld)GetProcAddress(module, "_val_bs_keyHeld");
    functions.bs_keyDownOnce = (PFN_bs_keyDownOnce)GetProcAddress(module, "_val_bs_keyDownOnce");
    functions.bs_keyUpOnce = (PFN_bs_keyUpOnce)GetProcAddress(module, "_val_bs_keyUpOnce");
    functions.bs_charDown = (PFN_bs_charDown)GetProcAddress(module, "_val_bs_charDown");
    functions.bs_charDownOnce = (PFN_bs_charDownOnce)GetProcAddress(module, "_val_bs_charDownOnce");
    functions.bs_charUpOnce = (PFN_bs_charUpOnce)GetProcAddress(module, "_val_bs_charUpOnce");
    functions.bs_scroll = (PFN_bs_scroll)GetProcAddress(module, "_val_bs_scroll");
    functions.bs_resizeWindow = (PFN_bs_resizeWindow)GetProcAddress(module, "_val_bs_resizeWindow");
    functions.bs_moveWindow = (PFN_bs_moveWindow)GetProcAddress(module, "_val_bs_moveWindow");
    functions.bs_overrideTitleBar = (PFN_bs_overrideTitleBar)GetProcAddress(module, "_val_bs_overrideTitleBar");
    functions.bs_window = (PFN_bs_window)GetProcAddress(module, "_val_bs_window");
    functions.bs_device = (PFN_bs_device)GetProcAddress(module, "_val_bs_device");
    functions.bs_tick = (PFN_bs_tick)GetProcAddress(module, "_val_bs_tick");
    functions.bs_exit = (PFN_bs_exit)GetProcAddress(module, "_val_bs_exit");
    functions.bs_setCursor = (PFN_bs_setCursor)GetProcAddress(module, "_val_bs_setCursor");
    functions.bs_deltaTime = (PFN_bs_deltaTime)GetProcAddress(module, "_val_bs_deltaTime");
    functions.bs_pause = (PFN_bs_pause)GetProcAddress(module, "_val_bs_pause");
    functions.bs_advance = (PFN_bs_advance)GetProcAddress(module, "_val_bs_advance");
    functions.bs_elapsedTime = (PFN_bs_elapsedTime)GetProcAddress(module, "_val_bs_elapsedTime");
    functions.bs_resolution = (PFN_bs_resolution)GetProcAddress(module, "_val_bs_resolution");
    functions.bs_titleWindow = (PFN_bs_titleWindow)GetProcAddress(module, "_val_bs_titleWindow");
    functions.bs_inFixedTick = (PFN_bs_inFixedTick)GetProcAddress(module, "_val_bs_inFixedTick");
    functions.bs_setTargetFramerate = (PFN_bs_setTargetFramerate)GetProcAddress(module, "_val_bs_setTargetFramerate");
    functions.bs_timer = (PFN_bs_timer)GetProcAddress(module, "_val_bs_timer");
    functions.bs_checkTimer = (PFN_bs_checkTimer)GetProcAddress(module, "_val_bs_checkTimer");
    functions.bs_copyToClipboard = (PFN_bs_copyToClipboard)GetProcAddress(module, "_val_bs_copyToClipboard");
    functions.bs_appendString = (PFN_bs_appendString)GetProcAddress(module, "_val_bs_appendString");
    functions.bs_foreachFile = (PFN_bs_foreachFile)GetProcAddress(module, "_val_bs_foreachFile");
    functions.bs_foreachDirectory = (PFN_bs_foreachDirectory)GetProcAddress(module, "_val_bs_foreachDirectory");
    functions.bs_numFiles = (PFN_bs_numFiles)GetProcAddress(module, "_val_bs_numFiles");
    functions.bs_numDirectories = (PFN_bs_numDirectories)GetProcAddress(module, "_val_bs_numDirectories");
    functions.bs_openFile = (PFN_bs_openFile)GetProcAddress(module, "_val_bs_openFile");
    functions.bs_closeFile = (PFN_bs_closeFile)GetProcAddress(module, "_val_bs_closeFile");
    functions.bs_loadFile = (PFN_bs_loadFile)GetProcAddress(module, "_val_bs_loadFile");
    functions.bs_loadFileChunk = (PFN_bs_loadFileChunk)GetProcAddress(module, "_val_bs_loadFileChunk");
    functions.bs_deleteFile = (PFN_bs_deleteFile)GetProcAddress(module, "_val_bs_deleteFile");
    functions.bs_deleteDirectoryContents = (PFN_bs_deleteDirectoryContents)GetProcAddress(module, "_val_bs_deleteDirectoryContents");
    functions.bs_deleteDirectory = (PFN_bs_deleteDirectory)GetProcAddress(module, "_val_bs_deleteDirectory");

    return &functions;
}

#endif
