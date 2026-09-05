#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 3) in vec3 in_world_position;

layout(push_constant) uniform constants {
    vec4 color;
} pushConst;

layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_INDEX, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_INPUT) uniform usubpassInput in_attachment_index;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_FLAGS, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_FLAGS_INPUT) uniform usubpassInput in_attachment_flags;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_NORMAL, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_NORMAL_INPUT) uniform subpassInput in_attachment_normal;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_POSITION, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_POSITION_INPUT) uniform subpassInput in_attachment_position;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_COLOR, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_COLOR_INPUT) uniform subpassInput in_attachment_color;

void main() {
    uint index = subpassLoad(in_attachment_index).r;
    uint flags = subpassLoad(in_attachment_flags).r;

    out_position = vec4(in_world_position, index);
    out_color = pushConst.color;
    out_color.rgb = subpassLoad(in_attachment_color).rgb * 0.6;
    out_color.a = 1.0;

    out_index = index;
    out_flags = flags | BSGFX_ID_IN_SHADOW;
}
