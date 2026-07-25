
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

typedef struct bsgfx_Text bsgfx_Text;
typedef struct bsgfx_MeshInstance bsgfx_MeshInstance;
typedef struct bsgfx_BoneInstance bsgfx_BoneInstance;
typedef struct bsgfx_QuadInstance bsgfx_QuadInstance;
typedef struct bsgfx_Scene bsgfx_Scene;
typedef struct bsgfx_Material bsgfx_Material;
typedef struct bsgfx_Collider bsgfx_Collider;
typedef struct bsgfx_SweepCollision bsgfx_SweepCollision;
typedef struct bsgfx_Animator bsgfx_Animator;
typedef struct bsgfx_AnimatorCallbacks bsgfx_AnimatorCallbacks;
typedef struct bsgfx_InstanceBuffer bsgfx_InstanceBuffer;
typedef struct bsgfx_Settings bsgfx_Settings;
typedef struct Poser Poser;
typedef struct bsgfx_Callbacks bsgfx_Callbacks;
typedef struct bsgfx_Application bsgfx_Application;
typedef struct bsgfx_TypeHeader bsgfx_TypeHeader;
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
typedef struct bsgfx_Widget bsgfx_Widget;
typedef struct bsgfx_AtlasCache bsgfx_AtlasCache;
typedef struct bsgfx_MenuTab bsgfx_MenuTab;
typedef struct bsgfx_MenuTabBar bsgfx_MenuTabBar;
typedef struct bsgfx_Menu bsgfx_Menu;
typedef struct bsgfx_TitleBar bsgfx_TitleBar;

typedef enum bsgfx_Subtype bsgfx_Subtype;
typedef enum bsgfx_ResourceType bsgfx_ResourceType;
typedef enum bsgfx_ImageId bsgfx_ImageId;
typedef enum bsgfx_SamplerId bsgfx_SamplerId;
typedef enum bsgfx_BufferId bsgfx_BufferId;
typedef enum bsgfx_BatchId bsgfx_BatchId;
typedef enum bsgfx_RendererId bsgfx_RendererId;
typedef enum bsgfx_QueueId bsgfx_QueueId;
typedef enum bsgfx_RayTracerId bsgfx_RayTracerId;
typedef enum bsgfx_AtlasId bsgfx_AtlasId;
typedef enum bsgfx_FontId bsgfx_FontId;
typedef enum bsgfx_MaterialCategory bsgfx_MaterialCategory;
typedef enum bsgfx_CollisionType bsgfx_CollisionType;
typedef enum bsgfx_AnimatorTypeBit bsgfx_AnimatorTypeBit;
typedef enum bsgfx_FontFlag bsgfx_FontFlag;
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

#define BSGFX_IMAGE_IDS(X)                                           \
    X(BSGFX_IMAGE_LO_RES_0_DEPTH)                                    \
    X(BSGFX_IMAGE_LO_RES_0_COLOR)                                    \
    X(BSGFX_IMAGE_LO_RES_0_NORMAL)                                   \
    X(BSGFX_IMAGE_LO_RES_0_POSITION)                                 \
    X(BSGFX_IMAGE_LO_RES_0_INDEX)                                    \
    X(BSGFX_IMAGE_LO_RES_0_FLAGS)                                    \
    X(BSGFX_IMAGE_LO_RES_0_VERTEX)                                   \
    X(BSGFX_IMAGE_LO_RES_1_COLOR)                                    \
    X(BSGFX_IMAGE_HI_RES_0_DEPTH)                                    \
    X(BSGFX_IMAGE_TILE)                                              \
    X(BSGFX_IMAGE_ANY)                                               \
    X(BSGFX_IMAGE_64)                                                \
    X(BSGFX_IMAGE_256)                                               \
    X(BSGFX_IMAGE_512)                                               \
    X(BSGFX_IMAGE_RAYTRACE_TEST)                                     \
    X(BSGFX_IMAGE_LEVEL_THUMBNAIL)                                   \
    X(BSGFX_IMAGE_MINIMAP)

