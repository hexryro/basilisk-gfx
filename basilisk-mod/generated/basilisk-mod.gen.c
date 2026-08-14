
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
        
#include <basilisk-mod.h>
#include <bsmod_internal.gen.h>
#include <bsmod_prevalidation.gen.h>
#include <bsmod_validation.gen.h>
#include <math.h>
#include <stdio.h>

static bsmod_FunctionTable next = { 0 };

const bsmod_FunctionTable* _bsmod_setFunctions(const bsmod_FunctionTable* a, bsmod_FunctionTable* b) {
    memcpy(&next, a, sizeof(next));

	if (!b) return &next;

    for (size_t offset = 0; offset < sizeof(bsmod_FunctionTable); offset += sizeof(void*)) {
        bs_Callback* f_a = ((unsigned char*)&next) + offset;
        bs_Callback* f_b = ((unsigned char*)b) + offset;
        if (!*f_a) 
            *f_a = *f_b;
    }

    return &next;
}

void bsmod_enableValidation()
{
    bsmod_FunctionTable* definitions = _bsmod_getFunctions();
    bsmod_FunctionTable* preval_definitions = _preval_bsmod_getFunctions();
    bsmod_FunctionTable* val_definitions = _val_bsmod_getFunctions();
    val_definitions = _preval_bsmod_setFunctions(val_definitions, definitions);
    preval_definitions = _bsmod_setFunctions(preval_definitions, val_definitions);
}

void bsmod_disableValidation()
{
    bsmod_FunctionTable* definitions = _bsmod_getFunctions();
    _bsmod_setFunctions(definitions, NULL);
}

const int* bsmod_subtypes()
{
    return next.bsmod_subtypes();
}

bsmod_Callbacks* bsmod_callbacks()
{
    return next.bsmod_callbacks();
}

void bsmod_copyHoveringDataToBuffer()
{
    next.bsmod_copyHoveringDataToBuffer();
}

bs_Queue* bsmod_onQueue()
{
    return next.bsmod_onQueue();
}

void bsmod_onIni()
{
    next.bsmod_onIni();
}

void bsmod_onLateIni()
{
    next.bsmod_onLateIni();
}

void bsmod_onCreateQuadSubtypes(
    bs_Range range)
{
    next.bsmod_onCreateQuadSubtypes(range);
}

void bsmod_onLoad()
{
    next.bsmod_onLoad();
}

void bsmod_bindAtlases()
{
    next.bsmod_bindAtlases();
}

void bsmod_onGfxRender()
{
    next.bsmod_onGfxRender();
}

void bsmod_onTick()
{
    next.bsmod_onTick();
}

void bsmod_onMap(
    bsgfx_TypeId type_id, 
    int id)
{
    next.bsmod_onMap(type_id, id);
}

void bsmod_beginTrackChanges()
{
    next.bsmod_beginTrackChanges();
}

void bsmod_tickTracker()
{
    next.bsmod_tickTracker();
}

void bsmod_onTrack()
{
    next.bsmod_onTrack();
}

bs_Result bsmod_onPackBindings()
{
    return next.bsmod_onPackBindings();
}

void bsmod_onCompileShader(
    bsmod_TrackParams params)
{
    next.bsmod_onCompileShader(params);
}

void bsmod_onConvertFont(
    bsmod_TrackParams params)
{
    next.bsmod_onConvertFont(params);
}

void bsmod_onPackAtlas(
    bsmod_TrackParams params)
{
    next.bsmod_onPackAtlas(params);
}

void bsmod_onPackModels(
    bsmod_TrackParams params)
{
    next.bsmod_onPackModels(params);
}

void bsmod_onPackBinary(
    bsmod_TrackParams params)
{
    next.bsmod_onPackBinary(params);
}

void bsmod_onPackTextureArray(
    bsmod_TrackParams params)
{
    next.bsmod_onPackTextureArray(params);
}

bs_Result bsmod_packFont(
    char* package_name, 
    char* ttf_path, 
    bsmod_UnicodeBlockRange blocks[], 
    int blocks_count, 
    int pt_sizes[], 
    int pt_sizes_count, 
    char* resource_name, 
    int resource_name_length)
{
    return next.bsmod_packFont(package_name, ttf_path, blocks, blocks_count, pt_sizes, pt_sizes_count, resource_name, resource_name_length);
}

bsmod_TextureInfo* bsmod_packAtlasTexture(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    char* name)
{
    return next.bsmod_packAtlasTexture(packer, data, get_data, param, width, height, category, name);
}

