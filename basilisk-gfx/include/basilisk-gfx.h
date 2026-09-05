
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

#ifndef BASILISK_GFX_H
#define BASILISK_GFX_H

#include <basilisk-gfx.gen.h>
#include <../bsgfx_contracts.h>

/*
#define BSGFX_FOREACH_PROC(X)                                        \
    X(PFN_void, bsmod_onIni)                                         \
    X(PFN_void, bsmod_onLateIni)                                     \
    X(PFN_void, bsmod_onLoad)                                        \
    X(PFN_void, bsmod_copyHoveringDataToBuffer)                      \
    X(PFN_bsmod_onCreateSubtypes, bsmod_onCreateQuadSubtypes)        \
    X(PFN_bsmod_onQueue, bsmod_onQueue)                              \
    X(PFN_void, bsmod_onGfxRender)                                   \
    X(PFN_bsmod_isSelected, bsmod_isSelected)                        \
    X(PFN_bsmod_onMap, bsmod_onMap)                                  \
    X(PFN_void, bsmod_onTrack)

typedef struct {
    BSGFX_FOREACH_PROC(BSGFX_STRUCT_GEN)
} bsgfx_Procedures;
BSGFXAPI extern bsgfx_Procedures _bsgfx_procs_;
*/
#define BSGFX_EMPTY_LIST(X)

#define BSGFX_CONTEXT_IDS(X)                                           \
    X(BSGFX_CONTEXT_MAIN)                                            \
    X(BSGFX_CONTEXTS_COUNT)

#define BSGFX_IMAGE_IDS(X)                                           \
    X(BSGFX_IMAGE_TILE)                                              \
    X(BSGFX_IMAGE_ANY)                                               \
    X(BSGFX_IMAGE_64)                                                \
    X(BSGFX_IMAGE_256)                                               \
    X(BSGFX_IMAGE_512)                                               \
    X(BSGFX_IMAGE_RAYTRACE_TEST)                                     \
    X(BSGFX_IMAGE_LEVEL_THUMBNAIL)                                   \
    X(BSGFX_IMAGES_COUNT)

#define BSGFX_SAMPLER_IDS(X)                                         \
    X(BSGFX_SAMPLER_NEAREST)                                         \
    X(BSGFX_SAMPLER_LINEAR)                                          \
    X(BSGFX_SAMPLERS_COUNT)

#define BSGFX_BUFFER_IDS(X)                                          \
    X(BSGFX_BUFFER_JOINTS)                                           \
    X(BSGFX_BUFFER_LO_RES_CURSOR_READS)                              \
    X(BSGFX_BUFFER_LO_RES_SCREENSHOT)                                \
    X(BSGFX_BUFFER_MATERIALS)                                        \
    X(BSGFX_BUFFERS_COUNT)

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
    X(BSGFX_BATCH_PRIMITIVE_TILES)                                   \
    X(BSGFX_BATCHES_COUNT)

#define BSGFX_RENDERER_IDS(X)                                        \
    X(BSGFX_RENDERER_LO_RES)                                         \
    X(BSGFX_RENDERER_HI_RES)                                         \
    X(BSGFX_RENDERERS_COUNT)

#define BSGFX_QUEUE_IDS(X)                                           \
    X(BSGFX_QUEUE_GRAPHICS)                                          \
    X(BSGFX_QUEUE_COMPUTE)                                           \
    X(BSGFX_QUEUE_SINGLE_TIMES)                                      \
    X(BSGFX_QUEUES_COUNT)

#define BSGFX_RAY_TRACER_IDS(X)                                      \
    X(BSGFX_RAY_TRACER_MAIN)                                         \
    X(BSGFX_RAY_TRACERS_COUNT)

#define BSGFX_ATLAS_IDS(X)                                           \
    X(BSGFX_ATLAS_ANY)                                               \
    X(BSGFX_ATLASES_COUNT)

#define BSGFX_FONT_IDS(X)                                            \
    X(BSGFX_FONTS_COUNT)

BS_GENERATE_ENUM(BSGFX_CONTEXT_IDS);
BS_GENERATE_ENUM(BSGFX_IMAGE_IDS);
BS_GENERATE_ENUM(BSGFX_SAMPLER_IDS);
BS_GENERATE_ENUM(BSGFX_BUFFER_IDS);
BS_GENERATE_ENUM(BSGFX_BATCH_IDS);
BS_GENERATE_ENUM(BSGFX_RENDERER_IDS);
BS_GENERATE_ENUM(BSGFX_QUEUE_IDS);
BS_GENERATE_ENUM(BSGFX_RAY_TRACER_IDS);
BS_GENERATE_ENUM(BSGFX_ATLAS_IDS);
BS_GENERATE_ENUM(BSGFX_FONT_IDS);

#define BSGFX_CONTEXTS bsgfx_fetchSource(BS_OBJECT_CONTEXT)
#define BSGFX_IMAGES bsgfx_fetchSource(BS_OBJECT_IMAGE)
#define BSGFX_SAMPLERS bsgfx_fetchSource(BS_OBJECT_SAMPLER)
#define BSGFX_BUFFERS bsgfx_fetchSource(BS_OBJECT_BUFFER)
#define BSGFX_BATCHES bsgfx_fetchSource(BS_OBJECT_BATCH)
#define BSGFX_RENDERERS bsgfx_fetchSource(BS_OBJECT_RENDERER)
#define BSGFX_QUEUES bsgfx_fetchSource(BS_OBJECT_QUEUE)
#define BSGFX_RAY_TRACERS bsgfx_fetchSource(BS_OBJECT_RAY_TRACER)
#define BSGFX_ATLASES bsgfx_fetchSource(BS_OBJECT_ATLAS)
#define BSGFX_FONTS bsgfx_fetchSource(BS_OBJECT_FONT)

BSGFXAPI int 
bsgfx_fetchSource(
    bs_ObjectType type);

enum {
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
    BSGFX_SUBTYPE_FONT,

    BSGFX_SUBTYPE_COUNT,
};

enum {
    BSGFX_INSTANCE_TYPE_2_BONE,
    BSGFX_INSTANCE_TYPE_2_MESH,
    BSGFX_INSTANCE_TYPE_2_LINE,
    BSGFX_INSTANCE_TYPE_2_POINT,
    BSGFX_INSTANCE_TYPE_2_QUAD,
    BSGFX_INSTANCE_TYPE_2_MESH_STATIC,
    BSMOD_INSTANCE_TYPE_2_TRACKER_QUAD,

    BSGFX_INSTANCE_TYPE_2_COUNT,
};

BSGFXAPI extern bsgfx_InstanceSubtype* _bsgfx_subtypes_[BSGFX_SUBTYPE_COUNT];
BSGFXAPI extern bsgfx_InstanceType* _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_COUNT];

#endif