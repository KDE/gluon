/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef GLUON_AUDIO_MUSIC_H
#define GLUON_AUDIO_MUSIC_H

#include <QtCore/QThread>
#include <cstring>
#include <cstdio>

#include <al.h>
#include <vorbis/vorbisfile.h>

#include "gluon_audio_export.h"

//TODO: Clean up this class. Heavily.
namespace GluonAudio
{
    class GLUON_AUDIO_EXPORT Music : public QThread
    {
            Q_OBJECT

        public:
            Music(QString fileName = QString());
            void run();
            bool isPlaying() const;

        public Q_SLOTS:
            void play()
            {
                run();
            }

        private Q_SLOTS:
            void playThread()
            {
                start();
            }

        protected:
            void open(std::string path);
            void release();
            void display();
            bool playback();
            bool update();

            void setFileName(QString f)
            {
                m_fileName = f;
            }

            bool stream(ALuint buffer);
            void empty();
            void check();
            std::string errorString(int code);

        private:
            FILE *oggFile;
            OggVorbis_File  oggStream;
            vorbis_info *vorbisInfo;
            vorbis_comment *vorbisComment;

            ALuint buffers[2];
            ALuint source;
            ALenum format;

            QString m_fileName;
    };
}

#endif // GLUON_AUDIO_MUSIC_H
