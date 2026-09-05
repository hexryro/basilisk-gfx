
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

BSMODAPI void _bsmod_instanceContextMenu(bs_List* widgets, bs_vec3 position, bs_vec2 size) {
    bool hovering = bsgfx_instanceWidgets((bsgfx_Menu) {
        .position = position,
        // .text_subtype = _bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS], // TODO: text rewrite
        // .font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head, // TODO: text rewrite
        .spacing = 4.0,
        .widgets = widgets->data,
        .widgets_count = widgets->count,
        .background_material_id_0 = $bsmod_grey_61()->id,
        .shadow_material_id = $bsmod_grey_30()->id,
        .untextured = {
            .dimensions = size,
            .auto_scale_width = true,
            .border_id = -1,
            // .has_shadow = true,
        },
        .blocked = false,
        .border_radius = BSMOD_DEFAULT_RADIUS,
    }, NULL, NULL);

    if (!_bsmod_.ui_blocked)
        _bsmod_.ui_blocked = hovering;
}

BSMODAPI void _bsmod_pushContextMenuButton(bs_List* widgets, bs_vec2 menu_size, bs_vec3 icon_offset, bsgfx_AtlasCache* icon, const char* name, int indent, PFN_bsgfx_ButtonWidgetCallback action, bool expandable) {
    const int padding = BSMOD_CONTEXT_MENU_PADDING;
    const int align_height = BSMOD_CONTEXT_MENU_BUTTON_HEIGHT;

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .offset.x = padding,
        .type = BSGFX_WIDGET_BUTTON,
        .button = {
            .size = { menu_size.x - padding * 2, 20.0 },
        // .name = name,
            .tick = action,
            .material = $bsmod_grey_61()->id,
            .selected_material = $bsmod_grey_100()->id,
        },
        .align_height = align_height,
    });
    bsgfx_AtlasCache* expand = $BSMOD_ATLAS_UI_expand();

    bsgfx_Widget expand_widget, icon_widget;
    _bsmod_iconWidget(
        expand, 
        align_height, 
        BS_V3(menu_size.x - padding * 2 - expand->size.x, 0.0, 0.0), 
        0,
        &expand_widget
    );
    _bsmod_iconWidget(
        icon, 
        align_height, 
        BS_V3(icon_offset.x + padding, icon_offset.y, icon_offset.z), 
        BSGFX_WIDGET_ADVANCE_RIGHT,
        &icon_widget
    );

    if (expandable)
        bs_pushBack(widgets, &expand_widget);
    bs_pushBack(widgets, &icon_widget);

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .offset.x = padding,
        .type = BSGFX_WIDGET_STRING,
        .string = {
            .value = name,
        },
        .align_height = align_height,
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN,
    });

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .advance_flags = BSGFX_WIDGET_ADVANCE_RESET_X,
    });
}

BSMODAPI void _bsmod_instanceTileContextMenu(bs_vec3 position, bs_vec2 size) {
    static bs_List widgets = { .unit_size = sizeof(bsgfx_Widget), .increment = 16 };
    widgets.count = 0;

    const int indent_0 = 8;
    const int indent_1 = 32;

    bs_pushBack(&widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_STRING,
        .string = {
            .value = "Add",
        },
        .material_id = $bsmod_grey_100()->id,
        .offset = { indent_0, -indent_0, 0.0 },
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN | BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Y,
    });

    bsgfx_Widget divider;
    _bsmod_dividerWidget(size.x, indent_0, &divider);

    bs_pushBack(&widgets, &divider);

    //_bsmod_pushContextMenuButton(&widgets, size, BS_V3(0, -1, 0), $BSMOD_ATLAS_UI_light_add(), "Light", indent_1, _bsmod_onAddLightTick, true);

    _bsmod_instanceContextMenu(&widgets, position, size);
}
