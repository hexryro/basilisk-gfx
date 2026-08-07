
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
#include <freetype/tttables.h>

FT_Library _freetype_library = NULL;

bs_Result _bsmod_convertFreetypeError(FT_Error error) {
	switch (error) {
	case 0: return BS_RESULT_OK;
	}

	return BS_RESULT_GENERAL_ERROR;
}



  /*==============================================================================
   * KERN table
   * https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6kern.html
   *============================================================================*/

 /**
  KERN header
  these are 4 bytes each on fonts targeted only for OS X, idk what to do about that
  */
#define KERN_VERSION                    0   // (bs_U16) - The version number of the kerning table (0x00010000 for the current version).
#define KERN_NUMBER_OF_TABLES           2   // (bs_U16) - The number of subtables included in the kerning table.

 /**
  KERN subtable
  */
#define KERN_LENGTH						4	// (bs_U32) - The length of this subtable in bytes, including this header.
#define KERN_COVERAGE					8	// (bs_U16) - Circumstances under which this table is used. See below for description.
#define KERN_TUPLE_INDEX				10	// (bs_U16) - The tuple index (used for variations fonts). This value specifies which tuple this subtable covers.

 // Coverage flags
#define KERN_COVERAGE_VERTICAL			0x8000 // Set if table has vertical kerning values.
#define KERN_COVERAGE_CROSS_STREAM		0x4000 // Set if table has cross-stream kerning values.
#define KERN_COVERAGE_VARIATION			0x2000 // Set if table has variation kerning values.
#define KERN_COVERAGE_UNUSED_BITS		0x1F00 // Set to 0.
#define KERN_COVERAGE_FORMAT_MASK		0x00FF // Set the format of this subtable (0-3 currently defined).

 /**
  Format 0
  */
#define KERN_FORMAT0_PAIRS_COUNT		0 // (bs_U16) - The number of kerning pairs in this subtable.
#define KERN_FORMAT0_SEARCH_RANGE		2 // (bs_U16) - The largest power of two less than or equal to the value of nPairs, multiplied by the size in bytes of an entry in the subtable.
#define KERN_FORMAT0_ENTRY_SELECTOR		4 // (bs_U16) - This is calculated as log2 of the largest power of two less than or equal to the value of nPairs. This value indicates how many iterations of the search loop have to be made. For example, in a list of eight items, there would be three iterations of the loop.
#define KERN_FORMAT0_RANGE_SHIFT		6 // (bs_U16) - The value of nPairs minus the largest power of two less than or equal to nPairs. This is multiplied by the size in bytes of an entry in the table.

#define KERN_FORMAT0_PAIR_START			8
#define KERN_FORMAT0_PAIR_LEFT			0 // (bs_U16) - The glyph index for the lefthand glyph in the kerning pair.
#define KERN_FORMAT0_PAIR_RIGHT			2 // (bs_U16) - The glyph index for the righthand glyph in the kerning pair.
#define KERN_FORMAT0_PAIR_VALUE			4 // (bs_I16) - The kerning value in FUnits for the left and right pair in FUnits. If this value is greater than zero, the glyphs are moved apart. If this value is less than zero, the glyphs are moved together.

static void _bsmod_findKerningPairs(FT_Face face, FT_UInt left, bsmod_UnicodeBlockRange blocks[], int blocks_count) {
	for (int i = 0; i < blocks_count; i++) {
		bsmod_UnicodeBlockRange* block = blocks + i;

		for (int j = 0; j < block->count; j++) {
			FT_UInt right = FT_Get_Char_Index(face, block->offset + j);
			if (right == 0)
				continue;

			FT_Vector kerning;

			FT_Get_Kerning(
				face,
				left,
				right,
				FT_KERNING_DEFAULT,
				&kerning
			);
		}
	}
}

/*
static int _bsmod_parseKernFormat0(bs_U8* data, int offset) {
	bs_U16 pairs_count = bs_getBigEndian16(data, KERN_FORMAT0_PAIRS_COUNT + offset);

	bs_U8* base = kern + KERN_FORMAT0_PAIR_START + offset;

	for (int i = 0; i < pairs_count; i++) {
		bs_U8* p = base + i * sizeof(bs_U16) * 3;

		bs_U16 left = bs_getBigEndian16(p, KERN_FORMAT0_PAIR_LEFT);
		bs_U16 right = bs_getBigEndian16(p, KERN_FORMAT0_PAIR_RIGHT);
		bs_U16 value = bs_getBigEndian16(p, KERN_FORMAT0_PAIR_VALUE);

		bs_Glyph* left_glyph = NULL;
		int right_glyph_index = -1;

		for (int j = 0; j < ttf->glyphs.count; j++) {
			bs_Glyph* glyph = bs_fetchUnit(&ttf->glyphs, j);

			if (glyph->index == left)
				left_glyph = glyph;

			if (glyph->index == right)
				right_glyph_index = j;

			if (left_glyph && right_glyph_index > 0)
				break;
		}

		if (!left_glyph || right_glyph_index == -1)
			continue;

		bs_pushBack(&ttf->kerning_pairs, &(bs_KerningPair){
			.right_index = right_glyph_index,
			.right = right,
			.value = value,
		});

		left_glyph->pairs_count++;
	}

	return sizeof(bs_U16) * 4 + sizeof(bs_U16) * 3 * pairs_count;
}

static void _bsmod_parseKernFormat(bs_U8* data) {
	bs_U16 version = bs_getBigEndian16(data + KERN_VERSION);
	bs_U16 subtables_count = bs_getBigEndian16(data + KERN_NUMBER_OF_TABLES);

	int header_size =
		sizeof(bs_U32) +
		sizeof(bs_U16) * 3;
	if (version == 1) // AAT - Apple Advanced Typography
		header_size += sizeof(bs_U16);

	for (int i = 0, offset = 0; i < subtables_count; i++) {
		bs_U32 length = bs_getBigEndian32(data + KERN_LENGTH + offset);
		bs_U16 coverage = bs_getBigEndian16(data + KERN_COVERAGE + offset);
		// bs_U16 tuple_index = bs_memU16(buf, KERN_TUPLE_INDEX + offset); // AAT

		int vertical = (coverage & KERN_COVERAGE_VERTICAL) != 0;
		int cross_stream = (coverage & KERN_COVERAGE_CROSS_STREAM) != 0;
		int variation = (coverage & KERN_COVERAGE_VARIATION) != 0;

		bs_U16 format = (coverage & 0xFF00) >> 8;

		switch (format) {
		case 0: offset += _bsmod_parseKernFormat0(data, offset + header_size); break;
		case 1:
		case 2:
		case 3:
			bs_throwBasiliskF(BSX_NOT_IMPLEMENTED, "KERN format %d", format);
		default:
			bs_throwBasiliskF(BSX_CORRUPTED, "KERN format %d is not between 0..4", format);
		}
	}
}
*/



  /*==============================================================================
   * GPOS Parsing
   *============================================================================*/

