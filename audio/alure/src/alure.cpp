/*
 * ALURE  OpenAL utility library
 * Copyright (c) 2009 by Chris Robinson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/* Title: Main and Miscellanious */

#include "config.h"

#include "main.h"

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif

#include <vector>
#include <string>
#include <map>

std::map<ALint,UserCallbacks> InstalledCallbacks;
CRITICAL_SECTION cs_StreamPlay;
alureStream::ListType alureStream::StreamList;

void *vorbisfile_handle = NULL;
void *flac_handle = NULL;
void *dumb_handle = NULL;
void *mod_handle = NULL;
void *mp123_handle = NULL;
void *sndfile_handle = NULL;
void *fsynth_handle = NULL;

#define MAKE_FUNC(x) typeof(x)* p##x
#ifdef HAS_VORBISFILE
MAKE_FUNC(ov_clear);
MAKE_FUNC(ov_info);
MAKE_FUNC(ov_open_callbacks);
MAKE_FUNC(ov_pcm_seek);
MAKE_FUNC(ov_read);
#endif
#ifdef HAS_FLAC
MAKE_FUNC(FLAC__stream_decoder_get_state);
MAKE_FUNC(FLAC__stream_decoder_finish);
MAKE_FUNC(FLAC__stream_decoder_new);
MAKE_FUNC(FLAC__stream_decoder_seek_absolute);
MAKE_FUNC(FLAC__stream_decoder_delete);
MAKE_FUNC(FLAC__stream_decoder_process_single);
MAKE_FUNC(FLAC__stream_decoder_init_stream);
#endif
#ifdef HAS_DUMB
MAKE_FUNC(dumbfile_open_ex);
MAKE_FUNC(dumbfile_close);
MAKE_FUNC(dumb_read_mod);
MAKE_FUNC(dumb_read_s3m);
MAKE_FUNC(dumb_read_xm);
MAKE_FUNC(dumb_read_it);
MAKE_FUNC(dumb_silence);
MAKE_FUNC(duh_sigrenderer_generate_samples);
MAKE_FUNC(duh_get_it_sigrenderer);
MAKE_FUNC(duh_end_sigrenderer);
MAKE_FUNC(unload_duh);
MAKE_FUNC(dumb_it_start_at_order);
MAKE_FUNC(dumb_it_set_loop_callback);
MAKE_FUNC(dumb_it_sr_get_speed);
MAKE_FUNC(dumb_it_sr_set_speed);
#endif
#ifdef HAS_MODPLUG
MAKE_FUNC(ModPlug_Load);
MAKE_FUNC(ModPlug_Unload);
MAKE_FUNC(ModPlug_Read);
MAKE_FUNC(ModPlug_SeekOrder);
#endif
#ifdef HAS_MPG123
MAKE_FUNC(mpg123_read);
MAKE_FUNC(mpg123_init);
MAKE_FUNC(mpg123_open_feed);
MAKE_FUNC(mpg123_new);
MAKE_FUNC(mpg123_delete);
MAKE_FUNC(mpg123_feed);
MAKE_FUNC(mpg123_exit);
MAKE_FUNC(mpg123_getformat);
MAKE_FUNC(mpg123_format_none);
MAKE_FUNC(mpg123_decode);
MAKE_FUNC(mpg123_format);
#endif
#ifdef HAS_SNDFILE
MAKE_FUNC(sf_close);
MAKE_FUNC(sf_open_virtual);
MAKE_FUNC(sf_readf_short);
MAKE_FUNC(sf_seek);
#endif
#ifdef HAS_FLUIDSYNTH
MAKE_FUNC(fluid_settings_setstr);
MAKE_FUNC(fluid_synth_program_change);
MAKE_FUNC(fluid_synth_sfload);
MAKE_FUNC(fluid_settings_setnum);
MAKE_FUNC(fluid_synth_sysex);
MAKE_FUNC(fluid_synth_cc);
MAKE_FUNC(fluid_synth_pitch_bend);
MAKE_FUNC(fluid_synth_channel_pressure);
MAKE_FUNC(fluid_synth_write_float);
MAKE_FUNC(new_fluid_synth);
MAKE_FUNC(delete_fluid_settings);
MAKE_FUNC(delete_fluid_synth);
MAKE_FUNC(fluid_synth_program_reset);
MAKE_FUNC(fluid_settings_setint);
MAKE_FUNC(new_fluid_settings);
MAKE_FUNC(fluid_synth_write_s16);
MAKE_FUNC(fluid_synth_noteoff);
MAKE_FUNC(fluid_synth_sfunload);
MAKE_FUNC(fluid_synth_noteon);
#endif
#undef MAKE_FUNC

