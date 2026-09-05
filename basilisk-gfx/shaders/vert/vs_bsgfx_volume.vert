#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = 0) in vec3 bs_Position;
layout (location = 1) in vec2 bs_Texture;
layout (location = 2) in float bsgfx_VolumeId;

layout(push_constant) uniform constants {
    mat4 camera;
} pushConst;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec2 out_texture;
layout(location = 2) out float out_volume_id;

void main() {
	//out_volume_id = bsgfx_VolumeId;
    out_position = bs_Position;
    out_texture = bs_Texture;

    gl_Position = pushConst.camera * vec4(bs_Position, 1.0);
    

   // gl_Position = runtime.proj * runtime.view * vec4(bs_animate(bs_Entity, bs_Position, bs_BoneId, bs_Weight).xyz, 1.0);

    gl_Position.y = -gl_Position.y;
    gl_Position.z = (gl_Position.z + gl_Position.w) / 2.0;
}
