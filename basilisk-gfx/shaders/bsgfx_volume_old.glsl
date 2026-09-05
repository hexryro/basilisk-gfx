#ifndef bsgfx_SHADOWS_GLSL
#define bsgfx_SHADOWS_GLSL

#define BSGFX_VOLUME_EPSILON                       0.005
#define BSGFX_VOLUME_EPSILON_PERP                  0.01
#define BSGFX_VOLUME_EXTRUDE                       100.0

#ifndef BSGFX_VOLUME_SIZE_X
#define BSGFX_VOLUME_SIZE_X                        128
#endif

#ifndef BSGFX_VOLUME_SIZE_Y
#define BSGFX_VOLUME_SIZE_Y                        1
#endif

#ifndef BSGFX_VOLUME_SIZE_Z
#define BSGFX_VOLUME_SIZE_Z                        1
#endif

struct bsgfx_OutVertex {
    vec3 position;
    vec2 texture;
    float id;
};

layout(std430, set = BSGFX_SET_VOLUME_OUT_VERTICES, binding = bsgfx_OUT_VERTICES) buffer bsgfx_volume_out_vertex_buffer {
    float bsgfx_volume_out_vertices[];
};

layout(std430, set = BSGFX_SET_VOLUME_IN_VERTICES, binding = bsgfx_IN_VERTICES) buffer bsgfx_volume_in_vertex_buffer {
    bsgfx_Vertex bsgfx_volume_in_vertices[];
};

layout(std430, set = BSGFX_SET_VOLUME_IN_INDICES, binding = bsgfx_IN_INDICES) buffer bsgfx_volume_in_index_buffer {
    int bsgfx_volume_in_indices[];
};

layout(push_constant) uniform constants {
    vec3 light_direction;
    int id;
    int subtypes_offset;
    int subtypes_count;
    int include_flag;
    int exclude_flag;
} pushConst;

shared int bsgfx_shared_volume_vertices[BSGFX_VOLUME_SIZE_X];
int bsgfx_num_local_vertices = 0;

#ifdef bsgfx_TEXTURED_VOLUME
#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"
uint bsgfx_global_vertex_offset = 0;

void bsgfx_pushVolumeVertex(vec3 direction, vec3 perp, vec3 pt, float extrusion, vec2 tex, uint index) {
	pt += direction * extrusion + perp * BSGFX_VOLUME_EPSILON_PERP;

    bsgfx_volume_out_vertices[(BSGFX_NUM_SHADOW_VERTICES * BSGFX_VOLUME_VERTEX_SIZE - bsgfx_num_local_vertices) + 0 - BSGFX_VOLUME_VERTEX_SIZE * 1] = pt.x;
    bsgfx_volume_out_vertices[(BSGFX_NUM_SHADOW_VERTICES * BSGFX_VOLUME_VERTEX_SIZE - bsgfx_num_local_vertices) + 1 - BSGFX_VOLUME_VERTEX_SIZE * 1] = pt.y;
    bsgfx_volume_out_vertices[(BSGFX_NUM_SHADOW_VERTICES * BSGFX_VOLUME_VERTEX_SIZE - bsgfx_num_local_vertices) + 2 - BSGFX_VOLUME_VERTEX_SIZE * 1] = pt.z;
    bsgfx_volume_out_vertices[(BSGFX_NUM_SHADOW_VERTICES * BSGFX_VOLUME_VERTEX_SIZE - bsgfx_num_local_vertices) + 3 - BSGFX_VOLUME_VERTEX_SIZE * 1] = tex.x;
    bsgfx_volume_out_vertices[(BSGFX_NUM_SHADOW_VERTICES * BSGFX_VOLUME_VERTEX_SIZE - bsgfx_num_local_vertices) + 4 - BSGFX_VOLUME_VERTEX_SIZE * 1] = tex.y;
    bsgfx_volume_out_vertices[(BSGFX_NUM_SHADOW_VERTICES * BSGFX_VOLUME_VERTEX_SIZE - bsgfx_num_local_vertices) + 5 - BSGFX_VOLUME_VERTEX_SIZE * 1] = float(bsgfx_mesh_instances[index].header.bone_index);
    bsgfx_num_local_vertices += BSGFX_VOLUME_VERTEX_SIZE;
}
#else
uint bsgfx_global_vertex_offset = 0;

