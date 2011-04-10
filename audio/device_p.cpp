/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "device_p.h"

#ifdef Q_WS_X11
#include <AL/al.h>
#elif defined(Q_WS_MAC)
#include <OpenAL/al.h>
#elif defined(Q_WS_WIN)
#include <AL/al.h>
#endif

using namespace GluonAudio;

Device::Device( ALCdevice* device )
    : m_device( device )
{
}

Device::~Device()
{
    alcCloseDevice( m_device );
}

bool Device::isExtensionPresent( const QString& extension )
{
    return alcIsExtensionPresent( 0, extension.toUtf8() );
}

QStringList Device::contextOption( int option )
{
    const ALCchar* alcList = alcGetString( 0, option );

    // alcGetString returns a list of devices separated by a null char (the list itself ends with a double null char)
    // So we can't pass it directly to QStringList
    QStringList optionList;
    if( alcList )
    {
        while( strlen( alcList ) > 0 )
        {
            optionList << QString( alcList );
            alcList += strlen( alcList ) + 1;
        }
    }
    return optionList;
}
