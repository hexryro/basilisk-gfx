
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

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BSMOD_DIRECTORY_BACKGROUND_PADDING 32
#define BSMOD_DIRECTORY_BACKGROUND_DIMENSIONS ((bs_vec2) { 256, 512 })

bool _bsmod_instance_grid_menu_ = false;
bs_String* _bsmod_search_input_ = NULL;

static void _bsmod_onCloseGridMenu() {
    _bsmod_instance_grid_menu_ = false;
}

typedef enum {
    BSMOD_DIRECTORY_NONE,

    BSMOD_DIRECTORY_TYPES,
        BSMOD_DIRECTORY_PRIMITIVES,
        BSMOD_DIRECTORY_PREFABS,
        BSMOD_DIRECTORY_TILES,
        BSMOD_DIRECTORY_SPAWNERS,
    BSMOD_DIRECTORY_MATERIALS,
        BSMOD_DIRECTORY_MATERIALS_CACHED,
        BSMOD_DIRECTORY_MATERIALS_STORED,
        BSMOD_DIRECTORY_MATERIALS_OTHER,

    BSMOD_DIRECTORY_COUNT
} bsmod_Directory;

static bsmod_Directory _bsmod_selected_directory;
static void _bsmod_onHoverDirectoryWidget(bsgfx_Widget* widget) {
    if (bs_leftClickOnce()) {
        _bsmod_selected_directory = *(bsmod_Directory*)widget->params;
    }
}

static void _bsmod_directoryWidget(bs_List* widgets, const char* name, int indent, bsmod_Directory* directory) {
    const int z_offset = 4;
    // these icons are all different sizes so manually shifting them a couple of pixels
    const int minimize_icon_y_offset = 0;
    const int folder_icon_y_offset = 0;
    const float align_height = 16.0;

    bool is_selected = _bsmod_selected_directory == *directory;

    bs_pushBack(widgets, &(bsgfx_Widget) {
       // .name = "",
        .type = BSGFX_WIDGET_ICON,
        .align_height = align_height,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            .type = BSGFX_ICON_ATLAS,
            .name = "minimize",
            .hover = _bsmod_onHoverDirectoryWidget,
            .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
        },
        .params = directory,
        .offset = { indent, minimize_icon_y_offset, z_offset },
        .material_id = $bsmod_grey_138()->id,
        .advance_flags = BSGFX_WIDGET_ADVANCE_RIGHT,
    });

    bs_pushBack(widgets, &(bsgfx_Widget) {
       // .name = "",
        .type = BSGFX_WIDGET_ICON,
        .align_height = align_height,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            .type = BSGFX_ICON_ATLAS,
            .name = "folder",
            .hover = _bsmod_onHoverDirectoryWidget,
        },
        .params = directory,
        .offset = { indent, folder_icon_y_offset, z_offset },
        .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
        .advance_flags = BSGFX_WIDGET_ADVANCE_RIGHT,
    });


    if (is_selected) {
        // TODO: text rewrite
        /*
        bsgfx_Font* font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head;
        bs_vec2 text_size = bsgfx_textDimensions(font, name, strlen(name));
        bs_pushBack(widgets, &(bsgfx_Widget) {
            .type = BSGFX_WIDGET_BACKGROUND,
            .background = {
                .border_radius = BSMOD_DEFAULT_RADIUS,
                .size = text_size,
                .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
                .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_DITHER],
                .outline_material_id = $bsmod_grey_30()->id,
            },
            .offset = { indent, font->min_y_shift, z_offset },
            .material_id = $bsmod_grey_100()->id,
        });
        */
    }
        bs_pushBack(widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_STRING,
        .align_height = align_height,
        .string = {
            .value = name,
            .on_hover = _bsmod_onHoverDirectoryWidget,
        },
        .params = directory,
        .offset = { indent, 0, z_offset },
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN,
    });


    bsgfx_Widget* last_widget = bs_fetchLast(widgets);
    last_widget->advance_flags |= BSGFX_WIDGET_ADVANCE_DOWN | BSGFX_WIDGET_ADVANCE_RESET_X;
}

