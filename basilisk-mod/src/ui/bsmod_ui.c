
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

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <bsmod_internal.h>
#include <bsmod_cache.h>

BSMODAPI void _bsmod_scrollbar(const int* scroll, bsgfx_Scrollbar* out) {
    *out = (bsgfx_Scrollbar) {
        .value = scroll,
        .substeps_count = 4,
        .padding = 8,
        .width = 16.0,
        .border_radius = BSMOD_DEFAULT_RADIUS,

        .material = $bsmod_grey_138()->id,
        .outline_material = $bsmod_grey_30()->id,
        .background_material = $bsmod_grey_61()->id,

        .button_icon_material = $bsmod_grey_61()->id,
        .button_background_material = $bsmod_grey_138()->id,
        .button_outline_material = $bsmod_grey_30()->id,
    };
}

BSMODAPI void _bsmod_dividerWidget(float width, int indent, bsgfx_Widget* out) {
    *out = (bsgfx_Widget) {
       // .name = "",
        .type = BSGFX_WIDGET_ICON,
        .offset.x = indent,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .name = "white",
            .material_id = $context_menu_grey_text_material()->id,
            .scale = { width - indent * 2 - 1, 1 },
        }
    };
}

BSMODAPI void _bsmod_iconWidget(const bsgfx_AtlasCache* cache, float align_height, bs_vec3 offset, bs_U32 advance_flags, bsgfx_Widget* out) {
    *out = (bsgfx_Widget) {
        .type = BSGFX_WIDGET_ICON,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            .type = BSGFX_ICON_ATLAS,
            .name = cache->name, // todo skip query
            .material_id = $white_material()->id,
        },
        .advance_flags = advance_flags,
        .material_id = $white_material()->id,
        .align_height = align_height,
        .offset = offset,
    };
}

BSMODAPI void _bsmod_pushInputWidget(
    bs_List* widgets,
    void* value,
    bs_vec3 offset, 
    float width, 
    int name_padding, 
    bool skip_advance, 
    bool is_last, 
    bool has_buttons,
    const char* name) 
{
    static int select_position, select_size;
    if (has_buttons) {
        const int button_padding = 2;
        bsgfx_AtlasCache* increment = $BSMOD_ATLAS_UI_increment();
        bsgfx_Widget* increment_button = bs_pushBack(widgets, &(bsgfx_Widget) {
            //.name = "",
            .type = BSGFX_WIDGET_ICON,
            .icon = {
                .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
                .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
                .type = BSGFX_ICON_ATLAS,
                .name = "increment",
                .material_id = $bsmod_grey_120()->id,
                //.placement = BSGFX_ICON_PLACE_BELOW
                //.hover = _bsmod_onHoverDirectoryWidget,
            },
            .advance_flags = BSGFX_WIDGET_ADVANCE_RIGHT,
            .material_id = $bsmod_grey_120()->id,
        });
        bs_v3Add(&offset, &BS_V3(width - increment->size.x - button_padding, -button_padding, 10.0), &increment_button->offset);

        bsgfx_Widget* decrement_button = bs_pushBack(widgets, &(bsgfx_Widget) {
           // .name = "",
            .type = BSGFX_WIDGET_ICON,
            .icon = {
                .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
                .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
                .type = BSGFX_ICON_ATLAS,
                .name = "increment",
                .material_id = $bsmod_grey_120()->id,
                //.placement = BSGFX_ICON_PLACE_BELOW,
                .flipped = true,
                //.hover = _bsmod_onHoverDirectoryWidget,
            },
            .advance_flags = BSGFX_WIDGET_ADVANCE_RIGHT,
            .material_id = $bsmod_grey_120()->id,
        });
        bs_v3Add(&offset, &BS_V3(width - increment->size.x - button_padding, -BSMOD_INPUT_HEIGHT + increment->size.y + button_padding, 10.0), &decrement_button->offset);
    }

    bs_pushBack(widgets, &(bsgfx_Widget) {
       // .name = name,
        .type = BSGFX_WIDGET_INPUT,
        .offset = offset,
        .input = {
            .dimensions = { width, BSMOD_INPUT_HEIGHT },
            .as_void = value,
            .placeholder_text = "",
            .placeholder_text_material_id = $bsmod_grey_120()->id,
            .outline_material_id = $bsmod_grey_40()->id,
            .background_outline_material_id = $bsmod_grey_30()->id,
            .select_position = &select_position,
            .select_size = &select_size,
        },
        .advance_flags = is_last ? BSGFX_WIDGET_ADVANCE_RESET_X : BSGFX_WIDGET_ADVANCE_RIGHT,
        .material_id = $bsmod_grey_120()->id,
    });
}

BSMODAPI void _val_bsmod_pushVecNWidget(bs_List* widgets, const char* name, bs_vec3 offset, float width, float* v, int n) {
    BSMOD_VALIDATE(n <= 4,,);

    _bsmod_pushVecNWidget(widgets, name, offset, width, v, n);
}

