
 /**
  MIT License
  
  Copyright (c) 2026 switch360hardflip <switch360hardflip@gmail.com>
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */ 

 /**
  _bs_models.c
  */

#include <stdio.h>
#include <time.h>
#include <float.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <direct.h>

#include <basilisk-core.h>
#include <bs_internal.h>



  /*==============================================================================
   * GLTF Helpers 
   =============================================================================*/
 
static bs_mat4 _bs_gltfMat4(bs_Model* model, bs_Json* root, int accessor, int i) {
    int buffer_view_id = _bs_fetchJsonF(root, BS_JSON_NUMBER, "accessors[%d].bufferView", accessor).as_number;
    int offset = _bs_fetchJsonF(root, BS_JSON_NUMBER, "bufferViews[%d].byteOffset", buffer_view_id).as_number;

    bs_mat4 m;
    memcpy(m.a, model->gltf + offset + i * sizeof(bs_mat4), sizeof(bs_mat4));

    return m;
}

static int* _bs_gltfIntArray(bs_Model* model, bs_Json* root, int accessor, int* out_len, int num_components, bs_U32 size) {
    int buffer_view_id = _bs_fetchJsonF(root, BS_JSON_NUMBER, "accessors[%d].bufferView", accessor).as_number;
    bs_Json buffer_view = _bs_jsonRoot(root, _bs_fetchJsonF(root, BS_JSON_OBJECT, "bufferViews[%d]", buffer_view_id).as_object);

    *out_len   = _bs_fetchJson(&buffer_view, BS_JSON_NUMBER, BS_CONSTANT_STRING("byteLength")).as_number / size;
    int offset = _bs_fetchJson(&buffer_view, BS_JSON_NUMBER, BS_CONSTANT_STRING("byteOffset")).as_number;

    return (int*)(model->gltf + offset);
}

static float* _bs_gltfFloatArray(bs_Model* model, bs_Json* root, int accessor, int* out_len, int num_components) {
    int buffer_view_id = _bs_fetchJsonF(root, BS_JSON_NUMBER, "accessors[%d].bufferView", accessor).as_number;
    int count = _bs_fetchJsonF(root, BS_JSON_NUMBER, "accessors[%d].count", accessor).as_number;
    int offset = _bs_fetchJsonF(root, BS_JSON_NUMBER, "bufferViews[%d].byteOffset", buffer_view_id).as_number;

    *out_len = count * num_components;

    return (float*)(model->gltf + offset);
}


  /*==============================================================================
   * GLTF Meshes / Primitives
   =============================================================================*/

static void _bs_modelAttribData(bs_Json* root, bs_Primitive* primitive, int accessor, int num_components, int offset) {
    int num_floats = 0;
    float* a = _bs_gltfFloatArray(primitive->parent->model, root, accessor, &num_floats, num_components);

    for (int i = 0; i < num_floats / num_components; i++, offset += primitive->vertex_size) {
        for (int j = 0; j < num_components; j++)
            primitive->vertices[offset + j] = a[i * num_components + j];
    }
}

static void _bs_modelAttribDataI(
    bs_Json* root,
    bs_Primitive* primitive, 
    int accessor, 
    int num_components, 
    int offset, 
    unsigned int* out)
{
    int num_floats = 0;
    bs_U8* arr = (bs_U8*)_bs_gltfFloatArray(primitive->parent->model, root, accessor, &num_floats, num_components);

    for (int i = 0; i < num_floats / num_components; i++, offset += primitive->vertex_size) {
        for (int j = 0; j < num_components; j++)
            out[offset + j] = arr[i * num_components];
    }
}

