
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

 /*
  _bsgfx_collider.c
  */

#include <bsgfx_internal.h>

#include <assert.h>
#include <stdio.h>



  /*==============================================================================
   * Macros
   *============================================================================*/

#define BSGFX_MAX_SLOPE (80.0)
#define BSGFX_COLLIDER(mx, my, mz, Mx, My, Mz) \
	{ .position = { .x = mx, .y = my, .z = mz }, .scale = { .x = Mx, .y = My, .z = Mz } }



  /*==============================================================================
   * Collision Detection & Response
   *============================================================================*/

 /**
  Slope ascent
  */
static inline void _bsgfx_climbSlopeAxis(bsgfx_Collider* collider, bs_vec3* velocity, int axis, float angle, bs_vec3 normal) {
	float move_distance = bs_abs(velocity->a[axis]);
	float climb_velocity = bs_sin(angle) * move_distance;

	if (velocity->y <= climb_velocity) {
		velocity->y = climb_velocity;
		velocity->a[axis] = bs_cos(angle) * move_distance * (float)bs_sign(velocity->a[axis]);
		collider->collision |= BSGFX_COLLISION_BELOW | BSGFX_COLLISION_SLOPE;
		collider->angle = angle;
		collider->normal = normal;
	}
}

 /**
  Slope descent
  */
static inline bs_Ray _bsgfx_descendSlopeRay(bsgfx_Collider* collider, bs_vec3* velocity, const bs_vec3* position, int axis) {
	const int axis_direction = bs_sign(velocity->a[axis]);
	int opposite_axis = axis == 0 ? 2 : 0;

	bs_Ray ray = {
		.direction = BS_V3(0.0, -1.0, 0.0),
		.length = BS_FLT_MAX,
	};

	ray.origin = (axis_direction == 1) ? collider->aabb.min : BS_V3(collider->aabb.max.x, collider->aabb.min.y, collider->aabb.max.z);
	ray.origin.a[opposite_axis] += (collider->aabb.max.a[opposite_axis] - collider->aabb.min.a[opposite_axis]) * axis_direction / 2.0; // put ray in middle

	bs_vec3 v;
	bs_v3AddS(&ray.origin, BSGFX_COLLIDER_SKIN, &v);
	bs_v3Add(position, &v, &ray.origin);

	return ray;
}

static bool _bsgfx_descendSlopeRayCast(
	bsgfx_Collider* collider,
	bs_vec3* velocity,
	const bs_Ray* ray,
	const bs_vec3* position,
	const bs_vec4* rotation,
	const bs_vec3* scale,
	int axis)
{
	//bs_Ray left_down_ray = _bsgfx_leftMaxSlopeRay(collider, velocity, p, axis);
	//bs_Ray right_down_ray = _bsgfx_rightMaxSlopeRay(collider, velocity, p, axis);

	//bsgfx_slideDownMaxSlopeAxis(collider, &left_down_ray, position, rotation, scale, velocity, axis);
	//bsgfx_slideDownMaxSlopeAxis(collider, &right_down_ray, position, rotation, scale, velocity, axis);

	if (collider->collision & BSGFX_COLLISION_MAX_SLOPE)
		return true;

	bs_RayVsObb result;
	bs_rayVsObb(ray, position, rotation, scale, &result);

	if (!result.hit)
		return false;

#ifdef _DEBUG
	if (result.normal.x == 0.0 && result.normal.y == 0.0 && result.normal.z == 0.0)
		bs_warnF("Normal is 0, 0, 0");
#endif

	float distance = bs_v3Distance(&ray->origin, &result.coordinate);
	float angle = bs_v3Angle(&result.normal, &BS_V3(0, 1, 0));
	float angle_deg = bs_degrees(angle);

	if (angle == 0.0 || angle_deg > BSGFX_MAX_SLOPE)
		return false;

	if (bs_sign(result.normal.a[axis]) != bs_sign(velocity->a[axis]))
		return false;

	if ((distance - BSGFX_COLLIDER_SKIN) > (bs_tan(angle) * bs_abs(velocity->a[axis])))
		return false;

	float move_distance = bs_abs(velocity->a[axis]);
	float descend_velocity = bs_sin(angle) * move_distance;
	velocity->a[axis] = bs_cos(angle) * move_distance * (float)bs_sign(velocity->a[axis]);
	velocity->y -= descend_velocity;

	collider->angle = angle;
	collider->normal = result.normal;
	collider->collision |= BSGFX_COLLISION_BELOW | BSGFX_COLLISION_SLOPE_DESCENT;

	return true;
}

