#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(push_constant) uniform constants {
	mat4 a, b;
} pushConst;

vec3 bsgfx_RGB(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 BSGFX_HSB(vec3 rgb) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(rgb.xxx + K.xyz) * 6.0 - K.www);
    return rgb.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), rgb.y);
}

void main() {
    float hue = bsgfx_material(in_material).hsva.r;

    vec3 color = bsgfx_RGB(vec3(hue / 360.0, in_texture.x, in_texture.y));
    out_color = vec4(color, 1.0);

    out_index = in_instance;
    out_flags = in_flags;
}
