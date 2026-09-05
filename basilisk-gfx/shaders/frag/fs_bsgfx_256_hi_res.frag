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

layout(set = BSGFX_SET_64, binding = BSGFX_BINDING_64) uniform sampler2DArray images_64;
layout(set = BSGFX_SET_256, binding = BSGFX_BINDING_256) uniform sampler2DArray images_256;
layout(set = BSGFX_SET_512, binding = BSGFX_BINDING_512) uniform sampler2DArray images_512;

layout(push_constant) uniform constants {
	mat4 a, b;
} pushConst;

void main() {
    bsgfx_MaterialContract m = bsgfx_material(in_material);

    out_index = in_instance;
    out_flags = in_flags;
}
