
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
#ifdef _WIN32
#include <windows.h>
#endif


typedef bsgfx_InstanceSubtype**(* PFN_bsmod_subtypes)();
typedef bsmod_Callbacks*(* PFN_bsmod_callbacks)();
typedef void(* PFN_bsmod_copyHoveringDataToBuffer)();
typedef bs_Queue*(* PFN_bsmod_onQueue)();
typedef void(* PFN_bsmod_onIni)();
typedef void(* PFN_bsmod_onLateIni)();
typedef void(* PFN_bsmod_onCreateQuadSubtypes)(bs_Range range);
typedef void(* PFN_bsmod_onLoad)();
typedef void(* PFN_bsmod_bindAtlases)();
typedef void(* PFN_bsmod_onGfxRender)();
typedef void(* PFN_bsmod_onTick)();
typedef void(* PFN_bsmod_onMap)(bsgfx_TypeId type_id, int id);
typedef void(* PFN_bsmod_beginTrackChanges)();
typedef void(* PFN_bsmod_tickTracker)();
typedef void(* PFN_bsmod_onTrack)();
typedef void(* PFN_bsmod_onCompileShader)(bsmod_TrackParams params);
typedef void(* PFN_bsmod_onConvertFont)(bsmod_TrackParams params);
typedef void(* PFN_bsmod_onPackAtlas)(bsmod_TrackParams params);
typedef void(* PFN_bsmod_onPackModels)(bsmod_TrackParams params);
typedef void(* PFN_bsmod_onPackBinary)(bsmod_TrackParams params);
typedef void(* PFN_bsmod_onPackTextureArray)(bsmod_TrackParams params);
typedef bs_Result(* PFN_bsmod_packFont)(bsmod_RenderMode render_mode, char* package_name, char* ttf_path, bsmod_UnicodeBlockRange blocks[], int blocks_count, int pt_sizes[], int pt_sizes_count, char* resource_name, int resource_name_length);
typedef bsmod_TextureInfo*(* PFN_bsmod_packAtlasTexture)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* name);
typedef bsmod_TextureInfo*(* PFN_bsmod_packAtlasTextureN)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* name, int name_length);
typedef bsmod_TextureInfo*(* PFN_bsmod_packAtlasTextureV)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* format, va_list args);
typedef bsmod_TextureInfo*(* PFN_bsmod_packAtlasTextureF)(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* format, ...);
typedef void(* PFN_bsmod_destroyAtlasPacker)(bsmod_AtlasPacker* packer);
typedef bs_Result(* PFN_bsmod_packAtlas)(bsmod_AtlasPacker* packer, int width, int height, int channels_count, char* package, char* resource_name, bool allow_paging);
typedef bsmod_AtlasPacker(* PFN_bsmod_createAtlasPacker)();
typedef bs_Result(* PFN_bsmod_packImageDirectory)(char* directory_name, char* package_name, char* resource_name);
typedef bs_List*(* PFN_bsmod_packages)();
typedef bsmod_Package*(* PFN_bsmod_queryPackage)(const char* path);
typedef bsmod_Package*(* PFN_bsmod_ensurePackage)(const char* path);
typedef bsmod_Resource*(* PFN_bsmod_queryResource)(bsmod_Package* package, bs_ResourceType type, const char* name);
typedef bs_Result(* PFN_bsmod_loadResource)(int type, int package_id, char* name);
typedef bs_Result(* PFN_bsmod_iniPackage)(int package_id);
typedef bs_Result(* PFN_bsmod_packResource)(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* resource_name);
typedef bs_Result(* PFN_bsmod_packResourceN)(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* resource_name, int resource_name_length);
typedef bs_Result(* PFN_bsmod_packResourceV)(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* format, va_list args);
typedef bs_Result(* PFN_bsmod_packResourceF)(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* format, ...);
typedef bs_Result(* PFN_bsmod_savePackage)(char* path);
typedef bs_Result(* PFN_bsmod_savePackageN)(char* path, int path_length);
typedef bs_Result(* PFN_bsmod_savePackageV)(char* format, va_list args);
typedef bs_Result(* PFN_bsmod_savePackageF)(char* format, ...);
typedef void(* PFN_bsmod_loadShaderReferences)();
typedef void(* PFN_bsmod_updateShaderReferences)();
typedef void(* PFN_bsmod_iniCompiler)();
typedef bs_Result(* PFN_bsmod_compileShader)(char* path, char* name, char* package);
typedef void(* PFN_bsmod_queueRasterize)(const char* package, const char* name, bs_Callback callback);
typedef void(* PFN_bsmod_pollRasterizer)();
typedef void(* PFN_bsmod_beginRasterize)(bs_ivec2 render_size, bs_ivec2 output_size);
typedef void(* PFN_bsmod_endRasterize)(bs_Queue* queue);
typedef bs_Result(* PFN_bsmod_rasterizeInstance)(bs_Queue* queue, bs_PipelineHash pipeline_hash, bsgfx_InstanceSubtype* subtype, int instance_offset, int instance_count, int category, char* name, int width, int height, size_t push_constant_size, void* push_constant);
typedef void(* PFN_bsmod_instanceTransform)();
typedef void(* PFN_bsmod_selectHoveringTypes)();
typedef bsgfx_TypeId(* PFN_bsmod_queryType)(const char* plural);
typedef void(* PFN_bsmod_delete)(bsgfx_TypeId type_id, int id);
typedef void(* PFN_bsmod_deleteSelected)(bsgfx_TypeId type_id);
typedef bs_Result(* PFN_bsmod_saveType)(bsgfx_TypeId id, char* value);
typedef bs_Result(* PFN_bsmod_saveTypeN)(bsgfx_TypeId id, char* value, int value_length);
typedef bs_Result(* PFN_bsmod_saveTypeV)(bsgfx_TypeId id, char* format, va_list args);
typedef bs_Result(* PFN_bsmod_saveTypeF)(bsgfx_TypeId id, char* format, ...);
typedef void*(* PFN_bsmod_add)(bsgfx_TypeId id, void* data);
typedef bool(* PFN_bsmod_isSelected)(bs_List* list, bsgfx_TypeId type, int id);
typedef void(* PFN_bsmod_select)(bs_List* list, bsgfx_TypeId type, int id);
typedef void(* PFN_bsmod_deselectAll)();
typedef void(* PFN_bsmod_deselectRange)(bs_List* list, int first, int count);
typedef void(* PFN_bsmod_deselectIndex)(bs_List* list, int id);
typedef void(* PFN_bsmod_deselect)(bs_List* list, int id);
typedef int(* PFN_bsmod_firstSelectedId)(bs_List* list);
typedef int(* PFN_bsmod_lastSelectedId)(bs_List* list);
typedef void*(* PFN_bsmod_removeFlexible)(bsgfx_TypeId type_id, int id);
typedef void*(* PFN_bsmod_addFlexible)(bsgfx_TypeId type_id, int id, void* data);
typedef void(* PFN_bsmod_readHoveringOutputs)();
typedef void(* PFN_bsmod_readHoveringInstanceData)();
typedef void(* PFN_bsmod_readHoveringVertex)();
typedef void(* PFN_bsmod_editSelectedType)();
typedef void(* PFN_bsmod_ensureTypeVersionsAreUpToDate)(int package_id);