static void _bsmod_instanceDirectoryMenu(bs_vec3 center, bs_vec2 dimensions) {
    static bs_List widgets = { .unit_size = sizeof(bsgfx_Widget), .increment = 16 };
    widgets.count = 0;

    const int indent_0 = 8;
    const int indent_1 = 16;
    const int indent_2 = 40;

    static int select_position, select_size;

    const int search_height = 16;

    bs_pushBack(&widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_INPUT,
        .input = {
            .type = BSGFX_INPUT_STRING,
            .dimensions = { BSMOD_DIRECTORY_BACKGROUND_DIMENSIONS.x, search_height },
            .as_string = &_bsmod_search_input_,
            .placeholder_text = "Search...",
            .placeholder_text_material_id = $bsmod_grey_120()->id,
            .outline_material_id = $bsmod_grey_61()->id,
            .background_outline_material_id = $bsmod_grey_30()->id,
            .select_position = &select_position,
            .select_size = &select_size,
        },
        .material_id = $bsmod_grey_120()->id,
        .offset = { indent_0, -8.0, 0.0 },
        .advance_flags = BSGFX_WIDGET_ADVANCE_DOWN | BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Y,
    });

    bs_pushBack(&widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_BACKGROUND,
        .background = {
            .border_radius = BSMOD_DEFAULT_RADIUS,
            .size = BSMOD_DIRECTORY_BACKGROUND_DIMENSIONS,
            .material_id = $bsmod_grey_61()->id,
            .outline_material_id = $bsmod_grey_30()->id,
            .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI_COLOR],
        },
        .offset = { indent_0, 0.0, 0 },
        .advance_flags = 0,
    });

    struct {
        const char* name;
        int indent;
        bsmod_Directory id;
    } directories[BSMOD_DIRECTORY_COUNT] = {
         [BSMOD_DIRECTORY_TYPES] = { "Types", indent_1 },
             [BSMOD_DIRECTORY_PRIMITIVES] = { "Primitives", indent_2 },
             [BSMOD_DIRECTORY_PREFABS] = { "Prefabs", indent_2 },
             [BSMOD_DIRECTORY_TILES] = { "Tiles", indent_2 },
             [BSMOD_DIRECTORY_SPAWNERS] = { "Spawners", indent_2 },
         [BSMOD_DIRECTORY_MATERIALS] = { "Materials", indent_1 },
             [BSMOD_DIRECTORY_MATERIALS_CACHED] = { "Cached", indent_2 },
             [BSMOD_DIRECTORY_MATERIALS_STORED] = { "Stored", indent_2 },
             [BSMOD_DIRECTORY_MATERIALS_OTHER] = { "Other", indent_2 },
    };

    for (int i = 0; i < BSMOD_DIRECTORY_COUNT; i++) {
        if (!directories[i].name)
            continue;
        directories[i].id = i;

        _bsmod_directoryWidget(&widgets, directories[i].name, directories[i].indent, &directories[i].id);
    }

     /**
      Tabs
      */
    static bs_List tabs = { .unit_size = sizeof(bsgfx_MenuTab), .increment = 16 };
    static int active_tab;
    if (tabs.count == 0) {
        int material = $bsmod_grey_30()->id;

        bs_pushBack(&tabs, &(bsgfx_MenuTab) {.name = "Resources", });
        bs_pushBack(&tabs, &(bsgfx_MenuTab) {.name = "Console", });
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

     /**
      Instance
      */
    bool hovering = bsgfx_instanceWidgets((bsgfx_Menu) {
        .position = center,
        // .font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head, // TODO: text rewrite
        // .text_subtype = _bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS], // TODO: text rewrite
        .spacing = 4.0,
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
    }, 
    NULL,
    //&(bsgfx_TitleBar) {
    //   // .name = "Window",
    //    .border_radius = BSMOD_DEFAULT_RADIUS,
    //    .font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16),
    //    .material_id = $bsmod_grey_120()->id,
    //    .button_hovering_material_id = $bsmod_red()->id,
    //    .button_icon_material_id = $bsmod_grey_120()->id,
    //    .button_unavailable_material_id = $bsmod_grey_148()->id,
    //    .button_material_id = $bsmod_grey_61()->id,
    //    .button_shadow_material_id = $bsmod_grey_112()->id,
    //    .on_close = _bsmod_onCloseGridMenu,
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

    if (!_bsmod_.ui_blocked)
        _bsmod_.ui_blocked = hovering;
}

static bool _bsmod_instanceGridPreview(bsgfx_Widget* widget, bsgfx_GridParams grid) {
    bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);
    bool hovering = bs_rectangleVsPoint(grid.position, &widget->grid.size, &cursor);

    switch (_bsmod_selected_directory) {
    case BSMOD_DIRECTORY_PRIMITIVES: _bsmod_instancePrimitivePreview(widget, grid.position, grid.index, hovering); break;
    case BSMOD_DIRECTORY_PREFABS: _bsmod_instancePrefabPreview(widget, grid.position, grid.index, hovering); break;
    case BSMOD_DIRECTORY_TILES: _bsmod_instanceTilePreview(widget, grid.position, grid.index, hovering); break;
    default:
        return false;
    }

    if (hovering) {
        bsgfx_instantiateQuad(
            bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            bsgfx_matrix(
                BS_V3(grid.position->x, grid.position->y, 50.0),
                BS_V3(widget->grid.size.x, widget->grid.size.y, 0.0)
            ),
            $BSMOD_ATLAS_UI_grid_hover()->coords,
            0, 0, 0);
    }

    return true;
}

