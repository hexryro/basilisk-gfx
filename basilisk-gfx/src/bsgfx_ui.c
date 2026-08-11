
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
#include <bsgfx_cache.h>

#define BSGFX_DEBUG_MENU_INPUT_COLOR (bs_RGBA) { 32, 32, 40, 255 }
#define BSGFX_DEBUG_MENU_INPUT_SELECTED_COLOR (bs_RGBA) { 24, 24, 32, 255 }

#define BSGFX_DEBUG_URL_COLOR (bs_RGBA) { 70, 80, 200, 255 }
#define BSGFX_DEBUG_URL_SELECTED_COLOR (bs_RGBA) { 100, 110, 255, 255 }



  /*==============================================================================
   * UI
   *============================================================================*/

static inline bs_mat4x3 _bsgfx_roundedMatrix(bs_vec3 position, bs_vec3 scale, bs_vec4 radii) {
	return (bs_mat4x3) {
		scale.x, radii.x, radii.y,
		radii.z, scale.y, 0.0,
		radii.w, 0.0, scale.z,
		position.x, position.y, position.z,
	};
}

static void _bsgfx_instanceBackground(
	int subtype,
	bs_vec3 position,
	bs_vec2 dimensions,
	bs_vec4 border_radii,
	int material_id,
	int outline_material_id,
	int shadow_material_id)
{
	bs_vec4 background_radii = border_radii;
	background_radii.z = background_radii.w = 0.0;

	bs_mat4x3 transform = _bsgfx_roundedMatrix(position, BS_V3(dimensions.x, dimensions.y, 0.0), BS_V4(0.0, 0.0, 0.0, 0.0));

	if (material_id) {
		_bsgfx_instanceQuad(subtype, transform, BS_V4(0.0, 0.0, 0.0, 0.0), 0, 0, material_id);
	}

	/**
	 Shadow
	 */
	if (shadow_material_id) {
		const float shadow_width = outline_material_id ? 2.0 : 1.0;
		bs_vec3 shadow_offset_1 = BS_V3(-shadow_width, -shadow_width, -2);
		bs_vec3 shadow_position;
		bs_v3Add(&position, &shadow_offset_1, &shadow_position);
		bs_vec3 shadow_size = BS_V3(dimensions.x + shadow_width * 2.0, dimensions.y + shadow_width * 2.0, 0.0);

		transform = _bsgfx_roundedMatrix(shadow_position, shadow_size, border_radii);
		_bsgfx_instanceQuad(subtype, transform, BS_V4(0.0, 0.0, 0.0, 0.0), 0, 0, shadow_material_id);
	}

	/**
	 Outline
	 */
	if (outline_material_id) {
		const float shadow_width = 1.0;
		bs_vec3 shadow_offset_2 = BS_V3(-shadow_width, -shadow_width, -1);
		bs_vec3 shadow_position;
		bs_v3Add(&position, &shadow_offset_2, &shadow_position);
		bs_vec3 shadow_size = BS_V3(dimensions.x + shadow_width * 2.0, dimensions.y + shadow_width * 2.0, 0.0);

		transform = _bsgfx_roundedMatrix(shadow_position, shadow_size, border_radii);
		_bsgfx_instanceQuad(subtype, transform, BS_V4(0.0, 0.0, 0.0, 0.0), 0, 0, outline_material_id);
	}
}

bool _bsgfx_rectangleVsPointExpand(const bs_vec2* position, const bs_vec2* dimensions, const bs_vec2* point, float expand) {
	// expand *= BSGFX_PIXEL_SCALE;

	bs_vec2 new_position, new_dimensions;

	bs_v2AddS(position, -expand, &new_position);
	bs_v2AddS(dimensions, expand * 2.0, &new_dimensions);

	return bs_rectangleVsPoint(position, dimensions, point);
}

static inline float _bsgfx_textHeight() {
	return 0.0;
	//bsgfx_Font* font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head;
	//return font->height;
}

/*
static inline float _bsgfx_instanceTextField(int subtype, bs_vec3* position, char* text, int material_id) {
	return 0.0;
	bsgfx_Font* font = bs_fetch(BSGFX_FONTS, BSGFX_FONT_ARIAL_16)->head;
	//position->y -= _bsgfx_textHeight();

	return _bsgfx_instanceText(subtype, font, &(bsgfx_Text) {
		.position = { position->x, position->y, position->z + 1, 1 },
		.scale = font->size,
		.material_id = material_id,
	}, text, strlen(text)).x;
}

static inline float _bsgfx_instanceTextFieldV(int subtype, bs_vec3* position, int material_id, const char* format, va_list args) {
	char formatted[256];
	vsnprintf(formatted, sizeof(formatted), format, args);
	return _bsgfx_instanceTextField(subtype, position, formatted, material_id);
}

float _bsgfx_instanceTextFieldF(int subtype, bs_vec2* position, int material_id, const char* format, ...) {
	va_list args;
	va_start(args, format);
	float width = _bsgfx_instanceTextFieldV(subtype, position, material_id, format, args);
	va_end(args);
	return width;
}
*/

static void _bsgfx_instanceScrollbar(bsgfx_Scrollbar* scrollbar, bs_vec3 position, int max_scroll, int scroll, float total_height) {
	position.x -= scrollbar->width;

	 /**
	  Buttons
	  */
	bool draw_buttons = scrollbar->button_icon_material > 0;
	if (draw_buttons) {
		total_height -= scrollbar->width * 2.0;

		 /**
		  Icons
		  */
	//	bsgfx_AtlasCache* button = $BSMOD_ATLAS_UI_scrollbar_button();
	//	position.y -= scrollbar->width;
	//	bs_vec3 icon_position = {
	//		position.x + (scrollbar->width - button->size.x) / 2.0,
	//		position.y + (scrollbar->width - button->size.y) / 2.0,
	//		position.z + BSGFX_BACKGROUND_Z_COUNT
	//	};

		 /**
		  Backgrounds
		  */
		_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
			BS_V3(position.x, position.y, position.z + 2),
			BS_V2(scrollbar->width, scrollbar->width),
			BS_V4(scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius),
			scrollbar->button_background_material,
			scrollbar->button_outline_material,
			0);

		_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
			BS_V3(position.x, position.y - total_height - scrollbar->width, position.z + 2),
			BS_V2(scrollbar->width, scrollbar->width),
			BS_V4(scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius),
			scrollbar->button_background_material,
			scrollbar->button_outline_material,
			0);

	//	bs_mat4x3 icon_matrix = _bsgfx_roundedMatrix(icon_position, bs_v3V2(button->size, 0.0), bs_v4V1(0.0));
	//	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI], icon_matrix, button->coords, 0, 0, scrollbar->button_icon_material);
	//	icon_matrix.v[3].y -= total_height + scrollbar->width;
	//	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI], icon_matrix, bs_flipUV(button->coords), 0, 0, scrollbar->button_icon_material);
	}

	 /**
	  Scrollbar background
	  */
	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(position.x, position.y - total_height, position.z + 1),
		BS_V2(scrollbar->width, total_height),
		BS_V4(scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius),
		scrollbar->background_material,
		0,
		0);

	 /**
	  Scrollbar
	  */
	if (draw_buttons) {
		const int padding = 2;
		position.y -= padding;
		total_height -= padding * 2;
	}

	float height = total_height / (float)(max_scroll + 1);
	position.y -= height * (scroll + 1);

	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(position.x, position.y, position.z + BSGFX_BACKGROUND_Z_COUNT),
		BS_V2(scrollbar->width, height),
		BS_V4(scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius, scrollbar->border_radius),
		scrollbar->material,
		scrollbar->outline_material,
		0);
}

/**
 URL
 */
static bool _bsgfx_instanceUrl(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, int id, bs_vec3 position, bs_vec2* out_width) {
	/*
	bs_vec2 cursor = bs_cursorPosition();
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bsgfx_Font* font = widget->font ? widget->font : menu->font;
	
	bsgfx_AtlasCache* ui_copy = $BSGFX_ATLAS_ANY_ui_copy();

	//if ((position->y - ui_copy_size.y) < menu->coords.y)
	//	return;

	bs_vec2 name_dimensions = bsgfx_textDimensions(font, widget->url.path, strlen(widget->url.path));
	bool url_hovering = !already_hovering && bs_rectangleVsPoint(bs_v2AddY(position.xy, -name_dimensions.y), &name_dimensions, &cursor);

	// url_hovering ? BSGFX_DEBUG_URL_SELECTED_COLOR : BSGFX_DEBUG_URL_COLOR
	_bsgfx_instanceTextField(menu->text_subtype, &position, widget->url.path,  0);

	bs_vec3 copy_position = BS_V3(position.x + name_dimensions.x, position.y, position.z + 1);
	bs_vec2 copy_dimensions;
	bs_v2MulV1(&ui_copy_size, BSGFX_PIXEL_SCALE, &copy_dimensions);
	bool copy_hovering = !already_hovering && bs_rectangleVsPoint(&copy_position.xy, &copy_dimensions, &cursor);

	bs_mat4 transform = bs_transform(copy_position, BS_QUAT_IDENTITY, BS_V3(copy_dimensions.x, copy_dimensions.y, 0));
	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON], bs_m4x3(transform), ui_copy->coords, 0, 0, 0);

	//bsgfx_atlasLegacyHiResInstance(atlas, copy_position, ui_copy, bs_v2V1(BSGFX_PIXEL_SCALE), BS_WHITE, false);

	if (bs_leftClickOnce()) {
		if (url_hovering) {
			bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
			bs_systemF(false, "explorer /select,\"%s\"", widget->url.path);
		}
		else if (copy_hovering) {
			bs_String* string = bs_fullPath(NULL, widget->url.path, strlen(widget->url.path));
			bs_replaceCharOccurrences(string->value, string->len, '\\', '/');
			bs_copyToClipboard(string->value, string->len);
			bs_free(string);
		}
	}

	*out_width = name_dimensions;

	return url_hovering || copy_hovering;
	*/
	return false;
}

