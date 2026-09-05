
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

#ifndef BSGFX_VALIDATION_H
#define BSGFX_VALIDATION_H

#include <basilisk-gfx.h>
#include <windows.h>

static inline bsgfx_FunctionTable* _val_bsgfx_getFunctions() {
    static bsgfx_FunctionTable functions;

#ifdef _WIN32
#define bs_getProcAddress(module, name) GetProcAddress(module, name)
    HMODULE module = NULL;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_val_bsgfx_getFunctions),
        &module);

#else
    Dl_info module_info;
    void *module = NULL;
    dladdr((void *)(&_val_bsgfx_getFunctions), &module_info);
    module = dlopen(module_info.dli_fname, RTLD_LAZY);
#define bs_getProcAddress(module, name) dlsym(module, name)
#endif
    functions.bsgfx_test = (PFN_bsgfx_test)bs_getProcAddress(module, "_val_bsgfx_test");
    functions.bsgfx_subtypes = (PFN_bsgfx_subtypes)bs_getProcAddress(module, "_val_bsgfx_subtypes");
    functions.bsgfx_instanceTypes = (PFN_bsgfx_instanceTypes)bs_getProcAddress(module, "_val_bsgfx_instanceTypes");
    functions.bsgfx_computeContextCamera = (PFN_bsgfx_computeContextCamera)bs_getProcAddress(module, "_val_bsgfx_computeContextCamera");
    functions.bsgfx_tickInstanceTypes = (PFN_bsgfx_tickInstanceTypes)bs_getProcAddress(module, "_val_bsgfx_tickInstanceTypes");
    functions.bsgfx_resetInstanceTypes = (PFN_bsgfx_resetInstanceTypes)bs_getProcAddress(module, "_val_bsgfx_resetInstanceTypes");
    functions.bsgfx_textDimensions = (PFN_bsgfx_textDimensions)bs_getProcAddress(module, "_val_bsgfx_textDimensions");
    functions.bsgfx_defaultPipelineHash = (PFN_bsgfx_defaultPipelineHash)bs_getProcAddress(module, "_val_bsgfx_defaultPipelineHash");
    functions.bsgfx_renderTileIcons = (PFN_bsgfx_renderTileIcons)bs_getProcAddress(module, "_val_bsgfx_renderTileIcons");
    functions.bsgfx_renderAtlasIcons = (PFN_bsgfx_renderAtlasIcons)bs_getProcAddress(module, "_val_bsgfx_renderAtlasIcons");
    functions.bsgfx_renderLineModel = (PFN_bsgfx_renderLineModel)bs_getProcAddress(module, "_val_bsgfx_renderLineModel");
    functions.bsgfx_renderLines = (PFN_bsgfx_renderLines)bs_getProcAddress(module, "_val_bsgfx_renderLines");
    functions.bsgfx_renderPoints = (PFN_bsgfx_renderPoints)bs_getProcAddress(module, "_val_bsgfx_renderPoints");
    functions.bsgfx_renderAtlas = (PFN_bsgfx_renderAtlas)bs_getProcAddress(module, "_val_bsgfx_renderAtlas");
    functions.bsgfx_renderPrimitiveTiles = (PFN_bsgfx_renderPrimitiveTiles)bs_getProcAddress(module, "_val_bsgfx_renderPrimitiveTiles");
    functions.bsgfx_swapBufferBindings = (PFN_bsgfx_swapBufferBindings)bs_getProcAddress(module, "_val_bsgfx_swapBufferBindings");
    functions.bsgfx_requiredForShadowVolumes = (PFN_bsgfx_requiredForShadowVolumes)bs_getProcAddress(module, "_val_bsgfx_requiredForShadowVolumes");
    functions.bsgfx_requiredForStencilShadows = (PFN_bsgfx_requiredForStencilShadows)bs_getProcAddress(module, "_val_bsgfx_requiredForStencilShadows");
    functions.bsgfx_requiredForTransparency = (PFN_bsgfx_requiredForTransparency)bs_getProcAddress(module, "_val_bsgfx_requiredForTransparency");
    functions.bsgfx_currentScene = (PFN_bsgfx_currentScene)bs_getProcAddress(module, "_val_bsgfx_currentScene");
    functions.bsgfx_loadScene = (PFN_bsgfx_loadScene)bs_getProcAddress(module, "_val_bsgfx_loadScene");
    functions.bsgfx_validateSubtype = (PFN_bsgfx_validateSubtype)bs_getProcAddress(module, "_val_bsgfx_validateSubtype");
    functions.bsgfx_validateInstanceType = (PFN_bsgfx_validateInstanceType)bs_getProcAddress(module, "_val_bsgfx_validateInstanceType");
    functions.bsgfx_worldToScreen = (PFN_bsgfx_worldToScreen)bs_getProcAddress(module, "_val_bsgfx_worldToScreen");
    functions.bsgfx_materialCategoryName = (PFN_bsgfx_materialCategoryName)bs_getProcAddress(module, "_val_bsgfx_materialCategoryName");
    functions.bsgfx_materials = (PFN_bsgfx_materials)bs_getProcAddress(module, "_val_bsgfx_materials");
    functions.bsgfx_queryMaterialHash = (PFN_bsgfx_queryMaterialHash)bs_getProcAddress(module, "_val_bsgfx_queryMaterialHash");
    functions.bsgfx_fetchMaterial = (PFN_bsgfx_fetchMaterial)bs_getProcAddress(module, "_val_bsgfx_fetchMaterial");
    functions.bsgfx_queryMaterial = (PFN_bsgfx_queryMaterial)bs_getProcAddress(module, "_val_bsgfx_queryMaterial");
    functions.bsgfx_loadMaterials = (PFN_bsgfx_loadMaterials)bs_getProcAddress(module, "_val_bsgfx_loadMaterials");
    functions.bsgfx_material = (PFN_bsgfx_material)bs_getProcAddress(module, "_val_bsgfx_material");
    functions.bsgfx_highlightMaterial = (PFN_bsgfx_highlightMaterial)bs_getProcAddress(module, "_val_bsgfx_highlightMaterial");
    functions.bsgfx_unhighlightMaterial = (PFN_bsgfx_unhighlightMaterial)bs_getProcAddress(module, "_val_bsgfx_unhighlightMaterial");
    functions.bsgfx_tickMaterials = (PFN_bsgfx_tickMaterials)bs_getProcAddress(module, "_val_bsgfx_tickMaterials");
    functions.bsgfx_sweepCollisions = (PFN_bsgfx_sweepCollisions)bs_getProcAddress(module, "_val_bsgfx_sweepCollisions");
    functions.bsgfx_collider = (PFN_bsgfx_collider)bs_getProcAddress(module, "_val_bsgfx_collider");
    functions.bsgfx_applyCollisions = (PFN_bsgfx_applyCollisions)bs_getProcAddress(module, "_val_bsgfx_applyCollisions");
    functions.bsgfx_printCollisions = (PFN_bsgfx_printCollisions)bs_getProcAddress(module, "_val_bsgfx_printCollisions");
    functions.bsgfx_instanceSweepCollisions = (PFN_bsgfx_instanceSweepCollisions)bs_getProcAddress(module, "_val_bsgfx_instanceSweepCollisions");
    functions.bsgfx_instanceCollider = (PFN_bsgfx_instanceCollider)bs_getProcAddress(module, "_val_bsgfx_instanceCollider");
    functions.bsgfx_skeleton = (PFN_bsgfx_skeleton)bs_getProcAddress(module, "_val_bsgfx_skeleton");
    functions.bsgfx_animationFrame = (PFN_bsgfx_animationFrame)bs_getProcAddress(module, "_val_bsgfx_animationFrame");
    functions.bsgfx_animationFrameCount = (PFN_bsgfx_animationFrameCount)bs_getProcAddress(module, "_val_bsgfx_animationFrameCount");
    functions.bsgfx_applyAnimationVelocity = (PFN_bsgfx_applyAnimationVelocity)bs_getProcAddress(module, "_val_bsgfx_applyAnimationVelocity");
    functions.bsgfx_queueAnimation = (PFN_bsgfx_queueAnimation)bs_getProcAddress(module, "_val_bsgfx_queueAnimation");
    functions.bsgfx_runAnimator = (PFN_bsgfx_runAnimator)bs_getProcAddress(module, "_val_bsgfx_runAnimator");
    functions.bsgfx_animator = (PFN_bsgfx_animator)bs_getProcAddress(module, "_val_bsgfx_animator");
    functions.bsgfx_ensureInstanceCount = (PFN_bsgfx_ensureInstanceCount)bs_getProcAddress(module, "_val_bsgfx_ensureInstanceCount");
    functions.bsgfx_instanceType = (PFN_bsgfx_instanceType)bs_getProcAddress(module, "_val_bsgfx_instanceType");
    functions.bsgfx_deleteSubtype = (PFN_bsgfx_deleteSubtype)bs_getProcAddress(module, "_val_bsgfx_deleteSubtype");
    functions.bsgfx_subtype = (PFN_bsgfx_subtype)bs_getProcAddress(module, "_val_bsgfx_subtype");
    functions.bsgfx_instantiate = (PFN_bsgfx_instantiate)bs_getProcAddress(module, "_val_bsgfx_instantiate");
    functions.bsgfx_tickInstanceType = (PFN_bsgfx_tickInstanceType)bs_getProcAddress(module, "_val_bsgfx_tickInstanceType");
    functions.bsgfx_renderSubtype = (PFN_bsgfx_renderSubtype)bs_getProcAddress(module, "_val_bsgfx_renderSubtype");
    functions.bsgfx_resetInstanceType = (PFN_bsgfx_resetInstanceType)bs_getProcAddress(module, "_val_bsgfx_resetInstanceType");
    functions.bsgfx_instanceHiResMesh = (PFN_bsgfx_instanceHiResMesh)bs_getProcAddress(module, "_val_bsgfx_instanceHiResMesh");
    functions.bsgfx_instanceMesh = (PFN_bsgfx_instanceMesh)bs_getProcAddress(module, "_val_bsgfx_instanceMesh");
    functions.bsgfx_instanceBoneMesh = (PFN_bsgfx_instanceBoneMesh)bs_getProcAddress(module, "_val_bsgfx_instanceBoneMesh");
    functions.bsgfx_instanceDepthlessLine = (PFN_bsgfx_instanceDepthlessLine)bs_getProcAddress(module, "_val_bsgfx_instanceDepthlessLine");
    functions.bsgfx_instanceLine = (PFN_bsgfx_instanceLine)bs_getProcAddress(module, "_val_bsgfx_instanceLine");
    functions.bsgfx_instanceRay = (PFN_bsgfx_instanceRay)bs_getProcAddress(module, "_val_bsgfx_instanceRay");
    functions.bsgfx_instanceAabb = (PFN_bsgfx_instanceAabb)bs_getProcAddress(module, "_val_bsgfx_instanceAabb");
    functions.bsgfx_instanceSphere = (PFN_bsgfx_instanceSphere)bs_getProcAddress(module, "_val_bsgfx_instanceSphere");
    functions.bsgfx_instanceCone = (PFN_bsgfx_instanceCone)bs_getProcAddress(module, "_val_bsgfx_instanceCone");
    functions.bsgfx_instancePoint = (PFN_bsgfx_instancePoint)bs_getProcAddress(module, "_val_bsgfx_instancePoint");
    functions.bsgfx_instantiateQuad = (PFN_bsgfx_instantiateQuad)bs_getProcAddress(module, "_val_bsgfx_instantiateQuad");
    functions.bsgfx_instanceDepthlessCircle = (PFN_bsgfx_instanceDepthlessCircle)bs_getProcAddress(module, "_val_bsgfx_instanceDepthlessCircle");
    functions.bsgfx_instanceAtlas = (PFN_bsgfx_instanceAtlas)bs_getProcAddress(module, "_val_bsgfx_instanceAtlas");
    functions.bsgfx_instanceAtlasFlipped = (PFN_bsgfx_instanceAtlasFlipped)bs_getProcAddress(module, "_val_bsgfx_instanceAtlasFlipped");
    functions.bsgfx_fontHeight = (PFN_bsgfx_fontHeight)bs_getProcAddress(module, "_val_bsgfx_fontHeight");
    functions.bsgfx_instantiateASCIIText = (PFN_bsgfx_instantiateASCIIText)bs_getProcAddress(module, "_val_bsgfx_instantiateASCIIText");
    functions.bsgfx_instanceHeader = (PFN_bsgfx_instanceHeader)bs_getProcAddress(module, "_val_bsgfx_instanceHeader");
    functions.bsgfx_instanceData = (PFN_bsgfx_instanceData)bs_getProcAddress(module, "_val_bsgfx_instanceData");
    functions.bsgfx_matrix = (PFN_bsgfx_matrix)bs_getProcAddress(module, "_val_bsgfx_matrix");
    functions.bsgfx_renderFineShadowVolumes = (PFN_bsgfx_renderFineShadowVolumes)bs_getProcAddress(module, "_val_bsgfx_renderFineShadowVolumes");
    functions.bsgfx_renderShadowVolumes = (PFN_bsgfx_renderShadowVolumes)bs_getProcAddress(module, "_val_bsgfx_renderShadowVolumes");
    functions.bsgfx_computeShadowVolumes = (PFN_bsgfx_computeShadowVolumes)bs_getProcAddress(module, "_val_bsgfx_computeShadowVolumes");
    functions.bsgfx_prefabModel = (PFN_bsgfx_prefabModel)bs_getProcAddress(module, "_val_bsgfx_prefabModel");
    functions.bsgfx_package = (PFN_bsgfx_package)bs_getProcAddress(module, "_val_bsgfx_package");
    functions.bsgfx_ini = (PFN_bsgfx_ini)bs_getProcAddress(module, "_val_bsgfx_ini");
    functions.bsgfx_tick = (PFN_bsgfx_tick)bs_getProcAddress(module, "_val_bsgfx_tick");
    functions.bsgfx_app = (PFN_bsgfx_app)bs_getProcAddress(module, "_val_bsgfx_app");
    functions.bsgfx_callbacks = (PFN_bsgfx_callbacks)bs_getProcAddress(module, "_val_bsgfx_callbacks");
    functions.bsgfx_settings = (PFN_bsgfx_settings)bs_getProcAddress(module, "_val_bsgfx_settings");
    functions.bsgfx_setCamera = (PFN_bsgfx_setCamera)bs_getProcAddress(module, "_val_bsgfx_setCamera");
    functions.bsgfx_type = (PFN_bsgfx_type)bs_getProcAddress(module, "_val_bsgfx_type");
    functions.bsgfx_map = (PFN_bsgfx_map)bs_getProcAddress(module, "_val_bsgfx_map");
    functions.bsgfx_remap = (PFN_bsgfx_remap)bs_getProcAddress(module, "_val_bsgfx_remap");
    functions.bsgfx_count = (PFN_bsgfx_count)bs_getProcAddress(module, "_val_bsgfx_count");
    functions.bsgfx_get = (PFN_bsgfx_get)bs_getProcAddress(module, "_val_bsgfx_get");
    functions.bsgfx_getType = (PFN_bsgfx_getType)bs_getProcAddress(module, "_val_bsgfx_getType");
    functions.bsgfx_id = (PFN_bsgfx_id)bs_getProcAddress(module, "_val_bsgfx_id");
    functions.bsgfx_rawId = (PFN_bsgfx_rawId)bs_getProcAddress(module, "_val_bsgfx_rawId");
    functions.bsgfx_getRaw = (PFN_bsgfx_getRaw)bs_getProcAddress(module, "_val_bsgfx_getRaw");
    functions.bsgfx_flexibleCount = (PFN_bsgfx_flexibleCount)bs_getProcAddress(module, "_val_bsgfx_flexibleCount");
    functions.bsgfx_loadLights = (PFN_bsgfx_loadLights)bs_getProcAddress(module, "_val_bsgfx_loadLights");
    functions.bsgfx_computePrefabShadows = (PFN_bsgfx_computePrefabShadows)bs_getProcAddress(module, "_val_bsgfx_computePrefabShadows");
    functions.bsgfx_renderPrefabShadowVolumes = (PFN_bsgfx_renderPrefabShadowVolumes)bs_getProcAddress(module, "_val_bsgfx_renderPrefabShadowVolumes");
    functions.bsgfx_prefabMetadata = (PFN_bsgfx_prefabMetadata)bs_getProcAddress(module, "_val_bsgfx_prefabMetadata");
    functions.bsgfx_loadPrefabs = (PFN_bsgfx_loadPrefabs)bs_getProcAddress(module, "_val_bsgfx_loadPrefabs");
    functions.bsgfx_prefabTransform = (PFN_bsgfx_prefabTransform)bs_getProcAddress(module, "_val_bsgfx_prefabTransform");
    functions.bsgfx_instancePrefabModel = (PFN_bsgfx_instancePrefabModel)bs_getProcAddress(module, "_val_bsgfx_instancePrefabModel");
    functions.bsgfx_instancePrefab = (PFN_bsgfx_instancePrefab)bs_getProcAddress(module, "_val_bsgfx_instancePrefab");
    functions.bsgfx_instancePrefabs = (PFN_bsgfx_instancePrefabs)bs_getProcAddress(module, "_val_bsgfx_instancePrefabs");
    functions.bsgfx_renderPrefabs = (PFN_bsgfx_renderPrefabs)bs_getProcAddress(module, "_val_bsgfx_renderPrefabs");
    functions.bsgfx_renderPrefabPrimitives = (PFN_bsgfx_renderPrefabPrimitives)bs_getProcAddress(module, "_val_bsgfx_renderPrefabPrimitives");
    functions.bsgfx_queryPrefabId = (PFN_bsgfx_queryPrefabId)bs_getProcAddress(module, "_val_bsgfx_queryPrefabId");
    functions.bsgfx_closestPrefab = (PFN_bsgfx_closestPrefab)bs_getProcAddress(module, "_val_bsgfx_closestPrefab");
    functions.bsgfx_primitivePosition = (PFN_bsgfx_primitivePosition)bs_getProcAddress(module, "_val_bsgfx_primitivePosition");
    functions.bsgfx_loadPrimitives = (PFN_bsgfx_loadPrimitives)bs_getProcAddress(module, "_val_bsgfx_loadPrimitives");
    functions.bsgfx_primitiveSubtype = (PFN_bsgfx_primitiveSubtype)bs_getProcAddress(module, "_val_bsgfx_primitiveSubtype");
    functions.bsgfx_instancePrimitive = (PFN_bsgfx_instancePrimitive)bs_getProcAddress(module, "_val_bsgfx_instancePrimitive");
    functions.bsgfx_queryTilePrimitive = (PFN_bsgfx_queryTilePrimitive)bs_getProcAddress(module, "_val_bsgfx_queryTilePrimitive");
    functions.bsgfx_instancePrimitives = (PFN_bsgfx_instancePrimitives)bs_getProcAddress(module, "_val_bsgfx_instancePrimitives");
    functions.bsgfx_renderPrimitives = (PFN_bsgfx_renderPrimitives)bs_getProcAddress(module, "_val_bsgfx_renderPrimitives");
    functions.bsgfx_queryPrimitive = (PFN_bsgfx_queryPrimitive)bs_getProcAddress(module, "_val_bsgfx_queryPrimitive");
    functions.bsgfx_loadSpawners = (PFN_bsgfx_loadSpawners)bs_getProcAddress(module, "_val_bsgfx_loadSpawners");
    functions.bsgfx_spawn = (PFN_bsgfx_spawn)bs_getProcAddress(module, "_val_bsgfx_spawn");
    functions.bsgfx_loadTiles = (PFN_bsgfx_loadTiles)bs_getProcAddress(module, "_val_bsgfx_loadTiles");
    functions.bsgfx_instanceTiles = (PFN_bsgfx_instanceTiles)bs_getProcAddress(module, "_val_bsgfx_instanceTiles");
    functions.bsgfx_pushTile = (PFN_bsgfx_pushTile)bs_getProcAddress(module, "_val_bsgfx_pushTile");
    functions.bsgfx_batchTile = (PFN_bsgfx_batchTile)bs_getProcAddress(module, "_val_bsgfx_batchTile");
    functions.bsgfx_tileAxes = (PFN_bsgfx_tileAxes)bs_getProcAddress(module, "_val_bsgfx_tileAxes");
    functions.bsgfx_tilePosition = (PFN_bsgfx_tilePosition)bs_getProcAddress(module, "_val_bsgfx_tilePosition");
    functions.bsgfx_tileRotation = (PFN_bsgfx_tileRotation)bs_getProcAddress(module, "_val_bsgfx_tileRotation");
    functions.bsgfx_tileEulerRotation = (PFN_bsgfx_tileEulerRotation)bs_getProcAddress(module, "_val_bsgfx_tileEulerRotation");
    functions.bsgfx_pushTileAt = (PFN_bsgfx_pushTileAt)bs_getProcAddress(module, "_val_bsgfx_pushTileAt");
    functions.bsgfx_tileCoordinate = (PFN_bsgfx_tileCoordinate)bs_getProcAddress(module, "_val_bsgfx_tileCoordinate");
    functions.bsgfx_tileAxis = (PFN_bsgfx_tileAxis)bs_getProcAddress(module, "_val_bsgfx_tileAxis");
    functions.bsgfx_tileIndex = (PFN_bsgfx_tileIndex)bs_getProcAddress(module, "_val_bsgfx_tileIndex");
    functions.bsgfx_instanceWidgets = (PFN_bsgfx_instanceWidgets)bs_getProcAddress(module, "_val_bsgfx_instanceWidgets");
    functions.bsgfx_instantiateTextUI = (PFN_bsgfx_instantiateTextUI)bs_getProcAddress(module, "_val_bsgfx_instantiateTextUI");
    functions.bsgfx_instantiateSolidUI = (PFN_bsgfx_instantiateSolidUI)bs_getProcAddress(module, "_val_bsgfx_instantiateSolidUI");
    functions.bsgfx_instantiateSolidUIElement = (PFN_bsgfx_instantiateSolidUIElement)bs_getProcAddress(module, "_val_bsgfx_instantiateSolidUIElement");
    functions.bsgfx_solidUIElement = (PFN_bsgfx_solidUIElement)bs_getProcAddress(module, "_val_bsgfx_solidUIElement");
    functions.bsgfx_instantiateAtlasIconUI = (PFN_bsgfx_instantiateAtlasIconUI)bs_getProcAddress(module, "_val_bsgfx_instantiateAtlasIconUI");
    functions.bsgfx_instantiateAtlasIconUIElement = (PFN_bsgfx_instantiateAtlasIconUIElement)bs_getProcAddress(module, "_val_bsgfx_instantiateAtlasIconUIElement");
    functions.bsgfx_atlasIconUIElement = (PFN_bsgfx_atlasIconUIElement)bs_getProcAddress(module, "_val_bsgfx_atlasIconUIElement");
    functions.bsgfx_hoveringUIElement = (PFN_bsgfx_hoveringUIElement)bs_getProcAddress(module, "_val_bsgfx_hoveringUIElement");
    functions.bsgfx_translateUIElement = (PFN_bsgfx_translateUIElement)bs_getProcAddress(module, "_val_bsgfx_translateUIElement");
    functions.bsgfx_renderColorPickers = (PFN_bsgfx_renderColorPickers)bs_getProcAddress(module, "_val_bsgfx_renderColorPickers");

    #undef bs_getProcAddress
#ifndef _WIN32
    dlclose(module);
#endif
    return &functions;
}

#endif
