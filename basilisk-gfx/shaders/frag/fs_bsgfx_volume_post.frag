#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;

void main() {
    out_color = vec4(vec3(1.0), 1.0);
}