#define BSGFX_SAMPLER_IDS(X)                                         \
    X(BSGFX_SAMPLER_NEAREST)                                         \
    X(BSGFX_SAMPLER_LINEAR)

#define BSGFX_BUFFER_IDS(X)                                          \
    X(BSGFX_BUFFER_JOINTS)                                           \
    X(BSGFX_BUFFER_INSTANCE_METADATA)                                \
    X(BSGFX_BUFFER_LO_RES_CURSOR_READS)                              \
    X(BSGFX_BUFFER_LO_RES_SCREENSHOT)                                \
    X(BSGFX_BUFFER_MATERIALS)                                        \
    X(BSGFX_BUFFER_MINIMAP)                                          \
    X(BSGFX_BUFFER_BINDING_TABLE)

#define BSGFX_BATCH_IDS(X)                                           \
    X(BSGFX_BATCH_VOLUME_COMPUTED)                                   \
    X(BSGFX_BATCH_PREFAB_SHADOWS)                                    \
    X(BSGFX_BATCH_VOLUME_INSTANCED)                                  \
    X(BSGFX_BATCH_VOLUME_SCREEN)                                     \
    X(BSGFX_BATCH_SCREEN)                                            \
    X(BSGFX_BATCH_LINE_INSTANCED)                                    \
    X(BSGFX_BATCH_POINT_INSTANCED)                                   \
    X(BSGFX_BATCH_SPHERE_INSTANCED)                                  \
    X(BSGFX_BATCH_BONE_INSTANCED)                                    \
    X(BSGFX_BATCH_MESH_INSTANCED)                                    \
    X(BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED)                         \
    X(BSGFX_BATCH_FOLIAGE)                                           \
    X(BSGFX_BATCH_QUAD_INSTANCED)                                    \
    X(BSGFX_BATCH_TEXT_INSTANCED)                                    \
    X(BSGFX_BATCH_ITEMS)                                             \
    X(BSGFX_BATCH_PRIMITIVE_TILES)

#define BSGFX_RENDERER_IDS(X)                                        \
    X(BSGFX_RENDERER_LO_RES)                                         \
    X(BSGFX_RENDERER_HI_RES)

#define BSGFX_QUEUE_IDS(X)                                           \
    X(BSGFX_QUEUE_GRAPHICS)                                          \
    X(BSGFX_QUEUE_COMPUTE)

#define BSGFX_RAY_TRACER_IDS(X)                                      \
    X(BSGFX_RAY_TRACER_MAIN)

#define BSGFX_ATLAS_IDS(X)                                           \
    X(BSGFX_ATLAS_ANY)

#define BSGFX_FONT_IDS(X)                                            \
    X(BSGFX_FONT_STANDARD)                                           \
    X(BSGFX_FONT_SMALL)                                              \
    X(BSGFX_FONT_TEMPLE)                                             \
    X(BSGFX_FONT_CONSOLAS)                                           \
    X(BSGFX_FONT_ARIAL_16)                                           \
    X(BSGFX_FONT_ARIAL_24)                                           \
    X(BSGFX_FONT_ARIAL_32)                                           \
    X(BSGFX_FONT_ARIAL_48)

#define BSGFX_CONTEXTS                                               \
    bsgfx_contexts()

#define BSGFX_IMAGES                                                 \
    bsgfx_images()

#define BSGFX_SAMPLERS                                               \
    bsgfx_samplers()

#define BSGFX_BUFFERS                                                \
    bsgfx_buffers()

#define BSGFX_BATCHES                                                \
    bsgfx_batches()

#define BSGFX_RENDERERS                                              \
    bsgfx_renderers()

#define BSGFX_QUEUES                                                 \
    bsgfx_queues()

#define BSGFX_RAY_TRACERS                                            \
    bsgfx_rayTracers()

#define BSGFX_ATLASES                                                \
    bsgfx_atlases()

#define BSGFX_FONTS                                                  \
    bsgfx_fonts()

#define BSGFX_DEPENDENCY_ALWAYS                                      \
    BSGFX_IMAGE_64,                                                  \
    BSGFX_IMAGE_256,                                                 \
    BSGFX_IMAGE_512,                                                 \
    BSGFX_SAMPLER_LINEAR

