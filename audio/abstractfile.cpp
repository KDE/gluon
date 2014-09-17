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

#include "abstractfile.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <core/debughelper.h>

#include "source.h"
#include "audiohelper.h"
#include "buffer.h"
#include "listener.h"

using namespace GluonAudio;

class AbstractFile::Private
{
    public:
        Private() : valid(true) {}
        
        QString file;
        bool valid;
};

AbstractFile::AbstractFile(QString file, QObject* parent)
    : QObject(parent)
    , d( new Private() )
{
    DEBUG_BLOCK
    d->file = file;
    if( AudioHelper::instance()->decoderPlugins().empty() )
    {
        DEBUG_TEXT( "No decoder plugins found!" )
        d->valid = false;
    }
}

AbstractFile::~AbstractFile()
{
    delete d;
}

bool AbstractFile::isValid()
{
    return d->valid;
}

QString AbstractFile::file()
{
    return d->file;
}

bool AbstractFile::generateBuffer(Buffer* buffer, bool isStereo)
{
    DEBUG_BLOCK
    ALenum format = isStereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    Listener::instance();
    alGenBuffers( 1, &buffer->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while creating buffer: %1", error )
        return false;
    }
    alBufferData( buffer->name, format, (void*) buffer->data, buffer->size, buffer->frequency );
    error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while filling buffer: %1", error )
        return false;
    }
    return true;
}

