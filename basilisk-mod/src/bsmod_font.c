
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

#include <stb_rect_pack/stb_rect_pack.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/tttables.h>
#include <freetype/ftoutln.h>
#include <freetype/ftmodapi.h>
#include <freetype/ftdriver.h>

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

typedef struct {
	bs_U32 flags;
	bs_U32 bitmap_offset;
	bs_U32 glyph_offset;
	bs_U32 codepoint;
	bs_U16 glyph_id;
	bs_U16 reserved;
	bs_U16 kern_pair_start;
	bs_U16 kern_pair_count;
	bs_U16 kern_pair_extended_start;
	bs_U16 kern_pair_extended_count;
	bs_I32 x_advance;
	bs_I32 y_advance;
	bs_I32 x_bearing;
	bs_I32 y_bearing;
	bs_I32 x_offset;
	bs_I32 y_offset;
	int info_id;
} bsmod_RasterizedGlyph;



  /*==============================================================================
   * GPOS Parsing
   *============================================================================*/

typedef struct {
	bs_I16 left_x_placement;
	bs_I16 left_y_placement;
	bs_I16 left_x_advance;
	bs_I16 left_y_advance;

	bs_I16 right_x_placement;
	bs_I16 right_y_placement;
	bs_I16 right_x_advance;
	bs_I16 right_y_advance;

	bs_U32 right;
} bsmod_KerningPair;

typedef struct {
	int x_placement_offset;
	int y_placement_offset;
	int x_advance_offset;
	int y_advance_offset;
	int size;
} bsmod_ValueRecordLayout;

static void _bsmod_parseSingleAdjustment(unsigned char* data) {
}

static bsmod_ValueRecordLayout _bsmod_valueRecordLayout(bs_U16 format) {
	int offset = 0;

	bsmod_ValueRecordLayout layout = { 0 };
	if (format & 1) {
		layout.x_placement_offset = offset;
		offset += 2;
	}

	if (format & 2) {
		layout.y_placement_offset = offset;
		offset += 2;
	}

	if (format & 4) {
		layout.x_advance_offset = offset;
		offset += 2;
	}

	if (format & 8) {
		layout.y_advance_offset = offset;
		offset += 2;
	}

	if (format & 16) offset += 2;
	if (format & 32) offset += 2;
	if (format & 64) offset += 2;
	if (format & 128) offset += 2;

	layout.size = offset;
	return layout;
}

static bsmod_RasterizedGlyph* _bsmod_queryPackerGlyphId(bsmod_AtlasPacker* packer, bs_List* glyphs, bs_U16 glyph_id) {
	for (int i = 0; i < packer->info.count; i++) {
		//stbrp_rect* rect = bs_fetchUnit(&packer->rects, i);
		bsmod_TextureInfo* texture_info = bs_fetchUnit(&packer->info, i);
		bsmod_RasterizedGlyph* glyph = bs_fetchUnit(glyphs, texture_info->id);

		if (glyph->glyph_id == glyph_id)
			return glyph;
	}

	return NULL;
}

