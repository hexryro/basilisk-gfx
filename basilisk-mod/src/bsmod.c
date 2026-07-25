
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

#include <bsmod_internal.h>
#include <bsmod_cache.h>
#include <stdio.h>

Bsmod _bsmod_ = {
    .bsgfx_package = -1,
    .package = -1,
    .history = BS_I64_MAX,
    .hovering = {
        .prefab = -1,
        .primitive = -1,
    },
    .selected_type = -1,
    .axis = -1,
    .dragging_id = -1,
    .dragging_subtype = -1,
    .selected_ids = {.unit_size = sizeof(int), .increment = 32 },
    .selected_tiles = {.unit_size = sizeof(int), .increment = 32 },
};

bs_Json _bsmod_config_ = { 0 };

int _bsmod_images_ = -1, _bsmod_samplers_ = -1, _bsmod_buffers_ = -1,
    _bsmod_batches_ = -1, _bsmod_renderers_ = -1, _bsmod_ray_tracers_ = -1,
    _bsmod_queues_ = -1, _bsmod_atlases_ = -1, _bsmod_fonts_ = -1;

volatile long _bsmod_has_performed_tracked_changes_ = 1;

int _bsmod_subtypes_[BSMOD_SUBTYPE_COUNT] = { 0 };

bsmod_Callbacks _bsmod_callbacks_ = { 0 };

BSMODAPI bsmod_Callbacks* _bsmod_callbacks() {
    return &_bsmod_callbacks_;
}

static void _bsmod_instanceAxisFace(
    bsgfx_Primitive* primitive,
    int axis,
    bs_RGBA color,
    bs_mat4* transform)
{
    const bsgfx_TileAxis* ax = bsgfx_tileAxes() + axis;

    int width = (int)(primitive->scale.a[ax->width_axis] * 2.0f);
    int height = (int)(primitive->scale.a[ax->height_axis] * 2.0f);

    bs_vec3 right, up, start, m;
    bs_qRotateV3(&primitive->rotation, &ax->right, &right);
    bs_qRotateV3(&primitive->rotation, &ax->up, &up);

    bs_v3Mul(&ax->start_sign, &primitive->scale, &m);
    bs_qRotateV3(&primitive->rotation, &m, &start);

    bs_v3Add(&start, &primitive->position, &start);

    bs_vec3 full_right, full_up; 
    bs_v3MulS(&right, (float)width, &full_right);
    bs_v3MulS(&up, (float)height, &full_up);

    bs_vec3 a = start, b, c, d;
    bs_v3Add(&a, &full_right, &b);
    bs_v3Add(&a, &full_up, &c);
    bs_v3Add(&c, &full_right, &d);

    bsgfx_instanceDepthlessLine(a, b, color);
    bsgfx_instanceDepthlessLine(b, d, color);
    bsgfx_instanceDepthlessLine(d, c, color);
    bsgfx_instanceDepthlessLine(c, a, color);
}

