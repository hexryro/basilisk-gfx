
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

		if (hash == package->name_hash)
			return package;
	}

	return NULL;
}

BSMODAPI bsmod_Package* _bsmod_ensurePackage(const char* name) {
	bsmod_Package* existing = _bsmod_queryPackage(name);
	if (existing)
		return existing;

	bs_infoF("Created package %s\n", name);
	return bs_pushBack(&_bsmod_packages_, &(bsmod_Package) {
		.name = name,
		.name_hash = bs_stringHash(name),
		.chunks = bs_list(sizeof(bsmod_Chunk), 16),
		.resources = bs_list(sizeof(bsmod_Resource), 32),
	});
}

BSMODAPI bsmod_Resource* _bsmod_queryResource(bsmod_Package* package, const char* name) {
	bs_U64 hash = bs_stringHash(name);

	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);

		if (hash == resource->header.name_hash)
			return resource;
	}

	return NULL;
}

static bsmod_Resource* _bsmod_ensureResource(bsmod_Package* package, char* name) {
	bsmod_Resource* existing = _bsmod_queryResource(package, name);
	if (existing)
		return existing;

	return bs_pushBack(&package->resources, &(bsmod_Resource) {
		.header = {
			.name_hash = bs_stringHash(name),
			.name_length = strlen(name),
		},
		.name = strdup(name),
	});
}