static void _bsmod_parsePairAdjustment(bs_List* kerning_pairs, bsmod_AtlasPacker* packer, bs_List* glyphs, size_t offsetof_kern, unsigned char* data) {
	bs_U16 format = bs_getBigEndian16(data + 0);

	if (format == 1) {
		bs_U16 coverage_offset = bs_getBigEndian16(data + 2);
		bs_U16 value_format_1 = bs_getBigEndian16(data + 4);
		bs_U16 value_format_2 = bs_getBigEndian16(data + 6);
		bs_U16 pair_set_count = bs_getBigEndian16(data + 8);
		unsigned char* pair_set_offsets = data + 10;

		if (value_format_1 == 0 && value_format_2 == 0)
			return;

		unsigned char* coverage = data + coverage_offset;
		bs_U16 coverage_format = bs_getBigEndian16(coverage + 0);

		bsmod_ValueRecordLayout value_record_1_layout = _bsmod_valueRecordLayout(value_format_1);
		bsmod_ValueRecordLayout value_record_2_layout = _bsmod_valueRecordLayout(value_format_2);

		if (coverage_format == 1) {

			bs_U16 coverage_glyph_count = bs_getBigEndian16(coverage + 2);

			if (coverage_glyph_count != pair_set_count) {
				bs_warnF("Coverage format 1 glyph count is not equal to the pair adjustment pair count (%d != %d)", coverage_glyph_count, pair_set_count);
				return;
			}

			unsigned char* coverage_glyphs = coverage + 4;
			for (int i = 0; i < coverage_glyph_count; i++) {
				bs_U16 left_glyph_id = bs_getBigEndian16(coverage_glyphs + i * sizeof(bs_U16));

				bsmod_RasterizedGlyph* glyph = _bsmod_queryPackerGlyphId(packer, glyphs, left_glyph_id);
				if (!glyph)
					continue;

				unsigned char* glyph_u8 = (unsigned char*)glyph;
				bs_U16* start_dst = (bs_U16*)(glyph_u8 + offsetof_kern);
				bs_U16* count_dst = (bs_U16*)(start_dst + 1);

				*start_dst = kerning_pairs->count;

				bs_U16 pair_set_offset = bs_getBigEndian16(pair_set_offsets + i * 2);
				unsigned char* pair_set = data + pair_set_offset;

				bs_U16 pair_value_count = bs_getBigEndian16(pair_set + 0);
				unsigned char* pair_values = pair_set + 2;

				unsigned char* pair_value = pair_values;

				for (int j = 0; j < pair_value_count; j++) {
					bs_U16 right_glyph_id = bs_getBigEndian16(pair_value);
					glyph = _bsmod_queryPackerGlyphId(packer, glyphs, right_glyph_id);
					if (!glyph) {
						pair_value += 2 + value_record_1_layout.size + value_record_2_layout.size;
						continue;
					}

					pair_value += 2;

					bsmod_KerningPair* pair = bs_pushBack(kerning_pairs, NULL);
					pair->right = glyph->codepoint;

					if (value_format_1 & 1) pair->left_x_placement = bs_getBigEndian16(pair_value + value_record_1_layout.x_advance_offset);
					if (value_format_1 & 2) pair->left_y_placement = bs_getBigEndian16(pair_value + value_record_1_layout.y_advance_offset);
					if (value_format_1 & 4) pair->left_x_advance = bs_getBigEndian16(pair_value + value_record_1_layout.x_placement_offset);
					if (value_format_1 & 8) pair->left_y_advance = bs_getBigEndian16(pair_value + value_record_1_layout.y_placement_offset);

					pair_value += value_record_1_layout.size;

					if (value_format_2 & 1) pair->right_x_placement = bs_getBigEndian16(pair_value + value_record_2_layout.x_advance_offset);
					if (value_format_2 & 2) pair->right_y_placement = bs_getBigEndian16(pair_value + value_record_2_layout.y_advance_offset);
					if (value_format_2 & 4) pair->right_x_advance = bs_getBigEndian16(pair_value + value_record_2_layout.x_placement_offset);
					if (value_format_2 & 8) pair->right_y_advance = bs_getBigEndian16(pair_value + value_record_2_layout.y_placement_offset);

					pair_value += value_record_2_layout.size;
				}

				*count_dst = kerning_pairs->count - *start_dst;
				assert(kerning_pairs->count <= BS_U16_MAX);
			}
		}
		else if (coverage_format == 2) {

			bs_U16 coverage_range_count = bs_getBigEndian16(coverage + 2);
			unsigned char* coverage_ranges = coverage + 4;

			for (int i = 0; i < coverage_range_count; i++) {

				unsigned char* range = coverage_ranges + i * 6;

				bs_U16 start_glyph_id = bs_getBigEndian16(range + 0);
				bs_U16 end_glyph_id = bs_getBigEndian16(range + 2);
				bs_U16 start_coverage_index = bs_getBigEndian16(range + 4);

				for (int j = start_glyph_id; j <= end_glyph_id; j++) {

					bs_U16 coverage_index = start_coverage_index + (j - start_glyph_id);

					bsmod_RasterizedGlyph* glyph = _bsmod_queryPackerGlyphId(packer, glyphs, j);
					if (!glyph)
						continue;

					unsigned char* glyph_u8 = (unsigned char*)glyph;
					bs_U16* start_dst = (bs_U16*)(glyph_u8 + offsetof_kern);
					bs_U16* count_dst = (bs_U16*)(start_dst + 1);

					*start_dst = kerning_pairs->count;

					bs_U16 pair_set_offset = bs_getBigEndian16(pair_set_offsets + coverage_index * 2);
					unsigned char* pair_set = data + pair_set_offset;

					bs_U16 pair_value_count = bs_getBigEndian16(pair_set + 0);
					unsigned char* pair_value = pair_set + 2;

					for (int j = 0; j < pair_value_count; j++) {
						bs_U16 right_glyph_id = bs_getBigEndian16(pair_value + 0);

						glyph = _bsmod_queryPackerGlyphId(packer, glyphs, right_glyph_id);

						if (!glyph) {
							pair_value += 2 + value_record_1_layout.size + value_record_2_layout.size;
							continue;
						}

						pair_value  += 2;

						bsmod_KerningPair pair = { 0 };

						pair.right = glyph->codepoint;

						if (value_format_1 & 1) pair.left_x_placement = bs_getBigEndian16(pair_value + value_record_1_layout.x_advance_offset);
						if (value_format_1 & 2) pair.left_y_placement = bs_getBigEndian16(pair_value + value_record_1_layout.y_advance_offset);
						if (value_format_1 & 4) pair.left_x_advance = bs_getBigEndian16(pair_value + value_record_1_layout.x_placement_offset);
						if (value_format_1 & 8) pair.left_y_advance = bs_getBigEndian16(pair_value + value_record_1_layout.y_placement_offset);

						pair_value += value_record_1_layout.size;

						if (value_format_2 & 1) pair.right_x_placement = bs_getBigEndian16(pair_value + value_record_2_layout.x_advance_offset);
						if (value_format_2 & 2) pair.right_y_placement = bs_getBigEndian16(pair_value + value_record_2_layout.y_advance_offset);
						if (value_format_2 & 4) pair.right_x_advance = bs_getBigEndian16(pair_value + value_record_2_layout.x_placement_offset);
						if (value_format_2 & 8) pair.right_y_advance = bs_getBigEndian16(pair_value + value_record_2_layout.y_placement_offset);

						pair_value += value_record_2_layout.size;

						bs_pushBack(kerning_pairs, &pair);
					}

					*count_dst = kerning_pairs->count - *start_dst;
					assert(kerning_pairs->count <= BS_U16_MAX);
				}
			}
		}
		else {
			bs_warnF("GPOS coverage format %d is not supported", coverage_format);
		}
	}
}

