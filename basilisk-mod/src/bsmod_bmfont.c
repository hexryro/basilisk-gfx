
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

typedef struct {
    int id;
    int x, y;
    int width, height;
    int x_offset, y_offset;
    int x_advance;
} bsmod_BMChar;

typedef struct {
    int first;
    int second;
    int amount;
} bsmod_BMKerning;

typedef struct {
    int size;

    bsmod_BMChar* chars;
    int char_count;

    bsmod_BMKerning* kerning_pairs;
    int kerning_pairs_count;

    int line_height;
    int base;
} bsmod_BMFont;

static void _bsmod_parseCharLine(const char* line, bsmod_BMChar* c) {
    sscanf(line, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d", &c->id, &c->x, &c->y, &c->width, &c->height, &c->x_offset, &c->y_offset, &c->x_advance);
}

static void _bsmod_parseKerningLine(const char* line, bsmod_BMKerning* k) {
    sscanf(line, "kerning first=%d second=%d amount=%d", &k->first, &k->second, &k->amount);
}

static bs_Result _bsmod_loadBMFont(const char* path, bsmod_BMFont* out) {
    bsmod_BMFont font = { 0 };

    FILE* f = fopen(path, "r");
    if (!f)
        return BS_RESULT_FAILED_TO_READ;

    char line[512];
    int charIdx = 0;
    int kernIdx = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "info ", 5) == 0) {
            sscanf(line, "info face=%*[^ ] size=%d", &font.size);
        }
        else if (strncmp(line, "common ", 7) == 0) {
            sscanf(line, "common lineHeight=%d base=%d", &font.line_height, &font.base);
        }
        else if (strncmp(line, "chars count=", 12) == 0) {
            sscanf(line, "chars count=%d", &font.char_count);
            font.chars = calloc(font.char_count, sizeof(bsmod_BMChar));
        }
        else if (strncmp(line, "kernings count=", 15) == 0) {
            sscanf(line, "kernings count=%d", &font.kerning_pairs_count);
            font.kerning_pairs = calloc(font.kerning_pairs_count, sizeof(bsmod_BMKerning));
        }
        else if (strncmp(line, "char ", 5) == 0)
            _bsmod_parseCharLine(line, &font.chars[charIdx++]);
        else if (strncmp(line, "kerning ", 8) == 0)
            _bsmod_parseKerningLine(line, &font.kerning_pairs[kernIdx++]);
    }

    fclose(f);
    *out = font;
    return BS_RESULT_OK;
}

BSMODAPI bs_Result _bsmod_packBMFont(char* package_name, char* bmfont_path, char* png_path, char* resource_name, int resource_name_length) {
    bs_Result result;

    const int channels_count = 4;

    bsmod_BMFont font;
    result = _bsmod_loadBMFont(bmfont_path, &font);
    if (result != BS_RESULT_OK)
        return result;

    bs_PngData png_data;
    result = bs_loadPng(png_path, channels_count, &png_data);
    if (result != BS_RESULT_OK)
        return result;

    const size_t bfnt_size = sizeof(bs_BfntHeader) + sizeof(bs_BfntKerningPair) * font.kerning_pairs_count + sizeof(bs_BfntGlyph) * font.char_count;
    const size_t batl_size = sizeof(bs_BatlHeader) + (sizeof(bs_BatlPointer) + sizeof("\n")) * font.char_count;

    bs_BfntHeader header = {
        .magic = 0x746E6662,
        .version = 1,
        .kerning_pairs_count = font.kerning_pairs_count,
        .glyphs_count = font.char_count,
        .line_height = font.line_height,
        .units_per_em = font.line_height, // good?
        .size = font.size,
        .batl_offset = bfnt_size,
    };

    const size_t total_size_excluding_binary = bfnt_size + batl_size;
    const size_t atlas_size = png_data.width * png_data.height * channels_count;
    const size_t total_size = total_size_excluding_binary + atlas_size;

    unsigned char* bfnt = bs_malloc(total_size);
    unsigned char* offset = bfnt + sizeof(bs_BfntHeader);

    for (int i = 0; i < font.kerning_pairs_count; i++) {
        bs_BfntKerningPair* pair = offset;
        pair->right = font.kerning_pairs[i].second;
        pair->value = font.kerning_pairs[i].amount;

        offset += sizeof(bs_BfntKerningPair);
    }

    for (int i = 0; i < font.char_count; i++) {
        bs_BfntGlyph* glyph = offset;
        bsmod_BMChar* g = &font.chars[i];
        int code = g->id;
        if (code < 256)
            header.ascii_table[code] = i;

        *glyph = (bs_BfntGlyph) {
            .code = code,
            .y_offset = font.base - (g->y_offset + g->height),
            .advance_width = g->x_advance,
            .left_side_bearing = g->x_offset,
            .kerning_pair_offset = 0,
            .kerning_pair_count = 0,
        };

        offset += sizeof(bs_BfntGlyph);
    }

   /**
    Atlas
    */
    bs_BatlHeader* batl_header = offset;
    *batl_header = (bs_BatlHeader) {
        .magic = BS_BATL_MAGIC,
        .version = 1,
        .binary_offset = batl_size,
        .width = png_data.width,
        .height = png_data.height,
        .channels_count = channels_count,
        .images_count = font.char_count,
    };
    offset += sizeof(bs_BatlHeader);

    for (int i = 0; i < font.char_count; i++) {
        bs_BatlPointer* p = offset;
        bsmod_BMChar* g = &font.chars[i];

        *p = (bs_BatlPointer){
            .x = g->x,
            .y = g->y,
            .w = g->width,
            .h = g->height,
        };

        offset += sizeof(bs_BatlPointer) + sizeof("\n");
    }

    assert((total_size - (offset - bfnt)) == atlas_size);
    memcpy(offset, png_data.data, atlas_size);
    memcpy(bfnt, &header, sizeof(bs_BfntHeader));

    result = _bsmod_packResource(BS_RESOURCE_FONT, bfnt, total_size, package_name, resource_name, resource_name_length);

    free(font.kerning_pairs);
    free(font.chars);
    bs_free(bfnt);

   // if (result != BS_RESULT_OK)
   //     return result;

    return result;
}