static void _bsgfx_descendSlopeAxis(bsgfx_Collider* collider, bs_vec3* velocity, const bs_vec3* position, int axis) {
	bs_Ray ray = _bsgfx_descendSlopeRay(collider, velocity, position, axis);

	for (int i = 0; i < _bsgfx_app_.sweep_collisions.count; i++) {
		bsgfx_SweepCollision* sweep_collision = bs_fetchUnit(&_bsgfx_app_.sweep_collisions, i);

		if (_bsgfx_descendSlopeRayCast(collider, velocity, &ray, &sweep_collision->position, &sweep_collision->rotation, &sweep_collision->scale, axis))
			collider->collision |= sweep_collision->flags;
	}
}

 /**
  Collision detection
  */
static float _bsgfx_applyCollisionRaycast(bsgfx_Collider* collider, bs_vec3* velocity, float ray_length, float distance, bs_vec3 normal, int axis, int axis_direction, int x) {
	float result = (distance - BSGFX_COLLIDER_SKIN) * (axis_direction);

	if (axis == 1) {
		// Y response
		velocity->y = result;

		// fixes jittering when colliding with a slope and ceiling
		if (collider->collision & BSGFX_COLLISION_SLOPE) {
			float tx = bs_tan(collider->angle) * (float)bs_sign(velocity->x);
			float tz = bs_tan(collider->angle) * (float)bs_sign(velocity->z);
#ifdef _DEBUG
			if (tx == 0.0 || tz == 0.0)
				bs_warnF("Division by 0\n");
#endif
			velocity->x = tx == 0.0 ? velocity->x : velocity->y / tx;
			velocity->z = tz == 0.0 ? velocity->z : velocity->y / tz;
		}

		ray_length = distance;
		collider->collision |= (axis_direction == 1) ? BSGFX_COLLISION_ABOVE : BSGFX_COLLISION_BELOW;
	}
	else {
		if (bs_abs(velocity->a[axis]) < BSGFX_COLLIDER_SKIN)
			ray_length = 2 * BSGFX_COLLIDER_SKIN;

		float angle = bs_v3Angle(&normal, &BS_V3(0, 1, 0));
		float angle_deg = bs_degrees(angle);

		// ascend slope
		const int first_row = (axis_direction == 1) ? collider->resolution.a[axis] - 1 : 0;
		if (x == first_row && angle_deg <= BSGFX_MAX_SLOPE) {
			float distance_to_slope = (angle == collider->angle_old) ? 0.0 : result;

			if (collider->collision & BSGFX_COLLISION_SLOPE_DESCENT) {
				collider->collision &= ~BSGFX_COLLISION_SLOPE_DESCENT;
				*velocity = collider->velocity_old;
			}

			velocity->a[axis] -= distance_to_slope;
			_bsgfx_climbSlopeAxis(collider, velocity, axis, angle, normal);
			velocity->a[axis] += distance_to_slope;
		}

		// X and Z response
		if (!(collider->collision & BSGFX_COLLISION_SLOPE) || angle_deg > BSGFX_MAX_SLOPE) {
			velocity->a[axis] = result;

			if (collider->collision & BSGFX_COLLISION_SLOPE)
				velocity->y = bs_tan(collider->angle) * bs_abs(velocity->a[axis]);

			ray_length = distance;

			if (axis == 0)
				collider->collision |= (axis_direction == 1) ? BSGFX_COLLISION_RIGHT : BSGFX_COLLISION_LEFT;
			else
				collider->collision |= (axis_direction == 1) ? BSGFX_COLLISION_FRONT : BSGFX_COLLISION_BACK;
		}
	}

	return ray_length;
}

