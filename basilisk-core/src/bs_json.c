
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

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include <basilisk-core.h>
#include <bs_internal.h>
#include <yyjson/yyjson.h>

BSAPI bs_Json _bs_jsonRoot(bs_Json* json, bs_JsonObject obj) {
	void* doc;
	if (!json) {
		doc = yyjson_mut_doc_new(NULL);
		yyjson_mut_doc_set_root(doc, obj);
	}
	else
		doc = json->doc;

	return (bs_Json) {
		.is_mutable = json ? json->is_mutable : true,
		.doc = doc,
		.as_object = obj,
	};
}

 /**
  TODO:
  if _bs_jsonRoot(root, ...) is called before this, "root" will become a dangling pointer
  */
BSAPI void _bs_ensureJsonMutable(bs_Json* root) {
	if (!root->is_mutable) {
		root->is_mutable = true;
		root->doc = yyjson_doc_mut_copy(root->doc, NULL);
		root->as_object = yyjson_mut_doc_get_root(root->doc);
	}
}

BSAPI bs_Json _bs_jsonCopy(const bs_Json* root) {
	bs_Json json = {
		.is_mutable = true,
		.doc = root->is_mutable ?
			yyjson_mut_doc_mut_copy(root->doc, NULL) :
			yyjson_doc_mut_copy(root->doc, NULL),
	};

	json.as_object = yyjson_mut_doc_get_root(json.doc);

	return json;
}

BSAPI bs_Result _bs_saveJson(bs_Json* json, bs_SaveJsonBits flags, char** out) {
	size_t size = 0;
	yyjson_write_err error = { 0 };
	char* result = json->is_mutable ?
		yyjson_mut_write_opts(json->doc, flags, NULL, &size, &error) :
		yyjson_write_opts(json->doc, flags, NULL, &size, &error);

	if (error.code) {
		_bs_warnF("Failed to save JSON: %s", error.msg);
		return BS_RESULT_FAILED_TO_WRITE;
	}

	*out = result;
	return BS_RESULT_OK;
}

BSAPI bs_Json _bs_emptyJson() {
	yyjson_doc* doc = yyjson_read("{}", 2, 0);

	return (bs_Json) {
		.doc = doc,
		.as_object = yyjson_doc_get_root(doc),
	};
}

BSAPI bs_Json _bs_emptyJsonArray() {
	yyjson_doc* doc = yyjson_read("[]", 2, 0);

	return (bs_Json) {
		.doc = doc,
		.as_object = yyjson_doc_get_root(doc),
	};
}

BSAPI bs_Result _bs_json(char* raw, int len, bs_Json* out_json) {
	yyjson_read_err err;
	yyjson_doc* doc = yyjson_read_opts(raw, len, 0, NULL, &err);

	bs_Json json = {
		.doc = doc,
		.as_object = yyjson_doc_get_root(doc),
	};

	if (!json.doc) {
		BS_WARN_YYJSON_ERROR("yyjson_read_opts", err.code, "%s", err.msg);
		return BS_RESULT_FAILED_TO_PARSE;
	}

	*out_json = json;

	return BS_RESULT_OK;
}

BSAPI bs_Result _bs_loadJsonN(bs_Json* out, char* path, int path_length) {
	bs_String* raw;
	bs_Result result;

	result = _bs_loadFileN(&raw, path, path_length);
	if (result != BS_RESULT_OK) {
		return result;
	}

	bs_Json json;
	result = _bs_json(raw->value, raw->len - 1, &json);
	if (result != BS_RESULT_OK) {
		return result;
	}

	_bs_free(raw);

	*out = json;
	return BS_RESULT_OK;
}

