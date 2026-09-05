#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"

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
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(set = BSGFX_SET_64, binding = BSGFX_BINDING_64) uniform sampler2DArray images_64;
layout(set = BSGFX_SET_256, binding = BSGFX_BINDING_256) uniform sampler2DArray images_256;
layout(set = BSGFX_SET_512, binding = BSGFX_BINDING_512) uniform sampler2DArray images_512;
layout(set = BSGFX_SET_IMAGE_ATLAS_ANY, binding = BSGFX_BINDING_IMAGE_ATLAS_ANY) uniform sampler2D atlas_texture;
layout(set = BSAPP_SET_MATERIAL_TEXTURES, binding = BSAPP_BINDING_MATERIAL_TEXTURES) uniform sampler2DArray images[BSGFX_MATERIAL_TEXTURE_COUNT];

layout(push_constant) uniform constants {
    mat4 camera;
    vec4 uv;
    vec4 sun_direction;
} pushConst;

vec3 apply_lighting(vec3 base_color, vec3 normal) {
    vec3 light_dir = -pushConst.sun_direction.xyz;
    vec3 light_color = vec3(1.0, 1.0, 1.0);
    float ambient_strength = 0.2;

    vec3 norm = normalize(normal);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;
    vec3 ambient = ambient_strength * light_color;
    vec3 lighting = ambient + diffuse;

    return base_color * lighting;
}

void main() {
    bsgfx_MaterialContract m = bsgfx_material(in_material);

    out_normal.xyz = in_normal;
    out_normal.a = 1.0;
    out_position = vec4(in_world_position, 1.0);

    vec4 sampled = texture(images[m.image_binding], vec3(in_texture.xy, m.image));
    vec3 base_color = sampled.rgb * m.color.rgb;

    vec3 lit_color = apply_lighting(base_color, in_normal);

    out_color = vec4(lit_color, sampled.a * m.color.a);
    out_color = vec4(1.0, 0.0, 0.0, 1.0);

    out_index = in_instance;
    out_flags = in_flags;

    vec3 adjusted = in_position / 2.0 + 0.5;
    adjusted.x = pow(adjusted.x, 1.0);
    adjusted.y = pow(adjusted.y, 1.0);
    adjusted.z = pow(adjusted.z, 1.0);

    out_local_position = vec4(adjusted, 1.0);
}