#define BSGFX_DEPENDENCY_PLAYER                                      \
    BSGFX_BATCH_BONE_INSTANCED,                                      \
    BSGFX_BATCH_MESH_INSTANCED,                                      \
    BSGFX_BUFFER_JOINTS

#define BSGFX_DEPENDENCY_TILE                                        \
    BSGFX_IMAGE_TILE

#define BSGFX_DEPENDENCY_LO_RES                                      \
    BSGFX_QUEUE_GRAPHICS,                                            \
    BSGFX_IMAGE_LO_RES_0_DEPTH,                                      \
    BSGFX_IMAGE_LO_RES_0_COLOR,                                      \
    BSGFX_IMAGE_LO_RES_0_NORMAL,                                     \
    BSGFX_IMAGE_LO_RES_0_POSITION,                                   \
    BSGFX_IMAGE_LO_RES_0_INDEX,                                      \
    BSGFX_IMAGE_LO_RES_0_FLAGS,                                      \
    BSGFX_IMAGE_LO_RES_0_VERTEX,                                     \
    BSGFX_IMAGE_LO_RES_1_COLOR,                                      \
    BSGFX_RENDERER_LO_RES

#define BSGFX_DEPENDENCY_SHADOWS                                     \
    BSGFX_DEPENDENCY_LO_RES,                                         \
    BSGFX_BUFFER_INSTANCE_METADATA,                                  \
    BSGFX_BATCH_VOLUME_COMPUTED,                                     \
    BSGFX_BATCH_PREFAB_SHADOWS,                                      \
    BSGFX_BATCH_VOLUME_DOWN_COMPUTED,                                \
    BSGFX_BATCH_VOLUME_INSTANCED,                                    \
    BSGFX_BATCH_VOLUME_SCREEN,                                       \
    BSGFX_QUEUE_COMPUTE

#define BSGFX_DEPENDENCY_HI_RES                                      \
    BSGFX_RENDERER_HI_RES,                                           \
    BSGFX_IMAGE_HI_RES_0_DEPTH

#define BSGFX_DEPENDENCY_FOLIAGE                                     \
    BSGFX_BATCH_FOLIAGE

#define BSGFX_DEPENDENCY_ATLAS                                       \
    BSGFX_SAMPLER_NEAREST,                                           \
    BSGFX_IMAGE_ANY

#define BSGFX_DEPENDENCY_INGAME                                      \
    BSGFX_DEPENDENCY_HI_RES,                                         \
    BSGFX_DEPENDENCY_LO_RES,                                         \
    BSGFX_DEPENDENCY_SHADOWS,                                        \
    BSGFX_DEPENDENCY_ATLAS,                                          \
    BSGFX_DEPENDENCY_FOLIAGE,                                        \
    BSGFX_DEPENDENCY_TILE,                                           \
    BSGFX_DEPENDENCY_PLAYER,                                         \
    BSGFX_RAY_TRACER_MAIN,                                           \
    BSGFX_IMAGE_RAYTRACE_TEST,                                       \
    BSGFX_BATCH_ITEMS,                                               \
    BSGFX_BUFFER_MATERIALS,                                          \
    BSGFX_BUFFER_MINIMAP,                                            \
    BSGFX_ATLAS_ANY,                                                 \
    BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED,                           \
    /* images*/                                                      \
    BSGFX_IMAGE_64,                                                  \
    BSGFX_IMAGE_256,                                                 \
    BSGFX_IMAGE_512,                                                 \
    BSGFX_IMAGE_MINIMAP,                                             \
    /* batches */                                                    \
    BSGFX_BATCH_QUAD_INSTANCED,                                      \
    BSGFX_BATCH_SCREEN,                                              \
    BSGFX_BATCH_SPHERE_INSTANCED,                                    \
    BSGFX_BATCH_PRIMITIVE_TILES,                                     \
    /* fonts */                                                      \
    BSGFX_FONT_STANDARD,                                             \
    BSGFX_FONT_TEMPLE,                                               \
    BSGFX_FONT_CONSOLAS,                                             \
    BSGFX_FONT_ARIAL_16,