/**
 Range
 */
static bool _bsgfx_instanceRange(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, int id, bs_vec3 position, bs_vec2* out_width) {
	bs_vec2 cursor = bs_cursorPosition();
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bsgfx_Font* font = widget->font ? widget->font : menu->font;

	bsgfx_AtlasCache* ui_increment = $BSGFX_ATLAS_ANY_ui_increment();

	//bs_vec2 name_dimensions = bsgfx_textDimensions(font, widget->name, strlen(widget->name));
	bs_vec2 name_dimensions = BS_V2(16, 16);

	bs_vec3 copy_position = BS_V3(position.x + name_dimensions.x, position.y, position.z + 1);

	bs_vec2 copy_dimensions;
	bs_v2MulS(&ui_increment->size, BSGFX_PIXEL_SCALE, &copy_dimensions);

	bs_mat4x3 m = _bsgfx_matrix(copy_position, BS_V3(copy_dimensions.x, copy_dimensions.y, 0.0));
	_bsgfx_instanceAtlasFlipped(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON], m, ui_increment->id, 0, 0, $white_material()->id);

	bool hovering = !already_hovering && bs_rectangleVsPoint(&copy_position.xy, &copy_dimensions, &cursor) && bs_leftClickOnce();
	if (hovering) {
		(*widget->range.value)--;
		if (widget->range.on_change)
			widget->range.on_change(widget);
	}

	copy_position.x += copy_dimensions.x + BSGFX_PIXEL_SCALE;
	bs_vec2 text_position = copy_position.xy;

	const bsgfx_Text text = {
		.position = { copy_position.x, copy_position.y, position.z + 1, 1 },
		.scale = BSGFX_PIXEL_SCALE,
	};

	bs_vec2 text_size;
	//_bsgfx_instanceTextF(font, &text, "%d/%d", &text_size, *widget->range.value, widget->range.max);
	copy_position.x += text_size.x;

	if (bs_rectangleVsPoint(&copy_position.xy, &copy_dimensions, &cursor) && bs_leftClickOnce()) {
		(*widget->range.value)++;
		if (widget->range.on_change)
			widget->range.on_change(widget);
	}

	m = _bsgfx_matrix(copy_position, BS_V3(copy_dimensions.x, copy_dimensions.y, 0.0));
	_bsgfx_instanceAtlas(_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON], m, ui_increment->id, 0, 0, $white_material()->id);

	if ((*widget->range.value) <= widget->range.min)
		(*widget->range.value) = widget->range.min;
	if ((*widget->range.value) > widget->range.max)
		(*widget->range.value) = widget->range.max;

	*out_width = copy_dimensions;

	return hovering;
}

/**
 Slider
 */
static bool _bsgfx_instanceSlider(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, int id, bs_vec3 position, bs_vec2* out_size) {
	bs_vec2 cursor = bs_cursorPosition();
	bsgfx_Font* font = widget->font ? widget->font : menu->font;

//	bs_vec2 name_dimensions = bsgfx_textDimensions(font, widget->name, strlen(widget->name));
	bs_vec2 name_dimensions = BS_V2(16, 16);
	bs_vec2 bar_dimensions = BS_V2(3 * BSGFX_PIXEL_SCALE, 4.0 * BSGFX_PIXEL_SCALE);
	position.y -= bar_dimensions.y;

	bs_vec3 copy_position = BS_V3(position.x + name_dimensions.x, position.y, position.z + 1);
	bs_vec2 text_position = copy_position.xy;

	const float default_width = 16.0;
	float width = (widget->slider.width == 0.0 ? default_width : widget->slider.width) * BSGFX_PIXEL_SCALE;

	float value_norm = (*widget->slider.value - widget->slider.min) / (widget->slider.max - widget->slider.min);
	value_norm = bs_clamp(value_norm, 0.0f, 1.0f);

	bs_vec3 bar_offset = BS_V3(value_norm * width, BSGFX_PIXEL_SCALE, 0.0);
	bs_vec3 bar_position;
	bs_v3Add(&copy_position, &bar_offset, &bar_position);

	bs_mat4x3 m = _bsgfx_matrix(
		BS_V3(copy_position.x, copy_position.y + bar_dimensions.y / 2.0, copy_position.z), 
		BS_V3(width, BSGFX_PIXEL_SCALE, 0.0)
	);

	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR], m, BS_V4(0, 0, 1, 1), 0, 0, $white_material()->id);
	m = _bsgfx_matrix(bar_position, BS_V3(bar_dimensions.x, bar_dimensions.y, 0.0));
	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR], m, BS_V4(0, 0, 1, 1), 0, 0, $white_material()->id);

	static bool dragging;

	if (!bs_leftClick())
		dragging = false;

	if (_bsgfx_rectangleVsPointExpand(&bar_position.xy, &bar_dimensions, &cursor, 0.0) && bs_leftClickOnce())
		dragging = true;

	if (dragging) {
		float diff = cursor.x - copy_position.x;
		float scale = bs_clamp(diff / width, 0.0f, 1.0f);

		*widget->slider.value = widget->slider.min + scale * (widget->slider.max - widget->slider.min);
		if (widget->slider.integer)
			*widget->slider.value = roundf(*widget->slider.value);
	}

	copy_position.x += width + BSGFX_PIXEL_SCALE;

	*out_size = BS_V2(width, bar_dimensions.y);

	return false;
}

/**
 Icon
 */
static bool _bsgfx_instanceIcon(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, int id, bs_vec3 position, bs_vec2* out_size) {
	int border_size = (bool)widget->icon.outline_material_id;
	//position->y -= border_size;

	bs_vec2 cursor = bs_cursorPosition();

	bsgfx_Font* font = widget->font ? widget->font : menu->font;

	int ui_icon = 0;
	if (widget->icon.type == BSGFX_ICON_ATLAS) {
		ui_icon = bs_queryAtlas(widget->icon.atlas, widget->icon.name);
		if (ui_icon == -1) {
			bs_warnF("Failed to query icon \"%s\"\n", widget->icon.name); // TODO: _bsgfx_warn
			return false;
		}
	}

	bs_vec2 size = widget->icon.scale;
	if (widget->icon.scale.x != 0.0)
		size = widget->icon.scale;
	else if (widget->icon.type == BSGFX_ICON_TILE)
		size = BSGFX_TILE_SIZE;
	else if (widget->icon.type == BSGFX_ICON_ATLAS) 
		size = bs_atlasSize(widget->icon.atlas, ui_icon);
	else if (widget->icon.type == BSGFX_ICON_MATERIAL) {
		//bsgfx_Material* material = bs_fetchUnit(_bsgfx_materials(), widget->icon.material_id);
		//bsgfx_Texture* texture = _bsgfx_fetchTexture(material->contract->scale, material->contract->image);
		//size = BS_IV2_TO_V2(texture->size);
		size = BS_V2(256, 256); // todo
	}

	//bs_vec2 name_dimensions = { 0 };
	//if (widget->name)
	//	name_dimensions = bsgfx_textDimensions(font, widget->name, strlen(widget->name));

	//if (widget->icon.placement == BSGFX_ICON_PLACE_BELOW)
	//	position->y -= size.y;


	if (widget->align_height == 0.0)
		widget->align_height = size.y;
	position.y -= (widget->align_height + size.y) / 2.0;
	bs_vec3 icon_position = BS_V3(position.x /* + (widget->icon.placement == BSGFX_ICON_PLACE_BELOW || widget->icon.placement == BSGFX_ICON_PLACE_LEFT ? 0.0 : name_dimensions.x)*/, position.y, position.z + 1);
	bool hovering = !already_hovering && bs_rectangleVsPoint(&icon_position.xy, &size, &cursor);

	bs_mat4 transform = BS_MAT4_IDENTITY;
	switch (widget->icon.type) {
	case BSGFX_ICON_TILE:
		bs_m4Translate(&transform, &icon_position, &transform);
		bs_m4Scale(&transform, &BS_V3(size.x, size.y, 0), &transform);

		_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_TILE_ICON], bs_m4x3(&transform), BS_V4(0, 0, 1, 1), 0, 0, widget->icon.material_id);
		//bsgfx_tileHiResInstance(icon_position, _bsgfx_queryTileType(widget->icon.name), BS_WHITE);
		//dux_tileHiResInstance(icon_position, _bsgfx_queryTileType(widget->icon.name), size, hovering ? bs_v4MulV1(color, 2.0) : color);
		break;
	case BSGFX_ICON_ATLAS:
		bs_Atlas* atlas = widget->icon.atlas;

		bs_m4Translate(&transform, &icon_position, &transform);
		bs_m4Scale(&transform, &BS_V3(size.x, size.y, 0), &transform);

		if (widget->icon.background_name) {
			int background_atlas = bs_queryAtlas(atlas, widget->icon.background_name);
			if (background_atlas >= 0) {
				bs_vec4 background_coords = bs_atlasCoordinates(atlas, background_atlas);
				_bsgfx_instanceQuad(widget->icon.atlas_subtype, bs_m4x3(&transform), background_coords, 0, 0, 0);
			}
		}

		transform.v[3].z++;

		int atlas_id = bs_queryAtlas(atlas, widget->icon.name);
		bs_vec4 coords = bs_atlasCoordinates(atlas, atlas_id); // TODO: widget->icon.frame

		if (widget->icon.flipped) 
			coords = bs_flipUV(coords);

		if (widget->icon.mirrored) 
			coords = bs_mirrorUV(coords);

		_bsgfx_instanceQuad(widget->icon.atlas_subtype, bs_m4x3(&transform), coords, 0, 0, widget->icon.material_id);

		break;
	case BSGFX_ICON_MATERIAL:
		_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
			icon_position,
			size,
			BS_V4(widget->icon.border_radius, widget->icon.border_radius, widget->icon.border_radius, widget->icon.border_radius),
			0,
			widget->icon.outline_material_id,
			0);

		icon_position.z += BSGFX_BACKGROUND_Z_COUNT;

		bs_m4Translate(&transform, &icon_position, &transform);
		bs_m4Scale(&transform, &BS_V3(size.x, size.y, 0), &transform);

		_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_QUAD_MATERIAL_TEXTURE], bs_m4x3(&transform), BS_V4(0, 0, 1, 1), 0, 0, widget->icon.material_id);
		break;
	}

	if (widget->icon.hover && hovering)
		widget->icon.hover(widget);

	/*
	if (widget->icon.placement == BSGFX_ICON_PLACE_LEFT)
		position->x += size.x;



	if (widget->prefer_x) {
		//position->y += size.y;
		if (widget->icon.placement != BSGFX_ICON_PLACE_LEFT)
			position->x += BS_MAX(size.x, name_dimensions.x);
	}
	*/

	*out_size = size;

	return hovering;
}

