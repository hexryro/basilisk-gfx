
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
#include "../bsgfx_contracts.h"

BSMODAPI bsgfx_TypeId _bsmod_queryType(const char* plural) {
	for (int i = 0; i < BSGFX_TYPE_COUNT; i++) {
		if (strcmp(bsgfx_getType(i)->plural, plural) == 0)
			return i;
	}

	return BSGFX_TYPE_UNDEFINED;
}



/*=============================================================================
 * Type Editor
 *============================================================================*/

BSMODAPI void _bsmod_delete(bsgfx_TypeId type_id, int id) {
	//bsgfx_saveHistory(type_id);

	bsgfx_Type* type = bsgfx_getType(type_id);
	for (int i = id; i < type->count - 1; i++) {
		void* instance = bsgfx_get(type_id, i);
		void* raw_instance = bsgfx_getRaw(type_id, i);

		void* next_instance = bsgfx_get(type_id, i + 1);
		void* next_raw_instance = bsgfx_getRaw(type_id, i + 1);

		memcpy(instance, next_instance, type->mapped_unit_size);
		memcpy(raw_instance, next_raw_instance, type->unmapped_unit_size);
	}
	type->count--;
	_bsmod_deselectAll();

	_bsmod_saveTypeF(type_id, "Deleted %s", type->singular);
}

BSMODAPI void _bsmod_deleteSelected(bsgfx_TypeId type_id) {
	// bsgfx_saveHistory(type_id);

	bsgfx_Type* type = bsgfx_getType(type_id);
	int count = _bsmod_.selected_ids.count;
	int* ids = _bsmod_.selected_ids.data;

	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (ids[i] < ids[j]) {
				int temp = ids[i];
				ids[i] = ids[j];
				ids[j] = temp;
			}
		}
	}

	for (int i = 0; i < count; i++) {
		for (int j = ids[i]; j < type->count - 1; j++) {
			void* instance = bsgfx_get(type_id, j);
			void* raw_instance = bsgfx_getRaw(type_id, j);

			void* next_instance = bsgfx_get(type_id, j + 1);
			void* next_raw_instance = bsgfx_getRaw(type_id, j + 1);

			memcpy(instance, next_instance, type->mapped_unit_size);
			memcpy(raw_instance, next_raw_instance, type->unmapped_unit_size);
		}
		type->count--;
	}

	_bsmod_deselectAll();

	if (count == 1)
		_bsmod_saveTypeF(type_id, "Deleted %s", type->singular);
	else
		_bsmod_saveTypeF(type_id, "Deleted %d %s", count, type->plural);
}

/*
static int bs_comparePrefabZ(const bsgfx_RawPrefab* a, const bsgfx_RawPrefab* b) {
	if (a->position.z == b->position.z) return 0;
	else if (a->position.z < b->position.z) return -1;
	else return 1;
}

static int bs_compareAccessorZ(const int* a_id, const int* b_id) {
	bsgfx_Type* type = bsgfx_types + BSGFX_TYPE_PREFAB;
	bsgfx_RawPrefab* a = type->unmapped + *a_id;
	bsgfx_RawPrefab* b = type->unmapped + *b_id;

	return bs_comparePrefabZ(a, b);
}
*/

