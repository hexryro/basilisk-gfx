
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
   * Billboards
   *============================================================================*/

BSMODAPI void _bsmod_instanceLightBillboards() {
    bs_vec2 resolution = BS_IV2_TO_V2(bs_resolution(bs_scope()->context));
    bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);
    const bs_mat4 identity = BS_MAT4_IDENTITY;

    for (int i = 0; i < bsgfx_count(BSGFX_TYPE_LIGHT); i++) {
        bsgfx_Light* light = bsgfx_get(BSGFX_TYPE_LIGHT, i);

        bs_mat4x3 m = bsgfx_matrix(light->position, BS_V3(1.0, 1.0, 0.0));
        bsgfx_AtlasCache* cache = NULL;

        switch (light->type) {
        case BSGFX_LIGHT_TYPE_POINT:
            cache = $BSMOD_ATLAS_UI_light();
            break;
        case BSGFX_LIGHT_TYPE_SUN:
            cache = $BSMOD_ATLAS_UI_sun();
            break;
        default: continue;
        }

        bsgfx_instanceQuad(_bsmod_subtypes_[BSMOD_SUBTYPE_BILLBOARD], m, cache->coords, 0, 0, $white_material()->id);

        const float length = 100.0;
        bsgfx_instanceLine(light->position, BS_V3_ADD(light->position, BS_V3_MUL_S(light->direction, length)), BS_BLACK);

        bs_vec2 p;
        bsgfx_worldToScreen(&light->position, &poser()->camera.result, &resolution, &p);

        bs_vec4 clip;
        bs_m4MulV4(&poser()->camera.result, &BS_V3_TO_V4(light->position, 1.0f), &clip);

        float pixels_per_unit = poser()->camera.proj.a[1][1] * resolution.y * 0.5f;
        float scaled_size = pixels_per_unit / clip.w;

        p.x -= scaled_size * 0.5;
        p.y -= scaled_size * 0.5;

       // bsgfx_AtlasCache* white = $BSMOD_ATLAS_UI_white();
       // bs_mat4x3 m2 = bsgfx_matrix(bs_v3V2(p, 50.0f), BS_V3(scaled_size, scaled_size, 0.0f));
       // bsgfx_instanceQuad(bsgfx_subtypes()[BSGFX_SUBTYPE_UI], m2, white->coords, 0, 0, $white_material()->id);

        bool hovering = bs_rectangleVsPoint(&p, &BS_V2(scaled_size, scaled_size), &cursor);
        if (hovering) {
            //_bsmod_.hovering.billboard = true;

            if (bs_leftClickOnce()) {
                if (!bs_keyDown(BS_KEY_ALT))
                    _bsmod_deselectAll();

                _bsmod_select(&_bsmod_.selected_ids, BSGFX_TYPE_LIGHT, i);
            }
        }
    }
}



  /*==============================================================================
   * Context Menu
   *============================================================================*/

static inline void _bsmod_addLight(bsgfx_LightType type) {
    assert(_bsmod_.selected_tiles.count == 1);

    int tile_id = *(int*)bs_fetchUnit(&_bsmod_.selected_tiles, 0);
    int primitive_id = bsgfx_queryTilePrimitive(tile_id);
    bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, primitive_id);

    int axis;
    bsgfx_tileAxis(primitive, tile_id, &axis);

    bs_ivec2 coords;
    bsgfx_tileCoordinate(primitive, axis, tile_id, &coords);

    bsgfx_RawLight data = {
        .type = type,
        .rotation = { 0.0 }
        //.direction = { 0.0, -1.0, 0.0 },
    };
    bsgfx_tilePosition(primitive, axis, coords.x, coords.y, &data.position);

    _bsmod_add(BSGFX_TYPE_LIGHT, &data);
}

static bool _bsmod_onAddPointTick(const bsgfx_ButtonParams* params) {
    if (params->hovering && bs_leftClickOnce())
        bs_warnN(BS_CONSTANT_STRING("Point light is not implemented\n"));

    return params->hovering;
}

static bool _bsmod_onAddSunTick(const bsgfx_ButtonParams* params) {
    if (params->hovering && bs_leftClickOnce())
        _bsmod_addLight(BSGFX_LIGHT_TYPE_SUN);

    return params->hovering;
}

BSMODAPI bool _bsmod_onAddLightTick(const bsgfx_ButtonParams* params) {
    static bool was_hovering;
    bool hovering = params->hovering;

    bs_vec3 position = params->widget_position;
    position.y += BSMOD_CONTEXT_MENU_BUTTON_HEIGHT;
    position.x += params->menu->untextured.dimensions.x;
    position.x -= BSMOD_CONTEXT_MENU_PADDING - 1;

    bs_vec2 size = BS_V2(125.0, 175.0);

    if (!hovering && was_hovering) {
        bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);
        bs_vec2 p = { position.x - (BSMOD_CONTEXT_MENU_PADDING + 2), position.y - size.y };

        if (bs_rectangleVsPoint(&p, &size, &cursor)) {
            hovering = true;
        }
    }

    if (hovering) {
        static bs_List widgets = { .unit_size = sizeof(bsgfx_Widget), .increment = 16};
        widgets.count = 0;

        const int indent = 4;
        //bsgfx_Widget sun_widget = _bsmod_iconWidget(icon, align_height, bs_v3AddX(icon_offset, padding), BSGFX_WIDGET_ADVANCE_RIGHT);
        _bsmod_pushContextMenuButton(&widgets, size, BS_V3(0, -1, 0), $BSMOD_ATLAS_UI_light_add(), "Point", 0, _bsmod_onAddPointTick, false);
        _bsmod_pushContextMenuButton(&widgets, size, BS_V3(0, 0, 0), $BSMOD_ATLAS_UI_sun_add(), "Sun", 0, _bsmod_onAddSunTick, false);

        _bsmod_instanceContextMenu(&widgets, position, size);
    }

    was_hovering = hovering;
    return hovering;
}