static bs_Primitive* _bs_loadPrimitive(
    bs_Mesh* mesh, 
    bs_Primitive* primitive, 
    bs_Json* root,
    bs_Json* primitive_json)
{
    memset(primitive, 0, sizeof(bs_Primitive));

    bs_Json attributes       = _bs_jsonRoot(root, _bs_fetchJson(primitive_json, BS_JSON_OBJECT, BS_CONSTANT_STRING("attributes")).as_object);
    bs_JsonValue position    = _bs_fetchJson(&attributes, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("POSITION"));
    bs_JsonValue normal      = _bs_fetchJson(&attributes, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("NORMAL"));
    bs_JsonValue tex_coord   = _bs_fetchJson(&attributes, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("TEXCOORD_0"));
    bs_JsonValue joints      = _bs_fetchJson(&attributes, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("JOINTS_0"));
    bs_JsonValue weights     = _bs_fetchJson(&attributes, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("WEIGHTS_0"));

    primitive->aabb.max = (bs_vec3) { -FLT_MAX, -FLT_MAX, -FLT_MAX };
    primitive->aabb.min = (bs_vec3) { FLT_MAX, FLT_MAX, FLT_MAX };
    
    int num_floats = 0, vertex_size = 0;
    _bs_gltfIntArray(mesh->model, root, position.as_number, &num_floats, 1, sizeof(bs_U32));

    if (position.found)  vertex_size += 3;
    if (normal.found)    vertex_size = (primitive->normal_offset = vertex_size) + 3;
    if (tex_coord.found) vertex_size = (primitive->texture_offset = vertex_size) + 2;
    if (joints.found)    vertex_size = (primitive->bone_offset = vertex_size) + 4;
    if (weights.found)   vertex_size = (primitive->weight_offset = vertex_size) + 4;

    primitive->material_id = _bs_fetchJson(primitive_json, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("material")).as_number;
    primitive->parent = mesh;
    primitive->vertex_size = vertex_size;
    primitive->num_vertices = num_floats / 3;
    primitive->vertices = _bs_malloc(primitive->num_vertices * vertex_size * sizeof(float));

    if (position.found)  _bs_modelAttribData(root, primitive, position.as_number, 3, 0);
    if (normal.found)    _bs_modelAttribData(root, primitive, normal.as_number, 3, primitive->normal_offset);
    if (tex_coord.found) _bs_modelAttribData(root, primitive, tex_coord.as_number, 2, primitive->texture_offset);
    if (joints.found)    _bs_modelAttribDataI(root, primitive, joints.as_number, 4, primitive->bone_offset, primitive->vertices);
    if (weights.found)   _bs_modelAttribData(root, primitive, weights.as_number, 4, primitive->weight_offset);

   /**
    Read indices
    */
    int accessor = _bs_fetchJson(primitive_json, BS_JSON_NUMBER, BS_CONSTANT_STRING("indices")).as_number;

    bs_U16* arr = (bs_U16*)_bs_gltfFloatArray(mesh->model, root, accessor, &primitive->num_indices, 1);
    primitive->indices = _bs_calloc(primitive->num_indices, sizeof(int));
    for (int i = 0; i < primitive->num_indices; i++)
        primitive->indices[i] = arr[i];

    mesh->num_vertices += primitive->num_vertices;
    mesh->num_indices += primitive->num_indices;
    mesh->model->num_vertices += primitive->num_vertices;
    mesh->model->num_indices += primitive->num_indices;

    return primitive;
}

static void _bs_loadMeshes(bs_Model* model, bs_Json* root) {
    bs_JsonValue meshes = _bs_fetchJson(root, BS_JSON_ARRAY, BS_CONSTANT_STRING("meshes"));
    bs_JsonValue nodes = _bs_fetchJson(root, BS_JSON_ARRAY, BS_CONSTANT_STRING("nodes"));

    model->meshes_count = meshes.size;
    model->meshes = _bs_malloc(model->meshes_count * sizeof(bs_Mesh));

    for (int i = 0; i < nodes.size; i++) {
        bs_Json node = _bs_jsonRoot(root, nodes.as_array.as_objects[i]);

        bs_JsonValue mesh_id = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("mesh"));
        if (!mesh_id.found) 
            continue;

        int id = mesh_id.as_number;
        bs_Json mesh_json = _bs_jsonRoot(root, meshes.as_array.as_objects[id]);

        bs_JsonValue primitives = _bs_fetchJson(&mesh_json, BS_JSON_ARRAY, BS_CONSTANT_STRING("primitives"));
        bs_JsonValue translation = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("translation"));
        bs_JsonValue rotation = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("rotation"));
        bs_JsonValue scale = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("scale"));

        bool has_translation = translation.found && translation.type & BS_JSON_ARRAY && translation.type & BS_JSON_NUMBER && translation.size == 3;
        bool has_rotation = rotation.found && rotation.type & BS_JSON_ARRAY && rotation.type & BS_JSON_NUMBER && rotation.size == 4;
        bool has_scale = scale.found && scale.type & BS_JSON_ARRAY && scale.type & BS_JSON_NUMBER && scale.size == 3;

        bs_Mesh* mesh = model->meshes + id;
        *mesh = (bs_Mesh) {
            .model = model,
            .aabb.max = { -FLT_MAX, -FLT_MAX, -FLT_MAX },
            .aabb.min = { FLT_MAX, FLT_MAX, FLT_MAX },
            .name = strdup(_bs_fetchJson(&node, BS_JSON_STRING, BS_CONSTANT_STRING("name")).as_string),
            .primitives = _bs_malloc(primitives.size * sizeof(bs_Primitive)),
            .primitives_count = primitives.size,

            .position = has_translation 
                ? (bs_vec3) { translation.as_array.as_numbers[0], translation.as_array.as_numbers[1], translation.as_array.as_numbers[2] } 
                : (bs_vec3) { 0 },

            .rotation = has_rotation 
                ? (bs_vec4) { rotation.as_array.as_numbers[0], rotation.as_array.as_numbers[1], rotation.as_array.as_numbers[2], rotation.as_array.as_numbers[3] } 
                : BS_QUAT_IDENTITY,

            .scale = has_scale 
                ? (bs_vec3) { scale.as_array.as_numbers[0], scale.as_array.as_numbers[1], scale.as_array.as_numbers[2] } 
                : (bs_vec3) { 1.0, 1.0, 1.0 },
        };
        mesh->name_hash = _bs_stringHash(mesh->name);

        for (int j = 0; j < mesh->primitives_count; j++) {
            bs_Json primitive_json = _bs_jsonRoot(root, primitives.as_array.as_objects[j]);
            _bs_loadPrimitive(mesh, mesh->primitives + j, root, &primitive_json);
        }

        model->primitives_count += mesh->primitives_count;
    }
}


  /*==============================================================================
   * GLTF Animation
   =============================================================================*/

