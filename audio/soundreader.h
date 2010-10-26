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
#ifndef GLUON_AUDIO_SOUNDREADER_H
#define GLUON_AUDIO_SOUNDREADER_H

#include "gluon_audio_export.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <al.h>

namespace GluonAudio
{
    class Buffer;

    class GLUON_AUDIO_EXPORT SoundReader
    {
        public:
            SoundReader(const QString &fileName);
            ~SoundReader();

            QString format() const;
            bool canRead() const;
            static QStringList supportedSoundFormats() ;
            QString fileName() const;
            ALuint alBuffer();
            Buffer *buffer();

        protected:
            ALuint fromWav();
            ALuint fromOgg();

        private:
            Q_DISABLE_COPY(SoundReader)

            class SoundReaderPrivate;
            SoundReaderPrivate *const d;

    };
}

#endif // GLUON_AUDIO_SOUNDREADER_H
