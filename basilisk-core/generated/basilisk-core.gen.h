
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
        

#ifndef BASILISK_CORE_GEN_H
#define BASILISK_CORE_GEN_H

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef union bs_vec2 bs_vec2;
typedef union bs_vec3 bs_vec3;
typedef union bs_vec4 bs_vec4;
typedef union bs_ivec2 bs_ivec2;
typedef union bs_ivec3 bs_ivec3;
typedef union bs_ivec4 bs_ivec4;
typedef union bs_mat2 bs_mat2;
typedef union bs_mat3 bs_mat3;
typedef union bs_mat4 bs_mat4;
typedef union bs_mat4x3 bs_mat4x3;
typedef union bs_RGBA bs_RGBA;
typedef union bs_RGB bs_RGB;
typedef union bs_BigInt bs_BigInt;
typedef struct bs_Aabb bs_Aabb;
typedef struct bs_Sphere bs_Sphere;
typedef struct bs_Rectangle bs_Rectangle;
typedef struct bs_Ray bs_Ray;
typedef struct bs_Quad bs_Quad;
typedef struct bs_Plane bs_Plane;
typedef struct bs_Box bs_Box;
typedef struct bs_FileInfo bs_FileInfo;
typedef struct bs_File bs_File;
typedef struct bs_PngData bs_PngData;
typedef struct bs_Procedure bs_Procedure;
typedef struct bs_Timer bs_Timer;
typedef struct bs_DateTime bs_DateTime;
typedef struct bs_RayVsObb bs_RayVsObb;
typedef struct bs_SphereVsPoint bs_SphereVsPoint;
typedef struct bs_SphereVsBox bs_SphereVsBox;
typedef struct bs_RectangleVsPoint bs_RectangleVsPoint;
typedef struct bs_LineVsLine bs_LineVsLine;
typedef struct bs_GUID bs_GUID;
typedef struct bs_List bs_List;
typedef struct bs_mat3SVD bs_mat3SVD;
typedef struct bs_String bs_String;
typedef struct bs_StringPoolEntry bs_StringPoolEntry;
typedef struct bs_Range bs_Range;
typedef struct bs_Header bs_Header;
typedef struct bs_Object bs_Object;
typedef struct bs_ResourceParams bs_ResourceParams;
typedef struct bs_Resource bs_Resource;
typedef struct bs_ResourceHeader bs_ResourceHeader;
typedef struct bs_PackageHeader bs_PackageHeader;
typedef struct bs_Package bs_Package;
typedef struct bs_BlitOperation bs_BlitOperation;
typedef struct bs_ImageIndex bs_ImageIndex;
typedef struct bs_ImageSwaps bs_ImageSwaps;
typedef struct bs_Image bs_Image;
typedef struct bs_BshaHeader bs_BshaHeader;
typedef struct bs_BshaAttribute bs_BshaAttribute;
typedef struct bs_BiffHeader bs_BiffHeader;
typedef struct bs_BiffPointer bs_BiffPointer;
typedef struct bs_BatlHeader bs_BatlHeader;
typedef struct bs_BatlImage bs_BatlImage;
typedef struct bs_AtlasTexture bs_AtlasTexture;
typedef struct bs_Atlas bs_Atlas;
typedef struct bs_Sampler bs_Sampler;
typedef struct bs_StencilOperation bs_StencilOperation;
typedef struct bs_Pipeline bs_Pipeline;
typedef struct bs_PipelineHash bs_PipelineHash;
typedef struct bs_RayTracePipelineHash bs_RayTracePipelineHash;
typedef struct bs_AttributeType bs_AttributeType;
typedef struct bs_Attribute bs_Attribute;
typedef struct bs_Shader bs_Shader;
typedef struct bs_BufferSwap bs_BufferSwap;
typedef struct bs_Buffer bs_Buffer;
typedef struct bs_Output bs_Output;
typedef struct bs_Input bs_Input;
typedef struct bs_RendererScope bs_RendererScope;
typedef struct bs_RendererSwaps bs_RendererSwaps;
typedef struct bs_Renderer bs_Renderer;
typedef struct bs_Batch bs_Batch;
typedef struct bs_WaitSemaphore bs_WaitSemaphore;
typedef struct bs_QueueSwaps bs_QueueSwaps;
typedef struct bs_Queue bs_Queue;
typedef struct bs_ShaderGroup bs_ShaderGroup;
typedef struct bs_RayTracer bs_RayTracer;
typedef union bs_JsonArray bs_JsonArray;
typedef struct bs_Json bs_Json;
typedef struct bs_JsonValue bs_JsonValue;
typedef struct bs_JsonEnumeration bs_JsonEnumeration;
typedef struct bs_Material bs_Material;
typedef struct bs_Primitive bs_Primitive;
typedef struct bs_Mesh bs_Mesh;
typedef struct bs_Model bs_Model;
typedef struct bs_Bone bs_Bone;
typedef struct bs_Armature bs_Armature;
typedef struct bs_AnimationBone bs_AnimationBone;
typedef struct bs_Animation bs_Animation;
typedef struct bs_Sound bs_Sound;
typedef struct bs_ImageDescriptor bs_ImageDescriptor;
typedef struct bs_Descriptor bs_Descriptor;
typedef struct bs_Binding bs_Binding;
typedef struct bs_BindSet bs_BindSet;
typedef struct bs_ObjectSource bs_ObjectSource;
typedef struct bs_ObjectId bs_ObjectId;
typedef struct bs_IO bs_IO;
typedef struct bs_Instance bs_Instance;
typedef struct bs_Bindings bs_Bindings;
typedef struct bs_Config bs_Config;
typedef struct bs_QueueFamily bs_QueueFamily;
typedef struct bs_SurfaceFormat bs_SurfaceFormat;
typedef struct bs_PhysicalDevice bs_PhysicalDevice;
typedef struct bs_Context bs_Context;
typedef struct bs_Scope bs_Scope;
typedef struct bs_Args bs_Args;
typedef struct bs_Features bs_Features;
typedef struct bs_Props bs_Props;
typedef struct bs_Callbacks bs_Callbacks;
typedef struct bs_LogQueueItem bs_LogQueueItem;

typedef enum bs_Library bs_Library;
typedef enum bs_MessageLevel bs_MessageLevel;
typedef enum bs_Result bs_Result;
typedef enum bs_IniFlag bs_IniFlag;
typedef enum bs_NonClientArea bs_NonClientArea;
typedef enum bs_WindowType bs_WindowType;
typedef enum bs_ImageFilter bs_ImageFilter;
typedef enum bs_PngType bs_PngType;
typedef enum bs_Slot bs_Slot;
typedef enum bs_BufferUsageFlag bs_BufferUsageFlag;
typedef enum bs_MemoryPropertyFlag bs_MemoryPropertyFlag;
typedef enum bs_AccessMask bs_AccessMask;
typedef enum bs_PipelineStage bs_PipelineStage;
typedef enum bs_DependencyFlag bs_DependencyFlag;
typedef enum bs_CullModeFlag bs_CullModeFlag;
typedef enum bs_StencilFaceFlag bs_StencilFaceFlag;
typedef enum bs_StencilOp bs_StencilOp;
typedef enum bs_BlendFactor bs_BlendFactor;
typedef enum bs_BlendOperationType bs_BlendOperationType;
typedef enum bs_CompareOp bs_CompareOp;
typedef enum bs_TopologyType bs_TopologyType;
typedef enum bs_PolygonType bs_PolygonType;
typedef enum bs_StoreOp bs_StoreOp;
typedef enum bs_LoadOp bs_LoadOp;
typedef enum bs_ColliderType bs_ColliderType;
typedef enum bs_ObjectFlag bs_ObjectFlag;
typedef enum bs_ResourceType bs_ResourceType;
typedef enum bs_ImageBit bs_ImageBit;
typedef enum bs_AtlasFlag bs_AtlasFlag;
typedef enum bs_SamplerBit bs_SamplerBit;
typedef enum bs_PipelineFlag bs_PipelineFlag;
typedef enum bs_PipelineType bs_PipelineType;
typedef enum bs_ShaderBit bs_ShaderBit;
typedef enum bs_BufferBit bs_BufferBit;
typedef enum bs_RendererBit bs_RendererBit;
typedef enum bs_OutputFlag bs_OutputFlag;
typedef enum bs_InputBit bs_InputBit;
typedef enum bs_BatchBit bs_BatchBit;
typedef enum bs_QueueBit bs_QueueBit;
typedef enum bs_ModelFlag bs_ModelFlag;
typedef enum bs_ArmatureFlag bs_ArmatureFlag;
typedef enum bs_AnimationFlag bs_AnimationFlag;
typedef enum bs_EndpointType bs_EndpointType;
typedef enum bs_CursorIcon bs_CursorIcon;
typedef enum bs_ObjectType bs_ObjectType;
typedef enum bs_SurfaceType bs_SurfaceType;
typedef enum bs_SwapchainMode bs_SwapchainMode;
typedef enum bs_JsonType bs_JsonType;
typedef enum bs_ShaderType bs_ShaderType;
typedef enum bs_Format bs_Format;
typedef enum bs_ColorSpace bs_ColorSpace;
typedef enum bs_PresentMode bs_PresentMode;
typedef enum bs_ImageLayout bs_ImageLayout;
typedef enum bs_DescriptorType bs_DescriptorType;
typedef enum bs_DescriptorTypeIndex bs_DescriptorTypeIndex;
typedef enum bs_VkObjectType bs_VkObjectType;

#define BS_CONFIGURE_SOURCE(sources, index, count, ids)              \
    sources[index] = bs_configureSource(index, count, (const char* []) { ids(BS_STRING_GEN) })

#define BS_RGBA(r, g, b, a)                                          \
    (bs_RGBA) { r, g, b, a }

#define BS_FLT_MAX                                                   \
    3.402823466e+38F

#define BPAK_MAGIC                                                   \
    0x6B617062

#define BS_BSHA_MAGIC                                                \
    0x61687362

#define BS_BBND_MAGIC                                                \
    0x646E6262

#define BS_BATL_MAGIC                                                \
    0x6C746162

#define BS_BIFF_MAGIC                                                \
    0x66666962

#define BFNT_MAGIC                                                   \
    0x746E6662

#define BS_CONSTANT_STRING(s)                                        \
    s, sizeof(s) - 1

#define BS_MAX_PHYSICAL_DEVICE_NAME_SIZE                             \
    256U

#define BS_PI                                                        \
    3.14159265359

#define BS_2PI                                                       \
    (3.14159265359 * 2.0)

#define BS_MIN(a, b)                                                 \
    (((a)<(b))?(a):(b))

#define BS_MAX(a, b)                                                 \
    (((a)>(b))?(a):(b))

#define BS_ENUM_GEN(ENUM)                                            \
    ENUM,

#define BS_STRING_GEN(STRING)                                        \
    #STRING,

#define BS_GENERATE_ENUM(ENUM)                                       \
    enum { ENUM(BS_ENUM_GEN) }

#define BS_GENERATE_STRINGS(STRING)                                  \
    (const char* []) { STRING(BS_STRING_GEN) }

#ifndef __VA_NARG__                                                  \


#define __VA_NARG__(...)                                             \
    BS_ARGS_COUNT_(__VA_ARGS__,BS_RSEQ_N())

#define BS_ARGS_COUNT_(...)                                          \
    BS_ARG_N(__VA_ARGS__)

#define BS_ARG_N(                                                    \
    _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,                          \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,                         \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,                         \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,                         \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,                         \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,                         \
    _61,_62,_63,N,...) N

#define BS_RSEQ_N()                                                  \
    63,62,61,60,                                                     \
    59,58,57,56,55,54,53,52,51,50,                                   \
    49,48,47,46,45,44,43,42,41,40,                                   \
    39,38,37,36,35,34,33,32,31,30,                                   \
    29,28,27,26,25,24,23,22,21,20,                                   \
    19,18,17,16,15,14,13,12,11,10,                                   \
    9,8,7,6,5,4,3,2,1,0

#endif                                                               \


#ifndef __VA_FOR__                                                   \


#define FE_0(WHAT)                                                   \


#define FE_1(WHAT, X)                                                \
    WHAT(X)

#define FE_2(WHAT, X, ...)                                           \
    WHAT(X) FE_1(WHAT, __VA_ARGS__)

#define FE_3(WHAT, X, ...)                                           \
    WHAT(X) FE_2(WHAT, __VA_ARGS__)

#define FE_4(WHAT, X, ...)                                           \
    WHAT(X) FE_3(WHAT, __VA_ARGS__)

#define FE_5(WHAT, X, ...)                                           \
    WHAT(X) FE_4(WHAT, __VA_ARGS__)

#define FE_6(WHAT, X, ...)                                           \
    WHAT(X) FE_5(WHAT, __VA_ARGS__)

#define FE_7(WHAT, X, ...)                                           \
    WHAT(X) FE_6(WHAT, __VA_ARGS__)

#define FE_8(WHAT, X, ...)                                           \
    WHAT(X) FE_7(WHAT, __VA_ARGS__)

#define FE_9(WHAT, X, ...)                                           \
    WHAT(X) FE_8(WHAT, __VA_ARGS__)

#define FE_10(WHAT, X, ...)                                          \
    WHAT(X) FE_9(WHAT, __VA_ARGS__)

#define FE_11(WHAT, X, ...)                                          \
    WHAT(X) FE_10(WHAT, __VA_ARGS__)

#define FE_12(WHAT, X, ...)                                          \
    WHAT(X) FE_11(WHAT, __VA_ARGS__)

#define FE_13(WHAT, X, ...)                                          \
    WHAT(X) FE_12(WHAT, __VA_ARGS__)

#define FE_14(WHAT, X, ...)                                          \
    WHAT(X) FE_13(WHAT, __VA_ARGS__)

#define FE_15(WHAT, X, ...)                                          \
    WHAT(X) FE_14(WHAT, __VA_ARGS__)

#define FE_16(WHAT, X, ...)                                          \
    WHAT(X) FE_15(WHAT, __VA_ARGS__)

#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,NAME,...) \
    NAME

#define __VA_FOR__(action, ...)                                      \
    GET_MACRO(_0, __VA_ARGS__,                                       \
    FE_16,FE_15,FE_14,FE_13,FE_12,FE_11,FE_10,FE_9,                  \
    FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)                    \
    (action, __VA_ARGS__)

#endif                                                               \


#define FE2_0(WHAT)                                                  \


#define FE2_2(WHAT, a, b)                                            \
    WHAT(a, b)

#define FE2_4(WHAT, a, b, ...)                                       \
    WHAT(a, b) FE2_2(WHAT, __VA_ARGS__)

#define FE2_6(WHAT, a, b, ...)                                       \
    WHAT(a, b) FE2_4(WHAT, __VA_ARGS__)

#define FE2_8(WHAT, a, b, ...)                                       \
    WHAT(a, b) FE2_6(WHAT, __VA_ARGS__)

#define FE2_10(WHAT, a, b, ...)                                      \
    WHAT(a, b) FE2_8(WHAT, __VA_ARGS__)

#define FE2_12(WHAT, a, b, ...)                                      \
    WHAT(a, b) FE2_10(WHAT, __VA_ARGS__)

#define FE2_14(WHAT, a, b, ...)                                      \
    WHAT(a, b) FE2_12(WHAT, __VA_ARGS__)

#define FE2_16(WHAT, a, b, ...)                                      \
    WHAT(a, b) FE2_14(WHAT, __VA_ARGS__)

#define GET_FE2_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,NAME,...) \
    NAME

#define __VA_FOR_2__(action, ...)                                    \
    GET_FE2_MACRO(__VA_ARGS__,                                       \
    FE2_16,FE2_16,                                                   \
    FE2_14,FE2_14,                                                   \
    FE2_12,FE2_12,                                                   \
    FE2_10,FE2_10,                                                   \
    FE2_8, FE2_8,                                                    \
    FE2_6, FE2_6,                                                    \
    FE2_4, FE2_4,                                                    \
    FE2_2, FE2_2,                                                    \
    FE2_0)                                                           \
    (action, __VA_ARGS__)

#define BS_MAX_NUM_BINDINGS                                          \
    32

#define BS_MAX_NUM_BIND_SETS                                         \
    32

#define BS_MAX_NUM_QUEUES                                            \
    8

#define BS_MAX_NUM_SUBPASSES                                         \
    6

#define BS_MAX_NUM_SUBPASS_DEPENDENCIES                              \
    6

#define BS_MAX_ATTACHMENTS_COUNT                                     \
    12

#define BS_TIMEOUT                                                   \
    60000000000000

#define BS_KEYS_COUNT                                                \
    256

#define BS_KEY_BYTES_COUNT                                           \
    ((BS_KEYS_COUNT + 8) / 8)

#define BS_MAT4_IDENTITY                                             \
    (bs_mat4) {{                                                     \
        { 1.0, 0.0, 0.0, 0.0 },                                      \
        { 0.0, 1.0, 0.0, 0.0 },                                      \
        { 0.0, 0.0, 1.0, 0.0 },                                      \
        { 0.0, 0.0, 0.0, 1.0 }                                       \
    }}

#define BS_MAT3_IDENTITY                                             \
    (bs_mat3) {{                                                     \
        { 1.0, 0.0, 0.0 },                                           \
        { 0.0, 1.0, 0.0 },                                           \
        { 0.0, 0.0, 1.0 }                                            \
    }}

#define BS_QUAT_IDENTITY                                             \
    (bs_vec4) { 0.0, 0.0, 0.0, 1.0 }

#define BS_LOG_QUEUE_SIZE                                            \
    10

#define BS_MAX_LOG_SIZE                                              \
    1024

#define BS_I8_MIN                                                    \
    (bs_I8)(-127 - 1)

#define BS_I16_MIN                                                   \
    (bs_I16)(-32767 - 1)

#define BS_I32_MIN                                                   \
    (bs_I32)(-2147483647 - 1)

#define BS_I64_MIN                                                   \
    (bs_I64)(-9223372036854775807 - 1)

#define BS_I8_MAX                                                    \
    (bs_I8)(127)

#define BS_I16_MAX                                                   \
    (bs_I16)(32767)

#define BS_I32_MAX                                                   \
    (bs_I32)(2147483647)

#define BS_I64_MAX                                                   \
    (bs_I64)(9223372036854775807)

#define BS_U8_MAX                                                    \
    (bs_U8)(0xff)

#define BS_U16_MAX                                                   \
    (bs_U16)(0xffff)

#define BS_U32_MAX                                                   \
    (bs_U32)(0xffffffff)

#define BS_U64_MAX                                                   \
    (bs_U64)(0xffffffffffffffff)

#define BS_PRINT_BLACK                                               \
    "\033[0;30m"

#define BS_PRINT_RED                                                 \
    "\033[0;31m"

#define BS_PRINT_RED_BRIGHT                                          \
    "\033[1;31m"

#define BS_PRINT_GREEN                                               \
    "\033[1;32m"

#define BS_PRINT_DARK_GREEN                                          \
    "\033[0;32m"

#define BS_PRINT_YELLOW                                              \
    "\033[0;33m"

#define BS_PRINT_YELLOW_BRIGHT                                       \
    "\033[1;33m"

#define BS_PRINT_BLUE                                                \
    "\033[0;34m"

#define BS_PRINT_BLUE_BRIGHT                                         \
    "\033[1;34m"

#define BS_PRINT_MAGENTA                                             \
    "\033[0;35m"

#define BS_PRINT_MAGENTA_BRIGHT                                      \
    "\033[1;35m"

#define BS_PRINT_CYAN                                                \
    "\033[0;36m"

#define BS_PRINT_CYAN_BRIGHT                                         \
    "\033[1;36m"

#define BS_PRINT_WHITE                                               \
    "\033[0;37m"

#define BS_PRINT_GRAY                                                \
    "\033[38;5;245m"

#define BS_PRINT_RESET                                               \
    "\033[0m"

#define BS_PRINT_COLOR(string, color)                                \
    color string BS_PRINT_RESET

#define BS_PRINT_BLACK_UNDERLINED                                    \
    "\033[4;30m"

#define BS_PRINT_RED_UNDERLINED                                      \
    "\033[4;31m"

#define BS_PRINT_GREEN_UNDERLINED                                    \
    "\033[4;32m"

#define BS_PRINT_YELLOW_UNDERLINED                                   \
    "\033[4;33m"

#define BS_PRINT_BLUE_UNDERLINED                                     \
    "\033[4;34m"

#define BS_PRINT_MAGENTA_UNDERLINED                                  \
    "\033[4;35m"

#define BS_PRINT_CYAN_UNDERLINED                                     \
    "\033[4;36m"

#define BS_PRINT_WHITE_UNDERLINED                                    \
    "\033[4;37m"

#define BS_VERSION                                                   \
    "1.0"

#define BS_VERTEX_DECLARATION_STRUCTURE(count)                       \
        struct {                                                     \
            bs_Batch* batch;                                         \
            bs_U32* offset;                                          \
            bool populated;                                          \
            int attributes_count;                                    \
            struct bs_VertexDeclarationAttribute {                   \
                int source_size;                                     \
                int source_offset;                                   \
                int destination_offset;                              \
                const char* attribute_name;                          \
            } attributes[count];                                     \
        }

#define BS_VERTEX_DECLARATION_QUALIFIER(type, name)                  \
    type name;

#define BS_VERTEX_ATTRIBUTE_QUALIFIER(type, name)                    \
    {                                                                \
        .source_size = sizeof(type),                                 \
        .attribute_name = #name,                                     \
    },

#define BS_VERTEX_DECLARATION(declaration_name, batch, offset_p, ...) \
        typedef BS_VERTEX_DECLARATION_STRUCTURE(__VA_NARG__(__VA_ARGS__) / 2) bs_VertexDeclaration2; \
        bs_VertexDeclaration2 declaration_name = {                   \
            .attributes_count = __VA_NARG__(__VA_ARGS__) / 2,        \
            .attributes = {                                          \
                __VA_FOR_2__(BS_VERTEX_ATTRIBUTE_QUALIFIER, __VA_ARGS__) \
            }                                                        \
        };                                                           \
        typedef struct {                                             \
            __VA_FOR_2__(BS_VERTEX_DECLARATION_QUALIFIER, __VA_ARGS__) \
        } bs_Vertex;                                                 \
        declaration_name.batch = batch;                              \
        declaration_name.offset = offset_p;                          \
        if (!declaration_name.populated)                             \
            bs_populateVertexDeclaration(&declaration_name, batch->attributes, batch->attributes_count)

#define BS_NUM_CUBE_VERTICES                                         \
    36

#define BS_NUM_CUBE_INDICES                                          \
    36

#define BS_NUM_SLOPE_VERTICES                                        \
    24

#define BS_NUM_SLOPE_INDICES                                         \
    24

