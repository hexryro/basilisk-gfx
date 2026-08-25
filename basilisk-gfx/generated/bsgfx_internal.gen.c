
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
        
#include <bsgfx_internal.h>
#include <stdarg.h>
#include <stdio.h>

bsgfx_Material* _bsgfx_material(
    char* name)
{
    return _bsgfx_materialN(name, strlen(name));
}

bsgfx_Material* _bsgfx_materialV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsgfx_materialN(_formatted, _length);
}

bsgfx_Material* _bsgfx_materialF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bsgfx_Material* _return = _bsgfx_materialV(format, args);
    va_end(args);
    return _return;
}

float _bsgfx_instanceASCIIText(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* text)
{
    return _bsgfx_instanceASCIITextN(subtype, font, position, pt_size, text, strlen(text));
}

float _bsgfx_instanceASCIITextV(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bsgfx_instanceASCIITextN(subtype, font, position, pt_size, _formatted, _length);
}

float _bsgfx_instanceASCIITextF(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    float _return = _bsgfx_instanceASCIITextV(subtype, font, position, pt_size, format, args);
    va_end(args);
    return _return;
}

