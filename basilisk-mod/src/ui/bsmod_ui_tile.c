
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
   * Instance Menu
   *============================================================================*/

static void _bsmod_pushDividerWidget(bs_List* widgets, bs_vec3 offset) {
    const int divider_indent = 8;
    bs_pushBack(widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_BACKGROUND,
        .background = {
            .size = { BSGFX_SIDE_MENU_WIDTH - divider_indent * 2.0, 1.0 },
            .material_id = $bsmod_grey_30()->id,
            .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI_COLOR],
        },
        .offset = { divider_indent, offset.y, offset.z + 1 },
        // .align_height = height,
    });
}

static void _bsmod_pushDropdownWidget(bs_List* widgets, bs_vec3 offset) {
    const int height = 24;

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_ICON,
        .icon = {
            .atlas = bs_fetch(BSMOD_ATLASES, BSMOD_ATLAS_UI)->atlas,
            .atlas_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
            .type = BSGFX_ICON_ATLAS,
            .name = "minimize",
            .material_id = BSMOD_UI_BASE_TEXT_MATERIAL()->id,
        },
        .advance_flags = BSGFX_WIDGET_ADVANCE_RIGHT | BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_X,
        .align_height = height,
        .offset = offset,
    });

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .type = BSGFX_WIDGET_STRING,
        .string = {
            .value = "Test",
        },
        .align_height = height,
    });

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .advance_flags = BSGFX_WIDGET_ADVANCE_RESET_X | BSGFX_WIDGET_ADVANCE_APPLY_OFFSET,
        .offset = { 0.0, -height, 0.0 },
    });

    _bsmod_pushDividerWidget(widgets, BS_V3(0.0, offset.y, offset.z));
}

BSMODAPI void _bsmod_pushTileMenuWidgets(bs_List* widgets, bs_vec2 background_size) {
    const int indent = 24;

    if (_bsmod_.selected_ids.count <= 0) {
        bs_pushBack(widgets, &(bsgfx_Widget) {
            .type = BSGFX_WIDGET_STRING,
            .string = {
                .value = "No tiles selected",
            },
            .offset.x = indent,
        });
        return;
    }

    bs_pushBack(widgets, &(bsgfx_Widget) {
        .advance_flags = BSGFX_WIDGET_ADVANCE_APPLY_OFFSET,
        .offset = { 0, -8.0, 0.0 },
    });

    _bsmod_pushDividerWidget(widgets, BS_V3(0.0, 0.0, 0.0));

    for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
        bsgfx_Tile* tile = bsgfx_get(BSGFX_TYPE_TILE, i);

        _bsmod_pushDropdownWidget(widgets, BS_V3(indent, 0, 0));
    }
}



  /*==============================================================================
   * Grid Icon
   *============================================================================*/

BSMODAPI bool _bsmod_instanceTilePreview(bsgfx_Widget* widget, bs_vec2* position, int id, bool hovering) {
    bs_Image* image = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_TILE)->image;
    bs_ImageIndex* index = image->indices + id;

    if (_bsmod_search_input_->len > 0 && strstr(index->name, _bsmod_search_input_->value) == NULL) {
        return false;
    }

    bs_mat4x3 transform = bsgfx_matrix(BS_V3(position->x, position->y, 0.0), BS_V3(widget->grid.size.x, widget->grid.size.y, 0));
    transform.f[8] = id;
    bsgfx_instantiateQuad(bsgfx_subtypes()[BSGFX_SUBTYPE_TILE_ICON], transform, BS_V4(0, 0, 1, 1), 0, 0, $white_material()->id);

    return true;
}



  /*==============================================================================
   * Dragging Icon
   *============================================================================*/

BSMODAPI void _bsmod_onDragTile(bsmod_DraggingParams params) {
    BS_WARN("Not implemented");
    /*
    if (_bsmod_.hovering.tile < 0 || _bsmod_.hovering.primitive < 0)
        return;

    bsgfx_Primitive* hovering_primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, _bsmod_.hovering.primitive);

    bs_ivec2 coords;
    bsgfx_tileCoordinate(hovering_primitive, _bsmod_.hovering.tile_axis, _bsmod_.hovering.tile, &coords);

    bs_vec3 tile_position;
    bsgfx_tilePosition(hovering_primitive, _bsmod_.hovering.tile_axis, coords.x, coords.y, &tile_position);

    bs_vec4 rotation;
    bsgfx_tileRotation(_bsmod_.hovering.tile_axis, &rotation);

    bs_vec3 euler_rotation;
    bsgfx_tileEulerRotation(_bsmod_.hovering.tile_axis, &euler_rotation);

    bs_qMulQ(&hovering_primitive->rotation, &rotation, &rotation);

    bs_mat4 matrix = BS_MAT4_IDENTITY;
    bs_m4Translate(&matrix, &tile_position, &matrix);
    bs_m4Rotate(&matrix, &rotation, &matrix);

    bs_Object* tile_image_object = bs_fetch(BSGFX_IMAGES, BSGFX_IMAGE_TILE);
    if (!tile_image_object)
        return;

    assert(_bsmod_.dragging_id >= 0 && _bsmod_.dragging_id < tile_image_object->image->num_indices);

    if (bs_leftClickUpOnce()) {
        if (_bsmod_isSelected(BSMOD_TILE_IDS, BSGFX_TYPE_TILE, _bsmod_.hovering.tile)) {
            for (int i = 0; i < _bsmod_.selected_tiles.count; i++) {
                int id = *(int*)bs_fetchUnit(&_bsmod_.selected_tiles, i);

                for (int j = 0; j < _bsmod_.selected_ids.count; j++) {
                    int existing_id = *(int*)bs_fetchUnit(&_bsmod_.selected_ids, j);
                    bsgfx_Tile* tile = bsgfx_get(BSGFX_TYPE_TILE, existing_id);
                    if (id == tile->index) {
                        bsgfx_RawTile* raw_tile = bsgfx_getRaw(BSGFX_TYPE_TILE, existing_id);
                        raw_tile->texture_hash = tile_image_object->image->indices[_bsmod_.dragging_id].name_hash;
                        goto next;
                    }
                }

                bsgfx_tileCoordinate(hovering_primitive, _bsmod_.hovering.tile_axis, id, &coords);

                _bsmod_add(BSGFX_TYPE_TILE, &(bsgfx_RawTile) {
                    .coords = coords,
                    .texture_hash = tile_image_object->image->indices[_bsmod_.dragging_id].name_hash,
                    .primitive = hovering_primitive->guid,
                    .axis = _bsmod_.hovering.tile_axis,
                });

            next:
                void;
            }
        }
        else {
            bs_warnF("Tile is not selected\n");
        }

        _bsmod_saveTypeN(BSGFX_TYPE_TILE, "Created %d tiles", _bsmod_.selected_tiles.count);
        _bsmod_deselectAll();
    }
    */
}
