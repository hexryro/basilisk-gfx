
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

#define BSGFX_AXIS_CLICK_SIZE (48)



  /*==============================================================================
   * Snapping Primitives
   * TODO: Make generic for any type
   =============================================================================*/

static bs_mat4 bsgfx_primitiveOrigin(bsgfx_RawPrimitive* primitive, bs_vec3 origin) {
	bs_mat4 m = BS_MAT4_IDENTITY;

	bs_vec3 p;
	bsgfx_primitivePosition(primitive, &p);

	bs_m4Translate(&m, &p, &m);

	if (primitive->rotation.x != 0.0 || primitive->rotation.y != 0.0 || primitive->rotation.z != 0.0) {
		bs_vec4 q;
		bs_eulToQ(&BS_V3_TO_RADIANS(primitive->rotation), &q);
		bs_m4Rotate(&m, &q, &m);
	}

	//bs_vec3 s = bs_v3MulS(primitive->scale, -1.0);
	bs_vec3 o;
	bs_v3MulS(&origin, 1.0, &o);
	bs_v3Mul(&o, &primitive->scale, &o);

	bs_m4Translate(&m, &o, &m);
	bs_m4Scale(&m, &primitive->scale, &m);

	return m;
}

BSMODAPI void _bsmod_snapPrimitive() {
	/*
	static bs_vec2 cursor_start;

	bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);
	bs_vec2 temp;
	bs_v2MulS(&bsgfx_app()->world_camera.position, 4.0, &temp); // what is 4 pixel scale maybe?
	bs_v2Add(&temp, &cursor, &cursor);

	if (_bsmod_.edit_type_old != _bsmod_.edit_type) {
		bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, _bsmod_firstSelectedId(BSGFX_TYPE_PRIMITIVE));
		if (primitive) {
			cursor_start = cursor;
		}
	}

	bs_RGBA axis_colors[3] = {
		BS_RGBA(255, 20, 50, 100),
		BS_RGBA(50, 255, 20, 100),
		BS_RGBA(50, 20, 255, 100)
	};

	bool edited = false;

	for (int i = 0; i < bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
		bsgfx_RawPrimitive* raw_primitive = bsgfx_getRaw(BSGFX_TYPE_PRIMITIVE, i);
		bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);

		if (_bsmod_isSelected(BSMOD_IDS, BSGFX_TYPE_PRIMITIVE, i)) {
			bs_vec2 diff = {
				((cursor.x - cursor_start.x) / BSGFX_TILE_SIZE.x),
				((cursor.y - cursor_start.y) / BSGFX_TILE_SIZE.y),
			};

			bs_vec3 previous_position = raw_primitive->position;
			bs_vec3 previous_rotation = raw_primitive->rotation;
			bs_vec3 previous_scale = raw_primitive->scale;

			bs_mat4 transform;
			if (bs_keyDown(BS_KEY_LEFT_CONTROL)) {
				bsgfx_RawPrimitive* closest_primitive = bsgfx_getRaw(BSGFX_TYPE_PRIMITIVE, _bsmod_.hovering.closest_primitive);

				bs_mat4 m = bsgfx_primitiveOrigin(closest_primitive, _bsmod_.hovering.closest_vertex);

				bs_vec3 target;
				bs_m4MulV3(&m, &BS_V3(0.0, 0.0, 0.0), &target);

				float dist = bs_v3Distance(&raw_primitive->position, &target);
				if (bs_keyDown(BS_KEY_LEFT_SHIFT)) {
					bs_vec3 v1 = raw_primitive->position;
					bs_vec3 v2 = target;
					bs_vec4 q;

					bs_vec3 a;
					bs_v3Cross(&v1, &v2, &a);

					q.xyz = a;
					q.w = bs_sqrt(bs_v3MagnitudeSqrd(&v1) * bs_v3MagnitudeSqrd(&v2)) + bs_v3Dot(&v1, &v2);
					bs_qNormalize(&q, &q);

					bs_qToEul(&q, &raw_primitive->rotation);
				}
				else
					raw_primitive->position = target;

				bsgfx_map(BSGFX_TYPE_PRIMITIVE, i);
			}

			transform = BS_MAT4_IDENTITY;
			bs_m4Translate(&transform, &primitive->position, &transform);
			bs_m4Rotate(&transform, &primitive->rotation, &transform);
			bs_m4Scale(&transform, &primitive->scale, &transform);

			bsgfx_instantiate(bsgfx_subtypes()[BSGFX_SUBTYPE_PRIMITIVE_BOX], &transform, sizeof(bs_mat4), BSGFX_ID_SELECTED | BSGFX_ID_INSTANCE_TYPE_MESH | BSGFX_ID_HIGHLIGHT | BSGFX_ID_IS_PRIMITIVE, 0, 0, 0);

			if (bs_keyDown(BS_KEY_LEFT_CONTROL)) {
				if (!bs_leftClickOnce()) {
					raw_primitive->position = previous_position;
					raw_primitive->rotation = previous_rotation;
					raw_primitive->scale = previous_scale;
					bsgfx_map(BSGFX_TYPE_PRIMITIVE, i);
				}
				else if (_bsmod_.edit_type != 0) {
					edited = true;
					_bsmod_.edit_type = 0;
				}
			}
		}
	}

	//if (edited)
	//	bs_io.left_clicked = false;
	*/
}



  /*==============================================================================
   * Type Transformation
   =============================================================================*/

