#ifndef ATLAS_GLSL
#define ATLAS_GLSL

#include "project/basilisk-gfx/shaders/bsgfx_material.glsl"

layout(set = BSGFX_SET_BUFFER_ATLAS_ANY, binding = BSGFX_BINDING_BUFFER_ATLAS_ANY) readonly buffer bsgfx_atlas_buffer {
    bsgfx_AtlasTexture bsgfx_atlas_textures[];
};

vec2 bsgfx_convertTextureCoordinates(int texture_id, vec2 coordinates) {
    vec2 coords = bsgfx_atlas_textures[texture_id].coords.xy;
    vec2 offset = bsgfx_atlas_textures[texture_id].coords.zw;

    return coordinates * coords + offset;
}

#endif