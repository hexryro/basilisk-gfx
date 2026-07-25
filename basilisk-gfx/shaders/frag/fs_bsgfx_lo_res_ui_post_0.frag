#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = BSGFX_LO_UI_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_COLOR_ATTACHMENT) uniform sampler2D attachment_color;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_FLAGS_ATTACHMENT) uniform usampler2D in_attachment_flags_read;

layout(location = 4) in vec3 in_texture;

void main() {

    uint flags = texture(in_attachment_flags_read, vec2(in_texture.x, 1.0 - in_texture.y)).r;

    vec3 color = texture(attachment_color, vec2(in_texture.x, 1.0 - in_texture.y)).rgb;
    out_color = vec4(1.0, 0.0, 1.0, 1.0);
   // out_color.rgb = color;

    
}
