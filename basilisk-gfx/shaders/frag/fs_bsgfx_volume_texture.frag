#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#define BSGFX_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(push_constant) uniform constants {
    mat4 camera;
    vec4 color;
    vec3 light_direction;
    int first_triangle;
    vec2 uv_offset;
    vec2 uv_coords;
    uint write_flags;
    int reserved;
} pushConst;

layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_INDEX, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_INPUT) uniform usubpassInput in_attachment_index;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_FLAGS, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_FLAGS_INPUT) uniform usubpassInput in_attachment_flags;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_NORMAL, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_NORMAL_INPUT) uniform subpassInput in_attachment_normal;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_POSITION, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_POSITION_INPUT) uniform subpassInput in_attachment_position;
layout (input_attachment_index = BSGFX_LO_SUBPASS_0_IN_COLOR, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_COLOR_INPUT) uniform subpassInput in_attachment_color;
layout(set = BSGFX_SET_IMAGE_ATLAS_ANY, binding = BSGFX_BINDING_IMAGE_ATLAS_ANY) uniform sampler2D atlas_texture;

layout(std430, set = BSGFX_SET_VOLUME_OUT_VERTICES, binding = BSGFX_BINDING_VOLUME_OUT_VERTICES) buffer bsgfx_volume_out_vertex_buffer {
    float bsgfx_volume_out_vertices[];
};

bool rayVsTriangle(
    vec3 rayOrigin,
    vec3 rayDir,
    vec3 v0,
    vec3 v1,
    vec3 v2,
    out float t,
    out vec3 bary
) {
    const float EPSILON = 1e-6;

    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;

    vec3 pvec = cross(rayDir, edge2);
    float det = dot(edge1, pvec);

    // If the determinant is near zero, the ray lies in the plane of the triangle
    if (abs(det) < EPSILON)
        return false;

    float invDet = 1.0 / det;

    vec3 tvec = rayOrigin - v0;
    float u = dot(tvec, pvec) * invDet;
    if (u < 0.0 || u > 1.0)
        return false;

    vec3 qvec = cross(tvec, edge1);
    float v = dot(rayDir, qvec) * invDet;
    if (v < 0.0 || u + v > 1.0)
        return false;

    t = dot(edge2, qvec) * invDet;
    if (t < 0.0)
        return false;

    bary = vec3(1.0 - u - v, u, v);
    return true;
}

float bsgfx_luminance(vec3 rgb) {
    const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    return dot(rgb, W);
}

void main() {
    uint index = subpassLoad(in_attachment_index).r;
    uint flags = subpassLoad(in_attachment_flags).r;

    if ((flags & BSGFX_ID_IN_SHADOW) != 0) {
      //  discard;
    }

    if ((flags & BSGFX_ID_IN_SHADOW) != 0) {
    if ((flags & BSGFX_ID_IN_SHADOW_TEXTURED) == 0) {

    }
    discard;
    }

    out_index = index;
    out_flags = flags | pushConst.write_flags;

    out_position = vec4(in_world_position, index);

    out_color = vec4(1.0, 0.0, 0.0, 1.0);

    int volume_size = 3 * 8;
    int first_triangle = pushConst.first_triangle;
    int vertex_size = 6;

    vec3 position = subpassLoad(in_attachment_position).rgb;
    
    vec3 v0 = vec3(
        bsgfx_volume_out_vertices[(first_triangle + 0) * vertex_size + 0],
        bsgfx_volume_out_vertices[(first_triangle + 0) * vertex_size + 1],
        bsgfx_volume_out_vertices[(first_triangle + 0) * vertex_size + 2]);
    vec2 uv0 = vec2(
        bsgfx_volume_out_vertices[(first_triangle + 0) * vertex_size + 3],
        bsgfx_volume_out_vertices[(first_triangle + 0) * vertex_size + 4]);

    vec3 v1 = vec3(
        bsgfx_volume_out_vertices[(first_triangle + 1) * vertex_size + 0],
        bsgfx_volume_out_vertices[(first_triangle + 1) * vertex_size + 1],
        bsgfx_volume_out_vertices[(first_triangle + 1) * vertex_size + 2]);
    vec2 uv1 = vec2(
        bsgfx_volume_out_vertices[(first_triangle + 1) * vertex_size + 3],
        bsgfx_volume_out_vertices[(first_triangle + 1) * vertex_size + 4]);

    vec3 v2 = vec3(
        bsgfx_volume_out_vertices[(first_triangle + 2) * vertex_size + 0],
        bsgfx_volume_out_vertices[(first_triangle + 2) * vertex_size + 1],
        bsgfx_volume_out_vertices[(first_triangle + 2) * vertex_size + 2]);
    vec2 uv2 = vec2(
        bsgfx_volume_out_vertices[(first_triangle + 2) * vertex_size + 3],
        bsgfx_volume_out_vertices[(first_triangle + 2) * vertex_size + 4]);

    float t = 0.0;
    vec3 bary = vec3(0.0);
    if (rayVsTriangle(position, pushConst.light_direction, v0, v1, v2, t, bary)) {
        out_color = vec4(0.5, 1.0, 1.0, 1.0);
        out_color = vec4(bary, 1.0);

        vec2 uv = 
            bary.x * uv0 +
            bary.y * uv1 +
            bary.z * uv2;

        out_color = vec4(uv.x, uv.y, 0.0, 1.0);
        uv = uv * pushConst.uv_coords + pushConst.uv_offset;
       
        out_color = texture(atlas_texture, vec2(uv.x, 1.0 - uv.y));
        if (out_color.a == 0.0) {
            discard;
        } else if (out_color.a < 1.0) {
            float l = bsgfx_luminance(out_color.rgb);
       // out_color.rgb = mix( vec3(l), subpassLoad(in_attachment_color).rgb * 0.65, 1.0 - out_color.a);


          /// out_color.rgb = vec3(l);
           out_color.rgb = subpassLoad(in_attachment_color).rgb * 2.0 * l;
        } else {
            float l = bsgfx_luminance(out_color.rgb);
           out_color.rgb = subpassLoad(in_attachment_color).rgb * 2.0 * l;
           out_color.rgb = subpassLoad(in_attachment_color).rgb * 0.65;
        }
    out_color.a = 1.0;
    } else {
        out_color = vec4(1.0, 0.0, 0.0, 1.0);
    }
     //   out_color.xyz = (pushConst.camera * vec4(vec3(position), 1.0)).xyz;

    if (in_instance == 96) {
  //     out_color = vec4(0.0, 1.0, 1.0, 1.0);
        
    } 
}
