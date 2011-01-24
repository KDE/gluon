/*
 * ALURE  OpenAL utility library
 * Copyright (c) 2009-2010 by Chris Robinson.
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

#include "config.h"

#include "main.h"

#include <string.h>

#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>


struct Decoder {
    typedef std::auto_ptr<alureStream>(*FactoryType)(std::istream*);
    typedef std::vector<FactoryType> ListType;

    static const ListType& GetList()
    { return AddList(NULL); }

protected:
    template<typename T>
    static std::auto_ptr<alureStream> Factory(std::istream *file)
    {
        std::auto_ptr<alureStream> ret(new T(file));
        if(ret->IsValid()) return ret;
        return std::auto_ptr<alureStream>();
    }

    static const ListType& AddList(FactoryType func)
    {
        static ListType FuncList;
        if(func) FuncList.push_back(func);
        return FuncList;
    }
};
template<typename T>
struct DecoderDecl : public Decoder {
    DecoderDecl() { AddList(Factory<T>); }
};


static inline ALuint read_le32(std::istream *file)
{
    ALubyte buffer[4];
    if(!file->read(reinterpret_cast<char*>(buffer), 4)) return 0;
    return buffer[0] | (buffer[1]<<8) | (buffer[2]<<16) | (buffer[3]<<24);
}

static inline ALushort read_le16(std::istream *file)
{
    ALubyte buffer[2];
    if(!file->read(reinterpret_cast<char*>(buffer), 2)) return 0;
    return buffer[0] | (buffer[1]<<8);
}

static inline ALuint read_be32(std::istream *file)
{
    ALubyte buffer[4];
    if(!file->read(reinterpret_cast<char*>(buffer), 4)) return 0;
    return (buffer[0]<<24) | (buffer[1]<<16) | (buffer[2]<<8) | buffer[3];
}

static inline ALushort read_be16(std::istream *file)
{
    ALubyte buffer[2];
    if(!file->read(reinterpret_cast<char*>(buffer), 2)) return 0;
    return (buffer[0]<<8) | buffer[1];
}

static inline ALuint read_be80extended(std::istream *file)
{
    ALubyte buffer[10];
    if(!file->read(reinterpret_cast<char*>(buffer), 10)) return 0;
    ALuint mantissa, last = 0;
    ALubyte exp = buffer[1];
    exp = 30 - exp;
    mantissa = (buffer[2]<<24) | (buffer[3]<<16) | (buffer[4]<<8) | buffer[5];
    while (exp--)
    {
        last = mantissa;
        mantissa >>= 1;
    }
    if((last&1)) mantissa++;
    return mantissa;
}


struct nullStream : public alureStream {
    virtual bool IsValid() { return false; }
    virtual bool GetFormat(ALenum*,ALuint*,ALuint*) { return false; }
    virtual ALuint GetData(ALubyte*,ALuint) { return 0; }
    virtual bool Rewind() { return false; }
    nullStream():alureStream(NULL) {}
};


struct customStream : public alureStream {
    void *usrFile;
    ALenum format;
    ALuint samplerate;
    ALuint blockAlign;
    MemDataInfo memInfo;

    UserCallbacks cb;

    virtual bool IsValid()
    { return usrFile != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        if(format == AL_NONE)
        {
            if(!cb.get_fmt || !cb.get_fmt(usrFile, &format, &samplerate, &blockAlign))
                return false;

            if(DetectBlockAlignment(format) != blockAlign)
                format = AL_NONE;
        }

        *fmt = format;
        *frequency = samplerate;
        *blockalign = blockAlign;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    { return cb.decode(usrFile, data, bytes); }

    virtual bool Rewind()
    {
        if(cb.rewind && cb.rewind(usrFile))
            return true;
        SetError("Rewind failed");
        return false;
    }

    customStream(const char *fname, const UserCallbacks &callbacks)
      : alureStream(NULL), usrFile(NULL), format(0), samplerate(0),
        blockAlign(0), cb(callbacks)
    { if(cb.open_file) usrFile = cb.open_file(fname); }

    customStream(const MemDataInfo &memData, const UserCallbacks &callbacks)
      : alureStream(NULL), usrFile(NULL), format(0), samplerate(0),
        blockAlign(0), memInfo(memData), cb(callbacks)
    { if(cb.open_mem) usrFile = cb.open_mem(memInfo.Data, memInfo.Length); }

    customStream(void *userdata, ALenum fmt, ALuint srate, const UserCallbacks &callbacks)
      : alureStream(NULL), usrFile(userdata), format(fmt), samplerate(srate),
        blockAlign(DetectBlockAlignment(format)), cb(callbacks)
    { }

    virtual ~customStream()
    {
        if(cb.close && usrFile)
            cb.close(usrFile);
        usrFile = NULL;
    }
};


struct wavStream : public alureStream {
    ALenum format;
    int samplerate;
    int blockAlign;
    int sampleSize;
    long dataStart;
    long dataLen;
    size_t remLen;

    virtual bool IsValid()
    { return (dataStart > 0 && format != AL_NONE); }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        *fmt = format;
        *frequency = samplerate;
        *blockalign = blockAlign;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        std::streamsize rem = ((remLen >= bytes) ? bytes : remLen) / blockAlign;
        fstream->read(reinterpret_cast<char*>(data), rem*blockAlign);

        std::streamsize got = fstream->gcount();
        got -= got%blockAlign;
        remLen -= got;

        if(BigEndian && sampleSize == 16)
        {
            for(std::streamsize i = 0;i < got;i+=2)
                swap(data[i], data[i+1]);
        }
        else if(BigEndian && sampleSize == 32)
        {
            for(std::streamsize i = 0;i < got;i+=4)
            {
                swap(data[i+0], data[i+3]);
                swap(data[i+1], data[i+2]);
            }
        }
        else if(BigEndian && sampleSize == 64)
        {
            for(std::streamsize i = 0;i < got;i+=8)
            {
                swap(data[i+0], data[i+7]);
                swap(data[i+1], data[i+6]);
                swap(data[i+2], data[i+5]);
                swap(data[i+3], data[i+4]);
            }
        }

        return got;
    }

    virtual bool Rewind()
    {
        fstream->clear();
        if(fstream->seekg(dataStart))
        {
            remLen = dataLen;
            return true;
        }

        SetError("Seek failed");
        return false;
    }

    wavStream(std::istream *_fstream)
      : alureStream(_fstream), format(0), dataStart(0)
    {
        ALubyte buffer[25];
        int length;

        if(!fstream->read(reinterpret_cast<char*>(buffer), 12) ||
           memcmp(buffer, "RIFF", 4) != 0 || memcmp(buffer+8, "WAVE", 4) != 0)
            return;

        while(!dataStart || format == AL_NONE)
        {
            char tag[4];
            if(!fstream->read(tag, 4))
                break;

            /* read chunk length */
            length = read_le32(fstream);

            if(memcmp(tag, "fmt ", 4) == 0 && length >= 16)
            {
                /* Data type (should be 1 for PCM data, 3 for float PCM data,
                 * and 17 for IMA4 data) */
                int type = read_le16(fstream);
                if(type != 0x0001 && type != 0x0003 && type != 0x0011)
                    break;

                /* mono or stereo data */
                int channels = read_le16(fstream);

                /* sample frequency */
                samplerate = read_le32(fstream);

                /* skip average bytes per second */
                fstream->ignore(4);

                /* bytes per block */
                blockAlign = read_le16(fstream);
                if(blockAlign == 0)
                    break;

                /* bits per sample */
                sampleSize = read_le16(fstream);

                length -= 16;

                /* Look for any extra data and try to find the format */
                int extrabytes = 0;
                if(length >= 2)
                {
                    extrabytes = read_le16(fstream);
                    length -= 2;
                }
                extrabytes = std::min(extrabytes, length);

                if(type == 0x0001)
                    format = GetSampleFormat(channels, sampleSize, false);
                else if(type == 0x0003)
                    format = GetSampleFormat(channels, sampleSize, true);
                else if(type == 0x0011 && extrabytes >= 2)
                {
                    int samples = read_le16(fstream);
                    length -= 2;

                    /* AL_EXT_IMA4 only supports 36 bytes-per-channel block
                     * alignment, which has 65 uncompressed sample frames */
                    if(blockAlign == 36*channels && samples == 65*channels &&
                       alIsExtensionPresent("AL_EXT_IMA4"))
                    {
                         if(channels == 1)
                             format = AL_FORMAT_MONO_IMA4;
                         else if(channels == 2)
                             format = AL_FORMAT_STEREO_IMA4;
                    }
                }
            }
            else if(memcmp(tag, "data", 4) == 0)
            {
                dataStart = fstream->tellg();
                dataLen = remLen = length;
            }

            fstream->seekg(length, std::ios_base::cur);
        }

        if(dataStart > 0 && format != AL_NONE)
            fstream->seekg(dataStart);
    }

    virtual ~wavStream()
    { }
};
static DecoderDecl<wavStream> wavStream_decoder;