void bsgfx_pushVolumeVertex(vec3 direction, vec3 perp, vec3 pt, float extrusion, vec2 tex, uint index) {
	pt += direction * extrusion + perp * BSGFX_VOLUME_EPSILON_PERP;

    bsgfx_volume_out_vertices[bsgfx_global_vertex_offset + bsgfx_num_local_vertices + 0] = pt.x;
    bsgfx_volume_out_vertices[bsgfx_global_vertex_offset + bsgfx_num_local_vertices + 1] = pt.y;
    bsgfx_volume_out_vertices[bsgfx_global_vertex_offset + bsgfx_num_local_vertices + 2] = pt.z;
    bsgfx_volume_out_vertices[bsgfx_global_vertex_offset + bsgfx_num_local_vertices + 3] = tex.x;
    bsgfx_volume_out_vertices[bsgfx_global_vertex_offset + bsgfx_num_local_vertices + 4] = tex.y;
    bsgfx_volume_out_vertices[bsgfx_global_vertex_offset + bsgfx_num_local_vertices + 5] = float(index);
    bsgfx_num_local_vertices += BSGFX_VOLUME_VERTEX_SIZE;
}
#endif

void bsgfx_extrudeVolumeEdgeCCW(vec3 direction, vec3 perp, vec3 a, vec3 b, vec2 txa, vec2 txb, uint index) {
    bsgfx_pushVolumeVertex(direction, perp, a, BSGFX_VOLUME_EPSILON, txa, index);
    bsgfx_pushVolumeVertex(direction, perp, b, BSGFX_VOLUME_EPSILON, txb, index);
    bsgfx_pushVolumeVertex(direction, perp, a, BSGFX_VOLUME_EXTRUDE, txa, index);

    bsgfx_pushVolumeVertex(direction, perp, a, BSGFX_VOLUME_EXTRUDE, txa, index);
    bsgfx_pushVolumeVertex(direction, perp, b, BSGFX_VOLUME_EPSILON, txb, index);
    bsgfx_pushVolumeVertex(direction, perp, b, BSGFX_VOLUME_EXTRUDE, txb, index);
}

void bsgfx_extrudeVolumeEdgeCW(vec3 direction, vec3 perp, vec3 a, vec3 b, vec2 txa, vec2 txb, uint index) {
    bsgfx_pushVolumeVertex(direction, perp, b, BSGFX_VOLUME_EPSILON, txb, index);
    bsgfx_pushVolumeVertex(direction, perp, a, BSGFX_VOLUME_EPSILON, txa, index);
    bsgfx_pushVolumeVertex(direction, perp, a, BSGFX_VOLUME_EXTRUDE, txa, index);

    bsgfx_pushVolumeVertex(direction, perp, b, BSGFX_VOLUME_EPSILON, txb, index);
    bsgfx_pushVolumeVertex(direction, perp, a, BSGFX_VOLUME_EXTRUDE, txa, index);
    bsgfx_pushVolumeVertex(direction, perp, b, BSGFX_VOLUME_EXTRUDE, txb, index);
}

uint bsgfx_getVolumeTriangleStartIndex(uint total_invocations) {
    uint base_size = total_invocations / BSGFX_VOLUME_SIZE_X;
    uint remainder = total_invocations % BSGFX_VOLUME_SIZE_X;
    return (gl_LocalInvocationIndex < remainder) ? (base_size + 1) * gl_LocalInvocationIndex : base_size * gl_LocalInvocationIndex + remainder;
}

uint bsgfx_getVolumeTriangleEndIndex(uint total_invocations, uint start_triangle) {
    uint base_size = total_invocations / BSGFX_VOLUME_SIZE_X;
    uint remainder = total_invocations % BSGFX_VOLUME_SIZE_X;
    return (gl_LocalInvocationIndex < remainder) ? start_triangle + base_size + 1 : start_triangle + base_size;
}

