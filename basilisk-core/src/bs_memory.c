
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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <threads.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <shlobj_core.h>
#else
#include <unistd.h>
#endif

#include <basilisk-core.h>
#include <bs_internal.h>
#include <vulkan.h>



  /*==============================================================================
   * System
   *============================================================================*/

#ifdef _WIN32
#define BS_POPEN  _popen
#define BS_PCLOSE _pclose
#else
#define BS_POPEN  popen
#define BS_PCLOSE pclose
#endif

BSAPI void _bs_system(char* command, int command_length) {
    char output[512];

    FILE* fp = BS_POPEN(command, "r");
    if (!fp) {
        _bs_warnF("Failed to run script");
        return;
    }

    while (fgets(output, sizeof(output), fp)) {
        _bs_infoF("%s", output);
    }

    BS_PCLOSE(fp);
    free(command);
}



  /*==============================================================================
   * Threads
   *============================================================================*/

BSAPI void _bs_createThread(bs_ThreadFunction function, void* param) {
    thrd_t thread;

    if (thrd_create(&thread, function, param) == thrd_success)
        thrd_detach(thread);
}



  /*==============================================================================
   * Cross-Platform/Wrapper C Standard Functions
   *============================================================================*/

BSAPI bs_U32 _bs_alignUp(bs_U32 value, bs_U32 alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

BSAPI char* _bs_strsep(char** stringp, const char* delim) {
#ifdef _WIN32
    if (*stringp == NULL) { return NULL; }
    char* token_start = *stringp;
    *stringp = strpbrk(token_start, delim);
    if (*stringp) {
        **stringp = '\0';
        (*stringp)++;
    }
    return token_start;
#else
    return strsep(stringp, delim);
#endif
}

BSAPI size_t _bs_strnlen(const char* src, size_t n) {
    size_t len = 0;
    while (len < n && src[len])
        len++;
    return len;
}

BSAPI char* _bs_strndup(const char* s, size_t n) {
    size_t len = _bs_strnlen(s, n);
    char* p = malloc(len + 1);
    if (p) {
        memcpy(p, s, len);
        p[len] = '\0';
    }
    return p;
}

BSAPI void* _bs_memmem(
    const void* haystack, bs_U32 haystack_len,
    const void* const needle, const bs_U32 needle_len) 
{
    for (const char *h = haystack; haystack_len >= needle_len;
       ++h, --haystack_len) 
    {
        if (memcmp(h, needle, needle_len) == 0) 
            return (void *)h;
    }

    return NULL;
}

BSAPI void* _bs_free(void* p) {
    free(p);
    return NULL;
}

/**
 if BSX_FAILED_TO_ALLOCATE occurs and we don't have cmd_log=true it'll try to allocate again which might fail
 _bs_infoF uses the C lib's realloc so it won't be an infinite loop or anything
 dunno if i care thoughh :|

 ... wait so what was the problem again? am i retarded?
 */

 /**
  malloc
  */
BSAPI void* _val_bs_malloc(bs_U64 size) {
    BS_VALIDATE(size != 0, NULL,);
    return _bs_malloc(size);
}

BSAPI void* _bs_malloc(bs_U64 size) {
    assert(size != 0);
    void* p = malloc(size);

    if (!p) {
        _bs_criticalF("malloc(%lld) returned NULL", size);
        return NULL;
    }

    return p;
}

 /**
  calloc
  */
BSAPI void* _val_bs_calloc(bs_U64 num_units, bs_U64 unit_size) {
    BS_VALIDATE(num_units > 0, NULL,);
    BS_VALIDATE(unit_size > 0, NULL,);

    return _bs_calloc(num_units, unit_size);
}

BSAPI void* _bs_calloc(bs_U64 num_units, bs_U64 unit_size) {
    assert((num_units * unit_size) != 0);
    void* p = calloc(num_units, unit_size);

    if (!p) {
        _bs_criticalF("calloc(%lld, %lld) returned NULL", num_units, unit_size);
        return NULL;
    }

    return p;
}

/**
 realloc
 */
BSAPI void* _val_bs_realloc(void* p, bs_U64 size) {
    BS_VALIDATE(size != 0, NULL, );
    return _bs_realloc(p, size);
}

BSAPI void* _bs_realloc(void* p, bs_U64 size) {
    assert(size != 0);
    p = realloc(p, size);

    if (!p) {
        _bs_warnF("realloc(%lld) returned NULL", size);
        return NULL;
    }

    return p;
}

BSAPI void* _bs_fetchUnit(bs_List* list, bs_U32 offset) {
    return ((bs_U8*)list->data) + offset * list->unit_size;
}



  /*==============================================================================
   * Strings
   *============================================================================*/

#define BS_STRING_OVERHEAD (128)

BSAPI char* _bs_charStringV(const char* format, va_list args) {
    int len = vsnprintf(NULL, 0, format, args);
    if (len < 0) {
        BS_WARN_ERRNO_PATH("vsnprintf", format);
        return NULL;
    }

    char* buffer = _bs_malloc(len + 1);
    vsnprintf(buffer, len + 1, format, args);
    return buffer;
}

BSAPI int _bs_formatStringLength(const char* format, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);
    assert(len >= 0);
    return len;
}

