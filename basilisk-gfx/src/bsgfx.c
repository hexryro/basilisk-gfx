
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

#include <bsgfx_internal.h>

#include <windows.h>
#include <complex.h>
#include <math.h>
#include <assert.h>
#include <inttypes.h>

bs_Model* _bsgfx_prefab_model__ = NULL;
bs_String* _bsgfx_variadic = NULL;
int _bsgfx_package_ = -1;
bs_Model* _bsgfx_prefab_model_ = NULL;
bsgfx_Callbacks _bsgfx_callbacks_ = { 0 };
bsgfx_Settings _bsgfx_settings_ = { 0 };
bsgfx_Scene _bsgfx_current_scene_ = { 0 };
bs_mat4* _bsgfx_shader_joints_ = NULL;
bs_U32 _bsgfx_num_shader_joints_ = 0;

bsgfx_Application _bsgfx_app_ = {
    .sweep_collisions = {.unit_size = sizeof(bsgfx_SweepCollision), .increment = 64 }
};

bsgfx_InstanceSubtype* _bsgfx_subtypes_[BSGFX_SUBTYPE_COUNT] = { 0 };
bsgfx_InstanceType* _bsgfx_instance_types_[BSGFX_INSTANCE_TYPE_2_COUNT] = { 0 };

static int _bsgfx_sources_[BS_OBJECT_TYPE_COUNT] = { -1 };
int bsgfx_fetchSource(bs_ObjectType type) { return _bsgfx_sources_[type]; }

BSGFXAPI bsgfx_InstanceType** _bsgfx_instanceTypes() { return _bsgfx_instance_types_; }
BSGFXAPI bsgfx_InstanceSubtype** _bsgfx_subtypes() { return _bsgfx_subtypes_; }
BSGFXAPI bsgfx_Scene* _bsgfx_currentScene() { return &_bsgfx_current_scene_; }
BSGFXAPI bsgfx_Application* _bsgfx_app() { return &_bsgfx_app_; }
BSGFXAPI bsgfx_Callbacks* _bsgfx_callbacks() { return &_bsgfx_callbacks_; }
BSGFXAPI bsgfx_Settings* _bsgfx_settings() { return &_bsgfx_settings_; }
BSGFXAPI bs_Model* _bsgfx_prefabModel() { return _bsgfx_prefab_model__; }

BSGFXAPI int _bsgfx_package() {
    return _bsgfx_package_;
}

static void _bsgfx_configure() {
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_CONTEXT, BSGFX_CONTEXTS_COUNT, BSGFX_CONTEXT_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_IMAGE, BSGFX_IMAGES_COUNT, BSGFX_IMAGE_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_SAMPLER, BSGFX_SAMPLERS_COUNT, BSGFX_SAMPLER_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_BUFFER, BSGFX_BUFFERS_COUNT, BSGFX_BUFFER_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_QUEUE, BSGFX_QUEUES_COUNT, BSGFX_QUEUE_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_BATCH, BSGFX_BATCHES_COUNT, BSGFX_BATCH_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_RENDERER, BSGFX_RENDERERS_COUNT, BSGFX_RENDERER_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_RAY_TRACER, BSGFX_RAY_TRACERS_COUNT, BSGFX_RAY_TRACER_IDS);
    BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_ATLAS, BSGFX_ATLASES_COUNT, BSGFX_ATLAS_IDS);

    bs_configureAttribute("bsgfx_VolumeId", BS_FORMAT_R32_SFLOAT);
    bs_configureAttribute("bsgfx_Index", BS_FORMAT_R32_UINT);

   // static const char* strs[] = { BSGFX_FOREACH_ID(BSGFX_STRING_GEN) };
   // for (int i = 0; i < _BSGFX_NUM_OBJECTS; i++)
   //     bs_nameId(i, strs[i]);
}

static void _bsgfx_fixedTick() {
    if (_bsgfx_callbacks_.fixedTick)
        _bsgfx_callbacks_.fixedTick();
}