struct aiffStream : public alureStream {
    ALenum format;
    int samplerate;
    int blockAlign;
    int sampleSize;
    long dataStart;
    long dataLen;
    size_t remLen;

    virtual bool IsValid()
    { return (dataStart > 0 && format != AL_NONE); }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        *fmt = format;
        *frequency = samplerate;
        *blockalign = blockAlign;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        std::streamsize rem = ((remLen >= bytes) ? bytes : remLen) / blockAlign;
        fstream->read(reinterpret_cast<char*>(data), rem*blockAlign);

        std::streamsize got = fstream->gcount();
        got -= got%blockAlign;
        remLen -= got;

        if(LittleEndian)
        {
            if(sampleSize == 2)
            {
                for(std::streamsize i = 0;i < got;i+=2)
                    swap(data[i], data[i+1]);
            }
            else if(sampleSize == 4)
            {
                for(std::streamsize i = 0;i < got;i+=4)
                {
                    swap(data[i+0], data[i+3]);
                    swap(data[i+1], data[i+2]);
                }
            }
        }

        return got;
    }

    virtual bool Rewind()
    {
        fstream->clear();
        if(fstream->seekg(dataStart))
        {
            remLen = dataLen;
            return true;
        }

        SetError("Seek failed");
        return false;
    }

    aiffStream(std::istream *_fstream)
      : alureStream(_fstream), format(0), dataStart(0)
    {
        ALubyte buffer[25];
        int length;

        if(!fstream->read(reinterpret_cast<char*>(buffer), 12) ||
           memcmp(buffer, "FORM", 4) != 0 || memcmp(buffer+8, "AIFF", 4) != 0)
            return;

        while(!dataStart || format == AL_NONE)
        {
            char tag[4];
            if(!fstream->read(tag, 4))
                break;

            /* read chunk length */
            length = read_be32(fstream);

            if(memcmp(tag, "COMM", 4) == 0 && length >= 18)
            {
                /* mono or stereo data */
                int channels = read_be16(fstream);

                /* number of sample frames */
                fstream->ignore(4);

                /* bits per sample */
                sampleSize = read_be16(fstream) / 8;

                /* sample frequency */
                samplerate = read_be80extended(fstream);

                /* block alignment */
                blockAlign = channels * sampleSize;

                format = GetSampleFormat(channels, sampleSize*8, false);

                length -= 18;
            }
            else if(memcmp(tag, "SSND", 4) == 0)
            {
                dataStart = fstream->tellg();
                dataStart += 8;
                dataLen = remLen = length - 8;
            }

            fstream->seekg(length, std::ios_base::cur);
        }

        if(dataStart > 0 && format != AL_NONE)
            fstream->seekg(dataStart);
    }

    virtual ~aiffStream()
    { }
};
static DecoderDecl<aiffStream> aiffStream_decoder;

#ifdef HAS_VORBISFILE
struct oggStream : public alureStream {
    OggVorbis_File oggFile;
    vorbis_info *oggInfo;
    int oggBitstream;
    ALenum format;

    virtual bool IsValid()
    { return oggInfo != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        if(format == AL_NONE)
            format = GetSampleFormat(oggInfo->channels, 16, false);
        *fmt = format;
        *frequency = oggInfo->rate;
        *blockalign = oggInfo->channels*2;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        ALuint got = 0;
        while(bytes > 0)
        {
            int res = pov_read(&oggFile, (char*)&data[got], bytes, BigEndian?1:0, 2, 1, &oggBitstream);
            if(res <= 0)
                break;
            bytes -= res;
            got += res;
        }
        // 1, 2, and 4 channel files decode into the same channel order as
        // OpenAL, however 6(5.1), 7(6.1), and 8(7.1) channel files need to be
        // re-ordered
        if(oggInfo->channels == 6)
        {
            ALshort *samples = (ALshort*)data;
            for(ALuint i = 0;i < got/sizeof(ALshort);i+=6)
            {
                // OpenAL : FL, FR, FC, LFE, RL, RR
                // Vorbis : FL, FC, FR,  RL, RR, LFE
                swap(samples[i+1], samples[i+2]);
                swap(samples[i+3], samples[i+5]);
                swap(samples[i+4], samples[i+5]);
            }
        }
        else if(oggInfo->channels == 7)
        {
            ALshort *samples = (ALshort*)data;
            for(ALuint i = 0;i < got/sizeof(ALshort);i+=7)
            {
                // OpenAL : FL, FR, FC, LFE, RC, SL, SR
                // Vorbis : FL, FC, FR,  SL, SR, RC, LFE
                swap(samples[i+1], samples[i+2]);
                swap(samples[i+3], samples[i+6]);
                swap(samples[i+4], samples[i+6]);
                swap(samples[i+5], samples[i+6]);
            }
        }
        else if(oggInfo->channels == 8)
        {
            ALshort *samples = (ALshort*)data;
            for(ALuint i = 0;i < got/sizeof(ALshort);i+=8)
            {
                // OpenAL : FL, FR, FC, LFE, RL, RR, SL, SR
                // Vorbis : FL, FC, FR,  SL, SR, RL, RR, LFE
                swap(samples[i+1], samples[i+2]);
                swap(samples[i+3], samples[i+7]);
                swap(samples[i+4], samples[i+5]);
                swap(samples[i+5], samples[i+6]);
                swap(samples[i+6], samples[i+7]);
            }
        }
        return got;
    }

    virtual bool Rewind()
    {
        if(pov_pcm_seek(&oggFile, 0) == 0)
            return true;

        SetError("Seek failed");
        return false;
    }

