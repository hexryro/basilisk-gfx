#version 460 core
#extension GL_EXT_ray_tracing : require
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout(location = 0) rayPayloadInEXT bsgfx_RayPayload payload;
layout(binding = BSGFX_BINDING_RAY_TRACE_OUTPUT, set = BSGFX_SET_RAY_TRACE_OUTPUT, rgba32f) uniform image2D img;

void main() {
	payload.hit_sky = 1.0;

		vec4 color = vec4(0, 1, 0, 1);
	ivec2 pixel = ivec2(gl_LaunchIDEXT.xy);

    imageStore(img, pixel, color);
}