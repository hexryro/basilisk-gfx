
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
        

#ifndef BASILISK_GFX_GEN_H
#define BASILISK_GFX_GEN_H

#include <basilisk-core.h>
#include <../bsgfx_contracts.h>
#include <wtypes.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

typedef struct bsgfx_UIElement bsgfx_UIElement;
typedef struct bsgfx_UIIcon bsgfx_UIIcon;
typedef struct bsgfx_UISolid bsgfx_UISolid;
typedef struct bsgfx_UIText bsgfx_UIText;
typedef struct bsgfx_Text bsgfx_Text;
typedef struct bsgfx_MeshInstance bsgfx_MeshInstance;
typedef struct bsgfx_BoneInstance bsgfx_BoneInstance;
typedef struct bsgfx_QuadInstance bsgfx_QuadInstance;
typedef struct bsgfx_PointInstance bsgfx_PointInstance;
typedef struct bsgfx_LineInstance bsgfx_LineInstance;
typedef struct bsgfx_Scene bsgfx_Scene;
typedef struct bsgfx_Material bsgfx_Material;
typedef struct bsgfx_Collider bsgfx_Collider;
typedef struct bsgfx_SweepCollision bsgfx_SweepCollision;
typedef struct bsgfx_Animator bsgfx_Animator;
typedef struct bsgfx_AnimatorCallbacks bsgfx_AnimatorCallbacks;
typedef struct bsgfx_Settings bsgfx_Settings;
typedef struct bsgfx_Callbacks bsgfx_Callbacks;
typedef struct bsgfx_Application bsgfx_Application;
typedef struct bsgfx_TypeHeader bsgfx_TypeHeader;
typedef struct bsgfx_InstanceType bsgfx_InstanceType;
typedef struct bsgfx_InstanceSubtype bsgfx_InstanceSubtype;
typedef struct bsgfx_Type bsgfx_Type;
typedef struct bsgfx_Foliage bsgfx_Foliage;
typedef struct bsgfx_RawFoliage bsgfx_RawFoliage;
typedef struct bsgfx_Light bsgfx_Light;
typedef struct bsgfx_RawLight bsgfx_RawLight;
typedef struct bsgfx_PrefabMetadata bsgfx_PrefabMetadata;
typedef struct bsgfx_Prefab bsgfx_Prefab;
typedef struct bsgfx_RawPrefab bsgfx_RawPrefab;
typedef struct bsgfx_Primitive bsgfx_Primitive;
typedef struct bsgfx_RawPrimitive bsgfx_RawPrimitive;
typedef struct bsgfx_TileAxis bsgfx_TileAxis;
typedef struct bsgfx_Spawner bsgfx_Spawner;
typedef struct bsgfx_RawSpawner bsgfx_RawSpawner;
typedef struct bsgfx_Tile bsgfx_Tile;
typedef struct bsgfx_RawTile bsgfx_RawTile;
typedef struct bsgfx_TileType bsgfx_TileType;
typedef struct bsgfx_RawTileV1 bsgfx_RawTileV1;
typedef struct bsgfx_ForeachVisibleRowParams bsgfx_ForeachVisibleRowParams;
typedef struct bsgfx_ButtonParams bsgfx_ButtonParams;
typedef struct bsgfx_TableField bsgfx_TableField;
typedef struct bsgfx_Scrollbar bsgfx_Scrollbar;
typedef struct bsgfx_GridParams bsgfx_GridParams;
typedef struct bsgfx_Glyph bsgfx_Glyph;
typedef struct bsgfx_UnicodeBlock2 bsgfx_UnicodeBlock2;
typedef struct bsgfx_KerningPair bsgfx_KerningPair;
typedef struct bsgfx_Font bsgfx_Font;
typedef struct bsgfx_Widget bsgfx_Widget;
typedef struct bsgfx_AtlasCache bsgfx_AtlasCache;
typedef struct bsgfx_MenuTab bsgfx_MenuTab;
typedef struct bsgfx_MenuTabBar bsgfx_MenuTabBar;
typedef struct bsgfx_Menu bsgfx_Menu;
typedef struct bsgfx_TitleBar bsgfx_TitleBar;

typedef enum bsgfx_MaterialCategory bsgfx_MaterialCategory;
typedef enum bsgfx_CollisionType bsgfx_CollisionType;
typedef enum bsgfx_AnimatorTypeBit bsgfx_AnimatorTypeBit;
typedef enum bsgfx_FontFlag bsgfx_FontFlag;
typedef enum bsgfx_InstanceSubtypeFlag bsgfx_InstanceSubtypeFlag;
typedef enum bsgfx_ModelSubtype bsgfx_ModelSubtype;
typedef enum bsgfx_Pipe bsgfx_Pipe;
typedef enum bsgfx_TypeId bsgfx_TypeId;
typedef enum bsgfx_LightType bsgfx_LightType;
typedef enum bsgfx_PrefabExtraSubtype bsgfx_PrefabExtraSubtype;
typedef enum bsgfx_PrefabSubtype bsgfx_PrefabSubtype;
typedef enum bsgfx_PrefabFlag bsgfx_PrefabFlag;
typedef enum bsgfx_PrimitiveFlag bsgfx_PrimitiveFlag;
typedef enum bsgfx_PrimitiveType bsgfx_PrimitiveType;
typedef enum bsgfx_SpawnerType bsgfx_SpawnerType;
typedef enum bsgfx_SpawnerFlag bsgfx_SpawnerFlag;
typedef enum bsgfx_WidgetType bsgfx_WidgetType;
typedef enum bsgfx_InputType bsgfx_InputType;
typedef enum bsgfx_WidgetAdvanceType bsgfx_WidgetAdvanceType;
typedef enum bsgfx_Language bsgfx_Language;

#define BSGFX_FOURCC(A, B, C, D)                                     \
    ((bs_U32)(A) | ((bs_U32)(B) << 8) | ((bs_U32)(C) << 16) | ((bs_U32)(D) << 24))

#define BSGFX_MODEL_PATH                                             \
    "resources/models/"

#define BSGFX_SHADER_PATH                                            \
    "resources/shaders/"

#define BSGFX_AUDIO_PATH                                             \
    "resources/audio/"

#define BSGFX_ENUM_GEN(ENUM)                                         \
    ENUM,

#define BSGFX_STRING_GEN(STRING)                                     \
    #STRING,