/**
 List
 */
static bool _bsgfx_instanceList(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, int id, bs_vec3 position, bs_vec2* out_size) {
	/*
	bs_vec2 cursor = bs_cursorPosition();
	bsgfx_Font* font = widget->font ? widget->font : menu->font;

	const int max_name_length = 128;

	bs_vec3 p = bs_v3AddZ(position, 5);
	p.y -= BSGFX_LIST_ROW_DIMENSIONS.y;

	int offset = widget->list.scroll ? *widget->list.scroll : 0;
	offset += widget->list.vk_offset;

//	if (widget->list.scroll)
//		_bsgfx_instanceScrollbar(
//			menu,
//			BS_V3(position->x + BSGFX_LIST_ROW_DIMENSIONS.x, position->y, position->z),
//			0, // todo
//			widget->list.scroll,
//			BSGFX_LIST_ROW_DIMENSIONS.y,
//			0, // todo
//			widget->list.count,
//			widget->list.max);
	for (int i = 0; i < BS_MIN(widget->list.max, widget->list.count - offset); i++) {
		p.x = position.x;
		char* row_string = widget->list.foreach_visible_row((bsgfx_ForeachVisibleRowParams) {
			.widget = widget,
			.position = &p,
			.id = i + offset,
		});
		if (!row_string)
			continue;

		p.y += _bsgfx_textHeight();

		if (strlen(row_string) > max_name_length) {
			char old = row_string[max_name_length - 1];
			row_string[max_name_length - 1] = '\0';
			_bsgfx_instanceTextFieldF(&p, 0, "%s...", row_string);
			row_string[max_name_length - 1] = old;
		}
		else
			_bsgfx_instanceTextField(menu->text_subtype, &p, row_string, 0);
		p.y -= BSGFX_LIST_ROW_DIMENSIONS.y;
	}

	bs_vec2 dimensions = BS_V2(BSGFX_LIST_ROW_DIMENSIONS.x, BSGFX_LIST_ROW_DIMENSIONS.y * (BS_MIN(widget->list.max, widget->list.count) + 1));
	position.y -= dimensions.y - BSGFX_LIST_ROW_DIMENSIONS.y;
	//bsgfx_instanceSquare(bs_v3AddZ(*position, 1), dimensions, BS_RGBA(80, 90, 90, 100));

	*out_size = dimensions;
	return !already_hovering && bs_rectangleVsPoint(&position.xy, &dimensions, &cursor);
	*/

	return false;
}

 /**
  String
  */
/*
static bool _bsgfx_instanceWidgetName(bsgfx_Menu* menu, bsgfx_Widget* widget, bs_vec2 cursor) {
	if (!widget->name)
		return false;

	int widget_name_len = strlen(widget->name);
	if (widget_name_len <= 0)
		return false;

	bsgfx_textDimensions(widget->font ? widget->font : menu->font, widget->name, widget_name_len);
	if (widget->type != BSGFX_WIDGET_BUTTON &&
		widget->type != BSGFX_WIDGET_URL)
	{
		bs_vec3 position = menu->position;
		float width = _bsgfx_instanceTextField(menu->text_subtype, &position, widget->name, widget->material_id);
		bsgfx_Font* font = widget->font ? widget->font : menu->font;
		bs_vec2 size = BS_V2(width, font->height);

		menu->position.x += width;
		//if (widget->prefer_x)
		//	menu->position.x += size.x;
		return bs_rectangleVsPoint(position.xy, size, cursor);
	}

	return false;
}
*/

static bool _bsgfx_instanceString(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, bs_vec3 position, bs_vec2* out_width) {
	bs_vec2 cursor = bs_cursorPosition();

	//if (widget->type != BSGFX_WIDGET_ICON || widget->icon.placement == BSGFX_ICON_PLACE_RIGHT || widget->icon.placement == BSGFX_ICON_PLACE_BELOW)
	//hovering_name = _bsgfx_instanceWidgetName(&menu, widget, cursor);

	bsgfx_Font* font = widget->font ? widget->font : menu->font;
	int len = strlen(widget->string.value);

	bs_vec2 text_dimensions;
	bsgfx_textDimensions(font, &text_dimensions, widget->string.value, len);

	if (widget->align_height == 0.0)
		widget->align_height = text_dimensions.y;

	//position.y -= (widget->align_height + text_dimensions.y) / 2.0 + font->min_y_shift; // TODO: Font rework
	const bsgfx_Text text = {
		.position = {
			position.x,
			position.y,
			position.z + 2, 1
		},
	//	.scale = font->size, // TODO: Font rework
	};

	bs_vec2 text_size;
	//_bsgfx_instanceTextN(menu->text_subtype, font, &text, &text_size, widget->string.value, len);
	bool hovering = bs_rectangleVsPoint(&text.position.xy, &text_dimensions, &cursor);
	if (widget->string.on_hover && hovering)
		widget->string.on_hover(widget);

	*out_width = text_dimensions;

	return hovering;
}

 /**
  Button
  */
static bool _bsgfx_instanceButton(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, bs_vec3 position, bs_vec2* out_width) {
	bs_vec2 cursor = bs_cursorPosition();
	bs_vec2 size = widget->button.size;

	bsgfx_Font* font = widget->font ? widget->font : menu->font;

	bs_vec2 text_dimensions;
	if (widget->button.name && font) {
		bsgfx_textDimensions(font, &text_dimensions, widget->button.name, strlen(widget->button.name));

		if (size.x == 0)
			size.x = text_dimensions.x;
		if (size.y == 0)
			size.y = text_dimensions.y;
	}

	if (menu->untextured.auto_scale_width)
		menu->untextured.dimensions.x = BS_MAX(menu->untextured.dimensions.x, size.x);

	position.y -= size.y;

	bool hovering =
		(widget->button.active_override.active_index && *widget->button.active_override.active_index == widget->button.active_override.this_index) ||
		(!already_hovering && bs_rectangleVsPoint(&position.xy, &size, &cursor));

	if (widget->button.name && font) {
		const bsgfx_Text text = {
			.position = {
				position.x + (size.x - text_dimensions.x) / 2.0,
				position.y + (size.y - text_dimensions.y) / 2.0,
				position.z + 2, 1
			},
			//.scale = font->size, // TODO: Font rework
		};

		bs_vec2 text_size;
		//_bsgfx_instanceText(menu->text_subtype, font, &text, &text_size, widget->button.name);

	}
	
	if (widget->button.tick) {
		hovering = widget->button.tick(&(bsgfx_ButtonParams) {
			.menu = menu,
			.widget = widget,
			.widget_position = position,
			.hovering = hovering,
		});
	}

	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_m4Translate(&transform, &BS_V3(position.x, position.y, position.z + 1), &transform); // TODO: improve z offset impl
	bs_m4Scale(&transform, &BS_V3(size.x, size.y, 0.0), &transform);

	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR], bs_m4x3(&transform), BS_V4(0, 0, 1, 1), 0, 0, hovering ? widget->button.selected_material : widget->button.material);

	//if (widget->prefer_x) {
	if (widget->advance_flags & BSGFX_WIDGET_ADVANCE_RIGHT) {
		position.y += size.y;
		position.x += size.x + 1.0;
	}

	static float hover_time;
	const float hover_time_threshhold = 0.5;
	if (hovering && widget->button.hint) {
		hover_time += bs_deltaTime();
		//if (hover_time > hover_time_threshhold)
		//	_bsgfx_instanceHint(menu->text_subtype, BS_V3(cursor.x, cursor.y, 100.0), widget->button.hint);
	}
	else
		hover_time = 0.0;

	*out_width = size;

	return hovering;
}

/**
 Color Picker
 */
BSGFXAPI void _bsgfx_renderColorPickers() {
	bs_beginCommentN(BS_CONSTANT_STRING("Color picker"));
	bs_Pipeline* pipeline;
	bs_PipelineHash hash;

	 /**
	  Color picker
	  */
	hash = _bsgfx_defaultPipelineHash();
	_bsgfx_requiredForTransparency(&hash);
	hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
	hash.shaders[1] = $fs_bsgfx_color_picker();

	hash.stencil_back = (bs_StencilOperation) {
		.fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
		.pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
		.depth_fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
		.compare_op = BS_COMPARE_OP_ALWAYS,
		.compare_mask = 0xFF,
		.write_mask = 0xFF,
	};

	hash.stencil_front = (bs_StencilOperation) {
		.fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
		.pass_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
		.depth_fail_op = BS_STENCIL_OP_INCREMENT_AND_CLAMP,
		.compare_op = BS_COMPARE_OP_ALWAYS,
		.compare_mask = 0xFF,
		.write_mask = 0xFF,
	};

	if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

		bs_pushConstant(pipeline, 0, sizeof(_poser_->screen_camera.result), &_poser_->screen_camera.result);
		_bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER], pipeline);
	}

	 /**
	  Hue
	  */
	hash = _bsgfx_defaultPipelineHash();
	_bsgfx_requiredForTransparency(&hash);
	hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
	hash.shaders[1] = $fs_bsgfx_hue();

	if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {

		bs_pushConstant(pipeline, 0, sizeof(_poser_->screen_camera.result), &_poser_->screen_camera.result);
		_bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_HUE], pipeline);
	}

	 /**
	  Alpha
	  */
	hash = _bsgfx_defaultPipelineHash();
	_bsgfx_requiredForTransparency(&hash);
	hash.shaders[0] = $vs_bsgfx_quad_rounded_instanced();
	hash.shaders[1] = $fs_bsgfx_alpha();

	if (bs_pipeline(&hash, &pipeline) == BS_RESULT_OK) {
		bs_pushConstant(pipeline, 0, sizeof(_poser_->screen_camera.result), &_poser_->screen_camera.result);
		_bsgfx_renderSubtype(_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_ALPHA], pipeline);
	}

	bs_endComment();
}

