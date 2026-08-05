
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
        
#include <bs_internal.h>
#include <stdio.h>
#include <stdarg.h>

void _bs_writeLogFile(
    char* value)
{
    _bs_writeLogFile(strlen(bs_writeLogFile));
}

void _bs_writeLogFileV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_writeLogFileN(_formatted, _length);
}

void _bs_writeLogFileF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_writeLogFileV(format, args);
    va_end(args);
}

void _bs_beginComment(
    char* value)
{
    _bs_beginComment(strlen(bs_beginComment));
}

void _bs_beginCommentV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_beginCommentN(_formatted, _length);
}

void _bs_beginCommentF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_beginCommentV(format, args);
    va_end(args);
}

bs_Attribute* _bs_queryAttribute(
    bs_Batch* batch, 
    char* name)
{
    return _bs_queryAttribute(batch, strlen(bs_queryAttribute));
}

bs_Attribute* _bs_queryAttributeV(
    bs_Batch* batch, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_queryAttributeN(batch, _formatted, _length);
}

bs_Attribute* _bs_queryAttributeF(
    bs_Batch* batch, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Attribute* _return = _bs_queryAttributeV(batch, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_peekPng(
    bs_PngData* out_png_data, 
    char* path)
{
    return _bs_peekPng(out_png_data, strlen(bs_peekPng));
}

bs_Result _bs_peekPngV(
    bs_PngData* out_png_data, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_peekPngN(out_png_data, _formatted, _length);
}

bs_Result _bs_peekPngF(
    bs_PngData* out_png_data, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_peekPngV(out_png_data, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_savePng(
    char* data, 
    bs_ivec2 resolution, 
    bs_PngType type, 
    char* path)
{
    return _bs_savePng(data, resolution, type, strlen(bs_savePng));
}

bs_Result _bs_savePngV(
    char* data, 
    bs_ivec2 resolution, 
    bs_PngType type, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_savePngN(data, resolution, type, _formatted, _length);
}

bs_Result _bs_savePngF(
    char* data, 
    bs_ivec2 resolution, 
    bs_PngType type, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_savePngV(data, resolution, type, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_loadImage(
    bs_Object* object, 
    int package_id, 
    bs_ImageBits flags, 
    char* path)
{
    return _bs_loadImage(object, package_id, flags, strlen(bs_loadImage));
}

bs_Result _bs_loadImageV(
    bs_Object* object, 
    int package_id, 
    bs_ImageBits flags, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadImageN(object, package_id, flags, _formatted, _length);
}

bs_Result _bs_loadImageF(
    bs_Object* object, 
    int package_id, 
    bs_ImageBits flags, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadImageV(object, package_id, flags, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_loadAtlas(
    bs_Object* object, 
    int package_id, 
    bs_U32 flags, 
    char* path)
{
    return _bs_loadAtlas(object, package_id, flags, strlen(bs_loadAtlas));
}

bs_Result _bs_loadAtlasV(
    bs_Object* object, 
    int package_id, 
    bs_U32 flags, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadAtlasN(object, package_id, flags, _formatted, _length);
}

bs_Result _bs_loadAtlasF(
    bs_Object* object, 
    int package_id, 
    bs_U32 flags, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadAtlasV(object, package_id, flags, format, args);
    va_end(args);
    return _return;
}

void _bsi_nameHandle(
    bs_U64 handle, 
    bs_U32 type, 
    char* value)
{
    _bsi_nameHandle(handle, type, strlen(bsi_nameHandle));
}

void _bsi_nameHandleV(
    bs_U64 handle, 
    bs_U32 type, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bsi_nameHandleN(handle, type, _formatted, _length);
}

void _bsi_nameHandleF(
    bs_U64 handle, 
    bs_U32 type, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bsi_nameHandleV(handle, type, format, args);
    va_end(args);
}

bs_Result _bs_loadJson(
    bs_Json* out, 
    char* path)
{
    return _bs_loadJson(out, strlen(bs_loadJson));
}

bs_Result _bs_loadJsonV(
    bs_Json* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadJsonN(out, _formatted, _length);
}

bs_Result _bs_loadJsonF(
    bs_Json* out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadJsonV(out, format, args);
    va_end(args);
    return _return;
}

bs_JsonValue _bs_fetchJson(
    bs_Json* root, 
    bs_JsonType expect, 
    char* path)
{
    return _bs_fetchJson(root, expect, strlen(bs_fetchJson));
}

bs_JsonValue _bs_fetchJsonV(
    bs_Json* root, 
    bs_JsonType expect, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_fetchJsonN(root, expect, _formatted, _length);
}

bs_JsonValue _bs_fetchJsonF(
    bs_Json* root, 
    bs_JsonType expect, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_JsonValue _return = _bs_fetchJsonV(root, expect, format, args);
    va_end(args);
    return _return;
}

void _bs_deleteJson(
    bs_Json* root, 
    char* path)
{
    _bs_deleteJson(root, strlen(bs_deleteJson));
}

void _bs_deleteJsonV(
    bs_Json* root, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_deleteJsonN(root, _formatted, _length);
}

void _bs_deleteJsonF(
    bs_Json* root, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_deleteJsonV(root, format, args);
    va_end(args);
}

bs_Result _bs_ensureJson(
    bs_Json* root, 
    bs_JsonValue value, 
    char* path)
{
    return _bs_ensureJson(root, value, strlen(bs_ensureJson));
}

bs_Result _bs_ensureJsonV(
    bs_Json* root, 
    bs_JsonValue value, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_ensureJsonN(root, value, _formatted, _length);
}

bs_Result _bs_ensureJsonF(
    bs_Json* root, 
    bs_JsonValue value, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_ensureJsonV(root, value, format, args);
    va_end(args);
    return _return;
}

void _bs_logSection(
    char* value)
{
    _bs_logSection(strlen(bs_logSection));
}

void _bs_logSectionV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_logSectionN(_formatted, _length);
}

void _bs_logSectionF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_logSectionV(format, args);
    va_end(args);
}

void _bs_logWithTimestamp(
    bs_MessageLevel level, 
    char* value)
{
    _bs_logWithTimestamp(level, strlen(bs_logWithTimestamp));
}

void _bs_logWithTimestampV(
    bs_MessageLevel level, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_logWithTimestampN(level, _formatted, _length);
}

void _bs_logWithTimestampF(
    bs_MessageLevel level, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_logWithTimestampV(level, format, args);
    va_end(args);
}

void _bs_log(
    char* message)
{
    _bs_log(strlen(bs_log));
}

void _bs_logV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_logN(_formatted, _length);
}

void _bs_logF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_logV(format, args);
    va_end(args);
}

void _bs_info(
    char* message)
{
    _bs_info(strlen(bs_info));
}

void _bs_infoV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_infoN(_formatted, _length);
}

void _bs_infoF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_infoV(format, args);
    va_end(args);
}

void _bs_warn(
    char* message)
{
    _bs_warn(strlen(bs_warn));
}

void _bs_warnV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_warnN(_formatted, _length);
}

void _bs_warnF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_warnV(format, args);
    va_end(args);
}

