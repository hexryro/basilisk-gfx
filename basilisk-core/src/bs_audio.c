
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



  /*==============================================================================
   * Windows Implementation (XAudio2)
   *============================================================================*/

#ifdef _WIN32

#include <mmreg.h>
#include <tchar.h>
#include <windows.h>
#include <xaudio2.h>

#ifdef _XBOX // Big-Endian
#define FOUR_CC_RIFF 'RIFF'
#define FOUR_CC_DATA 'data'
#define FOUR_CC_FMT 'fmt '
#define FOUR_CC_WAVE 'WAVE'
#define FOUR_CC_XWMA 'XWMA'
#define FOUR_CC_DPDS 'dpds'
#endif

#ifndef _XBOX // Little-Endian
#define FOUR_CC_RIFF 'FFIR'
#define FOUR_CC_DATA 'atad'
#define FOUR_CC_FMT ' tmf'
#define FOUR_CC_WAVE 'EVAW'
#define FOUR_CC_XWMA 'AMWX'
#define FOUR_CC_DPDS 'sdpd'
#endif

bool audio_initialized = false;
const float max_volume = 4.0;

IXAudio2* px_audio_2 = NULL;

#if(_WIN32_WINNT >= _WIN32_WINNT_WIN10)
    #define XAUDIO2_DLL_A  "xaudio2_9.dll"
    #define XAUDIO2_DLL_W L"xaudio2_9.dll"
    #define XAUDIO2D_DLL_A  "xaudio2_9d.dll"
    #define XAUDIO2D_DLL_W L"xaudio2_9d.dll"
#else
    #define XAUDIO2_DLL_A  "xaudio2_8.dll"
    #define XAUDIO2_DLL_W L"xaudio2_8.dll"
    #define XAUDIO2D_DLL_A  "xaudio2_8.dll"
    #define XAUDIO2D_DLL_W L"xaudio2_8.dll"
#endif
#ifdef UNICODE
    #define XAUDIO2_DLL XAUDIO2_DLL_W
    #define XAUDIO2D_DLL XAUDIO2D_DLL_W
#else
    #define XAUDIO2_DLL XAUDIO2_DLL_A
    #define XAUDIO2D_DLL XAUDIO2D_DLL_A
#endif


BSAPI bs_Result _bs_playSound(bs_Sound* sound, float volume) {
    IXAudio2SourceVoice* voice = sound->xaudio;

    if (volume > max_volume) volume = max_volume;
    if (volume < -max_volume) volume = -max_volume;

    XAUDIO2_BUFFER buffer = { 0 };
    buffer.AudioBytes = sound->size;
    buffer.pAudioData = sound->data;
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    voice->lpVtbl->Stop(voice, 0, 0);
    voice->lpVtbl->FlushSourceBuffers(voice);
    voice->lpVtbl->SubmitSourceBuffer(voice, &buffer, NULL);
    voice->lpVtbl->SetVolume(voice, volume, 0);
    voice->lpVtbl->Start(voice, 0, 0);

    return BS_RESULT_OK;
}

BSAPI bs_Result _val_bs_playSound(bs_Sound* sound, float volume) {
    BS_VALIDATE(sound->xaudio != NULL, BS_RESULT_INVALID_STATE, );

    return _bs_playSound(sound, volume);
}