static bs_JsonValue _bs_createJsonArray(bool is_mutable, void* root, int start, int end, bool is_32bit) {
	size_t idx, max;
	yyjson_type root_type;
	void* first;

	if (is_mutable) {
	    root_type = yyjson_mut_get_type(root);
		first = yyjson_mut_arr_get_first(root);
	} else {
    	root_type = yyjson_get_type(root);
    	first = yyjson_arr_get_first(root);
	}

	assert(root_type == YYJSON_TYPE_ARR);

	if (!first)
		return (bs_JsonValue) { .type = BS_JSON_ARRAY, .found = true };

	yyjson_type type = is_mutable ? yyjson_mut_get_type(first) : yyjson_get_type(first);
	assert((end - start) > 0);

	// hacky
	bs_JsonValueUnion* values = _bs_malloc((end - start) * (is_32bit ? sizeof(float) : sizeof(bs_JsonValueUnion)));
	union {
		float as_float;
	}* values_32 = (void*)values;

	bs_JsonType element_type = 0;
	if (type == YYJSON_TYPE_NUM) {
		element_type = is_32bit ? BS_JSON_FLOAT : BS_JSON_NUMBER;

		yyjson_subtype subtype = yyjson_mut_get_subtype(first);

		if (is_mutable) {
			yyjson_mut_val* hit;
			yyjson_mut_arr_foreach(root, idx, max, hit) {
				if (idx >= start) {
					if (subtype == YYJSON_SUBTYPE_SINT || subtype == YYJSON_SUBTYPE_UINT)
						values[idx - start].as_number = yyjson_mut_get_int(hit);
					else {
						if (is_32bit)
							values_32[idx - start].as_float = yyjson_mut_get_real(hit);
						else
							values[idx - start].as_number = yyjson_mut_get_real(hit);
					}
				}
				else if (idx >= end) break;
			}
		}
		else {
			yyjson_val* hit;
			yyjson_arr_foreach(root, idx, max, hit) {
				if (idx >= start) {
					yyjson_subtype subtype = yyjson_get_subtype(hit);
					if (subtype == YYJSON_SUBTYPE_SINT || subtype == YYJSON_SUBTYPE_UINT)
						values[idx - start].as_number = yyjson_get_int(hit);
					else {
						if (is_32bit)
							values_32[idx - start].as_float = yyjson_get_real(hit);
						else
							values[idx - start].as_number = yyjson_get_real(hit);
					}
				}
				else if (idx >= end) break;
			}
		}
	}
	else if (type == YYJSON_TYPE_STR || type == YYJSON_TYPE_NULL) {
		element_type = BS_JSON_STRING;
		if (is_mutable) {
			yyjson_mut_val* hit = NULL;
			yyjson_mut_arr_foreach(root, idx, max, hit) {
				if (idx >= start)
					values[idx - start].as_string = yyjson_mut_get_str(hit);
				else if (idx >= end) break;
			}
		}
		else {
			yyjson_val* hit;
			yyjson_arr_foreach(root, idx, max, hit) {
				if (idx >= start)
					values[idx - start].as_string = yyjson_get_str(hit);
				else if (idx >= end) break;
			}
		}
	}
	else if (type == YYJSON_TYPE_BOOL) {
		element_type = BS_JSON_BOOL;
		if (is_mutable) {
			yyjson_mut_val* hit;
			yyjson_mut_arr_foreach(root, idx, max, hit) {
				if (idx >= start)
					values[idx - start].as_string = yyjson_mut_get_str(hit);
				else if (idx >= end) break;
			}
		}
		else {
			yyjson_val* hit;
			yyjson_arr_foreach(root, idx, max, hit) {
				if (idx >= start)
					values[idx - start].as_string = yyjson_get_str(hit);
				else if (idx >= end) break;
			}
		}
	}
	else if (type == YYJSON_TYPE_OBJ) {
		element_type = BS_JSON_OBJECT;
		if (is_mutable) {
			yyjson_mut_val* hit;
			yyjson_mut_arr_foreach(root, idx, max, hit) {
				if (idx >= start) {
					values[idx - start].as_object = hit;
				}
				else if (idx >= end) break;
			}
		}
		else {
			yyjson_val* hit;
			yyjson_arr_foreach(root, idx, max, hit) {
				if (idx >= start)
					values[idx - start].as_object = hit;
				else if (idx >= end) break;
			}
		}
	}

	return (bs_JsonValue) {
		.found = true,
		.type = BS_JSON_ARRAY | element_type,
		.v.as_array.as_uchars = (bs_U8*)values,
		.size = end - start,
	};
}