#ifdef HAVE_GCC_CONSTRUCTOR
static void init_alure(void) __attribute__((constructor));
static void deinit_alure(void) __attribute__((destructor));
static struct MyConstructorClass {
    ~MyConstructorClass()
    { alureStream::Clear(); };
} MyConstructor;
#elif defined(_WIN32) && !defined(ALURE_STATIC_LIBRARY)
static void init_alure(void);
static void deinit_alure(void);
static struct MyConstructorClass {
    ~MyConstructorClass()
    { alureStream::Clear(); };
} MyConstructor;

extern "C" BOOL APIENTRY DllMain(HINSTANCE module, DWORD reason, LPVOID reserved)
{
    (void)reserved;

    // Perform actions based on the reason for calling.
    switch(reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            init_alure();
            break;

        case DLL_PROCESS_DETACH:
            deinit_alure();
            break;
    }
    return TRUE;
}
#else
static void init_alure(void);
static void deinit_alure(void);

static struct MyConstructorClass {
    MyConstructorClass()
    { init_alure(); };
    ~MyConstructorClass()
    { alureStream::Clear();
      deinit_alure(); };
} MyConstructor;
#endif


#ifndef DYNLOAD
static inline void *OpenLib(const char*)
{ return (void*)0xDEADBEEF; }
static inline void CloseLib(void*)
{ }
#define LOAD_FUNC(h, x) p##x = x

#else
#ifdef _WIN32

static inline void *OpenLib(const char *libname)
{ return LoadLibraryA(libname); }
static inline void CloseLib(void *hdl)
{ FreeLibrary((HINSTANCE)hdl); }
static inline void *GetLibProc(void *hdl, const char *funcname)
{ return (void*)GetProcAddress((HINSTANCE)hdl, funcname); }

#else

static inline void *OpenLib(const char *libname)
{
    dlerror();
    void *hdl = dlopen(libname, RTLD_NOW);
    const char *err;
    if((err=dlerror()) != NULL)
    {
        fprintf(stderr, "Error loading %s: %s\n", libname, err);
        return NULL;
    }
    return hdl;
}
static inline void *GetLibProc(void *hdl, const char *funcname)
{
    dlerror();
    void *fn = dlsym(hdl, funcname);
    const char *err;
    if((err=dlerror()) != NULL)
    {
        fprintf(stderr, "Error loading %s: %s\n", funcname, err);
        return NULL;
    }
    return fn;
}
static inline void CloseLib(void *hdl)
{ dlclose(hdl); }
#endif