typedef struct {
    int id;
    int category;
} bsmod_IdCategory;

typedef struct {
    bsmod_SideMenuTabId tab_id;
    bsgfx_InstanceSubtype* subtype2;
    bsmod_IdCategory* sorted_ids;
    bs_U32 source_id;
    bs_U32 object_id;
} bsmod_GridPreviewParams;

static void _bsmod_checkHoverGrid(bsgfx_Widget* widget, bsgfx_GridParams* grid) {
    bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);

    bsmod_GridPreviewParams* params = widget->params;
    bool hovering = bs_rectangleVsPoint(grid->position, &widget->grid.size, &cursor);

    if (hovering) {
        if (bs_leftClickOnce()) {
            _bsmod_.dragging_id = grid->index;

            _bsmod_setSideMenuTab(params->tab_id, (bsmod_GridClickParams) {
                .atlas_id = grid->index,
            });
        }

        if (bs_leftClickUpOnce()) {
            _bsmod_.dragging_id = -1;
        }

        bsgfx_instantiateQuad(
            bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            bsgfx_matrix(
                BS_V3(grid->position->x, grid->position->y, 50.0),
                BS_V3(widget->grid.size.x, widget->grid.size.y, 0.0)
            ),
            $BSMOD_ATLAS_UI_grid_hover()->coords,
            0, 0, 0);
    }
    else if (_bsmod_.dragging_id == grid->index) {
        _bsmod_.dragging_object_id = params->object_id;
        _bsmod_.dragging_subtype = params->subtype2;
    }
}

static bool _bsmod_instanceAtlasPreview(bsgfx_Widget* widget, bsgfx_GridParams grid) {

    bsmod_GridPreviewParams* params = widget->params;
    grid.index = params->sorted_ids[grid.index].id;

    bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, params->object_id)->atlas;

    // special case
    if (params->object_id == BSMOD_ATLAS_MATERIAL_ICONS) {
        static int last_category = 0;

        bsgfx_Material* material = bsgfx_queryMaterial(atlas->unmapped[grid.index].name);
        if (!material)
            return false;

        if (last_category != material->category) {
            const char* category_name = bsgfx_materialCategoryName(material->category);
            if (category_name) {
                // TODO: text rewrite
                /*
                bsgfx_Font* font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->font;
                grid.position->y -= font->height;
                grid.position->x = grid.start.x;
                bs_vec2 category_name_dimensions;
                bsgfx_instanceText(_bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS], font, &(bsgfx_Text) {
                    .position = { grid.position->x, grid.position->y, 70.0, 1 },
                    .scale = 16.0,
                    .material_id = $bsmod_grey_30()->id,
                }, &category_name_dimensions, category_name, strlen(category_name));
                */

                grid.position->y -= widget->grid.size.y;
                //position->x = 0.0;
            }
        }

        last_category = material->category;
    }

    bsgfx_instantiateQuad(
        params->subtype2,
        bsgfx_matrix(
            BS_V3(grid.position->x, grid.position->y, 60.0),
            BS_V3(widget->grid.size.x, widget->grid.size.y, 0.0)
        ),
        bs_atlasCoordinates(atlas, grid.index),
        0, 0, 0);

    _bsmod_checkHoverGrid(widget, &grid);

    return true;
}

static bool _bsmod_instanceImageArrayPreview(bsgfx_Widget* widget, bsgfx_GridParams grid) {
    bsmod_GridPreviewParams* params = widget->params;
    grid.index = params->sorted_ids[grid.index].id;

    bs_Image* image = bs_fetch(BSMOD_IMAGES, params->object_id)->image;
    bs_mat4x3 matrix = bsgfx_matrix(
        BS_V3(grid.position->x, grid.position->y, 60.0),
        BS_V3(widget->grid.size.x, widget->grid.size.y, 0.0)
    );
    matrix.f[8] = grid.index;
    bsgfx_instantiateQuad(
        params->subtype2,
        matrix,
        BS_V4(0.0, 0.0, 1.0, 1.0),
        0, 0, 0);

    _bsmod_checkHoverGrid(widget, &grid);

    return true;
}

static int _bsmod_compareCategories(const bsmod_IdCategory* a, const bsmod_IdCategory* b) {
    if (a->category == b->category) return 0;
    else if (a->category < b->category) return -1;
    else return 1;
}

