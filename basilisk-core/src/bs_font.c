
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

#define BS_FLAGSET(flag, cmp) ((flag >> cmp) & 0x01)
#define BS_TTF_MAX_PTS 1024



 /*==============================================================================
  * HEAD table offsets
  *============================================================================*/

#define HEAD_VERSION                    0   // 4 | fixed
#define HEAD_FONT_REVISION              4   // 4 | fixed
#define HEAD_CHECK_SUM_ADJUSTMENT       8   // 4 | uint32
#define HEAD_MAGIC_NUMBER               12  // 4 | uint32
#define HEAD_FLAGS                      16  // 2 | uint16
#define HEAD_UNITS_PER_EM               18  // 2 | uint16
#define HEAD_CREATED                    20  // 8 | longDateTime
#define HEAD_MODIFIED                   28  // 8 | longDateTime
#define HEAD_X_MIN                      36  // 2 | fWord
#define HEAD_Y_MIN                      38  // 2 | fWord
#define HEAD_X_MAX                      40  // 2 | fWord
#define HEAD_Y_MAX                      42  // 2 | fWord
#define HEAD_MAC_STYLE                  44  // 2 | uint16
#define HEAD_LOWEST_REC_PPEM            46  // 2 | uint16
#define HEAD_FONT_DIRECTION_HINT        48  // 2 | int16
#define HEAD_INDEX_TO_LOC_FORMAT        50  // 2 | int16
#define HEAD_GLYPH_DATA_FORMAT          52  // 2 | int16



 /*==============================================================================
  * MAXP table offsets
  *============================================================================*/

#define MAXP_VERSION                    0   // 4 | fixed
#define MAXP_NUM_GLYPHS                 4   // 2 | uint16
#define MAXP_MAX_POINTS                 6   // 2 | uint16
#define MAXP_MAX_CONTOURS               8   // 2 | uint16
#define MAXP_MAX_COMPONENT_POINTS       10  // 2 | uint16
#define MAXP_MAX_COMPONENT_CONTOURS     12  // 2 | uint16
#define MAXP_MAX_ZONES                  14  // 2 | uint16
#define MAXP_MAX_TWILIGHT_POINTS        16  // 2 | uint16
#define MAXP_MAX_STORAGE                18  // 2 | uint16
#define MAXP_MAX_FUNCTION_DEFS          20  // 2 | uint16
#define MAXP_MAX_INSTRUCTION_DEFS       22  // 2 | uint16
#define MAXP_MAX_STACK_ELEMENTS         24  // 2 | uint16
#define MAXP_MAX_SIZE_OF_INSTRUCTIONS   26  // 2 | uint16
#define MAXP_MAX_COMPONENT_ELEMENTS     28  // 2 | uint16
#define MAXP_MAX_COMPONENT_DEPTH        30  // 2 | uint16



 /*==============================================================================
  * HHEA table offsets
  *============================================================================*/

#define HHEA_VERSION                    0   // 4 | fixed
#define HHEA_ASCENT                     4   // 2 | fWord
#define HHEA_DESCENT                    6   // 2 | fWord
#define HHEA_LINE_GAP                   8   // 2 | fWord
#define HHEA_ADVANCE_WIDTH_MAX          10  // 2 | ufWord
#define HHEA_MIN_LEFT_SIDE_BEARING      12  // 2 | fWord
#define HHEA_MIN_RIGHT_SIDE_BEARING     14  // 2 | fWord
#define HHEA_X_MAX_EXTENT               16  // 2 | fWord
#define HHEA_CARET_SLOPE_RISE           18  // 2 | int16
#define HHEA_CARET_SLOPE_RUN            20  // 2 | int16
#define HHEA_CARET_OFFSET               22  // 2 | fWord
   // 8 bytes reserved here