BSMODAPI void _bsmod_onTick() {
    memset(&_bsmod_.queue, 0, sizeof(_bsmod_.queue));

  //  static float lisk_time = 0.0;
  //  lisk_time += bs_elapsedTime();
  //  if (lisk_time > 0.1) {
  //      if (bs_arguments()->use_lisk)
  //          _bsmod_tickLisk();
  //      lisk_time = 0.0;
  //  }

    if (InterlockedCompareExchange(&_bsmod_has_performed_tracked_changes_, 1, 1) == 1) {

        _bsmod_savePackage(BSMOD_CONTENT_PATH);
        _bsmod_savePackage(BSGFX_CONTENT_PATH);
        if (_bsmod_config_.doc)
            _bsmod_savePackage(_bsmod_applicationContentPath());

    }

    if (bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS) && bs_bufferIsMapped(bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS)->buffer)) {
        _bsmod_readHoveringOutputs();
        _bsmod_readHoveringInstanceData();
        _bsmod_readHoveringVertex();
    }

    _bsmod_instanceUI();
    if (!_bsmod_.ui_blocked)
        _bsmod_instanceTransform();
    if (!_bsmod_.ui_blocked)
        _bsmod_selectHoveringTypes();
    if (!_bsmod_.ui_blocked)
        _bsmod_editSelectedType();

    if (bs_keyDown(BS_KEY_LEFT_CONTROL) && bs_keyDownOnce(BS_KEY_C))
        _bsmod_deselectAll();

    static int last_selected_count = 0;
    static int last_selected_type = 0;
    switch (_bsmod_.selected_type) {
    case BSGFX_TYPE_TILE: {
        bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, _bsmod_.selected_tile_primitive);

        if (last_selected_type != _bsmod_.selected_type || last_selected_count != _bsmod_.selected_tiles.count) {
            bs_Batch* batch = bs_fetch(_bsmod_batches_, BSMOD_BATCH_TILE)->batch;
            bs_Scope last = *bs_getScope();
            bs_setScope(&(bs_Scope) { .queue = bs_singleTimesQueue() });
            bs_unpushBatch(batch);

            for (int i = 0; i < _bsmod_.selected_tiles.count; i++) {
                int* this = bs_fetchUnit(&_bsmod_.selected_tiles, i);

                bs_ivec2 coord;
                bsgfx_tileCoordinate(primitive, _bsmod_.selected_tile_axis, *this, &coord);

                if (coord.x == BS_I32_MAX)
                    continue;

                bs_U32 tile_index;
                bsgfx_pushTileAt(batch, primitive, _bsmod_.selected_tile_axis, coord.x, coord.y, 0, 0, &tile_index);
            }

            bs_pushBatch(batch, BS_U32_MAX, BS_U32_MAX);
            bs_setScope(&last);



            /**

             */
            for (int i = 0; i < bsgfx_count(BSGFX_TYPE_TILE); i++) {
                bsgfx_Tile* tile = bsgfx_get(BSGFX_TYPE_TILE, i);

                for (int j = 0; j < _bsmod_.selected_tiles.count; j++) {
                    int id = *(int*)bs_fetchUnit(&_bsmod_.selected_tiles, j);
                    if (tile->index == id) {
                        _bsmod_select(&_bsmod_.selected_ids, BSGFX_TYPE_TILE, i);
                    }
                }
            }

        }

        bs_mat4 transform = BS_MAT4_IDENTITY;
        bs_m4Translate(&transform, &primitive->position, &transform);
        bs_m4Rotate(&transform, &primitive->rotation, &transform);
        bs_m4Scale(&transform, &primitive->scale, &transform);

        bs_Aabb aabb = { .min = { -1, -1, -1 }, .max = { 1, 1, 1 } };
        //bsgfx_instanceObb(&aabb, BS_WHITE, &transform); //TODO:

        _bsmod_instanceAxisFace(primitive, _bsmod_.selected_tile_axis, BS_RGBA(130, 245, 245, 255), &BS_MAT4_IDENTITY);

        last_selected_count = _bsmod_.selected_tiles.count;
        last_selected_type = _bsmod_.selected_type;
    } return;
    case BSGFX_TYPE_PRIMITIVE: {
        for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
            int* this = bs_fetchUnit(&_bsmod_.selected_ids, i);
            bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, *this);

            bs_mat4 transform = BS_MAT4_IDENTITY;
            bs_m4Translate(&transform, &primitive->position, &transform);
            bs_m4Rotate(&transform, &primitive->rotation, &transform);
            bs_m4Scale(&transform, &primitive->scale, &transform);

            bs_Aabb aabb = { .min = { -1, -1, -1 }, .max = { 1, 1, 1 } };
            // bsgfx_obbInstance(&aabb, BS_WHITE, &transform); // TODO:
        }
    } break;
    case BSGFX_TYPE_PREFAB: {
        for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
            int* this = bs_fetchUnit(&_bsmod_.selected_ids, i);
            bsgfx_Prefab* prefab = bsgfx_get(BSGFX_TYPE_PREFAB, *this);

            bs_mat4 transform = BS_MAT4_IDENTITY;
            bs_m4Translate(&transform, &prefab->position, &transform);
            bs_m4Rotate(&transform, &prefab->rotation, &transform);
            bs_m4Scale(&transform, &prefab->scale, &transform);

            bs_Aabb aabb = { .min = { -1, -1, -1 }, .max = { 1, 1, 1 } };

            bsgfx_instancePrefab(*this, BSGFX_PREFAB_SUBTYPE_MESH_POLYGON_OUTLINE);
        }
    } break;
    }

    end:
    last_selected_count = _bsmod_.selected_ids.count;
    last_selected_type = _bsmod_.selected_type;

    if (_bsmod_callbacks_.tick)
        _bsmod_callbacks_.tick();
}