    oggStream(std::istream *_fstream)
      : alureStream(_fstream), oggInfo(NULL), oggBitstream(0), format(AL_NONE)
    {
        if(!vorbisfile_handle) return;

        const ov_callbacks streamIO = {
            read, seek, close, tell
        };

        if(pov_open_callbacks(this, &oggFile, NULL, 0, streamIO) == 0)
        {
            oggInfo = pov_info(&oggFile, -1);
            if(!oggInfo)
                pov_clear(&oggFile);
        }
    }

    virtual ~oggStream()
    {
        if(oggInfo)
            pov_clear(&oggFile);
        oggInfo = NULL;
    }

private:
    // libVorbisFile iostream callbacks
    static int seek(void *user_data, ogg_int64_t offset, int whence)
    {
        std::istream *stream = static_cast<oggStream*>(user_data)->fstream;
        stream->clear();

        if(whence == SEEK_CUR)
            stream->seekg(offset, std::ios_base::cur);
        else if(whence == SEEK_SET)
            stream->seekg(offset, std::ios_base::beg);
        else if(whence == SEEK_END)
            stream->seekg(offset, std::ios_base::end);
        else
            return -1;

        return stream->tellg();
    }

    static size_t read(void *ptr, size_t size, size_t nmemb, void *user_data)
    {
        std::istream *stream = static_cast<oggStream*>(user_data)->fstream;
        stream->clear();

        stream->read(static_cast<char*>(ptr), nmemb*size);
        size_t ret = stream->gcount();
        return ret/size;
    }

    static long tell(void *user_data)
    {
        std::istream *stream = static_cast<oggStream*>(user_data)->fstream;
        stream->clear();
        return stream->tellg();
    }

    static int close(void*)
    {
        return 0;
    }
};
static DecoderDecl<oggStream> oggStream_decoder;
#endif

#ifdef HAS_FLAC
struct flacStream : public alureStream {
    FLAC__StreamDecoder *flacFile;
    ALenum format;
    ALuint samplerate;
    ALuint blockAlign;
    ALboolean useFloat;

    std::vector<ALubyte> initialData;

    ALubyte *outBytes;
    ALuint outLen;
    ALuint outTotal;

    virtual bool IsValid()
    { return flacFile != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        *fmt = format;
        *frequency = samplerate;
        *blockalign = blockAlign;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        outBytes = data;
        outTotal = 0;
        outLen = bytes;

        if(initialData.size() > 0)
        {
            size_t rem = std::min(initialData.size(), (size_t)bytes);
            memcpy(data, &initialData[0], rem);
            outTotal += rem;
            initialData.erase(initialData.begin(), initialData.begin()+rem);
        }

        while(outTotal < bytes)
        {
            if(pFLAC__stream_decoder_process_single(flacFile) == false ||
               pFLAC__stream_decoder_get_state(flacFile) == FLAC__STREAM_DECODER_END_OF_STREAM)
                break;
        }

        return outTotal;
    }

    virtual bool Rewind()
    {
        if(pFLAC__stream_decoder_seek_absolute(flacFile, 0) != false)
        {
            initialData.clear();
            return true;
        }

        SetError("Seek failed");
        return false;
    }

    flacStream(std::istream *_fstream)
      : alureStream(_fstream), flacFile(NULL), format(AL_NONE), samplerate(0),
        blockAlign(0), useFloat(AL_FALSE)
    {
        if(!flac_handle) return;

        flacFile = pFLAC__stream_decoder_new();
        if(flacFile)
        {
            if(pFLAC__stream_decoder_init_stream(flacFile, ReadCallback, SeekCallback, TellCallback, LengthCallback, EofCallback, WriteCallback, MetadataCallback, ErrorCallback, this) == FLAC__STREAM_DECODER_INIT_STATUS_OK)
            {
                if(InitFlac())
                {
                    // all ok
                    return;
                }

                pFLAC__stream_decoder_finish(flacFile);
            }
            pFLAC__stream_decoder_delete(flacFile);
            flacFile = NULL;
        }
    }

    virtual ~flacStream()
    {
        if(flacFile)
        {
            pFLAC__stream_decoder_finish(flacFile);
            pFLAC__stream_decoder_delete(flacFile);
            flacFile = NULL;
        }
    }

private:
    bool InitFlac()
    {
        // We need to decode some data to be able to get the channel count, bit
        // depth, and sample rate. It also ensures the file has FLAC data, as
        // the FLAC__stream_decoder_init_* functions can succeed on non-FLAC
        // Ogg files.
        outLen = 0;
        outTotal = 0;
        while(initialData.size() == 0)
        {
            if(pFLAC__stream_decoder_process_single(flacFile) == false ||
               pFLAC__stream_decoder_get_state(flacFile) == FLAC__STREAM_DECODER_END_OF_STREAM)
                break;
        }

        if(initialData.size() > 0)
            return true;
        return false;
    }

    static FLAC__StreamDecoderWriteStatus WriteCallback(const FLAC__StreamDecoder*, const FLAC__Frame *frame, const FLAC__int32 *const buffer[], void *client_data)
    {
        flacStream *self = static_cast<flacStream*>(client_data);
        ALubyte *data = self->outBytes + self->outTotal;
        ALuint i = 0;

        if(self->format == AL_NONE)
        {
            ALuint bps = frame->header.bits_per_sample;
            if(bps == 24 || bps == 32)
            {
                self->format = GetSampleFormat(frame->header.channels, 32, true);
                if(self->format != AL_NONE)
                {
                    self->useFloat = AL_TRUE;
                    bps = 32;
                }
                else bps = 16;
            }
            if(self->format == AL_NONE)
                self->format = GetSampleFormat(frame->header.channels, bps, false);
            self->blockAlign = frame->header.channels * bps/8;
            self->samplerate = frame->header.sample_rate;
        }

        const ALboolean useFloat = self->useFloat;
        while(self->outTotal < self->outLen && i < frame->header.blocksize)
        {
            for(ALuint c = 0;c < frame->header.channels;c++)
            {
                if(frame->header.bits_per_sample == 8)
                    ((ALubyte*)data)[c] = buffer[c][i]+128;
                else if(frame->header.bits_per_sample == 16)
                    ((ALshort*)data)[c] = buffer[c][i];
                else if(frame->header.bits_per_sample == 24)
                {
                    if(useFloat)
                        ((ALfloat*)data)[c] = ((buffer[c][i]>=0) ?
                                               buffer[c][i]/(float)0x7FFFFF :
                                               buffer[c][i]/(float)0x800000);
                    else
                        ((ALshort*)data)[c] = buffer[c][i]>>8;
                }
                else if(frame->header.bits_per_sample == 32)
                {
                    if(useFloat)
                        ((ALfloat*)data)[c] = ((buffer[c][i]>=0) ?
                                               buffer[c][i]/(float)0x7FFFFFFF :
                                               buffer[c][i]/(float)0x80000000u);
                    else
                        ((ALshort*)data)[c] = buffer[c][i]>>16;
                }
            }
            self->outTotal += self->blockAlign;
            data += self->blockAlign;
            i++;
        }

        if(i < frame->header.blocksize)
        {
            ALuint blocklen = (frame->header.blocksize-i) *
                              self->blockAlign;
            ALuint start = self->initialData.size();

            self->initialData.resize(start+blocklen);
            data = &self->initialData[start];

            do {
                for(ALuint c = 0;c < frame->header.channels;c++)
                {
                    if(frame->header.bits_per_sample == 8)
                        ((ALubyte*)data)[c] = buffer[c][i]+128;
                    else if(frame->header.bits_per_sample == 16)
                        ((ALshort*)data)[c] = buffer[c][i];
                    else if(frame->header.bits_per_sample == 24)
                    {
                        if(useFloat)
                            ((ALfloat*)data)[c] = ((buffer[c][i]>=0) ?
                                                   buffer[c][i]/(float)0x7FFFFF :
                                                   buffer[c][i]/(float)0x800000);
                        else
                            ((ALshort*)data)[c] = buffer[c][i]>>8;
                    }
                    else if(frame->header.bits_per_sample == 32)
                    {
                        if(useFloat)
                            ((ALfloat*)data)[c] = ((buffer[c][i]>=0) ?
                                                   buffer[c][i]/(float)0x7FFFFFFF :
                                                   buffer[c][i]/(float)0x80000000u);
                        else
                            ((ALshort*)data)[c] = buffer[c][i]>>16;
                    }
                }
                data += self->blockAlign;
                i++;
            } while(i < frame->header.blocksize);
        }

        return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
    }
    static void MetadataCallback(const FLAC__StreamDecoder*,const FLAC__StreamMetadata*,void*)
    {
    }
    static void ErrorCallback(const FLAC__StreamDecoder*,FLAC__StreamDecoderErrorStatus,void*)
    {
    }

