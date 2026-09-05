#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

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

layout(set = BSGFX_SET_FONT_TEMPLE, binding = BSGFX_BINDING_FONT_TEMPLE) uniform sampler2D font_atlas;

void main() {
    out_color = vec4(in_normal, 1.0);
    out_normal.xyz = in_normal;
    out_normal.a = 0.0;
    out_position = vec4(in_world_position, 1.0);
    out_color = texture(font_atlas, vec2(in_texture.x, 1.0 - in_texture.y)) * in_color;

    out_normal.xyz = in_normal;
    if (out_normal.x != 0.0 || out_normal.y != 0.0 || out_normal.z != 0.0)
        out_normal.a = 1.0;

    if (out_color.a == 0.0)
        discard;

    out_index = in_instance;
    out_flags = in_flags;
}