static inline bs_vec3 _bsmod_axisScreenPosition(bs_vec3 position) {
	position.x *= BSGFX_TILE_SIZE.x * 2.0;
	position.x -= bsgfx_app()->world_camera.position.x;

	position.y -= position.z;
	position.y *= BSGFX_TILE_SIZE.y * 2.0;
	position.y -= bsgfx_app()->world_camera.position.y;

	position.x -= BSGFX_AXIS_CLICK_SIZE * 0.5;
	position.y -= BSGFX_AXIS_CLICK_SIZE * 0.5;

	position.z = 10.0;

	return position;
}

static inline bs_vec3 _bsmod_worldToScreenCoords(bs_vec3 world_coords, float width) {
	bs_ivec2 resolution = bs_resolution(bs_scope()->context);
	bs_mat4 camera = bsgfx_app()->camera.result;

	bs_vec4 px;
	bs_m4MulV4(&camera, &BS_V3_TO_V4(world_coords, 1.0), &px);

	bs_vec3 px1; 
	bs_v3DivS(&px.xyz, px.w, &px1);

	px1.x = (px1.x + 1.0f) * 0.5f * resolution.x - width / 2.0;
	px1.y = (px1.y + 1.0f) * 0.5f * resolution.y - width / 2.0;
	px1.z *= 100.0;

	return px1;
}

 /**
  Will rebuild this when needed, should be multi-purpose
  */