#define BS_SEARCH_CHANNEL(channel, animation_joint, time)                           \
    int closest = 0;                                                                \
    float smallest = FLT_MAX;                                                       \
    for (int i = 0; i < animation_joint->channel##_count; i++) {                    \
        if (animation_joint->channel[i].time < time) {                              \
            float diff = time - animation_joint->channel[i].time;                   \
            if (diff < smallest) {                                                  \
                smallest = diff;                                                    \
                closest = i;                                                        \
            }                                                                       \
        }                                                                           \
    }

BSAPI bs_vec4 _bs_interpolateRotation(bs_AnimationBone* animation_joint, float time) {
    if (!animation_joint->rotations) 
        return BS_QUAT_IDENTITY;

    BS_SEARCH_CHANNEL(rotations, animation_joint, time);
    return animation_joint->rotations[closest].value;
}

BSAPI bs_vec3 _bs_interpolateTranslation(bs_AnimationBone* animation_joint, float time) {
    if (!animation_joint->translations)
        return (bs_vec3) { 0 };

    BS_SEARCH_CHANNEL(translations, animation_joint, time);
    return animation_joint->translations[closest].value;
}

BSAPI bs_vec3 _bs_interpolateScale(bs_AnimationBone* animation_joint, float time) {
    if (!animation_joint->scalings) 
        return (bs_vec3) { 1.0, 1.0, 1.0 };

    BS_SEARCH_CHANNEL(scalings, animation_joint, time);
    return animation_joint->scalings[closest].value;
}

BSAPI bs_mat4 _bs_boneTransform(bs_Armature* armature, bs_Bone* joint) {
    return armature->bones[joint->id].matrix;
}

BSAPI bs_vec3 _bs_bonePosition(bs_Armature* armature, bs_Bone* joint) {
    bs_mat4 bone_transform = _bs_boneTransform(armature, joint);
    bs_vec4 result = { 0.0, 0.0, 0.0, 1.0 };

    bs_m4MulV4(&bone_transform, &result, &result);

    return result.xyz;
}

BSAPI bs_mat4* _bs_transformBone(bs_Armature* armature, bs_Bone* bone, const bs_mat4* transform) {
    bs_mat4 parent = (bone->parent_idx == -1) ? BS_MAT4_IDENTITY : armature->bones[bone->parent_idx].matrix;
    bs_mat4* destination = &armature->bones[bone->id].matrix;

    bs_m4Mul(&bone->local_matrix, transform, destination);
    bs_m4Mul(destination, &bone->bind_matrix_inverse, destination);
    bs_m4Mul(&parent, destination, destination);

    return destination;
}

BSAPI void _val_bs_blendPose(bs_Armature* armature, bs_Animation* animation_a, bs_Animation* animation_b, float factor, float time_a, float time_b) {
    BS_VALIDATE(!animation_b || animation_a->bones_count == animation_b->bones_count,,
        "Animation \"%s\" (%d bones) != \"%s\" (%d bones)",
        animation_a->name, animation_a->bones_count, 
        animation_b->name, animation_b->bones_count);

    _bs_blendPose(armature, animation_a, animation_b, factor, time_a, time_b);
}

BSAPI void _bs_blendPose(bs_Armature* armature, bs_Animation* animation_a, bs_Animation* animation_b, float factor, float time_a, float time_b) {
    if (animation_b) {
        for (int i = 0; i < armature->bones_count; i++) {
            bs_AnimationBone* a = animation_a->bones + i;
            bs_AnimationBone* b = animation_b->bones + i;

            bs_vec3 interpolated_translation_a = _bs_interpolateTranslation(a, time_a);
            bs_vec3 interpolated_translation_b = _bs_interpolateTranslation(b, time_b);

            bs_vec4 interpolated_rotation_a = _bs_interpolateRotation(a, time_a);
            bs_vec4 interpolated_rotation_b = _bs_interpolateRotation(b, time_b);

            bs_vec3 interpolated_scale_a = _bs_interpolateScale(a, time_a);
            bs_vec3 interpolated_scale_b = _bs_interpolateScale(b, time_b);

            bs_vec3 translation;
            bs_vec4 rotation;
            bs_vec3 scale;

            bs_v3Lerp(&interpolated_translation_a, &interpolated_translation_b, factor, &translation);
            bs_qSlerp(&interpolated_rotation_a, &interpolated_rotation_b, factor, &rotation);
            bs_v3Lerp(&interpolated_scale_a, &interpolated_scale_b, factor, &scale);

            bs_mat4 transform = BS_MAT4_IDENTITY;
            bs_m4Translate(&transform, &translation, &transform);
            bs_m4Rotate(&transform, &rotation, &transform);
            bs_m4Scale(&transform, &scale, &transform);

            _bs_transformBone(armature, &armature->bones[i].bone, &transform);
        }
    }
    else {
        for (int i = 0; i < armature->bones_count; i++) {
            bs_AnimationBone* a = animation_a->bones + i;

            bs_vec3 translation = _bs_interpolateTranslation(a, time_a);
            bs_vec4 rotation = _bs_interpolateRotation(a, time_a);
            bs_vec3 scale = _bs_interpolateScale(a, time_a);

            bs_mat4 transform = BS_MAT4_IDENTITY;
            bs_m4Translate(&transform, &translation, &transform);
            bs_m4Rotate(&transform, &rotation, &transform);
            bs_m4Scale(&transform, &scale, &transform);

            _bs_transformBone(armature, &armature->bones[i].bone, &transform);
        }
    }
}