int bsgfx_computeVertexSize(uint start_index, uint end_index, int instance) {
    vec3 direction = pushConst.light_direction;

    int count = 0;
    for (uint i = start_index; i < end_index; i += 3) {
        vec3 pts[3];
		pts[0] = bsgfx_createVolumeVertex(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 0]], instance);
		pts[1] = bsgfx_createVolumeVertex(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 1]], instance);
		pts[2] = bsgfx_createVolumeVertex(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 2]], instance);

        vec3 normal = cross(pts[1].xyz - pts[0].xyz, pts[2].xyz - pts[0].xyz);

        // skip backfacing
        #ifdef bsgfx_CULL_BACKFACING
        if (dot(normal, direction) > 0)
            continue;
        #else
        if (dot(normal, direction) < 0)
            continue;
        #endif

        int vertex_size = BSGFX_VOLUME_VERTEX_SIZE * 4;
        count += vertex_size * 3 * 2;
    }

    bsgfx_shared_volume_vertices[int(gl_LocalInvocationIndex)] += count;

    return count;
}

void bsgfx_pushVolume(uint start_index, uint end_index, int instance) {
    vec3 direction = pushConst.light_direction;
    vec3 perp = normalize(cross(direction, vec3(0.0, 1.0, 0.0)));

    for(uint i = start_index; i < end_index; i += 3) {
        #ifdef bsgfx_TEXTURED_VOLUME
        if (bsgfx_metadata.textured_volumes_count < BSGFX_MAX_NUM_TEXTURED_VOLUMES) {
            bsgfx_metadata.textured_volumes[bsgfx_metadata.textured_volumes_count].texture = int(instance);
            bsgfx_metadata.textured_volumes[bsgfx_metadata.textured_volumes_count].start = bsgfx_num_local_vertices / BSGFX_VOLUME_VERTEX_SIZE;
        }
        atomicAdd(bsgfx_metadata.textured_volumes_count, 1);
        #endif

	    vec3 pts[3];
        vec2 tx[3];

	    pts[0] = bsgfx_createVolumeVertex(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 0]], instance);
	    pts[1] = bsgfx_createVolumeVertex(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 1]], instance);
	    pts[2] = bsgfx_createVolumeVertex(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 2]], instance);
        
        tx[0] = vec2(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 0]].tx, bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 0]].ty);
        tx[1] = vec2(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 1]].tx, bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 1]].ty);
        tx[2] = vec2(bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 2]].tx, bsgfx_volume_in_vertices[bsgfx_volume_in_indices[i + 2]].ty);

        vec3 normal = cross(pts[1].xyz - pts[0].xyz, pts[2].xyz - pts[0].xyz);

        // skip backfacing
        #ifdef bsgfx_CULL_BACKFACING
        if (dot(normal, direction) > 0)
            continue;
        #else
        if (dot(normal, direction) < 0)
            continue;
        #endif

        vec3 edges[3][2];

        edges[0][0] = pts[1].xyz;
        edges[0][1] = pts[0].xyz;
        edges[1][0] = pts[2].xyz;
        edges[1][1] = pts[1].xyz;
        edges[2][0] = pts[0].xyz;
        edges[2][1] = pts[2].xyz;

        vec2 tx_edges[3][2];
        tx_edges[0][0] = tx[1].xy;
        tx_edges[0][1] = tx[0].xy;
        tx_edges[1][0] = tx[2].xy;
        tx_edges[1][1] = tx[1].xy;
        tx_edges[2][0] = tx[0].xy;
        tx_edges[2][1] = tx[2].xy;

        uint index = bsgfx_num_local_vertices / BSGFX_VOLUME_VERTEX_SIZE;

        // edges
        for (int e = 0; e < 3; e++) {
            if (edges[e][0] == pts[e].xyz)
                bsgfx_extrudeVolumeEdgeCW(direction, perp, edges[e][0], edges[e][1], tx_edges[e][0], tx_edges[e][1], index);
            else
                bsgfx_extrudeVolumeEdgeCCW(direction, perp, edges[e][0], edges[e][1], tx_edges[e][0], tx_edges[e][1], index);
        }

        // front cap
        bsgfx_pushVolumeVertex(direction, perp, pts[0].xyz, BSGFX_VOLUME_EPSILON, tx[0], index);
        bsgfx_pushVolumeVertex(direction, perp, pts[1].xyz, BSGFX_VOLUME_EPSILON, tx[1], index);
        bsgfx_pushVolumeVertex(direction, perp, pts[2].xyz, BSGFX_VOLUME_EPSILON, tx[2], index);

        // back cap
        bsgfx_pushVolumeVertex(direction, perp, pts[2].xyz, BSGFX_VOLUME_EXTRUDE, tx[2], index);
        bsgfx_pushVolumeVertex(direction, perp, pts[1].xyz, BSGFX_VOLUME_EXTRUDE, tx[1], index);
        bsgfx_pushVolumeVertex(direction, perp, pts[0].xyz, BSGFX_VOLUME_EXTRUDE, tx[0], index);
    }
}

