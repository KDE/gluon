/*
* This file is part of the Gluon project.
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

#include "soundreader.h"
#include "buffer.h"

#include <QtCore/QDebug>

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtGui/QMessageBox>
#include <QtCore/QVector>

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>
#include <sys/stat.h>
#include <vector>
#include <sndfile.h>

using namespace GluonAudio;

class SoundReader::SoundReaderPrivate
{
  public:
        QString fileName;
        bool error;
};

#define BUFFER_SIZE 32768 // 32 KB buffers

SoundReader::SoundReader(const QString& fileName)
        :d(new SoundReaderPrivate)

{
    d->fileName = fileName;
    d->error = false;
    if (!QFile::exists(fileName)) {
        qDebug() << "Could not find file" << fileName;
        d->error=true;
    }
}

SoundReader::~SoundReader()
{
    delete d;
}

bool SoundReader::canRead() const
{
    return supportedSoundFormats().contains(format());
}

ALuint SoundReader::alBuffer()
{

    if (format() == "ogg") {
        return fromOgg();
    }

    if (format() == "wav") {
        return fromWav();
    }

    return NULL;
}

Buffer *SoundReader::buffer()
{
  if (format() == "ogg") {
        return new Buffer(fromOgg());
    }

    if (format() == "wav") {
        return new Buffer(fromWav());
    }
    d->error=true;
    return new Buffer();
}

QStringList SoundReader::supportedSoundFormats()
{
    return (QStringList() << "wav" << "ogg");
}

ALuint SoundReader::fromWav()
{
    SF_INFO fileInfos;
    SNDFILE* file = sf_open(d->fileName.toUtf8(), SFM_READ, &fileInfos);

    if (!file) {
        qDebug() << "Could not load file:" << sf_strerror(file);
        return 0;
    }

    ALsizei samplesNumber  = static_cast<ALsizei>(fileInfos.channels * fileInfos.frames);
    ALsizei samplesRate = static_cast<ALsizei>(fileInfos.samplerate);

    // Reading signed 16 bits samples (most commonly used format)
    std::vector<ALshort> samples(samplesNumber);
    if (sf_read_short(file, &samples[0], samplesNumber) < samplesNumber) {
        qDebug() << "Could not read the sound data";
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
        qDebug() << "Unsupported format: more than two channels";
        return 0;
    }

    // creating openAL buffer and filling it with the samples we read
    ALuint buffer;
    alGenBuffers(1, &buffer);

    alBufferData(buffer, format, &samples[0], samplesNumber * sizeof(ALushort), samplesRate);

    if (alGetError() != AL_NO_ERROR) {
        qDebug() << "Could not read the samples: " << alGetError();
        return 0;
    }

    return buffer;
}
ALuint SoundReader::fromOgg()
{

    std::vector<char> buffer;
    ALenum format;
    ALsizei freq;
    int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];                // Local fixed size array
    FILE *f;

    // Open for binary reading
    f = fopen(d->fileName.toUtf8(), "rb");

    if (f == NULL) {
        qDebug() << "Cannot open " << d->fileName << " for reading...";
        return 0;
    }

    vorbis_info *pInfo;
    OggVorbis_File oggFile;

    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0) {
        qDebug() << "Error opening " << d->fileName << " for decoding...";
        return 0;
    }

    // Get some information about the OGG file
    pInfo = ov_info(&oggFile, -1);

    // Check the number of channels... always use 16-bit samples
    if (pInfo->channels == 1) {
        format = AL_FORMAT_MONO16;
    } else {
        format = AL_FORMAT_STEREO16;
    }

    // The frequency of the sampling rate
    freq = pInfo->rate;

    // Keep reading until all is read
    do {
        // Read up to a buffer's worth of decoded sound data
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0) {
            ov_clear(&oggFile);
            qDebug() << "Error decoding " << d->fileName << "..." ;
            return 0;
        }

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
        qDebug() << "Could not read the samples: " << alGetError();
        return 0;
    }

    return albuffer;

    /*
           FILE *f = fopen(d->fileName.toUtf8(), "rb");
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
    QString SoundReader::fileName() const {
        return d->fileName;
    }
    QString SoundReader::format() const {
        QFileInfo file(d->fileName);
        return file.completeSuffix();
    }
