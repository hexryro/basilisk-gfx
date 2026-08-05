
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
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb_rect_pack/stb_rect_pack.h>

static bs_List _bsmod_string_pool = { .unit_size = sizeof(bs_StringPoolEntry), .increment = 64 };

struct bsmod_Hook {
	char* path;
	char* function;
	char* package;
	char* prefix;
	bool call_once;
	bs_DateTime last_modified;
	bs_List entries;
};

// todo make this reloadable
static bs_List* _bsmod_loadHooks() {
	bs_Result result;

	static bs_List hooks = { .unit_size = sizeof(struct bsmod_Hook), .increment = 16 };
	if (hooks.capacity)
		return &hooks;

	bs_Json json;
	result = bs_loadJsonN(&json, BS_CONSTANT_STRING(BSMOD_HOOKS_PATH));
	if (result != BS_RESULT_OK)
		return NULL;

	bs_JsonValue value = bs_fetchJsonN(&json, BS_JSON_ARRAY, BS_CONSTANT_STRING("$"));

	//static bs_String* last_modified;

	for (int i = 0; i < value.size; i++) {
		bs_Json root = bs_jsonRoot(&json, value.as_array.as_objects[i]);

		//last_modified = bs_stringF(last_modified, "%02d-%02d-%02d %02d:%02d:%02d", m.years, m.months, m.days, m.hours, m.minutes, m.seconds);

		char* prefix = bs_fetchJsonN(&root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("prefix")).as_string;
		struct bsmod_Hook dir = {
			.path = strdup(bs_fetchJsonN(&root, BS_JSON_STRING, BS_CONSTANT_STRING("path")).as_string),
			.function = strdup(bs_fetchJsonN(&root, BS_JSON_STRING, BS_CONSTANT_STRING("function")).as_string),
			.package = strdup(bs_fetchJsonN(&root, BS_JSON_STRING, BS_CONSTANT_STRING("package")).as_string),
			.call_once = bs_fetchJsonN(&root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("callOnce")).as_bool,
			.prefix = prefix ? strdup(prefix) : "",
			.entries = bs_list(sizeof(char*), 16),
		};

		bs_JsonValue entries = bs_fetchJsonN(&root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("entries"));
		for (int i = 0; i < entries.size; i++) {
			char* string = entries.as_array.as_strings[i];
			string = bs_checkStringPool(&_bsmod_string_pool, string);
			bs_pushBack(&dir.entries, &string);
		}

		bs_JsonValue last_modified = bs_fetchJsonN(&root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("lastModified"));
		if (last_modified.found && last_modified.type == BS_JSON_STRING) {
			sscanf(last_modified.as_string, "%u-%u-%u %u:%u:%u",
				&dir.last_modified.years, &dir.last_modified.months, &dir.last_modified.days,
				&dir.last_modified.hours, &dir.last_modified.minutes, &dir.last_modified.seconds);
		}

		bs_pushBack(&hooks, &dir);
	}

	bs_destroyJson(&json);

	return &hooks;
}

static void _bsmod_saveHooks(bs_List* hooks) {
	bs_Result result;

	bs_Json json = bs_emptyJson();
	bs_ensureJsonMutable(&json);

	for (int i = 0; i < hooks->count; i++) {
		struct bsmod_Hook* dir = bs_fetchUnit(hooks, i);
		bs_ensureJsonF(&json, bs_jsonValue(dir->path), "$[%d].path", i);
		bs_ensureJsonF(&json, bs_jsonValue(dir->function), "$[%d].function", i);
		bs_ensureJsonF(&json, bs_jsonValue(dir->package), "$[%d].package", i);
		bs_ensureJsonF(&json, bs_jsonValue(dir->prefix), "$[%d].prefix", i);
		bs_ensureJsonF(&json, bs_jsonValue(dir->call_once), "$[%d].callOnce", i);
		bs_ensureJsonF(&json, bs_jsonValue(dir->last_modified), "$[%d].lastModified", i);

		bs_JsonValue entries = bs_jsonArray(BS_JSON_STRING, dir->entries.data, dir->entries.count);
		bs_ensureJsonF(&json, entries, "$[%d].entries", i);
	}

	char* data;
	result = bs_saveJson(&json, BS_JSON_PRETTY, &data);
	bs_destroyJson(&json);
	if (result != BS_RESULT_OK)
		return;

	result = bs_saveFileN(data, strlen(data), BS_CONSTANT_STRING(BSMOD_HOOKS_PATH));
	bs_free(data);
	if (result != BS_RESULT_OK)
		return;
}



  /*==============================================================================
   * Hooks
   * Definition needs BSMODAPI
   *============================================================================*/