static inline bs_vec3 _bs_worldSpaceJoint(bs_Armature* armature, int bone_id) {
    bs_mat4 bind_matrix;
    bs_m4Inverse(&armature->bones[bone_id].bone.bind_matrix_inverse, &bind_matrix);

    bs_mat4 mul;
    bs_m4Mul(&armature->bones[bone_id].matrix, &bind_matrix, &mul);

    bs_vec4 result = { 0.0, 0.0, 0.0, 1.0 };
    bs_m4MulV4(&mul, &result, &result);

    return result.xyz;
}

 /**
  pretty lazily implemented rn
  should test around with transforming the target instead of every joint
  */
BSAPI void _bs_fabrik(bs_Armature* armature, int end_effector_id, bs_vec3 target, int chain_length, float* chain) {
    bs_Bone* bone = &armature->bones[end_effector_id].bone;
    bs_vec3 current = target;

    int num = 0;
    int last_bone_id = 0;

    for (num = 0; bone && bone->parent_idx != -1 && (num < chain_length); num++) {
        bs_vec3 position = _bs_worldSpaceJoint(armature, bone->id);

        bs_vec3 direction;
        bs_v3Sub(&position, &current, &direction);
        bs_v3Normalize(&direction, &direction);

        armature->bones[num].ik_id = bone->id;
        armature->bones[num].ik_length = chain[num];
        armature->bones[num].ik_position = current;
        armature->bones[num].bone;

        bs_v3MulS(&direction, armature->bones[num].ik_length, &direction);
        bs_v3Add(&current, &direction, &current);

        last_bone_id = bone->id;
        bone = &armature->bones[bone->parent_idx].bone;
    }

    current = _bs_worldSpaceJoint(armature, last_bone_id);
    for (int i = num - 1; i >= 0; i--) {
        bs_vec3 direction;
        bs_v3Sub(&armature->bones[i].ik_position, &current, &direction);
        bs_v3Normalize(&direction, &direction);

        bs_vec3 up = BS_V3(0, 1, 0);
        bs_vec3 axis;
        bs_v3Cross(&up, &direction, &axis);

        float dot = bs_v3Dot(&up, &direction);
        float w = sqrt(bs_v3MagnitudeSqrd(&up) * bs_v3MagnitudeSqrd(&direction)) + dot;
        bs_vec4 rotation = { axis.x, axis.y, axis.z, w };
        bs_qNormalize(&rotation, &rotation);

        bs_mat4 transform = BS_MAT4_IDENTITY;
        bs_m4Translate(&transform, &current, &transform);
        bs_m4Rotate(&transform, &rotation, &transform);

        bs_m4Mul(&transform, &armature->bones[armature->bones[i].ik_id].bone.bind_matrix_inverse, &armature->bones[armature->bones[i].ik_id].matrix);

        bs_v3MulS(&direction, armature->bones[i].ik_length, &direction);

        bs_v3Add(&current, &direction, &current);
    }
}

BSAPI void _bs_bindPose(bs_Armature* armature) {
    for (int i = 0; i < armature->bones_count; i++)
        armature->bones[i].matrix = BS_MAT4_IDENTITY;
}

