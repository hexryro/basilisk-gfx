#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
//#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;
#ifdef _DEBUG
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION_LOCAL) out vec4 out_local_position;
#endif

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(set = BSAPP_SET_MATERIAL_TEXTURES, binding = BSAPP_BINDING_MATERIAL_TEXTURES) uniform sampler2DArray images[BSGFX_MATERIAL_TEXTURE_COUNT];

layout(push_constant) uniform constants {
	float camera_matrix[12];
	float model_matrix[12];
    vec4 color;
    int material_texture_size;
    int material_texture_id;
} pushConst;

void main() {
    vec4 sampled = texture(images[pushConst.material_texture_size], vec3(in_texture.xy, pushConst.material_texture_id));

    vec3 sun_direction = normalize(vec3(-0.5, -1.0, -0.3));
    vec3 N = normalize(in_normal);

    vec3 L = normalize(-sun_direction);

    float ambient = 0.2;
    float diffuse = max(dot(N, L), 0.0);

    vec3 base_color = sampled.xyz * pushConst.color.xyz;
    vec3 lit_color = base_color * (ambient + diffuse);

    out_color = vec4(lit_color, in_color.a);

    out_normal.xyz = N;
    out_normal.a = 1.0;

    out_position = vec4(in_world_position, 1.0);

    out_index = in_instance;
    out_flags = 0;

#ifdef _DEBUG
    out_local_position = vec4(in_position, 1.0);
#endif
}