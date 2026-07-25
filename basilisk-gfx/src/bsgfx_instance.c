
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

#include <assert.h>
#include <bs_internal.h>

static bs_List _bsgfx_subtype_data[BSGFX_MAX_NUM_SUBTYPES];

BSGFXAPI bs_List* _bsgfx_subtypeInstances(int subtype) {
	return &_bsgfx_subtype_data[subtype];
}

BSGFXAPI bs_Result _bsgfx_iniInstances() {
	bs_Result result;

	 /** Already initialized */
	if (bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)) {
		bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;

		if (buffer->bind_set != BSGFX_SET_MESH_DATA || buffer->binding != BSGFX_BINDING_MESH_DATA)
			bs_bindBuffer(BSGFX_SET_MESH_DATA, BSGFX_BINDING_MESH_DATA, buffer);

		return BS_RESULT_OK;
	}

	bs_Object* object = BS_BUFFER(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA, false);
	result = bs_buffer(object, sizeof(bsgfx_InstanceMetadata),
		BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT, 
		BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		0);

	if (result != BS_RESULT_OK)
		return result;

	result = bs_bindBuffer(BSGFX_SET_MESH_DATA, BSGFX_BINDING_MESH_DATA, object->buffer);
//	if (result != BS_RESULT_OK)
//		return result;

	result = bs_mapBuffer(object->buffer, BS_U32_MAX);

	return result;
}



  /*==============================================================================
   * Instance Types
   =============================================================================*/

BSGFXAPI bool _bsgfx_validateInstanceType(const char* library_name, int instance_type) { // TODO: use library_name
	BSGFX_VALIDATE(instance_type >= 0, false,);
	BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA), false,);
	BSGFX_VALIDATE(instance_type < BSGFX_INSTANCE_TYPE_COUNT, false,);
	BSGFX_VALIDATE(_poser_->instance_buffers[instance_type] != NULL, false,);

	return true;
}

 /**
  Create instance type
  */
BSGFXAPI void _val_bsgfx_instanceType(int instance_type_id, int max_instance_count, int bind_set, int point) {
	BSGFX_VALIDATE(_poser_->instance_buffers[instance_type_id] != NULL,,);
	BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA),,);

	bs_BindSet* bind_set_query = bs_queryBindSet(bind_set);
	BSGFX_VALIDATE(bind_set_query != NULL,,);
	BSGFX_VALIDATE(bs_queryBinding(bind_set_query, point) != NULL,,);

	_bsgfx_instanceType(instance_type_id, max_instance_count, bind_set, point);
}

BSGFXAPI void _bsgfx_instanceType(int instance_type_id, int max_instance_count, int bind_set, int point) {
	bs_Result result;

	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	
	bs_Binding* binding = bs_queryBinding(bs_queryBindSet(bind_set), point);
	if (!binding)
		return;

	bs_BufferUsageFlags usage_flags = 0;
	bs_MemoryPropertyFlags memory_flags = BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	if (binding->type == BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
		usage_flags |= BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	else if (binding->type == BS_DESCRIPTOR_TYPE_STORAGE_BUFFER)
		usage_flags |= BS_BUFFER_USAGE_STORAGE_BUFFER_BIT | BS_BUFFER_USAGE_TRANSFER_DST_BIT | BS_BUFFER_USAGE_TRANSFER_SRC_BIT;
	else {
		bs_warnF("Invalid bind type %d\n", binding->type); // TODO: _bsgfx_warn
		return;
	}

	// TODO: remove
	VkDeviceSize atom_size = 64;

	bs_U32 size = max_instance_count * sizeof(bsgfx_InstanceBuffer);
	VkDeviceSize aligned_size =
		(size + 64 - 1) & ~(atom_size - 1);

	bs_Object* object = BS_BUFFER(-1, 0, 0);
	result = bs_buffer(object, aligned_size, usage_flags, memory_flags, 0);
	if (result != BS_RESULT_OK)
		return;

	_poser_->instance_buffers[instance_type_id] = object->buffer;

	result = bs_bindBuffer(bind_set, point, _poser_->instance_buffers[instance_type_id]);
	if (result != BS_RESULT_OK)
		return;

	result = bs_mapBuffer(_poser_->instance_buffers[instance_type_id], BS_U32_MAX);
	if (result != BS_RESULT_OK)
		return;

	int num_swaps = (buffer->flags & BSI_BUFFER_SWAPS_BIT) ? bs_context()->frames_in_flight : 1;
	for (int i = 0; i < num_swaps; i++) {
		bsgfx_InstanceMetadata* metadata = buffer->_[i].data;
		metadata->instance_types[instance_type_id].allocated = max_instance_count;
	}
}



  /*==============================================================================
   * Subtypes
   =============================================================================*/

BSGFXAPI bool _bsgfx_validateSubtype(const char* library_name, int subtype) { // TODO: use library_name
	BSGFX_VALIDATE(subtype >= 0, false, );
	BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA), false, );

	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	BSGFX_VALIDATE(bs_bufferIsMapped(buffer), false, );

	int index = buffer->flags & BSI_BUFFER_SWAPS_BIT ? bs_context()->frame : 0;
	bsgfx_InstanceMetadata* metadata = buffer->_[index].data;

	BSGFX_VALIDATE(subtype < metadata->subtypes_count, false, );

	return true;
}

 /**
  Delete subtype
  */
