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

#ifndef KALSOUNDREADER_H
#define KALSOUNDREADER_H

#include <al.h>

#include "kal_export.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

class KALBuffer;

/**
 * \defgroup KAL KAL
 */

/**
* @class KALSoundReader kal/kalsoundreader.h <KAL/KALSoundReader>
* KALSoundReader generate a buffer from a sound file. Currently it allows to read Wav and ogg file.
* Phonon output device in KALEngine
*/

//@{
class KALSoundReaderPrivate;
class KAL_EXPORT KALSoundReader
{
public:
    KALSoundReader(const QString& fileName);
    ~KALSoundReader();

    QString format() const;
    bool canRead() const;
    static QStringList supportedSoundFormats() ;
    QString fileName() const;
    ALuint alBuffer();
    KALBuffer *buffer();

protected:
    ALuint fromWav();
    ALuint fromOgg();

private:
    Q_DISABLE_COPY(KALSoundReader)
    KALSoundReaderPrivate * const d;

};

//@}
#endif // KALSOUNDREADER_H