#define BSGFX_DEPENDENCY_TEXT                                        \
    BSGFX_BATCH_QUAD_INSTANCED,                                      \
    BSGFX_BATCH_TEXT_INSTANCED

#define BSGFX_DEPENDENCY_DEBUG                                       \
    BSGFX_DEPENDENCY_TEXT,                                           \
    BSGFX_BUFFER_LO_RES_CURSOR_READS,                                \
    BSGFX_BUFFER_LO_RES_SCREENSHOT,                                  \
    BSGFX_FONT_SMALL,                                                \
    BSGFX_BATCH_LINE_INSTANCED,                                      \
    BSGFX_BATCH_POINT_INSTANCED

#define BSGFX_COLLIDER_SKIN                                          \
    (0.015)

#define du_animatorCallback(name)                                    \
    void(*name)(bsgfx_Animator*)

#define BSGFX_ALPHABET_DEFAULT                                       \
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

#define BSGFX_CONTENT_PATH                                           \
    "content/bsgfx"

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

#define BSGFX_MAX_NUMBER_PLAYERS                                     \
    (8)

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
enum bsgfx_Subtype {
    BSGFX_SUBTYPE_BIPYRAMID,
    BSGFX_SUBTYPE_PRIMITIVE_BOX,
    BSGFX_SUBTYPE_PRIMITIVE_SPHERE,
    BSGFX_SUBTYPE_TILE,
    BSGFX_SUBTYPE_TILE_2,
    BSGFX_SUBTYPE_64_HI,
    BSGFX_SUBTYPE_256_HI,
    BSGFX_SUBTYPE_ATLAS_ICON,
    BSGFX_SUBTYPE_UI,
    BSGFX_SUBTYPE_UI_COLOR,
    BSGFX_SUBTYPE_UI_STENCIL,
    BSGFX_SUBTYPE_COLOR_PICKER,
    BSGFX_SUBTYPE_COLOR_PICKER_HUE,
    BSGFX_SUBTYPE_COLOR_PICKER_ALPHA,
    BSGFX_SUBTYPE_DITHER,
    BSGFX_SUBTYPE_CORNER_GRADIENT,
    BSGFX_SUBTYPE_TILE_ICON,
    BSGFX_SUBTYPE_QUAD_MATERIAL_TEXTURE,
    BSGFX_SUBTYPE_PRIMITIVE_HI,
    BSGFX_SUBTYPE_ATLAS_PREFAB,
    BSGFX_SUBTYPE_ATLAS_PREFAB_TRANSPARENT,
    BSGFX_SUBTYPE_PLANE_MESH,
    BSGFX_SUBTYPE_ATLAS,
    BSGFX_SUBTYPE_CONE_MESH,
    BSGFX_SUBTYPE_SPHERE_MESH,
    BSGFX_SUBTYPE_POINT,
    BSGFX_SUBTYPE_LINE,
    BSGFX_SUBTYPE_LINE_2D,
    BSGFX_SUBTYPE_LINE_DEPTHLESS,
    BSGFX_SUBTYPE_COUNT,
};

enum bsgfx_ResourceType {
    BSGFX_RESOURCE_PRIMITIVE = BS_RESOURCE_TYPE_COUNT,
    BSGFX_RESOURCE_PREFAB,
    BSGFX_RESOURCE_TILE,
    BSGFX_RESOURCE_LIGHT,
    BSGFX_RESOURCE_TYPE_COUNT,
};

enum bsgfx_ImageId {
    BSGFX_IMAGE_LO_RES_0_DEPTH,
    BSGFX_IMAGE_LO_RES_0_COLOR,
    BSGFX_IMAGE_LO_RES_0_NORMAL,
    BSGFX_IMAGE_LO_RES_0_POSITION,
    BSGFX_IMAGE_LO_RES_0_INDEX,
    BSGFX_IMAGE_LO_RES_0_FLAGS,
    BSGFX_IMAGE_LO_RES_0_VERTEX,
    BSGFX_IMAGE_LO_RES_1_COLOR,
    BSGFX_IMAGE_HI_RES_0_DEPTH,
    BSGFX_IMAGE_TILE,
    BSGFX_IMAGE_ANY,
    BSGFX_IMAGE_64,
    BSGFX_IMAGE_256,
    BSGFX_IMAGE_512,
    BSGFX_IMAGE_RAYTRACE_TEST,
    BSGFX_IMAGE_LEVEL_THUMBNAIL,
    BSGFX_IMAGE_MINIMAP,
    BSGFX_IMAGES_COUNT,
};