BSMODAPI bs_Result _bsmod_onPackBindings() {
	bs_Result result;

	int descriptors_count = 0;
	int bindings_count = 0;
	int bind_sets_count = 0;

	bool processed_bind_sets[BS_MAX_NUM_BIND_SETS] = { 0 };

	bs_foreachJson(&_bsmod_.bindings_json, e) {
		if (e.value.type != BS_JSON_OBJECT)
			continue;

		bs_Json root = bs_jsonRoot(&_bsmod_.bindings_json, e.value.as_object);

		descriptors_count += bs_fetchJsonN(&root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("count")).as_number;
		int bind_set = bs_fetchJsonN(&root, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("set")).as_number;

		BSMOD_VALIDATE(bind_set >= 0, BS_RESULT_VALIDATION_ERROR,);
		BSMOD_VALIDATE(bind_set < BS_MAX_NUM_BIND_SETS, BS_RESULT_VALIDATION_ERROR,);

		if (!processed_bind_sets[bind_set])
			bind_sets_count++;

		processed_bind_sets[bind_set] = true;
		bindings_count++;
	};

	bs_ensureJsonN(&_bsmod_.bindings_json, bs_jsonValue(bindings_count), BS_CONSTANT_STRING("bindingsCount"));
	bs_ensureJsonN(&_bsmod_.bindings_json, bs_jsonValue(bind_sets_count), BS_CONSTANT_STRING("bindSetsCount"));
	bs_ensureJsonN(&_bsmod_.bindings_json, bs_jsonValue(descriptors_count), BS_CONSTANT_STRING("descriptorsCount"));

	char* raw;
	result = bs_saveJson(&_bsmod_.bindings_json, BS_JSON_PRETTY, &raw);
	if (result != BS_RESULT_OK)
		return result;

	result = _bsmod_packResourceN(BS_RESOURCE_BINARY, raw, strlen(raw), BSGFX_CONTENT_PATH, BS_CONSTANT_STRING("bindings"));
	bs_free(raw);
	if (result != BS_RESULT_OK)
		return result;

	return BS_RESULT_OK;
}

BSMODAPI void _bsmod_onConvertFont(bsmod_TrackParams params) {
	bsmod_AtlasPacker packer = _bsmod_createAtlasPacker();

	bsmod_UnicodeBlockRange ranges[] = {
		{
			.block = BSGFX_UNICODE_BLOCK_BASIC_LATIN,
			.offset = 0,
			.count = 0x007F - 0,
			.size = 1,
			.rasterize = true,
		}
	};

	int ranges_count = sizeof(ranges) / sizeof(*ranges);

	int pt_sizes[] = { 11 };

	int pt_sizes_count = sizeof(pt_sizes) / sizeof(*pt_sizes);

	bsmod_packFont(params.package, params.path, ranges, ranges_count, pt_sizes, pt_sizes_count, params.path, strlen(params.path));
}

static bs_Result _bsmod_onPackAtlasTexture(bs_FileInfo info, bsmod_AtlasPacker* packer) {
	char* name = bs_fileName(info.path);
	char* ext = bs_fileExtension(name);

	size_t size = 0;

	bs_PngData png_data;
	if (bs_loadPng(info.path, 4, &png_data) == BS_RESULT_OK) {
		ext[-1] = '\0';
		_bsmod_packAtlasTexture(packer, png_data.data, png_data.width, png_data.height, 0, name);
		ext[-1] = '.';
	}

	return BS_RESULT_OK;
}

