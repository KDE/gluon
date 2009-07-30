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

#ifndef KALOGGSTREAMER_H
#define KALOGGSTREAMER_H

#include <AL/al.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <QThread>
#include <string>
#include "kalsource.h"
#define BUFFER_SIZE (4096 * 4)

using namespace std;

class KALOggStreamer : public QThread
{
    Q_OBJECT

public:
    KALOggStreamer(QString fileName = QString());
    void run();
    bool isPlaying();

public slots:
    void play() {
        run();
    }
    void playThread() {
        start();
    }

protected:
    void open(string path);
    void release();
    void display();
    bool playback();
    bool update();

    void setFileName(QString f) {
        m_fileName = f;
    }

    bool stream(ALuint buffer);
    void empty();
    void check();
    string errorString(int code);

private:
    FILE*           oggFile;
    OggVorbis_File  oggStream;
    vorbis_info*    vorbisInfo;
    vorbis_comment* vorbisComment;

    ALuint buffers[2];
    ALuint source;
    ALenum format;

    QString m_fileName;
};

#endif // KALOGGSTREAMER_H