static bs_Result _bs_findAudioChunk(
    HANDLE file_handle, DWORD four_cc,
    DWORD* dw_chunk_size, DWORD* dw_chunk_data_position)
{
    HRESULT result = S_OK;
    if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        return BS_RESULT_GENERAL_ERROR;

    DWORD dw_read;
    DWORD dw_chunk_type;
    DWORD dw_chunk_data_size;
    DWORD dw_RIFF_data_size = 0;
    DWORD dw_file_type;
    DWORD dw_offset = 0;
    DWORD num_bytes_read = 0;

    while (result == S_OK) {
        if (ReadFile(file_handle, &dw_chunk_type, sizeof(DWORD), &dw_read, NULL) == 0)
            return BS_RESULT_GENERAL_ERROR;

        if (ReadFile(file_handle, &dw_chunk_data_size, sizeof(DWORD), &dw_read, NULL) == 0)
            return BS_RESULT_GENERAL_ERROR;

        switch (dw_chunk_type) {
        case FOUR_CC_RIFF: {
            dw_RIFF_data_size = dw_chunk_data_size;
            dw_chunk_data_size = 4;
            if (ReadFile(file_handle, &dw_file_type, sizeof(DWORD), &dw_read, NULL) == 0)
                return BS_RESULT_GENERAL_ERROR;
        } break;
        default:
            if (SetFilePointer(file_handle, dw_chunk_data_size, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
                return BS_RESULT_GENERAL_ERROR;
        }

        dw_offset += sizeof(DWORD) * 2;
        if (dw_chunk_type == four_cc) {
            *dw_chunk_size = dw_chunk_data_size;
            *dw_chunk_data_position = dw_offset;
            return BS_RESULT_OK;
        }

        dw_offset += dw_chunk_data_size;

        if (num_bytes_read >= dw_RIFF_data_size)
            return BS_RESULT_GENERAL_ERROR;
    }

    return BS_RESULT_OK;
}

static bs_Result _bs_readAudioChunk(
    HANDLE file_handle, void* buffer,
    DWORD buffer_num_bytes, DWORD buffer_offset)
{
    DWORD dw_read;

    if (SetFilePointer(file_handle, buffer_offset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        return BS_RESULT_GENERAL_ERROR;

    if (ReadFile(file_handle, buffer, buffer_num_bytes, &dw_read, NULL) == 0)
        return BS_RESULT_GENERAL_ERROR;

    return BS_RESULT_OK;
}

BSAPI bs_Result _bs_sound(bs_Resource* resource, bs_U32 flags) {
    /*
    IXAudio2SourceVoice* src_voice = NULL;
    WAVEFORMATEXTENSIBLE wfx = { 0 };
    DWORD chunk_size;
    DWORD chunk_offset;
    DWORD file_type;
    HANDLE file_handle = CreateFile(path->value, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    BYTE *data;

    if (file_handle == INVALID_HANDLE_VALUE)
        _bs_throwLastWin32Error(name);

    if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        _bs_throwLastWin32Error(name);

    // check the file type, should be fourccWAVE or 'XWMA'
    _bs_findAudioChunk(file_handle, FOUR_CC_RIFF, &chunk_size, &chunk_offset);
    _bs_readAudioChunk(file_handle, &file_type, sizeof(DWORD), chunk_offset);

    if (file_type != FOUR_CC_WAVE)
        _bs_throwBasilisk(BSXI_INTERNAL | BSX_INVALID_FILE_TYPE);

    _bs_findAudioChunk(file_handle, FOUR_CC_FMT, &chunk_size, &chunk_offset);
    _bs_readAudioChunk(file_handle, &wfx, chunk_size, chunk_offset);

    _bs_findAudioChunk(file_handle, FOUR_CC_DATA, &chunk_size, &chunk_offset);
    data = _bs_malloc(chunk_size);
    _bs_readAudioChunk(file_handle, data, chunk_size, chunk_offset);

    HRESULT result = px_audio_2->lpVtbl->CreateSourceVoice(px_audio_2, &src_voice, (WAVEFORMATEX*)&wfx, 0, XAUDIO2_MAX_FREQ_RATIO, NULL, NULL, NULL);
    if (FAILED(result))
        _bs_throwHResult(result, NULL);

    CloseHandle(file_handle);

    bs_Sound sound = {
        .xaudio = src_voice,
        .data = data,
        .size = chunk_size,
        .name = name,
    };

    _bs_free(path);

    memcpy(existing, &sound, sizeof(bs_Sound));
    */

    return BS_RESULT_NOT_IMPLEMENTED;
}

BSAPI bs_Result _bs_iniAudio() {
    HRESULT result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    IXAudio2MasteringVoice* master_voice = NULL;

    if (FAILED(result))
        return BS_RESULT_GENERAL_ERROR;

    result = XAudio2Create(&px_audio_2, 0, XAUDIO2_DEFAULT_PROCESSOR);

    if (FAILED(result))
        return BS_RESULT_GENERAL_ERROR;

    result = px_audio_2->lpVtbl->CreateMasteringVoice(px_audio_2, &master_voice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, NULL, NULL, 0);
    if (result == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
        return BS_RESULT_GENERAL_ERROR;

    audio_initialized = true;

    return BS_RESULT_OK;
}

#else
#endif