BSGFXAPI void _val_bsgfx_deleteSubtype(int subtype) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return;

	_bsgfx_deleteSubtype(subtype);
}

BSGFXAPI void _bsgfx_deleteSubtype(int subtype) {
	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	int num_swaps = (buffer->flags & BSI_BUFFER_SWAPS_BIT) ? bs_context()->frames_in_flight : 1;

	for (int i = 0; i < num_swaps; i++) {
		bsgfx_InstanceMetadata* metadata = buffer->_[i].data;
		struct bsgfx_InstanceTypeMetadata* type_metadata = metadata->instance_types + metadata->instance_subtypes[subtype].instance_type;

		for (int j = subtype; j < metadata->subtypes_count; j++)
			metadata->instance_subtypes[j] = metadata->instance_subtypes[j + 1];

		metadata->subtypes_count--;
	}
}

 /**
  Subtype range
  */
BSGFXAPI bs_Range _val_bsgfx_subtypeRange(int subtype) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return (bs_Range) { 0 };

	return _bsgfx_subtypeRange(subtype);
}

BSGFXAPI bs_Range _bsgfx_subtypeRange(int subtype) {
	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	int index = buffer->flags & BSI_BUFFER_SWAPS_BIT ? bs_context()->frame : 0;
	bsgfx_InstanceMetadata* metadata = buffer->_[index].data;

	bsgfx_InstanceSubtypeMetadata* subtype_metadata = metadata->instance_subtypes + subtype;

	return (bs_Range) { 
		.offset = subtype_metadata->index_offset, 
		.num = subtype_metadata->index_count, 
	//	.batch = bs_fetch(subtype_metadata->batch_source_id, subtype_metadata->batch_id)->batch
	};
}

 /**
  Instance count
  */
BSGFXAPI int _val_bsgfx_instanceCount(int subtype) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return 0;

	return _bsgfx_instanceCount(subtype);
}

BSGFXAPI int _bsgfx_instanceCount(int subtype) {
	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	int index = buffer->flags & BSI_BUFFER_SWAPS_BIT ? bs_context()->frame : 0;

	bsgfx_InstanceMetadata* metadata = buffer->_[index].data;
	return metadata->instance_subtypes[subtype].instance_count;
}

 /**
  Subtype count
  */
BSGFXAPI int _val_bsgfx_subtypeCount(int instance_type_id) {
	if (!_bsgfx_validateInstanceType("GFX", instance_type_id))
		return 0;

	return _bsgfx_subtypeCount(instance_type_id);
}

BSGFXAPI int _bsgfx_subtypeCount(int instance_type_id) {
	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	int index = buffer->flags & BSI_BUFFER_SWAPS_BIT ? bs_context()->frame : 0;

	bsgfx_InstanceMetadata* metadata = buffer->_[index].data;
	return metadata->instance_types[instance_type_id].subtype_count;
}

BSGFXAPI const int* _bsgfx_subtypes() {
	return _bsgfx_subtypes_;
}

 /**
  Create subtype
  */