static inline bs_Ray _bsgfx_collisionRay(bsgfx_Collider* collider, bs_vec3* velocity, const bs_vec3* position, const int axis) {
	const int axis_direction = bs_sign(velocity->a[axis]);
	float len = bs_abs(velocity->a[axis]) + BSGFX_COLLIDER_SKIN;

	bs_vec3 origin;
	bs_v3AddS((axis_direction == 1) ? &collider->aabb.max : &collider->aabb.min, BSGFX_COLLIDER_SKIN, &origin);
	bs_v3Add(position, &origin, &origin);

	bs_Ray ray = {
		.length = len,
		.origin = origin,
	};

	ray.direction.a[axis] = axis_direction;

	return ray;
}

static inline bs_vec3 _bsgfx_collisionRayStepped(bsgfx_Collider* collider, bs_vec3 origin, int x, int y, bs_vec3 steps, bs_vec3* velocity, const int axis, int axis_direction) {
	bs_vec3 result;
	bs_vec3 delta;
	if		(axis == 0) delta = BS_V3(0.0, steps.y * x * -axis_direction, steps.z * y * -axis_direction);
	else if (axis == 1) delta = BS_V3(steps.x * x * -axis_direction + velocity->x, 0.0, steps.z * y * -axis_direction + velocity->z);
	else                delta = BS_V3(steps.x * y * -axis_direction, steps.y * x * -axis_direction, 0.0);
	bs_v3Add(&origin, &delta, &result);
	return result;
}

static inline bs_vec3 _bsgfx_colliderRaySteps(const bsgfx_Collider* collider, int axis) {
	return BS_V3(
		(collider->aabb.max.x - collider->aabb.min.x) / ((float)collider->resolution.a[axis] - 1.0),
		(collider->aabb.max.y - collider->aabb.min.y) / ((float)collider->resolution.a[axis] - 1.0),
		(collider->aabb.max.z - collider->aabb.min.z) / ((float)collider->resolution.a[axis] - 1.0));
}

static void _bsgfx_applyCollisionAxis(bsgfx_Collider* collider, bs_vec3* velocity, const bs_vec3* position, const int axis) {
	const int axis_direction = bs_sign(velocity->a[axis]);

	bs_vec3 steps = _bsgfx_colliderRaySteps(collider, axis);
	bs_Ray ray = _bsgfx_collisionRay(collider, velocity, position, axis);
	bs_vec3 origin = ray.origin;

	for (int x = 0; x < collider->resolution.a[axis]; x++) {
		for (int y = 0; y < collider->resolution.a[axis]; y++) {
			ray.origin = _bsgfx_collisionRayStepped(collider, origin, x, y, steps, velocity, axis, axis_direction);

			bs_vec3 normal = { 0 };
			float distance = BS_FLT_MAX;

			bsgfx_ColliderFlags flags = 0;
			for (int i = 0; i < _bsgfx_app_.sweep_collisions.count; i++) {
				bsgfx_SweepCollision* sweep_collision = bs_fetchUnit(&_bsgfx_app_.sweep_collisions, i);
				bs_vec3 coordinate = { 0 }, new_normal = { 0 };

				bs_RayVsObb result;
				bs_rayVsObb(&ray, &sweep_collision->position, &sweep_collision->rotation, &sweep_collision->scale, &result);

				if (!result.hit)
					continue;

				float new_distance = bs_v3Distance(&ray.origin, &coordinate);
				if (new_distance >= distance)
					continue;

				distance = new_distance;
				normal = new_normal;
				flags = sweep_collision->flags;
			}

			if (distance == BS_FLT_MAX)
				continue;

			if (distance > ray.length)
				continue;

			ray.length = _bsgfx_applyCollisionRaycast(collider, velocity, ray.length, distance, normal, axis, axis_direction, x);
			collider->collision |= flags;

			//for (int i = 0; i < _bsgfx_meshes_count; i++) {
			//	bs_Aabb* aabbs = _bsgfx_collider_prefabs[_bsgfx_meshes[i].type].aabbs;
			//	int count = _bsgfx_collider_prefabs[_bsgfx_meshes[i].type].count;
			//	if (_bsgfx_applyCollisionRay(collider, velocity, &ray, ))
			//}
		}
	}
}

 /**
  Secondary slope correction
  Fixes issues going up slopes consecutively by casting a ray forward and finding a new (secondary) slope
  */
