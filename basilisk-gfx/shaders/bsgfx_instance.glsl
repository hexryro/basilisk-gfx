#ifndef BSGFX_INSTANCE_GLSL
#define BSGFX_INSTANCE_GLSL

#include "project/basilisk-gfx/shaders/bsgfx.glsl"

layout(std430, set = BSGFX_SET_MESH_DATA, binding = BSGFX_BINDING_MESH_DATA) buffer mesh_data {
	bsgfx_Instantiator bsgfx_metadata;
};

#endif