#define BS_CHANNEL_INCREMENT_BY (16)
#define BS_SET_CHANNEL(channel, p)                                                                              \
    if (bone->channel##_count >= bone->channel##_allocated) {                                                   \
        bone->channel##_allocated += BS_CHANNEL_INCREMENT_BY;                                                   \
        bone->channel = _bs_realloc(bone->channel, bone->channel##_allocated * sizeof(*bone->channel));          \
    }                                                                                                           \
    bone->channel[bone->channel##_count].value = p;                                                             \
    bone->channel[bone->channel##_count++].time = timestamp;

BSAPI void _bs_keyframePosition(bs_AnimationBone* bone, float timestamp, bs_vec3 translation) { 
    BS_SET_CHANNEL(translations, translation);
}

BSAPI void _bs_keyframeRotation(bs_AnimationBone* bone, float timestamp, bs_vec4 rotation) { 
    BS_SET_CHANNEL(rotations, rotation); 
}

BSAPI void _bs_keyframeScale(bs_AnimationBone* bone, float timestamp, bs_vec3 scale) { 
    BS_SET_CHANNEL(scalings, scale); 
}

static int _bs_queryAnimation(bs_Model* model, char* name) {
    bs_U64 hash = _bs_stringHash(name);

    for (int i = 0; i < model->animations_count; i++) {
        if (model->animation_hashes[i] == hash) {
            return i;
        }
    }

    return -1;
}

BSAPI bs_Result _bs_loadAnimation(bs_Model* model, const char* name, bs_Animation* out) {
    int animation_id = _bs_queryAnimation(model, name);
    if (animation_id == -1) {
        _bs_warnF("Failed to query animation \"%s\"", name);
        return BS_RESULT_FAILED_TO_QUERY;
    }

    bs_Json* root = &model->json;
    bs_JsonValue animation_object = _bs_fetchJsonF(root, BS_JSON_UNDEFINED, "animations[%d]", animation_id);
    bs_Json animation_root = _bs_jsonRoot(root, animation_object.as_object);

    bs_JsonArray samplers = _bs_fetchJson(&animation_root, BS_JSON_ARRAY, BS_CONSTANT_STRING("samplers")).as_array;
    bs_JsonValue channels_json = _bs_fetchJson(&animation_root, BS_JSON_ARRAY, BS_CONSTANT_STRING("channels"));

    bs_Animation animation = {
        .name = strdup(_bs_fetchJson(&animation_root, BS_JSON_STRING, BS_CONSTANT_STRING("name")).as_string),
        .bones_allocated = channels_json.size / 3,
    };

    if (channels_json.size > 0)
        animation.bones = _bs_calloc(animation.bones_allocated, sizeof(bs_AnimationBone));

    for (int i = 0, last_node = -1; i < channels_json.size; i++) {
        bs_Json channel_json = _bs_jsonRoot(root, channels_json.as_array.as_objects[i]);

        int sampler_id = _bs_fetchJson(&channel_json, BS_JSON_NUMBER, BS_CONSTANT_STRING("sampler")).as_number;
        bs_Json sampler = _bs_jsonRoot(root, samplers.as_objects[sampler_id]);
        int input = _bs_fetchJson(&sampler, BS_JSON_NUMBER, BS_CONSTANT_STRING("input")).as_number;
        int output = _bs_fetchJson(&sampler, BS_JSON_NUMBER, BS_CONSTANT_STRING("output")).as_number;
        char* path = _bs_fetchJson(&channel_json, BS_JSON_STRING, BS_CONSTANT_STRING("target.path")).as_string;
        int node = _bs_fetchJson(&channel_json, BS_JSON_NUMBER, BS_CONSTANT_STRING("target.node")).as_number;

        //char* name = __bs_fetchJsonF(root, BS_JSON_STRING, "nodes[%d].name", node).as_string;
        int num_inputs = 0, num_outputs = 0;
        float* inputs = _bs_gltfFloatArray(model, root, input, &num_inputs, 1);
        float* outputs = _bs_gltfFloatArray(model, root, output, &num_outputs, 1);
        assert(num_inputs == num_outputs);

        if (last_node != -1 && last_node != node)
            animation.bones_count++;
        last_node = node;
        assert(animation.bones_count < animation.bones_allocated);

        animation.frames_count = BS_MAX(animation.frames_count, num_inputs);
        for (int j = 0; j < num_inputs; j++)
            animation.length = BS_MAX(animation.length, inputs[j]);

        int path_len = strlen(path);
        if ((sizeof("translation") - 1) == path_len && strncmp(path, "translation", path_len) == 0) {
            for (int j = 0; j < num_inputs; j++)
                _bs_keyframePosition(animation.bones + animation.bones_count, inputs[j], ((bs_vec3*)outputs)[j]);
        }
        else if ((sizeof("rotation") - 1) == path_len && strncmp(path, "rotation", path_len) == 0) {
            for (int j = 0; j < num_inputs; j++)
                _bs_keyframeRotation(animation.bones + animation.bones_count, inputs[j], ((bs_vec4*)outputs)[j]);
        }
        else if ((sizeof("scale") - 1) == path_len && strncmp(path, "scale", path_len) == 0) {
            for (int j = 0; j < num_inputs; j++)
                _bs_keyframeScale(animation.bones + animation.bones_count, inputs[j], ((bs_vec3*)outputs)[j]);
        }
        else {
            // bet my life this wont ever happen
            _bs_warnF("Animation \"%s\" has an invalid path type \"%s\"", name, path);
            return BS_RESULT_CORRUPTED;
        }
    }

    assert(animation.frames_count > 0);

    *out = animation;
    return BS_RESULT_OK;
}



  /*==============================================================================
   * GLTF Armature
   =============================================================================*/

static inline void _bs_setParentIds(bs_Armature* armature, bs_JsonArray* joints, bs_JsonValue* children, int i) {
    for (int j = 0; j < children->size; j++) {
        for (int k = 0; k < armature->bones_count; k++) {
            if (joints->as_numbers[k] == children->as_array.as_numbers[j]) {
                armature->bones[k].bone.parent_idx = i;
                break;
            }
        }
        children->as_array.as_numbers[j] = i;
    }
}

static inline void _bs_setOppositeIds(bs_Armature* armature, bs_Bone* bone) {
    if (bone->name_length <= 2) return;
    if (bone->name[bone->name_length - 2] != '.') return;
    
    int opposite_id = -1;
    if (bone->name[bone->name_length - 1] == 'L') {
        bone->name[bone->name_length - 1] = 'R';
        opposite_id = _bs_queryBoneId(armature, bone->name);
        bone->name[bone->name_length - 1] = 'L';
    }
    else if (bone->name[bone->name_length - 1] == 'R') {
        bone->name[bone->name_length - 1] = 'L';
        opposite_id = _bs_queryBoneId(armature, bone->name);
        bone->name[bone->name_length - 1] = 'R';
    }

    if (opposite_id >= 0)
        bone->opposite_id = opposite_id;
}

static void _bs_loadArmature(bs_Model* model, bs_Armature* armature, bs_Json* root, bs_Json* skin_root) {
    int inverse_bind_matrices_accessor = _bs_fetchJson(skin_root, BS_JSON_NUMBER, BS_CONSTANT_STRING("inverseBindMatrices")).as_number;
    bs_JsonValue joints = _bs_fetchJson(skin_root, BS_JSON_ARRAY, BS_CONSTANT_STRING("joints"));

    *armature = (bs_Armature){
        .name = strdup(_bs_fetchJson(skin_root, BS_JSON_STRING, BS_CONSTANT_STRING("name")).as_string),
        .bones_count = joints.size,
        .bones_allocated = joints.size,
        .bones = _bs_calloc(joints.size, sizeof(*armature->bones)),
    };

    for (int j = 0; j < armature->bones_count; j++)
        armature->bones[j].bone.parent_idx = armature->bones[j].bone.opposite_id = -1;

    for (int j = 0; j < armature->bones_count; j++) {
        int node_id = joints.as_array.as_numbers[j];
        bs_Json node = _bs_jsonRoot(root, _bs_fetchJsonF(root, BS_JSON_OBJECT, "nodes[%d]", node_id).as_object);
        bs_JsonValue children = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("children"));

        _bs_setParentIds(armature, &joints.as_array, &children, j);

        double* translation = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("translation")).as_array.as_numbers;
        double* rotation = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("rotation")).as_array.as_numbers;
        double* scale = _bs_fetchJson(&node, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("scale")).as_array.as_numbers;

        bs_mat4 transform = BS_MAT4_IDENTITY;
        if (translation)
            bs_m4Translate(&transform, &(bs_vec3) { translation[0], translation[1], translation[2] }, &transform);
        if (rotation)
            bs_m4Translate(&transform, &(bs_vec4) { rotation[0], rotation[1], rotation[2], rotation[3] }, & transform);
        if (scale)
            bs_m4Translate(&transform, &(bs_vec3) { scale[0], scale[1], scale[2] }, & transform);
        bs_m4Inverse(&transform, &transform);

        bs_Bone* bone = &armature->bones[j].bone;

        bone->bind_matrix_inverse = _bs_gltfMat4(model, root, inverse_bind_matrices_accessor, j);

        bs_mat4 bind_matrix; 
        bs_m4Inverse(&bone->bind_matrix_inverse, &bind_matrix);

        bone->local_matrix;
        bs_m4Mul(&bind_matrix, &transform, &bone->local_matrix);

        char* name = _bs_fetchJson(&node, BS_JSON_STRING, BS_CONSTANT_STRING("name")).as_string;
        if (name) {
            bone->name_hash = _bs_stringHash(name);
            bone->name = strdup(name);
            bone->name_length = bone->name ? strlen(bone->name) : 0;
        }
        bone->id = j;
    }

    for (int j = 0; j < armature->bones_count; j++) {
        bs_Bone* bone = &armature->bones[j].bone;
        _bs_setOppositeIds(armature, bone);
    }
}