static inline bs_Ray _bsgfx_secondarySlopeRay(bsgfx_Collider* collider, bs_vec3* velocity, const bs_vec3* position, int axis) {
	const int axis_direction = bs_sign(velocity->a[axis]);

	bs_Ray ray = {
		.length = bs_abs(velocity->a[axis]) + BSGFX_COLLIDER_SKIN,
		.origin = collider->aabb.min,
	};
	ray.direction.a[axis] = axis_direction;

	bs_vec3 origin = collider->aabb.min;
	origin.a[axis] = (axis_direction == 1) ? collider->aabb.max.a[axis] : origin.a[axis];

	bs_v3AddS(&origin, BSGFX_COLLIDER_SKIN, &origin);
	bs_v3Add(position, &origin, &origin);

	return ray;
}

static inline bs_vec3 _bsgfx_secondarySlopeRayStepped(bs_vec3* velocity, bs_vec3 origin, bs_vec3 steps, int axis, int y) {
	bs_vec3 result;
	bs_vec3 delta = axis == 0 ?
		BS_V3(0.0, velocity->y, steps.z * y) :
		BS_V3(steps.x * y, velocity->y, 0.0);
	bs_v3Add(&origin, &delta, &result);
	return result;
}

static void _bsgfx_applySecondarySlopeRaycast(
	bsgfx_Collider* collider,
	bs_vec3* velocity,
	bs_Ray* ray,
	const bs_vec3* position,
	const bs_vec4* rotation,
	const bs_vec3* scale,
	int axis,
	int axis_direction)
{
	bs_RayVsObb result;
	bs_rayVsObb(ray, position, rotation, scale, &result);
	if (!result.hit)
		return;

#ifdef _DEBUG
	if (result.normal.x == 0.0 && result.normal.y == 0.0 && result.normal.z == 0.0)
		bs_warnF("Normal is 0, 0, 0");
#endif

	float distance = bs_v3Distance(&ray->origin, &result.coordinate);
	if (distance > ray->length)
		return;

	float angle = bs_v3Angle(&result.normal, &BS_V3(0, 1, 0));
#ifdef _DEBUG
	if (angle == 0.0)
		bs_warnF("Angle is 0");
#endif

	if (angle != collider->angle) {
		velocity->a[axis] = (distance - BSGFX_COLLIDER_SKIN) * axis_direction;
		collider->angle = angle;
		collider->normal = result.normal;
		ray->length = distance;
	}
}

static void _bsgfx_applySecondarySlopeAxis(bsgfx_Collider* collider, bs_vec3* velocity, const bs_vec3* position, int axis) {
	const int axis_direction = bs_sign(velocity->a[axis]);

	if (axis_direction == 0) return;

	bs_Ray ray = _bsgfx_secondarySlopeRay(collider, velocity, position, axis);
	bs_vec3 origin = ray.origin;
	bs_vec3 steps = _bsgfx_colliderRaySteps(collider, axis);

	for (int y = 0; y < collider->resolution.a[axis]; y++) {
		ray.origin = _bsgfx_secondarySlopeRayStepped(velocity, origin, steps, axis, y);

		for (int i = 0; i < _bsgfx_app_.sweep_collisions.count; i++) {
			bsgfx_SweepCollision* sweep_collision = bs_fetchUnit(&_bsgfx_app_.sweep_collisions, i);
			_bsgfx_applySecondarySlopeRaycast(collider, velocity, &ray, &sweep_collision->position, &sweep_collision->rotation, &sweep_collision->scale, axis, axis_direction);
		}
	}
}