BSMODAPI void _bsmod_onMap(bsgfx_TypeId type_id, int id) {
    switch (type_id) {
    case BSGFX_TYPE_PRIMITIVE:
        bsgfx_Primitive* primitive = bsgfx_get(type_id, id);
        if (_bsmod_.settings.draw_hidden_primitives && primitive->flags & BSGFX_PRIMITIVE_HIDDEN)
            primitive->flags &= ~BSGFX_PRIMITIVE_HIDDEN;
        break;
    }
}

static void _bsmod_computeFlyCamera() {
    bs_vec2 resolution = {
        .x = (float)bs_resolution().x,
        .y = (float)bs_resolution().y
    };

    float move_speed = 0.15;
    const float mouse_sensitivity = 0.005;

    static float yaw = -3.8;
    static float pitch = -0.2;

    static bool rotating = false;
    static bs_vec2 last_cursor;

    bs_vec2 cursor = bs_cursorPosition();

    if (bs_keyDown(BS_KEY_LEFT_SHIFT))
        move_speed = 0.5;

    if (bs_middleClickOnce()) {
        rotating = true;
        last_cursor = cursor;
    }

    if (bs_middleClick()) {
        bs_vec2 delta = {
            last_cursor.x - cursor.x,
            last_cursor.y - cursor.y
        };

        yaw += delta.x * mouse_sensitivity;
        pitch -= delta.y * mouse_sensitivity;

        if (pitch > 1.5) pitch = 1.5;
        if (pitch < -1.5) pitch = -1.5;

        last_cursor = cursor;
    }

    if (bs_middleClickUpOnce()) {
        rotating = false;
    }

    bs_vec3 forward = {
        bs_cos(pitch) * bs_sin(yaw),
        bs_sin(pitch),
        bs_cos(pitch) * bs_cos(yaw)
    };

    static bs_vec3 camera_direction;
    static bs_vec3 camera_position = { 7.7, 12.7, 18.0 };

    bs_vec3 temp;
    bs_vec3 right, up = BS_V3(0.0, 1.0, 0.0);

    bs_v3Normalize(&forward, &camera_direction);
    bs_v3Cross(&camera_direction, &BS_V3(0.0, 1.0, 0.0), &right);
    bs_v3Normalize(&right, &right);

    if (bs_keyDown(BS_KEY_W)) {
        bs_v3MulS(&camera_direction, move_speed, &temp);
        bs_v3Add(&camera_position, &temp, &camera_position);
    }

    if (bs_keyDown(BS_KEY_S)) {
        bs_v3MulS(&camera_direction, move_speed, &temp);
        bs_v3Sub(&camera_position, &temp, &camera_position);
    }

    if (bs_keyDown(BS_KEY_D)) {
        bs_v3MulS(&right, move_speed, &temp);
        bs_v3Add(&camera_position, &temp, &camera_position);
    }

    if (bs_keyDown(BS_KEY_A)) {
        bs_v3MulS(&right, move_speed, &temp);
        bs_v3Sub(&camera_position, &temp, &camera_position);
    }

    bs_mat4 proj, view;
    
    bs_perspective(
        bs_radians(50.0),
        resolution.x / resolution.y,
        0.1,
        1000.0,
        &proj
    );

    bs_vec3 center;
    bs_v3Add(&camera_position, &camera_direction, &center),
    bs_lookAt(
        &camera_position,
        &center,
        &BS_V3(0.0, 1.0, 0.0),
        &view
    );

    bsgfx_setCamera(&proj, &view);
}