#define BS_STRING_GEN_2(TYPE, FUNC, ...)                             \
    { .size = sizeof(TYPE), .func = #FUNC, __VA_OPT__(.is_required = __VA_ARGS__) },

#define BS_PARSE_FORMAT(format, data, len)                           \
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

#define BSI_LOG_CREATED(text)                                        \
    (_bs_args.color_log ? (BS_PRINT_GREEN "+ " BS_PRINT_RESET text) : ("+ " text))

#define BSI_LOG_ALTERED(text)                                        \
    (_bs_args.color_log ? (BS_PRINT_YELLOW "/ " BS_PRINT_RESET text) : ("/ " text))

#define BSI_LOG_DELETED(text)                                        \
    (_bs_args.color_log ? (BS_PRINT_RED "- " BS_PRINT_RESET text) : ("- " text))

#define BS_JSON_PRETTY                                               \
    (1 << 0)

#define BS_JSON_ESCAPE_UNICODE                                       \
    (1 << 1)

#define BS_JSON_ESCAPE_SLASHES                                       \
    (1 << 2)

#define BS_JSON_ALLOW_INF_AND_NAN                                    \
    (1 << 3)

#define BS_JSON_INF_AND_NAN_AS_NULL                                  \
    (1 << 4)

#define BS_JSON_ALLOW_INVALID_UNICODE                                \
    (1 << 5)

#define BS_JSON_PRETTY_TWO_SPACES                                    \
    (1 << 6)

#define BS_JSON_NEWLINE_AT_END                                       \
    (1 << 7)

#define bs_foreachJson(json, e)                                      \
    	for (bs_JsonEnumeration e = bs_beginEnumeration(json); e.key; bs_enumerateJson(json, &e))

#define bs_jsonValue(x)                                              \
    _Generic((0, x),                                                 \
        int: bs_jsonValueFromInteger,                                \
        long: bs_jsonValueFromInteger,                               \
        long long: bs_jsonValueFromInteger,                          \
        unsigned int: bs_jsonValueFromInteger,                       \
        unsigned long: bs_jsonValueFromInteger,                      \
        unsigned long long: bs_jsonValueFromInteger,                 \
        short: bs_jsonValueFromInteger,                              \
        unsigned short: bs_jsonValueFromInteger,                     \
        char: bs_jsonValueFromInteger,                               \
        unsigned char: bs_jsonValueFromInteger,                      \
        bool: bs_jsonValueFromBool,                                  \
        float: bs_jsonValueFromFloat,                                \
        double: bs_jsonValueFromFloat,                               \
        char*: bs_jsonValueFromString,                               \
        const char*: bs_jsonValueFromString,                         \
        bs_Json: bs_jsonValueFromRoot,                               \
        bs_DateTime: bs_jsonValueFromDateTime,                       \
        bs_RGBA: bs_jsonRGBA,                                        \
        bs_vec2*: bs_jsonVec2,                                       \
        bs_vec3*: bs_jsonVec3,                                       \
        bs_vec4*: bs_jsonVec4                                        \
    	)(x)

#define BS_JSONIFY_FIELD(field, value)                               \
    bs_ensureJson(&_tmp, bs_jsonValue(value), field);

#define BS_JSONIFY(json, ...)                                        \
        ({                                                           \
            bs_JsonValue _obj = bs_jsonObject();                     \
            bs_Json _tmp = bs_jsonRoot(json, _obj.as_object);        \
             __VA_FOR_2__(BS_JSONIFY_FIELD, __VA_ARGS__);            \
           _obj;                                                     \
         })

#define BS_ALL_EXCEPTIONS                                            \
    0xFFFFFFFFFFFFFFFF

#define BS_ERROR_HEADER                                              \
    BS_PRINT_COLOR("[ERR] ", BS_PRINT_RED)

#define BS_WARN_HEADER                                               \
    BS_PRINT_COLOR("[WRN] ", BS_PRINT_YELLOW)

#define BS_INFO_HEADER                                               \
    BS_PRINT_COLOR("[INF] ", BS_PRINT_CYAN)

#define BS_STACK_LIST(type, c)                                       \
        { .capacity = c, .data = bs_alloca(c * sizeof(type)), .unit_size = sizeof(type) }

#define BS_SWAP_SIZE(type)                                           \
    (sizeof(*((type*)NULL)->_))

#define BS_SWAPS_COUNT(flags)                                        \
    ((flags & BS_OBJECT_HAS_SWAPS_BIT) ? (bs_scope()->context ? bs_scope()->context->frames_in_flight : bs_instance()->max_frames_in_flight) : 1)

#define BS_OBJECT(type, source_id, id, swaps_count, flags, object_type) \
        bs_object(source_id, id, sizeof(type), BS_SWAP_SIZE(type), swaps_count, flags, object_type)

#define BS_CONTEXT(source_id, id, flags)                             \
    BS_OBJECT(bs_Context, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_CONTEXT)

#define BS_IMAGE(source_id, id, flags)                               \
    BS_OBJECT(bs_Image, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_IMAGE)

#define BS_SAMPLER(source_id, id, flags)                             \
    BS_OBJECT(bs_Sampler, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_SAMPLER)

#define BS_RENDERER(source_id, id, flags)                            \
    BS_OBJECT(bs_Renderer, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_RENDERER)

#define BS_BATCH(source_id, id, flags)                               \
    BS_OBJECT(bs_Batch, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_BATCH)

#define BS_QUEUE(source_id, id, flags)                               \
    BS_OBJECT(bs_Queue, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_QUEUE)

#define BS_BUFFER(source_id, id, flags)                              \
    BS_OBJECT(bs_Buffer, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_BUFFER)

#define BS_PIPELINE(source_id, id, flags)                            \
    BS_OBJECT(bs_Pipeline, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_PIPELINE)

#define BS_RAY_TRACER(source_id, id, flags)                          \
    BS_OBJECT(bs_RayTracer, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_RAY_TRACER)

#define BS_ATLAS(source_id, id, flags)                               \
    BS_OBJECT(bs_Atlas, source_id, id, BS_SWAPS_COUNT(flags), flags, BS_OBJECT_ATLAS)

#define BS_NUM_STRIKES_RULE                                          \
    (1)

#define BS_QUERY_FORCE_CREATE                                        \
    (1 << 31)

#define BS_QUERY_ALLOW_NULL                                          \
    (1 << 30)

#define BS_QUERY_MODEL_KEEP_JSON                                     \
    (1 << 29)

#define BSAPI                                                        \
    _declspec(dllexport)

#define BS_BLANK                                                     \
    (bs_RGBA) {   0,   0,   0,   0 }

#define BS_BLACK                                                     \
    (bs_RGBA) {   0,   0,   0, 255 }

#define BS_RED                                                       \
    (bs_RGBA) { 255,   0,   0, 255 }

#define BS_GREEN                                                     \
    (bs_RGBA) {   0, 255,   0, 255 }

#define BS_BLUE                                                      \
    (bs_RGBA) {   0,   0, 255, 255 }

#define BS_WHITE                                                     \
    (bs_RGBA) { 255, 255, 255, 255 }

#define BS_YELLOW                                                    \
    (bs_RGBA) { 255, 255,   0, 255 }

#define BS_MAGENTA                                                   \
    (bs_RGBA) { 255,   0, 255, 255 }

#define BS_CYAN                                                      \
    (bs_RGBA) {   0, 255, 255, 255 }

#define BS_ATLAS_TEXTURE_HAS_ALPHA                                   \
    (1 << 0)

#define BS_ATLAS_TEXTURE_IS_SOLID                                    \
    (1 << 1)

#define BS_RENDERER_SUBPASS_HAS_DEPTH(flags, subpass)                \
    (flags & (1 << subpass))

#define BS_SET_BIT(array, index)                                     \
    ((array)[(index) / 8] |=  (1 << ((index) % 8)))

#define BS_CLEAR_BIT(array, index)                                   \
    ((array)[(index) / 8] &= ~(1 << ((index) % 8)))

#define BS_GET_BIT(array, index)                                     \
    (((array)[(index) / 8] >> ((index) % 8)) & 1)

#define BS_WRITE_BIT(array, index, value)                            \
        do { if (value) BS_SET_BIT(array, index); else BS_CLEAR_BIT(array, index); } while (0)

#define BS_LEFT_MOUSE_BUTTON                                         \
    0x01

#define BS_RIGHT_MOUSE_BUTTON                                        \
    0x02

#define BS_CTRL_BRK_PRCS                                             \
    0x03

#define BS_MID_MOUSE_BUTTON                                          \
    0x04

#define BS_THUMB_FORWARD                                             \
    0x05

#define BS_THUMB_BACK                                                \
    0x06

#define BS_KEY_BACKSPACE                                             \
    0x08

#define BS_KEY_TAB                                                   \
    0x09

#define BS_CLEAR                                                     \
    0x0C

#define BS_KEY_ENTER                                                 \
    0x0D

#define BS_KEY_LEFT_SHIFT                                            \
    0x10

#define BS_KEY_LEFT_CONTROL                                          \
    0x11

#define BS_KEY_ALT                                                   \
    0x12

#define BS_PAUSE                                                     \
    0x13

#define BS_CAPSLOCK                                                  \
    0x14

#define BS_KANA                                                      \
    0x15

#define BS_HANGEUL                                                   \
    0x15

#define BS_HANGUL                                                    \
    0x15

#define BS_JUNJU                                                     \
    0x17

#define BS_FINAL                                                     \
    0x18

#define BS_HANJA                                                     \
    0x19

#define BS_KANJI                                                     \
    0x19

#define BS_KEY_ESCAPE                                                \
    0x1B

#define BS_CONVERT                                                   \
    0x1C

#define BS_NONCONVERT                                                \
    0x1D

#define BS_ACCEPT                                                    \
    0x1E

#define BS_MODECHANGE                                                \
    0x1F

#define BS_KEY_SPACE                                                 \
    0x20

#define BS_KEY_PAGEUP                                                \
    0x21

#define BS_KEY_PAGEDOWN                                              \
    0x22

#define BS_KEY_END                                                   \
    0x23

#define BS_KEY_HOME                                                  \
    0x24

#define BS_KEY_LEFT                                                  \
    0x25

#define BS_KEY_UP                                                    \
    0x26

#define BS_KEY_RIGHT                                                 \
    0x27

#define BS_KEY_DOWN                                                  \
    0x28

#define BS_KEY_SELECT                                                \
    0x29

#define BS_KEY_PRINT                                                 \
    0x2A

#define BS_KEY_EXECUTE                                               \
    0x2B

#define BS_KEY_PRINT_SCREEN                                          \
    0x2C

#define BS_KEY_INSERT                                                \
    0x2D

#define BS_KEY_DELETE                                                \
    0x2E

#define BS_HELP                                                      \
    0x2F

#define BS_KEY_0                                                     \
    0x30

#define BS_KEY_1                                                     \
    0x31

#define BS_KEY_2                                                     \
    0x32

#define BS_KEY_3                                                     \
    0x33

#define BS_KEY_4                                                     \
    0x34

#define BS_KEY_5                                                     \
    0x35

#define BS_KEY_6                                                     \
    0x36

#define BS_KEY_7                                                     \
    0x37

#define BS_KEY_8                                                     \
    0x38

#define BS_KEY_9                                                     \
    0x39

#define BS_KEY_A                                                     \
    0x41

#define BS_KEY_B                                                     \
    0x42

#define BS_KEY_C                                                     \
    0x43

#define BS_KEY_D                                                     \
    0x44

#define BS_KEY_E                                                     \
    0x45

#define BS_KEY_F                                                     \
    0x46

#define BS_KEY_G                                                     \
    0x47

#define BS_KEY_H                                                     \
    0x48

#define BS_KEY_I                                                     \
    0x49

#define BS_KEY_J                                                     \
    0x4A

#define BS_KEY_K                                                     \
    0x4B

#define BS_KEY_L                                                     \
    0x4C

#define BS_KEY_M                                                     \
    0x4D

#define BS_KEY_N                                                     \
    0x4E

#define BS_KEY_O                                                     \
    0x4F

#define BS_KEY_P                                                     \
    0x50

#define BS_KEY_Q                                                     \
    0x51

#define BS_KEY_R                                                     \
    0x52

#define BS_KEY_S                                                     \
    0x53

#define BS_KEY_T                                                     \
    0x54

#define BS_KEY_U                                                     \
    0x55

#define BS_KEY_V                                                     \
    0x56

#define BS_KEY_W                                                     \
    0x57

#define BS_KEY_X                                                     \
    0x58

#define BS_KEY_Y                                                     \
    0x59

#define BS_KEY_Z                                                     \
    0x5A

#define BS_LEFT_WIN                                                  \
    0x5B

#define BS_RIGHT_WIN                                                 \
    0x5C

#define BS_APPS                                                      \
    0x5D

#define BS_SLEEP                                                     \
    0x5F

#define BS_NUMPAD0                                                   \
    0x60

#define BS_NUMPAD1                                                   \
    0x61

#define BS_NUMPAD2                                                   \
    0x62

#define BS_NUMPAD3                                                   \
    0x63

#define BS_NUMPAD4                                                   \
    0x64

#define BS_NUMPAD5                                                   \
    0x65

#define BS_NUMPAD6                                                   \
    0x66

#define BS_NUMPAD7                                                   \
    0x67

#define BS_NUMPAD8                                                   \
    0x68

#define BS_NUMPAD9                                                   \
    0x69

#define BS_MULTIPLY                                                  \
    0x6A

#define BS_ADD                                                       \
    0x6B

#define BS_SEPARATOR                                                 \
    0x6C

#define BS_SUBTRACT                                                  \
    0x6D

#define BS_DECIMAL                                                   \
    0x6E

#define BS_DIVIDE                                                    \
    0x6F

#define BS_KEY_F1                                                    \
    0x70

#define BS_KEY_F2                                                    \
    0x71

#define BS_KEY_F3                                                    \
    0x72

#define BS_KEY_F4                                                    \
    0x73

#define BS_KEY_F5                                                    \
    0x74

#define BS_KEY_F6                                                    \
    0x75

#define BS_KEY_F7                                                    \
    0x76

#define BS_KEY_F8                                                    \
    0x77

#define BS_KEY_F9                                                    \
    0x78

#define BS_KEY_F10                                                   \
    0x79

#define BS_KEY_F11                                                   \
    0x7A

#define BS_KEY_F12                                                   \
    0x7B

#define BS_KEY_F13                                                   \
    0x7C

#define BS_KEY_F14                                                   \
    0x7D

#define BS_KEY_F15                                                   \
    0x7E

#define BS_KEY_F16                                                   \
    0x7F

#define BS_KEY_F17                                                   \
    0x80

#define BS_KEY_F18                                                   \
    0x81

#define BS_KEY_F19                                                   \
    0x82

#define BS_KEY_F20                                                   \
    0x83

#define BS_KEY_F21                                                   \
    0x84

#define BS_KEY_F22                                                   \
    0x85

#define BS_KEY_F23                                                   \
    0x86

#define BS_KEY_F24                                                   \
    0x87

#define BS_NAVIGATION_VIEW                                           \
    0x88

#define BS_NAVIGATION_MENU                                           \
    0x89

#define BS_NAVIGATION_UP                                             \
    0x8A

#define BS_NAVIGATION_DOWN                                           \
    0x8B

#define BS_NAVIGATION_LEFT                                           \
    0x8C

#define BS_NAVIGATION_RIGHT                                          \
    0x8D

#define BS_NAVIGATION_ACCEPT                                         \
    0x8E

#define BS_NAVIGATION_CANCEL                                         \
    0x8F

#define BS_NUMLOCK                                                   \
    0x90

#define BS_SCROLLLOCK                                                \
    0x91

#define BS_NUMPAD_EQUAL                                              \
    0x92

#define BS_FJ_JISHO                                                  \
    0x92

#define BS_FJ_MASSHOU                                                \
    0x93

#define BS_FJ_TOUROKU                                                \
    0x94

#define BS_FJ_LOYA                                                   \
    0x95

#define BS_FJ_ROYA                                                   \
    0x96

#define BS_KEY_RIGHT_SHIFT                                           \
    0xA1

#define BS_KEY_LEFT_CTRL                                             \
    0xA2

#define BS_KEY_RIGHT_CTRL                                            \
    0xA3

#define BS_KEY_LEFT_MENU                                             \
    0xA4

#define BS_KEY_RIGHT_MENU                                            \
    0xA5

#define BS_BROWSER_BACK                                              \
    0xA6

#define BS_BROWSER_FORWARD                                           \
    0xA7

#define BS_BROWSER_REFRESH                                           \
    0xA8

#define BS_BROWSER_STOP                                              \
    0xA9

#define BS_BROWSER_SEARCH                                            \
    0xAA

#define BS_BROWSER_FAVORITES                                         \
    0xAB

#define BS_BROWSER_HOME                                              \
    0xAC

#define BS_VOLUME_MUTE                                               \
    0xAD

#define BS_VOLUME_DOWN                                               \
    0xAE

#define BS_VOLUME_UP                                                 \
    0xAF

#define BS_NEXT_TRACK                                                \
    0xB0

#define BS_PREV_TRACK                                                \
    0xB1

#define BS_STOP                                                      \
    0xB2

#define BS_PLAY_PAUSE                                                \
    0xB3

#define BS_MAIL                                                      \
    0xB4

#define BS_MEDIA_SELECT                                              \
    0xB5

#define BS_APP1                                                      \
    0xB6

typedef void (__cdecl* bs_VoidFunction)();
typedef int (__cdecl* bs_ThreadFunction)(void*);
typedef bs_Result (__cdecl* bs_ForeachDocumentFunction)(bs_FileInfo, void*);
typedef void (__stdcall* bs_MessageFunction)(const bs_LogQueueItem*);
typedef void (__stdcall* bs_NameObjectFunction)(bs_Object*, const char*);
typedef void (__stdcall* bs_ValidationErrorFunction)();
typedef void (__stdcall* bs_ContextTickFunction)(bs_VoidFunction);
typedef void (__stdcall* bs_ConfigureWindowFunction)(bs_Context*);
typedef bs_NonClientArea (__stdcall* bs_NonClientAreaTickFunction)(bs_Context*, bs_ivec2);
typedef void (__stdcall* bs_ResizeContextFunction)(bs_Context*);
typedef void (__stdcall* bs_SubpassFunction)(bs_RendererScope*);
typedef void (__stdcall* bs_ContextTickFunction)(bs_Context* context);
typedef long long bs_I64;
typedef int bs_I32;
typedef short bs_I16;
typedef char bs_I8;
typedef void* bs_JsonObject;
typedef unsigned long long bs_U64;
typedef unsigned int bs_U32;
typedef unsigned short bs_U16;
typedef unsigned char bs_U8;
typedef double bs_F64;
typedef float bs_F32;
typedef bs_U32 bs_IniBits;
typedef bs_U32 bs_SlotBits;
typedef bs_U32 bs_SwapchainBits;
typedef bs_U32 bs_BufferUsageFlags;
typedef bs_U32 bs_MemoryPropertyFlags;
typedef bs_U32 bs_DependencyFlags;
typedef bs_U32 bs_CullFlags;
typedef bs_U32 bs_ImageBits;
typedef bs_U32 bs_SamplerBits;
typedef bs_U32 bs_PipelineFlags;
typedef bs_U32 bs_ShaderBits;
typedef bs_U32 bs_BufferBits;
typedef bs_U32 bs_RendererBits;
typedef bs_U32 bs_OutputFlags;
typedef bs_U32 bs_InputBits;
typedef bs_U32 bs_BatchBits;
typedef bs_U32 bs_QueueBits;
typedef bs_U32 bs_ModelFlags;
typedef bs_U32 bs_ArmatureFlags;
typedef bs_U32 bs_AnimationFlags;
typedef bs_U32 bs_SaveJsonBits;
typedef void (*bs_Callback)();
typedef BS_VERTEX_DECLARATION_STRUCTURE() bs_VertexDeclaration;
enum bs_Library {
    BS_LIBRARY_UNDEFINED,
    BS_LIBRARY_BASILISK,
    BS_LIBRARY_YYJSON,
    BS_LIBRARY_LODEPNG,
    BS_LIBRARY_VULKAN,
    BS_LIBRARY_WIN32,
    BS_LIBRARIES_COUNT,
};

enum bs_MessageLevel {
    BS_MESSAGE_INFO,
    BS_MESSAGE_WARNING,
    BS_MESSAGE_VALIDATION_ERROR,
    BS_MESSAGE_LEVELS_COUNT,
};

enum bs_Result {
    BS_RESULT_OK,
    BS_RESULT_WAITING,
    BS_RESULT_GENERAL_ERROR,
    BS_RESULT_INTEGER_OVERFLOW,
    BS_RESULT_INVALID_BASE64_PADDING,
    BS_RESULT_INVALID_PARAM,
    BS_RESULT_INVALID_TYPE,
    BS_RESULT_INVALID_STATE,
    BS_RESULT_CORRUPTED,
    BS_RESULT_NOT_SUPPORTED,
    BS_RESULT_NOT_IMPLEMENTED,
    BS_RESULT_FAILED_TO_QUERY,
    BS_RESULT_FAILED_TO_WRITE,
    BS_RESULT_FAILED_TO_ENCODE,
    BS_RESULT_FAILED_TO_READ,
    BS_RESULT_FAILED_TO_INSPECT,
    BS_RESULT_FAILED_TO_PARSE,
    BS_RESULT_OUT_OF_BOUNDS,
    BS_RESULT_VALIDATION_ERROR,
    BS_RESULT_ZERO_ALLOC,
};

enum bs_IniFlag {
    BS_INI_AUDIO_BIT = 1 << 0,
    BS_INI_STEAM_BIT = 1 << 1,
    BS_INI_STEAM_INPUT_BIT = 1 << 2,
};

enum bs_NonClientArea {
    BS_CLIENT_AREA = 0,
    BS_NON_CLIENT_AREA_CAPTION = 1,
    BS_NON_CLIENT_AREA_CAPTION_BUTTON = 2,
};

enum bs_WindowType {
    BS_WINDOW_DEFAULT = 0,
    BS_WINDOW_NO_TITLE_BAR = 1,
    BS_WINDOW_MENU = 2,
};

enum bs_ImageFilter {
    BS_FILTER_NEAREST = 0,
    BS_FILTER_LINEAR = 1,
};

enum bs_PngType {
    BS_PNG_RGB = 0,
    BS_PNG_RGBA = 1,
    BS_PNG_GREY = 2,
    BS_PNG_GREY_ALPHA = 3,
};

enum bs_Slot {
    BS_SLOT_NONE = 0,
    BS_SLOT_00_BIT = 1 << 0,
    BS_SLOT_01_BIT = 1 << 1,
    BS_SLOT_02_BIT = 1 << 2,
    BS_SLOT_03_BIT = 1 << 3,
    BS_SLOT_04_BIT = 1 << 4,
    BS_SLOT_05_BIT = 1 << 5,
    BS_SLOT_06_BIT = 1 << 6,
    BS_SLOT_07_BIT = 1 << 7,
    BS_SLOT_08_BIT = 1 << 8,
    BS_SLOT_09_BIT = 1 << 9,
    BS_SLOT_10_BIT = 1 << 10,
    BS_SLOT_11_BIT = 1 << 11,
    BS_SLOT_12_BIT = 1 << 12,
    BS_SLOT_13_BIT = 1 << 13,
    BS_SLOT_14_BIT = 1 << 14,
    BS_SLOT_15_BIT = 1 << 15,
    BS_SLOT_16_BIT = 1 << 16,
    BS_SLOT_17_BIT = 1 << 17,
    BS_SLOT_18_BIT = 1 << 18,
    BS_SLOT_19_BIT = 1 << 19,
    BS_SLOT_20_BIT = 1 << 20,
    BS_SLOT_21_BIT = 1 << 21,
    BS_SLOT_22_BIT = 1 << 22,
    BS_SLOT_23_BIT = 1 << 23,
    BS_SLOT_24_BIT = 1 << 24,
    BS_SLOT_25_BIT = 1 << 25,
    BS_SLOT_26_BIT = 1 << 26,
    BS_SLOT_27_BIT = 1 << 27,
    BS_SLOT_28_BIT = 1 << 28,
    BS_SLOT_29_BIT = 1 << 29,
    BS_SLOT_30_BIT = 1 << 30,
    BS_SLOT_31_BIT = 1 << 31,
};

enum bs_BufferUsageFlag {
    BS_BUFFER_USAGE_TRANSFER_SRC_BIT = 1 << 0,
    BS_BUFFER_USAGE_TRANSFER_DST_BIT = 1 << 1,
    BS_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = 1 << 2,
    BS_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = 1 << 3,
    BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT = 1 << 4,
    BS_BUFFER_USAGE_STORAGE_BUFFER_BIT = 1 << 5,
    BS_BUFFER_USAGE_INDEX_BUFFER_BIT = 1 << 6,
    BS_BUFFER_USAGE_VERTEX_BUFFER_BIT = 1 << 7,
    BS_BUFFER_USAGE_INDIRECT_BUFFER_BIT = 1 << 8,
};

enum bs_MemoryPropertyFlag {
    BS_MEMORY_PROPERTY_DEVICE_LOCAL_BIT = 1 << 0,
    BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT = 1 << 1,
    BS_MEMORY_PROPERTY_HOST_COHERENT_BIT = 1 << 2,
    BS_MEMORY_PROPERTY_HOST_CACHED_BIT = 1 << 3,
    BS_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT = 1 << 4,
};

enum bs_AccessMask {
    BS_ACCESS_INDIRECT_COMMAND_READ_BIT = 1 << 0,
    BS_ACCESS_INDEX_READ_BIT = 1 << 1,
    BS_ACCESS_VERTEX_ATTRIBUTE_READ_BIT = 1 << 2,
    BS_ACCESS_UNIFORM_READ_BIT = 1 << 3,
    BS_ACCESS_INPUT_ATTACHMENT_READ_BIT = 1 << 4,
    BS_ACCESS_SHADER_READ_BIT = 1 << 5,
    BS_ACCESS_SHADER_WRITE_BIT = 1 << 6,
    BS_ACCESS_COLOR_ATTACHMENT_READ_BIT = 1 << 7,
    BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT = 1 << 8,
    BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = 1 << 9,
    BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 1 << 10,
    BS_ACCESS_TRANSFER_READ_BIT = 1 << 11,
    BS_ACCESS_TRANSFER_WRITE_BIT = 1 << 12,
    BS_ACCESS_HOST_READ_BIT = 1 << 13,
    BS_ACCESS_HOST_WRITE_BIT = 1 << 14,
    BS_ACCESS_MEMORY_READ_BIT = 1 << 15,
    BS_ACCESS_MEMORY_WRITE_BIT = 1 << 16,
};

enum bs_PipelineStage {
    BS_PIPELINE_STAGE_TOP_OF_PIPE_BIT = 1 << 0,
    BS_PIPELINE_STAGE_DRAW_INDIRECT_BIT = 1 << 1,
    BS_PIPELINE_STAGE_VERTEX_INPUT_BIT = 1 << 2,
    BS_PIPELINE_STAGE_VERTEX_SHADER_BIT = 1 << 3,
    BS_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = 1 << 4,
    BS_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = 1 << 5,
    BS_PIPELINE_STAGE_GEOMETRY_SHADER_BIT = 1 << 6,
    BS_PIPELINE_STAGE_FRAGMENT_SHADER_BIT = 1 << 7,
    BS_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = 1 << 8,
    BS_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = 1 << 9,
    BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = 1 << 10,
    BS_PIPELINE_STAGE_COMPUTE_SHADER_BIT = 1 << 11,
    BS_PIPELINE_STAGE_TRANSFER_BIT = 1 << 12,
    BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = 1 << 13,
    BS_PIPELINE_STAGE_HOST_BIT = 1 << 14,
    BS_PIPELINE_STAGE_ALL_GRAPHICS_BIT = 1 << 15,
    BS_PIPELINE_STAGE_ALL_COMMANDS_BIT = 1 << 16,
};

enum bs_DependencyFlag {
    BS_DEPENDENCY_BY_REGION_BIT = 1 << 0,
};

enum bs_CullModeFlag {
    BS_CULL_MODE_NONE = 0,
    BS_CULL_MODE_FRONT_BIT = 1 << 0,
    BS_CULL_MODE_BACK_BIT = 1 << 1,
    BS_CULL_MODE_FRONT_AND_BACK = 0x00000003,
};

enum bs_StencilFaceFlag {
    BS_STENCIL_FACE_FRONT_BIT = 1 << 0,
    BS_STENCIL_FACE_BACK_BIT = 1 << 1,
    BS_STENCIL_FACE_FRONT_AND_BACK = 0x00000003,
    BS_STENCIL_FRONT_AND_BACK = 0,
};

enum bs_StencilOp {
    BS_STENCIL_OP_KEEP = 0,
    BS_STENCIL_OP_ZERO = 1,
    BS_STENCIL_OP_REPLACE = 2,
    BS_STENCIL_OP_INCREMENT_AND_CLAMP = 3,
    BS_STENCIL_OP_DECREMENT_AND_CLAMP = 4,
    BS_STENCIL_OP_INVERT = 5,
    BS_STENCIL_OP_INCREMENT_AND_WRAP = 6,
    BS_STENCIL_OP_DECREMENT_AND_WRAP = 7,
};

enum bs_BlendFactor {
    BS_BLEND_FACTOR_ZERO = 0,
    BS_BLEND_FACTOR_ONE = 1,
    BS_BLEND_FACTOR_SRC_COLOR = 2,
    BS_BLEND_FACTOR_ONE_MINUS_SRC_COLOR = 3,
    BS_BLEND_FACTOR_DST_COLOR = 4,
    BS_BLEND_FACTOR_ONE_MINUS_DST_COLOR = 5,
    BS_BLEND_FACTOR_SRC_ALPHA = 6,
    BS_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 7,
    BS_BLEND_FACTOR_DST_ALPHA = 8,
    BS_BLEND_FACTOR_ONE_MINUS_DST_ALPHA = 9,
    BS_BLEND_FACTOR_CONSTANT_COLOR = 10,
    BS_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 11,
    BS_BLEND_FACTOR_CONSTANT_ALPHA = 12,
    BS_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 13,
    BS_BLEND_FACTOR_SRC_ALPHA_SATURATE = 14,
    BS_BLEND_FACTOR_SRC1_COLOR = 15,
    BS_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR = 16,
    BS_BLEND_FACTOR_SRC1_ALPHA = 17,
    BS_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA = 18,
};

enum bs_BlendOperationType {
    BS_BLEND_OP_ADD = 0,
    BS_BLEND_OP_SUBTRACT = 1,
    BS_BLEND_OP_REVERSE_SUBTRACT = 2,
    BS_BLEND_OP_MIN = 3,
    BS_BLEND_OP_MAX = 4,
};

enum bs_CompareOp {
    BS_COMPARE_OP_NEVER = 0,
    BS_COMPARE_OP_LESS = 1,
    BS_COMPARE_OP_EQUAL = 2,
    BS_COMPARE_OP_LESS_OR_EQUAL = 3,
    BS_COMPARE_OP_GREATER = 4,
    BS_COMPARE_OP_NOT_EQUAL = 5,
    BS_COMPARE_OP_GREATER_OR_EQUAL = 6,
    BS_COMPARE_OP_ALWAYS = 7,
};

enum bs_TopologyType {
    BS_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
    BS_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
    BS_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
    BS_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
    BS_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
    BS_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
    BS_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
    BS_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
    BS_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
    BS_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
    BS_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
};

enum bs_PolygonType {
    BS_POLYGON_MODE_FILL = 0,
    BS_POLYGON_MODE_LINE = 1,
    BS_POLYGON_MODE_POINT = 2,
};

enum bs_StoreOp {
    BS_ATTACHMENT_STORE_OP_STORE = 0,
    BS_ATTACHMENT_STORE_OP_DONT_CARE = 1,
};

enum bs_LoadOp {
    BS_ATTACHMENT_LOAD_OP_LOAD = 0,
    BS_ATTACHMENT_LOAD_OP_CLEAR = 1,
    BS_ATTACHMENT_LOAD_OP_DONT_CARE = 2,
};

enum bs_ColliderType {
    BS_COLLIDER_NONE = 0,
    BS_COLLIDER_SPHERE = 1,
    BS_COLLIDER_AABB = 2,
};

enum bs_ObjectFlag {
    BS_OBJECT_SHOULD_LOAD = (1 << 0),
    BS_OBJECT_HAS_SWAPS_BIT = (1 << 1),
    BS_OBJECT_FORCE_DESTROY = (1 << 2),
    BS_OBJECT_ALREADY_EXISTS = (1 << 3),
    BS_OBJECT_WAS_CREATED = (1 << 4),
    BS_OBJECT_WAS_ALTERED = (1 << 5),
};

enum bs_ResourceType {
    BS_RESOURCE_BINARY = 0,
    BS_RESOURCE_IMAGE = 1,
    BS_RESOURCE_MODEL = 2,
    BS_RESOURCE_SHADER = 3,
    BS_RESOURCE_SOUND = 4,
    BS_RESOURCE_ATLAS = 5,
    BS_RESOURCE_FONT = 6,
    BS_RESOURCE_BINDING = 7,
    BSGFX_RESOURCE_PRIMITIVE = 8,
    BSGFX_RESOURCE_PREFAB = 9,
    BSGFX_RESOURCE_TILE = 10,
    BSGFX_RESOURCE_LIGHT = 11,
    BS_RESOURCE_TYPE_COUNT = 12,
};

enum bs_ImageBit {
    BS_IMAGE_SWAPS_BIT = 1 << 0,
    BS_IMAGE_SHADER_ACCESSIBLE_BIT = 1 << 4,
    BS_IMAGE_ATTACHMENT_BIT = 1 << 5,
    BS_IMAGE_INPUT_ATTACHMENT_BIT = 1 << 6,
    BS_IMAGE_USAGE_TRANSFER_DST_BIT = 1 << 7,
    BS_IMAGE_USAGE_TRANSFER_SRC_BIT = 1 << 8,
    BS_IMAGE_IS_BOUND = 1 << 10,
    BS_IMAGE_USAGE_STORAGE_BIT = 1 << 13,
};

enum bs_AtlasFlag {
    BS_ATLAS_FORCE_CREATE = 1 << 0,
};

enum bs_SamplerBit {
    BS_SAMPLER_SWAPS_BIT = 1 << 0,
    BS_SAMPLER_MAG_NEAREST = 1 << 1,
    BS_SAMPLER_FORCE_CREATE = 1 << 2,
};

enum bs_PipelineFlag {
    BS_PIPELINE_NEEDS_UPDATING = 1 << 1,
    BS_PIPELINE_FORCE_CREATE = 1 << 2,
};

enum bs_PipelineType {
    BS_PIPELINE_GRAPHICS = 0,
    BS_PIPELINE_COMPUTE = 1,
    BS_PIPELINE_RAY_TRACE = 2,
    BS_PIPELINE_TYPE_COUNT = 3,
};

enum bs_ShaderBit {
    BS_SHADER_FORCE_CREATE = 1 << 0,
    BS_SHADER_ENSURE_RETURN = 1 << 1,
    BS_SHADER_KEEP_SPIRV = 1 << 2,
};

enum bs_BufferBit {
    BSI_BUFFER_SWAPS_BIT = 1 << 0,
    BSI_BUFFER_IS_BOUND = 1 << 1,
    BS_BUFFER_PRE_MAP = 1 << 2,
    BS_BUFFER_IS_NAMED = 1 << 3,
};

enum bs_RendererBit {
    BSI_RENDERER_SUBPASS_00_DEPTH_BIT = (1 << 0),
    BSI_RENDERER_SUBPASS_01_DEPTH_BIT = (1 << 1),
    BSI_RENDERER_SUBPASS_02_DEPTH_BIT = (1 << 2),
    BSI_RENDERER_SUBPASS_03_DEPTH_BIT = (1 << 3),
    BSI_RENDERER_SUBPASS_04_DEPTH_BIT = (1 << 4),
    BSI_RENDERER_SUBPASS_05_DEPTH_BIT = (1 << 5),
    BSI_RENDERER_HAS_SWAPS_BIT = (1 << 7),
};

enum bs_OutputFlag {
    BS_OUTPUT_SELF_DEPENDENCY = (1 << 0),
    BS_OUTPUT_EXTERNAL_DEPENDENCY = (1 << 1),
};

enum bs_InputBit {
    BS_INPUT_AWAIT_WRITE = (1 << 0),
};

enum bs_BatchBit {
    BS_BATCH_FORCE_DESTROY = (1 << 0),
    BS_BATCH_IS_PUSHED = (1 << 1),
    BS_BATCH_KEEP_DATA = (1 << 2),
    BSI_BATCH_SWAPS_BIT = (1 << 3),
    BS_BATCH_RAY_TRACEABLE = (1 << 4),
    BS_BATCH_IS_CREATED = (1 << 5),
};

enum bs_QueueBit {
    BSI_QUEUE_SWAPS_BIT = (1 << 0),
    BS_QUEUE_GRAPHICS_BIT = (1 << 1),
    BS_QUEUE_COMPUTE_BIT = (1 << 2),
    BS_QUEUE_TRANSFER_BIT = (1 << 3),
    BS_QUEUE_SINGLE_TIMES_BIT = (1 << 4),
    BS_QUEUE_DONT_SIGNAL = (1 << 5),
};

enum bs_ModelFlag {
    BS_MODEL_FORCE_DESTROY = 1 << 0,
    BS_MODEL_JUST_CREATED = 1 << 1,
    BS_MODEL_KEEP_JSON = 1 << 2,
};

enum bs_ArmatureFlag {
    BS_ARMATURE_FORCE_DESTROY = 1 << 0,
};

enum bs_AnimationFlag {
    BS_ANIMATION_FORCE_DESTROY = 1 << 0,
};

enum bs_EndpointType {
    BS_ENDPOINT_NONE = 0,
    BS_GET = 1,
    BS_PUT = 2,
    BS_POST = 3,
};

enum bs_CursorIcon {
    BS_CURSOR_DEFAULT = 0,
    BS_CURSOR_TEXT = 1,
    BS_CURSOR_TYPE_COUNT = 2,
};

enum bs_ObjectType {
    BS_OBJECT_CONTEXT,
    BS_OBJECT_IMAGE,
    BS_OBJECT_SAMPLER,
    BS_OBJECT_BUFFER,
    BS_OBJECT_QUEUE,
    BS_OBJECT_BATCH,
    BS_OBJECT_RENDERER,
    BS_OBJECT_RAY_TRACER,
    BS_OBJECT_ATLAS,
    BS_OBJECT_TYPE_COUNT,
};

enum bs_SurfaceType {
    BS_SURFACE_TYPE_UNDEFINED = 0,
    BS_SURFACE_TYPE_WIN32 = 1,
    BS_SURFACE_TYPE_WAYLAND = 2,
    BS_SURFACE_TYPE_X11 = 3,
    BS_SURFACE_TYPE_HEADLESS = 4,
};

enum bs_SwapchainMode {
    BS_SWAPCHAIN_MODE_SINGLE = 1,
    BS_SWAPCHAIN_MODE_DOUBLE = 2,
    BS_SWAPCHAIN_MODE_TRIPLE = 3,
    BS_SWAPCHAIN_MODE_MAX = 3,
};

enum bs_JsonType {
    BS_JSON_UNDEFINED = 1,
    BS_JSON_DONT_CARE = 2,
    BS_JSON_SYNTAX = 1 << 2,
    BS_JSON_OBJECT = 1 << 3,
    BS_JSON_ARRAY = 1 << 4,
    BS_JSON_VALUE_TYPE = 17,
    BS_JSON_STRING = 1 << 5,
    BS_JSON_NUMBER = 1 << 6,
    BS_JSON_NUMBER_INTEGER = 1 << 8,
    BS_JSON_FLOAT = 1 << 9,
    BS_JSON_BOOL = 1 << 10,
    BS_JSON_UCHAR = 1 << 11,
};

enum bs_ShaderType {
    BS_SHADER_STAGE_VERTEX_BIT = 1 << 0,
    BS_SHADER_STAGE_TESSELLATION_CONTROL_BIT = 1 << 1,
    BS_SHADER_STAGE_TESSELLATION_EVALUATION_BIT = 1 << 2,
    BS_SHADER_STAGE_GEOMETRY_BIT = 1 << 3,
    BS_SHADER_STAGE_FRAGMENT_BIT = 1 << 4,
    BS_SHADER_STAGE_COMPUTE_BIT = 1 << 5,
    BS_SHADER_STAGE_ALL_GRAPHICS = 0x0000001F,
    BS_SHADER_STAGE_ALL = 0x7FFFFFFF,
};

enum bs_Format {
    BS_FORMAT_UNDEFINED = 0,
    BS_FORMAT_R4G4_UNORM_PACK8 = 1,
    BS_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
    BS_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
    BS_FORMAT_R5G6B5_UNORM_PACK16 = 4,
    BS_FORMAT_B5G6R5_UNORM_PACK16 = 5,
    BS_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
    BS_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
    BS_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
    BS_FORMAT_R8_UNORM = 9,
    BS_FORMAT_R8_SNORM = 10,
    BS_FORMAT_R8_USCALED = 11,
    BS_FORMAT_R8_SSCALED = 12,
    BS_FORMAT_R8_UINT = 13,
    BS_FORMAT_R8_SINT = 14,
    BS_FORMAT_R8_SRGB = 15,
    BS_FORMAT_R8G8_UNORM = 16,
    BS_FORMAT_R8G8_SNORM = 17,
    BS_FORMAT_R8G8_USCALED = 18,
    BS_FORMAT_R8G8_SSCALED = 19,
    BS_FORMAT_R8G8_UINT = 20,
    BS_FORMAT_R8G8_SINT = 21,
    BS_FORMAT_R8G8_SRGB = 22,
    BS_FORMAT_R8G8B8_UNORM = 23,
    BS_FORMAT_R8G8B8_SNORM = 24,
    BS_FORMAT_R8G8B8_USCALED = 25,
    BS_FORMAT_R8G8B8_SSCALED = 26,
    BS_FORMAT_R8G8B8_UINT = 27,
    BS_FORMAT_R8G8B8_SINT = 28,
    BS_FORMAT_R8G8B8_SRGB = 29,
    BS_FORMAT_B8G8R8_UNORM = 30,
    BS_FORMAT_B8G8R8_SNORM = 31,
    BS_FORMAT_B8G8R8_USCALED = 32,
    BS_FORMAT_B8G8R8_SSCALED = 33,
    BS_FORMAT_B8G8R8_UINT = 34,
    BS_FORMAT_B8G8R8_SINT = 35,
    BS_FORMAT_B8G8R8_SRGB = 36,
    BS_FORMAT_R8G8B8A8_UNORM = 37,
    BS_FORMAT_R8G8B8A8_SNORM = 38,
    BS_FORMAT_R8G8B8A8_USCALED = 39,
    BS_FORMAT_R8G8B8A8_SSCALED = 40,
    BS_FORMAT_R8G8B8A8_UINT = 41,
    BS_FORMAT_R8G8B8A8_SINT = 42,
    BS_FORMAT_R8G8B8A8_SRGB = 43,
    BS_FORMAT_B8G8R8A8_UNORM = 44,
    BS_FORMAT_B8G8R8A8_SNORM = 45,
    BS_FORMAT_B8G8R8A8_USCALED = 46,
    BS_FORMAT_B8G8R8A8_SSCALED = 47,
    BS_FORMAT_B8G8R8A8_UINT = 48,
    BS_FORMAT_B8G8R8A8_SINT = 49,
    BS_FORMAT_B8G8R8A8_SRGB = 50,
    BS_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
    BS_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
    BS_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
    BS_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
    BS_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
    BS_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
    BS_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
    BS_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
    BS_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
    BS_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
    BS_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
    BS_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
    BS_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
    BS_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
    BS_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
    BS_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
    BS_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
    BS_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
    BS_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
    BS_FORMAT_R16_UNORM = 70,
    BS_FORMAT_R16_SNORM = 71,
    BS_FORMAT_R16_USCALED = 72,
    BS_FORMAT_R16_SSCALED = 73,
    BS_FORMAT_R16_UINT = 74,
    BS_FORMAT_R16_SINT = 75,
    BS_FORMAT_R16_SFLOAT = 76,
    BS_FORMAT_R16G16_UNORM = 77,
    BS_FORMAT_R16G16_SNORM = 78,
    BS_FORMAT_R16G16_USCALED = 79,
    BS_FORMAT_R16G16_SSCALED = 80,
    BS_FORMAT_R16G16_UINT = 81,
    BS_FORMAT_R16G16_SINT = 82,
    BS_FORMAT_R16G16_SFLOAT = 83,
    BS_FORMAT_R16G16B16_UNORM = 84,
    BS_FORMAT_R16G16B16_SNORM = 85,
    BS_FORMAT_R16G16B16_USCALED = 86,
    BS_FORMAT_R16G16B16_SSCALED = 87,
    BS_FORMAT_R16G16B16_UINT = 88,
    BS_FORMAT_R16G16B16_SINT = 89,
    BS_FORMAT_R16G16B16_SFLOAT = 90,
    BS_FORMAT_R16G16B16A16_UNORM = 91,
    BS_FORMAT_R16G16B16A16_SNORM = 92,
    BS_FORMAT_R16G16B16A16_USCALED = 93,
    BS_FORMAT_R16G16B16A16_SSCALED = 94,
    BS_FORMAT_R16G16B16A16_UINT = 95,
    BS_FORMAT_R16G16B16A16_SINT = 96,
    BS_FORMAT_R16G16B16A16_SFLOAT = 97,
    BS_FORMAT_R32_UINT = 98,
    BS_FORMAT_R32_SINT = 99,
    BS_FORMAT_R32_SFLOAT = 100,
    BS_FORMAT_R32G32_UINT = 101,
    BS_FORMAT_R32G32_SINT = 102,
    BS_FORMAT_R32G32_SFLOAT = 103,
    BS_FORMAT_R32G32B32_UINT = 104,
    BS_FORMAT_R32G32B32_SINT = 105,
    BS_FORMAT_R32G32B32_SFLOAT = 106,
    BS_FORMAT_R32G32B32A32_UINT = 107,
    BS_FORMAT_R32G32B32A32_SINT = 108,
    BS_FORMAT_R32G32B32A32_SFLOAT = 109,
    BS_FORMAT_R64_UINT = 110,
    BS_FORMAT_R64_SINT = 111,
    BS_FORMAT_R64_SFLOAT = 112,
    BS_FORMAT_R64G64_UINT = 113,
    BS_FORMAT_R64G64_SINT = 114,
    BS_FORMAT_R64G64_SFLOAT = 115,
    BS_FORMAT_R64G64B64_UINT = 116,
    BS_FORMAT_R64G64B64_SINT = 117,
    BS_FORMAT_R64G64B64_SFLOAT = 118,
    BS_FORMAT_R64G64B64A64_UINT = 119,
    BS_FORMAT_R64G64B64A64_SINT = 120,
    BS_FORMAT_R64G64B64A64_SFLOAT = 121,
    BS_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
    BS_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
    BS_FORMAT_D16_UNORM = 124,
    BS_FORMAT_X8_D24_UNORM_PACK32 = 125,
    BS_FORMAT_D32_SFLOAT = 126,
    BS_FORMAT_S8_UINT = 127,
    BS_FORMAT_D16_UNORM_S8_UINT = 128,
    BS_FORMAT_D24_UNORM_S8_UINT = 129,
    BS_FORMAT_D32_SFLOAT_S8_UINT = 130,
    BS_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
    BS_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
    BS_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
    BS_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
    BS_FORMAT_BC2_UNORM_BLOCK = 135,
    BS_FORMAT_BC2_SRGB_BLOCK = 136,
    BS_FORMAT_BC3_UNORM_BLOCK = 137,
    BS_FORMAT_BC3_SRGB_BLOCK = 138,
    BS_FORMAT_BC4_UNORM_BLOCK = 139,
    BS_FORMAT_BC4_SNORM_BLOCK = 140,
    BS_FORMAT_BC5_UNORM_BLOCK = 141,
    BS_FORMAT_BC5_SNORM_BLOCK = 142,
    BS_FORMAT_BC6H_UFLOAT_BLOCK = 143,
    BS_FORMAT_BC6H_SFLOAT_BLOCK = 144,
    BS_FORMAT_BC7_UNORM_BLOCK = 145,
    BS_FORMAT_BC7_SRGB_BLOCK = 146,
    BS_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
    BS_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
    BS_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
    BS_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
    BS_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
    BS_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
    BS_FORMAT_EAC_R11_UNORM_BLOCK = 153,
    BS_FORMAT_EAC_R11_SNORM_BLOCK = 154,
    BS_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
    BS_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
    BS_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
    BS_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
    BS_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
    BS_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
    BS_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
    BS_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
    BS_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
    BS_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
    BS_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
    BS_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
    BS_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
    BS_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
    BS_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
    BS_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
    BS_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
    BS_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
    BS_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
    BS_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
    BS_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
    BS_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
    BS_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
    BS_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
    BS_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
    BS_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
    BS_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
    BS_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
    BS_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
    BS_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
};

enum bs_ColorSpace {
    BS_COLOR_SPACE_SRGB_NONLINEAR_KHR = 0,
    BS_COLORSPACE_SRGB_NONLINEAR_KHR = 0,
};

enum bs_PresentMode {
    BS_PRESENT_MODE_IMMEDIATE_KHR = 0,
    BS_PRESENT_MODE_MAILBOX_KHR = 1,
    BS_PRESENT_MODE_FIFO_KHR = 2,
    BS_PRESENT_MODE_FIFO_RELAXED_KHR = 3,
};

enum bs_ImageLayout {
    BS_IMAGE_LAYOUT_UNDEFINED = 0,
    BS_IMAGE_LAYOUT_GENERAL = 1,
    BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL = 2,
    BS_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
    BS_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
    BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL = 5,
    BS_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL = 6,
    BS_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL = 7,
    BS_IMAGE_LAYOUT_PREINITIALIZED = 8,
    BS_IMAGE_LAYOUT_PRESENT_SRC_KHR = 1000001002,
};

enum bs_DescriptorType {
    BS_DESCRIPTOR_TYPE_SAMPLER = 0,
    BS_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER = 1,
    BS_DESCRIPTOR_TYPE_SAMPLED_IMAGE = 2,
    BS_DESCRIPTOR_TYPE_STORAGE_IMAGE = 3,
    BS_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER = 4,
    BS_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER = 5,
    BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER = 6,
    BS_DESCRIPTOR_TYPE_STORAGE_BUFFER = 7,
    BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC = 8,
    BS_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC = 9,
    BS_DESCRIPTOR_TYPE_INPUT_ATTACHMENT = 10,
    BS_DESCRIPTOR_TYPES_COUNT = 11,
};

enum bs_DescriptorTypeIndex {
    BS_DESCRIPTOR_TYPE_SAMPLER_INDEX = 0,
    BS_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER_INDEX = 1,
    BS_DESCRIPTOR_TYPE_SAMPLED_IMAGE_INDEX = 2,
    BS_DESCRIPTOR_TYPE_STORAGE_IMAGE_INDEX = 3,
    BS_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER_INDEX = 4,
    BS_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER_INDEX = 5,
    BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER_INDEX = 6,
    BS_DESCRIPTOR_TYPE_STORAGE_BUFFER_INDEX = 7,
    BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC_INDEX = 8,
    BS_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC_INDEX = 9,
    BS_DESCRIPTOR_TYPE_INPUT_ATTACHMENT_INDEX = 10,
};

enum bs_VkObjectType {
    BS_OBJECT_TYPE_UNKNOWN = 0,
    BS_OBJECT_TYPE_INSTANCE = 1,
    BS_OBJECT_TYPE_PHYSICAL_DEVICE = 2,
    BS_OBJECT_TYPE_DEVICE = 3,
    BS_OBJECT_TYPE_QUEUE = 4,
    BS_OBJECT_TYPE_SEMAPHORE = 5,
    BS_OBJECT_TYPE_COMMAND_BUFFER = 6,
    BS_OBJECT_TYPE_FENCE = 7,
    BS_OBJECT_TYPE_DEVICE_MEMORY = 8,
    BS_OBJECT_TYPE_BUFFER = 9,
    BS_OBJECT_TYPE_IMAGE = 10,
    BS_OBJECT_TYPE_EVENT = 11,
    BS_OBJECT_TYPE_QUERY_POOL = 12,
    BS_OBJECT_TYPE_BUFFER_VIEW = 13,
    BS_OBJECT_TYPE_IMAGE_VIEW = 14,
    BS_OBJECT_TYPE_SHADER_MODULE = 15,
    BS_OBJECT_TYPE_PIPELINE_CACHE = 16,
    BS_OBJECT_TYPE_PIPELINE_LAYOUT = 17,
    BS_OBJECT_TYPE_RENDER_PASS = 18,
    BS_OBJECT_TYPE_PIPELINE = 19,
    BS_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT = 20,
    BS_OBJECT_TYPE_SAMPLER = 21,
    BS_OBJECT_TYPE_DESCRIPTOR_POOL = 22,
    BS_OBJECT_TYPE_DESCRIPTOR_SET = 23,
    BS_OBJECT_TYPE_FRAMEBUFFER = 24,
    BS_OBJECT_TYPE_COMMAND_POOL = 25,
    BS_OBJECT_TYPE_SWAPCHAIN_KHR = 1000001000,
};

union bs_vec2 {
    float a[2];
    struct {
        float x;
        float y;
    };
};

union bs_vec3 {
    float a[3];
    struct {
        float x;
        float y;
        float z;
    };
    bs_vec2 xy;
    struct {
        float _x;
        bs_vec2 yz;
    };
};

union bs_vec4 {
    float a[4];
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    struct {
        bs_vec2 xy;
        bs_vec2 zw;
    };
    bs_vec3 xyz;
};

union bs_ivec2 {
    int a[2];
    struct {
        int x;
        int y;
    };
};

union bs_ivec3 {
    int a[3];
    struct {
        int x;
        int y;
        int z;
    };
    bs_ivec2 xy;
    struct {
        float _x;
        bs_vec2 yz;
    };
};

union bs_ivec4 {
    int a[4];
    struct {
        int x;
        int y;
        int z;
        int w;
    };
    struct {
        bs_vec2 xy;
        bs_vec2 zw;
    };
    bs_ivec3 xyz;
};

union bs_mat2 {
    bs_vec2 v[2];
    float f[4];
    float a[2][2];
};

union bs_mat3 {
    bs_vec3 v[3];
    float f[9];
    float a[3][3];
};

union bs_mat4 {
    bs_vec4 v[4];
    float f[16];
    float a[4][4];
};

union bs_mat4x3 {
    bs_vec3 v[4];
    float f[12];
    float a[4][3];
};

union bs_RGBA {
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    bs_U32 hex;
    unsigned char array[4];
};

union bs_RGB {
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };
    bs_U32 hex;
};