int to_reset[] = {
    BSGFX_INSTANCE_TYPE_2_BONE,
    BSGFX_INSTANCE_TYPE_2_MESH,
    BSGFX_INSTANCE_TYPE_2_LINE,
    BSGFX_INSTANCE_TYPE_2_POINT,
    BSGFX_INSTANCE_TYPE_2_QUAD,
    BSGFX_INSTANCE_TYPE_2_MESH_STATIC,
};

void _bsgfx_computeContextCamera() {
    bs_Context* ctx = bs_scope()->context;
    bs_vec2 resolution = { .x = (float)bs_resolution(ctx).x, .y = (float)bs_resolution(ctx).y };

    bs_mat4 screen_camera_proj;
    bs_mat4 screen_camera_view;

    bs_orthographic(0, resolution.x, 0, resolution.y, -1000, 1000, &screen_camera_proj);
    bs_lookAt(&(bs_vec3) { 0 }, & (bs_vec3) { 0.0, 0.0, -1.0 }, & (bs_vec3) { 0.0, 1.0, 0.0 }, & screen_camera_view);
    bs_m4Mul(&screen_camera_proj, &screen_camera_view, &_bsgfx_app_.screen_camera.result);
}

void _bsgfx_tickInstanceTypes() {
    int to_reset_count = sizeof(to_reset) / sizeof(*to_reset);

    for (int i = 0; i < to_reset_count; i++)
        bsgfx_tickInstanceType(_bsgfx_instance_types_[to_reset[i]]);

}

void _bsgfx_resetInstanceTypes() {
    int to_reset_count = sizeof(to_reset) / sizeof(*to_reset);

    for (int i = 0; i < to_reset_count; i++)
        bsgfx_resetInstanceType(_bsgfx_instance_types_[to_reset[i]]);
}

BSGFXAPI void _bsgfx_setCamera(const bs_mat4* proj, const bs_mat4* view) {
    _bsgfx_app_.camera.proj = *proj;
    _bsgfx_app_.camera.view = *view;
    bs_m4Mul(proj, view, &_bsgfx_app_.camera.result);
}

BSGFXAPI void _bsgfx_ini(const char* name, bs_U32 width, bs_U32 height, bs_U32 window_flags, int argc, char* argv[]) {
    for (int i = 0; i < BSGFX_SUBTYPE_COUNT; i++)
        _bsgfx_subtypes_[i] = -1;

    _bsgfx_app_.name = name;

    bs_parseArgs(argc, argv);

#ifdef _DEBUG
    const char* args[] = { "--use-validation-layers", "--track-changes"};
    bs_parseArgs(sizeof(args) / sizeof(char*), args);
#endif
    
    _bsgfx_configure();
    bs_ini();

    bs_Object* context_object = BS_CONTEXT(BSGFX_CONTEXTS, BSGFX_CONTEXT_MAIN, 0);
    bs_window(context_object->context, NULL, _bsgfx_callbacks_.tick, width, height, name, window_flags);
    bs_showWindow(context_object->context);
    bs_device(context_object->context, NULL);
    bs_swapchain(context_object->context);
    bs_iniAudio();

    bs_loadPackage(&_bsgfx_package_, BSGFX_CONTENT_PATH);

    bs_Object* queue_obj = BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES, 0);
    bs_Queue* queue = queue_obj->queue;
    bs_queue(queue_obj, 0, BS_QUEUE_GRAPHICS_BIT | BS_QUEUE_SINGLE_TIMES_BIT);

    bs_queue(BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS, BS_OBJECT_HAS_SWAPS_BIT), 0, BS_QUEUE_GRAPHICS_BIT);
    bs_queue(BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_COMPUTE, BS_OBJECT_HAS_SWAPS_BIT), 0, BS_QUEUE_COMPUTE_BIT);

    bs_sampler(BS_SAMPLER(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST, 0), BS_FILTER_NEAREST, 0);
    bs_sampler(BS_SAMPLER(BSGFX_SAMPLERS, BSGFX_SAMPLER_LINEAR, 0), BS_FILTER_LINEAR, 0);
}

BSGFXAPI void _bsgfx_tick() {
    bs_Object* context_object = bs_fetch(BSGFX_CONTEXTS, BSGFX_CONTEXT_MAIN);
    bs_tick(_bsgfx_fixedTick);
}