    static FLAC__StreamDecoderReadStatus ReadCallback(const FLAC__StreamDecoder*, FLAC__byte buffer[], size_t *bytes, void *client_data)
    {
        std::istream *stream = static_cast<flacStream*>(client_data)->fstream;
        stream->clear();

        if(*bytes <= 0)
            return FLAC__STREAM_DECODER_READ_STATUS_ABORT;

        stream->read(reinterpret_cast<char*>(buffer), *bytes);
        *bytes = stream->gcount();
        if(*bytes == 0 && stream->eof())
            return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;

        return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
    }
    static FLAC__StreamDecoderSeekStatus SeekCallback(const FLAC__StreamDecoder*, FLAC__uint64 absolute_byte_offset, void *client_data)
    {
        std::istream *stream = static_cast<flacStream*>(client_data)->fstream;
        stream->clear();

        if(!stream->seekg(absolute_byte_offset))
            return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;
        return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
    }
    static FLAC__StreamDecoderTellStatus TellCallback(const FLAC__StreamDecoder*, FLAC__uint64 *absolute_byte_offset, void *client_data)
    {
        std::istream *stream = static_cast<flacStream*>(client_data)->fstream;
        stream->clear();

        *absolute_byte_offset = stream->tellg();
        return FLAC__STREAM_DECODER_TELL_STATUS_OK;
    }
    static FLAC__StreamDecoderLengthStatus LengthCallback(const FLAC__StreamDecoder*, FLAC__uint64 *stream_length, void *client_data)
    {
        std::istream *stream = static_cast<flacStream*>(client_data)->fstream;
        stream->clear();

        std::streampos pos = stream->tellg();
        if(stream->seekg(0, std::ios_base::end))
        {
            *stream_length = stream->tellg();
            stream->seekg(pos);
        }

        if(!stream->good())
            return FLAC__STREAM_DECODER_LENGTH_STATUS_ERROR;
        return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
    }
    static FLAC__bool EofCallback(const FLAC__StreamDecoder*, void *client_data)
    {
        std::istream *stream = static_cast<flacStream*>(client_data)->fstream;
        return (stream->eof()) ? true : false;
    }
};
static DecoderDecl<flacStream> flacStream_decoder;
#endif

#ifdef HAS_FLUIDSYNTH
struct fluidStream : public alureStream {
private:
    static const ALubyte MIDI_CHANNEL_MASK = 0x0F;
    static const ALubyte MIDI_EVENT_MASK   = 0xF0;

    static const ALubyte MIDI_NOTEOFF    = 0x80;    // + note + velocity
    static const ALubyte MIDI_NOTEON     = 0x90;    // + note + velocity
    static const ALubyte MIDI_POLYPRESS  = 0xA0;    // + pressure (2 bytes)
    static const ALubyte MIDI_CTRLCHANGE = 0xB0;    // + ctrl + value
    static const ALubyte MIDI_PRGMCHANGE = 0xC0;    // + new patch
    static const ALubyte MIDI_CHANPRESS  = 0xD0;    // + pressure (1 byte)
    static const ALubyte MIDI_PITCHBEND  = 0xE0;    // + pitch bend (2 bytes)
    static const ALubyte MIDI_SPECIAL    = 0xF0;    // Special event

    static const ALubyte MIDI_SYSEX    = 0xF0;      // SysEx begin
    static const ALubyte MIDI_SYSEXEND = 0xF7;      // SysEx end
    static const ALubyte MIDI_SONGPOS  = 0xF2;      // Song position
    static const ALubyte MIDI_SONGSEL  = 0xF3;      // Song select
    static const ALubyte MIDI_META     = 0xFF;      // Meta event begin

    static const ALubyte MIDI_META_EOT   = 0x2F;    // End-of-track
    static const ALubyte MIDI_META_TEMPO = 0x51;    // Tempo change

    struct MidiTrack {
        std::vector<ALubyte> data;
        size_t Offset;
        ALubyte LastEvent;
        ALdouble SamplesLeft;

        MidiTrack() : Offset(0), LastEvent(0), SamplesLeft(0.)
        { }
        MidiTrack(const MidiTrack &rhs)
          : data(rhs.data), Offset(rhs.Offset), LastEvent(rhs.LastEvent),
            SamplesLeft(rhs.SamplesLeft)
        { }

        void Reset()
        {
            Offset = 0;
            LastEvent = 0;
            SamplesLeft = 0.;
        }

        const MidiTrack& operator=(const MidiTrack &rhs)
        {
            data = rhs.data;
            Offset = rhs.Offset;
            LastEvent = rhs.LastEvent;
            SamplesLeft = rhs.SamplesLeft;
            return *this;
        }

        unsigned long ReadVarLen()
        {
            if(Offset >= data.size())
                return 0;

            unsigned long len = data[Offset]&0x7F;
            while((data[Offset]&0x80))
            {
                if(++Offset >= data.size())
                    return 0;
                len = (len<<7) | (data[Offset]&0x7F);
            }
            Offset++;

            return len;
        }
    };

    ALuint Divisions;
    std::vector<MidiTrack> Tracks;

    ALenum format;
    ALsizei sampleRate;
    ALdouble samplesPerTick;

    fluid_settings_t *fluidSettings;
    fluid_synth_t *fluidSynth;
    int fontID;

public:
    virtual bool IsValid()
    { return fluidSynth != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        if(format == AL_NONE)
        {
            format = GetSampleFormat(2, 32, true);
            if(format == AL_NONE)
                format = AL_FORMAT_STEREO16;
        }
        *fmt = format;
        *frequency = sampleRate;
        *blockalign = 2 * ((format==AL_FORMAT_STEREO16) ? sizeof(ALshort) :
                                                          sizeof(ALfloat));
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        ALuint ret;

        if(format == AL_FORMAT_STEREO16)
        {
            ALshort *ptr = reinterpret_cast<ALshort*>(data);
            ret = FillBuffer(ptr, bytes/2/sizeof(ALshort));
            ret *= 2 * sizeof(ALshort);
        }
        else
        {
            ALfloat *ptr = reinterpret_cast<ALfloat*>(data);
            ret = FillBuffer(ptr, bytes/2/sizeof(ALfloat));
            ret *= 2 * sizeof(ALfloat);
        }

        return ret;
    }

