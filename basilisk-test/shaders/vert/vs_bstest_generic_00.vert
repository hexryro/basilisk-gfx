#version 450
#extension GL_ARB_shading_language_include : require

layout (location = 0) in vec3 bs_Position;

void main() {
    gl_Position = vec4(bs_Position, 1.0);
}