static void _bsmod_parseGPOS(bsmod_AtlasPacker* packer, bs_List* glyphs, unsigned char* data, bs_List* kerning_pairs, bs_List* kerning_pairs_extended) {
	*kerning_pairs = bs_list(sizeof(bsmod_KerningPair), 64);
	*kerning_pairs_extended = bs_list(sizeof(bsmod_KerningPair), 64);

	bs_U16 major_version = bs_getBigEndian16(data + 0);
	bs_U16 minor_version = bs_getBigEndian16(data + 2);

	bs_U16 script_list_offset = bs_getBigEndian16(data + 4);
	bs_U16 feature_list_offset = bs_getBigEndian16(data + 6);
	bs_U16 lookup_list_offset = bs_getBigEndian16(data + 8);

	unsigned char* lookup_list = data + lookup_list_offset;

	bs_U16 lookup_count = bs_getBigEndian16(lookup_list);

	for (bs_U16 i = 0; i < lookup_count; i++) {
		bs_U16 lookup_offset = bs_getBigEndian16(lookup_list + 2 + i * 2);

		unsigned char* lookup = lookup_list + lookup_offset;

		bs_U16 lookup_type = bs_getBigEndian16(lookup + 0);
		bs_U16 lookup_flags = bs_getBigEndian16(lookup + 2);
		bs_U16 subtable_count = bs_getBigEndian16(lookup + 4);
		unsigned char* subtable_offsets = lookup + 6;

		for (bs_U16 j = 0; j < subtable_count; j++) {
			bs_U16 subtable_offset = bs_getBigEndian16(subtable_offsets + j * sizeof(bs_U16));

			unsigned char* subtable = lookup + subtable_offset;

			switch (lookup_type) {
			case 1: _bsmod_parseSingleAdjustment(subtable); break;
			case 2: _bsmod_parsePairAdjustment(kerning_pairs, packer, glyphs, offsetof(bsmod_RasterizedGlyph, kern_pair_start), subtable); break;

				/**
				 Extension positioning
				 */
			case 9:
				bs_U16 extension_lookup_type = bs_getBigEndian16(subtable + 2);
				bs_U32 extension_offset = bs_getBigEndian32(subtable + 4);

				unsigned char* extension = subtable + extension_offset;

				switch (extension_lookup_type) {
				case 1: _bsmod_parseSingleAdjustment(extension); break;
				case 2: _bsmod_parsePairAdjustment(kerning_pairs_extended, packer, glyphs, offsetof(bsmod_RasterizedGlyph, kern_pair_extended_start), extension); break;
				}

				break;

			default:
				break;
			}
		}
	}
}



  /*==============================================================================
   * Font Packing
   *============================================================================*/

typedef struct {
	bs_List* bitmap;
	bs_List* rasterized_glyphs;
} bsmod_FontTextureDataParam;