BSMODAPI bs_Result _bsmod_saveTypeN(bsgfx_TypeId id, char* comment, int comment_length) {
	bs_Result result;

	bsgfx_Type* type = bsgfx_getType(id);

	// _bsmod_.history = BS_I64_MAX; // ?

	bsgfx_TypeHeader* data;
	size_t size = sizeof(*data) + type->count * sizeof(int) + type->count * type->unmapped_unit_size + type->flexible_count * type->unmapped_flexible_size;

	if (size == 0) // TODO: bsmod warn
		return BS_RESULT_ZERO_ALLOC;

	data = bs_malloc(size);
	memset(data, 0, sizeof(*data));
	data->count = type->count;
	data->magic = BSGFX_TYPE_MAGIC;
	data->version = type->version;
	data->flexible_count = type->flexible_count;

	memcpy(data->accessors, type->unmapped_accessors, type->count * sizeof(int));
	memcpy(data->accessors + type->count, type->unmapped, type->count * type->unmapped_unit_size + type->flexible_count * type->unmapped_flexible_size);

	bs_ResourceType resource_type = 0;
	switch (id) {
	case BSGFX_TYPE_PRIMITIVE: resource_type = BSGFX_RESOURCE_PRIMITIVE; break;
	case BSGFX_TYPE_PREFAB: resource_type = BSGFX_RESOURCE_PREFAB; break;
	case BSGFX_TYPE_TILE: resource_type = BSGFX_RESOURCE_TILE; break;
	case BSGFX_TYPE_LIGHT: resource_type = BSGFX_RESOURCE_LIGHT; break;
	default:
		bs_warnF("Invalid type id %d\n", id); // TODO: bsmod warn
		return BS_RESULT_INVALID_TYPE;
	}

	bsgfx_remap(id); // debugging purposes

	// TODO: get application package name
	result = _bsmod_packResourceF(resource_type, data, size, _bsmod_applicationContentPath(), "levels/%s_%s", bsgfx_currentScene()->name, type->plural);
	// bs_saveFileF(data, size, "resources/levels/%s/%s.bin", bsgfx_fetchLevel(poser()->current_level)->name, type->plural);
	bs_free(data);
	if (result != BS_RESULT_OK)
		return result;

	bs_logWithTimestampN(BS_MESSAGE_INFO, comment, comment_length);

	return BS_RESULT_OK;
}

// remove if data is NULL, otherwise insert
static void* _bsmod_shiftFlexible(bsgfx_TypeId type_id, int id, void* data) {
	bsgfx_Type* type = bsgfx_getType(type_id);

	int unmapped_offset = 0, mapped_offset = 0;

	if (data && type->flexible_count >= type->flexible_capacity) {
		type->flexible_capacity += 128;

		int unmapped_capacity = type->capacity * type->unmapped_unit_size + type->flexible_capacity * type->unmapped_flexible_size;
		int mapped_capacity = type->capacity * type->mapped_unit_size + type->flexible_capacity * type->mapped_flexible_size;

		type->unmapped = bs_realloc(type->unmapped, unmapped_capacity);
		type->mapped = bs_realloc(type->mapped, mapped_capacity);
	}

	int dir = data ? 1 : -1;
	void* result = NULL;

	for (int i = 0; i <= id; i++) {
		int* unmapped_flexible_count = type->unmapped + unmapped_offset + type->unmapped_flexible_offset;
		int* mapped_flexible_count = type->mapped + mapped_offset + type->mapped_flexible_offset;

		unmapped_offset += type->unmapped_unit_size + *unmapped_flexible_count * type->unmapped_flexible_size;
		mapped_offset += type->mapped_unit_size + *mapped_flexible_count * type->mapped_flexible_size;

		if (i == id) {
			int unmapped_tail_size = type->count * type->unmapped_unit_size + type->flexible_count * type->unmapped_flexible_size - unmapped_offset;
			int mapped_tail_size = type->count * type->mapped_unit_size + type->flexible_count * type->mapped_flexible_size - mapped_offset;

			memmove(
				(char*)type->unmapped + unmapped_offset + type->unmapped_flexible_size,
				(char*)type->unmapped + unmapped_offset,
				unmapped_tail_size);

			memmove(
				(char*)type->mapped + mapped_offset + type->mapped_flexible_size,
				(char*)type->mapped + mapped_offset,
				mapped_tail_size);

			if (data)
				result = memcpy(
					(char*)type->unmapped + unmapped_offset,
					data,
					type->unmapped_flexible_size);

			(*unmapped_flexible_count) += dir;
			(*mapped_flexible_count) += dir;
		}
	}

	type->flexible_count += dir;

	for (int i = id + 1; i < type->count; i++) {
		type->unmapped_accessors[id] += type->unmapped_flexible_size * dir;
		type->mapped_accessors[id] += type->mapped_flexible_size * dir;
	}

	return result;
}

BSMODAPI void* _bsmod_addFlexible(bsgfx_TypeId type_id, int id, void* data) {
	bsgfx_Type* type = bsgfx_getType(type_id);

	void* result = _bsmod_shiftFlexible(type_id, id, data);

	bsgfx_map(type_id, id);

	return result;
}

