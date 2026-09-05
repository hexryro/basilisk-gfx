
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
/*
BSMODAPI void _bsmod_saveHistory(bsgfx_TypeId type_id) {
    //    bsgfx_Type* type = bsgfx_types + type_id;
    //    if (!type->count)
    //        return;
    //
    //    char appdata[MAX_PATH];
    //    bs_appdataPath(appdata);
    //
    //    bs_DateTime time = bs_dateTime();
    //    bs_I64 seconds = bs_totalSeconds(&time);
    //
    //    bs_String* name = bs_stringF(NULL, "%s/.voc/history/%s_%ld.bin", appdata, type->plural, seconds); // todo get game name
    //
    //    bs_ensureDirectory(name->value);
    //    bs_saveFile(name->value, type->list, *type->count * type->type_size);
    //
    //    bs_free(name);
}

static void _bsmod_findClosestHistory(bs_FileInfo info, struct { bsgfx_TypeId previous_type, next_type; bs_I64 previous, next; } *params) {
    info.path = bs_fileName(info.path);

    char* date_start = strchr(info.path, '_');
    assert(date_start);
    char* end = strchr(info.path, '.');
    assert(end);

    end[0] = '\0'; // hack to skip alloc
    date_start[0] = '\0';

    bs_I64 time = bs_toLong(date_start + 1);
    bsgfx_TypeId type = _bsmod_queryType(info.path);

    end[0] = '.';
    date_start[0] = '\0';

    if (time != 0) {
        if (time - _bsmod_.history > 0) {
            params->next = BS_MIN(params->next, time);
            params->next_type = type;
        }
        else if (time - _bsmod_.history < 0) {
            params->previous = BS_MAX(params->previous, time);
            params->previous_type = type;
        }
    }
}

BSMODAPI void _bsmod_loadPreviousHistory() {
    char* appdata = bs_appdataPath(appdata);

    struct { bsgfx_TypeId previous_type, next_type; bs_I64 previous, next; } params = {
        .previous = 0,
        .next = 0,
    };

    bs_foreachFileF(
        _bsmod_findClosestHistory,
        &params,
        "%s/.woc/history", // todo get game name
        appdata);

    if (params.previous != 0) {
        if (_bsmod_.history == BS_I64_MAX)
            _bsmod_saveHistory(params.previous_type);

        _bsmod_.history = params.previous;
        //bsmod_queueLoadType(params.previous_type);
    }
}

BSMODAPI void _bsmod_loadNextHistory() {
    if (_bsmod_.history == BS_I64_MAX)
        return;

    char* appdata = bs_appdataPath(appdata);

    struct { bsgfx_TypeId previous_type, next_type; bs_I64 previous, next; } params = {
        .previous = 0,
        .next = BS_I64_MAX,
    };

    bs_foreachFileF(
        _bsmod_findClosestHistory,
        &params,
        "%s/.woc/history", // todo get game name
        appdata);

    if (params.next != BS_I64_MAX) {
        _bsmod_.history = params.next;
        //bsmod_queueLoadType(params.next_type);
    }
}
*/