void _bs_critical(
    char* message)
{
    _bs_critical(strlen(bs_critical));
}

void _bs_criticalV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_criticalN(_formatted, _length);
}

void _bs_criticalF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_criticalV(format, args);
    va_end(args);
}

void _bs_system(
    char* value)
{
    _bs_system(strlen(bs_system));
}

void _bs_systemV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_systemN(_formatted, _length);
}

void _bs_systemF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_systemV(format, args);
    va_end(args);
}

bs_String* _bs_string(
    bs_String* old, 
    char* value)
{
    return _bs_string(old, strlen(bs_string));
}

bs_String* _bs_stringV(
    bs_String* old, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_stringN(old, _formatted, _length);
}

bs_String* _bs_stringF(
    bs_String* old, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_String* _return = _bs_stringV(old, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_setWorkingDirectory(
    char* path)
{
    return _bs_setWorkingDirectory(strlen(bs_setWorkingDirectory));
}

bs_Result _bs_setWorkingDirectoryV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_setWorkingDirectoryN(_formatted, _length);
}

bs_Result _bs_setWorkingDirectoryF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_setWorkingDirectoryV(format, args);
    va_end(args);
    return _return;
}

char* _bs_charStringF(
    const char* format, 
     ...)
{
    va_list args;
    va_start(args, format);
    char* _return = bs_charStringV(format, args);
    va_end(args);
    return _return;
}