bsmod_TextureInfo* bsmod_packAtlasTextureN(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    char* name, 
    int name_length)
{
    return next.bsmod_packAtlasTextureN(packer, data, get_data, param, width, height, category, name, name_length);
}

bsmod_TextureInfo* bsmod_packAtlasTextureV(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    char* format, 
    va_list args)
{
    return next.bsmod_packAtlasTextureV(packer, data, get_data, param, width, height, category, format, args);
}

bsmod_TextureInfo* bsmod_packAtlasTextureF(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bsmod_TextureInfo* _return = next.bsmod_packAtlasTextureV(packer, data, get_data, param, width, height, category, format, args);
    va_end(args);
    return _return;
}

void bsmod_destroyAtlasPacker(
    bsmod_AtlasPacker* packer)
{
    next.bsmod_destroyAtlasPacker(packer);
}

bs_Result bsmod_packAtlas(
    bsmod_AtlasPacker* packer, 
    int width, 
    int height, 
    int channels_count, 
    char* package, 
    char* resource_name, 
    bool allow_paging)
{
    return next.bsmod_packAtlas(packer, width, height, channels_count, package, resource_name, allow_paging);
}

bsmod_AtlasPacker bsmod_createAtlasPacker()
{
    return next.bsmod_createAtlasPacker();
}

bs_Result bsmod_packImageDirectory(
    char* directory_name, 
    char* package_name, 
    char* resource_name)
{
    return next.bsmod_packImageDirectory(directory_name, package_name, resource_name);
}

void bsmod_scrollbar(
    const int* scroll, 
    bsgfx_Scrollbar* out)
{
    next.bsmod_scrollbar(scroll, out);
}

void bsmod_dividerWidget(
    float width, 
    int indent, 
    bsgfx_Widget* out)
{
    next.bsmod_dividerWidget(width, indent, out);
}

void bsmod_iconWidget(
    const bsgfx_AtlasCache* cache, 
    float align_height, 
    bs_vec3 offset, 
    bs_U32 advance_flags, 
    bsgfx_Widget* out)
{
    next.bsmod_iconWidget(cache, align_height, offset, advance_flags, out);
}

bs_List* bsmod_packages()
{
    return next.bsmod_packages();
}

bsmod_Package* bsmod_queryPackage(
    const char* path)
{
    return next.bsmod_queryPackage(path);
}

bsmod_Package* bsmod_ensurePackage(
    const char* path)
{
    return next.bsmod_ensurePackage(path);
}

bsmod_Resource* bsmod_queryResource(
    bsmod_Package* package, 
    bs_ResourceType type, 
    const char* name)
{
    return next.bsmod_queryResource(package, type, name);
}

bs_Result bsmod_iniPackage(
    int package_id)
{
    return next.bsmod_iniPackage(package_id);
}

bs_Result bsmod_packResource(
    bs_ResourceType type, 
    unsigned char* data, 
    size_t data_size, 
    const char* package_name, 
    char* resource_name)
{
    return next.bsmod_packResource(type, data, data_size, package_name, resource_name);
}

bs_Result bsmod_packResourceN(
    bs_ResourceType type, 
    unsigned char* data, 
    size_t data_size, 
    const char* package_name, 
    char* resource_name, 
    int resource_name_length)
{
    return next.bsmod_packResourceN(type, data, data_size, package_name, resource_name, resource_name_length);
}

bs_Result bsmod_packResourceV(
    bs_ResourceType type, 
    unsigned char* data, 
    size_t data_size, 
    const char* package_name, 
    char* format, 
    va_list args)
{
    return next.bsmod_packResourceV(type, data, data_size, package_name, format, args);
}

bs_Result bsmod_packResourceF(
    bs_ResourceType type, 
    unsigned char* data, 
    size_t data_size, 
    const char* package_name, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = next.bsmod_packResourceV(type, data, data_size, package_name, format, args);
    va_end(args);
    return _return;
}

bs_Result bsmod_savePackage(
    char* path)
{
    return next.bsmod_savePackage(path);
}

bs_Result bsmod_savePackageN(
    char* path, 
    int path_length)
{
    return next.bsmod_savePackageN(path, path_length);
}

bs_Result bsmod_savePackageV(
    char* format, 
    va_list args)
{
    return next.bsmod_savePackageV(format, args);
}

bs_Result bsmod_savePackageF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = next.bsmod_savePackageV(format, args);
    va_end(args);
    return _return;
}

void bsmod_loadShaderReferences()
{
    next.bsmod_loadShaderReferences();
}

void bsmod_updateShaderReferences()
{
    next.bsmod_updateShaderReferences();
}