    virtual bool Rewind()
    {
        for(std::vector<MidiTrack>::iterator i = Tracks.begin(), end = Tracks.end();i != end;i++)
        {
            i->Reset();
            unsigned long val = i->ReadVarLen();
            i->SamplesLeft += val * samplesPerTick;
        }
        pfluid_synth_program_reset(fluidSynth);
        UpdateTempo(500000);
        return true;
    }

    virtual bool SetPatchset(const char *sfont)
    {
        int newid = pfluid_synth_sfload(fluidSynth, sfont, true);
        if(newid == FLUID_FAILED)
        {
            SetError("Failed to load soundfont");
            return false;
        }

        if(fontID != FLUID_FAILED)
            pfluid_synth_sfunload(fluidSynth, fontID, true);
        fontID = newid;

        return true;
    }

    fluidStream(std::istream *_fstream)
      : alureStream(_fstream), Divisions(100),
        format(AL_NONE), sampleRate(48000), samplesPerTick(1.),
        fluidSettings(NULL), fluidSynth(NULL), fontID(FLUID_FAILED)
    {
        if(!fsynth_handle) return;

        ALCdevice *device = alcGetContextsDevice(alcGetCurrentContext());
        if(device)
            alcGetIntegerv(device, ALC_FREQUENCY, 1, &sampleRate);

        char hdr[4];
        if(!fstream->read(hdr, 4))
            return;

        if(memcmp(hdr, "MThd", 4) == 0)
        {
            ALuint len = read_be32(fstream);
            if(len != 6)
                return;

            int type = read_be16(fstream);
            if(type != 0 && type != 1)
                return;

            ALuint numtracks = read_be16(fstream);

            Divisions = read_be16(fstream);
            UpdateTempo(500000);

            Tracks.resize(numtracks);
            for(std::vector<MidiTrack>::iterator i = Tracks.begin(), end = Tracks.end();i != end;i++)
            {
                if(!fstream->read(hdr, 4) || memcmp(hdr, "MTrk", 4) != 0)
                    return;

                ALuint len = read_be32(fstream);
                i->data.resize(len);
                if(!fstream->read(reinterpret_cast<char*>(&i->data[0]), len))
                    return;

                unsigned long val = i->ReadVarLen();
                i->SamplesLeft += val * samplesPerTick;
            }
            SetupSynth();
        }
    }

    virtual ~fluidStream()
    {
        if(fontID != FLUID_FAILED)
            pfluid_synth_sfunload(fluidSynth, fontID, true);
        fontID = FLUID_FAILED;

        if(fluidSynth != NULL)
            pdelete_fluid_synth(fluidSynth);
        fluidSynth = NULL;

        if(fluidSettings != NULL)
            pdelete_fluid_settings(fluidSettings);
        fluidSettings = NULL;
    }

private:
    template<typename T>
    ALuint FillBuffer(T *Buffer, ALuint BufferSamples)
    {
        ALuint SamplesInBuffer = 0;
        while(SamplesInBuffer < BufferSamples)
        {
            // Check if any tracks are still playing and how many samples are waiting to render
            size_t TracksPlaying = 0;
            ALuint SamplesToDo = BufferSamples - SamplesInBuffer;
            for(std::vector<MidiTrack>::iterator i = Tracks.begin(),
                                                 end = Tracks.end();i != end;i++)
            {
                if(i->Offset < i->data.size())
                {
                    SamplesToDo = std::min<ALuint>(SamplesToDo, i->SamplesLeft);
                    TracksPlaying++;
                }
            }
            if(TracksPlaying == 0)
                break;

            if(SamplesToDo == 0)
            {
                ProcessMidi();
                continue;
            }

            // Render samples
            WriteSamples(SamplesToDo, Buffer);
            Buffer += SamplesToDo*2;
            SamplesInBuffer += SamplesToDo;

            for(std::vector<MidiTrack>::iterator i = Tracks.begin(),
                                                 end = Tracks.end();i != end;i++)
            {
                if(i->Offset < i->data.size())
                    i->SamplesLeft -= SamplesToDo;
            }
        }

        return SamplesInBuffer;
    }

    void WriteSamples(ALuint count, short *buffer)
    { pfluid_synth_write_s16(fluidSynth, count, buffer, 0, 2, buffer, 1, 2); }
    void WriteSamples(ALuint count, float *buffer)
    { pfluid_synth_write_float(fluidSynth, count, buffer, 0, 2, buffer, 1, 2); }

    void ProcessMidi()
    {
        ALuint newtempo = 0;

        // Process more events
        std::vector<MidiTrack>::iterator i=Tracks.begin(), end=Tracks.end();
        while(i != end)
        {
            if(i->Offset >= i->data.size() || i->SamplesLeft >= 1.)
            {
                i++;
                continue;
            }

            if(i->data.size() - i->Offset < 3)
            {
                i->Offset = i->data.size();
                i++;
                continue;
            }

            ALubyte event = i->data[i->Offset++];
            ALubyte parm1, parm2;
            if(!(event&0x80))
            {
                event = i->LastEvent;
                i->Offset--;
            }
            if((event&MIDI_EVENT_MASK) != MIDI_SPECIAL)
                i->LastEvent = event;
            parm1 = i->data[i->Offset];
            parm2 = i->data[i->Offset+1];

            int channel = event&MIDI_CHANNEL_MASK;
            switch(event&MIDI_EVENT_MASK)
            {
                case MIDI_NOTEOFF:
                    pfluid_synth_noteoff(fluidSynth, channel, parm1);
                    i->Offset += 2;
                    break;
                case MIDI_NOTEON:
                    pfluid_synth_noteon(fluidSynth, channel, parm1, parm2);
                    i->Offset += 2;
                    break;
                case MIDI_POLYPRESS:
                    i->Offset += 2;
                    break;

                case MIDI_CTRLCHANGE:
                    pfluid_synth_cc(fluidSynth, channel, parm1, parm2);
                    i->Offset += 2;
                    break;
                case MIDI_PRGMCHANGE:
                    pfluid_synth_program_change(fluidSynth, channel, parm1);
                    i->Offset += 1;
                    break;

                case MIDI_CHANPRESS:
                    pfluid_synth_channel_pressure(fluidSynth, channel, parm1);
                    i->Offset += 1;
                    break;

                case MIDI_PITCHBEND:
                    pfluid_synth_pitch_bend(fluidSynth, channel, (parm1&0x7F) | ((parm2&0x7F)<<7));
                    i->Offset += 2;
                    break;

                case MIDI_SPECIAL:
                    switch(event)
                    {
                        case MIDI_SYSEX:
                        {
                            unsigned long len = i->ReadVarLen();
                            if(i->data.size() - i->Offset < len)
                            {
                                i->Offset = i->data.size();
                                break;
                            }

                            if(len > 1 && i->data[len-1] == MIDI_SYSEXEND)
                            {
                                char *data = reinterpret_cast<char*>(&i->data[i->Offset]);
                                pfluid_synth_sysex(fluidSynth, data, len-1, NULL, NULL, NULL, false);
                            }
                            i->Offset += len;
                            break;
                        }
                        case MIDI_SYSEXEND:
                        {
                            unsigned long len = i->ReadVarLen();
                            if(i->data.size() - i->Offset < len)
                            {
                                i->Offset = i->data.size();
                                break;
                            }
                            i->Offset += len;
                            break;
                        }

                        case MIDI_SONGPOS:
                            i->Offset += 2;
                            break;

                        case MIDI_SONGSEL:
                            i->Offset += 1;
                            break;

                        case MIDI_META:
                        {
                            ALubyte metatype = i->data[i->Offset++];
                            unsigned long val = i->ReadVarLen();

                            if(i->data.size() - i->Offset < val)
                            {
                                i->Offset = i->data.size();
                                break;
                            }

                            if(metatype == MIDI_META_EOT)
                            {
                                i->Offset = i->data.size();
                                break;
                            }

                            if(metatype == MIDI_META_TEMPO && val >= 3)
                            {
                                newtempo = (i->data[i->Offset] << 16) |
                                           (i->data[i->Offset+1] << 8) |
                                           (i->data[i->Offset+2]);
                            }

                            i->Offset += val;
                            break;
                        }

                        default:
                            /* The rest of the special events don't have any
                             * data bytes */
                            break;
                    }
                    break;

                default:
                    /* Shouldn't ever get to here */
                    break;
            }

            unsigned long val = i->ReadVarLen();
            i->SamplesLeft += val * samplesPerTick;
        }
        if(newtempo)
            UpdateTempo(newtempo);
    }

