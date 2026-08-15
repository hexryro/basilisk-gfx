
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

#include <bsmod_internal.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

static bs_List _bsmod_packages_ = { .unit_size = sizeof(bsmod_Package), .increment = 4 };

BSMODAPI bs_List* _bsmod_packages() {
	return &_bsmod_packages_;
}

BSMODAPI bsmod_Package* _bsmod_queryPackage(const char* name) {
	bs_U64 hash = bs_stringHash(name);

	for (int i = 0; i < _bsmod_packages_.count; i++) {
		bsmod_Package* package = bs_fetchUnit(&_bsmod_packages_, i);

		if (hash == package->path_hash)
			return package;
	}

	return NULL;
}

BSMODAPI bsmod_Package* _bsmod_ensurePackage(char* path) {
	bsmod_Package* existing = _bsmod_queryPackage(path);
	if (existing)
		return existing;

	bs_infoF("Created package %s\n", path);

	char* name;
	char* file_name = bs_fileName(path);
	char* ext = strrchr(file_name, '.');

	if (ext) {
		ext[0] = '\0';
		name = strdup(file_name);
		ext[0] = '\.';
	}
	else
		name = strdup(file_name);

	file_name[-1] = '\0';
	char* directory = strdup(path);
	file_name[-1] = '/';

	return bs_pushBack(&_bsmod_packages_, &(bsmod_Package) {
		.name = name,
		.name_hash = bs_stringHash(name),
		.directory = directory,
		.directory_hash = bs_stringHash(directory),
		.path_hash = bs_stringHash(path),
		.path = path,
		.chunks = bs_list(sizeof(bsmod_Chunk), 16),
		.resources = bs_list(sizeof(bsmod_Resource), 32),
	});
}

BSMODAPI bsmod_Resource* _bsmod_queryResource(bsmod_Package* package, bs_ResourceType type, const char* name) {
	bs_U64 hash = bs_stringHash(name);

	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);

		if (resource->name_hash == hash && resource->type == type)
			return resource;
	}

	return NULL;
}

static bsmod_Resource* _bsmod_ensureResource(bsmod_Package* package, bs_ResourceType type, char* name) {
	bsmod_Resource* existing = _bsmod_queryResource(package, type, name);
	if (existing)
		return existing;

	return bs_pushBack(&package->resources, &(bsmod_Resource) {
		.name_hash = bs_stringHash(name),
		.name_length = strlen(name),
		.name = strdup(name),
	});
}

BSMODAPI bs_Result _val_bsmod_iniPackage(int package_id) {
	BSMOD_VALIDATE(package_id >= 0, BS_RESULT_VALIDATION_ERROR, );
	BSMOD_VALIDATE(bs_fetchUnit(bs_packages(), package_id) != NULL, BS_RESULT_VALIDATION_ERROR,);

	return _bsmod_iniPackage(package_id);
}

BSMODAPI bs_Result _bsmod_iniPackage(int package_id) {
	bs_List* packages = bs_packages();
	bs_Package* package = bs_fetchUnit(packages, package_id);

	bs_Result result;

	int previous_count = _bsmod_packages_.count;
	bsmod_Package* package_metadata = _bsmod_ensurePackage(package->path);
//	if (previous_count == _bsmod_packages_.count) {
//		bs_warnF("Package \"%s\" is already initialized\n", package->path);
//		return BS_RESULT_OK; // TODO
//	}

	if (package_metadata->is_initialized)
		return BS_RESULT_OK;

	package_metadata->is_initialized = true;

	bs_String* bpak;
	result = bs_loadFile(&bpak, package->path);
	if (result != BS_RESULT_OK)
		return result;

	for (int i = 0; i < package->resource_headers_count; i++) {
		bs_ResourceHeader* header = package->resource_headers + i;

		bsmod_Resource* added = bs_pushBack(&package_metadata->resources, &(bsmod_Resource) {
			.chunk = header->chunk,
			.name = header->name,
			.name_hash = header->name_hash,
			.name_length = header->name_length,
			.offset = header->offset,
			.size = header->size,
			.type = header->type,
		});
	}

	for (int i = 0; i < package->chunks_count; i++) {
		bs_String* chunk_bin; 
		char* ext = strrchr(package->path, '.');
		if (bs_loadFileF(&chunk_bin, "%s/%s_%03d.bpak", package_metadata->directory, package_metadata->name, (i + 1)) != BS_RESULT_OK) {
			continue;
		}

		bsmod_Chunk* chunk = bs_pushBack(&package_metadata->chunks, &(bsmod_Chunk) {
			.bin = bs_list(sizeof(unsigned char), 10000),
			.id = i,
		});

		bs_ensureSize(&chunk->bin, chunk_bin->len);
		memcpy(chunk->bin.data, chunk_bin->value, chunk_bin->len);
		chunk->bin.count = chunk_bin->len;

		bs_free(chunk_bin);
	}

	bs_free(bpak);

	return BS_RESULT_OK;
}

