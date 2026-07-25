
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
        

#ifndef BASILISK_MOD_GEN_H
#define BASILISK_MOD_GEN_H

#include <basilisk-core.h>
#include <basilisk-gfx.h>

typedef struct bsmod_Callbacks bsmod_Callbacks;
typedef struct bsmod_TrackParams bsmod_TrackParams;
typedef struct bsmod_QueueLoad bsmod_QueueLoad;
typedef struct bsmod_AtlasPacker bsmod_AtlasPacker;
typedef struct bsmod_TextureInfo bsmod_TextureInfo;
typedef struct bsmod_Chunk bsmod_Chunk;
typedef struct bsmod_Package bsmod_Package;
typedef struct bsmod_Resource bsmod_Resource;
typedef struct bsmod_DraggingParams bsmod_DraggingParams;
typedef struct bsmod_GridClickParams bsmod_GridClickParams;
typedef struct bsmod_SideMenuTab bsmod_SideMenuTab;

typedef enum bsmod_EditType bsmod_EditType;
typedef enum bsmod_DraggingType bsmod_DraggingType;
typedef enum bsmod_SideMenuTabId bsmod_SideMenuTabId;

#define BSMODAPI                                                     \
    _declspec(dllexport)

#define BSMOD_CONTENT_PATH                                           \
    "content/bsmod"

#define BSMOD_CONFIG_PATH                                            \
    "project/bsmod_config.json"

enum {                                                               \
    BSMOD_SUBTYPE_MATERIAL_ICON,                                     \
    BSMOD_SUBTYPE_PRIMITIVE_ICON,                                    \
    BSMOD_SUBTYPE_PREFAB_ICON,                                       \
    BSMOD_SUBTYPE_TILE_ICON,                                         \
    BSMOD_SUBTYPE_SPHERE_HIGH_QUALITY,                               \
    BSMOD_SUBTYPE_FONT_CONSOLAS,                                     \
    BSMOD_SUBTYPE_BILLBOARD,                                         \
    BSMOD_SUBTYPE_COUNT,                                             \
    };

#define BSMOD_FOREACH_PROC(X)                                        \
    X(PFN_void, >_loadFonts)

#define BSMOD_STRUCT_GEN(TYPE, FUNC, ...)                            \
    TYPE FUNC;

#define BSMOD_COUNT_GEN(TYPE, FUNC, ...)                             \
    +1

#define BSMOD_BPAK_CHUNK_SIZE                                        \
    100'000'000

#define BSMOD_DEFAULT_RADIUS                                         \
    5.0

#define BSMOD_TAB_BAR_HEIGHT                                         \
    20.0

#define BSMOD_GRID_SIDE_MENU_SPACE                                   \
    16.0

#define BSGFX_SIDE_MENU_WIDTH                                        \
    400

#define BSMOD_INPUT_HEIGHT                                           \
    16

#define BSMOD_UI_BASE_TEXT_MATERIAL                                  \
    $bsmod_grey_230

#define BSMOD_CONTEXT_MENU_BUTTON_HEIGHT                             \
    20

#define BSMOD_CONTEXT_MENU_PADDING                                   \
    4

#define BSMOD_HOOKS_PATH                                             \
    "project/bsmod_hooks.json"

#define BSMOD_IDS                                                    \
    &_bsmod_.selected_ids

#define BSMOD_TILE_IDS                                               \
    &_bsmod_.selected_tiles

typedef void (__stdcall* PFN_void)();
typedef const char* (__stdcall* PFN_bsmod_GridMenu)(bs_List* widgets);
typedef void (__stdcall* PFN_bsmod_GridMenuCallback)(struct bsgfx_DebugMenuWidget*, int);
enum bsmod_EditType {
    BSMOD_EDIT_UNDEFINED,
    BSMOD_EDIT_POSITION,
    BSMOD_EDIT_ROTATION,
    BSMOD_EDIT_SCALE,
};

