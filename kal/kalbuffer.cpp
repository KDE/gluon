/*
* This file is part of the KALEngine project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#include "kalbuffer.h"
#include "kalengine.h"

#include <KDebug>

#include <QFileInfo>

#include <al.h>
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>
#include <sys/stat.h>
#include <vector>

#define BUFFER_SIZE     32768       // 32 KB buffers

using namespace std;
KALBuffer::KALBuffer()
        : m_buffer(0)
{
    init();
}

KALBuffer::KALBuffer(const QString &fileName)
        : m_buffer(0)
{
    setBuffer(fileName);
    init();
}

KALBuffer::KALBuffer(ALuint buffer)
{
    m_buffer = buffer;
    init();
}

KALBuffer::~KALBuffer()
{
    alDeleteBuffers(1, &m_buffer);
    KALEngine *engine = KALEngine::getInstance();
    engine->removeBuffer(this);
}


void KALBuffer::init()
{
    KALEngine *engine = KALEngine::getInstance();
    engine->addBuffer(this);
}

void KALBuffer::setBuffer(const QString &fileName)
{
    QFileInfo file(fileName);

    if (!file.exists()) {
        kDebug() << "Could not load file: the file dosn't exist";
        return;
    }

    if (file.completeSuffix() == "ogg") {
        m_buffer = fromOgg(fileName);
    } else if (file.completeSuffix() == "wav") {
        m_buffer = fromWav(fileName);
    }
}

ALuint KALBuffer::fromWav(const QString &fileName)
{
    SF_INFO fileInfos;
    SNDFILE* file = sf_open(fileName.toUtf8(), SFM_READ, &fileInfos);

    if (!file) {
        kDebug() << "Could not load file:" << sf_strerror(file);
        return 0;
    }

    ALsizei samplesNumber  = static_cast<ALsizei>(fileInfos.channels * fileInfos.frames);
    ALsizei samplesRate = static_cast<ALsizei>(fileInfos.samplerate);

    // Reading signed 16 bits samples (most commonly used format)
    std::vector<ALshort> samples(samplesNumber);
    if (sf_read_short(file, &samples[0], samplesNumber) < samplesNumber) {
        kDebug() << "Could not read the sound data";
        return 0;
    }

    sf_close(file);

    // Determine file format from number of canals
    ALenum format;
    switch (fileInfos.channels) {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    default :
        kDebug() << "Unsupported format: more than two channels";
        return 0;
    }

    // creating openAL buffer and filling it with the samples we read
    ALuint buffer;
    alGenBuffers(1, &buffer);

    alBufferData(buffer, format, &samples[0], samplesNumber * sizeof(ALushort), samplesRate);

    if (alGetError() != AL_NO_ERROR) {
        kDebug() << "Could not read the samples: " << alGetError();
        return 0;
    }

    return buffer;
}

ALuint KALBuffer::fromOgg(const QString &fileName)
{

    vector<char> buffer;
    ALenum format;
    ALsizei freq;
    int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];                // Local fixed size array
    FILE *f;

    // Open for binary reading
    f = fopen(fileName.toUtf8(), "rb");

    if (f == NULL) {
        kDebug() << "Cannot open " << fileName << " for reading...";
        return 0;
    }
    // end if

    vorbis_info *pInfo;
    OggVorbis_File oggFile;

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0) {
        kDebug() << "Error opening " << fileName << " for decoding...";
        return 0;
    }
    // end if

    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Check the number of channels... always use 16-bit samples
    if (pInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;
    // end if

    // The frequency of the sampling rate
    freq = pInfo->rate;

    // Keep reading until all is read
    do {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0) {
            ov_clear(&oggFile);
            kDebug() << "Error decoding " << fileName << "..." ;
            return 0;
        }
        // end if

        // Append to end of buffer
        buffer.insert(buffer.end(), array, array + bytes);
    } while (bytes > 0);

    // Clean up!
    ov_clear(&oggFile);

// end of LoadOGG

    ALuint albuffer;
    alGenBuffers(1, &albuffer);

    alBufferData(albuffer, format, &buffer[0], static_cast<ALsizei>(buffer.size()), freq);

    if (alGetError() != AL_NO_ERROR) {
        kDebug() << "Could not read the samples: " << alGetError();
        return 0;
    }

    return albuffer;

    /*
           FILE *f = fopen(fileName.toUtf8(), "rb");
           int oggBitstream = 0;
           OggVorbis_File ov;

           ov_open_callbacks(f, &ov, NULL, 0, OV_CALLBACKS_DEFAULT);

           vorbis_info *info = ov_info(&ov, -1);
           ALenum fmt = ((info->channels==2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16);

           std::vector<char> data;
           int got = 0, res;
           while(res > 0)
           {
               if(got == data.size())
                   data.resize(got + 65536);
               res = ov_read(&ov, (char*)&data[got], data.size()-got, 0, 2, 1, &oggBitstream);
               if(res > 0)
                   got += res;
           }
       //     ov_close(&ov);
           data.resize(got);

           ALuint buf;
           alGenBuffers(1, &buf);
           alBufferData(buf, fmt, data, data.size(), info->rate);

           return buf;*/
}