BSMODAPI void _bsmod_pushVecNWidget(bs_List* widgets, const char* name, bs_vec3 offset, float width, float* v, int n) {
    const char* xyzw[] = { "x", "y", "z", "w" };

    const float align_height = 16;

    if (name) {
        bs_pushBack(widgets, &(bsgfx_Widget) {
            .type = BSGFX_WIDGET_STRING,
            .string.value = name,
            .offset = offset,
            .advance_flags = 0,
            .align_height = align_height,
        });
        offset.x += 96.0;
    }

    for (int i = 0; i < n; i++) {
        bs_pushBack(widgets, &(bsgfx_Widget) {
            .type = BSGFX_WIDGET_STRING,
            .offset = offset,
            .string = {
                .value = xyzw[i]
            },
            .advance_flags = BSGFX_WIDGET_ADVANCE_RIGHT,
            .align_height = align_height,
        });

        bs_pushBack(widgets, &(bsgfx_Widget) {
            .type = BSGFX_WIDGET_INPUT,
            .input = {
                .type = BSGFX_INPUT_FLOAT,
                .outline_material_id = $bsmod_grey_40()->id,
                .background_outline_material_id = $bsmod_grey_30()->id,
                .dimensions = { width, 16.0 },
                .as_float = v + i,
            },
            .offset = offset,
            .advance_flags = i == (n - 1) ? BSGFX_WIDGET_ADVANCE_RESET_X | BSGFX_WIDGET_ADVANCE_DOWN : BSGFX_WIDGET_ADVANCE_RIGHT,
            .align_height = align_height,
        });
        offset.x += 4.0;
    }
}

#define BSMOD_DIRECTORY_BACKGROUND_PADDING 8
#define BSMOD_DIRECTORY_BACKGROUND_DIMENSIONS ((bs_vec2) { 256, 512 })

BSMODAPI void _bsmod_instanceBackgroundMenu(bs_vec3 position, bs_vec2 dimensions) {
    const int width = 64;
    static int scroll;
    static bs_List tabs = { .unit_size = sizeof(bsgfx_MenuTab), .increment = 16 };
    static int active_tab;
    if (tabs.count == 0) {
        int material = $bsmod_grey_30()->id;
    }

    for (int i = 0; i < tabs.count; i++) {
        bsgfx_MenuTab* tab = bs_fetchUnit(&tabs, i);
        if (active_tab == i) {
            tab->material_id = $bsmod_grey_120()->id;
            tab->shadow_material_id = $bsmod_grey_61()->id;
            tab->outline_material_id = $bsmod_grey_148()->id;
        }
        else {

            tab->material_id = $context_menu_title_bar_material()->id;
            tab->outline_material_id = $bsmod_grey_148()->id;
            tab->shadow_material_id = $bsmod_grey_61()->id;
        }
    }

    const int padding = 24.0;

    position.z -= 13.0;
    position.x -= padding;
    position.y += padding;
    position.y += BSMOD_TAB_BAR_HEIGHT;
    dimensions.x += BSMOD_GRID_SIDE_MENU_SPACE;
    dimensions.x += padding * 2;
    dimensions.y += padding * 2;
    dimensions.y += BSMOD_TAB_BAR_HEIGHT;

    bool hovering = bsgfx_instanceWidgets((bsgfx_Menu) {
        .position = position,
        //.text_subtype = _bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS], // TODO: text rewrite
        //.font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head, // TODO: text rewrite
        .spacing = 4.0,
        .widgets = NULL,
        .widgets_count = 0,
        .background_material_id_0 = $white_material()->id,
        .untextured = {
            .dimensions = dimensions,
            .auto_scale_width = true,
            .border_id = -1,
            // .has_shadow = true,
        },
        .blocked = false,
        .border_radius = BSMOD_DEFAULT_RADIUS,
        //.shadow_material_id = $bsmod_grey_61()->id,
        //.outline_material_id = $bsmod_grey_148()->id,
    }, & (bsgfx_TitleBar) {
        .name = "Window",
        .border_radius = BSMOD_DEFAULT_RADIUS,
        //.font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head, // TODO: text rewrite
        .material_id = $white_material()->id,
        .button_hovering_material_id = $bsmod_red()->id,
        .button_icon_material_id = $bsmod_grey_120()->id,
        .button_unavailable_material_id = $bsmod_grey_148()->id,
        .button_material_id = $bsmod_grey_61()->id,
        .button_shadow_material_id = $bsmod_grey_112()->id,
    }, NULL);

    if (!_bsmod_.ui_blocked)
        _bsmod_.ui_blocked = hovering;
}

