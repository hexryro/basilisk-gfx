
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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include <assert.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <shlobj_core.h>
#else
#include <unistd.h>
#endif

#include <basilisk-core.h>
#include <bs_internal.h>
#include <vulkan.h>



  /*==============================================================================
   * Package Format (.bpak)
   *============================================================================*/

BSAPI bs_List* _bs_packages() {
    static bs_List _bs_packages_ = {
        .unit_size = sizeof(bs_Package),
        .increment = 4
    };

    return &_bs_packages_;
}

BSAPI bs_List* _bs_objectSources() {
    static bs_List _bs_object_sources_ = {
        .unit_size = sizeof(bs_Object),
        .increment = 32,
    };

    return &_bs_object_sources_;
}

BSAPI void _bs_destroyResource(bs_Resource* resource) {
    _bs_free(resource->data);
    _bs_free(resource);
}

#define BS_FAILED_TO_QUERY(format, ...) \
    _bs_warnF("Failed to query:\n" format __VA_OPT__("\n",) __VA_ARGS__)

BSAPI bs_Result _bs_queryResource(int package_id, bs_ResourceType type, const char* name, bs_Resource** out) {
    bs_Package* package = _bs_fetchUnit(_bs_packages(), package_id);
    bs_U64 hash = _bs_stringHash(name);

    bs_Range range = package->resource_type_offsets[type];

    for (int i = 0; i < range.num; i++) {
        bs_ResourceHeader* resource = package->resource_headers + range.offset + i;
        if (resource->name_hash == hash) {
            *out = resource->resource;
            return BS_RESULT_OK;
        }
    }

    *out = NULL;

    BS_FAILED_TO_QUERY("Resource \"%s\"", name);
    return BS_RESULT_FAILED_TO_QUERY;
}

BSAPI int _bs_queryPackage(const char* name) {
    bs_U64 hash = _bs_stringHash(name);

    for (int i = 0; i < _bs_packages()->count; i++) {
        bs_Package* package = _bs_fetchUnit(_bs_packages(), i);
        if (package->path_hash == hash) {
            return i;
        }
    }

    return -1;
}

BSAPI bs_Result _bs_loadResourceN(int package_id, bs_U32 flags, bs_ResourceType type, bs_Resource** out, char* resource_name, int resource_name_length) {
    if (package_id < 0)
        return BS_RESULT_OUT_OF_BOUNDS;

    bs_Package* package = _bs_fetchUnit(_bs_packages(), package_id);

    bs_U64 hash = _bs_stringHash(resource_name);

    bs_ResourceHeader* existing = NULL;
    for (int i = 0; i < package->resource_type_offsets[type].num; i++) {
        bs_ResourceHeader* resource = package->resource_headers + package->resource_type_offsets[type].offset + i;
        if (resource->name_hash == hash) {
            existing = resource;
            break;
        }
    }

    if (!existing) {
        _bs_warnF("Failed to query resource \"%s\" in package \"%s\"", resource_name, package->path);
        return BS_RESULT_FAILED_TO_QUERY;
    }

    if (!existing->resource) {
        existing->resource = _bs_calloc(1, sizeof(bs_Resource)); // TODO: don't allocate each resource individually
        existing->resource->hash = hash;
        existing->resource->name = resource_name;
    }
    //else
    //    _bs_free(existing->resource->data);

    char* ext = strrchr(package->path, '.');
    if (ext) ext[0] = '\0';

    bs_Result result = _bs_loadFileChunkF(
        existing->offset, 
        existing->size, 
        &existing->resource->data, 
        "%s_%03d.bpak", 
        package->path, (existing->chunk + 1)
    );

    if (ext) ext[0] = '.';

    if (result == BS_RESULT_OK) {
        _bs_infoF("Loaded resource \"%s\"", resource_name);
        *out = existing->resource;
    }

    return result;
}

