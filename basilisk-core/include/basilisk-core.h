
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

#ifndef BASILISK_CORE_H
#define BASILISK_CORE_H

#include <basilisk-core.gen.h>

#ifdef __linux__
#include <alloca.h>
#endif

#define BS_IV2(x, y) (bs_ivec2) { x, y }
#define BS_IV3(x, y, z) (bs_ivec3) { x, y, z }
#define BS_IV4(x, y, z, w) (bs_ivec4) { x, y, z, w }

#define BS_V2(x, y) (bs_vec2) { x, y }
#define BS_V3(x, y, z) (bs_vec3) { x, y, z }
#define BS_V4(x, y, z, w) (bs_vec4) { x, y, z, w }

#define BS_V2_TO_V3(v, s) (bs_vec3) { v.x, v.y, s }
#define BS_V2_TO_V4(v, s1, s2) (bs_vec4) { v.x, v.y, s1, s2 }
#define BS_V3_TO_V4(v, s) (bs_vec4) { v.x, v.y, v.z, s }

#define BS_IV2_TO_V2(v) (bs_vec2) { v.x, v.y }
#define BS_IV3_TO_V3(v) (bs_vec4) { v.x, v.y, v.z }
#define BS_IV4_TO_V4(v) (bs_vec4) { v.x, v.y, v.z, v.w }

// TODO: make functions instead
#define BS_V2_TO_DEGREES(v) BS_V2(bs_degrees(v.x), bs_degrees(v.y))
#define BS_V3_TO_DEGREES(v) BS_V3(bs_degrees(v.x), bs_degrees(v.y), bs_degrees(v.z))

#define BS_V2_TO_RADIANS(v) BS_V2(bs_radians(v.x), bs_radians(v.y))
#define BS_V3_TO_RADIANS(v) BS_V3(bs_radians(v.x), bs_radians(v.y), bs_radians(v.z))

#define BS_V2_ADD(a, b) (bs_vec2) { a.x + b.x, a.y + b.y }
#define BS_V3_ADD(a, b) (bs_vec3) { a.x + b.x, a.y + b.y, a.z + b.z }
#define BS_V4_ADD(a, b) (bs_vec4) { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w }

#define BS_V2_SUB(a, b) (bs_vec2) { a.x - b.x, a.y - b.y }
#define BS_V3_SUB(a, b) (bs_vec3) { a.x - b.x, a.y - b.y, a.z - b.z }
#define BS_V4_SUB(a, b) (bs_vec4) { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w }

#define BS_V2_MUL(a, b) (bs_vec2) { a.x * b.x, a.y * b.y }
#define BS_V3_MUL(a, b) (bs_vec3) { a.x * b.x, a.y * b.y, a.z * b.z }
#define BS_V4_MUL(a, b) (bs_vec4) { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w }

#define BS_V2_DIV(a, b) (bs_vec2) { a.x / b.x, a.y / b.y }
#define BS_V3_DIV(a, b) (bs_vec3) { a.x / b.x, a.y / b.y, a.z / b.z }
#define BS_V4_DIV(a, b) (bs_vec4) { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w }

#define BS_V2_ADD_S(a, s) (bs_vec2) { a.x + s, a.y + s }
#define BS_V3_ADD_S(a, s) (bs_vec3) { a.x + s, a.y + s, a.z + s }
#define BS_V4_ADD_S(a, s) (bs_vec4) { a.x + s, a.y + s, a.z + s, a.w + s }

#define BS_V2_SUB_S(a, s) (bs_vec2) { a.x - s, a.y - s }
#define BS_V3_SUB_S(a, s) (bs_vec3) { a.x - s, a.y - s, a.z - s }
#define BS_V4_SUB_S(a, s) (bs_vec4) { a.x - s, a.y - s, a.z - s, a.w - s }

#define BS_V2_MUL_S(a, s) (bs_vec2) { a.x * s, a.y * s }
#define BS_V3_MUL_S(a, s) (bs_vec3) { a.x * s, a.y * s, a.z * s }
#define BS_V4_MUL_S(a, s) (bs_vec4) { a.x * s, a.y * s, a.z * s, a.w * s }

