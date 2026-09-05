#ifndef BSGFX_QUAD_GLSL
#define BSGFX_QUAD_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

struct bsgfx_QuadInstance {
    bsgfx_InstanceHeader header;
    vec4 position;
    vec2 coords;
    vec2 offset;
    vec4 test;
    vec2 dimensions;
    uint flags;
    int reserved;
};

layout(set = BSGFX_SET_QUAD_LEGACY_INSTANCES, binding = BSGFX_BINDING_QUAD_LEGACY_INSTANCES) readonly buffer bsgfx_quad_instance_buffer {
    bsgfx_QuadInstance bsgfx_quad_instances[BSGFX_QUAD_INSTANCE_COUNT];
};

vec3 bsgfx_quadPosition(uint instance, vec3 bs_position) {
    vec3 position = bsgfx_quad_instances[instance].position.xyz;
    position += bs_position * vec3(bsgfx_quad_instances[instance].dimensions.xy, 1.0);
    return position;
}

vec4 bsgfx_quadColor(uint instance) {
    return bsgfx_quad_instances[instance].color;
}

vec2 bsgfx_quadTextureCoordinates(uint instance, vec2 bs_texture) {
    return bs_texture * bsgfx_quad_instances[instance].coords + bsgfx_quad_instances[instance].offset;
}
#endif