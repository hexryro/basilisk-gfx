#ifndef BSGFX_BONE_GLSL
#define BSGFX_BONE_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

// - bindings -

layout(set = BSGFX_SET_JOINTS, binding = BSGFX_BINDING_JOINTS) readonly uniform bsgfx_joint_uniform {
    mat4 bsgfx_joints[1024]; // TODO storage buffer
};

struct bsgfx_BoneInstance {
    bsgfx_InstanceHeader header;
    mat4 transform;
};

layout(set = BSGFX_SET_BONE_INSTANCES, binding = BSGFX_BINDING_BONE_INSTANCES) readonly buffer bsgfx_bone_instance_uniform {
    bsgfx_BoneInstance bsgfx_bone_instances[];
};

// - functions -

// todo these should probably be ifndef debug somehow
// checks should be on cpu and hope for the best in prod
float bsgfx_v4Max(ivec4 v) {
  return max(max(max(v.x, v.y), v.z), v.w);
}

float bsgfx_v4Min(ivec4 v) {
  return min(min(min(v.x, v.y), v.z), v.w);
}

vec4 bsgfx_animatev4(uint bone_index, vec3 pos, ivec4 bid, vec4 wei) {
    uint start_joint = bsgfx_extractBoneOffset(bone_index);
    uint count = bsgfx_extractBoneCount(bone_index);

    if ((start_joint + bsgfx_v4Max(bid)) >= 1024)
        return vec4(0.0);

    if ((start_joint + bsgfx_v4Min(bid)) < 0)
        return vec4(0.0);

	return vec4(
        bsgfx_joints[start_joint + bid[0]] * vec4(pos, 1.0) * wei[0] +
        bsgfx_joints[start_joint + bid[1]] * vec4(pos, 1.0) * wei[1] +
        bsgfx_joints[start_joint + bid[2]] * vec4(pos, 1.0) * wei[2] +
        bsgfx_joints[start_joint + bid[3]] * vec4(pos, 1.0) * wei[3]
    );
}

vec3 bsgfx_animate(int instance, vec3 pos, ivec4 bid, vec4 wei) {
    return (bsgfx_bone_instances[instance].transform * vec4(bsgfx_animatev4(bsgfx_bone_instances[instance].header.bone_index, pos, bid, wei).xyz, 1.0)).xyz;
}

#endif