enum bsgfx_SamplerId {
    BSGFX_SAMPLER_NEAREST,
    BSGFX_SAMPLER_LINEAR,
    BSGFX_SAMPLERS_COUNT,
};

enum bsgfx_BufferId {
    BSGFX_BUFFER_JOINTS,
    BSGFX_BUFFER_INSTANCE_METADATA,
    BSGFX_BUFFER_LO_RES_CURSOR_READS,
    BSGFX_BUFFER_LO_RES_SCREENSHOT,
    BSGFX_BUFFER_MATERIALS,
    BSGFX_BUFFER_MINIMAP,
    BSGFX_BUFFER_BINDING_TABLE,
    BSGFX_BUFFERS_COUNT,
};

enum bsgfx_BatchId {
    BSGFX_BATCH_VOLUME_COMPUTED,
    BSGFX_BATCH_PREFAB_SHADOWS,
    BSGFX_BATCH_VOLUME_INSTANCED,
    BSGFX_BATCH_VOLUME_SCREEN,
    BSGFX_BATCH_SCREEN,
    BSGFX_BATCH_LINE_INSTANCED,
    BSGFX_BATCH_POINT_INSTANCED,
    BSGFX_BATCH_SPHERE_INSTANCED,
    BSGFX_BATCH_BONE_INSTANCED,
    BSGFX_BATCH_MESH_INSTANCED,
    BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED,
    BSGFX_BATCH_FOLIAGE,
    BSGFX_BATCH_QUAD_INSTANCED,
    BSGFX_BATCH_TEXT_INSTANCED,
    BSGFX_BATCH_ITEMS,
    BSGFX_BATCH_PRIMITIVE_TILES,
    BSGFX_BATCHES_COUNT,
};

enum bsgfx_RendererId {
    BSGFX_RENDERER_LO_RES,
    BSGFX_RENDERER_HI_RES,
    BSGFX_RENDERERS_COUNT,
};

enum bsgfx_QueueId {
    BSGFX_QUEUE_GRAPHICS,
    BSGFX_QUEUE_COMPUTE,
    BSGFX_QUEUES_COUNT,
};

enum bsgfx_RayTracerId {
    BSGFX_RAY_TRACER_MAIN,
    BSGFX_RAY_TRACERS_COUNT,
};

enum bsgfx_AtlasId {
    BSGFX_ATLAS_ANY,
    BSGFX_ATLASES_COUNT,
};

enum bsgfx_FontId {
    BSGFX_FONT_STANDARD,
    BSGFX_FONT_SMALL,
    BSGFX_FONT_TEMPLE,
    BSGFX_FONT_CONSOLAS,
    BSGFX_FONT_ARIAL_16,
    BSGFX_FONT_ARIAL_24,
    BSGFX_FONT_ARIAL_32,
    BSGFX_FONT_ARIAL_48,
    BSGFX_FONTS_COUNT,
};

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

struct bsgfx_InstanceBuffer {
    struct bsgfx_InstanceHeader header;
    char data[64];
};

struct bsgfx_Settings {
    bool cull_backfaces;
    float master_volume;
    bool music;
};

struct Poser {
    int day;
    int hour;
    int minute;
    int second;
    float time;
    bs_vec3 sun_direction;
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
    float zoom;
    bool instances_ticked;
    bs_Buffer* instance_buffers[BSGFX_INSTANCE_TYPE_COUNT];
    struct {
        int joint_offset;
    } members[BSGFX_MAX_NUMBER_PLAYERS];
    int member_count;
    bs_List sweep_collisions;
    bool menu_blocked;
    bool menu_open;
};