enum bsmod_DraggingType {
    BSMOD_DRAGGING_UNDEFINED,
    BSMOD_DRAGGING_TILE,
    BSMOD_DRAGGING_ATLAS,
    BSMOD_DRAGGING_TEXTURE,
    BSMOD_DRAGGING_PREFAB,
    BSMOD_DRAGGING_MATERIAL,
    BSMOD_DRAGGING_PRIMITIVE,
    BSMOD_DRAGGING_ITEM,
};

enum bsmod_SideMenuTabId {
    BSMOD_TAB_INSTANCE,
    BSMOD_TAB_MATERIAL,
    BSMOD_TAB_SETTINGS,
    BSMOD_TABS_COUNT,
};

struct bsmod_Callbacks {
    PFN_void tick;
};

struct bsmod_TrackParams {
    char* path;
    char* package;
    char* prefix;
    union {
        struct {
            bool compile_references;
        };
    };
};

struct bsmod_QueueLoad {
    bs_ResourceType type;
    char* path;
};

struct bsmod_AtlasPacker {
    bs_List info;
    bs_List rects;
};

struct bsmod_TextureInfo {
    char* name;
    bs_RGBA* data;
    int name_length;
    int category;
};

struct bsmod_Chunk {
    bs_List bin;
    int id;
    bool has_changes;
};

struct bsmod_Package {
    const char* name;
    bs_U64 name_hash;
    bs_List chunks;
    bs_List resources;
    bool has_changes;
};

struct bsmod_Resource {
    bs_ResourceHeaderData header;
    char* name;
    bool has_changes;
};

struct bsmod_DraggingParams {
    int t;
};

struct bsmod_GridClickParams {
    int atlas_id;
};

struct bsmod_SideMenuTab {
    const char* name;
    bsgfx_AtlasCache* (*cache)();
    void (*push_widgets)(bs_List*, bs_vec2);
    void (*on_click)(bsmod_GridClickParams);
};

 /**
  @return void
  */
BSMODAPI void
bsmod_enableValidation();

 /**
  @return void
  */
BSMODAPI void
bsmod_disableValidation();

 /**
  @return bsmod_Callbacks*
  */
BSMODAPI bsmod_Callbacks*
bsmod_callbacks();

 /**
  @return void
  */
BSMODAPI void
bsmod_copyHoveringDataToBuffer();

 /**
  @return void
  */
BSMODAPI void
bsmod_onIni();

 /**
  @return void
  */
BSMODAPI void
bsmod_onLateIni();

 /**
  @param range
  @return void
  */
BSMODAPI void
bsmod_onCreateQuadSubtypes(
    bs_Range range);

 /**
  @return void
  */
BSMODAPI void
bsmod_onLoad();

 /**
  @return void
  */
BSMODAPI void
bsmod_bindAtlases();

 /**
  @return void
  */
BSMODAPI void
bsmod_onGfxRender();

 /**
  @return void
  */
BSMODAPI void
bsmod_onTick();

 /**
  @param type_id
  @param id
  @return void
  */
BSMODAPI void
bsmod_onMap(
    bsgfx_TypeId type_id,
    int id);

 /**
  @return void
  */
BSMODAPI void
bsmod_onTrack();

 /**
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_onPackBindings();

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onCompileShader(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onLoadTTF(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onConvertBMFont(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackAtlas(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackModels(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackBinary(
    bsmod_TrackParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onPackTextureArray(
    bsmod_TrackParams params);

 /**
  @param packer
  @param name
  @param data
  @param width
  @param height
  @param category
  @return void
  */
BSMODAPI void
bsmod_packAtlasTexture(
    bsmod_AtlasPacker* packer,
    char* name,
    bs_RGBA* data,
    int width,
    int height,
    int category);

 /**
  @param packer
  @param width
  @param height
  @param package
  @param resource_name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packAtlas(
    bsmod_AtlasPacker* packer,
    int width,
    int height,
    char* package,
    char* resource_name);

 /**
  @return bsmod_AtlasPacker
  */