#define LOAD_FUNC(h, x) p##x = (typeof(p##x))GetLibProc(h##_handle, #x);     \
if(!p##x)                                                                    \
{                                                                            \
    CloseLib(h##_handle);                                                    \
    h##_handle = NULL;                                                       \
    break;                                                                   \
}
#endif

static void init_alure(void)
{
    InitializeCriticalSection(&cs_StreamPlay);

#ifdef _WIN32
#define VORBISFILE_LIB "vorbisfile.dll"
#define FLAC_LIB "libFLAC.dll"
#define DUMB_LIB "libdumb.dll"
#define MODPLUG_LIB "libmodplug.dll"
#define MPG123_LIB "libmpg123.dll"
#define SNDFILE_LIB "libsndfile-1.dll"
#define FLUIDSYNTH_LIB "libfluidsynth.dll"
#elif defined(__APPLE__)
#define VORBISFILE_LIB "libvorbisfile.3.dylib"
#define FLAC_LIB "libFLAC.8.dylib"
#define DUMB_LIB "libdumb.dylib"
#define MODPLUG_LIB "libmodplug.1.dylib"
#define MPG123_LIB "libmpg123.0.dylib"
#define SNDFILE_LIB "libsndfile.1.dylib"
#define FLUIDSYNTH_LIB "libfluidsynth.1.dylib"
#else
#define VORBISFILE_LIB "libvorbisfile.so.3"
#define FLAC_LIB "libFLAC.so.8"
#define DUMB_LIB "libdumb.so"
#define MODPLUG_LIB "libmodplug.so.1"
#define MPG123_LIB "libmpg123.so.0"
#define SNDFILE_LIB "libsndfile.so.1"
#define FLUIDSYNTH_LIB "libfluidsynth.so.1"
#endif

#ifdef HAS_VORBISFILE
    vorbisfile_handle = OpenLib(VORBISFILE_LIB);
    while(vorbisfile_handle)
    {
        LOAD_FUNC(vorbisfile, ov_clear);
        LOAD_FUNC(vorbisfile, ov_info);
        LOAD_FUNC(vorbisfile, ov_open_callbacks);
        LOAD_FUNC(vorbisfile, ov_pcm_seek);
        LOAD_FUNC(vorbisfile, ov_read);
        break;
    }
#endif

#ifdef HAS_FLAC
    flac_handle = OpenLib(FLAC_LIB);
    while(flac_handle)
    {
        LOAD_FUNC(flac, FLAC__stream_decoder_get_state);
        LOAD_FUNC(flac, FLAC__stream_decoder_finish);
        LOAD_FUNC(flac, FLAC__stream_decoder_new);
        LOAD_FUNC(flac, FLAC__stream_decoder_seek_absolute);
        LOAD_FUNC(flac, FLAC__stream_decoder_delete);
        LOAD_FUNC(flac, FLAC__stream_decoder_process_single);
        LOAD_FUNC(flac, FLAC__stream_decoder_init_stream);
        break;
    }
#endif

#ifdef HAS_DUMB
    dumb_handle = OpenLib(DUMB_LIB);
    while(dumb_handle)
    {
        LOAD_FUNC(dumb, dumbfile_open_ex);
        LOAD_FUNC(dumb, dumbfile_close);
        LOAD_FUNC(dumb, dumb_read_mod);
        LOAD_FUNC(dumb, dumb_read_s3m);
        LOAD_FUNC(dumb, dumb_read_xm);
        LOAD_FUNC(dumb, dumb_read_it);
        LOAD_FUNC(dumb, dumb_silence);
        LOAD_FUNC(dumb, duh_sigrenderer_generate_samples);
        LOAD_FUNC(dumb, duh_get_it_sigrenderer);
        LOAD_FUNC(dumb, duh_end_sigrenderer);
        LOAD_FUNC(dumb, unload_duh);
        LOAD_FUNC(dumb, dumb_it_start_at_order);
        LOAD_FUNC(dumb, dumb_it_set_loop_callback);
        LOAD_FUNC(dumb, dumb_it_sr_get_speed);
        LOAD_FUNC(dumb, dumb_it_sr_set_speed);
        break;
    }
#endif

#ifdef HAS_MODPLUG
    mod_handle = OpenLib(MODPLUG_LIB);
    while(mod_handle)
    {
        LOAD_FUNC(mod, ModPlug_Load);
        LOAD_FUNC(mod, ModPlug_Unload);
        LOAD_FUNC(mod, ModPlug_Read);
        LOAD_FUNC(mod, ModPlug_SeekOrder);
        break;
    }
#endif

#ifdef HAS_MPG123
    mp123_handle = OpenLib(MPG123_LIB);
    while(mp123_handle)
    {
        LOAD_FUNC(mp123, mpg123_read);
        LOAD_FUNC(mp123, mpg123_init);
        LOAD_FUNC(mp123, mpg123_open_feed);
        LOAD_FUNC(mp123, mpg123_new);
        LOAD_FUNC(mp123, mpg123_delete);
        LOAD_FUNC(mp123, mpg123_feed);
        LOAD_FUNC(mp123, mpg123_exit);
        LOAD_FUNC(mp123, mpg123_getformat);
        LOAD_FUNC(mp123, mpg123_format_none);
        LOAD_FUNC(mp123, mpg123_decode);
        LOAD_FUNC(mp123, mpg123_format);
        pmpg123_init();
        break;
    }
#endif

#ifdef HAS_SNDFILE
    sndfile_handle = OpenLib(SNDFILE_LIB);
    while(sndfile_handle)
    {
        LOAD_FUNC(sndfile, sf_close);
        LOAD_FUNC(sndfile, sf_open_virtual);
        LOAD_FUNC(sndfile, sf_readf_short);
        LOAD_FUNC(sndfile, sf_seek);
        break;
    }
#endif

#ifdef HAS_FLUIDSYNTH
    fsynth_handle = OpenLib(FLUIDSYNTH_LIB);
    while(fsynth_handle)
    {
        LOAD_FUNC(fsynth, fluid_settings_setstr);
        LOAD_FUNC(fsynth, fluid_synth_program_change);
        LOAD_FUNC(fsynth, fluid_synth_sfload);
        LOAD_FUNC(fsynth, fluid_settings_setnum);
        LOAD_FUNC(fsynth, fluid_synth_sysex);
        LOAD_FUNC(fsynth, fluid_synth_cc);
        LOAD_FUNC(fsynth, fluid_synth_pitch_bend);
        LOAD_FUNC(fsynth, fluid_synth_channel_pressure);
        LOAD_FUNC(fsynth, fluid_synth_write_float);
        LOAD_FUNC(fsynth, new_fluid_synth);
        LOAD_FUNC(fsynth, delete_fluid_settings);
        LOAD_FUNC(fsynth, delete_fluid_synth);
        LOAD_FUNC(fsynth, fluid_synth_program_reset);
        LOAD_FUNC(fsynth, fluid_settings_setint);
        LOAD_FUNC(fsynth, new_fluid_settings);
        LOAD_FUNC(fsynth, fluid_synth_write_s16);
        LOAD_FUNC(fsynth, fluid_synth_noteoff);
        LOAD_FUNC(fsynth, fluid_synth_sfunload);
        LOAD_FUNC(fsynth, fluid_synth_noteon);
        break;
    }
#endif

#undef VORBISFILE_LIB
#undef FLAC_LIB
#undef DUMB_LIB
#undef MPG123_LIB
#undef SNDFILE_LIB
#undef LOAD_FUNC
}

static void deinit_alure(void)
{
#ifdef HAS_VORBISFILE
    if(vorbisfile_handle)
        CloseLib(vorbisfile_handle);
    vorbisfile_handle = NULL;
#endif
#ifdef HAS_FLAC
    if(flac_handle)
        CloseLib(flac_handle);
    flac_handle = NULL;
#endif
#ifdef HAS_DUMB
    if(dumb_handle)
        CloseLib(dumb_handle);
    dumb_handle = NULL;
#endif
#ifdef HAS_MODPLUG
    if(mod_handle)
        CloseLib(mod_handle);
    mod_handle = NULL;
#endif
#ifdef HAS_MPG123
    if(mp123_handle)
    {
        pmpg123_exit();
        CloseLib(mp123_handle);
    }
    mp123_handle = NULL;
#endif
#ifdef HAS_SNDFILE
    if(sndfile_handle)
        CloseLib(sndfile_handle);
    sndfile_handle = NULL;
#endif
#ifdef HAS_FLUIDSYNTH
    if(fsynth_handle)
        CloseLib(fsynth_handle);
    fsynth_handle = NULL;
#endif

    DeleteCriticalSection(&cs_StreamPlay);
}


static const ALchar *last_error = "No error";

void SetError(const char *err)
{
    last_error = err;
}

ALuint DetectBlockAlignment(ALenum format)
{
    switch(format)
    {
#define CHECK_RET(f,s) case (f): return (s)
        CHECK_RET(AL_FORMAT_MONO8, sizeof(ALubyte));
        CHECK_RET(AL_FORMAT_MONO16, sizeof(ALshort));
        CHECK_RET(AL_FORMAT_MONO_FLOAT32, sizeof(ALfloat));
        CHECK_RET(AL_FORMAT_MONO_DOUBLE_EXT, sizeof(ALdouble));
        CHECK_RET(AL_FORMAT_MONO_MULAW, sizeof(ALubyte)*1);

        CHECK_RET(AL_FORMAT_STEREO8, sizeof(ALubyte)*2);
        CHECK_RET(AL_FORMAT_STEREO16, sizeof(ALshort)*2);
        CHECK_RET(AL_FORMAT_STEREO_FLOAT32, sizeof(ALfloat)*2);
        CHECK_RET(AL_FORMAT_STEREO_DOUBLE_EXT, sizeof(ALdouble)*2);
        CHECK_RET(AL_FORMAT_STEREO_MULAW, sizeof(ALubyte)*2);

        CHECK_RET(AL_FORMAT_QUAD8, sizeof(ALubyte)*4);
        CHECK_RET(AL_FORMAT_QUAD16, sizeof(ALshort)*4);
        CHECK_RET(AL_FORMAT_QUAD32, sizeof(ALfloat)*4);
        CHECK_RET(AL_FORMAT_QUAD_MULAW, sizeof(ALubyte)*4);

        CHECK_RET(AL_FORMAT_REAR8, sizeof(ALubyte)*2);
        CHECK_RET(AL_FORMAT_REAR16, sizeof(ALshort)*2);
        CHECK_RET(AL_FORMAT_REAR32, sizeof(ALfloat)*2);
        CHECK_RET(AL_FORMAT_REAR_MULAW, sizeof(ALubyte)*2);

        CHECK_RET(AL_FORMAT_51CHN8, sizeof(ALubyte)*6);
        CHECK_RET(AL_FORMAT_51CHN16, sizeof(ALshort)*6);
        CHECK_RET(AL_FORMAT_51CHN32, sizeof(ALfloat)*6);
        CHECK_RET(AL_FORMAT_51CHN_MULAW, sizeof(ALubyte)*6);

        CHECK_RET(AL_FORMAT_61CHN8, sizeof(ALubyte)*7);
        CHECK_RET(AL_FORMAT_61CHN16, sizeof(ALshort)*7);
        CHECK_RET(AL_FORMAT_61CHN32, sizeof(ALfloat)*7);
        CHECK_RET(AL_FORMAT_61CHN_MULAW, sizeof(ALubyte)*7);

        CHECK_RET(AL_FORMAT_71CHN8, sizeof(ALubyte)*8);
        CHECK_RET(AL_FORMAT_71CHN16, sizeof(ALshort)*8);
        CHECK_RET(AL_FORMAT_71CHN32, sizeof(ALfloat)*8);
        CHECK_RET(AL_FORMAT_71CHN_MULAW, sizeof(ALubyte)*8);

        CHECK_RET(AL_FORMAT_MONO_IMA4, 36);
        CHECK_RET(AL_FORMAT_STEREO_IMA4, 36*2);
#undef CHECK_RET
    }
    return 0;
}

ALuint DetectCompressionRate(ALenum format)
{
    switch(format)
    {
    case AL_FORMAT_MONO8:
    case AL_FORMAT_MONO16:
    case AL_FORMAT_MONO_FLOAT32:
    case AL_FORMAT_MONO_DOUBLE_EXT:
    case AL_FORMAT_STEREO8:
    case AL_FORMAT_STEREO16:
    case AL_FORMAT_STEREO_FLOAT32:
    case AL_FORMAT_STEREO_DOUBLE_EXT:
    case AL_FORMAT_QUAD8:
    case AL_FORMAT_QUAD16:
    case AL_FORMAT_QUAD32:
    case AL_FORMAT_REAR8:
    case AL_FORMAT_REAR16:
    case AL_FORMAT_REAR32:
    case AL_FORMAT_51CHN8:
    case AL_FORMAT_51CHN16:
    case AL_FORMAT_51CHN32:
    case AL_FORMAT_61CHN8:
    case AL_FORMAT_61CHN16:
    case AL_FORMAT_61CHN32:
    case AL_FORMAT_71CHN8:
    case AL_FORMAT_71CHN16:
    case AL_FORMAT_71CHN32:
        return 1;

    case AL_FORMAT_MONO_MULAW:
    case AL_FORMAT_STEREO_MULAW:
    case AL_FORMAT_QUAD_MULAW:
    case AL_FORMAT_REAR_MULAW:
    case AL_FORMAT_51CHN_MULAW:
    case AL_FORMAT_61CHN_MULAW:
    case AL_FORMAT_71CHN_MULAW:
        return 1;

    case AL_FORMAT_MONO_IMA4:
    case AL_FORMAT_STEREO_IMA4:
        return 65;
    }
    fprintf(stderr, "Alure lib: Unhandled format: %#x\n", format);
    return 0;
}

ALenum GetSampleFormat(ALuint channels, ALuint bits, bool isFloat)
{
#define CHECK_FMT_RET(f) do {                                                 \
    ALenum fmt = alGetEnumValue(#f);                                          \
    if(alGetError() == AL_NO_ERROR && fmt != 0 && fmt != -1)                  \
        return fmt;                                                           \
} while(0)
    if(!isFloat)
    {
        if(bits == 8)
        {
            if(channels == 1) CHECK_FMT_RET(AL_FORMAT_MONO8);
            if(channels == 2) CHECK_FMT_RET(AL_FORMAT_STEREO8);
            if(alIsExtensionPresent("AL_EXT_MCFORMATS"))
            {
                if(channels == 4) CHECK_FMT_RET(AL_FORMAT_QUAD8);
                if(channels == 6) CHECK_FMT_RET(AL_FORMAT_51CHN8);
                if(channels == 7) CHECK_FMT_RET(AL_FORMAT_61CHN8);
                if(channels == 8) CHECK_FMT_RET(AL_FORMAT_71CHN8);
            }
            if(alIsExtensionPresent("AL_LOKI_quadriphonic"))
            {
                if(channels == 4) CHECK_FMT_RET(AL_FORMAT_QUAD8_LOKI);
            }
            SetError("Unsupported 8-bit channel count\n");
            return AL_NONE;
        }
        if(bits == 16)
        {
            if(channels == 1) CHECK_FMT_RET(AL_FORMAT_MONO16);
            if(channels == 2) CHECK_FMT_RET(AL_FORMAT_STEREO16);
            if(alIsExtensionPresent("AL_EXT_MCFORMATS"))
            {
                if(channels == 4) CHECK_FMT_RET(AL_FORMAT_QUAD16);
                if(channels == 6) CHECK_FMT_RET(AL_FORMAT_51CHN16);
                if(channels == 7) CHECK_FMT_RET(AL_FORMAT_61CHN16);
                if(channels == 8) CHECK_FMT_RET(AL_FORMAT_71CHN16);
            }
            if(alIsExtensionPresent("AL_LOKI_quadriphonic"))
            {
                if(channels == 4) CHECK_FMT_RET(AL_FORMAT_QUAD16_LOKI);
            }
            SetError("Unsupported 16-bit channel count\n");
            return AL_NONE;
        }
        SetError("Unsupported PCM bit depth\n");
        return AL_NONE;
    }

    if(bits == 32 && alIsExtensionPresent("AL_EXT_FLOAT32"))
    {
        if(channels == 1) CHECK_FMT_RET(AL_FORMAT_MONO_FLOAT32);
        if(channels == 2) CHECK_FMT_RET(AL_FORMAT_STEREO_FLOAT32);
        if(alIsExtensionPresent("AL_EXT_MCFORMATS"))
        {
            if(channels == 4) CHECK_FMT_RET(AL_FORMAT_QUAD32);
            if(channels == 6) CHECK_FMT_RET(AL_FORMAT_51CHN32);
            if(channels == 7) CHECK_FMT_RET(AL_FORMAT_61CHN32);
            if(channels == 8) CHECK_FMT_RET(AL_FORMAT_71CHN32);
        }
        SetError("Unsupported float32 channel count\n");
        return AL_NONE;
    }
    if(bits == 64 && alIsExtensionPresent("AL_EXT_DOUBLE"))
    {
        if(channels == 1) CHECK_FMT_RET(AL_FORMAT_MONO_DOUBLE_EXT);
        if(channels == 2) CHECK_FMT_RET(AL_FORMAT_STEREO_DOUBLE_EXT);
        SetError("Unsupported double channel count\n");
        return AL_NONE;
    }
#undef CHECK_FMT_RET

    SetError("Unsupported float bit depth\n");
    return AL_NONE;
}

extern "C" {

/* Function: alureGetVersion
 *
 * Stores the major and minor version of the library. If either major or minor
 * are NULL, that value is not provided.
 */
ALURE_API void ALURE_APIENTRY alureGetVersion(ALuint *major, ALuint *minor)
{
    if(major) *major = ALURE_VER_MAJOR;
    if(minor) *minor = ALURE_VER_MINOR;
}

/* Function: alureGetErrorString
 *
 * Returns a string describing the last error encountered.
 */
ALURE_API const ALchar* ALURE_APIENTRY alureGetErrorString(void)
{
    const ALchar *ret = last_error;
    last_error = "No error";
    return ret;
}


/* Function: alureGetDeviceNames
 *
 * Gets an array of device name strings from OpenAL. This encapsulates
 * AL_ENUMERATE_ALL_EXT (if supported and 'all' is true) and standard
 * enumeration, with 'count' being set to the number of returned device
 * names.
 *
 * Returns:
 * An array of device name strings, or NULL on error.
 *
 * See Also:
 * <alureFreeDeviceNames>
 */
ALURE_API const ALCchar** ALURE_APIENTRY alureGetDeviceNames(ALCboolean all, ALCsizei *count)
{
    const ALCchar *list = NULL;
    if(all && alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT"))
        list = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
    else
        list = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    if(!list)
    {
        alcGetError(NULL);
        SetError("No device names found");
        return NULL;
    }

    const ALCchar *cur = list;
    ALuint retlistLen = 0;
    while(*cur)
    {
        cur += strlen(cur)+1;
        retlistLen++;
    }

    const ALCchar **retlist = new const ALCchar*[retlistLen+1];
    retlistLen = 0;
    cur = list;
    while(*cur)
    {
        ALCuint len = strlen(cur)+1;
        ALCchar *newstr = new ALCchar[len];

        memcpy(newstr, cur, len);
        cur += len;

        retlist[retlistLen] = newstr;
        retlistLen++;
    }
    retlist[retlistLen] = NULL;

    *count = retlistLen;
    return retlist;
}

/* Function: alureFreeDeviceNames
 *
 * Frees the device name array returned from alureGetDeviceNames.
 *
 * See Also:
 * <alureGetDeviceNames>
 */
ALURE_API ALvoid ALURE_APIENTRY alureFreeDeviceNames(const ALCchar **names)
{
    if(names)
    {
        for(ALCuint i = 0;names[i];i++)
            delete[] const_cast<ALCchar*>(names[i]);
        delete[] names;
    }
}


/* Function: alureInitDevice
 *
 * Opens the named device, creates a context with the given attributes, and
 * sets that context as current. The name and attribute list would be the same
 * as what's passed to alcOpenDevice and alcCreateContext respectively.
 *
 * Returns:
 * AL_FALSE on error.
 *
 * See Also:
 * <alureShutdownDevice>
 */
ALURE_API ALboolean ALURE_APIENTRY alureInitDevice(const ALCchar *name, const ALCint *attribs)
{
    ALCdevice *device = alcOpenDevice(name);
    if(!device)
    {
        alcGetError(NULL);

        SetError("Device open failed");
        return AL_FALSE;
    }

    ALCcontext *context = alcCreateContext(device, attribs);
    if(!context || alcMakeContextCurrent(context) == ALC_FALSE)
    {
        if(context)
            alcDestroyContext(context);
        alcCloseDevice(device);

        SetError("Context setup failed");
        return AL_FALSE;
    }
    alcGetError(device);

    return AL_TRUE;
}

/* Function: alureShutdownDevice
 *
 * Destroys the current context and closes its associated device.
 *
 * Returns:
 * AL_FALSE on error.
 *
 * See Also:
 * <alureInitDevice>
 */
ALURE_API ALboolean ALURE_APIENTRY alureShutdownDevice(void)
{
    ALCcontext *context = alcGetCurrentContext();
    ALCdevice *device = alcGetContextsDevice(context);
    if(!context || !device)
    {
        alcGetError(device);
        SetError("Failed to get current device");
        return AL_FALSE;
    }

    if(alcMakeContextCurrent(NULL) == ALC_FALSE)
    {
        alcGetError(NULL);
        SetError("Failed to unset current context");
        return AL_FALSE;
    }

    alcDestroyContext(context);
    alcCloseDevice(device);
    alcGetError(NULL);

    return AL_TRUE;
}


/* Function: alureGetSampleFormat
 *
 * Retrieves an OpenAL format for the given sample format. If bits is non-0,
 * floatbits must be 0, and if floatbits is non-0, bits must be 0. The
 * application should not rely on any particular format enum being returned as
 * it is dependant on the available extensions. The returned format will be
 * valid for the current context. Requires an active context.
 *
 * Returns:
 * An OpenAL format enum for the given sample format, or AL_NONE if one can't
 * be found.
 */
ALURE_API ALenum ALURE_APIENTRY alureGetSampleFormat(ALuint channels, ALuint bits, ALuint floatbits)
{
    if(alGetError() != AL_NO_ERROR)
    {
        SetError("Existing OpenAL error");
        return AL_NONE;
    }

    if(bits && floatbits)
    {
        SetError("Both bit-types specified");
        return AL_NONE;
    }

    if(bits)
        return GetSampleFormat(channels, bits, false);
    return GetSampleFormat(channels, floatbits, true);
}


/* Function: alureInstallDecodeCallbacks
 *
 * Installs callbacks to enable ALURE to handle more file types. The index is
 * the order that each given set of callbacks will be tried, starting at the
 * most negative number (INT_MIN) and going up. Negative indices will be tried
 * before the built-in decoders, and positive indices will be tried after.
 * Installing callbacks onto the same index multiple times will remove the
 * previous callbacks, and removing old callbacks won't affect any opened files
 * using them (they'll continue to use the old functions until properly closed,
 * although newly opened files will use the new ones). Passing NULL for all
 * callbacks is a valid way to remove an installed set, otherwise certain
 * callbacks must be specified. Callbacks that are not specified will assume
 * failure.
 *
 * Parameters:
 * open_file - This callback is expected to open the named file and prepare it
 *             for decoding. If the callbacks cannot decode the file, NULL
 *             should be returned to indicate failure. Upon success, a non-NULL
 *             handle must be returned, which will be used as a unique
 *             identifier for the decoder instance. This callback is required
 *             if open_memory is not specified.
 * open_memory - This callback behaves the same as open_file, except it takes a
 *               memory segment for input instead of a filename. The given
 *               memory will remain valid while the instance is open. This
 *               callback is required if open_file is not specified.
 * get_format - This callback is used to retrieve the format of the decoded
 *              data for the given instance. It is the responsibility of the
 *              function to make sure the returned format is valid for the
 *              current AL context (eg. don't return AL_FORMAT_QUAD16 if the
 *              AL_EXT_MCFORMATS extension isn't available). Returning 0 for
 *              samplerate or blocksize, or returning AL_NONE for format, will
 *              cause a failure. Returning AL_FALSE indicates failure. This
 *              callback is required.
 * decode - This callback is called to get more decoded data. Up to the
 *          specified amount of bytes should be written to the data pointer.
 *          The number of bytes written should be a multiple of the block size,
 *          otherwise an OpenAL error may occur during buffering. The function
 *          should return the number of bytes written. This callback is
 *          required.
 * rewind - This callback is for rewinding the instance so that the next decode
 *          calls for it will get audio data from the start of the sound file.
 *          If the stream fails to rewind, AL_FALSE should be returned.
 * close - This callback is called at the end of processing for a particular
 *         instance. The handle will not be used further and any associated
 *         data may be deleted.
 *
 * Returns:
 * AL_FALSE on error.
 */
ALURE_API ALboolean ALURE_APIENTRY alureInstallDecodeCallbacks(ALint index,
      void*     (*open_file)(const ALchar *filename),
      void*     (*open_memory)(const ALubyte *data, ALuint length),
      ALboolean (*get_format)(void *instance, ALenum *format, ALuint *samplerate, ALuint *blocksize),
      ALuint    (*decode)(void *instance, ALubyte *data, ALuint bytes),
      ALboolean (*rewind)(void *instance),
      void      (*close)(void *instance))
{
    if(!open_file && !open_memory && !get_format && !decode && !rewind && !close)
    {
        std::map<ALint,UserCallbacks>::iterator i = InstalledCallbacks.find(index);
        if(i != InstalledCallbacks.end())
            InstalledCallbacks.erase(i);
        return AL_TRUE;
    }

    if((!open_file && !open_memory) || !get_format || !decode)
    {
        SetError("Missing callback functions");
        return AL_FALSE;
    }

    UserCallbacks newcb;
    newcb.open_file = open_file;
    newcb.open_mem  = open_memory;
    newcb.get_fmt   = get_format;
    newcb.decode    = decode;
    newcb.rewind    = rewind;
    newcb.close     = close;

    InstalledCallbacks[index] = newcb;

    return AL_TRUE;
}


/* Function: alureSleep
 *
 * Rests the calling thread for the given number of seconds.
 *
 * Returns:
 * AL_FALSE on error.
 */
ALURE_API ALboolean ALURE_APIENTRY alureSleep(ALfloat duration)
{
    if(duration < 0.0f)
    {
        SetError("Invalid duration");
        return AL_FALSE;
    }

    ALuint seconds = (ALuint)duration;
    ALfloat rest = duration - (ALfloat)seconds;

#ifdef HAVE_NANOSLEEP

    struct timespec t, remainingTime;
    t.tv_sec = (time_t)seconds;
    t.tv_nsec = (long)(rest*1000000)*1000;

    while(nanosleep(&t, &remainingTime) < 0 && errno == EINTR)
        t = remainingTime;

#elif defined(HAVE_WINDOWS_H)

    while(seconds > 0)
    {
        Sleep(1000);
        seconds--;
    }
    Sleep((DWORD)(rest * 1000));

#endif

    return AL_TRUE;
}


/* Function: alureGetProcAddress
 *
 * Returns a pointer for the named ALURE function.
 *
 * Returns:
 * NULL on error.
 *
 * *Version Added*: 1.1
 */
ALURE_API void* ALURE_APIENTRY alureGetProcAddress(const ALchar *funcname)
{
    static const struct {
        const char *name;
        void *func;
    } FunctionList[] = {
#define ADD_FUNCTION(x) { #x, (void*)x },
        ADD_FUNCTION(alureGetVersion)
        ADD_FUNCTION(alureGetErrorString)
        ADD_FUNCTION(alureGetDeviceNames)
        ADD_FUNCTION(alureFreeDeviceNames)
        ADD_FUNCTION(alureInitDevice)
        ADD_FUNCTION(alureShutdownDevice)
        ADD_FUNCTION(alureGetSampleFormat)
        ADD_FUNCTION(alureSleep)
        ADD_FUNCTION(alureCreateBufferFromFile)
        ADD_FUNCTION(alureCreateBufferFromMemory)
        ADD_FUNCTION(alureBufferDataFromFile)
        ADD_FUNCTION(alureBufferDataFromMemory)
        ADD_FUNCTION(alureCreateStreamFromFile)
        ADD_FUNCTION(alureCreateStreamFromMemory)
        ADD_FUNCTION(alureCreateStreamFromStaticMemory)
        ADD_FUNCTION(alureCreateStreamFromCallback)
        ADD_FUNCTION(alureRewindStream)
        ADD_FUNCTION(alureDestroyStream)
        ADD_FUNCTION(alureInstallDecodeCallbacks)
        ADD_FUNCTION(alureSetIOCallbacks)
        ADD_FUNCTION(alureGetProcAddress)
        ADD_FUNCTION(alurePlaySourceStream)
        ADD_FUNCTION(alurePlaySource)
        ADD_FUNCTION(alureStopSource)
#undef ADD_FUNCTION
        { NULL, NULL }
    };

    size_t i;
    for(i = 0;FunctionList[i].name;i++)
    {
        if(strcmp(FunctionList[i].name, funcname) == 0)
            break;
    }

    if(!FunctionList[i].name)
        SetError("Function not found");
    return FunctionList[i].func;
}

} // extern "C"
