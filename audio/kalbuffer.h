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

#ifndef KALBUFFER_H
#define KALBUFFER_H

#include "kal_export.h"

#ifdef Q_WS_X11
#include <AL/al.h>
#endif

#ifdef Q_WS_MAC
#include <OpenAL/al.h>
#endif

/**
 * @class kal/kalbuffer.h <KAL/KALBuffer>
 *
 * @short the Wrapper class of openAL buffer.
 *
 * KALBuffer allow you to manage data of sound. If you want to generate or manupulate sound data, use this class.
 * You can setup a KALSound from a KALBuffer
 * You can initialize the class with a pathName or a buffer. For example :
 * @code
 * KALBuffer* buffer = new KALBuffer;
 * {action inside the buffer}
 * KALSound * sound = new KALSound(buffer);
 * sound->play();
 * @endcode

 */

/**
 * \defgroup KAL KAL
 */
//@{

class KALBufferPrivate;
class KAL_EXPORT KALBuffer
{
public:
    KALBuffer();
    KALBuffer(const QString &fileName);
    KALBuffer(ALuint buffer);
    ~KALBuffer();

    void setBuffer(const QString &fileName);
    void setBuffer(ALuint buffer);
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
    Q_DISABLE_COPY(KALBuffer)

    KALBufferPrivate * const d;
};

//@}
#endif // KALBUFFER_H