BSMODAPI void* _bsmod_removeFlexible(bsgfx_TypeId type_id, int id) {
	bsgfx_Type* type = bsgfx_getType(type_id);

	void* result = _bsmod_shiftFlexible(type_id, id, NULL);

	bsgfx_map(type_id, id);

	return result;
}

BSMODAPI void* _bsmod_add(bsgfx_TypeId id, void* data) {
	bsgfx_Type* type = bsgfx_getType(id);

	if (type->count >= type->capacity) {
		type->capacity += 128;

		size_t mapped_capacity = type->capacity * type->mapped_unit_size + type->flexible_capacity * type->mapped_flexible_size;
		size_t unmapped_capacity = type->capacity * type->unmapped_unit_size + type->flexible_capacity * type->unmapped_flexible_size;

		size_t mapped_old_capacity = type->count * type->mapped_unit_size + type->flexible_count * type->mapped_flexible_size;
		size_t unmapped_old_capacity = type->count * type->unmapped_unit_size + type->flexible_count * type->unmapped_flexible_size;

		type->mapped = bs_realloc(type->mapped, mapped_capacity);
		type->unmapped = bs_realloc(type->unmapped, unmapped_capacity);
		type->unmapped_accessors = bs_realloc(type->unmapped_accessors, type->capacity * sizeof(int));
		type->mapped_accessors = bs_realloc(type->mapped_accessors, type->capacity * sizeof(int));

		memset(type->mapped + mapped_old_capacity, 0, mapped_capacity - mapped_old_capacity);
		memset(type->unmapped + unmapped_old_capacity, 0, unmapped_capacity - unmapped_old_capacity);
		memset(type->unmapped_accessors + type->count, 0, type->capacity * sizeof(int) - type->count * sizeof(int));
		memset(type->mapped_accessors + type->count, 0, type->capacity * sizeof(int) - type->count * sizeof(int));
	}

	//bs_warnF("Max number of %s exceeded!\n", type->plural);

	int* this = type->unmapped_accessors + type->count;
	int* last = this - 1;
	*this = type->count == 0 ? 0 : (*last + type->unmapped_unit_size + bsgfx_flexibleCount(id, type->count - 1));

	int* this_mapped = type->mapped_accessors + type->count;
	int* last_mapped = this_mapped - 1;
	*this_mapped = type->count == 0 ? 0 : (*last_mapped + type->mapped_unit_size + bsgfx_flexibleCount(id, type->count - 1));

	void* unmapped = bsgfx_getRaw(id, type->count);
	void* mapped = bsgfx_get(id, type->count);

	if (data)
		memcpy(unmapped, data, type->unmapped_unit_size);
	else
		memset(unmapped, 0, type->unmapped_unit_size); // unnecessary?

	type->mapper(unmapped, mapped);
	type->count++;

	return unmapped;
}



/*=============================================================================
 * Type Selection
 *============================================================================*/

BSMODAPI bool _bsmod_isSelected(bs_List* list, bsgfx_TypeId type, int id) {
	if (_bsmod_.selected_type != type)
		return false;

	for (int i = 0; i < list->count; i++) {
		int* this = bs_fetchUnit(list, i);
		if (*this == id)
			return true;
	}

	return false;
}

BSMODAPI void _bsmod_select(bs_List* list, bsgfx_TypeId type, int id) {
	if (_bsmod_.selected_type != type) {
		_bsmod_deselectAll();
		_bsmod_.selected_type = type;
	}

	if (_bsmod_isSelected(list, type, id))
		return;

	if (list == BSMOD_IDS)
		bs_infoF("Selected %s %d\n", bsgfx_getType(_bsmod_.selected_type)->singular, id);

	// bsgfx_highlightEditorTab("instance");

	//int max_count = bsgfx_count(type);
	//if (id >= max_count || id < 0)
	//	return bs_throwBasiliskF(BSX_OUT_OF_BOUNDS, "%s id %d (0-%d)", bsgfx_getType(type)->singular, id, max_count);

	bs_pushBack(list, &id);
}