BSAPI const char* _bs_checkStringPool(bs_List* pool, char* string) {
    bs_U64 hash = _bs_stringHash(string);

    for (int i = 0; i < pool->count; i++) {
        bs_StringPoolEntry* entry = _bs_fetchUnit(pool, i);
        if (hash == entry->hash)
            return entry->string;
    }

    bs_StringPoolEntry* entry = _bs_pushBack(pool, NULL);
    entry->hash = hash;
    entry->string = strdup(string);

    return entry->string;
}

BSAPI bs_String* _bs_stringAlloc(bs_String* old, int len) {
    bs_String* data;

    if (old) {
        if (old->capacity < len)
            data = _bs_realloc(old, sizeof(bs_String) + len + 1);
        else {
            len = old->capacity;
            data = old;
        }
    }
    else 
        data = _bs_malloc(sizeof(bs_String) + len + 1);

    memset(data, 0, sizeof(bs_String));
    data->capacity = len;
    data->value[0] = '\0';
    return data;
}

BSAPI bs_String* _bs_string(bs_String* old, char* str, int len) {
    if (len < 0)
        len = strlen(str);
    bs_String* data = _bs_stringAlloc(old, len);
    if (str)
        memcpy(data->value, str, len);
    data->value[len] = '\0';
    data->len = len;
    return data;
}

BSAPI bs_String* _bs_emptyString(bs_String* old) {
    return _bs_string(old, "", 0);
}

BSAPI void _bs_shortenString(bs_String* string, int len) {
    string->len -= len;
    string->value[string->len] = '\0';
}

BSAPI bs_String* _bs_appendString(bs_String* string, char* append, int len) {
    if (!string)
        string = _bs_stringAlloc(NULL, len + BS_STRING_OVERHEAD);
    else if ((string->capacity - string->len) < len + 1) {
        string->capacity = string->len + len + BS_STRING_OVERHEAD;
        string = _bs_realloc(string, sizeof(bs_String) + string->capacity + 1);
    }
    strncat(string->value, append, len);
    string->len += len;

    return string;
}

BSAPI bs_String* _bs_appendChar(bs_String* string, char c) {
    if (!string)
        string = _bs_stringAlloc(NULL, BS_STRING_OVERHEAD);
    else if ((string->capacity - string->len) < 1) {
        string->capacity += BS_STRING_OVERHEAD;
        string = _bs_realloc(string, sizeof(bs_String) + string->capacity + 1);
    }

    string->value[string->len++] = c;
    string->value[string->len] = '\0';
    return string;
}

 /**
  Remove last N chars
  */
BSAPI void _val_bs_removeLastNChars(bs_String* string, int n) {
    BS_VALIDATE(string->len >= n,,);
}

BSAPI void _bs_removeLastNChars(bs_String* string, int n) {
    string->len -= n;
    string->value[string->len] = '\0';
}

 /**
  Remove char range
  */
BSAPI void _val_bs_removeCharRange(bs_String* string, int start, int count) {
    BS_VALIDATE(start >= 0,,);
    BS_VALIDATE(count >= 0,,);
    BS_VALIDATE(start < string->len,,);

    _bs_removeCharRange(string, start, count);
}

BSAPI void _bs_removeCharRange(bs_String* string, int start, int count) {
    if (start + count > string->len)
        count = string->len - start;

    memmove(
        string->value + start,
        string->value + start + count,
        string->len - (start + count) + 1);

    string->len -= count;
}

 /**
  Insert char
  */
BSAPI bs_String* _val_bs_insertChar(bs_String* string, int index, char c) {
    BS_VALIDATE(index >= 0, NULL,,);
    BS_VALIDATE(index <= string->len, NULL,,);

    return _bs_insertChar(string, index, c);
}

BSAPI bs_String* _bs_insertChar(bs_String* string, int index, char c) {
    if (!string)
        string = _bs_stringAlloc(NULL, BS_STRING_OVERHEAD);

    if ((string->capacity - string->len) < 1) {
        string->capacity += BS_STRING_OVERHEAD;
        string = _bs_realloc(string, sizeof(bs_String) + string->capacity + 1);
    }

    memmove(
        string->value + index + 1,
        string->value + index,
        string->len - index + 1
    );

    string->value[index] = c;
    string->len++;

    return string;
}

BSAPI bs_String* _bs_appendPath(bs_String* string, char* path, int path_len) {
    if (path_len == 0 || string->value[string->len - 1] != '/')
        string = _bs_appendChar(string, '/');
    return _bs_appendString(string, path, path_len);
}

