
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
#include <assert.h>
#include <stdio.h>

#include <spirv_cross_c.h>
#include <glslang/Include/glslang_c_interface.h>
#include <glslang/Public/resource_limits_c.h>

static spvc_context _bsmod_compiler_context_;



  /*==============================================================================
   * Shader Format
   *============================================================================*/

static bs_U32 _bsmod_readPushConstantSize(spvc_compiler compiler, spvc_resources resources) {
	spvc_reflected_resource* resource_list = NULL;
	size_t resource_size = 0;
	spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_PUSH_CONSTANT, &resource_list, &resource_size);

	if (resource_size == 0)
		return 0;

	if (resource_size > 1) {
		bs_warnF("Too many push constants, reading the first one\n");
	}

	spvc_type spirv_type = spvc_compiler_get_type_handle(compiler, resource_list->type_id);

	size_t struct_size = 0;
	spvc_compiler_get_declared_struct_size(compiler, spirv_type, &struct_size);

	return struct_size;
}


static bs_U32 _bsmod_readBindSetFlags(spvc_compiler compiler, spvc_resources resources, spvc_resource_type type) {
	bs_U32 bind_set_flags = 0;

	spvc_reflected_resource* resource_list = NULL;
	size_t resource_size = 0;
	spvc_resources_get_resource_list_for_type(resources, type, &resource_list, &resource_size);

	for (int i = 0; i < resource_size; i++) {
		spvc_reflected_resource* data = resource_list + i;

		int set = spvc_compiler_get_decoration(compiler, data->id, SpvDecorationDescriptorSet);
		if (set >= BS_MAX_NUM_BIND_SETS) {
			bs_warnF("Bind set %d is greater than BS_MAX_NUM_BIND_SETS (%d)\n", set, BS_MAX_NUM_BIND_SETS);
			continue;
		}

		bind_set_flags |= (1 << set);
	}

	return bind_set_flags;
}

BSMODAPI bs_Result _bsmod_packShader(spvc_compiler compiler, spvc_resources resources, bs_U32* spirv, size_t spirv_size, bs_ShaderType shader_type, bsmod_Package* package, char* resource_name) {
	bs_Result result;

	bs_BshaHeader header = {
		.magic = BS_BSHA_MAGIC,
		.version = 1,
		.push_constant_size = _bsmod_readPushConstantSize(compiler, resources),
		.shader_type = shader_type,
		.spirv_size = spirv_size,
	};

	spvc_resource_type types[] = {
		SPVC_RESOURCE_TYPE_UNIFORM_BUFFER,
		SPVC_RESOURCE_TYPE_STORAGE_BUFFER,
		SPVC_RESOURCE_TYPE_SEPARATE_IMAGE,
		SPVC_RESOURCE_TYPE_SEPARATE_SAMPLERS,
		SPVC_RESOURCE_TYPE_SUBPASS_INPUT,
		SPVC_RESOURCE_TYPE_SAMPLED_IMAGE,
		SPVC_RESOURCE_TYPE_ACCELERATION_STRUCTURE,
		SPVC_RESOURCE_TYPE_STORAGE_IMAGE,
	};

	for (int i = 0; i < (sizeof(types) / sizeof(*types)); i++)
		header.bind_set_flags |= _bsmod_readBindSetFlags(compiler, resources, types[i]);

	spvc_reflected_resource* attributes_resource_list = NULL;
	if (shader_type == BS_SHADER_STAGE_VERTEX_BIT) {
		size_t attributes_count = 0;
		spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_STAGE_INPUT, &attributes_resource_list, &attributes_count);
		header.attributes_count = attributes_count;
	}

	const size_t total_size_excluding_binary = sizeof(bs_BshaHeader) + header.attributes_count * sizeof(bs_BshaAttribute);
	const size_t total_size = total_size_excluding_binary + spirv_size;

	unsigned char* bsha = bs_malloc(total_size);

	for (int i = 0; i < header.attributes_count; i++) {
		spvc_reflected_resource* data = attributes_resource_list + i;

		spvc_type type = spvc_compiler_get_type_handle(compiler, data->base_type_id);
		int num_units = spvc_type_get_vector_size(type);
		int location = spvc_compiler_get_decoration(compiler, data->id, SpvDecorationLocation);
		bs_U64 name_hash = bs_stringHash(data->name);

		bs_BshaAttribute attribute = {
			.location = location,
			.name_hash = name_hash,
			.size = num_units * sizeof(bs_U32),
		};

		memcpy(bsha + sizeof(bs_BshaHeader) + i * sizeof(bs_BshaAttribute), &attribute, sizeof(bs_BshaAttribute));
	}

	memcpy(bsha + total_size_excluding_binary, spirv, spirv_size);
	memcpy(bsha, &header, sizeof(bs_BatlHeader));

	result = _bsmod_packResource(BS_RESOURCE_SHADER, bsha, total_size, package->name, resource_name, strlen(resource_name));
	bs_free(bsha);

	return BS_RESULT_OK;
}



  /*==============================================================================
   * Binding Format
   *============================================================================*/

