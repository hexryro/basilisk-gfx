
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

 /**
  This file was generated from basilisk-gfx.com

  It is not recommended to make changes to this file as it will be lost if
  the code is regenerated.
  */

#include <bsmod_internal.h>
#include <stdarg.h>
#include <stdio.h>

bsmod_TextureInfo* _bsmod_packAtlasTexture(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    int id, 
    char* name)
{
    return _bsmod_packAtlasTextureN(packer, data, get_data, param, width, height, category, id, name, strlen(name));
}

bsmod_TextureInfo* _bsmod_packAtlasTextureV(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    int id, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsmod_packAtlasTextureN(packer, data, get_data, param, width, height, category, id, _formatted, _length);
}

bsmod_TextureInfo* _bsmod_packAtlasTextureF(
    bsmod_AtlasPacker* packer, 
    unsigned char* data, 
    PFN_bsmod_getAtlasTextureData get_data, 
    void* param, 
    int width, 
    int height, 
    int category, 
    int id, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bsmod_TextureInfo* _return = _bsmod_packAtlasTextureV(packer, data, get_data, param, width, height, category, id, format, args);
    va_end(args);
    return _return;
}

bs_Result _bsmod_packResource(
    bs_ResourceType type, 
    void* data, 
    size_t data_size, 
    const char* package_name, 
    char* resource_name)
{
    return _bsmod_packResourceN(type, data, data_size, package_name, resource_name, strlen(resource_name));
}

bs_Result _bsmod_packResourceV(
    bs_ResourceType type, 
    void* data, 
    size_t data_size, 
    const char* package_name, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsmod_packResourceN(type, data, data_size, package_name, _formatted, _length);
}

bs_Result _bsmod_packResourceF(
    bs_ResourceType type, 
    void* data, 
    size_t data_size, 
    const char* package_name, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bsmod_packResourceV(type, data, data_size, package_name, format, args);
    va_end(args);
    return _return;
}

bs_Result _bsmod_savePackage(
    char* path)
{
    return _bsmod_savePackageN(path, strlen(path));
}

bs_Result _bsmod_savePackageV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsmod_savePackageN(_formatted, _length);
}

bs_Result _bsmod_savePackageF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bsmod_savePackageV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bsmod_saveType(
    bsgfx_TypeId id, 
    char* value)
{
    return _bsmod_saveTypeN(id, value, strlen(value));
}

bs_Result _bsmod_saveTypeV(
    bsgfx_TypeId id, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsmod_saveTypeN(id, _formatted, _length);
}

bs_Result _bsmod_saveTypeF(
    bsgfx_TypeId id, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bsmod_saveTypeV(id, format, args);
    va_end(args);
    return _return;
}