BSAPI void _bs_replaceCharOccurrences(char* string, int string_len, char a, char b) {
    for (int i = 0; i < string_len; i++) {
        if (string[i] == a) 
            string[i] = b;
    }
}

 /**
  To lowercase
  */
BSAPI void _val_bs_toLower(char* string, int len) {
    BS_VALIDATE(len >= 0,,);
    _bs_toLower(string, len);
}

BSAPI void _bs_toLower(char* string, int len) {
    for (int i = 0; i < len; i++)
        string[i] = (char)tolower((unsigned char)string[i]);
}

 /**
  To uppercase
  */
BSAPI void _val_bs_toUpper(char* string, int len) {
    BS_VALIDATE(len >= 0,,);
    _bs_toUpper(string, len);
}

BSAPI void _bs_toUpper(char* string, int len) {
    for (int i = 0; i < len; i++)
        string[i] = (char)toupper((unsigned char)string[i]);
}

 /**
  Hashing
  */
BSAPI bs_U64 _bs_hash(unsigned char* data, size_t size) {
    bs_U64 hash = 0xcbf29ce484222325;

    for (int i = 0; i < size; i++) {
        hash ^= data[i];
        hash *= 0x100000001b3;
    }

    return hash;
}

BSAPI bs_U64 _bs_stringHash(char* string) {
    bs_U64 hash = 0xcbf29ce484222325;

    for (int i = 0; i < strlen(string); i++) {
        hash ^= ((unsigned char*)string)[i];
        hash *= 0x100000001b3;
    }

    return hash;
}

BSAPI bool _bs_startsWith(char* string, const char* prefix) {
    while (*prefix && *string == *prefix) ++string, ++prefix;
    return *prefix == 0;
}

BSAPI bool _bs_endsWith(char* string, const char* suffix) {
    size_t string_len = strlen(string);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > string_len)
        return false;

    return strncmp(string + string_len - suffix_len, suffix, suffix_len) == 0;
}

BSAPI char _val_bs_lastChar(char* string, int len) {
    BS_VALIDATE(len > 0, '\0',,);
    return _bs_lastChar(string, len);
}

BSAPI char _bs_lastChar(char* string, int len) {
    return string[len - 1];
}

BSAPI bool _bs_stringContainsChar(char* string, char c) {
    return strchr(string, c);
}

 /**
  Wide strings
  */
