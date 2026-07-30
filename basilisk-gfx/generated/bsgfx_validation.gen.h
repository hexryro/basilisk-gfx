
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

    HMODULE module = NULL;
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_val_bsgfx_getFunctions),
        &module);

    functions.bsgfx_test = (PFN_bsgfx_test)GetProcAddress(module, "_val_bsgfx_test");
    functions.bsgfx_defaultPipelineHash = (PFN_bsgfx_defaultPipelineHash)GetProcAddress(module, "_val_bsgfx_defaultPipelineHash");
    functions.bsgfx_renderTileIcons = (PFN_bsgfx_renderTileIcons)GetProcAddress(module, "_val_bsgfx_renderTileIcons");
    functions.bsgfx_renderAtlasIcons = (PFN_bsgfx_renderAtlasIcons)GetProcAddress(module, "_val_bsgfx_renderAtlasIcons");
    functions.bsgfx_renderLineModel = (PFN_bsgfx_renderLineModel)GetProcAddress(module, "_val_bsgfx_renderLineModel");
    functions.bsgfx_renderLines = (PFN_bsgfx_renderLines)GetProcAddress(module, "_val_bsgfx_renderLines");
    functions.bsgfx_renderPoints = (PFN_bsgfx_renderPoints)GetProcAddress(module, "_val_bsgfx_renderPoints");
    functions.bsgfx_renderAtlas = (PFN_bsgfx_renderAtlas)GetProcAddress(module, "_val_bsgfx_renderAtlas");
    functions.bsgfx_renderPrimitiveTiles = (PFN_bsgfx_renderPrimitiveTiles)GetProcAddress(module, "_val_bsgfx_renderPrimitiveTiles");
    functions.bsgfx_swapBufferBindings = (PFN_bsgfx_swapBufferBindings)GetProcAddress(module, "_val_bsgfx_swapBufferBindings");
    functions.bsgfx_requiredForShadowVolumes = (PFN_bsgfx_requiredForShadowVolumes)GetProcAddress(module, "_val_bsgfx_requiredForShadowVolumes");
    functions.bsgfx_requiredForStencilShadows = (PFN_bsgfx_requiredForStencilShadows)GetProcAddress(module, "_val_bsgfx_requiredForStencilShadows");
    functions.bsgfx_requiredForTransparency = (PFN_bsgfx_requiredForTransparency)GetProcAddress(module, "_val_bsgfx_requiredForTransparency");
    functions.bsgfx_currentScene = (PFN_bsgfx_currentScene)GetProcAddress(module, "_val_bsgfx_currentScene");
    functions.bsgfx_loadScene = (PFN_bsgfx_loadScene)GetProcAddress(module, "_val_bsgfx_loadScene");
    functions.bsgfx_validateSubtype = (PFN_bsgfx_validateSubtype)GetProcAddress(module, "_val_bsgfx_validateSubtype");
    functions.bsgfx_validateInstanceType = (PFN_bsgfx_validateInstanceType)GetProcAddress(module, "_val_bsgfx_validateInstanceType");
    functions.bsgfx_worldToScreen = (PFN_bsgfx_worldToScreen)GetProcAddress(module, "_val_bsgfx_worldToScreen");
    functions.bsgfx_materialCategoryName = (PFN_bsgfx_materialCategoryName)GetProcAddress(module, "_val_bsgfx_materialCategoryName");
    functions.bsgfx_materials = (PFN_bsgfx_materials)GetProcAddress(module, "_val_bsgfx_materials");
    functions.bsgfx_queryMaterialHash = (PFN_bsgfx_queryMaterialHash)GetProcAddress(module, "_val_bsgfx_queryMaterialHash");
    functions.bsgfx_fetchMaterial = (PFN_bsgfx_fetchMaterial)GetProcAddress(module, "_val_bsgfx_fetchMaterial");
    functions.bsgfx_queryMaterial = (PFN_bsgfx_queryMaterial)GetProcAddress(module, "_val_bsgfx_queryMaterial");
    functions.bsgfx_loadMaterials = (PFN_bsgfx_loadMaterials)GetProcAddress(module, "_val_bsgfx_loadMaterials");
    functions.bsgfx_material = (PFN_bsgfx_material)GetProcAddress(module, "_val_bsgfx_material");
    functions.bsgfx_highlightMaterial = (PFN_bsgfx_highlightMaterial)GetProcAddress(module, "_val_bsgfx_highlightMaterial");
    functions.bsgfx_unhighlightMaterial = (PFN_bsgfx_unhighlightMaterial)GetProcAddress(module, "_val_bsgfx_unhighlightMaterial");
    functions.bsgfx_tickMaterials = (PFN_bsgfx_tickMaterials)GetProcAddress(module, "_val_bsgfx_tickMaterials");
    functions.bsgfx_sweepCollisions = (PFN_bsgfx_sweepCollisions)GetProcAddress(module, "_val_bsgfx_sweepCollisions");
    functions.bsgfx_collider = (PFN_bsgfx_collider)GetProcAddress(module, "_val_bsgfx_collider");
    functions.bsgfx_applyCollisions = (PFN_bsgfx_applyCollisions)GetProcAddress(module, "_val_bsgfx_applyCollisions");
    functions.bsgfx_printCollisions = (PFN_bsgfx_printCollisions)GetProcAddress(module, "_val_bsgfx_printCollisions");
    functions.bsgfx_instanceSweepCollisions = (PFN_bsgfx_instanceSweepCollisions)GetProcAddress(module, "_val_bsgfx_instanceSweepCollisions");
    functions.bsgfx_instanceCollider = (PFN_bsgfx_instanceCollider)GetProcAddress(module, "_val_bsgfx_instanceCollider");
    functions.bsgfx_skeleton = (PFN_bsgfx_skeleton)GetProcAddress(module, "_val_bsgfx_skeleton");
    functions.bsgfx_animationFrame = (PFN_bsgfx_animationFrame)GetProcAddress(module, "_val_bsgfx_animationFrame");
    functions.bsgfx_animationFrameCount = (PFN_bsgfx_animationFrameCount)GetProcAddress(module, "_val_bsgfx_animationFrameCount");
    functions.bsgfx_applyAnimationVelocity = (PFN_bsgfx_applyAnimationVelocity)GetProcAddress(module, "_val_bsgfx_applyAnimationVelocity");
    functions.bsgfx_queueAnimation = (PFN_bsgfx_queueAnimation)GetProcAddress(module, "_val_bsgfx_queueAnimation");
    functions.bsgfx_runAnimator = (PFN_bsgfx_runAnimator)GetProcAddress(module, "_val_bsgfx_runAnimator");
    functions.bsgfx_animator = (PFN_bsgfx_animator)GetProcAddress(module, "_val_bsgfx_animator");
    functions.bsgfx_subtypeInstances = (PFN_bsgfx_subtypeInstances)GetProcAddress(module, "_val_bsgfx_subtypeInstances");
    functions.bsgfx_iniInstances = (PFN_bsgfx_iniInstances)GetProcAddress(module, "_val_bsgfx_iniInstances");
    functions.bsgfx_instanceType = (PFN_bsgfx_instanceType)GetProcAddress(module, "_val_bsgfx_instanceType");
    functions.bsgfx_subtypeRange = (PFN_bsgfx_subtypeRange)GetProcAddress(module, "_val_bsgfx_subtypeRange");
    functions.bsgfx_deleteSubtype = (PFN_bsgfx_deleteSubtype)GetProcAddress(module, "_val_bsgfx_deleteSubtype");
    functions.bsgfx_instanceCount = (PFN_bsgfx_instanceCount)GetProcAddress(module, "_val_bsgfx_instanceCount");
    functions.bsgfx_subtypeCount = (PFN_bsgfx_subtypeCount)GetProcAddress(module, "_val_bsgfx_subtypeCount");
    functions.bsgfx_subtypes = (PFN_bsgfx_subtypes)GetProcAddress(module, "_val_bsgfx_subtypes");
    functions.bsgfx_subtype = (PFN_bsgfx_subtype)GetProcAddress(module, "_val_bsgfx_subtype");
    functions.bsgfx_instance = (PFN_bsgfx_instance)GetProcAddress(module, "_val_bsgfx_instance");
    functions.bsgfx_tickInstances = (PFN_bsgfx_tickInstances)GetProcAddress(module, "_val_bsgfx_tickInstances");
    functions.bsgfx_subtypeHasFlag = (PFN_bsgfx_subtypeHasFlag)GetProcAddress(module, "_val_bsgfx_subtypeHasFlag");
    functions.bsgfx_renderSubtype = (PFN_bsgfx_renderSubtype)GetProcAddress(module, "_val_bsgfx_renderSubtype");
    functions.bsgfx_resetInstances = (PFN_bsgfx_resetInstances)GetProcAddress(module, "_val_bsgfx_resetInstances");
    functions.bsgfx_resetSubtype = (PFN_bsgfx_resetSubtype)GetProcAddress(module, "_val_bsgfx_resetSubtype");
    functions.bsgfx_instanceHiResMesh = (PFN_bsgfx_instanceHiResMesh)GetProcAddress(module, "_val_bsgfx_instanceHiResMesh");
    functions.bsgfx_instanceMesh = (PFN_bsgfx_instanceMesh)GetProcAddress(module, "_val_bsgfx_instanceMesh");
    functions.bsgfx_instanceBoneMesh = (PFN_bsgfx_instanceBoneMesh)GetProcAddress(module, "_val_bsgfx_instanceBoneMesh");
    functions.bsgfx_instanceDepthlessLine = (PFN_bsgfx_instanceDepthlessLine)GetProcAddress(module, "_val_bsgfx_instanceDepthlessLine");
    functions.bsgfx_instanceLine = (PFN_bsgfx_instanceLine)GetProcAddress(module, "_val_bsgfx_instanceLine");
    functions.bsgfx_instanceRay = (PFN_bsgfx_instanceRay)GetProcAddress(module, "_val_bsgfx_instanceRay");
    functions.bsgfx_instanceAabb = (PFN_bsgfx_instanceAabb)GetProcAddress(module, "_val_bsgfx_instanceAabb");
    functions.bsgfx_instanceSphere = (PFN_bsgfx_instanceSphere)GetProcAddress(module, "_val_bsgfx_instanceSphere");
    functions.bsgfx_instanceCone = (PFN_bsgfx_instanceCone)GetProcAddress(module, "_val_bsgfx_instanceCone");
    functions.bsgfx_instancePoint = (PFN_bsgfx_instancePoint)GetProcAddress(module, "_val_bsgfx_instancePoint");
    functions.bsgfx_instanceQuad = (PFN_bsgfx_instanceQuad)GetProcAddress(module, "_val_bsgfx_instanceQuad");
    functions.bsgfx_instanceDepthlessCircle = (PFN_bsgfx_instanceDepthlessCircle)GetProcAddress(module, "_val_bsgfx_instanceDepthlessCircle");
    functions.bsgfx_instanceAtlas = (PFN_bsgfx_instanceAtlas)GetProcAddress(module, "_val_bsgfx_instanceAtlas");
    functions.bsgfx_instanceAtlasFlipped = (PFN_bsgfx_instanceAtlasFlipped)GetProcAddress(module, "_val_bsgfx_instanceAtlasFlipped");
    functions.bsgfx_instanceText = (PFN_bsgfx_instanceText)GetProcAddress(module, "_val_bsgfx_instanceText");
    functions.bsgfx_matrix = (PFN_bsgfx_matrix)GetProcAddress(module, "_val_bsgfx_matrix");
    functions.bsgfx_renderFineShadowVolumes = (PFN_bsgfx_renderFineShadowVolumes)GetProcAddress(module, "_val_bsgfx_renderFineShadowVolumes");
    functions.bsgfx_renderShadowVolumes = (PFN_bsgfx_renderShadowVolumes)GetProcAddress(module, "_val_bsgfx_renderShadowVolumes");
    functions.bsgfx_computeShadowVolumes = (PFN_bsgfx_computeShadowVolumes)GetProcAddress(module, "_val_bsgfx_computeShadowVolumes");
    functions.bsgfx_prefabModel = (PFN_bsgfx_prefabModel)GetProcAddress(module, "_val_bsgfx_prefabModel");
    functions.bsgfx_package = (PFN_bsgfx_package)GetProcAddress(module, "_val_bsgfx_package");
    functions.bsgfx_ini = (PFN_bsgfx_ini)GetProcAddress(module, "_val_bsgfx_ini");
    functions.bsgfx_app = (PFN_bsgfx_app)GetProcAddress(module, "_val_bsgfx_app");
    functions.bsgfx_callbacks = (PFN_bsgfx_callbacks)GetProcAddress(module, "_val_bsgfx_callbacks");
    functions.bsgfx_settings = (PFN_bsgfx_settings)GetProcAddress(module, "_val_bsgfx_settings");
    functions.poser = (PFN_poser)GetProcAddress(module, "_val_poser");
    functions.bsgfx_setCamera = (PFN_bsgfx_setCamera)GetProcAddress(module, "_val_bsgfx_setCamera");
    functions.bsgfx_type = (PFN_bsgfx_type)GetProcAddress(module, "_val_bsgfx_type");
    functions.bsgfx_map = (PFN_bsgfx_map)GetProcAddress(module, "_val_bsgfx_map");
    functions.bsgfx_remap = (PFN_bsgfx_remap)GetProcAddress(module, "_val_bsgfx_remap");
    functions.bsgfx_count = (PFN_bsgfx_count)GetProcAddress(module, "_val_bsgfx_count");
    functions.bsgfx_get = (PFN_bsgfx_get)GetProcAddress(module, "_val_bsgfx_get");
    functions.bsgfx_getType = (PFN_bsgfx_getType)GetProcAddress(module, "_val_bsgfx_getType");
    functions.bsgfx_id = (PFN_bsgfx_id)GetProcAddress(module, "_val_bsgfx_id");
    functions.bsgfx_rawId = (PFN_bsgfx_rawId)GetProcAddress(module, "_val_bsgfx_rawId");
    functions.bsgfx_getRaw = (PFN_bsgfx_getRaw)GetProcAddress(module, "_val_bsgfx_getRaw");
    functions.bsgfx_flexibleCount = (PFN_bsgfx_flexibleCount)GetProcAddress(module, "_val_bsgfx_flexibleCount");
    functions.bsgfx_loadLights = (PFN_bsgfx_loadLights)GetProcAddress(module, "_val_bsgfx_loadLights");
    functions.bsgfx_computePrefabShadows = (PFN_bsgfx_computePrefabShadows)GetProcAddress(module, "_val_bsgfx_computePrefabShadows");
    functions.bsgfx_renderPrefabShadowVolumes = (PFN_bsgfx_renderPrefabShadowVolumes)GetProcAddress(module, "_val_bsgfx_renderPrefabShadowVolumes");
    functions.bsgfx_prefabMetadata = (PFN_bsgfx_prefabMetadata)GetProcAddress(module, "_val_bsgfx_prefabMetadata");
    functions.bsgfx_loadPrefabs = (PFN_bsgfx_loadPrefabs)GetProcAddress(module, "_val_bsgfx_loadPrefabs");
    functions.bsgfx_prefabTransform = (PFN_bsgfx_prefabTransform)GetProcAddress(module, "_val_bsgfx_prefabTransform");
    functions.bsgfx_instancePrefabModel = (PFN_bsgfx_instancePrefabModel)GetProcAddress(module, "_val_bsgfx_instancePrefabModel");
    functions.bsgfx_instancePrefab = (PFN_bsgfx_instancePrefab)GetProcAddress(module, "_val_bsgfx_instancePrefab");
    functions.bsgfx_instancePrefabs = (PFN_bsgfx_instancePrefabs)GetProcAddress(module, "_val_bsgfx_instancePrefabs");
    functions.bsgfx_renderPrefabs = (PFN_bsgfx_renderPrefabs)GetProcAddress(module, "_val_bsgfx_renderPrefabs");
    functions.bsgfx_renderScenePrefabs = (PFN_bsgfx_renderScenePrefabs)GetProcAddress(module, "_val_bsgfx_renderScenePrefabs");
    functions.bsgfx_renderPrefabPrimitives = (PFN_bsgfx_renderPrefabPrimitives)GetProcAddress(module, "_val_bsgfx_renderPrefabPrimitives");
    functions.bsgfx_queryPrefabId = (PFN_bsgfx_queryPrefabId)GetProcAddress(module, "_val_bsgfx_queryPrefabId");
    functions.bsgfx_closestPrefab = (PFN_bsgfx_closestPrefab)GetProcAddress(module, "_val_bsgfx_closestPrefab");
    functions.bsgfx_primitivePosition = (PFN_bsgfx_primitivePosition)GetProcAddress(module, "_val_bsgfx_primitivePosition");
    functions.bsgfx_loadPrimitives = (PFN_bsgfx_loadPrimitives)GetProcAddress(module, "_val_bsgfx_loadPrimitives");
    functions.bsgfx_primitiveSubtype = (PFN_bsgfx_primitiveSubtype)GetProcAddress(module, "_val_bsgfx_primitiveSubtype");
    functions.bsgfx_instancePrimitive = (PFN_bsgfx_instancePrimitive)GetProcAddress(module, "_val_bsgfx_instancePrimitive");
    functions.bsgfx_queryTilePrimitive = (PFN_bsgfx_queryTilePrimitive)GetProcAddress(module, "_val_bsgfx_queryTilePrimitive");
    functions.bsgfx_instancePrimitives = (PFN_bsgfx_instancePrimitives)GetProcAddress(module, "_val_bsgfx_instancePrimitives");
    functions.bsgfx_renderPrimitives = (PFN_bsgfx_renderPrimitives)GetProcAddress(module, "_val_bsgfx_renderPrimitives");
    functions.bsgfx_queryPrimitive = (PFN_bsgfx_queryPrimitive)GetProcAddress(module, "_val_bsgfx_queryPrimitive");
    functions.bsgfx_loadSpawners = (PFN_bsgfx_loadSpawners)GetProcAddress(module, "_val_bsgfx_loadSpawners");
    functions.bsgfx_spawn = (PFN_bsgfx_spawn)GetProcAddress(module, "_val_bsgfx_spawn");
    functions.bsgfx_loadTiles = (PFN_bsgfx_loadTiles)GetProcAddress(module, "_val_bsgfx_loadTiles");
    functions.bsgfx_instanceTiles = (PFN_bsgfx_instanceTiles)GetProcAddress(module, "_val_bsgfx_instanceTiles");
    functions.bsgfx_pushTile = (PFN_bsgfx_pushTile)GetProcAddress(module, "_val_bsgfx_pushTile");
    functions.bsgfx_batchTile = (PFN_bsgfx_batchTile)GetProcAddress(module, "_val_bsgfx_batchTile");
    functions.bsgfx_tileAxes = (PFN_bsgfx_tileAxes)GetProcAddress(module, "_val_bsgfx_tileAxes");
    functions.bsgfx_tilePosition = (PFN_bsgfx_tilePosition)GetProcAddress(module, "_val_bsgfx_tilePosition");
    functions.bsgfx_tileRotation = (PFN_bsgfx_tileRotation)GetProcAddress(module, "_val_bsgfx_tileRotation");
    functions.bsgfx_tileEulerRotation = (PFN_bsgfx_tileEulerRotation)GetProcAddress(module, "_val_bsgfx_tileEulerRotation");
    functions.bsgfx_pushTileAt = (PFN_bsgfx_pushTileAt)GetProcAddress(module, "_val_bsgfx_pushTileAt");
    functions.bsgfx_tileCoordinate = (PFN_bsgfx_tileCoordinate)GetProcAddress(module, "_val_bsgfx_tileCoordinate");
    functions.bsgfx_tileAxis = (PFN_bsgfx_tileAxis)GetProcAddress(module, "_val_bsgfx_tileAxis");
    functions.bsgfx_tileIndex = (PFN_bsgfx_tileIndex)GetProcAddress(module, "_val_bsgfx_tileIndex");
    functions.bsgfx_instanceWidgets = (PFN_bsgfx_instanceWidgets)GetProcAddress(module, "_val_bsgfx_instanceWidgets");
    functions.bsgfx_renderColorPickers = (PFN_bsgfx_renderColorPickers)GetProcAddress(module, "_val_bsgfx_renderColorPickers");

    return &functions;
}

#endif