BSGFXAPI int _val_bsgfx_subtype(int instance_type_id, bs_Batch* batch, bs_U32 flags, bs_Range range) {
	if (!_bsgfx_validateInstanceType("GFX", instance_type_id))
		return 0;

	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	int num_swaps = (buffer->flags & BSI_BUFFER_SWAPS_BIT) ? bs_context()->frames_in_flight : 1;
	for (int i = 0; i < num_swaps; i++) {
		bsgfx_InstanceMetadata* metadata = buffer->_[i].data;
		BSGFX_VALIDATE(metadata->subtypes_count < BSGFX_MAX_NUM_SUBTYPES, 0,);
	}

	return _bsgfx_subtype(instance_type_id, batch, flags, range);
}

BSGFXAPI int _bsgfx_subtype(int instance_type_id, bs_Batch* batch, bs_U32 flags, bs_Range range) {
	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	int num_swaps = (buffer->flags & BSI_BUFFER_SWAPS_BIT) ? bs_context()->frames_in_flight : 1;

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

	int subtype = -1;
	for (int i = 0; i < num_swaps; i++) {
		bsgfx_InstanceMetadata* metadata = buffer->_[i].data;

		//subtype = existing == -1 ? metadata->subtypes_count : existing;
		subtype = metadata->subtypes_count;
		metadata->instance_subtypes[subtype].instance_type = instance_type_id;
		metadata->instance_subtypes[subtype].index_offset = range.offset;
		metadata->instance_subtypes[subtype].index_count = range.num;
		metadata->instance_subtypes[subtype].batch_source_id = batch->head.source_id;
		metadata->instance_subtypes[subtype].batch_id = batch->head.id;
		metadata->instance_subtypes[subtype].flags = flags;

		//if (existing == -1) {
		if (i == 0)
			_bsgfx_subtype_data[metadata->subtypes_count] = bs_list(sizeof(bsgfx_InstanceBuffer), 32);
		metadata->subtypes_count++;
		metadata->instance_types[instance_type_id].subtype_count++;
		//}
	}

	return subtype;
}

 /**
  Subtype has flag
  */
BSGFXAPI bool _val_bsgfx_subtypeHasFlag(int subtype, bs_U32 flag) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return false;

	return _bsgfx_subtypeHasFlag(subtype, flag);
}

BSGFXAPI bool _bsgfx_subtypeHasFlag(int subtype, bs_U32 flag) {
	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);
	return metadata->instance_subtypes[subtype].flags & flag;
}

 /**
  Render subtype
  */
BSGFXAPI void _val_bsgfx_renderSubtype(int subtype, bs_Pipeline* pipeline) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return;

	_bsgfx_renderSubtype(subtype, pipeline);
}

BSGFXAPI void _bsgfx_renderSubtype(int subtype, bs_Pipeline* pipeline) {
	if (subtype < 0)
		return;

	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

	if (!bs_exists(metadata->instance_subtypes[subtype].batch_source_id, metadata->instance_subtypes[subtype].batch_id))
		return;

	bs_render(
		bs_fetch(metadata->instance_subtypes[subtype].batch_source_id, metadata->instance_subtypes[subtype].batch_id)->batch, pipeline,
		metadata->instance_subtypes[subtype].index_offset, 
		metadata->instance_subtypes[subtype].index_count,
		metadata->instance_subtypes[subtype].instance_offset,
		metadata->instance_subtypes[subtype].instance_count);
}

 /**
  Reset subtype
  */
BSGFXAPI void _val_bsgfx_resetSubtype(int subtype) {
	if (!_bsgfx_validateSubtype("GFX", subtype))
		return;
	
	_bsgfx_resetSubtype(subtype);
}

BSGFXAPI void _bsgfx_resetSubtype(int subtype) {
	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

	struct bsgfx_InstanceSubtypeMetadata* subtype_metadata = metadata->instance_subtypes + subtype;
	struct bsgfx_InstanceTypeMetadata* type_metadata = metadata->instance_types + subtype_metadata->instance_type;

	bsgfx_InstanceBuffer* instance = bs_bufferMap(_poser_->instance_buffers[subtype_metadata->instance_type]);
	int count = type_metadata->count;

	for (int i = 0; i < count; i++) {
		if (instance[i].header.subtype == subtype) {
			for (int j = i; j < count - 1; j++)
				instance[j] = instance[j + 1];

			type_metadata->count--;
		}
	}

	subtype_metadata->instance_count = 0;

	assert(type_metadata->count >= 0);
}



  /*==============================================================================
   * Instancing
   =============================================================================*/

 /**
  Create instance
  */