#define HHEA_METRIC_DATA_FORMAT         32  // 2 | int16
#define HHEA_NUM_OF_LONG_HOR_METRICS    34  // 2 | uint16



 /*==============================================================================
  * HMTX table offsets
  *============================================================================*/

   // HMTX table offsets
#define HMTX_LONG_HOR_METRICS			0   // 4 | uin16, int16 ARRAY
// #define HMTX_LEFT_SIDE_BEARING			0   // 2 | fWord ARRAY



 /*==============================================================================
  * GLYF table offsets
  *============================================================================*/

#define GLYF_NUMBER_OF_CONTOURS             0   // 2 | int16
#define GLYF_XMIN                           2   // 2 | fWord
#define GLYF_YMIN                           4   // 2 | fWord
#define GLYF_XMAX                           6   // 2 | fWord
#define GLYF_YMAX                           8   // 2 | fWord
#define GLYF_END_PTS_OF_CONTOURS            10  // 2 | uint16 ARRAY
#define GLYF_INSTRUCTION_LENGTH(contours)   GLYF_END_PTS_OF_CONTOURS + contours * 2 // 2 | uint16
#define GLYF_INSTRUCTIONS                   10                                      // 1 | uint8  ARRAY
#define GLYF_FLAGS(offset, instructions)    offset + instructions + 2               // 1 | uint8  ARRAY

   // flags
#define GLYF_ON_CURVE   0
#define GLYF_X_SHORT    1
#define GLYF_Y_SHORT    2
#define GLYF_REPEAT     3
#define GLYF_X_SAME     4
#define GLYF_Y_SAME     5
#define GLYF_OVERLAP    6

#define GLYF_XCOORDS(offset, num_flags) offset + num_flags                  // 1 | uint8  ARRAY
#define GLYF_YCOORDS(offset, num_flags, coord) offset + num_flags + coord   // 1 | uint8  ARRAY



 /*==============================================================================
  * CMAP table offsets
  *============================================================================*/

#define CMAP_VERSION                    0   // 2 | uint16
#define CMAP_NUMBER_SUBTABLES           2   // 2 | uint16

   // field variables
#define CMAP_PLATFORM_ID                4   // 2 | uint16
#define CMAP_PLATFORM_SPECIFIC_ID       6   // 2 | uint16
#define CMAP_OFFSET                     8   // 4 | uint32
#define CMAP_TABLE_SIZE                 (2 + 2 + 4)

// formats
#define CMAP_SUBTABLE_FORMAT            0   // 2 | uint16

// #define CMAP_FORMAT0_LENGTH             2   // 2 | uint16
// #define CMAP_FORMAT0_LANGUAGE           4   // 2 | uint16
// #define CMAP_FORMAT0_GLYPH_ARRAY        6   // 256 | uint8
// #define CMAP_FORMAT0_GLYPH_ARRAY_SIZE   6   // 256 | uint8