static void _bs_loadArmatures(bs_Model* model, bs_Json* root) {
    bs_JsonValue skins = _bs_fetchJson(root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("skins"));
    if (!skins.found || skins.size == 0)
        return;

    model->armatures_count = skins.size;
    if (model->armatures_count == 0)
        return;
    
    model->armatures = _bs_malloc(model->armatures_count * sizeof(bs_Armature));

    for (int i = 0; i < model->armatures_count; i++) {
        bs_Armature* armature = model->armatures + i;
        bs_Json armature_json = _bs_jsonRoot(root, skins.as_array.as_objects[i]);
        _bs_loadArmature(model, armature, root, &armature_json);
    }
}


  /*==============================================================================
   * GLTF Materials
   =============================================================================*/

static void _bs_loadMaterial(bs_Material* material, bs_Json* root) {
    material->name = strdup(_bs_fetchJson(root, BS_JSON_STRING, BS_CONSTANT_STRING("name")).as_string);

    bs_JsonValue base_color_factor = _bs_fetchJson(root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("pbrMetallicRoughness.baseColorFactor"));
    if (base_color_factor.found) {
        // asserts shouldnt ever fail
        assert(base_color_factor.size == 4);
        assert(base_color_factor.type & BS_JSON_NUMBER);

        material->color = (bs_RGBA) {
            base_color_factor.as_array.as_numbers[0] * 255,
            base_color_factor.as_array.as_numbers[1] * 255,
            base_color_factor.as_array.as_numbers[2] * 255,
            base_color_factor.as_array.as_numbers[3] * 255
        };
    }
}

static void _bs_loadMaterials(bs_Model* model, bs_Json* root) {
    bs_JsonValue materials = _bs_fetchJson(root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("materials"));
    if (!materials.found || materials.size == 0)
        return;

    model->materials_count = materials.size;
    model->materials = _bs_calloc(model->materials_count, sizeof(bs_Material));

    for (int i = 0; i < model->materials_count; i++) {
        bs_Json material_root = _bs_jsonRoot(root, materials.as_array.as_objects[i]);
        _bs_loadMaterial(model->materials + i, &material_root);
    }
}

  /*==============================================================================
   * GLTF Models
   =============================================================================*/