static void _bsmod_clearTiles() {
	bs_Batch* batch = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_TILE)->batch;
	bs_Scope last = *bs_getScope();
	bs_setScope(&(bs_Scope) { .queue = bs_singleTimesQueue() });
	bs_unpushBatch(batch);
	bs_pushBatch(batch, BS_U32_MAX, BS_U32_MAX);
	bs_setScope(&last);
}

BSMODAPI void _bsmod_deselectAll() {
	if (_bsmod_.selected_ids.count != 0 || _bsmod_.selected_tiles.count != 0)
		bs_infoF("Deselected all %s\n", bsgfx_getType(_bsmod_.selected_type)->plural);

	if (_bsmod_.selected_type == BSGFX_TYPE_TILE)
		_bsmod_clearTiles();

	_bsmod_.selected_tiles.count = 0;
	_bsmod_.selected_ids.count = 0;
	_bsmod_.selected_type = BSGFX_TYPE_UNDEFINED;
	_bsmod_.edit_type = BSMOD_EDIT_UNDEFINED;
}

BSMODAPI void _bsmod_deselectRange(bs_List* list, int first, int count) {
	if (count > 0)
		bs_infoF("Deselected %s %d-%d\n", bsgfx_getType(_bsmod_.selected_type)->plural, first, (first + count));

	for (int i = first; i + count < list->count; i++) {
		int* this = bs_fetchUnit(list, i);
		int* next = bs_fetchUnit(list, i + count);
		*this = *next;
	}

	list->count -= count;

	if (list->count == 0)
		_bsmod_deselectAll();
}

BSMODAPI void _val_bsmod_deselectIndex(bs_List* list, int id) {
	BSGFX_VALIDATE(id >= 0,,);

	_bsmod_deselectIndex(list, id);
}

BSMODAPI void _bsmod_deselectIndex(bs_List* list, int id) {
	for (int i = id; i < list->count; i++) {
		int* this = bs_fetchUnit(list, i);
		int* next = bs_fetchUnit(list, i + 1);
		*this = *next;
	}

	bs_infoF("Deselected %s %d\n", bsgfx_getType(_bsmod_.selected_type)->singular, id);
	if (--list->count == 0)
		_bsmod_deselectAll();
}

BSMODAPI void _bsmod_deselect(bs_List* list, int id) {
	int start = -1;
	for (int i = 0; i < list->count; i++) {
		int* this = bs_fetchUnit(list, i);
		if (*this == id) {
			start = i;
			break;
		}
	}

	_bsmod_deselectIndex(list, start);
}

BSMODAPI int _bsmod_firstSelectedId(bs_List* list) {
	int* first = list->data;
	//	if (*first < 0 || (*first >= bsgfx_getType(_bsmod_.selected_type)->count))
	//		return -1;

	return *first;
}

BSMODAPI int _bsmod_lastSelectedId(bs_List* list) {
	int* first = list->data;
	//	if (first < 0 || (_bsmod_.selected_ids.count - 1) >= bsgfx_getType(_bsmod_.selected_type)->count)
	//		return -1;

	int* last = bs_fetchUnit(list, list->count - 1);
	return *last;
}



/*=============================================================================
 * Version Converters
 *============================================================================*/

 /**
  Tile version converter
  */
static void _bsmod_convertTileVersion1(bsgfx_TypeHeader* old_tiles, bsgfx_TypeHeader* new_tiles) {
	unsigned char* old_data = old_tiles->accessors + old_tiles->count;
	unsigned char* new_data = new_tiles->accessors + new_tiles->count;

	size_t offset = 0;
	for (int i = 0; i < old_tiles->count; i++) {
		bsgfx_RawTileV1* old_tile = old_data + old_tiles->accessors[i];
		bsgfx_RawTile* new_tile = new_data + offset;

		*new_tile = (bsgfx_RawTile){
			.axis = 0,
			.coords = { old_tile->coords.x, old_tile->coords.y },
			.flags = old_tile->flags,
			.primitive = old_tile->primitive,
			.texture_hash = old_tile->texture_hash,
		};

		new_tiles->accessors[i] = offset += sizeof(bsgfx_RawTile);
	}
}