BSGFXAPI int _val_bsgfx_instance(int subtype, const char* data, int data_size, bs_U32 flags, unsigned int bone_index, int id, int material) {
	BSGFX_VALIDATE(subtype >= 0, 0,);
	BSGFX_VALIDATE(flags <= 65536, 0,);
	BSGFX_VALIDATE(material <= 65536, 0,);
	BSGFX_VALIDATE(_poser_->instances_ticked == false, 0,);
	BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA), 0, );

	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

	int instance_type = metadata->instance_subtypes[subtype].instance_type;
	BSGFX_VALIDATE(_poser_->instance_buffers[instance_type] != NULL, 0, "Instance type %d has not been created or has no subtypes", instance_type);
	BSGFX_VALIDATE(bs_bufferIsMapped(_poser_->instance_buffers[instance_type]), 0, "Instance type %d", instance_type);
	BSGFX_VALIDATE(metadata->instance_types[instance_type].count >= metadata->instance_types[instance_type].allocated, 0, "Instance buffer of type %d is maxed out\n", instance_type);

	return _bsgfx_instance(subtype, data, data_size, flags, bone_index, id, material);
}

BSGFXAPI int _bsgfx_instance(int subtype, const char* data, int data_size, bs_U32 flags, unsigned int bone_index, int id, int material) {
	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;

	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

	int instance_type = metadata->instance_subtypes[subtype].instance_type;
	bsgfx_InstanceBuffer* instance_buffer = bs_bufferMap(_poser_->instance_buffers[instance_type]);

	flags |= (1 << instance_type);
	int out_index = bsgfx_index(flags, metadata->instance_types[instance_type].count);
	metadata->instance_subtypes[subtype].instance_count++;
	metadata->instance_types[instance_type].count++;

	bsgfx_InstanceBuffer instance;
	memcpy(instance.data, data, data_size);
	instance.header.id = id;
	instance.header.flags = flags;
	instance.header.material = material;
	instance.header.subtype = subtype;
	instance.header.bone_index = bone_index;

	bs_pushBack(&_bsgfx_subtype_data[subtype], &instance);

	return metadata->instance_subtypes[subtype].instance_count - 1;
}

 /**
  Tick instances
  */
BSGFXAPI void _val_bsgfx_tickInstances() {
	BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA),,);

	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;

	BSGFX_VALIDATE(bs_bufferIsMapped(metadata_buffer),,);

	_bsgfx_tickInstances();
}

BSGFXAPI void _bsgfx_tickInstances() {
	if (!bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA))
		return;

	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	if (!_bs_bufferIsMapped(metadata_buffer))
		return;

	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

	for (int i = 0; i < BSGFX_INSTANCE_TYPE_COUNT; i++) {
		struct bsgfx_InstanceTypeMetadata* type_metadata = metadata->instance_types + i;
		if (type_metadata->count == 0) 
			continue;

		bsgfx_InstanceBuffer* first_instance = bs_bufferMap(_poser_->instance_buffers[i]);

		for (int j = 0, offset = 0; j < metadata->subtypes_count; j++) {
			struct bsgfx_InstanceSubtypeMetadata* subtype_metadata = metadata->instance_subtypes + j;

			if (subtype_metadata->instance_type != i)
				continue;

			bsgfx_InstanceBuffer* instance = first_instance + offset;

			memcpy(instance, _bsgfx_subtype_data[j].data, _bsgfx_subtype_data[j].count * sizeof(bsgfx_InstanceBuffer));
			_bsgfx_subtype_data[j].count = 0;
			metadata->instance_subtypes[j].instance_offset = offset;
			offset += metadata->instance_subtypes[j].instance_count;
		}

		bs_bindBuffer(_poser_->instance_buffers[i]->bind_set, _poser_->instance_buffers[i]->binding, _poser_->instance_buffers[i]);
	}

	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	bs_bindBuffer(BSGFX_SET_MESH_DATA, BSGFX_BINDING_MESH_DATA, buffer);
}

 /**
  Reset instances
  */
BSGFXAPI void _val_bsgfx_resetInstances() {
	BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA),,);

	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	BSGFX_VALIDATE(bs_bufferIsMapped(metadata_buffer),,);

	_bsgfx_resetInstances();
}