BSMODAPI bsmod_AtlasPacker
bsmod_createAtlasPacker();

 /**
  @param directory_name
  @param package_name
  @param resource_name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packImageDirectory(
    char* directory_name,
    char* package_name,
    char* resource_name);

 /**
  @param package_name
  @param bmfont_path
  @param png_path
  @param value
  @param value_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packBMFont(
    char* package_name,
    char* bmfont_path,
    char* png_path,
    char* value,
    int value_length);

 /**
  @param package_name
  @param bmfont_path
  @param png_path
  @param format
  @param args
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packBMFontV(
    char* package_name,
    char* bmfont_path,
    char* png_path,
    char* format,
    va_list args);

 /**
  @param package_name
  @param bmfont_path
  @param png_path
  @param format
  @param ...
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packBMFontF(
    char* package_name,
    char* bmfont_path,
    char* png_path,
    char* format,
     ...);

 /**
  @param scroll
  @param out
  @return void
  */
BSMODAPI void
bsmod_scrollbar(
    const int* scroll,
    bsgfx_Scrollbar* out);

 /**
  @param width
  @param indent
  @param out
  @return void
  */
BSMODAPI void
bsmod_dividerWidget(
    float width,
    int indent,
    bsgfx_Widget* out);

 /**
  @param cache
  @param align_height
  @param offset
  @param advance_flags
  @param out
  @return void
  */
BSMODAPI void
bsmod_iconWidget(
    const bsgfx_AtlasCache* cache,
    float align_height,
    bs_vec3 offset,
    bs_U32 advance_flags,
    bsgfx_Widget* out);

 /**
  @return bs_List*
  */
BSMODAPI bs_List*
bsmod_packages();

 /**
  @param name
  @return bsmod_Package*
  */
BSMODAPI bsmod_Package*
bsmod_queryPackage(
    const char* name);

 /**
  @param name
  @return bsmod_Package*
  */
BSMODAPI bsmod_Package*
bsmod_ensurePackage(
    const char* name);

 /**
  @param package
  @param name
  @return bsmod_Resource*
  */
BSMODAPI bsmod_Resource*
bsmod_queryResource(
    bsmod_Package* package,
    const char* name);

 /**
  @param package_name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_iniPackage(
    const char* package_name);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param resource_name
  @param resource_name_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResource(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* resource_name,
    int resource_name_length);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param format
  @param args
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResourceV(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* format,
    va_list args);

 /**
  @param type
  @param data
  @param data_size
  @param package_name
  @param format
  @param ...
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_packResourceF(
    bs_ResourceType type,
    unsigned char* data,
    size_t data_size,
    const char* package_name,
    char* format,
     ...);

 /**
  @param name
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_savePackage(
    const char* name);

 /**
  @return void
  */
BSMODAPI void
bsmod_loadShaderReferences();

 /**
  @return void
  */
BSMODAPI void
bsmod_updateShaderReferences();

 /**
  @return void
  */
BSMODAPI void
bsmod_iniCompiler();

 /**
  @param path
  @param name
  @param package
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_compileShader(
    char* path,
    char* name,
    char* package);

 /**
  @param package
  @param name
  @param callback
  @return void
  */
BSMODAPI void
bsmod_queueRasterize(
    const char* package,
    const char* name,
    bs_Callback callback);

 /**
  @return void
  */
BSMODAPI void
bsmod_pollRasterizer();

 /**
  @param render_size
  @param output_size
  @return void
  */
BSMODAPI void
bsmod_beginRasterize(
    bs_ivec2 render_size,
    bs_ivec2 output_size);

 /**
  @return void
  */
BSMODAPI void
bsmod_endRasterize();

 /**
  @param pipeline_hash
  @param subtype
  @param instance_id
  @param category
  @param name
  @param width
  @param height
  @param push_constant_size
  @param push_constant
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_rasterizeInstance(
    bs_PipelineHash pipeline_hash,
    int subtype,
    int instance_id,
    int category,
    char* name,
    int width,
    int height,
    size_t push_constant_size,
    unsigned char* push_constant);

 /**
  @return void
  */
BSMODAPI void
bsmod_instanceTransform();

 /**
  @return void
  */