BSMODAPI bs_Result _bsmod_iniPackage(const char* package_name) {
	bs_Result result;

	int previous_count = _bsmod_packages_.count;
	bsmod_Package* package = _bsmod_ensurePackage(package_name);
	if (previous_count == _bsmod_packages_.count) {
		bs_warnF("Package \"%s\" is already initialized\n", package_name);
		return BS_RESULT_OK; // TODO
	}

	bs_String* bpak;
	result = bs_loadFileF(&bpak, "%s.bpak", package_name);
	if (result != BS_RESULT_OK)
		return result;

	int chunks_count = 0;

	for (int i = sizeof(bs_PackageHeader); i < (bpak->len - 1);) {
		bs_ResourceHeader* header = bpak->value + i;
		i += sizeof(header->header);
		if (i >= bpak->len) {
			bs_criticalF("Package \"%s\" has corrupted data", package_name); // TODO: bsmod warn
			return BS_RESULT_CORRUPTED;
		}

		char* name = bpak->value + i;
		i += header->header.name_length + 1;
		if (i >= bpak->len) {
			bs_criticalF("Package \"%s\" has corrupted data", package_name); // TODO: bsmod warn
			return BS_RESULT_CORRUPTED;
		}

		char* end = strchr(name, '\n');
		if (!end) {
			bs_criticalF("Package \"%s\" has corrupted data", package_name); // TODO: bsmod warn
			return BS_RESULT_CORRUPTED;
		}
		end[0] = '\0';

		bsmod_Resource* added = bs_pushBack(&package->resources, &(bsmod_Resource) {
			.header = header->header,
			.name = strdup(name),
		});

		chunks_count = BS_MAX(chunks_count, (header->header.chunk + 1));
	}

	for (int i = 0; i < chunks_count; i++) {
		bs_String* chunk_bin; 
		if (bs_loadFileF(&chunk_bin, "%s_%03d.bpak", package_name, (i + 1)) != BS_RESULT_OK)
			continue;

		bsmod_Chunk* chunk = bs_pushBack(&package->chunks, &(bsmod_Chunk) {
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

BSMODAPI bs_Result _bsmod_packResource(bs_ResourceType type, unsigned char* data, size_t data_size, const char* package_name, char* resource_name, int resource_name_length) {
	bsmod_Package* package = _bsmod_ensurePackage(package_name);

	bsmod_Resource* resource = _bsmod_ensureResource(package, resource_name);
	resource->header.type = type;

	bsmod_Chunk* chunk = bs_fetchUnit(&package->chunks, resource->header.chunk);
	
	if (resource->header.size != data_size) {
		if (resource->header.size > 0) {
			bs_infoF("Deleting old resource %s " BS_PRINT_COLOR("(-%d bytes)", BS_PRINT_RED) "\n", resource_name, resource->header.size);
			
			size_t remaining = chunk->bin.count - resource->header.offset;
			BSMOD_VALIDATE(remaining >= resource->header.size, BS_RESULT_VALIDATION_ERROR,);

			memmove(
				chunk->bin.data + resource->header.offset,
				chunk->bin.data + resource->header.offset + resource->header.size,
				chunk->bin.count - (resource->header.offset + resource->header.size));
			chunk->bin.count -= resource->header.size;
			chunk->has_changes = true;

			for (int i = 0; i < package->resources.count; i++) {
				bsmod_Resource* r = bs_fetchUnit(&package->resources, i);
				if (r != resource && r->header.chunk == resource->header.chunk && r->header.offset > resource->header.offset) {
					bs_infoF("  Adjusted offset for resource \"%s\"\n", r->name);
					r->header.offset -= resource->header.size;
					BSMOD_VALIDATE(r->header.offset >= 0, BS_RESULT_VALIDATION_ERROR,);
				}
			}
		}

		chunk = _bsmod_ensureChunk(package, data_size);
		resource->header.chunk = chunk->id;
		resource->header.offset = chunk->bin.count;
		resource->header.size = data_size;
		resource->header.type = type;
		resource->header.reserved = 0;
		chunk->bin.count += data_size;
		bs_infoF("Created resource %s " BS_PRINT_COLOR("(+%d bytes)", BS_PRINT_GREEN) "\n", resource_name, data_size);
	} 
	else
		bs_infoF("Packed resource %s " BS_PRINT_COLOR("(+-0 bytes)", BS_PRINT_GRAY) "\n", resource_name);

	memcpy(chunk->bin.data + resource->header.offset * chunk->bin.unit_size, data, data_size);

	chunk->has_changes = true;
	package->has_changes = true;
	resource->has_changes = true;

	return BS_RESULT_OK;
}

static bs_Result _bsmod_loadResource(int type, int package_id, char* name) {
	bs_Result result = BS_RESULT_OK;

	bs_Scope scope = bs_enterSingle();

	bs_Resource* resource; 
	result = bs_queryResource(package_id, name, &resource);
	if (result != BS_RESULT_OK)
		goto end;

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
			result = bs_loadImage(image_object, package_id, existing_image->flags, name, strlen(name));
			if (result != BS_RESULT_OK)
				goto end;

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
				if (source->type == BS_OBJECT_IMAGE) {
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
			if (bs_loadAtlas(atlas_object, package_id, 0, name, strlen(name)) == BS_RESULT_OK) {
				_bsmod_bindAtlases();
			}
		}
		else {
			bs_warnF("Could not reload resource \"%s\", object id could not be found\n", name);
		}
		
		break;
	case BS_RESOURCE_SHADER:
		bs_Resource* existing_shader;
		result = bs_queryResource(package_id, name, &existing_shader);
		if (result == BS_RESULT_OK)
			bs_shader(package_id, name, 0, &existing_shader);

		break;
	case BS_RESOURCE_MODEL:
		bs_Resource* existing_model;
		result = bs_queryResource(package_id, name, &existing_model);
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

end:
	bs_leaveSingle(&scope);

	return result;
}

static int _bsmod_compareResource(const bsmod_Resource* a, const bsmod_Resource* b) {
	if (a->header.type < b->header.type) return -1;
	else if (a->header.type > b->header.type) return 1;
	return 0;
}

BSMODAPI bs_Result _val_bsmod_savePackage(const char* name) {
	BSMOD_VALIDATE(bs_instance()->device != NULL, BS_RESULT_VALIDATION_ERROR,);

	return _bsmod_savePackage(name);
}

BSMODAPI bs_Result _bsmod_savePackage(const char* name) {
	bs_Result result;
	bsmod_Package* package = _bsmod_ensurePackage(name);

	if (!package->has_changes)
		return BS_RESULT_OK;

	package->has_changes = false;

	/**
	 Binary
	 */
	for (int i = 0; i < package->chunks.count; i++) {
		bsmod_Chunk* chunk = bs_fetchUnit(&package->chunks, i);
		if (!chunk->has_changes)
			continue;

		bs_saveFileF(chunk->bin.data, chunk->bin.count, "%s_%03d.bpak", name, (i + 1));
		chunk->has_changes = false;
	}

	/**
	 Sort by type
	 */
	qsort(package->resources.data, package->resources.count, sizeof(bsmod_Resource), _bsmod_compareResource);

	/**
	 Headers
	 */
	int name_lengths = 0;
	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);
		name_lengths += strlen(resource->name);
	}

	const size_t header_size = sizeof(bs_ResourceHeaderData);

	size_t size = sizeof(bs_PackageHeader) + package->resources.count * (header_size + 1) + name_lengths;
	unsigned char* data = bs_malloc(size);

	bs_PackageHeader header = {
		.magic = BS_BPAK_MAGIC,
		.resources_count = package->resources.count,
		.resource_types_count = BS_RESOURCE_TYPE_COUNT,
	};

	bs_ResourceType last_type = -1;
	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);

		if (last_type != resource->header.type) {
			last_type = resource->header.type;
			header.resource_type_offsets[last_type].offset = i;
		}

		assert(last_type >= 0);
		header.resource_type_offsets[last_type].num++;
	}

	memcpy(data, &header, sizeof(bs_PackageHeader));

	size_t offset = sizeof(bs_PackageHeader);
	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);

		memcpy(data + offset, &resource->header, header_size);
		offset += header_size;
		memcpy(data + offset, resource->name, resource->header.name_length);
		offset += resource->header.name_length;
		memcpy(data + offset, "\n", 1);
		offset++;
	}

	bs_saveFileF(data, size, "%s.bpak", name);

	bs_free(data);

	/**
	 Reload resources
	 */
	int package_id;
	result = bs_loadPackage(name, &package_id);
	if (result != BS_RESULT_OK)
		return result;

	for (int i = 0; i < package->resources.count; i++) {
		bsmod_Resource* resource = bs_fetchUnit(&package->resources, i);
		if (resource->has_changes) {
			result = _bsmod_loadResource(resource->header.type, package_id, resource->name);
			resource->has_changes = false;
		}
	}

	return BS_RESULT_OK;
}