#define CMAP_FORMAT4_LENGTH             2
#define CMAP_FORMAT4_LANGUAGE           4
#define CMAP_FORMAT4_NUM_SEGMENTS_X2	6
#define CMAP_FORMAT4_SEARCH_RANGE       8
#define CMAP_FORMAT4_ENTRY_SELECTOR     10
#define CMAP_FORMAT4_RANGE_SHIFT        12
#define CMAP_FORMAT4_END_CODE           14
// 2 bytes reserved here
#define CMAP_FORMAT4_START_CODE(num_segments) (14 + 2 + num_segments * sizeof(bs_U16))
#define CMAP_FORMAT4_ID_DELTA(num_segments) (CMAP_FORMAT4_START_CODE(num_segments) + num_segments * sizeof(bs_U16))
#define CMAP_FORMAT4_ID_RANGE_OFFSET(num_segments) (CMAP_FORMAT4_ID_DELTA(num_segments) + num_segments * sizeof(bs_U16))
#define CMAP_FORMAT4_GLYPH_ARRAY(num_segments) (CMAP_FORMAT4_ID_RANGE_OFFSET(num_segments) + num_segments * sizeof(bs_U16))



 /*==============================================================================
  * KERN table offsets
  * https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6kern.html
  *============================================================================*/

   /**
    KERN header
    these are 4 bytes each on fonts targeted only for OS X apparently, so i
    guess the entire implementation just breaks and there's no way to know?
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



static inline bs_U8 _bs_memU8(void* data, bs_U32 offset) {
    return *((bs_U8*)data + offset);
}

static inline bs_U16 _bs_memU16(void* data, bs_U32 offset) {
    const bs_U8* base = (bs_U8*)data + offset;
    return (bs_U16)(base[0] << 8 | base[1]);
}

static inline bs_U32 _bs_memU32(void* data, bs_U32 offset) {
    const bs_U8* base = (bs_U8*)data + offset;
    return (bs_U32)(base[0] << 24 | base[1] << 16 | base[2] << 8 | base[3]);
}

static inline int _bs_memcmpU32(const void* a, const void* b) {
    return memcmp(a, b, sizeof(bs_U32));
}

static bs_Result _bs_findTable(bs_TTF* ttf, const char tag[4], char** out) {
    const char* table = NULL;
    for (int i = 0; i < ttf->buffer->len - 4; i++) {
        const char* ptr = ttf->buffer->value + i;

        if (memcmp(ptr, tag, 4) == 0) {
            bs_U32 offset = _bs_memU32(ptr, 8);
            *out = ttf->buffer->value + offset;
            return BS_RESULT_OK;
        }
    }
    
    return BS_RESULT_FAILED_TO_QUERY;
}

 /** 
  'head' Table 
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6head.html
  */
static void _bs_readHeadTable(bs_TTF* ttf) {
    _bs_findTable(ttf, "head", &ttf->head.buf);
    bs_U32 version = _bs_memU32(ttf->head.buf, HEAD_VERSION);
    ttf->head.units_per_em = _bs_memU16(ttf->head.buf, HEAD_UNITS_PER_EM);
    ttf->head.index_to_loc_format = _bs_memU16(ttf->head.buf, HEAD_INDEX_TO_LOC_FORMAT);
}

 /** 
  'maxp' Table 
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6maxp.html
  */
static void _bs_readMaxpTable(bs_TTF* ttf) {
    _bs_findTable(ttf, "maxp", &ttf->maxp.buf);
    ttf->maxp.num_glyphs = _bs_memU16(ttf->maxp.buf, MAXP_NUM_GLYPHS);
}

 /** 
  'hhea' Table 
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6hhea.html
  */
static void _bs_readHheaTable(bs_TTF* ttf) {
    _bs_findTable(ttf, "hhea", &ttf->hhea.buf);
    ttf->hhea.num_of_long_hor_metrics = _bs_memU16(ttf->hhea.buf, HHEA_NUM_OF_LONG_HOR_METRICS);
}

 /** 
  'kern' Table 
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6kern.html 
  */