static bs_Result _bsmod_convertTileVersion(int package_id, bsgfx_Scene* scene) {
	bs_Result result;

	bs_Package* package = bs_fetchUnit(bs_packages(), package_id);
	if (!package)
		return BS_RESULT_OUT_OF_BOUNDS;

	static bs_String* s;
	s = bs_stringF(s, "levels/%s_tiles", scene->name);

	bs_Resource* tiles;
	result = bs_loadResourceN(package_id, 0, &tiles, s->value, s->len);
	if (result != BS_RESULT_OK)
		return result;

	bsgfx_TypeHeader* old_tiles = tiles->data->value;
	if (old_tiles->version == BSGFX_TILE_VERSION) {
		bs_infoF("Tiles are up to date.\n");
		return BS_RESULT_OK;
	}

	size_t size =
		sizeof(bsgfx_TypeHeader) +
		old_tiles->count * sizeof(int) +
		old_tiles->count * sizeof(bsgfx_RawTile);

	bsgfx_TypeHeader* new_tiles = bs_malloc(size);
	memcpy(new_tiles, old_tiles, sizeof(bsgfx_TypeHeader));
	new_tiles->version = BSGFX_TILE_VERSION;

	switch (old_tiles->version) {
	case 1: _bsmod_convertTileVersion1(old_tiles, new_tiles); break;
	default:
		bs_warnF("Tile version %d converter\n", old_tiles->version); // TODO: BSMOD warn
	}

	result = _bsmod_packResourceN(BSGFX_RESOURCE_TILE, new_tiles, size, bs_fileName(package->path), s->value, s->len);
	bs_free(new_tiles);

	return BS_RESULT_OK;
}

/***/
BSMODAPI void _bsmod_ensureTypeVersionsAreUpToDate(int package_id) {
	_bsmod_iniPackage(package_id);

	bs_Result result = _bsmod_convertTileVersion(package_id, bsgfx_currentScene());
	if (!result)
		return;

	//bs_except(BSX_FAILED_TO_QUERY);
	//bs_Resource* primitives = bs_loadResource(package_id, (s = bs_stringF(s, "levels/%s_primitives", scene->name))->value, 0);
	//
	//bs_except(BSX_FAILED_TO_QUERY);
	//bs_Resource* prefabs = bs_loadResource(package_id, (s = bs_stringF(s, "levels/%s_prefabs", scene->name))->value, 0);
	//bs_except(0);

	_bsmod_savePackage(package_id);
}



/*=============================================================================
 * Hovering Pixel Data
 * TODO: move some of this somewhere else
 *============================================================================*/

BSMODAPI void _val_bsmod_copyHoveringDataToBuffer() {
	BSMOD_VALIDATE(bs_exists(BSGFX_RENDERERS, BSGFX_RENDERER_LO_RES),,);

	_bsmod_copyHoveringDataToBuffer();
}

BSMODAPI void _bsmod_copyHoveringDataToBuffer() {
	bs_vec2 cursor = bs_cursorPosition();

	bs_Renderer* renderer = bs_fetch(BSGFX_RENDERERS, BSGFX_RENDERER_LO_RES)->renderer;

	bs_ivec2 resolution = bs_resolution();
	bs_ivec2 pixel_resolution = BS_IV2(resolution.x / BSGFX_PIXEL_SCALE, resolution.y / BSGFX_PIXEL_SCALE);

	bs_vec2 p;
	bs_v2Mul(&cursor, &BS_IV2_TO_V2(resolution), &p);

	bs_ivec2 cursor_position = BS_IV2(p.x / BSGFX_PIXEL_SCALE, p.y / BSGFX_PIXEL_SCALE);

	if (bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS) &&
		bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_SCREENSHOT))
	{
		bs_Buffer* cursor_reads_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS)->buffer;
		bs_Buffer* tile_read_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_SCREENSHOT)->buffer;

		for (int i = 0; i < renderer->num_outputs; i++) {
			bs_Image* image = renderer->outputs[i].image;
			if (!(image->flags & BS_IMAGE_USAGE_TRANSFER_SRC_BIT))
				continue;

			bs_copyImageToBufferAsync(
				image,
				cursor_reads_buffer,
				0,
				BS_IMAGE_LAYOUT_GENERAL,
				i * 4,
				cursor_position,
				BS_IV2(1, 1));

			if (_bsmod_.queue.screenshot)
				bs_copyImageToBufferAsync(image, tile_read_buffer, 0, BS_IMAGE_LAYOUT_GENERAL, pixel_resolution.x * pixel_resolution.y * i * 4, BS_IV2(0, 0), pixel_resolution);
		}
	}
}

