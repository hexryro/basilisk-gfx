#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"
#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_FLAGS) out uint out_flags;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout(set = BSGFX_SET_512, binding = BSGFX_BINDING_512) uniform sampler2DArray images;

layout(push_constant) uniform constants {
	mat4 camera;
    float elapsed;
    int noise_00;
    int noise_01;
} pushConst;

// https://github.com/SableRaf/Filters4Processing/blob/master/sketches/ContrastSaturationBrightness/data/ContrastSaturationBrightness.glsl
vec3 bsgfx_csb(vec3 color, float brt, float sat, float con) {
	// Increase or decrease theese values to adjust r, g and b color channels seperately
	const float AvgLumR = 0.5;
	const float AvgLumG = 0.5;
	const float AvgLumB = 0.5;
	
	const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
	
	vec3 AvgLumin  = vec3(AvgLumR, AvgLumG, AvgLumB);
	vec3 brtColor  = color * brt;
	vec3 intensity = vec3(dot(brtColor, LumCoeff));
	vec3 satColor  = mix(intensity, brtColor, sat);
	vec3 conColor  = mix(AvgLumin, satColor, con);
	
	return conColor;
}

vec2 bsgfx_sineWave(vec2 p) {
    float pi = 3.14159;
    float A = 0.015;
    float w = 10.0 * pi;
    float t = 30.0 * pi / 180.0;

    float y = sin(w * p.x + t) * A;

    return vec2(p.x, p.y + y);
}

void main() {
    bsgfx_MaterialContract m = bsgfx_material(in_material);

    float w = bsgfx_mesh_instances[in_instance].transform[0][3];
    float h = bsgfx_mesh_instances[in_instance].transform[1][3];

    out_color = vec4(in_texture.xy, 0.0, 1.0);
    out_normal.xyz = in_normal;
    out_normal.a = 1.0;
    out_position = vec4(in_world_position, 1.0);
    out_color.xyz = in_normal;

    vec2 scale = vec2(0.035, 0.07);
    vec2 direction_00 = vec2(0.05, 0.08);
    vec2 direction_01 = vec2(0.05, 0.02);

    out_color = texture(images, vec3(vec2(pushConst.elapsed) * direction_00 + (in_texture.xy + vec2(0.5)) * vec2(w, h) * scale, pushConst.noise_00));
    out_color += (1.0 + out_color) * texture(images, vec3(vec2(pushConst.elapsed) * direction_01 + in_texture.xy * vec2(-w, h) * scale, pushConst.noise_00));
    out_color.xyz = bsgfx_csb(out_color.xyz, 1.0, 1.0, 0.2);
    out_color.xyz *= vec3(0.2, 0.4, 1.2);
    float brightness = dot(out_color.xyz, vec3(0.2126, 0.7152, 0.0722));

    if (brightness > 1.0)
     //   out_color.xyz = vec3(8, 10, 50) / 255.0;
        out_color.xyz = vec3(50, 120, 160) / 255.0;

    out_color.w = 0.75;
    out_index = in_instance;
    out_flags = in_flags;
    gl_FragDepth = in_depth;
    out_color *= m.color;
    out_color = vec4(0.0);
}