static unsigned char* _bsmod_getFontTextureData(bsmod_AtlasPacker* packer, int index) {
	bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, index);
	bsmod_FontTextureDataParam* param = info->param;
	bsmod_RasterizedGlyph* glyph = bs_fetchUnit(param->rasterized_glyphs, info->id);

	return param->bitmap->data + glyph->bitmap_offset;
}

static inline void _bsmod_setKerningPairs(unsigned char* kerning_pairs_offset, int* kern_id, bs_List* list, int start, int count) {
	kerning_pairs_offset += *kern_id * BFNT_KERNING_PAIR_SIZE;

	int end = start + count;
	for (int i = start; i < end; i++) {
		bsmod_KerningPair* pair = bs_fetchUnit(list, i);
		bs_setLittleEndian32(pair->right, kerning_pairs_offset + BFNT_OFFSET_KERNING_PAIR_RIGHT);

		bs_setLittleEndian16(pair->left_x_placement, kerning_pairs_offset + BFNT_OFFSET_KERN_LEFT_X_PLACEMENT);
		bs_setLittleEndian16(pair->left_y_placement, kerning_pairs_offset + BFNT_OFFSET_KERN_LEFT_Y_PLACEMENT);
		bs_setLittleEndian16(pair->left_x_advance, kerning_pairs_offset + BFNT_OFFSET_KERN_LEFT_X_ADVANCE);
		bs_setLittleEndian16(pair->left_y_advance, kerning_pairs_offset + BFNT_OFFSET_KERN_LEFT_Y_ADVANCE);

		bs_setLittleEndian16(pair->right_x_placement, kerning_pairs_offset + BFNT_OFFSET_KERN_RIGHT_X_PLACEMENT);
		bs_setLittleEndian16(pair->right_y_placement, kerning_pairs_offset + BFNT_OFFSET_KERN_RIGHT_Y_PLACEMENT);
		bs_setLittleEndian16(pair->right_x_advance, kerning_pairs_offset + BFNT_OFFSET_KERN_RIGHT_X_ADVANCE);
		bs_setLittleEndian16(pair->right_y_advance, kerning_pairs_offset + BFNT_OFFSET_KERN_RIGHT_Y_ADVANCE);

		kerning_pairs_offset += BFNT_KERNING_PAIR_SIZE;
	}

	*kern_id += count;
}

static void _bsmod_renderGlyphsFreeType(
	bsmod_FontTextureDataParam* get_data_param,
	FT_Face face,
	FT_Render_Mode render_mode,
	bsmod_UnicodeBlockRange blocks[],
	int blocks_count,
	int pt_sizes[],
	int pt_sizes_count,
	bsmod_AtlasPacker* packer,
	int channels_count)
{

	//bs_logF("Rasterizing %d blocks of %d sizes (%d potential glyphs)", blocks_count, pt_sizes_count, total_glyphs_count);
	for (int i = 0, glyphs_block_offset = 0; i < blocks_count; i++) {
		if (!blocks[i].rasterize)
			continue;

		for (int j = 0; j < pt_sizes_count; j++) {
			int glyphs_pt_offset = glyphs_block_offset * BFNT_GLYPH_SIZE + blocks[i].count * j * BFNT_GLYPH_SIZE;

			const int dpi = 100;
			int pt_size = pt_sizes[j];
			FT_Set_Pixel_Sizes(face, 0, pt_size);

			for (int k = 0; k < blocks[i].count; k++) {
				int glyph_offset = glyphs_pt_offset + k * BFNT_GLYPH_SIZE;

				FT_ULong codepoint = (FT_ULong)(blocks[i].offset + k);
				FT_UInt glyph_id = FT_Get_Char_Index(face, codepoint);

				if (glyph_id == 0)
					continue;

				if (FT_Load_Glyph(face, glyph_id, FT_LOAD_PEDANTIC | FT_LOAD_NO_AUTOHINT))
					continue;

				if (FT_Render_Glyph(face->glyph, render_mode))
					continue;

				int rasterized_glyph_id = get_data_param->rasterized_glyphs->count;

				bsmod_RasterizedGlyph* rasterized_glyph = bs_pushBack(get_data_param->rasterized_glyphs, &(bsmod_RasterizedGlyph) {
					.glyph_offset = glyph_offset,
					.glyph_id = glyph_id,
					.codepoint = codepoint,
					.x_advance = face->glyph->advance.x,
					.y_advance = face->glyph->advance.y,
					.x_offset = face->glyph->bitmap_left,
				});

				if (face->glyph->bitmap.width == 0 || face->glyph->bitmap.rows == 0) {
					rasterized_glyph->flags |= BFNT_GLYPH_FLAG_SKIP_RENDER;
					continue;
				}

				FT_Bitmap* bmp = &face->glyph->bitmap;
				bs_ensureSize(get_data_param->bitmap, bmp->rows * bmp->width * channels_count);

				unsigned char* dst = get_data_param->bitmap->data + get_data_param->bitmap->count;
				for (int y = 0; y < bmp->rows; y++) {
					memcpy(dst + y * bmp->width * channels_count,
						bmp->buffer + y * bmp->pitch * channels_count,
						bmp->width * channels_count);
				}

				rasterized_glyph->bitmap_offset = get_data_param->bitmap->count,
				rasterized_glyph->y_offset = face->glyph->bitmap_top - bmp->rows;
				rasterized_glyph->info_id = packer->info.count;

				//FT_BBox box;
				//FT_Outline_Get_CBox(&face->glyph->outline, &box);

				bsmod_TextureInfo* texture = bsmod_packAtlasTextureF(
					packer,
					NULL,
					_bsmod_getFontTextureData,
					get_data_param,
					bmp->width,
					bmp->rows,
					0,
					rasterized_glyph_id,
					"%d",
					glyph_id
				);

			//	bs_savePng(dst, BS_IV2(bmp->width, bmp->rows), BS_PNG_GREY, "test.png");

				get_data_param->bitmap->count += bmp->rows * bmp->width * channels_count;
			}
		}

		glyphs_block_offset += blocks[i].count * pt_sizes_count;
		bs_logF("%d/%d: Rasterized glyph block %d-%d", i + 1, blocks_count, blocks[i].offset, blocks[i].offset + blocks[i].count);
	}
}
#define SERIALIZER_SCALE 64.0f