#ifdef _WIN32
BSAPI bs_Result _bs_widen(char* src, wchar_t* dst, bs_U32 dst_size) {
    int result = MultiByteToWideChar(CP_UTF8, 0, src, -1, dst, dst_size);
    if (result == 0) {
        BS_WARN_WIN32_PATH("MultiByteToWideChar", src);
        return _bs_convertWin32Error(GetLastError());
    }

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_unwiden(wchar_t* src, char* dst, bs_U32 dst_size) {
    int result = WideCharToMultiByte(CP_UTF8, 0, src, -1, dst, dst_size, NULL, NULL);
    if (result == 0) {
        BS_WARN_WIN32_PATH("WideCharToMultiByte", src);
        return _bs_convertWin32Error(GetLastError());
    }

    return BS_RESULT_OK;
}
#endif



  /*==============================================================================
   * List
   *============================================================================*/

BSAPI bool _bs_listContains(bs_List* list, void* data) {
    for (int i = 0; i < list->count; i++) {
        void* compare = _bs_fetchUnit(list, i);

        if (memcmp(compare, data, list->unit_size) == 0)
            return true;
    }

    return false;
}

BSAPI void* _val_bs_fetchUnit(bs_List* list, bs_U32 offset) {
    BS_VALIDATE(list->data != NULL, NULL,);
    BS_VALIDATE(offset < list->count, NULL, );

    return _bs_fetchUnit(list, offset);
}

BSAPI void _val_bs_seekList(bs_List* list, bs_U32 offset) {
    BS_VALIDATE(list->data != NULL,,);
    BS_VALIDATE(offset < list->capacity,,);

    _bs_seekList(list, offset);
}

BSAPI void _bs_seekList(bs_List* list, bs_U32 offset) {
    list->count = 0;
}

BSAPI void* _val_bs_fetchLast(bs_List* list) {
    BS_VALIDATE(list->count > 0, NULL, );
    return _bs_fetchLast(list);
}

BSAPI void* _bs_fetchLast(bs_List* list) {
    return _bs_fetchUnit(list, list->count - 1);
}

BSAPI void _bs_ensureSize(bs_List* list, bs_U32 num_units) {
    if ((list->count + num_units) < list->capacity)
        return;

    bs_U32 prev_capacity = list->capacity;
    list->capacity += BS_MAX(num_units, list->increment);
    list->data = _bs_realloc(list->data, list->capacity * list->unit_size);

    bs_U32 size = (list->capacity - prev_capacity) * list->unit_size;

    void* unit = _bs_fetchUnit(list, prev_capacity);
    if (unit)
        memset(unit, 0, size);
}

BSAPI void* _bs_pushBackUnsafe(bs_List* list, char* data) {
    bs_U8* dest = _bs_fetchUnit(list, list->count);
    memcpy(dest, data, list->unit_size);
    list->count++;
    return dest;
}

BSAPI void* _bs_pushBack(bs_List* list, char* data) {
    _bs_ensureSize(list, 1);

    char* dest = _bs_fetchUnit(list, list->count);
    if (data)
        memcpy(dest, data, list->unit_size);
    else memset(dest, 0, list->unit_size);

    list->count++;
    return dest;
}

BSAPI void* _val_bs_pushBackList(bs_List* source, bs_List* destination) {
    BS_VALIDATE(source->unit_size == destination->unit_size, NULL,);

    return _bs_pushBackList(source, destination);
}

BSAPI void* _bs_pushBackList(bs_List* source, bs_List* destination) {
    _bs_ensureSize(destination, source->count);

    bs_U8* dest = _bs_fetchUnit(destination, destination->count);
    for (int i = 0; i < source->count; i++) {
        void* data = _bs_fetchUnit(source, i);
        memcpy(dest + i * destination->unit_size, data, destination->unit_size);
    }

    destination->count += source->count;
    return dest;
}

BSAPI void _val_bs_erase(bs_List* list, int index, bs_U32 count) {
    BS_VALIDATE((index + count - 1) < list->count,, );

    _bs_erase(list, index, count);
}

BSAPI void _bs_erase(bs_List* list, int index, bs_U32 count) {
    for (int i = index; i < (list->count - 1); i++) {
        unsigned char* this = list->data + i * list->unit_size;
        unsigned char* next = this + count * list->unit_size;

        memcpy(this, next, list->unit_size);
    }

    list->count -= count;
}

BSAPI void _bs_destroyList(bs_List* list) {
    _bs_free(list->data);
    list->capacity = 0;
    list->data = NULL;
}

BSAPI void _bs_minimizeList(bs_List* list) {
    bs_U64 smallest = (list->count * list->unit_size);
    if (smallest < list->capacity) {
        list->data = _bs_realloc(list->data, smallest);
        list->capacity = smallest;
    }
}

BSAPI bs_List _bs_list(int unit_size, int increment) {
    return (bs_List) {
        .unit_size = unit_size,
        .increment = increment,
    };
}



  /*==============================================================================
   * File I/O
   *============================================================================*/

    /**
     Iterate documents
     */
#ifdef _WIN32
static inline bs_Result _bs_iterateDocuments(int is_file, bs_ForeachDocumentFunction x, void* param, const char* directory, int directory_length) {
    bs_Result result = BS_RESULT_OK;

    char path[MAX_PATH]; // TODO: is this fine
    path[0] = '\0';

    strncat(path, directory, directory_length);
    if (directory[directory_length - 1] == '/') {
        strncat(path, "*", 1);
    }
    else {
        directory_length++;
        strncat(path, "/*", 2);
    }

    WIN32_FIND_DATA file_data;
    HANDLE handle = FindFirstFile(path, &file_data);
    if (handle == INVALID_HANDLE_VALUE) {
        BS_WARN_WIN32_PATH("FindFirstFile", directory);
        return _bs_convertWin32Error(GetLastError());
    }

    do {
        if (is_file ? 
            !(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) : 
            (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
        {
            if (file_data.cFileName[0] == '.') continue;
            strcpy(path + directory_length, file_data.cFileName);

            result = x((bs_FileInfo) {
                .path = path,
                .size = ((size_t)file_data.nFileSizeHigh << 32) | file_data.nFileSizeLow,
            }, param);

            if (result != BS_RESULT_OK)
                goto end;
        }
    } while (FindNextFile(handle, &file_data));

end:
    FindClose(handle);

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_foreachFile(bs_ForeachDocumentFunction x, void* param, char* directory, int directory_length) {
    return _bs_iterateDocuments(true, x, param, directory, directory_length);
}

BSAPI bs_Result _bs_foreachDirectory(bs_ForeachDocumentFunction x, void* param, char* directory, int directory_length) {
    return _bs_iterateDocuments(false, x, param, directory, directory_length);
}

 /**
  Document counting
  */
static inline bs_Result _bs_increment(bs_FileInfo info, void* i) { 
    (*(int*)i)++; 
    return BS_RESULT_OK; 
}

BSAPI int _bs_numFiles(char* directory, int directory_length) {
    int i = 0;
    _bs_foreachFile(_bs_increment, (void*)&i, directory, directory_length);
    return i;
}

BSAPI int _bs_numDirectories(char* directory, int directory_length) {
    int i = 0;
    _bs_foreachDirectory(_bs_increment, (void*)&i, directory, directory_length);
    return i;
}

#else
BSAPI bs_Result _bs_foreachFile(bs_ForeachDocumentFunction x, const char* directory) { _bs_warnF("_bs_foreachFile not implemented on this platform"); return BS_RESULT_NOT_IMPLEMENTED; }
BSAPI bs_Result _bs_foreachDirectory(bs_ForeachDocumentFunction x, const char* directory) { _bs_warnF("_bs_foreachDirectory not implemented on this platform"); return BS_RESULT_NOT_IMPLEMENTED; }
#endif

   /**
    Document information
    */

BSAPI char* _bs_fileName(const char* path) {
    char* slash = strrchr(path, '/');
    if (!slash || slash == path) {
        return path;
    }
    return slash + 1;
}

BSAPI char* _bs_fileExtension(const char* path) {
    char* dot = strrchr(path, '.');
    if (!dot || dot == path || dot[1] == '/' || dot[1] == '\\') {
        _bs_warnF("%s: Path \"%s\" does not have a file extension", __func__, path);
        return NULL;
    }
    return dot + 1;
}

BSAPI bool _bs_fileExtensionIs(const char* path, char* extension) {
    char* actual = _bs_fileExtension(path);
    return strcmp(actual, extension) == 0;
}

#ifdef _WIN32
static inline bs_DateTime _bs_fromSystemTime(SYSTEMTIME system_time) {
    return (bs_DateTime) {
        .years          = system_time.wYear,
        .months         = system_time.wMonth,
        .days           = system_time.wDay,
        .hours          = system_time.wHour,
        .minutes        = system_time.wMinute,
        .seconds        = system_time.wSecond,
        .milliseconds   = system_time.wMilliseconds,
    };
}

static inline SYSTEMTIME _bs_toSystemTime(bs_DateTime* date_time) {
    return (SYSTEMTIME) {
        .wYear          = date_time->years,
        .wMonth         = date_time->months,
        .wDay           = date_time->days,
        .wHour          = date_time->hours,
        .wMinute        = date_time->minutes,
        .wSecond        = date_time->seconds,
        .wMilliseconds  = date_time->milliseconds,
    };
}
#endif

static inline bs_DateTime _bs_fromUnixTime(time_t unix_time) {
    struct tm tm;

#ifdef _WIN32
    gmtime_s(&tm, &unix_time);
#else
    gmtime_r(&unix_time, &tm);
#endif

    return (bs_DateTime) {
        .years          = (unsigned int)(tm.tm_year + 1900),
        .months         = (unsigned int)(tm.tm_mon + 1),
        .days           = (unsigned int)tm.tm_mday,
        .hours          = (unsigned int)tm.tm_hour,
        .minutes        = (unsigned int)tm.tm_min,
        .seconds        = (unsigned int)tm.tm_sec,
        .milliseconds   = 0,
        .day_of_week    = (unsigned int)tm.tm_wday,
    };
}

static inline time_t _bs_toUnixTime(const bs_DateTime *date_time) {
    struct tm tm = {
        .tm_year        = (int)date_time->years - 1900,
        .tm_mon         = (int)date_time->months - 1,
        .tm_mday        = (int)date_time->days,
        .tm_hour        = (int)date_time->hours,
        .tm_min         = (int)date_time->minutes,
        .tm_sec         = (int)date_time->seconds,
        .tm_isdst       = 0,
    };

#ifdef _WIN32
    return _mkgmtime(&tm);
#else
    return timegm(&tm);
#endif
}

BSAPI bs_Result _bs_fileModifiedDate(bs_DateTime* out, char* path, int path_length) {
#ifdef _WIN32
    HANDLE file = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    FILETIME modified;

    if (file == INVALID_HANDLE_VALUE) {
        BS_WARN_WIN32_PATH("CreateFile", path);
        return _bs_convertWin32Error(GetLastError());
    }

    if (!GetFileTime(file, NULL, NULL, &modified)) {
        BS_WARN_WIN32_PATH("GetFileTime", path);
        return _bs_convertWin32Error(GetLastError());
    }

    CloseHandle(file);

    SYSTEMTIME system_time = { 0 };
    FileTimeToSystemTime(&modified, &system_time);

    *out = _bs_fromSystemTime(system_time);

    return BS_RESULT_OK;
#else
    struct stat st;

    if (stat(path, &st) != 0) {
        BS_WARN_ERRNO_PATH("stat", path);
        return _bs_convertErrno(errno);
    }

    *out = _bs_fromUnixTime(st.st_mtime);

    return BS_RESULT_OK;
#endif
}

BSAPI bs_Result _bs_setFileModifiedDate(bs_DateTime* date, char* path, int path_length) {
#ifdef _WIN32
    HANDLE file = CreateFile(
        path,
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (file == INVALID_HANDLE_VALUE) {
        BS_WARN_WIN32_PATH("CreateFile", path);
        return _bs_convertWin32Error(GetLastError());
    }

    SYSTEMTIME system_time = _bs_toSystemTime(date);
    FILETIME file_time;

    if (!SystemTimeToFileTime(&system_time, &file_time)) {
        BS_WARN_WIN32_PATH("SystemTimeToFileTime", path);
        CloseHandle(file);
        return _bs_convertWin32Error(GetLastError());
    }

    if (!SetFileTime(file, NULL, NULL, &file_time)) {
        BS_WARN_WIN32_PATH("SetFileTime", path);
        CloseHandle(file);
        return _bs_convertWin32Error(GetLastError());
    }

    CloseHandle(file);
    return BS_RESULT_OK;
#else
    struct stat st;

    if (stat(path, &st) != 0) {
        BS_WARN_ERRNO_PATH("stat", path);
        return _bs_convertErrno();
    }

    struct timespec times[2];

    times[0] = st.st_atim;

    times[1].tv_sec = _bs_toUnixTime(date);
    times[1].tv_nsec = 0;

    if (utimensat(AT_FDCWD, path, times, 0) != 0) {
        BS_WARN_ERRNO_PATH("utimensat", path);
        return _bs_convertErrno();
    }

    return BS_RESULT_OK;
#endif
}

BSAPI bool _bs_fileExists(char* path, int path_length) {
#ifdef _WIN32
    return _access(path, 0) == 0;
#else
    return access(path, 0) == 0;
#endif
}

BSAPI bs_String* _bs_executablePath() { return _bs_io_.executable; }
BSAPI void _bs_findRelativePath();
BSAPI bs_String* _bs_workingDirectory() {
    if (!_bs_io_.cwd) _bs_findRelativePath();
    return _bs_io_.cwd;
}

BSAPI bs_Result _bs_setWorkingDirectory(char* path, int path_length) {
#ifdef _WIN32
    if (!SetCurrentDirectory(path)) {
        BS_WARN_WIN32_PATH("SetCurrentDirectory", path);
        return _bs_convertWin32Error(GetLastError());
    }
#else
    if (chdir(path) != 0) {
        BS_WARN_ERRNO_PATH("chdir", path);
        return _bs_convertErrno(errno);
    }
#endif

    _bs_findRelativePath();
    return BS_RESULT_OK;
}

   /**
    Loading documents
    */

 /** TODO: More checks needed in here */
static bs_String* _bs_loadFileFromHandle(FILE* file) {
    fseek(file, 0, SEEK_END);
    long len = ftell(file) + 1;
    fseek(file, 0, SEEK_SET);

    bs_String* string = _bs_stringAlloc(NULL, len);
    string->len = len;

    fread(string->value, 1, len, file);
    fclose(file);

    string->value[len - 1] = '\0';
    return string;
}

bs_Result _bs_openFile(const char* path, const char* mode, bs_File* out) {
    FILE* file = fopen(path, mode);
    if (!file) {
        BS_WARN_ERRNO_PATH("fopen", path);
        return _bs_convertErrno();
    }
}

void _bs_closeFile(bs_File* file) {
    fclose(file->handle);
}

BSAPI bs_Result _bs_loadFile(bs_String** out, char* path, int path_length) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        BS_WARN_ERRNO_PATH("fopen", path);
        return _bs_convertErrno();
    }

    *out = _bs_loadFileFromHandle(file);
    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_loadFileChunk(long offset, size_t size, bs_String** out, char* path, int path_length) {
    FILE* file = fopen(path, "rb");

    if (!file) {
        BS_WARN_ERRNO_PATH("fopen", path);
        return _bs_convertErrno();
    }
    
    if (fseek(file, offset, SEEK_SET) != 0) {
        fclose(file);
        return _bs_convertErrno();
    }

    bs_String* buffer = _bs_stringAlloc(NULL, size);

    size_t bytes_read = fread(buffer->value, 1, size, file);
    buffer->len = bytes_read;

    if (bytes_read != size) {
        _bs_warnF("Read %lld/%lld bytes from \"%s\" at offset %lld", bytes_read, size, path, offset);
        return BS_RESULT_FAILED_TO_READ;
    }

    fclose(file);

    *out = buffer;
    return BS_RESULT_OK;
}

   /**
    Deleting documents
    */

BSAPI bs_Result _bs_deleteFile(char* path, int path_length) {
#ifdef _WIN32
    if (!DeleteFileA(path)) {
        BS_WARN_WIN32_PATH("DeleteFileA", path);
        return _bs_convertWin32Error(GetLastError());
    }
#else
    if (unlink(path) != 0) {
        BS_WARN_ERRNO_PATH("unlink", path);
        return _bs_convertErrno(errno);
    }
#endif

    _bs_infoF("Deleted file %s", path);
    return BS_RESULT_OK;
}

static bs_Result _bs_doDeleteFile(bs_FileInfo file_info, int* path_length) {
    _bs_deleteFile(file_info.path, *path_length);
    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_deleteDirectoryContents(char* path, int path_length) {
#ifdef _WIN32
    return _bs_foreachFile(_bs_doDeleteFile, &path_length, path, path_length);
#else
#endif
}

BSAPI bs_Result _bs_deleteDirectory(char* path, int path_length) {
    bs_Result result = _bs_deleteDirectoryContents(path, path_length);
    if (result != BS_RESULT_OK) {
        return result;
    }

#ifdef _WIN32
    if (!RemoveDirectoryA(path)) {
        BS_WARN_WIN32_PATH("RemoveDirectoryA", path);
        return _bs_convertWin32Error(GetLastError());
    }
#else
    if (rmdir(path) != 0) {
        BS_WARN_ERRNO_PATH("rmdir", path);
        return _bs_convertErrno(errno);
    }
#endif

    return BS_RESULT_OK;
}

BSAPI bool _bs_directoryExists(char* path, int path_length) {
#ifdef _WIN32
    DWORD attrs = GetFileAttributesA(path);
    return attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

   /**
    Saving documents
    */

static inline bs_Result _bs_writeFile(const char* mode, char* data, bs_U32 data_len, char* path, int path_length) {
    FILE* file = fopen(path, mode);
    if (!file) {
        BS_WARN_ERRNO_PATH("fopen", path);
        return _bs_convertErrno();
    }

    if (data)
        fwrite(data, data_len, 1, file);
    fclose(file);

    _bs_infoF("Saved %d bytes to %s", data_len, path);
    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_appendFile(char* data, bs_U32 data_length, char* path, int path_length) {
    return _bs_writeFile("ab", data, data_length, path, path_length);
}

BSAPI bs_Result _bs_saveFile(char* data, bs_U32 data_length, char* path, int path_length) {
    return _bs_writeFile("wb", data, data_length, path, path_length);
}

BSAPI bs_String* _bs_fullPath(bs_String* old, const char* path, int path_len) {
    bs_String* cwd = _bs_workingDirectory();
    bs_String* relative_path = _bs_stringAlloc(old, path_len + cwd->len);
    relative_path = _bs_appendString(relative_path, cwd->value, cwd->len);
    relative_path = _bs_appendPath(relative_path, path, path_len);
    return relative_path;
}



  /*==============================================================================
   * GUID
   *============================================================================*/

BSAPI void _bs_guidToString(bs_GUID* guid, char out[37]) {
#ifdef _WIN32
    OLECHAR str[39] = { 0 };
    int len = StringFromGUID2(guid, str, 39);

    for (int i = 1; i < len - 2; i++)
        out[i - 1] = str[i];
    out[36] = '\0';
#else
    uuid_unparse_lower(guid, out);
#endif
}

BSAPI bs_GUID _bs_stringToGuid(const char* string) {
    bs_GUID guid;

#ifdef _WIN32

    wchar_t wstr[39];
    wchar_t formatted[39];

    mbstowcs(wstr, string, 37);
    swprintf(formatted, 39, L"{%s}", wstr);

    HRESULT hr = CLSIDFromString(formatted, &guid);
    if (FAILED(hr)) {
        _bs_warnF("CLSIDFromString failed for string \"%s\" (HRESULT %lx)", string, hr);
        return (bs_GUID) { 0 };
    }
#else
    if (uuid_parse(str, &guid) != 0) {
        _bs_warnF("uuid_parse failed for string \"%s\"", string);
        return (bs_GUID) { 0 };
    }
#endif

    return guid;
}

BSAPI bs_GUID _bs_guid() {
    bs_GUID guid;

#ifdef _WIN32
    HRESULT hr = CoCreateGuid(&guid);
    if (FAILED(hr)) {
        _bs_warnF("CoCreateGuid failed (HRESULT %lx)", hr);
        return (bs_GUID) { 0 };
    }
#else
    uuid_generate(&guid);
#endif

    return guid;
}

BSAPI bool _bs_guidIsNull(bs_GUID* guid) {
    bs_GUID empty = { 0 };
    return guid->a == 0 && guid->b == 0;
}

BSAPI bool _bs_sameGuid(bs_GUID* a, bs_GUID* b) {
    return a->a == b->a && a->b == b->b;
}



  /*==============================================================================
   * 
   *============================================================================*/

BSAPI int _bs_numDigits(int n) {
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

BSAPI bs_I64 _bs_toLong(const char* str) {
    char* o = NULL;
    bs_I64 v = strtol(str, &o, 10);

    if (str == o) {
        BS_WARN_ERRNO_PATH("strtol", str);
        return BS_I64_MAX;
    }

    return v;
}

BSAPI bs_U64 _bs_toULong(const char* str) {
    char* o = NULL;
    bs_I64 v = strtol(str, &o, 10);

    if (v < 0) {
        _bs_warnF("Expected unsigned value for \"%s\"", str);
        return BS_U64_MAX;
    }

    if (str == o) {
        BS_WARN_ERRNO_PATH("strtol", str);
        return BS_U64_MAX;
    }

    return v;
}

BSAPI bs_F64 _bs_toDouble(const char *str) {
    char* o = NULL;
    bs_F64 v = strtod(str, &o);

    if (str == o) {
        BS_WARN_ERRNO_PATH("strtod", str);
        return 0.0; // TODO
    }

    return v;
}



  /*==============================================================================
   * Windows Specific
   *============================================================================*/

#ifdef _WIN32

BSAPI void _bs_convertWin32Path(char* path, int len) {
    for (int i = 0; i < len; i++)
        path[i] = path[i] == '/' ? '\\' : path[i];
}

// todo document that this will alter the path from / to \\ for win32
// todo document limits
BSAPI bs_Result _bs_ensureDirectory(char* path, int path_length) {
    _bs_convertWin32Path(path, path_length);
    DWORD file_attributes = GetFileAttributes(path);

    if (file_attributes == INVALID_FILE_ATTRIBUTES) {
        char* last = strrchr(path, '\\');

        if (last && last[1] != '\0') {
            last[0] = '\0';
            bs_Result result = _bs_ensureDirectory(path, strlen(path));
            last[0] = '\\';

            if (result != BS_RESULT_OK)
                return result;
        }

        if (strrchr(path, '.')) // skip files
            return BS_RESULT_OK;

        if (!CreateDirectoryA(path, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            BS_WARN_WIN32_PATH("CreateDirectoryA", path);
            return _bs_convertWin32Error(GetLastError());
        }
    }
    else {
        bool is_directory_or_junction =
            ((file_attributes & FILE_ATTRIBUTE_DIRECTORY)     != 0) ||
            ((file_attributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0);

       // if (!is_directory_or_junction)
       //     _bs_throwLastWin32Error(path);
    }

    return BS_RESULT_OK;
}

BSAPI void _bs_findExecutablePaths() {
    char executable_path[MAX_PATH];
    int len = GetModuleFileName(NULL, executable_path, MAX_PATH);

    _bs_io_.executable = _bs_string(NULL, executable_path, len);
    char* exe_path = _bs_io_.executable->value;

    int i = 0;
    for (; i < len; i++) {
        char v = exe_path[i];
        exe_path[i] = v == '\\' ? '/' : v;
    }

    for (i = len - 1; i >= 0; i--) {
        if (exe_path[i] == '/') {
            if (i != len - 1) exe_path[i + 1] = '\0';
            break;
        }
    }

    len -= len - i - 1;
    _bs_io_.executable->len = len;
    _bs_infoF("Executable path = (\"%s\")", exe_path);
}

BSAPI void _bs_findRelativePath() {
    char path[MAX_PATH]; // todo check if this can be more than max path
    int len = GetCurrentDirectory(MAX_PATH, path);
    if (len == 0) {
        _bs_warnF("_bs_findRelativePath -> GetCurrentDirectory failed with error %lu", GetLastError());
        return;
    }

    _bs_io_.cwd = _bs_string(NULL, path, len);
    for (int i = 0; i < len; i++) {
        char c = _bs_io_.cwd->value[i];
        _bs_io_.cwd->value[i] = c == '\\' ? '/' : c;
    }
}

BSAPI char* _bs_appdataPath() {
    if (_bs_io_.appdata)
        return _bs_io_.appdata->value;

    PWSTR wpath = NULL;
    HRESULT result = SHGetKnownFolderPath(&FOLDERID_RoamingAppData, 0, NULL, &wpath);

    if (result != S_OK) {
        _bs_warnF("_bs_appdataPath -> SHGetKnownFolderPath failed with HRESULT %lx", result);
        return NULL;
    }

    int len = lstrlenW(wpath);
    _bs_io_.appdata = _bs_string(_bs_io_.appdata, NULL, len);
    _bs_unwiden(wpath, _bs_io_.appdata->value, len + 1);
    _bs_io_.appdata->len = len;

    _bs_replaceCharOccurrences(_bs_io_.appdata->value, len, '\\', '/');

    return _bs_io_.appdata->value;
}

#endif _WIN32


  /*==============================================================================
   * Clipboard
   *============================================================================*/

#ifdef _WIN32
BSAPI void _bs_copyToClipboard(char* s, int len) {
    len++;
    HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(mem), s, len);
    GlobalUnlock(mem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, mem);
    CloseClipboard();

    _bs_infoF("Copied %s to the clipboard", s);
}
#else
BSAPI void _bs_copyToClipboard(char* s, int len) {
    _bs_warnF("_bs_copyToClipboard has not been implemented for this OS yet");
}
#endif