void bsmod_iniCompiler()
{
    next.bsmod_iniCompiler();
}

bs_Result bsmod_compileShader(
    char* path, 
    char* name, 
    char* package)
{
    return next.bsmod_compileShader(path, name, package);
}

void bsmod_queueRasterize(
    const char* package, 
    const char* name, 
    bs_Callback callback)
{
    next.bsmod_queueRasterize(package, name, callback);
}

void bsmod_pollRasterizer()
{
    next.bsmod_pollRasterizer();
}

void bsmod_beginRasterize(
    bs_ivec2 render_size, 
    bs_ivec2 output_size)
{
    next.bsmod_beginRasterize(render_size, output_size);
}

void bsmod_endRasterize(
    bs_Queue* queue)
{
    next.bsmod_endRasterize(queue);
}

bs_Result bsmod_rasterizeInstance(
    bs_Queue* queue, 
    bs_PipelineHash pipeline_hash, 
    int subtype, 
    int instance_id, 
    int category, 
    char* name, 
    int width, 
    int height, 
    size_t push_constant_size, 
    unsigned char* push_constant)
{
    return next.bsmod_rasterizeInstance(queue, pipeline_hash, subtype, instance_id, category, name, width, height, push_constant_size, push_constant);
}

void bsmod_instanceTransform()
{
    next.bsmod_instanceTransform();
}

void bsmod_selectHoveringTypes()
{
    next.bsmod_selectHoveringTypes();
}

bsgfx_TypeId bsmod_queryType(
    const char* plural)
{
    return next.bsmod_queryType(plural);
}

void bsmod_delete(
    bsgfx_TypeId type_id, 
    int id)
{
    next.bsmod_delete(type_id, id);
}

void bsmod_deleteSelected(
    bsgfx_TypeId type_id)
{
    next.bsmod_deleteSelected(type_id);
}

bs_Result bsmod_saveType(
    bsgfx_TypeId id, 
    char* value)
{
    return next.bsmod_saveType(id, value);
}

bs_Result bsmod_saveTypeN(
    bsgfx_TypeId id, 
    char* value, 
    int value_length)
{
    return next.bsmod_saveTypeN(id, value, value_length);
}

bs_Result bsmod_saveTypeV(
    bsgfx_TypeId id, 
    char* format, 
    va_list args)
{
    return next.bsmod_saveTypeV(id, format, args);
}

bs_Result bsmod_saveTypeF(
    bsgfx_TypeId id, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = next.bsmod_saveTypeV(id, format, args);
    va_end(args);
    return _return;
}

void* bsmod_add(
    bsgfx_TypeId id, 
    void* data)
{
    return next.bsmod_add(id, data);
}

bool bsmod_isSelected(
    bs_List* list, 
    bsgfx_TypeId type, 
    int id)
{
    return next.bsmod_isSelected(list, type, id);
}

void bsmod_select(
    bs_List* list, 
    bsgfx_TypeId type, 
    int id)
{
    next.bsmod_select(list, type, id);
}

void bsmod_deselectAll()
{
    next.bsmod_deselectAll();
}

void bsmod_deselectRange(
    bs_List* list, 
    int first, 
    int count)
{
    next.bsmod_deselectRange(list, first, count);
}

void bsmod_deselectIndex(
    bs_List* list, 
    int id)
{
    next.bsmod_deselectIndex(list, id);
}

void bsmod_deselect(
    bs_List* list, 
    int id)
{
    next.bsmod_deselect(list, id);
}

int bsmod_firstSelectedId(
    bs_List* list)
{
    return next.bsmod_firstSelectedId(list);
}

int bsmod_lastSelectedId(
    bs_List* list)
{
    return next.bsmod_lastSelectedId(list);
}

void* bsmod_removeFlexible(
    bsgfx_TypeId type_id, 
    int id)
{
    return next.bsmod_removeFlexible(type_id, id);
}

void* bsmod_addFlexible(
    bsgfx_TypeId type_id, 
    int id, 
    void* data)
{
    return next.bsmod_addFlexible(type_id, id, data);
}

void bsmod_readHoveringOutputs()
{
    next.bsmod_readHoveringOutputs();
}

void bsmod_readHoveringInstanceData()
{
    next.bsmod_readHoveringInstanceData();
}

void bsmod_readHoveringVertex()
{
    next.bsmod_readHoveringVertex();
}

void bsmod_editSelectedType()
{
    next.bsmod_editSelectedType();
}

void bsmod_ensureTypeVersionsAreUpToDate(
    int package_id)
{
    next.bsmod_ensureTypeVersionsAreUpToDate(package_id);
}