union bs_BigInt {
    unsigned long low_part;
    long high_part;
    long long quad_part;
};

struct bs_Aabb {
    bs_vec3 min;
    bs_vec3 max;
};

struct bs_Sphere {
    bs_vec3 center;
    float radius;
};

struct bs_Rectangle {
    bs_vec2 position;
    bs_vec2 dimensions;
};

struct bs_Ray {
    bs_vec3 origin;
    bs_vec3 direction;
    float length;
};

struct bs_Quad {
    bs_vec3 a, b, c, d;
    bs_vec2 ca, cb, cc, cd;
};

struct bs_Plane {
    bs_vec3 point;
    bs_vec3 normal;
};

struct bs_Box {
    bs_vec3 extent;
    bs_mat4* transform;
};

struct bs_FileInfo {
    char* path;
    size_t size;
};

struct bs_File {
    FILE* handle;
};

struct bs_PngData {
    int width;
    int height;
    int channels_count;
    size_t size;
    unsigned char* data;
};

struct bs_Procedure {
    const char* func;
    size_t size;
    bool is_required;
};

struct bs_Timer {
    bs_BigInt ticks_per_second;
    bs_BigInt tick_count;
    bs_BigInt last_tick_count;
    bs_U64 microseconds;
    double seconds;
};

struct bs_DateTime {
    unsigned int years;
    unsigned int months;
    unsigned int days;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
    unsigned int milliseconds;
    unsigned int day_of_week;
};

