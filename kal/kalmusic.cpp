/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
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

#include "kalmusic.h"
#include <KDebug>

KALMusic::KALMusic(QString fileName)
{
    setFileName(fileName);
}

void KALMusic::open(string path)
{
    int result;

    if (!(oggFile = fopen(path.c_str(), "rb")))
        kDebug() << "Could not open Ogg file.";

    if ((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0) {
        fclose(oggFile);

        kDebug() << "Could not open Ogg stream. ";
    }

    vorbisInfo = ov_info(&oggStream, -1);
    vorbisComment = ov_comment(&oggStream, -1);

    if (vorbisInfo->channels == 1) {
        format = AL_FORMAT_MONO16;
    } else {
        format = AL_FORMAT_STEREO16;
    }

    alGenBuffers(2, buffers);
    check();
    alGenSources(1, &source);
    check();

    alSource3f(source, AL_POSITION, 0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY, 0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION, 0.0, 0.0, 0.0);
    alSourcef(source, AL_ROLLOFF_FACTOR, 0.0);
    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
}

void KALMusic::release()
{
    alSourceStop(source);
    empty();
    alDeleteSources(1, &source);
    check();
    alDeleteBuffers(1, buffers);
    check();

    ov_clear(&oggStream);
}

void KALMusic::display()
{
    kDebug()
    << "version         " << vorbisInfo->version         << "\n"
    << "channels        " << vorbisInfo->channels        << "\n"
    << "rate (hz)       " << vorbisInfo->rate            << "\n"
    << "bitrate upper   " << vorbisInfo->bitrate_upper   << "\n"
    << "bitrate nominal " << vorbisInfo->bitrate_nominal << "\n"
    << "bitrate lower   " << vorbisInfo->bitrate_lower   << "\n"
    << "bitrate window  " << vorbisInfo->bitrate_window  << "\n"
    << "\n"
    << "vendor " << vorbisComment->vendor << "\n";

    for (int i = 0; i < vorbisComment->comments; i++) {
        kDebug() << "   " << vorbisComment->user_comments[i] << "\n";
    }
}

bool KALMusic::playback()
{
    if (isPlaying()) {
        return true;
    }

    if (!stream(buffers[0])) {
        return false;
    }

    if (!stream(buffers[1])) {
        return false;
    }

    alSourceQueueBuffers(source, 2, buffers);
    alSourcePlay(source);

    return true;
}

bool KALMusic::isPlaying()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_PLAYING);
}

bool KALMusic::update()
{
    int processed;
    bool active = true;

    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

    while (processed--) {
        ALuint buffer;

        alSourceUnqueueBuffers(source, 1, &buffer);
        check();

        active = stream(buffer);

        alSourceQueueBuffers(source, 1, &buffer);
        check();
    }

    return active;
}

bool KALMusic::stream(ALuint buffer)
{
    char pcm[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while (size < BUFFER_SIZE) {
        result = ov_read(&oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);

        if (result > 0) {
            size += result;
        } else {
            if (result < 0) {
                kDebug() << "errorString(result)";
            } else {
                break;
            }
        }
    }

    if (size == 0) {
        return false;
    }

    alBufferData(buffer, format, pcm, size, vorbisInfo->rate);
    check();

    return true;
}

void KALMusic::empty()
{
    int queued;

    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

    while (queued--) {
        ALuint buffer;

        alSourceUnqueueBuffers(source, 1, &buffer);
        check();
    }
}

void KALMusic::check()
{
    int error = alGetError();

    if (error != AL_NO_ERROR) {
        kDebug() << "OpenAL error was raised.";
    }
}

string KALMusic::errorString(int code)
{
    switch (code) {
    case OV_EREAD:
        return string("Read from media.");
    case OV_ENOTVORBIS:
        return string("Not Vorbis data.");
    case OV_EVERSION:
        return string("Vorbis version mismatch.");
    case OV_EBADHEADER:
        return string("Invalid Vorbis header.");
    case OV_EFAULT:
        return string("Internal logic fault (bug or heap/stack corruption.");
    default:
        return string("Unknown Ogg error.");
    }
}

void KALMusic::run()
{
    open(m_fileName.toUtf8().data());
    display();
    if (!playback()) {
        kDebug() << "Ogg refused to play.";
    }

    while (update()) {
        if (!isPlaying()) {
            if (!playback()) {
                kDebug() << "Ogg abruptly stopped.";
            } else {
                kDebug() << "Ogg stream was interrupted.\n";
            }
        }
    }
    release();
}
