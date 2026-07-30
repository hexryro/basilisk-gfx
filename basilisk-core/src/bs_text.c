
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include <basilisk-core.h>
#include <bs_internal.h>



  /*==============================================================================
   * Font Format
   *============================================================================*/

BSAPI bs_vec2 _bs_textDimensions(bs_Font* font, char* name, int length) {
    float width = 0.0;
    float layout_scale = ((float)font->size / (float)font->units_per_em);

    for (int i = 0; i < length; i++) {
        char c = font->table[name[i]];
        int index = font->table[c];
        if (index >= font->atlas->count)
            index = 0;
        float spacing = font->glyphs[index].advance_width * layout_scale;
        width += spacing;
        // width += name[i] == ' ' ? font->spacing * layout_scale : _bs_atlasSize(font->atlas, c).x;
    }

    return BS_V2(width, font->height);
}

BSAPI void _bs_destroyFont(bs_Font* font) {
    if (font->atlas)
        _bs_destroyAtlas(font->atlas);
    //	if (font->fragment_shader)
    //		_bs_destroyShader(font->fragment_shader);

    _bs_resetObject(&font->head, sizeof(bs_Font));
}

BSAPI void _bs_bindFont(bs_Font* font, bs_Sampler* sampler, int bind_set, int bind_point) {
    _bs_bindImages(bind_set, bind_point, &(bs_ImageDescriptor) {
        .image = font->atlas->image,
        .layout = BS_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        .sampler = sampler,
    }, 1);
}

BSAPI bs_Result _bs_loadFont(bs_Object* object, int package_id, const char* resource_name, const char* alphabet, float spacing, bs_U32 flags) {
    /*
    bs_Result result;

    bs_Font* font = object->font;

    if (object->flags & BS_OBJECT_ALREADY_EXISTS && !(object->flags & BS_OBJECT_FORCE_DESTROY)) {
        return BS_RESULT_OK;
    }

    _bs_destroyFont(font);

    bs_Resource* resource;
    result = _bs_loadResource(package_id, 0, &resource, resource_name, strlen(resource_name));
    if (result != BS_RESULT_OK) {
        return result;
    }

    bs_BfntHeader* header = resource->data->value;
    if (header->magic != 0x746E6662) {
        _bs_warnF("Font \"%s\" is corrupted", resource_name);
        return BS_RESULT_CORRUPTED;
    }

    if (header->version != 1) {
        _bs_warnF("Font version %d is not supported", header->version);
        return BS_RESULT_NOT_SUPPORTED;
    }

    bs_Object* atlas_object = BS_ATLAS(-1, 0, 0);
    _bs_loadAtlasMemory(atlas_object, package_id, resource->name, resource->data->value + header->batl_offset, 0);
    if (atlas_object->atlas->count <= 0) {
        _bs_warnF("Font \"%s\" has 0 glyphs", resource_name);
        _bs_destroyFont(font);
        return BS_RESULT_ZERO_ALLOC;
    }

    font->spacing = spacing;
    font->alphabet = alphabet;
    font->atlas = atlas_object->atlas;
    font->size = header->size;
    font->units_per_em = header->units_per_em;
    font->height = header->line_height;
    font->glyphs = _bs_malloc(font->atlas->count * sizeof(*font->glyphs));
    font->pairs_count = header->kerning_pairs_count;

    if (font->units_per_em == 0)
        font->units_per_em = 1;

    unsigned char* offset = resource->data->value + sizeof(bs_BfntHeader);

    if (font->pairs_count > 0) {
        font->pairs = _bs_malloc(font->pairs_count * sizeof(*font->pairs));

        for (int i = 0; i < font->pairs_count; i++) {
            bs_BfntKerningPair* pair = offset;
            font->pairs[i].value = pair->value;
            font->pairs[i].right = pair->right;

            offset += sizeof(bs_BfntKerningPair);
        }
    }

    for (int i = 0; i < header->glyphs_count; i++) {
        bs_BfntGlyph* glyph = offset;

        font->glyphs[i].advance_width = glyph->advance_width;
        font->glyphs[i].left_side_bearing = glyph->left_side_bearing;
        font->glyphs[i].kerning_pair_offset = glyph->kerning_pair_offset;
        font->glyphs[i].kerning_pair_count = glyph->kerning_pair_count;
        font->glyphs[i].y_offset = glyph->y_offset;
        font->min_y_shift = BS_MIN(font->min_y_shift, glyph->y_offset);
        offset += sizeof(bs_BfntGlyph);
    }

    memcpy(font->table, header->ascii_table, 256);

    resource->font = font;
    */
    return BS_RESULT_OK;
}