typedef enum {
	BSGFX_ORIGIN_LEFT,
	BSGFX_ORIGIN_CENTER,
} bsgfx_OriginType;

static void _bsgfx_instanceUIElement(bsgfx_AtlasCache* cache, bsgfx_OriginType origin, bs_vec3 position, int material_id) {
	if (origin == BSGFX_ORIGIN_CENTER) {
		position.x -= cache->size.x / 2.0;
		position.y -= cache->size.x / 2.0;
	}
	bs_mat4x3 icon_matrix = _bsgfx_roundedMatrix(position, BS_V3(cache->size.x, cache->size.y, 0.0), BS_V4(0.0, 0.0, 0.0, 0.0));
	_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_STENCIL], icon_matrix, cache->coords, 0, 0, material_id);
}

static bool _bsgfx_instanceColorPicker(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, bs_vec3 position, bs_vec2* out_size) {
	int border_size = (bool)widget->color.outline_material_id + (bool)widget->color.shadow_material_id;
	position.y -= widget->color.dimensions.y;
	//position->y -= border_size;

	bs_vec2 cursor = bs_cursorPosition();
	bs_vec3 hue_dimensions = BS_V3(widget->color.hue_width, widget->color.dimensions.y, 0.0);
	bs_vec3 alpha_dimensions = BS_V3(widget->color.hue_width, widget->color.dimensions.y, 0.0);
	bs_vec4 border_radii = BS_V4(widget->color.border_radius, widget->color.border_radius, widget->color.border_radius, widget->color.border_radius);
	bs_vec3 hue_position = BS_V3(position.x + widget->color.dimensions.x + widget->color.padding, position.y, position.z);
	bs_vec3 alpha_position = BS_V3(hue_position.x + hue_dimensions.x + widget->color.padding, position.y, position.z);
	
	float z = 1.0;

	 /**
	  Background
	  */
	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(position.x, position.y, position.z + z),
		widget->color.dimensions, 
		border_radii,
		0,
		widget->color.outline_material_id,
		widget->color.shadow_material_id);

	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(hue_position.x, hue_position.y, hue_position.z + z),
		hue_dimensions.xy,
		border_radii,
		0,
		widget->color.outline_material_id,
		widget->color.shadow_material_id);

	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(alpha_position.x, alpha_position.y, alpha_position.z + z),
		alpha_dimensions.xy,
		border_radii,
		0,
		widget->color.outline_material_id,
		widget->color.shadow_material_id);
	z += BSGFX_BACKGROUND_Z_COUNT;

	 /**
	  Color picker
	  */
	position.z++;
	hue_position.z++;
	alpha_position.z++;

	_bsgfx_instanceQuad(
		_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER],
		_bsgfx_roundedMatrix(position, BS_V3(widget->color.dimensions.x, widget->color.dimensions.y, 0.0), border_radii),
		BS_V4(0, 0, 1, 1),
		0, 0, widget->color.material_id);
	
	_bsgfx_instanceQuad(
		_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_HUE],
		_bsgfx_roundedMatrix(hue_position, hue_dimensions, border_radii),
		BS_V4(0, 0, 1, 1),
		0, 0, $white_material()->id);

	_bsgfx_instanceQuad(
		_bsgfx_subtypes_[BSGFX_SUBTYPE_COLOR_PICKER_ALPHA],
		_bsgfx_roundedMatrix(alpha_position, alpha_dimensions, border_radii),
		BS_V4(0, 0, alpha_dimensions.x / alpha_dimensions.y, 1.0),
		0, 0, $white_material()->id);

	//int ui_bar = bs_queryAtlas(atlas, "ui_bar");

	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(hue_position.x, hue_position.y + widget->color.hsva->x / 360.0 * hue_dimensions.y, position.z + 20),
		BS_V2(hue_dimensions.x, 1.0),
		BS_V4(0.0, 0.0, 0.0, 0.0),
		widget->color.background_material_id,
		widget->color.outline_material_id, 
		0);

	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(alpha_position.x, alpha_position.y + widget->color.hsva->w * alpha_dimensions.y, position.z + 20),
		BS_V2(hue_dimensions.x, 1.0),
		BS_V4(0.0, 0.0, 0.0, 0.0),
		widget->color.background_material_id,
		widget->color.outline_material_id,
		0);

	bool hovering_picker = !already_hovering && bs_rectangleVsPoint(&position.xy, &widget->color.dimensions, &cursor);
	bool hovering_hue = !already_hovering && bs_rectangleVsPoint(&hue_position.xy, &hue_dimensions, &cursor);
	bool hovering_alpha = !already_hovering && bs_rectangleVsPoint(&alpha_position.xy, &alpha_dimensions, &cursor);
	bool changed = false;

	static bool dragging_picker;
	static bool dragging_hue;
	static bool dragging_alpha;

	if ((hovering_picker || dragging_picker) && !dragging_hue && !dragging_alpha) {
		bs_vec2 relative = BS_V2(cursor.x - position.x, cursor.y - position.y);
		bs_v2Div(&relative, &widget->color.dimensions, &relative);
		relative = BS_V2(bs_clamp(relative.x, 0.0, 1.0), bs_clamp(relative.y, 0.0, 1.0));

		if (bs_leftClick()) {
			widget->color.hsva->y = relative.x;
			widget->color.hsva->z = relative.y;
			changed = true;
			dragging_picker = true;
		}
	}

	if (!bs_leftClick())
		dragging_picker = false;

	if ((hovering_hue || dragging_hue) && !dragging_picker && !dragging_alpha) {
		bs_vec2 relative = BS_V2(cursor.x - hue_position.x, cursor.y - hue_position.y);
		bs_v2Div(&relative, &hue_dimensions, &relative);

		if (bs_leftClick()) {
			widget->color.hsva->x = bs_clamp(relative.y * 360.0, 0.0, 360.0);
			changed = true;
			dragging_hue = true;
		}
	}

	if (!bs_leftClick())
		dragging_hue = false;

	if ((hovering_alpha || dragging_alpha) && !dragging_hue && !dragging_picker) {
		bs_vec2 relative = BS_V2(cursor.x - alpha_position.x, cursor.y - alpha_position.y);
		bs_v2Div(&relative, &alpha_dimensions, &relative);

		if (bs_leftClick()) {
			widget->color.hsva->w = bs_clamp(relative.y, 0.0, 1.0);
			changed = true;
			dragging_alpha = true;
		}
	}

	if (!bs_leftClick())
		dragging_alpha = false;

	if (changed) {
		if (widget->color.on_change_color) {
			bs_vec3 rgb = bs_hsvToRgb(&widget->color.hsva->xyz);

			bs_RGBA color = BS_RGBA(rgb.x * 255.0, rgb.y * 255.0, rgb.z * 255.0, widget->color.hsva->w * 255.0);

			widget->color.on_change_color(widget, color); // TODO: vec4 color
		}
	}

	// circumcise
	//bsgfx_instanceUIElement($BSMOD_ATLAS_UI_circle(), BSGFX_ORIGIN_CENTER, BS_V3(
	//	position.x + widget->color.hsva->y * widget->color.dimensions.x,
	//	position.y + widget->color.hsva->z * widget->color.dimensions.y,
	//	position.z + 30), $white_material()->id);

	if (widget->advance_flags & BSGFX_WIDGET_ADVANCE_RIGHT) {
		bsgfx_Font* font = widget->font ? widget->font : menu->font;
	//	position->y -= font->height + widget->name_padding;
		position.x += widget->color.dimensions.x + hue_dimensions.x + alpha_dimensions.x + widget->color.padding * 3;
	}

	return hovering_picker || hovering_hue;
}

/**
 Input
 */
static bs_U64 _bsgfx_selected_input = 0;

static inline void _bsgfx_findClosestX(bsgfx_Font* font, bs_String* input, int* select_position, float* select_draw_position_x, float target) {
	const float spacing = 16.0; // TODO: Font rework

	float result_draw_position_x = 0.0;

	for (; *select_position < input->len; (*select_position)++) {
		char c = input->value[*select_position];

		// next line is shorter than the input line
		if (c == '\n')
			break;

	//	float size = c == ' ' ? spacing : bs_atlasSize(font->batl->atlas, font->table[c]).x;
		float size = 16.0; // TODO: Font rework
		float next_draw_position_x = result_draw_position_x + size * BSGFX_PIXEL_SCALE;

		// found
		if (result_draw_position_x <= target && next_draw_position_x > target)
			break;

		result_draw_position_x = next_draw_position_x;
	}

	if (select_draw_position_x)
		*select_draw_position_x = result_draw_position_x;
}