static void _bs_deleteJsonArrayRange(yyjson_mut_val* root, int start, int end) {
	yyjson_type root_type = yyjson_mut_get_type(root);
	assert(root_type == YYJSON_TYPE_ARR);
	assert((end - start) > 0);

	for (int i = end - 1; i >= start; i--)
		yyjson_mut_arr_remove(root, i);
}

static inline void _bs_warnUnexpectedJsonType(bs_JsonType expect, const char* actual) {
	_bs_warnF("Expected JSON type %s, got %s type", bs_serializeJsonType(expect), actual);
}

static bs_JsonValue _bs_createJsonValue(bool is_mutable, void* root, char* name, bs_JsonType expect) {
	yyjson_val_uni uni = { 0 };
	yyjson_type type;

	if (is_mutable) {
		if (root)
			uni = ((yyjson_mut_val *)root)->uni;
		type = yyjson_mut_get_type(root);
	} else {
		if (root)
			uni = ((yyjson_val *)root)->uni;
		type = yyjson_get_type(root);
	}

	if (type == YYJSON_TYPE_ARR) {
		if (!(expect & (BS_JSON_ARRAY | BS_JSON_DONT_CARE | BS_JSON_UNDEFINED))) {
			_bs_warnUnexpectedJsonType(expect, "array");
			return (bs_JsonValue) { 0 };
		}

		int size = is_mutable ? yyjson_mut_arr_size(root) : yyjson_arr_size(root);
		return _bs_createJsonArray(is_mutable, root, 0, size, false);
	}
	else if (type == YYJSON_TYPE_STR || type == YYJSON_TYPE_NULL) {
		if (!(expect & (BS_JSON_STRING | BS_JSON_DONT_CARE | BS_JSON_UNDEFINED))) {
			_bs_warnUnexpectedJsonType(expect, "string");
			return (bs_JsonValue) { 0 };
		}

		return (bs_JsonValue) {
			.v.as_string = (char*)uni.str,
			.found = true,
			.type = BS_JSON_STRING,
		};
	}
	else if (type == YYJSON_TYPE_NUM) {
		if (!(expect & (BS_JSON_BOOL | BS_JSON_NUMBER | BS_JSON_FLOAT | BS_JSON_NUMBER_INTEGER | BS_JSON_UCHAR | BS_JSON_DONT_CARE | BS_JSON_UNDEFINED))) {
			_bs_warnUnexpectedJsonType(expect, "number");
			return (bs_JsonValue) { 0 };
		}

		yyjson_subtype subtype = is_mutable ? yyjson_mut_get_subtype(root) : yyjson_get_subtype(root);
		double value = (subtype == YYJSON_SUBTYPE_UINT || subtype == YYJSON_SUBTYPE_SINT) ? (bs_F64)uni.i64 : (bs_F64)uni.f64;
		bs_JsonValue v = {
			.found = true,
			.type = BS_JSON_NUMBER,
			.v.as_number = value,
		};

		if (expect & BS_JSON_BOOL) {
			v.type = BS_JSON_BOOL;
			v.v.as_bool = value == 0.0 ? false : true;
		}

		return v;
	}
	else if (type == YYJSON_TYPE_BOOL) {
		if (!(expect & (BS_JSON_BOOL | BS_JSON_DONT_CARE | BS_JSON_UNDEFINED))) {
			_bs_warnUnexpectedJsonType(expect, "boolean");
			return (bs_JsonValue) { 0 };
		}

		return (bs_JsonValue) {
			.found = true,
			.v.as_bool = yyjson_get_bool(root),
			.type = BS_JSON_BOOL,
		};
	}
	else if (type == YYJSON_TYPE_OBJ) {
		if (!(expect & (BS_JSON_OBJECT | BS_JSON_DONT_CARE | BS_JSON_UNDEFINED))) {
			_bs_warnUnexpectedJsonType(expect, "object");
			return (bs_JsonValue) { 0 };
		}

		return (bs_JsonValue) {
			.found = true,
			.v.as_object = root,
			.type = BS_JSON_OBJECT,
		};
	}

	_bs_warnUnexpectedJsonType(expect, "unknown");
	return (bs_JsonValue) { 0 };
}

