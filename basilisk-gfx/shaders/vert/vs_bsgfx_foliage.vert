#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout (location = 0) in vec4 bs_Position;
layout (location = 1) in vec3 bs_Texture;
layout (location = 2) in vec3 bs_Normal;
layout (location = 3) in vec4 bs_Color;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec4 out_color;
layout(location = 2) out vec3 out_normal;
layout(location = 3) out vec3 out_world_position;
layout(location = 4) out vec3 out_texture;
layout(location = 5) out uint out_instance;
layout(location = 6) out uint out_flags;
layout(location = 7) out uint out_material;
layout(location = 8) out float out_depth;

layout(push_constant) uniform constants {
	mat4 camera;
    float elapsed;
} pushConst;

layout(set = BSGFX_SET_BUFFER_ATLAS_ANY, binding = BSGFX_BINDING_BUFFER_ATLAS_ANY) readonly buffer bsgfx_atlas_buffer {
    bsgfx_AtlasTexture bsgfx_atlas_textures[];
};

void main() {
    out_position = bs_Position.xyz;
    out_color = bs_Color;
    out_texture = bs_Texture;

    bsgfx_AtlasTexture texture = bsgfx_atlas_textures[int(bs_Position.w)];

    float width = texture.coords.z - texture.coords.x;
    out_texture.x += width * float((int(pushConst.elapsed * 5.0 + bs_Texture.z)) % texture.split);

    vec4 clipSpacePosition = bsgfx_process(pushConst.camera * vec4(bs_Normal, 1.0));
    vec3 ndcPosition = clipSpacePosition.xyz / clipSpacePosition.w;
    vec2 windowPosition = (ndcPosition.xy * 0.5 + 0.5);

    out_normal.xy = windowPosition;
    out_normal = bs_Normal;
    gl_Position = bsgfx_process(pushConst.camera * vec4(bs_Position.xyz, 1.0));
    out_depth = gl_Position.z / gl_Position.w;
}
