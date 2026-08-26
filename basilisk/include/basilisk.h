
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

#ifndef BASILISK_OBJECTS_H
#define BASILISK_OBJECTS_H

typedef struct {
    int sources[BS_OBJECT_TYPE_COUNT];
    int package_id;
    bs_U32 main_thread_id;
    bs_Context* context;
} Basilisk;

extern Basilisk basilisk;

#define BASILISK_TITLE_BAR_HEIGHT 32

#define BASILISK_IMAGE_IDS(X)								    \
    X(BASILISK_IMAGE_MAIN_OUTPUT_DEPTH)                         \
    X(BASILISK_IMAGE_MAIN_OUTPUT_COLOR)                         \
    X(BASILISK_IMAGES_COUNT)

#define BASILISK_SAMPLER_IDS(X)                                 \
	X(BASILISK_SAMPLERS_COUNT)

#define BASILISK_BUFFER_IDS(X)                                  \
	X(BASILISK_BUFFERS_COUNT)

#define BASILISK_BATCH_IDS(X)									\
    X(BASILISK_BATCHES_COUNT)

#define BASILISK_RENDERER_IDS(X)							    \
    X(BASILISK_RENDERER_MAIN)                                   \
    X(BASILISK_RENDERERS_COUNT)

#define BASILISK_QUEUE_IDS(X)									\
    X(BASILISK_QUEUES_COUNT)

#define BASILISK_RAY_TRACER_IDS(X)                              \
	X(BASILISK_RAY_TRACERS_COUNT)

#define BASILISK_ATLAS_IDS(X)                                   \
    X(BASILISK_ATLASES_COUNT)

#define BASILISK_FONT_IDS(X)                                    \
	X(BASILISK_FONTS_COUNT)

BS_GENERATE_ENUM(BASILISK_IMAGE_IDS);
BS_GENERATE_ENUM(BASILISK_SAMPLER_IDS);
BS_GENERATE_ENUM(BASILISK_BUFFER_IDS);
BS_GENERATE_ENUM(BASILISK_BATCH_IDS);
BS_GENERATE_ENUM(BASILISK_RENDERER_IDS);
BS_GENERATE_ENUM(BASILISK_QUEUE_IDS);
BS_GENERATE_ENUM(BASILISK_RAY_TRACER_IDS);
BS_GENERATE_ENUM(BASILISK_ATLAS_IDS);
BS_GENERATE_ENUM(BASILISK_FONT_IDS);

#define BASILISK_CONTEXTS basilisk.sources[BS_OBJECT_CONTEXT]
#define BASILISK_IMAGES basilisk.sources[BS_OBJECT_IMAGE]
#define BASILISK_SAMPLERS basilisk.sources[BS_OBJECT_SAMPLER]
#define BASILISK_BUFFERS basilisk.sources[BS_OBJECT_BUFFER]
#define BASILISK_BATCHES basilisk.sources[BS_OBJECT_BATCH]
#define BASILISK_RENDERERS basilisk.sources[BS_OBJECT_RENDERER]
#define BASILISK_QUEUES basilisk.sources[BS_OBJECT_QUEUE]
#define BASILISK_RAY_TRACERS basilisk.sources[BS_OBJECT_RAY_TRACER]
#define BASILISK_ATLASES basilisk.sources[BS_OBJECT_ATLAS]
#define BASILISK_FONTS basilisk.sources[BS_OBJECT_FONT]

void basilisk_createRenderers();

void basilisk_instantiateTitleBarUI();

#endif