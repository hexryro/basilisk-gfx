#ifndef BSGFX_MESH_COLOR_GLSL
#define BSGFX_MESH_COLOR_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

struct bsgfx_PrefabColorInstance {
    bsgfx_InstanceHeader header;
    mat4 transform;
};

layout(set = BSGFX_SET_MESH_COLOR_INSTANCES, binding = BSGFX_BINDING_MESH_COLOR_INSTANCES) readonly buffer bsgfx_mesh_color_instance_uniform {
    mat4 bsgfx_mesh_color_instances[];
};

vec4 bsgfx_translateMeshColor(uint instance, vec3 pos) {
    return bsgfx_mesh_color_instances[instance] * vec4(pos, 1.0);
}

#endif