#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#define BSMOD_TRACKER_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"

layout (location = 0) in vec3 bs_Position; // todo vec2
layout (location = 1) in vec2 bs_Texture;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec4 out_color;
layout(location = 2) out vec3 out_normal;
layout(location = 3) out vec3 out_world_position;
layout(location = 4) out vec3 out_texture;
layout(location = 5) out uint out_instance;
layout(location = 6) out uint out_flags;
layout(location = 7) out uint out_material;
layout(location = 8) out float out_depth;
layout(location = 9) out vec2 out_texture_unprocessed;

layout(push_constant) uniform constants {
	mat4 camera;
} pushConst;

void main() {
    uint instance = uint(gl_InstanceIndex);
    out_texture = vec3(bsgfx_quadTextureCoordinates(instance, bs_Texture), 0.0);

    out_texture_unprocessed = bs_Texture;

    out_position = bsgfx_quadVertex(instance, bs_Position);

    out_flags = bsgfx_quad_instances[instance].header.flags;
    out_material = bsgfx_quad_instances[int(gl_InstanceIndex)].header.material;
    out_color = bsgfx_material(out_material).color;
    out_instance = instance;
    gl_Position = bsgfx_process(pushConst.camera * vec4(out_position.x, out_position.y, out_position.z, 1.0));

    out_position.z = bsgfx_quad_instances[instance].transform[8];
    out_depth = gl_Position.z / gl_Position.w;
}