struct bsgfx_Callbacks {
    PFN_void tick;
    PFN_void fixedTick;
    PFN_void render;
    PFN_void ini;
    PFN_void lateIni;
    PFN_void loadScene;
    PFN_bsgfx_onQueue queue;
};

struct bsgfx_Application {
    const char* name;
};

struct bsgfx_TypeHeader {
    bs_U32 magic;
    bs_U32 version;
    int flexible_count;
    int count;
    int accessors[];
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
    bs_Font* font;
    union {
        struct {
            char* value;
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
            int atlas_subtype;
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
            int subtype;
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
    bs_Font* font;
    float border_radius;
    int shadow_material_id;
    int outline_material_id;
    int text_subtype;
};

struct bsgfx_TitleBar {
    const char* name;
    bs_Font* font;
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
  @return bs_PipelineHash
  */
BSGFXAPI bs_PipelineHash
bsgfx_defaultPipelineHash();

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
  @return int
  */
BSGFXAPI int
bsgfx_contexts();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_images();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_samplers();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_buffers();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_batches();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_renderers();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_queues();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_rayTracers();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_atlases();

 /**
  @return int
  */
BSGFXAPI int
bsgfx_fonts();

 /**
  @param library_name
  @param subtype
  @return bool
  */
BSGFXAPI bool
bsgfx_validateSubtype(
    const char* library_name,
    int subtype);

 /**
  @param library_name
  @param instance_type_id
  @return bool
  */
BSGFXAPI bool
bsgfx_validateInstanceType(
    const char* library_name,
    int instance_type_id);

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
  @param name_length
  @return bsgfx_Material*
  */
BSGFXAPI bsgfx_Material*
bsgfx_material(
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
  @return void
  */
BSGFXAPI void
bsgfx_pipeline();

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
  @param subtype
  @return bs_List*
  */
BSGFXAPI bs_List*
bsgfx_subtypeInstances(
    int subtype);

 /**
  @return bs_Result
  */
BSGFXAPI bs_Result
bsgfx_iniInstances();

 /**
  @param type
  @param max_instance_count
  @param bind_set
  @param binding
  @return void
  */
BSGFXAPI void
bsgfx_instanceType(
    int type,
    int max_instance_count,
    int bind_set,
    int binding);

 /**
  @param subtype
  @return bs_Range
  */
BSGFXAPI bs_Range
bsgfx_subtypeRange(
    int subtype);

 /**
  @param subtype
  @return void
  */
BSGFXAPI void
bsgfx_deleteSubtype(
    int subtype);

 /**
  @param subtype
  @return int
  */
BSGFXAPI int
bsgfx_instanceCount(
    int subtype);

 /**
  @param instance_type_id
  @return int
  */
BSGFXAPI int
bsgfx_subtypeCount(
    int instance_type_id);

 /**
  @return const int*
  */
BSGFXAPI const int*
bsgfx_subtypes();

 /**
  @param type
  @param batch
  @param flags
  @param range
  @return int
  */
BSGFXAPI int
bsgfx_subtype(
    int type,
    bs_Batch* batch,
    bs_U32 flags,
    bs_Range range);

 /**
  @param subtype
  @param data
  @param data_size
  @param flags
  @param bone_index
  @param id
  @param material
  @return int
  */
BSGFXAPI int
bsgfx_instance(
    int subtype,
    const char* data,
    int data_size,
    bs_U32 flags,
    unsigned int bone_index,
    int id,
    int material);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_tickInstances();

 /**
  @param subtype
  @param flag
  @return bool
  */
BSGFXAPI bool
bsgfx_subtypeHasFlag(
    int subtype,
    bs_U32 flag);

 /**
  @param subtype
  @param pipeline
  @return void
  */
BSGFXAPI void
bsgfx_renderSubtype(
    int subtype,
    bs_Pipeline* pipeline);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_resetInstances();

 /**
  @param subtype
  @return void
  */
BSGFXAPI void
bsgfx_resetSubtype(
    int subtype);

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
    int subtype,
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
    int subtype,
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
    int subtype,
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
    int subtype,
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
    int subtype,
    bs_mat4x3 transform,
    int texture,
    bs_U32 flags,
    int id,
    int material);