BSMODAPI void _bsmod_onPackAtlas(bsmod_TrackParams params) {
	bsmod_AtlasPacker packer = _bsmod_createAtlasPacker();

	char* file_name = bs_fileName(params.path);
	char* extension = bs_fileExtension(params.path);

	file_name[-1] = '\0';
	char* directory_name = bs_fileName(params.path); // hacky
	bs_foreachFile(_bsmod_onPackAtlasTexture, &packer, params.path);

	extension[-1] = '\0';
	_bsmod_packAtlas(&packer, 1024, 1024, 4, params.package, directory_name, true);
	extension[-1] = '.';
	file_name[-1] = '/';
}

BSMODAPI void _bsmod_onPackModels(bsmod_TrackParams params) {
	bs_Result result;

	bs_String* glb = NULL;

	char* ext = bs_fileExtension(params.path);
	char* name = bs_fileName(params.path);
	if (strcmp(ext, "gltf") == 0) {
		bs_infoF("Converting \"%s\" to glb\n", params.path);

		bs_String* gltf;
		result = bs_loadFile(&gltf, params.path);
		if (result != BS_RESULT_OK)
			return;
		gltf->len--; // null terminator TERMINATORRR

		bs_Json json;
		result = bs_json(&json, gltf->value, gltf->len);
		if (result != BS_RESULT_OK) {
			bs_free(gltf);
			return;
		}

		char* uri = bs_fetchJsonN(&json, BS_JSON_STRING, BS_CONSTANT_STRING("buffers[0].uri")).as_string;

		char* file_name = bs_fileName(params.path);
		char* directory = "";

		if (file_name != params.path) {
			directory = params.path;
			file_name[-1] = '\0';
		}

		bs_String* bin;
		result = bs_loadFileF(&bin, "%s/%s", directory, uri);
		if (result != BS_RESULT_OK) {
			bs_free(gltf);
			bs_destroyJson(&json);
			return;
		}

		if (file_name != params.path)
			file_name[-1] = '/';

		struct {
			bs_U32 length;
			bs_U32 type;
			bs_String* data;
		} chunks[] = {
			{
				.type = 0x4E4F534A,
				.length = gltf->len,
				.data = gltf,
			},
			{
				.type = 0x004E4942,
				.length = bin->len,
				.data = bin,
			}
		};
		const int chunk_size = sizeof(bs_U32) * 2;
		const int chunks_count = 2;

		struct {
			bs_U32 magic;
			bs_U32 version;
			bs_U32 length;
		} header = {
			.magic = 0x46546C67,
			.length = sizeof(header),
		};

		for (int i = 0; i < chunks_count; i++)
			header.length += chunks[i].length + chunk_size;

		glb = bs_stringAlloc(glb, header.length);

		char* offset = glb->value;
		memcpy(offset, &header, sizeof(header));
		offset += sizeof(header);

		for (int i = 0; i < chunks_count; i++) {
			memcpy(offset, chunks + i, chunk_size);
			offset += chunk_size;
			memcpy(offset, chunks[i].data->value, chunks[i].length);
			offset += chunks[i].length;
		}

		glb->len = header.length;

		bs_free(gltf);
		bs_free(bin);
		bs_destroyJson(&json);
	}
	else if (!strcmp(ext, "glb") == 0) {
		bs_warnF("Unknown model format \"%s\"\n", params.path);
		return;
	}
	else {
		result = bs_loadFile(&glb, params.path);
		if (result != BS_RESULT_OK)
			return;
	}

	result = _bsmod_packResourceF(BS_RESOURCE_MODEL, glb->value, glb->len, params.package, "models/%.*s", strlen(name) - strlen(ext) - 1, name);
	bs_free(glb);
	if (result != BS_RESULT_OK)
		return;
}

BSMODAPI void _bsmod_onPackBinary(bsmod_TrackParams params) {
	bs_Result result;

	bs_String* data;
	result = bs_loadFile(&data, params.path);
	if (result != BS_RESULT_OK)
		return;

	char* ext = bs_fileExtension(params.path);
	ext[-1] = '\0';
	result = _bsmod_packResourceF(BS_RESOURCE_BINARY, data->value, data->len, params.package, "%s%s", params.prefix, bs_fileName(params.path));
	ext[-1] = '.';
	bs_free(data);
	if (result != BS_RESULT_OK)
		return;
}