static bs_BindTypeIndex bsmod_convertBindType(spvc_resource_type type) {
	switch (type) {
	case SPVC_RESOURCE_TYPE_STORAGE_BUFFER: return BS_DESCRIPTOR_TYPE_STORAGE_BUFFER_INDEX;
	case SPVC_RESOURCE_TYPE_UNIFORM_BUFFER: return BS_DESCRIPTOR_TYPE_UNIFORM_BUFFER_INDEX;
	case SPVC_RESOURCE_TYPE_SEPARATE_IMAGE: return BS_DESCRIPTOR_TYPE_SAMPLED_IMAGE_INDEX;
	case SPVC_RESOURCE_TYPE_SUBPASS_INPUT: return BS_DESCRIPTOR_TYPE_INPUT_ATTACHMENT_INDEX;
	case SPVC_RESOURCE_TYPE_SEPARATE_SAMPLERS: return BS_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER_INDEX;
	case SPVC_RESOURCE_TYPE_SAMPLED_IMAGE: return BS_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER_INDEX;
//	case SPVC_RESOURCE_TYPE_ACCELERATION_STRUCTURE: return BS_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_INDEX;
	case SPVC_RESOURCE_TYPE_STORAGE_IMAGE: return BS_DESCRIPTOR_TYPE_STORAGE_IMAGE_INDEX;
	default:
		bs_warnF("SPVC buffer type (%d) not supported\n", type);
		return SPVC_RESOURCE_TYPE_UNKNOWN;
	}
}

static bs_Result _bsmod_packBinding(spvc_compiler compiler, spvc_reflected_resource* resource, bsmod_Package* package, bs_BindTypeIndex bind_type_index, bs_ShaderType shader_type) {
	bs_Result bs_result;
	spvc_result result;

	bs_BbndHeader header = {
		.magic = BS_BBND_MAGIC,
		.version = 1,
		.set = spvc_compiler_get_decoration(compiler, resource->id, SpvDecorationDescriptorSet),
		.point = spvc_compiler_get_decoration(compiler, resource->id, SpvDecorationBinding),
		.descriptors_count = 1,
		.type = bs_indexBindType(bind_type_index),
		.type_index = bind_type_index,
		.shader_stages = shader_type,
	};

	const size_t total_size_excluding_binary = sizeof(bs_BbndHeader);
	const size_t total_size = total_size_excluding_binary;

	//int block = spvc_compiler_get_decoration(compiler, resource->id, SpvDecorationUniform);

	int len = snprintf(NULL, 0, "_bbnd/%d/%d", header.set, header.point);
	char* name = bs_alloca(len + 1);
	snprintf(name, len + 1, "_bbnd/%d/%d", header.set, header.point);

	bsmod_Resource* existing = _bsmod_queryResource(package, name);
	if (existing) {
		bsmod_Chunk* chunk = bs_fetchUnit(&package->chunks, existing->header.chunk);
		bs_BbndHeader* existing_header = chunk->bin.data + existing->header.offset;

		if (existing_header->magic == BS_BBND_MAGIC) {
			header.shader_stages |= existing_header->shader_stages;
		}
		else {
			bs_warnF("Found existing binding \"%s\" with invalid magic, overwriting.\n", name);
		}
	}

	spvc_type spirv_type = spvc_compiler_get_type_handle(compiler, resource->type_id);

	int count = spvc_type_get_num_array_dimensions(spirv_type);
	if (count == 1 && spvc_type_array_dimension_is_literal(spirv_type, 0)) { // nested arrays not supported atm, idk how to handle
		header.descriptors_count = spvc_type_get_array_dimension(spirv_type, 0);
	}

	size_t struct_size = 0;
	result = spvc_compiler_get_declared_struct_size(compiler, spirv_type, &struct_size);
	if (result != SPVC_SUCCESS) {
		BSMOD_WARN_SPVC_ERROR("spvc_compiler_get_declared_struct_size", result,);
	}

	//.type = bs_serializeBindType(type),

	//shader_stages |= shader_type;
	//name = strdup(name);
	//source = strdup(path);

	unsigned char* bbnd = bs_malloc(total_size);
	memcpy(bbnd, &header, sizeof(bs_BbndHeader));
	bs_result = _bsmod_packResource(BS_RESOURCE_BINDING, bbnd, total_size, package->name, name, len);
	bs_free(bbnd);

	return bs_result;
}



  /*==============================================================================
   * Compile Shaders
   *============================================================================*/