typedef struct {
    PFN_bsmod_subtypes bsmod_subtypes;
    PFN_bsmod_callbacks bsmod_callbacks;
    PFN_bsmod_copyHoveringDataToBuffer bsmod_copyHoveringDataToBuffer;
    PFN_bsmod_onQueue bsmod_onQueue;
    PFN_bsmod_onIni bsmod_onIni;
    PFN_bsmod_onLateIni bsmod_onLateIni;
    PFN_bsmod_onCreateQuadSubtypes bsmod_onCreateQuadSubtypes;
    PFN_bsmod_onLoad bsmod_onLoad;
    PFN_bsmod_bindAtlases bsmod_bindAtlases;
    PFN_bsmod_onGfxRender bsmod_onGfxRender;
    PFN_bsmod_onTick bsmod_onTick;
    PFN_bsmod_onMap bsmod_onMap;
    PFN_bsmod_beginTrackChanges bsmod_beginTrackChanges;
    PFN_bsmod_tickTracker bsmod_tickTracker;
    PFN_bsmod_onTrack bsmod_onTrack;
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
    PFN_bsmod_packages bsmod_packages;
    PFN_bsmod_queryPackage bsmod_queryPackage;
    PFN_bsmod_ensurePackage bsmod_ensurePackage;
    PFN_bsmod_queryResource bsmod_queryResource;
    PFN_bsmod_loadResource bsmod_loadResource;
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
} bsmod_FunctionTable;