BSMODAPI void _bsmod_onGfxRender() {
    static bool override_camera;

    if (BS_GET_BIT(bs_io()->keys, BS_KEY_TAB) && !BS_GET_BIT(bs_io()->keys_old, BS_KEY_TAB)) {
        bs_disableUserInputs(false);
        override_camera = !override_camera;

    }

    if (_bsmod_.ui_blocked)
        bs_lockCursorPosition(false);

    if (override_camera) {
        bs_lockCursorPosition(false);
        _bsmod_computeFlyCamera();
        bs_disableUserInputs(true);
    }
}

static DWORD WINAPI _bsmod_tickAsync(void* param) {
    while (1) {
        InterlockedExchange(&_bsmod_has_performed_tracked_changes_, 0);
        _bsmod_onTrack();
        InterlockedExchange(&_bsmod_has_performed_tracked_changes_, 1);
        Sleep(1000);
    }
}

static void _bsmod_onLoadVariables() {
    if (_bsmod_config_.doc)
        bs_destroyJson(&_bsmod_config_);

    bs_loadJson(&_bsmod_config_, BS_CONSTANT_STRING(BSMOD_CONFIG_PATH));
    if (_bsmod_config_.doc)
        bs_infoF("Loaded \"%s\"\n", BSMOD_CONFIG_PATH);

}

