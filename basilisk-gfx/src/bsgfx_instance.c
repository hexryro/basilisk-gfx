
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

#include <bsgfx_cache.h>
#include <bsgfx_internal.h>
#include <string.h>

#include <assert.h>
#include <bs_internal.h>

static bs_List _bsgfx_instance_types = { .unit_size = sizeof(bsgfx_InstanceType), .increment = 32 };



  /*==============================================================================
   * Instance Types
   =============================================================================*/

BSGFXAPI bs_Result _val_bsgfx_ensureInstanceCount(bsgfx_InstanceType* instance_type, bs_U32 instances_count, bs_U32 overhead_count) {
	BSGFX_VALIDATE(instance_type->device_instances != NULL, BS_RESULT_VALIDATION_ERROR,);

	return _bsgfx_ensureInstanceCount(instance_type, instances_count, overhead_count);
}

BSGFXAPI bs_Result _bsgfx_ensureInstanceCount(bsgfx_InstanceType* instance_type, bs_U32 instances_count, bs_U32 overhead_count) {
	bs_Result result = BS_RESULT_OK;

	size_t existing_capacity = instance_type->device_instances->num_bytes;
	size_t existing_size = instance_type->instance_count * (size_t)instance_type->instance_size;
	size_t requested_size = instances_count * (size_t)instance_type->instance_size;

	assert(existing_capacity >= existing_size);

	if ((existing_size + requested_size) > existing_capacity) {
		size_t remaining_size = existing_capacity - existing_size;
		size_t needed_size = remaining_size - requested_size;

		size_t overhead_size = overhead_count * (size_t)instance_type->instance_size;
		size_t total_size = existing_capacity + needed_size + overhead_size;

		assert(remaining_size > requested_size);

		bs_destroyBuffer(instance_type->device_instances);

		bs_Object* object = BS_BUFFER(-1, -1, false);
		result = bs_buffer(object, total_size,
			BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT,
			BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			0);

		if (result != BS_RESULT_OK)
			return result;

		result = bs_mapBuffer(object->buffer, BS_U32_MAX);
		result = bs_bindBuffer(BSGFX_SET_INSTANCE_SUBTYPES, BSGFX_BINDING_INSTANCE_SUBTYPES, object->buffer);
	}

	return result;
}

BSGFXAPI bool _bsgfx_validateInstanceType(const char* library_name, bsgfx_InstanceType* instance_type) { // TODO: use library_name
	//BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_TYPES), false, );
	//BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_SUBTYPES), false,);
//	BSGFX_VALIDATE(instance_type < BSGFX_INSTANCE_TYPE_COUNT, false,);
//	BSGFX_VALIDATE(_poser_->instance_buffers[instance_type] != NULL, false,);

	return true;
}

 /**
  Create instance type
  */
BSGFXAPI bs_Result _val_bsgfx_instanceType(size_t instance_size, int bind_set, int point, bsgfx_InstanceType** out) {
	//BSGFX_VALIDATE(_poser_->instance_buffers[instance_type_id] != NULL,,);
	//BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_TYPES),, );
	//BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_SUBTYPES),,);
	bs_BindSet* bind_set_query = bs_queryBindSet(bind_set);
	BSGFX_VALIDATE(bind_set_query != NULL, BS_RESULT_VALIDATION_ERROR,);
	BSGFX_VALIDATE(bs_queryBinding(bind_set_query, point) != NULL, BS_RESULT_VALIDATION_ERROR,);

	return _bsgfx_instanceType(instance_size, bind_set, point, out);
}

