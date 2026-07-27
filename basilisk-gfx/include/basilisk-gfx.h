
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
    X(BSGFX_BUFFER_INSTANCE_METADATA)                                \
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
    X(BSGFX_QUEUES_COUNT)

#define BSGFX_RAY_TRACER_IDS(X)                                      \
    X(BSGFX_RAY_TRACER_MAIN)                                         \
    X(BSGFX_RAY_TRACERS_COUNT)

#define BSGFX_ATLAS_IDS(X)                                           \
    X(BSGFX_ATLAS_ANY)                                               \
    X(BSGFX_ATLASES_COUNT)

#define BSGFX_FONT_IDS(X)                                            \
    X(BSGFX_FONTS_COUNT)

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
    BSGFX_ATLAS_ANY,                                                 \
    BSGFX_BATCH_MESH_TYPE_VOLUME_COMPUTED,                           \
    /* images*/                                                      \
    BSGFX_IMAGE_64,                                                  \
    BSGFX_IMAGE_256,                                                 \
    BSGFX_IMAGE_512,                                                 \
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


#endif