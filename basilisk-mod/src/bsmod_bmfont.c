
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
    int chars_count;

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

static void _bsmod_peekBMFont(FILE* file, bsmod_BMFont* out, int* out_offset) {
    bsmod_BMFont font = { 0 };

    char line[512];
    int c;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "info ", 5) == 0) {
            c = sscanf(line, "info face=\"%*[^\"]\" size=%d", &font.size);
            if (c <= 0) {
                bs_warnF("Could not get bmfont size");
            }
        }
        else if (strncmp(line, "common ", 7) == 0) {
            c = sscanf(line, "common lineHeight=%d base=%d", &font.line_height, &font.base);
        }
        else if (strncmp(line, "chars count=", 12) == 0) {
            c = sscanf(line, "chars count=%d", &font.chars_count);
        }
        else if (strncmp(line, "kernings count=", 15) == 0) {
            c = sscanf(line, "kernings count=%d", &font.kerning_pairs_count);
        }
    }

    *out_offset = c;
    *out = font;
}

static void _bsmod_loadBMFontMemory(FILE* file, bsmod_BMFont* inout, int offset) {
    inout->chars = bs_calloc(inout->chars_count, sizeof(bsmod_BMChar));
    inout->kerning_pairs = bs_calloc(inout->kerning_pairs_count, sizeof(bsmod_BMKerning));

    fseek(file, offset, 0);

    char line[512];
    int char_idx = 0;
    int kern_idx = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "char ", 5) == 0)
            _bsmod_parseCharLine(line, &inout->chars[char_idx++]);
        else if (strncmp(line, "kerning ", 8) == 0)
            _bsmod_parseKerningLine(line, &inout->kerning_pairs[kern_idx++]);
    }

    fclose(file);
}

static bs_Result _bsmod_loadBMFont(const char* path, bsmod_BMFont* out) {
    bsmod_BMFont font;

    FILE* file = fopen(path, "r");
    if (!file)
        return BS_RESULT_FAILED_TO_READ;

    int offset = 0;
    _bsmod_peekBMFont(file, &font, &offset);
    _bsmod_loadBMFontMemory(file, &font, offset);

    fclose(file);
    *out = font;

    return BS_RESULT_OK;
}

static void _bsmod_destroyBMFont(bsmod_BMFont* bmfont) {
    bs_free(bmfont->chars);
    bs_free(bmfont->kerning_pairs);
}

typedef struct {
    int count;
    size_t glyph_offset;
    size_t batl_offset;
    unsigned char* data;

    char* ascii_table;

    bsmod_BMFont expected;
} bsmod_PackBMFontParams;

static bs_Result _bsmod_packBMFont(bs_FileInfo info, bsmod_PackBMFontParams* params) {
    const int channels_count = 4;
    bs_Result result;

   /**
    Load resources
    */
    static bs_String* name;
    char* ext = bs_fileExtension(info.path);
    if (!ext) 
        return result;

    ext[-1] = '\0';
    name = bs_stringF(name, "%s.fnt", ext);
    ext[-1] = '.';

    bsmod_BMFont font;
    result = _bsmod_loadBMFont(name->value, &font);
    if (result != BS_RESULT_OK)
        return result;

    ext[-1] = '\0';
    name = bs_stringF(name, "%s.png", ext);
    ext[-1] = '.';

    bs_PngData png_data;
    result = bs_loadPng(name->value, 4, &png_data);
    if (result != BS_RESULT_OK) {
        _bsmod_destroyBMFont(&font);
        return result;
    }

   /**
    */

    unsigned char* offset = params->data + params->batl_offset;

    for (int i = 0; i < font.kerning_pairs_count; i++) {
        bs_BfntKerningPair* pair = offset;
        pair->right = font.kerning_pairs[i].second;
        pair->value = font.kerning_pairs[i].amount;

        offset += sizeof(bs_BfntKerningPair);
    }

    for (int i = 0; i < font.chars_count; i++) {
        bs_BfntGlyph* glyph = offset;
        bsmod_BMChar* g = &font.chars[i];
        int code = g->id;

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
        .binary_offset = params->batl_offset,
        .width = png_data.width,
        .height = png_data.height,
        .channels_count = channels_count,
        .images_count = font.chars_count,
    };
    offset += sizeof(bs_BatlHeader);

    for (int i = 0; i < font.chars_count; i++) {
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

    memcpy(offset, png_data.data, atlas_size);
    memcpy(bfnt, &header, sizeof(bs_BfntHeader));

    return result;
}

static bs_Result _bsmod_findFirstFontFile(bs_FileInfo info, bsmod_PackBMFontParams* params) {
    if (!bs_fileExtensionIs(info.path, "fnt"))
        return BS_RESULT_OK;

    FILE* file = fopen(info.path, "r");
    if (!file)
        return BS_RESULT_FAILED_TO_READ;

    int offset;
    _bsmod_peekBMFont(file, &params->expected, &offset);

    ; ()

    fseek(file, offset, 0);

    char line[512];
    int char_idx = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "char ", 5) == 0) {
            bsmod_BMChar bmchar;
            _bsmod_parseCharLine(line, &bmchar);
            params->ascii_table[bmchar.id] = char_idx;
        }
    }

    fclose(file);

    return BS_RESULT_GENERAL_ERROR; // stop iterating
}

BSMODAPI bs_Result _bsmod_packBMFonts(char* package_name, char* directory_path, char* resource_name, int resource_name_length) {
    bs_Result result;

    bs_BfntHeader header = {
        .magic = 0x746E6662,
        .version = 1,
    };

    bsmod_PackBMFontParams params = {
        .ascii_table = header.ascii_table,
    };

    bs_foreachFile(_bsmod_findFirstFontFile, &params, directory_path, strlen(directory_path));

    int kerning_pairs_count = params.expected.kerning_pairs_count;
    int chars_count = params.expected.chars_count;

    size_t bfnt_size, batl_size;

    bfnt_size = sizeof(bs_BfntHeader);
    bfnt_size += kerning_pairs_count * sizeof(bs_BfntKerningPair);
    bfnt_size += chars_count * sizeof(bs_BfntGlyph);

    batl_size = sizeof(bs_BatlHeader);
    batl_size += sizeof(bs_BatlPointer);
    batl_size += chars_count * sizeof("\n");

    size_t total_size_excluding_binary = bfnt_size + batl_size;

    bs_foreachFile(_bsmod_packBMFont, &params, directory_path, strlen(directory_path));

    result = _bsmod_packResource(BS_RESOURCE_FONT, bfnt, total_size, package_name, resource_name, resource_name_length);

   // if (result != BS_RESULT_OK)
   //     return result;

    return result;
}