BSGFXAPI void _bsgfx_sweepCollisions(float sweep_radius, const bs_vec3* position) {
	_bsgfx_app_.sweep_collisions.count = 0;

	for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
		bsgfx_Primitive* primitive = _bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);

		if (bs_sphereVsObbTest(position, sweep_radius, &primitive->position, &primitive->rotation, &primitive->scale)) {
			bs_pushBack(&_bsgfx_app_.sweep_collisions, &(bsgfx_SweepCollision) {
				.position = primitive->position,
				.rotation = primitive->rotation,
				.scale = primitive->scale,
				.flags = primitive->collision,
			});
		}
	}

	//for (int i = 0; i < _bsgfx_meshes_count; i++) {
	//	if (_bsgfx_meshes[i].type >= BSGFX_MESH_COUNT)
	//		continue;
	//
	//	bsgfx_ColliderPrefab* prefabs = _bsgfx_collider_prefabs[_bsgfx_meshes[i].type].prefabs;
	//	int prefabs_count = _bsgfx_collider_prefabs[_bsgfx_meshes[i].type].count;
	//
	//	for (int j = 0; j < prefabs_count; j++) {
	//		bs_vec3 p = bs_v3Add(prefabs[j].position, _bsgfx_meshes[i].position);
	//		bs_vec3 s = bs_v3Mul(prefabs[j].scale, _bsgfx_meshes[i].scale);
	//
	//		if (bs_sphereVsBox(position, collider->sweep_radius, p, _bsgfx_meshes[i].rotation, s, NULL, NULL, NULL)) {
	//			if (_bsgfx_sweep_collisions_allocated <= _bsgfx_sweep_collisions_count) {
	//				_bsgfx_sweep_collisions_allocated += 32;
	//				_bsgfx_sweep_collisions = bs_realloc(_bsgfx_sweep_collisions, _bsgfx_sweep_collisions_allocated * sizeof(*_bsgfx_sweep_collisions));
	//			}
	//			_bsgfx_sweep_collisions[_bsgfx_sweep_collisions_count].position = p;
	//			_bsgfx_sweep_collisions[_bsgfx_sweep_collisions_count].rotation = _bsgfx_meshes[i].rotation;
	//			_bsgfx_sweep_collisions[_bsgfx_sweep_collisions_count].scale = s;
	//			_bsgfx_sweep_collisions[_bsgfx_sweep_collisions_count++].flags = 0;
	//		}
	//	}
	//}
}



  /*==============================================================================
   * Interface
   *============================================================================*/

BSGFXAPI bsgfx_Collider _bsgfx_collider(bs_Aabb aabb, bs_vec3 scale, bs_ivec3 resolution, float sweep_radius) {
	bsgfx_Collider collider = {
		.resolution = resolution,
		.sweep_radius = sweep_radius,
		.scale = { 1.0, 1.0, 1.0 },
	};
	bs_v3Mul(&aabb.min, &scale, &collider.aabb.min);
	bs_v3Mul(&aabb.max, &scale, &collider.aabb.max);

	return collider;
}

BSGFXAPI void _bsgfx_applyCollisions(bsgfx_Collider* collider, const bs_vec3* position, bs_vec3* velocity) {
	collider->collision = BSGFX_COLLISION_NONE;
	collider->angle_old = collider->angle;
	collider->angle = 0.0;
	collider->normal = BS_V3(0, 0, 0);
	collider->velocity_old = *velocity;

	_bsgfx_sweepCollisions(collider->sweep_radius, position);

	if (_bsgfx_app_.sweep_collisions.count == 0)
		return;

	bsgfx_ColliderFlags flags;
	if (velocity->y < 0.0) {
		flags = collider->collision;
		collider->collision = BSGFX_COLLISION_NONE;

		_bsgfx_descendSlopeAxis(collider, velocity, position, 0);

		collider->collision |= flags;

		_bsgfx_descendSlopeAxis(collider, velocity, position, 2);
	}

	if (velocity->x != 0.0)
		_bsgfx_applyCollisionAxis(collider, velocity, position, 0);

	flags = collider->collision;
	collider->collision = BSGFX_COLLISION_NONE;

	if (velocity->z != 0.0)
		_bsgfx_applyCollisionAxis(collider, velocity, position, 2);

	collider->collision |= flags;

	if (velocity->y != 0.0) {
		_bsgfx_applyCollisionAxis(collider, velocity, position, 1);

		if (collider->collision & BSGFX_COLLISION_SLOPE) {
			flags = collider->collision;
			collider->collision = BSGFX_COLLISION_NONE;

			_bsgfx_applySecondarySlopeAxis(collider, velocity, position, 0);

			collider->collision |= flags;

			_bsgfx_applySecondarySlopeAxis(collider, velocity, position, 2);
		}
	}
}



  /*==============================================================================
   * Debugging
   *============================================================================*/