BSMODAPI void
bsmod_selectHoveringTypes();

 /**
  @param plural
  @return bsgfx_TypeId
  */
BSMODAPI bsgfx_TypeId
bsmod_queryType(
    const char* plural);

 /**
  @param type_id
  @param id
  @return void
  */
BSMODAPI void
bsmod_delete(
    bsgfx_TypeId type_id,
    int id);

 /**
  @param type_id
  @return void
  */
BSMODAPI void
bsmod_deleteSelected(
    bsgfx_TypeId type_id);

 /**
  @param id
  @param value
  @param value_length
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveType(
    bsgfx_TypeId id,
    char* value,
    int value_length);

 /**
  @param id
  @param format
  @param args
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveTypeV(
    bsgfx_TypeId id,
    char* format,
    va_list args);

 /**
  @param id
  @param format
  @param ...
  @return bs_Result
  */
BSMODAPI bs_Result
bsmod_saveTypeF(
    bsgfx_TypeId id,
    char* format,
     ...);

 /**
  @param id
  @param data
  @return void*
  */
BSMODAPI void*
bsmod_add(
    bsgfx_TypeId id,
    void* data);

 /**
  @param list
  @param type
  @param id
  @return bool
  */
BSMODAPI bool
bsmod_isSelected(
    bs_List* list,
    bsgfx_TypeId type,
    int id);

 /**
  @param list
  @param type
  @param id
  @return void
  */
BSMODAPI void
bsmod_select(
    bs_List* list,
    bsgfx_TypeId type,
    int id);

 /**
  @return void
  */
BSMODAPI void
bsmod_deselectAll();

 /**
  @param list
  @param first
  @param count
  @return void
  */
BSMODAPI void
bsmod_deselectRange(
    bs_List* list,
    int first,
    int count);

 /**
  @param list
  @param id
  @return void
  */
BSMODAPI void
bsmod_deselectIndex(
    bs_List* list,
    int id);

 /**
  @param list
  @param id
  @return void
  */
BSMODAPI void
bsmod_deselect(
    bs_List* list,
    int id);

 /**
  @param list
  @return int
  */
BSMODAPI int
bsmod_firstSelectedId(
    bs_List* list);

 /**
  @param list
  @return int
  */
BSMODAPI int
bsmod_lastSelectedId(
    bs_List* list);

 /**
  @param type_id
  @param id
  @return void*
  */
BSMODAPI void*
bsmod_removeFlexible(
    bsgfx_TypeId type_id,
    int id);

 /**
  @param type_id
  @param id
  @param data
  @return void*
  */
BSMODAPI void*
bsmod_addFlexible(
    bsgfx_TypeId type_id,
    int id,
    void* data);

 /**
  @return void
  */
BSMODAPI void
bsmod_readHoveringOutputs();

 /**
  @return void
  */
BSMODAPI void
bsmod_readHoveringInstanceData();

 /**
  @return void
  */
BSMODAPI void
bsmod_readHoveringVertex();

 /**
  @return void
  */
BSMODAPI void
bsmod_editSelectedType();

 /**
  @param package_id
  @return void
  */
BSMODAPI void
bsmod_ensureTypeVersionsAreUpToDate(
    int package_id);

 /**
  @return void
  */
BSMODAPI void
bsmod_renderBillboards();

 /**
  @return void
  */
BSMODAPI void
bsmod_instanceUI();

 /**
  @param widgets
  @param name
  @param offset
  @param width
  @param v
  @param n
  @return void
  */
BSMODAPI void
bsmod_pushVecNWidget(
    bs_List* widgets,
    const char* name,
    bs_vec3 offset,
    float width,
    float* v,
    int n);

 /**
  @param widgets
  @param value
  @param offset
  @param width
  @param name_padding
  @param skip_advance
  @param is_last
  @param has_buttons
  @param name
  @return void
  */
BSMODAPI void
bsmod_pushInputWidget(
    bs_List* widgets,
    void* value,
    bs_vec3 offset,
    float width,
    int name_padding,
    bool skip_advance,
    bool is_last,
    bool has_buttons,
    const char* name);

 /**
  @param position
  @param size
  @return void
  */