    void UpdateTempo(ALuint tempo)
    {
        ALdouble sampletickrate = sampleRate / (1000000. / tempo) / Divisions;

        for(std::vector<MidiTrack>::iterator i = Tracks.begin(),
                                             end = Tracks.end();i != end;i++)
        {
            if(i->Offset >= i->data.size())
                continue;
            i->SamplesLeft = i->SamplesLeft / samplesPerTick * sampletickrate;
        }
        samplesPerTick = sampletickrate;
    }

    void SetupSynth()
    {
        fluidSettings = pnew_fluid_settings();
        if(fluidSettings)
        {
            pfluid_settings_setnum(fluidSettings, "synth.gain", 0.5);
            pfluid_settings_setstr(fluidSettings, "synth.reverb.active", "yes");
            pfluid_settings_setstr(fluidSettings, "synth.chorus.active", "yes");
            pfluid_settings_setint(fluidSettings, "synth.polyphony", 256);
            pfluid_settings_setnum(fluidSettings, "synth.sample-rate", (double)sampleRate);

            fluidSynth = pnew_fluid_synth(fluidSettings);
            if(fluidSynth)
            {
                const char *soundfont = getenv("FLUID_SOUNDFONT");
                if(soundfont && soundfont[0])
                    fontID = pfluid_synth_sfload(fluidSynth, soundfont, true);
            }
        }
    }
};
static DecoderDecl<fluidStream> fluidStream_decoder;
#endif

#ifdef HAS_SNDFILE
struct sndStream : public alureStream {
    SNDFILE *sndFile;
    SF_INFO sndInfo;
    ALenum format;

    virtual bool IsValid()
    { return sndFile != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        if(format == AL_NONE)
            format = GetSampleFormat(sndInfo.channels, 16, false);
        *fmt = format;
        *frequency = sndInfo.samplerate;
        *blockalign = sndInfo.channels*2;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        const ALuint frameSize = 2*sndInfo.channels;
        return psf_readf_short(sndFile, (short*)data, bytes/frameSize) * frameSize;
    }

    virtual bool Rewind()
    {
        if(psf_seek(sndFile, 0, SEEK_SET) != -1)
            return true;

        SetError("Seek failed");
        return false;
    }

    sndStream(std::istream *_fstream)
      : alureStream(_fstream), sndFile(NULL), format(AL_NONE)
    {
        memset(&sndInfo, 0, sizeof(sndInfo));

        if(!sndfile_handle) return;

        static SF_VIRTUAL_IO streamIO = {
            get_filelen, seek,
            read, write, tell
        };
        sndFile = psf_open_virtual(&streamIO, SFM_READ, &sndInfo, this);
    }

    virtual ~sndStream()
    {
        if(sndFile)
            psf_close(sndFile);
        sndFile = NULL;
    }

private:
    // libSndFile iostream callbacks
    static sf_count_t get_filelen(void *user_data)
    {
        std::istream *stream = static_cast<sndStream*>(user_data)->fstream;
        stream->clear();

        std::streampos len = -1;
        std::streampos pos = stream->tellg();
        if(stream->seekg(0, std::ios_base::end))
        {
            len = stream->tellg();
            stream->seekg(pos);
        }

        return len;
    }

    static sf_count_t seek(sf_count_t offset, int whence, void *user_data)
    {
        std::istream *stream = static_cast<sndStream*>(user_data)->fstream;
        stream->clear();

        if(whence == SEEK_CUR)
            stream->seekg(offset, std::ios_base::cur);
        else if(whence == SEEK_SET)
            stream->seekg(offset, std::ios_base::beg);
        else if(whence == SEEK_END)
            stream->seekg(offset, std::ios_base::end);
        else
            return -1;

        return stream->tellg();
    }

    static sf_count_t read(void *ptr, sf_count_t count, void *user_data)
    {
        std::istream *stream = static_cast<sndStream*>(user_data)->fstream;
        stream->clear();
        stream->read(static_cast<char*>(ptr), count);
        return stream->gcount();
    }

    static sf_count_t write(const void*, sf_count_t, void*)
    { return -1; }

    static sf_count_t tell(void *user_data)
    {
        std::istream *stream = static_cast<sndStream*>(user_data)->fstream;
        stream->clear();
        return stream->tellg();
    }
};
static DecoderDecl<sndStream> sndStream_decoder;
#endif

#ifdef HAS_DUMB
struct dumbStream : public alureStream {
    DUMBFILE_SYSTEM vfs;
    DUMBFILE *dumbFile;
    DUH *duh;
    DUH_SIGRENDERER *renderer;
    std::vector<sample_t> sampleBuf;
    ALuint lastOrder;
    ALenum format;
    ALCint samplerate;

    virtual bool IsValid()
    { return renderer != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        if(format == AL_NONE)
        {
            format = GetSampleFormat(2, 32, true);
            if(format == AL_NONE)
                format = AL_FORMAT_STEREO16;
        }
        *fmt = format;
        *frequency = samplerate;
        *blockalign = 2 * ((format==AL_FORMAT_STEREO16) ? sizeof(ALshort) :
                                                          sizeof(ALfloat));
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        ALuint ret = 0;

        if(pdumb_it_sr_get_speed(pduh_get_it_sigrenderer(renderer)) == 0)
            return 0;

        ALuint sample_count = bytes / ((format==AL_FORMAT_STEREO16) ?
                                       sizeof(ALshort) : sizeof(ALfloat));

        sampleBuf.resize(sample_count);
        sample_t *samples[] = {
            &sampleBuf[0]
        };

        pdumb_silence(samples[0], sample_count);
        ret = pduh_sigrenderer_generate_samples(renderer, 1.0f, 65536.0f/samplerate, sample_count/2, samples);
        ret *= 2;
        if(format == AL_FORMAT_STEREO16)
        {
            for(ALuint i = 0;i < ret;i++)
                ((ALshort*)data)[i] = clamp(samples[0][i]>>8, -32768, 32767);
        }
        else
        {
            for(ALuint i = 0;i < ret;i++)
                ((ALfloat*)data)[i] = ((samples[0][i]>=0) ?
                                       samples[0][i]/(float)0x7FFFFF :
                                       samples[0][i]/(float)0x800000);
        }
        ret *= ((format==AL_FORMAT_STEREO16) ? sizeof(ALshort) : sizeof(ALfloat));

        return ret;
    }