BSAPI bs_Result _bs_loadPackageN(int* out, const char* path, int path_length) {
    bs_Result result;

    bs_String* raw;
    result = _bs_loadFileF(&raw, path);
    if (result != BS_RESULT_OK)
        return result;

    unsigned char* data = raw->value;

    bs_U32 magic = bs_getLittleEndian32(data + BPAK_MAGIC_OFFSET);
    if (magic != BPAK_MAGIC) {
        bs_free(raw);
        BS_WARN_INVALID_MAGIC("package", path);
        return BS_RESULT_CORRUPTED;
    }

    bs_U32 resources_count = bs_getLittleEndian32(data + BPAK_RESOURCES_COUNT_OFFSET);
    if (resources_count == 0) {
        bs_warnF("%s at %s:%d: No resources in package \"%s\"", __func__, __FILE__, __LINE__, path); // TODO: warn macro
        return BS_RESULT_CORRUPTED;
    }

    bs_U32 resources_types_count = bs_getLittleEndian32(data + BPAK_RESOURCES_TYPES_COUNT_OFFSET);
    if (resources_types_count == 0) {
        bs_warnF("%s at %s:%d: No resource types in package \"%s\"", __func__, __FILE__, __LINE__, path); // TODO: warn macro
        return BS_RESULT_CORRUPTED;
    }

    bs_U64 path_hash = _bs_stringHash(path);

    bs_Package* existing = NULL;
    bs_ResourceHeader* old_headers = NULL;
    int old_headers_count = 0;
    int id = -1;
    for (int i = 0; i < _bs_packages()->count; i++) {
        bs_Package* package = _bs_fetchUnit(_bs_packages(), i);
        if (package->path_hash == path_hash) {
            existing = package;
            old_headers = package->resource_headers;
            old_headers_count = package->resource_headers_count;
            id = i;
            _bs_free(package->raw);
            package->raw = NULL;
            break;
        }
    }

    _bs_infoF("Loading package \"%s\"", path);
    if (!existing) {
        id = _bs_packages()->count;

        existing = _bs_pushBack(_bs_packages(), &(bs_Package) {
            .path = strdup(path),
            .path_hash = path_hash,
        });
    }

    existing->raw = raw;
    existing->resource_headers_count = resources_count;
    existing->resource_headers = bs_calloc(resources_count, sizeof(bs_ResourceHeader));

    if (resources_types_count > BS_RESOURCE_TYPE_COUNT) {
        bs_warnF("%s at %s:%d: Invalid resource types count (%d) in package \"%s\"", __func__, __FILE__, __LINE__, resources_types_count, path); // TODO: warn macro
        return BS_RESULT_CORRUPTED;
    }

    unsigned char* resource_types_offset = data + BPAK_RESOURCE_TYPES_OFFSET;
    for (int i = 0; i < resources_types_count; i++) {
        existing->resource_type_offsets[i].offset = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_TYPE_START_OFFSET);
        existing->resource_type_offsets[i].num = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_TYPE_COUNT_OFFSET);

        resource_types_offset += BPAK_RESOURCE_TYPE_SIZE;
    }

    int actual_resources_count = 0;
    for (int i = 0; i < resources_count; i++) {

        bs_U64 name_hash = bs_getLittleEndian64(resource_types_offset + BPAK_RESOURCE_NAME_HASH_OFFSET);
        bs_I32 chunk = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_CHUNK_OFFSET);
        bs_I32 offset = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_START_OFFSET);
        bs_I32 size = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_SIZE_OFFSET);
        bs_I32 name_length = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_NAME_LENGTH_OFFSET);
        bs_I32 type = bs_getLittleEndian32(resource_types_offset + BPAK_RESOURCE_TYPE_OFFSET);

#ifdef _DEBUG
        if (chunk < 0 || offset < 0 || size < 0 || name_length < 0 || type < 0) {
            bs_warnF("%s at %s:%d: Corrupted resource (%d) in package \"%s\"", __func__, __FILE__, __LINE__, i, path); // TODO: warn macro
            return BS_RESULT_CORRUPTED;
        }