static inline bs_vec3 _bs_v3MinBound(bs_vec3 a, bs_vec3 b) { return BS_V3(BS_MIN(a.x, b.x), BS_MIN(a.y, b.y), BS_MIN(a.z, b.z)); }
static inline bs_vec3 _bs_v3MaxBound(bs_vec3 a, bs_vec3 b) { return BS_V3(BS_MAX(a.x, b.x), BS_MAX(a.y, b.y), BS_MAX(a.z, b.z)); }
static void _bs_calculateModelBounds(bs_Model* model) {
    if (model->aabb.min.x != FLT_MAX) return;

    for (int i = 0; i < model->meshes_count; i++) {
        bs_Mesh* mesh = model->meshes + i;

        for (int j = 0; j < mesh->primitives_count; j++) {
            bs_Primitive* prim = mesh->primitives + j;

            for (int k = 0; k < prim->num_vertices; k++) {
                bs_vec3 pos = *(bs_vec3*)(prim->vertices + k * prim->vertex_size);
                prim->aabb.min = _bs_v3MinBound(prim->aabb.min, pos);
                prim->aabb.max = _bs_v3MaxBound(prim->aabb.max, pos);
            }

            mesh->aabb.min = _bs_v3MinBound(mesh->aabb.min, prim->aabb.min);
            mesh->aabb.max = _bs_v3MaxBound(mesh->aabb.max, prim->aabb.max);
        }

        model->aabb.min = _bs_v3MinBound(model->aabb.min, mesh->aabb.min);
        model->aabb.max = _bs_v3MaxBound(model->aabb.max, mesh->aabb.max);
    }
}

BSAPI void _bs_destroyModel(bs_Model* model) {
    for (int i = 0; i < model->meshes_count; i++) {
        bs_Mesh* mesh = model->meshes + i;
        for (int j = 0; j < mesh->primitives_count; j++) {
            bs_Primitive* primitive = mesh->primitives + j;

            primitive->indices = _bs_free(primitive->indices);
            primitive->vertices = _bs_free(primitive->vertices);
        }

        mesh->name = _bs_free(mesh->name);
        mesh->primitives = _bs_free(mesh->primitives);
    }

    model->armatures = _bs_free(model->armatures);
    model->meshes = _bs_free(model->meshes);
}

BSAPI bs_Result _bs_model(int package_id, const char* name, bs_U32 flags, bs_Resource** out) {
    bs_Result result;

    bs_Resource* resource;
    result = _bs_loadResource(package_id, flags, &resource, name, strlen(name));
    if (result != BS_RESULT_OK)
        return result;

    struct {
        bs_U32 magic;
        bs_U32 version;
        bs_U32 length;
    }* header = resource->data->value;
    if (header->magic != 0x46546C67) {
        _bs_warnF("%s: Invalid magic for model \"%s\"", __func__, name);
        return BS_RESULT_CORRUPTED;
    }
    
    bs_Json json = { 0 };
    unsigned char* gltf = NULL;

    int offset = sizeof(*header);
    while (offset < header->length) {
        struct {
            bs_U32 length;
            bs_U32 type;
            char data[];
        }* chunk = resource->data->value + offset;

        if (chunk->type == 0x4E4F534A) { // json
            assert(json.doc == NULL);
            result = _bs_json(resource->data->value + offset + sizeof(*chunk), chunk->length, &json);
            if (result != BS_RESULT_OK) {
                _bs_destroyResource(resource);
                return result;
            }
        }
        else if (chunk->type == 0x004E4942) { // bin
            gltf = resource->data->value + offset + sizeof(*chunk);
        }
        else {
            _bs_warnF("%s: Unknown chunk type 0x%08X", __func__, chunk->type);
            return BS_RESULT_CORRUPTED;
        }

        offset += chunk->length + sizeof(*chunk);
    }

    if (!json.doc) {
        _bs_warnF("%s: missing JSON chunk", __func__);
        return BS_RESULT_GENERAL_ERROR;
    }
    
    bs_Model model = {
        .aabb.max = { -FLT_MAX, -FLT_MAX, -FLT_MAX },
        .aabb.min = { FLT_MAX, FLT_MAX, FLT_MAX },
        .json = json,
        .flags = BS_MODEL_JUST_CREATED,
        .gltf = gltf,
    };

    _bs_loadMeshes(&model, &json);
    _bs_loadArmatures(&model, &json);
    _bs_loadMaterials(&model, &json);

    _bs_calculateModelBounds(&model);
   // if (!(flags & BS_QUERY_MODEL_KEEP_JSON))
   //     _bs_destroyJson(&json);

    resource->model = _bs_malloc(sizeof(bs_Model)); // todo dont do this
    memcpy(resource->model, &model, sizeof(bs_Model));

    *out = resource;

    return BS_RESULT_OK;
}


 /*==============================================================================
  * Armature
   =============================================================================*/

