
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

bs_Result _bsmod_packResourceV(
    bs_ResourceType type, 
    unsigned char* data, 
    size_t data_size, 
    const char* package_name, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsmod_packResource(type, data, data_size, package_name, _formatted, _length);
}

bs_Result _bsmod_packResourceF(
    bs_ResourceType type, 
    unsigned char* data, 
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

bs_Result _bsmod_saveTypeV(
    bsgfx_TypeId id, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsmod_saveType(id, _formatted, _length);
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

