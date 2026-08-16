
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

#ifndef BSMOD_INTERNAL_H
#define BSMOD_INTERNAL_H

#include <bsmod_internal.gen.h>

#ifdef RENDERDOC_PATH
#include RENDERDOC_PATH
#endif

typedef struct {
    int package;
    int bsgfx_package;
    int selected_tile_primitive;
    int selected_tile_axis;
    struct {
        bs_RGBA color;
        bs_vec3 normal;
        bs_U32 index;
        bs_U32 flags;
        bs_vec3 position;
        int instance_type;
        int instance_id;
        int subtype;
        int closest_primitive;
        bs_vec3 closest_vertex;
        bool billboard;
        int primitive;
        int prefab;
        int tile;
        int tile_axis;
    } hovering;
    bs_List selected_ids;
    bs_List selected_tiles;
    int editor_resource_type;
    int editor_resource_id;
    bs_String* foliage_density_input;
    bs_String* primitive_angle_input;
    bs_vec2 selected_tile_size;
    bool draw_menu;
    bool active;
    bool ui_blocked;
    int overlay;
    PFN_bsmod_GridMenu grid_menu;
    PFN_bsmod_GridMenuCallback grid_menu_callback;
    void* grid_menu_params;
    int clicked_type;
    int clicked_id;
    bsgfx_TypeId selected_type;
    int axis;
    bs_I64 history;
    struct {
        bool draw_hidden_primitives;
    } settings;
    struct {
        int isolated_subtype;
        int isolated_id;
        bool screenshot;
        bool load_fonts;
        bool load_shaders;
        bool load_materials;
        bool load_textures;
        bool load_scripts;
        bool skip_mesh_index_write;
    } queue;
    int dragging_object_id;
    int dragging_subtype;
    int dragging_id;
    bsmod_EditType edit_type;
    bsmod_EditType edit_type_old;
    bs_Json track_json;
   // bs_Json bindings_json;
    bs_String* variadic;
    bs_List queue_load;
    HMODULE module;
#ifdef RENDERDOC_PATH
    HMODULE renderdoc_module;
    RENDERDOC_API_1_6_0* renderdoc_api;
    RENDERDOC_DevicePointer renderdoc_device;
#endif
} Bsmod;

BSMODAPI extern Bsmod _bsmod_;

static inline const char* _bsmod_applicationContentPath() {
	return bs_fetchJsonN(&_bsmod_config_, BS_JSON_STRING, BS_CONSTANT_STRING("application.content_path")).as_string;
}

#define BSMOD_WARN_SPVC_ERROR(function, code, format, ...)            \
    bs_warnF("%s at %s:%d: %s failed" __VA_OPT__(", ") format " (SPVC result %d)\n", __func__, __FILE__, __LINE__, function __VA_OPT__(,) __VA_ARGS__, code)

#define BSMOD_WARN_FREETYPE_ERROR(function, code, format, ...)        \
    bs_warnF("%s at %s:%d: %s failed" __VA_OPT__(", ") format " (FreeType error %d)\n", __func__, __FILE__, __LINE__, function __VA_OPT__(,) __VA_ARGS__, code)

#endif