/*
bs_Object _bs_armature(int id, bs_ArmatureFlags flags) {
    if (!id) 
        _bs_throwBasilisk(BSXI_INTERNAL | BSX_NOT_IMPLEMENTED);
    if (_bs_shouldLoadId(id)) {
        bs_Object existing = _bs_fetchNull(id);
        if (existing.armature && !(flags & BS_ARMATURE_FORCE_DESTROY))
            return existing;
    } else return (bs_Object) { 0 };

    bs_Object object = BS_ENSURE(id, ((bs_Armature) {
        .name = "armature",
    }), 0, 0);

    return object;
}
*/

BSAPI int _bs_bone(bs_Armature* armature, bs_mat4 local_transform, int parent_id, const char* name) {
    bs_mat4 bind_matrix = BS_MAT4_IDENTITY;

    if (armature->bones_count >= armature->bones_allocated) {
        const int increment_by = 16;
        armature->bones_allocated += increment_by;
        armature->bones = _bs_realloc(armature->bones, armature->bones_allocated * sizeof(*armature->bones));
    }

    armature->bones[armature->bones_count].ik_id = 0;
    armature->bones[armature->bones_count].ik_position = BS_V3(0.0, 0.0, 0.0);
    armature->bones[armature->bones_count].bone = (bs_Bone) {
        .bind_matrix_inverse = bind_matrix,
        .id = armature->bones_count,
        .name = name,
        .parent_idx = parent_id,
    };

    bs_m4Mul(&bind_matrix, &local_transform, &armature->bones[armature->bones_count].bone.local_matrix);

    _bs_transformBone(armature, &armature->bones[armature->bones_count].bone, &BS_MAT4_IDENTITY);

    return armature->bones_count++;
}

BSAPI void _bs_destroyAnimation(bs_Animation* animation) {
    animation->bones_count = 0;
    animation->bones = NULL;
    _bs_free(animation->bones);
}

/*
bs_Object _bs_animation(bs_Armature* armature, int id, const char* name, bs_AnimationFlags flags) {
    if (!id) 
        _bs_throwBasilisk(BSXI_INTERNAL | BSX_NOT_IMPLEMENTED);
    if (!armature) 
        _bs_throwBasilisk(BSXI_INTERNAL | BSX_INVALID_PARAM);

    if (_bs_shouldLoadId(id)) {
        bs_Object existing = _bs_fetchNull(id);

        if (existing.animation) {
            if (flags & BS_ANIMATION_FORCE_DESTROY)
                _bs_destroyAnimation(existing.animation);
            else return existing;
        }

    } else return (bs_Object) { 0 };

    bs_Object object = BS_ENSURE(id, ((bs_Animation) {
        .name = name,
        .bones = _bs_calloc(armature->bones_count, sizeof(bs_AnimationBone)),
        .bones_count = armature->bones_count,
    }), 0, 0);

    return object;
}
*/

 /*==============================================================================
  * Queries
  =============================================================================*/

BSAPI bs_Mesh* _bs_queryMeshHash(bs_Model* model, bs_U64 hash) {
    for (int i = 0; i < model->meshes_count; i++) {
        bs_Mesh* mesh = model->meshes + i;
        if (mesh->name_hash == hash)
            return mesh;
    }

    return NULL;
}

BSAPI bs_Mesh* _bs_queryMesh(bs_Model* model, const char* name) {
    return _bs_queryMeshHash(model, _bs_stringHash(name));
}

/*
bs_Object _bs_queryArmature(bs_Model* model, int id, const char* name, bs_ArmatureFlags flags) {
    if (!id) 
        _bs_throwBasilisk(BSXI_INTERNAL | BSX_NOT_IMPLEMENTED);
    if (_bs_shouldLoadId(id)) {
    }
    else return (bs_Object) { 0 };

    for(int i = 0; i < model->armatures_count; i++) {
        bs_Armature* armature = model->armatures + i;
        if (strcmp(name, armature->name) == 0) {
            armature->head.id = id;

            bs_Object object = {
                .type = BS_ARMATURE,
                .armature = armature,
            };

            _bs_map(id, &object);
            return object;
        }
    }
    
    _bs_throwBasiliskF(BSXI_INTERNAL | BSX_FAILED_TO_QUERY, "Armature \"%s\"", name);
    return (bs_Object) { 0 };
}
*/

BSAPI bs_Armature* _bs_queryArmature(bs_Model* model, const char* name) {
    for (int i = 0; i < model->armatures_count; i++) {
        if (strcmp(name, model->armatures[i].name) == 0)
            return model->armatures + i;
    }

    return NULL;
}

BSAPI int _bs_queryBoneId(bs_Armature* armature, const char* name) {
    bs_U64 name_hash = _bs_stringHash(name);
    for (int i = 0; i < armature->bones_count; i++) {
        if (armature->bones[i].bone.name_hash == name_hash)
            return i;
    }

    return -1;
}

BSAPI bs_Bone* _bs_queryBone(bs_Armature* armature, const char* name) {
    int id = _bs_queryBoneId(armature, name);
    return id == -1 ? NULL : &armature->bones[id].bone;
}

BSAPI bs_Material* _bs_queryMaterial(bs_Model* model, const char* name) {
    for (int i = 0; i < model->materials_count; i++) {
        if (strcmp(name, model->materials[i].name) == 0)
            return model->materials + i;
    }

    return NULL;
}