static inline int _bs_findPair(uint8_t* base, int count, uint16_t left) {
    int lo = 0;
    int hi = count;

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        bs_U16 mid_left = _bs_memU16(base + mid * 6, 0);

        if (mid_left < left)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

static inline int _bs_kernFormat0(bs_TTF* ttf, char* kern, int offset) {
    bs_U16 pairs_count = _bs_memU16(kern, KERN_FORMAT0_PAIRS_COUNT + offset);

    bs_U8* base = kern + KERN_FORMAT0_PAIR_START + offset;

    for (int i = 0; i < pairs_count; i++) {
        bs_U8* p = base + i * sizeof(bs_U16) * 3;

        bs_U16 left = _bs_memU16(p, KERN_FORMAT0_PAIR_LEFT);
        bs_U16 right = _bs_memU16(p, KERN_FORMAT0_PAIR_RIGHT);
        bs_U16 value = _bs_memU16(p, KERN_FORMAT0_PAIR_VALUE);

        bs_Glyph* left_glyph = NULL;
        int right_glyph_index = -1;

        for (int j = 0; j < ttf->glyphs.count; j++) {
            bs_Glyph* glyph = _bs_fetchUnit(&ttf->glyphs, j);

            if (glyph->index == left)
                left_glyph = glyph;

            if (glyph->index == right)
                right_glyph_index = j;

            if (left_glyph && right_glyph_index > 0)
                break;
        }

        if (!left_glyph || right_glyph_index == -1)
            continue;

        _bs_pushBack(&ttf->kerning_pairs, &(bs_KerningPair){
            .right_index = right_glyph_index,
            .right = right,
            .value = value,
        });

        left_glyph->pairs_count++;
    }

    return sizeof(bs_U16) * 4 + sizeof(bs_U16) * 3 * pairs_count;
}

BSAPI void _bs_readKernTable(bs_TTF* ttf) {
    char* buf;
    _bs_findTable(ttf, "kern", &buf);
    
    // TODO: these can be bs_U32 on OS X only fonts but idk how 2 check
    bs_U16 version = _bs_memU16(buf, KERN_VERSION);
    bs_U16 subtables_count = _bs_memU16(buf, KERN_NUMBER_OF_TABLES);

    int header_size =
        sizeof(bs_U32) +
        sizeof(bs_U16) * 3;
    if (version == 1) // AAT - Apple Advanced Typography
        header_size += sizeof(bs_U16);

    for (int i = 0, offset = 0; i < subtables_count; i++) {
        bs_U32 length = _bs_memU32(buf, KERN_LENGTH + offset);
        bs_U16 coverage = _bs_memU16(buf, KERN_COVERAGE + offset);
        // bs_U16 tuple_index = _bs_memU16(buf, KERN_TUPLE_INDEX + offset); // AAT

        int vertical = (coverage & KERN_COVERAGE_VERTICAL) != 0;
        int cross_stream = (coverage & KERN_COVERAGE_CROSS_STREAM) != 0;
        int variation = (coverage & KERN_COVERAGE_VARIATION) != 0;

        bs_U16 format = (coverage & 0xFF00) >> 8;

        switch (format) {
        case 0: offset += _bs_kernFormat0(ttf, buf, offset + header_size); break;
        case 1:
        case 2:
        case 3:
            _bs_warnF("KERN format %d is not supported", format);
        default:
            _bs_warnF("KERN format %d is not between 0..4", format);
        }
    }
}

 /**
  'hmtx' Table
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6hmtx.html
  */
static void _bs_readHmtxTable(bs_TTF* ttf, bs_Glyph* glyph) {
    _bs_findTable(ttf, "hmtx", &ttf->hmtx.buf);

    bs_U32 offset = glyph->index * sizeof(bs_LongHorMetric);
    glyph->long_hor_metric.advance_width = _bs_memU16(ttf->hmtx.buf, offset);
    glyph->long_hor_metric.left_side_bearing = (bs_I16)_bs_memU16(ttf->hmtx.buf, offset + 2);
}


 /**
  'loca' Table
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6loca.html
  */
static bs_U32 _bs_readLocaTable(bs_TTF* ttf, int id) {
    _bs_findTable(ttf, "loca", &ttf->loca.buf);

    bs_U32 offset = 0;
    if (ttf->head.index_to_loc_format == 0)
        offset = _bs_memU16(ttf->loca.buf, id * sizeof(bs_U16)) * 2;
    else
        offset = _bs_memU32(ttf->loca.buf, id * sizeof(bs_U32));

    return offset;
}

 /**
  'glyf' Table
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6glyf.html
  */
static int _bs_glyfCoords(bs_Glyf* glyf, bool y, bs_U8* flags, bs_GlyfPt* pts, int offset, int num_points) {
    bs_U16 coord_prev = 0;
    for (int i = 0; i < num_points; i++) {
        bs_U8 flag = flags[i];
        bs_U16 coord;

	    // If coord is 8-bit
	    if (BS_FLAGSET(flag, GLYF_X_SHORT + y)) {
	        coord = _bs_memU8(glyf->buf, offset);
	        offset += 1;

            if (!BS_FLAGSET(flag, GLYF_X_SAME + y)) {
                coord = -coord;
            }

	        coord += coord_prev;
	    } else {
	        if (BS_FLAGSET(flag, GLYF_X_SAME + y)) {
		        coord = coord_prev;
	        } else {
		        coord = _bs_memU16(glyf->buf, offset);
		        coord += coord_prev;
		        offset += 2;
	        }
	    }

	    coord_prev = coord;
	    char *data = (char *)(pts + i);
	    bs_U16 *val = (bs_U16*)(data + y * sizeof(bs_U16));

	    *val = coord;
    }
    
    return offset;
}

static void _bs_readGlyfTable(bs_TTF* ttf, bs_Glyph* glyph) {
    if (_bs_findTable(ttf, "glyf", ttf->glyf.buf) != BS_RESULT_OK) {
        return;
    }

    // get location of glyph in ttf buffer
    bs_U32 loc = _bs_readLocaTable(ttf, glyph->index);
    ttf->glyf.buf += loc;

    // get bounding boxes
    glyph->x_min = _bs_memU16(ttf->glyf.buf, GLYF_XMIN);
    glyph->y_min = _bs_memU16(ttf->glyf.buf, GLYF_YMIN);
    glyph->x_max = _bs_memU16(ttf->glyf.buf, GLYF_XMAX);
    glyph->y_max = _bs_memU16(ttf->glyf.buf, GLYF_YMAX);

    // parse contours
    int num_contours = _bs_memU16(ttf->glyf.buf, GLYF_NUMBER_OF_CONTOURS);
    int* end_pts = _alloca(num_contours * sizeof(int));
    for (int i = 0; i < num_contours; i++) {
        end_pts[i] = _bs_memU16(ttf->glyf.buf, GLYF_END_PTS_OF_CONTOURS + i * 2);
    }

    // num points is equal to end of last contour
    int num_points = end_pts[num_contours - 1] + 1;

    int instruction_offset = GLYF_INSTRUCTION_LENGTH(num_contours);
    int num_instructions = _bs_memU16(ttf->glyf.buf, instruction_offset);

    int flag_offset = GLYF_FLAGS(instruction_offset, num_instructions);
    int flag_offset_original = flag_offset;

    int coord_offset = GLYF_XCOORDS(flag_offset, num_points);

    glyph->coords = _bs_malloc(num_points * sizeof(bs_GlyfPt));
    glyph->contours = _bs_malloc(num_contours * sizeof(uint16_t));
    glyph->num_contours = num_contours;
    glyph->num_points = num_points;

    for (int i = 0; i < num_contours; i++)
        glyph->contours[i] = end_pts[i];

    int num_repeats_total = 0;
    bs_U8* flags = _alloca(num_points);

    // Parse flags
    for (int i = 0; i < num_points; i++) {
        flags[i] = _bs_memU8(ttf->glyf.buf, flag_offset++);

        // Add repeated flags
        if (BS_FLAGSET(flags[i], GLYF_REPEAT)) {
            int num_repeats = _bs_memU8(ttf->glyf.buf, flag_offset++);
            int flag_repeated = flags[i];

            num_repeats_total += num_repeats - 1;

            assert((i + num_repeats) <= num_points);

            for (int j = 0; j < num_repeats; j++)
                flags[++i] = flag_repeated;
        }
    }

    coord_offset -= num_repeats_total;

    for (int i = 0; i < num_points; i++) {
        glyph->coords[i].on_curve = BS_FLAGSET(flags[i], GLYF_ON_CURVE);
    }

    // Get X and Y coords
    coord_offset = _bs_glyfCoords(&ttf->glyf, 0, flags, glyph->coords, coord_offset, num_points);
    coord_offset = _bs_glyfCoords(&ttf->glyf, 1, flags, glyph->coords, coord_offset, num_points);
}

 /**
  'cmap' Table
  https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6cmap.html
  */
static bs_Result _bs_cmapFormat4(bs_TTF* ttf, bs_Glyph* glyph, char* subtable) {
    bs_U16 seg_count_x2 = _bs_memU16(subtable, CMAP_FORMAT4_NUM_SEGMENTS_X2);
    bs_U16 seg_count = seg_count_x2 / 2;

    int index = -1;

    for (int j = 0; j < seg_count; j++) {
        bs_U16 end_code = _bs_memU16(subtable, CMAP_FORMAT4_END_CODE + j * sizeof(bs_U16));

        if (end_code >= glyph->code) {
            index = j;
            break;
        }
    }

    if (index == -1) {
        _bs_warnF("Couldn't find format4 glyph index for glyph %d in font \"%s\"", glyph->code, ttf->name);
        return BS_RESULT_FAILED_TO_QUERY;
    }

    bs_U16* id_range_offset_address = (bs_U16*)(subtable + CMAP_FORMAT4_ID_RANGE_OFFSET(seg_count) + index * sizeof(bs_U16));
    bs_U16 id_range_offset = _bs_memU16(subtable, CMAP_FORMAT4_ID_RANGE_OFFSET(seg_count) + index * sizeof(bs_U16));
    bs_U16 start_code = _bs_memU16(subtable, CMAP_FORMAT4_START_CODE(seg_count) + index * sizeof(bs_U16));
    bs_I16 id_delta = _bs_memU16(subtable, CMAP_FORMAT4_ID_DELTA(seg_count) + index * sizeof(bs_U16));
    bs_U16 end_code = _bs_memU16(subtable, CMAP_FORMAT4_END_CODE + index * sizeof(bs_U16));

    int glyph_index;

    if (id_range_offset == 0) {
        glyph_index = (glyph->code + id_delta) & 0xFFFF;
    }
    else {
        bs_U8* addr =
            (bs_U8*)id_range_offset_address +
            id_range_offset +
            2 * (glyph->code - start_code);

        glyph_index = _bs_memU16(addr, 0);

        if (glyph_index != 0)
            glyph_index = (glyph_index + id_delta) & 0xFFFF;
    }

    glyph->index = glyph_index;

    return BS_RESULT_OK;
}

static bool _bs_readCmapTable(bs_TTF* ttf, bs_Glyph* glyph) {
    char* cmap; 
    _bs_findTable(ttf, "cmap", &cmap);

    bs_U16 subtables_count = _bs_memU16(cmap, CMAP_NUMBER_SUBTABLES);

    int subtable_offset = -1;
    for (int i = 0; i < subtables_count; i++) {
        bs_U32 platform_id          = _bs_memU16(cmap, CMAP_PLATFORM_ID + CMAP_TABLE_SIZE * i);
        bs_U32 platform_specific_id = _bs_memU16(cmap, CMAP_PLATFORM_SPECIFIC_ID + CMAP_TABLE_SIZE * i);
        subtable_offset             = _bs_memU32(cmap, CMAP_OFFSET + CMAP_TABLE_SIZE * i);

        if (platform_id == 0) 
            break;
    }

    if (subtable_offset == -1) {
        _bs_warnF("Font \"%s\" has an unsupported encoding type, only Unicode is supported", ttf->name);
        return false;
    }

    char* subtable = cmap + subtable_offset;
    bs_U16 format = _bs_memU16(subtable, CMAP_SUBTABLE_FORMAT);

    switch (format) {
    case 4: _bs_cmapFormat4(ttf, glyph, subtable); break;
    default: 
        _bs_warnF("TTF format %d has not been implemented yet", format);
        return false;
    }

    return true;
}

static int _bs_cmpFloats(const void *a, const void *b) {
    float f_a = *(float *)a;
    float f_b = *(float *)b;

    if (f_a < f_b) 
        return -1;
    else if (f_a > f_b) 
        return 1;

    return 0;
}

static int _bs_glyphWindingOrder(bs_Glyph* glyph, bs_vec2 point, bs_vec2* pts, int num_pts) {
    int winding = 0;

    for (int i = 0; i < num_pts; ++i) {
        bs_vec2 pt1 = pts[i];
        bs_vec2 pt2 = pts[(i + 1) % num_pts];

        if (pt1.y <= point.y && pt2.y > point.y) {
            float intersect_x = pt1.x + (point.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y);
            if (intersect_x > point.x)
                winding++;
        }
        else if (pt1.y > point.y && pt2.y <= point.y) {
            float intersect_x = pt1.x + (point.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y);
            if (intersect_x > point.x)
                winding--;
        }
    }

    return winding;
}

static void _bs_calculateContourCurves(bs_Glyph* glyph, int contour, bs_vec2* out, bs_U32* out_num_pts) {
#define BS_TTF_DETAIL 4

    uint16_t first = (contour == 0) ? 0 : glyph->contours[contour - 1] + 1;
    uint16_t last = glyph->contours[contour] + 1;

    for (int j = first; j < last; j++) {
        bs_GlyfPt curr = glyph->coords[j];
        bs_GlyfPt curr_off, next_off;

        int idx;
        if ((j + 1) >= last) 
            idx = (j + 1) - last + first;
        else
            idx = (j + 1);

        curr_off = glyph->coords[idx];
        if (!curr.on_curve) continue;

        bs_vec2 curr_off_v, next_off_v, curr_v = BS_V2(curr.x, curr.y);
        if (curr_off.on_curve) {
            out[(*out_num_pts)++] = curr_v;
            continue;
        }

        while (!(curr_off = glyph->coords[idx]).on_curve) {
            next_off = glyph->coords[((j + 2) >= last) ? ((j + 2) - last + first) : (j + 2)];
            if (next_off.on_curve) break;

            curr_off_v = BS_V2(curr_off.x, curr_off.y);
            next_off_v = BS_V2(next_off.x, next_off.y);

            bs_vec2 mid;
            _bs_v2Mid(&curr_off_v, &next_off_v, &mid);

            bs_vec2 elems[BS_TTF_DETAIL + 1];
            _bs_v2QuadBezier(&curr_v, &curr_off_v, &mid, elems, BS_TTF_DETAIL);

            elems[BS_TTF_DETAIL] = mid;
            for (int i = 0; i < BS_TTF_DETAIL; i++) {
                out[(*out_num_pts)++] = elems[i];
            }

            curr_v = mid;
            j++;
            if ((j + 1) >= last) idx = (j + 1) - last + first;
            else                 idx = (j + 1);
        }

        curr_off = glyph->coords[((j + 1) >= last) ? ((j + 1) - last + first) : (j + 1)];
        next_off = glyph->coords[((j + 2) >= last) ? ((j + 2) - last + first) : (j + 2)];
        curr_off_v = BS_V2(curr_off.x, curr_off.y);
        next_off_v = BS_V2(next_off.x, next_off.y);

        double t = 0.0;
        double incr = 1.0 / (double)BS_TTF_DETAIL;

        for (int k = 0; k < BS_TTF_DETAIL; k++, t += incr) {
            bs_vec2 v;
            v.x = (1 - t) * (1 - t) * curr_v.x + 2 * (1 - t) * t * curr_off_v.x + t * t * next_off_v.x;
            v.y = (1 - t) * (1 - t) * curr_v.y + 2 * (1 - t) * t * curr_off_v.y + t * t * next_off_v.y;
            out[(*out_num_pts)++] = v;
        }
    }
    out[(*out_num_pts)++] = BS_V2(glyph->coords[first].x, glyph->coords[first].y);
}

#define AA_SAMPLES 4
#define AA_TOTAL (AA_SAMPLES * AA_SAMPLES)

BSAPI void _bs_rasterizeGlyph(bs_TTF* font, bs_Glyph* glyph, int width, int height, char* out_bmp, float scale) {
   // int num_pts = font->lookup[code].num_points;
    bs_vec2 out[BS_TTF_MAX_PTS]; // todo too much stack
    bs_U32 out_num_pts = 0;

    for (int i = 0; i < glyph->num_contours; i++) {
        bs_U32 num_pts = 0;
        bs_vec2* pts = out + out_num_pts;
        _bs_calculateContourCurves(glyph, i, pts, &num_pts);
        out_num_pts += num_pts;

        for (int j = 0; j < num_pts; j++) {
            pts[j].x = (pts[j].x - glyph->x_min) * scale;
            pts[j].y = (pts[j].y - glyph->y_min) * scale;
        }

        for (int y = 0; y < glyph->height; y++) {
            float* intersections = _alloca(num_pts * sizeof(float));
            int num_intersections = 0;

            for (int j = 0; j < num_pts; j++) {
                bs_vec2 pt0 = pts[j];
                bs_vec2 pt1 = pts[(j + 1) % num_pts];

                if ((y < fmin(pt0.y, pt1.y)) || (y >= fmax(pt0.y, pt1.y))) 
                    continue;

                float dy = pt1.y - pt0.y;
                if (dy != 0) {
                    float dx = pt1.x - pt0.x;
                    float x_intersect = pt0.x + (y - pt0.y) * dx / dy;
                    intersections[num_intersections++] = x_intersect;
                }
            }

            qsort(intersections, num_intersections, sizeof(float), _bs_cmpFloats);

            for (int j = 0; j < num_intersections - 1; j += 2) {
                int start = ceil(intersections[j]);
                int end = floor(intersections[j + 1]);

                for (int x = start; x <= end; x++) {
                    if (x >= 0 && x < glyph->width) {
                        int z = _bs_glyphWindingOrder(glyph, BS_V2(x, y), pts, num_pts);

                        out_bmp[y * glyph->width + x] = z == -1 ? 255 : 0;
                    }
                }
            }
        }
    }
}

BSAPI void _bs_glyph(bs_TTF* ttf, bs_U16 code) {
    //int index = _bs_glyphIndex(ttf, code);

    bs_Glyph* glyph = _bs_pushBack(&ttf->glyphs, &(bs_Glyph) {.code = code});

    _bs_readCmapTable(ttf, glyph);
    _bs_readGlyfTable(ttf, glyph);
    _bs_readHmtxTable(ttf, glyph);
}

BSAPI void _bs_destroyTtf(bs_TTF* ttf) {
    free(ttf->buffer);
    //free(ttf->atlas);
}

BSAPI bs_Result _bs_ttf(bs_TTF* existing, const char* path, bs_U32 flags) {
    bs_Result result;

    bs_TTF ttf = {
        .glyphs = _bs_list(sizeof(bs_Glyph), 64),
        .kerning_pairs = _bs_list(sizeof(bs_KerningPair), 64),
    };

    result = _bs_loadFile(&ttf.buffer, path, strlen(path));
    if (result != BS_RESULT_OK)
        return result;

    ttf.table_count = _bs_memU16(ttf.buffer->value, 4);

    _bs_readHeadTable(&ttf);
    _bs_readMaxpTable(&ttf);
    _bs_readHheaTable(&ttf);

    memcpy(existing, &ttf, sizeof(bs_TTF));

    return BS_RESULT_OK;
}



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
    return BS_RESULT_OK;
}