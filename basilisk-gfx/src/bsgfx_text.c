
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

#include <basilisk-gfx.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdlib.h>
#include <string.h>
#include <uchar.h>

#define WIDTH   640
#define HEIGHT  480

unsigned char image[HEIGHT][WIDTH];


BSAPI bs_vec2 _bsgfx_textDimensions(bsgfx_Font* font, char* name, int length) {
    /*
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
    */
    return BS_V2(16, 16); // temp ofc
}

static int _bsgfx_queryPtSize(bsgfx_Font* font, int pt_size) {
    int id = -1;
    for (int i = 0; i < font->pt_sizes_count; i++) {
        id = i;
        if (font->pt_sizes[i] >= pt_size)
            return id;
    }

    return id;
}

static bsgfx_UnicodeBlock2* _bsgfx_queryUnicodeBlock(bsgfx_Font* font, char32_t c) {
    for (int j = 0; j < font->blocks_count; j++) {
        bsgfx_UnicodeBlock2* block = font->blocks + j;

        bs_U32 offset = block->offset;
        bs_U32 end = block->offset + block->count;

        if (c >= offset && c < end)
            return block;
    }

    return NULL;
}

static inline bsgfx_Glyph* _bsgfx_getGlyph(const bsgfx_Font* font, const bsgfx_UnicodeBlock2* block, char32_t c, int pt_size_id) {
    const int pt_offset = pt_size_id * block->count;
    int glyph_offset = block->glyphs_offset + pt_offset + (c - block->offset);
    assert(glyph_offset < font->glyphs_count);
    return font->glyphs + glyph_offset;
}

static inline float _bsgfx_convertDesignUnits(bsgfx_Font* font, float pt_size, float units) {
    return (units / (float)font->units_per_em) * pt_size;
}

BSGFXAPI void _bsgfx_instanceASCIITextN(bsgfx_InstanceSubtype* subtype, bsgfx_Font* font, bs_vec3 position, int pt_size, char* text, int text_length) {
    // TODO: check if basic latin block is available
    int pt_size_id = _bsgfx_queryPtSize(font, pt_size);
    assert(pt_size_id != -1);

    bsgfx_UnicodeBlock2* block = font->blocks;
    assert(block != NULL);
    // assert basic latin
    //assert(block->offset == 0);
    //assert(block->count == 127);

    bs_mat4 test_transform = BS_MAT4_IDENTITY;
    bs_m4Translate(&test_transform, &BS_V3(100.0, 100.0, 0.0), &test_transform);
    bs_m4Scale(&test_transform, &BS_V3(1024, 1024, 0), &test_transform);

  //  bsgfx_instanceQuad(subtype, bs_m4x3(&test_transform), BS_V4(0, 0, 1, 1), 0, 0, 0);
    if (block->offset != 0)
        return;
    if (block->count != 127)
        return;

    int glyph_pt_offset = pt_size_id * block->count;

    bs_vec2 next_glyph_placement = { 0 };
    bs_vec2 next_glyph_advance = { 0 };

    const float spacing = 8.0;
    const float temp_scale = 8.0;

    for (int i = 0; i < text_length; i++) {
        char c = text[i];
        if (c < 0)
            continue;

        if (c == ' ') {
            position.x += spacing;
            continue;
        }

        bsgfx_Glyph* glyph = _bsgfx_getGlyph(font, block, c, pt_size_id);

        bs_vec2 size = bs_atlasSize(font->atlas_object->atlas, glyph->atlas_index);
        bs_vec4 coords = bs_atlasCoordinates(font->atlas_object->atlas, glyph->atlas_index);

        bs_vec2 placement = next_glyph_placement;
        bs_vec2 advance = next_glyph_advance;

        next_glyph_placement = BS_V2(0, 0);
        next_glyph_advance = BS_V2(0, 0);

        bs_vec3 p = position;
        p.x += placement.x;
        p.y += placement.y;
        p.y += glyph->y_offset;

        if (i < (text_length - 1)) {
            char next = text[i + 1];
            //bsgfx_Glyph* next_glyph = _bsgfx_getGlyph(font, block, c, pt_size_id);

            //int next_index = font->table[next];

            int start = glyph->kerning_pair_start;
            int end = start + glyph->kerning_pair_count;

            for (int j = start; j < end; j++) {
                bsgfx_KerningPair* pair = font->kerning_pairs + j;

                if (next == pair->right) {
                    p.x += _bsgfx_convertDesignUnits(font, pt_size, pair->left_x_placement);
                    p.y += _bsgfx_convertDesignUnits(font, pt_size, pair->left_y_placement);

                    advance.x += _bsgfx_convertDesignUnits(font, pt_size, pair->left_x_advance);
                    advance.y += _bsgfx_convertDesignUnits(font, pt_size, pair->left_y_advance);

                    next_glyph_placement.x = _bsgfx_convertDesignUnits(font, pt_size, pair->right_x_placement);
                    next_glyph_placement.y = _bsgfx_convertDesignUnits(font, pt_size, pair->right_y_placement);

                    next_glyph_advance.x = _bsgfx_convertDesignUnits(font, pt_size, pair->right_x_advance);
                    next_glyph_advance.y = _bsgfx_convertDesignUnits(font, pt_size, pair->right_y_advance);

                    break;
                }
            }
        }

        bs_mat4 transform = BS_MAT4_IDENTITY;

        bs_m4Translate(&transform, &p, &transform);
        bs_m4Scale(&transform, &BS_V3(size.x * temp_scale, size.y * temp_scale, 0), &transform);

        bsgfx_instanceQuad(subtype, bs_m4x3(&transform), coords, 0, glyph->atlas_page, 0);

        // instanceAtlasTexture(glyph->atlas_page, glyph->atlas_index)

        position.x += ((float)glyph->x_advance / 64.0) * temp_scale;

        position.x += advance.x * temp_scale;
        position.y += advance.y;
        position.z += 0.01;
    }
}

