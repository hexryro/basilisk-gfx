#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"

layout (location = 0) out vec4 out_color;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(set = BSGFX_SET_FONTS, binding = BSGFX_BINDING_FONT_SANS_SERIF) uniform sampler2D font_atlases[BSGFX_MAX_FONTS_COUNT];

void main() {
   // out_color = vec4(in_normal, 1.0);
   // out_normal.xyz = in_normal;
   // out_normal.a = 0.0;
   // out_position = vec4(in_world_position, 1.0);
   out_color = texture(font_atlases, vec2(in_texture.x, 1.0 - in_texture.y));
   //
   // out_normal.xyz = in_normal;
   // if (out_normal.x != 0.0 || out_normal.y != 0.0 || out_normal.z != 0.0)
   //     out_normal.a = 1.0;

    bsgfx_MaterialContract material = bsgfx_material(in_material);

    out_color.a = out_color.r * material.color.a;
    out_color.rgb = material.color.rgb;
    if (out_color.a == 0.0) {
        if ((in_flags & BSGFX_ID_FONT_IS_SELECTED) != 0)
            out_color = vec4(0.2, 0.35, 0.8, 0.8);
        else
            discard;
    }

    out_color = vec4(1.0);

    //out_index = in_instance;
    //out_flags = in_flags;
}