bool _bs_directoryExists(
    char* path)
{
    return _bs_directoryExists(strlen(bs_directoryExists));
}

bool _bs_directoryExistsV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_directoryExistsN(_formatted, _length);
}

bool _bs_directoryExistsF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bool _return = _bs_directoryExistsV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_appendFile(
    char* data, 
    bs_U32 data_len, 
    char* value)
{
    return _bs_appendFile(data, data_len, strlen(bs_appendFile));
}

bs_Result _bs_appendFileV(
    char* data, 
    bs_U32 data_len, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_appendFileN(data, data_len, _formatted, _length);
}

bs_Result _bs_appendFileF(
    char* data, 
    bs_U32 data_len, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_appendFileV(data, data_len, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_saveFile(
    char* data, 
    bs_U32 data_len, 
    char* path)
{
    return _bs_saveFile(data, data_len, strlen(bs_saveFile));
}

bs_Result _bs_saveFileV(
    char* data, 
    bs_U32 data_len, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_saveFileN(data, data_len, _formatted, _length);
}

bs_Result _bs_saveFileF(
    char* data, 
    bs_U32 data_len, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_saveFileV(data, data_len, format, args);
    va_end(args);
    return _return;
}

void _bs_convertWin32Path(
    char* path)
{
    _bs_convertWin32Path(strlen(bs_convertWin32Path));
}

void _bs_convertWin32PathV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_convertWin32PathN(_formatted, _length);
}

void _bs_convertWin32PathF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_convertWin32PathV(format, args);
    va_end(args);
}

bs_Result _bs_ensureDirectory(
    char* path)
{
    return _bs_ensureDirectory(strlen(bs_ensureDirectory));
}

bs_Result _bs_ensureDirectoryV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_ensureDirectoryN(_formatted, _length);
}

bs_Result _bs_ensureDirectoryF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_ensureDirectoryV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_fileModifiedDate(
    bs_DateTime* out, 
    char* path)
{
    return _bs_fileModifiedDate(out, strlen(bs_fileModifiedDate));
}

bs_Result _bs_fileModifiedDateV(
    bs_DateTime* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_fileModifiedDateN(out, _formatted, _length);
}

bs_Result _bs_fileModifiedDateF(
    bs_DateTime* out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_fileModifiedDateV(out, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_setFileModifiedDate(
    bs_DateTime* date, 
    char* path)
{
    return _bs_setFileModifiedDate(date, strlen(bs_setFileModifiedDate));
}

bs_Result _bs_setFileModifiedDateV(
    bs_DateTime* date, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_setFileModifiedDateN(date, _formatted, _length);
}

bs_Result _bs_setFileModifiedDateF(
    bs_DateTime* date, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_setFileModifiedDateV(date, format, args);
    va_end(args);
    return _return;
}

bool _bs_fileExists(
    char* path)
{
    return _bs_fileExists(strlen(bs_fileExists));
}

bool _bs_fileExistsV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_fileExistsN(_formatted, _length);
}

bool _bs_fileExistsF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bool _return = _bs_fileExistsV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_loadResource(
    int package_id, 
    bs_U32 flags, 
    bs_Resource** out, 
    char* value)
{
    return _bs_loadResource(package_id, flags, out, strlen(bs_loadResource));
}

bs_Result _bs_loadResourceV(
    int package_id, 
    bs_U32 flags, 
    bs_Resource** out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadResourceN(package_id, flags, out, _formatted, _length);
}

bs_Result _bs_loadResourceF(
    int package_id, 
    bs_U32 flags, 
    bs_Resource** out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadResourceV(package_id, flags, out, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_loadPackage(
    int* out, 
    char* path)
{
    return _bs_loadPackage(out, strlen(bs_loadPackage));
}

bs_Result _bs_loadPackageV(
    int* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadPackageN(out, _formatted, _length);
}

bs_Result _bs_loadPackageF(
    int* out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadPackageV(out, format, args);
    va_end(args);
    return _return;
}

void _bs_titleWindow(
    char* name)
{
    _bs_titleWindow(strlen(bs_titleWindow));
}

void _bs_titleWindowV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_titleWindowN(_formatted, _length);
}

void _bs_titleWindowF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_titleWindowV(format, args);
    va_end(args);
}

void _bs_copyToClipboard(
    char* value)
{
    _bs_copyToClipboard(strlen(bs_copyToClipboard));
}

void _bs_copyToClipboardV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_copyToClipboardN(_formatted, _length);
}

