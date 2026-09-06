
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

#ifndef BSMOD_VALIDATION_H
#define BSMOD_VALIDATION_H

#include <basilisk-mod.h>
#ifdef __linux__
#define __USE_GNU
#include <dlfcn.h>
#endif

static inline bsmod_FunctionTable* _val_bsmod_getFunctions() {
    static bsmod_FunctionTable functions;

#ifdef _WIN32
    HMODULE module = NULL;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_val_bsmod_getFunctions),
        &module);

#else
    Dl_info module_info;
    void *module = NULL;
    dladdr((void *)(&_val_bsmod_getFunctions), &module_info);
    module = dlopen(module_info.dli_fname, RTLD_LAZY);
#endif
    functions.bsmod_subtypes = (PFN_bsmod_subtypes)bs_getProcAddress(module, "_val_bsmod_subtypes");
    functions.bsmod_callbacks = (PFN_bsmod_callbacks)bs_getProcAddress(module, "_val_bsmod_callbacks");
    functions.bsmod_copyHoveringDataToBuffer = (PFN_bsmod_copyHoveringDataToBuffer)bs_getProcAddress(module, "_val_bsmod_copyHoveringDataToBuffer");
    functions.bsmod_onQueue = (PFN_bsmod_onQueue)bs_getProcAddress(module, "_val_bsmod_onQueue");
    functions.bsmod_onIni = (PFN_bsmod_onIni)bs_getProcAddress(module, "_val_bsmod_onIni");
    functions.bsmod_onLateIni = (PFN_bsmod_onLateIni)bs_getProcAddress(module, "_val_bsmod_onLateIni");
    functions.bsmod_onCreateQuadSubtypes = (PFN_bsmod_onCreateQuadSubtypes)bs_getProcAddress(module, "_val_bsmod_onCreateQuadSubtypes");
    functions.bsmod_onLoad = (PFN_bsmod_onLoad)bs_getProcAddress(module, "_val_bsmod_onLoad");
    functions.bsmod_bindAtlases = (PFN_bsmod_bindAtlases)bs_getProcAddress(module, "_val_bsmod_bindAtlases");
    functions.bsmod_onGfxRender = (PFN_bsmod_onGfxRender)bs_getProcAddress(module, "_val_bsmod_onGfxRender");
    functions.bsmod_onTick = (PFN_bsmod_onTick)bs_getProcAddress(module, "_val_bsmod_onTick");
    functions.bsmod_onMap = (PFN_bsmod_onMap)bs_getProcAddress(module, "_val_bsmod_onMap");
    functions.bsmod_beginTrackChanges = (PFN_bsmod_beginTrackChanges)bs_getProcAddress(module, "_val_bsmod_beginTrackChanges");
    functions.bsmod_tickTracker = (PFN_bsmod_tickTracker)bs_getProcAddress(module, "_val_bsmod_tickTracker");
    functions.bsmod_onTrack = (PFN_bsmod_onTrack)bs_getProcAddress(module, "_val_bsmod_onTrack");
    functions.bsmod_onCompileShader = (PFN_bsmod_onCompileShader)bs_getProcAddress(module, "_val_bsmod_onCompileShader");
    functions.bsmod_onConvertFont = (PFN_bsmod_onConvertFont)bs_getProcAddress(module, "_val_bsmod_onConvertFont");
    functions.bsmod_onPackAtlas = (PFN_bsmod_onPackAtlas)bs_getProcAddress(module, "_val_bsmod_onPackAtlas");
    functions.bsmod_onPackModels = (PFN_bsmod_onPackModels)bs_getProcAddress(module, "_val_bsmod_onPackModels");
    functions.bsmod_onPackBinary = (PFN_bsmod_onPackBinary)bs_getProcAddress(module, "_val_bsmod_onPackBinary");
    functions.bsmod_onPackTextureArray = (PFN_bsmod_onPackTextureArray)bs_getProcAddress(module, "_val_bsmod_onPackTextureArray");
    functions.bsmod_packFont = (PFN_bsmod_packFont)bs_getProcAddress(module, "_val_bsmod_packFont");
    functions.bsmod_packAtlasTexture = (PFN_bsmod_packAtlasTexture)bs_getProcAddress(module, "_val_bsmod_packAtlasTexture");
    functions.bsmod_destroyAtlasPacker = (PFN_bsmod_destroyAtlasPacker)bs_getProcAddress(module, "_val_bsmod_destroyAtlasPacker");
    functions.bsmod_packAtlas = (PFN_bsmod_packAtlas)bs_getProcAddress(module, "_val_bsmod_packAtlas");
    functions.bsmod_createAtlasPacker = (PFN_bsmod_createAtlasPacker)bs_getProcAddress(module, "_val_bsmod_createAtlasPacker");
    functions.bsmod_packImageDirectory = (PFN_bsmod_packImageDirectory)bs_getProcAddress(module, "_val_bsmod_packImageDirectory");
    functions.bsmod_packages = (PFN_bsmod_packages)bs_getProcAddress(module, "_val_bsmod_packages");
    functions.bsmod_queryPackage = (PFN_bsmod_queryPackage)bs_getProcAddress(module, "_val_bsmod_queryPackage");
    functions.bsmod_ensurePackage = (PFN_bsmod_ensurePackage)bs_getProcAddress(module, "_val_bsmod_ensurePackage");
    functions.bsmod_queryResource = (PFN_bsmod_queryResource)bs_getProcAddress(module, "_val_bsmod_queryResource");
    functions.bsmod_loadResource = (PFN_bsmod_loadResource)bs_getProcAddress(module, "_val_bsmod_loadResource");
    functions.bsmod_iniPackage = (PFN_bsmod_iniPackage)bs_getProcAddress(module, "_val_bsmod_iniPackage");
    functions.bsmod_packResource = (PFN_bsmod_packResource)bs_getProcAddress(module, "_val_bsmod_packResource");
    functions.bsmod_savePackage = (PFN_bsmod_savePackage)bs_getProcAddress(module, "_val_bsmod_savePackage");
    functions.bsmod_loadShaderReferences = (PFN_bsmod_loadShaderReferences)bs_getProcAddress(module, "_val_bsmod_loadShaderReferences");
    functions.bsmod_updateShaderReferences = (PFN_bsmod_updateShaderReferences)bs_getProcAddress(module, "_val_bsmod_updateShaderReferences");
    functions.bsmod_iniCompiler = (PFN_bsmod_iniCompiler)bs_getProcAddress(module, "_val_bsmod_iniCompiler");
    functions.bsmod_compileShader = (PFN_bsmod_compileShader)bs_getProcAddress(module, "_val_bsmod_compileShader");
    functions.bsmod_queueRasterize = (PFN_bsmod_queueRasterize)bs_getProcAddress(module, "_val_bsmod_queueRasterize");
    functions.bsmod_pollRasterizer = (PFN_bsmod_pollRasterizer)bs_getProcAddress(module, "_val_bsmod_pollRasterizer");
    functions.bsmod_beginRasterize = (PFN_bsmod_beginRasterize)bs_getProcAddress(module, "_val_bsmod_beginRasterize");
    functions.bsmod_endRasterize = (PFN_bsmod_endRasterize)bs_getProcAddress(module, "_val_bsmod_endRasterize");
    functions.bsmod_rasterizeInstance = (PFN_bsmod_rasterizeInstance)bs_getProcAddress(module, "_val_bsmod_rasterizeInstance");
    functions.bsmod_instanceTransform = (PFN_bsmod_instanceTransform)bs_getProcAddress(module, "_val_bsmod_instanceTransform");
    functions.bsmod_selectHoveringTypes = (PFN_bsmod_selectHoveringTypes)bs_getProcAddress(module, "_val_bsmod_selectHoveringTypes");
    functions.bsmod_queryType = (PFN_bsmod_queryType)bs_getProcAddress(module, "_val_bsmod_queryType");
    functions.bsmod_delete = (PFN_bsmod_delete)bs_getProcAddress(module, "_val_bsmod_delete");
    functions.bsmod_deleteSelected = (PFN_bsmod_deleteSelected)bs_getProcAddress(module, "_val_bsmod_deleteSelected");
    functions.bsmod_saveType = (PFN_bsmod_saveType)bs_getProcAddress(module, "_val_bsmod_saveType");
    functions.bsmod_add = (PFN_bsmod_add)bs_getProcAddress(module, "_val_bsmod_add");
    functions.bsmod_isSelected = (PFN_bsmod_isSelected)bs_getProcAddress(module, "_val_bsmod_isSelected");
    functions.bsmod_select = (PFN_bsmod_select)bs_getProcAddress(module, "_val_bsmod_select");
    functions.bsmod_deselectAll = (PFN_bsmod_deselectAll)bs_getProcAddress(module, "_val_bsmod_deselectAll");
    functions.bsmod_deselectRange = (PFN_bsmod_deselectRange)bs_getProcAddress(module, "_val_bsmod_deselectRange");
    functions.bsmod_deselectIndex = (PFN_bsmod_deselectIndex)bs_getProcAddress(module, "_val_bsmod_deselectIndex");
    functions.bsmod_deselect = (PFN_bsmod_deselect)bs_getProcAddress(module, "_val_bsmod_deselect");
    functions.bsmod_firstSelectedId = (PFN_bsmod_firstSelectedId)bs_getProcAddress(module, "_val_bsmod_firstSelectedId");
    functions.bsmod_lastSelectedId = (PFN_bsmod_lastSelectedId)bs_getProcAddress(module, "_val_bsmod_lastSelectedId");
    functions.bsmod_removeFlexible = (PFN_bsmod_removeFlexible)bs_getProcAddress(module, "_val_bsmod_removeFlexible");
    functions.bsmod_addFlexible = (PFN_bsmod_addFlexible)bs_getProcAddress(module, "_val_bsmod_addFlexible");
    functions.bsmod_readHoveringOutputs = (PFN_bsmod_readHoveringOutputs)bs_getProcAddress(module, "_val_bsmod_readHoveringOutputs");
    functions.bsmod_readHoveringInstanceData = (PFN_bsmod_readHoveringInstanceData)bs_getProcAddress(module, "_val_bsmod_readHoveringInstanceData");
    functions.bsmod_readHoveringVertex = (PFN_bsmod_readHoveringVertex)bs_getProcAddress(module, "_val_bsmod_readHoveringVertex");
    functions.bsmod_editSelectedType = (PFN_bsmod_editSelectedType)bs_getProcAddress(module, "_val_bsmod_editSelectedType");
    functions.bsmod_ensureTypeVersionsAreUpToDate = (PFN_bsmod_ensureTypeVersionsAreUpToDate)bs_getProcAddress(module, "_val_bsmod_ensureTypeVersionsAreUpToDate");
#ifdef __linux__
    dlclose(module);
#endif
    return &functions;
}

#endif
