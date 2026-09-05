#ifndef BSGFX_MESH_GLSL
#define BSGFX_MESH_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

struct bsgfx_PrefabInstance {
    bsgfx_InstanceHeader header;
    mat4 transform;
};

layout(set = BSGFX_SET_MESH_INSTANCES, binding = BSGFX_BINDING_MESH_INSTANCES) readonly buffer bsgfx_mesh_instance_uniform {
    bsgfx_PrefabInstance bsgfx_mesh_instances[];
};

layout(set = BSGFX_SET_MESH_STATIC_INSTANCES, binding = BSGFX_BINDING_MESH_STATIC_INSTANCES) readonly buffer bsgfx_static_mesh_instance_uniform {
    bsgfx_PrefabInstance bsgfx_static_mesh_instances[];
};

vec4 bsgfx_translateMesh(uint instance, vec3 pos) {
    mat4 m = bsgfx_mesh_instances[instance].transform;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1;

    return m * vec4(pos, 1.0);
}

vec4 bsgfx_translateStaticMesh(uint instance, vec3 pos) {
    mat4 m = bsgfx_static_mesh_instances[instance].transform;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 1;

    return m * vec4(pos, 1.0);
}

#endif