BSGFXAPI void _bsgfx_instanceUnicodeTextN(bsgfx_InstanceSubtype* subtype, bsgfx_Font* font, bs_vec3 position, int pt_size, char32_t* text, int text_length) {
    int pt_size_id = _bsgfx_queryPtSize(font, pt_size);
    assert(pt_size_id != -1);

    for (int i = 0; i < text_length; i++) {
        char32_t c = text[i];

        bsgfx_UnicodeBlock2* block = _bsgfx_queryUnicodeBlock(font, c);

        if (!block)
            continue; // TODO: warn

        bsgfx_Glyph* glyph = _bsgfx_getGlyph(font, block, c, pt_size_id);

        position.x += glyph->x_advance;
    }
}

// TODO: _bsgfx_instanceShapedTextN()

BSGFXAPI bs_Result _bsgfx_loadFont(bs_Queue* queue, int package_id, const char* name, bs_U32 flags, bs_Resource **out) {
    *out = NULL;
    bs_Result result;

    bs_Resource* bfnt;
    result = bs_loadResourceN(package_id, flags, BS_RESOURCE_FONT, &bfnt, name, strlen(name));
    if (result != BS_RESULT_OK)
        return result;

    bs_Object* atlas_object = BS_ATLAS(-1, -1, 0);
    bs_loadAtlas(queue, atlas_object, package_id, 0, name);

    unsigned char* data = bfnt->data->value;

    bs_U32 magic = bs_getLittleEndian32(data + BFNT_MAGIC_OFFSET);
    if (magic != BFNT_MAGIC) {
        BS_WARN_INVALID_MAGIC("font", name);
        return BS_RESULT_CORRUPTED;
    }

    bs_U32 version = bs_getLittleEndian32(data + BFNT_VERSION_OFFSET);
    if (version != 1) {
        BS_WARN_UNSUPPORTED_VERSION("font", name);
        return BS_RESULT_NOT_SUPPORTED;
    }

    bsgfx_Font* font = bs_calloc(1, sizeof(bsgfx_Font));
    font->atlas_object = atlas_object;
    bfnt->model = font;

    bs_U16 blocks_count = bs_getLittleEndian16(data + BFNT_BLOCKS_COUNT_OFFSET);
    bs_U16 pt_sizes_count = bs_getLittleEndian16(data + BFNT_PT_SIZES_COUNT_OFFSET);
    bs_U32 glyphs_count = bs_getLittleEndian32(data + BFNT_GLYPHS_COUNT_OFFSET);
    bs_U16 kerning_pairs_count = bs_getLittleEndian16(data + BFNT_KERNING_PAIRS_COUNT_OFFSET);
    bs_U16 units_per_em = bs_getLittleEndian16(data + BFNT_UNITS_PER_EM);
    //bs_U32 glyphs_count = atlas_object->atlas->count;

    font->blocks_count = blocks_count;
    font->pt_sizes_count = pt_sizes_count;
    font->glyphs_count = glyphs_count;
    font->kerning_pairs_count = kerning_pairs_count;
    font->units_per_em = units_per_em;

    if (blocks_count > 0) font->blocks = bs_malloc(blocks_count * sizeof(bsgfx_UnicodeBlock2));
    if (pt_sizes_count > 0) font->pt_sizes = bs_malloc(pt_sizes_count * sizeof(int));
    if (glyphs_count > 0) font->glyphs = bs_malloc(glyphs_count * sizeof(bsgfx_Glyph));
    if (kerning_pairs_count > 0) font->kerning_pairs = bs_malloc(kerning_pairs_count * sizeof(bsgfx_KerningPair));

   /**
    Pt sizes
    */
    unsigned char* pt_size_offset = data + BFNT_POINTS_OFFSET;
    for (int i = 0; i < pt_sizes_count; i++) {
        font->pt_sizes[i] = bs_getLittleEndian32(pt_size_offset + BFNT_POINT_SIZE_OFFSET);
        pt_size_offset += BFNT_POINT_SIZE;
    }

   /**
    Unicode blocks
    */
    unsigned char* blocks_offset = pt_size_offset;
    for (int i = 0; i < blocks_count; i++) {
        bs_U32 code_start = bs_getLittleEndian32(blocks_offset + BFNT_BLOCK_START);
        bs_U16 code_count = bs_getLittleEndian16(blocks_offset + BFNT_BLOCK_LENGTH);
        bs_U32 glyphs_offset = bs_getLittleEndian32(blocks_offset + BFNT_BLOCK_GLYPHS);

        font->blocks[i] = (bsgfx_UnicodeBlock2) {
            .offset = code_start,
            .count = code_count,
            .glyphs_offset = glyphs_offset,
        };

        blocks_offset += BFNT_BLOCK_SIZE;
    }

   /**
    Glyphs
    */
    unsigned char* glyphs_offset = blocks_offset;
    for (int i = 0; i < glyphs_count; i++) {
        bs_U16 page = bs_getLittleEndian16(glyphs_offset + BFNT_GLYPH_PAGE);
        bs_U16 atlas_index = bs_getLittleEndian16(glyphs_offset + BFNT_GLYPH_ATLAS_INDEX);
        bs_U16 glyph_index = bs_getLittleEndian16(glyphs_offset + BFNT_GLYPH_GLYPH_INDEX);
        bs_U32 codepoint = bs_getLittleEndian32(glyphs_offset + BFNT_GLYPH_CODEPOINT);
        bs_I32 y_offset = bs_getLittleEndian32(glyphs_offset + BFNT_GLYPH_Y_OFFSET);
        bs_I32 x_advance = bs_getLittleEndian32(glyphs_offset + BFNT_GLYPH_X_ADVANCE);
        
        bs_U16 kern_start_pair = bs_getLittleEndian16(glyphs_offset + BFNT_GLYPH_KERNING_START);
        bs_U16 kern_count_pair = bs_getLittleEndian16(glyphs_offset + BFNT_GLYPH_KERNING_COUNT);

        assert(atlas_index < atlas_object->atlas->count);

        font->glyphs[i] = (bsgfx_Glyph) {
            .atlas_page = page,
            .atlas_index = atlas_index,
            .glyph_index = glyph_index,
            .x_advance = x_advance, // temp
            .y_advance = 16.0, // temp
            .kerning_pair_start = kern_start_pair,
            .kerning_pair_count = kern_count_pair,
            .y_offset = y_offset,
        };

        glyphs_offset += BFNT_GLYPH_SIZE;
    }

   /**
    Kerning pairs
    */
    unsigned char* kerning_pairs_offset = glyphs_offset;
    for (int i = 0; i < kerning_pairs_count; i++) {
        bs_U32 right = bs_getLittleEndian32(kerning_pairs_offset + BFNT_KERNING_PAIR_RIGHT);

        bs_I16 left_x_placement = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_LEFT_X_PLACEMENT);
        bs_I16 left_y_placement = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_LEFT_Y_PLACEMENT);
        bs_I16 left_x_advance = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_LEFT_X_ADVANCE);
        bs_I16 left_y_advance = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_LEFT_Y_ADVANCE);

        bs_I16 right_x_placement = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_RIGHT_X_PLACEMENT);
        bs_I16 right_y_placement = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_RIGHT_Y_PLACEMENT);
        bs_I16 right_x_advance = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_RIGHT_X_ADVANCE);
        bs_I16 right_y_advance = bs_getLittleEndian16(kerning_pairs_offset + BFNT_KERN_RIGHT_Y_ADVANCE);

        font->kerning_pairs[i] = (bsgfx_KerningPair) {
            .right = right,

            .left_x_placement = left_x_placement,
            .left_y_placement = left_y_placement,
            .left_x_advance = left_x_advance,
            .left_y_advance = left_y_advance,

            .right_x_placement = right_x_placement,
            .right_y_placement = right_y_placement,
            .right_x_advance = right_x_advance,
            .right_y_advance = right_y_advance,
        };

        kerning_pairs_offset += BFNT_KERNING_PAIR_SIZE;
    }

    *out = bfnt;
    return BS_RESULT_OK;
}

BSGFXAPI void _bsgfx_test() {
    int package_id = 0;
    if (bs_loadPackage(&package_id, "content/basilisk-fonts.bpak") != BS_RESULT_OK)
        return;

    bs_Queue* queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;

    bs_Resource* resource;
    _bsgfx_loadFont(queue, package_id, "project/fonts/segoeui.ttf", 0, &resource);

    bsgfx_Font* font = resource->model;
    bs_bindImage(BSGFX_SET_FONTS, BSGFX_BINDING_FONTS, font->atlas_object->atlas->image, bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler, BS_IMAGE_LAYOUT_GENERAL);

    //_bsgfx_loadFont(package_id, "")

   // _bsgfx_test2("notonaskharabic.ttf", u8"ششش");
}