#endif

        resource_types_offset += BPAK_RESOURCE_SIZE;
        unsigned char* resource_name = resource_types_offset;

        char* end = strchr(resource_name, '\n');
        if (!end) {
            return BS_RESULT_CORRUPTED;
        }
        end[0] = '\0';

        resource_types_offset += name_length + 1; // \n

        bs_ResourceHeader* added = existing->resource_headers + actual_resources_count++;

        if (actual_resources_count > resources_count) {
            end[0] = '\n';
            break;
        }

        existing->chunks_count = BS_MAX(existing->chunks_count, chunk + 1);

        *added = (bs_ResourceHeader) {
            .chunk = chunk,
            .name_hash = name_hash,
            .name_length = name_length,
            .offset = offset,
            .size = size,
            .type = type,
            .name = strdup(resource_name),
        };
        
        for (int j = 0; j < old_headers_count; j++) {
            bs_ResourceHeader* existing_header = old_headers + j;
            if (existing_header->name_hash == name_hash) {
                added->resource = existing_header->resource;
                break;
            }
        }

        end[0] = '\n';
    }

    *out = id;

    if (old_headers) {
        bs_free(old_headers);
    }

    if (actual_resources_count != resources_count) {
        // Kinda critical but we'll see what happens, shouldn't happen though
        bs_warnF("Package \"%s\" specifies %d resources, but %d resources were found\n", resources_count, (actual_resources_count + 1));
        return BS_RESULT_CORRUPTED;
    }

    return BS_RESULT_OK;
}



  /*==============================================================================
   * Objects
   *============================================================================*/

#define BS_VALIDATE_SOURCE(source_id, _return) \
    BS_VALIDATE(source_id < _bs_objectSources()->count, _return,)

#define BS_VALIDATE_ID(id, _return) \
    BS_VALIDATE(id < ((bs_ObjectSource*)_bs_fetchUnit(_bs_objectSources(), source_id))->ids_count, _return,)

BSAPI int _bs_configureSource(bs_ObjectType type, int count, const char** names) {
    if (count == 0)
        return -1;

    bs_ObjectSource source = {
        .type = type,
        .ids = _bs_calloc(count, sizeof(struct bs_ObjectId)),
        .ids_count = count,
    };

    for (int i = 0; i < source.ids_count; i++) {
        source.ids[i].name = names[i];
        source.ids[i].name_hash = _bs_stringHash(source.ids[i].name);
    }

    bs_List* object_sources = _bs_objectSources();
    _bs_pushBack(object_sources, &source);

    return object_sources->count - 1;
}

 /**
  _bs_exists
  */
BSAPI bool _val_bs_exists(bs_U32 source_id, bs_U32 id) {
    BS_VALIDATE_SOURCE(source_id, false);
    BS_VALIDATE_ID(id, false);

    return _bs_exists(source_id, id);
}

BSAPI bool _bs_exists(bs_U32 source_id, bs_U32 id) {
    bs_List* object_sources = _bs_objectSources();
    bs_ObjectSource* source = _bs_fetchUnit(object_sources, source_id);

    bs_Object* object = source->ids[id].object;

    return
        object &&
       // object->strikes == 0 &&
        object->head != NULL && 
        object->head->id >= 0;
}

 /**
  _bs_fetch
  */
BSAPI bs_Object* _val_bs_fetch(bs_U32 source_id, bs_U32 id) {
    BS_VALIDATE_SOURCE(source_id, NULL);
    BS_VALIDATE_ID(id, NULL);

    return _bs_fetch(source_id, id);
}

BSAPI bs_Object* _postval_bs_fetch(bs_U32 source_id, bs_U32 id, bs_Object* object) {
    BS_VALIDATE(object != NULL, NULL, "Object (%d, %d) has not been created yet", source_id, id);
    BS_VALIDATE(object->head != NULL, NULL, "Object (%d, %d)", source_id, id); // TODO: what does this mean
    BS_VALIDATE(object->head->id >= 0, NULL, "Object (%d, %d)", source_id, id); // TODO: what does this mean

    return object;
}

BSAPI bs_Object* _bs_fetch(bs_U32 source_id, bs_U32 id) {
    bs_List* object_sources = _bs_objectSources();
    bs_ObjectSource* source = _bs_fetchUnit(object_sources, source_id);
    bs_Object* object = source->ids[id].object;

    return object;
}

 /**
  */
BSAPI bool _bs_shouldLoadId(bs_U32 source_id, bs_U32 id) {
    return true;

   // assert(source_id < _bs_object_sources.count);
   // bs_ObjectSource* source = _bs_fetchUnit(&_bs_object_sources, source_id);
   // assert(id < source->ids_count);
   // bs_Object* object = source->ids[id].object;

   // return object->flags & BS_OBJECT_SHOULD_LOAD;
}