BSGFXAPI bs_Result _bsgfx_instanceType(size_t instance_size, int bind_set, int point, bsgfx_InstanceType** out) {
	bs_Result result;

	instance_size += sizeof(bsgfx_InstanceHeader);

	//bs_Buffer* instance_types = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_TYPES)->buffer;
	
	bs_BufferUsageFlags usage_flags = 0;
	bs_MemoryPropertyFlags memory_flags = BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	bs_Binding* binding = bs_queryBinding(bs_queryBindSet(bind_set), point);
	if (!binding)
		return BS_RESULT_FAILED_TO_QUERY;

	if (binding->type == BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
		usage_flags |= BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	else if (binding->type == BS_DESCRIPTOR_TYPE_STORAGE_BUFFER)
		usage_flags |= BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT;
	else {
		bs_warnF("Invalid bind type %d\n", binding->type); // TODO: _bsgfx_warn
		return BS_RESULT_INVALID_TYPE;
	}

	// TODO: remove
	// figure out what is correct first
	VkDeviceSize atom_size = 64;

	const int initial_instances_count = 128;
	size_t size = initial_instances_count * instance_size;
	VkDeviceSize aligned_size = (size + 64 - 1) & ~(atom_size - 1);

	bs_Object* object = BS_BUFFER(-1, 0, 0);
	result = bs_buffer(object, aligned_size, usage_flags, memory_flags, 0);
	if (result != BS_RESULT_OK)
		return result;

	result = bs_mapBuffer(object->buffer, BS_U32_MAX);
	if (result != BS_RESULT_OK)
		return result;

	result = bs_bindBuffer(bind_set, point, object->buffer);

	*out = bs_pushBack(&_bsgfx_instance_types, &(bsgfx_InstanceType) {
		.device_instances = object->buffer,
		.instance_size = instance_size,
		.subtypes = bs_list(sizeof(bsgfx_InstanceSubtype), 256)
	});

//	int num_swaps = (instance_types->flags & BSI_BUFFER_SWAPS_BIT) ? bs_context()->frames_in_flight : 1;
//	for (int i = 0; i < num_swaps; i++) {
//		bsgfx_InstanceTypeHeader* instance_type_header = instance_types->_[i].data;
//		instance_type_header->instance_types[instance_type_id].allocated = max_instance_count;
//	}

	return BS_RESULT_OK;
}



  /*==============================================================================
   * Subtypes
   =============================================================================*/

BSGFXAPI bool _bsgfx_validateSubtype(const char* library_name, bsgfx_InstanceSubtype* subtype) { // TODO: use library_name
	BSGFX_VALIDATE(subtype != NULL, BS_RESULT_VALIDATION_ERROR, );

	return true;
}

 /**
  Delete subtype
  */
BSGFXAPI void _val_bsgfx_deleteSubtype(bsgfx_InstanceSubtype* subtype) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return;

	_bsgfx_deleteSubtype(subtype);
}

BSGFXAPI void _bsgfx_deleteSubtype(bsgfx_InstanceSubtype* subtype) {
	BS_WARN("Not implemented");
	//bsgfx_InstanceType* type = bs_fetchUnit(&_bsgfx_instance_types, instance_type_id);
	//_bs_erase(&type->subtypes, subtype_id, 1);
}
 /**
  Create subtype
  */
BSGFXAPI int _val_bsgfx_subtype(bsgfx_InstanceType* instance_type, bs_Batch* batch, bs_U32 flags, bs_Range range, bsgfx_InstanceSubtype** out) {
	if (!_bsgfx_validateInstanceType("GFX", instance_type))
		return 0;

	return _bsgfx_subtype(instance_type, batch, flags, range, out);
}

BSGFXAPI bs_Result _bsgfx_subtype(bsgfx_InstanceType* instance_type, bs_Batch* batch, bs_U32 flags, bs_Range range, bsgfx_InstanceSubtype** out) {
	int index = instance_type->subtypes.count;
	*out = bs_pushBack(&instance_type->subtypes, &(bsgfx_InstanceSubtype) {
		.instance_type2 = instance_type,
		.index_offset = range.offset,
		.index_count = range.num,
		.batch_source_id = batch->head.source_id,
		.batch_id = batch->head.id,
		.flags = flags,
		.host_instances = bs_list(instance_type->instance_size, 64),
	});

	//int existing = -1;

//	if (key != 0) {
//		existing = _bsgfx_querySubtypeNull(instance_type_id, key);
//		if (existing != -1)
//			bs_throwBasiliskF(BSX_DUPLICATE, "Subtypes (%d, %d)", instance_type_id, key);
//
//		if (bs_fetch(batch_id)->batch != range.batch) {
//			bs_throwBasiliskF(BSX_MISMATCH, "Subtype (%d, %d)\nBatch %s != Batch %s",
//				instance_type_id, key, bs_idName(batch_id), (range.batch->head.id ? bs_idName(range.batch->head.id) : NULL));
//			return -1;
//		}
//	}

	return BS_RESULT_OK;
}

 /**
  Render subtype
  */
BSGFXAPI void _val_bsgfx_renderSubtype(bs_Queue* queue, bsgfx_InstanceSubtype* subtype, bs_Pipeline* pipeline) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return;

	_bsgfx_renderSubtype(queue, subtype, pipeline);
}