BSMODAPI void _bsmod_readHoveringInstanceData() {
	_bsmod_.hovering.instance_type = -1;
	_bsmod_.hovering.subtype = -1;

	for (int j = 0; j < BSGFX_INSTANCE_TYPE_COUNT; j++) {
		if (_bsmod_.hovering.flags & (1 << j)) {
			_bsmod_.hovering.instance_type = j;
			break;
		}
	}

	if (_bsmod_.hovering.instance_type != -1) {
		bsgfx_InstanceBuffer* instance = bs_bufferMap(poser()->instance_buffers[_bsmod_.hovering.instance_type]);
		instance += _bsmod_.hovering.index;
		_bsmod_.hovering.instance_id = instance->header.id;

		bs_Buffer* metadata_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_INSTANCE_METADATA)->buffer;
		bsgfx_InstanceMetadata* metadata = bs_bufferMap(metadata_buffer);

		for (int j = 0; j < metadata->subtypes_count; j++) {
			if (metadata->instance_subtypes[j].instance_type != _bsmod_.hovering.instance_type) continue;

			struct bsgfx_InstanceSubtypeMetadata* subtype_metadata = metadata->instance_subtypes + j;

			if (_bsmod_.hovering.index >= metadata->instance_subtypes[j].instance_offset &&
				_bsmod_.hovering.index < (metadata->instance_subtypes[j].instance_offset + metadata->instance_subtypes[j].instance_count)) {

				_bsmod_.hovering.subtype = j;
				break;
			}
		}
	}
}

 /**
  Read Hovering Vertex
  */
BSMODAPI void _val_bsmod_readHoveringVertex() {
	BSMOD_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS),,);

	_bsmod_readHoveringVertex();
}

BSMODAPI void _bsmod_readHoveringVertex() {
	if (_bsmod_.hovering.instance_type < 0)
		return;

	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS)->buffer;

	bs_U32* data = buffer->_->data ? bs_bufferMap(buffer) : bs_mapBuffer(buffer, buffer->num_bytes);

	bsgfx_InstanceBuffer* instance = bs_bufferMap(poser()->instance_buffers[_bsmod_.hovering.instance_type]);

	bool is_unselected_primitive = _bsmod_.hovering.flags & BSGFX_ID_IS_PRIMITIVE && !_bsmod_isSelected(BSMOD_IDS, BSGFX_TYPE_PRIMITIVE, instance->header.id);
	if (is_unselected_primitive)
		_bsmod_.hovering.closest_primitive = _bsmod_.hovering.instance_id;

	bs_RGBA position = *(bs_RGBA*)(data + BSGFX_LO_SUBPASS_0_OUT_POSITION_LOCAL);
	bs_vec3 normal = BS_V3((position.r / 255.0 - 0.5) * 2.0, (position.g / 255.0 - 0.5) * 2.0, (position.b / 255.0 - 0.5) * 2.0);
	normal.x = (normal.x == 0.0f) ? 0.0f : (normal.x > 0.0f ? 1.0f : -1.0f);
	normal.y = (normal.y == 0.0f) ? 0.0f : (normal.y > 0.0f ? 1.0f : -1.0f);
	normal.z = (normal.z == 0.0f) ? 0.0f : (normal.z > 0.0f ? 1.0f : -1.0f);

	if (is_unselected_primitive)
		_bsmod_.hovering.closest_vertex = normal;
}

 /**
  Read Hovering Outputs
  */

BSMODAPI void _val_bsmod_readHoveringOutputs() {
	BSMOD_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS), , );

	_bsmod_readHoveringOutputs();
}

