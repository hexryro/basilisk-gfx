#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = BSGFX_HI_SUBPASS_0_OUT_COLOR) out vec4 out_color;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_1_COLOR_ATTACHMENT) uniform sampler2D attachment_color;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_NORMAL_ATTACHMENT) uniform sampler2D attachment_normal;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_ATTACHMENT) uniform usampler2D attachment_index;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_DEPTH_ATTACHMENT) uniform sampler2D attachment_depth;
layout(binding = BSGFX_BINDING_RAY_TRACE_OUTPUT, set = BSGFX_SET_RAY_TRACE_OUTPUT, rgba32f) uniform image2D ray_trace_output;

layout(push_constant) uniform constants {
	mat4 inv_proj;
    vec3 selected_color;
    float elapsed;
    vec3 light_direction;
    float pad;
    vec2 resolution;
} pushConst;

vec2 tex_offset;

struct FogParameters
{
	vec3 color;
	float linearStart;
	float linearEnd;
	float density;
	
	int equation;
	bool isEnabled;
};
float getFogFactor(FogParameters params, float fogCoordinate)
{
	float result = 0.0;
	if(params.equation == 0)
	{
		float fogLength = params.linearEnd - params.linearStart;
		result = (params.linearEnd - fogCoordinate) / fogLength;
	}
	else if(params.equation == 1) {
		result = exp(-params.density * fogCoordinate);
	}
	else if(params.equation == 2) {
		result = exp(-pow(params.density * fogCoordinate, 2.0));
	}
	
	result = 1.0 - clamp(result, 0.0, 1.0);
	return result;
}

vec2 bsgfx_getUV(int i) {
    vec2 uvs[5] = {
        vec2(in_texture.x + tex_offset.x, 1. - in_texture.y),
        vec2(in_texture.x - tex_offset.x, 1. - in_texture.y),
        vec2(in_texture.x, 1. - (in_texture.y + tex_offset.y)),
        vec2(in_texture.x, 1. - (in_texture.y - tex_offset.y)),
        vec2(in_texture.x, 1. - in_texture.y)
    };

    return uvs[i];
}

float bsgfx_getDepth(int i) {
    vec2 uv = bsgfx_getUV(i);
	float depth = texture(attachment_depth, uv).r;
    vec3 ndc = vec3(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, depth);
    vec4 view = pushConst.inv_proj * vec4(ndc, 1.0);
    view.xyz /= view.w;

	float near = -1.0, far = 1.0;
    return (near * far / (far + depth * (near - far)));
    return depth;
    return -view.z / 200.0;
}

vec3 bsgfx_getNormal(int i) {
	return texture(attachment_normal, bsgfx_getUV(i)).rgb;
}

/*
uint bsgfx_getIndex(int i) {
    uint index = uint(texture(attachment_index, bsgfx_getUV(i)).r);
    uint flags = bsgfx_extractFlags(index) & ~BSGFX_ID_IN_SHADOW;
	return bsgfx_index(flags, bsgfx_extractInstanceId(index));
}

float bsgfx_depthEdgeIndicator(float depth, vec3 normal) {
	float diff = 0.;
	diff += clamp(bsgfx_getDepth(0) - depth, 0., 1.);
	diff += clamp(bsgfx_getDepth(1) - depth, 0., 1.);
	diff += clamp(bsgfx_getDepth(2) - depth, 0., 1.);
	diff += clamp(bsgfx_getDepth(3) - depth, 0., 1.);
	return floor(smoothstep(.01, .02, diff) * 2.) / 2.;
}

float bsgfx_neighborNormalEdgeIndicator(int i, float depth, vec3 normal) {
	float depth_diff = bsgfx_getDepth(i) - depth;
	vec3 neighbor_normal = bsgfx_getNormal(i);
					
	float normal_diff = dot(normal - neighbor_normal, vec3(1., 0., 0.));
	float normal_indicator = clamp(smoothstep(-.01, .01, normal_diff), 0., 1.);
					
	return normal_diff + depth_diff;
}

float bsgfx_normalEdgeIndicator(float depth, vec3 normal) {
	float indicator = 0.;

	indicator += bsgfx_neighborNormalEdgeIndicator(0, depth, normal);
	indicator += bsgfx_neighborNormalEdgeIndicator(1, depth, normal);
	indicator += bsgfx_neighborNormalEdgeIndicator(2, depth, normal);
	indicator += bsgfx_neighborNormalEdgeIndicator(3, depth, normal);

	return step(.0075, indicator);
}

float bsgfx_indexEdgeIndicator(uint index) {
	float indicator = 0.;

    if (bsgfx_getIndex(0) != index) return 1.0;
    else if (bsgfx_getIndex(1) != index) return 1.0;
    else if (bsgfx_getIndex(2) != index) return 1.0;
    else if (bsgfx_getIndex(3) != index) return 1.0;

	return 0.0;
}
*/

void main() {
    out_color = vec4(1.);

	float depth = bsgfx_getDepth(4);
    vec3 normal = bsgfx_getNormal(4);
    vec3 color = texture(attachment_color, vec2(in_texture.x, 1.0 - in_texture.y)).rgb;
    uint index = uint(texture(attachment_index, vec2(in_texture.x, 1.0 - in_texture.y)).r);
    vec3 ray_trace = imageLoad(ray_trace_output, ivec2(
        in_texture.x * pushConst.resolution.x / 4.0, 
        (1.0 - in_texture.y) * pushConst.resolution.y / 4.0)).rgb;



    out_color.rgb = color;
    tex_offset = 1. / textureSize(attachment_depth, 0);


   // float dei = 0.0;
   // if (depthEdgeStrength > 0.0) 

   /*
    float dei = 0.0, nei = 0.0;
    if ((bsgfx_extractFlags(bsgfx_getIndex(0)) & BSGFX_ID_HIGHLIGHT) != 0 &&
        (bsgfx_extractFlags(bsgfx_getIndex(1)) & BSGFX_ID_HIGHLIGHT) != 0 &&
        (bsgfx_extractFlags(bsgfx_getIndex(2)) & BSGFX_ID_HIGHLIGHT) != 0 &&
        (bsgfx_extractFlags(bsgfx_getIndex(3)) & BSGFX_ID_HIGHLIGHT) != 0) 
    {
        dei = bsgfx_depthEdgeIndicator(depth, normal);
        nei = bsgfx_normalEdgeIndicator(depth, normal);
    }
    */

    float depth_strength = 2.0;
    float normal_strength = 1.0;
    vec3 edge_color = vec3(1.0, 0.95, 0.9);
   // float strength = dei > 0.0 ? (1.0 - depth_strength * dei) : (1.0 + normal_strength * nei);
   // if ((nei > 0.0 || dei > 0.0) && normal != vec3(0.0)) {
   //    // out_color.r *= (nei * normal_strength + dei * depth_strength) * edge_color.r;
   //    // out_color.b *= (nei * normal_strength + dei * depth_strength) * edge_color.g;
   //    // out_color.g *= (nei * normal_strength + dei * depth_strength) * edge_color.b;
   // }

  	depth = texture(attachment_depth, vec2(in_texture.x, 1.0 - in_texture.y)).r;

    out_color.a = 1.0;
}
