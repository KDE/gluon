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

#ifndef KALMUSIC_H
#define KALMUSIC_H


#include <QThread>
#include <string.h>

#ifdef Q_OS_MACX
#  include <OpenAL/al.h>
#else
#  include <AL/al.h>
#endif
#include <vorbis/vorbisfile.h>

using namespace std;

/**
 * \defgroup KAL KAL
 */
//@{

class KALMusic : public QThread
{
    Q_OBJECT

public:
    KALMusic(QString fileName = QString());
    void run();
    bool isPlaying() const;

public slots:
    void play() {
        run();
    }

    private slots:
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

//@}
#endif // KALMusic_H