struct bs_RayVsObb {
    bs_vec3 coordinate;
    bs_vec3 normal;
    int plane;
    bool hit;
};

struct bs_SphereVsPoint {
    bool hit;
};

struct bs_SphereVsBox {
    bs_vec3 point;
    bs_vec3 normal;
    float penetration;
    bool hit;
};

struct bs_RectangleVsPoint {
    bool hit;
};

struct bs_LineVsLine {
    bs_vec2 point;
    bool hit;
};

struct bs_GUID {
    bs_U64 a, b;
};

struct bs_List {
    int count;
    int unit_size;
    int capacity;
    int increment;
    bs_U8* data;
};

struct bs_mat3SVD {
    bs_mat3 U;
    bs_vec3 S;
    bs_mat3 V;
};

struct bs_String {
    int len;
    int capacity;
    char value[];
};

struct bs_StringPoolEntry {
    bs_U64 hash;
    const char* string;
};

struct bs_Range {
    bs_U32 offset;
    bs_U32 num;
};

struct bs_Header {
    int id;
    int source_id;
    bs_U32 swaps_count;
    bs_ObjectType type;
    const char* name;
};

struct bs_Object {
    bs_U32 flags;
    union {
        bs_Header* head;
        bs_Batch* batch;
        bs_Buffer* buffer;
        bs_Image* image;
        bs_Atlas* atlas;
        bs_Sampler* sampler;
        bs_Renderer* renderer;
        bs_Sound* sound;
        bs_Queue* queue;
        bs_RayTracer* ray_tracer;
        bs_Context* context;
    };
};

struct bs_ResourceParams {
    bs_U32 type;
    int unit_size;
    const char* name;
};

struct bs_Resource {
    bs_U64 hash;
    char* name;
    bs_String* data;
    union {
        bs_Model* model;
        bs_Shader* shader;
        bs_Sound* sound;
        bs_Atlas* atlas;
        bs_Image* image;
        struct bsgfx_Font* font;
    };
};

struct bs_ResourceHeader {
    bs_U64 name_hash;
    bs_I32 chunk;
    bs_I32 offset;
    bs_I32 size;
    bs_I32 name_length;
    bs_I32 type;
    char* name;
    bs_Resource* resource;
};

struct bs_PackageHeader {
    bs_U32 magic;
    bs_I32 resources_count;
    bs_I32 resource_types_count;
    bs_I32 reserved;
    bs_Range resource_type_offsets[BS_RESOURCE_TYPE_COUNT];
};

struct bs_Package {
    bs_U64 path_hash;
    char* path;
    int resource_headers_count;
    bs_ResourceHeader* resource_headers;
    bs_String* raw;
    bs_Range resource_type_offsets[BS_RESOURCE_TYPE_COUNT];
    int chunks_count;
};

struct bs_BlitOperation {
    bs_Image* source;
    bs_Image* destination;
    bs_ImageLayout source_layout;
    bs_ImageLayout destination_layout;
    bs_ivec2 source_scale;
    bs_ivec2 destination_scale;
};

struct bs_ImageIndex {
    char* name;
    bs_U64 name_hash;
};

struct bs_ImageSwaps {
    struct VkImage_T* vk_image;
    struct VkImageView_T* vk_image_view;
    struct VkDeviceMemory_T* vk_memory;
};

struct bs_Image {
    bs_Header head;
    bs_ImageBits flags;
    bs_ivec2 dim;
    int num_indices;
    bs_ImageIndex* indices;
    int bind_set;
    int bind_point;
    bs_Format format;
    enum VkImageUsageFlags usage_flags;
    enum VkImageAspectFlags aspect_flags;
    bs_ImageSwaps _[];
};

struct bs_BshaHeader {
    bs_U32 magic;
    bs_U32 version;
    bs_U32 push_constant_size;
    bs_U32 bind_set_flags;
    bs_ShaderType shader_type;
    bs_U32 attributes_count;
    bs_U64 spirv_size;
    bs_U32 reserved_0;
    bs_U32 reserved_1;
    bs_U32 reserved_2;
    bs_U32 reserved_3;
};

struct bs_BshaAttribute {
    bs_U64 name_hash;
    bs_U32 location;
    bs_U32 size;
};

struct bs_BiffHeader {
    bs_U32 magic;
    bs_U32 version;
    bs_U32 images_count;
    bs_U32 width;
    bs_U32 height;
    bs_U32 channels_count;
    bs_U32 reserved_0, reserved_1;
};

struct bs_BiffPointer {
    bs_U32 offset;
    bs_U32 size;
    bs_U32 name_length;
    bs_U32 reserved;
};

struct bs_BatlHeader {
    bs_U32 magic;
    bs_U32 version;
    bs_U32 width;
    bs_U32 height;
    bs_U32 channels_count;
    bs_U32 pages_count;
    bs_U32 images_count;
    bs_U32 reserved_0;
};

struct bs_BatlImage {
    bs_I32 x;
    bs_I32 y;
    bs_I32 w;
    bs_I32 h;
    bs_U32 name_length;
    bs_U32 flags;
    int category;
    bs_U32 page;
};

struct bs_AtlasTexture {
    bs_vec4 coords;
    int x, y;
    int w, h;
    int split;
    bs_U32 flags;
};

struct bs_Atlas {
    bs_Header head;
    int count;
    struct {
        char* name;
        bs_U64 name_hash;
        int category;
    }* unmapped;
    bs_AtlasTexture* mapped;
    bs_Image* image;
    bs_Buffer* buffer;
    struct {
        void* unused;
    }_[];
};

struct bs_Sampler {
    bs_Header head;
    bs_SamplerBits flags;
    bs_ImageFilter filter;
    struct {
        struct VkSampler_T* vk_sampler;
    }_[];
};

struct bs_StencilOperation {
    bs_StencilOp fail_op;
    bs_StencilOp pass_op;
    bs_StencilOp depth_fail_op;
    bs_CompareOp compare_op;
    bs_U32 compare_mask;
    bs_U32 write_mask;
    bs_U32 reference;
};

struct bs_Pipeline {
    bs_Header head;
    int shaders_count;
    bs_U64 hash;
    bs_PipelineType type;
    bs_PipelineFlags flags;
    bs_SlotBits bind_sets;
    bs_U32 shader_stages;
    int num_bind_sets;
    int constant_size;
    bs_String* name;
    bs_Buffer* binding_table;
    struct VkPipelineLayout_T* vk_layout;
    struct VkPipeline_T* vk_pipeline;
    struct {
        bs_Shader* shader;
    }_[];
};

struct bs_PipelineHash {
    bs_PipelineFlags flags;
    int subpass;
    bs_Renderer* renderer;
    bs_TopologyType topology_type;
    bs_BlendFactor src_color_factor;
    bs_BlendFactor dst_color_factor;
    bs_BlendFactor src_alpha_factor;
    bs_BlendFactor dst_alpha_factor;
    bs_BlendOperationType color_op;
    bs_BlendOperationType alpha_op;
    bs_StencilOperation stencil_front;
    bs_StencilOperation stencil_back;
    bs_CullModeFlag cull_type;
    bs_PolygonType polygon_type;
    bs_CompareOp depth_comparison;
    bool restart_primitive;
    bool clamp_depth;
    bool skip_depth_test;
    bool skip_stencil_test;
    bool skip_depth_write;
    bool disable_blend;
    bs_Shader* shaders[2];
    struct {
        bool skip_write;
    } attachments[BS_MAX_ATTACHMENTS_COUNT];
};

struct bs_RayTracePipelineHash {
    bs_RayTracer* ray_tracer;
};

struct bs_AttributeType {
    const char* name;
    bs_U64 name_hash;
    bs_Format base_format;
};

struct bs_Attribute {
    bs_U64 name_hash;
    bs_U32 location;
    bs_U32 size;
    bs_Format format;
    bs_U32 offset;
};

struct bs_Shader {
    bs_ShaderType type;
    bs_PipelineType pipeline_type;
    bs_SlotBits bind_sets;
    bs_U32* spirv;
    bs_U32 spirv_length;
    bs_Attribute* attributes;
    int num_attributes;
    int constant_size;
    bs_Resource* resource;
    struct VkShaderModule_T* vk_module;
};

struct bs_BufferSwap {
    struct VkBuffer_T* vk_buffer;
    struct VkBufferView_T* vk_buffer_view;
    struct VkDeviceMemory_T* memory;
    char* data;
};

struct bs_Buffer {
    bs_Header head;
    bs_BufferBits flags;
    bs_U32 bind_set;
    bs_U32 binding;
    size_t num_bytes;
    bs_BufferUsageFlags usage_flags;
    bs_MemoryPropertyFlags memory_flags;
    bs_BufferSwap _[];
};

struct bs_Output {
    bs_OutputFlags flags;
    bs_U32 subpass;
    bs_U32 attachment;
    bs_LoadOp load_op;
    bs_StoreOp store_op;
    bs_Image* image;
    bs_ImageLayout old_layout;
    bs_ImageLayout new_layout;
};

struct bs_Input {
    bs_InputBits flags;
    bs_U32 subpass;
    bs_U32 parent_subpass;
    bs_U32 attachment;
};

struct bs_RendererScope {
    bs_Queue* queue;
    bs_Renderer* renderer;
    int subpass;
};

struct bs_RendererSwaps {
    struct VkFramebuffer_T* framebuffer;
};

struct bs_Renderer {
    bs_Header head;
    bs_RendererBits flags;
    bs_Input* inputs;
    bs_Output* outputs;
    struct VkSubpassDependency* dependencies;
    int num_inputs;
    int num_outputs;
    int num_subpasses;
    int num_dependencies;
    bs_ivec2 dim;
    bs_Queue* queue;
    bs_Context* context;
    struct VkRenderPass_T* render_pass;
    bs_RendererSwaps _[];
};

struct bs_Batch {
    bs_Header head;
    bs_BatchBits flags;
    bs_Attribute* attributes;
    bs_U32 attributes_count;
    bs_U32 attribute_flags;
    bs_Object* vertex_buffer;
    bs_Object* index_buffer;
    bs_Object* staging_buffer;
    bs_List vertices;
    bs_List indices;
    struct {
        void* unused;
    }_[];
};

struct bs_WaitSemaphore {
    struct VkSemaphore_T* semaphore;
    bs_PipelineStage stage;
};

struct bs_QueueSwaps {
    struct VkCommandBuffer_T* command_buffer;
    struct VkSemaphore_T* semaphore;
    struct VkFence_T* fence;
};

struct bs_Queue {
    bs_Header head;
    bs_QueueBits flags;
    bs_U32 family;
    struct VkQueue_T* queue;
    bs_QueueSwaps _[];
};

struct bs_ShaderGroup {
    bs_Shader* shader;
};

struct bs_RayTracer {
    bs_Header head;
    bs_List aabbs;
    bs_List batches;
    bs_Buffer* BLAS_buffer;
    bs_Buffer* TLAS_buffer;
    bs_Buffer* BLAS_scratch_buffer;
    bs_Buffer* TLAS_scratch_buffer;
    bs_U32 record_size;
    bs_U32 groups_count;
    struct VkAccelerationStructureKHR_T* BLAS;
    struct VkAccelerationStructureKHR_T* TLAS;
    bs_ShaderGroup _[];
};

union bs_JsonArray {
    unsigned char* as_uchars;
    float* as_floats;
    int* as_ints;
    bs_F64* as_numbers;
    char** as_strings;
    bs_JsonObject* as_objects;
    bool* as_bools;
    bs_vec2* vec2;
    bs_vec3* vec3;
    bs_vec4* vec4;
};

struct bs_Json {
    bool is_mutable;
    union {
        bs_JsonObject as_object;
    };
    void* doc;
};

struct bs_JsonValue {
    bool found;
    bs_JsonType type;
    int size;
    union bs_JsonValueUnion {
        bs_JsonArray as_array;
        bs_JsonObject as_object;
        bs_F64 as_number;
        char* as_string;
        bool as_bool;
    };
};

struct bs_JsonEnumeration {
    const char* key;
    bs_JsonValue value;
    struct {
        bs_U64 idx;
        bs_U64 max;
        void* cur;
        union {
            void* obj;
            bs_JsonArray as_array;
            struct {
                void* mut_pre;
                void* mut_obj;
            };
        };
    }iter;
};

struct bs_Material {
    char* name;
    bs_RGBA color;
};

struct bs_Primitive {
    float* vertices;
    int num_vertices;
    int vertex_size;
    int texture_offset;
    int normal_offset;
    int bone_offset;
    int weight_offset;
    int index_offset;
    bs_U32 num_indices;
    bs_U32* indices;
    int material_id;
    bs_Mesh* parent;
    bs_Aabb aabb;
    int* extra;
};

struct bs_Mesh {
    char* name;
    bs_U64 name_hash;
    bs_vec3 position;
    bs_vec4 rotation;
    bs_vec3 scale;
    bs_Primitive* primitives;
    int primitives_count;
    int num_vertices;
    int num_indices;
    bs_Model* model;
    bs_Aabb aabb;
    int* extra;
};

struct bs_Model {
    bs_Header head;
    bs_ModelFlags flags;
    bs_Armature* armatures;
    bs_Mesh* meshes;
    bs_Material* materials;
    bs_U64* animation_hashes;
    int animations_count;
    int armatures_count;
    int meshes_count;
    int materials_count;
    int primitives_count;
    int num_vertices;
    int num_indices;
    bs_Json json;
    bs_Aabb aabb;
    unsigned char* gltf;
    int* extra;
};

struct bs_Bone {
    bs_U32 id;
    int parent_idx;
    int opposite_id;
    int name_length;
    char* name;
    bs_U64 name_hash;
    bs_mat4 local_matrix;
    bs_mat4 bind_matrix_inverse;
};

struct bs_Armature {
    struct {
        float ik_length;
        int ik_id;
        bs_vec3 ik_direction;
        bs_vec3 ik_position;
        bs_mat4 matrix;
        bs_Bone bone;
    }* bones;
    int bones_count;
    int bones_allocated;
    char* name;
};

struct bs_AnimationBone {
    bs_vec3 last_translation;
    bs_vec4 last_rotation;
    bs_vec3 last_scale;
    int translations_count, translations_allocated;
    int rotations_count, rotations_allocated;
    int scalings_count, scalings_allocated;
    struct {
        float time;
        bs_vec3 value;
    }* translations;
    struct {
        float time;
        bs_vec4 value;
    }* rotations;
    struct {
        float time;
        bs_vec3 value;
    }* scalings;
};

struct bs_Animation {
    char* name;
    bs_AnimationBone* bones;
    int bones_count;
    int bones_allocated;
    int frames_count;
    float length;
};

struct bs_Sound {
    bs_Header head;
    const char* name;
    void* data;
    void* xaudio;
    int size;
};

struct bs_ImageDescriptor {
    bs_Sampler* sampler;
    bs_Image* image;
    bs_ImageLayout layout;
};

struct bs_Descriptor {
    union {
        struct {
            struct VkSampler_T* vk_sampler;
            struct VkImageView_T* vk_image_view;
            enum VkImageLayout vk_image_layout;
            bs_U32 padding;
            bs_Image* image;
            bs_Sampler* sampler;
        } as_image;
        struct {
            struct VkBuffer_T* vk_buffer;
            bs_U64 vk_offset;
            bs_U64 vk_range;
            bs_Buffer* buffer;
        } as_buffer;
        struct {
            struct VkBufferView_T* vk_buffer_view;
            bs_Buffer* buffer;
        } as_texel_buffer;
    };
    int object_type;
    int reserved;
    int bind_set;
    int bind_point;
};

