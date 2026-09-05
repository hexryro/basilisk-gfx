#version 450
#extension GL_ARB_shading_language_include : require

layout (location = 0) in vec3 bs_Position;
layout (location = 1) in vec2 bs_Texture;

void main() {
    gl_Position = vec4(1.0);
}
