#ifndef BSGFX_GLSL
#define BSGFX_GLSL

#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
#extension GL_EXT_shader_16bit_storage : require
#include "project/basilisk-gfx/bsgfx_contracts.h"

// - bindings -

// - functions -

vec4 bsgfx_process(vec4 vertex) {
    vertex.y = -vertex.y;
    vertex.z = (vertex.z + vertex.w) / 2.0;

    return vertex;
}

mat4x3 bsgfx_m4x3(float transform[12]) {
    return mat4x3(
        transform[0], transform[1], transform[2],
        transform[3], transform[4], transform[5],
        transform[6], transform[7], transform[8],
        transform[9], transform[10], transform[11]
    );
}


#endif