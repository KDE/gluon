/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
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
#ifndef GLUON_AUDIO_BUFFER_H
#define GLUON_AUDIO_BUFFER_H

#include "gluon_audio_export.h"

#include <al.h>

#include <QtCore/QSharedDataPointer>

namespace GluonAudio
{
    class GLUON_AUDIO_EXPORT Buffer
    {
        public:
            Buffer();
            Buffer(const QString &fileName);
            Buffer(ALuint buffer);
            Buffer(const Buffer &other);
            ~Buffer();

            void setBuffer(const QString &fileName);
            void setBuffer(ALuint buffer, bool shared = false);
            bool isEmpty() const;
            /**
            * This function will generate a "hello word" sound.
            */
            //void setHelloWord();
            ALuint buffer() const;
            /**
            * @return the duration of buffer in msecond
            */
            ALfloat duration() const;

        protected:
            void init();

        private:
            class BufferPrivate;
            QSharedDataPointer<BufferPrivate> d;
    };
}

#endif // GLUON_AUDIO_BUFFER_H