BSMODAPI void _bsmod_onIni() {
    bs_Result result;

    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
        (LPCSTR)(&_bsmod_onIni),
        &_bsmod_.module);

    _bsmod_images_ = bs_configureSource(BS_OBJECT_IMAGE, BSMOD_IMAGES_COUNT, (const char* []) { BSMOD_IMAGE_IDS(BS_STRING_GEN) });
    _bsmod_samplers_ = bs_configureSource(BS_OBJECT_SAMPLER, BSMOD_SAMPLERS_COUNT, (const char* []) { BSMOD_SAMPLER_IDS(BS_STRING_GEN) });
    _bsmod_buffers_ = bs_configureSource(BS_OBJECT_BUFFER, BSMOD_BUFFERS_COUNT, (const char* []) { BSMOD_BUFFER_IDS(BS_STRING_GEN) });
    _bsmod_queues_ = bs_configureSource(BS_OBJECT_QUEUE, BSMOD_QUEUES_COUNT, (const char* []) { BSMOD_QUEUE_IDS(BS_STRING_GEN) });
    _bsmod_batches_ = bs_configureSource(BS_OBJECT_BATCH, BSMOD_BATCHES_COUNT, (const char* []) { BSMOD_BATCH_IDS(BS_STRING_GEN) });
    _bsmod_renderers_ = bs_configureSource(BS_OBJECT_RENDERER, BSMOD_RENDERERS_COUNT, (const char* []) { BSMOD_RENDERER_IDS(BS_STRING_GEN) });
    _bsmod_ray_tracers_ = bs_configureSource(BS_OBJECT_RAY_TRACER, BSMOD_RAY_TRACERS_COUNT, (const char* []) { BSMOD_RAY_TRACER_IDS(BS_STRING_GEN) });
    _bsmod_fonts_ = bs_configureSource(BS_OBJECT_FONT, BSMOD_FONTS_COUNT, (const char* []) { BSMOD_FONT_IDS(BS_STRING_GEN) });
    _bsmod_atlases_ = bs_configureSource(BS_OBJECT_ATLAS, BSMOD_ATLASES_COUNT, (const char* []) { BSMOD_ATLAS_IDS(BS_STRING_GEN) });

    _bsmod_onLoadVariables();
    _bsmod_loadShaderReferences();

    result = bs_loadPackage(BSGFX_CONTENT_PATH, &_bsmod_.bsgfx_package);

    if (result == BS_RESULT_OK) {

        bs_Resource* resource;
        result = bs_loadResource(_bsmod_.bsgfx_package, 0, &resource, BS_CONSTANT_STRING("bindings"));

        if (result == BS_RESULT_OK) {
            result = bs_json(resource->data->value, resource->data->len, &_bsmod_.bindings_json);
        }
    }

    if (!_bsmod_.bindings_json.doc)
        _bsmod_.bindings_json = bs_emptyJson();

    _bsmod_iniPackage(BSMOD_CONTENT_PATH);
    _bsmod_iniPackage(BSGFX_CONTENT_PATH);
    _bsmod_iniPackage(_bsmod_applicationContentPath());
    // _bsmod_iniLisk();
    _bsmod_iniCompiler();

    bs_configureSource(BS_OBJECT_IMAGE, BSMOD_IMAGES_COUNT, (const char* []) { BSMOD_IMAGE_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_SAMPLER, BSMOD_SAMPLERS_COUNT, (const char* []) { BSMOD_SAMPLER_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_BUFFER, BSMOD_BUFFERS_COUNT, (const char* []) { BSMOD_BUFFER_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_QUEUE, BSMOD_QUEUES_COUNT, (const char* []) { BSMOD_QUEUE_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_BATCH, BSMOD_BATCHES_COUNT, (const char* []) { BSMOD_BATCH_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_RENDERER, BSMOD_RENDERERS_COUNT, (const char* []) { BSMOD_RENDERER_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_RAY_TRACER, BSMOD_RAY_TRACERS_COUNT, (const char* []) { BSMOD_RAY_TRACER_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_FONT, BSMOD_FONTS_COUNT, (const char* []) { BSMOD_FONT_IDS(BS_STRING_GEN) });
    bs_configureSource(BS_OBJECT_ATLAS, BSMOD_ATLASES_COUNT, (const char* []) { BSMOD_ATLAS_IDS(BS_STRING_GEN) });
}

BSMODAPI void _bsmod_onLateIni() { // ugly, called after first track
    bs_Result result;

    _bsmod_savePackage(BSMOD_CONTENT_PATH);
    _bsmod_savePackage(BSGFX_CONTENT_PATH);
    _bsmod_savePackage(_bsmod_applicationContentPath());

    result = bs_loadPackage(BSMOD_CONTENT_PATH, &_bsmod_.package);

    if (bs_args()->track_changes)
        CreateThread(NULL, 0, _bsmod_tickAsync, NULL, 0, NULL);
}

BSMODAPI void _bsmod_onCreateQuadSubtypes(bs_Range range) {
    bs_Batch* batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_QUAD_INSTANCED)->batch;
    _bsmod_subtypes_[BSMOD_SUBTYPE_MATERIAL_ICON] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, batch, 0, range);
    _bsmod_subtypes_[BSMOD_SUBTYPE_PRIMITIVE_ICON] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, batch, 0, range);
    _bsmod_subtypes_[BSMOD_SUBTYPE_PREFAB_ICON] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, batch, 0, range);
    _bsmod_subtypes_[BSMOD_SUBTYPE_BILLBOARD] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, batch, 0, range);
}

BSMODAPI void _bsmod_bindAtlases() {
    bs_Sampler* nearest_sampler = bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler;

    if (bs_exists(BSMOD_ATLASES, BSMOD_ATLAS_UI)) {
        bs_Atlas* ui = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas;
        bs_bindImages(BSMOD_SET_IMAGE_ATLAS_UI, BSMOD_BINDING_IMAGE_ATLAS_UI, &(bs_ImageDescriptor) {
            .image = ui->image,
            .sampler = nearest_sampler,
            .layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        }, 1);
    }

    bs_ImageDescriptor icon_atlases[BSMOD_ATLAS_ICONS_COUNT] = { 0 };

    if (bs_exists(BSMOD_ATLASES, BSMOD_ATLAS_MATERIAL_ICONS))
        icon_atlases[BSMOD_ATLAS_ICONS_MATERIALS_BINDING].image = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_MATERIAL_ICONS)->atlas->image;

    if (bs_exists(BSMOD_ATLASES, BSMOD_ATLAS_PRIMITIVE_ICONS))
        icon_atlases[BSMOD_ATLAS_ICONS_PRIMITIVES_BINDING].image = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_PRIMITIVE_ICONS)->atlas->image;

    if (bs_exists(BSMOD_ATLASES, BSMOD_ATLAS_PREFAB_ICONS))
        icon_atlases[BSMOD_ATLAS_ICONS_PREFABS_BINDING].image = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_PREFAB_ICONS)->atlas->image;

    for (int i = 0; i < BSMOD_ATLAS_ICONS_COUNT; i++) {
        icon_atlases[i].layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        icon_atlases[i].sampler = nearest_sampler;
    }

    bool bind_icons = true;
    for (int i = 0; i < BSMOD_ATLAS_ICONS_COUNT; i++) {
        if (!icon_atlases[i].image) {
            bs_warnF("Could not bind atlas icons, binding \"%d\" does not exist\n", i);
            bind_icons = false;
            break;
        }
    }

    if (bind_icons)
        bs_bindImages(BSMOD_SET_IMAGE_ATLAS_ICONS, BSMOD_BINDING_IMAGE_ATLAS_ICONS, icon_atlases, BSMOD_ATLAS_ICONS_COUNT);
}

