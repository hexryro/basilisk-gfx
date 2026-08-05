
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



  /*==============================================================================
   * BPAK Format
   *============================================================================*/

 /**
  Header
  */
#define BS_BPAK_MAGIC_OFFSET                    0 // U32
#define BS_BPAK_RESOURCES_COUNT_OFFSET          4 // U32
#define BS_BPAK_RESOURCES_TYPES_COUNT_OFFSET    8 // U32
#define BS_BPAK_RESOURCES_RESERVED             12 // U32

#define BS_BPAK_HEADER_SIZE                    16

 /**
  Resource types
  */
#define BS_BPAK_RESOURCE_TYPES_OFFSET          BS_BPAK_HEADER_SIZE

#define BS_BPAK_RESOURCE_TYPE_START_OFFSET     0 // U32
#define BS_BPAK_RESOURCE_TYPE_COUNT_OFFSET     4 // U32

#define BS_BPAK_RESOURCE_TYPE_SIZE             8

 /**
  Resources

  Ends with resource name + \n\0
  */
#define BS_BPAK_RESOURCE_NAME_HASH_OFFSET      0 // U64
#define BS_BPAK_RESOURCE_CHUNK_OFFSET          8 // I32
#define BS_BPAK_RESOURCE_START_OFFSET         12 // I32
#define BS_BPAK_RESOURCE_SIZE_OFFSET          16 // I32
#define BS_BPAK_RESOURCE_NAME_LENGTH_OFFSET   20 // I32
#define BS_BPAK_RESOURCE_TYPE_OFFSET          24 // I32
#define BS_BPAK_RESOURCE_RESERVED             28 // I32

#define BS_BPAK_RESOURCE_SIZE                  32



  /*==============================================================================
   * BATL Version 1
   *============================================================================*/



  /*==============================================================================
   * BFNT Version 1
   *============================================================================*/

 /**
  Font header
  */
#define BS_BFNT_MAGIC_OFFSET              0 // U32
#define BS_BFNT_VERSION_OFFSET            4 // U32
#define BS_BFNT_1_BLOCKS_COUNT_OFFSET     8 // U16
#define BS_BFNT_1_RESERVED_0             10 // U16
#define BS_BFNT_1_RESERVED_1             12 // U32

 /**
  Mapping all 355 codepoint blocks found in Unicode 18.0.0 to an 
  index pointing to an element in the font specific codepoints
  */
#define BS_BFNT_1_BLOCK_LOOKUP_OFFSET    16
#define BS_BFNT_1_BLOCK_LOOKUP_LENGTH   355 // 355 * U16

#define BS_BFNT_1_HEADER_SIZE (BS_BFNT_1_BLOCK_LOOKUP_OFFSET + BS_BFNT_1_BLOCK_LOOKUP_LENGTH)

 /**
  Font specific codepoint ranges
  */
#define BS_BFNT_1_BLOCKS_OFFSET         BS_BFNT_1_HEADER_SIZE
#define BS_BFNT_1_BLOCK_START_OFFSET     0 // U32
#define BS_BFNT_1_BLOCK_LENGTH_OFFSET    4 // U16
#define BS_BFNT_1_BLOCK_SIZE_OFFSET      6 // U16
#define BS_BFNT_1_BLOCK_ATLAS_OFFSET     8 // U32 - Value is 0 if no atlas is available

#define BS_BFNT_1_BLOCK_SIZE             12


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

#endif 