BSMODAPI void _bsmod_onPackTextureArray(bsmod_TrackParams params) {
	char* file_name = bs_fileName(params.path);

	file_name[-1] = '\0';
	_bsmod_packImageDirectory(params.path, params.package, params.prefix); // TODO: prefix will change to name prolly
	file_name[-1] = '/';
}



  /*==============================================================================
   * Tracker
   *============================================================================*/

static bs_Result _bsmod_findLastModifiedFile(bs_FileInfo info, struct { bs_DateTime original_date; bs_DateTime date; const bs_List* added_entries; bs_List* changed_entries; bs_List* entries; }*out) {
	bs_Result result;

	bs_DateTime date_time;
	result = bs_fileModifiedDate(&date_time, info.path);
	if (result != BS_RESULT_OK)
		return BS_RESULT_OK; // keep the iteration going

	char* cached = bs_checkStringPool(&_bsmod_string_pool, info.path);
	bs_pushBack(out->entries, &cached);

	if (bs_isLaterThan(&date_time, &out->original_date)) {
		if (bs_isLaterThan(&date_time, &out->date)) {
			out->date = date_time;
		}

		bs_pushBack(out->changed_entries, &cached);
	}

	return BS_RESULT_OK;
}

static bs_Result _bsmod_findLastModifiedDirectory(bs_FileInfo info, struct { bs_DateTime date; const bs_List* added_entries; bs_List* changed_entries; bs_List* entries; }*result) {
	bs_foreachFile(_bsmod_findLastModifiedFile, result, info.path);
	return BS_RESULT_OK;
}

static void _bsmod_trackDirectoryDifferences(const bs_List* changed, const bs_List* a, const bs_List* b, bs_List* out_differences) {
	for (int i = 0; i < a->count; i++) {
		char* new_entry = *(char**)bs_fetchUnit(a, i);

		bool found = false;
		for (int j = 0; j < b->count; j++) {
			char* old_entry = *(char**)bs_fetchUnit(b, j);

			if (new_entry == old_entry) {
				found = true;
				break;
			}
		}

		if (!found && !bs_listContains(changed, &new_entry))
			bs_pushBack(out_differences, &new_entry);
	}
}

static bool _bsmod_isFile(const char* path) {
	char* dot = strrchr(path, '.');
	if (!dot || dot == path || dot[1] == '/' || dot[1] == '\\') {
		return false;
	}
	return true;
}

