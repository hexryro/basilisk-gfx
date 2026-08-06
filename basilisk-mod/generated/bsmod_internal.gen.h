
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
        
#ifndef BSMOD_INTERNAL_GEN_H
#define BSMOD_INTERNAL_GEN_H

#include <basilisk-mod.h>
#include <windows.h>

typedef const int*(__stdcall* PFN_bsmod_subtypes)();
typedef bsmod_Callbacks*(__stdcall* PFN_bsmod_callbacks)();
typedef void(__stdcall* PFN_bsmod_copyHoveringDataToBuffer)();
typedef void(__stdcall* PFN_bsmod_onIni)();
typedef void(__stdcall* PFN_bsmod_onLateIni)();
typedef void(__stdcall* PFN_bsmod_onCreateQuadSubtypes)(bs_Range range);
typedef void(__stdcall* PFN_bsmod_onLoad)();
typedef void(__stdcall* PFN_bsmod_bindAtlases)();
typedef void(__stdcall* PFN_bsmod_onGfxRender)();
typedef void(__stdcall* PFN_bsmod_onTick)();
typedef void(__stdcall* PFN_bsmod_onMap)(bsgfx_TypeId type_id, int id);
typedef void(__stdcall* PFN_bsmod_onTrack)();
typedef bs_Result(__stdcall* PFN_bsmod_onPackBindings)();
typedef void(__stdcall* PFN_bsmod_onCompileShader)(bsmod_TrackParams params);
typedef void(__stdcall* PFN_bsmod_onConvertFont)(bsmod_TrackParams params);
typedef void(__stdcall* PFN_bsmod_onPackAtlas)(bsmod_TrackParams params);
typedef void(__stdcall* PFN_bsmod_onPackModels)(bsmod_TrackParams params);
typedef void(__stdcall* PFN_bsmod_onPackBinary)(bsmod_TrackParams params);
typedef void(__stdcall* PFN_bsmod_onPackTextureArray)(bsmod_TrackParams params);
typedef bs_Result(__stdcall* PFN_bsmod_packFont)(char* package_name, char* ttf_path, bsmod_UnicodeBlockRange blocks[], int blocks_count, int pt_sizes[], int pt_sizes_count, char* resource_name, int resource_name_length);
typedef bsmod_TextureInfo*(__stdcall* PFN_bsmod_packAtlasTexture)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* name);
typedef bsmod_TextureInfo*(__stdcall* PFN_bsmod_packAtlasTextureN)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* name, int name_length);
typedef bsmod_TextureInfo*(__stdcall* PFN_bsmod_packAtlasTextureV)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* format, va_list args);
typedef bsmod_TextureInfo*(__stdcall* PFN_bsmod_packAtlasTextureF)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* format, ...);
typedef void(__stdcall* PFN_bsmod_destroyAtlasPacker)(bsmod_AtlasPacker* packer);
typedef bs_Result(__stdcall* PFN_bsmod_packAtlas)(bsmod_AtlasPacker* packer, int width, int height, int channels_count, char* package, char* resource_name, bool allow_paging);
typedef bsmod_AtlasPacker(__stdcall* PFN_bsmod_createAtlasPacker)();
typedef bs_Result(__stdcall* PFN_bsmod_packImageDirectory)(char* directory_name, char* package_name, char* resource_name);
typedef void(__stdcall* PFN_bsmod_scrollbar)(const int* scroll, bsgfx_Scrollbar* out);
typedef void(__stdcall* PFN_bsmod_dividerWidget)(float width, int indent, bsgfx_Widget* out);
typedef void(__stdcall* PFN_bsmod_iconWidget)(const bsgfx_AtlasCache* cache, float align_height, bs_vec3 offset, bs_U32 advance_flags, bsgfx_Widget* out);
typedef bs_List*(__stdcall* PFN_bsmod_packages)();
typedef bsmod_Package*(__stdcall* PFN_bsmod_queryPackage)(const char* path);
typedef bsmod_Package*(__stdcall* PFN_bsmod_ensurePackage)(const char* path);
typedef bsmod_Resource*(__stdcall* PFN_bsmod_queryResource)(bsmod_Package* package, bs_ResourceType type, const char* name);
typedef bs_Result(__stdcall* PFN_bsmod_iniPackage)(int package_id);
typedef bs_Result(__stdcall* PFN_bsmod_packResource)(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* resource_name);
typedef bs_Result(__stdcall* PFN_bsmod_packResourceN)(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* resource_name, int resource_name_length);
typedef bs_Result(__stdcall* PFN_bsmod_packResourceV)(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* format, va_list args);
typedef bs_Result(__stdcall* PFN_bsmod_packResourceF)(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* format, ...);
typedef bs_Result(__stdcall* PFN_bsmod_savePackage)(char* path);
typedef bs_Result(__stdcall* PFN_bsmod_savePackageN)(char* path, int path_length);
typedef bs_Result(__stdcall* PFN_bsmod_savePackageV)(char* format, va_list args);
typedef bs_Result(__stdcall* PFN_bsmod_savePackageF)(char* format, ...);
typedef void(__stdcall* PFN_bsmod_loadShaderReferences)();
typedef void(__stdcall* PFN_bsmod_updateShaderReferences)();
typedef void(__stdcall* PFN_bsmod_iniCompiler)();
typedef bs_Result(__stdcall* PFN_bsmod_compileShader)(char* path, char* name, char* package);
typedef void(__stdcall* PFN_bsmod_queueRasterize)(const char* package, const char* name, bs_Callback callback);
typedef void(__stdcall* PFN_bsmod_pollRasterizer)();
typedef void(__stdcall* PFN_bsmod_beginRasterize)(bs_ivec2 render_size, bs_ivec2 output_size);
typedef void(__stdcall* PFN_bsmod_endRasterize)();
typedef bs_Result(__stdcall* PFN_bsmod_rasterizeInstance)(bs_PipelineHash pipeline_hash, int subtype, int instance_id, int category, char* name, int width, int height, size_t push_constant_size, unsigned char* push_constant);
typedef void(__stdcall* PFN_bsmod_instanceTransform)();
typedef void(__stdcall* PFN_bsmod_selectHoveringTypes)();
typedef bsgfx_TypeId(__stdcall* PFN_bsmod_queryType)(const char* plural);
typedef void(__stdcall* PFN_bsmod_delete)(bsgfx_TypeId type_id, int id);
typedef void(__stdcall* PFN_bsmod_deleteSelected)(bsgfx_TypeId type_id);
typedef bs_Result(__stdcall* PFN_bsmod_saveType)(bsgfx_TypeId id, char* value);
typedef bs_Result(__stdcall* PFN_bsmod_saveTypeN)(bsgfx_TypeId id, char* value, int value_length);
typedef bs_Result(__stdcall* PFN_bsmod_saveTypeV)(bsgfx_TypeId id, char* format, va_list args);
typedef bs_Result(__stdcall* PFN_bsmod_saveTypeF)(bsgfx_TypeId id, char* format, ...);
typedef void*(__stdcall* PFN_bsmod_add)(bsgfx_TypeId id, void* data);
typedef bool(__stdcall* PFN_bsmod_isSelected)(bs_List* list, bsgfx_TypeId type, int id);
typedef void(__stdcall* PFN_bsmod_select)(bs_List* list, bsgfx_TypeId type, int id);
typedef void(__stdcall* PFN_bsmod_deselectAll)();
typedef void(__stdcall* PFN_bsmod_deselectRange)(bs_List* list, int first, int count);
typedef void(__stdcall* PFN_bsmod_deselectIndex)(bs_List* list, int id);
typedef void(__stdcall* PFN_bsmod_deselect)(bs_List* list, int id);
typedef int(__stdcall* PFN_bsmod_firstSelectedId)(bs_List* list);
typedef int(__stdcall* PFN_bsmod_lastSelectedId)(bs_List* list);
typedef void*(__stdcall* PFN_bsmod_removeFlexible)(bsgfx_TypeId type_id, int id);
typedef void*(__stdcall* PFN_bsmod_addFlexible)(bsgfx_TypeId type_id, int id, void* data);
typedef void(__stdcall* PFN_bsmod_readHoveringOutputs)();
typedef void(__stdcall* PFN_bsmod_readHoveringInstanceData)();
typedef void(__stdcall* PFN_bsmod_readHoveringVertex)();
typedef void(__stdcall* PFN_bsmod_editSelectedType)();
typedef void(__stdcall* PFN_bsmod_ensureTypeVersionsAreUpToDate)(int package_id);
typedef void(__stdcall* PFN_bsmod_renderBillboards)();
typedef void(__stdcall* PFN_bsmod_instanceUI)();
typedef void(__stdcall* PFN_bsmod_pushVecNWidget)(bs_List* widgets, const char* name, bs_vec3 offset, float width, float* v, int n);
typedef void(__stdcall* PFN_bsmod_pushInputWidget)(bs_List* widgets, void* value, bs_vec3 offset, float width, int name_padding, bool skip_advance, bool is_last, bool has_buttons, const char* name);
typedef void(__stdcall* PFN_bsmod_instanceTileContextMenu)(bs_vec3 position, bs_vec2 size);
typedef void(__stdcall* PFN_bsmod_instanceContextMenu)(bs_List* widgets, bs_vec3 position, bs_vec2 size);
typedef void(__stdcall* PFN_bsmod_pushContextMenuButton)(bs_List* widgets, bs_vec2 menu_size, bs_vec3 icon_offset, bsgfx_AtlasCache* icon, const char* name, int indent, PFN_bsgfx_ButtonWidgetCallback action, bool expandable);
typedef void(__stdcall* PFN_bsmod_instanceGridMenu)(bs_vec3 position, bs_vec2 dimensions);
typedef void(__stdcall* PFN_bsmod_instanceLightBillboards)();
typedef void(__stdcall* PFN_bsmod_pushMaterialWidgets)(bs_List* widgets, bs_vec2 background_size);
typedef void(__stdcall* PFN_bsmod_onDragMaterial)(bsmod_DraggingParams params);
typedef void(__stdcall* PFN_bsmod_onClickMaterialMenu)(bsmod_GridClickParams params);
typedef void(__stdcall* PFN_bsmod_rasterizeMaterialIcons)();
typedef void(__stdcall* PFN_bsmod_pushPrefabMenuWidgets)(bs_List* widgets, bs_vec2 background_size);
typedef bool(__stdcall* PFN_bsmod_instancePrefabPreview)(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering);
typedef void(__stdcall* PFN_bsmod_onDragPrefab)(bsmod_DraggingParams params);
typedef void(__stdcall* PFN_bsmod_rasterizePrefabIcons)();
typedef bool(__stdcall* PFN_bsmod_instancePrimitivePreview)(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering);
typedef void(__stdcall* PFN_bsmod_onDragPrimitive)(bsmod_DraggingParams params);
typedef void(__stdcall* PFN_bsmod_rasterizePrimitiveIcons)();
typedef void(__stdcall* PFN_bsmod_setSideMenuTab)(int id, bsmod_GridClickParams params);
typedef void(__stdcall* PFN_bsmod_instanceSideMenu)(bs_vec3 position, bs_vec2 dimensions);
typedef void(__stdcall* PFN_bsmod_pushTileMenuWidgets)(bs_List* widgets, bs_vec2 background_size);
typedef bool(__stdcall* PFN_bsmod_instanceTilePreview)(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering);
typedef void(__stdcall* PFN_bsmod_onDragTile)(bsmod_DraggingParams params);

