#ifndef BSGFX_LINE_GLSL
#define BSGFX_LINE_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

struct bsgfx_LineInstance {
    bsgfx_InstanceHeader header;
    vec4 coords[2];
    vec4 color;
    vec4 a;
};

layout(set = BSGFX_SET_LINE_INSTANCES, binding = BSGFX_BINDING_LINE_INSTANCES) readonly buffer bsgfx_line_instance_uniform {
    bsgfx_LineInstance bsgfx_line_instances[];
};

vec4 bsgfx_translateLine(uint instance, int vertex_id) {
    return vec4(bsgfx_line_instances[instance].coords[vertex_id].xyz, 1.0);
}

#endif