#define BS_V2_DIV_S(a, s) (bs_vec2) { a.x / s, a.y / s }
#define BS_V3_DIV_S(a, s) (bs_vec3) { a.x / s, a.y / s, a.z / s }
#define BS_V4_DIV_S(a, s) (bs_vec4) { a.x / s, a.y / s, a.z / s, a.w / s }

#define BS_V3_MAX(a, b) BS_V3(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z)
#define BS_V3_MIN(a, b) BS_V3(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z)

#ifdef _WIN32

#define bs_alloca                                                    \
    _alloca

#else

#define bs_alloca                                                    \
    alloca

#endif

#define BS_WARN_UNSUPPORTED_VERSION(resource_type, path)             \
    bs_criticalF("Unsupported version for %s \"%s\"", resource_type, path)
   // _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_CRITICAL_ERROR, BS_RESULT_CORRUPTED, BS_RESULT_CORRUPTED, __func__, __FILE__, __LINE__, "Unsupported version for %s \"%s\"", resource_type, path)

#define BS_WARN_INVALID_MAGIC(resource_type, path)                   \
    bs_criticalF("Invalid magic for %s \"%s\"", resource_type, path)
   // _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_CRITICAL_ERROR, BS_RESULT_CORRUPTED, BS_RESULT_CORRUPTED, __func__, __FILE__, __LINE__, "Invalid magic for %s \"%s\"", resource_type, path)

#define BS_WARN(format, ...) \
    bs_warnF("%s at %s:%d: " format, __func__, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)




  /*==============================================================================
   * BPAK Format
   *============================================================================*/

 /**
  Header
  */
#define BPAK_OFFSET_MAGIC                    0 // U32
#define BPAK_OFFSET_RESOURCES_COUNT          4 // U32
#define BPAK_OFFSET_RESOURCES_TYPES_COUNT    8 // U32
#define BPAK_HEADER_RESERVED_0              12 // U32

#define BPAK_HEADER_SIZE                    16

 /**
  Resource types
  */
#define BPAK_RESOURCE_TYPES_OFFSET          BPAK_HEADER_SIZE

#define BPAK_OFFSET_RESOURCE_TYPE_START     0 // U32
#define BPAK_OFFSET_RESOURCE_TYPE_COUNT     4 // U32

#define BPAK_RESOURCE_TYPE_SIZE             8

 /**
  Resources

  Ends with resource name + \n
  */
#define BPAK_OFFSET_RESOURCE_NAME_HASH      0 // U64
#define BPAK_OFFSET_RESOURCE_CHUNK          8 // I32
#define BPAK_OFFSET_RESOURCE_START         12 // I32
#define BPAK_OFFSET_RESOURCE_SIZE          16 // I32
#define BPAK_OFFSET_RESOURCE_NAME_LENGTH   20 // I32
#define BPAK_OFFSET_RESOURCE_TYPE          24 // I32
#define BPAK_RESOURCE_RESERVED_0           28 // I32

#define BPAK_RESOURCE_SIZE                 32



  /*==============================================================================
   * BATL Version 1
   *============================================================================*/



  /*==============================================================================
   * BBND Version 1
   *============================================================================*/

 /**
  Binding header
  */
#define BBND_OFFSET_MAGIC                    0 // U32
#define BBND_OFFSET_VERSION                  4 // U32
#define BBND_OFFSET_BIND_SET                 8 // U32
#define BBND_OFFSET_BIND_POINT              12 // U32
#define BBND_OFFSET_DESCRIPTOR_COUNT        16 // U32
#define BBND_OFFSET_SHADER_STAGES           20 // U32
#define BBND_OFFSET_DESCRIPTOR_TYPE         24 // U32
#define BBND_RESERVED_0                     28 // U32

#define BBND_HEADER_SIZE                    32



  /*==============================================================================
   * BFNT Version 1
   *============================================================================*/

 /**
  Font header
  */