BSMODAPI void _bsmod_onCompileShader(bsmod_TrackParams params) {
	bs_Result result;

	if (!bs_fileExists(params.path, strlen(params.path)))
		return;

	char* resource_name = bs_fileName(params.path);
	static bs_String* variadic;
	variadic = bs_stringF(variadic, "shaders/%s", resource_name);

	bs_logF("Compiling \"%s\" as \"%s\"\n", params.path, variadic->value);

	bool success = _bsmod_compileShader(params.path, variadic->value, params.package);
	if (success) {

		if (params.compile_references)
			_bsmod_updateShaderReferences();
		//bs_loadBindings(_bsmod_.bsgfx_package, "bindings");

		if (bs_instance()->instance) {
			int package;
			result = bs_loadPackage(params.package, &package);
			if (result != BS_RESULT_OK)
				return;

			bs_Resource* resource;
			bs_shader(package, variadic->value, 0, &resource);
		}
	}

	if (params.compile_references && (bs_fileExtensionIs(params.path, "glsl") || bs_fileExtensionIs(params.path, "h"))) { // header file, compile all references
		bs_Json json;
		result = bs_loadJson(&json, BS_CONSTANT_STRING("project/woc/references.json")); // TODO: remove woc
		if (result != BS_RESULT_OK)
			return;

		bs_JsonValue files = bs_fetchJsonF(&json, BS_JSON_UNDEFINED, "%.*s", strlen(params.path) - 5, params.path);

		if (files.size > 0)
			bs_infoF(BS_PRINT_CYAN "Compiling %d reference(s)\n" BS_PRINT_RESET, files.size);

		for (int i = 0; i < files.size; i++) {
			char* file = files.as_array.as_strings[i];

			_bsmod_onCompileShader((bsmod_TrackParams) {
				.prefix = params.prefix,
				.package = params.package,
				.path = file,
			});
		}
	}
}

