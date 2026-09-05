#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"

layout (location = 0) in vec3 bs_Position;
layout (location = 1) in vec2 bs_Texture;
layout (location = 2) in float bsgfx_VolumeId;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec2 out_texture;
layout(location = 2) out float out_volume_id;

layout(push_constant) uniform constants {
	mat4 camera;
} pushConst;

void main() {
	out_volume_id = bsgfx_VolumeId;

	vec3 position = bsgfx_mesh_instances[int(gl_InstanceIndex)].transform[3].xyz;
    out_texture = bs_Texture;

    gl_Position = bsgfx_process(pushConst.camera * vec4(bs_Position + position, 1.0));
}