static inline const char* _bs_objectTypeName(bs_ObjectType type) {
    switch (type) {
    case BS_OBJECT_IMAGE: return "image";
    case BS_OBJECT_SAMPLER: return "sampler";
    case BS_OBJECT_BUFFER: return "buffer";
    case BS_OBJECT_QUEUE: return "queue";
    case BS_OBJECT_BATCH: return "batch";
    case BS_OBJECT_RENDERER: return "renderer";
    default: return "unknown object type";
    }
}

static inline void _bs_logObjectCreated(bs_U32 source_id, bs_U32 id) {
    bs_List* object_sources = _bs_objectSources();
    bs_ObjectSource* source = _bs_fetchUnit(object_sources, source_id);
    bs_Object* object = source->ids[id].object;
    const char* object_type_name = _bs_objectTypeName(source->type);

    if (_bs_args_.color_log)
        _bs_infoF(BS_PRINT_GREEN "+" BS_PRINT_RESET " (%d) %s " BS_PRINT_CYAN "%s" BS_PRINT_RESET, id, object_type_name, source->ids[id].name);
    else
        _bs_infoF("+ (%d) %s %s", id, object_type_name, source->ids[id].name);
}

static inline void _bs_logObjectUpdated(bs_U32 source_id, bs_U32 id) {
    bs_List* object_sources = _bs_objectSources();
    bs_ObjectSource* source = _bs_fetchUnit(object_sources, source_id);
    bs_Object* object = source->ids[id].object;
    const char* object_type_name = _bs_objectTypeName(source->type);

    if (_bs_args_.color_log)
        _bs_infoF(BS_PRINT_YELLOW "/" BS_PRINT_RESET  " (%d) %s " BS_PRINT_CYAN "%s" BS_PRINT_RESET, id, object_type_name, source->ids[id].name);
    else
        _bs_infoF("/ (%d) %s %s", id, object_type_name, source->ids[id].name);
}

static inline void _bs_logObjectUnchanged(bs_U32 source_id, bs_U32 id) {
  //  if (_bs_args_.color_log)
  //      _bs_infoF(BS_PRINT_GRAY "~" BS_PRINT_RESET  " (%d) %s " "%s\n" BS_PRINT_RESET, id, _bs_objectName(type), _bs_idName(id));
  //  else
  //      _bs_infoF("~ (%d) %s %s\n", id, _bs_objectName(type), _bs_idName(id));
}

static inline bs_ObjectSource* _bs_fetchObjectSource(bs_U32 source_id) {
    bs_List* object_sources = _bs_objectSources();
    bs_ObjectSource* source = _bs_fetchUnit(object_sources, source_id);
    return source;
}

BSAPI const char* _val_bs_idName(bs_U32 source_id, bs_U32 id) {
    BS_VALIDATE_SOURCE(source_id, NULL);
    BS_VALIDATE_ID(id, NULL);

    return _bs_idName(source_id, id);
}

BSAPI const char* _bs_idName(bs_U32 source_id, bs_U32 id) {
    if (source_id == BS_U32_MAX)
        return "";
    bs_ObjectSource* source = _bs_fetchObjectSource(source_id);
    return source->ids[id].name;
}

static bs_Object* _bs_allocateObject(size_t size, size_t flexible_size, int flexible_count, bs_U32 flags) {
    static int heaps_count;
    static struct {
        char* block;
        bs_U64 size;
    }* heaps = NULL;

    const size_t flexible_array_size = flexible_size * flexible_count;
    size_t new_size = size + flexible_array_size + sizeof(bs_Object);

    const int heap_size = 65536;
    if (!heaps || (heaps[heaps_count - 1].size + new_size) > heap_size) {
        heaps = _bs_realloc(heaps, sizeof(*heaps) * ++heaps_count);
        heaps[heaps_count - 1].size = 0;
        heaps[heaps_count - 1].block = _bs_malloc(heap_size);
    }

    unsigned char* result = (int*)(heaps[heaps_count - 1].block + heaps[heaps_count - 1].size);
    bs_Object object = {
        .head = result + sizeof(bs_Object),
        .flags = flags | BS_OBJECT_WAS_CREATED,
    };

    memcpy(result, &object, sizeof(bs_Object));
    memset(result + sizeof(bs_Object), 0, size);
    memset(result + sizeof(bs_Object) + size, 0, flexible_array_size);

    heaps[heaps_count - 1].size += new_size;

    return result;
}