/*
static void _bsmod_saveBuffer(bs_Json* json, char* shader_type, const char* name, spvc_resource_type type, bs_U32* spirv, bs_U32 size, bool add_to_bindings) {
	bsmod_Reflection reflection = _bsmod_reflectionData(spirv, size, type);

	static bs_String* path;

	const char* type_string = _bsmod_serializeBufferType(type);
	for (int i = 0; i < reflection.num; i++) {
		spvc_reflected_resource* data = reflection.data + i;

		int set = spvc_compiler_get_decoration(reflection.compiler, data->id, SpvDecorationDescriptorSet);
		int point = spvc_compiler_get_decoration(reflection.compiler, data->id, SpvDecorationBinding);
		int block = spvc_compiler_get_decoration(reflection.compiler, data->id, SpvDecorationUniform);

		path = bs_stringF(path, "%d_%d", set, point);

	//	bs_ensureJsonF(json, bs_jsonObject(json), "%s[%d]", name, i);
		bs_ensureJsonF(json, bs_jsonValue(data->name), "%s[%d].name", name, i);
		bs_ensureJsonF(json, bs_jsonValue(set), "%s[%d].set", name, i);
		bs_ensureJsonF(json, bs_jsonValue(point), "%s[%d].point", name, i);
		bs_ensureJsonF(json, bs_jsonValue(type_string), "%s[%d].type", name, i);

		spvc_type spirv_type = spvc_compiler_get_type_handle(reflection.compiler, data->type_id);
		int count = spvc_type_get_num_array_dimensions(spirv_type);
		if (count == 1 && spvc_type_array_dimension_is_literal(spirv_type, 0)) { // nested arrays not supported atm, idk how to handle
			spvc_constant_id descriptor_count = spvc_type_get_array_dimension(spirv_type, 0);
			bs_ensureJsonF(json, bs_jsonValue(descriptor_count), "%s[%d].count", name, i);

			if (add_to_bindings)
				bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(descriptor_count), "%s.count", path->value);
		}
		else {
			bs_ensureJsonF(json, bs_jsonValue(1), "%s[%d].count", name, i);

			if (add_to_bindings)
				bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(1), "%s.count", path->value);
		}

		size_t struct_size = 0;
		spvc_compiler_get_declared_struct_size(reflection.compiler, spirv_type, &struct_size);
		bs_ensureJsonF(json, bs_jsonValue(struct_size), "%s[%d].size", name, i);

		if (add_to_bindings) {
			double size = bs_fetchJsonF(&_bsmod_.bindings_json, BS_JSON_UNDEFINED, "%s.size", path->value).as_number;
			if (size != 0.0 && size != struct_size) {
				bs_warnF("Existing binding (set: %d, point: %d) differs in size (old: %lld, new: %lld)\n", set, point, (size_t)size, (size_t)struct_size);
				//continue;
			}

			bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(data->name), "%s.name", path->value);
			bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(type_string), "%s.type", path->value);
			bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(struct_size), "%s.size", path->value);
			bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(set), "%s.set", path->value);
			bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(point), "%s.point", path->value);

			bs_JsonValue v = bs_fetchJsonF(&_bsmod_.bindings_json, BS_JSON_UNDEFINED, "%s.stages", path->value);
			bool found = false;
			for (int j = 0; j < v.size; j++) {
				char* stage = v.as_array.as_strings[j];
				if (strcmp(stage, shader_type) == 0) {
					found = true;
					break;
				}
			}

			if (!found)
				bs_ensureJsonF(&_bsmod_.bindings_json, bs_jsonValue(shader_type), "%s.stages[999]", path->value);
		}
	}
}
*/


static bs_Json _bsmod_shader_references = { 0 };
BSMODAPI void _bsmod_loadShaderReferences() {
	bs_Result result = bs_loadJson(&_bsmod_shader_references, BS_CONSTANT_STRING("project/woc/references.json")); // TODO: remove woc
	if (result == BS_RESULT_OK)
		_bsmod_shader_references = bs_emptyJson();
}

BSMODAPI void _bsmod_updateShaderReferences() {
	bs_Result result;

	char* raw;
	result = bs_saveJson(&_bsmod_shader_references, BS_JSON_PRETTY, &raw);
	if (result != BS_RESULT_OK)
		return;

	result = bs_saveFile(raw, strlen(raw), BS_CONSTANT_STRING("project/woc/references.json")); //TODO: remove woc
	if (result != BS_RESULT_OK)
		return;
}

static void _bsmod_writeReferences(char* path, bs_String* glsl) {
	bs_String* include_path = bs_string(NULL, "", 0);
#define INCLUDE_SEARCH "#include "
	char* include = glsl->value;
	int length = glsl->len;
	for (int i = 0 ;; i++) {
		include = bs_memmem(include, length, INCLUDE_SEARCH, sizeof(INCLUDE_SEARCH) - 1);
		if (!include) break;

		// i mean these asserts shouldnt fire cause howsit gonna compile the shaderthing but yea
		include = strchr(include, '\"');
		assert(include);

		char* end = strchr(++include, '\"');
		assert(end);
		int len = end - include;

		include_path = bs_string(include_path, include, len);
		char* ext = bs_fileExtension(include_path->value);
		assert(ext);
		int name_len = (ext - 1) - include_path->value;

		if (memchr(include_path->value, '.', name_len))
			goto next;

		bs_JsonValue existing = bs_fetchJsonF(&_bsmod_shader_references, BS_JSON_UNDEFINED, "%.*s", name_len, include_path->value);
		int index = 99999;
		for (int j = 0; j < existing.size; j++) {
			if (strcmp(existing.as_array.as_strings[j], path) == 0)
				goto next;
		}

		bs_ensureJsonF(&_bsmod_shader_references, bs_jsonValue(path), "%.*s[%d]", name_len, include_path->value, index);

	next:
		include = strchr(end, '\n');
		length = strlen(include);
	}
	bs_free(include_path);
}

