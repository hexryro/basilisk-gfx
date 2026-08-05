
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



  /*==============================================================================
   * Dragging Material
   *============================================================================*/

BSMODAPI void _bsmod_onDragMaterial(bsmod_DraggingParams params) {
    if (_bsmod_.hovering.flags & BSGFX_ID_IS_PREFAB) {
        bsgfx_Prefab* prefab = bsgfx_get(BSGFX_TYPE_PREFAB, _bsmod_.hovering.instance_id);
        bsgfx_RawPrefab* raw_prefab = bsgfx_getRaw(BSGFX_TYPE_PREFAB, _bsmod_.hovering.instance_id);
        if (bs_leftClickUpOnce()) {
            raw_prefab->material_hash = bsgfx_fetchMaterial(_bsmod_.dragging_id)->hash;
            _bsmod_saveTypeN(BSGFX_TYPE_PREFAB, BS_CONSTANT_STRING("Changed prefab material"));
        }
    }

}



  /*==============================================================================
   * Side Menu Material UI
   *============================================================================*/

bs_String* _bsmod_hex_input = NULL;
static bs_RGBA _bsmod_material_color_input = { 255, 255, 255, 255 };

static bsgfx_Material* _bsmod_selected_material;
static bs_String* _bsmod_material_name = NULL;
static bs_vec4 _bsmod_material_hsva = { 0, 0, 0, 1 };

static bsmod_GridClickParams _bsmod_click_params;

static void bsgfx_onChangeColor(struct bsgfx_Widget* widget, bs_RGBA color) {
    _bsmod_material_color_input = color;
    _bsmod_hex_input = bs_stringF(_bsmod_hex_input, "#%02X%02X%02X%02X", color.r, color.g, color.b, color.a);
    _bsmod_selected_material->contract->color = BS_V4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
    if (widget)
        _bsmod_selected_material->contract->hsva = _bsmod_material_hsva;
}

BSMODAPI void _bsmod_onClickMaterialMenu(bsmod_GridClickParams params) {
    bs_Atlas* atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_MATERIAL_ICONS)->atlas;

    char* name = atlas->unmapped[params.atlas_id].name;

    _bsmod_selected_material = bsgfx_queryMaterial(name);
    bs_infoF("Selected material \"%s\"\n", name);

    bs_vec4 rgba_f;
    bs_v4MulS(&_bsmod_selected_material->contract->color, 255.0, &rgba_f);

    bs_RGBA rgba = BS_RGBA(rgba_f.x, rgba_f.y, rgba_f.z, rgba_f.w);
    bsgfx_onChangeColor(NULL, rgba);

    _bsmod_material_name = bs_string(_bsmod_material_name, name);
    _bsmod_material_hsva.xyz = bs_rgbToHsv(&rgba);
    _bsmod_material_hsva.w = _bsmod_selected_material->contract->color.w;
    _bsmod_selected_material->contract->hsva = _bsmod_material_hsva;

    _bsmod_click_params = params;
}