static bs_Object* _bs_update(bs_U32 source_id, bs_U32 id, int size, int swap_size) {
    bs_Object* object = _bs_fetch(source_id, id);
    memset(object->head, 0, size + swap_size);
    //memcpy(object->head, data, size);
    object->head->id = id;
    object->head->source_id = source_id;
    object->flags |= BS_OBJECT_ALREADY_EXISTS | BS_OBJECT_WAS_ALTERED;
    object->flags &= ~BS_OBJECT_WAS_CREATED;

    _bs_logObjectUpdated(source_id, id);

    return object;
}

BSAPI bs_Object* _val_bs_object(bs_U32 source_id, bs_U32 id, size_t size, size_t flexible_array_size, int flexible_count, bs_U32 flags, bs_ObjectType object_type) {
    if (source_id != BS_U32_MAX) {
        BS_VALIDATE_SOURCE(source_id, NULL);
    }
    if (source_id != BS_U32_MAX) {
        BS_VALIDATE_ID(id, NULL);
    }

    BS_VALIDATE(flexible_count >= 0, NULL,);

    return _bs_object(source_id, id, size, flexible_array_size, flexible_count, flags, object_type);
}

BSAPI bs_Object* _bs_object(bs_U32 source_id, bs_U32 id, size_t size, size_t flexible_array_size, int flexible_count, bs_U32 flags, bs_ObjectType object_type) {
    bs_Object* result;
    if (source_id == BS_U32_MAX) {
        result = _bs_allocateObject(size, flexible_array_size, flexible_count, flags);
        result->head->type = object_type;
        result->head->source_id = source_id;
        return result;
    }

    bs_ObjectSource* source = _bs_fetchObjectSource(source_id);

    result = source->ids[id].object;

    if (!_bs_shouldLoadId(source_id, id))
        return NULL;

    if (result && result->head) {
        result->flags = flags | BS_OBJECT_ALREADY_EXISTS;
        if (flags & BS_OBJECT_FORCE_DESTROY)
            _bs_logObjectUpdated(source_id, id);

        return result;
    }

    if (!_bs_exists(source_id, id)) {
        result = source->ids[id].object = _bs_allocateObject(size, flexible_array_size, flexible_count, flags);
        result->head->type = object_type;
        result->head->id = id;
        result->head->source_id = source_id;

        _bs_logObjectCreated(source_id, id);

        return result;
    }
    else
        return _bs_update(source_id, id, size, flexible_array_size);
}

BSAPI void _bs_resetObject(bs_Header* head, size_t size) {
    int id = head->id;
    int source_id = head->source_id;
    bs_ObjectType type = head->type;
    memset(head, 0, size);
    head->source_id = source_id;
    head->id = id;
    head->type = type;
}

 /**
  Name object
  */

BSAPI void _bs_nameImage(bs_Object* object, const char* name) {
    for (int i = 0; i < _bs_imageSwapsCount(object->image); i++) {
        bsi_nameHandleF(object->image->_[i].vk_image, VK_OBJECT_TYPE_IMAGE, BS_PRINT_COLOR("%s", BS_PRINT_BLUE_BRIGHT), name);
        bsi_nameHandleF(object->image->_[i].vk_image_view, VK_OBJECT_TYPE_IMAGE_VIEW, BS_PRINT_COLOR("%s (View)", BS_PRINT_BLUE_BRIGHT), name);
        bsi_nameHandleF(object->image->_[i].vk_memory, VK_OBJECT_TYPE_DEVICE_MEMORY, BS_PRINT_COLOR("%s (Memory)", BS_PRINT_BLUE_BRIGHT), name);
    }
}

BSAPI void _bs_nameSampler(bs_Object* object, const char* name) {
    int name_length = strlen(name);
    for (int i = 0; i < _bs_samplerSwapsCount(object->sampler); i++) {
        bsi_nameHandleN(object->sampler->_[i].vk_sampler, VK_OBJECT_TYPE_SAMPLER, name, name_length);
    }
}