BSMODAPI void _bsmod_readHoveringOutputs() {
	_bsmod_.hovering.color = BS_RGBA(0, 0, 0, 0);
	_bsmod_.hovering.normal = BS_V3(0.0, 0.0, 0.0);
	_bsmod_.hovering.flags = _bsmod_.hovering.index = 0;

	bs_Buffer* buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_LO_RES_CURSOR_READS)->buffer;

	bs_U32* data = buffer->_->data ? bs_bufferMap(buffer) : bs_mapBuffer(buffer, buffer->num_bytes);

	bs_RGBA* normal_color = data + BSGFX_LO_SUBPASS_0_OUT_NORMAL;
	_bsmod_.hovering.normal = BS_V3((float)normal_color->r / 255.0, (float)normal_color->g / 255.0, (float)normal_color->b / 255.0);
	_bsmod_.hovering.color = *(bs_RGBA*)(data + BSGFX_LO_SUBPASS_0_OUT_COLOR);
	_bsmod_.hovering.index = data[BSGFX_LO_SUBPASS_0_OUT_INDEX];
	_bsmod_.hovering.flags = data[BSGFX_LO_SUBPASS_0_OUT_FLAGS];
}

BSMODAPI void _bsmod_editSelectedType() {
	if (_bsmod_.selected_type == BSGFX_TYPE_UNDEFINED)
		return;

	bsgfx_Type* type = bsgfx_getType(_bsmod_.selected_type);

	if (bs_keyDownOnce(BS_KEY_DELETE)) {
		_bsmod_deleteSelected(_bsmod_.selected_type);
	}
}