BSMODAPI bsgfx_InstanceSubtype** _bsmod_subtypes();
BSMODAPI bsmod_Callbacks* _bsmod_callbacks();
BSMODAPI void _bsmod_copyHoveringDataToBuffer();
BSMODAPI bs_Queue* _bsmod_onQueue();
BSMODAPI void _bsmod_onIni();
BSMODAPI void _bsmod_onLateIni();
BSMODAPI void _bsmod_onCreateQuadSubtypes(bs_Range range);
BSMODAPI void _bsmod_onLoad();
BSMODAPI void _bsmod_bindAtlases();
BSMODAPI void _bsmod_onGfxRender();
BSMODAPI void _bsmod_onTick();
BSMODAPI void _bsmod_onMap(bsgfx_TypeId type_id, int id);
BSMODAPI void _bsmod_beginTrackChanges();
BSMODAPI void _bsmod_tickTracker();
BSMODAPI void _bsmod_onTrack();
BSMODAPI void _bsmod_onCompileShader(bsmod_TrackParams params);
BSMODAPI void _bsmod_onConvertFont(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackAtlas(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackModels(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackBinary(bsmod_TrackParams params);
BSMODAPI void _bsmod_onPackTextureArray(bsmod_TrackParams params);
BSMODAPI bs_Result _bsmod_packFont(bsmod_RenderMode render_mode, char* package_name, char* ttf_path, bsmod_UnicodeBlockRange blocks[], int blocks_count, int pt_sizes[], int pt_sizes_count, char* resource_name, int resource_name_length);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTexture(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* name);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureN(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* name, int name_length);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureV(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* format, va_list args);
BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureF(bsmod_AtlasPacker* packer, unsigned char* data, PFN_bsmod_getAtlasTextureData get_data, void* param, int width, int height, int category, int id, char* format,  ...);
BSMODAPI void _bsmod_destroyAtlasPacker(bsmod_AtlasPacker* packer);
BSMODAPI bs_Result _bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, int channels_count, char* package, char* resource_name, bool allow_paging);
BSMODAPI bsmod_AtlasPacker _bsmod_createAtlasPacker();
BSMODAPI bs_Result _bsmod_packImageDirectory(char* directory_name, char* package_name, char* resource_name);
BSMODAPI bs_List* _bsmod_packages();
BSMODAPI bsmod_Package* _bsmod_queryPackage(const char* path);
BSMODAPI bsmod_Package* _bsmod_ensurePackage(const char* path);
BSMODAPI bsmod_Resource* _bsmod_queryResource(bsmod_Package* package, bs_ResourceType type, const char* name);
BSMODAPI bs_Result _bsmod_loadResource(int type, int package_id, char* name);
BSMODAPI bs_Result _bsmod_iniPackage(int package_id);
BSMODAPI bs_Result _bsmod_packResource(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* resource_name);
BSMODAPI bs_Result _bsmod_packResourceN(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* resource_name, int resource_name_length);
BSMODAPI bs_Result _bsmod_packResourceV(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* format, va_list args);
BSMODAPI bs_Result _bsmod_packResourceF(bs_ResourceType type, void* data, size_t data_size, const char* package_name, char* format,  ...);
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
BSMODAPI void _bsmod_endRasterize(bs_Queue* queue);
BSMODAPI bs_Result _bsmod_rasterizeInstance(bs_Queue* queue, bs_PipelineHash pipeline_hash, bsgfx_InstanceSubtype* subtype, int instance_offset, int instance_count, int category, char* name, int width, int height, size_t push_constant_size, void* push_constant);
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

static inline bsmod_FunctionTable* _bsmod_getFunctions() {
    static bsmod_FunctionTable functions;

    functions.bsmod_subtypes = _bsmod_subtypes;
    functions.bsmod_callbacks = _bsmod_callbacks;
    functions.bsmod_copyHoveringDataToBuffer = _bsmod_copyHoveringDataToBuffer;
    functions.bsmod_onQueue = _bsmod_onQueue;
    functions.bsmod_onIni = _bsmod_onIni;
    functions.bsmod_onLateIni = _bsmod_onLateIni;
    functions.bsmod_onCreateQuadSubtypes = _bsmod_onCreateQuadSubtypes;
    functions.bsmod_onLoad = _bsmod_onLoad;
    functions.bsmod_bindAtlases = _bsmod_bindAtlases;
    functions.bsmod_onGfxRender = _bsmod_onGfxRender;
    functions.bsmod_onTick = _bsmod_onTick;
    functions.bsmod_onMap = _bsmod_onMap;
    functions.bsmod_beginTrackChanges = _bsmod_beginTrackChanges;
    functions.bsmod_tickTracker = _bsmod_tickTracker;
    functions.bsmod_onTrack = _bsmod_onTrack;
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
    functions.bsmod_packages = _bsmod_packages;
    functions.bsmod_queryPackage = _bsmod_queryPackage;
    functions.bsmod_ensurePackage = _bsmod_ensurePackage;
    functions.bsmod_queryResource = _bsmod_queryResource;
    functions.bsmod_loadResource = _bsmod_loadResource;
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

    return &functions;
}

#endif