static void _bsmod_instanceDraggingIcon() {
    bsmod_DraggingParams params = { 0 };
    bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);

    bs_Atlas* atlas_ui = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas;
    bsgfx_AtlasCache* cache = $BSMOD_ATLAS_UI_prohibition();

    bsgfx_instantiateQuad(
        bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
        bsgfx_matrix(
            BS_V3(cursor.x, cursor.y, 101.0),
            BS_V3(cache->size.x, cache->size.y, 0.0)
        ),
        cache->coords,
        0, 0, 0);

    switch (_bsmod_.dragging_object_id) {
    case BSMOD_ATLAS_MATERIAL_ICONS: _bsmod_onDragMaterial(params); break;
    case BSMOD_ATLAS_PREFAB_ICONS: _bsmod_onDragPrefab(params); break;
    case BSMOD_ATLAS_PRIMITIVE_ICONS: _bsmod_onDragPrimitive(params); break;
    case BSGFX_IMAGE_TILE:  _bsmod_onDragTile(params); break;
    default:
        return;
    }

    if (bs_inputDown(BS_LEFT_MOUSE_BUTTON)) {
        bs_infoF("Drop\n");
        _bsmod_.dragging_id = -1;
        _bsmod_.dragging_object_id = 0;
        _bsmod_.dragging_subtype = -1;
    }
}

BSMODAPI void _bsmod_renderBillboards(bs_RendererScope* scope, bs_Queue* queue) {
    bs_Pipeline* pipeline;
    bs_PipelineHash hash;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsmod_billboard();
    hash.shaders[1] = $fs_bsmod_billboard();
    hash.skip_depth_test = true;
    bsgfx_requiredForTransparency(&hash);

    if (bs_pipeline(scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        struct {
            bs_mat4 camera;
            bs_mat4 view;

        } push_const = {
            .camera = bsgfx_app()->camera.result,
            .view = bsgfx_app()->camera.view,
        };

        bs_beginCommentN(queue, BS_CONSTANT_STRING("Billboards"));

        bs_pushConstant(queue, pipeline, 0, sizeof(push_const), &push_const);
        bsgfx_renderSubtype(queue, _bsmod_subtypes_[BSMOD_SUBTYPE_BILLBOARD], pipeline);

        bs_endComment(queue);
    }
}

static void _bsmod_instanceBillboards() {
    //_bsmod_.hovering.billboard = false;
    _bsmod_instanceLightBillboards();
}

BSMODAPI void _bsmod_instanceUI() {
    _bsmod_.ui_blocked = false;
    static bool right_clicked;
    static bs_vec2 position;

    if (bs_inputUpOnce(BS_RIGHT_MOUSE_BUTTON)) {
        right_clicked = true;
        position = bs_windowCursorPosition(bs_scope()->context);
    }

    if (bs_inputDown(BS_LEFT_MOUSE_BUTTON) || bs_inputDown(BS_MIDDLE_MOUSE_BUTTON))
        right_clicked = false;

    if (right_clicked) {
        bs_vec3 p = BS_V3(position.x, position.y, 20.0);
        bs_vec2 s = { 200.0, 300.0 };

        float d = p.y - s.y;

        if (d < 0.0)
            p.y -= d;

        if (_bsmod_.selected_type == BSGFX_TYPE_TILE && _bsmod_.selected_tiles.count == 1)
            _bsmod_instanceTileContextMenu(p, s);
    }

    if (bs_inputDown(BS_KEY_ALT) && !bs_inputDown(BS_KEY_LEFT_CONTROL)) {
        if (bs_inputDownOnce(BS_KEY_1)) {
            _bsmod_instance_grid_menu_ = true;

        }

        for (int i = BS_KEY_2; i < BS_KEY_9; i++) {
            if (bs_inputDownOnce(i)) {
                _bsmod_instance_grid_menu_ = false;
                //bs_disableUserInputs(false);
            }
        }
    }

    if (_bsmod_.dragging_subtype >= 0)
        _bsmod_instance_grid_menu_ = false;

    if (_bsmod_instance_grid_menu_) {
       // bs_disableUserInputs(true);

        bs_vec2 dimensions = { 1600.0, 900.0 };
        bs_ivec2 resolution = bs_resolution(bs_scope()->context);
        bs_vec3 center = {
            (int)((resolution.x - dimensions.x) / 2.0),
            (int)((resolution.y + dimensions.y) / 2.0),
            25.0
        };

      //  _bsmod_instanceBackgroundMenu(center, dimensions);

        const int side_menu_width = BSGFX_SIDE_MENU_WIDTH;
        dimensions.x -= side_menu_width;
        _bsmod_instanceGridMenu(center, dimensions);

        center.x += dimensions.x;
        center.x += BSMOD_GRID_SIDE_MENU_SPACE;
        _bsmod_instanceSideMenu(center, BS_V2(side_menu_width, dimensions.y));
    }

    if (_bsmod_.dragging_subtype >= 0) {
        _bsmod_instanceDraggingIcon();
    }

    _bsmod_instanceBillboards();
}
