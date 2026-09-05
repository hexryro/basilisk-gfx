#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#define BSGFX_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;
layout(location = 9) in vec2 in_texture_unprocessed;

layout(set = BSMOD_SET_IMAGE_ATLAS_ICONS, binding = BSMOD_BINDING_IMAGE_ATLAS_ICONS) uniform sampler2D atlas_texture[BSMOD_ATLAS_ICONS_COUNT];

layout(push_constant) uniform constants {
    mat4 camera;
    int atlas_binding;
} pushConst;

void main() {
    out_color = vec4(1.0);
    out_normal.xyz = in_normal;
    out_normal.a = 0.0;
    out_position = vec4(in_world_position, 1.0);
    out_color = texture(atlas_texture[pushConst.atlas_binding], vec2(in_texture.x, 1.0 - in_texture.y));

}