static inline bs_RGBA _bsgfx_axisColor(int axis) {
	if		(axis == 0) return BS_RGBA(255, 0, 0, 255);
	else if (axis == 1) return BS_RGBA(50, 255, 50, 255);
	else if (axis == 2) return BS_RGBA(0, 150, 255, 255);
	return BS_WHITE;
}

static void _bsgfx_instanceColliderAxis(bsgfx_Collider* collider, const bs_vec3* position, bs_vec3* velocity, int axis) {
	const int axis_direction = bs_sign(velocity->a[axis]);

	bs_vec3 steps = _bsgfx_colliderRaySteps(collider, axis);
	bs_Ray ray = _bsgfx_collisionRay(collider, velocity, position, axis);
	bs_vec3 origin = ray.origin;

	for (int x = 0; x < collider->resolution.a[axis]; x++) {
		for (int y = 0; y < collider->resolution.a[axis]; y++) {
			ray.origin = _bsgfx_collisionRayStepped(collider, origin, x, y, steps, velocity, axis, axis_direction);
			ray.length = 0.1;
			_bsgfx_instanceRay(&ray, _bsgfx_axisColor(axis));
		}
	}

	if (axis != 1) {
		bs_Ray descend_ray = _bsgfx_descendSlopeRay(collider, velocity, position, axis);
		_bsgfx_instanceRay(&descend_ray, _bsgfx_axisColor(axis));
	}


   /* max slopes */
	//bs_Ray ray = _bsgfx_leftMaxSlopeRay(collider, velocity, position);
	//bs_Ray ray = _bsgfx_rightMaxSlopeRay(collider, velocity, position);
}

BSGFXAPI void _bsgfx_instanceSweepCollisions() {
	for (int i = 0; i < _bsgfx_app_.sweep_collisions.count; i++) {
		bsgfx_SweepCollision* sweep_collision = bs_fetchUnit(&_bsgfx_app_.sweep_collisions, i);

		bs_mat4 transform = BS_MAT4_IDENTITY;
		bs_m4Translate(&transform, &sweep_collision->position, &transform);
		bs_m4Rotate(&transform, &sweep_collision->rotation, &transform);
		bs_m4Scale(&transform, &sweep_collision->scale, &transform);

		bs_Aabb aabb = { .min = { -1, -1, -1 }, .max = { 1, 1, 1 } };
		//bsgfx_instanceObb(&aabb, BS_WHITE, &transform);
		bs_warnF("_bsgfx_instanceSweepCollisions not implemented\n");
	}
}

BSGFXAPI void _bsgfx_instanceCollider(bsgfx_Collider* collider, const bs_vec3* position, bs_vec3* velocity) {
	_bsgfx_instanceColliderAxis(collider, position, velocity, 0);
	_bsgfx_instanceColliderAxis(collider, position, velocity, 2);
	_bsgfx_instanceColliderAxis(collider, position, velocity, 1);
//	_bsgfx_instanceSphere(position, collider->sweep_radius);
}

BSGFXAPI void _bsgfx_printCollisions(bsgfx_Collider* collider) {
	bs_U32 c = collider->collision;

	printf("%d, %d, %d (%d)\n",
		c & BSGFX_COLLISION_LEFT ? -1 : (c & BSGFX_COLLISION_RIGHT ? 1 : 0),
		c & BSGFX_COLLISION_BELOW ? -1 : (c & BSGFX_COLLISION_ABOVE ? 1 : 0),
		c & BSGFX_COLLISION_BACK ? -1 : (c & BSGFX_COLLISION_FRONT ? 1 : 0),
		c & BSGFX_COLLISION_SLOPE_DESCENT ? -1 : (c & BSGFX_COLLISION_SLOPE ? 1 : 0));
}
