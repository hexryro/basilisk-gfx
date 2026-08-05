
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

#include <inttypes.h>

const char* _bsgfx_material_categories_[BSGFX_MATERIAL_CATEGORY_COUNT] = {
    [BSGFX_MATERIAL_CATEGORY_NONE] = NULL,
    [BSGFX_MATERIAL_CATEGORY_UI_COLOR_SCHEME] = "BSMOD UI Color Scheme",
};

bs_List _bsgfx_materials_ = { .unit_size = sizeof(bsgfx_Material), .increment = 64 };



  /*==============================================================================
   * Materials
   *============================================================================*/

BSGFXAPI const char* _bsgfx_materialCategoryName(bsgfx_MaterialCategory category) {
    return _bsgfx_material_categories_[category];
}

BSGFXAPI bs_List* _bsgfx_materials() {
    return &_bsgfx_materials_;
}

BSGFXAPI bsgfx_Material* _bsgfx_queryMaterialHash(bs_U64 hash) {
    for (int i = 0; i < _bsgfx_materials_.count; i++) {
        bsgfx_Material* material = bs_fetchUnit(&_bsgfx_materials_, i);
        if (material->hash == hash)
            return material;
    }

    return NULL;
}

BSGFXAPI bsgfx_Material* _bsgfx_queryMaterial(const char* name) {
    return _bsgfx_queryMaterialHash(bs_stringHash(name));
}

BSGFXAPI bsgfx_Material* _bsgfx_fetchMaterial(int id) {
    return bs_fetchUnit(&_bsgfx_materials_, id);
}

 /**
  Create material
  */
BSGFXAPI bsgfx_Material* _val_bsgfx_materialN(char* name, int name_length) {
    BSGFX_VALIDATE(bs_exists(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS), NULL,);

    return _bsgfx_materialN(name, name_length);
}

BSGFXAPI bsgfx_Material* _bsgfx_materialN(char* name, int name_length) {
    bs_Buffer* materials_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS)->buffer;
    bsgfx_MaterialContract* contract = bs_bufferMap(bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS)->buffer);

    bsgfx_Material* existing = _bsgfx_queryMaterial(name);

    if (existing)
        return existing;

    return bs_pushBack(&_bsgfx_materials_, &(bsgfx_Material) {
        .name = strdup(name),
        .hash = bs_stringHash(name),
        .contract = contract + _bsgfx_materials_.count,
        .id = _bsgfx_materials_.count,
        .json_index = -1,
    });
}

void _bsgfx_allocateMaterials() {
    bs_Result result;
    
    result = bs_buffer(BS_BUFFER(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS, false), BSGFX_MAX_MATERIALS_COUNT * sizeof(bsgfx_MaterialContract),
        BS_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    if (result != BS_RESULT_OK)
        return;

    bs_Buffer* materials_buffer = bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS)->buffer;
    
    result = bs_mapBuffer(materials_buffer, BS_U32_MAX);
    if (result != BS_RESULT_OK)
        return;

    bs_bindBuffer(BSGFX_SET_MATERIALS, BSGFX_BINDING_MATERIALS, materials_buffer);

    bsgfx_Material* material = bs_fetchUnit(&_bsgfx_materials_, _bsgfx_materialN(BS_CONSTANT_STRING("blank"))->id);
    material->contract->color = BS_V4(1.0, 1.0, 1.0, 1.0);
}

BSGFXAPI void _bsgfx_loadMaterials() {
    /*
    return;

    bs_Json json;
    bs_loadJson(&json, BS_CONSTANT_STRING("resources/materials.json"));

    bs_JsonValue root = bs_fetchJson(&json, BS_JSON_ARRAY, BS_CONSTANT_STRING("$"));
    
    for (int i = 0; i < root.size; i++) {
        bs_Json material_json = bs_jsonRoot(&json, root.as_array.as_objects[i]);

        bs_F64* color = bs_fetchJson(&material_json, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("color[:4]")).as_array.as_numbers;
        bs_F64* tile_color = bs_fetchJson(&material_json, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("tile_color[:4]")).as_array.as_numbers;
        bs_F64* tile_color_add = bs_fetchJson(&material_json, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("tile_color_add[:4]")).as_array.as_numbers;

        int image_size = bs_fetchJson(&material_json, BS_JSON_UNDEFINED, BS_CONSTANT_STRING("image.size")).as_number;

        char* material_name = bs_fetchJson(&material_json, BS_JSON_STRING, BS_CONSTANT_STRING("name")).as_string;

        bsgfx_Material* material = _bsgfx_material(material_name, strlen(material_name));
        material->json_index = i;
        material->editable = true;
        *material->contract = (bsgfx_MaterialContract){
            .color = color ? BSGFX_RGBA(color[0], color[1], color[2], color[3]) : (bs_vec4) { 1.0, 1.0, 1.0, 1.0 },
           // .image = image_size ? _bsgfx_queryTexture(image_size, bs_fetchJson(&material_json, BS_JSON_STRING, "image.name").as_string) : 0,
           // .scale = image_size,
        };
    }

#ifndef _DEBUG
    // bs_unmapBuffer(materials_buffer);
#endif
    bs_destroyJson(&json);

    bs_infoF("Loaded %d materials\n", _bsgfx_materials_.count);
    */
}

// highlighting is kinda scuffed

BSGFXAPI void _bsgfx_highlightMaterial(int material_id, bool auto_unhighlight) {
    bsgfx_Material* material = bs_fetchUnit(&_bsgfx_materials_, material_id);
    if (material->highlighted)
        return;

    bsgfx_MaterialContract* contract = bs_bufferMap(bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS)->buffer);
    contract += material_id;

    bs_v3Add(&contract->color.xyz, &(bs_vec3) { 0.25, 0.25, 0.25 }, &contract->color.xyz);

    material->highlighted = true;
    material->auto_unhighlight = auto_unhighlight;
}

BSGFXAPI void _bsgfx_unhighlightMaterial(int material_id) {
    bsgfx_Material* material = bs_fetchUnit(&_bsgfx_materials_, material_id);
    bsgfx_MaterialContract* contract = bs_bufferMap(bs_fetch(BSGFX_BUFFERS, BSGFX_BUFFER_MATERIALS)->buffer);
    contract += material_id;

    bs_v3Sub(&contract->color.xyz, &(bs_vec3) { 0.25, 0.25, 0.25 }, & contract->color.xyz);

    material->highlighted = false;
}

BSGFXAPI void _bsgfx_tickMaterials() {
    for (int i = 0; i < _bsgfx_materials_.count; i++) {
        bsgfx_Material* material = bs_fetchUnit(&_bsgfx_materials_, i);
        if (material->highlighted && material->auto_unhighlight)
            _bsgfx_unhighlightMaterial(i);
    }
}