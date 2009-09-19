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

#include "kalbuffer.h"
#include "kalengine.h"
#include "kalsoundreader.h"

KALBuffer::KALBuffer()
    : m_buffer(0)
{
    init();
}

KALBuffer::KALBuffer(const QString &fileName)
    : m_buffer(0)
{
    setBuffer(fileName);
    init();
}

KALBuffer::KALBuffer(ALuint buffer)
{
    m_buffer = buffer;
    init();
}

void KALBuffer::init()
{

    KALEngine::instance()->addBuffer(this);
}

KALBuffer::~KALBuffer()
{
    alDeleteBuffers(1, &m_buffer);
    KALEngine *engine = KALEngine::instance();
    engine->removeBuffer(this);
}

void KALBuffer::setBuffer(const QString &fileName)
{
    KALSoundReader reader(fileName);
    if (reader.canRead()) {
        m_buffer = reader.buffer();
    }
}