BSGFXAPI void _bsgfx_renderSubtype(bs_Queue* queue, bsgfx_InstanceSubtype* subtype, bs_Pipeline* pipeline) {
	int batch_source_id = subtype->batch_source_id;
	int batch_id = subtype->batch_id;

	if (!bs_exists(batch_source_id, batch_id))
		return;

	bs_Batch* batch = bs_fetch(batch_source_id, batch_id)->batch;

	bs_render(queue, batch, pipeline,
		subtype->index_offset,
		subtype->index_count,
		subtype->instance_offset,
		subtype->host_instances.count);
}

 /**
  Reset subtype
  */
/*
BSGFXAPI void _val_bsgfx_resetSubtype(int subtype) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return;
	
	_bsgfx_resetSubtype(subtype);
}

BSGFXAPI void _bsgfx_resetSubtype(int subtype_id) {
	bsgfx_InstanceSubtype* instance_subtype = bs_fetchUnit(&_bsgfx_instance_subtypes, subtype_id);
	bsgfx_InstanceType* instance_type = bs_fetchUnit(&_bsgfx_instance_types, instance_subtype->instance_type);

	unsigned char* instances = bs_bufferMap(instance_type->device_instances);

	int count = type_metadata->count;

	for (int i = 0; i < count; i++) {
		bsgfx_InstanceHeader* instance = instances + i * instance_type->instance_size;

		if (instance->subtype == subtype) {
			for (int j = i; j < count - 1; j++)
				instance[j] = instance[j + 1];

			type_metadata->count--;
		}
	}

	subtype_metadata->instance_count = 0;

	assert(type_metadata->count >= 0);
}
*/



  /*==============================================================================
   * Instancing
   =============================================================================*/

 /**
  Create instance
  */
BSGFXAPI int _val_bsgfx_instantiate(bsgfx_InstanceSubtype* subtype, const char* data, int data_size, bs_U32 flags, unsigned int bone_index, int id, int material) {
	const int max_tick_count = 1000;

	BSGFX_VALIDATE(flags <= BS_U16_MAX, 0,);
	BSGFX_VALIDATE(material <= BS_U16_MAX, 0, );
	BSGFX_VALIDATE((data_size + sizeof(bsgfx_InstanceHeader)) <= subtype->instance_type2->instance_size, 0, );
	BSGFX_VALIDATE(subtype->instance_type2->tick_count < max_tick_count, 0, "Infinite loop detected");

	return _bsgfx_instantiate(subtype, data, data_size, flags, bone_index, id, material);
}

BSGFXAPI int _bsgfx_instantiate(bsgfx_InstanceSubtype* subtype, const char* data, int data_size, bs_U32 flags, unsigned int bone_index, int id, int material) {
	//int out_index = bsgfx_index(flags, instance_type->instance_count);

	subtype->instance_type2->instance_count++;

	bsgfx_InstanceHeader* instance = bs_alloca(subtype->instance_type2->instance_size);
	instance->id = id;
	instance->flags = flags;
	instance->material = material;
	//instance->subtype = subtype_id;
	instance->bone_index = bone_index;
	memcpy(instance + 1, data, data_size);

	int index = subtype->host_instances.count;
	bs_pushBack(&subtype->host_instances, instance);

	return index;
}

 /**
  Tick instances
  */
BSGFXAPI void _val_bsgfx_tickInstancesType(bsgfx_InstanceType* type) {
	BSGFX_VALIDATE(type->device_instances != NULL,,);
	_bsgfx_tickInstanceType(type);
}

BSGFXAPI void _bsgfx_tickInstanceType(bsgfx_InstanceType* type) {
	if (type->instance_count <= 0)
		return;

	unsigned char* destination = bs_bufferMap(type->device_instances);

	for (int j = 0, offset = 0; j < type->subtypes.count; j++) {
		bsgfx_InstanceSubtype* subtype = bs_fetchUnit(&type->subtypes, j);

		bsgfx_InstanceHeader* src_instance = subtype->host_instances.data;
		bsgfx_InstanceHeader* dst_instance = destination + offset;

		memcpy(dst_instance, src_instance, subtype->host_instances.count * type->instance_size);
		subtype->host_instances.count = 0;

		subtype->instance_offset = offset;

		offset += subtype->host_instances.count * type->instance_size;
	}

	bs_bindBuffer(type->device_instances->bind_set, type->device_instances->binding, type->device_instances);
	type->tick_count++;
}

 /**
  Reset instances
  */
BSGFXAPI void _val_bsgfx_resetInstanceType(bsgfx_InstanceType* type) {
	BSGFX_VALIDATE(type != NULL, , );
	BSGFX_VALIDATE(bs_bufferIsMapped(type->device_instances),,);

	_bsgfx_resetInstanceType(type);
}

