
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

#include <basilisk-mod.h>
#include <bsmod_cache.h>
#include <basilisk.h>

void basilisk_instanceTitleBarUI() {
    bs_vec3 position = { 0 };
    bs_vec2 dimensions = { 256, 256 };

	const int width = 64;
    static int scroll;
    static bs_List tabs = {.unit_size = sizeof(bsgfx_MenuTab), .increment = 16 };
    static bs_List widgets = { .unit_size = sizeof(bsgfx_Widget), .increment = 16 };

    tabs.count = 0;
    widgets.count = 0;

    const int padding = 8;
    bs_vec2 background_size = { dimensions.x - padding * 2, dimensions.y - padding * 2 };

    bs_pushBack(&widgets, &(bsgfx_Widget) {
        .offset = { 0, -padding, 0 },
        .advance_flags = BSGFX_WIDGET_ADVANCE_APPLY_OFFSET,
    });

    bs_pushBack(&widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_BACKGROUND,
        .background = {
            .border_radius = BSMOD_DEFAULT_RADIUS,
            .size = background_size,
            .material_id = $bsmod_grey_61()->id,
           // .outline_material_id = $bsmod_grey_30()->id,
            .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI_COLOR],
        },
        .offset = { padding, 0.0, 0 },
    });

    position.z += 10;

    static bool active_tab;
    bool hovering = bsgfx_instanceWidgets((bsgfx_Menu) {
        .position = position,
        .text_subtype = bsmod_subtypes()[BSMOD_SUBTYPE_FONT_CONSOLAS],
        .font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head,
        .spacing = 8.0,
        .widgets = widgets.data,
        .widgets_count = widgets.count,
        .background_material_id_0 = $context_menu_title_bar_transparent_material()->id,
        .background_material_id_1 = $context_menu_title_bar_material()->id,
        .untextured = {
            .dimensions = dimensions,
            .auto_scale_width = true,
            .border_id = -1,
            // .has_shadow = true,
        },
        .blocked = false,
        .border_radius = BSMOD_DEFAULT_RADIUS,
        .shadow_material_id = $bsmod_grey_61()->id,
        .outline_material_id = $bsmod_grey_148()->id,
    }, NULL,
    // &(bsgfx_TitleBar) {
    //    .name = "",
    //    .border_radius = BSMOD_DEFAULT_RADIUS,
    //    .font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16),
    //    .material_id = $bsmod_grey_120()->id,
    //    .button_hovering_material_id = $bsmod_red()->id,
    //    .button_icon_material_id = $bsmod_grey_120()->id,
    //    .button_unavailable_material_id = $bsmod_grey_148()->id,
    //    .button_material_id = $bsmod_grey_61()->id,
    //    .button_shadow_material_id = $bsmod_grey_112()->id,
    //}, 
    &(bsgfx_MenuTabBar) {
        .tabs_count = tabs.count,
        .tabs = tabs.data,
        .active_tab = &active_tab,
        .material_id = $bsmod_grey_61()->id,
        .outline_material_id = $bsmod_grey_61()->id,
        .shadow_material_id = $bsmod_grey_30()->id,
        .height = BSMOD_TAB_BAR_HEIGHT,
    });
}