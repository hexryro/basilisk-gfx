#ifndef BSGFX_QUAD_GLSL
#define BSGFX_QUAD_GLSL

#ifdef BSGFX_QUAD_INSTANCES

#define QUAD_INSTANCES_SET          BSGFX_SET_QUAD_INSTANCES
#define QUAD_INSTANCES_BINDING      BSGFX_BINDING_QUAD_INSTANCES
#define QUAD_INSTANCES_COUNT        BSGFX_QUAD_INSTANCE_COUNT

#elif defined BSMOD_TRACKER_QUAD_INSTANCES

#define QUAD_INSTANCES_SET          BSMOD_SET_TRACKER_QUAD_INSTANCES
#define QUAD_INSTANCES_BINDING      BSMOD_BINDING_TRACKER_QUAD_INSTANCES
#define QUAD_INSTANCES_COUNT        BSMOD_TRACKER_QUAD_INSTANCE_COUNT

#endif

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

struct bsgfx_QuadInstance {
    bsgfx_InstanceHeader header;
    float transform[12];
    vec2 coords;
    vec2 offset;
};

layout(set = QUAD_INSTANCES_SET, binding = QUAD_INSTANCES_BINDING) readonly buffer bsgfx_quad_instance_buffer {
    bsgfx_QuadInstance bsgfx_quad_instances[QUAD_INSTANCES_COUNT];
};

vec2 bsgfx_quadSize(uint instance) {
    return vec2(
        bsgfx_quad_instances[instance].transform[0],
        bsgfx_quad_instances[instance].transform[4]
    );
}

vec3 bsgfx_quadPosition(uint instance) {
    return vec3(
        bsgfx_quad_instances[instance].transform[9], 
        bsgfx_quad_instances[instance].transform[10], 
        bsgfx_quad_instances[instance].transform[11]
    );
}

vec3 bsgfx_quadVertex(uint instance, vec3 bs_position) {
    mat4x3 m = mat4x3(
        bsgfx_quad_instances[instance].transform[0], bsgfx_quad_instances[instance].transform[1], bsgfx_quad_instances[instance].transform[2],
        bsgfx_quad_instances[instance].transform[3], bsgfx_quad_instances[instance].transform[4], bsgfx_quad_instances[instance].transform[5],
        bsgfx_quad_instances[instance].transform[6], bsgfx_quad_instances[instance].transform[7], bsgfx_quad_instances[instance].transform[8],
        bsgfx_quad_instances[instance].transform[9], bsgfx_quad_instances[instance].transform[10], bsgfx_quad_instances[instance].transform[11]
    );

    return m * vec4(bs_position, 1.0);
}

vec4 bsgfx_roundedQuadRadii(uint instance) {
    return vec4(
        bsgfx_quad_instances[instance].transform[1], 
        bsgfx_quad_instances[instance].transform[2],
        bsgfx_quad_instances[instance].transform[3],
        bsgfx_quad_instances[instance].transform[6]
    );
}

vec3 bsgfx_roundedQuadPosition(uint instance, vec3 bs_position) {
// bsgfx_quad_instances[instance].transform[7]
// bsgfx_quad_instances[instance].transform[5]
    mat4x3 m = mat4x3(
        bsgfx_quad_instances[instance].transform[0], 0.0                                         , 0.0,
        0.0                                        , bsgfx_quad_instances[instance].transform[4] , 0.0,
        0.0                                        , 0.0                                         , bsgfx_quad_instances[instance].transform[8],
        bsgfx_quad_instances[instance].transform[9], bsgfx_quad_instances[instance].transform[10], bsgfx_quad_instances[instance].transform[11]
    );

    return m * vec4(bs_position, 1.0);
}

vec2 bsgfx_quadTextureCoordinates(uint instance, vec2 bs_texture) {
    return bs_texture * bsgfx_quad_instances[instance].coords + bsgfx_quad_instances[instance].offset;
}
#endif