static inline void _bsgfx_inputCursorPosition(bsgfx_Font* font, bs_String* input, float relative_x, float relative_y, int* position) {
	float current = 0.0;

	// find y
	int target_row = relative_y / _bsgfx_textHeight();
	int actual_row = 0;
	if (target_row != 0) {
		for (*position = 0; *position < input->len; (*position)++) {
			char c = input->value[*position];
			if (c == '\n') {
				if (++actual_row == target_row) {
					(*position)++;
					break;
				}
			}
		}
	}

	// find x
//	for (*position = 0; *position < input->len; (*position)++) {
//		int index = font->table[input->value[*position]];
//		if (index >= font->atlas->count)
//			index = 0;
//
//		float size = bs_atlasSize(font->atlas, index).x;
//		current += size * BSGFX_PIXEL_SCALE + BSGFX_PIXEL_SCALE;
//		if (current > relative_x)
//			break;
//	}

	_bsgfx_findClosestX(font, input, position, NULL, relative_x);
}

static inline void _bsgfx_findPreviousLine(bsgfx_Font* font, bs_String* input, int* select_position_out, float* select_draw_position_x, float* select_draw_position_y) {
	int select_position = (*select_position_out) - 1;
	float target = *select_draw_position_x;

	// go to previous row
	bool hit = false; // bad
	for (; select_position > 0; select_position--) {
		char c = input->value[select_position];
		if (c == '\n') {
			select_position--;
			hit = true;
			break;
		}
	}

	if (select_position < 0 || !hit)
		return;

	// go to start of previous row
	for (; select_position > 0; select_position--) {
		char c = input->value[select_position];
		if (c == '\n') {
			select_position++;
			break;
		}
	}

	_bsgfx_findClosestX(font, input, &select_position, select_draw_position_x, *select_draw_position_x);

	*select_position_out = select_position;
	*select_draw_position_y += _bsgfx_textHeight(&select_position);
}

static inline void _bsgfx_findNextLine(bsgfx_Font* font, bs_String* input, int* select_position_out, float* select_draw_position_x, float* select_draw_position_y) {
	int select_position = *select_position_out;

	// go to next row
	for (; select_position >= 0 && select_position < input->len; select_position++) {
		char c = input->value[select_position];
		if (c == '\n') {
			select_position++;
			break;
		}
	}

	if (select_position >= input->len)
		return;

	_bsgfx_findClosestX(font, input, &select_position, select_draw_position_x, *select_draw_position_x);

	*select_position_out = select_position;
	*select_draw_position_y -= _bsgfx_textHeight(&select_position);
}

static void _bsgfx_deserializeInputValue(bsgfx_Widget* widget, bs_String* string) {
	switch (widget->input.type) {
	case BSGFX_INPUT_DOUBLE: *widget->input.as_double = bs_toDouble(string->value); break;
	case BSGFX_INPUT_FLOAT: *widget->input.as_float = bs_toDouble(string->value); break;
	case BSGFX_INPUT_ULONG: *widget->input.as_ulong = bs_toULong(string->value); break;
	case BSGFX_INPUT_LONG: *widget->input.as_long = bs_toLong(string->value); break;
	case BSGFX_INPUT_UINT: *widget->input.as_uint = bs_toULong(string->value); break;
	case BSGFX_INPUT_INT: *widget->input.as_uint = bs_toLong(string->value); break;
	case BSGFX_INPUT_CHAR: *widget->input.as_uint = bs_toLong(string->value); break;
	case BSGFX_INPUT_UCHAR: *widget->input.as_uint = bs_toULong(string->value); break;
	case BSGFX_INPUT_STRING: *widget->input.as_string = bs_stringN(*widget->input.as_string, string->value, string->len); break;
	default:
		bs_warnF("Input type %d", widget->input.type); // TODO: bsgfx warn
	}
}

static bs_String* _bsgfx_serializeInputValue(bsgfx_Widget* widget, bs_String* string) {

	switch (widget->input.type) {
	case BSGFX_INPUT_DOUBLE: return bs_stringF(string, "%.4f", (float)*widget->input.as_double);
	case BSGFX_INPUT_FLOAT: return bs_stringF(string, "%.4f", (float)*widget->input.as_float);
	case BSGFX_INPUT_ULONG: return bs_stringF(string, "%lld", (long long)*widget->input.as_ulong);
	case BSGFX_INPUT_LONG: return bs_stringF(string, "%lld", (long long)*widget->input.as_long);
	case BSGFX_INPUT_UINT: return bs_stringF(string, "%d", (int)*widget->input.as_uint);
	case BSGFX_INPUT_INT: return bs_stringF(string, "%d", (int)*widget->input.as_int);
	case BSGFX_INPUT_CHAR: return bs_stringF(string, "%d", (int)*widget->input.as_char);
	case BSGFX_INPUT_UCHAR: return bs_stringF(string, "%d", (int)*widget->input.as_uchar);
	case BSGFX_INPUT_STRING: 
		return *widget->input.as_string ? bs_stringN(string, (*widget->input.as_string)->value, (*widget->input.as_string)->len) : string;
	default:
		bs_warnF("Input type %d", widget->input.type); // TODO: bsgfx warn
		return NULL;
	}
}

static bool _bsgfx_instanceInput(
	bsgfx_Menu* menu,
	bsgfx_Widget* widget,
	bool already_hovering,
	bs_vec3 position,
	bs_vec2* out_width,
	const char* alphabet)
{
	bs_vec2 cursor = bs_cursorPosition();

	bsgfx_Font* font = widget->font ? widget->font : menu->font;

	static bs_String* string;
	if (!string)
		string = bs_stringN(string, "", 0);

	string = _bsgfx_serializeInputValue(widget, string);

	const int outline_width = widget->input.outline_material_id != 0;
	float height = widget->input.dimensions.y + outline_width * 2;

	if (widget->align_height == 0.0)
		widget->align_height = height;

	position.y -= (widget->align_height + height) / 2.0;

	if (widget->input.active)
		_bsgfx_selected_input = widget->input.hash;

	// input background
	bool hovering = !already_hovering && bs_rectangleVsPoint(&position.xy, &widget->input.dimensions, &cursor);

	static char blinking_underscore = ' ';
	const float blink_every = 0.6;
	static float blink_timer = 0.0;

	// click selecting (WIP!!!)
	int start = 0;
	int end = 0;

	if (widget->input.select_position && widget->input.select_size) {
		int select_position = *widget->input.select_position;
		int select_size = *widget->input.select_size;

		if (bs_leftClickOnce()) {
			if (hovering) {
				if (_bsgfx_selected_input != widget->input.hash) {
					_bsgfx_selected_input = widget->input.hash;
					//select_position = value->len;
					//select_size = -value->len;
					//first_select = true;
				}
				//else {
				_bsgfx_inputCursorPosition(font, string, cursor.x - position.x, widget->input.dimensions.y - (cursor.y - position.y), &select_position);
				select_size = 0;
				//}
			}
			else
				_bsgfx_selected_input = select_position = select_size = 0;
		}

		if (hovering)
			bs_setCursor(BS_CURSOR_TEXT);
		else
			bs_setCursor(BS_CURSOR_DEFAULT);

		int x_dir = 0, y_dir = 0;
		if (bs_keyHeld(BS_KEY_LEFT)) x_dir = -1;
		if (bs_keyHeld(BS_KEY_RIGHT)) x_dir = 1;
		if (bs_keyHeld(BS_KEY_UP)) y_dir = -1;
		if (bs_keyHeld(BS_KEY_DOWN)) y_dir = 1;

		if (!bs_keyDown(BS_KEY_LEFT_SHIFT)) {
			if (x_dir != 0)
				select_size = 0;
		}

		if (x_dir != 0 || y_dir != 0) {
			select_position += x_dir;
			blinking_underscore = '|';
			blink_timer = 0.0;
		}

		// assert(value);

		// wouldnt be surprised if the select_size calculation breaks here
		if (select_position < 0 || (select_position + select_size) < 0) {
			select_size += *widget->input.select_position;
			select_position = 0;
		}
		else if (select_position > string->len || (select_position + select_size) > string->len) {
			select_position = string->len;
		}
		else if (bs_keyDown(BS_KEY_LEFT_SHIFT)) {
			if (bs_keyHeld(BS_KEY_LEFT))
				select_size++;
			else if (bs_keyHeld(BS_KEY_RIGHT))
				select_size--;
		}

		int row_position = 0;
		int row_index = 0;
		for (int i = 0, reset = 0; i < select_position; i++, reset++) {
			if (string->value[i] == '\n') {
				row_position += reset + 1;
				row_index++;
				reset = -1; // will increment to 0
			}
		}

		if (bs_keyHeld(BS_KEY_END)) {
			blink_timer = 0.0;
			blinking_underscore = '|';

			int start = select_position + select_size;

			for (; select_position < string->len; select_position++) {
				if (string->value[select_position] == '\n') {
					break;
				}
			}

			if (bs_keyDown(BS_KEY_LEFT_SHIFT))
				select_size = start - select_position;
			else
				select_size = 0;
		}
		else if (bs_keyHeld(BS_KEY_HOME)) {
			blink_timer = 0.0;
			blinking_underscore = '|';
			if (bs_keyDown(BS_KEY_LEFT_SHIFT))
				select_size += select_position - row_position;
			else
				select_size = 0;
			select_position = row_position;
		}
		else if (bs_keyDown(BS_KEY_LEFT_CONTROL) && bs_keyHeld(BS_KEY_A)) {
			blink_timer = 0.0;
			blinking_underscore = '|';
			select_position = 0;
			select_size = string->len;
		}

		char* row = string->value + row_position;
		bs_vec2 select_draw_position;
		bsgfx_textDimensions(font, &select_draw_position, row, select_position - row_position);
		select_draw_position.y = widget->input.dimensions.y - _bsgfx_textHeight() - (row_index * _bsgfx_textHeight());
		if (y_dir != 0) {
			if (bs_keyDown(BS_KEY_LEFT_SHIFT)) {
				int select_size_end = select_position;
				float select_size_draw_position_x = select_draw_position.x;
				float select_size_draw_position_y = select_draw_position.y;

				if (y_dir > 0)
					_bsgfx_findNextLine(font, string, &select_position, &select_size_draw_position_x, &select_size_draw_position_y);
				if (y_dir < 0)
					_bsgfx_findPreviousLine(font, string, &select_position, &select_size_draw_position_x, &select_size_draw_position_y);

				select_size += (select_size_end - select_position);
			}
			else {
				select_size = 0;
				if (y_dir > 0)
					_bsgfx_findNextLine(font, string, &select_position, &select_draw_position.x, &select_draw_position.y);
				if (y_dir < 0)
					_bsgfx_findPreviousLine(font, string, &select_position, &select_draw_position.x, &select_draw_position.y);
			}
		}

		if (_bsgfx_selected_input == widget->input.hash) {
			blink_timer += bs_deltaTime();

#define BSGFX_REPLACE_CHARS { \
		int size = select_size == 0 ? -1 : select_size;\
		if (size > 0)\
			bs_removeCharRange(string, select_position, size);\
		else {\
			bs_removeCharRange(string, select_position + size, -size);\
			select_position += size;\
		}\
		select_size = 0; \
	}

			if (bs_keyHeld(BS_KEY_BACKSPACE) && string->len > 0) {
				blink_timer = 0.0;
				blinking_underscore = '|';

				BSGFX_REPLACE_CHARS;

				_bsgfx_deserializeInputValue(widget, string);
			}
			else if (bs_keyHeld(BS_KEY_ENTER) && widget->input.new_line_on_enter) {
				blink_timer = 0.0;
				blinking_underscore = '|';

				if (select_size != 0)
					BSGFX_REPLACE_CHARS;

				string = bs_insertChar(string, select_position++, '\n');
				_bsgfx_deserializeInputValue(widget, string);
			}
			else if (bs_keyHeld(BS_KEY_SPACE)) {
				blink_timer = 0.0;
				blinking_underscore = '|';

				if (select_size != 0)
					BSGFX_REPLACE_CHARS;

				string = bs_insertChar(string, select_position++, ' ');
				_bsgfx_deserializeInputValue(widget, string);
			}
			else {
				// TODO: Font rework
				/*
				for (int i = 0; font->alphabet[i] != '\0'; i++) {
					if (bs_charDown(font->alphabet[i])) {
						if (select_size != 0)
							BSGFX_REPLACE_CHARS;

						blink_timer = 0.0;
						blinking_underscore = '|';

						string = bs_insertChar(string, select_position++, font->alphabet[i]);
						_bsgfx_deserializeInputValue(widget, string);

						break;
					}
				}
				*/
			}
		}

		start = select_position;
		end = select_position + select_size;
		if (start > end) {
			int temp = start;
			start = end;
			end = temp;
		}

		*widget->input.select_position = select_position;
		*widget->input.select_size = select_size;

		if (_bsgfx_selected_input == widget->input.hash && blinking_underscore == '|') {
			char c[2] = { blinking_underscore, '\0' };
			bsgfx_Text text = {
				// TODO: Font rework
				//.position = { position.x + select_draw_position.x, position.y + select_draw_position.y - font->min_y_shift, position.z + 4, 1 },
				.scale = 16.0, // todo font scale
				.material_id = $black_material()->id,
			};

			bs_vec2 text_size;
		//_bsgfx_instanceTextN(menu->text_subtype, font, &text, &text_size, c, 1);
		}
	}

	if (_bsgfx_selected_input == widget->input.hash && blink_timer > blink_every) {
		blinking_underscore = blinking_underscore == '|' ? ' ' : '|';
		blink_timer = 0.0;
	}

	bsgfx_Text text = {
		.colors = {
			BS_BLACK, BS_RED, BS_GREEN, BS_YELLOW, BS_BLUE, BS_MAGENTA, BS_CYAN, BS_WHITE
		},
		// TODO: Font rework
		//.position = { position.x, position.y - font->min_y_shift, position.z + 4, 1 },
		.scale = 16.0, // todo font scale
		.select_start = start,
		.select_end = end,
	};

	if (string->len == 0 && widget->input.placeholder_text) {
		text.material_id = widget->input.placeholder_text_material_id;
		bs_vec2 text_size;
		//_bsgfx_instanceText(menu->text_subtype, font, &text, &text_size, widget->input.placeholder_text);
	}
	else {
		text.material_id = widget->material_id;
		bs_vec2 text_size;
		//_bsgfx_instanceTextN(menu->text_subtype, font, &text, &text_size, string->value, BS_MIN(string->len, 1024));
	}

	const float z_offset = 3;
	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		BS_V3(position.x, position.y, position.z + z_offset),
		widget->input.dimensions,
		BS_V4(menu->border_radius, menu->border_radius, menu->border_radius, menu->border_radius),
		widget->input.outline_material_id,
		widget->input.background_outline_material_id,
		widget->input.background_shadow_material_id);

	//	if (active && bs_keyDownOnce(BS_KEY_ENTER) && widget->input.action) {
	//		widget->input.action(widget);
	//		_bsgfx_selected_input = 0;
	//	}

	*out_width = BS_V2(widget->input.dimensions.x, height);


	return hovering;
}

