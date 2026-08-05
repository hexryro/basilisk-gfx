
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

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library _freetype_library = NULL;

static void _bsmod_packFontAtlas(bs_U32 first_codepoint, bs_U16 codepoints_count) {
	for (int i = 0; i < codepoints_count; i++) {
		bs_U32 codepoint = first_codepoint;
	}
}

/*
			<param><type>char*</type><name>resource_name</name></param>
			<param><type>int</type><name>resource_name_length</name></param>
*/

void _bsmod_iniFont() {
}

bs_Result _bsmod_convertFreetypeError(FT_Error error) {
	switch (error) {
	case 0: return BS_RESULT_OK;
	}

	return BS_RESULT_GENERAL_ERROR;
}

BSMODAPI bs_Result _bsmod_packFont(
	char* package_path, 
	char* ttf_path, 
	bsmod_UnicodeBlockRange blocks[], 
	int blocks_count, 
	int pt_sizes[], 
	int pt_sizes_count,
	const char* resource_name,
	int resource_name_length)
{
	const int padding = 0;

	bsmod_AtlasPacker packer = bsmod_createAtlasPacker();

	FT_Error error;
	FT_Face face;

	if (!_freetype_library) {
		error = FT_Init_FreeType(&_freetype_library);
		if (error) {
			BSMOD_WARN_FREETYPE_ERROR("FT_Init_FreeType", error, );
			return _bsmod_convertFreetypeError(error);
		}
	}

	error = FT_New_Face(_freetype_library, ttf_path, 0, &face);
	if (error) {
		BSMOD_WARN_FREETYPE_ERROR("FT_Set_Char_Size", error, );
		return _bsmod_convertFreetypeError(error);
	}

	bs_Result result;

   /**
    Allocate memory
    */
	bs_String* ttf = NULL;
	result = bs_loadFile(&ttf, ttf_path);
	if (result != BS_RESULT_OK)
		return result;

	size_t total_size = 0;

	total_size += BS_BFNT_1_HEADER_SIZE * sizeof(bs_U32);
	total_size += blocks_count * BS_BFNT_1_BLOCK_SIZE;
	total_size += ttf->len;

	for (int i = 0; i < blocks_count; i++) {
		assert(blocks[i].block >= 0);
		assert(blocks[i].block < BS_BFNT_1_BLOCK_LOOKUP_LENGTH);
	}

	unsigned char* batl = bs_malloc(total_size);

	memset(batl, 0, BS_BFNT_1_HEADER_SIZE);

	bs_setLittleEndian32(BS_BFNT_MAGIC, batl + BS_BFNT_MAGIC_OFFSET);
	bs_setLittleEndian32(1, batl + BS_BFNT_VERSION_OFFSET);
	bs_setLittleEndian16(blocks_count, batl + BS_BFNT_1_BLOCKS_COUNT_OFFSET);

   /**
    Font specific codepoint ranges
	*/
	unsigned char* block_offset = batl + BS_BFNT_1_BLOCKS_OFFSET;

	for (int i = 0; i < blocks_count; i++) {
		bs_setLittleEndian16(i, batl + BS_BFNT_1_BLOCK_LOOKUP_OFFSET + blocks[i].block * sizeof(bs_U16));

		bs_setLittleEndian32(blocks[i].offset, block_offset + BS_BFNT_1_BLOCK_START_OFFSET);
		bs_setLittleEndian32(blocks[i].count, block_offset + BS_BFNT_1_BLOCK_LENGTH_OFFSET);
		bs_setLittleEndian32(blocks[i].size, block_offset + BS_BFNT_1_BLOCK_SIZE_OFFSET);

		if (blocks[i].rasterize) {
			for (int j = 0; j < pt_sizes_count; j++) {

				const int dpi = 100;
				int pt_size = pt_sizes[j];

				error = FT_Set_Char_Size(face, pt_size * 64, 0, dpi, 0);
				if (error) {
					BSMOD_WARN_FREETYPE_ERROR("FT_Set_Char_Size", error, );
					continue;
				}

				for (int k = 0; k < blocks[i].count; k++) {
					FT_ULong codepoint = (FT_ULong)(blocks[i].offset + k);
					FT_UInt glyph_id = FT_Get_Char_Index(face, codepoint);

					if (glyph_id == 0)
						continue;

					if (FT_Load_Glyph(face, glyph_id, FT_LOAD_DEFAULT))
						continue;

					if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
						continue;

					if (face->glyph->bitmap.width == 0)
						continue;

					if (face->glyph->bitmap.rows == 0)
						continue;

					bsmod_packAtlasTextureF(&packer, face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, "%d", glyph_id);
				}
			}
		}

		block_offset += BS_BFNT_1_BLOCK_SIZE;
	}

	FT_Done_Face(face);

   /**
    Copy TTF data
    */
	unsigned char* ttf_offset = block_offset;

	memcpy(ttf_offset, ttf->value, ttf->len);

	bs_free(ttf);

	//result = bs_savePng(batl + header.binary_offset, BS_IV2(width, height), BS_PNG_RGBA, BS_CONSTANT_STRING("test.png"));

	result = _bsmod_packAtlas(&packer, 1024, 1024, 1, package_path, resource_name, true);
	if (result != BS_RESULT_OK)
		return result;

	result = _bsmod_packResource(BS_RESOURCE_FONT, batl, total_size, package_path, resource_name);

	bs_free(batl);
	//	if (result != BS_RESULT_OK)
	//		return result;

	return result;
}