static void _bsmod_parseGPOS(bs_U8* data) {
	bs_U16 major_version = bs_getBigEndian16(data + 0);
	bs_U16 minor_version = bs_getBigEndian16(data + 2);

	bs_U16 script_list_offset = bs_getBigEndian16(data + 4);
	bs_U16 feature_list_offset = bs_getBigEndian16(data + 6);
	bs_U16 lookup_list_offset = bs_getBigEndian16(data + 8);
}



  /*==============================================================================
   * Font Packing
   *============================================================================*/

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

	FT_ULong length = 0;

	error = FT_Load_Sfnt_Table(face, FT_MAKE_TAG('G', 'P', 'O', 'S'), 0, NULL, &length);

	if (!error) {
		bs_U8* gpos = malloc(length);

		error = FT_Load_Sfnt_Table(face, FT_MAKE_TAG('G', 'P', 'O', 'S'), 0, gpos, &length);

		_bsmod_parseGPOS(gpos);

		bs_free(gpos);
	}

	/*
	FT_ULong length = 0;

	error = FT_Load_Sfnt_Table(face, FT_MAKE_TAG('k', 'e', 'r', 'n'), 0, NULL, &length);

	if (!error) {
		bs_U8* kern = malloc(length);

		error = FT_Load_Sfnt_Table(face, FT_MAKE_TAG('k', 'e', 'r', 'n'), 0, kern, &length);

		bs_U16 version = bs_getBigEndian16(kern + KERN_VERSION);
		bs_U16 subtables_count = bs_getBigEndian16(kern + KERN_NUMBER_OF_TABLES);

		int header_size =
			sizeof(bs_U32) +
			sizeof(bs_U16) * 3;

		if (version == 1) // AAT
			header_size += sizeof(bs_U16);

	}
	*/

	/*
	for (int i = 0; i < blocks_count; i++) {
		bsmod_UnicodeBlockRange* block = blocks + i;

		for (int j = 0; j < block->count; j++) {
			FT_UInt left = FT_Get_Char_Index(face, block->offset + j);
			if (left == 0)
				continue;
			_bsmod_findKerningPairs(face, left, blocks, blocks_count);
		}
	}
	*/

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

	unsigned char* data = bs_calloc(1, total_size);

//memset(data, 0, BFNT_HEADER_SIZE);

	bs_setLittleEndian32(BFNT_MAGIC, data + BFNT_MAGIC_OFFSET);
	bs_setLittleEndian32(1, data + BFNT_VERSION_OFFSET);
	bs_setLittleEndian16(blocks_count, data + BFNT_BLOCKS_COUNT_OFFSET);
	bs_setLittleEndian16(pt_sizes_count, data + BFNT_PT_SIZES_COUNT_OFFSET);
	bs_setLittleEndian32(total_glyphs_count, data + BFNT_GLYPHS_COUNT_OFFSET);

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
	unsigned char* glyphs_offset = data + BFNT_POINTS_OFFSET + blocks_count * BFNT_BLOCK_SIZE + pt_sizes_count * BFNT_POINT_SIZE;

	for (int i = 0, glyphs_block_offset = 0; i < blocks_count; i++) {
		//bs_setLittleEndian16(i, data + BFNT_BLOCK_LOOKUP_OFFSET + blocks[i].block * sizeof(bs_U16));

		bs_setLittleEndian32(blocks[i].offset, offset + BFNT_BLOCK_START_OFFSET);
		bs_setLittleEndian32(blocks[i].count, offset + BFNT_BLOCK_LENGTH_OFFSET);
		bs_setLittleEndian32(blocks[i].size, offset + BFNT_BLOCK_SIZE_OFFSET);

		if (blocks[i].rasterize) {
			bs_setLittleEndian32(glyphs_block_offset, offset + BFNT_BLOCK_GLYPHS_OFFSET);

			for (int j = 0; j < pt_sizes_count; j++) {
				int glyphs_pt_offset = glyphs_block_offset * BFNT_GLYPH_SIZE + blocks[i].count * j;

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
		assert(info->reserved == rect->id);

		int glyph_offset = info->id2;
		bs_setLittleEndian16(info->page, offset + glyph_offset + BFNT_GLYPH_PAGE_OFFSET);
		bs_setLittleEndian32(i, offset + glyph_offset + BFNT_GLYPH_ATLAS_INDEX);
	}

	offset += total_glyphs_count * BFNT_GLYPH_SIZE;
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