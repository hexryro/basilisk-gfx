
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

bsgfx_Type _bsgfx_types_[BSGFX_TYPE_COUNT] = { 0 };

BSGFXAPI bsgfx_Type* _bsgfx_getType(bsgfx_TypeId type_id) {
    return _bsgfx_types_ + type_id;
}

BSGFXAPI int _bsgfx_count(bsgfx_TypeId type_id) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;
    return type->count;
}

BSGFXAPI int _bsgfx_id(bsgfx_TypeId type_id, unsigned char* p) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;
    return (p - type->mapped) / type->mapped_unit_size;
}

BSGFXAPI int _bsgfx_rawId(bsgfx_TypeId type_id, unsigned char* p) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;
    return (p - type->unmapped) / type->unmapped_unit_size;
}

static inline bool _bsgfx_validateTypeBounds(bsgfx_TypeId type_id, int id) {
    int count = _bsgfx_count(type_id);
    if (id >= count) {
        bs_warnF("\"%s\" %d >= %d", _bsgfx_types_[type_id].singular, id, count); // TODO: bsgfx warn
        return false;
    }

    return true;
}

 /**
  Get type
  */
BSGFXAPI void* _val_bsgfx_get(bsgfx_TypeId type_id, bs_U32 id) {
    if (!_bsgfx_validateTypeBounds(type_id, id))
        return NULL;

    return _bsgfx_get(type_id, id);
}

BSGFXAPI void* _bsgfx_get(bsgfx_TypeId type_id, bs_U32 id) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;
    return type->mapped + type->mapped_accessors[id];
}

 /**
  Get raw type
  */
BSGFXAPI void* _val_bsgfx_getRaw(bsgfx_TypeId type_id, int id) {
    if (!_bsgfx_validateTypeBounds(type_id, id))
        return NULL;

    return _bsgfx_getRaw(type_id, id);
}

BSGFXAPI void* _bsgfx_getRaw(bsgfx_TypeId type_id, int id) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;
    return type->unmapped + type->unmapped_accessors[id];
}

 /**
  Flexible count
  */
static int _bsgfx_flexibleCountPointer(int flexible_offset, unsigned char* p) {
    return flexible_offset == 0 ? 0 :*(int*)(p + flexible_offset);
}

BSGFXAPI int _bsgfx_flexibleCount(bsgfx_TypeId type_id, int id) {
    return _bsgfx_flexibleCountPointer(_bsgfx_types_[type_id].unmapped_flexible_offset, _bsgfx_getRaw(type_id, id));
}

//void _bsgfx_addFlexible(bsgfx_TypeId type_id, int id) {
//    bsgfx_Type* type = _bsgfx_types + type_id;
//    unsigned char* p = _bsgfx_get(type_id, id);
//    if (!p)
//        return;
//
//  //  size_t mapped_capacity = type->capacity * mapped_size + type->flexible_count * mapped_flexible_size;
//  //  size_t unmapped_capacity = type->capacity * unmapped_size + type->flexible_count * unmapped_flexible_size;
//
//    type->flexible_count++;
//}

 /**
  Map type
  */
BSGFXAPI void _val_bsgfx_map(bsgfx_TypeId type_id, int id) {
    BSGFX_VALIDATE(id >= 0,,);
    BSGFX_VALIDATE(id < _bsgfx_count(type_id),,);

    bsgfx_Type* type = _bsgfx_types_ + type_id;
    BSGFX_VALIDATE(type->mapped != NULL,,);

    _bsgfx_map(type_id, id);
}

BSGFXAPI void _bsgfx_map(bsgfx_TypeId type_id, int id) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;

    type->mapper(
        _bsgfx_getRaw(type_id, id),
        _bsgfx_get(type_id, id)
    );

   // if (_bsgfx_procs_.bsmod_onMap) // TODO: maybe put in postval
   //     _bsgfx_procs_.bsmod_onMap(type_id, id);
}

BSGFXAPI void _bsgfx_remap(bsgfx_TypeId type_id) {
    bsgfx_Type* type = _bsgfx_types_ + type_id;
    for (int i = 0; i < type->count; i++)
        _bsgfx_map(type_id, i);
}