void bsgfx_createVolumes() {
    int local_i = int(gl_LocalInvocationIndex);
    bsgfx_shared_volume_vertices[local_i] = 0;

    bsgfx_InstanceTypeMetadata type = bsgfx_metadata.instance_types[BSGFX_INSTANCE_TYPE];

    int first_subtype = 0;
    int last_subtype = bsgfx_metadata.subtypes_count;

    if (pushConst.subtypes_count != -1) {
        first_subtype = pushConst.subtypes_offset;
        last_subtype = pushConst.subtypes_offset + pushConst.subtypes_count;
    }

    for (int j = first_subtype; j < last_subtype; j++) {
        bsgfx_InstanceSubtypeMetadata subtype = bsgfx_metadata.instance_subtypes[j];
        if (subtype.instance_type != BSGFX_INSTANCE_TYPE)
            continue;
        if ((subtype.flags & pushConst.include_flag) == 0)
            continue;

        uint start_index = bsgfx_getVolumeTriangleStartIndex(subtype.index_count / 3);
        uint end_index = bsgfx_getVolumeTriangleEndIndex(subtype.index_count / 3, start_index) * 3 + subtype.index_offset;
        start_index *= 3;
        start_index += subtype.index_offset;

        int count = 0;
        if (pushConst.include_flag != BSGFX_SUBTYPE_PRE_COMPUTE_SHADOWS) {
            for (int instance = subtype.instance_offset; instance < (subtype.instance_count + subtype.instance_offset); instance++) {
                count += bsgfx_computeVertexSize(start_index, end_index, instance);
            }
        }
        else {
            count += bsgfx_computeVertexSize(start_index, end_index, subtype.instance_offset);
        }

	    atomicAdd(bsgfx_metadata.computed_subtype_volume_vertices[j], count / 3);
    }

	if (bsgfx_shared_volume_vertices[local_i] == 0) 
        return;

    bsgfx_global_vertex_offset = bsgfx_metadata.computed_volume_vertices[pushConst.id] * 3;
//    for (int i = 0; i < BSGFX_NUM_VOLUME_COMPUTATIONS; i++)
//	    bsgfx_global_vertex_offset += bsgfx_metadata.computed_volume_vertices[i] * 3;

bsgfx_metadata.textured_volumes_count = 0;
    barrier();

	// atomicAdd(bsgfx_metadata.offset, bsgfx_shared_volume_vertices[local_i] / 3);
	atomicAdd(bsgfx_metadata.computed_volume_vertices[pushConst.id], bsgfx_shared_volume_vertices[local_i] / 3);

    for (int i = 0; i < local_i; i++)
        bsgfx_global_vertex_offset += bsgfx_shared_volume_vertices[i];

    for (int j = first_subtype; j < last_subtype; j++) {
        bsgfx_InstanceSubtypeMetadata subtype = bsgfx_metadata.instance_subtypes[j];
        if (subtype.instance_type != BSGFX_INSTANCE_TYPE)
            continue;
        if ((subtype.flags & pushConst.include_flag) == 0)
            continue;
        if ((subtype.flags & pushConst.exclude_flag) != 0)
            continue;

        uint start_index = bsgfx_getVolumeTriangleStartIndex(subtype.index_count / 3);
        uint end_index = bsgfx_getVolumeTriangleEndIndex(subtype.index_count / 3, start_index) * 3 + subtype.index_offset;
        start_index *= 3;
        start_index += subtype.index_offset;

        if (pushConst.include_flag != BSGFX_SUBTYPE_PRE_COMPUTE_SHADOWS) {
            for (int instance = subtype.instance_offset; instance < (subtype.instance_count + subtype.instance_offset); instance++) {
                bsgfx_pushVolume(start_index, end_index, instance);
            }
        }
        else {
            bsgfx_pushVolume(start_index, end_index, 999);
        }
    }
}

#endif