struct bs_Binding {
    bs_U32 stages;
    int slot;
    int set;
    int location;
    int descriptors_count;
    bool in_use;
    int size;
    bs_DescriptorType type;
    int type_index;
};

struct bs_BindSet {
    bs_U32 slot;
    bool needs_update;
    int bindings_count;
    int descriptors_count;
    int max_binding;
    int bound_descriptors_count;
    bs_Binding* bindings;
    bs_Descriptor* descriptors;
    struct VkDescriptorUpdateTemplate_T* vk_update_template;
    struct VkDescriptorSetLayout_T* vk_layout;
    struct VkDescriptorSet_T* vk_set;
};

struct bs_ObjectSource {
    bs_ObjectId* ids;
    int ids_count;
    bs_ObjectType type;
};

struct bs_ObjectId {
    const char* name;
    bs_U64 name_hash;
    bs_Object* object;
};

struct bs_IO {
    bool left_clicked;
    bool right_clicked;
    bool middle_clicked;
    bool left_clicked_last;
    bool right_clicked_last;
    bool middle_clicked_last;
    bs_U8 hold_keys[BS_KEY_BYTES_COUNT];
    bs_U8 keys[BS_KEY_BYTES_COUNT];
    bs_U8 keys_old[BS_KEY_BYTES_COUNT];
    bs_U8 chars[BS_KEY_BYTES_COUNT];
    bs_U8 chars_old[BS_KEY_BYTES_COUNT];
    bs_I8 scroll, scroll_old;
};

struct bs_Instance {
    int bind_sets_count;
    int bindings_count;
    int descriptors_count;
    int max_bind_set;
    bs_BindSet* bind_sets;
    bs_Binding* bindings;
    bs_Descriptor* descriptors;
    bool descriptor_pool_needs_update;
    bool alive;
    bs_vec2 screen_cursor;
    struct {
        bs_List objects;
    } object_types[BS_OBJECT_TYPE_COUNT];
    bs_Timer timer;
    double time, time_old;
    double delta_time;
    double fixed_time;
    double fixed_interpolation;
    double target_frame_time;
    double elapsed_time;
    int last_fixed_update_times[2];
    int new_time_index;
    bool in_fixed;
    bool paused;
    bool advance;
    bs_String* executable;
    bs_String* cwd;
    bs_String* appdata;
    bs_String* log;
    struct {
        int* bindings;
        int bind_set;
    }* descriptor_lookup;
    struct {
        bs_SurfaceType surface_type;
    } extensions;
    int max_frames_in_flight;
    bs_PhysicalDevice* physical_device;
    bs_QueueFamily* queue_family;
    struct VkDescriptorSet_T* sets[BS_MAX_NUM_BIND_SETS];
    struct VkDescriptorSetLayout_T* layouts[BS_MAX_NUM_BIND_SETS];
    struct VkInstance_T* instance;
    struct VkDevice_T* device;
};

struct bs_Bindings {
    bs_BindSet* bs_bind_sets;
    int bs_bind_sets_count;
};

struct bs_Config {
    bs_List attributes;
    bs_U32 queues_count;
};

struct bs_QueueFamily {
    bool supports_present;
    bs_U32 queue_flags;
    bs_U32 queue_count;
    bs_U32 index;
};

struct bs_SurfaceFormat {
    bs_Format format;
    bs_ColorSpace color_space;
};

struct bs_PhysicalDevice {
    struct VkPhysicalDevice_T* vk_device;
    bool supports_present;
    bs_U32 api_version;
    int type;
    bs_List queue_families;
    bs_List surface_formats;
    const char name[BS_MAX_PHYSICAL_DEVICE_NAME_SIZE];
};

struct bs_Context {
    bs_Header head;
    const char* title;
    void* hwnd;
    bs_Timer timer;
    bs_ivec2 dimensions;
    bs_Callback destroy;
    bs_ContextTickFunction tick;
    bs_vec2 cursor;
    bs_vec2 border_size;
    bs_WindowType window_type;
    bs_CursorIcon cursor_icon;
    bs_ResizeContextFunction resize;
    struct VkSurfaceKHR_T* surface;
    bs_SurfaceFormat surface_format;
    bs_PresentMode present_mode;
    void* user_data;
    int id;
    int frames_in_flight;
    int frame;
    bool hidden;
    bool active;
    bool resized;
    bool image_acquired;
    bs_Object* swapchain_image;
    struct VkSwapchainKHR_T* swapchain;
    bs_IO io;
    struct {
        struct VkSemaphore_T* semaphore;
    }_[];
};

struct bs_Scope {
    bs_Context* context;
    bs_Queue* queue;
    bs_Renderer* renderer;
    int subpass;
};

struct bs_Args {
    bool use_validation_layers;
};

struct bs_Features {
    bool independent_blend;
    bool ray_tracing;
};

struct bs_Props {
    bs_U32 shader_group_handle_size;
    bs_U32 shader_group_base_alignment;
    bs_U32 min_acceleration_structure_scratch_offset_alignment;
};

struct bs_Callbacks {
    bs_MessageFunction log;
    bs_ValidationErrorFunction error;
    bs_NonClientAreaTickFunction client_area_tick;
};

struct bs_LogQueueItem {
    bs_MessageFunction log;
    bs_Library library;
    bs_MessageLevel level;
    bs_Result result;
    int code;
    const char* function;
    const char* file;
    int line;
    bs_U32 thread_id;
    char message[BS_MAX_LOG_SIZE];
};

 /**
  @return void
  */
BSAPI void
bs_enableValidation();

 /**
  @return void
  */
BSAPI void
bs_disableValidation();

 /**
  @return bs_Callbacks*
  */
BSAPI bs_Callbacks*
bs_callbacks();

 /**
  @return bs_Scope*
  */
BSAPI bs_Scope*
bs_scope();

 /**
  @param value
  @return void
  */
BSAPI void
bs_writeLogFile(
    char* value);

 /**
  @param value
  @param value_length
  @return void
  */
