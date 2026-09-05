#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"
#define BSGFX_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;
layout(location = 9) in vec2 in_texture_unprocessed;

layout(set = BSGFX_SET_IMAGE_ATLAS_ANY, binding = BSGFX_BINDING_IMAGE_ATLAS_ANY) uniform sampler2D atlas_texture;
//layout (input_attachment_index = 0, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_INPUT) uniform usubpassInput in_attachment_index;
//layout (input_attachment_index = 0, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_COLOR_INPUT) uniform subpassInput in_attachment_color;

layout(push_constant) uniform constants {
	mat4 camera;
    float elapsed;
    float padding;
    vec2 resolution;
} pushConst;

void main() {
    out_color = vec4(in_normal, 1.0);
    out_normal.xyz = in_normal;
    out_normal.a = 0.0;
    out_position = vec4(in_world_position, 1.0);
   // out_color = texture(atlas_texture, vec2(in_texture.x, 1.0 - in_texture.y)) * in_color;
    out_normal.xyz = in_normal;

    float y = in_texture_unprocessed.y;
    float t = abs(y - 0.5) * 2.0;

    float mid = 0.65;

    float gradient = mix(mid, 1.0, pow(t, 1.5));

    int material0_id = bsgfx_quad_instances[in_instance].header.id;
    uint material1_id = bsgfx_quad_instances[in_instance].header.material;

    bsgfx_MaterialContract material0 = bsgfx_material(material0_id);
    bsgfx_MaterialContract material1 = bsgfx_material(material1_id);

    out_color = mix(material0.color, material1.color, 1.0 - gradient);
}