BSMODAPI void _bsmod_selectHoveringTypes() {
	if (_bsmod_.hovering.billboard) {
		return;
	}

	bool select_tile = false;
	if (bs_leftClickOnce()) {
		if (_bsmod_.selected_type == BSGFX_TYPE_PRIMITIVE && _bsmod_.selected_ids.count && _bsmod_.hovering.primitive == _bsmod_firstSelectedId(BSMOD_IDS)) {
			select_tile = true;
		}
		else if (_bsmod_.selected_type == BSGFX_TYPE_TILE) {
			if (bs_keyDown(BS_KEY_ALT) && !bs_keyDown(BS_KEY_LEFT_CONTROL))
				select_tile = true;
			if (bs_keyDown(BS_KEY_LEFT_SHIFT))
				select_tile = true;
		}
	}

	if (select_tile && !bs_keyDown(BS_KEY_LEFT_SHIFT)) {
		if (_bsmod_.selected_tile_axis != _bsmod_.hovering.tile_axis)
			_bsmod_deselectAll();

		_bsmod_.selected_tile_primitive = _bsmod_.hovering.primitive;
		_bsmod_.selected_tile_axis = _bsmod_.hovering.tile_axis;

		if (_bsmod_isSelected(BSMOD_TILE_IDS, BSGFX_TYPE_TILE, _bsmod_.hovering.tile))
			_bsmod_deselect(BSMOD_TILE_IDS, _bsmod_.hovering.tile);
		else
			_bsmod_select(BSMOD_TILE_IDS, BSGFX_TYPE_TILE, _bsmod_.hovering.tile);
	}

	_bsmod_.hovering.tile_axis = _bsmod_.hovering.primitive = _bsmod_.hovering.tile = -1;

	if (_bsmod_.hovering.flags & BSGFX_ID_IS_PRIMITIVE) {
		bs_U32 tile = bsgfx_extract24(_bsmod_.hovering.index);
		bs_U32 axis = bsgfx_extract8(_bsmod_.hovering.index);

		for (int i = 0; i < bsgfx_count(BSGFX_TYPE_PRIMITIVE); i++) {
			bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);
			if (tile >= primitive->first_tile && tile < primitive->last_tile) {
				if (bs_leftClickOnce() && !select_tile) {
					_bsmod_deselectAll();
					_bsmod_select(BSMOD_IDS, BSGFX_TYPE_PRIMITIVE, i);
				}

				_bsmod_.hovering.primitive = i;
				_bsmod_.hovering.tile_axis = axis;
				_bsmod_.hovering.tile = tile;

				break;
			}
		}
	}

	if (_bsmod_.hovering.flags & BSGFX_ID_IS_PREFAB) {
		//bsgfx_Prefab* prefab = bsgfx_get(BSGFX_TYPE_PREFAB, _bsmod_.hovering.index);

		if (bs_leftClickOnce()) {
			if (!bs_keyDown(BS_KEY_ALT) || bs_keyDown(BS_KEY_LEFT_CONTROL))
				_bsmod_deselectAll();

			_bsmod_select(BSMOD_IDS, BSGFX_TYPE_PREFAB, _bsmod_.hovering.instance_id);
		}
	}

	if (bs_leftClickOnce() && _bsmod_.selected_type == BSGFX_TYPE_TILE && bs_keyDown(BS_KEY_LEFT_SHIFT)) {
		bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, _bsmod_.selected_tile_primitive);

		int first_tile = _bsmod_firstSelectedId(BSMOD_TILE_IDS);

		int first_tile_axis;
		bsgfx_tileAxis(primitive, first_tile, &first_tile_axis);

		if (first_tile_axis == _bsmod_.hovering.tile_axis && _bsmod_.hovering.tile >= 0 && first_tile >= 0) {

			bs_ivec2 start, end;
			bsgfx_tileCoordinate(primitive, _bsmod_.hovering.tile_axis, _bsmod_.hovering.tile, &start);
			bsgfx_tileCoordinate(primitive, first_tile_axis, first_tile, &end);

			if (start.x != BS_I32_MAX && end.x != BS_I32_MAX) {
				if (start.x > end.x) {
					float temp = start.x;
					start.x = end.x;
					end.x = temp;
				}
				if (start.y > end.y) {
					float temp = start.y;
					start.y = end.y;
					end.y = temp;
				}

				for (int x = start.x; x < end.x + 1; x++) {
					for (int y = start.y; y < end.y + 1; y++) {
						bs_U32 index;
						bsgfx_tileIndex(primitive, _bsmod_.hovering.tile_axis, x, y, &index);

						_bsmod_select(BSMOD_TILE_IDS, BSGFX_TYPE_TILE, index);
					}
				}
			}
		}
	}

	 /**
	  For each selected tile, get its primitive and select all tiles on that primitive
	  */
	if (_bsmod_.selected_type == BSGFX_TYPE_TILE && bs_keyDown(BS_KEY_LEFT_CONTROL) && bs_keyDownOnce(BS_KEY_A)) {
		static bs_List primitives_to_select = { .unit_size = sizeof(int) , .increment = 256 };
		bs_seekList(&primitives_to_select, 0);

		const int primitives_count = bsgfx_count(BSGFX_TYPE_PRIMITIVE);

		for (int i = 0; i < primitives_count; i++) {
			bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, i);

			for (int j = 0; j < _bsmod_.selected_tiles.count; j++) {
				int tile_id = *(int*)bs_fetchUnit(&_bsmod_.selected_tiles, j);

				if (tile_id >= primitive->first_tile && tile_id <= primitive->last_tile) {
					bs_pushBack(&primitives_to_select, &i);
					break;
				}
			}
		}

		for (int i = 0; i < primitives_to_select.count; i++) {
			int primitive_id = *(int*)bs_fetchUnit(&primitives_to_select, i);
			bsgfx_Primitive* primitive = bsgfx_get(BSGFX_TYPE_PRIMITIVE, primitive_id);

			for (int j = primitive->first_tile; j <= primitive->last_tile; j++) {
				int axis;
				bsgfx_tileAxis(primitive, j, &axis);

				if (axis == _bsmod_.selected_tile_axis)
					_bsmod_select(BSMOD_TILE_IDS, BSGFX_TYPE_TILE, j);
			}

			break;
		}
	}

	if (bs_leftClickOnce()) {
		_bsmod_.ui_blocked = true;
	}

	//printf("%d, prim %d, tile %d\n", _bsmod_.hovering.index, _bsmod_.hovering.primitive, _bsmod_.hovering.tile);
}