    virtual bool Rewind()
    {
        DUH_SIGRENDERER *newrenderer = pdumb_it_start_at_order(duh, 2, lastOrder);
        if(!newrenderer)
        {
            SetError("Could not start renderer");
            return false;
        }
        pduh_end_sigrenderer(renderer);
        renderer = newrenderer;
        return true;
    }

    virtual bool SetOrder(ALuint order)
    {
        DUH_SIGRENDERER *newrenderer = pdumb_it_start_at_order(duh, 2, order);
        if(!newrenderer)
        {
            SetError("Could not set order");
            return false;
        }
        pduh_end_sigrenderer(renderer);
        renderer = newrenderer;

        lastOrder = order;
        return true;
    }

    dumbStream(std::istream *_fstream)
      : alureStream(_fstream), dumbFile(NULL), duh(NULL), renderer(NULL),
        lastOrder(0), format(AL_NONE), samplerate(48000)
    {
        if(!dumb_handle) return;

        ALCdevice *device = alcGetContextsDevice(alcGetCurrentContext());
        if(device)
            alcGetIntegerv(device, ALC_FREQUENCY, 1, &samplerate);

        DUH* (*funcs[])(DUMBFILE*) = {
            pdumb_read_it,
            pdumb_read_xm,
            pdumb_read_s3m,
            pdumb_read_mod,
            NULL
        };

        vfs.open = NULL;
        vfs.skip = skip;
        vfs.getc = read_char;
        vfs.getnc = read;
        vfs.close = NULL;

        for(size_t i = 0;funcs[i];i++)
        {
            dumbFile = pdumbfile_open_ex(this, &vfs);
            if(dumbFile)
            {
                duh = funcs[i](dumbFile);
                if(duh)
                {
                    renderer = pdumb_it_start_at_order(duh, 2, lastOrder);
                    if(renderer)
                    {
                        pdumb_it_set_loop_callback(pduh_get_it_sigrenderer(renderer), loop_cb, this);
                        break;
                    }

                    punload_duh(duh);
                    duh = NULL;
                }

                pdumbfile_close(dumbFile);
                dumbFile = NULL;
            }
            fstream->clear();
            fstream->seekg(0);
        }
    }

    virtual ~dumbStream()
    {
        if(renderer)
            pduh_end_sigrenderer(renderer);
        renderer = NULL;

        if(duh)
            punload_duh(duh);
        duh = NULL;

        if(dumbFile)
            pdumbfile_close(dumbFile);
        dumbFile = NULL;
    }

private:
    // DUMBFILE iostream callbacks
    static int skip(void *user_data, long offset)
    {
        std::istream *stream = static_cast<dumbStream*>(user_data)->fstream;
        stream->clear();

        if(stream->seekg(offset, std::ios_base::cur))
            return 0;
        return -1;
    }

    static long read(char *ptr, long size, void *user_data)
    {
        std::istream *stream = static_cast<dumbStream*>(user_data)->fstream;
        stream->clear();

        stream->read(ptr, size);
        return stream->gcount();
    }

    static int read_char(void *user_data)
    {
        std::istream *stream = static_cast<dumbStream*>(user_data)->fstream;
        stream->clear();

        unsigned char ret;
        stream->read(reinterpret_cast<char*>(&ret), 1);
        if(stream->gcount() > 0)
            return ret;
        return -1;
    }

    static int loop_cb(void *user_data)
    {
        dumbStream *self = static_cast<dumbStream*>(user_data);
        pdumb_it_sr_set_speed(pduh_get_it_sigrenderer(self->renderer), 0);
        return 0;
    }
};
static DecoderDecl<dumbStream> dumbStream_decoder;
#endif

#ifdef HAS_MODPLUG
struct modStream : public alureStream {
    ModPlugFile *modFile;
    int lastOrder;

    virtual bool IsValid()
    { return modFile != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        *fmt = AL_FORMAT_STEREO16;
        *frequency = 44100;
        *blockalign = 2 * sizeof(ALshort);
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        int ret = pModPlug_Read(modFile, data, bytes);
        if(ret < 0) return 0;
        return ret;
    }

    virtual bool Rewind()
    { return SetOrder(lastOrder); }

    virtual bool SetOrder(ALuint order)
    {
        std::vector<char> data(16384);
        ALuint total = 0;
        while(total < 2*1024*1024)
        {
            fstream->read(&data[total], data.size()-total);
            if(fstream->gcount() == 0) break;
            total += fstream->gcount();
            data.resize(total*2);
        }
        data.resize(total);

        ModPlugFile *newMod = pModPlug_Load(&data[0], data.size());
        if(!newMod)
        {
            SetError("Could not reload data");
            return false;
        }
        pModPlug_Unload(modFile);
        modFile = newMod;

        // There seems to be no way to tell if the seek succeeds
        pModPlug_SeekOrder(modFile, order);
        lastOrder = order;

        return true;
    }

    modStream(std::istream *_fstream)
      : alureStream(_fstream), modFile(NULL), lastOrder(0)
    {
        if(!mod_handle) return;

        std::vector<char> data(16384);
        ALuint total = 0;
        while(total < 2*1024*1024)
        {
            fstream->read(&data[total], data.size()-total);
            if(fstream->gcount() == 0) break;
            total += fstream->gcount();
            data.resize(total*2);
        }
        data.resize(total);

        modFile = pModPlug_Load(&data[0], data.size());
    }

    virtual ~modStream()
    {
        if(modFile)
            pModPlug_Unload(modFile);
        modFile = NULL;
    }
};
static DecoderDecl<modStream> modStream_decoder;
#endif

#ifdef HAS_MPG123
struct mp3Stream : public alureStream {
    mpg123_handle *mp3File;
    long samplerate;
    int channels;
    ALenum format;
    std::ios::pos_type dataStart;
    std::ios::pos_type dataEnd;

    virtual bool IsValid()
    { return mp3File != NULL; }

    virtual bool GetFormat(ALenum *fmt, ALuint *frequency, ALuint *blockalign)
    {
        *fmt = format;
        *frequency = samplerate;
        *blockalign = channels*2;
        return true;
    }

