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

#include <alut.h>
#include <sndfile.h>
#include <QFile>
#include <QStringList>
#include "kalengine_export.h"

class KALENGINE_EXPORT KALBuffer
{
public:
    KALBuffer();
    KALBuffer(const QString &fileName);
    KALBuffer(ALuint buffer);
    ~KALBuffer();

    void setBuffer(const QString &fileName);
    void setBuffer(ALuint buffer) {
        m_buffer = buffer;
    }
    bool isEmpty() {
        return !m_buffer;
    }
   void setHelloWord() {
        m_buffer = alutCreateBufferHelloWorld();
    }
    ALuint buffer()
    {
        return m_buffer;
    }

protected:
    void init();
private :
    ALuint m_buffer;

};

#endif // KALBUFFER_H
