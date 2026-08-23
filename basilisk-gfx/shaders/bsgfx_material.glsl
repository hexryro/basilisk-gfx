#ifndef bsgfx_MATERIAL_GLSL
#define bsgfx_MATERIAL_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout(set = BSGFX_SET_MATERIALS, binding = BSGFX_BINDING_MATERIALS) readonly buffer bsgfx_materials_uniform {
    bsgfx_MaterialContract bsgfx_materials[];
};

bsgfx_MaterialContract bsgfx_material(uint index) {
    if (index >= BSGFX_MAX_MATERIALS_COUNT) {
        return bsgfx_materials[0];
    }
    return bsgfx_materials[index];
}

#endif