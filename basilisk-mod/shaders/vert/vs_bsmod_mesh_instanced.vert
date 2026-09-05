#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

struct bsgfx_PrefabInstance {
    bsgfx_InstanceHeader header;
    mat4 transform;
};

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
	float camera_matrix[12];
	float model_matrix[12];
    vec4 color;
    int material_texture_size;
    int material_texture_id;
} pushConst;

void main() {
    mat4 camera_matrix = mat4(bsgfx_m4x3(pushConst.camera_matrix));
    mat4 model_matrix = mat4(bsgfx_m4x3(pushConst.model_matrix));

    mat3 normal_matrix = transpose(inverse(mat3(model_matrix)));

    out_normal = normalize(normal_matrix * bs_Normal);
    out_texture = vec3(bs_Texture, 0.0);
    out_world_position = (model_matrix * vec4(bs_Position, 1.0)).xyz;

    gl_Position = bsgfx_process(camera_matrix * vec4(out_world_position, 1.0));
}