typedef struct {
    PFN_bsmod_subtypes bsmod_subtypes;
    PFN_bsmod_callbacks bsmod_callbacks;
    PFN_bsmod_copyHoveringDataToBuffer bsmod_copyHoveringDataToBuffer;
    PFN_bsmod_onIni bsmod_onIni;
    PFN_bsmod_onLateIni bsmod_onLateIni;
    PFN_bsmod_onCreateQuadSubtypes bsmod_onCreateQuadSubtypes;
    PFN_bsmod_onLoad bsmod_onLoad;
    PFN_bsmod_bindAtlases bsmod_bindAtlases;
    PFN_bsmod_onGfxRender bsmod_onGfxRender;
    PFN_bsmod_onTick bsmod_onTick;
    PFN_bsmod_onMap bsmod_onMap;
    PFN_bsmod_onTrack bsmod_onTrack;
    PFN_bsmod_onPackBindings bsmod_onPackBindings;
    PFN_bsmod_onCompileShader bsmod_onCompileShader;
    PFN_bsmod_onConvertFont bsmod_onConvertFont;
    PFN_bsmod_onPackAtlas bsmod_onPackAtlas;
    PFN_bsmod_onPackModels bsmod_onPackModels;
    PFN_bsmod_onPackBinary bsmod_onPackBinary;
    PFN_bsmod_onPackTextureArray bsmod_onPackTextureArray;
    PFN_bsmod_packFont bsmod_packFont;
    PFN_bsmod_packAtlasTexture bsmod_packAtlasTexture;
    PFN_bsmod_packAtlasTextureN bsmod_packAtlasTextureN;
    PFN_bsmod_packAtlasTextureV bsmod_packAtlasTextureV;
    PFN_bsmod_packAtlasTextureF bsmod_packAtlasTextureF;
    PFN_bsmod_destroyAtlasPacker bsmod_destroyAtlasPacker;
    PFN_bsmod_packAtlas bsmod_packAtlas;
    PFN_bsmod_createAtlasPacker bsmod_createAtlasPacker;
    PFN_bsmod_packImageDirectory bsmod_packImageDirectory;
    PFN_bsmod_scrollbar bsmod_scrollbar;
    PFN_bsmod_dividerWidget bsmod_dividerWidget;
    PFN_bsmod_iconWidget bsmod_iconWidget;
    PFN_bsmod_packages bsmod_packages;
    PFN_bsmod_queryPackage bsmod_queryPackage;
    PFN_bsmod_ensurePackage bsmod_ensurePackage;
    PFN_bsmod_queryResource bsmod_queryResource;
    PFN_bsmod_iniPackage bsmod_iniPackage;
    PFN_bsmod_packResource bsmod_packResource;
    PFN_bsmod_packResourceN bsmod_packResourceN;
    PFN_bsmod_packResourceV bsmod_packResourceV;
    PFN_bsmod_packResourceF bsmod_packResourceF;
    PFN_bsmod_savePackage bsmod_savePackage;
    PFN_bsmod_savePackageN bsmod_savePackageN;
    PFN_bsmod_savePackageV bsmod_savePackageV;
    PFN_bsmod_savePackageF bsmod_savePackageF;
    PFN_bsmod_loadShaderReferences bsmod_loadShaderReferences;
    PFN_bsmod_updateShaderReferences bsmod_updateShaderReferences;
    PFN_bsmod_iniCompiler bsmod_iniCompiler;
    PFN_bsmod_compileShader bsmod_compileShader;
    PFN_bsmod_queueRasterize bsmod_queueRasterize;
    PFN_bsmod_pollRasterizer bsmod_pollRasterizer;
    PFN_bsmod_beginRasterize bsmod_beginRasterize;
    PFN_bsmod_endRasterize bsmod_endRasterize;
    PFN_bsmod_rasterizeInstance bsmod_rasterizeInstance;
    PFN_bsmod_instanceTransform bsmod_instanceTransform;
    PFN_bsmod_selectHoveringTypes bsmod_selectHoveringTypes;
    PFN_bsmod_queryType bsmod_queryType;
    PFN_bsmod_delete bsmod_delete;
    PFN_bsmod_deleteSelected bsmod_deleteSelected;
    PFN_bsmod_saveType bsmod_saveType;
    PFN_bsmod_saveTypeN bsmod_saveTypeN;
    PFN_bsmod_saveTypeV bsmod_saveTypeV;
    PFN_bsmod_saveTypeF bsmod_saveTypeF;
    PFN_bsmod_add bsmod_add;
    PFN_bsmod_isSelected bsmod_isSelected;
    PFN_bsmod_select bsmod_select;
    PFN_bsmod_deselectAll bsmod_deselectAll;
    PFN_bsmod_deselectRange bsmod_deselectRange;
    PFN_bsmod_deselectIndex bsmod_deselectIndex;
    PFN_bsmod_deselect bsmod_deselect;
    PFN_bsmod_firstSelectedId bsmod_firstSelectedId;
    PFN_bsmod_lastSelectedId bsmod_lastSelectedId;
    PFN_bsmod_removeFlexible bsmod_removeFlexible;
    PFN_bsmod_addFlexible bsmod_addFlexible;
    PFN_bsmod_readHoveringOutputs bsmod_readHoveringOutputs;
    PFN_bsmod_readHoveringInstanceData bsmod_readHoveringInstanceData;
    PFN_bsmod_readHoveringVertex bsmod_readHoveringVertex;
    PFN_bsmod_editSelectedType bsmod_editSelectedType;
    PFN_bsmod_ensureTypeVersionsAreUpToDate bsmod_ensureTypeVersionsAreUpToDate;
    PFN_bsmod_renderBillboards bsmod_renderBillboards;
    PFN_bsmod_instanceUI bsmod_instanceUI;
    PFN_bsmod_pushVecNWidget bsmod_pushVecNWidget;
    PFN_bsmod_pushInputWidget bsmod_pushInputWidget;
    PFN_bsmod_instanceTileContextMenu bsmod_instanceTileContextMenu;
    PFN_bsmod_instanceContextMenu bsmod_instanceContextMenu;
    PFN_bsmod_pushContextMenuButton bsmod_pushContextMenuButton;
    PFN_bsmod_instanceGridMenu bsmod_instanceGridMenu;
    PFN_bsmod_instanceLightBillboards bsmod_instanceLightBillboards;
    PFN_bsmod_pushMaterialWidgets bsmod_pushMaterialWidgets;
    PFN_bsmod_onDragMaterial bsmod_onDragMaterial;
    PFN_bsmod_onClickMaterialMenu bsmod_onClickMaterialMenu;
    PFN_bsmod_rasterizeMaterialIcons bsmod_rasterizeMaterialIcons;
    PFN_bsmod_pushPrefabMenuWidgets bsmod_pushPrefabMenuWidgets;
    PFN_bsmod_instancePrefabPreview bsmod_instancePrefabPreview;
    PFN_bsmod_onDragPrefab bsmod_onDragPrefab;
    PFN_bsmod_rasterizePrefabIcons bsmod_rasterizePrefabIcons;
    PFN_bsmod_instancePrimitivePreview bsmod_instancePrimitivePreview;
    PFN_bsmod_onDragPrimitive bsmod_onDragPrimitive;
    PFN_bsmod_rasterizePrimitiveIcons bsmod_rasterizePrimitiveIcons;
    PFN_bsmod_setSideMenuTab bsmod_setSideMenuTab;
    PFN_bsmod_instanceSideMenu bsmod_instanceSideMenu;
    PFN_bsmod_pushTileMenuWidgets bsmod_pushTileMenuWidgets;
    PFN_bsmod_instanceTilePreview bsmod_instanceTilePreview;
    PFN_bsmod_onDragTile bsmod_onDragTile;
} bsmod_FunctionTable;

