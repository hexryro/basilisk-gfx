#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_atlas.glsl"

layout (location = 0) in vec3 bs_Position;
layout (location = 1) in vec2 bs_Texture;
layout (location = 2) in vec3 bs_Normal;

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
    float z;
} pushConst;

void main() {
    uint instance = uint(gl_InstanceIndex);

    mat3 normal_matrix = transpose(inverse(mat3(bsgfx_mesh_instances[int(gl_InstanceIndex)].transform)));

    out_position = bs_Position;
    out_normal = normalize(normal_matrix * bs_Normal);
    out_texture = vec3(bs_Texture, 0.0);

    out_world_position = bsgfx_translateMesh(int(gl_InstanceIndex), bs_Position).xyz;

    out_flags = bsgfx_mesh_instances[instance].header.flags;
    out_instance = instance;
    out_material = bsgfx_mesh_instances[instance].header.material;

    vec4 preprocessed = pushConst.camera * vec4(out_world_position, 1.0);
    gl_Position = preprocessed;
    gl_Position = bsgfx_process(pushConst.camera * vec4(out_world_position, 1.0));

    out_depth = gl_Position.z / gl_Position.w;

    vec3 worldPos = out_world_position;

    vec4 clipPos = pushConst.camera * vec4(worldPos, 1.0);

    float ndcDepth = clipPos.z / clipPos.w;

    out_depth = (ndcDepth * 0.5) + 0.5;
}