static bool _bsmod_queryShaderType(char* path, glslang_stage_t* out_stage, bs_ShaderType* out_type) {
	char* ext = bs_fileExtension(path);

	if (strcmp(ext, "comp") == 0) {
		*out_stage = GLSLANG_STAGE_COMPUTE;
		*out_type = BS_SHADER_STAGE_COMPUTE_BIT;
	}
	else if (strcmp(ext, "geom") == 0) {
		*out_stage = GLSLANG_STAGE_GEOMETRY;
		*out_type = BS_SHADER_STAGE_GEOMETRY_BIT;
	}
	else if (strcmp(ext, "tesc") == 0) {
		*out_stage = GLSLANG_STAGE_TESSCONTROL;
		*out_type = BS_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
	}
	else if (strcmp(ext, "tese") == 0) {
		*out_stage = GLSLANG_STAGE_TESSEVALUATION;
		*out_type = GLSLANG_STAGE_TESSEVALUATION;
	}
	else if (strcmp(ext, "vert") == 0) {
		*out_stage = GLSLANG_STAGE_VERTEX;
		*out_type = BS_SHADER_STAGE_VERTEX_BIT;
	}
	else if (strcmp(ext, "frag") == 0) {
		*out_stage = GLSLANG_STAGE_FRAGMENT;
		*out_type = BS_SHADER_STAGE_FRAGMENT_BIT;
	}
	else {
		return BS_RESULT_GENERAL_ERROR;
	}

	return BS_RESULT_OK;
}

static void _bsmod_packBindings(spvc_compiler compiler, spvc_resources resources, bsmod_Package* package, spvc_resource_type type, bs_ShaderType shader_type) {
	spvc_result result;

	size_t bindings_count = 0;
	spvc_reflected_resource* resource_list = NULL;
	result = spvc_resources_get_resource_list_for_type(resources, type, &resource_list, &bindings_count);

	if (result != SPVC_SUCCESS) {
		BSMOD_WARN_SPVC_ERROR("spvc_resources_get_resource_list_for_type", result,);
		return BS_RESULT_GENERAL_ERROR;
	}

	bs_BindTypeIndex bind_type = bsmod_convertBindType(type);
	for (int i = 0; i < bindings_count; i++) {
		spvc_reflected_resource* resource = resource_list + i;
		
		_bsmod_packBinding(compiler, resource, package, bind_type, shader_type);
	}
}