static bsmod_Chunk* _bsmod_ensureChunk(bsmod_Package* package, int size) {
	bsmod_Chunk* chunk;
	for (int i = 0; i < package->chunks.count; i++) {
		chunk = bs_fetchUnit(&package->chunks, i);
		if (chunk->bin.count == 0 || (chunk->bin.count + size) < BSMOD_BPAK_CHUNK_SIZE) {
			bs_ensureSize(&chunk->bin, size);
			return chunk;
		}
	}

	bs_infoF("Created chunk\n");
	chunk = bs_pushBack(&package->chunks, &(bsmod_Chunk) {
		.bin = bs_list(sizeof(unsigned char), 10000),
		.id = package->chunks.count,
	});
	bs_ensureSize(&chunk->bin, size);
	return chunk;
}

BSMODAPI bs_Result _bsmod_packResourceN(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* resource_name, int resource_name_length) {
	bsmod_Package* package = _bsmod_ensurePackage(package_name);

	/** Ensure package is loaded to not overwrite data */
	if (!package->is_initialized) {
		int existing_package_id = bs_queryPackage(package->path);
		if (existing_package_id < 0)
			bs_loadPackage(&existing_package_id, package->path);

		if (existing_package_id >= 0)
			_bsmod_iniPackage(existing_package_id);

		package->is_initialized = true;
	}

	bsmod_Resource* resource = _bsmod_ensureResource(package, type, resource_name);
	resource->type = type;

	bsmod_Chunk* chunk = bs_fetchUnit(&package->chunks, resource->chunk);
	
	if (resource->size != data_size) {
		if (resource->size > 0) {
			bs_infoF("Deleting old resource %s " BS_PRINT_COLOR("(-%d bytes)", BS_PRINT_RED) "\n", resource_name, resource->size);
			
			size_t remaining = chunk->bin.count - resource->offset;
			BSMOD_VALIDATE(remaining >= resource->size, BS_RESULT_VALIDATION_ERROR,);

			memmove(
				chunk->bin.data + resource->offset,
				chunk->bin.data + resource->offset + resource->size,
				chunk->bin.count - (resource->offset + resource->size));
			chunk->bin.count -= resource->size;
			chunk->has_changes = true;

			for (int i = 0; i < package->resources.count; i++) {
				bsmod_Resource* r = bs_fetchUnit(&package->resources, i);
				if (r != resource && r->chunk == resource->chunk && r->offset > resource->offset) {
					bs_infoF("  Adjusted offset for resource \"%s\"\n", r->name);
					r->offset -= resource->size;
					BSMOD_VALIDATE(r->offset >= 0, BS_RESULT_VALIDATION_ERROR,);
				}
			}
		}

		chunk = _bsmod_ensureChunk(package, data_size);
		resource->chunk = chunk->id;
		resource->offset = chunk->bin.count;
		resource->size = data_size;
		resource->type = type;
		chunk->bin.count += data_size;
		bs_infoF("Created resource %s " BS_PRINT_COLOR("(+%d bytes)", BS_PRINT_GREEN) "\n", resource_name, data_size);
	} 
	else
		bs_infoF("Packed resource %s " BS_PRINT_COLOR("(+-0 bytes)", BS_PRINT_GRAY) "\n", resource_name);

	memcpy(chunk->bin.data + resource->offset * chunk->bin.unit_size, data, data_size);

	chunk->has_changes = true;
	package->has_changes = true;
	resource->has_changes = true;

	return BS_RESULT_OK;
}