BSMODAPI const int* _bsmod_subtypes();
BSMODAPI bsmod_Callbacks* _bsmod_callbacks();
BSMODAPI void _bsmod_copyHoveringDataToBuffer();
BSMODAPI void _bsmod_onIni();
BSMODAPI void _bsmod_onLateIni();
BSMODAPI void _bsmod_onCreateQuadSubtypes(bs_Range range);
BSMODAPI void _bsmod_onLoad();
BSMODAPI void _bsmod_bindAtlases();
BSMODAPI void _bsmod_onGfxRender();
BSMODAPI void _bsmod_onTick();
BSMODAPI void _bsmod_onMap(bsgfx_TypeId type_id, int id);
BSMODAPI void _bsmod_onTrack();
BSMODAPI bs_Result _bsmod_onPackBindings();
BSMODAPI void _bsmod_onCompileShader(bsmod_TrackParams params);
BSMODAPI void _bsmod_onConvertFont(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackAtlas(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackModels(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackBinary(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackTextureArray(bsmod_TrackParams params);
BSMODAPI bs_Result _bsmod_packFont(char* package_name, char* ttf_path, bsmod_UnicodeBlockRange blocks[], int blocks_count, int pt_sizes[], int pt_sizes_count, char* resource_name, int resource_name_length);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTexture(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* name);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureN(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* name, int name_length);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureV(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* format, va_list args);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureF(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id1, int id2, char* format,  ...);
BSMODAPI void _bsmod_destroyAtlasPacker(bsmod_AtlasPacker* packer);
BSMODAPI bs_Result _bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, int channels_count, char* package, char* resource_name, bool allow_paging);
BSMODAPI bsmod_AtlasPacker _bsmod_createAtlasPacker();
BSMODAPI bs_Result _bsmod_packImageDirectory(char* directory_name, char* package_name, char* resource_name);
BSMODAPI void _bsmod_scrollbar(const int* scroll, bsgfx_Scrollbar* out);
BSMODAPI void _bsmod_dividerWidget(float width, int indent, bsgfx_Widget* out);
BSMODAPI void _bsmod_iconWidget(const bsgfx_AtlasCache* cache, float align_height, bs_vec3 offset, bs_U32 advance_flags, bsgfx_Widget* out);
BSMODAPI bs_List* _bsmod_packages();
BSMODAPI bsmod_Package* _bsmod_queryPackage(const char* path);
BSMODAPI bsmod_Package* _bsmod_ensurePackage(const char* path);
BSMODAPI bsmod_Resource* _bsmod_queryResource(bsmod_Package* package, bs_ResourceType type, const char* name);
BSMODAPI bs_Result _bsmod_iniPackage(int package_id);
BSMODAPI bs_Result _bsmod_packResource(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* resource_name);
BSMODAPI bs_Result _bsmod_packResourceN(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* resource_name, int resource_name_length);
BSMODAPI bs_Result _bsmod_packResourceV(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* format, va_list args);
BSMODAPI bs_Result _bsmod_packResourceF(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* format,  ...);
BSMODAPI bs_Result _bsmod_savePackage(char* path);
BSMODAPI bs_Result _bsmod_savePackageN(char* path, int path_length);
BSMODAPI bs_Result _bsmod_savePackageV(char* format, va_list args);
BSMODAPI bs_Result _bsmod_savePackageF(char* format,  ...);
BSMODAPI void _bsmod_loadShaderReferences();
BSMODAPI void _bsmod_updateShaderReferences();
BSMODAPI void _bsmod_iniCompiler();
BSMODAPI bs_Result _bsmod_compileShader(char* path, char* name, char* package);
BSMODAPI void _bsmod_queueRasterize(const char* package, const char* name, bs_Callback callback);
BSMODAPI void _bsmod_pollRasterizer();
BSMODAPI void _bsmod_beginRasterize(bs_ivec2 render_size, bs_ivec2 output_size);
BSMODAPI void _bsmod_endRasterize();
BSMODAPI bs_Result _bsmod_rasterizeInstance(bs_PipelineHash pipeline_hash, int subtype, int instance_id, int category, char* name, int width, int height, size_t push_constant_size, unsigned char* push_constant);
BSMODAPI void _bsmod_instanceTransform();
BSMODAPI void _bsmod_selectHoveringTypes();
BSMODAPI bsgfx_TypeId _bsmod_queryType(const char* plural);
BSMODAPI void _bsmod_delete(bsgfx_TypeId type_id, int id);
BSMODAPI void _bsmod_deleteSelected(bsgfx_TypeId type_id);
BSMODAPI bs_Result _bsmod_saveType(bsgfx_TypeId id, char* value);
BSMODAPI bs_Result _bsmod_saveTypeN(bsgfx_TypeId id, char* value, int value_length);
BSMODAPI bs_Result _bsmod_saveTypeV(bsgfx_TypeId id, char* format, va_list args);
BSMODAPI bs_Result _bsmod_saveTypeF(bsgfx_TypeId id, char* format,  ...);
BSMODAPI void* _bsmod_add(bsgfx_TypeId id, void* data);
BSMODAPI bool _bsmod_isSelected(bs_List* list, bsgfx_TypeId type, int id);
BSMODAPI void _bsmod_select(bs_List* list, bsgfx_TypeId type, int id);
BSMODAPI void _bsmod_deselectAll();
BSMODAPI void _bsmod_deselectRange(bs_List* list, int first, int count);
BSMODAPI void _bsmod_deselectIndex(bs_List* list, int id);
BSMODAPI void _bsmod_deselect(bs_List* list, int id);
BSMODAPI int _bsmod_firstSelectedId(bs_List* list);
BSMODAPI int _bsmod_lastSelectedId(bs_List* list);
BSMODAPI void* _bsmod_removeFlexible(bsgfx_TypeId type_id, int id);
BSMODAPI void* _bsmod_addFlexible(bsgfx_TypeId type_id, int id, void* data);
BSMODAPI void _bsmod_readHoveringOutputs();
BSMODAPI void _bsmod_readHoveringInstanceData();
BSMODAPI void _bsmod_readHoveringVertex();
BSMODAPI void _bsmod_editSelectedType();
BSMODAPI void _bsmod_ensureTypeVersionsAreUpToDate(int package_id);
BSMODAPI void _bsmod_renderBillboards();
BSMODAPI void _bsmod_instanceUI();
BSMODAPI void _bsmod_pushVecNWidget(bs_List* widgets, const char* name, bs_vec3 offset, float width, float* v, int n);
BSMODAPI void _bsmod_pushInputWidget(bs_List* widgets, void* value, bs_vec3 offset, float width, int name_padding, bool skip_advance, bool is_last, bool has_buttons, const char* name);
BSMODAPI void _bsmod_instanceTileContextMenu(bs_vec3 position, bs_vec2 size);
BSMODAPI void _bsmod_instanceContextMenu(bs_List* widgets, bs_vec3 position, bs_vec2 size);
BSMODAPI void _bsmod_pushContextMenuButton(bs_List* widgets, bs_vec2 menu_size, bs_vec3 icon_offset, bsgfx_AtlasCache* icon, const char* name, int indent, PFN_bsgfx_ButtonWidgetCallback action, bool expandable);
BSMODAPI void _bsmod_instanceGridMenu(bs_vec3 position, bs_vec2 dimensions);
BSMODAPI void _bsmod_instanceLightBillboards();
BSMODAPI void _bsmod_pushMaterialWidgets(bs_List* widgets, bs_vec2 background_size);
BSMODAPI void _bsmod_onDragMaterial(bsmod_DraggingParams params);
BSMODAPI void _bsmod_onClickMaterialMenu(bsmod_GridClickParams params);
BSMODAPI void _bsmod_rasterizeMaterialIcons();
BSMODAPI void _bsmod_pushPrefabMenuWidgets(bs_List* widgets, bs_vec2 background_size);
BSMODAPI bool _bsmod_instancePrefabPreview(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering);
BSMODAPI void _bsmod_onDragPrefab(bsmod_DraggingParams params);
BSMODAPI void _bsmod_rasterizePrefabIcons();
BSMODAPI bool _bsmod_instancePrimitivePreview(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering);
BSMODAPI void _bsmod_onDragPrimitive(bsmod_DraggingParams params);
BSMODAPI void _bsmod_rasterizePrimitiveIcons();
BSMODAPI void _bsmod_setSideMenuTab(int id, bsmod_GridClickParams params);
BSMODAPI void _bsmod_instanceSideMenu(bs_vec3 position, bs_vec2 dimensions);
BSMODAPI void _bsmod_pushTileMenuWidgets(bs_List* widgets, bs_vec2 background_size);
BSMODAPI bool _bsmod_instanceTilePreview(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering);
BSMODAPI void _bsmod_onDragTile(bsmod_DraggingParams params);

static inline bsmod_FunctionTable* _bsmod_getFunctions() {
    static bsmod_FunctionTable functions;

    functions.bsmod_subtypes = _bsmod_subtypes;
    functions.bsmod_callbacks = _bsmod_callbacks;
    functions.bsmod_copyHoveringDataToBuffer = _bsmod_copyHoveringDataToBuffer;
    functions.bsmod_onIni = _bsmod_onIni;
    functions.bsmod_onLateIni = _bsmod_onLateIni;
    functions.bsmod_onCreateQuadSubtypes = _bsmod_onCreateQuadSubtypes;
    functions.bsmod_onLoad = _bsmod_onLoad;
    functions.bsmod_bindAtlases = _bsmod_bindAtlases;
    functions.bsmod_onGfxRender = _bsmod_onGfxRender;
    functions.bsmod_onTick = _bsmod_onTick;
    functions.bsmod_onMap = _bsmod_onMap;
    functions.bsmod_onTrack = _bsmod_onTrack;
    functions.bsmod_onPackBindings = _bsmod_onPackBindings;
    functions.bsmod_onCompileShader = _bsmod_onCompileShader;
    functions.bsmod_onConvertFont = _bsmod_onConvertFont;
    functions.bsmod_onPackAtlas = _bsmod_onPackAtlas;
    functions.bsmod_onPackModels = _bsmod_onPackModels;
    functions.bsmod_onPackBinary = _bsmod_onPackBinary;
    functions.bsmod_onPackTextureArray = _bsmod_onPackTextureArray;
    functions.bsmod_packFont = _bsmod_packFont;
    functions.bsmod_packAtlasTexture = _bsmod_packAtlasTexture;
    functions.bsmod_packAtlasTextureN = _bsmod_packAtlasTextureN;
    functions.bsmod_packAtlasTextureV = _bsmod_packAtlasTextureV;
    functions.bsmod_packAtlasTextureF = _bsmod_packAtlasTextureF;
    functions.bsmod_destroyAtlasPacker = _bsmod_destroyAtlasPacker;
    functions.bsmod_packAtlas = _bsmod_packAtlas;
    functions.bsmod_createAtlasPacker = _bsmod_createAtlasPacker;
    functions.bsmod_packImageDirectory = _bsmod_packImageDirectory;
    functions.bsmod_scrollbar = _bsmod_scrollbar;
    functions.bsmod_dividerWidget = _bsmod_dividerWidget;
    functions.bsmod_iconWidget = _bsmod_iconWidget;
    functions.bsmod_packages = _bsmod_packages;
    functions.bsmod_queryPackage = _bsmod_queryPackage;
    functions.bsmod_ensurePackage = _bsmod_ensurePackage;
    functions.bsmod_queryResource = _bsmod_queryResource;
    functions.bsmod_iniPackage = _bsmod_iniPackage;
    functions.bsmod_packResource = _bsmod_packResource;
    functions.bsmod_packResourceN = _bsmod_packResourceN;
    functions.bsmod_packResourceV = _bsmod_packResourceV;
    functions.bsmod_packResourceF = _bsmod_packResourceF;
    functions.bsmod_savePackage = _bsmod_savePackage;
    functions.bsmod_savePackageN = _bsmod_savePackageN;
    functions.bsmod_savePackageV = _bsmod_savePackageV;
    functions.bsmod_savePackageF = _bsmod_savePackageF;
    functions.bsmod_loadShaderReferences = _bsmod_loadShaderReferences;
    functions.bsmod_updateShaderReferences = _bsmod_updateShaderReferences;
    functions.bsmod_iniCompiler = _bsmod_iniCompiler;
    functions.bsmod_compileShader = _bsmod_compileShader;
    functions.bsmod_queueRasterize = _bsmod_queueRasterize;
    functions.bsmod_pollRasterizer = _bsmod_pollRasterizer;
    functions.bsmod_beginRasterize = _bsmod_beginRasterize;
    functions.bsmod_endRasterize = _bsmod_endRasterize;
    functions.bsmod_rasterizeInstance = _bsmod_rasterizeInstance;
    functions.bsmod_instanceTransform = _bsmod_instanceTransform;
    functions.bsmod_selectHoveringTypes = _bsmod_selectHoveringTypes;
    functions.bsmod_queryType = _bsmod_queryType;
    functions.bsmod_delete = _bsmod_delete;
    functions.bsmod_deleteSelected = _bsmod_deleteSelected;
    functions.bsmod_saveType = _bsmod_saveType;
    functions.bsmod_saveTypeN = _bsmod_saveTypeN;
    functions.bsmod_saveTypeV = _bsmod_saveTypeV;
    functions.bsmod_saveTypeF = _bsmod_saveTypeF;
    functions.bsmod_add = _bsmod_add;
    functions.bsmod_isSelected = _bsmod_isSelected;
    functions.bsmod_select = _bsmod_select;
    functions.bsmod_deselectAll = _bsmod_deselectAll;
    functions.bsmod_deselectRange = _bsmod_deselectRange;
    functions.bsmod_deselectIndex = _bsmod_deselectIndex;
    functions.bsmod_deselect = _bsmod_deselect;
    functions.bsmod_firstSelectedId = _bsmod_firstSelectedId;
    functions.bsmod_lastSelectedId = _bsmod_lastSelectedId;
    functions.bsmod_removeFlexible = _bsmod_removeFlexible;
    functions.bsmod_addFlexible = _bsmod_addFlexible;
    functions.bsmod_readHoveringOutputs = _bsmod_readHoveringOutputs;
    functions.bsmod_readHoveringInstanceData = _bsmod_readHoveringInstanceData;
    functions.bsmod_readHoveringVertex = _bsmod_readHoveringVertex;
    functions.bsmod_editSelectedType = _bsmod_editSelectedType;
    functions.bsmod_ensureTypeVersionsAreUpToDate = _bsmod_ensureTypeVersionsAreUpToDate;
    functions.bsmod_renderBillboards = _bsmod_renderBillboards;
    functions.bsmod_instanceUI = _bsmod_instanceUI;
    functions.bsmod_pushVecNWidget = _bsmod_pushVecNWidget;
    functions.bsmod_pushInputWidget = _bsmod_pushInputWidget;
    functions.bsmod_instanceTileContextMenu = _bsmod_instanceTileContextMenu;
    functions.bsmod_instanceContextMenu = _bsmod_instanceContextMenu;
    functions.bsmod_pushContextMenuButton = _bsmod_pushContextMenuButton;
    functions.bsmod_instanceGridMenu = _bsmod_instanceGridMenu;
    functions.bsmod_instanceLightBillboards = _bsmod_instanceLightBillboards;
    functions.bsmod_pushMaterialWidgets = _bsmod_pushMaterialWidgets;
    functions.bsmod_onDragMaterial = _bsmod_onDragMaterial;
    functions.bsmod_onClickMaterialMenu = _bsmod_onClickMaterialMenu;
    functions.bsmod_rasterizeMaterialIcons = _bsmod_rasterizeMaterialIcons;
    functions.bsmod_pushPrefabMenuWidgets = _bsmod_pushPrefabMenuWidgets;
    functions.bsmod_instancePrefabPreview = _bsmod_instancePrefabPreview;
    functions.bsmod_onDragPrefab = _bsmod_onDragPrefab;
    functions.bsmod_rasterizePrefabIcons = _bsmod_rasterizePrefabIcons;
    functions.bsmod_instancePrimitivePreview = _bsmod_instancePrimitivePreview;
    functions.bsmod_onDragPrimitive = _bsmod_onDragPrimitive;
    functions.bsmod_rasterizePrimitiveIcons = _bsmod_rasterizePrimitiveIcons;
    functions.bsmod_setSideMenuTab = _bsmod_setSideMenuTab;
    functions.bsmod_instanceSideMenu = _bsmod_instanceSideMenu;
    functions.bsmod_pushTileMenuWidgets = _bsmod_pushTileMenuWidgets;
    functions.bsmod_instanceTilePreview = _bsmod_instanceTilePreview;
    functions.bsmod_onDragTile = _bsmod_onDragTile;

    return &functions;
}

#endif
