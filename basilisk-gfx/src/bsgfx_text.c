
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

#define KB_TEXT_SHAPE_IMPLEMENTATION
#define KB_TEXT_SHAPE_STATIC
#include <kb/kb_text_shape.h>

#define WIDTH   640
#define HEIGHT  480

unsigned char image[HEIGHT][WIDTH];


BSAPI bs_vec2 _bsgfx_textDimensions(bsgfx_Font* font, char* name, int length) {
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


BSGFXAPI bs_Result _bsgfx_loadFont(int package_id, const char* name, bs_U32 flags, bs_Resource **out) {
    bs_Result result;

    bs_Resource* resource;
    result = bs_loadResourceN(package_id, flags, &resource, name, strlen(name));
    if (result != BS_RESULT_OK)
        return result;

    unsigned char* data = resource->data->value;

    bs_U32 magic = bs_getLittleEndian32(data + BS_BFNT_MAGIC_OFFSET);
    if (magic != BS_BFNT_MAGIC) {
        BS_WARN_INVALID_MAGIC("font", name);
        return BS_RESULT_CORRUPTED;
    }

    bs_U32 version = bs_getLittleEndian32(data + BS_BFNT_VERSION_OFFSET);
    if (version != 1) {
        BS_WARN_UNSUPPORTED_VERSION("font", name);
        return BS_RESULT_NOT_SUPPORTED;
    }

    bs_U16 blocks_count = bs_getLittleEndian16(data + BS_BFNT_1_BLOCKS_COUNT_OFFSET);

    unsigned char* blocks_offset = data;
    for (int i = 0; i < blocks_count; i++) {
        bs_U32 code_start = bs_getLittleEndian32(blocks_offset + BS_BFNT_1_BLOCK_START_OFFSET);
        bs_U16 code_count = bs_getLittleEndian16(blocks_offset + BS_BFNT_1_BLOCKS_COUNT_OFFSET);

        blocks_offset += BS_BFNT_1_BLOCK_SIZE;
    }

    return BS_RESULT_OK;
}

BSGFXAPI void _bsgfx_test() {
    int package_id = 0;
    if (bs_loadPackage(&package_id, "content/basilisk-fonts") != BS_RESULT_OK)
        return;

    bs_Resource* resource;
    _bsgfx_loadFont(package_id, "project/fonts/segoeui.ttf", 0, &resource);


    //_bsgfx_loadFont(package_id, "")

   // _bsgfx_test2("notonaskharabic.ttf", u8"ششش");
}