bs_Result _bsmod_loadResource(int type, int package_id, char* name) {
	bs_Result result = BS_RESULT_OK;

	bs_Resource* resource; 
	result = bs_queryResource(package_id, type, name, &resource);
	if (result != BS_RESULT_OK)
		return result;

	bs_Object* single_times_queue_object = bs_fetch(BSMOD_QUEUES, BSGFX_QUEUE_SINGLE_TIMES);
	if (!single_times_queue_object)
		return result;

	bs_Queue* single_times_queue = single_times_queue_object->queue;
	bs_List* sources = bs_objectSources();

	switch (type) {
	case BSGFX_RESOURCE_PREFAB:
		bsgfx_loadPrefabs(bsgfx_getType(BSGFX_TYPE_PREFAB)->package_id, bsgfx_prefabModel());
		break;
	case BSGFX_RESOURCE_PRIMITIVE:
		bsgfx_loadPrimitives(bsgfx_getType(BSGFX_TYPE_PRIMITIVE)->package_id);
	case BSGFX_RESOURCE_TILE:
		bsgfx_loadTiles(bsgfx_getType(BSGFX_TYPE_TILE)->package_id, true);
		break;
	case BSGFX_RESOURCE_LIGHT:
	//	bsgfx_loadLights(bsgfx_getType(BSGFX_TYPE_LIGHT)->package_id);
		break;
	case BS_RESOURCE_IMAGE:

		bs_Image* existing_image = NULL;
		if (resource && resource->image) {
			for (int i = 0; i < sources->count; i++ ){
				bs_ObjectSource* source = bs_fetchUnit(sources, i);
				if (source->type == BS_OBJECT_IMAGE) {
					for (int j = 0; j < source->ids_count; j++) {
						bs_Object* image = source->ids[j].object;
						if (resource->image == image->image) {
							existing_image = image->image;
							goto image_end;
						}
					}
				}
			}
		image_end:
			void;
		}

		if (existing_image) {
			bs_Object* image_object = BS_IMAGE(existing_image->head.source_id, existing_image->head.id, BS_OBJECT_FORCE_DESTROY);
			result = bs_loadImage(single_times_queue, image_object, package_id, existing_image->flags, name);
			if (result != BS_RESULT_OK)
				return result;

			for (int i = 0; i < bs_instance()->bind_sets_count; i++) {
				bs_BindSet* bind_set = bs_instance()->bind_sets + i;
				for (int j = 0; j < bind_set->bindings_count; j++) {
					bs_Binding* binding = bind_set->bindings + j;
					bs_Descriptor* descriptor = ((unsigned char*)bind_set->descriptors) + binding->location;

					bs_ImageDescriptor* new_descriptors = NULL;
					int new_descriptors_count = 0;
					for (int k = 0; k < binding->descriptors_count; k++, descriptor++) {
						if (descriptor->object_type != BS_OBJECT_IMAGE)
							continue;

						if (descriptor->as_image.image == existing_image)
							new_descriptors = _alloca(binding->descriptors_count * sizeof(bs_ImageDescriptor));
					}

					if (new_descriptors) {
						descriptor = ((unsigned char*)bind_set->descriptors) + binding->location;
						for (int k = 0; k < binding->descriptors_count; k++, descriptor++) {
							assert(descriptor->object_type == BS_OBJECT_IMAGE);

							new_descriptors[k] = (bs_ImageDescriptor){
								.image = descriptor->as_image.image,
								.layout = (bs_ImageLayout)descriptor->as_image.vk_image_layout,
								.sampler = descriptor->as_image.sampler,
							};

							if (descriptor->as_image.image == existing_image)
								new_descriptors[k].image = image_object->image;
						}

						bs_bindImages(binding->set, binding->slot, new_descriptors, binding->descriptors_count);
					}
				}
			}
		}
		else {
			bs_warnF("Could not reload resource \"%s\", object id could not be found\n", name);
		}


		break;
	case BS_RESOURCE_ATLAS:

		bs_Atlas* existing_atlas = NULL;
		if (resource && resource->atlas) {
			for (int i = 0; i < sources->count; i++ ){
				bs_ObjectSource* source = bs_fetchUnit(sources, i);
				if (source->type == BS_OBJECT_ATLAS) {
					for (int j = 0; j < source->ids_count; j++) {
						bs_Object* o = source->ids[j].object;
						if (o && resource->atlas == o->atlas) {
							existing_atlas = o->atlas;
							goto atlas_end;
						}
					}
				}
			}
		atlas_end:
			void;
		}

		if (existing_atlas) {
			bs_Atlas* atlas_object = BS_ATLAS(existing_atlas->head.source_id, existing_atlas->head.id, BS_OBJECT_FORCE_DESTROY);
			if (bs_loadAtlas(single_times_queue, atlas_object, package_id, 0, name) == BS_RESULT_OK) {
				_bsmod_bindAtlases();
				bs_pushDescriptors();
			}
		}
		else {
			bs_warnF("Could not reload resource \"%s\", object id could not be found\n", name);
		}
		
		break;
	case BS_RESOURCE_SHADER:
		bs_Resource* existing_shader;
		result = bs_queryResource(package_id, BS_RESOURCE_SHADER, name, &existing_shader);
		if (result == BS_RESULT_OK)
			bs_shader(package_id, name, 0, &existing_shader);

		break;
	case BS_RESOURCE_MODEL:
		bs_Resource* existing_model;
		result = bs_queryResource(package_id, BS_RESOURCE_MODEL, name, &existing_model);
		if (result == BS_RESULT_OK && existing_model->model == bsgfx_prefabModel()) {
			result = bs_model(package_id, name, 0, &existing_model);

			if (result == BS_RESULT_OK) {
				bs_Batch* batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_MESH_INSTANCED)->batch;
				bs_unpushBatch(batch);
				bsgfx_loadPrefabs(bsgfx_getType(BSGFX_TYPE_PREFAB)->package_id, resource->model);
			}
		}

	break;
	//case BS_RESOURCE_TEXTURE:
	//	bs_except(BSX_FAILED_TO_QUERY);
	//	bs_queryResource(package_id, name);
	//	if (!bs_except(0))
	//		bsgfx_textureArray(0, package_id, name);
	//
	//	//bsgfx_loadTextureDimension(package_id, name, 64, BSGFX_IMAGE_64, BSGFX_SET_64, BSGFX_BINDING_64);
	//	break;
	}

	return result;
}

