
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

#include <basilisk-core.h>
#include <bs_internal.h>

#include <stdarg.h>
#include <stdio.h>
#include <threads.h>
#include <errno.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <DbgHelp.h>
#endif
#include <vulkan.h>


#define BS_SECTION_HEADER_START BS_PRINT_DARK_GREEN "\n\n\n  ==============================================================================\n    "
#define BS_SECTION_HEADER_END "\n  ==============================================================================\n\n" BS_PRINT_RESET
#define BS_SECTION_END BS_PRINT_DARK_GREEN "\n  ==============================================================================\n\n" BS_PRINT_RESET



 /*==============================================================================
  * Logger
  * Taken from https://github.com/harshithsunku/ThreadSafeCLogger
  *============================================================================*/

static FILE* _log_file_ = NULL;
static bs_LogQueueItem _log_queue_[BS_LOG_QUEUE_SIZE];
static int _queue_start_ = 0;
static int _queue_end_ = 0;
static mtx_t _bs_log_mutex_;
static mtx_t _bs_log_file_mutex_;
static cnd_t _bs_log_condition_;

BSAPI void _bs_writeLogFileN(char* message, int message_length) {
    fprintf(_log_file_, "%s\n", message);
}

static int bs_loggerThread(void* args) {
    bool running = true;

    while (1) {
        mtx_lock(&_bs_log_mutex_);

        while (_queue_start_ == _queue_end_ && running) {
            cnd_wait(&_bs_log_condition_, &_bs_log_mutex_);
        }

        if (!running && _queue_start_ == _queue_end_) {
            mtx_unlock(&_bs_log_mutex_);
            break;
        }

        bs_LogQueueItem msg = _log_queue_[_queue_start_];
        _queue_start_ = (_queue_start_ + 1) % BS_LOG_QUEUE_SIZE;

        mtx_unlock(&_bs_log_mutex_);

        mtx_lock(&_bs_log_file_mutex_);

        _bs_callbacks_.log(&msg);
        fflush(_log_file_);

        mtx_unlock(&_bs_log_file_mutex_);
    }

    mtx_unlock(&_bs_log_mutex_);
    return 0;
}

void _bs_iniLogger() {
    if (!_bs_callbacks_.log) {
        printf("[WARNING] No logger callback detected, logs will not be available.");
        return;
    }

    FILE* f = fopen("basilisk.log", "w");
    if (f)
        fclose(f);

    _log_file_ = fopen("basilisk.log", "a");

    mtx_init(&_bs_log_mutex_, mtx_plain);
    mtx_init(&_bs_log_file_mutex_, mtx_plain);
    cnd_init(&_bs_log_condition_);

    _bs_createThread(bs_loggerThread, NULL);
}

BSAPI void _bs_writeLogger(
    bs_Library library,
    bs_MessageLevel level,
    bs_Result result,
    int code,
    const char* function,
    const char* file,
    int line,
    const char* message, ...)
{
    mtx_lock(&_bs_log_mutex_);

    va_list args;
    va_start(args, message);

    _log_queue_[_queue_end_] = (bs_LogQueueItem) {
        .library = library,
        .level = level,
        .result = result,
        .function = function,
        .file = file,
        .line = line,
        .thread_id = thrd_current(),
    };

    vsnprintf(
        _log_queue_[_queue_end_].message,
        BS_MAX_LOG_SIZE,
        message, args);

    va_end(args);

    _queue_end_ = (_queue_end_ + 1) % BS_LOG_QUEUE_SIZE;

    cnd_signal(&_bs_log_condition_);
    mtx_unlock(&_bs_log_mutex_);
}

BSAPI void _bs_logN(char* message, int message_len) {
    _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_INFO, 0, 0, NULL, NULL, 0, "%s", message);
}

void _bs_destroyLogger() {
//    mtx_lock(&log_mutex);
//    //running = 0;
//    cnd_signal(&log_cond);
//    mtx_unlock(&log_mutex);
//
//    pthread_join(log_thread, NULL);
//
//    fclose(log_file);
}




 /*==============================================================================
  * Log Functions
  *============================================================================*/


 /** Log section */
BSAPI void _bs_logSectionN(char* message, int message_len) {
    _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_INFO, 0, 0, NULL, NULL, 0, "%s%s%s", BS_SECTION_HEADER_START, message, BS_SECTION_HEADER_END);
}

 /** Log end of section */
BSAPI void _bs_logEndOfSection() {
    _bs_writeLogger(BS_LIBRARY_BASILISK, BS_MESSAGE_INFO, 0, 0, NULL, NULL, 0, "%s", BS_SECTION_END);
}

 /** Log with timestamp */