BSGFXAPI void _bsgfx_resetInstanceType(bsgfx_InstanceType* type) {
	for (int i = 0; i < type->subtypes.count; i++) {
		bsgfx_InstanceSubtype* instance_subtype = bs_fetchUnit(&type->subtypes, i);
		instance_subtype->host_instances.count = 0;
	}
	type->tick_count = 0;
}

BSGFXAPI void _bsgfx_instanceHiResMesh(bs_Mesh* mesh, const bs_vec3* position, const bs_vec4* rotation, float scale, int subtype_offset, bool origin_at_center) {
	bs_vec3 min = mesh->aabb.min;
	bs_vec3 max = mesh->aabb.max;
	bs_vec3 size;
	bs_v3Sub(&max, &min, &size);

	float max_dim = BS_MAX(BS_MAX(size.x, size.y), size.z);

	float s = scale / max_dim;
	bs_vec3 sc = { s, s, s };

	bs_vec3 center;
	bs_v3Add(&min, &max, &center);
	bs_v3MulS(&center, 0.5f, &center);

	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_m4Translate(&transform, position, &transform);
	bs_m4Rotate(&transform, rotation, &transform);

	if (!origin_at_center) {
		bs_vec3 offset;
		bs_v3MulS(&center, -1, &offset);
		bs_m4Translate(&transform, &offset, &transform);
	}

	int mesh_subtype = mesh->extra[subtype_offset];
	BS_WARN("Not implemented");
	//_bsgfx_instantiate(mesh_subtype, &transform, sizeof(bs_mat4), 0, 0, -1, 0);
}



  /*==============================================================================
   * Helpers
   =============================================================================*/

static inline int _bsgfx_instanceLineSubtype(bs_vec3 start, bs_vec3 end, bs_RGBA color, bsgfx_InstanceSubtype* subtype) {
	bsgfx_LineInstance data = {
		.start.xyz = start,
		.end.xyz = end,
		.color = BS_V4((float)color.r / 255.0, (float)color.g / 255.0, (float)color.b / 255.0, (float)color.a / 255.0)
	};

	return bsgfx_instantiate(subtype, &data, sizeof(data), 0, 0, 0, 0);
}

 /**
  Push constants
  */