BSMODAPI void _bsmod_instanceTransform() {
	if (_bsmod_.selected_ids.count == 0)
		return;
	return;
	bs_vec3 position = { 0 };
	bs_vec4 rotation = { 0, 0, 0, 1 };
	bs_vec3 scale = { 1, 1, 1 };

	bsgfx_TypeId type = _bsmod_.selected_type;
	int position_offset = 0, rotation_offset = 0, scale_offset = 0;
	int unit_size = 0;
	switch (type) {
	case BSGFX_TYPE_PRIMITIVE:
		unit_size = sizeof(bsgfx_RawPrimitive);
		position_offset = offsetof(bsgfx_RawPrimitive, position);
		rotation_offset = offsetof(bsgfx_RawPrimitive, rotation);
		scale_offset = offsetof(bsgfx_RawPrimitive, scale);
		break;
	case BSGFX_TYPE_PREFAB: {
		unit_size = sizeof(bsgfx_RawPrefab);
		position_offset = offsetof(bsgfx_RawPrefab, position);
		rotation_offset = offsetof(bsgfx_RawPrefab, rotation);
		scale_offset = offsetof(bsgfx_RawPrefab, scale);
		break;
	}
	case BSGFX_TYPE_LIGHT: {
		unit_size = sizeof(bsgfx_RawLight);
		position_offset = offsetof(bsgfx_RawLight, position);
		rotation_offset = offsetof(bsgfx_RawLight, rotation);
		scale_offset = -1;
		break;
	};
	default: return;
	}

	for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
		int* id = bs_fetchUnit(&_bsmod_.selected_ids, i);
		unsigned char* data = bsgfx_getRaw(type, *id);

		bs_vec3* p = data + position_offset;
		bs_vec3* r = data + rotation_offset;

		bs_v3Add(&position, p, &position);

		if (rotation_offset != -1) {
			rotation = BS_QUAT_IDENTITY;

			if (_bsmod_.selected_ids.count == 1)
				bs_eulToQ(r, &rotation);
		}
			
	}

	bs_v3DivS(&position, _bsmod_.selected_ids.count, &position);

	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_m4Translate(&transform, &position, &transform);
	bs_m4Rotate(&transform, &rotation, &transform);
	bs_m4Scale(&transform, &scale, &transform);

	if (bs_leftClickUpOnce() && _bsmod_.axis != -1) {
		_bsmod_saveTypeN(type, NULL, 0);

		_bsmod_.axis = -1;
	}

	const float axis_length = 1.0;
	const float radius = 0.2;
	float theta = BS_PI / 2.0;

	bs_vec3 origin;
	bs_m4MulV3(&transform, &BS_V3(0.0, 0.0, 0.0), &origin);

	bs_vec3 x, y, z; 
	bs_m4MulV3(&transform, &BS_V3(axis_length, 0, 0), &x);
	bs_m4MulV3(&transform, &BS_V3(0, axis_length, 0), &y);
	bs_m4MulV3(&transform, &BS_V3(0, 0, axis_length), &z);

	bs_vec3 directions[3] = { 0 };

	bs_v3Normalize(&BS_V3_SUB(origin, x), directions + 0);
	bs_v3Normalize(&BS_V3_SUB(origin, y), directions + 1);
	bs_v3Normalize(&BS_V3_SUB(origin, z), directions + 2);

	bs_vec4 xr, zr;
	bs_qAxisAngle(&BS_V3(0, 0, 1), -BS_PI / 2.0, &xr);
	bs_qAxisAngle(&BS_V3(1, 0, 0), BS_PI / 2.0, &zr);

	bs_qMulQ(&rotation, &xr, &xr);
	bs_qMulQ(&rotation, &zr, &zr);

	bs_mat4 om = BS_MAT4_IDENTITY;
	bs_m4Translate(&om, &origin, &om);
	bs_m4Rotate(&om, &rotation, &om);
	bs_m4Scale(&om, &BS_V3(radius, radius, radius), &om);

	bs_mat4 xm = BS_MAT4_IDENTITY;
	bs_m4Translate(&xm, &x, &xm);
	bs_m4Rotate(&xm, &xr, &xm);
	bs_m4Scale(&xm, &BS_V3(radius, radius, radius), &xm);

	bs_mat4 ym = BS_MAT4_IDENTITY;
	bs_m4Translate(&ym, &y, &ym);
	bs_m4Rotate(&ym, &rotation, &ym);
	bs_m4Scale(&ym, &BS_V3(radius, radius, radius), &ym);

	bs_mat4 zm = BS_MAT4_IDENTITY;
	bs_m4Translate(&zm, &z, &zm);
	bs_m4Rotate(&zm, &zr, &zm);
	bs_m4Scale(&zm, &BS_V3(radius, radius, radius), &zm);

	bs_vec3 v0;
	bs_m4MulV3(&transform, &BS_V3(0.0, 0.0, 0.0), &v0);

	bs_vec3 vx, vy, vz;
	bs_m4MulV3(&transform, &BS_V3(axis_length, 0.0, 0.0), &vx);
	bs_m4MulV3(&transform, &BS_V3(0.0, axis_length, 0.0), &vy);
	bs_m4MulV3(&transform, &BS_V3(0.0, 0.0, axis_length), &vz);

	bsgfx_instanceDepthlessLine(v0, vx, BS_RED);
	bsgfx_instanceDepthlessLine(v0, vy, BS_GREEN);
	bsgfx_instanceDepthlessLine(v0, vz, BS_BLUE);

	bsgfx_instanceCone(xm, radius, 0, 0, _bsmod_.axis == 0 ? $yellow_material()->id : $red_material()->id);
	bsgfx_instanceCone(ym, radius, 0, 0, _bsmod_.axis == 1 ? $yellow_material()->id : $green_material()->id);
	bsgfx_instanceCone(zm, radius, 0, 0, _bsmod_.axis == 2 ? $yellow_material()->id : $blue_material()->id);

	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	int white = bs_queryAtlas(atlas, "white");

	bs_vec2 click_size = { BSGFX_AXIS_CLICK_SIZE, BSGFX_AXIS_CLICK_SIZE };

	// dux_atlasHiResInstance(atlas, xs, white, 0, click_size, BS_V4(1, 0, 0, 1), false);
	// dux_atlasHiResInstance(atlas, ys, white, 0, click_size, 
	// BS_V4(0, 1, 0, 1), false);
	// dux_atlasHiResInstance(atlas, zs, white, 0, click_size, BS_V4(0, 0, 1, 1), false);

	static int last_axis = -1;
	static bs_vec2 last_cursor, pressed_cursor;
	bs_vec2 cursor = bs_windowCursorPosition(bs_scope()->context);

	static struct {
		float rotation;
	}*initial_values;
	static float tile_remainder[3];

	static int allocated_rotations;

	if (allocated_rotations < _bsmod_.selected_ids.capacity) {
		initial_values = bs_realloc(initial_values, _bsmod_.selected_ids.capacity * sizeof(*initial_values));
		//memset(initial_values + allocated_rotations, 0, (bsgfx_debug.selected_capacity - allocated_rotations) * sizeof(*initial_values));
		allocated_rotations = _bsmod_.selected_ids.capacity;
	}

	bs_ivec2 resolution = bs_resolution(bs_scope()->context);

   /**
    Detect clicked axis
    */
	float width = 36;
	bs_vec3 screen_coordinates[] = {
		_bsmod_worldToScreenCoords(x, width),
		_bsmod_worldToScreenCoords(y, width),
		_bsmod_worldToScreenCoords(z, width),
	};
	static bs_vec3 start_coordinate;
	static bs_vec2 start_direction;
	bs_vec3 closest_coordinate;
	float closest_z = BS_FLT_MAX;
	int closest_axis = 0;

	for (int i = 0; i < 3; i++) {
		if (screen_coordinates[i].z < closest_z) {

			if (bs_rectangleVsPoint(&screen_coordinates[i].xy, &BS_V2(width, width), &cursor)) {
				closest_coordinate = screen_coordinates[i];
				closest_z = screen_coordinates[i].z;
				closest_axis = i;
			}
		}
	}

	if (closest_z != BS_FLT_MAX) {
		if (bs_leftClickOnce()) {
			_bsmod_.ui_blocked = true;
			_bsmod_.axis = closest_axis;
			start_coordinate = _bsmod_worldToScreenCoords(origin, 1.0);
			bs_v2Normalize(&BS_V2_SUB(cursor, start_coordinate.xy), &start_direction);
		}
	}

	//bsgfx_instantiateQuad(bsgfx_subtypes()[BSGFX_SUBTYPE_UI], bsgfx_matrix(sx, BS_V3(width, width, 0.0)), $BSMOD_ATLAS_UI_white()->coords, 0, 0, $yellow_material()->id);
	//bsgfx_instantiateQuad(bsgfx_subtypes()[BSGFX_SUBTYPE_UI], bsgfx_matrix(sy, BS_V3(width, width, 0.0)), $BSMOD_ATLAS_UI_white()->coords, 0, 0, $yellow_material()->id);
	//bsgfx_instantiateQuad(bsgfx_subtypes()[BSGFX_SUBTYPE_UI], bsgfx_matrix(sz, BS_V3(width, width, 0.0)), $BSMOD_ATLAS_UI_white()->coords, 0, 0, $yellow_material()->id);

	//bsgfx_instancePoint(px1, BS_YELLOW, 16.0);
	//int cone_subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_CONE_MESH];
	//if (bs_leftClickOnce() && _bsmod_.hovering.subtype == cone_subtype) {
	//	pressed_cursor = cursor;
	//	int new_axis = _bsmod_.hovering.instance_id - editor_cone_offset;
	//	if (new_axis >= 0 && new_axis < 3)
	//		_bsmod_.axis = _bsmod_.hovering.instance_id - editor_cone_offset;
	//}
	static float last_angle = 0.0f;


	if (rotation_offset != -1 && bs_keyDownOnce(BS_KEY_ALT)) {
		bs_vec2 up = BS_V2(0.0, 1.0);
		bs_vec2 diff = BS_V2_SUB(cursor, start_coordinate.xy);
		bs_v2Normalize(&BS_V2(diff.x, diff.y), &diff);

		float dot = bs_v2Dot(&up, &diff);
		float cross = up.x * diff.y - up.y * diff.x;
		last_angle = bs_degrees(atan2(cross, dot));
		if (last_angle < 0.0)
			last_angle += 360.0;

		for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
			int* id = bs_fetchUnit(&_bsmod_.selected_ids, i);
			unsigned char* data = bsgfx_getRaw(type, *id);

			bs_vec3* r = data + rotation_offset;

			initial_values[i].rotation = r->a[_bsmod_.axis];
		}
	}

	if (_bsmod_.axis != -1) {
	   /**
	    Rotate
	    */
		if (rotation_offset != -1 && bs_keyDown(BS_KEY_ALT)) {

			bs_vec2 up = BS_V2(0.0, 1.0);
			bs_vec2 diff = BS_V2_SUB(cursor, start_coordinate.xy);

			const float angle_snap = 15.0;
			const int segments = 16;
			unsigned char alpha = 255;

			bs_Range range;
			bs_mat4 m = BS_MAT4_IDENTITY;
			bs_m4Translate(&m, &origin, &m);

			if (_bsmod_.axis == 0) {
				bs_m4Rotate(&m, &zr, &m);
				bsgfx_instanceDepthlessCircle(&m, segments, axis_length, BS_RGBA(0, 0, 255, alpha), &range);
			}
			else if (_bsmod_.axis == 1) {
				bs_m4Rotate(&m, &zr, &m);
				bsgfx_instanceDepthlessCircle(&m, segments, axis_length, BS_RGBA(0, 255, 0, alpha), &range);
			}
			else if (_bsmod_.axis == 2) {
				bs_m4Rotate(&m, &xr, &m);
				bsgfx_instanceDepthlessCircle(&m, segments, axis_length, BS_RGBA(255, 0, 0, alpha), &range);
			}

			bs_v2Normalize(&diff, &diff);

			float dot = bs_v2Dot(&up, &diff);

			float cross = up.x * diff.y - up.y * diff.x;
			float current_angle = bs_degrees(atan2(cross, dot));
			if (current_angle < 0.0)
				current_angle += 360.0;

			float delta_angle = current_angle - last_angle;

			for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
				int* id = bs_fetchUnit(&_bsmod_.selected_ids, i);
				unsigned char* data = bsgfx_getRaw(type, *id);

				bs_vec3* r = data + rotation_offset;

				float* result = r->a + _bsmod_.axis;
				*result = initial_values[i].rotation + delta_angle;
				*result = bs_round((*result) / angle_snap) * angle_snap;

				//bsgfx_instanceHintF(menu, origins[_bsmod_.axis], "%f", *result);

				bsgfx_map(type, *id);
			}
		}
	   /**
	    Translate / Scale
	    */
		else {
			const float d45 = bs_radians(45);
			bs_mat3 r = {
				1, 0, 0,
				0, cos(d45), -sin(d45),
				0, sin(d45), cos(d45)
			};

			bs_vec3 mul;
			bs_m3MulV3(&r, &directions[_bsmod_.axis], &mul);

			if (bs_abs(mul.y) < 0.1) // hack
				mul.y += mul.z;

			bs_vec2 diff;
			bs_v2Sub(&last_cursor, &cursor, &diff);

			float magnitude = bs_v2Magnitude(&diff);
			bs_v2Normalize(&diff, &diff);

			float d = bs_v2Dot(&mul.xy, &diff) * magnitude;

			float scales[3] = { BSGFX_TILE_SIZE.x, BSGFX_TILE_SIZE.y, BSGFX_TILE_SIZE.y };

			if (bs_keyDown(BS_KEY_LEFT_CONTROL)) {
				for (int j = 0; j < 3; j++) {
					float move_tiles = (directions[_bsmod_.axis].a[j] * -d / scales[j]) / 2.0f;
					for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
						int* id = bs_fetchUnit(&_bsmod_.selected_ids, i);
						unsigned char* data = bsgfx_getRaw(type, *id);
						bs_vec3* p = data + position_offset;

						p->a[j] += 0.1 * move_tiles;
						bsgfx_map(type, *id);
					}
				}
			}
			else if (bs_abs(d) > 0.5f) {
				if (scale_offset != -1 && bs_keyDown(BS_KEY_LEFT_SHIFT)) {
					float move_tiles = (directions[_bsmod_.axis].a[_bsmod_.axis] * -d / scales[_bsmod_.axis]) / 2.0f;

					tile_remainder[_bsmod_.axis] += move_tiles;

					if (bs_abs(tile_remainder[_bsmod_.axis]) >= 0.5f) {
						int half_tile_steps = (int)round(tile_remainder[_bsmod_.axis] * 1.0f);

						for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
							int* id = bs_fetchUnit(&_bsmod_.selected_ids, i);
							unsigned char* data = bsgfx_getRaw(type, *id);
							bs_vec3* s = data + scale_offset;

							s->a[_bsmod_.axis] += half_tile_steps * 0.5;
							bsgfx_map(type, *id);
						}

						tile_remainder[_bsmod_.axis] -= half_tile_steps / 2.0f;
					}
				}
				else {
					for (int j = 0; j < 3; j++) {
						float move_tiles = (directions[_bsmod_.axis].a[j] * -d / scales[j]) / 2.0f;

						tile_remainder[j] += move_tiles;

						if (bs_abs(tile_remainder[j]) >= 0.5f) {
							int half_tile_steps = (int)bs_round(tile_remainder[j] * 2.0f);
							for (int i = 0; i < _bsmod_.selected_ids.count; i++) {
								int* id = bs_fetchUnit(&_bsmod_.selected_ids, i);
								unsigned char* data = bsgfx_getRaw(type, *id);
								bs_vec3* p = data + position_offset;

								p->a[j] += half_tile_steps * 0.5;
								p->a[j] = bs_round(p->a[j] * 2.0) * 0.5;
								bsgfx_map(type, *id);
							}
							tile_remainder[j] -= half_tile_steps / 2.0f;
						}
					}
				}
			}
		}
	}
	last_cursor = cursor;
	last_axis = _bsmod_.axis;
}
