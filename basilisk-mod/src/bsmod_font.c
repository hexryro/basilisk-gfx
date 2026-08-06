
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
#include <stb_rect_pack/stb_rect_pack.h>
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

static unsigned char* _bsmod_getFontTextureData(bsmod_AtlasPacker* packer, int index) {
	bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, index);
	bs_List* bitmap = info->param;

	return bitmap->data + info->id1;
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

	total_size += BFNT_HEADER_SIZE * sizeof(bs_U32);
	total_size += blocks_count * BFNT_BLOCK_SIZE;
	total_size += pt_sizes_count * BFNT_POINT_SIZE;
	total_size += ttf->len;

	int total_glyphs_count = 0;
	for (int i = 0; i < blocks_count; i++) {
		assert(blocks[i].block >= 0);
		//assert(blocks[i].block < BFNT_BLOCK_LOOKUP_LENGTH);

		if (blocks[i].rasterize)
			total_glyphs_count += blocks[i].count * pt_sizes_count;
	}

	total_size += total_glyphs_count * BFNT_GLYPH_SIZE;

	unsigned char* data = bs_malloc(total_size);

	memset(data, 0, BFNT_HEADER_SIZE);

	bs_setLittleEndian32(BFNT_MAGIC, data + BFNT_MAGIC_OFFSET);
	bs_setLittleEndian32(1, data + BFNT_VERSION_OFFSET);
	bs_setLittleEndian16(blocks_count, data + BFNT_BLOCKS_COUNT_OFFSET);
	bs_setLittleEndian16(pt_sizes_count, data + BFNT_PT_SIZES_COUNT_OFFSET);
	//bs_setLittleEndian32(total_glyphs_count, data + BFNT_GLYPHS_COUNT_OFFSET);

	bs_List bitmap_data = bs_list(sizeof(unsigned char), 1024);

	unsigned char* offset = data + BFNT_POINTS_OFFSET;

   /**
    Point sizes
    */
	for (int i = 0; i < pt_sizes_count; i++) {
		bs_setLittleEndian32(pt_sizes[i], offset + BFNT_POINT_SIZE_OFFSET);
		offset += BFNT_POINT_SIZE;
	}

   /**
    Font specific codepoint ranges
	*/
	unsigned char* glyphs_offset = offset + blocks_count * BFNT_BLOCK_SIZE + pt_sizes_count * BFNT_POINT_SIZE;

	for (int i = 0, glyphs_block_offset = 0; i < blocks_count; i++) {
		//bs_setLittleEndian16(i, data + BFNT_BLOCK_LOOKUP_OFFSET + blocks[i].block * sizeof(bs_U16));

		bs_setLittleEndian32(blocks[i].offset, offset + BFNT_BLOCK_START_OFFSET);
		bs_setLittleEndian32(blocks[i].count, offset + BFNT_BLOCK_LENGTH_OFFSET);
		bs_setLittleEndian32(blocks[i].size, offset + BFNT_BLOCK_SIZE_OFFSET);

		if (blocks[i].rasterize) {
			bs_setLittleEndian32(glyphs_block_offset, offset + BFNT_BLOCK_GLYPHS_OFFSET);

			for (int j = 0; j < pt_sizes_count; j++) {
				int glyphs_pt_offset = glyphs_block_offset + blocks[i].count * j;

				const int dpi = 100;
				int pt_size = pt_sizes[j];

				error = FT_Set_Char_Size(face, pt_size * 64, 0, dpi, 0);
				if (error) {
					BSMOD_WARN_FREETYPE_ERROR("FT_Set_Char_Size", error, );
					continue;
				}

				for (int k = 0; k < blocks[i].count; k++) {
					int glyph_offset = glyphs_pt_offset + k * BFNT_GLYPH_SIZE;

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

					bs_setLittleEndian32(codepoint, glyphs_offset + glyph_offset + BFNT_GLYPH_CODEPOINT);
					bs_setLittleEndian32(glyph_id, glyphs_offset + glyph_offset + BFNT_GLYPH_GLYPH_INDEX);

					FT_Bitmap* bmp = &face->glyph->bitmap;
					bs_ensureSize(&bitmap_data, bmp->rows * bmp->width);

					unsigned char* dst = bitmap_data.data + bitmap_data.count;
					for (int y = 0; y < bmp->rows; ++y) {
						memcpy(dst + y * bmp->width,
							bmp->buffer + y * bmp->pitch,
							bmp->width);
					}

					bsmod_TextureInfo* texture = bsmod_packAtlasTextureF(
						&packer, 
						NULL, 
						_bsmod_getFontTextureData, 
						&bitmap_data,
						bmp->width, 
						bmp->rows, 
						0, 
						bitmap_data.count,
						glyph_offset,
						"%d", 
						glyph_id
					);

					bitmap_data.count += bmp->rows * bmp->width;
				}
			}

			glyphs_block_offset += blocks[i].count * pt_sizes_count;
		}

		offset += BFNT_BLOCK_SIZE;
	}

   /**
    Pack into atlas
    */
	result = _bsmod_packAtlas(&packer, 1024, 1024, 1, package_path, resource_name, true);
	if (result != BS_RESULT_OK)
		goto end;

	for (int i = 0; i < packer.rects.count; i++) {
		stbrp_rect* rect = bs_fetchUnit(&packer.rects, i);

		bsmod_TextureInfo* info = bs_fetchUnit(&packer.info, rect->id);

		int glyph_offset = info->id2;
		bs_setLittleEndian32(info->page, offset + glyph_offset + BFNT_GLYPH_PAGE_OFFSET);
		bs_setLittleEndian32(i, offset + glyph_offset + BFNT_GLYPH_ATLAS_INDEX);
		
		offset += BFNT_GLYPH_SIZE;
	}
	_bsmod_destroyAtlasPacker(&packer);

   /**
    Copy TTF data
    */
	memcpy(offset, ttf->value, ttf->len);

	result = _bsmod_packResource(BS_RESOURCE_FONT, data, total_size, package_path, resource_name);
	
end:
	bs_destroyList(&bitmap_data);
	FT_Done_Face(face);
	bs_free(ttf);
	bs_free(data);
	//	if (result != BS_RESULT_OK)
	//		return result;

	return result;
}