BSGFXAPI void _bsgfx_type(
    bsgfx_TypeId id,
    int package_id,
    int version,
    const char* plural,
    const char* singular,
    size_t unmapped_size,
    size_t mapped_size,
    PFN_bsgfx_TypeMapper mapper,
    size_t unmapped_flexible_offset,
    size_t mapped_flexible_offset,
    size_t unmapped_flexible_size,
    size_t mapped_flexible_size)
{
    bs_Result result;
    bsgfx_Type* type = _bsgfx_types_ + id;
    //memset(type, 0, sizeof(bsgfx_Type));

    type->version = version;
    type->mapper = mapper;
    type->mapped_unit_size = mapped_size;
    type->unmapped_unit_size = unmapped_size;
    type->plural = plural;
    type->singular = singular;
    type->unmapped_flexible_offset = unmapped_flexible_offset;
    type->unmapped_flexible_size = unmapped_flexible_size;
    type->mapped_flexible_offset = mapped_flexible_offset;
    type->mapped_flexible_size = mapped_flexible_size;

    bs_Resource* resource;
    result = bs_loadResourceF(package_id, 0, BS_RESOURCE_BINARY, &resource, "levels/%s_%s", _bsgfx_current_scene_.name, plural);
    if (result != BS_RESULT_OK)
        return;

    type->package_id = package_id;
    bs_String* binary = resource->data;

    unsigned char* unmapped_data = NULL;

    bsgfx_TypeHeader* data = NULL;
    if (binary) {
        // binary->len--; // null terminator terminator
        assert(binary->len >= sizeof(bsgfx_TypeHeader));
        data = (bsgfx_TypeHeader*)binary->value;

        if (data->magic == BSGFX_TYPE_MAGIC) {
            bs_warnF("Invalid magic number for type \"%s\"\n", singular); // TODO: bsgfx warn

        }

        if (data->version != version && data->count > 0) {
            bs_warnF("Unsupported type version %d\n", data->version); // TODO: bsgfx warn
            return;
        }

        if ((data->count * sizeof(int) + sizeof(*data)) > binary->len) {
            bs_warnF("Type \"%s\" has corrupted data", singular);  // TODO: bsgfx warn
            return;
        }

        type->flexible_count = 0;
        type->count = data->count;
        type->capacity = BS_MAX(type->count, type->capacity);
        type->capacity = BS_MAX(type->capacity, 1);

        type->unmapped_accessors = bs_realloc(type->unmapped_accessors, type->capacity * sizeof(int));
        type->mapped_accessors = bs_realloc(type->mapped_accessors, type->capacity * sizeof(int));

        memset(type->unmapped_accessors, 0, type->capacity * sizeof(int));
        memset(type->mapped_accessors, 0, type->capacity * sizeof(int));

        memcpy(type->unmapped_accessors, data->accessors, data->count * sizeof(int));

        unmapped_data = (unsigned char*)(data->accessors + data->count);

        for (int i = 0, unmapped_offset = 0, mapped_offset = 0; i < data->count; i++) {
            int flexible_count = unmapped_flexible_offset == 0 ? 0 : _bsgfx_flexibleCountPointer(unmapped_flexible_offset, unmapped_data + unmapped_offset);
            type->mapped_accessors[i] = mapped_offset;
            type->flexible_count += flexible_count;
            unmapped_offset += unmapped_size + unmapped_flexible_size * flexible_count;
            mapped_offset += mapped_size + mapped_flexible_size * flexible_count;
        }

        assert(type->flexible_count == data->flexible_count);

        type->flexible_capacity = type->flexible_count;
    }

    size_t mapped_capacity = type->capacity * mapped_size + type->flexible_capacity * mapped_flexible_size;
    size_t unmapped_capacity = type->capacity * unmapped_size + type->flexible_capacity * unmapped_flexible_size;

    if (mapped_capacity != 0) {
        type->mapped = bs_realloc(type->mapped, mapped_capacity);
        memset(type->mapped, 0, mapped_capacity);

        type->unmapped = bs_realloc(type->unmapped, unmapped_capacity);
        size_t unmapped_count_capacity = type->count * unmapped_size + type->flexible_count * unmapped_flexible_size;

        if (unmapped_data)
            memcpy(type->unmapped, unmapped_data, unmapped_count_capacity);
    }

    if (type->unmapped) {
        for (int i = 0; i < type->count; i++)
            mapper(_bsgfx_getRaw(id, i), _bsgfx_get(id, i));
    }

//#ifndef _DEBUG
//    type->unmapped = bs_free(type->unmapped);
//#endif

    bs_free(binary);
    bs_infoF("Loaded %d %s\n", type->count, plural);
}