
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

void _bs_writeLogFileV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_writeLogFile(_formatted, _length);
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

void _bs_beginCommentV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_beginComment(_formatted, _length);
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

bs_Attribute* _bs_queryAttributeV(
    bs_Batch* batch, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_queryAttribute(batch, _formatted, _length);
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

bs_Result _bs_peekPngV(
    bs_PngData* out_png_data, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_peekPng(out_png_data, _formatted, _length);
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
    return _bs_savePng(data, resolution, type, _formatted, _length);
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
    return _bs_loadImage(object, package_id, flags, _formatted, _length);
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
    return _bs_loadAtlas(object, package_id, flags, _formatted, _length);
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

void _bsi_nameHandleV(
    bs_U64 handle, 
    bs_U32 type, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bsi_nameHandle(handle, type, _formatted, _length);
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

bs_Result _bs_loadJsonV(
    bs_Json* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadJson(out, _formatted, _length);
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

bs_JsonValue _bs_fetchJsonV(
    bs_Json* root, 
    bs_JsonType expect, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_fetchJson(root, expect, _formatted, _length);
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

void _bs_deleteJsonV(
    bs_Json* root, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_deleteJson(root, _formatted, _length);
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

bs_Result _bs_ensureJsonV(
    bs_Json* root, 
    bs_JsonValue value, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_ensureJson(root, value, _formatted, _length);
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

void _bs_logSectionV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_logSection(_formatted, _length);
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

void _bs_logWithTimestampV(
    bs_MessageLevel level, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_logWithTimestamp(level, _formatted, _length);
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

void _bs_logV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_log(_formatted, _length);
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

void _bs_infoV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_info(_formatted, _length);
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

void _bs_warnV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_warn(_formatted, _length);
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

void _bs_criticalV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_critical(_formatted, _length);
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

void _bs_systemV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_system(_formatted, _length);
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

bs_String* _bs_stringV(
    bs_String* old, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_string(old, _formatted, _length);
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

bs_Result _bs_setWorkingDirectoryV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_setWorkingDirectory(_formatted, _length);
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

bool _bs_directoryExistsV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_directoryExists(_formatted, _length);
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

bs_Result _bs_appendFileV(
    char* data, 
    bs_U32 data_len, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_appendFile(data, data_len, _formatted, _length);
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

bs_Result _bs_saveFileV(
    char* data, 
    bs_U32 data_len, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_saveFile(data, data_len, _formatted, _length);
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

void _bs_convertWin32PathV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_convertWin32Path(_formatted, _length);
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

bs_Result _bs_ensureDirectoryV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_ensureDirectory(_formatted, _length);
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

bs_Result _bs_fileModifiedDateV(
    bs_DateTime* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_fileModifiedDate(out, _formatted, _length);
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

bs_Result _bs_setFileModifiedDateV(
    bs_DateTime* date, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_setFileModifiedDate(date, _formatted, _length);
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

bool _bs_fileExistsV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_fileExists(_formatted, _length);
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
    return _bs_loadResource(package_id, flags, out, _formatted, _length);
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

void _bs_titleWindowV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_titleWindow(_formatted, _length);
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

void _bs_copyToClipboardV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    _bs_copyToClipboard(_formatted, _length);
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

bs_String* _bs_appendStringV(
    bs_String* destination, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_appendString(destination, _formatted, _length);
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

bs_Result _bs_foreachFileV(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_foreachFile(x, param, _formatted, _length);
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

bs_Result _bs_foreachDirectoryV(
    bs_ForeachDocumentFunction x, 
    void* param, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_foreachDirectory(x, param, _formatted, _length);
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

int _bs_numFilesV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_numFiles(_formatted, _length);
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

int _bs_numDirectoriesV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_numDirectories(_formatted, _length);
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

bs_Result _bs_openFileV(
    const char* mode, 
    bs_File* out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_openFile(mode, out, _formatted, _length);
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

bs_Result _bs_loadFileV(
    bs_String** out, 
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_loadFile(out, _formatted, _length);
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
    return _bs_loadFileChunk(offset, size, out, _formatted, _length);
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

bs_Result _bs_deleteFileV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_deleteFile(_formatted, _length);
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

bs_Result _bs_deleteDirectoryContentsV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_deleteDirectoryContents(_formatted, _length);
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

bs_Result _bs_deleteDirectoryV(
    char* format, 
    va_list args)
{
    int _length = bs_formatStringLength(format, args);
    char* _formatted = bs_alloca(_length + 1);
    vsnprintf(_formatted, _length + 1, format, args);
    return _bs_deleteDirectory(_formatted, _length);
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