BSGFXAPI void _bsgfx_resetInstances() {
	bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
	if (!metadata_buffer) return;
	bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

	for (int i = 0; i < metadata->subtypes_count; i++) {
		// metadata->instance_types[metadata->instance_subtypes[i].instance_type].count -= metadata->instance_subtypes[i].instance_count;
		metadata->instance_subtypes[i].instance_count = 0;
	}
	for (int i = 0; i < BSGFX_INSTANCE_TYPE_COUNT; i++)
		metadata->instance_types[i].count = 0;

	//for (int i = 0; i < BSGFX_INSTANCE_TYPE_COUNT; i++) {
	//	assert(metadata->instance_types[i].count >= 0);
	//}

	_poser_->instances_ticked = false;
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
	_bsgfx_instance(mesh_subtype, &transform, sizeof(bs_mat4), 0, 0, -1, 0);
}



  /*==============================================================================
   * Helpers
   =============================================================================*/

static inline int _bsgfx_instanceLineSubtype(bs_vec3 start, bs_vec3 end, bs_RGBA color, int subtype) {
	struct {
		bs_vec4 start, end, color;
	} data = {
		.start.xyz = start,
		.end.xyz = end,
		.color = BS_V4((float)color.r / 255.0, (float)color.g / 255.0, (float)color.b / 255.0, (float)color.a / 255.0)
	};

	return bsgfx_instance(subtype, &data, sizeof(data), 0, 0, 0, 0);
}

 /**
  Push constants
  */