BSMODAPI void _bsmod_onLoad() {
    bs_Result result;

    bs_Sampler* nearest_sampler = bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler;

    bs_Object* font_object = BS_FONT(BSGFX_FONTS, BSGFX_FONT_ARIAL_16, 0);
    result = bs_loadFont(font_object, _bsmod_.package, "fonts/consolas_16", BSGFX_ALPHABET_DEFAULT, 32.0, 0);
    if (result == BS_RESULT_OK)
        bs_bindFont(font_object->font, bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler, BSGFX_SET_FONTS, BSGFX_BINDING_FONT_ARIAL);

    bs_Object* quad_instanced_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_QUAD_INSTANCED);
    bs_Range range = {
		.num = 6, // single quad
	};
	_bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instanced_batch->batch, 0, range);

    bs_Object* tile_batch_object = BS_BATCH(BSMOD_BATCHES, BSMOD_BATCH_TILE, 0);
    result = bs_batch(tile_batch_object, sizeof(int), $vs_bsgfx_tile_static(), BS_BATCH_KEEP_DATA);
    if (result == BS_RESULT_OK && bs_canPushBatch(tile_batch_object->batch)) {
        bs_Range range;
        bs_Quad quad;
        bs_quad(&BS_V3(0, 0, 0), &BS_V2(1, 1), &quad);

        bsgfx_pushTile(tile_batch_object->batch, &quad, BS_V3(0, 0, 0), 0, 0, &range);
        bs_pushBatch(tile_batch_object->batch, BS_U32_MAX, BS_U32_MAX);
    }

    //_bsmod_subtypes[BSMOD_SUBTYPE_SPHERE_HIGH_QUALITY] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_MESH, BSGFX_BATCH_MESH_INSTANCED, BSGFX_SUBTYPE_HAS_SHADOWS, sphere_high_quality_range);

    bs_queue(BS_QUEUE(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS, BS_OBJECT_HAS_SWAPS_BIT), BS_QUEUE_GRAPHICS_BIT);
    bs_queue(BS_QUEUE(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION, 0), BS_QUEUE_GRAPHICS_BIT | BS_QUEUE_DONT_SIGNAL);

    bs_Object* renderer_object = BS_RENDERER(BSMOD_RENDERERS, BSMOD_RENDERER, BS_OBJECT_HAS_SWAPS_BIT);
    result = bs_renderer(renderer_object, 0);

    bs_ivec2 resolution = bs_resolution();
    if (result == BS_RESULT_OK) {
        bs_Object* depth = BS_IMAGE(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH, 0);
        bs_Object* color = BS_IMAGE(BSMOD_IMAGES, BSMOD_IMAGE_COLOR, 0);

        result = bs_image(depth, resolution, 0, BS_FORMAT_D32_SFLOAT_S8_UINT, BS_IMAGE_ATTACHMENT_BIT);
        result = bs_image(color, resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);

        // bs_U32 subpass, bs_Image* image, bs_ImageLayout old_layout, bs_ImageLayout new_layout, bs_OutputFlags flags
        bs_output(renderer_object->renderer, (bs_Output) {
            .subpass = 0, 
            .image = bs_context()->swapchain_image->image,
            .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
            .store_op = BS_ATTACHMENT_STORE_OP_STORE,
            .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
            .new_layout = BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        });

        bs_Image* subpass_0_outputs[] = {
            depth->image,
        };

        for (int i = 0; i < sizeof(subpass_0_outputs) / sizeof(*subpass_0_outputs); i++) {
            bs_output(renderer_object->renderer, (bs_Output) {
                .subpass = 0,
                .image = subpass_0_outputs[i],
                .load_op = BS_ATTACHMENT_LOAD_OP_CLEAR,
                .store_op = BS_ATTACHMENT_STORE_OP_STORE,
                .old_layout = BS_IMAGE_LAYOUT_UNDEFINED,
                .new_layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            });
        }

        bs_dependency(renderer_object->renderer, -1, 0, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | BS_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
            BS_ACCESS_MEMORY_READ_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT);

        bs_renderPass(renderer_object->renderer);
        bs_framebuffer(renderer_object->renderer, resolution);
    }

    bs_Object* renderer_3d = BS_RENDERER(_bsmod_renderers_, BSMOD_RENDERER_3D, BS_OBJECT_HAS_SWAPS_BIT);
    result = bs_renderer(renderer_3d, 0);
    if (result == BS_RESULT_OK) {
        bs_Object* depth = BS_IMAGE(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH_3D, 0);
        bs_image(depth, resolution, 0, BS_FORMAT_D32_SFLOAT_S8_UINT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_DST_BIT);
       // bs_Image* color = bs_image(BS_IMAGE(BSMOD_IMAGE_COLOR, 0), resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT)->image;

        bs_output(renderer_3d->renderer, (bs_Output) {
            .subpass = 0, 
            .image = bs_context()->swapchain_image->image,
            .load_op = BS_ATTACHMENT_LOAD_OP_LOAD,
            .store_op = BS_ATTACHMENT_STORE_OP_STORE,
            .old_layout = BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            .new_layout = BS_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        });

        bs_transition(depth->image, 0, BS_IMAGE_LAYOUT_UNDEFINED, BS_IMAGE_LAYOUT_GENERAL);
        bs_output(renderer_3d->renderer, (bs_Output) {
            .subpass = 0, 
            .image = depth->image,
            .load_op = BS_ATTACHMENT_LOAD_OP_LOAD,
            .store_op = BS_ATTACHMENT_STORE_OP_STORE,
            .old_layout = BS_IMAGE_LAYOUT_GENERAL,
            .new_layout = BS_IMAGE_LAYOUT_GENERAL,
        });

        bs_dependency(renderer_3d->renderer, -1, 0, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | BS_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
            BS_ACCESS_MEMORY_READ_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT);

        bs_renderPass(renderer_3d->renderer);
        bs_framebuffer(renderer_3d->renderer, resolution);
    }

    bs_Object* ui = BS_ATLAS(BSMOD_ATLASES, BSMOD_ATLAS_UI, 0);
    bs_Object* material_icons = BS_ATLAS(BSMOD_ATLASES, BSMOD_ATLAS_MATERIAL_ICONS, 0);
    bs_Object* primitive_icons = BS_ATLAS(BSMOD_ATLASES, BSMOD_ATLAS_PRIMITIVE_ICONS, 0);
    bs_Object* prefab_icons = BS_ATLAS(BSMOD_ATLASES, BSMOD_ATLAS_PREFAB_ICONS, 0);

    bs_loadAtlas(ui, _bsmod_.package, 0, BS_CONSTANT_STRING("ui"));
    bs_loadAtlas(material_icons, _bsmod_.package, 0, BS_CONSTANT_STRING("material_icons"));
    bs_loadAtlas(primitive_icons, _bsmod_.package, 0, BS_CONSTANT_STRING("primitive_icons"));
    bs_loadAtlas(prefab_icons, _bsmod_.package, 0, BS_CONSTANT_STRING("prefab_icons"));

    _bsmod_bindAtlases();
}