/**
 Grid
 */
static bs_U64 _bsgfx_selected_grid = 0;
static bool _bsgfx_instanceGrid(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, bs_vec3 position, bs_vec2* out_width) {
	bs_vec2 cursor = bs_cursorPosition();

	int columns = bs_floor(widget->grid.total_size.x / widget->grid.size.x);
	int rows = bs_floor(widget->grid.total_size.y / widget->grid.size.y);
	rows++;

	const float wrap_after_x = columns * widget->grid.size.x;
	const float wrap_after_y = rows * widget->grid.size.y;

	const int advance = widget->grid.scrollbar.substeps_count <= 0 ? 1 : widget->grid.scrollbar.substeps_count;
	const float scroll_offset = 1.0 / (float)advance;


	int max_scroll = 0;
	if (widget->grid.scrollbar.value) {
		bs_vec2 s = { position.x, position.y - widget->grid.total_size.y };
		bool hovering_area = bs_rectangleVsPoint(&s, &widget->grid.total_size, &cursor);
		if (hovering_area) {
			*widget->grid.scrollbar.value -= bs_scroll();
			if (*widget->grid.scrollbar.value < 0)
				*widget->grid.scrollbar.value = 0;
		}

		int total_rows = (int)bs_ceil(widget->grid.count / (float)columns);
		int max_rows_count = total_rows - rows;
		if (max_rows_count < 0)
			max_rows_count = 0;

		max_scroll = max_rows_count * advance + 1;

		if (*widget->grid.scrollbar.value > max_scroll)
			*widget->grid.scrollbar.value = max_scroll;
	}
	bs_vec3 start = position;

	position.y -= widget->grid.size.y;
	float start_y = position.y;

	bs_vec2 grid_position = position.xy;

	bool hovering = false;
	if (!widget->grid.always_active) {
		hovering = !already_hovering && bs_rectangleVsPoint(&position.xy, &widget->grid.size, &cursor);
		widget->grid.action(widget, (bsgfx_GridParams) {
			.start = position.xy, 
			.position = &grid_position, 
			.index = -1
		});
		grid_position.x += widget->grid.size.x;

	//	if (hovering && bs_leftClickOnce())
	//		_bsgfx_selected_grid = _bsgfx_selected_grid == id ? 0 : id;
	//	if (_bsgfx_selected_grid != id)
	//		return hovering;
	}

	int i = 0;
	int draw_count = 0;

	if (widget->grid.scrollbar.value)
		grid_position.y += (float)(*widget->grid.scrollbar.value % advance) * widget->grid.size.y * scroll_offset;

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++, i++) {
		//	bool hovering_grid = !already_hovering && bs_rectangleVsPoint(grid_position, widget->grid.size, cursor);
		//	if (hovering_grid)
		//		hovering = true;

			int index = i + columns * (int)((float)*widget->grid.scrollbar.value * scroll_offset);
			if (index >= widget->grid.count)
				goto end;

			bool should_advance = widget->grid.action(widget, (bsgfx_GridParams) {
				.start = position.xy, 
				.position = &grid_position, 
				.index = index
			});

			if (should_advance) {
				grid_position.x += widget->grid.size.x + widget->grid.padding;
				draw_count++;
			}

			if (grid_position.y < (start_y - wrap_after_y))
				goto end;


			if (grid_position.x > (position.x + (columns - 1) * widget->grid.size.x)) {
			//if (draw_count > 0 && draw_count % columns == 0) {
				grid_position.x = position.x;
				grid_position.y -= widget->grid.size.y + widget->grid.padding;
			}
		}
	}

end:
	if (widget->grid.scrollbar.value) {
		bs_vec3 scrollbar_position = BS_V3(start.x + widget->grid.total_size.x - widget->grid.scrollbar.padding, start.y - widget->grid.scrollbar.padding, start.z);
		_bsgfx_instanceScrollbar(
			&widget->grid.scrollbar,
			scrollbar_position,
			max_scroll,
			*widget->grid.scrollbar.value,
			widget->grid.total_size.y - widget->grid.scrollbar.padding * 2);
	}

	*out_width = widget->grid.total_size;

	position.y -= rows * widget->grid.size.y;
	return hovering;
}

/**
 Model
 */