BSGFXAPI int _bsgfx_instanceMesh(int subtype, const bsgfx_MeshInstance* data, bs_U32 flags, int id, int material) {
	return bsgfx_instance(subtype, data, sizeof(bsgfx_MeshInstance), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceBoneMesh(int subtype, const bsgfx_BoneInstance* data, bs_U32 flags, int id, int material) {
	return bsgfx_instance(subtype, data, sizeof(bsgfx_BoneInstance), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceDepthlessLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
	return _bsgfx_instanceLineSubtype(start, end, color, _bsgfx_subtypes()[BSGFX_SUBTYPE_LINE_DEPTHLESS]);
}

BSGFXAPI int _bsgfx_instanceLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
	return _bsgfx_instanceLineSubtype(start, end, color, _bsgfx_subtypes()[BSGFX_SUBTYPE_LINE]);
}

BSGFXAPI int _bsgfx_instanceRay(const bs_Ray* ray, bs_RGBA color) {
	bs_vec3 direction, end;

	bs_v3MulS(&ray->direction, ray->length, &direction);
	bs_v3Add(&ray->origin, &direction, &end);

	return _bsgfx_instanceLineSubtype(ray->origin, end, color, _bsgfx_subtypes()[BSGFX_SUBTYPE_LINE]);
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

	return bsgfx_instance(_bsgfx_subtypes()[BSGFX_SUBTYPE_SPHERE_MESH], &transform, sizeof(bs_mat4), 0, 0, 0, 0);
}

BSGFXAPI int _bsgfx_instanceCone(bs_mat4 transform, float radius, bs_U32 flags, int id, int material) {
	return bsgfx_instance(_bsgfx_subtypes()[BSGFX_SUBTYPE_CONE_MESH], &transform, sizeof(bs_mat4), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instancePoint(bs_vec3 position, bs_RGBA color, float size) {
	struct {
		bs_vec3 coord;
		float size;
		bs_vec4 color;
	} data = {
		.coord = position,
		.size = size,
		.color = _bsgfx_convertColor(color),
	};

	return bsgfx_instance(_bsgfx_subtypes()[BSGFX_SUBTYPE_POINT], &data, sizeof(data), 0, 0, 0, 0);
}

BSGFXAPI int _bsgfx_instanceQuad(int subtype, bs_mat4x3 transform, bs_vec4 coords, bs_U32 flags, int id, int material) {
	struct bsgfx_QuadInstance tmp = {
		.transform = transform,
		.offset = coords.xy,
		.coords = coords.zw,
	};

	return bsgfx_instance(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceAtlas(int subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bs_vec4 coords = bs_atlasCoordinates(atlas, texture);

	struct bsgfx_QuadInstance tmp = {
		.transform = transform,
		.offset = coords.xy,
		.coords = coords.zw,
	};

	return bsgfx_instance(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
}

BSGFXAPI int _bsgfx_instanceAtlasFlipped(int subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
	bs_Atlas* atlas = bs_fetch(BSGFX_ATLASES, BSGFX_ATLAS_ANY)->atlas;
	bs_vec4 coords = bs_atlasCoordinates(atlas, texture);
	coords = bs_mirrorUV(coords);

	struct bsgfx_QuadInstance tmp = {
		.transform = transform,
		.offset = coords.xy,
		.coords = coords.zw,
	};

	return bsgfx_instance(subtype, &tmp, sizeof(tmp), flags, 0, id, material);
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

BSGFXAPI void _bsgfx_instanceText(int subtype, bs_Font* font, bsgfx_Text* params, bs_vec2* out_text_size, char* text, int text_length) {
	if (!text)
		text = "(null)";

	bs_RGBA color = BS_WHITE;

	bs_vec2 offset = { 0 };

	bs_vec3 scale;
	bs_v2MulS(&BS_V2(font->spacing, font->atlas->mapped[0].h), params->scale, &scale.xy);
	scale.z = 0.0;

	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_m4Translate(&transform, &params->position.xyz, &transform);
	bs_m4Rotate(&transform, &BS_QUAT_IDENTITY, &transform);
	bs_m4Scale(&transform, &BS_QUAT_IDENTITY, &transform);

	bs_U32 flags;
	float layout_scale = (params->scale / (float)font->units_per_em);

	for (int i = 0; i < text_length; i++) {
		char c = text[i];
		int index = font->table[c];
		if (index >= font->atlas->count)
			index = 0;

		flags = params->flags;
		if ((params->select_end || params->select_start) && (
			(i >= params->select_start && i < params->select_end) ||
			(i > params->select_end && i <= params->select_start))) {
			flags |= BSGFX_ID_FONT_IS_SELECTED;
		}

		float spacing = font->glyphs[index].advance_width * layout_scale;
		if (c == ' ') {
			float new_offset = offset.x + spacing * layout_scale;
			if (params->max_length > 0.0 && new_offset > params->max_length)
				break;

			transform.v[3].x = params->position.x + offset.x;
			transform.v[3].y = params->position.y + offset.y;
			transform.v[0].x = spacing * layout_scale;
			transform.v[1].y = font->height * layout_scale;
			//bsgfx_instanceQuad(subtype, bs_m4x3(transform), bs_v4(0, 0, 0, 0), flags, 0, 0);

			offset.x = new_offset;
			continue;
		}
		else if (c == '\n') {
			offset.x = 0.0;
			offset.y -= font->height * layout_scale;
			continue;
		}

		bs_vec4 coords = bs_atlasCoordinates(font->atlas, index);
		bs_vec2 size = bs_atlasSize(font->atlas, index);

		float new_offset = offset.x + size.x * layout_scale;
		if (params->max_length > 0.0 && new_offset > params->max_length)
			break;

		transform.v[3].x = params->position.x + offset.x;
		transform.v[3].y = params->position.y + offset.y + ((float)font->glyphs[index].y_offset) * layout_scale;
		transform.v[0].x = (size.x + font->glyphs[index].left_side_bearing) * layout_scale;
		transform.v[1].y = size.y * layout_scale;

		_bsgfx_instanceQuad(subtype, bs_m4x3(&transform), coords, flags, 0, params->material_id);
		offset.x += spacing;

		if (i <= (text_length - 1)) {
			char next = text[i + 1];
			int next_index = font->table[next];

			for (int j = font->glyphs[index].kerning_pair_offset; j < (font->glyphs[index].kerning_pair_offset + font->glyphs[index].kerning_pair_count); j++) {
				if (next_index == font->pairs[j].right) {
					offset.x += font->pairs[j].value;
					break;
				}
			}
		}

	}

	*out_text_size = offset;
}

BSGFXAPI bs_mat4x3 _bsgfx_matrix(bs_vec3 position, bs_vec3 scale) {
	return (bs_mat4x3) {
		scale.x, 0.0, 0.0,
		0.0, scale.y, 0.0,
		0.0, 0.0, scale.z,
		position.x, position.y, position.z,
	};
}