static int _bsmod_compareResource(const bsmod_Resource* a, const bsmod_Resource* b) {
	if (a->type < b->type) return -1;
	else if (a->type > b->type) return 1;
	return 0;
}

BSMODAPI bs_Result _val_bsmod_savePackageN(const char* path, int path_length) {
	BSMOD_VALIDATE(bs_instance()->device != NULL, BS_RESULT_VALIDATION_ERROR,);

	return _bsmod_savePackageN(path, path_length);
}

BSMODAPI bs_Result _bsmod_savePackageN(char* path, int path_length) {
	bs_Result result;

	bsmod_Package* package = _bsmod_queryPackage(path);

	if (!package || !package->has_changes)
		return BS_RESULT_OK;

	/**
	 Binary
	 */
	for (int i = 0; i < package->chunks.count; i++) {
		bsmod_Chunk* chunk = bs_fetchUnit(&package->chunks, i);
		if (!chunk->has_changes)
			continue;

		bs_saveFileF(chunk->bin.data, chunk->bin.count, "%s/%s_%03d.bpak", package->directory, package->name, (i + 1));
		chunk->has_changes = false;
	}

	/**
	 Sort by type
	 */
	qsort(package->resources.data, package->resources.count, sizeof(bsmod_Resource), _bsmod_compareResource);

	/**
	 Headers
	 */
	size_t size;
	size = BPAK_HEADER_SIZE;
	size += BS_RESOURCE_TYPE_COUNT * BPAK_RESOURCE_TYPE_SIZE;
	size += package->resources.count * BPAK_RESOURCE_SIZE;

	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);
		size += strlen(resource->name) + 1; // + \n
	}

	unsigned char* data = bs_malloc(size);

	bs_setLittleEndian32(BPAK_MAGIC, data + BPAK_MAGIC_OFFSET);
	bs_setLittleEndian32(package->resources.count, data + BPAK_RESOURCES_COUNT_OFFSET);
	bs_setLittleEndian32(BS_RESOURCE_TYPE_COUNT, data + BPAK_RESOURCES_TYPES_COUNT_OFFSET);
	bs_setLittleEndian32(0, data + BPAK_RESOURCES_RESERVED);

	unsigned char* resource_types_data = data + BPAK_RESOURCE_TYPES_OFFSET;
	memset(resource_types_data, 0, BS_RESOURCE_TYPE_COUNT * BPAK_RESOURCE_TYPE_SIZE);

	bs_ResourceType last_type = -1;
	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);
		unsigned char* resource_type_data;

		if (last_type != resource->type) {
			last_type = resource->type;

			assert(last_type >= 0);
			assert(last_type < BS_RESOURCE_TYPE_COUNT);

			resource_type_data = resource_types_data + last_type * BPAK_RESOURCE_TYPE_SIZE;

			bs_setLittleEndian32(i, resource_type_data + BPAK_RESOURCE_TYPE_START_OFFSET);
		}
		else
			resource_type_data = resource_types_data + last_type * BPAK_RESOURCE_TYPE_SIZE;


		bs_U32 num = bs_getLittleEndian32(resource_type_data + BPAK_RESOURCE_TYPE_COUNT_OFFSET);
		bs_setLittleEndian32(num + 1, resource_type_data + BPAK_RESOURCE_TYPE_COUNT_OFFSET);
	}

	unsigned char* resources_data = resource_types_data + BS_RESOURCE_TYPE_COUNT * BPAK_RESOURCE_TYPE_SIZE;

	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);

		bs_setLittleEndian64(resource->name_hash, resources_data + BPAK_RESOURCE_NAME_HASH_OFFSET);
		bs_setLittleEndian32(resource->chunk, resources_data + BPAK_RESOURCE_CHUNK_OFFSET);
		bs_setLittleEndian32(resource->offset, resources_data + BPAK_RESOURCE_START_OFFSET);
		bs_setLittleEndian32(resource->size, resources_data + BPAK_RESOURCE_SIZE_OFFSET);
		bs_setLittleEndian32(resource->name_length, resources_data + BPAK_RESOURCE_NAME_LENGTH_OFFSET);
		bs_setLittleEndian32(resource->type, resources_data + BPAK_RESOURCE_TYPE_OFFSET);
		bs_setLittleEndian32(0, resources_data + BPAK_RESOURCE_RESERVED);
		resources_data += BPAK_RESOURCE_SIZE;

		memcpy(resources_data, resource->name, resource->name_length);
		resources_data += resource->name_length;

		memcpy(resources_data, "\n", 1);
		resources_data++;
	}

	bs_saveFileF(data, size, "%s/%s.bpak", package->directory, package->name);

	bs_free(data);

	/**
	 Reload resources
	 */
	int package_id;
	result = bs_loadPackageF(&package_id, "%s/%s.bpak", package->directory, package->name);

	package->has_changes = false;
	return result;
}