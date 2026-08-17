#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_instance.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_bone.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"
#define BSGFX_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;
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

layout(set = BSGFX_SET_34_24, binding = BSGFX_BINDING_34_24) uniform sampler2DArray samp;
layout (input_attachment_index = 0, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_INPUT) uniform usubpassInput in_attachment_index;

layout(push_constant) uniform constants {
	mat4 camera;
} pushConst;

void main() {
    if (in_position.z >= 0) {
        if (out_color.a == 0.0)
            discard;
    }

    out_color = texture(samp, vec3(in_texture.x, 1.0 - in_texture.y, in_texture.z));
    out_normal = vec4(in_normal, 1.0);
    out_position = vec4(in_world_position, 1.0);

    out_index = in_instance;
    out_flags = BSGFX_ID_IS_PRIMITIVE;
}