 /**
  @param subtype
  @param font
  @param params
  @param out_text_size
  @param value
  @param value_length
  @return void
  */
BSGFXAPI void
bsgfx_instanceText(
    int subtype,
    bs_Font* font,
    bsgfx_Text* params,
    bs_vec2* out_text_size,
    char* value,
    int value_length);

 /**
  @param subtype
  @param font
  @param params
  @param out_text_size
  @param format
  @param args
  @return void
  */
BSGFXAPI void
bsgfx_instanceTextV(
    int subtype,
    bs_Font* font,
    bsgfx_Text* params,
    bs_vec2* out_text_size,
    char* format,
    va_list args);

 /**
  @param subtype
  @param font
  @param params
  @param out_text_size
  @param format
  @param ...
  @return void
  */
BSGFXAPI void
bsgfx_instanceTextF(
    int subtype,
    bs_Font* font,
    bsgfx_Text* params,
    bs_vec2* out_text_size,
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
  @return struct Poser*
  */
BSGFXAPI struct Poser*
poser();

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
  @return void
  */
BSGFXAPI void
bsgfx_computePrefabShadows();

 /**
  @return void
  */
BSGFXAPI void
bsgfx_renderPrefabShadowVolumes();

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
  @param pipeline
  @param key_start
  @return void
  */
BSGFXAPI void
bsgfx_renderPrefabs(
    bs_Pipeline* pipeline,
    int key_start);

 /**
  @return void
  */
BSGFXAPI void
bsgfx_renderScenePrefabs();

 /**
  @param pipeline
  @param key_start
  @return void
  */
BSGFXAPI void
bsgfx_renderPrefabPrimitives(
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
  @return int
  */
BSGFXAPI int
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
    int subtype,
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
  @param camera
  @return void
  */
BSGFXAPI void
bsgfx_renderPrimitives(
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
  @return void
  */
BSGFXAPI void
bsgfx_renderColorPickers();

BSGFXAPI extern bsgfx_Scene _bsgfx_current_scene_;
BSGFXAPI extern int _bsgfx_contexts_;
BSGFXAPI extern int _bsgfx_images_;
BSGFXAPI extern int _bsgfx_samplers_;
BSGFXAPI extern int _bsgfx_buffers_;
BSGFXAPI extern int _bsgfx_batches_;
BSGFXAPI extern int _bsgfx_renderers_;
BSGFXAPI extern int _bsgfx_queues_;
BSGFXAPI extern int _bsgfx_ray_tracers_;
BSGFXAPI extern int _bsgfx_atlases_;
BSGFXAPI extern int _bsgfx_fonts_;
BSGFXAPI extern bsgfx_Type _bsgfx_types_[BSGFX_TYPE_COUNT];
BSGFXAPI extern int _bsgfx_subtypes_[BSGFX_SUBTYPE_COUNT];
BSGFXAPI extern const char* _bsgfx_material_categories_[BSGFX_MATERIAL_CATEGORY_COUNT];
BSGFXAPI extern bs_List _bsgfx_materials_;
BSGFXAPI extern bs_mat4* _bsgfx_shader_joints_;
BSGFXAPI extern bs_U32 _bsgfx_num_shader_joints_;
BSGFXAPI extern bsgfx_Settings _bsgfx_settings_;
BSGFXAPI extern struct Poser* _poser_;
BSGFXAPI extern bsgfx_Application _bsgfx_app_;
BSGFXAPI extern bs_Model* _bsgfx_prefab_model_;
BSGFXAPI extern bsgfx_Callbacks _bsgfx_callbacks_;
BSGFXAPI extern HINSTANCE _bsgfx_bsmod_dll_;
BSGFXAPI extern bs_String* _bsgfx_variadic_;
BSGFXAPI extern int _bsgfx_package_;
BSGFXAPI extern bsgfx_PrefabMetadata* _bsgfx_prefabs_;
BSGFXAPI extern int _bsgfx_prefabs_count_;

#endif