BSAPI void _bs_logWithTimestampN(bs_MessageLevel level, char* message, int message_len) {
    bs_DateTime dt = _bs_dateTime();

    _bs_writeLogger(BS_LIBRARY_BASILISK, level, 0, 0, NULL, NULL, 0, "[%02d-%02d-%02d %02d:%02d:%02d %04d] %s",
        dt.years, dt.months, dt.days, dt.hours, dt.minutes, dt.seconds, dt.milliseconds, message);
}

/** Info log */
BSAPI void _bs_infoN(char* message, int message_len) {
    _bs_logWithTimestampN(BS_MESSAGE_INFO, message, message_len);
}

 /** Warning log */
BSAPI void _bs_warnN(char* message, int message_len) {
    _bs_logWithTimestampN(BS_MESSAGE_WARNING, message, message_len);
}

 /** Critical error log */
BSAPI void _bs_criticalN(char* message, int message_len) {
    printf(BS_PRINT_COLOR("[CRITICAL ERROR]", BS_PRINT_RED) "%s", message);

#ifdef _WIN32
    if (_bs_scope_.context && _bs_scope_.context->hwnd) {
        int report_bug = MessageBox(
            _bs_scope_.context->hwnd,
            message,
            _bs_scope_.context->title,
            MB_ICONERROR | MB_OK
        );
    }
#endif

    /*
    if (_bs_args_.send_bugs)
    {
        int report_bug = MessageBox(
            _bs_wnd.hwnd,
            "The application has crashed :(\nWould you like to create a bug report?",
            _bs_wnd.title,
            MB_ICONERROR | MB_YESNO
        );

        if (report_bug == IDYES) {
            _bs_except(BS_U64_MAX);
            bs_Json json = _bs_emptyJson();
            _bs_ensureJson(&json, _bs_jsonValue(_bs_scope_.context->io.log->value), "$.Log");
            char* result = _bs_saveJson(&json, 0);

            bs_Json response = _bs_post("http://basilisk-gfx.com/reportbug", 5000, &json);
            char* raw = _bs_saveJson(&response, BS_JSON_PRETTY);

            printf("Bug report response:\n%s\n", raw);

            _bs_destroyJson(&response);
            _bs_free(raw);
            _bs_except(0);
        }
    }

    if (_bs_wnd.destroy)
        _bs_wnd.destroy();
    */

    exit(0);
}

BSAPI const char* _bs_serializeErrno() {
    switch (errno) {
        case  1: return "Operation not permitted";
        case  2: return "No such file or directory";
        case  3: return "No such process";
        case  4: return "Interrupted system call";
        case  5: return "I/O error";
        case  6: return "No such device or address";
        case  7: return "Argument list too long";
        case  8: return "Exec format error";
        case  9: return "Bad file number";
        case 10: return "No child processes";
        case 11: return "Try again";
        case 12: return "Out of memory";
        case 13: return "Permission denied";
        case 14: return "Bad address";
        case 15: return "Block device required";
        case 16: return "Device or resource busy";
        case 17: return "File exists";
        case 18: return "Cross-device link";
        case 19: return "No such device";
        case 20: return "Not a directory";
        case 21: return "Is a directory";
        case 22: return "Invalid argument";
        case 23: return "File table overflow";
        case 24: return "Too many open files";
        case 25: return "Not a typewriter";
        case 26: return "Text file busy";
        case 27: return "File too large";
        case 28: return "No space left on device";
        case 29: return "Illegal seek";
        case 30: return "Read-only file system";
        case 31: return "Too many links";
        case 32: return "Broken pipe";
        case 33: return "Math argument out of domain of func";
        case 34: return "Math result not representable";
    }

    return "Unknown";
}

BSAPI bs_Result _bs_convertVulkanResult(int result) {
    switch (result) {
        case VK_SUCCESS: return BS_RESULT_OK;
    }

    return BS_RESULT_GENERAL_ERROR;
}

BSAPI bs_Result _bs_convertYyjsonResult(int result) {
    switch (result) {
    case 0: return BS_RESULT_OK;
    }

    return BS_RESULT_GENERAL_ERROR;
}

BSAPI bs_Result _bs_convertErrno() {
    switch (errno) {
    }

    return BS_RESULT_GENERAL_ERROR;
}

#ifdef _WIN32
BSAPI bs_Result _bs_convertWin32Error(int code) {
    switch (code) {
        case 0: return BS_RESULT_OK;
    }

    return BS_RESULT_GENERAL_ERROR;
}

BSAPI const char* _bs_serializeWin32Error(int code) {
    switch (code) {
    }

    return "Unknown";
}

BSAPI bs_Result _bs_convertHResult(int code) {
    switch (code) {
        case 0: return BS_RESULT_OK;
    }

    return BS_RESULT_GENERAL_ERROR;
}

#endif
