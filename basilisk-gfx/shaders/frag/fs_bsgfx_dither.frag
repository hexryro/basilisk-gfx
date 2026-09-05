#version 450
#extension GL_ARB_shading_language_include : require
#extension GL_EXT_samplerless_texture_functions : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
#define BSGFX_QUAD_INSTANCES
#include "project/basilisk-gfx/shaders/bsgfx_quad.glsl"

layout (location = BSGFX_LO_SUBPASS_0_OUT_COLOR) out vec4 out_color;
layout (location = BSGFX_LO_SUBPASS_0_OUT_NORMAL) out vec4 out_normal;
layout (location = BSGFX_LO_SUBPASS_0_OUT_INDEX) out uint out_index;
layout (location = BSGFX_LO_SUBPASS_0_OUT_POSITION) out vec4 out_position;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;
layout(location = 9) in vec2 in_texture_unprocessed;

layout(set = BSMOD_SET_IMAGE_ATLAS_UI, binding = BSMOD_BINDING_IMAGE_ATLAS_UI) uniform sampler2D atlas_texture;

layout(push_constant) uniform constants {
    mat4 camera;
    float elapsed;
    float padding;
    vec2 resolution;
    float border_radius;
} pushConst;

void dither() {
    ivec2 p = ivec2(gl_FragCoord.xy);

    if (((p.x + p.y) & 1) == 0) {
        discard;
    }
}

void onlyBorder(uint instance) {
    vec2 quad_size = bsgfx_quadSize(instance);
    vec2 quad_min = bsgfx_quadPosition(instance).xy;
    vec2 quad_max = quad_min + quad_size;

    vec2 p = gl_FragCoord.xy;
    p.y = pushConst.resolution.y - p.y;

    bool on_border =        
        p.x < quad_min.x + 1.0 ||
        p.x > quad_max.x - 1.0 ||
        p.y < quad_min.y + 1.0 ||
        p.y > quad_max.y - 1.0;


    if (!on_border)
        discard;
}

void main() {
    out_color = vec4(in_normal, 1.0);
    out_normal.xyz = in_normal;
    out_normal.a = 0.0;
    out_position = vec4(in_world_position, 1.0);

    out_normal.xyz = in_normal;
    if (out_normal.x != 0.0 || out_normal.y != 0.0 || out_normal.z != 0.0)
        out_normal.a = 1.0;

    out_color = texture(atlas_texture, vec2(in_texture.x, 1.0 - in_texture.y)) * in_color;

    vec2 scale = vec2(
        bsgfx_quad_instances[in_instance].transform[0],
        bsgfx_quad_instances[in_instance].transform[4]);

    vec2 uv = vec2(in_texture_unprocessed.x, 1.0 - in_texture_unprocessed.y);

    vec2 p = (uv - 0.5) * scale;

    vec2 halfSize = scale * 0.5;

    vec4 radii = bsgfx_roundedQuadRadii(in_instance);

    vec2 quadrant = step(0.0, p);

    float r = mix(
        mix(radii.w, radii.z, quadrant.x),
        mix(radii.x, radii.y, quadrant.x),
        quadrant.y
    );

    r = min(r, min(halfSize.x, halfSize.y));

    vec2 q = abs(p) - halfSize + vec2(r);
    float dist = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;

    float aa = fwidth(dist);
    float alpha = 1.0 - smoothstep(0.0, aa, dist);
    out_color.a *= alpha;

    if (out_color.a == 0.0)
        discard;

    dither();
    onlyBorder(in_instance);
}