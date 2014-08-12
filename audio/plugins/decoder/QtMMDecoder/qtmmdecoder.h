/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2014 Felix Rohrbach <kde@fxrh.de>
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

#ifndef GLUON_AUDIO_QTMMDECODER_H
#define GLUON_AUDIO_QTMMDECODER_H

#include <QtCore/QObject>
#include <QtMultimedia/QAudioDecoder>
#include <QtMultimedia/QAudioFormat>

#include <audio/decoder.h>
#include <audio/buffer.h>

namespace GluonAudio
{
    class QtMMDecoder: public Decoder, public QObject
    {
        public:
            QtMMDecoder( QString file, QObject* parent=0 );
            ~QtMMDecoder();
            
            virtual void startDecoding();
            virtual void stopDecoding();
            
            virtual void setBufferSize( int bytes );
            
            virtual bool buffersAvailable();
            virtual Buffer getBuffer();
            
            virtual bool isLoaded();
            virtual bool isValid();
            virtual float duration();
            virtual int size();
            
            virtual bool isStereo();
            virtual bool isEndOfFile();
            
        protected Q_SLOTS:
            void gotError(QAudioDecoder::Error error);
            void gotFinished();
            void gotFormatChanged(const QAudioFormat& format);
            
        private:
            class Private;
            Private* d;
    };
}

#endif // GLUON_AUDIO_QTMMDECODER_H