BSMODAPI bs_Result _bsmod_compileShader(char* path, char* name, char* package_name) {
	bs_Result bs_result = BS_RESULT_OK;

	bs_String* glsl; 
	bs_result = bs_loadFile(&glsl, path, strlen(path));
	if (bs_result != BS_RESULT_OK)
		return bs_result;
	//char* name = bs_fileName(path);
	
//	_bsmod_writeReferences(path, glsl);

	glslang_stage_t stage;
	bs_ShaderType type;
	bs_result = _bsmod_queryShaderType(path, &stage, &type);
	if (bs_result != BS_RESULT_OK) {
		return bs_result;
	}

	bsmod_Package* package = _bsmod_ensurePackage(package_name);
	
	const glslang_input_t input = {
		.language = GLSLANG_SOURCE_GLSL,
		.stage = stage,
		.client = GLSLANG_CLIENT_VULKAN,
		.client_version = GLSLANG_TARGET_VULKAN_1_3,
		.target_language = GLSLANG_TARGET_SPV,
		.target_language_version = GLSLANG_TARGET_SPV_1_5,
		.code = glsl->value,
		.default_version = 450,
		.default_profile = GLSLANG_NO_PROFILE,
		.force_default_version_and_profile = false,
		.forward_compatible = false,
		.messages = GLSLANG_MSG_DEFAULT_BIT,
		.resource = glslang_default_resource(),
	};

	glslang_shader_t* shader = glslang_shader_create(&input);
	glslang_program_t* program = NULL;
	bs_U32* spirv = NULL;
	if (!glslang_shader_preprocess(shader, &input)) {
		bs_warnF("Failed to preprocess \"%s\"\n%s\n%s\n", path, glslang_shader_get_info_log(shader), glslang_shader_get_info_debug_log(shader)); // TODO: bsmod warn
		goto destroy;
	}

	if (!glslang_shader_parse(shader, &input)) {
		bs_warnF("Failed to parse \"%s\"\n%s\n%s\n", path, glslang_shader_get_info_log(shader), glslang_shader_get_info_debug_log(shader)); // TODO: bsmod warn
		goto destroy;
	}

	program = glslang_program_create();
	glslang_program_add_shader(program, shader);

	if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
		bs_warnF("Failed to link \"%s\"\n%s\n%s\n", path, glslang_shader_get_info_log(shader), glslang_shader_get_info_debug_log(shader)); // TODO: bsmod warn
		goto destroy;
	}

	glslang_spv_options_t options = {
		.generate_debug_info = true,
		.disable_optimizer = true,
	};
	glslang_program_SPIRV_generate_with_options(program, stage, &options);

	bs_U64 size = glslang_program_SPIRV_get_size(program);
	spirv = malloc(size * sizeof(bs_U32));
	glslang_program_SPIRV_get(program, spirv);

	const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
	if (spirv_messages) 
		bs_warnF("%s\b", spirv_messages);

	spvc_result result;
	spvc_compiler compiler;
	spvc_reflected_resource* data;
	spvc_parsed_ir ir = NULL;
	spvc_resources resources = NULL;

	result = spvc_context_parse_spirv(_bsmod_compiler_context_, spirv, size, &ir);
	if (result != SPVC_SUCCESS) {
		BSMOD_WARN_SPVC_ERROR("spvc_context_parse_spirv", result,);
		return BS_RESULT_GENERAL_ERROR;
	}

	result = spvc_context_create_compiler(_bsmod_compiler_context_, SPVC_BACKEND_GLSL, ir, SPVC_CAPTURE_MODE_TAKE_OWNERSHIP, &compiler);
	if (result != SPVC_SUCCESS) {
		BSMOD_WARN_SPVC_ERROR("spvc_context_create_compiler", result, );
		return BS_RESULT_GENERAL_ERROR;
	}

	result = spvc_compiler_create_shader_resources(compiler, &resources);
	if (result != SPVC_SUCCESS) {
		BSMOD_WARN_SPVC_ERROR("spvc_compiler_create_shader_resources", result, );
		return BS_RESULT_GENERAL_ERROR;
	}

	bs_result = _bsmod_packShader(compiler, resources, spirv, size * sizeof(bs_U32), type, package, name);
	if (bs_result != BS_RESULT_OK) {
		return bs_result;
	}

	spvc_resource_type resource_types[] = {
		SPVC_RESOURCE_TYPE_STORAGE_BUFFER,
		SPVC_RESOURCE_TYPE_UNIFORM_BUFFER,
		SPVC_RESOURCE_TYPE_SEPARATE_IMAGE,
		SPVC_RESOURCE_TYPE_SUBPASS_INPUT,
		SPVC_RESOURCE_TYPE_SEPARATE_SAMPLERS,
		SPVC_RESOURCE_TYPE_SAMPLED_IMAGE,
		SPVC_RESOURCE_TYPE_ACCELERATION_STRUCTURE,
		SPVC_RESOURCE_TYPE_STORAGE_IMAGE,
	};
	size_t resource_types_count = sizeof(resource_types) / sizeof(*resource_types);

	for (int i = 0; i < resource_types_count; i++) {
		_bsmod_packBindings(compiler, resources, package, resource_types[i], type);
	}

	//result = _bsmod_packBinding();
	//result = _bsmod_packShaderReferences();

destroy:
	if (glsl)
		bs_free(glsl);
//if (result)
//	bs_free(result);

	if (program)
		glslang_program_delete(program);
	if (shader)
		glslang_shader_delete(shader);
	if (spirv)
		free(spirv);
	return bs_result;
}

static void ls_reflectionError(void* param, const char* error) {
	if (strcmp(error, "Declared struct in block cannot be empty.") == 0)
		return;

	bs_warnF("Reflection error: %s\n", error); // TODO: bsmod warn

	//ls_throw("%s\n", error);
}

BSMODAPI void _bsmod_iniCompiler() {
	spvc_context_create(&_bsmod_compiler_context_);
	spvc_context_set_error_callback(_bsmod_compiler_context_, ls_reflectionError, NULL);
	glslang_initialize_process();
}

BSMODAPI void _bsmod_destroyCompiler() {
	glslang_finalize_process();
	spvc_context_destroy(_bsmod_compiler_context_);
}