BSMODAPI void _bsmod_instanceGridMenu(bs_vec3 position, bs_vec2 dimensions) {
    _bsmod_instanceDirectoryMenu(position, dimensions);

    bs_vec2 size = { dimensions.x - (BSMOD_DIRECTORY_BACKGROUND_DIMENSIONS.x + BSMOD_DIRECTORY_BACKGROUND_PADDING), dimensions.y };

    static int scroll;

    bsmod_GridPreviewParams params = {
        .subtype2 = NULL,
    };
    bsgfx_Widget widget = {
        .type = BSGFX_WIDGET_GRID,
        .grid = {
            .always_active = true,
            .total_size = size,
            .count = BSGFX_PRIMITIVE_TYPE_COUNT,
            .action = _bsmod_instanceGridPreview,
        },
        .params = &params,
    };
    _bsmod_scrollbar(&scroll, &widget.grid.scrollbar);

    widget.grid.count = 0;
    widget.grid.action = NULL;
    params.subtype2 = NULL;

    bs_Atlas* atlas = NULL;
    bs_Image* image_array = NULL;
    float scale = 1.0;
    switch (_bsmod_selected_directory) {
  //  case BSMOD_DIRECTORY_PREFABS: widget.grid.count = bsgfx_prefabModel()->meshes_count; break;
  //  case BSMOD_DIRECTORY_TILES: widget.grid.count = bsgfx_tileTypes()->count; break;
    case BSMOD_DIRECTORY_PREFABS:
        atlas = bs_fetch(BSMOD_ATLASES, params.object_id = BSMOD_ATLAS_PREFAB_ICONS)->head;
        widget.grid.action = _bsmod_instanceAtlasPreview;
        widget.grid.count = atlas->count;
        params.subtype2 = _bsmod_subtypes_[BSMOD_SUBTYPE_PREFAB_ICON];

        break;
    case BSMOD_DIRECTORY_PRIMITIVES:
        //bs_Atlas* atlas = bs_fetch(BSMOD_ATLAS_MATERIAL_ICONS)->head;
        atlas = bs_fetch(BSMOD_ATLASES, params.object_id = BSMOD_ATLAS_PRIMITIVE_ICONS)->head;
        widget.grid.count = atlas->count;
        widget.grid.action = _bsmod_instanceAtlasPreview;
        params.subtype2 = _bsmod_subtypes_[BSMOD_SUBTYPE_PRIMITIVE_ICON];

        break;
    case BSMOD_DIRECTORY_TILES: 
        image_array = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_TILE)->image;
        widget.grid.count = image_array->num_indices;
        widget.grid.action = _bsmod_instanceImageArrayPreview;
        widget.grid.padding = 8.0;
        params.subtype2 = _bsmod_subtypes_[BSGFX_SUBTYPE_TILE];
        params.object_id = BSGFX_IMAGE_TILE;
        scale = 2.0;
        break;
    case BSMOD_DIRECTORY_MATERIALS_CACHED: 
        bs_Object* atlas_object = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_MATERIAL_ICONS);

        if (atlas_object) {
            widget.grid.count = atlas_object->atlas->count;
            widget.grid.action = _bsmod_instanceAtlasPreview;
            params.subtype2 = _bsmod_subtypes_[BSMOD_SUBTYPE_MATERIAL_ICON];
            params.tab_id = BSMOD_TAB_MATERIAL;
            params.object_id = BSMOD_ATLAS_MATERIAL_ICONS;
        }
        
        break;
    default:
        return;
    }

    if (widget.grid.count > 0) {
        if (atlas) {
            widget.grid.size = BS_V2(atlas->mapped[0].w, atlas->mapped[0].h);
            assert(atlas->count == widget.grid.count);
        }
        else if (image_array) {
            widget.grid.size = BS_IV2_TO_V2(image_array->dim);
            assert(image_array->num_indices == widget.grid.count);
        }

        widget.grid.size.x *= scale;
        widget.grid.size.y *= scale;

        params.sorted_ids = _alloca(widget.grid.count * sizeof(bsmod_IdCategory));
        for (int i = 0; i < widget.grid.count; i++) {
            params.sorted_ids[i] = (bsmod_IdCategory){
                .id = i,
                .category = atlas ? atlas->unmapped[i].category : 0,
            };
        }

        qsort(params.sorted_ids, widget.grid.count, sizeof(bsmod_IdCategory), _bsmod_compareCategories);
    }

    position.x += BSMOD_DIRECTORY_BACKGROUND_DIMENSIONS.x + BSMOD_DIRECTORY_BACKGROUND_PADDING;
    position.z += 10;

    bool hovering = bsgfx_instanceWidgets((bsgfx_Menu) {
        .position = position,
        // .text_subtype = _bsmod_subtypes_[BSMOD_SUBTYPE_FONT_CONSOLAS], // TODO: text rewrite
        // .font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head, // TODO: text rewrite
        .spacing = 16.0,
        .widgets = &widget,
        .widgets_count = 1,
        .background_material_id_0 = $blank_material()->id,
        .background_material_id_1 = $blank_material()->id,
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