BSGFXAPI int _bsgfx_instanceMesh(bsgfx_InstanceSubtype* subtype, const bsgfx_MeshInstance* data, bs_U32 flags, int id, int material) {
	return bsgfx_instantiate(subtype, data, sizeof(bsgfx_MeshInstance), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceBoneMesh(bsgfx_InstanceSubtype* subtype, const bsgfx_BoneInstance* data, bs_U32 flags, int id, int material) {
	return bsgfx_instantiate(subtype, data, sizeof(bsgfx_BoneInstance), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceDepthlessLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
	return _bsgfx_instanceLineSubtype(start, end, color, _bsgfx_subtypes_[BSGFX_SUBTYPE_LINE_DEPTHLESS]);
}

BSGFXAPI int _bsgfx_instanceLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
	return _bsgfx_instanceLineSubtype(start, end, color, _bsgfx_subtypes_[BSGFX_SUBTYPE_LINE]);
}

BSGFXAPI int _bsgfx_instanceRay(const bs_Ray* ray, bs_RGBA color) {
	bs_vec3 direction, end;

	bs_v3MulS(&ray->direction, ray->length, &direction);
	bs_v3Add(&ray->origin, &direction, &end);

	return _bsgfx_instanceLineSubtype(ray->origin, end, color, _bsgfx_subtypes_[BSGFX_SUBTYPE_LINE]);
}

BSGFXAPI void _bsgfx_instanceAabb(const bs_Aabb* aabb, bs_RGBA color, bs_Range* out) {
	int first = _bsgfx_instanceLine(aabb->min, BS_V3(aabb->max.x, aabb->min.y, aabb->min.z), color);

	_bsgfx_instanceLine(aabb->min, BS_V3(aabb->min.x, aabb->min.y, aabb->max.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->max.x, aabb->min.y, aabb->max.z), BS_V3(aabb->max.x, aabb->min.y, aabb->min.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->max.x, aabb->min.y, aabb->max.z), BS_V3(aabb->min.x, aabb->min.y, aabb->max.z), color);
	_bsgfx_instanceLine(aabb->max, BS_V3(aabb->min.x, aabb->max.y, aabb->max.z), color);
	_bsgfx_instanceLine(aabb->max, BS_V3(aabb->max.x, aabb->max.y, aabb->min.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->min.x, aabb->max.y, aabb->min.z), BS_V3(aabb->min.x, aabb->max.y, aabb->max.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->min.x, aabb->max.y, aabb->min.z), BS_V3(aabb->max.x, aabb->max.y, aabb->min.z), color);
	_bsgfx_instanceLine(aabb->min, BS_V3(aabb->min.x, aabb->max.y, aabb->min.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->min.x, aabb->min.y, aabb->max.z), BS_V3(aabb->min.x, aabb->max.y, aabb->max.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->max.x, aabb->min.y, aabb->min.z), BS_V3(aabb->max.x, aabb->max.y, aabb->min.z), color);
	_bsgfx_instanceLine(BS_V3(aabb->max.x, aabb->min.y, aabb->max.z), BS_V3(aabb->max.x, aabb->max.y, aabb->max.z), color);

	*out = (bs_Range) { first, 12 };
}

BSGFXAPI int _bsgfx_instanceSphere(bs_vec3 position, float radius) {
	bs_mat4 transform = BS_MAT4_IDENTITY;

	bs_m4Translate(&transform, &position, &transform);
	bs_m4Scale(&transform, &BS_V3(radius, radius, radius), &transform);

	return bsgfx_instantiate(_bsgfx_subtypes_[BSGFX_SUBTYPE_SPHERE_MESH], &transform, sizeof(bs_mat4), 0, 0, 0, 0);
}

BSGFXAPI int _bsgfx_instanceCone(bs_mat4 transform, float radius, bs_U32 flags, int id, int material) {
	return bsgfx_instantiate(_bsgfx_subtypes_[BSGFX_SUBTYPE_CONE_MESH], &transform, sizeof(bs_mat4), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instancePoint(bs_vec3 position, bs_RGBA color, float size) {
	bsgfx_PointInstance data = {
		.coord = position,
		.size = size,
		.color = _bsgfx_convertColor(color),
	};

	return bsgfx_instantiate(_bsgfx_subtypes_[BSGFX_SUBTYPE_POINT], &data, sizeof(data), 0, 0, 0, 0);
}

BSGFXAPI int _bsgfx_instanceQuad(bsgfx_InstanceSubtype* subtype, bs_mat4x3 transform, bs_vec4 coords, bs_U32 flags, int id, int material) {
	struct bsgfx_QuadInstance tmp = {
		.transform = transform,
		.offset = coords.xy,
		.coords = coords.zw,
	};

	return bsgfx_instantiate(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceAtlas(bsgfx_InstanceSubtype* subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bs_vec4 coords = bs_atlasCoordinates(atlas, texture);

	struct bsgfx_QuadInstance tmp = {
		.transform = transform,
		.offset = coords.xy,
		.coords = coords.zw,
	};

	return bsgfx_instantiate(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceAtlasFlipped(bsgfx_InstanceSubtype* subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bs_vec4 coords = bs_atlasCoordinates(atlas, texture);
	coords = bs_mirrorUV(coords);

	struct bsgfx_QuadInstance tmp = {
		.transform = transform,
		.offset = coords.xy,
		.coords = coords.zw,
	};

	return bsgfx_instantiate(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
}

BSGFXAPI void _bsgfx_instanceDepthlessCircle(const bs_mat4* transform, int segments, float radius, bs_RGBA color, bs_Range* out) {
	bs_Range result = { 0 };

	float prev_x = 0.0f, prev_z = 0.0f;
	for (int i = 0; i <= segments; i++) {
		float ratio = (float)i / segments;
		float r = ratio * BS_2PI;
		float x = bs_cos(r) * radius;
		float z = bs_sin(r) * radius;

		if (i > 0) {
			bs_vec3 start, end;
			bs_m4MulV3(transform, &BS_V3(prev_x, 0.0, prev_z), &start);
			bs_m4MulV3(transform, &BS_V3(x, 0.0, z), &end);

			result.offset = _bsgfx_instanceDepthlessLine(start, end, color);
			result.num++;
		}

		prev_x = x;
		prev_z = z;
	}

	result.offset -= result.num;
	*out = result;
}

BSGFXAPI bs_mat4x3 _bsgfx_matrix(bs_vec3 position, bs_vec3 scale) {
	return (bs_mat4x3) {
		scale.x, 0.0, 0.0,
		0.0, scale.y, 0.0,
		0.0, 0.0, scale.z,
		position.x, position.y, position.z,
	};
}