BSAPI void
bs_writeLogFileN(
    char* value,
    int value_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_writeLogFileV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_writeLogFileF(
    char* format,
     ...);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v2Add(
    const bs_vec2* a,
    const bs_vec2* b,
    bs_vec2* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v2Sub(
    const bs_vec2* a,
    const bs_vec2* b,
    bs_vec2* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v2Mul(
    const bs_vec2* a,
    const bs_vec2* b,
    bs_vec2* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v2Div(
    const bs_vec2* a,
    const bs_vec2* b,
    bs_vec2* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v2AddS(
    const bs_vec2* v,
    float s,
    bs_vec2* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v2SubS(
    const bs_vec2* v,
    float s,
    bs_vec2* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v2MulS(
    const bs_vec2* v,
    float s,
    bs_vec2* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v2DivS(
    const bs_vec2* v,
    float s,
    bs_vec2* out);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v2Dot(
    const bs_vec2* a,
    const bs_vec2* b);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v2Distance(
    const bs_vec2* a,
    const bs_vec2* b);

 /**
  @param v
  @return float
  */
BSAPI float
bs_v2Magnitude(
    const bs_vec2* v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_v2MagnitudeSqrd(
    const bs_vec2* v);

 /**
  @param v
  @param out
  @return void
  */
BSAPI void
bs_v2Normalize(
    const bs_vec2* v,
    bs_vec2* out);

 /**
  @param from
  @param to
  @param t
  @param out
  @return void
  */
BSAPI void
bs_v2Lerp(
    const bs_vec2* from,
    const bs_vec2* to,
    float t,
    bs_vec2* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v2Mid(
    const bs_vec2* a,
    const bs_vec2* b,
    bs_vec2* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v3Add(
    const bs_vec3* a,
    const bs_vec3* b,
    bs_vec3* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v3Sub(
    const bs_vec3* a,
    const bs_vec3* b,
    bs_vec3* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v3Mul(
    const bs_vec3* a,
    const bs_vec3* b,
    bs_vec3* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v3Div(
    const bs_vec3* a,
    const bs_vec3* b,
    bs_vec3* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v3AddS(
    const bs_vec3* v,
    float s,
    bs_vec3* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v3SubS(
    const bs_vec3* v,
    float s,
    bs_vec3* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v3MulS(
    const bs_vec3* v,
    float s,
    bs_vec3* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v3DivS(
    const bs_vec3* v,
    float s,
    bs_vec3* out);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v3Dot(
    const bs_vec3* a,
    const bs_vec3* b);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v3Distance(
    const bs_vec3* a,
    const bs_vec3* b);

 /**
  @param v
  @return float
  */
BSAPI float
bs_v3Magnitude(
    const bs_vec3* v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_v3MagnitudeSqrd(
    const bs_vec3* v);

 /**
  @param v
  @param out
  @return void
  */
BSAPI void
bs_v3Normalize(
    const bs_vec3* v,
    bs_vec3* out);

 /**
  @param from
  @param to
  @param t
  @param out
  @return void
  */
BSAPI void
bs_v3Lerp(
    const bs_vec3* from,
    const bs_vec3* to,
    float t,
    bs_vec3* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v3Mid(
    const bs_vec3* a,
    const bs_vec3* b,
    bs_vec3* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v3Cross(
    const bs_vec3* a,
    const bs_vec3* b,
    bs_vec3* out);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v3Angle(
    const bs_vec3* a,
    const bs_vec3* b);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v4Add(
    const bs_vec4* a,
    const bs_vec4* b,
    bs_vec4* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v4Sub(
    const bs_vec4* a,
    const bs_vec4* b,
    bs_vec4* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v4Mul(
    const bs_vec4* a,
    const bs_vec4* b,
    bs_vec4* out);

 /**
  @param a
  @param b
  @param out
  @return void
  */
BSAPI void
bs_v4Div(
    const bs_vec4* a,
    const bs_vec4* b,
    bs_vec4* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v4AddS(
    const bs_vec4* v,
    float s,
    bs_vec4* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v4SubS(
    const bs_vec4* v,
    float s,
    bs_vec4* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v4MulS(
    const bs_vec4* v,
    float s,
    bs_vec4* out);

 /**
  @param v
  @param s
  @param out
  @return void
  */
BSAPI void
bs_v4DivS(
    const bs_vec4* v,
    float s,
    bs_vec4* out);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v4Dot(
    const bs_vec4* a,
    const bs_vec4* b);

 /**
  @param a
  @param b
  @return float
  */
BSAPI float
bs_v4Distance(
    const bs_vec4* a,
    const bs_vec4* b);

 /**
  @param v
  @return float
  */
BSAPI float
bs_v4Magnitude(
    const bs_vec4* v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_v4MagnitudeSqrd(
    const bs_vec4* v);

 /**
  @param v
  @param out
  @return void
  */
BSAPI void
bs_v4Normalize(
    const bs_vec4* v,
    bs_vec4* out);

 /**
  @param from
  @param to
  @param t
  @param out
  @return void
  */
BSAPI void
bs_v4Lerp(
    const bs_vec4* from,
    const bs_vec4* to,
    float t,
    bs_vec4* out);

 /**
  @param a
  @param b
  @param result
  @return void
  */
BSAPI void
bs_m3Mul(
    const bs_mat3* a,
    const bs_mat3* b,
    const bs_mat3* result);

 /**
  @param m
  @param result
  @return void
  */
BSAPI void
bs_m3Transpose(
    const bs_mat3* m,
    const bs_mat3* result);

 /**
  @param m
  @param result
  @return void
  */
BSAPI void
bs_m3Inverse(
    const bs_mat3* m,
    const bs_mat3* result);

 /**
  @param m
  @param v
  @param out
  @return void
  */
BSAPI void
bs_m3MulV3(
    const bs_mat3* m,
    const bs_vec3* v,
    bs_vec3* out);

 /**
  @param a
  @param b
  @param result
  @return void
  */
BSAPI void
bs_m4Mul(
    const bs_mat4* a,
    const bs_mat4* b,
    const bs_mat4* result);

 /**
  @param m
  @param result
  @return void
  */
BSAPI void
bs_m4Transpose(
    const bs_mat4* m,
    const bs_mat4* result);

 /**
  @param m
  @param result
  @return void
  */
BSAPI void
bs_m4Inverse(
    const bs_mat4* m,
    const bs_mat4* result);

 /**
  @param m
  @return bs_mat4x3
  */
BSAPI bs_mat4x3
bs_m4x3(
    const bs_mat4* m);

 /**
  @param m
  @param v
  @param out
  @return void
  */
BSAPI void
bs_m4MulV3(
    const bs_mat4* m,
    const bs_vec3* v,
    bs_vec3* out);

 /**
  @param m
  @param v
  @param out
  @return void
  */
BSAPI void
bs_m4MulV4(
    const bs_mat4* m,
    const bs_vec4* v,
    bs_vec4* out);

 /**
  @param m
  @param v
  @param out
  @return void
  */
BSAPI void
bs_m4Translate(
    const bs_mat4* m,
    const bs_vec3* v,
    bs_mat4* out);

 /**
  @param m
  @param q
  @param out
  @return void
  */
BSAPI void
bs_m4Rotate(
    const bs_mat4* m,
    const bs_vec4* q,
    bs_mat4* out);

 /**
  @param m
  @param v
  @param out
  @return void
  */
BSAPI void
bs_m4Scale(
    const bs_mat4* m,
    const bs_vec3* v,
    bs_mat4* out);

 /**
  @param m
  @param out
  @return void
  */
BSAPI void
bs_m3ToQ(
    const bs_mat3* m,
    bs_vec4* out);

 /**
  @param m
  @param out
  @return void
  */
BSAPI void
bs_m4ToQ(
    const bs_mat4* m,
    bs_vec4* out);

 /**
  @param q
  @param out
  @return void
  */
BSAPI void
bs_qToM3(
    const bs_vec4* q,
    bs_mat3* out);

 /**
  @param q
  @param out
  @return void
  */
BSAPI void
bs_qToM4(
    const bs_vec4* q,
    bs_mat4* out);

 /**
  @param p
  @param q
  @param out
  @return void
  */
BSAPI void
bs_qMulQ(
    const bs_vec4* p,
    const bs_vec4* q,
    bs_vec4* out);

 /**
  @param axis
  @param radians
  @param out
  @return void
  */
BSAPI void
bs_qAxisAngle(
    const bs_vec3* axis,
    float radians,
    bs_vec4* out);

 /**
  @param q
  @param out
  @return void
  */
BSAPI void
bs_qNormalize(
    const bs_vec4* q,
    bs_vec4* out);

 /**
  @param from
  @param to
  @param t
  @param out
  @return void
  */
BSAPI void
bs_qSlerp(
    const bs_vec4* from,
    const bs_vec4* to,
    float t,
    bs_vec4* out);

 /**
  @param q
  @param v
  @param out
  @return void
  */
BSAPI void
bs_qRotateV3(
    const bs_vec4* q,
    const bs_vec3* v,
    bs_vec3* out);

 /**
  @param from
  @param to
  @param t
  @param out
  @return void
  */
BSAPI void
bs_qLongSlerp(
    const bs_vec4* from,
    const bs_vec4* to,
    float t,
    bs_vec4* out);

 /**
  @param eul
  @param out
  @return void
  */
BSAPI void
bs_eulToQ(
    const bs_vec3* eul,
    bs_vec4* out);

 /**
  @param q
  @param out
  @return void
  */
BSAPI void
bs_qToEul(
    const bs_vec4* q,
    bs_vec3* out);

 /**
  @param left
  @param right
  @param bottom
  @param top
  @param near_z
  @param far_z
  @param out
  @return void
  */
BSAPI void
bs_orthographic(
    float left,
    float right,
    float bottom,
    float top,
    float near_z,
    float far_z,
    bs_mat4* out);

 /**
  @param fov
  @param aspect
  @param near_z
  @param far_z
  @param out
  @return void
  */
BSAPI void
bs_perspective(
    float fov,
    float aspect,
    float near_z,
    float far_z,
    bs_mat4* out);

 /**
  @param eye
  @param center
  @param up
  @param out
  @return void
  */
BSAPI void
bs_lookAt(
    const bs_vec3* eye,
    const bs_vec3* center,
    const bs_vec3* up,
    bs_mat4* out);

 /**
  @param eye
  @param direction
  @param up
  @param out
  @return void
  */
BSAPI void
bs_look(
    const bs_vec3* eye,
    const bs_vec3* direction,
    const bs_vec3* up,
    bs_mat4* out);

 /**
  @param p0
  @param p1
  @param p2
  @param p3
  @param out
  @param out_length
  @return void
  */
BSAPI void
bs_v2CubicBezier(
    const bs_vec2* p0,
    const bs_vec2* p1,
    const bs_vec2* p2,
    const bs_vec2* p3,
    bs_vec2* out,
    int out_length);

 /**
  @param p0
  @param p1
  @param p2
  @param out
  @param out_length
  @return void
  */
BSAPI void
bs_v2QuadBezier(
    const bs_vec2* p0,
    const bs_vec2* p1,
    const bs_vec2* p2,
    bs_vec2* out,
    int out_length);

 /**
  @param p0
  @param p1
  @param p2
  @param p3
  @param out
  @param out_length
  @return void
  */
BSAPI void
bs_v3CubicBezier(
    const bs_vec3* p0,
    const bs_vec3* p1,
    const bs_vec3* p2,
    const bs_vec3* p3,
    bs_vec3* out,
    int out_length);

 /**
  @param p0
  @param p1
  @param p2
  @param out
  @param out_length
  @return void
  */
BSAPI void
bs_v3QuadBezier(
    const bs_vec3* p0,
    const bs_vec3* p1,
    const bs_vec3* p2,
    bs_vec3* out,
    int out_length);

 /**
  @param aabb
  @param rotation_matrix
  @param out
  @return void
  */
BSAPI void
bs_rotateAabb(
    const bs_Aabb* aabb,
    const bs_mat3* rotation_matrix,
    bs_Aabb* out);

 /**
  @param aabb
  @param size
  @param rotation
  @param out
  @return void
  */
BSAPI void
bs_fitAabb(
    const bs_Aabb* aabb,
    const bs_vec2* size,
    const bs_vec4* rotation,
    bs_mat4* out);

 /**
  @param v
  @return float
  */
BSAPI float
bs_round(
    float v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_abs(
    float v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_sqrt(
    float v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_sin(
    float v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_cos(
    float v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_tan(
    float v);

 /**
  @param v
  @return int
  */
BSAPI int
bs_sign(
    float v);

 /**
  @param position
  @param dimensions
  @param out
  @return void
  */
BSAPI void
bs_quad(
    const bs_vec3* position,
    const bs_vec2* dimensions,
    bs_Quad* out);

 /**
  @param from
  @param to
  @param t
  @return float
  */
BSAPI float
bs_lerp(
    float from,
    float to,
    float t);

 /**
  @param radians
  @return float
  */
BSAPI float
bs_degrees(
    float radians);

 /**
  @param degrees
  @return float
  */
BSAPI float
bs_radians(
    float degrees);

 /**
  @param v
  @return float
  */
BSAPI float
bs_ceil(
    float v);

 /**
  @param v
  @return float
  */
BSAPI float
bs_floor(
    float v);

 /**
  @param v
  @param min
  @param max
  @return float
  */
BSAPI float
bs_clamp(
    float v,
    float min,
    float max);

 /**
  @param value
  @return float
  */
BSAPI float
bs_linearTosRGB(
    float value);

 /**
  @param value
  @return float
  */
BSAPI float
bs_sRGBToLinear(
    float value);

 /**
  @param value
  @return bs_vec3
  */
BSAPI bs_vec3
bs_linearV3TosRGB(
    const bs_vec3* value);

 /**
  @param value
  @return bs_vec3
  */
BSAPI bs_vec3
bs_sRGBToLinearV3(
    const bs_vec3* value);

 /**
  @param value
  @return bs_RGBA
  */
BSAPI bs_RGBA
bs_rgbV4ToUChar(
    const bs_vec4* value);

 /**
  @param value
  @return bs_vec4
  */
BSAPI bs_vec4
bs_rgbUCharToV4(
    bs_RGBA value);

 /**
  @param hsv
  @return bs_vec3
  */
BSAPI bs_vec3
bs_hsvToRgb(
    const bs_vec3* hsv);

 /**
  @param rgb
  @return bs_vec3
  */
BSAPI bs_vec3
bs_rgbToHsv(
    const bs_vec3* rgb);

 /**
  @param code
  @return bs_Result
  */
BSAPI bs_Result
bs_convertYyjsonResult(
    int code);

 /**
  @param code
  @return bs_Result
  */
BSAPI bs_Result
bs_convertVulkanResult(
    int code);

 /**
  @param code
  @return bs_Result
  */
BSAPI bs_Result
bs_convertWin32Error(
    int code);

 /**
  @param code
  @return const char*
  */
BSAPI const char*
bs_serializeWin32Error(
    int code);

 /**
  @return bs_Result
  */
BSAPI bs_Result
bs_convertErrno();

 /**
  @return const char*
  */
BSAPI const char*
bs_serializeErrno();

 /**
  @param sound
  @param volume
  @return bs_Result
  */
BSAPI bs_Result
bs_playSound(
    bs_Sound* sound,
    float volume);

 /**
  @param resource
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_sound(
    bs_Resource* resource,
    bs_U32 flags);

 /**
  @return bs_Result
  */
BSAPI bs_Result
bs_iniAudio();

 /**
  @param ray
  @param position
  @param rotation
  @param scale
  @param out
  @return void
  */
BSAPI void
bs_rayVsObb(
    const bs_Ray* ray,
    const bs_vec3* position,
    const bs_vec4* rotation,
    const bs_vec3* scale,
    bs_RayVsObb* out);

 /**
  @param center
  @param radius
  @param point
  @param out
  @return bool
  */
BSAPI bool
bs_sphereVsPoint(
    const bs_vec3* center,
    float radius,
    const bs_vec3* point,
    bs_SphereVsPoint* out);

 /**
  @param center
  @param radius
  @param position
  @param rotation
  @param scale
  @return bool
  */
BSAPI bool
bs_sphereVsObbTest(
    const bs_vec3* center,
    float radius,
    const bs_vec3* position,
    const bs_vec4* rotation,
    const bs_vec3* scale);

 /**
  @param center
  @param radius
  @param position
  @param rotation
  @param scale
  @param out
  @return bool
  */
BSAPI bool
bs_sphereVsObb(
    const bs_vec3* center,
    float radius,
    const bs_vec3* position,
    const bs_vec4* rotation,
    const bs_vec3* scale,
    bs_SphereVsBox* out);

 /**
  @param position
  @param dimensions
  @param point
  @return bool
  */
BSAPI bool
bs_rectangleVsPoint(
    const bs_vec2* position,
    const bs_vec2* dimensions,
    const bs_vec2* point);

 /**
  @param l1_start
  @param l1_end
  @param l2_start
  @param l2_end
  @param out
  @return bool
  */
BSAPI bool
bs_lineVsLine(
    const bs_vec2* l1_start,
    const bs_vec2* l1_end,
    const bs_vec2* l2_start,
    const bs_vec2* l2_end,
    bs_LineVsLine* out);

 /**
  @param declaration
  @param attributes
  @param attributes_count
  @return void
  */
BSAPI void
bs_populateVertexDeclaration(
    bs_VertexDeclaration* declaration,
    bs_Attribute* attributes,
    int attributes_count);

 /**
  @param queue
  @param value
  @return void
  */
BSAPI void
bs_beginComment(
    bs_Queue* queue,
    char* value);

 /**
  @param queue
  @param value
  @param value_length
  @return void
  */
BSAPI void
bs_beginCommentN(
    bs_Queue* queue,
    char* value,
    int value_length);

 /**
  @param queue
  @param format
  @param args
  @return void
  */
BSAPI void
bs_beginCommentV(
    bs_Queue* queue,
    char* format,
    va_list args);

 /**
  @param queue
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_beginCommentF(
    bs_Queue* queue,
    char* format,
     ...);

 /**
  @param queue
  @return void
  */
BSAPI void
bs_endComment(
    bs_Queue* queue);

 /**
  @return bs_Image*
  */
BSAPI bs_Image*
bs_swapchainImage();

 /**
  @param queue
  @param index
  @param resolution
  @param value
  @return void
  */
BSAPI void
bs_clearStencil(
    bs_Queue* queue,
    bs_U32 index,
    bs_ivec2 resolution,
    bs_U32 value);

 /**
  @param queue
  @param index
  @param dim
  @param value
  @return void
  */
BSAPI void
bs_clearDepth(
    bs_Queue* queue,
    bs_U32 index,
    bs_ivec2 dim,
    float value);

 /**
  @param queue
  @param index
  @param dim
  @param depth_value
  @param stencil_value
  @return void
  */
BSAPI void
bs_clearDepthStencil(
    bs_Queue* queue,
    bs_U32 index,
    bs_ivec2 dim,
    float depth_value,
    bs_U32 stencil_value);

 /**
  @param queue
  @param index
  @param dim
  @param color
  @return void
  */
BSAPI void
bs_clearColor(
    bs_Queue* queue,
    bs_U32 index,
    bs_ivec2 dim,
    const bs_vec4* color);

 /**
  @param queue
  @param face
  @param reference
  @return void
  */
BSAPI void
bs_stencilReference(
    bs_Queue* queue,
    bs_StencilFaceFlag face,
    bs_U32 reference);

 /**
  @param queue
  @param flags
  @return void
  */
BSAPI void
bs_cull(
    bs_Queue* queue,
    bs_CullFlags flags);

 /**
  @param queue
  @param width
  @return void
  */
BSAPI void
bs_setLineWidth(
    bs_Queue* queue,
    float width);

 /**
  @param batch
  @return int
  */
BSAPI int
bs_batchSize(
    bs_Batch* batch);

 /**
  @param queue
  @param batch
  @param pipeline
  @param vertex_offset
  @param vertex_count
  @param first_instance
  @param num_instances
  @return void
  */
BSAPI void
bs_render(
    bs_Queue* queue,
    bs_Batch* batch,
    bs_Pipeline* pipeline,
    bs_U32 vertex_offset,
    bs_U32 vertex_count,
    bs_U32 first_instance,
    bs_U32 num_instances);

 /**
  @param queue
  @param dependency_flags
  @param src
  @param dst
  @param src_access
  @param dst_access
  @return void
  */
BSAPI void
bs_barrier(
    bs_Queue* queue,
    bs_U32 dependency_flags,
    bs_U32 src,
    bs_U32 dst,
    bs_U32 src_access,
    bs_U32 dst_access);

 /**
  @param ray_tracer
  @param pipeline
  @param width
  @param height
  @param depth
  @return void
  */
BSAPI void
bs_rayTrace(
    bs_RayTracer* ray_tracer,
    bs_Pipeline* pipeline,
    bs_U32 width,
    bs_U32 height,
    bs_U32 depth);

 /**
  @param object
  @param flags
  @param shaders
  @param shaders_count
  @return bs_Result
  */
BSAPI bs_Result
bs_rayTracer(
    bs_Object* object,
    bs_U32 flags,
    bs_Shader* shaders[],
    int shaders_count);

 /**
  @param ray_tracer
  @param aabb
  @return void
  */
BSAPI void
bs_accelerateAabb(
    bs_RayTracer* ray_tracer,
    bs_Aabb aabb);

 /**
  @param ray_tracer
  @param batch
  @return void
  */
BSAPI void
bs_accelerateBatch(
    bs_RayTracer* ray_tracer,
    bs_Batch* batch);

 /**
  @param queue
  @param ray_tracer
  @return bs_Result
  */
BSAPI bs_Result
bs_build(
    bs_Queue* queue,
    bs_RayTracer* ray_tracer);

 /**
  @param ray_tracer
  @return void
  */
BSAPI void
bs_destroyRayTracer(
    bs_RayTracer* ray_tracer);

 /**
  @param queue
  @param pipeline
  @param x
  @param y
  @param z
  @return void
  */
BSAPI void
bs_dispatchAsync(
    bs_Queue* queue,
    bs_Pipeline* pipeline,
    bs_U32 x,
    bs_U32 y,
    bs_U32 z);

 /**
  @param buffer
  @param format
  @param start
  @param count
  @return bs_Result
  */
BSAPI bs_Result
bs_bufferView(
    bs_Buffer* buffer,
    bs_Format format,
    bs_U64 start,
    bs_U64 count);

 /**
  @param object
  @param num_bytes
  @param usage_flags
  @param memory_flags
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_buffer(
    bs_Object* object,
    size_t num_bytes,
    bs_BufferUsageFlags usage_flags,
    bs_MemoryPropertyFlags memory_flags,
    bs_BufferBits flags);

 /**
  @param buffer
  @return bool
  */
BSAPI bool
bs_bufferIsMapped(
    bs_Buffer* buffer);

 /**
  @param buffer
  @return char*
  */
BSAPI char*
bs_bufferMap(
    bs_Buffer* buffer);

 /**
  @param buffer
  @param num_bytes
  @return bs_Result
  */
BSAPI bs_Result
bs_mapBuffer(
    bs_Buffer* buffer,
    bs_U32 num_bytes);

 /**
  @param buffer
  @return void
  */
BSAPI void
bs_unmapBuffer(
    bs_Buffer* buffer);

 /**
  @param buffer
  @return void
  */
BSAPI void
bs_stageNull(
    bs_Buffer* buffer);

 /**
  @param buffer
  @param list
  @return void
  */
BSAPI void
bs_stageList(
    bs_Buffer* buffer,
    bs_List* list);

 /**
  @param buffer
  @param channels_count
  @param dim
  @param data
  @return void
  */
BSAPI void
bs_stageImage(
    bs_Buffer* buffer,
    int channels_count,
    bs_ivec2 dim,
    const char* data);

 /**
  @param buffer
  @return void
  */
BSAPI void
bs_destroyBuffer(
    bs_Buffer* buffer);

 /**
  @param queue
  @param src
  @param dst
  @param src_offset
  @param dst_offset
  @param num_bytes
  @return void
  */
BSAPI void
bs_copyAsync(
    bs_Queue* queue,
    bs_Buffer* src,
    bs_Buffer* dst,
    bs_U32 src_offset,
    bs_U32 dst_offset,
    bs_U32 num_bytes);

 /**
  @param queue
  @param buffer
  @param offset
  @param num_bytes
  @param value
  @return void
  */
BSAPI void
bs_setBufferAsync(
    bs_Queue* queue,
    bs_Buffer* buffer,
    bs_U32 offset,
    bs_U32 num_bytes,
    bs_U32 value);

 /**
  @param object
  @param index_size
  @param vertex_shader
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_batch(
    bs_Object* object,
    int index_size,
    bs_Shader* vertex_shader,
    bs_BatchBits flags);

 /**
  @param batch
  @param name
  @return bs_Attribute*
  */
BSAPI bs_Attribute*
bs_queryAttribute(
    bs_Batch* batch,
    char* name);

 /**
  @param batch
  @param name
  @param name_length
  @return bs_Attribute*
  */
BSAPI bs_Attribute*
bs_queryAttributeN(
    bs_Batch* batch,
    char* name,
    int name_length);

 /**
  @param batch
  @param format
  @param args
  @return bs_Attribute*
  */
BSAPI bs_Attribute*
bs_queryAttributeV(
    bs_Batch* batch,
    char* format,
    va_list args);

 /**
  @param batch
  @param format
  @param ...
  @return bs_Attribute*
  */
BSAPI bs_Attribute*
bs_queryAttributeF(
    bs_Batch* batch,
    char* format,
     ...);

 /**
  @param batch
  @return bool
  */
BSAPI bool
bs_canPushBatch(
    bs_Batch* batch);

 /**
  @param batch
  @return bool
  */
BSAPI bool
bs_batchIsIndexed(
    bs_Batch* batch);

 /**
  @param batch
  @return void
  */
BSAPI void
bs_minimizeBatch(
    bs_Batch* batch);

 /**
  @param queue
  @param batch
  @param num_index_bytes
  @param num_vertex_bytes
  @return bs_Result
  */
BSAPI bs_Result
bs_pushBatch(
    bs_Queue* queue,
    bs_Batch* batch,
    bs_U32 num_index_bytes,
    bs_U32 num_vertex_bytes);

 /**
  @param batch
  @return void
  */
BSAPI void
bs_unpushBatch(
    bs_Batch* batch);

 /**
  @param batch
  @return void
  */
BSAPI void
bs_destroyBatch(
    bs_Batch* batch);

 /**
  @param batch
  @param num_indices
  @param num_vertices
  @return void
  */
BSAPI void
bs_ensureBatchSize(
    bs_Batch* batch,
    bs_U32 num_indices,
    bs_U32 num_vertices);

 /**
  @param declaration
  @param src
  @return void
  */
BSAPI void
bs_batchVertex(
    bs_VertexDeclaration* declaration,
    const unsigned char* src);

 /**
  @param batch
  @param offset
  @return bs_Range
  */
BSAPI bs_Range
bs_batchRange(
    bs_Batch* batch,
    bs_U32 offset);

 /**
  @param batch
  @param index
  @return void
  */
BSAPI void
bs_pushIndex(
    bs_Batch* batch,
    int index);

 /**
  @param batch
  @param indices
  @param indices_count
  @return void
  */
BSAPI void
bs_pushIndices(
    bs_Batch* batch,
    int indices[],
    int indices_count);

 /**
  @param batch
  @param offset
  @param color
  @return void
  */
BSAPI void
bs_batchCube(
    bs_Batch* batch,
    bs_U32* offset,
    bs_RGBA color);

 /**
  @param batch
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushCube(
    bs_Batch* batch,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param segments
  @param height
  @param radius
  @param color
  @return void
  */
BSAPI void
bs_batchCone(
    bs_Batch* batch,
    bs_U32* offset,
    int segments,
    float height,
    float radius,
    bs_RGBA color);

 /**
  @param batch
  @param segments
  @param height
  @param radius
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushCone(
    bs_Batch* batch,
    int segments,
    float height,
    float radius,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param quad
  @param color
  @return void
  */
BSAPI void
bs_batchQuad(
    bs_Batch* batch,
    bs_U32* offset,
    const bs_Quad* quad,
    bs_RGBA color);

 /**
  @param batch
  @param quad
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushQuad(
    bs_Batch* batch,
    const bs_Quad* quad,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param a
  @param b
  @param c
  @param color
  @return void
  */
BSAPI void
bs_batchTriangle(
    bs_Batch* batch,
    bs_U32* offset,
    bs_vec3 a,
    bs_vec3 b,
    bs_vec3 c,
    bs_RGBA color);

 /**
  @param batch
  @param a
  @param b
  @param c
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushTriangle(
    bs_Batch* batch,
    bs_vec3 a,
    bs_vec3 b,
    bs_vec3 c,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param start
  @param end
  @param color
  @return void
  */
BSAPI void
bs_batchLine(
    bs_Batch* batch,
    bs_U32* offset,
    bs_vec3 start,
    bs_vec3 end,
    bs_RGBA color);

 /**
  @param batch
  @param start
  @param end
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushLine(
    bs_Batch* batch,
    bs_vec3 start,
    bs_vec3 end,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param position
  @param color
  @return void
  */
BSAPI void
bs_batchPoint(
    bs_Batch* batch,
    bs_U32* offset,
    bs_vec3 position,
    bs_RGBA color);

 /**
  @param batch
  @param position
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushPoint(
    bs_Batch* batch,
    bs_vec3 position,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param aabb
  @param color
  @return void
  */
BSAPI void
bs_batchAabb(
    bs_Batch* batch,
    bs_U32* offset,
    bs_Aabb* aabb,
    bs_RGBA color);

 /**
  @param batch
  @param aabb
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushAabb(
    bs_Batch* batch,
    bs_Aabb* aabb,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param position
  @param radius
  @param lats
  @param longs
  @param color
  @return void
  */
BSAPI void
bs_batchSphere(
    bs_Batch* batch,
    bs_U32* offset,
    bs_vec3 position,
    float radius,
    bs_U32 lats,
    bs_U32 longs,
    bs_RGBA color);

 /**
  @param batch
  @param position
  @param radius
  @param lats
  @param longs
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushSphere(
    bs_Batch* batch,
    bs_vec3 position,
    float radius,
    bs_U32 lats,
    bs_U32 longs,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param pos
  @param width
  @param height
  @param color
  @return void
  */
BSAPI void
bs_batchPyramid(
    bs_Batch* batch,
    bs_U32* offset,
    bs_vec3 pos,
    float width,
    float height,
    bs_RGBA color);

 /**
  @param batch
  @param pos
  @param width
  @param height
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushPyramid(
    bs_Batch* batch,
    bs_vec3 pos,
    float width,
    float height,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param pos
  @param width
  @param height
  @param color
  @return void
  */
BSAPI void
bs_batchBipyramid(
    bs_Batch* batch,
    bs_U32* offset,
    bs_vec3 pos,
    float width,
    float height,
    bs_RGBA color);

 /**
  @param batch
  @param pos
  @param width
  @param height
  @param color
  @return bs_Range
  */
BSAPI bs_Range
bs_pushBipyramid(
    bs_Batch* batch,
    bs_vec3 pos,
    float width,
    float height,
    bs_RGBA color);

 /**
  @param batch
  @param offset
  @param primitive
  @return void
  */
BSAPI void
bs_batchPrimitive(
    bs_Batch* batch,
    bs_U32* offset,
    bs_Primitive* primitive);

 /**
  @param batch
  @param primitive
  @return bs_Range
  */
BSAPI bs_Range
bs_pushPrimitive(
    bs_Batch* batch,
    bs_Primitive* primitive);

 /**
  @param batch
  @param offset
  @param mesh
  @return void
  */
BSAPI void
bs_batchMesh(
    bs_Batch* batch,
    bs_U32* offset,
    bs_Mesh* mesh);

 /**
  @param batch
  @param mesh
  @return bs_Range
  */
BSAPI bs_Range
bs_pushMesh(
    bs_Batch* batch,
    bs_Mesh* mesh);

 /**
  @param batch
  @param offset
  @param model
  @return void
  */
BSAPI void
bs_batchModel(
    bs_Batch* batch,
    bs_U32* offset,
    bs_Model* model);

 /**
  @param batch
  @param model
  @return bs_Range
  */
BSAPI bs_Range
bs_pushModel(
    bs_Batch* batch,
    bs_Model* model);

 /**
  @param renderer
  @param context
  @return void
  */
BSAPI void
bs_autoResizeRenderer(
    bs_Renderer* renderer,
    bs_Context* context);

 /**
  @param object
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_renderer(
    bs_Object* object,
    bs_RendererBits flags);

 /**
  @param renderer
  @param output
  @return void
  */
BSAPI void
bs_output(
    bs_Renderer* renderer,
    bs_Output output);

 /**
  @param renderer
  @param input
  @return void
  */
BSAPI void
bs_input(
    bs_Renderer* renderer,
    bs_Input input);

 /**
  @param renderer
  @param src_subpass
  @param dst_subpass
  @param flags
  @param src_stage
  @param dst_stage
  @param src_access
  @param dst_access
  @return void
  */
BSAPI void
bs_dependency(
    bs_Renderer* renderer,
    bs_U32 src_subpass,
    bs_U32 dst_subpass,
    bs_DependencyFlags flags,
    bs_PipelineStage src_stage,
    bs_PipelineStage dst_stage,
    bs_AccessMask src_access,
    bs_AccessMask dst_access);

 /**
  @param renderer
  @return bs_Result
  */
BSAPI bs_Result
bs_renderPass(
    bs_Renderer* renderer);

 /**
  @param renderer
  @param resolution
  @return bs_Result
  */
BSAPI bs_Result
bs_framebuffer(
    bs_Renderer* renderer,
    bs_ivec2 resolution);

 /**
  @param queue
  @param renderer
  @param callbacks
  @param callbacks_count
  @return void
  */
BSAPI void
bs_runPass(
    bs_Queue* queue,
    bs_Renderer* renderer,
    bs_SubpassFunction callbacks[],
    int callbacks_count);

 /**
  @param renderer
  @return bool
  */
BSAPI bool
bs_rendererIsDynamic(
    bs_Renderer* renderer);

 /**
  @param queue
  @param renderer
  @return bs_RendererScope
  */
BSAPI bs_RendererScope
bs_beginRender(
    bs_Queue* queue,
    bs_Renderer* renderer);

 /**
  @param queue
  @param renderer
  @return void
  */
BSAPI void
bs_endRender(
    bs_Queue* queue,
    bs_Renderer* renderer);

 /**
  @param renderer
  @return void
  */
BSAPI void
bs_destroyRenderer(
    bs_Renderer* renderer);

 /**
  @param renderer
  @param resolution
  @return void
  */
BSAPI void
bs_resizeRenderer(
    bs_Renderer* renderer,
    bs_ivec2 resolution);

 /**
  @param flags
  @return bs_I32
  */
BSAPI bs_I32
bs_queueFamily(
    bs_QueueBits flags);

 /**
  @param queue
  @param wait_queues
  @param wait_queues_count
  @return void
  */
BSAPI void
bs_present(
    bs_Queue* queue,
    bs_Queue* wait_queues[],
    int wait_queues_count);

 /**
  @return void
  */
BSAPI void
bs_acquire();

 /**
  @param queue
  @return int
  */
BSAPI int
bs_queueSwap(
    bs_Queue* queue);

 /**
  @param queue
  @param function
  @return void
  */
BSAPI void
bs_enqueue(
    bs_Queue* queue,
    bs_Callback function);

 /**
  @return int
  */
BSAPI int
bs_imageIndex();

 /**
  @param object
  @param queue_index
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_queue(
    bs_Object* object,
    bs_U32 queue_index,
    bs_QueueBits flags);

 /**
  @param queue
  @return void
  */
BSAPI void
bs_destroyQueue(
    bs_Queue* queue);

 /**
  @return void
  */
BSAPI void
bs_stallGPU();

 /**
  @param queue
  @return void
  */
BSAPI void
bs_stallQueue(
    bs_Queue* queue);

 /**
  @param queue
  @return bs_Result
  */
BSAPI bs_Result
bs_stall(
    bs_Queue* queue);

 /**
  @param queue
  @return bs_Result
  */
BSAPI bs_Result
bs_poll(
    bs_Queue* queue);

 /**
  @param object
  @param dim
  @param num_indices
  @param format
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_image(
    bs_Object* object,
    bs_ivec2 dim,
    int num_indices,
    bs_Format format,
    bs_U32 flags);

 /**
  @param queue
  @param image
  @param index
  @param old_layout
  @param new_layout
  @return void
  */
BSAPI void
bs_transition(
    bs_Queue* queue,
    bs_Image* image,
    int index,
    bs_ImageLayout old_layout,
    bs_ImageLayout new_layout);

 /**
  @param out_png_data
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_peekPng(
    bs_PngData* out_png_data,
    char* path);

 /**
  @param out_png_data
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_peekPngN(
    bs_PngData* out_png_data,
    char* path,
    int path_length);

 /**
  @param out_png_data
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_peekPngV(
    bs_PngData* out_png_data,
    char* format,
    va_list args);

 /**
  @param out_png_data
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_peekPngF(
    bs_PngData* out_png_data,
    char* format,
     ...);

 /**
  @param data
  @param size
  @param channels_count
  @param out_png_data
  @return bs_Result
  */
BSAPI bs_Result
bs_loadPngData(
    char* data,
    size_t size,
    int channels_count,
    bs_PngData* out_png_data);

 /**
  @param path
  @param channels_count
  @param out_png_data
  @return bs_Result
  */
BSAPI bs_Result
bs_loadPng(
    const char* path,
    int channels_count,
    bs_PngData* out_png_data);

 /**
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_peekFile(
    bs_FileInfo* out,
    char* path,
    int path_length);

 /**
  @param data
  @param resolution
  @param type
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_savePng(
    char* data,
    bs_ivec2 resolution,
    bs_PngType type,
    char* path);

 /**
  @param data
  @param resolution
  @param type
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_savePngN(
    char* data,
    bs_ivec2 resolution,
    bs_PngType type,
    char* path,
    int path_length);

 /**
  @param data
  @param resolution
  @param type
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_savePngV(
    char* data,
    bs_ivec2 resolution,
    bs_PngType type,
    char* format,
    va_list args);

 /**
  @param data
  @param resolution
  @param type
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_savePngF(
    char* data,
    bs_ivec2 resolution,
    bs_PngType type,
    char* format,
     ...);

 /**
  @param out_size
  @param data
  @param size
  @param type
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_encodePng(
    size_t* out_size,
    const unsigned char* data,
    bs_ivec2 size,
    bs_PngType type,
    unsigned char** out);

 /**
  @param image
  @return void
  */
BSAPI void
bs_destroyImage(
    bs_Image* image);

 /**
  @param image
  @param size
  @param indices_count
  @return bs_Result
  */
BSAPI bs_Result
bs_resizeImage(
    bs_Image* image,
    bs_ivec2 size,
    int indices_count);

 /**
  @param image
  @param name_hash
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_queryImageIndexHash(
    bs_Image* image,
    bs_U64 name_hash,
    int* out);

 /**
  @param image
  @param name
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_queryImageIndex(
    bs_Image* image,
    char* name,
    int* out);

 /**
  @param queue
  @param image
  @param buffer
  @param image_index
  @param layout
  @param buffer_offset
  @param offset
  @param resolution
  @return void
  */
BSAPI void
bs_copyImageToBufferAsync(
    bs_Queue* queue,
    bs_Image* image,
    bs_Buffer* buffer,
    int image_index,
    bs_ImageLayout layout,
    bs_U64 buffer_offset,
    bs_ivec2 offset,
    bs_ivec2 resolution);

 /**
  @param queue
  @param buffer
  @param image
  @param index
  @param layout
  @return void
  */
BSAPI void
bs_copyBufferToImage(
    bs_Queue* queue,
    bs_Buffer* buffer,
    bs_Image* image,
    int index,
    bs_ImageLayout layout);

 /**
  @param queue
  @param operation
  @return void
  */
BSAPI void
bs_blit(
    bs_Queue* queue,
    bs_BlitOperation operation);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_loadImage(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_ImageBits flags,
    char* path);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadImageN(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_ImageBits flags,
    char* path,
    int path_length);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadImageV(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_ImageBits flags,
    char* format,
    va_list args);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadImageF(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_ImageBits flags,
    char* format,
     ...);

 /**
  @param format
  @return bool
  */
BSAPI bool
bs_isStencilFormat(
    bs_Format format);

 /**
  @param format
  @return bool
  */
BSAPI bool
bs_isDepthFormat(
    bs_Format format);

 /**
  @param format
  @return bool
  */
BSAPI bool
bs_hasAlpha(
    bs_Format format);

 /**
  @param sampler
  @return void
  */
BSAPI void
bs_destroySampler(
    bs_Sampler* sampler);

 /**
  @param object
  @param filter
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_sampler(
    bs_Object* object,
    bs_ImageFilter filter,
    bs_SamplerBits flags);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_loadAtlas(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_U32 flags,
    char* path);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadAtlasN(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_U32 flags,
    char* path,
    int path_length);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadAtlasV(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_U32 flags,
    char* format,
    va_list args);

 /**
  @param queue
  @param object
  @param package_id
  @param flags
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadAtlasF(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    bs_U32 flags,
    char* format,
     ...);

 /**
  @param atlas
  @param texture_id
  @return bs_vec4
  */
BSAPI bs_vec4
bs_atlasCoordinates(
    bs_Atlas* atlas,
    int texture_id);

 /**
  @param uv
  @return bs_vec4
  */
BSAPI bs_vec4
bs_mirrorUV(
    bs_vec4 uv);

 /**
  @param uv
  @return bs_vec4
  */
BSAPI bs_vec4
bs_flipUV(
    bs_vec4 uv);

 /**
  @param atlas
  @param texture
  @return bs_vec2
  */
BSAPI bs_vec2
bs_atlasSize(
    bs_Atlas* atlas,
    int texture);

 /**
  @param atlas
  @param hash
  @return int
  */
BSAPI int
bs_queryAtlasHash(
    bs_Atlas* atlas,
    bs_U64 hash);

 /**
  @param atlas
  @param name
  @return int
  */
BSAPI int
bs_queryAtlas(
    bs_Atlas* atlas,
    const char* name);

 /**
  @param atlas
  @return void
  */
BSAPI void
bs_destroyAtlas(
    bs_Atlas* atlas);

 /**
  @param queue
  @param object
  @param package_id
  @param resource_name
  @param data
  @param flags
  @return bs_Result
  */
BSAPI bs_Result
bs_loadAtlasMemory(
    bs_Queue* queue,
    bs_Object* object,
    int package_id,
    char* resource_name,
    char* data,
    bs_U32 flags);

 /**
  @param argc
  @param argv
  @return void
  */
BSAPI void
bs_parseArgs(
    int argc,
    char* argv[]);

 /**
  @param count
  @return void
  */
BSAPI void
bs_configureQueuesCount(
    bs_U32 count);

 /**
  @return void
  */
BSAPI void
bs_ini();

 /**
  @param procedures
  @param count
  @param dll_handle
  @param destination
  @return void
  */
BSAPI void
bs_queryProcedures(
    bs_Procedure* procedures,
    int count,
    void* dll_handle,
    unsigned char* destination);

 /**
  @param queue
  @param stage
  @return bs_WaitSemaphore
  */
BSAPI bs_WaitSemaphore
bs_queueSemaphore(
    bs_Queue* queue,
    bs_PipelineStage stage);

 /**
  @return bs_WaitSemaphore
  */
BSAPI bs_WaitSemaphore
bs_acquisitionSemaphore();

 /**
  @param queue
  @return bs_Result
  */
BSAPI bs_Result
bs_resetQueue(
    bs_Queue* queue);

 /**
  @param queue
  @param wait_semaphores_count
  @param wait_semaphores
  @return bs_Result
  */
BSAPI bs_Result
bs_pushQueue(
    bs_Queue* queue,
    int wait_semaphores_count,
    bs_WaitSemaphore wait_semaphores[]);

 /**
  @param handle
  @param type
  @param value
  @return void
  */
BSAPI void
bsi_nameHandle(
    bs_U64 handle,
    bs_U32 type,
    char* value);

 /**
  @param handle
  @param type
  @param value
  @param value_length
  @return void
  */
BSAPI void
bsi_nameHandleN(
    bs_U64 handle,
    bs_U32 type,
    char* value,
    int value_length);

 /**
  @param handle
  @param type
  @param format
  @param args
  @return void
  */
BSAPI void
bsi_nameHandleV(
    bs_U64 handle,
    bs_U32 type,
    char* format,
    va_list args);

 /**
  @param handle
  @param type
  @param format
  @param ...
  @return void
  */
BSAPI void
bsi_nameHandleF(
    bs_U64 handle,
    bs_U32 type,
    char* format,
     ...);

 /**
  @param json
  @return bs_JsonEnumeration
  */
BSAPI bs_JsonEnumeration
bs_beginEnumeration(
    bs_Json* json);

 /**
  @param json
  @param e
  @return void
  */
BSAPI void
bs_enumerateJson(
    bs_Json* json,
    bs_JsonEnumeration* e);

 /**
  @param json
  @param object
  @return bs_Json
  */
BSAPI bs_Json
bs_jsonRoot(
    bs_Json* json,
    bs_JsonObject object);

 /**
  @param root
  @return void
  */
BSAPI void
bs_ensureJsonMutable(
    bs_Json* root);

 /**
  @param root
  @return bs_Json
  */
BSAPI bs_Json
bs_jsonCopy(
    const bs_Json* root);

 /**
  @param json
  @param flags
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_saveJson(
    bs_Json* json,
    bs_SaveJsonBits flags,
    char** out);

 /**
  @return bs_Json
  */
BSAPI bs_Json
bs_emptyJson();

 /**
  @return bs_Json
  */
BSAPI bs_Json
bs_emptyJsonArray();

 /**
  @param raw
  @param len
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_json(
    char* raw,
    int len,
    bs_Json* out);

 /**
  @param out
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_loadJson(
    bs_Json* out,
    char* path);

 /**
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadJsonN(
    bs_Json* out,
    char* path,
    int path_length);

 /**
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadJsonV(
    bs_Json* out,
    char* format,
    va_list args);

 /**
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadJsonF(
    bs_Json* out,
    char* format,
     ...);

 /**
  @param json
  @return void
  */
BSAPI void
bs_destroyJson(
    bs_Json* json);

 /**
  @param raw
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_parseJsonValue(
    char* raw);

 /**
  @param root
  @param expect
  @param path
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_fetchJson(
    bs_Json* root,
    bs_JsonType expect,
    char* path);

 /**
  @param root
  @param expect
  @param path
  @param path_length
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_fetchJsonN(
    bs_Json* root,
    bs_JsonType expect,
    char* path,
    int path_length);

 /**
  @param root
  @param expect
  @param format
  @param args
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_fetchJsonV(
    bs_Json* root,
    bs_JsonType expect,
    char* format,
    va_list args);

 /**
  @param root
  @param expect
  @param format
  @param ...
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_fetchJsonF(
    bs_Json* root,
    bs_JsonType expect,
    char* format,
     ...);

 /**
  @param root
  @param path
  @return void
  */
BSAPI void
bs_deleteJson(
    bs_Json* root,
    char* path);

 /**
  @param root
  @param path
  @param path_length
  @return void
  */
BSAPI void
bs_deleteJsonN(
    bs_Json* root,
    char* path,
    int path_length);

 /**
  @param root
  @param format
  @param args
  @return void
  */
BSAPI void
bs_deleteJsonV(
    bs_Json* root,
    char* format,
    va_list args);

 /**
  @param root
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_deleteJsonF(
    bs_Json* root,
    char* format,
     ...);

 /**
  @param root
  @param value
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureJson(
    bs_Json* root,
    bs_JsonValue value,
    char* path);

 /**
  @param root
  @param value
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureJsonN(
    bs_Json* root,
    bs_JsonValue value,
    char* path,
    int path_length);

 /**
  @param root
  @param value
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureJsonV(
    bs_Json* root,
    bs_JsonValue value,
    char* format,
    va_list args);

 /**
  @param root
  @param value
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureJsonF(
    bs_Json* root,
    bs_JsonValue value,
    char* format,
     ...);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromObject(
    bs_JsonObject x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromRoot(
    bs_Json x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromBool(
    bool x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromInteger(
    int x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromFloat(
    double x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromString(
    char* x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromStringPointer(
    char* x);

 /**
  @param x
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonValueFromDateTime(
    bs_DateTime x);

 /**
  @param json
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonObject(
    bs_Json* json);

 /**
  @param type
  @param data
  @param count
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonArray(
    bs_JsonType type,
    char* data,
    int count);

 /**
  @param vector
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonVec2(
    bs_vec2* vector);

 /**
  @param vector
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonVec3(
    bs_vec3* vector);

 /**
  @param vector
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonVec4(
    bs_vec4* vector);

 /**
  @param color
  @return bs_JsonValue
  */
BSAPI bs_JsonValue
bs_jsonRGBA(
    bs_RGBA color);

 /**
  @param value
  @return void
  */
BSAPI void
bs_logSection(
    char* value);

 /**
  @param value
  @param value_length
  @return void
  */
BSAPI void
bs_logSectionN(
    char* value,
    int value_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_logSectionV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_logSectionF(
    char* format,
     ...);

 /**
  @return void
  */
BSAPI void
bs_logEndOfSection();

 /**
  @param level
  @param value
  @return void
  */
BSAPI void
bs_logWithTimestamp(
    bs_MessageLevel level,
    char* value);

 /**
  @param level
  @param value
  @param value_length
  @return void
  */
BSAPI void
bs_logWithTimestampN(
    bs_MessageLevel level,
    char* value,
    int value_length);

 /**
  @param level
  @param format
  @param args
  @return void
  */
BSAPI void
bs_logWithTimestampV(
    bs_MessageLevel level,
    char* format,
    va_list args);

 /**
  @param level
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_logWithTimestampF(
    bs_MessageLevel level,
    char* format,
     ...);

 /**
  @param message
  @return void
  */
BSAPI void
bs_log(
    char* message);

 /**
  @param message
  @param message_length
  @return void
  */
BSAPI void
bs_logN(
    char* message,
    int message_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_logV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_logF(
    char* format,
     ...);

 /**
  @param message
  @return void
  */
BSAPI void
bs_info(
    char* message);

 /**
  @param message
  @param message_length
  @return void
  */
BSAPI void
bs_infoN(
    char* message,
    int message_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_infoV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_infoF(
    char* format,
     ...);

 /**
  @param message
  @return void
  */
BSAPI void
bs_warn(
    char* message);

 /**
  @param message
  @param message_length
  @return void
  */
BSAPI void
bs_warnN(
    char* message,
    int message_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_warnV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_warnF(
    char* format,
     ...);

 /**
  @param message
  @return void
  */
BSAPI void
bs_critical(
    char* message);

 /**
  @param message
  @param message_length
  @return void
  */
BSAPI void
bs_criticalN(
    char* message,
    int message_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_criticalV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_criticalF(
    char* format,
     ...);

 /**
  @return bs_Instance*
  */
BSAPI bs_Instance*
bs_instance();

 /**
  @return bs_Args*
  */
BSAPI bs_Args*
bs_args();

 /**
  @return bs_Features*
  */
BSAPI bs_Features*
bs_features();

 /**
  @return bs_Props*
  */
BSAPI bs_Props*
bs_props();

 /**
  @return bs_Config*
  */
BSAPI bs_Config*
bs_config();

 /**
  @param value
  @return void
  */
BSAPI void
bs_system(
    char* value);

 /**
  @param value
  @param value_length
  @return void
  */
BSAPI void
bs_systemN(
    char* value,
    int value_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_systemV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_systemF(
    char* format,
     ...);

 /**
  @param function
  @param param
  @return void
  */
BSAPI void
bs_createThread(
    bs_ThreadFunction function,
    void* param);

 /**
  @param format
  @param args
  @return int
  */
BSAPI int
bs_formatStringLength(
    const char* format,
    va_list args);

 /**
  @param pool
  @param string
  @return const char*
  */
BSAPI const char*
bs_checkStringPool(
    bs_List* pool,
    char* string);

 /**
  @param old
  @param len
  @return bs_String*
  */
BSAPI bs_String*
bs_stringAlloc(
    bs_String* old,
    int len);

 /**
  @param old
  @return bs_String*
  */
BSAPI bs_String*
bs_emptyString(
    bs_String* old);

 /**
  @param old
  @param value
  @return bs_String*
  */
BSAPI bs_String*
bs_string(
    bs_String* old,
    char* value);

 /**
  @param old
  @param value
  @param value_length
  @return bs_String*
  */
BSAPI bs_String*
bs_stringN(
    bs_String* old,
    char* value,
    int value_length);

 /**
  @param old
  @param format
  @param args
  @return bs_String*
  */
BSAPI bs_String*
bs_stringV(
    bs_String* old,
    char* format,
    va_list args);

 /**
  @param old
  @param format
  @param ...
  @return bs_String*
  */
BSAPI bs_String*
bs_stringF(
    bs_String* old,
    char* format,
     ...);

 /**
  @param string
  @param len
  @return void
  */
BSAPI void
bs_toUpper(
    char* string,
    int len);

 /**
  @param string
  @param len
  @return void
  */
BSAPI void
bs_toLower(
    char* string,
    int len);

 /**
  @param data
  @param size
  @return bs_U64
  */
BSAPI bs_U64
bs_hash(
    unsigned char* data,
    size_t size);

 /**
  @param string
  @return bs_U64
  */
BSAPI bs_U64
bs_stringHash(
    char* string);

 /**
  @param string
  @param prefix
  @return bool
  */
BSAPI bool
bs_startsWith(
    char* string,
    const char* prefix);

 /**
  @param string
  @param suffix
  @return bool
  */
BSAPI bool
bs_endsWith(
    char* string,
    const char* suffix);

 /**
  @param string
  @param len
  @return char
  */
BSAPI char
bs_lastChar(
    char* string,
    int len);

 /**
  @param string
  @param c
  @return bool
  */
BSAPI bool
bs_stringContainsChar(
    char* string,
    char c);

 /**
  @return bs_String*
  */
BSAPI bs_String*
bs_workingDirectory();

 /**
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_setWorkingDirectory(
    char* path);

 /**
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_setWorkingDirectoryN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_setWorkingDirectoryV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_setWorkingDirectoryF(
    char* format,
     ...);

 /**
  @return bs_String*
  */
BSAPI bs_String*
bs_executablePath();

 /**
  @return char*
  */
BSAPI char*
bs_appdataPath();

 /**
  @param string
  @param len
  @return void
  */
BSAPI void
bs_shortenString(
    bs_String* string,
    int len);

 /**
  @param string
  @param c
  @return bs_String*
  */
BSAPI bs_String*
bs_appendChar(
    bs_String* string,
    char c);

 /**
  @param string
  @param start
  @param count
  @return void
  */
BSAPI void
bs_removeCharRange(
    bs_String* string,
    int start,
    int count);

 /**
  @param string
  @param index
  @param c
  @return bs_String*
  */
BSAPI bs_String*
bs_insertChar(
    bs_String* string,
    int index,
    char c);

 /**
  @param string
  @param path
  @param path_len
  @return bs_String*
  */
BSAPI bs_String*
bs_appendPath(
    bs_String* string,
    char* path,
    int path_len);

 /**
  @param string
  @param string_len
  @param a
  @param b
  @return void
  */
BSAPI void
bs_replaceCharOccurrences(
    char* string,
    int string_len,
    char a,
    char b);

 /**
  @param s
  @param n
  @return char*
  */
BSAPI char*
bs_strndup(
    const char* s,
    size_t n);

 /**
  @param src
  @param n
  @return size_t
  */
BSAPI size_t
bs_strnlen(
    const char* src,
    size_t n);

 /**
  @param stringp
  @param delim
  @return char*
  */
BSAPI char*
bs_strsep(
    char** stringp,
    const char* delim);

 /**
  @param haystack
  @param haystack_len
  @param needle
  @param needle_len
  @return void*
  */
BSAPI void*
bs_memmem(
    const void* haystack,
    bs_U32 haystack_len,
    const void* const needle,
    const bs_U32 needle_len);

 /**
  @param value
  @param alignment
  @return bs_U32
  */
BSAPI bs_U32
bs_alignUp(
    bs_U32 value,
    bs_U32 alignment);

 /**
  @param src
  @param dst
  @param dst_size
  @return bs_Result
  */
BSAPI bs_Result
bs_widen(
    char* src,
    wchar_t* dst,
    bs_U32 dst_size);

 /**
  @param src
  @param dst
  @param dst_size
  @return bs_Result
  */
BSAPI bs_Result
bs_unwiden(
    wchar_t* src,
    char* dst,
    bs_U32 dst_size);

 /**
  @param format
  @param args
  @return char*
  */
BSAPI char*
bs_charStringV(
    const char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return char*
  */
BSAPI char*
bs_charStringF(
    const char* format,
     ...);

 /**
  @param p
  @return void*
  */
BSAPI void*
bs_free(
    void* p);

 /**
  @param size
  @return void*
  */
BSAPI void*
bs_malloc(
    bs_U64 size);

 /**
  @param num_units
  @param unit_size
  @return void*
  */
BSAPI void*
bs_calloc(
    bs_U64 num_units,
    bs_U64 unit_size);

 /**
  @param p
  @param size
  @return void*
  */
BSAPI void*
bs_realloc(
    void* p,
    bs_U64 size);

 /**
  @param list
  @param data
  @return bool
  */
BSAPI bool
bs_listContains(
    bs_List* list,
    void* data);

 /**
  @param list
  @param index
  @return void*
  */
BSAPI void*
bs_fetchUnit(
    bs_List* list,
    bs_U32 index);

 /**
  @param list
  @return void*
  */
BSAPI void*
bs_fetchLast(
    bs_List* list);

 /**
  @param list
  @param num_units
  @return void
  */
BSAPI void
bs_ensureSize(
    bs_List* list,
    bs_U32 num_units);

 /**
  @param list
  @param index
  @param count
  @return void
  */
BSAPI void
bs_erase(
    bs_List* list,
    int index,
    bs_U32 count);

 /**
  @param list
  @param data
  @return void*
  */
BSAPI void*
bs_pushBack(
    bs_List* list,
    void* data);

 /**
  @param source
  @param destination
  @return void*
  */
BSAPI void*
bs_pushBackList(
    bs_List* source,
    bs_List* destination);

 /**
  @param list
  @return void
  */
BSAPI void
bs_destroyList(
    bs_List* list);

 /**
  @param list
  @param unit_index
  @return void
  */
BSAPI void
bs_seekList(
    bs_List* list,
    bs_U32 unit_index);

 /**
  @param list
  @return void
  */
BSAPI void
bs_minimizeList(
    bs_List* list);

 /**
  @param unit_size
  @param increment
  @return bs_List
  */
BSAPI bs_List
bs_list(
    int unit_size,
    int increment);

 /**
  @param guid
  @param out
  @return void
  */
BSAPI void
bs_guidToString(
    bs_GUID* guid,
    char out[37]);

 /**
  @param str
  @return bs_GUID
  */
BSAPI bs_GUID
bs_stringToGuid(
    const char* str);

 /**
  @param a
  @param b
  @return bool
  */
BSAPI bool
bs_sameGuid(
    bs_GUID* a,
    bs_GUID* b);

 /**
  @return bs_GUID
  */
BSAPI bs_GUID
bs_guid();

 /**
  @param guid
  @return bool
  */
BSAPI bool
bs_guidIsNull(
    bs_GUID* guid);

 /**
  @param n
  @return int
  */
BSAPI int
bs_numDigits(
    int n);

 /**
  @param path
  @return bool
  */
BSAPI bool
bs_directoryExists(
    char* path);

 /**
  @param path
  @param path_length
  @return bool
  */
BSAPI bool
bs_directoryExistsN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bool
  */
BSAPI bool
bs_directoryExistsV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bool
  */
BSAPI bool
bs_directoryExistsF(
    char* format,
     ...);

 /**
  @param path
  @return char*
  */
BSAPI char*
bs_fileExtension(
    const char* path);

 /**
  @param path
  @param extension
  @return bool
  */
BSAPI bool
bs_fileExtensionIs(
    const char* path,
    char* extension);

 /**
  @param path
  @return char*
  */
BSAPI char*
bs_fileName(
    const char* path);

 /**
  @param data
  @param data_len
  @param value
  @return bs_Result
  */
BSAPI bs_Result
bs_appendFile(
    char* data,
    bs_U32 data_len,
    char* value);

 /**
  @param data
  @param data_len
  @param value
  @param value_length
  @return bs_Result
  */
BSAPI bs_Result
bs_appendFileN(
    char* data,
    bs_U32 data_len,
    char* value,
    int value_length);

 /**
  @param data
  @param data_len
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_appendFileV(
    char* data,
    bs_U32 data_len,
    char* format,
    va_list args);

 /**
  @param data
  @param data_len
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_appendFileF(
    char* data,
    bs_U32 data_len,
    char* format,
     ...);

 /**
  @param data
  @param data_len
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_saveFile(
    char* data,
    bs_U32 data_len,
    char* path);

 /**
  @param data
  @param data_len
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_saveFileN(
    char* data,
    bs_U32 data_len,
    char* path,
    int path_length);

 /**
  @param data
  @param data_len
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_saveFileV(
    char* data,
    bs_U32 data_len,
    char* format,
    va_list args);

 /**
  @param data
  @param data_len
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_saveFileF(
    char* data,
    bs_U32 data_len,
    char* format,
     ...);

 /**
  @param path
  @return void
  */
BSAPI void
bs_convertWin32Path(
    char* path);

 /**
  @param path
  @param path_length
  @return void
  */
BSAPI void
bs_convertWin32PathN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_convertWin32PathV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_convertWin32PathF(
    char* format,
     ...);

 /**
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureDirectory(
    char* path);

 /**
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureDirectoryN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureDirectoryV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_ensureDirectoryF(
    char* format,
     ...);

 /**
  @param out
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_fileModifiedDate(
    bs_DateTime* out,
    char* path);

 /**
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_fileModifiedDateN(
    bs_DateTime* out,
    char* path,
    int path_length);

 /**
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_fileModifiedDateV(
    bs_DateTime* out,
    char* format,
    va_list args);

 /**
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_fileModifiedDateF(
    bs_DateTime* out,
    char* format,
     ...);

 /**
  @param date
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_setFileModifiedDate(
    bs_DateTime* date,
    char* path);

 /**
  @param date
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_setFileModifiedDateN(
    bs_DateTime* date,
    char* path,
    int path_length);

 /**
  @param date
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_setFileModifiedDateV(
    bs_DateTime* date,
    char* format,
    va_list args);

 /**
  @param date
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_setFileModifiedDateF(
    bs_DateTime* date,
    char* format,
     ...);

 /**
  @param old
  @param path
  @param path_len
  @return bs_String*
  */
BSAPI bs_String*
bs_fullPath(
    bs_String* old,
    const char* path,
    int path_len);

 /**
  @param path
  @return bool
  */
BSAPI bool
bs_fileExists(
    char* path);

 /**
  @param path
  @param path_length
  @return bool
  */
BSAPI bool
bs_fileExistsN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bool
  */
BSAPI bool
bs_fileExistsV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bool
  */
BSAPI bool
bs_fileExistsF(
    char* format,
     ...);

 /**
  @param str
  @return bs_I64
  */
BSAPI bs_I64
bs_toLong(
    const char* str);

 /**
  @param str
  @return bs_U64
  */
BSAPI bs_U64
bs_toULong(
    const char* str);

 /**
  @param str
  @return bs_F64
  */
BSAPI bs_F64
bs_toDouble(
    const char* str);

 /**
  @param package_id
  @param name
  @param flags
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_model(
    int package_id,
    const char* name,
    bs_U32 flags,
    bs_Resource** out);

 /**
  @param model
  @return void
  */
BSAPI void
bs_destroyModel(
    bs_Model* model);

 /**
  @param animation_joint
  @param time
  @return bs_vec4
  */
BSAPI bs_vec4
bs_interpolateRotation(
    bs_AnimationBone* animation_joint,
    float time);

 /**
  @param animation_joint
  @param time
  @return bs_vec3
  */
BSAPI bs_vec3
bs_interpolateTranslation(
    bs_AnimationBone* animation_joint,
    float time);

 /**
  @param animation_joint
  @param time
  @return bs_vec3
  */
BSAPI bs_vec3
bs_interpolateScale(
    bs_AnimationBone* animation_joint,
    float time);

 /**
  @param armature
  @param bone
  @return bs_mat4
  */
BSAPI bs_mat4
bs_boneTransform(
    bs_Armature* armature,
    bs_Bone* bone);

 /**
  @param armature
  @param bone
  @return bs_vec3
  */
BSAPI bs_vec3
bs_bonePosition(
    bs_Armature* armature,
    bs_Bone* bone);

 /**
  @param armature
  @param bone
  @param transform
  @return bs_mat4*
  */
BSAPI bs_mat4*
bs_transformBone(
    bs_Armature* armature,
    bs_Bone* bone,
    const bs_mat4* transform);

 /**
  @param armature
  @param animation_a
  @param animation_b
  @param factor
  @param time_a
  @param time_b
  @return void
  */
BSAPI void
bs_blendPose(
    bs_Armature* armature,
    bs_Animation* animation_a,
    bs_Animation* animation_b,
    float factor,
    float time_a,
    float time_b);

 /**
  @param armature
  @param local_transform
  @param parent_id
  @param name
  @return int
  */
BSAPI int
bs_bone(
    bs_Armature* armature,
    bs_mat4 local_transform,
    int parent_id,
    const char* name);

 /**
  @param armature
  @param end_effector_id
  @param target
  @param chain_length
  @param chain
  @return void
  */
BSAPI void
bs_fabrik(
    bs_Armature* armature,
    int end_effector_id,
    bs_vec3 target,
    int chain_length,
    float* chain);

 /**
  @param armature
  @return void
  */
BSAPI void
bs_bindPose(
    bs_Armature* armature);

 /**
  @param bone
  @param timestamp
  @param position
  @return void
  */
BSAPI void
bs_keyframePosition(
    bs_AnimationBone* bone,
    float timestamp,
    bs_vec3 position);

 /**
  @param bone
  @param timestamp
  @param rotation
  @return void
  */
BSAPI void
bs_keyframeRotation(
    bs_AnimationBone* bone,
    float timestamp,
    bs_vec4 rotation);

 /**
  @param bone
  @param timestamp
  @param scale
  @return void
  */
BSAPI void
bs_keyframeScale(
    bs_AnimationBone* bone,
    float timestamp,
    bs_vec3 scale);

 /**
  @param model
  @param name
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_loadAnimation(
    bs_Model* model,
    const char* name,
    bs_Animation* out);

 /**
  @param armature
  @param name
  @return int
  */
BSAPI int
bs_queryBoneId(
    bs_Armature* armature,
    const char* name);

 /**
  @param model
  @param name
  @return bs_Armature*
  */
BSAPI bs_Armature*
bs_queryArmature(
    bs_Model* model,
    const char* name);

 /**
  @param armature
  @param name
  @return bs_Bone*
  */
BSAPI bs_Bone*
bs_queryBone(
    bs_Armature* armature,
    const char* name);

 /**
  @param model
  @param name
  @return bs_Mesh*
  */
BSAPI bs_Mesh*
bs_queryMesh(
    bs_Model* model,
    const char * name);

 /**
  @param model
  @param hash
  @return bs_Mesh*
  */
BSAPI bs_Mesh*
bs_queryMeshHash(
    bs_Model* model,
    bs_U64 hash);

 /**
  @param model
  @param name
  @return bs_Material*
  */
BSAPI bs_Material*
bs_queryMaterial(
    bs_Model* model,
    const char* name);

 /**
  @param source_id
  @param id
  @return const char*
  */
BSAPI const char*
bs_idName(
    bs_U32 source_id,
    bs_U32 id);

 /**
  @param head
  @param size
  @return void
  */
BSAPI void
bs_resetObject(
    bs_Header* head,
    size_t size);

 /**
  @param source_id
  @param id
  @param size
  @param flexible_size
  @param flexible_count
  @param flags
  @param object_type
  @return bs_Object*
  */
BSAPI bs_Object*
bs_object(
    bs_U32 source_id,
    bs_U32 id,
    size_t size,
    size_t flexible_size,
    int flexible_count,
    bs_U32 flags,
    bs_ObjectType object_type);

 /**
  @return bs_List*
  */
BSAPI bs_List*
bs_packages();

 /**
  @return bs_List*
  */
BSAPI bs_List*
bs_objectSources();

 /**
  @param resource
  @return void
  */
BSAPI void
bs_destroyResource(
    bs_Resource* resource);

 /**
  @param package_id
  @param resource_type
  @param name
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_queryResource(
    int package_id,
    int resource_type,
    const char* name,
    bs_Resource** out);

 /**
  @param name
  @return int
  */
BSAPI int
bs_queryPackage(
    const char* name);

 /**
  @param package_id
  @param flags
  @param type
  @param out
  @param value
  @return bs_Result
  */
BSAPI bs_Result
bs_loadResource(
    int package_id,
    bs_U32 flags,
    bs_ResourceType type,
    bs_Resource** out,
    char* value);

 /**
  @param package_id
  @param flags
  @param type
  @param out
  @param value
  @param value_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadResourceN(
    int package_id,
    bs_U32 flags,
    bs_ResourceType type,
    bs_Resource** out,
    char* value,
    int value_length);

 /**
  @param package_id
  @param flags
  @param type
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadResourceV(
    int package_id,
    bs_U32 flags,
    bs_ResourceType type,
    bs_Resource** out,
    char* format,
    va_list args);

 /**
  @param package_id
  @param flags
  @param type
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadResourceF(
    int package_id,
    bs_U32 flags,
    bs_ResourceType type,
    bs_Resource** out,
    char* format,
     ...);

 /**
  @param out
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_loadPackage(
    int* out,
    char* path);

 /**
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadPackageN(
    int* out,
    char* path,
    int path_length);

 /**
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadPackageV(
    int* out,
    char* format,
    va_list args);

 /**
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadPackageF(
    int* out,
    char* format,
     ...);

 /**
  @param type
  @param count
  @param names
  @return int
  */
BSAPI int
bs_configureSource(
    bs_ObjectType type,
    int count,
    const char** names);

 /**
  @param source_id
  @param id
  @return bool
  */
BSAPI bool
bs_exists(
    bs_U32 source_id,
    bs_U32 id);

 /**
  @param source_id
  @param id
  @return bs_Object*
  */
BSAPI bs_Object*
bs_fetch(
    bs_U32 source_id,
    bs_U32 id);

 /**
  @param source_id
  @param id
  @return bool
  */
BSAPI bool
bs_shouldLoadId(
    bs_U32 source_id,
    bs_U32 id);

 /**
  @param package_id
  @param name
  @param flags
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_shader(
    int package_id,
    const char* name,
    bs_U32 flags,
    bs_Resource** out);

 /**
  @param shader
  @return void
  */
BSAPI void
bs_destroyShader(
    bs_Shader* shader);

 /**
  @param compute_shader
  @param flags
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_computePipeline(
    bs_Shader* compute_shader,
    bs_PipelineFlags flags,
    bs_Pipeline** out);

 /**
  @param pipeline
  @return void
  */
BSAPI void
bs_destroyComputePipeline(
    bs_Pipeline* pipeline);

 /**
  @param type
  @param hash
  @return bs_Pipeline*
  */
BSAPI bs_Pipeline*
bs_queryPipeline(
    bs_PipelineType type,
    bs_U64 hash);

 /**
  @param descriptor
  @return bs_U64
  */
BSAPI bs_U64
bs_pipelineHash(
    bs_PipelineHash* descriptor);

 /**
  @param scope
  @param queue
  @param descriptor
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_pipeline(
    bs_RendererScope* scope,
    bs_Queue* queue,
    bs_PipelineHash* descriptor,
    bs_Pipeline** out);

 /**
  @param pipeline
  @return void
  */
BSAPI void
bs_destroyPipeline(
    bs_Pipeline* pipeline);

 /**
  @param queue
  @param pipeline
  @param offset
  @param size
  @param data
  @return void
  */
BSAPI void
bs_pushConstant(
    bs_Queue* queue,
    bs_Pipeline* pipeline,
    bs_U32 offset,
    bs_U32 size,
    void* data);

 /**
  @param queue
  @param pipeline_hash
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_rayTracingPipeline(
    bs_Queue* queue,
    bs_RayTracePipelineHash* pipeline_hash,
    bs_Pipeline** out);

 /**
  @return void
  */
BSAPI void
bs_loadBindings();

 /**
  @param bind_set
  @param bind_point
  @param descriptors
  @param descriptors_count
  @return bs_Result
  */
BSAPI bs_Result
bs_binding(
    bs_BindSet* bind_set,
    bs_Binding* bind_point,
    bs_Descriptor* descriptors,
    int descriptors_count);

 /**
  @param bind_set_slot
  @param bind_point_slot
  @param image
  @param sampler
  @param layout
  @return bs_Result
  */
BSAPI bs_Result
bs_bindImage(
    bs_U32 bind_set_slot,
    bs_U32 bind_point_slot,
    bs_Image* image,
    bs_Sampler* sampler,
    bs_ImageLayout layout);

 /**
  @param bind_set_slot
  @param bind_point_slot
  @param images
  @param images_count
  @return bs_Result
  */
BSAPI bs_Result
bs_bindImages(
    bs_U32 bind_set_slot,
    bs_U32 bind_point_slot,
    bs_ImageDescriptor* images,
    int images_count);

 /**
  @param bind_set_slot
  @param bind_point_slot
  @param buffer
  @return bs_Result
  */
BSAPI bs_Result
bs_bindBuffer(
    bs_U32 bind_set_slot,
    bs_U32 bind_point_slot,
    bs_Buffer* buffer);

 /**
  @param bind_set_slot
  @param bind_point_slot
  @param buffers
  @param buffers_count
  @return bs_Result
  */
BSAPI bs_Result
bs_bindBuffers(
    bs_U32 bind_set_slot,
    bs_U32 bind_point_slot,
    bs_Buffer** buffers,
    int buffers_count);

 /**
  @param bind_set_slot
  @param bind_point_slot
  @param ray_tracer
  @return bs_Result
  */
BSAPI bs_Result
bs_bindAccelerationStructure(
    bs_U32 bind_set_slot,
    bs_U32 bind_point_slot,
    bs_RayTracer* ray_tracer);

 /**
  @param bind_set_slot
  @param bind_point_slot
  @param ray_tracers
  @param ray_tracers_count
  @return bs_Result
  */
BSAPI bs_Result
bs_bindAccelerationStructures(
    bs_U32 bind_set_slot,
    bs_U32 bind_point_slot,
    bs_RayTracer** ray_tracers,
    int ray_tracers_count);

 /**
  @return void
  */
BSAPI void
bs_pushDescriptors();

 /**
  @return void
  */
BSAPI void
bs_pushBindings();

 /**
  @param id
  @return bs_BindSet*
  */
BSAPI bs_BindSet*
bs_queryBindSet(
    bs_U32 id);

 /**
  @param bind_set
  @param id
  @return bs_Binding*
  */
BSAPI bs_Binding*
bs_queryBinding(
    const bs_BindSet* bind_set,
    bs_U32 id);

 /**
  @param name
  @param base_format
  @return void
  */
BSAPI void
bs_configureAttribute(
    const char* name,
    bs_Format base_format);

 /**
  @param out
  @return bs_Result
  */
BSAPI bs_Result
bs_timeZoneBias(
    int* out);

 /**
  @return bs_DateTime
  */
BSAPI bs_DateTime
bs_dateTime();

 /**
  @param date_time
  @return bs_I64
  */
BSAPI bs_I64
bs_totalSeconds(
    const bs_DateTime* date_time);

 /**
  @param a
  @param b
  @return bool
  */
BSAPI bool
bs_isLaterThan(
    const bs_DateTime* a,
    const bs_DateTime* b);

 /**
  @param context
  @return bs_vec2
  */
BSAPI bs_vec2
bs_windowCursorPosition(
    bs_Context* context);

 /**
  @return bs_ivec2
  */
BSAPI bs_ivec2
bs_windowPosition();

 /**
  @return bs_vec2
  */
BSAPI bs_vec2
bs_screenCursorPosition();

 /**
  @return bool
  */
BSAPI bool
bs_middleClick();

 /**
  @return bool
  */
BSAPI bool
bs_middleClickOnce();

 /**
  @return bool
  */
BSAPI bool
bs_middleClickUpOnce();

 /**
  @return bool
  */
BSAPI bool
bs_leftClick();

 /**
  @return bool
  */
BSAPI bool
bs_rightClick();

 /**
  @return bool
  */
BSAPI bool
bs_rightClickOnce();

 /**
  @return bool
  */
BSAPI bool
bs_leftClickOnce();

 /**
  @return bool
  */
BSAPI bool
bs_rightClickUpOnce();

 /**
  @return bool
  */
BSAPI bool
bs_leftClickUpOnce();

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextMiddleClick(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextMiddleClickOnce(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextMiddleClickUpOnce(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextLeftClick(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextRightClick(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextRightClickOnce(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextLeftClickOnce(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextRightClickUpOnce(
    bs_Context* context);

 /**
  @param context
  @return bool
  */
BSAPI bool
bs_contextLeftClickUpOnce(
    bs_Context* context);

 /**
  @param code
  @return bool
  */
BSAPI bool
bs_keyDown(
    bs_U32 code);

 /**
  @param code
  @return bool
  */
BSAPI bool
bs_keyHeld(
    bs_U32 code);

 /**
  @param code
  @return bool
  */
BSAPI bool
bs_keyDownOnce(
    bs_U32 code);

 /**
  @param code
  @return bool
  */
BSAPI bool
bs_keyUpOnce(
    bs_U32 code);

 /**
  @param c
  @return bool
  */
BSAPI bool
bs_charDown(
    unsigned char c);

 /**
  @param c
  @return bool
  */
BSAPI bool
bs_charDownOnce(
    unsigned char c);

 /**
  @param c
  @return bool
  */
BSAPI bool
bs_charUpOnce(
    unsigned char c);

 /**
  @param context
  @param code
  @return bool
  */
BSAPI bool
bs_contextKeyDown(
    bs_Context* context,
    bs_U32 code);

 /**
  @param context
  @param code
  @return bool
  */
BSAPI bool
bs_contextKeyHeld(
    bs_Context* context,
    bs_U32 code);

 /**
  @param context
  @param code
  @return bool
  */
BSAPI bool
bs_contextKeyDownOnce(
    bs_Context* context,
    bs_U32 code);

 /**
  @param context
  @param code
  @return bool
  */
BSAPI bool
bs_contextKeyUpOnce(
    bs_Context* context,
    bs_U32 code);

 /**
  @param context
  @param c
  @return bool
  */
BSAPI bool
bs_contextCharDown(
    bs_Context* context,
    unsigned char c);

 /**
  @param context
  @param c
  @return bool
  */
BSAPI bool
bs_contextCharDownOnce(
    bs_Context* context,
    unsigned char c);

 /**
  @param context
  @param c
  @return bool
  */
BSAPI bool
bs_contextCharUpOnce(
    bs_Context* context,
    unsigned char c);

 /**
  @return int
  */
BSAPI int
bs_scroll();

 /**
  @param context
  @param width
  @param height
  @return void
  */
BSAPI void
bs_resizeWindow(
    bs_Context* context,
    bs_U32 width,
    bs_U32 height);

 /**
  @param context
  @param x
  @param y
  @return void
  */
BSAPI void
bs_moveWindow(
    bs_Context* context,
    int x,
    int y);

 /**
  @param context
  @param parent
  @param tick
  @param width
  @param height
  @param title
  @param type
  @return bs_Result
  */
BSAPI bs_Result
bs_window(
    bs_Context* context,
    bs_Context* parent,
    bs_ContextTickFunction tick,
    bs_U32 width,
    bs_U32 height,
    const char* title,
    bs_WindowType type);

 /**
  @param context
  @return void
  */
BSAPI void
bs_swapchain(
    bs_Context* context);

 /**
  @param context
  @return void
  */
BSAPI void
bs_showWindow(
    bs_Context* context);

 /**
  @param context
  @return void
  */
BSAPI void
bs_hideWindow(
    bs_Context* context);

 /**
  @param context
  @param device
  @return void
  */
BSAPI void
bs_device(
    bs_Context* context,
    bs_PhysicalDevice* device);

 /**
  @param fixed_tick
  @return void
  */
BSAPI void
bs_tick(
    bs_Callback fixed_tick);

 /**
  @return void
  */
BSAPI void
bs_exit();

 /**
  @param type
  @return void
  */
BSAPI void
bs_setCursor(
    bs_CursorIcon type);

 /**
  @return double
  */
BSAPI double
bs_deltaTime();

 /**
  @return void
  */
BSAPI void
bs_pause();

 /**
  @return void
  */
BSAPI void
bs_advance();

 /**
  @return double
  */
BSAPI double
bs_elapsedTime();

 /**
  @param context
  @return bs_ivec2
  */
BSAPI bs_ivec2
bs_resolution(
    bs_Context* context);

 /**
  @param context
  @param name
  @return void
  */
BSAPI void
bs_titleWindow(
    bs_Context* context,
    char* name);

 /**
  @param context
  @param name
  @param name_length
  @return void
  */
BSAPI void
bs_titleWindowN(
    bs_Context* context,
    char* name,
    int name_length);

 /**
  @param context
  @param format
  @param args
  @return void
  */
BSAPI void
bs_titleWindowV(
    bs_Context* context,
    char* format,
    va_list args);

 /**
  @param context
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_titleWindowF(
    bs_Context* context,
    char* format,
     ...);

 /**
  @return bool
  */
BSAPI bool
bs_inFixedTick();

 /**
  @param fps
  @return void
  */
BSAPI void
bs_setTargetFramerate(
    int fps);

 /**
  @return bs_Timer
  */
BSAPI bs_Timer
bs_timer();

 /**
  @param timer
  @return void
  */
BSAPI void
bs_checkTimer(
    bs_Timer* timer);

 /**
  @param value
  @return void
  */
BSAPI void
bs_copyToClipboard(
    char* value);

 /**
  @param value
  @param value_length
  @return void
  */
BSAPI void
bs_copyToClipboardN(
    char* value,
    int value_length);

 /**
  @param format
  @param args
  @return void
  */
BSAPI void
bs_copyToClipboardV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return void
  */
BSAPI void
bs_copyToClipboardF(
    char* format,
     ...);

 /**
  @param destination
  @param value
  @return bs_String*
  */
BSAPI bs_String*
bs_appendString(
    bs_String* destination,
    char* value);

 /**
  @param destination
  @param value
  @param value_length
  @return bs_String*
  */
BSAPI bs_String*
bs_appendStringN(
    bs_String* destination,
    char* value,
    int value_length);

 /**
  @param destination
  @param format
  @param args
  @return bs_String*
  */
BSAPI bs_String*
bs_appendStringV(
    bs_String* destination,
    char* format,
    va_list args);

 /**
  @param destination
  @param format
  @param ...
  @return bs_String*
  */
BSAPI bs_String*
bs_appendStringF(
    bs_String* destination,
    char* format,
     ...);

 /**
  @param x
  @param param
  @param value
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachFile(
    bs_ForeachDocumentFunction x,
    void* param,
    char* value);

 /**
  @param x
  @param param
  @param value
  @param value_length
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachFileN(
    bs_ForeachDocumentFunction x,
    void* param,
    char* value,
    int value_length);

 /**
  @param x
  @param param
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachFileV(
    bs_ForeachDocumentFunction x,
    void* param,
    char* format,
    va_list args);

 /**
  @param x
  @param param
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachFileF(
    bs_ForeachDocumentFunction x,
    void* param,
    char* format,
     ...);

 /**
  @param x
  @param param
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachDirectory(
    bs_ForeachDocumentFunction x,
    void* param,
    char* path);

 /**
  @param x
  @param param
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachDirectoryN(
    bs_ForeachDocumentFunction x,
    void* param,
    char* path,
    int path_length);

 /**
  @param x
  @param param
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachDirectoryV(
    bs_ForeachDocumentFunction x,
    void* param,
    char* format,
    va_list args);

 /**
  @param x
  @param param
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_foreachDirectoryF(
    bs_ForeachDocumentFunction x,
    void* param,
    char* format,
     ...);

 /**
  @param path
  @return int
  */
BSAPI int
bs_numFiles(
    char* path);

 /**
  @param path
  @param path_length
  @return int
  */
BSAPI int
bs_numFilesN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return int
  */
BSAPI int
bs_numFilesV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return int
  */
BSAPI int
bs_numFilesF(
    char* format,
     ...);

 /**
  @param path
  @return int
  */
BSAPI int
bs_numDirectories(
    char* path);

 /**
  @param path
  @param path_length
  @return int
  */
BSAPI int
bs_numDirectoriesN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return int
  */
BSAPI int
bs_numDirectoriesV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return int
  */
BSAPI int
bs_numDirectoriesF(
    char* format,
     ...);

 /**
  @param mode
  @param out
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_openFile(
    const char* mode,
    bs_File* out,
    char* path);

 /**
  @param mode
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_openFileN(
    const char* mode,
    bs_File* out,
    char* path,
    int path_length);

 /**
  @param mode
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_openFileV(
    const char* mode,
    bs_File* out,
    char* format,
    va_list args);

 /**
  @param mode
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_openFileF(
    const char* mode,
    bs_File* out,
    char* format,
     ...);

 /**
  @param file
  @return void
  */
BSAPI void
bs_closeFile(
    bs_File* file);

 /**
  @param out
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFile(
    bs_String** out,
    char* path);

 /**
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileN(
    bs_String** out,
    char* path,
    int path_length);

 /**
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileV(
    bs_String** out,
    char* format,
    va_list args);

 /**
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileF(
    bs_String** out,
    char* format,
     ...);

 /**
  @param offset
  @param size
  @param out
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileChunk(
    long offset,
    size_t size,
    bs_String** out,
    char* path);

 /**
  @param offset
  @param size
  @param out
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileChunkN(
    long offset,
    size_t size,
    bs_String** out,
    char* path,
    int path_length);

 /**
  @param offset
  @param size
  @param out
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileChunkV(
    long offset,
    size_t size,
    bs_String** out,
    char* format,
    va_list args);

 /**
  @param offset
  @param size
  @param out
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_loadFileChunkF(
    long offset,
    size_t size,
    bs_String** out,
    char* format,
     ...);

 /**
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteFile(
    char* path);

 /**
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteFileN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteFileV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteFileF(
    char* format,
     ...);

 /**
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryContents(
    char* path);

 /**
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryContentsN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryContentsV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryContentsF(
    char* format,
     ...);

 /**
  @param path
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectory(
    char* path);

 /**
  @param path
  @param path_length
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryN(
    char* path,
    int path_length);

 /**
  @param format
  @param args
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryV(
    char* format,
    va_list args);

 /**
  @param format
  @param ...
  @return bs_Result
  */
BSAPI bs_Result
bs_deleteDirectoryF(
    char* format,
     ...);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeJsonType(
    bs_JsonType e);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeShaderType(
    bs_ShaderType e);

 /**
  @param value
  @return bs_ShaderType
  */
BSAPI bs_ShaderType
bs_deserializeShaderType(
    const char* value);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeFormat(
    bs_Format e);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeColorSpace(
    bs_ColorSpace e);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializePresentMode(
    bs_PresentMode e);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeImageLayout(
    bs_ImageLayout e);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeDescriptorType(
    bs_DescriptorType e);

 /**
  @param value
  @return bs_DescriptorType
  */
BSAPI bs_DescriptorType
bs_deserializeDescriptorType(
    const char* value);

 /**
  @param index
  @return bs_DescriptorType
  */
BSAPI bs_DescriptorType
bs_indexDescriptorType(
    int index);

 /**
  @param e
  @return const char*
  */
BSAPI const char*
bs_serializeVkObjectType(
    bs_VkObjectType e);

BSAPI extern bs_Instance* _bs_instance_;
BSAPI extern bs_Bindings _bs_bind_;
BSAPI extern bs_Config _bs_config_;
BSAPI extern bs_Args _bs_args_;
BSAPI extern bs_Features _bs_features_;
BSAPI extern bs_Props _bs_props_;
BSAPI extern int _bs_image_index_;
BSAPI extern bs_List _bs_physical_devices_;
BSAPI extern bs_Callbacks _bs_callbacks_;

#endif
