#include <bsgfx_internal.h>

BSGFXAPI void _val_bsgfx_worldToScreen(const bs_vec3* position, const bs_mat4* camera, const bs_vec2* resolution, bs_vec2* out) {
	bs_vec4 clip;
	bs_m4MulV4(&camera, &BS_V4(position->x, position->y, position->z, 1.0), &clip);

	BSGFX_VALIDATE(clip.w != 0.0,,);

	_bsgfx_worldToScreen(position, camera, resolution, out);
}

BSGFXAPI void _bsgfx_worldToScreen(const bs_vec3* position, const bs_mat4* camera, const bs_vec2* resolution, bs_vec2* out) {
	bs_vec4 clip;
	bs_m4MulV4(&camera, &BS_V4(position->x, position->y, position->z, 1.0), &clip);

	bs_vec3 ndc;
	bs_v3DivS(&clip.xyz, clip.w, &ndc);

	bs_vec2 screen = {
		.x = (ndc.x * 0.5 + 0.5) * resolution->x,
		.y = (ndc.y * 0.5 + 0.5) * resolution->y,
	};

	*out = screen;
}