#define BSGFX_VALIDATE(condition, ret, format, ...)                  \
    if (!(condition)) {                                              \
        bs_warnF(BS_PRINT_COLOR("[GFX] [VAL]", BS_PRINT_RED) " %s: %s\n" __VA_OPT__(format) "\n", __func__, #condition __VA_OPT__(,) __VA_ARGS__); \
        return ret;                                                  \
    }

#define BSGFX_COLLIDER_SKIN                                          \
    (0.015)

#define du_animatorCallback(name)                                    \
    void(*name)(bsgfx_Animator*)

#define BSGFX_ALPHABET_DEFAULT                                       \
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

#define BSGFX_CONTENT_PATH                                           \
    "content/bsgfx.bpak"

#define BSGFX_PARSE_FORMAT(format, data, len)                        \
        do {                                                         \
            va_list args;                                            \
            va_start(args, format);                                  \
            len = vsnprintf(NULL, 0, format, args);                  \
            va_end(args);                                            \
            if (len >= (sizeof(data) / sizeof(*data))) {             \
                bs_throwBasiliskF(BSX_OUT_OF_BOUNDS,                 \
                    "Format %s has a limit of %d characters",        \
                    format, sizeof(data) - 1);                       \
            }                                                        \
            va_start(args, format);                                  \
            vsprintf(data, format, args);                            \
            va_end(args);                                            \
        } while (0)

#define BSGFX_PIXEL_SCALE                                            \
    (4.0)

#define BSGFX_FIXED_TICK                                             \
    (1.0 / 40.0)

#define BSGFX_TITLE_BAR_COLOR                                        \
    (bs_RGBA) { 255, 255, 255, 200 }

#define BSGFX_SCREENSHOT_DIMENSIONS                                  \
    BS_IV2(1920 / 4, 1080 / 4)

#define BSGFX_SHADOW_COLOR                                           \
    ((bs_RGBA) { 50, 50, 60, 150 })

#define BSGFX_RGBA(r, g, b, a)                                       \
    ((bs_vec4) { (float)r / 255.0, (float)g / 255.0, (float)b / 255.0, (float)a / 255.0 })

#define BSGFX_WHITE                                                  \
    BSGFX_RGBA(255, 255, 255, 255)

#define BSGFX_TILE_SIZE                                              \
    ((bs_vec2) { 32, 32 })

#define BSGFX_TEXTURE_PATH                                           \
    "resources/textures/"

#define BSGFX_MODEL_SUBTYPE(X)                                       \
    X(BSGFX_MODEL_SUBTYPE_DEFAULT)                                   \
    X(BSGFX_MODEL_SUBTYPE_MIRRORED)                                  \
    X(BSGFX_MODEL_SUBTYPE_COUNT)

#define BSGFX_STRUCT_GEN(TYPE, FUNC, ...)                            \
    TYPE FUNC;

#define BSGFX_COUNT_GEN(TYPE, FUNC, ...)                             \
    +1

#define BSGFX_TYPE_MAGIC                                             \
    0x65707974

#define BSGFX_FOLIAGE_VERSION                                        \
    1

#define BSGFX_TYPE_STRUCTURE(type, name)                             \
    type name;

#define BSGFX_TYPE_FIELD_NAMES(type, name)                           \
    #name,

#define BSGFX_TYPE_NAMES(type, name)                                 \
    #type,

#define BSGFX_TYPE_SIZES(type, name)                                 \
    sizeof(type),

#define BSGFX_UNMAPPED_TYPE                                          \
    struct {                                                         \
        BSGFX_TYPE_FIELDS(BSGFX_TYPE_STRUCTURE)                      \
    }

#define BSGFX_MAX_NUM_FOLIAGES                                       \
    256

#define BSGFX_LIGHT_VERSION                                          \
    2

#define BSGFX_MAX_NUM_PREFABS                                        \
    512

#define BSGFX_PREFAB_VERSION                                         \
    1

#define BSGFX_MAX_PRIMITIVES_COUNT                                   \
    (512)

#define BSGFX_PRIMITIVE_VERSION                                      \
    1

#define BSGFX_SPAWNER_VERSION                                        \
    1

#define BSGFX_MAX_TILES_COUNT                                        \
    8192

#define BSGFX_MAX_TILE_PATH_LENGTH                                   \
    16

#define BSGFX_TILE_VERSION                                           \
    2

#define BSGFX_LIST_ROW_DIMENSIONS                                    \
    BS_V2(320, 6.0 * BSGFX_PIXEL_SCALE)

#define BSGFX_BACKGROUND_Z_COUNT                                     \
    3

typedef enum bsgfx_Id bsgfx_Id;
typedef bs_U32 bsgfx_ColliderFlags;
typedef void (__stdcall* PFN_void)();
typedef bs_Queue* (__stdcall* PFN_bsgfx_onQueue)();
typedef bs_U32 bsgfx_PrimitiveFlags;
typedef bs_U32 bsgfx_SpawnerFlags;
typedef void (__stdcall* PFN_bsgfx_TypeMapper)(void*, void*);
typedef bool (__stdcall* PFN_bsgfx_ButtonWidgetCallback)(const bsgfx_ButtonParams*);
typedef struct bsgfx_InstanceHeader bsgfx_InstanceHeader;
enum bsgfx_MaterialCategory {
    BSGFX_MATERIAL_CATEGORY_NONE,
    BSGFX_MATERIAL_CATEGORY_UI_COLOR_SCHEME,
    BSGFX_MATERIAL_CATEGORY_COUNT,
};

enum bsgfx_CollisionType {
    BSGFX_COLLISION_NONE = 0,
    BSGFX_COLLISION_SLOPE = 1 << 0,
    BSGFX_COLLISION_SLOPE_DESCENT = 1 << 1,
    BSGFX_COLLISION_ABOVE = 1 << 2,
    BSGFX_COLLISION_BELOW = 1 << 3,
    BSGFX_COLLISION_LEFT = 1 << 4,
    BSGFX_COLLISION_RIGHT = 1 << 5,
    BSGFX_COLLISION_BACK = 1 << 6,
    BSGFX_COLLISION_FRONT = 1 << 7,
    BSGFX_COLLISION_MAX_SLOPE = 1 << 8,
    BSGFX_COLLISION_STAIRS = 1 << 9,
};

enum bsgfx_AnimatorTypeBit {
    BSGFX_ANIMATOR_TYPE_ONCE_BIT = 1 << 0,
    BSGFX_ANIMATOR_TYPE_ONCE_PER_TICK_BIT = 1 << 1,
    BSGFX_ANIMATOR_TYPE_ONCE_PER_LOOP_BIT = 1 << 2,
    BSGFX_ANIMATOR_TYPE_ONCE_PER_EXIT_BIT = 1 << 3,
};

enum bsgfx_FontFlag {
    BSGFX_FONT_FORCE_CREATE = 1 << 0,
    BSGFX_FONT_NO_CAPS = 1 << 1,
};

enum bsgfx_InstanceSubtypeFlag {
    BSGFX_SUBTYPE_MANUAL_RESET = 1 << 0,
};

enum bsgfx_ModelSubtype {
    BSGFX_MODEL_SUBTYPE_DEFAULT,
    BSGFX_MODEL_SUBTYPE_MIRRORED,
    BSGFX_MODEL_SUBTYPE_COUNT,
};

enum bsgfx_Pipe {
    BSGFX_GRAPHICS_PIPE = (1 << 0),
    BSGFX_COMPUTE_PIPE = (1 << 1),
    BSGFX_SHADOW_PIPE = (1 << 2),
    BSGFX_BONE_PIPE = (1 << 3),
    BSGFX_MESH_PIPE = (1 << 4),
    BSGFX_RENDER_LINES = (1 << 5),
    BSGFX_RENDER_TILES = (1 << 6),
    BSGFX_ALL_PIPES = 0xFFFFFFFF,
};

enum bsgfx_TypeId {
    BSGFX_TYPE_UNDEFINED = -1,
    BSGFX_TYPE_PRIMITIVE,
    BSGFX_TYPE_TILE,
    BSGFX_TYPE_PREFAB,
    BSGFX_TYPE_FOLIAGE,
    BSGFX_TYPE_SPAWNER,
    BSGFX_TYPE_LIGHT,
    BSGFX_TYPE_COUNT,
};

enum bsgfx_LightType {
    BSGFX_LIGHT_TYPE_POINT = 1,
    BSGFX_LIGHT_TYPE_SUN = 2,
};

enum bsgfx_PrefabExtraSubtype {
    BSGFX_PREFAB_SUBTYPE_PRIMITIVE,
};

enum bsgfx_PrefabSubtype {
    BSGFX_PREFAB_SUBTYPE_MESH,
    BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE,
    BSGFX_PREFAB_SUBTYPE_MESH_TEXTURED,
    BSGFX_PREFAB_SUBTYPE_MESH_HI_RES_SCREEN,
    BSGFX_PREFAB_SUBTYPE_MESH_LO_RES_SCREEN,
    BSGFX_PREFAB_SUBTYPE_MESH_VOLUME,
    BSGFX_PREFAB_SUBTYPE_COUNT,
};

enum bsgfx_PrefabFlag {
    BSGFX_PREFAB_HAS_COLLIDER = 1 << 0,
    BSGFX_PREFAB_HIDDEN = 1 << 1,
    BSGFX_PREFAB_TEXTURED_SHADOWS = 1 << 2,
    BSGFX_PREFAB_NO_DEPTH = 1 << 3,
    BSGFX_PREFAB_WRITE_POSITION = 1 << 4,
};

enum bsgfx_PrimitiveFlag {
    BSGFX_PRIMITIVE_HIDDEN = 1 << 0,
};

enum bsgfx_PrimitiveType {
    BSGFX_PRIMITIVE_TYPE_BOX,
    BSGFX_PRIMITIVE_TYPE_SPHERE,
    BSGFX_PRIMITIVE_TYPE_COUNT,
};

enum bsgfx_SpawnerType {
    BSGFX_SPAWNER_ITEM,
    BSGFX_SPAWNER_ENTITY,
};

enum bsgfx_SpawnerFlag {
    BSGFX_SPAWN_ON_SCENE_LOAD = 1 << 0,
};

enum bsgfx_WidgetType {
    BSGFX_WIDGET_UNDEFINED,
    BSGFX_WIDGET_STRING,
    BSGFX_WIDGET_BUTTON,
    BSGFX_WIDGET_INPUT,
    BSGFX_WIDGET_GRID,
    BSGFX_WIDGET_URL,
    BSGFX_WIDGET_RANGE,
    BSGFX_WIDGET_ICON,
    BSGFX_WIDGET_LIST,
    BSGFX_WIDGET_COLOR,
    BSGFX_WIDGET_SLIDER,
    BSGFX_WIDGET_MODEL,
    BSGFX_WIDGET_TABLE,
    BSGFX_WIDGET_BACKGROUND,
};

enum bsgfx_InputType {
    BSGFX_INPUT_DOUBLE,
    BSGFX_INPUT_FLOAT,
    BSGFX_INPUT_ULONG,
    BSGFX_INPUT_LONG,
    BSGFX_INPUT_UINT,
    BSGFX_INPUT_INT,
    BSGFX_INPUT_CHAR,
    BSGFX_INPUT_UCHAR,
    BSGFX_INPUT_STRING,
};

enum bsgfx_WidgetAdvanceType {
    BSGFX_WIDGET_ADVANCE_DOWN = (1 << 0),
    BSGFX_WIDGET_ADVANCE_RIGHT = (1 << 1),
    BSGFX_WIDGET_ADVANCE_RESET_X = (1 << 2),
    BSGFX_WIDGET_ADVANCE_RESET_Y = (1 << 3),
    BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_X = (1 << 4),
    BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Y = (1 << 5),
    BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Z = (1 << 6),
    BSGFX_WIDGET_ADVANCE_APPLY_OFFSET = (BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_X | BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Y | BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Z),
    BSGFX_WIDGET_PLACEMENT_RIGHT = (1 << 7),
};

enum bsgfx_Language {
    BS_LANGUAGE_DONT_KNOW = 0,
    BS_LANGUAGE_A_HMAO = BSGFX_FOURCC('H', 'M', 'D', ' '),
    BS_LANGUAGE_AARI = BSGFX_FOURCC('A', 'R', 'I', ' '),
    BS_LANGUAGE_ABAZA = BSGFX_FOURCC('A', 'B', 'A', ' '),
    BS_LANGUAGE_ABKHAZIAN = BSGFX_FOURCC('A', 'B', 'K', ' '),
    BS_LANGUAGE_ACHI = BSGFX_FOURCC('A', 'C', 'R', ' '),
    BS_LANGUAGE_ACHOLI = BSGFX_FOURCC('A', 'C', 'H', ' '),
    BS_LANGUAGE_ADYGHE = BSGFX_FOURCC('A', 'D', 'Y', ' '),
    BS_LANGUAGE_AFAR = BSGFX_FOURCC('A', 'F', 'R', ' '),
    BS_LANGUAGE_AFRIKAANS = BSGFX_FOURCC('A', 'F', 'K', ' '),
    BS_LANGUAGE_AGAW = BSGFX_FOURCC('A', 'G', 'W', ' '),
    BS_LANGUAGE_AITON = BSGFX_FOURCC('A', 'I', 'O', ' '),
    BS_LANGUAGE_AKAN = BSGFX_FOURCC('A', 'K', 'A', ' '),
    BS_LANGUAGE_ALBANIAN = BSGFX_FOURCC('S', 'Q', 'I', ' '),
    BS_LANGUAGE_ALSATIAN = BSGFX_FOURCC('A', 'L', 'S', ' '),
    BS_LANGUAGE_ALTAI = BSGFX_FOURCC('A', 'L', 'T', ' '),
    BS_LANGUAGE_ALUO = BSGFX_FOURCC('Y', 'N', 'A', ' '),
    BS_LANGUAGE_AMERICAN_PHONETIC = BSGFX_FOURCC('A', 'P', 'P', 'H'),
    BS_LANGUAGE_AMHARIC = BSGFX_FOURCC('A', 'M', 'H', ' '),
    BS_LANGUAGE_ANGLO_SAXON = BSGFX_FOURCC('A', 'N', 'G', ' '),
    BS_LANGUAGE_ARABIC = BSGFX_FOURCC('A', 'R', 'A', ' '),
    BS_LANGUAGE_ARAGONESE = BSGFX_FOURCC('A', 'R', 'G', ' '),
    BS_LANGUAGE_ARAKANESE = BSGFX_FOURCC('A', 'R', 'K', ' '),
    BS_LANGUAGE_ARAKWAL = BSGFX_FOURCC('R', 'K', 'W', ' '),
    BS_LANGUAGE_ARMENIAN = BSGFX_FOURCC('H', 'Y', 'E', ' '),
    BS_LANGUAGE_ARMENIAN_EAST = BSGFX_FOURCC('H', 'Y', 'E', '0'),
    BS_LANGUAGE_AROMANIAN = BSGFX_FOURCC('R', 'U', 'P', ' '),
    BS_LANGUAGE_ARPITAN = BSGFX_FOURCC('F', 'R', 'P', ' '),
    BS_LANGUAGE_ASSAMESE = BSGFX_FOURCC('A', 'S', 'M', ' '),
    BS_LANGUAGE_ASTURIAN = BSGFX_FOURCC('A', 'S', 'T', ' '),
    BS_LANGUAGE_ATHAPASKAN = BSGFX_FOURCC('A', 'T', 'H', ' '),
    BS_LANGUAGE_ATSINA = BSGFX_FOURCC('A', 'T', 'S', ' '),
    BS_LANGUAGE_AVAR = BSGFX_FOURCC('A', 'V', 'R', ' '),
    BS_LANGUAGE_AVATIME = BSGFX_FOURCC('A', 'V', 'N', ' '),
    BS_LANGUAGE_AWADHI = BSGFX_FOURCC('A', 'W', 'A', ' '),
    BS_LANGUAGE_AYMARA = BSGFX_FOURCC('A', 'Y', 'M', ' '),
    BS_LANGUAGE_AZERBAIDJANI = BSGFX_FOURCC('A', 'Z', 'E', ' '),
    BS_LANGUAGE_BADAGA = BSGFX_FOURCC('B', 'A', 'D', ' '),
    BS_LANGUAGE_BAGHELKHANDI = BSGFX_FOURCC('B', 'A', 'G', ' '),
    BS_LANGUAGE_BAGRI = BSGFX_FOURCC('B', 'G', 'Q', ' '),
    BS_LANGUAGE_BALANTE = BSGFX_FOURCC('B', 'L', 'N', ' '),
    BS_LANGUAGE_BALINESE = BSGFX_FOURCC('B', 'A', 'N', ' '),
    BS_LANGUAGE_BALKAR = BSGFX_FOURCC('B', 'A', 'L', ' '),
    BS_LANGUAGE_BALTI = BSGFX_FOURCC('B', 'L', 'T', ' '),
    BS_LANGUAGE_BALUCHI = BSGFX_FOURCC('B', 'L', 'I', ' '),
    BS_LANGUAGE_BAMBARA = BSGFX_FOURCC('B', 'M', 'B', ' '),
    BS_LANGUAGE_BAMILEKE = BSGFX_FOURCC('B', 'M', 'L', ' '),
    BS_LANGUAGE_BANDA = BSGFX_FOURCC('B', 'A', 'D', '0'),
    BS_LANGUAGE_BANDJALANG = BSGFX_FOURCC('B', 'D', 'Y', ' '),
    BS_LANGUAGE_BANGLA = BSGFX_FOURCC('B', 'E', 'N', ' '),
    BS_LANGUAGE_BASHKIR = BSGFX_FOURCC('B', 'S', 'H', ' '),
    BS_LANGUAGE_BASQUE = BSGFX_FOURCC('E', 'U', 'Q', ' '),
    BS_LANGUAGE_BATAK = BSGFX_FOURCC('B', 'T', 'K', ' '),
    BS_LANGUAGE_BATAK_ALAS_KLUET = BSGFX_FOURCC('B', 'T', 'Z', ' '),
    BS_LANGUAGE_BATAK_ANGKOLA = BSGFX_FOURCC('A', 'K', 'B', ' '),
    BS_LANGUAGE_BATAK_DAIRI = BSGFX_FOURCC('B', 'T', 'D', ' '),
    BS_LANGUAGE_BATAK_KARO = BSGFX_FOURCC('B', 'T', 'X', ' '),
    BS_LANGUAGE_BATAK_MANDAILING = BSGFX_FOURCC('B', 'T', 'M', ' '),
    BS_LANGUAGE_BATAK_SIMALUNGUN = BSGFX_FOURCC('B', 'T', 'S', ' '),
    BS_LANGUAGE_BATAK_TOBA = BSGFX_FOURCC('B', 'B', 'C', ' '),
    BS_LANGUAGE_BAULE = BSGFX_FOURCC('B', 'A', 'U', ' '),
    BS_LANGUAGE_BAVARIAN = BSGFX_FOURCC('B', 'A', 'R', ' '),
    BS_LANGUAGE_BELARUSIAN = BSGFX_FOURCC('B', 'E', 'L', ' '),
    BS_LANGUAGE_BEMBA = BSGFX_FOURCC('B', 'E', 'M', ' '),
    BS_LANGUAGE_BENCH = BSGFX_FOURCC('B', 'C', 'H', ' '),
    BS_LANGUAGE_BERBER = BSGFX_FOURCC('B', 'B', 'R', ' '),
    BS_LANGUAGE_BETI = BSGFX_FOURCC('B', 'T', 'I', ' '),
    BS_LANGUAGE_BETTE_KURUMA = BSGFX_FOURCC('X', 'U', 'B', ' '),
    BS_LANGUAGE_BHILI = BSGFX_FOURCC('B', 'H', 'I', ' '),
    BS_LANGUAGE_BHOJPURI = BSGFX_FOURCC('B', 'H', 'O', ' '),
    BS_LANGUAGE_BHUTANESE = BSGFX_FOURCC('D', 'Z', 'N', ' '),
    BS_LANGUAGE_BIBLE_CREE = BSGFX_FOURCC('B', 'C', 'R', ' '),
    BS_LANGUAGE_BIKOL = BSGFX_FOURCC('B', 'I', 'K', ' '),
    BS_LANGUAGE_BILEN = BSGFX_FOURCC('B', 'I', 'L', ' '),
    BS_LANGUAGE_BISHNUPRIYA_MANIPURI = BSGFX_FOURCC('B', 'P', 'Y', ' '),
    BS_LANGUAGE_BISLAMA = BSGFX_FOURCC('B', 'I', 'S', ' '),
    BS_LANGUAGE_BLACKFOOT = BSGFX_FOURCC('B', 'K', 'F', ' '),
    BS_LANGUAGE_BODO = BSGFX_FOURCC('B', 'R', 'X', ' '),
    BS_LANGUAGE_BOSNIAN = BSGFX_FOURCC('B', 'O', 'S', ' '),
    BS_LANGUAGE_BOUYEI = BSGFX_FOURCC('P', 'C', 'C', ' '),
    BS_LANGUAGE_BRAHUI = BSGFX_FOURCC('B', 'R', 'H', ' '),
    BS_LANGUAGE_BRAJ_BHASHA = BSGFX_FOURCC('B', 'R', 'I', ' '),
    BS_LANGUAGE_BRETON = BSGFX_FOURCC('B', 'R', 'E', ' '),
    BS_LANGUAGE_BUGIS = BSGFX_FOURCC('B', 'U', 'G', ' '),
    BS_LANGUAGE_BULGARIAN = BSGFX_FOURCC('B', 'G', 'R', ' '),
    BS_LANGUAGE_BUMTHANGKHA = BSGFX_FOURCC('K', 'J', 'Z', ' '),
    BS_LANGUAGE_BURMESE = BSGFX_FOURCC('B', 'R', 'M', ' '),
    BS_LANGUAGE_BURUSHASKI = BSGFX_FOURCC('B', 'S', 'K', ' '),
    BS_LANGUAGE_CAJUN_FRENCH = BSGFX_FOURCC('F', 'R', 'C', ' '),
    BS_LANGUAGE_CARRIER = BSGFX_FOURCC('C', 'R', 'R', ' '),
    BS_LANGUAGE_CATALAN = BSGFX_FOURCC('C', 'A', 'T', ' '),
    BS_LANGUAGE_CAYUGA = BSGFX_FOURCC('C', 'A', 'Y', ' '),
    BS_LANGUAGE_CEBUANO = BSGFX_FOURCC('C', 'E', 'B', ' '),
    BS_LANGUAGE_CENTRAL_YUPIK = BSGFX_FOURCC('E', 'S', 'U', ' '),
    BS_LANGUAGE_CHAHA_GURAGE = BSGFX_FOURCC('C', 'H', 'G', ' '),
    BS_LANGUAGE_CHAMORRO = BSGFX_FOURCC('C', 'H', 'A', ' '),
    BS_LANGUAGE_CHATTISGARHI = BSGFX_FOURCC('C', 'H', 'H', ' '),
    BS_LANGUAGE_CHECHEN = BSGFX_FOURCC('C', 'H', 'E', ' '),
    BS_LANGUAGE_CHEROKEE = BSGFX_FOURCC('C', 'H', 'R', ' '),
    BS_LANGUAGE_CHEYENNE = BSGFX_FOURCC('C', 'H', 'Y', ' '),
    BS_LANGUAGE_CHICHEWA = BSGFX_FOURCC('C', 'H', 'I', ' '),
    BS_LANGUAGE_CHIGA = BSGFX_FOURCC('C', 'G', 'G', ' '),
    BS_LANGUAGE_CHIMILA = BSGFX_FOURCC('C', 'B', 'G', ' '),
    BS_LANGUAGE_CHIN = BSGFX_FOURCC('Q', 'I', 'N', ' '),
    BS_LANGUAGE_CHINANTEC = BSGFX_FOURCC('C', 'C', 'H', 'N'),
    BS_LANGUAGE_CHINESE_PHONETIC = BSGFX_FOURCC('Z', 'H', 'P', ' '),
    BS_LANGUAGE_CHINESE_SIMPLIFIED = BSGFX_FOURCC('Z', 'H', 'S', ' '),
    BS_LANGUAGE_CHINESE_TRADITIONAL = BSGFX_FOURCC('Z', 'H', 'T', ' '),
    BS_LANGUAGE_CHINESE_TRADITIONAL_HONG_KONG = BSGFX_FOURCC('Z', 'H', 'H', ' '),
    BS_LANGUAGE_CHINESE_TRADITIONAL_MACAO = BSGFX_FOURCC('Z', 'H', 'T', 'M'),
    BS_LANGUAGE_CHIPEWYAN = BSGFX_FOURCC('C', 'H', 'P', ' '),
    BS_LANGUAGE_CHITTAGONIAN = BSGFX_FOURCC('C', 'T', 'G', ' '),
    BS_LANGUAGE_CHOCTAW = BSGFX_FOURCC('C', 'H', 'O', ' '),
    BS_LANGUAGE_CHUKCHI = BSGFX_FOURCC('C', 'H', 'K', ' '),
    BS_LANGUAGE_CHURCH_SLAVONIC = BSGFX_FOURCC('C', 'S', 'L', ' '),
    BS_LANGUAGE_CHUUKESE = BSGFX_FOURCC('C', 'H', 'K', '0'),
    BS_LANGUAGE_CHUVASH = BSGFX_FOURCC('C', 'H', 'U', ' '),
    BS_LANGUAGE_COMORIAN = BSGFX_FOURCC('C', 'M', 'R', ' '),
    BS_LANGUAGE_COMOX = BSGFX_FOURCC('C', 'O', 'O', ' '),
    BS_LANGUAGE_COPTIC = BSGFX_FOURCC('C', 'O', 'P', ' '),
    BS_LANGUAGE_CORNISH = BSGFX_FOURCC('C', 'O', 'R', ' '),
    BS_LANGUAGE_CORSICAN = BSGFX_FOURCC('C', 'O', 'S', ' '),
    BS_LANGUAGE_CREE = BSGFX_FOURCC('C', 'R', 'E', ' '),
    BS_LANGUAGE_CREOLES = BSGFX_FOURCC('C', 'P', 'P', ' '),
    BS_LANGUAGE_CRIMEAN_TATAR = BSGFX_FOURCC('C', 'R', 'T', ' '),
    BS_LANGUAGE_CRIOULO = BSGFX_FOURCC('K', 'E', 'A', ' '),
    BS_LANGUAGE_CROATIAN = BSGFX_FOURCC('H', 'R', 'V', ' '),
    BS_LANGUAGE_CYPRIOT_ARABIC = BSGFX_FOURCC('A', 'C', 'Y', ' '),
    BS_LANGUAGE_CZECH = BSGFX_FOURCC('C', 'S', 'Y', ' '),
    BS_LANGUAGE_DAGBANI = BSGFX_FOURCC('D', 'A', 'G', ' '),
    BS_LANGUAGE_DAN = BSGFX_FOURCC('D', 'N', 'J', ' '),
    BS_LANGUAGE_DANGME = BSGFX_FOURCC('D', 'N', 'G', ' '),
    BS_LANGUAGE_DANISH = BSGFX_FOURCC('D', 'A', 'N', ' '),
    BS_LANGUAGE_DARGWA = BSGFX_FOURCC('D', 'A', 'R', ' '),
    BS_LANGUAGE_DARI = BSGFX_FOURCC('D', 'R', 'I', ' '),
    BS_LANGUAGE_DAYI = BSGFX_FOURCC('D', 'A', 'X', ' '),
    BS_LANGUAGE_DEFAULT = BSGFX_FOURCC('d', 'f', 'l', 't'), // Can be DFLT too..,
    BS_LANGUAGE_DEHONG_DAI = BSGFX_FOURCC('T', 'D', 'D', ' '),
    BS_LANGUAGE_DHANGU = BSGFX_FOURCC('D', 'H', 'G', ' '),
    BS_LANGUAGE_DHIVEHI = BSGFX_FOURCC('D', 'I', 'V', ' '),
    BS_LANGUAGE_DHUWAL = BSGFX_FOURCC('D', 'U', 'J', ' '),
    BS_LANGUAGE_DIMLI = BSGFX_FOURCC('D', 'I', 'Q', ' '),
    BS_LANGUAGE_DINKA = BSGFX_FOURCC('D', 'N', 'K', ' '),
    BS_LANGUAGE_DIVEHI = BSGFX_FOURCC('D', 'I', 'V', ' '),
    BS_LANGUAGE_DJAMBARRPUYNGU = BSGFX_FOURCC('D', 'J', 'R', '0'),
    BS_LANGUAGE_DOGRI = BSGFX_FOURCC('D', 'G', 'O', ' '),
    BS_LANGUAGE_DOGRI_MACROLANGUAGE = BSGFX_FOURCC('D', 'G', 'R', ' '),
    BS_LANGUAGE_DUNGAN = BSGFX_FOURCC('D', 'U', 'N', ' '),
    BS_LANGUAGE_DUTCH = BSGFX_FOURCC('N', 'L', 'D', ' '),
    BS_LANGUAGE_DZONGKHA = BSGFX_FOURCC('D', 'Z', 'N', ' '),
    BS_LANGUAGE_EASTERN_ABENAKI = BSGFX_FOURCC('A', 'A', 'Q', ' '),
    BS_LANGUAGE_EASTERN_CHAM = BSGFX_FOURCC('C', 'J', 'M', ' '),
    BS_LANGUAGE_EASTERN_CREE = BSGFX_FOURCC('E', 'C', 'R', ' '),
    BS_LANGUAGE_EASTERN_MANINKAKAN = BSGFX_FOURCC('E', 'M', 'K', ' '),
    BS_LANGUAGE_EASTERN_PWO_KAREN = BSGFX_FOURCC('K', 'J', 'P', ' '),
    BS_LANGUAGE_EBIRA = BSGFX_FOURCC('E', 'B', 'I', ' '),
    BS_LANGUAGE_EDO = BSGFX_FOURCC('E', 'D', 'O', ' '),
    BS_LANGUAGE_EFIK = BSGFX_FOURCC('E', 'F', 'I', ' '),
    BS_LANGUAGE_EMBERA_BAUDO = BSGFX_FOURCC('B', 'D', 'C', ' '),
    BS_LANGUAGE_EMBERA_CATIO = BSGFX_FOURCC('C', 'T', 'O', ' '),
    BS_LANGUAGE_EMBERA_CHAMI = BSGFX_FOURCC('C', 'M', 'I', ' '),
    BS_LANGUAGE_EMBERA_TADO = BSGFX_FOURCC('T', 'D', 'C', ' '),
    BS_LANGUAGE_ENGLISH = BSGFX_FOURCC('E', 'N', 'G', ' '),
    BS_LANGUAGE_EPENA = BSGFX_FOURCC('S', 'J', 'A', ' '),
    BS_LANGUAGE_ERZYA = BSGFX_FOURCC('E', 'R', 'Z', ' '),
    BS_LANGUAGE_KB_TEXT_SHAPEANTO = BSGFX_FOURCC('N', 'T', 'O', ' '),
    BS_LANGUAGE_ESTONIAN = BSGFX_FOURCC('E', 'T', 'I', ' '),
    BS_LANGUAGE_EVEN = BSGFX_FOURCC('E', 'V', 'N', ' '),
    BS_LANGUAGE_EVENKI = BSGFX_FOURCC('E', 'V', 'K', ' '),
    BS_LANGUAGE_EWE = BSGFX_FOURCC('E', 'W', 'E', ' '),
    BS_LANGUAGE_FALAM_CHIN = BSGFX_FOURCC('H', 'A', 'L', ' '),
    BS_LANGUAGE_FANG = BSGFX_FOURCC('F', 'A', 'N', '0'),
    BS_LANGUAGE_FANTI = BSGFX_FOURCC('F', 'A', 'T', ' '),
    BS_LANGUAGE_FAROESE = BSGFX_FOURCC('F', 'O', 'S', ' '),
    BS_LANGUAGE_FEFE = BSGFX_FOURCC('F', 'M', 'P', ' '),
    BS_LANGUAGE_FIJIAN = BSGFX_FOURCC('F', 'J', 'I', ' '),
    BS_LANGUAGE_FILIPINO = BSGFX_FOURCC('P', 'I', 'L', ' '),
    BS_LANGUAGE_FINNISH = BSGFX_FOURCC('F', 'I', 'N', ' '),
    BS_LANGUAGE_FLEMISH = BSGFX_FOURCC('F', 'L', 'E', ' '),
    BS_LANGUAGE_FON = BSGFX_FOURCC('F', 'O', 'N', ' '),
    BS_LANGUAGE_FOREST_ENETS = BSGFX_FOURCC('F', 'N', 'E', ' '),
    BS_LANGUAGE_FRENCH = BSGFX_FOURCC('F', 'R', 'A', ' '),
    BS_LANGUAGE_FRENCH_ANTILLEAN = BSGFX_FOURCC('F', 'A', 'N', ' '),
    BS_LANGUAGE_FRISIAN = BSGFX_FOURCC('F', 'R', 'I', ' '),
    BS_LANGUAGE_FRIULIAN = BSGFX_FOURCC('F', 'R', 'L', ' '),
    BS_LANGUAGE_FULAH = BSGFX_FOURCC('F', 'U', 'L', ' '),
    BS_LANGUAGE_FUTA = BSGFX_FOURCC('F', 'T', 'A', ' '),
    BS_LANGUAGE_GA = BSGFX_FOURCC('G', 'A', 'D', ' '),
    BS_LANGUAGE_GAGAUZ = BSGFX_FOURCC('G', 'A', 'G', ' '),
    BS_LANGUAGE_GALICIAN = BSGFX_FOURCC('G', 'A', 'L', ' '),
    BS_LANGUAGE_GANDA = BSGFX_FOURCC('L', 'U', 'G', ' '),
    BS_LANGUAGE_GARHWALI = BSGFX_FOURCC('G', 'A', 'W', ' '),
    BS_LANGUAGE_GARO = BSGFX_FOURCC('G', 'R', 'O', ' '),
    BS_LANGUAGE_GARSHUNI = BSGFX_FOURCC('G', 'A', 'R', ' '),
    BS_LANGUAGE_GEBA_KAREN = BSGFX_FOURCC('K', 'V', 'Q', ' '),
    BS_LANGUAGE_GEEZ = BSGFX_FOURCC('G', 'E', 'Z', ' '),
    BS_LANGUAGE_GEORGIAN = BSGFX_FOURCC('K', 'A', 'T', ' '),
    BS_LANGUAGE_GEPO = BSGFX_FOURCC('Y', 'G', 'P', ' '),
    BS_LANGUAGE_GERMAN = BSGFX_FOURCC('D', 'E', 'U', ' '),
    BS_LANGUAGE_GIKUYU = BSGFX_FOURCC('K', 'I', 'K', ' '),
    BS_LANGUAGE_GILAKI = BSGFX_FOURCC('G', 'L', 'K', ' '),
    BS_LANGUAGE_GILBERTESE = BSGFX_FOURCC('G', 'I', 'L', '0'),
    BS_LANGUAGE_GILYAK = BSGFX_FOURCC('G', 'I', 'L', ' '),
    BS_LANGUAGE_GITHABUL = BSGFX_FOURCC('G', 'I', 'H', ' '),
    BS_LANGUAGE_GOGO = BSGFX_FOURCC('G', 'O', 'G', ' '),
    BS_LANGUAGE_GONDI = BSGFX_FOURCC('G', 'O', 'N', ' '),
    BS_LANGUAGE_GREEK = BSGFX_FOURCC('E', 'L', 'L', ' '),
    BS_LANGUAGE_GREENLANDIC = BSGFX_FOURCC('G', 'R', 'N', ' '),
    BS_LANGUAGE_GUARANI = BSGFX_FOURCC('G', 'U', 'A', ' '),
    BS_LANGUAGE_GUINEA = BSGFX_FOURCC('G', 'K', 'P', ' '),
    BS_LANGUAGE_GUJARATI = BSGFX_FOURCC('G', 'U', 'J', ' '),
    BS_LANGUAGE_GUMATJ = BSGFX_FOURCC('G', 'N', 'N', ' '),
    BS_LANGUAGE_GUMUZ = BSGFX_FOURCC('G', 'M', 'Z', ' '),
    BS_LANGUAGE_GUPAPUYNGU = BSGFX_FOURCC('G', 'U', 'F', ' '),
    BS_LANGUAGE_GUSII = BSGFX_FOURCC('G', 'U', 'Z', ' '),
    BS_LANGUAGE_HAIDA = BSGFX_FOURCC('H', 'A', 'I', '0'),
    BS_LANGUAGE_HAITIAN_CREOLE = BSGFX_FOURCC('H', 'A', 'I', ' '),
    BS_LANGUAGE_HALKOMELEM = BSGFX_FOURCC('H', 'U', 'R', ' '),
    BS_LANGUAGE_HAMMER_BANNA = BSGFX_FOURCC('H', 'B', 'N', ' '),
    BS_LANGUAGE_HARARI = BSGFX_FOURCC('H', 'R', 'I', ' '),
    BS_LANGUAGE_HARAUTI = BSGFX_FOURCC('H', 'A', 'R', ' '),
    BS_LANGUAGE_HARYANVI = BSGFX_FOURCC('B', 'G', 'C', ' '),
    BS_LANGUAGE_HAUSA = BSGFX_FOURCC('H', 'A', 'U', ' '),
    BS_LANGUAGE_HAVASUPAI_WALAPAI_YAVAPAI = BSGFX_FOURCC('Y', 'U', 'F', ' '),
    BS_LANGUAGE_HAWAIIAN = BSGFX_FOURCC('H', 'A', 'W', ' '),
    BS_LANGUAGE_HAYA = BSGFX_FOURCC('H', 'A', 'Y', ' '),
    BS_LANGUAGE_HAZARAGI = BSGFX_FOURCC('H', 'A', 'Z', ' '),
    BS_LANGUAGE_HEBREW = BSGFX_FOURCC('I', 'W', 'R', ' '),
    BS_LANGUAGE_HEILTSUK = BSGFX_FOURCC('H', 'E', 'I', ' '),
    BS_LANGUAGE_HERERO = BSGFX_FOURCC('H', 'E', 'R', ' '),
    BS_LANGUAGE_HIGH_MARI = BSGFX_FOURCC('H', 'M', 'A', ' '),
    BS_LANGUAGE_HILIGAYNON = BSGFX_FOURCC('H', 'I', 'L', ' '),
    BS_LANGUAGE_HINDI = BSGFX_FOURCC('H', 'I', 'N', ' '),
    BS_LANGUAGE_HINDKO = BSGFX_FOURCC('H', 'N', 'D', ' '),
    BS_LANGUAGE_HIRI_MOTU = BSGFX_FOURCC('H', 'M', 'O', ' '),
    BS_LANGUAGE_HMONG = BSGFX_FOURCC('H', 'M', 'N', ' '),
    BS_LANGUAGE_HMONG_DAW = BSGFX_FOURCC('M', 'W', 'W', ' '),
    BS_LANGUAGE_HMONG_SHUAT = BSGFX_FOURCC('H', 'M', 'Z', ' '),
    BS_LANGUAGE_HO = BSGFX_FOURCC('H', 'O', ' ', ' '),
    BS_LANGUAGE_HUNGARIAN = BSGFX_FOURCC('H', 'U', 'N', ' '),
    BS_LANGUAGE_IBAN = BSGFX_FOURCC('I', 'B', 'A', ' '),
    BS_LANGUAGE_IBIBIO = BSGFX_FOURCC('I', 'B', 'B', ' '),
    BS_LANGUAGE_ICELANDIC = BSGFX_FOURCC('I', 'S', 'L', ' '),
    BS_LANGUAGE_IDO = BSGFX_FOURCC('I', 'D', 'O', ' '),
    BS_LANGUAGE_IGBO = BSGFX_FOURCC('I', 'B', 'O', ' '),
    BS_LANGUAGE_IJO = BSGFX_FOURCC('I', 'J', 'O', ' '),
    BS_LANGUAGE_ILOKANO = BSGFX_FOURCC('I', 'L', 'O', ' '),
    BS_LANGUAGE_INARI_SAMI = BSGFX_FOURCC('I', 'S', 'M', ' '),
    BS_LANGUAGE_INDONESIAN = BSGFX_FOURCC('I', 'N', 'D', ' '),
    BS_LANGUAGE_INGUSH = BSGFX_FOURCC('I', 'N', 'G', ' '),
    BS_LANGUAGE_INTERLINGUA = BSGFX_FOURCC('I', 'N', 'A', ' '),
    BS_LANGUAGE_INTERLINGUE = BSGFX_FOURCC('I', 'L', 'E', ' '),
    BS_LANGUAGE_INUKTITUT = BSGFX_FOURCC('I', 'N', 'U', ' '),
    BS_LANGUAGE_INUPIAT = BSGFX_FOURCC('I', 'P', 'K', ' '),
    BS_LANGUAGE_IPA_PHONETIC = BSGFX_FOURCC('I', 'P', 'P', ' '),
    BS_LANGUAGE_IRISH = BSGFX_FOURCC('I', 'R', 'I', ' '),
    BS_LANGUAGE_IRISH_TRADITIONAL = BSGFX_FOURCC('I', 'R', 'T', ' '),
    BS_LANGUAGE_IRULA = BSGFX_FOURCC('I', 'R', 'U', ' '),
    BS_LANGUAGE_ITALIAN = BSGFX_FOURCC('I', 'T', 'A', ' '),
    BS_LANGUAGE_JAMAICAN_CREOLE = BSGFX_FOURCC('J', 'A', 'M', ' '),
    BS_LANGUAGE_JAPANESE = BSGFX_FOURCC('J', 'A', 'N', ' '),
    BS_LANGUAGE_JAVANESE = BSGFX_FOURCC('J', 'A', 'V', ' '),
    BS_LANGUAGE_JENNU_KURUMA = BSGFX_FOURCC('X', 'U', 'J', ' '),
    BS_LANGUAGE_JUDEO_TAT = BSGFX_FOURCC('J', 'D', 'T', ' '),
    BS_LANGUAGE_JULA = BSGFX_FOURCC('J', 'U', 'L', ' '),
    BS_LANGUAGE_KABARDIAN = BSGFX_FOURCC('K', 'A', 'B', ' '),
    BS_LANGUAGE_KABYLE = BSGFX_FOURCC('K', 'A', 'B', '0'),
    BS_LANGUAGE_KACHCHI = BSGFX_FOURCC('K', 'A', 'C', ' '),
    BS_LANGUAGE_KADIWEU = BSGFX_FOURCC('K', 'B', 'C', ' '),
    BS_LANGUAGE_KALENJIN = BSGFX_FOURCC('K', 'A', 'L', ' '),
    BS_LANGUAGE_KALMYK = BSGFX_FOURCC('K', 'L', 'M', ' '),
    BS_LANGUAGE_KAMBA = BSGFX_FOURCC('K', 'M', 'B', ' '),
    BS_LANGUAGE_KANAUJI = BSGFX_FOURCC('B', 'J', 'J', ' '),
    BS_LANGUAGE_KANNADA = BSGFX_FOURCC('K', 'A', 'N', ' '),
    BS_LANGUAGE_KANURI = BSGFX_FOURCC('K', 'N', 'R', ' '),
    BS_LANGUAGE_KAQCHIKEL = BSGFX_FOURCC('C', 'A', 'K', ' '),
    BS_LANGUAGE_KARACHAY = BSGFX_FOURCC('K', 'A', 'R', ' '),
    BS_LANGUAGE_KARAIM = BSGFX_FOURCC('K', 'R', 'M', ' '),
    BS_LANGUAGE_KARAKALPAK = BSGFX_FOURCC('K', 'R', 'K', ' '),
    BS_LANGUAGE_KARELIAN = BSGFX_FOURCC('K', 'R', 'L', ' '),
    BS_LANGUAGE_KAREN = BSGFX_FOURCC('K', 'R', 'N', ' '),
    BS_LANGUAGE_KASHMIRI = BSGFX_FOURCC('K', 'S', 'H', ' '),
    BS_LANGUAGE_KASHUBIAN = BSGFX_FOURCC('C', 'S', 'B', ' '),
    BS_LANGUAGE_KATE = BSGFX_FOURCC('K', 'M', 'G', ' '),
    BS_LANGUAGE_KAZAKH = BSGFX_FOURCC('K', 'A', 'Z', ' '),
    BS_LANGUAGE_KEBENA = BSGFX_FOURCC('K', 'E', 'B', ' '),
    BS_LANGUAGE_KEKCHI = BSGFX_FOURCC('K', 'E', 'K', ' '),
    BS_LANGUAGE_KHAKASS = BSGFX_FOURCC('K', 'H', 'A', ' '),
    BS_LANGUAGE_KHAMTI_SHAN = BSGFX_FOURCC('K', 'H', 'T', ' '),
    BS_LANGUAGE_KHAMYANG = BSGFX_FOURCC('K', 'S', 'U', ' '),
    BS_LANGUAGE_KHANTY_KAZIM = BSGFX_FOURCC('K', 'H', 'K', ' '),
    BS_LANGUAGE_KHANTY_SHURISHKAR = BSGFX_FOURCC('K', 'H', 'S', ' '),
    BS_LANGUAGE_KHANTY_VAKHI = BSGFX_FOURCC('K', 'H', 'V', ' '),
    BS_LANGUAGE_KHASI = BSGFX_FOURCC('K', 'S', 'I', ' '),
    BS_LANGUAGE_KHENGKHA = BSGFX_FOURCC('X', 'K', 'F', ' '),
    BS_LANGUAGE_KHINALUG = BSGFX_FOURCC('K', 'J', 'J', ' '),
    BS_LANGUAGE_KHMER = BSGFX_FOURCC('K', 'H', 'M', ' '),
    BS_LANGUAGE_KHORASANI_TURKIC = BSGFX_FOURCC('K', 'M', 'Z', ' '),
    BS_LANGUAGE_KHOWAR = BSGFX_FOURCC('K', 'H', 'W', ' '),
    BS_LANGUAGE_KHUTSURI_GEORGIAN = BSGFX_FOURCC('K', 'G', 'E', ' '),
    BS_LANGUAGE_KICHE = BSGFX_FOURCC('Q', 'U', 'C', ' '),
    BS_LANGUAGE_KIKONGO = BSGFX_FOURCC('K', 'O', 'N', ' '),
    BS_LANGUAGE_KILDIN_SAMI = BSGFX_FOURCC('K', 'S', 'M', ' '),
    BS_LANGUAGE_KINYARWANDA = BSGFX_FOURCC('R', 'U', 'A', ' '),
    BS_LANGUAGE_KIRMANJKI = BSGFX_FOURCC('K', 'I', 'U', ' '),
    BS_LANGUAGE_KISII = BSGFX_FOURCC('K', 'I', 'S', ' '),
    BS_LANGUAGE_KITUBA = BSGFX_FOURCC('M', 'K', 'W', ' '),
    BS_LANGUAGE_KODAGU = BSGFX_FOURCC('K', 'O', 'D', ' '),
    BS_LANGUAGE_KOKNI = BSGFX_FOURCC('K', 'K', 'N', ' '),
    BS_LANGUAGE_KOMI = BSGFX_FOURCC('K', 'O', 'M', ' '),
    BS_LANGUAGE_KOMI_PERMYAK = BSGFX_FOURCC('K', 'O', 'P', ' '),
    BS_LANGUAGE_KOMI_ZYRIAN = BSGFX_FOURCC('K', 'O', 'Z', ' '),
    BS_LANGUAGE_KOMO = BSGFX_FOURCC('K', 'M', 'O', ' '),
    BS_LANGUAGE_KOMSO = BSGFX_FOURCC('K', 'M', 'S', ' '),
    BS_LANGUAGE_KONGO = BSGFX_FOURCC('K', 'O', 'N', '0'),
    BS_LANGUAGE_KONKANI = BSGFX_FOURCC('K', 'O', 'K', ' '),
    BS_LANGUAGE_KOORETE = BSGFX_FOURCC('K', 'R', 'T', ' '),
    BS_LANGUAGE_KOREAN = BSGFX_FOURCC('K', 'O', 'R', ' '),
    BS_LANGUAGE_KOREAO_OLD_HANGUL = BSGFX_FOURCC('K', 'O', 'H', ' '),
    BS_LANGUAGE_KORYAK = BSGFX_FOURCC('K', 'Y', 'K', ' '),
    BS_LANGUAGE_KOSRAEAN = BSGFX_FOURCC('K', 'O', 'S', ' '),
    BS_LANGUAGE_KPELLE = BSGFX_FOURCC('K', 'P', 'L', ' '),
    BS_LANGUAGE_KPELLE_LIBERIA = BSGFX_FOURCC('X', 'P', 'E', ' '),
    BS_LANGUAGE_KRIO = BSGFX_FOURCC('K', 'R', 'I', ' '),
    BS_LANGUAGE_KRYMCHAK = BSGFX_FOURCC('J', 'C', 'T', ' '),
    BS_LANGUAGE_KUANYAMA = BSGFX_FOURCC('K', 'U', 'A', ' '),
    BS_LANGUAGE_KUBE = BSGFX_FOURCC('K', 'G', 'F', ' '),
    BS_LANGUAGE_KUI = BSGFX_FOURCC('K', 'U', 'I', ' '),
    BS_LANGUAGE_KULVI = BSGFX_FOURCC('K', 'U', 'K', ' '),
    BS_LANGUAGE_KUMAONI = BSGFX_FOURCC('K', 'M', 'N', ' '),
    BS_LANGUAGE_KUMYK = BSGFX_FOURCC('K', 'U', 'M', ' '),
    BS_LANGUAGE_KURDISH = BSGFX_FOURCC('K', 'U', 'R', ' '),
    BS_LANGUAGE_KURUKH = BSGFX_FOURCC('K', 'U', 'U', ' '),
    BS_LANGUAGE_KUY = BSGFX_FOURCC('K', 'U', 'Y', ' '),
    BS_LANGUAGE_KWAKWALA = BSGFX_FOURCC('K', 'W', 'K', ' '),
    BS_LANGUAGE_KYRGYZ = BSGFX_FOURCC('K', 'I', 'R', ' '),
    BS_LANGUAGE_L_CREE = BSGFX_FOURCC('L', 'C', 'R', ' '),
    BS_LANGUAGE_LADAKHI = BSGFX_FOURCC('L', 'D', 'K', ' '),
    BS_LANGUAGE_LADIN = BSGFX_FOURCC('L', 'A', 'D', ' '),
    BS_LANGUAGE_LADINO = BSGFX_FOURCC('J', 'U', 'D', ' '),
    BS_LANGUAGE_LAHULI = BSGFX_FOURCC('L', 'A', 'H', ' '),
    BS_LANGUAGE_LAK = BSGFX_FOURCC('L', 'A', 'K', ' '),
    BS_LANGUAGE_LAKI = BSGFX_FOURCC('L', 'K', 'I', ' '),
    BS_LANGUAGE_LAMBANI = BSGFX_FOURCC('L', 'A', 'M', ' '),
    BS_LANGUAGE_LAMPUNG = BSGFX_FOURCC('L', 'J', 'P', ' '),
    BS_LANGUAGE_LAO = BSGFX_FOURCC('L', 'A', 'O', ' '),
    BS_LANGUAGE_LATIN = BSGFX_FOURCC('L', 'A', 'T', ' '),
    BS_LANGUAGE_LATVIAN = BSGFX_FOURCC('L', 'V', 'I', ' '),
    BS_LANGUAGE_LAZ = BSGFX_FOURCC('L', 'A', 'Z', ' '),
    BS_LANGUAGE_LELEMI = BSGFX_FOURCC('L', 'E', 'F', ' '),
    BS_LANGUAGE_LEZGI = BSGFX_FOURCC('L', 'E', 'Z', ' '),
    BS_LANGUAGE_LIGURIAN = BSGFX_FOURCC('L', 'I', 'J', ' '),
    BS_LANGUAGE_LIMBU = BSGFX_FOURCC('L', 'M', 'B', ' '),
    BS_LANGUAGE_LIMBURGISH = BSGFX_FOURCC('L', 'I', 'M', ' '),
    BS_LANGUAGE_LINGALA = BSGFX_FOURCC('L', 'I', 'N', ' '),
    BS_LANGUAGE_LIPO = BSGFX_FOURCC('L', 'P', 'O', ' '),
    BS_LANGUAGE_LISU = BSGFX_FOURCC('L', 'I', 'S', ' '),
    BS_LANGUAGE_LITHUANIAN = BSGFX_FOURCC('L', 'T', 'H', ' '),
    BS_LANGUAGE_LIV = BSGFX_FOURCC('L', 'I', 'V', ' '),
    BS_LANGUAGE_LOJBAN = BSGFX_FOURCC('J', 'B', 'O', ' '),
    BS_LANGUAGE_LOMA = BSGFX_FOURCC('L', 'O', 'M', ' '),
    BS_LANGUAGE_LOMBARD = BSGFX_FOURCC('L', 'M', 'O', ' '),
    BS_LANGUAGE_LOMWE = BSGFX_FOURCC('L', 'M', 'W', ' '),
    BS_LANGUAGE_LOW_MARI = BSGFX_FOURCC('L', 'M', 'A', ' '),
    BS_LANGUAGE_LOW_SAXON = BSGFX_FOURCC('N', 'D', 'S', ' '),
    BS_LANGUAGE_LOWER_SORBIAN = BSGFX_FOURCC('L', 'S', 'B', ' '),
    BS_LANGUAGE_LU = BSGFX_FOURCC('X', 'B', 'D', ' '),
    BS_LANGUAGE_LUBA_KATANGA = BSGFX_FOURCC('L', 'U', 'B', ' '),
    BS_LANGUAGE_LUBA_LULUA = BSGFX_FOURCC('L', 'U', 'A', ' '),
    BS_LANGUAGE_LULE_SAMI = BSGFX_FOURCC('L', 'S', 'M', ' '),
    BS_LANGUAGE_LUO = BSGFX_FOURCC('L', 'U', 'O', ' '),
    BS_LANGUAGE_LURI = BSGFX_FOURCC('L', 'R', 'C', ' '),
    BS_LANGUAGE_LUSHOOTSEED = BSGFX_FOURCC('L', 'U', 'T', ' '),
    BS_LANGUAGE_LUXEMBOURGISH = BSGFX_FOURCC('L', 'T', 'Z', ' '),
    BS_LANGUAGE_LUYIA = BSGFX_FOURCC('L', 'U', 'H', ' '),
    BS_LANGUAGE_MACEDONIAN = BSGFX_FOURCC('M', 'K', 'D', ' '),
    BS_LANGUAGE_MADURA = BSGFX_FOURCC('M', 'A', 'D', ' '),
    BS_LANGUAGE_MAGAHI = BSGFX_FOURCC('M', 'A', 'G', ' '),
    BS_LANGUAGE_MAITHILI = BSGFX_FOURCC('M', 'T', 'H', ' '),
    BS_LANGUAGE_MAJANG = BSGFX_FOURCC('M', 'A', 'J', ' '),
    BS_LANGUAGE_MAKASAR = BSGFX_FOURCC('M', 'K', 'R', ' '),
    BS_LANGUAGE_MAKHUWA = BSGFX_FOURCC('M', 'A', 'K', ' '),
    BS_LANGUAGE_MAKONDE = BSGFX_FOURCC('K', 'D', 'E', ' '),
    BS_LANGUAGE_MALAGASY = BSGFX_FOURCC('M', 'L', 'G', ' '),
    BS_LANGUAGE_MALAY = BSGFX_FOURCC('M', 'L', 'Y', ' '),
    BS_LANGUAGE_MALAYALAM = BSGFX_FOURCC('M', 'A', 'L', ' '),
    BS_LANGUAGE_MALAYALAM_REFORMED = BSGFX_FOURCC('M', 'L', 'R', ' '),
    BS_LANGUAGE_MALE = BSGFX_FOURCC('M', 'L', 'E', ' '),
    BS_LANGUAGE_MALINKE = BSGFX_FOURCC('M', 'L', 'N', ' '),
    BS_LANGUAGE_MALTESE = BSGFX_FOURCC('M', 'T', 'S', ' '),
    BS_LANGUAGE_MAM = BSGFX_FOURCC('M', 'A', 'M', ' '),
    BS_LANGUAGE_MANCHU = BSGFX_FOURCC('M', 'C', 'H', ' '),
    BS_LANGUAGE_MANDAR = BSGFX_FOURCC('M', 'D', 'R', ' '),
    BS_LANGUAGE_MANDINKA = BSGFX_FOURCC('M', 'N', 'D', ' '),
    BS_LANGUAGE_MANINKA = BSGFX_FOURCC('M', 'N', 'K', ' '),
    BS_LANGUAGE_MANIPURI = BSGFX_FOURCC('M', 'N', 'I', ' '),
    BS_LANGUAGE_MANO = BSGFX_FOURCC('M', 'E', 'V', ' '),
    BS_LANGUAGE_MANSI = BSGFX_FOURCC('M', 'A', 'N', ' '),
    BS_LANGUAGE_MANX = BSGFX_FOURCC('M', 'N', 'X', ' '),
    BS_LANGUAGE_MAORI = BSGFX_FOURCC('M', 'R', 'I', ' '),
    BS_LANGUAGE_MAPUDUNGUN = BSGFX_FOURCC('M', 'A', 'P', ' '),
    BS_LANGUAGE_MARATHI = BSGFX_FOURCC('M', 'A', 'R', ' '),
    BS_LANGUAGE_MARSHALLESE = BSGFX_FOURCC('M', 'A', 'H', ' '),
    BS_LANGUAGE_MARWARI = BSGFX_FOURCC('M', 'A', 'W', ' '),
    BS_LANGUAGE_MAYAN = BSGFX_FOURCC('M', 'Y', 'N', ' '),
    BS_LANGUAGE_MAZANDERANI = BSGFX_FOURCC('M', 'Z', 'N', ' '),
    BS_LANGUAGE_MBEMBE_TIGON = BSGFX_FOURCC('N', 'Z', 'A', ' '),
    BS_LANGUAGE_MBO = BSGFX_FOURCC('M', 'B', 'O', ' '),
    BS_LANGUAGE_MBUNDU = BSGFX_FOURCC('M', 'B', 'N', ' '),
    BS_LANGUAGE_MEDUMBA = BSGFX_FOURCC('B', 'Y', 'V', ' '),
    BS_LANGUAGE_MEEN = BSGFX_FOURCC('M', 'E', 'N', ' '),
    BS_LANGUAGE_MENDE = BSGFX_FOURCC('M', 'D', 'E', ' '),
    BS_LANGUAGE_MERU = BSGFX_FOURCC('M', 'E', 'R', ' '),
    BS_LANGUAGE_MEWATI = BSGFX_FOURCC('W', 'T', 'M', ' '),
    BS_LANGUAGE_MINANGKABAU = BSGFX_FOURCC('M', 'I', 'N', ' '),
    BS_LANGUAGE_MINJANGBAL = BSGFX_FOURCC('X', 'J', 'B', ' '),
    BS_LANGUAGE_MIRANDESE = BSGFX_FOURCC('M', 'W', 'L', ' '),
    BS_LANGUAGE_MIZO = BSGFX_FOURCC('M', 'I', 'Z', ' '),
    BS_LANGUAGE_MOHAWK = BSGFX_FOURCC('M', 'O', 'H', ' '),
    BS_LANGUAGE_MOKSHA = BSGFX_FOURCC('M', 'O', 'K', ' '),
    BS_LANGUAGE_MOLDAVIAN = BSGFX_FOURCC('M', 'O', 'L', ' '),
    BS_LANGUAGE_MON = BSGFX_FOURCC('M', 'O', 'N', ' '),
    BS_LANGUAGE_MONGOLIAN = BSGFX_FOURCC('M', 'N', 'G', ' '),
    BS_LANGUAGE_MOOSE_CREE = BSGFX_FOURCC('M', 'C', 'R', ' '),
    BS_LANGUAGE_MORISYEN = BSGFX_FOURCC('M', 'F', 'E', ' '),
    BS_LANGUAGE_MOROCCAN = BSGFX_FOURCC('M', 'O', 'R', ' '),
    BS_LANGUAGE_MOSSI = BSGFX_FOURCC('M', 'P', 'S', ' '),
    BS_LANGUAGE_MUNDARI = BSGFX_FOURCC('M', 'U', 'N', ' '),
    BS_LANGUAGE_MUSCOGEE = BSGFX_FOURCC('M', 'U', 'S', ' '),
    BS_LANGUAGE_N_CREE = BSGFX_FOURCC('N', 'C', 'R', ' '),
    BS_LANGUAGE_NAGA_ASSAMESE = BSGFX_FOURCC('N', 'A', 'G', ' '),
    BS_LANGUAGE_NAGARI = BSGFX_FOURCC('N', 'G', 'R', ' '),
    BS_LANGUAGE_NAHUATL = BSGFX_FOURCC('N', 'A', 'H', ' '),
    BS_LANGUAGE_NANAI = BSGFX_FOURCC('N', 'A', 'N', ' '),
    BS_LANGUAGE_NASKAPI = BSGFX_FOURCC('N', 'A', 'S', ' '),
    BS_LANGUAGE_NAURUAN = BSGFX_FOURCC('N', 'A', 'U', ' '),
    BS_LANGUAGE_NAVAJO = BSGFX_FOURCC('N', 'A', 'V', ' '),
    BS_LANGUAGE_NDAU = BSGFX_FOURCC('N', 'D', 'C', ' '),
    BS_LANGUAGE_NDEBELE = BSGFX_FOURCC('N', 'D', 'B', ' '),
    BS_LANGUAGE_NDONGA = BSGFX_FOURCC('N', 'D', 'G', ' '),
    BS_LANGUAGE_NEAPOLITAN = BSGFX_FOURCC('N', 'A', 'P', ' '),
    BS_LANGUAGE_NEPALI = BSGFX_FOURCC('N', 'E', 'P', ' '),
    BS_LANGUAGE_NEWARI = BSGFX_FOURCC('N', 'E', 'W', ' '),
    BS_LANGUAGE_NGBAKA = BSGFX_FOURCC('N', 'G', 'A', ' '),
    BS_LANGUAGE_NIGERIAN_FULFULDE = BSGFX_FOURCC('F', 'U', 'V', ' '),
    BS_LANGUAGE_NIMADI = BSGFX_FOURCC('N', 'O', 'E', ' '),
    BS_LANGUAGE_NISI = BSGFX_FOURCC('N', 'I', 'S', ' '),
    BS_LANGUAGE_NIUEAN = BSGFX_FOURCC('N', 'I', 'U', ' '),
    BS_LANGUAGE_NKO = BSGFX_FOURCC('N', 'K', 'O', ' '),
    BS_LANGUAGE_NOGAI = BSGFX_FOURCC('N', 'O', 'G', ' '),
    BS_LANGUAGE_NORFOLK = BSGFX_FOURCC('P', 'I', 'H', ' '),
    BS_LANGUAGE_NORTH_SLAVEY = BSGFX_FOURCC('S', 'C', 'S', ' '),
    BS_LANGUAGE_NORTHERN_EMBERA = BSGFX_FOURCC('E', 'M', 'P', ' '),
    BS_LANGUAGE_NORTHERN_SAMI = BSGFX_FOURCC('N', 'S', 'M', ' '),
    BS_LANGUAGE_NORTHERN_SOTHO = BSGFX_FOURCC('N', 'S', 'O', ' '),
    BS_LANGUAGE_NORTHERN_TAI = BSGFX_FOURCC('N', 'T', 'A', ' '),
    BS_LANGUAGE_NORWAY_HOUSE_CREE = BSGFX_FOURCC('N', 'H', 'C', ' '),
    BS_LANGUAGE_NORWEGIAN = BSGFX_FOURCC('N', 'O', 'R', ' '),
    BS_LANGUAGE_NORWEGIAN_NYNORSK = BSGFX_FOURCC('N', 'Y', 'N', ' '),
    BS_LANGUAGE_NOVIAL = BSGFX_FOURCC('N', 'O', 'V', ' '),
    BS_LANGUAGE_NUMANGGANG = BSGFX_FOURCC('N', 'O', 'P', ' '),
    BS_LANGUAGE_NUNAVIK_INUKTITUT = BSGFX_FOURCC('I', 'N', 'U', ' '),
    BS_LANGUAGE_NUU_CHAH_NULTH = BSGFX_FOURCC('N', 'U', 'K', ' '),
    BS_LANGUAGE_NYAMWEZI = BSGFX_FOURCC('N', 'Y', 'M', ' '),
    BS_LANGUAGE_NYANKOLE = BSGFX_FOURCC('N', 'K', 'L', ' '),
    BS_LANGUAGE_OCCITAN = BSGFX_FOURCC('O', 'C', 'I', ' '),
    BS_LANGUAGE_ODIA = BSGFX_FOURCC('O', 'R', 'I', ' '),
    BS_LANGUAGE_OJI_CREE = BSGFX_FOURCC('O', 'C', 'R', ' '),
    BS_LANGUAGE_OJIBWAY = BSGFX_FOURCC('O', 'J', 'B', ' '),
    BS_LANGUAGE_OLD_IRISH = BSGFX_FOURCC('S', 'G', 'A', ' '),
    BS_LANGUAGE_OLD_JAVANESE = BSGFX_FOURCC('K', 'A', 'W', ' '),
    BS_LANGUAGE_ONEIDA = BSGFX_FOURCC('O', 'N', 'E', ' '),
    BS_LANGUAGE_ONONDAGA = BSGFX_FOURCC('O', 'N', 'O', ' '),
    BS_LANGUAGE_OROMO = BSGFX_FOURCC('O', 'R', 'O', ' '),
    BS_LANGUAGE_OSSETIAN = BSGFX_FOURCC('O', 'S', 'S', ' '),
    BS_LANGUAGE_PA_O_KAREN = BSGFX_FOURCC('B', 'L', 'K', ' '),
    BS_LANGUAGE_PALAUAN = BSGFX_FOURCC('P', 'A', 'U', ' '),
    BS_LANGUAGE_PALAUNG = BSGFX_FOURCC('P', 'L', 'G', ' '),
    BS_LANGUAGE_PALESTINIAN_ARAMAIC = BSGFX_FOURCC('P', 'A', 'A', ' '),
    BS_LANGUAGE_PALI = BSGFX_FOURCC('P', 'A', 'L', ' '),
    BS_LANGUAGE_PALPA = BSGFX_FOURCC('P', 'A', 'P', ' '),
    BS_LANGUAGE_PAMPANGAN = BSGFX_FOURCC('P', 'A', 'M', ' '),
    BS_LANGUAGE_PANGASINAN = BSGFX_FOURCC('P', 'A', 'G', ' '),
    BS_LANGUAGE_PAPIAMENTU = BSGFX_FOURCC('P', 'A', 'P', '0'),
    BS_LANGUAGE_PASHTO = BSGFX_FOURCC('P', 'A', 'S', ' '),
    BS_LANGUAGE_PATTANI_MALAY = BSGFX_FOURCC('M', 'F', 'A', ' '),
    BS_LANGUAGE_PENNSYLVANIA_GERMAN = BSGFX_FOURCC('P', 'D', 'C', ' '),
    BS_LANGUAGE_PERSIAN = BSGFX_FOURCC('F', 'A', 'R', ' '),
    BS_LANGUAGE_PHAKE = BSGFX_FOURCC('P', 'J', 'K', ' '),
    BS_LANGUAGE_PICARD = BSGFX_FOURCC('P', 'C', 'D', ' '),
    BS_LANGUAGE_PIEMONTESE = BSGFX_FOURCC('P', 'M', 'S', ' '),
    BS_LANGUAGE_PILAGA = BSGFX_FOURCC('P', 'L', 'G', ' '),
    BS_LANGUAGE_PITE_SAMI = BSGFX_FOURCC('S', 'J', 'E', ' '),
    BS_LANGUAGE_POCOMCHI = BSGFX_FOURCC('P', 'O', 'H', ' '),
    BS_LANGUAGE_POHNPEIAN = BSGFX_FOURCC('P', 'O', 'N', ' '),
    BS_LANGUAGE_POLISH = BSGFX_FOURCC('P', 'L', 'K', ' '),
    BS_LANGUAGE_POLYTONIC_GREEK = BSGFX_FOURCC('P', 'G', 'R', ' '),
    BS_LANGUAGE_PORTUGUESE = BSGFX_FOURCC('P', 'T', 'G', ' '),
    BS_LANGUAGE_PROVENCAL = BSGFX_FOURCC('P', 'R', 'O', ' '),
    BS_LANGUAGE_PUNJABI = BSGFX_FOURCC('P', 'A', 'N', ' '),
    BS_LANGUAGE_QUECHUA = BSGFX_FOURCC('Q', 'U', 'Z', ' '),
    BS_LANGUAGE_QUECHUA_BOLIVIA = BSGFX_FOURCC('Q', 'U', 'H', ' '),
    BS_LANGUAGE_QUECHUA_ECUADOR = BSGFX_FOURCC('Q', 'V', 'I', ' '),
    BS_LANGUAGE_QUECHUA_PERU = BSGFX_FOURCC('Q', 'W', 'H', ' '),
    BS_LANGUAGE_R_CREE = BSGFX_FOURCC('R', 'C', 'R', ' '),
    BS_LANGUAGE_RAJASTHANI = BSGFX_FOURCC('R', 'A', 'J', ' '),
    BS_LANGUAGE_RAKHINE = BSGFX_FOURCC('A', 'R', 'K', ' '),
    BS_LANGUAGE_RAROTONGAN = BSGFX_FOURCC('R', 'A', 'R', ' '),
    BS_LANGUAGE_REJANG = BSGFX_FOURCC('R', 'E', 'J', ' '),
    BS_LANGUAGE_RIANG = BSGFX_FOURCC('R', 'I', 'A', ' '),
    BS_LANGUAGE_RIPUARIAN = BSGFX_FOURCC('K', 'S', 'H', ' '),
    BS_LANGUAGE_RITARUNGO = BSGFX_FOURCC('R', 'I', 'T', ' '),
    BS_LANGUAGE_ROHINGYA = BSGFX_FOURCC('R', 'H', 'G', ' '),
    BS_LANGUAGE_ROMANIAN = BSGFX_FOURCC('R', 'O', 'M', ' '),
    BS_LANGUAGE_ROMANSH = BSGFX_FOURCC('R', 'M', 'S', ' '),
    BS_LANGUAGE_ROMANY = BSGFX_FOURCC('R', 'O', 'Y', ' '),
    BS_LANGUAGE_ROTUMAN = BSGFX_FOURCC('R', 'T', 'M', ' '),
    BS_LANGUAGE_RUNDI = BSGFX_FOURCC('R', 'U', 'N', ' '),
    BS_LANGUAGE_RUSSIAN = BSGFX_FOURCC('R', 'U', 'S', ' '),
    BS_LANGUAGE_RUSSIAN_BURIAT = BSGFX_FOURCC('R', 'B', 'U', ' '),
    BS_LANGUAGE_RUSYN = BSGFX_FOURCC('R', 'S', 'Y', ' '),
    BS_LANGUAGE_SADRI = BSGFX_FOURCC('S', 'A', 'D', ' '),
    BS_LANGUAGE_SAKHA = BSGFX_FOURCC('Y', 'A', 'K', ' '),
    BS_LANGUAGE_SAMOAN = BSGFX_FOURCC('S', 'M', 'O', ' '),
    BS_LANGUAGE_SAMOGITIAN = BSGFX_FOURCC('S', 'G', 'S', ' '),
    BS_LANGUAGE_SAN_BLAS_KUNA = BSGFX_FOURCC('C', 'U', 'K', ' '),
    BS_LANGUAGE_SANGO = BSGFX_FOURCC('S', 'G', 'O', ' '),
    BS_LANGUAGE_SANSKRIT = BSGFX_FOURCC('S', 'A', 'N', ' '),
    BS_LANGUAGE_SANTALI = BSGFX_FOURCC('S', 'A', 'T', ' '),
    BS_LANGUAGE_SARAIKI = BSGFX_FOURCC('S', 'R', 'K', ' '),
    BS_LANGUAGE_SARDINIAN = BSGFX_FOURCC('S', 'R', 'D', ' '),
    BS_LANGUAGE_SASAK = BSGFX_FOURCC('S', 'A', 'S', ' '),
    BS_LANGUAGE_SATERLAND_FRISIAN = BSGFX_FOURCC('S', 'T', 'Q', ' '),
    BS_LANGUAGE_SAYISI = BSGFX_FOURCC('S', 'A', 'Y', ' '),
    BS_LANGUAGE_SCOTS = BSGFX_FOURCC('S', 'C', 'I', ' '),
    BS_LANGUAGE_SCOTTISH_GAELIC = BSGFX_FOURCC('G', 'A', 'E', ' '),
    BS_LANGUAGE_SEKOTA = BSGFX_FOURCC('S', 'E', 'J', ' '),
    BS_LANGUAGE_SELKUP = BSGFX_FOURCC('S', 'E', 'L', ' '),
    BS_LANGUAGE_SENA = BSGFX_FOURCC('S', 'N', 'A', ' '),
    BS_LANGUAGE_SENECA = BSGFX_FOURCC('S', 'E', 'E', ' '),
    BS_LANGUAGE_SERBIAN = BSGFX_FOURCC('S', 'R', 'B', ' '),
    BS_LANGUAGE_SERER = BSGFX_FOURCC('S', 'R', 'R', ' '),
    BS_LANGUAGE_SGAW_KAREN = BSGFX_FOURCC('K', 'S', 'W', ' '),
    BS_LANGUAGE_SHAN = BSGFX_FOURCC('S', 'H', 'N', ' '),
    BS_LANGUAGE_SHONA = BSGFX_FOURCC('S', 'N', 'A', ' '),
    BS_LANGUAGE_SIBE = BSGFX_FOURCC('S', 'I', 'B', ' '),
    BS_LANGUAGE_SICILIAN = BSGFX_FOURCC('S', 'C', 'N', ' '),
    BS_LANGUAGE_SIDAMO = BSGFX_FOURCC('S', 'I', 'D', ' '),
    BS_LANGUAGE_SILESIAN = BSGFX_FOURCC('S', 'Z', 'L', ' '),
    BS_LANGUAGE_SILTE_GURAGE = BSGFX_FOURCC('S', 'I', 'G', ' '),
    BS_LANGUAGE_SINDHI = BSGFX_FOURCC('S', 'N', 'D', ' '),
    BS_LANGUAGE_SINHALA = BSGFX_FOURCC('S', 'N', 'H', ' '),
    BS_LANGUAGE_SKOLT_SAMI = BSGFX_FOURCC('S', 'K', 'S', ' '),
    BS_LANGUAGE_SLAVEY = BSGFX_FOURCC('S', 'L', 'A', ' '),
    BS_LANGUAGE_SLOVAK = BSGFX_FOURCC('S', 'K', 'Y', ' '),
    BS_LANGUAGE_SLOVENIAN = BSGFX_FOURCC('S', 'L', 'V', ' '),
    BS_LANGUAGE_SMALL_FLOWERY_MIAO = BSGFX_FOURCC('S', 'F', 'M', ' '),
    BS_LANGUAGE_SODO_GURAGE = BSGFX_FOURCC('S', 'O', 'G', ' '),
    BS_LANGUAGE_SOGA = BSGFX_FOURCC('X', 'O', 'G', ' '),
    BS_LANGUAGE_SOMALI = BSGFX_FOURCC('S', 'M', 'L', ' '),
    BS_LANGUAGE_SONGE = BSGFX_FOURCC('S', 'O', 'P', ' '),
    BS_LANGUAGE_SONINKE = BSGFX_FOURCC('S', 'N', 'K', ' '),
    BS_LANGUAGE_SOUTH_SLAVEY = BSGFX_FOURCC('S', 'S', 'L', ' '),
    BS_LANGUAGE_SOUTHERN_KIWAI = BSGFX_FOURCC('K', 'J', 'D', ' '),
    BS_LANGUAGE_SOUTHERN_SAMI = BSGFX_FOURCC('S', 'S', 'M', ' '),
    BS_LANGUAGE_SOUTHERN_SOTHO = BSGFX_FOURCC('S', 'O', 'T', ' '),
    BS_LANGUAGE_SPANISH = BSGFX_FOURCC('E', 'S', 'P', ' '),
    BS_LANGUAGE_STANDARD_MOROCCAN_TAMAZIGHT = BSGFX_FOURCC('Z', 'G', 'H', ' '),
    BS_LANGUAGE_STRAITS_SALISH = BSGFX_FOURCC('S', 'T', 'R', ' '),
    BS_LANGUAGE_SUKUMA = BSGFX_FOURCC('S', 'U', 'K', ' '),
    BS_LANGUAGE_SUNDANESE = BSGFX_FOURCC('S', 'U', 'N', ' '),
    BS_LANGUAGE_SURI = BSGFX_FOURCC('S', 'U', 'R', ' '),
    BS_LANGUAGE_SUTU = BSGFX_FOURCC('S', 'X', 'T', ' '),
    BS_LANGUAGE_SVAN = BSGFX_FOURCC('S', 'V', 'A', ' '),
    BS_LANGUAGE_SWADAYA_ARAMAIC = BSGFX_FOURCC('S', 'W', 'A', ' '),
    BS_LANGUAGE_SWAHILI = BSGFX_FOURCC('S', 'W', 'K', ' '),
    BS_LANGUAGE_SWATI = BSGFX_FOURCC('S', 'W', 'Z', ' '),
    BS_LANGUAGE_SWEDISH = BSGFX_FOURCC('S', 'V', 'E', ' '),
    BS_LANGUAGE_SYLHETI = BSGFX_FOURCC('S', 'Y', 'L', ' '),
    BS_LANGUAGE_SYRIAC = BSGFX_FOURCC('S', 'Y', 'R', ' '),
    BS_LANGUAGE_SYRIAC_EASTERN = BSGFX_FOURCC('S', 'Y', 'R', 'N'),
    BS_LANGUAGE_SYRIAC_ESTRANGELA = BSGFX_FOURCC('S', 'Y', 'R', 'E'),
    BS_LANGUAGE_SYRIAC_WESTERN = BSGFX_FOURCC('S', 'Y', 'R', 'J'),
    BS_LANGUAGE_TABASARAN = BSGFX_FOURCC('T', 'A', 'B', ' '),
    BS_LANGUAGE_TACHELHIT = BSGFX_FOURCC('S', 'H', 'I', ' '),
    BS_LANGUAGE_TAGALOG = BSGFX_FOURCC('T', 'G', 'L', ' '),
    BS_LANGUAGE_TAHAGGART_TAMAHAQ = BSGFX_FOURCC('T', 'H', 'V', ' '),
    BS_LANGUAGE_TAHITIAN = BSGFX_FOURCC('T', 'H', 'T', ' '),
    BS_LANGUAGE_TAI_LAING = BSGFX_FOURCC('T', 'J', 'L', ' '),
    BS_LANGUAGE_TAJIKI = BSGFX_FOURCC('T', 'A', 'J', ' '),
    BS_LANGUAGE_TALYSH = BSGFX_FOURCC('T', 'L', 'Y', ' '),
    BS_LANGUAGE_TAMASHEK = BSGFX_FOURCC('T', 'M', 'H', ' '),
    BS_LANGUAGE_TAMASHEQ = BSGFX_FOURCC('T', 'A', 'Q', ' '),
    BS_LANGUAGE_TAMAZIGHT = BSGFX_FOURCC('T', 'Z', 'M', ' '),
    BS_LANGUAGE_TAMIL = BSGFX_FOURCC('T', 'A', 'M', ' '),
    BS_LANGUAGE_TARIFIT = BSGFX_FOURCC('R', 'I', 'F', ' '),
    BS_LANGUAGE_TATAR = BSGFX_FOURCC('T', 'A', 'T', ' '),
    BS_LANGUAGE_TAWALLAMMAT_TAMAJAQ = BSGFX_FOURCC('T', 'T', 'Q', ' '),
    BS_LANGUAGE_TAY = BSGFX_FOURCC('T', 'Y', 'Z', ' '),
    BS_LANGUAGE_TAYART_TAMAJEQ = BSGFX_FOURCC('T', 'H', 'Z', ' '),
    BS_LANGUAGE_TELUGU = BSGFX_FOURCC('T', 'E', 'L', ' '),
    BS_LANGUAGE_TEMNE = BSGFX_FOURCC('T', 'M', 'N', ' '),
    BS_LANGUAGE_TETUM = BSGFX_FOURCC('T', 'E', 'T', ' '),
    BS_LANGUAGE_TH_CREE = BSGFX_FOURCC('T', 'C', 'R', ' '),
    BS_LANGUAGE_THAI = BSGFX_FOURCC('T', 'H', 'A', ' '),
    BS_LANGUAGE_THAILAND_MON = BSGFX_FOURCC('M', 'O', 'N', 'T'),
    BS_LANGUAGE_THOMPSON = BSGFX_FOURCC('T', 'H', 'P', ' '),
    BS_LANGUAGE_TIBETAN = BSGFX_FOURCC('T', 'I', 'B', ' '),
    BS_LANGUAGE_TIGRE = BSGFX_FOURCC('T', 'G', 'R', ' '),
    BS_LANGUAGE_TIGRINYA = BSGFX_FOURCC('T', 'G', 'Y', ' '),
    BS_LANGUAGE_TIV = BSGFX_FOURCC('T', 'I', 'V', ' '),
    BS_LANGUAGE_TLINGIT = BSGFX_FOURCC('T', 'L', 'I', ' '),
    BS_LANGUAGE_TOBO = BSGFX_FOURCC('T', 'B', 'V', ' '),
    BS_LANGUAGE_TODO = BSGFX_FOURCC('T', 'O', 'D', ' '),
    BS_LANGUAGE_TOK_PISIN = BSGFX_FOURCC('T', 'P', 'I', ' '),
    BS_LANGUAGE_TOMA = BSGFX_FOURCC('T', 'O', 'D', '0'),
    BS_LANGUAGE_TONGA = BSGFX_FOURCC('T', 'N', 'G', ' '),
    BS_LANGUAGE_TONGAN = BSGFX_FOURCC('T', 'G', 'N', ' '),
    BS_LANGUAGE_TORKI = BSGFX_FOURCC('A', 'Z', 'B', ' '),
    BS_LANGUAGE_TSHANGLA = BSGFX_FOURCC('T', 'S', 'J', ' '),
    BS_LANGUAGE_TSONGA = BSGFX_FOURCC('T', 'S', 'G', ' '),
    BS_LANGUAGE_TSWANA = BSGFX_FOURCC('T', 'N', 'A', ' '),
    BS_LANGUAGE_TULU = BSGFX_FOURCC('T', 'U', 'L', ' '),
    BS_LANGUAGE_TUMBUKA = BSGFX_FOURCC('T', 'U', 'M', ' '),
    BS_LANGUAGE_TUNDRA_ENETS = BSGFX_FOURCC('T', 'N', 'E', ' '),
    BS_LANGUAGE_TURKISH = BSGFX_FOURCC('T', 'R', 'K', ' '),
    BS_LANGUAGE_TURKMEN = BSGFX_FOURCC('T', 'K', 'M', ' '),
    BS_LANGUAGE_TUROYO_ARAMAIC = BSGFX_FOURCC('T', 'U', 'A', ' '),
    BS_LANGUAGE_TUSCARORA = BSGFX_FOURCC('T', 'U', 'S', ' '),
    BS_LANGUAGE_TUVALU = BSGFX_FOURCC('T', 'V', 'L', ' '),
    BS_LANGUAGE_TUVIN = BSGFX_FOURCC('T', 'U', 'V', ' '),
    BS_LANGUAGE_TWI = BSGFX_FOURCC('T', 'W', 'I', ' '),
    BS_LANGUAGE_TZOTZIL = BSGFX_FOURCC('T', 'Z', 'O', ' '),
    BS_LANGUAGE_UDI = BSGFX_FOURCC('U', 'D', 'I', ' '),
    BS_LANGUAGE_UDMURT = BSGFX_FOURCC('U', 'D', 'M', ' '),
    BS_LANGUAGE_UKRAINIAN = BSGFX_FOURCC('U', 'K', 'R', ' '),
    BS_LANGUAGE_UMBUNDU = BSGFX_FOURCC('U', 'M', 'B', ' '),
    BS_LANGUAGE_UME_SAMI = BSGFX_FOURCC('S', 'J', 'U', ' '),
    BS_LANGUAGE_UPPER_SAXON = BSGFX_FOURCC('S', 'X', 'U', ' '),
    BS_LANGUAGE_UPPER_SORBIAN = BSGFX_FOURCC('U', 'S', 'B', ' '),
    BS_LANGUAGE_URALIC_PHONETIC = BSGFX_FOURCC('U', 'P', 'P', ' '),
    BS_LANGUAGE_URDU = BSGFX_FOURCC('U', 'R', 'D', ' '),
    BS_LANGUAGE_UYGHUR = BSGFX_FOURCC('U', 'Y', 'G', ' '),
    BS_LANGUAGE_UZBEK = BSGFX_FOURCC('U', 'Z', 'B', ' '),
    BS_LANGUAGE_VENDA = BSGFX_FOURCC('V', 'E', 'N', ' '),
    BS_LANGUAGE_VENETIAN = BSGFX_FOURCC('V', 'E', 'C', ' '),
    BS_LANGUAGE_VIETNAMESE = BSGFX_FOURCC('V', 'I', 'T', ' '),
    BS_LANGUAGE_VLAX_ROMANI = BSGFX_FOURCC('R', 'M', 'Y', ' '),
    BS_LANGUAGE_VOLAPUK = BSGFX_FOURCC('V', 'O', 'L', ' '),
    BS_LANGUAGE_VORO = BSGFX_FOURCC('V', 'R', 'O', ' '),
    BS_LANGUAGE_WA = BSGFX_FOURCC('W', 'A', ' ', ' '),
    BS_LANGUAGE_WACI_GBE = BSGFX_FOURCC('W', 'C', 'I', ' '),
    BS_LANGUAGE_WAGDI = BSGFX_FOURCC('W', 'A', 'G', ' '),
    BS_LANGUAGE_WAKHI = BSGFX_FOURCC('W', 'B', 'L', ' '),
    BS_LANGUAGE_WALLOON = BSGFX_FOURCC('W', 'L', 'N', ' '),
    BS_LANGUAGE_WARAY_WARAY = BSGFX_FOURCC('W', 'A', 'R', ' '),
    BS_LANGUAGE_WAYANAD_CHETTI = BSGFX_FOURCC('C', 'T', 'T', ' '),
    BS_LANGUAGE_WAYUU = BSGFX_FOURCC('G', 'U', 'C', ' '),
    BS_LANGUAGE_WELSH = BSGFX_FOURCC('W', 'E', 'L', ' '),
    BS_LANGUAGE_WENDAT = BSGFX_FOURCC('W', 'D', 'T', ' '),
    BS_LANGUAGE_WEST_CREE = BSGFX_FOURCC('W', 'C', 'R', ' '),
    BS_LANGUAGE_WESTERN_CHAM = BSGFX_FOURCC('C', 'J', 'A', ' '),
    BS_LANGUAGE_WESTERN_KAYAH = BSGFX_FOURCC('K', 'Y', 'U', ' '),
    BS_LANGUAGE_WESTERN_PANJABI = BSGFX_FOURCC('P', 'N', 'B', ' '),
    BS_LANGUAGE_WESTERN_PWO_KAREN = BSGFX_FOURCC('P', 'W', 'O', ' '),
    BS_LANGUAGE_WOLOF = BSGFX_FOURCC('W', 'L', 'F', ' '),
    BS_LANGUAGE_WOODS_CREE = BSGFX_FOURCC('D', 'C', 'R', ' '),
    BS_LANGUAGE_WUDING_LUQUAN_YI = BSGFX_FOURCC('Y', 'W', 'Q', ' '),
    BS_LANGUAGE_WYANDOT = BSGFX_FOURCC('W', 'Y', 'N', ' '),
    BS_LANGUAGE_XHOSA = BSGFX_FOURCC('X', 'H', 'S', ' '),
    BS_LANGUAGE_Y_CREE = BSGFX_FOURCC('Y', 'C', 'R', ' '),
    BS_LANGUAGE_YAO = BSGFX_FOURCC('Y', 'A', 'O', ' '),
    BS_LANGUAGE_YAPESE = BSGFX_FOURCC('Y', 'A', 'P', ' '),
    BS_LANGUAGE_YI_CLASSIC = BSGFX_FOURCC('Y', 'I', 'C', ' '),
    BS_LANGUAGE_YI_MODERN = BSGFX_FOURCC('Y', 'I', 'M', ' '),
    BS_LANGUAGE_YIDDISH = BSGFX_FOURCC('J', 'I', 'I', ' '),
    BS_LANGUAGE_YORUBA = BSGFX_FOURCC('Y', 'B', 'A', ' '),
    BS_LANGUAGE_ZAMBOANGA_CHAVACANO = BSGFX_FOURCC('C', 'B', 'K', ' '),
    BS_LANGUAGE_ZANDE = BSGFX_FOURCC('Z', 'N', 'D', ' '),
    BS_LANGUAGE_ZARMA = BSGFX_FOURCC('D', 'J', 'R', ' '),
    BS_LANGUAGE_ZAZAKI = BSGFX_FOURCC('Z', 'Z', 'A', ' '),
    BS_LANGUAGE_ZEALANDIC = BSGFX_FOURCC('Z', 'E', 'A', ' '),
    BS_LANGUAGE_ZHUANG = BSGFX_FOURCC('Z', 'H', 'A', ' '),
    BS_LANGUAGE_ZULU = BSGFX_FOURCC('Z', 'U', 'L', ' '),
};

struct bsgfx_UIElement {
    bs_vec2 size;
    bs_vec3 position;
};

struct bsgfx_UIIcon {
    bs_vec2 size;
    bs_vec3 position;
    float align_height;
    bsgfx_AtlasCache* cache;
    bsgfx_InstanceSubtype* subtype;
    int material_id;
    bool flip;
    bool mirror;
};

struct bsgfx_UISolid {
    bs_vec2 size;
    bs_vec3 position;
    float align_height;
    int material_id;
};

struct bsgfx_UIText {
    bs_vec3 position;
    float align_height;
    int px_size;
    bsgfx_Font* font;
    struct {
        char* as_ascii;
    };
};

struct bsgfx_Text {
    bs_vec4 position;
    float scale;
    float max_length;
    bs_U32 flags;
    int select_start, select_end;
    int material_id;
    bs_RGBA colors[8];
};

struct bsgfx_MeshInstance {
    bs_mat4 transform;
};

struct bsgfx_BoneInstance {
    bs_mat4 transform;
};

struct bsgfx_QuadInstance {
    bs_mat4x3 transform;
    bs_vec2 coords;
    bs_vec2 offset;
};

struct bsgfx_PointInstance {
    bs_vec3 coord;
    float size;
    bs_vec4 color;
};

struct bsgfx_LineInstance {
    bs_vec4 start;
    bs_vec4 end;
    bs_vec4 color;
};

struct bsgfx_Scene {
    const char* name;
    bs_U64 name_hash;
};

struct bsgfx_Material {
    bs_U64 hash;
    char* name;
    bsgfx_MaterialCategory category;
    bool highlighted, auto_unhighlight;
    bool editable;
    int id;
    int json_index;
    bsgfx_MaterialContract* contract;
};

struct bsgfx_Collider {
    bsgfx_ColliderFlags collision;
    bs_U32 batch_offset;
    bs_vec3 velocity_old;
    bs_vec3 normal;
    float angle;
    float angle_old;
    float length;
    float sweep_radius;
    bs_ivec3 resolution;
    bs_vec3 scale;
    bs_Aabb aabb;
    bool active;
};

struct bsgfx_SweepCollision {
    bs_vec3 position;
    bs_vec4 rotation;
    bs_vec3 scale;
    bs_U32 flags;
};

struct bsgfx_Animator {
    float time;
    float previous_time;
    float blend_factor;
    int queued_animation_id;
    int current_animation_id;
    int current_blend_animation_id;
    bs_Armature* armature;
    bs_U32 skeleton;
    bs_Animation* animations;
    int animations_count;
    void (*exit)();
};

struct bsgfx_AnimatorCallbacks {
    du_animatorCallback(once) ;
    du_animatorCallback(once_per_tick) ;
    du_animatorCallback(once_per_loop) ;
    du_animatorCallback(once_per_exit) ;
    du_animatorCallback(pose) ;
};

struct bsgfx_Settings {
    bool cull_backfaces;
    float master_volume;
    bool music;
};

struct bsgfx_Callbacks {
    PFN_void tick;
    PFN_void fixedTick;
    PFN_void render;
    PFN_void loadScene;
    PFN_bsgfx_onQueue queue;
    PFN_void pipeline;
};

struct bsgfx_Application {
    const char* name;
    struct {
        bs_mat4 proj;
        bs_mat4 view;
        bs_mat4 result;
    } camera;
    struct {
        bs_mat4 proj;
        bs_mat4 view;
        bs_mat4 result;
        bs_vec2 position;
    } world_camera;
    struct {
        bs_mat4 result;
    } screen_camera;
    bs_List sweep_collisions;
    int joint_offset;
};

struct bsgfx_TypeHeader {
    bs_U32 magic;
    bs_U32 version;
    int flexible_count;
    int count;
    int accessors[];
};

struct bsgfx_InstanceType {
    int tick_count;
    int instance_count;
    int instance_size;
    bs_List subtypes;
    bs_Buffer* device_instances;
};

struct bsgfx_InstanceSubtype {
    int index_offset;
    int index_count;
    int instance_offset;
    int batch_source_id;
    int batch_id;
    uint flags;
    bsgfx_InstanceType* instance_type2;
    bs_List host_instances;
};

struct bsgfx_Type {
    int version;
    int capacity;
    int flexible_capacity;
    int count;
    int flexible_count;
    int package_id;
    const char* plural;
    const char* singular;
    PFN_bsgfx_TypeMapper mapper;
    int* unmapped_accessors;
    int* mapped_accessors;
    unsigned char* mapped;
    unsigned char* unmapped;
    int mapped_unit_size;
    int unmapped_unit_size;
    int unmapped_flexible_offset;
    int mapped_flexible_offset;
    int unmapped_flexible_size;
    int mapped_flexible_size;
};

struct bsgfx_Foliage {
    bs_GUID guid;
    int density;
    int textures_count;
    struct bsgfx_FoliageTexture {
        bs_vec4 coords;
        bs_vec2 size;
        int id;
        bs_RGBA color;
    } textures[];
};

struct bsgfx_RawFoliage {
    bs_GUID guid;
    int density;
    int textures_count;
    struct bsgfx_RawFoliageTexture {
        bs_U64 texture_hash;
        bs_RGBA color;
        int reserved;
    } textures[];
};

struct bsgfx_Light {
    bs_vec3 position;
    bs_vec3 direction;
    bsgfx_LightType type;
};

struct bsgfx_RawLight {
    bs_vec3 position;
    bs_vec3 rotation;
    bsgfx_LightType type;
    int reserved_a;
    int reserved_b;
    int reserved_c;
    int reserved_d;
    int reserved_e;
};

struct bsgfx_PrefabMetadata {
    int variety_count;
    struct bsgfx_PrefabVariety {
        int texture_id;
    }*varieties;
};

struct bsgfx_Prefab {
    bs_vec3 position;
    bs_vec4 rotation;
    bs_vec3 scale;
    int mesh_id;
    int material_id;
    int texture_id;
    int z_order;
    bs_U32 flags;
    int shadow_subtype;
    bs_GUID guid;
};

struct bsgfx_RawPrefab {
    bs_vec3 position;
    bs_vec3 rotation;
    bs_vec3 scale;
    bs_U32 flags;
    bs_U64 name_hash;
    bs_U64 material_hash;
    bs_U64 texture_hash;
    bs_GUID guid;
    int z_order;
    int reserved;
};

struct bsgfx_Primitive {
    bs_vec3 position;
    bs_vec4 rotation;
    bs_vec3 scale;
    int first_tile, last_tile;
    bs_U32 collision;
    bsgfx_PrimitiveFlags flags;
    bsgfx_PrimitiveType type;
    int subtype_index;
    bs_GUID guid;
};

struct bsgfx_RawPrimitive {
    bs_vec3 position;
    bs_vec3 scale;
    bs_vec3 rotation;
    bs_U32 collision;
    bsgfx_PrimitiveFlags flags;
    bsgfx_PrimitiveType type;
    bs_GUID guid;
};

struct bsgfx_TileAxis {
    bs_vec3 normal;
    bs_vec3 right;
    bs_vec3 up;
    bs_vec3 start_sign;
    int width_axis;
    int height_axis;
};

struct bsgfx_Spawner {
    bs_vec3 position;
    bsgfx_SpawnerType spawn_type;
    bs_U64 spawn_name;
    bsgfx_SpawnerFlags flags;
    float spawn_periodicity;
    int material_id;
    int reserved;
};

struct bsgfx_RawSpawner {
    bs_vec3 position;
    bsgfx_SpawnerType spawn_type;
    bs_U64 spawn_name;
    bsgfx_SpawnerFlags flags;
    float spawn_periodicity;
    bs_U64 material_name;
};

struct bsgfx_Tile {
    bs_ivec2 coords;
    bs_U32 axis;
    int index;
    int image_index;
    bs_U32 flags;
    int material;
};

struct bsgfx_RawTile {
    bs_ivec2 coords;
    bs_U32 axis;
    bs_U32 flags;
    bs_U64 texture_hash;
    bs_GUID primitive;
};

struct bsgfx_TileType {
    int id;
};

struct bsgfx_RawTileV1 {
    bs_vec2 coords;
    bs_U32 flags;
    bs_U64 texture_hash;
    bs_GUID primitive;
};

struct bsgfx_ForeachVisibleRowParams {
    bsgfx_Widget* widget;
    bs_vec3* position;
    int id;
};

struct bsgfx_ButtonParams {
    bsgfx_Menu* menu;
    bsgfx_Widget* widget;
    bs_vec3 widget_position;
    bool hovering;
};

struct bsgfx_TableField {
    const char* name;
    int count;
    enum  {
        BSGFX_TABLE_FIELD_INTEGER,
        BSGFX_TABLE_FIELD_FLOAT,
    } type;
};

struct bsgfx_Scrollbar {
    int* value;
    float width;
    float border_radius;
    int substeps_count;
    int padding;
    int material;
    int outline_material;
    int background_material;
    int button_icon_material;
    int button_outline_material;
    int button_background_material;
};

struct bsgfx_GridParams {
    bs_vec2 start;
    bs_vec2* position;
    int index;
};

struct bsgfx_Glyph {
    bs_U32 flags;
    int atlas_page;
    int atlas_index;
    int glyph_index;
    int x_advance;
    int y_advance;
    int x_offset;
    int y_offset;
    bs_U16 kerning_pair_start;
    bs_U16 kerning_pair_count;
};

struct bsgfx_UnicodeBlock2 {
    bs_U32 offset;
    bs_U16 count;
    bs_U16 reserved;
    bs_U32 glyphs_offset;
};

struct bsgfx_KerningPair {
    bs_U16 right;
    bs_I16 left_x_placement;
    bs_I16 left_y_placement;
    bs_I16 left_x_advance;
    bs_I16 left_y_advance;
    bs_I16 right_x_placement;
    bs_I16 right_y_placement;
    bs_I16 right_x_advance;
    bs_I16 right_y_advance;
};

struct bsgfx_Font {
    int blocks_count;
    int pt_sizes_count;
    int glyphs_count;
    int kerning_pairs_count;
    int du_height;
    bs_U16 units_per_em;
    bs_Object* atlas_object;
    bsgfx_UnicodeBlock2* blocks;
    bsgfx_Glyph* glyphs;
    int* pt_sizes;
    bsgfx_KerningPair* kerning_pairs;
    struct {
        void* unused;
    }_[];
};

struct bsgfx_Widget {
    int indent;
    int id;
    int material_id;
    const char* hint;
    bsgfx_WidgetType type;
    bool disabled;
    bsgfx_WidgetAdvanceType advance_flags;
    void* params;
    bs_vec3 offset;
    float align_height;
    bsgfx_Font* font;
    union {
        struct {
            char* value;
            int px_size;
            void (*on_hover)(struct bsgfx_Widget*);
        } string;
        struct {
            bsgfx_InputType type;
            bool active;
            bool new_line_on_enter;
            const char* placeholder_text;
            int placeholder_text_material_id;
            int outline_material_id;
            int background_outline_material_id;
            int background_shadow_material_id;
            bs_vec2 dimensions;
            bs_U64 hash;
            int* select_position;
            int* select_size;
            union {
                double* as_double;
                float* as_float;
                long long* as_long;
                unsigned long long* as_ulong;
                int* as_int;
                int* as_uint;
                char* as_char;
                unsigned char* as_uchar;
                bs_String** as_string;
                void* as_void;
            };
        } input;
        struct {
            bool always_active;
            int selected;
            int count;
            bs_vec2 size;
            bs_vec2 total_size;
            float padding;
            bool (*action)(bsgfx_Widget*, bsgfx_GridParams);
            bsgfx_Scrollbar scrollbar;
        } grid;
        struct {
            char* path;
        } url;
        struct {
            int material;
            int selected_material;
            bs_vec2 size;
            PFN_bsgfx_ButtonWidgetCallback tick;
            struct {
                int* active_index;
                int this_index;
            } active_override;
            const char* name;
            const char* hint;
            enum  {
                BSGFX_BUTTON_ALIGN_CENTER,
                BSGFX_BUTTON_ALIGN_LEFT,
            } alignment;
        } button;
        struct {
            int* value;
            int min, max;
            void (*on_change)(struct bsgfx_Widget*);
        } range;
        struct {
            float* value;
            float min, max;
            float width;
            bool integer;
        } slider;
        struct {
            enum  {
                BSGFX_ICON_ATLAS,
                BSGFX_ICON_TILE,
                BSGFX_ICON_MATERIAL,
                BSGFX_ICON_64,
                BSGFX_ICON_256,
                BSGFX_ICON_512,
            } type;
            bs_vec2 scale;
            const char* name;
            const char* background_name;
            const char* background_selected_name;
            int frame;
            void (*hover)(struct bsgfx_Widget*);
            int material_id;
            float border_radius;
            int outline_material_id;
            bs_Atlas* atlas;
            bsgfx_InstanceSubtype* atlas_subtype;
            bool flipped;
            bool mirrored;
        } icon;
        struct {
            bs_vec4* hsva;
            bs_vec2 dimensions;
            float hue_width;
            float border_radius;
            int padding;
            int material_id;
            int background_material_id;
            int shadow_material_id;
            int outline_material_id;
            void (*on_change_color)(struct bsgfx_Widget*, bs_RGBA);
        } color;
        struct {
            int max;
            int vk_offset;
            int count;
            int* scroll;
            char* (*foreach_visible_row)(bsgfx_ForeachVisibleRowParams params);
        } list;
        struct {
            const char* name;
            const char* mesh_name;
            void (*instance)(const bs_mat4* transform);
        } model;
        struct {
            const bs_List* fields;
            unsigned char* data;
            int count, unit_size;
            int max_count;
        } table;
        struct {
            bs_vec2 size;
            float border_radius;
            bsgfx_InstanceSubtype* subtype;
            int material_id;
            int outline_material_id;
            int shadow_material_id;
        } background;
    };
};

struct bsgfx_AtlasCache {
    const char* name;
    int id;
    bs_vec4 coords;
    bs_vec2 size;
};

struct bsgfx_MenuTab {
    const char* name;
    bs_U64 hash;
    bsgfx_AtlasCache* icon_cache;
    int icon_material_id;
    int material_id;
    int outline_material_id;
    int shadow_material_id;
};

struct bsgfx_MenuTabBar {
    bsgfx_MenuTab* tabs;
    int* active_tab;
    int tabs_count;
    float height;
    int material_id;
    int outline_material_id;
    int shadow_material_id;
};

struct bsgfx_Menu {
    bs_vec3 position;
    bsgfx_Widget* widgets;
    int widgets_count;
    float spacing;
    bool blocked;
    int background_material_id_0;
    int background_material_id_1;
    struct {
        bs_vec2 dimensions;
        int border_id;
        bool auto_scale_width;
    } untextured;
    bsgfx_Font* font;
    float border_radius;
    int shadow_material_id;
    int outline_material_id;
    bsgfx_InstanceSubtype* text_subtype;
};

struct bsgfx_TitleBar {
    const char* name;
    bsgfx_Font* font;
    int material_id;
    int button_unavailable_material_id;
    int button_material_id;
    int button_hovering_material_id;
    int button_icon_material_id;
    int button_shadow_material_id;
    int button_selected_shadow_material_id;
    void (*on_close)();
    void (*on_maximize)();
    void (*on_minimize)();
    float border_radius;
};

 /**
  @return void
  */
BSGFXAPI void
bsgfx_enableValidation();

 /**
  @return void
  */
BSGFXAPI void
bsgfx_disableValidation();

 /**
  @return void
  */
BSGFXAPI void
bsgfx_test();

 /**
  @return bsgfx_InstanceSubtype**
  */
BSGFXAPI bsgfx_InstanceSubtype**
bsgfx_subtypes();

 /**
  @return bsgfx_InstanceType**
  */
BSGFXAPI bsgfx_InstanceType**
bsgfx_instanceTypes();

 /**
  @param font
  @param out
  @param name
  @param length
  @return void
  */
BSGFXAPI void
bsgfx_textDimensions(
    bsgfx_Font* font,
    bs_vec2* out,
    char* name,
    int length);

 /**
  @return bs_PipelineHash
  */
BSGFXAPI bs_PipelineHash
bsgfx_defaultPipelineHash();

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderTileIcons(
    bs_RendererScope* scope,
    bs_Queue* queue);

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderAtlasIcons(
    bs_RendererScope* scope,
    bs_Queue* queue);

 /**
  @param scope
  @param queue
  @param camera
  @param subtype
  @param skip_depth_test
  @return void
  */
BSGFXAPI void
bsgfx_renderLineModel(
    bs_RendererScope* scope,
    bs_Queue* queue,
    const bs_mat4* camera,
    bsgfx_InstanceSubtype* subtype,
    bool skip_depth_test);

 /**
  @param scope
  @param queue
  @param camera
  @param subtype
  @param skip_depth_test
  @return void
  */
BSGFXAPI void
bsgfx_renderLines(
    bs_RendererScope* scope,
    bs_Queue* queue,
    const bs_mat4* camera,
    bsgfx_InstanceSubtype* subtype,
    bool skip_depth_test);

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderPoints(
    bs_RendererScope* scope,
    bs_Queue* queue);

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderAtlas(
    bs_RendererScope* scope,
    bs_Queue* queue);

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderPrimitiveTiles(
    bs_RendererScope* scope,
    bs_Queue* queue);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_swapBufferBindings();

 /**
  @param inout
  @return void
  */
BSGFXAPI void
bsgfx_requiredForShadowVolumes(
    bs_PipelineHash* inout);

 /**
  @param inout
  @return void
  */
BSGFXAPI void
bsgfx_requiredForStencilShadows(
    bs_PipelineHash* inout);

 /**
  @param inout
  @return void
  */
BSGFXAPI void
bsgfx_requiredForTransparency(
    bs_PipelineHash* inout);

 /**
  @return bsgfx_Scene*
  */
BSGFXAPI bsgfx_Scene*
bsgfx_currentScene();

 /**
  @param name
  @return void
  */
BSGFXAPI void
bsgfx_loadScene(
    const char* name);

 /**
  @param library_name
  @param subtype
  @return bool
  */
BSGFXAPI bool
bsgfx_validateSubtype(
    const char* library_name,
    bsgfx_InstanceSubtype* subtype);

 /**
  @param library_name
  @param instance_type
  @return bool
  */
BSGFXAPI bool
bsgfx_validateInstanceType(
    const char* library_name,
    bsgfx_InstanceType* instance_type);

 /**
  @param position
  @param camera
  @param resolution
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_worldToScreen(
    const bs_vec3* position,
    const bs_mat4* camera,
    const bs_vec2* resolution,
    bs_vec2* out);

 /**
  @param category
  @return const char*
  */
BSGFXAPI const char*
bsgfx_materialCategoryName(
    bsgfx_MaterialCategory category);

 /**
  @return bs_List*
  */
BSGFXAPI bs_List*
bsgfx_materials();

 /**
  @param hash
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_queryMaterialHash(
    bs_U64 hash);

 /**
  @param id
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_fetchMaterial(
    int id);

 /**
  @param name
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_queryMaterial(
    const char* name);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_loadMaterials();

 /**
  @param name
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_material(
    char* name);

 /**
  @param name
  @param name_length
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_materialN(
    char* name,
    int name_length);

 /**
  @param format
  @param args
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_materialV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_materialF(
    char* format,
     ...);

 /**
  @param material_id
  @param auto_unhighlight
  @return void
  */
BSGFXAPI void
bsgfx_highlightMaterial(
    int material_id,
    bool auto_unhighlight);

 /**
  @param material_id
  @return void
  */
BSGFXAPI void
bsgfx_unhighlightMaterial(
    int material_id);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_tickMaterials();

 /**
  @param sweep_radius
  @param position
  @return void
  */
BSGFXAPI void
bsgfx_sweepCollisions(
    float sweep_radius,
    const bs_vec3* position);

 /**
  @param aabb
  @param scale
  @param resolution
  @param sweep_radius
  @return bsgfx_Collider
  */
BSGFXAPI bsgfx_Collider
bsgfx_collider(
    bs_Aabb aabb,
    bs_vec3 scale,
    bs_ivec3 resolution,
    float sweep_radius);

 /**
  @param collider
  @param position
  @param velocity
  @return void
  */
BSGFXAPI void
bsgfx_applyCollisions(
    bsgfx_Collider* collider,
    const bs_vec3* position,
    bs_vec3* velocity);

 /**
  @param collider
  @return void
  */
BSGFXAPI void
bsgfx_printCollisions(
    bsgfx_Collider* collider);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_instanceSweepCollisions();

 /**
  @param collider
  @param position
  @param velocity
  @return void
  */
BSGFXAPI void
bsgfx_instanceCollider(
    bsgfx_Collider* collider,
    const bs_vec3* position,
    bs_vec3* velocity);

 /**
  @param armature
  @return int
  */
BSGFXAPI int
bsgfx_skeleton(
    bs_Armature* armature);

 /**
  @param animation
  @param time
  @param num_frames
  @return int
  */
BSGFXAPI int
bsgfx_animationFrame(
    bs_Animation* animation,
    float time,
    int num_frames);

 /**
  @param animation
  @param time_scale
  @return int
  */
BSGFXAPI int
bsgfx_animationFrameCount(
    bs_Animation* animation,
    float time_scale);

 /**
  @param animator
  @param velocity
  @param input
  @return void
  */
BSGFXAPI void
bsgfx_applyAnimationVelocity(
    bsgfx_Animator* animator,
    bs_vec3* velocity,
    bs_vec2 input);

 /**
  @param animator
  @param animation_id
  @return void
  */
BSGFXAPI void
bsgfx_queueAnimation(
    bsgfx_Animator* animator,
    int animation_id);

 /**
  @param animator
  @param callbacks
  @return void
  */
BSGFXAPI void
bsgfx_runAnimator(
    bsgfx_Animator* animator,
    bsgfx_AnimatorCallbacks callbacks);

 /**
  @param armature
  @param resting_animation_id
  @param animations_count
  @return bsgfx_Animator
  */
BSGFXAPI bsgfx_Animator
bsgfx_animator(
    bs_Armature* armature,
    int resting_animation_id,
    int animations_count);

 /**
  @param instance_type
  @param instances_count
  @param overhead_count
  @return bs_Result
  */
BSGFXAPI bs_Result
bsgfx_ensureInstanceCount(
    bsgfx_InstanceType* instance_type,
    bs_U32 instances_count,
    bs_U32 overhead_count);

 /**
  @param instance_size
  @param bind_set
  @param binding
  @param out
  @return bs_Result
  */
BSGFXAPI bs_Result
bsgfx_instanceType(
    size_t instance_size,
    int bind_set,
    int binding,
    bsgfx_InstanceType** out);

 /**
  @param instance_subtype
  @return void
  */
BSGFXAPI void
bsgfx_deleteSubtype(
    bsgfx_InstanceSubtype* instance_subtype);

 /**
  @param instance_type
  @param batch
  @param flags
  @param range
  @param out
  @return bs_Result
  */
BSGFXAPI bs_Result
bsgfx_subtype(
    bsgfx_InstanceType* instance_type,
    bs_Batch* batch,
    bs_U32 flags,
    bs_Range range,
    bsgfx_InstanceSubtype** out);

 /**
  @param instance_subtype
  @param data
  @param data_size
  @param flags
  @param bone_index
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instantiate(
    bsgfx_InstanceSubtype* instance_subtype,
    const char* data,
    int data_size,
    bs_U32 flags,
    unsigned int bone_index,
    int id,
    int material);

 /**
  @param instance_type
  @return void
  */
BSGFXAPI void
bsgfx_tickInstanceType(
    bsgfx_InstanceType* instance_type);

 /**
  @param queue
  @param instance_subtype
  @param pipeline
  @return void
  */
BSGFXAPI void
bsgfx_renderSubtype(
    bs_Queue* queue,
    bsgfx_InstanceSubtype* instance_subtype,
    bs_Pipeline* pipeline);

 /**
  @param instance_type
  @return void
  */
BSGFXAPI void
bsgfx_resetInstanceType(
    bsgfx_InstanceType* instance_type);

 /**
  @param mesh
  @param position
  @param rotation
  @param scale
  @param subtype_offset
  @param origin_at_center
  @return void
  */
BSGFXAPI void
bsgfx_instanceHiResMesh(
    bs_Mesh* mesh,
    const bs_vec3* position,
    const bs_vec4* rotation,
    float scale,
    int subtype_offset,
    bool origin_at_center);

 /**
  @param subtype
  @param data
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instanceMesh(
    bsgfx_InstanceSubtype* subtype,
    const bsgfx_MeshInstance* data,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param subtype
  @param data
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instanceBoneMesh(
    bsgfx_InstanceSubtype* subtype,
    const bsgfx_BoneInstance* data,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param start
  @param end
  @param color
  @return int
  */
BSGFXAPI int
bsgfx_instanceDepthlessLine(
    bs_vec3 start,
    bs_vec3 end,
    bs_RGBA color);

 /**
  @param start
  @param end
  @param color
  @return int
  */
BSGFXAPI int
bsgfx_instanceLine(
    bs_vec3 start,
    bs_vec3 end,
    bs_RGBA color);

 /**
  @param ray
  @param color
  @return int
  */
BSGFXAPI int
bsgfx_instanceRay(
    const bs_Ray* ray,
    bs_RGBA color);

 /**
  @param aabb
  @param color
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_instanceAabb(
    const bs_Aabb* aabb,
    bs_RGBA color,
    bs_Range* out);

 /**
  @param position
  @param radius
  @return int
  */
BSGFXAPI int
bsgfx_instanceSphere(
    bs_vec3 position,
    float radius);

 /**
  @param transform
  @param radius
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instanceCone(
    bs_mat4 transform,
    float radius,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param position
  @param color
  @param size
  @return int
  */
BSGFXAPI int
bsgfx_instancePoint(
    bs_vec3 position,
    bs_RGBA color,
    float size);

 /**
  @param subtype
  @param transform
  @param coords
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instanceQuad(
    bsgfx_InstanceSubtype* subtype,
    bs_mat4x3 transform,
    bs_vec4 coords,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param transform
  @param segments
  @param radius
  @param color
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_instanceDepthlessCircle(
    const bs_mat4* transform,
    int segments,
    float radius,
    bs_RGBA color,
    bs_Range* out);

 /**
  @param subtype
  @param transform
  @param texture
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instanceAtlas(
    bsgfx_InstanceSubtype* subtype,
    bs_mat4x3 transform,
    int texture,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param subtype
  @param transform
  @param texture
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instanceAtlasFlipped(
    bsgfx_InstanceSubtype* subtype,
    bs_mat4x3 transform,
    int texture,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param font
  @param px_size
  @return float
  */
BSGFXAPI float
bsgfx_fontHeight(
    bsgfx_Font* font,
    int px_size);

 /**
  @param subtype
  @param font
  @param position
  @param pt_size
  @param text
  @return float
  */
BSGFXAPI float
bsgfx_instanceASCIIText(
    bsgfx_InstanceSubtype* subtype,
    bsgfx_Font* font,
    bs_vec3 position,
    int pt_size,
    char* text);

 /**
  @param subtype
  @param font
  @param position
  @param pt_size
  @param text
  @param text_length
  @return float
  */
BSGFXAPI float
bsgfx_instanceASCIITextN(
    bsgfx_InstanceSubtype* subtype,
    bsgfx_Font* font,
    bs_vec3 position,
    int pt_size,
    char* text,
    int text_length);

 /**
  @param subtype
  @param font
  @param position
  @param pt_size
  @param format
  @param args
  @return float
  */
BSGFXAPI float
bsgfx_instanceASCIITextV(
    bsgfx_InstanceSubtype* subtype,
    bsgfx_Font* font,
    bs_vec3 position,
    int pt_size,
    char* format,
    va_list args);

 /**
  @param subtype
  @param font
  @param position
  @param pt_size
  @param format
  @param ...
  @return float
  */
BSGFXAPI float
bsgfx_instanceASCIITextF(
    bsgfx_InstanceSubtype* subtype,
    bsgfx_Font* font,
    bs_vec3 position,
    int pt_size,
    char* format,
     ...);

 /**
  @param position
  @param scale
  @return bs_mat4x3
  */
BSGFXAPI bs_mat4x3
bsgfx_matrix(
    bs_vec3 position,
    bs_vec3 scale);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_renderFineShadowVolumes();

 /**
  @return void
  */
BSGFXAPI void
bsgfx_renderShadowVolumes();

 /**
  @return void
  */
BSGFXAPI void
bsgfx_computeShadowVolumes();

 /**
  @return bs_Model*
  */
BSGFXAPI bs_Model*
bsgfx_prefabModel();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_package();

 /**
  @param name
  @param width
  @param height
  @param argc
  @param argv
  @return void
  */
BSGFXAPI void
bsgfx_ini(
    const char* name,
    bs_U32 width,
    bs_U32 height,
    int argc,
    char* argv[]);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_tick();

 /**
  @return void
  */
BSGFXAPI void
bsgfx_show();

 /**
  @return bsgfx_Application*
  */
BSGFXAPI bsgfx_Application*
bsgfx_app();

 /**
  @return bsgfx_Callbacks*
  */
BSGFXAPI bsgfx_Callbacks*
bsgfx_callbacks();

 /**
  @return bsgfx_Settings*
  */
BSGFXAPI bsgfx_Settings*
bsgfx_settings();

 /**
  @param proj
  @param view
  @return void
  */
BSGFXAPI void
bsgfx_setCamera(
    const bs_mat4* proj,
    const bs_mat4* view);

 /**
  @param id
  @param package_id
  @param version
  @param plural
  @param singular
  @param unmapped_size
  @param mapped_size
  @param mapper
  @param unmapped_flexible_offset
  @param mapped_flexible_offset
  @param unmapped_flexible_size
  @param mapped_flexible_size
  @return void
  */
BSGFXAPI void
bsgfx_type(
    bsgfx_TypeId id,
    int package_id,
    int version,
    const char* plural,
    const char* singular,
    size_t unmapped_size,
    size_t mapped_size,
    PFN_bsgfx_TypeMapper mapper,
    size_t unmapped_flexible_offset,
    size_t mapped_flexible_offset,
    size_t unmapped_flexible_size,
    size_t mapped_flexible_size);

 /**
  @param type
  @param id
  @return void
  */
BSGFXAPI void
bsgfx_map(
    bsgfx_TypeId type,
    int id);

 /**
  @param type_id
  @return void
  */
BSGFXAPI void
bsgfx_remap(
    bsgfx_TypeId type_id);

 /**
  @param type_id
  @return int
  */
BSGFXAPI int
bsgfx_count(
    bsgfx_TypeId type_id);

 /**
  @param type_id
  @param id
  @return void*
  */
BSGFXAPI void*
bsgfx_get(
    bsgfx_TypeId type_id,
    bs_U32 id);

 /**
  @param type_id
  @return bsgfx_Type*
  */
BSGFXAPI bsgfx_Type*
bsgfx_getType(
    bsgfx_TypeId type_id);

 /**
  @param type_id
  @param p
  @return int
  */
BSGFXAPI int
bsgfx_id(
    bsgfx_TypeId type_id,
    unsigned char* p);

 /**
  @param type_id
  @param p
  @return int
  */
BSGFXAPI int
bsgfx_rawId(
    bsgfx_TypeId type_id,
    unsigned char* p);

 /**
  @param type_id
  @param id
  @return void*
  */
BSGFXAPI void*
bsgfx_getRaw(
    bsgfx_TypeId type_id,
    int id);

 /**
  @param type_id
  @param id
  @return int
  */
BSGFXAPI int
bsgfx_flexibleCount(
    bsgfx_TypeId type_id,
    int id);

 /**
  @param package_id
  @return void
  */
BSGFXAPI void
bsgfx_loadLights(
    int package_id);

 /**
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_computePrefabShadows(
    bs_Queue* queue);

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderPrefabShadowVolumes(
    bs_RendererScope* scope,
    bs_Queue* queue);

 /**
  @param mesh_id
  @return bsgfx_PrefabMetadata*
  */
BSGFXAPI bsgfx_PrefabMetadata*
bsgfx_prefabMetadata(
    int mesh_id);

 /**
  @param package_id
  @param model
  @return void
  */
BSGFXAPI void
bsgfx_loadPrefabs(
    int package_id,
    bs_Model* model);

 /**
  @param prefab
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_prefabTransform(
    bsgfx_Prefab* prefab,
    bs_mat4* out);

 /**
  @param mesh_id
  @param transform
  @param prefab_subtype
  @param material_id
  @return int
  */
BSGFXAPI int
bsgfx_instancePrefabModel(
    int mesh_id,
    bs_mat4 transform,
    bsgfx_PrefabSubtype prefab_subtype,
    int material_id);

 /**
  @param id
  @param prefab_subtype
  @return int
  */
BSGFXAPI int
bsgfx_instancePrefab(
    int id,
    bsgfx_PrefabSubtype prefab_subtype);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_instancePrefabs();

 /**
  @param queue
  @param pipeline
  @param key_start
  @return void
  */
BSGFXAPI void
bsgfx_renderPrefabs(
    bs_Queue* queue,
    bs_Pipeline* pipeline,
    int key_start);

 /**
  @param queue
  @param pipeline
  @param key_start
  @return void
  */
BSGFXAPI void
bsgfx_renderPrefabPrimitives(
    bs_Queue* queue,
    bs_Pipeline* pipeline,
    int key_start);

 /**
  @param guid
  @return int
  */
BSGFXAPI int
bsgfx_queryPrefabId(
    const bs_GUID* guid);

 /**
  @param mesh_name_hash
  @param position
  @param radius
  @return int
  */
BSGFXAPI int
bsgfx_closestPrefab(
    bs_U64 mesh_name_hash,
    bs_vec3 position,
    float radius);

 /**
  @param primitive
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_primitivePosition(
    const bsgfx_RawPrimitive* primitive,
    bs_vec3* out);

 /**
  @param package_id
  @return void
  */
BSGFXAPI void
bsgfx_loadPrimitives(
    int package_id);

 /**
  @param type
  @return bsgfx_InstanceSubtype*
  */
BSGFXAPI bsgfx_InstanceSubtype*
bsgfx_primitiveSubtype(
    bsgfx_PrimitiveType type);

 /**
  @param subtype
  @param transform
  @param flags
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instancePrimitive(
    bsgfx_InstanceSubtype* subtype,
    bs_mat4 transform,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param tile_id
  @return int
  */
BSGFXAPI int
bsgfx_queryTilePrimitive(
    int tile_id);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_instancePrimitives();

 /**
  @param scope
  @param queue
  @param camera
  @return void
  */
BSGFXAPI void
bsgfx_renderPrimitives(
    bs_RendererScope* scope,
    bs_Queue* queue,
    bs_mat4 camera);

 /**
  @param guid
  @return int
  */
BSGFXAPI int
bsgfx_queryPrimitive(
    bs_GUID* guid);

 /**
  @param package_id
  @return void
  */
BSGFXAPI void
bsgfx_loadSpawners(
    int package_id);

 /**
  @param spawner
  @return void
  */
BSGFXAPI void
bsgfx_spawn(
    bsgfx_Spawner* spawner);

 /**
  @param package_id
  @param force_destroy
  @return void
  */
BSGFXAPI void
bsgfx_loadTiles(
    int package_id,
    bool force_destroy);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_instanceTiles();

 /**
  @param batch
  @param quad
  @param normal
  @param index
  @param image_index
  @param out_range
  @return void
  */
BSGFXAPI void
bsgfx_pushTile(
    const bs_Batch* batch,
    const bs_Quad* quad,
    bs_vec3 normal,
    bs_U32 index,
    int image_index,
    bs_Range* out_range);

 /**
  @param batch
  @param offset
  @param quad
  @param normal
  @param index
  @param image_index
  @return void
  */
BSGFXAPI void
bsgfx_batchTile(
    const bs_Batch* batch,
    const bs_U32* offset,
    const bs_Quad* quad,
    bs_vec3 normal,
    bs_U32 index,
    int image_index);

 /**
  @return const bsgfx_TileAxis*
  */
BSGFXAPI const bsgfx_TileAxis*
bsgfx_tileAxes();

 /**
  @param primitive
  @param axis
  @param x
  @param y
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_tilePosition(
    const bsgfx_Primitive* primitive,
    int axis,
    int x,
    int y,
    bs_vec3* out);

 /**
  @param axis
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_tileRotation(
    int axis,
    bs_vec4* out);

 /**
  @param axis
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_tileEulerRotation(
    int axis,
    bs_vec3* out);

 /**
  @param batch
  @param primitive
  @param axis
  @param x
  @param y
  @param index
  @param image_index
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_pushTileAt(
    const bs_Batch* batch,
    const bsgfx_Primitive* primitive,
    int axis,
    int x,
    int y,
    bs_U32 index,
    int image_index,
    bs_U32* out);

 /**
  @param primitive
  @param axis
  @param index
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_tileCoordinate(
    const bsgfx_Primitive* primitive,
    int axis,
    int index,
    bs_ivec2* out);

 /**
  @param primitive
  @param index
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_tileAxis(
    const bsgfx_Primitive* primitive,
    int index,
    int* out);

 /**
  @param primitive
  @param axis
  @param x
  @param y
  @param out
  @return void
  */
BSGFXAPI void
bsgfx_tileIndex(
    const bsgfx_Primitive* primitive,
    int axis,
    int x,
    int y,
    bs_U32* out);

 /**
  @param menu
  @param title_bar
  @param tab_bar
  @return bool
  */
BSGFXAPI bool
bsgfx_instanceWidgets(
    bsgfx_Menu menu,
    bsgfx_TitleBar* title_bar,
    bsgfx_MenuTabBar* tab_bar);

 /**
  @param text
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_instantiateTextUI(
    bsgfx_UIText text,
    bsgfx_UIElement* element);

 /**
  @param solid
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_instantiateSolidUI(
    bsgfx_UISolid solid,
    bsgfx_UIElement* element);

 /**
  @param solid
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_instantiateSolidUIElement(
    bsgfx_UISolid solid,
    const bsgfx_UIElement* element);

 /**
  @param solid
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_solidUIElement(
    bsgfx_UISolid solid,
    bsgfx_UIElement* element);

 /**
  @param icon
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_instantiateAtlasIconUI(
    bsgfx_UIIcon icon,
    bsgfx_UIElement* element);

 /**
  @param icon
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_instantiateAtlasIconUIElement(
    bsgfx_UIIcon icon,
    const bsgfx_UIElement* element);

 /**
  @param icon
  @param element
  @return void
  */
BSGFXAPI void
bsgfx_atlasIconUIElement(
    bsgfx_UIIcon icon,
    bsgfx_UIElement* element);

 /**
  @param element
  @return bool
  */
BSGFXAPI bool
bsgfx_hoveringUIElement(
    const bsgfx_UIElement* element);

 /**
  @param scope
  @param queue
  @return void
  */
BSGFXAPI void
bsgfx_renderColorPickers(
    bs_RendererScope* scope,
    bs_Queue* queue);

BSGFXAPI extern bsgfx_Scene _bsgfx_current_scene_;
BSGFXAPI extern bsgfx_Type _bsgfx_types_[BSGFX_TYPE_COUNT];
BSGFXAPI extern const char* _bsgfx_material_categories_[BSGFX_MATERIAL_CATEGORY_COUNT];
BSGFXAPI extern bs_List _bsgfx_materials_;
BSGFXAPI extern bs_mat4* _bsgfx_shader_joints_;
BSGFXAPI extern bs_U32 _bsgfx_num_shader_joints_;
BSGFXAPI extern bsgfx_Settings _bsgfx_settings_;
BSGFXAPI extern bsgfx_Application _bsgfx_app_;
BSGFXAPI extern bs_Model* _bsgfx_prefab_model_;
BSGFXAPI extern bsgfx_Callbacks _bsgfx_callbacks_;
BSGFXAPI extern HINSTANCE _bsgfx_bsmod_dll_;
BSGFXAPI extern bs_String* _bsgfx_variadic_;
BSGFXAPI extern int _bsgfx_package_;
BSGFXAPI extern bsgfx_PrefabMetadata* _bsgfx_prefabs_;
BSGFXAPI extern int _bsgfx_prefabs_count_;

#endif