#define BFNT_OFFSET_MAGIC                           0 // U32
#define BFNT_OFFSET_VERSION                         4 // U32
#define BFNT_OFFSET_GLYPHS_COUNT                    8 // U32
#define BFNT_OFFSET_BLOCKS_COUNT                   12 // U16
#define BFNT_OFFSET_PT_SIZES_COUNT                 14 // U16
#define BFNT_OFFSET_KERNING_PAIRS_COUNT            16 // U16
#define BFNT_OFFSET_UNITS_PER_EM                   18 // U16
#define BFNT_OFFSET_DU_HEIGHT                      20 // I16
#define BFNT_OFFSET_RESERVED                       22 // U16

 /**
  Mapping all 355 codepoint blocks found in Unicode 18.0.0 to an
  index pointing to an element in the font specific codepoints
  */
//#define BFNT_BLOCK_LOOKUP_OFFSET       24
//#define BFNT_BLOCK_LOOKUP_LENGTH      355 // 355 * U16
//
//#define BFNT_HEADER_SIZE (BFNT_BLOCK_LOOKUP_OFFSET + BFNT_BLOCK_LOOKUP_LENGTH)

#define BFNT_HEADER_SIZE                24

 /**
  Rasterized pt sizes
  */
#define BFNT_OFFSET_POINTS              BFNT_HEADER_SIZE
#define BFNT_OFFSET_POINT_SIZE          0 // U32
#define BFNT_POINT_SIZE                 4

 /**
  Font specific codepoint ranges
  */
#define BFNT_OFFSET_BLOCK_START         0 // U32
#define BFNT_OFFSET_BLOCK_LENGTH        4 // U16
#define BFNT_OFFSET_BLOCK_SIZE          6 // U16
#define BFNT_OFFSET_BLOCK_GLYPHS        8 // U32 - Value is 0 if no atlas is available

#define BFNT_BLOCK_SIZE                12

 /**
  Rasterized glyphs
  */

#define BFNT_GLYPH_FLAG_SKIP_RENDER            (1 << 0) // Don't render certain characters like spaces ' '

#define BFNT_OFFSET_GLYPH_FLAGS                0 // U16
#define BFNT_OFFSET_GLYPH_PAGE                 2 // U16
#define BFNT_OFFSET_GLYPH_KERNING_START        4 // U16
#define BFNT_OFFSET_GLYPH_KERNING_COUNT        6 // U16
#define BFNT_OFFSET_GLYPH_GLYPH_INDEX          8 // U16
#define BFNT_OFFSET_GLYPH_ATLAS_INDEX         10 // U16
#define BFNT_OFFSET_GLYPH_CODEPOINT           12 // U32
#define BFNT_OFFSET_GLYPH_X_OFFSET            16 // I32
#define BFNT_OFFSET_GLYPH_Y_OFFSET            20 // I32
#define BFNT_OFFSET_GLYPH_X_ADVANCE           24 // I32
#define BFNT_OFFSET_GLYPH_Y_ADVANCE           28 // I32

#define BFNT_GLYPH_SIZE                       32

 /**
  Kerning pairs
  */
#define BFNT_OFFSET_KERNING_PAIR_RIGHT         0 // U32
#define BFNT_OFFSET_KERN_LEFT_X_PLACEMENT      4 // I16
#define BFNT_OFFSET_KERN_LEFT_Y_PLACEMENT      6 // I16
#define BFNT_OFFSET_KERN_LEFT_X_ADVANCE        8 // I16
#define BFNT_OFFSET_KERN_LEFT_Y_ADVANCE       10 // I16
#define BFNT_OFFSET_KERN_RIGHT_X_PLACEMENT    12 // I16
#define BFNT_OFFSET_KERN_RIGHT_Y_PLACEMENT    14 // I16
#define BFNT_OFFSET_KERN_RIGHT_X_ADVANCE      16 // I16
#define BFNT_OFFSET_KERN_RIGHT_Y_ADVANCE      18 // I16

#define BFNT_KERNING_PAIR_SIZE             20



  /*==============================================================================
   * Little endian
   *
   * Taken from Linux source code
   * https://github.com/torvalds/linux/blob/master/tools/include/tools/le_byteshift.h
   *============================================================================*/

static inline bs_U32 _bs_getLittleEndian16(const bs_U8* p) {
    return p[0] | p[1] << 8;
}

static inline bs_U32 _bs_getLittleEndian32(const bs_U8* p) {
    return p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
}

