#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#define BSGFX_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(set = BSGFX_SET_FONTS, binding = BSGFX_BINDING_FONTS) uniform sampler2DArray font_atlas;

void main() {
    int atlas_page = bsgfx_quad_instances[in_instance].header.id;

    vec3 uv = vec3(in_texture.x, 1.0 - in_texture.y, float(atlas_page));
    float r = texture(font_atlas, uv).r;
    out_color = vec4(r, r, r, 1.0);
    //out_color = vec4(in_texture.x, in_texture.y, 0.0, 1.0);

    float sdf = texture(font_atlas, uv).r;
    out_color = vec4(1.0, 1.0, 1.0, sdf);

    float thickness = 0.791;
    float softness = 0.035;

    sdf = smoothstep(1.0 - thickness - softness, 1.0 - thickness + softness, sdf);

   // if (sdf < 0.2)
   //     discard;

   // out_color = vec4(1.0, 1.0, 1.0, sdf);


}