BSMODAPI void _bsmod_onTrack() {
	static bs_String* last;
	bs_String* cwd = bs_workingDirectory();
	last = bs_stringN(last, cwd->value, cwd->len);

	//static float timer = 1.0;
	//timer += bs_deltaTime();
	//if (timer < 1.0)
	//	return;
	//else
	//	timer = 0.0;

	bs_infoF(BS_PRINT_COLOR("track\n", BS_PRINT_RED));

	bs_List* hooks = _bsmod_loadHooks();
	if (!hooks)
		return;

	static bool reload_all = false; // temp
	for (int i = 0; i < hooks->count; i++) {
		struct bsmod_Hook* dir = bs_fetchUnit(hooks, i);

		if (reload_all)
			bs_logSectionF("Directory \"%s\"", dir->path);
		if (_bsmod_isFile(dir->path)) {

			bs_DateTime last_modified;
			if (bs_fileModifiedDate(&last_modified, dir->path) != BS_RESULT_OK) {
				continue;
			}

			if (reload_all || bs_isLaterThan(&last_modified, &dir->last_modified)) {
				dir->last_modified = last_modified;

				FARPROC function = GetProcAddress(_bsmod_.module, dir->function);
				if (function) {
					function((bsmod_TrackParams) {
						.path = dir->path,
						.prefix = dir->prefix,
						.package = dir->package,
						.compile_references = true,
					});
				}

				_bsmod_saveHooks(hooks);
			}
		}
		else {
			static bs_List changed_entries = { .unit_size = sizeof(char*), .increment = 16 };
			static bs_List entries = { .unit_size = sizeof(char*), .increment = 16 };
			static bs_List added_entries = { .unit_size = sizeof(char*), .increment = 4 };
			static bs_List removed_entries = { .unit_size = sizeof(char*), .increment = 4 };

			changed_entries.count = entries.count = added_entries.count = removed_entries.count = 0;
			struct {
				bs_DateTime original_date;
				bs_DateTime date;
				const bs_List* added_entries;
				bs_List* changed_entries;
				bs_List* entries;
			} result = {
				.original_date = dir->last_modified,
				.date = dir->last_modified,
				.added_entries = &added_entries,
				.changed_entries = &changed_entries,
				.entries = &entries,
			};

			bs_foreachFile(_bsmod_findLastModifiedFile, &result, dir->path);
			bs_foreachDirectory(_bsmod_findLastModifiedDirectory, &result, dir->path); // TODO: this blows up the stack
			_bsmod_trackDirectoryDifferences(&changed_entries, result.entries, &dir->entries, &added_entries);
			_bsmod_trackDirectoryDifferences(&changed_entries, &dir->entries, result.entries, &removed_entries);

			bool later = bs_isLaterThan(&result.date, &dir->last_modified);
			bool changed = added_entries.count > 0 || removed_entries.count > 0;

			// TODO: this code is getting pretty ugly

			if (reload_all) {
				FARPROC function = GetProcAddress(_bsmod_.module, dir->function);
				if (function) {
					int count = dir->call_once ? bs_clamp(result.entries->count, 0, 1) : result.entries->count;

					for (int j = 0; j < count; j++) {
						char* path = *(char**)bs_fetchUnit(result.entries, j);
						function((bsmod_TrackParams) {
							.package = dir->package,
							.path = path,
							.prefix = dir->prefix,
							.compile_references = false,
						});
					}
				}
			} else if (later || changed) {
				dir->last_modified = result.date;
				// dir->entries = result.entries->count;

				FARPROC function = GetProcAddress(_bsmod_.module, dir->function);
				if (function) {
					int count = dir->call_once ? bs_clamp(result.changed_entries->count, 0, 1) : result.changed_entries->count;

					for (int j = 0; j < count; j++) {
						char* path = *(char**)bs_fetchUnit(result.changed_entries, j);
						function((bsmod_TrackParams) {
							.package = dir->package,
							.path = path,
							.prefix = dir->prefix,
							.compile_references = true,
						});
					}
				}
				else {
					if (_bsmod_.module)
						bs_warnF("Changes found in \"%s\", but callback function \"%s\" does not exist\n", dir->path, dir->function);
					else
						bs_warnF("Changes found in \"%s\", but basilisk-mod.dll has not been loaded\n", dir->package);
				}

				if (changed && function) {
					bsmod_TrackParams params = {
						.package = dir->package,
						.prefix = dir->prefix,
						.compile_references = true,
					};

					int added_count = added_entries.count, removed_count = removed_entries.count;
					if (dir->call_once) {
						added_count = bs_clamp(added_count, 0, 1);
						removed_count = added_count > 0 ? 0 : bs_clamp(removed_count, 0, 1);
					}

					for (int j = 0; j < added_count; j++) {
						params.path = *(char**)bs_fetchUnit(&added_entries, j);
						function(params);
					}

					for (int j = 0; j < removed_count; j++) {
						params.path = *(char**)bs_fetchUnit(&removed_entries, j);
						function(params);
					}
				}

				bs_ensureSize(&dir->entries, dir->entries.count = result.entries->count);
				for (int j = 0; j < result.entries->count; j++) {
					char* path = *(char**)bs_fetchUnit(result.entries, j);
					char** result = bs_fetchUnit(&dir->entries, j);
					*result = path;
				}

				_bsmod_saveHooks(hooks);
			}
		}
	}

	reload_all = false;

	for (int i = 0; i < _bsmod_packages()->count; i++)
		bsmod_savePackage(i);
}