static inline bs_U64 _bs_getLittleEndian64(const bs_U8* p) {
    return (bs_U64)_bs_getLittleEndian32(p + 4) << 32 | _bs_getLittleEndian32(p);
}

static inline void _bs_setLittleEndian16(bs_U16 val, bs_U8* p) {
    *p++ = val;
    *p++ = val >> 8;
}

static inline void _bs_setLittleEndian32(bs_U32 val, bs_U8* p) {
    _bs_setLittleEndian16(val >> 16, p + 2);
    _bs_setLittleEndian16(val, p);
}

static inline void _bs_setLittleEndian64(bs_U64 val, bs_U8* p) {
    _bs_setLittleEndian32(val >> 32, p + 4);
    _bs_setLittleEndian32(val, p);
}

static inline bs_U16 bs_getLittleEndian16(const bs_U8* p) {
    return _bs_getLittleEndian16((const bs_U8*)p);
}

static inline bs_U32 bs_getLittleEndian32(const void* p) {
    return _bs_getLittleEndian32((const bs_U8*)p);
}

static inline bs_U64 bs_getLittleEndian64(const void* p) {
    return _bs_getLittleEndian64((const bs_U8*)p);
}

static inline void bs_setLittleEndian16(bs_U16 val, void* p) {
    _bs_setLittleEndian16(val, p);
}

static inline void bs_setLittleEndian32(bs_U32 val, void* p) {
    _bs_setLittleEndian32(val, p);
}

static inline void bs_setLittleEndian64(bs_U64 val, void* p) {
    _bs_setLittleEndian64(val, p);
}

static inline float bs_getLittleEndianF32(const void* p) {
    bs_U32 bits = bs_getLittleEndian32(p);
    return *(float*)&bits;
}

static inline void bs_setLittleEndianF32(float f, void* p) {
    bs_setLittleEndian32(*(bs_U32*)&f, p);
}



  /*==============================================================================
   * Big endian
   *
   * Taken from Linux source code
   * https://github.com/torvalds/linux/blob/master/tools/include/tools/be_byteshift.h
   *============================================================================*/

static inline bs_U16 _bs_getBigEndian16(const bs_U8* p) {
    return p[0] << 8 | p[1];
}

static inline bs_U32 _bs_getBigEndian32(const bs_U8* p) {
    return p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
}

static inline bs_U64 _bs_getBigEndian64(const bs_U8* p) {
    return (bs_U64)_bs_getBigEndian32(p) << 32 | _bs_getBigEndian32(p + 4);
}

static inline void _bs_setBigEndian16(bs_U16 val, bs_U8* p) {
    *p++ = val >> 8;
    *p++ = val;
}

static inline void _bs_setBigEndian32(bs_U32 val, bs_U8* p) {
    _bs_setBigEndian16(val >> 16, p);
    _bs_setBigEndian16(val, p + 2);
}

static inline void _bs_setBigEndian64(bs_U64 val, bs_U8* p) {
    _bs_setBigEndian32(val >> 32, p);
    _bs_setBigEndian32(val, p + 4);
}

static inline bs_U16 bs_getBigEndian16(const void* p) {
    return _bs_getBigEndian16((const bs_U8*)p);
}

static inline bs_U32 bs_getBigEndian32(const void* p) {
    return _bs_getBigEndian32((const bs_U8*)p);
}

static inline bs_U64 bs_getBigEndian64(const void* p) {
    return _bs_getBigEndian64((const bs_U8*)p);
}

static inline void bs_setBigEndian16(bs_U16 val, void* p) {
    _bs_setBigEndian16(val, p);
}

static inline void bs_setBigEndian32(bs_U32 val, void* p) {
    _bs_setBigEndian32(val, p);
}

static inline void bs_setBigEndian64(bs_U64 val, void* p) {
    _bs_setBigEndian64(val, p);
}

static inline float bs_getBigEndianF32(const void* p) {
    bs_U32 bits = bs_getBigEndian32(p);
    return *(float*)&bits;
}

static inline void bs_setBigEndianF32(float f, void* p) {
    bs_setBigEndian32(*(bs_U32*)&f, p);
}

#endif