void _bs_copyToClipboardF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    _bs_copyToClipboardV(format, args);
    va_end(args);
}

bs_String* _bs_appendString(
    bs_String* destination, 
    char* value)
{
    return _bs_appendString(destination, strlen(bs_appendString));
}

bs_String* _bs_appendStringV(
    bs_String* destination, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_appendStringN(destination, _formatted, _length);
}

bs_String* _bs_appendStringF(
    bs_String* destination, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_String* _return = _bs_appendStringV(destination, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_foreachFile(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* value)
{
    return _bs_foreachFile(x, param, strlen(bs_foreachFile));
}

bs_Result _bs_foreachFileV(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_foreachFileN(x, param, _formatted, _length);
}

bs_Result _bs_foreachFileF(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_foreachFileV(x, param, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_foreachDirectory(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* path)
{
    return _bs_foreachDirectory(x, param, strlen(bs_foreachDirectory));
}

bs_Result _bs_foreachDirectoryV(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_foreachDirectoryN(x, param, _formatted, _length);
}

bs_Result _bs_foreachDirectoryF(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_foreachDirectoryV(x, param, format, args);
    va_end(args);
    return _return;
}

int _bs_numFiles(
    char* path)
{
    return _bs_numFiles(strlen(bs_numFiles));
}

int _bs_numFilesV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_numFilesN(_formatted, _length);
}

int _bs_numFilesF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    int _return = _bs_numFilesV(format, args);
    va_end(args);
    return _return;
}

int _bs_numDirectories(
    char* path)
{
    return _bs_numDirectories(strlen(bs_numDirectories));
}

int _bs_numDirectoriesV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_numDirectoriesN(_formatted, _length);
}

int _bs_numDirectoriesF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    int _return = _bs_numDirectoriesV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_openFile(
    const char* mode, 
    bs_File* out, 
    char* path)
{
    return _bs_openFile(mode, out, strlen(bs_openFile));
}

bs_Result _bs_openFileV(
    const char* mode, 
    bs_File* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_openFileN(mode, out, _formatted, _length);
}

bs_Result _bs_openFileF(
    const char* mode, 
    bs_File* out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_openFileV(mode, out, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_loadFile(
    bs_String** out, 
    char* path)
{
    return _bs_loadFile(out, strlen(bs_loadFile));
}

bs_Result _bs_loadFileV(
    bs_String** out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadFileN(out, _formatted, _length);
}

bs_Result _bs_loadFileF(
    bs_String** out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadFileV(out, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_loadFileChunk(
    long offset, 
    size_t size, 
    bs_String** out, 
    char* path)
{
    return _bs_loadFileChunk(offset, size, out, strlen(bs_loadFileChunk));
}

bs_Result _bs_loadFileChunkV(
    long offset, 
    size_t size, 
    bs_String** out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadFileChunkN(offset, size, out, _formatted, _length);
}

bs_Result _bs_loadFileChunkF(
    long offset, 
    size_t size, 
    bs_String** out, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_loadFileChunkV(offset, size, out, format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_deleteFile(
    char* path)
{
    return _bs_deleteFile(strlen(bs_deleteFile));
}

bs_Result _bs_deleteFileV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_deleteFileN(_formatted, _length);
}

bs_Result _bs_deleteFileF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_deleteFileV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_deleteDirectoryContents(
    char* path)
{
    return _bs_deleteDirectoryContents(strlen(bs_deleteDirectoryContents));
}

bs_Result _bs_deleteDirectoryContentsV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_deleteDirectoryContentsN(_formatted, _length);
}

bs_Result _bs_deleteDirectoryContentsF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_deleteDirectoryContentsV(format, args);
    va_end(args);
    return _return;
}

bs_Result _bs_deleteDirectory(
    char* path)
{
    return _bs_deleteDirectory(strlen(bs_deleteDirectory));
}

bs_Result _bs_deleteDirectoryV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_deleteDirectoryN(_formatted, _length);
}

bs_Result _bs_deleteDirectoryF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bs_Result _return = _bs_deleteDirectoryV(format, args);
    va_end(args);
    return _return;
}