static bs_Result _bsmod_renderGlyphsMSDF(const char* package_path, const char* resource_name, FT_Face face, int32_t start, int32_t end) {
    int nrender = end - start;
    if (nrender <= 0)
        return -1;

    const float font_scale = 4;
    const float font_range = 2;

    size_t* meta_sizes = NULL, * point_sizes = NULL;
   //msdfgl_index_entry* atlas_index = NULL;

    meta_sizes = bs_alloca(nrender * sizeof(size_t));
    point_sizes = bs_alloca(nrender * sizeof(size_t));

    //atlas_index = bs_alloca(nrender * sizeof(msdfgl_index_entry));

    size_t meta_size_sum = 0, point_size_sum = 0;
    for (size_t i = 0; (int)i < (int)nrender; i++) {
        int index = start + (int)i;
       // msdfgl_glyph_buffer_size(face, index, &meta_sizes[i], &point_sizes[i]);

        meta_size_sum += meta_sizes[i];
        point_size_sum += point_sizes[i];
    }

    bs_Object* point_data_object = BS_BUFFER(-1, -1, 0);
    bs_Object* metadata_object = BS_BUFFER(-1, -1, 0);

    bs_buffer(
        point_data_object,
        point_size_sum,
        BS_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    bs_buffer(
        metadata_object,
        meta_size_sum,
        BS_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    bs_bufferView(point_data_object->buffer, BS_FORMAT_R32_SFLOAT, 0, BS_U64_MAX);
    bs_bufferView(metadata_object->buffer, BS_FORMAT_R8_UINT, 0, BS_U64_MAX);

    bs_mapBuffer(point_data_object->buffer, BS_U32_MAX);
    bs_mapBuffer(metadata_object->buffer, BS_U32_MAX);

    bs_bindBuffer(BSMOD_SET_MSDF_BITMAP, BSMOD_BINDING_MSDF_BITMAP, metadata_object->buffer);
    bs_bindBuffer(BSMOD_SET_MSDF_INDEX, BSMOD_BINDING_MSDF_INDEX, point_data_object->buffer);

    bs_pushBindings();
    bs_pushDescriptors();

    void* point_data = point_data_object->buffer->_->data;
    void* metadata = metadata_object->buffer->_->data;

    /* Serialize the glyphs into RAM. */
    char* meta_ptr = metadata;
    char* point_ptr = point_data;

    bsmod_AtlasPacker packer = bsmod_createAtlasPacker();

    for (size_t i = 0; (int)i < (int)nrender; i++) {
        float buffer_width, buffer_height;

        int index = start + (int)i;
        //_bsmod_serializeGlyphMSDF(face, index, meta_ptr, (float*)point_ptr);

        buffer_width = face->glyph->metrics.width / SERIALIZER_SCALE + font_range;
        buffer_height = face->glyph->metrics.height / SERIALIZER_SCALE + font_range;
        buffer_width *= font_scale;
        buffer_height *= font_scale;

       // atlas_index[i].offset_x = 0;
       // atlas_index[i].offset_y = 0;
       // atlas_index[i].size_x = buffer_width;
       // atlas_index[i].size_y = buffer_height;
       // atlas_index[i].bearing_x = (float)face->glyph->metrics.horiBearingX;
       // atlas_index[i].bearing_y = (float)face->glyph->metrics.horiBearingY;
       // atlas_index[i].glyph_width = (float)face->glyph->metrics.width;
       // atlas_index[i].glyph_height = (float)face->glyph->metrics.height;

		/*
		bs_pushBack(&rasterized_glyphs, &(bsmod_RasterizedGlyph) {
			.bitmap_offset = bitmap_data->count,
			.glyph_offset = glyph_offset,
			.glyph_id = glyph_id,
			.codepoint = codepoint,
			.x_advance = face->glyph->advance.x,
			.y_advance = face->glyph->advance.y,
			.x_bearing = (float)face->glyph->metrics.horiBearingX,
			.y_bearing = (float)face->glyph->metrics.horiBearingY,
			.y_offset = face->glyph->bitmap_top - bmp->rows,
		});
		*/

        bsmod_packAtlasTexture(&packer, NULL, NULL, NULL, face->glyph->metrics.width, face->glyph->metrics.height, 0, 0, "tmp");

        meta_ptr += meta_sizes[i];
        point_ptr += point_sizes[i];
    }

    const int atlas_width = 1024, atlas_height = 1024;
    bsmod_packAtlas(&packer, atlas_width, atlas_height, 4, package_path, resource_name, true); // TODO: do 3 channels

    //bs_mat4 framebuffer_projection;
    //bs_mat4 atlas_projection;
    //
    //bs_orthographic(0, atlas_width, 0, atlas_height, -1.0, 1.0, &framebuffer_projection);
    //bs_orthographic(-atlas_width, atlas_width, -atlas_height, atlas_height, -1.0, 1.0, &atlas_projection);

	/*
    bsmod_MSDFPushConstant push_const = {
        .scale = { font_scale, font_scale},
        .range = font_range,
        .meta_offset = 0,
        .point_offset = 0,
    };

    int meta_offset = 0;
    int point_offset = 0;
    for (int i = 0; i < nrender; ++i) {
        if (end && start == 0 && i != 0 && _msdfgl_is_control(i))
            continue;

       // msdfgl_index_entry g = atlas_index[i];

        push_const.translate = BS_V2(
            -g.bearing_x / SERIALIZER_SCALE + font_range / 2.0f,
            (g.glyph_height - g.bearing_y) / SERIALIZER_SCALE + font_range / 2.0f
        );
        push_const.glyph_height = g.size_y;
        push_const.size = BS_V2(g.size_x, g.size_y);

        push_const.meta_offset = meta_offset;
        push_const.point_offset = point_offset / (2 * sizeof(float));

        if (((unsigned char*)metadata)[meta_offset])
            _bsmod_renderGlyphAtlas(push_const);

        meta_offset += meta_sizes[i];
        point_offset += point_sizes[i];
    }
	*/

    return BS_RESULT_OK;
}

BSMODAPI bs_Result _bsmod_packFont(
	bsmod_RenderMode render_mode,
	char* package_path,
	char* ttf_path,
	bsmod_UnicodeBlockRange blocks[],
	int blocks_count,
	int pt_sizes[],
	int pt_sizes_count,
	char* resource_name,
	int resource_name_length)
{

	if (!bs_exists(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION))
		return BS_RESULT_OK;

	const int channels_count = 1;
	const int padding = 0;


   /**
    Load FreeType library
    */
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
    Rasterize glyphs
    */
	bs_List bitmap_data = bs_list(sizeof(unsigned char), 1024 * 1024 * channels_count);
	bs_List rasterized_glyphs = bs_list(sizeof(bsmod_RasterizedGlyph), 1024);

	int total_glyphs_count = 0;
	for (int i = 0; i < blocks_count; i++) {
		assert(blocks[i].block >= 0);
		//assert(blocks[i].block < BFNT_BLOCK_LOOKUP_LENGTH);

		if (blocks[i].rasterize)
			total_glyphs_count += blocks[i].count * pt_sizes_count;
	}

	bsmod_AtlasPacker packer = bsmod_createAtlasPacker();

	bsmod_FontTextureDataParam get_data_param = {
		.bitmap = &bitmap_data,
		.rasterized_glyphs = &rasterized_glyphs,
	};

	if (render_mode == BSMOD_RENDER_MODE_MSDF) {
#ifdef RENDERDOC_PATH
		if (_bsmod_.renderdoc_device) {
			bs_logF("Starting frame capture");
			_bsmod_.renderdoc_api->StartFrameCapture(_bsmod_.renderdoc_device, NULL);
		}
#endif

		bs_Object* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION);
		bs_Object* renderer = bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER_MSDF);
		bs_Object* msdf_glyphs = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_MSDF_GLYPHS);

		if (bs_resetQueue(queue->queue) == BS_RESULT_OK) {
			_bsmod_renderGlyphsMSDF(package_path, resource_name, face, 65, 66);
			bs_pushQueue(queue->queue, 0, NULL);

			bs_stallQueue(queue->queue);
			_bsmod_pollRasterizer();
		}

#ifdef RENDERDOC_PATH
		if (_bsmod_.renderdoc_device) {
			bs_logF("Ending frame capture");

			bs_U32 result = _bsmod_.renderdoc_api->EndFrameCapture(_bsmod_.renderdoc_api, NULL);

			if (result != 1)
				BS_WARN("EndFrameCapture returned %d", result);
		}
#endif
	}
	else {
		FT_Render_Mode ft_render_mode = FT_RENDER_MODE_NORMAL;
		switch (render_mode) {
			case BSMOD_RENDER_MODE_NORMAL: ft_render_mode = FT_RENDER_MODE_NORMAL; break;
			case BSMOD_RENDER_MODE_LIGHT: ft_render_mode = FT_RENDER_MODE_LIGHT; break;
			case BSMOD_RENDER_MODE_MONO: ft_render_mode = FT_RENDER_MODE_MONO; break;
			case BSMOD_RENDER_MODE_LCD: ft_render_mode = FT_RENDER_MODE_LCD; break;
			case BSMOD_RENDER_MODE_LCD_V: ft_render_mode = FT_RENDER_MODE_LCD_V; break;
			case BSMOD_RENDER_MODE_SDF: ft_render_mode = FT_RENDER_MODE_SDF; break;
		}

		_bsmod_renderGlyphsFreeType(
			&get_data_param,
			face,
			render_mode,
			blocks,
			blocks_count,
			pt_sizes,
			pt_sizes_count,
			&packer,
			channels_count
		);

		result = _bsmod_packAtlas(&packer, 2048, 2048, 1, package_path, resource_name, true);
		if (result != BS_RESULT_OK) {
			// TODO: free
			return result;
		}
	}

	const int glyphs_count = rasterized_glyphs.count;

   /**
    Read Kernings
    */
	FT_ULong length = 0;
	bs_List kerning_pairs = { 0 }, kerning_pairs_extended = { 0 };

	error = FT_Load_Sfnt_Table(face, FT_MAKE_TAG('G', 'P', 'O', 'S'), 0, NULL, &length);

	if (!error) {
		bs_U8* gpos = malloc(length);

		error = FT_Load_Sfnt_Table(face, FT_MAKE_TAG('G', 'P', 'O', 'S'), 0, gpos, &length);

		_bsmod_parseGPOS(&packer, &rasterized_glyphs, gpos, &kerning_pairs, &kerning_pairs_extended);

		bs_free(gpos);
	}

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

	const int kerning_pairs_count = kerning_pairs.count + kerning_pairs_extended.count;
	total_size += kerning_pairs_count * BFNT_KERNING_PAIR_SIZE;
	total_size += total_glyphs_count * BFNT_GLYPH_SIZE;

	unsigned char* data = bs_calloc(1, total_size);

	bs_setLittleEndian32(BFNT_MAGIC, data + BFNT_OFFSET_MAGIC);
	bs_setLittleEndian32(1, data + BFNT_OFFSET_VERSION);
	bs_setLittleEndian16(blocks_count, data + BFNT_OFFSET_BLOCKS_COUNT);
	bs_setLittleEndian16(pt_sizes_count, data + BFNT_OFFSET_PT_SIZES_COUNT);
	bs_setLittleEndian16(kerning_pairs_count, data + BFNT_OFFSET_KERNING_PAIRS_COUNT);
	bs_setLittleEndian32(total_glyphs_count, data + BFNT_OFFSET_GLYPHS_COUNT);
	bs_setLittleEndian16(face->units_per_EM, data + BFNT_OFFSET_UNITS_PER_EM);
	bs_setLittleEndian16(face->height, data + BFNT_OFFSET_DU_HEIGHT);

   /**
    Point sizes
    */
	unsigned char* pt_sizes_offset = data + BFNT_OFFSET_POINTS;

	for (int i = 0; i < pt_sizes_count; i++) {
		unsigned char* offset = pt_sizes_offset + i * BFNT_POINT_SIZE;

		bs_setLittleEndian32(pt_sizes[i], offset + BFNT_OFFSET_POINT_SIZE);
	}

   /**
    Unicode Blocks
    */
	unsigned char* unicode_blocks_offset = pt_sizes_offset + pt_sizes_count * BFNT_POINT_SIZE;

	for (int i = 0, glyphs_block_offset = 0; i < blocks_count; i++) {
		unsigned char* offset = unicode_blocks_offset + i * BFNT_BLOCK_SIZE;
		//bs_setLittleEndian16(i, data + BFNT_BLOCK_LOOKUP_OFFSET + blocks[i].block * sizeof(bs_U16));

		bs_setLittleEndian32(blocks[i].offset, offset + BFNT_OFFSET_BLOCK_START);
		bs_setLittleEndian16(blocks[i].count, offset + BFNT_OFFSET_BLOCK_LENGTH);
		bs_setLittleEndian16(blocks[i].size, offset + BFNT_OFFSET_BLOCK_SIZE);

		if (blocks[i].rasterize) {
			bs_setLittleEndian32(glyphs_block_offset, offset + BFNT_OFFSET_BLOCK_GLYPHS);
			glyphs_block_offset += blocks[i].count * pt_sizes_count;
		}
	}

   /**
    Glyphs
    */
	unsigned char* glyphs_offset = unicode_blocks_offset + blocks_count * BFNT_BLOCK_SIZE;

	for (int i = 0; i < glyphs_count; i++) {
		bsmod_RasterizedGlyph* glyph = bs_fetchUnit(&rasterized_glyphs, i);

		unsigned char* offset = glyphs_offset + glyph->glyph_offset;

		if (!(glyph->flags & BFNT_GLYPH_FLAG_SKIP_RENDER)) {
			bsmod_TextureInfo* info = bs_fetchUnit(&packer.info, glyph->info_id);
			bs_setLittleEndian16(info->page, offset + BFNT_OFFSET_GLYPH_PAGE);
		}

		bs_setLittleEndian16(glyph->flags, offset + BFNT_OFFSET_GLYPH_FLAGS);
		bs_setLittleEndian16(glyph->info_id, offset + BFNT_OFFSET_GLYPH_ATLAS_INDEX);
		bs_setLittleEndian16(glyph->glyph_id, offset + BFNT_OFFSET_GLYPH_GLYPH_INDEX);
		bs_setLittleEndian32(glyph->codepoint, offset + BFNT_OFFSET_GLYPH_CODEPOINT);
		bs_setLittleEndian32(glyph->x_offset, offset + BFNT_OFFSET_GLYPH_X_OFFSET);
		bs_setLittleEndian32(glyph->y_offset, offset + BFNT_OFFSET_GLYPH_Y_OFFSET);
		bs_setLittleEndian32(glyph->x_advance, offset + BFNT_OFFSET_GLYPH_X_ADVANCE);
		bs_setLittleEndian32(glyph->y_advance, offset + BFNT_OFFSET_GLYPH_Y_ADVANCE);
	}

   /**
    Kerning Pairs
    */
	unsigned char* kerning_pairs_offset = glyphs_offset + total_glyphs_count * BFNT_GLYPH_SIZE;

	int kern_id = 0;
	for (int i = 0; i < glyphs_count; i++) {
		bsmod_RasterizedGlyph* glyph = bs_fetchUnit(&rasterized_glyphs, i);

		unsigned char* offset = glyphs_offset + glyph->glyph_offset;

		int start = kern_id;
		bs_setLittleEndian16(start, offset + BFNT_OFFSET_GLYPH_KERNING_START);

		_bsmod_setKerningPairs(kerning_pairs_offset, &kern_id, &kerning_pairs, glyph->kern_pair_start, glyph->kern_pair_count);
		_bsmod_setKerningPairs(kerning_pairs_offset, &kern_id, &kerning_pairs_extended, glyph->kern_pair_extended_start, glyph->kern_pair_extended_count);

		bs_setLittleEndian16(kern_id - start, offset + BFNT_OFFSET_GLYPH_KERNING_COUNT);
	}

	assert(kern_id == kerning_pairs_count);

   /**
    Copy TTF data
    */
	unsigned char* ttf_offset = kerning_pairs_offset + kerning_pairs_count * BFNT_KERNING_PAIR_SIZE;
	memcpy(ttf_offset, ttf->value, ttf->len);

   /**
    Pack Resource
    */
	result = _bsmod_packResource(BS_RESOURCE_FONT, data, total_size, package_path, resource_name);

	_bsmod_destroyAtlasPacker(&packer);
	bs_destroyList(&bitmap_data);
	FT_Done_Face(face);
	bs_free(ttf);
	bs_free(data);
	//	if (result != BS_RESULT_OK)
	//		return result;

	return result;
}
