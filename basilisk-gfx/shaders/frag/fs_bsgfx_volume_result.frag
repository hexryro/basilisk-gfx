#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in float in_volume_id;

void main() {
    out_color = vec4(vec3(in_volume_id), 1.0);
    if (uint(in_volume_id) == 96)
        out_color = vec4(1.0, 0.0, 1.0, 1.0);

        
    out_index = 0;
    out_flags = uint(in_volume_id);
}