BSMODAPI void
bsmod_instanceTileContextMenu(
    bs_vec3 position,
    bs_vec2 size);

 /**
  @param widgets
  @param position
  @param size
  @return void
  */
BSMODAPI void
bsmod_instanceContextMenu(
    bs_List* widgets,
    bs_vec3 position,
    bs_vec2 size);

 /**
  @param widgets
  @param menu_size
  @param icon_offset
  @param icon
  @param name
  @param indent
  @param action
  @param expandable
  @return void
  */
BSMODAPI void
bsmod_pushContextMenuButton(
    bs_List* widgets,
    bs_vec2 menu_size,
    bs_vec3 icon_offset,
    bsgfx_AtlasCache* icon,
    const char* name,
    int indent,
    PFN_bsgfx_ButtonWidgetCallback action,
    bool expandable);

 /**
  @param position
  @param dimensions
  @return void
  */
BSMODAPI void
bsmod_instanceGridMenu(
    bs_vec3 position,
    bs_vec2 dimensions);

 /**
  @return void
  */
BSMODAPI void
bsmod_instanceLightBillboards();

 /**
  @param widgets
  @param background_size
  @return void
  */
BSMODAPI void
bsmod_pushMaterialWidgets(
    bs_List* widgets,
    bs_vec2 background_size);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragMaterial(
    bsmod_DraggingParams params);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onClickMaterialMenu(
    bsmod_GridClickParams params);

 /**
  @return void
  */
BSMODAPI void
bsmod_rasterizeMaterialIcons();

 /**
  @param widgets
  @param background_size
  @return void
  */
BSMODAPI void
bsmod_pushPrefabMenuWidgets(
    bs_List* widgets,
    bs_vec2 background_size);

 /**
  @param widget
  @param position
  @param id
  @param hovering
  @return bool
  */
BSMODAPI bool
bsmod_instancePrefabPreview(
    bsgfx_Widget* widget,
    bs_vec2* position,
    int id,
    bool hovering);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragPrefab(
    bsmod_DraggingParams params);

 /**
  @return void
  */
BSMODAPI void
bsmod_rasterizePrefabIcons();

 /**
  @param widget
  @param position
  @param id
  @param hovering
  @return bool
  */
BSMODAPI bool
bsmod_instancePrimitivePreview(
    bsgfx_Widget* widget,
    bs_vec2* position,
    int id,
    bool hovering);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragPrimitive(
    bsmod_DraggingParams params);

 /**
  @return void
  */
BSMODAPI void
bsmod_rasterizePrimitiveIcons();

 /**
  @param id
  @param params
  @return void
  */
BSMODAPI void
bsmod_setSideMenuTab(
    int id,
    bsmod_GridClickParams params);

 /**
  @param position
  @param dimensions
  @return void
  */
BSMODAPI void
bsmod_instanceSideMenu(
    bs_vec3 position,
    bs_vec2 dimensions);

 /**
  @param widgets
  @param background_size
  @return void
  */
BSMODAPI void
bsmod_pushTileMenuWidgets(
    bs_List* widgets,
    bs_vec2 background_size);

 /**
  @param widget
  @param position
  @param id
  @param hovering
  @return bool
  */
BSMODAPI bool
bsmod_instanceTilePreview(
    bsgfx_Widget* widget,
    bs_vec2* position,
    int id,
    bool hovering);

 /**
  @param params
  @return void
  */
BSMODAPI void
bsmod_onDragTile(
    bsmod_DraggingParams params);

BSMODAPI extern bsmod_Callbacks _bsmod_callbacks_;
BSMODAPI extern int _bsmod_subtypes_[BSMOD_SUBTYPE_COUNT];
BSMODAPI extern bs_Json _bsmod_config_;
BSMODAPI extern bool _bsmod_instance_grid_menu_;
BSMODAPI extern bs_String* _bsmod_search_input_;
BSMODAPI extern bsmod_SideMenuTab _bsmod_side_menu_tabs_[BSMOD_TABS_COUNT];

#endif