static bool _bsgfx_instanceModel(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, bs_vec3 position, bs_vec2* out_size) {
	//bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
	/*
	bs_vec2 cursor = bs_cursorPosition();

	bs_U64 hash = bs_stringHash(widget->model.name);
	bs_Model* model = bs_queryHash(widget->model.name, NULL, hash, 0).model;
	bs_Mesh* mesh = widget->model.mesh_name ? bs_queryMesh(model, widget->model.mesh_name) : NULL;

	bs_Aabb aabb = mesh ? mesh->aabb : model->aabb;

	bs_vec2 dim = { 256, 256 };
	bs_vec2 sc = position->xy;

	float width = aabb.max.x - aabb.min.x;
	float height = aabb.max.y - aabb.min.y;
	float depth = aabb.max.z - aabb.min.z;

	sc = bs_v2Div(sc, bs_v2MulV1(BSGFX_TILE_SIZE, 2));
	sc.x += (width / BSGFX_PIXEL_SCALE);
	sc.y -= (height / BSGFX_PIXEL_SCALE) * 2.0 * 2.0;

	static float diff = 0.0;
	static float start = 0.0;

	if (bs_leftClickOnce())
		start = cursor.x;

	if (bs_leftClick()) {
		diff += cursor.x - start;
		start = cursor.x;
	}

	const float rotation_factor = 0.5;

	bs_vec4 rotation = bs_qFromDegreesV3(0.0, 180 + diff * rotation_factor, 0.0);
	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_vec3 p = BS_V3(sc.x + width, sc.y - depth * BS_SIN_45, 0);

	bs_translateP(&transform, &p);
	bs_rotateP(&transform, &rotation);

	bs_vec3 offset = { -width / 2.0, 0.0, depth / 2.0 };
	bs_translateP(&transform, &offset);

	if (widget->model.instance)
		widget->model.instance(&transform);
		*/
	return false;
}

/**
 Table
 */
static bool _bsgfx_instanceTable(bsgfx_Menu* menu, bsgfx_Widget* widget, bool already_hovering, bs_vec3 position, bs_vec2* out_size) {
	/*
	bs_vec2 cursor = bs_cursorPosition();

	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bsgfx_Font* font = widget->font ? widget->font : menu->font;
	int white = bs_queryAtlas(atlas, "white");
	bs_vec4 coords = bs_atlasCoordinates(atlas, white, 0);
//	int atlas_any_hi_res_subtype = _bsgfx_querySubtypeNull(BSGFX_INSTANCE_TYPE_QUAD_LEGACY, BSGFX_QUAD_LEGACY_KEY_ATLAS_ANY_HI_RES);

	bsgfx_Text text = {
		.position = { position.x, position.y - _bsgfx_textHeight() - BSGFX_PIXEL_SCALE, position.z + 2, 1 },
		.scale = BSGFX_PIXEL_SCALE,
	};

	int actual_unit_size = 0;
	for (int i = 0; i < widget->table.fields->count; i++) {
		bsgfx_TableField* field = bs_fetchUnit(widget->table.fields, i);
		switch (field->type) {
		case BSGFX_TABLE_FIELD_FLOAT: actual_unit_size += field->count * sizeof(float); break;
		case BSGFX_TABLE_FIELD_INTEGER: actual_unit_size += field->count * sizeof(int); break;
		default:
			bs_throwBasilisk(BSX_INVALID_TYPE);
			return false;
		}
	}

	if (actual_unit_size != widget->table.unit_size) {
		bs_throwBasilisk(BSX_MISMATCH);
		return false;
	}

	static bs_String* string;
	if (!string)
		string = bs_stringAlloc(NULL, 128);

	unsigned char* field_data = widget->table.data;
	for (int i = 0; i < widget->table.fields->count; i++) {
		bsgfx_TableField* field = bs_fetchUnit(widget->table.fields, i);
		bs_vec2 text_dim = _bsgfx_textInstanceF(font, &text, " %s |", field->name);
		text_dim.y += _bsgfx_textHeight();

	//	_bsgfx_quadLegacyInstance(atlas_any_hi_res_subtype,
	//		bs_v4V2(text.position.xy, position->z + 1, 1),
	//		text_dim,
	//		coords,
	//		i % 2 == 0 ? BS_BLACK : BS_RGBA(150, 150, 150, 255),
	//		0);

		bsgfx_Text row_text = {
			.position = text.position,
			.scale = BSGFX_PIXEL_SCALE,
			.max_length = text_dim.x,
		};

		// string builder
		int count = BS_MIN(widget->table.max_count, widget->table.count);
		int field_size = 0;
		for (int j = 0; j < count; j++) {
			string = bs_emptyString(string);
			field_size = 0;
			for (int k = 0; k < field->count; k++) {
				unsigned char* value_data = field_data + k * actual_unit_size;

				switch (field->type) {
				case BSGFX_TABLE_FIELD_FLOAT:
					field_size += sizeof(float);
					bs_appendStringF(string, "%.1f"); break;
				case BSGFX_TABLE_FIELD_INTEGER:
					field_size += sizeof(int);
					bs_appendStringF(string, "%d"); break;
				}

				if (k != (field->count - 1))
					bs_appendString(string, ", ", 2);
			}

			string = bs_appendChar(string, '\n');

			_bsgfx_instanceText(menu->text_subtype, font, &row_text, string->value, string->len);
			row_text.position.y -= _bsgfx_textHeight();
		}

		field_data += field->count * field_size;

		text.position.x += text_dim.x;
	}

	//*out_size = BS_V2(, _bsgfx_textHeight()).
	*/
	return false;
}



  /*==============================================================================
   * Menu System
   =============================================================================*/

static bool _bsgfx_instanceDebugSettingsMenu(bsgfx_Menu* menu, bsgfx_TitleBar* title_bar, bs_vec3 position, bs_vec2 dimensions, int border_id, float title_bar_height) {
	bs_vec2 cursor = bs_cursorPosition();

	// int atlas_any_hi_res_subtype = _bsgfx_querySubtypeNull(BSGFX_INSTANCE_TYPE_QUAD_LEGACY, BSGFX_QUAD_LEGACY_KEY_ATLAS_ANY_HI_RES);

	position.y -= dimensions.y;
	bool hovering = _bsgfx_rectangleVsPointExpand(&position.xy, &dimensions, &cursor, 1.0);

	position.z -= 10; // add some z space so widgets can use negative offsets, maybe change to something else
	bs_mat4x3 transform = _bsgfx_roundedMatrix(position, BS_V3(dimensions.x, dimensions.y, 0.0), BS_V4(0.0, 0.0, 0.0, 0.0));
	if (menu->background_material_id_1)
		_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_CORNER_GRADIENT], transform, BS_V4(0, 0, 1, 1), 0, menu->background_material_id_1, menu->background_material_id_0);
	else
		_bsgfx_instanceQuad(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR], transform, BS_V4(0, 0, 1, 1), 0, 0, menu->background_material_id_0);

	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		position,
		BS_V2(dimensions.x, dimensions.y + (title_bar ? title_bar_height : 0.0)),
		BS_V4(menu->border_radius, menu->border_radius, menu->border_radius, menu->border_radius),
		0,
		menu->outline_material_id,
		menu->shadow_material_id);

	return hovering;
}

static void _bsgfx_instanceMenuTabs(bsgfx_Menu* menu, bsgfx_MenuTabBar* tab_bar) {
	const int x_indent = 0.0;
	bsgfx_Font* font = menu->font;
	bs_vec3 position = menu->position;
	bs_vec3 scale = BS_V3(64.0, tab_bar->height, 1.0);

	position.x += x_indent;
	scale.x -= x_indent;
	position.z -= 10;
	bs_vec3 start = position;

	bs_vec2 close_dimensions;
	bsgfx_textDimensions(font, &close_dimensions, " [x]", 4);

	position.z -= BSGFX_BACKGROUND_Z_COUNT;
	_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
		position,
		BS_V2(menu->untextured.dimensions.x, scale.y),
		BS_V4(menu->border_radius, menu->border_radius, menu->border_radius, menu->border_radius),
		tab_bar->material_id,
		tab_bar->outline_material_id,
		tab_bar->shadow_material_id);

	position.z += BSGFX_BACKGROUND_Z_COUNT;
	for (int i = 0; i < tab_bar->tabs_count; i++) {
		position.x +=  4;
		bsgfx_MenuTab* tab = tab_bar->tabs + i;

		bs_vec2 name_dimensions;
		_bsgfx_instanceText(menu->text_subtype, font, &(bsgfx_Text) {
			.position = {
				position.x + 4.0 + (tab->icon_cache ? tab->icon_cache->size.x : 0.0),
				position.y + tab_bar->height / 2.0 - 4, // todo idk why 4 will figure out when i try another font
				position.z + 1,
				1,
			},
			.scale = 16.0,
			.max_length = menu->untextured.dimensions.x / (float)tab_bar->tabs_count
		}, & name_dimensions, tab->name);

		name_dimensions.x += 16.0;
		scale.x = name_dimensions.x + x_indent;

		if (tab->icon_cache) {
			bs_vec3 tab_icon_offset = BS_V3(0.0, (tab_bar->height - tab->icon_cache->size.y) / 2.0, 10.0);
			bs_vec3 tab_icon_position;
			bs_v3Add(&position, &tab_icon_offset, &tab_icon_position);
			_bsgfx_instanceQuad(
				_bsgfx_subtypes_[BSGFX_SUBTYPE_UI],
				_bsgfx_roundedMatrix(
					tab_icon_position,
					BS_V3(tab->icon_cache->size.x, tab->icon_cache->size.y, 0.0),
					BS_V4(0, 0, 0, 0)
				),
				tab->icon_cache->coords,
				0, 0, tab->icon_material_id); 

			scale.x += tab->icon_cache->size.x;
		}

		bs_vec2 cursor_position = bs_cursorPosition();
		if (bs_rectangleVsPoint(&position.xy, &scale.xy, &cursor_position)) {
			_poser_->menu_blocked = true;
			if (bs_leftClickOnce())
				*tab_bar->active_tab = i;
		}

		if (*tab_bar->active_tab == i) {
			_bsgfx_instanceBackground(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI_COLOR],
				position,
				scale.xy,
				BS_V4(0, 0, menu->border_radius, menu->border_radius),
				tab->material_id,
				tab->outline_material_id,
				tab->shadow_material_id);
		}

		if (tab->icon_cache)
			position.x += tab->icon_cache->size.x;
		position.x += name_dimensions.x + 4;
		/*
		_bsgfx_quadInstance(_bsgfx_subtypes_[BSGFX_SUBTYPE_UI],
			_bsgfx_roundedMatrix(
				bs_v3AddZ(position, 1.0),
				bs_v3V2(title_bar_close->size, 0.0),
				bs_v4V1(0)
			),
			title_bar_close->coords,
			0, 0, $white_material()->id);
		*/
		position.y = start.y;
	}
}