BSAPI bs_JsonValue _bs_parseJsonValue(char* raw) {
	yyjson_doc* doc = yyjson_read(raw, strlen(raw), 0);
	yyjson_val* root = yyjson_doc_get_root(doc);

	return _bs_createJsonValue(false, root, NULL, BS_JSON_UNDEFINED);
}

static bs_JsonValue _bs_fetchJsonOpt(bs_Json* root, bs_JsonType expect, char* path, int len, bool delete) {
	char* old = path;
	path = strdup(path);

	bool is_32bit = expect & BS_JSON_FLOAT;

	const bool is_mutable = root->is_mutable;

	void* object = root->as_object;
	const char* name = is_mutable ? yyjson_mut_get_type_desc(object) : yyjson_get_type_desc(object);

	char* token = NULL;
	char* last = strrchr(path, '.');
	last = last ? (last + 1) : path;
	while ((token = _bs_strsep(&path, "."))) {
		char* array_start = strchr(token, '[');
		if (array_start) {
			char* array_end = strchr(array_start, ']');
			if (!array_end) {
				_bs_warnF("Expected end of array in JSON path \"%s\"", old);
				return (bs_JsonValue) { 0 };
			}

			assert(array_end[1] == '\0'); // todo error
			array_end[0] = array_start[0] = '\0';
			array_start++;

			if (strncmp(token, "$", 1) == 0) {
				object = root->as_object;
				assert((is_mutable ? yyjson_mut_get_type(object) : yyjson_get_type(object)) == YYJSON_TYPE_ARR);
			}
			else {
			    if (is_mutable)
					object = yyjson_mut_obj_get(object, token);
				else
                    object = yyjson_obj_get(object, token);

				if (!object) {
					if (expect != BS_JSON_UNDEFINED)
						_bs_warnF("Couldn't find object \"%s\" from path \"%s\"", token, old);

					return (bs_JsonValue) { 0 };
				}
			}

			char* selection = strchr(array_start, ':');
			if (selection) {
				assert(token == last);
				if (array_start[0] == ':') { // [:n] - Selects the first n elements of the array
					double end = _bs_toDouble(selection + 1);
					if (delete) {
						yyjson_mut_arr_remove_range(object, 0, end);
						return (bs_JsonValue) { 0 };
					}
					else
						return _bs_createJsonArray(is_mutable, object, 0, end, is_32bit);
				}
				else if (selection[1] == '\0') {
					if (array_start[0] == '-') { // [-n:] - Selects the last n elements of the array.
						selection[0] = '\0';
						double start = -_bs_toDouble(array_start);
						int size = is_mutable ? yyjson_mut_arr_size(object) : yyjson_arr_size(object);

						if (delete) {
							yyjson_mut_arr_remove_range(object, size - start, start);
							return (bs_JsonValue) { 0 };
						}
						else
							return _bs_createJsonArray(is_mutable, object, size - start, size, is_32bit);
					}
					else { // [n:] - Selects array elements from the start index.
						selection[0] = '\0';
						double start = _bs_toDouble(array_start);
						int size = is_mutable ? yyjson_mut_arr_size(object) : yyjson_arr_size(object);

						if (delete) {
							yyjson_mut_arr_remove_range(object, start, size - start);
							return (bs_JsonValue) { 0 };
						}
						else
							return _bs_createJsonArray(is_mutable, object, start, size, is_32bit);
					}
				}
				else { // [1:5] - Selects array elements from the start index and up to, but not including, end index.
					selection[0] = '\0';
					double start = _bs_toDouble(array_start);
					double end = _bs_toDouble(selection + 1) - 1;

					if (delete) {
						yyjson_mut_arr_remove_range(object, start, start - end);
						return (bs_JsonValue) { 0 };
					}
					else
						return _bs_createJsonArray(is_mutable, object, start, end, is_32bit);
				}
			}
			else {
				if (strchr(token, ',')) { // [1, 2, 7, 2] - Selects array elements with the specified indexes.
					_bs_warnF("JSON path specific index selection has not been implemented yet", token, old);
					return (bs_JsonValue) { 0 };
					assert(token == last);
					char* array_token = NULL;
					while ((array_token = _bs_strsep(&token, ","))) {
						double index = _bs_toDouble(array_token);
						double y = index;
					}
				}
				else { // [n] - Selects the n-th element from an array.
					double index = _bs_toDouble(array_start);

					if (delete && token == last) {
						yyjson_mut_arr_remove(object, index);
						break;
					}

					if (is_mutable)
					    object = yyjson_mut_arr_get(object, index);
					else
						object = yyjson_arr_get(object, index);

					continue;
				}
			}
		}
		else if (delete && token == last) {
			yyjson_mut_obj_remove_key(object, last);
			break;
		}
		else if (strncmp(token, "$", 1) == 0) {
			object = root->as_object;
			continue;
		}

		if (is_mutable)
		    object = yyjson_mut_obj_get(object, token);
		else
		    object = yyjson_obj_get(object, token);

		if (token != last && ((is_mutable ? yyjson_mut_get_type(object) : yyjson_get_type(object)) != YYJSON_TYPE_OBJ)) {
			if (expect != BS_JSON_UNDEFINED)
				_bs_warnF("Couldn't find object \"%s\" from path \"%s\"", token, old);

			return (bs_JsonValue) { 0 };
		}

	}

	free(path);

	if (!delete)
		return _bs_createJsonValue(is_mutable, object, last, expect);
	return (bs_JsonValue) { 0 };

}

