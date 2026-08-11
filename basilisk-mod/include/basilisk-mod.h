
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

#ifndef BASILISK_MOD_H
#define BASILISK_MOD_H

#include <basilisk-mod.gen.h>

#define BSMOD_VALIDATE(condition, ret, format, ...)                  \
    if (!(condition)) {                                              \
        bs_warnF(BS_PRINT_COLOR("[MOD] [VAL]", BS_PRINT_RED) " %s: %s\n" __VA_OPT__(format) "\n", __func__, #condition __VA_OPT__(,) __VA_ARGS__); \
        return ret;                                                  \
    }

#define BSMOD_IMAGE_IDS(X)									\
    X(BSMOD_IMAGE_DEPTH)                                    \
    X(BSMOD_IMAGE_DEPTH_3D)                                 \
    X(BSMOD_IMAGE_COLOR)                                    \
    X(BSMOD_IMAGES_COUNT)

#define BSMOD_SAMPLER_IDS(X)                                \
	X(BSMOD_SAMPLERS_COUNT)

#define BSMOD_BUFFER_IDS(X)                                 \
	X(BSMOD_BUFFERS_COUNT)

#define BSMOD_BATCH_IDS(X)									\
    X(BSMOD_BATCH_TILE)                                     \
    X(BSMOD_BATCH_MSDF_GLYPHS)                              \
    X(BSMOD_BATCHES_COUNT)

#define BSMOD_RENDERER_IDS(X)								\
    X(BSMOD_RENDERER)                                       \
    X(BSMOD_RENDERER_3D)                                    \
    X(BSMOD_RENDERER_MSDF)                                  \
    X(BSMOD_RENDERERS_COUNT)

#define BSMOD_QUEUE_IDS(X)									\
    X(BSMOD_QUEUE_GRAPHICS)                                 \
    X(BSMOD_QUEUE_GRAPHICS_RASTERIZATION)                   \
    X(BSMOD_QUEUE_MSDF)                                     \
    X(BSMOD_QUEUES_COUNT)

#define BSMOD_RAY_TRACER_IDS(X) \
	X(BSMOD_RAY_TRACERS_COUNT)

#define BSMOD_ATLAS_IDS(X)                                  \
    X(BSMOD_ATLAS_UI)                                       \
    X(BSMOD_ATLAS_MATERIAL_ICONS)                           \
    X(BSMOD_ATLAS_PRIMITIVE_ICONS)                          \
    X(BSMOD_ATLAS_PREFAB_ICONS)                             \
    X(BSMOD_ATLASES_COUNT)

#define BSMOD_FONT_IDS(X)                                   \
	X(BSMOD_FONTS_COUNT)

BS_GENERATE_ENUM(BSMOD_IMAGE_IDS);
BS_GENERATE_ENUM(BSMOD_SAMPLER_IDS);
BS_GENERATE_ENUM(BSMOD_BUFFER_IDS);
BS_GENERATE_ENUM(BSMOD_BATCH_IDS);
BS_GENERATE_ENUM(BSMOD_RENDERER_IDS);
BS_GENERATE_ENUM(BSMOD_QUEUE_IDS);
BS_GENERATE_ENUM(BSMOD_RAY_TRACER_IDS);
BS_GENERATE_ENUM(BSMOD_ATLAS_IDS);
BS_GENERATE_ENUM(BSMOD_FONT_IDS);

#define BSMOD_CONTEXTS bsmod_fetchSource(BS_OBJECT_CONTEXT)
#define BSMOD_IMAGES bsmod_fetchSource(BS_OBJECT_IMAGE)
#define BSMOD_SAMPLERS bsmod_fetchSource(BS_OBJECT_SAMPLER)
#define BSMOD_BUFFERS bsmod_fetchSource(BS_OBJECT_BUFFER)
#define BSMOD_BATCHES bsmod_fetchSource(BS_OBJECT_BATCH)
#define BSMOD_RENDERERS bsmod_fetchSource(BS_OBJECT_RENDERER)
#define BSMOD_QUEUES bsmod_fetchSource(BS_OBJECT_QUEUE)
#define BSMOD_RAY_TRACERS bsmod_fetchSource(BS_OBJECT_RAY_TRACER)
#define BSMOD_ATLASES bsmod_fetchSource(BS_OBJECT_ATLAS)

BSMODAPI int
bsmod_fetchSource(
    bs_ObjectType type);

typedef enum {
    BSMOD_SUBTYPE_MATERIAL_ICON,
    BSMOD_SUBTYPE_PRIMITIVE_ICON,
    BSMOD_SUBTYPE_PREFAB_ICON,
    BSMOD_SUBTYPE_TILE_ICON,
    BSMOD_SUBTYPE_SPHERE_HIGH_QUALITY,
    BSMOD_SUBTYPE_BILLBOARD,
    BSMOD_SUBTYPE_COUNT,
} bsmod_Subtypes;

BSMODAPI extern int _bsmod_subtypes_[BSMOD_SUBTYPE_COUNT];

#endif