static void _bsgfx_instanceTitleBar(bsgfx_Menu* menu, bsgfx_TitleBar* title_bar, bs_vec3 position, bs_vec2 dimensions) {
	bsgfx_Font* font = title_bar->font ? title_bar->font : menu->font;
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	
	bsgfx_AtlasCache* white = $BSGFX_ATLAS_ANY_white();

	const int bar_padding = 8;
	 /**
	  Title bar
	  */
	_bsgfx_instanceQuad(
		_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON],
		_bsgfx_roundedMatrix(position, BS_V3(dimensions.x, dimensions.y, 1.0), BS_V4(0, 0, 0, 0)),
		white->coords,
		0, 0, title_bar->material_id);

	int offset = 0;

	 /**
	  Title bar name
	  */
	if (title_bar->name) {
		bs_vec2 text_size;
	//	_bsgfx_instanceText(menu->text_subtype, font, &(bsgfx_Text) {
	//		.position = BS_V4(position.x + bar_padding, position.y + bar_padding, position.z + 1, 1),
	//		.scale = 16.0,
	//	}, &text_size, title_bar->name);
	}

	 /**
	  Buttons
	  */
	const int button_padding = 24;
	const float button_height = 16;
	const float outline_width = 1.0;
	/*

	struct {
		int id;
		bs_vec4 radii;
		void(*action)();
	} buttons[] = {
		{.id = bs_queryAtlas(atlas_ui, "title_bar_close"), .action = title_bar->on_close,.radii = {0, title_bar->border_radius, title_bar->border_radius, 0}},
		{.id = bs_queryAtlas(atlas_ui, "title_bar_maximize"), .action = title_bar->on_maximize },
		{.id = bs_queryAtlas(atlas_ui, "title_bar_minimize"), .action = title_bar->on_minimize, .radii = { title_bar->border_radius, 0, 0, title_bar->border_radius } },
	};

	position.x -= bar_padding / 2;
	position.y += bar_padding / 2;

	bs_vec3 button_position;

	const int count = (!title_bar->on_close && !title_bar->on_maximize && !title_bar->on_minimize) ? 0 : 3;
	for (int i = 0; i < count; i++) {
		bs_vec2 size = bs_v2MulV1(bs_atlasSize(atlas_ui, buttons[i].id), 1.0);

		offset += size.x + button_padding + outline_width;

		bs_vec3 button_size = BS_V3(size.x + button_padding, button_height, 1.0);
		button_position = bs_v3AddX(position, dimensions.x);
		button_position.x -= offset;
		button_position.z += 1;

		bool hovering = buttons[i].action && bs_rectangleVsPoint(button_position.xy, button_size.xy, bs_cursorPosition());
		_bsgfx_instanceQuad(
			_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON],
			_bsgfx_roundedMatrix(button_position, button_size, buttons[i].radii),
			coords,
			0, 0, buttons[i].action ? (hovering ? title_bar->button_hovering_material_id : title_bar->button_material_id) : title_bar->button_unavailable_material_id);

		if (hovering && bs_leftClickOnce())
			buttons[i].action();

		bs_vec3 icon_size = BS_V3(size.x, size.y, 1.0);
		bs_vec3 icon_position = bs_v3AddX(position, dimensions.x - offset);
		icon_position.x += button_padding / 2;
		icon_position.y += button_height / 4.0;
		icon_position.z += 2;

		_bsgfx_instanceQuad(
			_bsgfx_subtypes_[BSGFX_SUBTYPE_UI],
			_bsgfx_roundedMatrix(icon_position, icon_size, BS_V4(0, 0, 0, 0)),
			bs_atlasCoordinates(atlas_ui, buttons[i].id, 0),
			0, 0, title_bar->button_icon_material_id);
	}
	*/

	if (title_bar->button_shadow_material_id) {
		bs_vec3 outline_size = BS_V3(offset - outline_width, button_height, 1.0);
		bs_vec3 outline_position = BS_V3(position.x + dimensions.x, position.y, position.z);
		outline_position.y -= outline_width;
		outline_position.x -= offset;
		outline_position.z++;

		_bsgfx_instanceQuad(
			_bsgfx_subtypes_[BSGFX_SUBTYPE_ATLAS_ICON],
			_bsgfx_roundedMatrix(outline_position, outline_size, BS_V4(title_bar->border_radius, title_bar->border_radius, title_bar->border_radius, title_bar->border_radius)),
			white->coords,
			0, 0, title_bar->button_shadow_material_id);
	}
}

BSGFXAPI bool _bsgfx_instanceWidgets(bsgfx_Menu menu, bsgfx_TitleBar* title_bar, bsgfx_MenuTabBar* tab_bar) {

	const int title_bar_height = 24.0;
	if (title_bar) {
		bs_vec3 title_bar_offset = BS_V3(0, 0, 1);
		bs_vec3 title_bar_position;
		bs_v3Add(&menu.position, &title_bar_offset, &title_bar_position);
		_bsgfx_instanceTitleBar(&menu, title_bar, title_bar_position, BS_V2(menu.untextured.dimensions.x, title_bar_height));
	}

	bool hovering = menu.blocked;
	bool hovering_widgets = false;

	bs_vec3 menu_start_position = menu.position, menu_position = menu.position;
	float lowest_y = menu_start_position.y;
	bs_vec2 cursor = bs_cursorPosition();

	for (int i = 0; i < menu.widgets_count; i++) {
		bsgfx_Widget* widget = menu.widgets + i;
		if (widget->disabled)
			continue;

		bs_v3Add(&menu.position, &widget->offset, &menu.position);
		float start_x = menu.position.x;
		float start_y = menu.position.y;
		float start_z = menu.position.z;

		bs_vec2 widget_size = { 0 };

		//menu.position.y -= widget->align_height;

		bool hovering_widget = false;
		switch (widget->type) {
		case BSGFX_WIDGET_STRING: hovering_widget = _bsgfx_instanceString(&menu, widget, hovering, menu.position, &widget_size); break;
		case BSGFX_WIDGET_BUTTON: hovering_widget = _bsgfx_instanceButton(&menu, widget, hovering, menu.position, &widget_size); break;
		case BSGFX_WIDGET_INPUT: hovering_widget = _bsgfx_instanceInput(&menu, widget, hovering, menu.position, &widget_size,
			"!#$%&'()*+,-./abcdefghijklmnopqrstuvwxyz0123456789:;[\\]_{|}~"); break;
		case BSGFX_WIDGET_GRID: hovering_widget = _bsgfx_instanceGrid(&menu, widget, hovering, menu.position, &widget_size); break;
		case BSGFX_WIDGET_URL: hovering_widget = _bsgfx_instanceUrl(&menu, widget, hovering, i, menu.position, &widget_size); break;
		case BSGFX_WIDGET_RANGE: hovering_widget = _bsgfx_instanceRange(&menu, widget, hovering, i, menu.position, &widget_size); break;
		case BSGFX_WIDGET_SLIDER: hovering_widget = _bsgfx_instanceSlider(&menu, widget, hovering, i, menu.position, &widget_size); break;
		case BSGFX_WIDGET_ICON: hovering_widget = _bsgfx_instanceIcon(&menu, widget, hovering, i, menu.position, &widget_size); break;
		case BSGFX_WIDGET_LIST: hovering_widget = _bsgfx_instanceList(&menu, widget, hovering, i, menu.position, &widget_size); break;
		case BSGFX_WIDGET_COLOR: hovering_widget = _bsgfx_instanceColorPicker(&menu, widget, hovering, menu.position, &widget_size); break;
		case BSGFX_WIDGET_TABLE: hovering_widget = _bsgfx_instanceTable(&menu, widget, hovering, menu.position, &widget_size); break;
		case BSGFX_WIDGET_MODEL: hovering_widget = _bsgfx_instanceModel(&menu, widget, hovering, menu.position, &widget_size); break;
		case BSGFX_WIDGET_BACKGROUND: 
			widget_size = widget->background.size;
			_bsgfx_instanceBackground(widget->background.subtype,
				BS_V3(menu.position.x, menu.position.y - widget->background.size.y, menu.position.z),
				widget->background.size,
				BS_V4(widget->background.border_radius, widget->background.border_radius, widget->background.border_radius, widget->background.border_radius),
				widget->background.material_id,
				widget->background.outline_material_id,
				widget->background.shadow_material_id);
			break;
		}

		if (hovering_widget)
			hovering_widgets = true;

		if (!hovering)
			hovering = hovering_widget;

		widget_size.y = BS_MAX(widget_size.y, widget->align_height);

		if (!(widget->advance_flags & BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_X))
			menu.position.x = menu.position.x - widget->offset.x;
		if (!(widget->advance_flags & BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Y))
			menu.position.y = menu.position.y - widget->offset.y;
		if (!(widget->advance_flags & BSGFX_WIDGET_ADVANCE_APPLY_OFFSET_Z))
			menu.position.z = menu.position.z - widget->offset.z;

		menu.position.z = start_z;

		if (widget->advance_flags & BSGFX_WIDGET_ADVANCE_RIGHT)
			menu.position.x += widget_size.x + menu.spacing;
		if (widget->advance_flags & BSGFX_WIDGET_ADVANCE_DOWN)
			menu.position.y -= widget_size.y + menu.spacing;
		if (widget->advance_flags & BSGFX_WIDGET_ADVANCE_RESET_X)
			menu.position.x = menu_start_position.x;
	}
	// dimensions->y = start.y - position.y;

	bool hovering_menu = _bsgfx_instanceDebugSettingsMenu(&menu, title_bar, menu_start_position, menu.untextured.dimensions, menu.untextured.border_id, title_bar_height);

	if (hovering_widgets || hovering_menu)
		_poser_->menu_blocked = true;
	return hovering_widgets || hovering_menu;
}
