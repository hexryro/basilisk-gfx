
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

/*
#define VULKAN_H_
#include <GFSDK_Aftermath_GpuCrashDump.h>
#include <GFSDK_Aftermath_GpuCrashDumpDecoding.h>
#include <GFSDK_Aftermath.h>
*/

struct Poser* _poser_ = NULL;

bs_Model* _bsgfx_prefab_model__ = NULL;
bs_String* _bsgfx_variadic = NULL;
int _bsgfx_package_ = -1;
bs_Model* _bsgfx_prefab_model_ = NULL;
bsgfx_Callbacks _bsgfx_callbacks_ = { 0 };
bsgfx_Settings _bsgfx_settings_ = { 0 };
bsgfx_Scene _bsgfx_current_scene_ = { 0 };
bs_mat4* _bsgfx_shader_joints_ = NULL;
bs_U32 _bsgfx_num_shader_joints_ = 0;

bsgfx_Application _bsgfx_app_;

int _bsgfx_subtypes_[BSGFX_SUBTYPE_COUNT] = { 0 };

// TODO: object configuration generation

static int _bsgfx_sources_[BS_OBJECT_TYPE_COUNT] = { -1 };

int bsgfx_fetchSource(bs_ObjectType type) {
    return _bsgfx_sources_[type];
}

BSGFXAPI bsgfx_Scene* _bsgfx_currentScene() {
    return &_bsgfx_current_scene_;
}

BSGFXAPI bsgfx_Application* _bsgfx_app() {
    return &_bsgfx_app_;
}

BSGFXAPI bsgfx_Callbacks* _bsgfx_callbacks() {
    return &_bsgfx_callbacks_;
}

BSGFXAPI bsgfx_Settings* _bsgfx_settings() {
    return &_bsgfx_settings_;
}

BSGFXAPI bs_Model* _bsgfx_prefabModel() {
    return _bsgfx_prefab_model__;
}

BSGFXAPI int _bsgfx_package() {
    return _bsgfx_package_;
}

BSGFXAPI struct Poser* _poser() {
    return _poser_;
}