BSMODAPI void _bsmod_pushMaterialWidgets(bs_List* widgets, bs_vec2 background_size) {

    bs_vec3 offset = { 8 + 16, -8, 0 };
    offset.z += BSGFX_BACKGROUND_Z_COUNT;

    const int name_padding = 4;
    const int color_padding = 6;
    const int hue_width = 24;
    const int texture_dimensions = 128;
    const int color_dimensions = 215;
    const int channel_width = 72;

    static int select_position, select_size;

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_INPUT,
        //.name = "Name",
        .input = {
            .type = BSGFX_INPUT_STRING,
            .as_string = &_bsmod_material_name,
            .dimensions = { background_size.x - offset.x, 16 },
            .outline_material_id = $bsmod_grey_40()->id,
            .background_outline_material_id = $bsmod_grey_30()->id,
            .select_position = &select_position,
            .select_size = &select_size,
        },
        .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
        .offset = offset,
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN,
    });

    bs_pushBack(widgets, &(bsgfx_Widget) {
       // .name = "Texture",
        .type = BSGFX_WIDGET_ICON,
        .offset = offset,
        .icon = {
            .type = BSGFX_ICON_MATERIAL,
            .scale = { texture_dimensions, texture_dimensions },
            .border_radius = BSMOD_DEFAULT_RADIUS,
            .outline_material_id = $bsmod_grey_30()->id,
            .material_id = _bsmod_click_params.atlas_id,
        },
        .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN,
    });

    bs_pushBack(widgets, &(bsgfx_Widget) {
       // .name = "Color",
        .type = BSGFX_WIDGET_COLOR,
        .offset = offset,
        .color = {
            .dimensions = { color_dimensions, color_dimensions },
            .hsva = &_bsmod_material_hsva,
            .hue_width = hue_width,
            .material_id = _bsmod_selected_material->id,
            .background_material_id = $white_material()->id,
            .outline_material_id = $bsmod_grey_30()->id,
            .padding = color_padding,
            .border_radius = BSMOD_DEFAULT_RADIUS,
            .on_change_color = bsgfx_onChangeColor,
        },
        .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN,
        //.prefer_x = true,
    });

    //offset.x += color_padding+ hue_width * 2;
    //bsmod_pushInputWidget(widgets, &_bsmod_red_input, offset, channel_width, name_padding, true, false, true, _bsmod_onChangeRedInput, "");
    //bsmod_pushInputWidget(widgets, &_bsmod_green_input, bs_v3AddY(offset, -(BSMOD_INPUT_HEIGHT + color_padding) * 1), channel_width, name_padding, true, false, true, _bsmod_onChangeGreenInput, "");
    //bsmod_pushInputWidget(widgets, &_bsmod_blue_input, bs_v3AddY(offset, -(BSMOD_INPUT_HEIGHT + color_padding) * 2), channel_width, name_padding, true, false, true, _bsmod_onChangeBlueInput, "");
    //bsmod_pushInputWidget(widgets, &_bsmod_alpha_input, bs_v3AddY(offset, -(BSMOD_INPUT_HEIGHT + color_padding) * 3), channel_width, name_padding, true, false, true, _bsmod_onChangeAlphaInput, "");
    //bsmod_pushInputWidget(widgets, &_bsmod_hex_input, bs_v3AddY(offset, -color_dimensions + BSMOD_INPUT_HEIGHT), channel_width, name_padding, true, true, false, _bsmod_onChangeHexInput, "");
}



  /*==============================================================================
   * Rasterizing Icons
   *============================================================================*/

BSMODAPI void _bsmod_rasterizeMaterialIcons() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsmod_mesh_instanced();
    hash.shaders[1] = $fs_bsmod_rasterize();

    if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
        const int width = 74;

        const bs_ivec2 render_size = { width * 2, width * 2 };
        const bs_ivec2 output_size = { width, width };

        bs_mat4 proj, view, camera;
        bs_orthographic(0, render_size.x, 0, render_size.y, -500.0, 500.0, &proj);
        bs_lookAt(&BS_V3(0, 0, 1), &BS_V3(0, 0, 0), &BS_V3(0, 1, 0), &view);

        bs_m4Mul(&proj, &view, &camera);

        struct {
            bs_mat4x3 camera;
            bs_mat4x3 model;
            bs_vec4 color;
            int material_texture_size;
            int material_texture_id;
        } push_const = {
            .camera = bs_m4x3(&camera),
        };

        _bsmod_beginRasterize(render_size, output_size);

        int sphere_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_PRIMITIVE_SPHERE];

        bs_List* materials = bsgfx_materials();

        bs_mat4 transform = BS_MAT4_IDENTITY;
        float s = render_size.x / 2.0 - 4.0;
        bs_m4Translate(&transform,  &BS_V3(render_size.x / 2, render_size.y / 2, 0.0), &transform);
        bs_m4Scale(&transform, &BS_V3(s, s, s), &transform);

        bs_mat4x3 matrix = bs_m4x3(&transform);

        for (int i = 0; i < materials->count; i++) {
            bsgfx_Material* material = bs_fetchUnit(materials, i);
            push_const.color = material->contract->color;
            push_const.material_texture_size = material->contract->image_binding;
            push_const.material_texture_id = material->contract->image;
            push_const.model = matrix;

            int instance = bsgfx_instancePrimitive(sphere_subtype, BS_MAT4_IDENTITY, 0, 0, 0);
            _bsmod_rasterizeInstance(hash, sphere_subtype, instance, material->category, material->name, render_size.x, render_size.y, sizeof(push_const), &push_const);
        }

        _bsmod_endRasterize();
    }
}