BSAPI bs_JsonValue _bs_fetchJsonN(bs_Json* root, bs_JsonType expect, char* path, int path_length) {
	return _bs_fetchJsonOpt(root, expect, path, path_length, false);
}

BSAPI void _val_bs_deleteJson(bs_Json* root, char* path, int path_length) {
	BS_VALIDATE(root->is_mutable == true,, );

	_bs_deleteJsonN(root, path, path_length);
}

BSAPI void _bs_deleteJsonN(bs_Json* root, char* path, int path_length) {
	_bs_ensureJsonMutable(root);
	_bs_fetchJsonOpt(root, 0, path, path_length, true);
}

static inline void _bs_warnFailedToUpdate(char* type, char* token, char* path) {
	_bs_warnF("Failed to update JSON %s \"%s\" in path \"%s\"", type, token, path);
}

BSAPI bs_Result _val_bs_ensureJsonN(bs_Json* root, bs_JsonValue value, char* path, int path_length) {
	BS_VALIDATE(root->is_mutable == true, false,);

	return _bs_ensureJsonN(root, value, path, path_length);
}

BSAPI bs_Result _bs_ensureJsonN(bs_Json* root, bs_JsonValue value, char* path, int path_length) {
	bs_Result result = BS_RESULT_OK;

	char* old_path = path;
	path = strdup(path);

	yyjson_mut_val* object = root->as_object;
	char* token = NULL;
	char* last = strrchr(path, '.');
	last = last ? (last + 1) : path;
	while ((token = _bs_strsep(&path, "."))) {
		yyjson_mut_val* old = object;

		char* array_start = strchr(token, '[');
		if (array_start) {
			char* array_end = strchr(array_start, ']');
			if (!array_end) {
				_bs_warnF("Expected end of array in JSON path \"%s\"", old_path);
				result = BS_RESULT_GENERAL_ERROR;
				goto end;
			}

			assert(array_end[1] == '\0'); // todo error
			array_end[0] = array_start[0] = '\0';
			int index = _bs_toDouble(array_start + 1);

			if (strncmp(token, "$", 1) == 0) {
				object = old = root->as_object;
				if (yyjson_mut_get_type(object) != YYJSON_TYPE_ARR) {
					object = root->as_object = yyjson_mut_arr(root->doc);
					yyjson_mut_doc_set_root(root->doc, object);
				}
			}
			else
				object = yyjson_mut_obj_get(object, token);

			if (!object) {
				yyjson_mut_val* field = yyjson_mut_strcpy(root->doc, token);
				object = yyjson_mut_arr(root->doc);
				if (!yyjson_mut_obj_add(old, field, object)) {
					_bs_warnF("Failed to add JSON object \"%s\" in path \"%s\"", token, old_path);
					result = BS_RESULT_GENERAL_ERROR;
					goto end;
				}
			}
			old = object;
			object = yyjson_mut_arr_get(object, index);

			if (token != last) {
				if (!object) {
					object = yyjson_mut_obj(root->doc);
					if (!yyjson_mut_arr_append(old, object)) {
						_bs_warnF("Failed to append JSON object \"%s\" in path \"%s\"", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
			}
			else {
				yyjson_mut_val* val = NULL;
				if		(value.type & BS_JSON_STRING)							val = yyjson_mut_str(root->doc, value.v.as_string);
				else if (value.type & BS_JSON_NUMBER)							val = yyjson_mut_double(root->doc, value.v.as_number);
				else if (value.type & BS_JSON_FLOAT)							val = yyjson_mut_double(root->doc, value.v.as_number);
				else if (value.type & (BS_JSON_NUMBER_INTEGER | BS_JSON_UCHAR))	val = yyjson_mut_int(root->doc, value.v.as_number);
				else if (value.type & BS_JSON_BOOL)								val = yyjson_mut_bool(root->doc, value.v.as_bool);
				else if (value.type & BS_JSON_OBJECT)							val = value.v.as_object;
				else {
					_bs_warnF("Invalid JSON type \"%d\" (%d)\n", bs_serializeJsonType(value.type), value.type);
					result = BS_RESULT_INVALID_TYPE;
					goto end;
				}

				if (!object) {
					if (!yyjson_mut_arr_append(old, val)) {
						_bs_warnF("Failed to append JSON value \"%s\" in path \"%s\"", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else {
					if (!yyjson_mut_arr_replace(old, index, val)) {
						_bs_warnF("Failed to replace JSON value \"%s\" in path \"%s\"", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
			}
		}
		else {
			if (token != last) {
				if (strncmp(token, "$", 1) == 0) {
					object = old = root->as_object;
					if (yyjson_mut_get_type(object) != YYJSON_TYPE_OBJ) {
						object = root->as_object = yyjson_mut_obj(root->doc);
						yyjson_mut_doc_set_root(root->doc, object);
					}
				}
				else
					object = yyjson_mut_obj_get(object, token);

				if (!object) {
					object = yyjson_mut_obj(root->doc);
					if (!yyjson_mut_obj_add(old, yyjson_mut_strcpy(root->doc, token), object)) {
						_bs_warnF("Failed to add JSON object \"%s\" in path \"%s\"", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else if (yyjson_mut_get_type(object) != YYJSON_TYPE_OBJ) {
					object = yyjson_mut_obj(root->doc);
					if (!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), object)) {
						_bs_warnF("Failed to update JSON object \"%s\" in path \"%s\"", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
			}
			else {
				if (value.type & (BS_JSON_ARRAY)) {
					yyjson_mut_val* arr = yyjson_mut_arr(root->doc);
					if (value.type & BS_JSON_STRING) {
						for (int i = 0; i < value.size; i++)
							yyjson_mut_arr_append(arr, yyjson_mut_str(root->doc, value.v.as_array.as_strings[i]));
					}
					else if (value.type & BS_JSON_NUMBER) {
						for (int i = 0; i < value.size; i++)
							yyjson_mut_arr_append(arr, yyjson_mut_float(root->doc, value.v.as_array.as_numbers[i]));
					}
					else if (value.type & BS_JSON_FLOAT) {
						for (int i = 0; i < value.size; i++)
							yyjson_mut_arr_append(arr, yyjson_mut_float(root->doc, value.v.as_array.as_floats[i]));
					}
					else if (value.type & BS_JSON_NUMBER_INTEGER) {
						for (int i = 0; i < value.size; i++)
							yyjson_mut_arr_append(arr, yyjson_mut_int(root->doc, value.v.as_array.as_ints[i]));
					}
					else if (value.type & BS_JSON_BOOL) {
						for (int i = 0; i < value.size; i++)
							yyjson_mut_arr_append(arr, yyjson_mut_bool(root->doc, value.v.as_array.as_bools[i]));
					}
					else if (value.type & BS_JSON_OBJECT)
						yyjson_mut_arr_append(old, value.v.as_object);
					else if (value.type & BS_JSON_UCHAR) {
						for (int i = 0; i < value.size; i++)
							yyjson_mut_arr_append(arr, yyjson_mut_int(root->doc, value.v.as_array.as_uchars[i]));
					}
					if (strncmp(token, "$", 1) == 0) {
						object = root->as_object = arr;
						yyjson_mut_doc_set_root(root->doc, object);
					}
					else
						yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), arr);
				}
				else if (value.type & BS_JSON_STRING) {
					if (!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), yyjson_mut_str(root->doc, value.v.as_string))) {
						_bs_warnFailedToUpdate("string", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else if (value.type & BS_JSON_NUMBER) {
					if (!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), yyjson_mut_double(root->doc, value.v.as_number))) {
						_bs_warnFailedToUpdate("number", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else if (value.type & BS_JSON_FLOAT) {
					if (!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), yyjson_mut_float(root->doc, value.v.as_number))) {
						_bs_warnFailedToUpdate("float", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else if (value.type & (BS_JSON_NUMBER_INTEGER | BS_JSON_UCHAR)) {
					if (!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), yyjson_mut_int(root->doc, value.v.as_number))) {
						_bs_warnFailedToUpdate("integer", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else if (value.type & BS_JSON_OBJECT) {
					if(!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), value.v.as_object)) {
						_bs_warnFailedToUpdate("object", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
				else if (value.type & BS_JSON_BOOL) {
					if (!yyjson_mut_obj_put(old, yyjson_mut_str(root->doc, token), yyjson_mut_bool(root->doc, value.v.as_bool))) {
						_bs_warnFailedToUpdate("boolean", token, old_path);
						result = BS_RESULT_GENERAL_ERROR;
						goto end;
					}
				}
			}
		}
	}

end:
	free(path);

	return result;
}

BSAPI void _bs_destroyJson(bs_Json* json) {
	if (json->is_mutable)
		yyjson_mut_doc_free(json->doc);
	else
		yyjson_doc_free(json->doc);
}

static void _bs_enumerateMutableJson(bs_Json* json, bs_JsonEnumeration* e) {
	yyjson_mut_val* key = yyjson_mut_obj_iter_next((yyjson_mut_obj_iter*)&e->iter);

	yyjson_mut_val* value = yyjson_mut_obj_iter_get_val(key);
	const char* key_str = yyjson_mut_get_str(key);

	e->key = key_str;
	e->value = _bs_createJsonValue(json->is_mutable, value, key_str, BS_JSON_UNDEFINED);
}

BSAPI void _bs_enumerateJson(bs_Json* json, bs_JsonEnumeration* e) {
	if (json->is_mutable) {
		_bs_enumerateMutableJson(json, e);
		return;
	}

	yyjson_val* key = yyjson_obj_iter_next((yyjson_obj_iter*)&e->iter);

	yyjson_val* value = yyjson_obj_iter_get_val(key);
	const char* key_str = yyjson_get_str(key);

	e->key = key_str;
	e->value = _bs_createJsonValue(json->is_mutable, value, key_str, BS_JSON_UNDEFINED);
}

BSAPI bs_JsonEnumeration _bs_beginEnumeration(bs_Json* json) {
	bs_JsonEnumeration result;

	if (json->is_mutable) {
		yyjson_mut_obj_iter iter = yyjson_mut_obj_iter_with(json->as_object);
		memcpy(&result.iter, &iter, sizeof(yyjson_mut_obj_iter));
	}
	else {
		yyjson_obj_iter iter = yyjson_obj_iter_with(json->as_object);
		memcpy(&result.iter, &iter, sizeof(yyjson_obj_iter));
	}

	_bs_enumerateJson(json, &result);

	return result;
}

//bool
//_bs_ensureJson(
//	bs_JsonObject* root,
//	char* path,
//	bs_JsonValue value);
//
//bool
//_bs_ensureJsonF(
//	bs_JsonObject* root,
//	bs_JsonValue value,
//	const char* path,
//	...);

BSAPI bs_JsonValue _bs_jsonValueFromRoot(bs_Json x) { return (bs_JsonValue) { .type = BS_JSON_OBJECT, .v.as_object = x.as_object, .found = true }; }
BSAPI bs_JsonValue _bs_jsonValueFromObject(bs_JsonObject x) { return (bs_JsonValue) { .type = BS_JSON_OBJECT, .v.as_object = x, .found = true, }; }
BSAPI bs_JsonValue _bs_jsonValueFromBool(bool x) { return (bs_JsonValue) { .type = BS_JSON_BOOL, .v.as_bool = x, .found = true }; }
BSAPI bs_JsonValue _bs_jsonValueFromInteger(int x) { return (bs_JsonValue) { .type = BS_JSON_NUMBER_INTEGER, .v.as_number = x, .found = true, }; }
BSAPI bs_JsonValue _bs_jsonValueFromFloat(double x) { return (bs_JsonValue) { .type = BS_JSON_NUMBER, .v.as_number = x, .found = true, }; }
BSAPI bs_JsonValue _bs_jsonValueFromString(char* x) { return (bs_JsonValue) { .type = BS_JSON_STRING, .v.as_string = x ? strdup(x) : x, .found = true, }; }
BSAPI bs_JsonValue _bs_jsonValueFromStringPointer(char* x) { return (bs_JsonValue) { .type = BS_JSON_STRING, .v.as_string = x, .found = true, }; }
BSAPI bs_JsonValue _bs_jsonValueFromDateTime(bs_DateTime x) {
	return (bs_JsonValue) {
		.type = BS_JSON_STRING,
		.v.as_string = _bs_charStringF("%02d-%02d-%02d %02d:%02d:%02d", x.years, x.months, x.days, x.hours, x.minutes, x.seconds),
		.found = true,
	};
}
BSAPI bs_JsonValue _bs_jsonObject(bs_Json* json) { return (bs_JsonValue) { .type = BS_JSON_OBJECT, .v.as_object = yyjson_mut_obj(json->doc), .found = true, }; }
BSAPI bs_JsonValue _bs_jsonArray(bs_JsonType type, void* data, int count) { return (bs_JsonValue) { .type = BS_JSON_ARRAY | type, .found = true, .v.as_array.as_ints = data, .size = count }; }

BSAPI bs_JsonValue _bs_jsonVec2(bs_vec2* vector) {
	return (bs_JsonValue) {
		.type = BS_JSON_ARRAY | BS_JSON_FLOAT,
		.found = true,
		.size = 2,
		.v.as_array.as_floats = vector->a,
	};
}

BSAPI bs_JsonValue _bs_jsonVec3(bs_vec3* vector) {
	return (bs_JsonValue) {
		.type = BS_JSON_ARRAY | BS_JSON_FLOAT,
		.found = true,
		.size = 3,
		.v.as_array.as_floats = vector->a
	};
}

BSAPI bs_JsonValue _bs_jsonVec4(bs_vec4* vector) {
	return (bs_JsonValue) {
		.type = BS_JSON_ARRAY | BS_JSON_FLOAT,
		.found = true,
		.size = 4,
		.v.as_array.as_floats = vector->a
	};
}

BSAPI bs_JsonValue _bs_jsonRGBA(bs_RGBA color) {
	return (bs_JsonValue) {
		.type = BS_JSON_ARRAY | BS_JSON_UCHAR,
		.found = true,
		.size = 4,
		.v.as_array.as_uchars = color.array
	};
}
