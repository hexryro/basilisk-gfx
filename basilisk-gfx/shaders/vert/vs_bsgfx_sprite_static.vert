#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = 0) in vec3 bs_Position;
layout (location = 1) in vec2 bs_Texture;
layout (location = 2) in vec4 bs_Color;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec4 out_color;
layout(location = 2) out vec3 out_normal;
layout(location = 3) out vec3 out_world_position;
layout(location = 4) out vec3 out_texture;
layout(location = 5) out uint out_instance;
layout(location = 6) out uint out_flags;
layout(location = 7) out uint out_material;
layout(location = 8) out float out_depth;

layout(push_constant) uniform constants {
	mat4 camera;
} pushConst;

void main() {
    out_position = bs_Position;
    out_color = bs_Color;
    out_texture = vec3(bs_Texture, 0.0);
    out_world_position = bs_Position;

    gl_Position = bsgfx_process(pushConst.camera * vec4(bs_Position, 1.0));
    out_depth = gl_Position.z / gl_Position.w;
}