void bsmod_renderBillboards()
{
    next.bsmod_renderBillboards();
}

void bsmod_instanceUI()
{
    next.bsmod_instanceUI();
}

void bsmod_pushVecNWidget(
    bs_List* widgets, 
    const char* name, 
    bs_vec3 offset, 
    float width, 
    float* v, 
    int n)
{
    next.bsmod_pushVecNWidget(widgets, name, offset, width, v, n);
}

void bsmod_pushInputWidget(
    bs_List* widgets, 
    void* value, 
    bs_vec3 offset, 
    float width, 
    int name_padding, 
    bool skip_advance, 
    bool is_last, 
    bool has_buttons, 
    const char* name)
{
    next.bsmod_pushInputWidget(widgets, value, offset, width, name_padding, skip_advance, is_last, has_buttons, name);
}

void bsmod_instanceTileContextMenu(
    bs_vec3 position, 
    bs_vec2 size)
{
    next.bsmod_instanceTileContextMenu(position, size);
}

void bsmod_instanceContextMenu(
    bs_List* widgets, 
    bs_vec3 position, 
    bs_vec2 size)
{
    next.bsmod_instanceContextMenu(widgets, position, size);
}

void bsmod_pushContextMenuButton(
    bs_List* widgets, 
    bs_vec2 menu_size, 
    bs_vec3 icon_offset, 
    bsgfx_AtlasCache* icon, 
    const char* name, 
    int indent, 
    PFN_bsgfx_ButtonWidgetCallback action, 
    bool expandable)
{
    next.bsmod_pushContextMenuButton(widgets, menu_size, icon_offset, icon, name, indent, action, expandable);
}

void bsmod_instanceGridMenu(
    bs_vec3 position, 
    bs_vec2 dimensions)
{
    next.bsmod_instanceGridMenu(position, dimensions);
}

void bsmod_instanceLightBillboards()
{
    next.bsmod_instanceLightBillboards();
}

void bsmod_pushMaterialWidgets(
    bs_List* widgets, 
    bs_vec2 background_size)
{
    next.bsmod_pushMaterialWidgets(widgets, background_size);
}

void bsmod_onDragMaterial(
    bsmod_DraggingParams params)
{
    next.bsmod_onDragMaterial(params);
}

void bsmod_onClickMaterialMenu(
    bsmod_GridClickParams params)
{
    next.bsmod_onClickMaterialMenu(params);
}

void bsmod_rasterizeMaterialIcons()
{
    next.bsmod_rasterizeMaterialIcons();
}

void bsmod_pushPrefabMenuWidgets(
    bs_List* widgets, 
    bs_vec2 background_size)
{
    next.bsmod_pushPrefabMenuWidgets(widgets, background_size);
}

bool bsmod_instancePrefabPreview(
    bsgfx_Widget* widget, 
    bs_vec2* position, 
    int id, 
    bool hovering)
{
    return next.bsmod_instancePrefabPreview(widget, position, id, hovering);
}

void bsmod_onDragPrefab(
    bsmod_DraggingParams params)
{
    next.bsmod_onDragPrefab(params);
}

void bsmod_rasterizePrefabIcons()
{
    next.bsmod_rasterizePrefabIcons();
}

bool bsmod_instancePrimitivePreview(
    bsgfx_Widget* widget, 
    bs_vec2* position, 
    int id, 
    bool hovering)
{
    return next.bsmod_instancePrimitivePreview(widget, position, id, hovering);
}

void bsmod_onDragPrimitive(
    bsmod_DraggingParams params)
{
    next.bsmod_onDragPrimitive(params);
}

void bsmod_rasterizePrimitiveIcons()
{
    next.bsmod_rasterizePrimitiveIcons();
}

void bsmod_setSideMenuTab(
    int id, 
    bsmod_GridClickParams params)
{
    next.bsmod_setSideMenuTab(id, params);
}

void bsmod_instanceSideMenu(
    bs_vec3 position, 
    bs_vec2 dimensions)
{
    next.bsmod_instanceSideMenu(position, dimensions);
}

void bsmod_pushTileMenuWidgets(
    bs_List* widgets, 
    bs_vec2 background_size)
{
    next.bsmod_pushTileMenuWidgets(widgets, background_size);
}

bool bsmod_instanceTilePreview(
    bsgfx_Widget* widget, 
    bs_vec2* position, 
    int id, 
    bool hovering)
{
    return next.bsmod_instanceTilePreview(widget, position, id, hovering);
}

void bsmod_onDragTile(
    bsmod_DraggingParams params)
{
    next.bsmod_onDragTile(params);
}