    virtual ALuint GetData(ALubyte *data, ALuint bytes)
    {
        ALuint amt = 0;
        while(bytes > 0)
        {
            size_t got = 0;
            int ret = pmpg123_read(mp3File, data, bytes, &got);

            bytes -= got;
            data += got;
            amt += got;

            if(ret == MPG123_NEW_FORMAT)
            {
                long newrate;
                int newchans, enc;
                pmpg123_getformat(mp3File, &newrate, &newchans, &enc);
                continue;
            }
            if(ret == MPG123_NEED_MORE)
            {
                unsigned char data[4096];
                ALint insize = std::min((ALint)sizeof(data),
                                        (ALint)(dataEnd-fstream->tellg()));
                if(insize > 0)
                {
                    fstream->read((char*)data, insize);
                    insize = fstream->gcount();
                }
                if(insize > 0 && pmpg123_feed(mp3File, data, insize) == MPG123_OK)
                    continue;
            }
            if(got == 0)
                break;
        }
        return amt;
    }

    virtual bool Rewind()
    {
        fstream->clear();
        std::istream::pos_type oldpos = fstream->tellg();
        fstream->seekg(dataStart);

        mpg123_handle *newFile = pmpg123_new(NULL, NULL);
        if(pmpg123_open_feed(newFile) == MPG123_OK)
        {
            unsigned char data[4096];
            long newrate;
            int newchans;
            int enc;

            ALuint amt, total = 0;
            int ret = MPG123_OK;
            do {
                amt = std::min((ALint)sizeof(data),
                               (ALint)(dataEnd-fstream->tellg()));
                fstream->read((char*)data, amt);
                amt = fstream->gcount();
                if(amt == 0)  break;
                total += amt;
                ret = pmpg123_decode(newFile, data, amt, NULL, 0, NULL);
            } while(ret == MPG123_NEED_MORE && total < 64*1024);

            if(ret == MPG123_NEW_FORMAT &&
               pmpg123_getformat(newFile, &newrate, &newchans, &enc) == MPG123_OK)
            {
                if(pmpg123_format_none(newFile) == MPG123_OK &&
                   pmpg123_format(newFile, samplerate, channels, MPG123_ENC_SIGNED_16) == MPG123_OK)
                {
                    // All OK
                    pmpg123_delete(mp3File);
                    mp3File = newFile;
                    return true;
                }
            }
            pmpg123_delete(newFile);
        }

        fstream->seekg(oldpos);
        SetError("Restart failed");
        return false;
    }

    mp3Stream(std::istream *_fstream)
      : alureStream(_fstream), mp3File(NULL), format(AL_NONE),
        dataStart(0), dataEnd(0)
    {
        if(!mp123_handle) return;

        if(!FindDataChunk())
            return;

        mp3File = pmpg123_new(NULL, NULL);
        if(pmpg123_open_feed(mp3File) == MPG123_OK)
        {
            unsigned char data[4096];
            int enc;

            ALuint amt, total = 0;
            int ret = MPG123_OK;
            do {
                amt = std::min((ALint)sizeof(data),
                               (ALint)(dataEnd-fstream->tellg()));
                fstream->read((char*)data, amt);
                amt = fstream->gcount();
                if(amt == 0)  break;
                total += amt;
                ret = pmpg123_decode(mp3File, data, amt, NULL, 0, NULL);
            } while(ret == MPG123_NEED_MORE && total < 64*1024);

            if(ret == MPG123_NEW_FORMAT &&
               pmpg123_getformat(mp3File, &samplerate, &channels, &enc) == MPG123_OK)
            {
                format = GetSampleFormat(channels, 16, false);
                if(pmpg123_format_none(mp3File) == MPG123_OK &&
                   pmpg123_format(mp3File, samplerate, channels, MPG123_ENC_SIGNED_16) == MPG123_OK)
                {
                    // All OK
                    return;
                }
            }
        }
        pmpg123_delete(mp3File);
        mp3File = NULL;
    }

    virtual ~mp3Stream()
    {
        if(mp3File)
            pmpg123_delete(mp3File);
        mp3File = NULL;
    }

private:
    bool FindDataChunk()
    {
        ALubyte buffer[25];
        int length;

        if(!fstream->read(reinterpret_cast<char*>(buffer), 12))
            return false;

        if(memcmp(buffer, "RIFF", 4) != 0 || memcmp(buffer+8, "WAVE", 4) != 0)
        {
            dataStart = 0;

            // Check for an ID3v2 tag, and skip it
            if(memcmp(buffer, "ID3", 3) == 0 &&
               buffer[3] <= 4 && buffer[4] != 0xff &&
               (buffer[5]&0x0f) == 0 && (buffer[6]&0x80) == 0 &&
               (buffer[7]&0x80) == 0 && (buffer[8]&0x80) == 0 &&
               (buffer[9]&0x80) == 0)
            {
                dataStart = (buffer[6]<<21) | (buffer[7]<<14) |
                            (buffer[8]<< 7) | (buffer[9]    );
                dataStart += ((buffer[5]&0x10) ? 20 : 10);
            }

            if(fstream->seekg(0, std::ios_base::end))
            {
                dataEnd = fstream->tellg();
                fstream->seekg(dataStart);
            }
            return true;
        }

        int type = 0;
        while(1)
        {
            char tag[4];
            if(!fstream->read(tag, 4))
                break;

            /* read chunk length */
            length = read_le32(fstream);

            if(memcmp(tag, "fmt ", 4) == 0 && length >= 16)
            {
                /* Data type (should be 0x0050 or 0x0055 for MP3 data) */
                type = read_le16(fstream);
                if(type != 0x0050 && type != 0x0055)
                    break;
                length -= 2;
                /* Ignore the rest of the chunk. Everything we need is in the
                 * data stream */
            }
            else if(memcmp(tag, "data", 4) == 0)
            {
                if(type == 0x0050 || type == 0x0055)
                {
                    dataStart = fstream->tellg();
                    dataEnd = dataStart;
                    dataEnd += length;
                    return true;
                }
            }

            fstream->seekg(length, std::ios_base::cur);
        }

        return false;
    }
};
static DecoderDecl<mp3Stream> mp3Stream_decoder;
#endif


template <typename T>
alureStream *get_stream_decoder(const T &fdata)
{
    std::map<ALint,UserCallbacks>::iterator i = InstalledCallbacks.begin();
    while(i != InstalledCallbacks.end() && i->first < 0)
    {
        std::auto_ptr<alureStream> stream(new customStream(fdata, i->second));
        if(stream->IsValid()) return stream.release();
        i++;
    }

    std::istream *file = new InStream(fdata);
    if(!file->fail())
    {
        Decoder::ListType Factories = Decoder::GetList();
        Decoder::ListType::iterator factory = Factories.begin();
        Decoder::ListType::iterator end = Factories.end();
        while(factory != end)
        {
            file->clear();
            file->seekg(0, std::ios_base::beg);

            std::auto_ptr<alureStream> stream((*factory)(file));
            if(stream.get() != NULL) return stream.release();

            factory++;
        }

        SetError("Unsupported type");
        delete file;
    }
    else
    {
        SetError("Failed to open file");
        delete file;
    }

    while(i != InstalledCallbacks.end())
    {
        std::auto_ptr<alureStream> stream(new customStream(fdata, i->second));
        if(stream->IsValid()) return stream.release();
        i++;
    }

    return new nullStream;
}

alureStream *create_stream(const char *fname)
{ return get_stream_decoder(fname); }
alureStream *create_stream(const MemDataInfo &memData)
{ return get_stream_decoder(memData); }

alureStream *create_stream(ALvoid *userdata, ALenum format, ALuint rate, const UserCallbacks &cb)
{ return new customStream(userdata, format, rate, cb); }