static void _bsgfx_configure() {
  //  BS_CONFIGURE_SOURCE(_bsgfx_sources_, BS_OBJECT_CONTEXT, BSGFX_CONTEXTS_COUNT, BSGFX_CONTEXT_IDS);
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

void _bsgfx_tickMaterials();
static void _bsgfx_tick() {
    _poser_->menu_blocked = false;

    static int timer;
    const double time_scale = 0.0;
    
    _poser_->time += time_scale * bs_deltaTime();
    _poser_->second = ((int)_poser_->time) % 86400;
    _poser_->hour = _poser_->second / 3600;
    _poser_->minute = (_poser_->second % 3600) / 60;

    float day_fraction = (float)_poser_->time / 86400.0f;
    float angle = day_fraction * 2.0f * BS_PI;

    _poser_->sun_direction = BS_V3(-sinf(angle), cosf(angle), -0.48);
    bs_v3Normalize(&_poser_->sun_direction, &_poser_->sun_direction);

    //bssteam_pollActions();
    //bssteam_tickSteam();
    //bsgfx_instanceItems();

    bs_vec2 resolution = { .x = (float)bs_resolution().x, .y = (float)bs_resolution().y };

    bs_mat4 screen_camera_proj;
    bs_mat4 screen_camera_view;

    bs_orthographic(0, resolution.x, 0, resolution.y, -1000, 1000, &screen_camera_proj);
    bs_lookAt(&(bs_vec3) { 0 }, &(bs_vec3) { 0.0, 0.0, -1.0 }, &(bs_vec3) { 0.0, 1.0, 0.0 }, &screen_camera_view);
    bs_m4Mul(&screen_camera_proj, &screen_camera_view, &_poser_->screen_camera.result);

    _bsgfx_instancePrimitives();
    if (_bsgfx_prefab_model__)
        _bsgfx_instancePrefabs();
    _bsgfx_instanceTiles();


    //if (bs_charDown(' '))
    //    bs_advance();
    //bsgfx_instanceEntities();

//    if (_bsgfx_scene != BSGFX_SCENE_MENU)
//        _bsgfx_instanceMinimap();

    //if (_bsgfx_procs_.bsmod_onGfxRender)
    //    _bsgfx_procs_.bsmod_onGfxRender();
    if (_bsgfx_callbacks_.tick)
        _bsgfx_callbacks_.tick();

    _bsgfx_tickInstances();

    if (_bsgfx_callbacks_.pipeline)
        _bsgfx_callbacks_.pipeline();

    _bsgfx_resetInstances();

    //_bsgfx_pipeline();
    _bsgfx_tickMaterials();
}

static void _bsgfx_fixedTick() {
 //   _bsgfx_tickItems();

    if (_bsgfx_callbacks_.fixedTick)
        _bsgfx_callbacks_.fixedTick();
}

/*
static void _bsgfx_onGpuCrash(const void* crash_dump, const bs_U32 crash_dump_size, void* params) {
    bs_saveFile("aftermath.nv-gpudmp", crash_dump, crash_dump_size);
}

static void _bsgfx_onShaderDebugInfo(const void* info, const uint32_t size, void* params) {
    GFSDK_Aftermath_ShaderDebugInfoIdentifier identifier = { 0 };
    GFSDK_Aftermath_Result result = GFSDK_Aftermath_GetShaderDebugInfoIdentifier(GFSDK_Aftermath_Version_API, info, size, &identifier);

    if (result == GFSDK_Aftermath_Result_Success) {
        bs_saveFileF(info, size, "%016" PRIx64 ".nvdbg", identifier.id[0]);
    }
}

void _bsgfx_onGpuCrashDescription(PFN_GFSDK_Aftermath_AddGpuCrashDumpDescription add_description, void* params) {
   // add_description(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_ApplicationName, "Hello Nsight Aftermath");
}

static inline const char* bsgfx_GFSDK_resultName(GFSDK_Aftermath_Result result) {
    switch (result) {
    case GFSDK_Aftermath_Result_NotAvailable: return "Not available";
    case GFSDK_Aftermath_Result_Fail: return "Fail";
    case GFSDK_Aftermath_Result_FAIL_VersionMismatch: return "Version mismatch";
    case GFSDK_Aftermath_Result_FAIL_NotInitialized: return "Not initialized";
    case GFSDK_Aftermath_Result_FAIL_InvalidAdapter: return "Invalid adapter";
    case GFSDK_Aftermath_Result_FAIL_InvalidParameter: return "Invalid parameter";
    case GFSDK_Aftermath_Result_FAIL_Unknown: "Unknown";
    case GFSDK_Aftermath_Result_FAIL_ApiError: return "API error";
    case GFSDK_Aftermath_Result_FAIL_NvApiIncompatible: return "NVIDIA API incompatible";
    case GFSDK_Aftermath_Result_FAIL_GettingContextDataWithNewCommandList: return "Getting context data with new command list";
    case GFSDK_Aftermath_Result_FAIL_AlreadyInitialized: return "Already initialized";
    case GFSDK_Aftermath_Result_FAIL_D3DDebugLayerNotCompatible: return "D3D debug layer not compatible";
    case GFSDK_Aftermath_Result_FAIL_DriverInitFailed: return "Driver initializaion failed";
    case GFSDK_Aftermath_Result_FAIL_DriverVersionNotSupported: return "Driver version not supported";
    case GFSDK_Aftermath_Result_FAIL_OutOfMemory: return "Out of memory";
    case GFSDK_Aftermath_Result_FAIL_GetDataOnBundle: return "Get data on bundle";
    case GFSDK_Aftermath_Result_FAIL_GetDataOnDeferredContext: return "Get data on deferred context";
    case GFSDK_Aftermath_Result_FAIL_FeatureNotEnabled: return "Feature not enabled";
    case GFSDK_Aftermath_Result_FAIL_NoResourcesRegistered: return "No resources registered";
    case GFSDK_Aftermath_Result_FAIL_ThisResourceNeverRegistered: return "This resource never registered";
    case GFSDK_Aftermath_Result_FAIL_NotSupportedInUWP: return "Not supported in UWP";
    case GFSDK_Aftermath_Result_FAIL_D3dDllNotSupported: return "D3D DLL not supported";
    case GFSDK_Aftermath_Result_FAIL_D3dDllInterceptionNotSupported: return "D3D DLL interception not supported";
    case GFSDK_Aftermath_Result_FAIL_Disabled: return "Disabled";
    case GFSDK_Aftermath_Result_FAIL_NotSupportedOnContext: return "Not supported on context";
    }

    return "Invalid GFSDK error";
}


void _bsgfx_logGFSDK(GFSDK_Aftermath_Result result) {
    if (result != GFSDK_Aftermath_Result_Success)
        bs_infoF("GFSDK Aftermath error:\n%s\n", bsgfx_GFSDK_resultName(result));
}

void _bsgfx_checkGFSDK(GFSDK_Aftermath_Result result) {
    if (result != GFSDK_Aftermath_Result_Success) {
        bs_throwBasilisk(BSX_GENERAL);
    }
}
*/

BSGFXAPI void _bsgfx_setCamera(const bs_mat4* proj, const bs_mat4* view) {
    _poser_->camera.proj = *proj;
    _poser_->camera.view = *view;
    bs_m4Mul(proj, view, &_poser_->camera.result);
}

BSGFXAPI void _bsgfx_ini(const char* name, bs_U32 width, bs_U32 height, int argc, char* argv[]) {
    for (int i = 0; i < BSGFX_SUBTYPE_COUNT; i++)
        _bsgfx_subtypes_[i] = -1;

    _bsgfx_app_.name = name;

    _poser_ = bs_malloc(sizeof(struct Poser));
    *_poser_ = (struct Poser){
        .time = 10.8 * 60 * 60,
        .menu_open = true, // main menu
        .sweep_collisions = bs_list(sizeof(bsgfx_SweepCollision), 64),
    };

    bs_parseArgs(argc, argv);

#ifdef _DEBUG
    const char* args[] = { "--cmd-log", "--color-log", "--use-lisk", "--use-validation-layers", "--track-changes"};
    bs_parseArgs(sizeof(args) / sizeof(char*), args);
#endif
    
    _bsgfx_configure();
    bs_ini();

    bs_Object* context_object = BS_CONTEXT(-1, 0, 0);
    bs_window(context_object->context, width, height, name);
    bs_device(context_object->context, NULL);

    /*
    GFSDK_Aftermath_Result result = GFSDK_Aftermath_EnableGpuCrashDumps(
        GFSDK_Aftermath_Version_API,
        GFSDK_Aftermath_GpuCrashDumpWatchedApiFlags_Vulkan,
        GFSDK_Aftermath_GpuCrashDumpFeatureFlags_Default,
        _bsgfx_onGpuCrash,
        _bsgfx_onShaderDebugInfo,
        _bsgfx_onGpuCrashDescription,
        NULL,
        NULL);
    */

/*
    bssteam_iniSteam();
    bssteam_iniSteamInput();
#ifdef _DEBUG
    bssteam_overrideManifestFile("resources/iga.vdf");
#endif
*/


   // bs_pause();

    bs_loadPackage(&_bsgfx_package_, BSGFX_CONTENT_PATH);
    _bsgfx_iniInstances();

    bs_Object* queue_obj = BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES, 0);
    bs_Queue* queue = queue_obj->queue;
    bs_queue(queue_obj, BS_QUEUE_GRAPHICS_BIT | BS_QUEUE_SINGLE_TIMES_BIT);

    bs_queue(BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_GRAPHICS, BS_OBJECT_HAS_SWAPS_BIT), BS_QUEUE_GRAPHICS_BIT);
    bs_queue(BS_QUEUE(BSGFX_QUEUES, BSGFX_QUEUE_COMPUTE, BS_OBJECT_HAS_SWAPS_BIT), BS_QUEUE_COMPUTE_BIT);

    bs_sampler(BS_SAMPLER(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST, 0), BS_FILTER_NEAREST, 0);
    bs_sampler(BS_SAMPLER(BSGFX_SAMPLERS, BSGFX_SAMPLER_LINEAR, 0), BS_FILTER_LINEAR, 0);

    if (_bsgfx_callbacks_.ini)
        _bsgfx_callbacks_.ini();

    bs_iniAudio();

    if (_bsgfx_callbacks_.lateIni)
        _bsgfx_callbacks_.lateIni();
    printf("exiting\n");
    exit(0);

    bs_tick(_bsgfx_tick, _bsgfx_fixedTick);// TODO

    if (bs_exists(BSGFX_RAY_TRACERS, BSGFX_RAY_TRACER_MAIN))
        bs_destroyRayTracer(bs_fetch(BSGFX_RAY_TRACERS, BSGFX_RAY_TRACER_MAIN)->ray_tracer);

    bs_free(_poser_);
    // todo destroy dll
}