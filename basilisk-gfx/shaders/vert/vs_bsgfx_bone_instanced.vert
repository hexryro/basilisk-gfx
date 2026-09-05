#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_bone.glsl"

layout (location = 0) in vec3 bs_Position;
layout (location = 1) in vec2 bs_Texture;
layout (location = 2) in vec3 bs_Normal;
layout (location = 3) in ivec4 bs_Bone;
layout (location = 4) in vec4 bs_Weight;

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
    uint instance = uint(gl_InstanceIndex);

    vec3 animated_position = bsgfx_animate(int(instance), bs_Position, bs_Bone, bs_Weight);
    mat3 normal_matrix = transpose(inverse(mat3(bsgfx_bone_instances[instance].transform)));
    out_normal = normalize(normal_matrix * bs_Normal);
    out_position = bs_Position;
    out_texture = vec3(bs_Texture, 0.0);

    out_flags = bsgfx_bone_instances[instance].header.flags;
    out_instance = instance;
    out_material = bsgfx_bone_instances[instance].header.material;

    out_world_position = animated_position.xyz;
    vec4 position = vec4(animated_position, 1.0);
    vec4 final = bsgfx_process(pushConst.camera * position);
    gl_Position = final;
    out_depth = gl_Position.z / gl_Position.w;
}
