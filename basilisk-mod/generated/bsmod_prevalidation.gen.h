
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
        
#ifndef BSMOD_PREVALIDATION_H
#define BSMOD_PREVALIDATION_H

#include <basilisk-mod.h>

static inline bsmod_FunctionTable* _preval_bsmod_getFunctions() {
    static bsmod_FunctionTable functions;

    HMODULE module = NULL;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_preval_bsmod_getFunctions),
        &module);

    functions.bsmod_callbacks = (PFN_bsmod_callbacks)GetProcAddress(module, "_preval_bsmod_callbacks");
    functions.bsmod_copyHoveringDataToBuffer = (PFN_bsmod_copyHoveringDataToBuffer)GetProcAddress(module, "_preval_bsmod_copyHoveringDataToBuffer");
    functions.bsmod_onIni = (PFN_bsmod_onIni)GetProcAddress(module, "_preval_bsmod_onIni");
    functions.bsmod_onLateIni = (PFN_bsmod_onLateIni)GetProcAddress(module, "_preval_bsmod_onLateIni");
    functions.bsmod_onCreateQuadSubtypes = (PFN_bsmod_onCreateQuadSubtypes)GetProcAddress(module, "_preval_bsmod_onCreateQuadSubtypes");
    functions.bsmod_onLoad = (PFN_bsmod_onLoad)GetProcAddress(module, "_preval_bsmod_onLoad");
    functions.bsmod_bindAtlases = (PFN_bsmod_bindAtlases)GetProcAddress(module, "_preval_bsmod_bindAtlases");
    functions.bsmod_onGfxRender = (PFN_bsmod_onGfxRender)GetProcAddress(module, "_preval_bsmod_onGfxRender");
    functions.bsmod_onTick = (PFN_bsmod_onTick)GetProcAddress(module, "_preval_bsmod_onTick");
    functions.bsmod_onMap = (PFN_bsmod_onMap)GetProcAddress(module, "_preval_bsmod_onMap");
    functions.bsmod_onTrack = (PFN_bsmod_onTrack)GetProcAddress(module, "_preval_bsmod_onTrack");
    functions.bsmod_onPackBindings = (PFN_bsmod_onPackBindings)GetProcAddress(module, "_preval_bsmod_onPackBindings");
    functions.bsmod_onCompileShader = (PFN_bsmod_onCompileShader)GetProcAddress(module, "_preval_bsmod_onCompileShader");
    functions.bsmod_onLoadTTF = (PFN_bsmod_onLoadTTF)GetProcAddress(module, "_preval_bsmod_onLoadTTF");
    functions.bsmod_onConvertBMFont = (PFN_bsmod_onConvertBMFont)GetProcAddress(module, "_preval_bsmod_onConvertBMFont");
    functions.bsmod_onPackAtlas = (PFN_bsmod_onPackAtlas)GetProcAddress(module, "_preval_bsmod_onPackAtlas");
    functions.bsmod_onPackModels = (PFN_bsmod_onPackModels)GetProcAddress(module, "_preval_bsmod_onPackModels");
    functions.bsmod_onPackBinary = (PFN_bsmod_onPackBinary)GetProcAddress(module, "_preval_bsmod_onPackBinary");
    functions.bsmod_onPackTextureArray = (PFN_bsmod_onPackTextureArray)GetProcAddress(module, "_preval_bsmod_onPackTextureArray");
    functions.bsmod_packAtlasTexture = (PFN_bsmod_packAtlasTexture)GetProcAddress(module, "_preval_bsmod_packAtlasTexture");
    functions.bsmod_packAtlas = (PFN_bsmod_packAtlas)GetProcAddress(module, "_preval_bsmod_packAtlas");
    functions.bsmod_createAtlasPacker = (PFN_bsmod_createAtlasPacker)GetProcAddress(module, "_preval_bsmod_createAtlasPacker");
    functions.bsmod_packImageDirectory = (PFN_bsmod_packImageDirectory)GetProcAddress(module, "_preval_bsmod_packImageDirectory");
    functions.bsmod_packBMFont = (PFN_bsmod_packBMFont)GetProcAddress(module, "_preval_bsmod_packBMFont");
    functions.bsmod_scrollbar = (PFN_bsmod_scrollbar)GetProcAddress(module, "_preval_bsmod_scrollbar");
    functions.bsmod_dividerWidget = (PFN_bsmod_dividerWidget)GetProcAddress(module, "_preval_bsmod_dividerWidget");
    functions.bsmod_iconWidget = (PFN_bsmod_iconWidget)GetProcAddress(module, "_preval_bsmod_iconWidget");
    functions.bsmod_packages = (PFN_bsmod_packages)GetProcAddress(module, "_preval_bsmod_packages");
    functions.bsmod_queryPackage = (PFN_bsmod_queryPackage)GetProcAddress(module, "_preval_bsmod_queryPackage");
    functions.bsmod_ensurePackage = (PFN_bsmod_ensurePackage)GetProcAddress(module, "_preval_bsmod_ensurePackage");
    functions.bsmod_queryResource = (PFN_bsmod_queryResource)GetProcAddress(module, "_preval_bsmod_queryResource");
    functions.bsmod_iniPackage = (PFN_bsmod_iniPackage)GetProcAddress(module, "_preval_bsmod_iniPackage");
    functions.bsmod_packResource = (PFN_bsmod_packResource)GetProcAddress(module, "_preval_bsmod_packResource");
    functions.bsmod_savePackage = (PFN_bsmod_savePackage)GetProcAddress(module, "_preval_bsmod_savePackage");
    functions.bsmod_loadShaderReferences = (PFN_bsmod_loadShaderReferences)GetProcAddress(module, "_preval_bsmod_loadShaderReferences");
    functions.bsmod_updateShaderReferences = (PFN_bsmod_updateShaderReferences)GetProcAddress(module, "_preval_bsmod_updateShaderReferences");
    functions.bsmod_iniCompiler = (PFN_bsmod_iniCompiler)GetProcAddress(module, "_preval_bsmod_iniCompiler");
    functions.bsmod_compileShader = (PFN_bsmod_compileShader)GetProcAddress(module, "_preval_bsmod_compileShader");
    functions.bsmod_queueRasterize = (PFN_bsmod_queueRasterize)GetProcAddress(module, "_preval_bsmod_queueRasterize");
    functions.bsmod_pollRasterizer = (PFN_bsmod_pollRasterizer)GetProcAddress(module, "_preval_bsmod_pollRasterizer");
    functions.bsmod_beginRasterize = (PFN_bsmod_beginRasterize)GetProcAddress(module, "_preval_bsmod_beginRasterize");
    functions.bsmod_endRasterize = (PFN_bsmod_endRasterize)GetProcAddress(module, "_preval_bsmod_endRasterize");
    functions.bsmod_rasterizeInstance = (PFN_bsmod_rasterizeInstance)GetProcAddress(module, "_preval_bsmod_rasterizeInstance");
    functions.bsmod_instanceTransform = (PFN_bsmod_instanceTransform)GetProcAddress(module, "_preval_bsmod_instanceTransform");
    functions.bsmod_selectHoveringTypes = (PFN_bsmod_selectHoveringTypes)GetProcAddress(module, "_preval_bsmod_selectHoveringTypes");
    functions.bsmod_queryType = (PFN_bsmod_queryType)GetProcAddress(module, "_preval_bsmod_queryType");
    functions.bsmod_delete = (PFN_bsmod_delete)GetProcAddress(module, "_preval_bsmod_delete");
    functions.bsmod_deleteSelected = (PFN_bsmod_deleteSelected)GetProcAddress(module, "_preval_bsmod_deleteSelected");
    functions.bsmod_saveType = (PFN_bsmod_saveType)GetProcAddress(module, "_preval_bsmod_saveType");
    functions.bsmod_add = (PFN_bsmod_add)GetProcAddress(module, "_preval_bsmod_add");
    functions.bsmod_isSelected = (PFN_bsmod_isSelected)GetProcAddress(module, "_preval_bsmod_isSelected");
    functions.bsmod_select = (PFN_bsmod_select)GetProcAddress(module, "_preval_bsmod_select");
    functions.bsmod_deselectAll = (PFN_bsmod_deselectAll)GetProcAddress(module, "_preval_bsmod_deselectAll");
    functions.bsmod_deselectRange = (PFN_bsmod_deselectRange)GetProcAddress(module, "_preval_bsmod_deselectRange");
    functions.bsmod_deselectIndex = (PFN_bsmod_deselectIndex)GetProcAddress(module, "_preval_bsmod_deselectIndex");
    functions.bsmod_deselect = (PFN_bsmod_deselect)GetProcAddress(module, "_preval_bsmod_deselect");
    functions.bsmod_firstSelectedId = (PFN_bsmod_firstSelectedId)GetProcAddress(module, "_preval_bsmod_firstSelectedId");
    functions.bsmod_lastSelectedId = (PFN_bsmod_lastSelectedId)GetProcAddress(module, "_preval_bsmod_lastSelectedId");
    functions.bsmod_removeFlexible = (PFN_bsmod_removeFlexible)GetProcAddress(module, "_preval_bsmod_removeFlexible");
    functions.bsmod_addFlexible = (PFN_bsmod_addFlexible)GetProcAddress(module, "_preval_bsmod_addFlexible");
    functions.bsmod_readHoveringOutputs = (PFN_bsmod_readHoveringOutputs)GetProcAddress(module, "_preval_bsmod_readHoveringOutputs");
    functions.bsmod_readHoveringInstanceData = (PFN_bsmod_readHoveringInstanceData)GetProcAddress(module, "_preval_bsmod_readHoveringInstanceData");
    functions.bsmod_readHoveringVertex = (PFN_bsmod_readHoveringVertex)GetProcAddress(module, "_preval_bsmod_readHoveringVertex");
    functions.bsmod_editSelectedType = (PFN_bsmod_editSelectedType)GetProcAddress(module, "_preval_bsmod_editSelectedType");
    functions.bsmod_ensureTypeVersionsAreUpToDate = (PFN_bsmod_ensureTypeVersionsAreUpToDate)GetProcAddress(module, "_preval_bsmod_ensureTypeVersionsAreUpToDate");
    functions.bsmod_renderBillboards = (PFN_bsmod_renderBillboards)GetProcAddress(module, "_preval_bsmod_renderBillboards");
    functions.bsmod_instanceUI = (PFN_bsmod_instanceUI)GetProcAddress(module, "_preval_bsmod_instanceUI");
    functions.bsmod_pushVecNWidget = (PFN_bsmod_pushVecNWidget)GetProcAddress(module, "_preval_bsmod_pushVecNWidget");
    functions.bsmod_pushInputWidget = (PFN_bsmod_pushInputWidget)GetProcAddress(module, "_preval_bsmod_pushInputWidget");
    functions.bsmod_instanceTileContextMenu = (PFN_bsmod_instanceTileContextMenu)GetProcAddress(module, "_preval_bsmod_instanceTileContextMenu");
    functions.bsmod_instanceContextMenu = (PFN_bsmod_instanceContextMenu)GetProcAddress(module, "_preval_bsmod_instanceContextMenu");
    functions.bsmod_pushContextMenuButton = (PFN_bsmod_pushContextMenuButton)GetProcAddress(module, "_preval_bsmod_pushContextMenuButton");
    functions.bsmod_instanceGridMenu = (PFN_bsmod_instanceGridMenu)GetProcAddress(module, "_preval_bsmod_instanceGridMenu");
    functions.bsmod_instanceLightBillboards = (PFN_bsmod_instanceLightBillboards)GetProcAddress(module, "_preval_bsmod_instanceLightBillboards");
    functions.bsmod_pushMaterialWidgets = (PFN_bsmod_pushMaterialWidgets)GetProcAddress(module, "_preval_bsmod_pushMaterialWidgets");
    functions.bsmod_onDragMaterial = (PFN_bsmod_onDragMaterial)GetProcAddress(module, "_preval_bsmod_onDragMaterial");
    functions.bsmod_onClickMaterialMenu = (PFN_bsmod_onClickMaterialMenu)GetProcAddress(module, "_preval_bsmod_onClickMaterialMenu");
    functions.bsmod_rasterizeMaterialIcons = (PFN_bsmod_rasterizeMaterialIcons)GetProcAddress(module, "_preval_bsmod_rasterizeMaterialIcons");
    functions.bsmod_pushPrefabMenuWidgets = (PFN_bsmod_pushPrefabMenuWidgets)GetProcAddress(module, "_preval_bsmod_pushPrefabMenuWidgets");
    functions.bsmod_instancePrefabPreview = (PFN_bsmod_instancePrefabPreview)GetProcAddress(module, "_preval_bsmod_instancePrefabPreview");
    functions.bsmod_onDragPrefab = (PFN_bsmod_onDragPrefab)GetProcAddress(module, "_preval_bsmod_onDragPrefab");
    functions.bsmod_rasterizePrefabIcons = (PFN_bsmod_rasterizePrefabIcons)GetProcAddress(module, "_preval_bsmod_rasterizePrefabIcons");
    functions.bsmod_instancePrimitivePreview = (PFN_bsmod_instancePrimitivePreview)GetProcAddress(module, "_preval_bsmod_instancePrimitivePreview");
    functions.bsmod_onDragPrimitive = (PFN_bsmod_onDragPrimitive)GetProcAddress(module, "_preval_bsmod_onDragPrimitive");
    functions.bsmod_rasterizePrimitiveIcons = (PFN_bsmod_rasterizePrimitiveIcons)GetProcAddress(module, "_preval_bsmod_rasterizePrimitiveIcons");
    functions.bsmod_setSideMenuTab = (PFN_bsmod_setSideMenuTab)GetProcAddress(module, "_preval_bsmod_setSideMenuTab");
    functions.bsmod_instanceSideMenu = (PFN_bsmod_instanceSideMenu)GetProcAddress(module, "_preval_bsmod_instanceSideMenu");
    functions.bsmod_pushTileMenuWidgets = (PFN_bsmod_pushTileMenuWidgets)GetProcAddress(module, "_preval_bsmod_pushTileMenuWidgets");
    functions.bsmod_instanceTilePreview = (PFN_bsmod_instanceTilePreview)GetProcAddress(module, "_preval_bsmod_instanceTilePreview");
    functions.bsmod_onDragTile = (PFN_bsmod_onDragTile)GetProcAddress(module, "_preval_bsmod_onDragTile");

    return &functions;
}

const bsmod_FunctionTable* _preval_bsmod_setFunctions(const bsmod_FunctionTable* a, bsmod_FunctionTable* b);

#endif
