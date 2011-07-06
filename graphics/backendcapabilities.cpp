/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "backendcapabilities.h"

#include "glheaders.h"

#include <QtCore/QStringList>

using namespace GluonGraphics;

int BackendCapabilities::backendVersion = -1;
int BackendCapabilities::backendShaderVersion = -1;

BackendCapabilities::BackendType
BackendCapabilities::type()
{
#ifdef GLUON_GRAPHICS_GLES
    return BT_OPENGLES;
#else
    return BT_OPENGL;
#endif
}

int
BackendCapabilities::version()
{
    if( backendVersion != -1 )
        return backendVersion;

    const GLubyte* version = glGetString( GL_VERSION );

    QString versionString = QString::fromAscii( reinterpret_cast<const char*>( version ) );
    QStringList versionParts = versionString.split( '.' );

    int versionNumber = 0;
    versionNumber += versionParts.at( 0 ).toInt() * 100;
    versionNumber += ( versionParts.at( 1 ).toInt() > 9 ) ? versionParts.at( 1 ).toInt() : versionParts.at( 1 ).toInt() * 10;

    if( versionParts.count() > 2 )
        versionNumber += qMin( versionParts.at( 2 ).toInt(), 9 );

    backendVersion = versionNumber;
    return versionNumber;
}

int
BackendCapabilities::shaderVersion()
{
    if( backendShaderVersion != -1 )
        return backendShaderVersion;

    const GLubyte* version = glGetString( GL_SHADING_LANGUAGE_VERSION );
    if( glGetError() == GL_INVALID_ENUM )
        return -1;

    QString versionString = QString::fromAscii( reinterpret_cast<const char*>( version ) );
    QStringList versionParts = versionString.split( '.' );

    int versionNumber = 0;
    versionNumber += versionParts.at( 0 ).toInt() * 100;
    versionNumber += ( versionParts.at( 1 ).toInt() > 9 ) ? versionParts.at( 1 ).toInt() : versionParts.at( 1 ).toInt() * 10;

    if( versionParts.count() > 2 )
        versionNumber += qMin( versionParts.at( 2 ).toInt(), 9 );

    backendShaderVersion = versionNumber;
    return versionNumber;
}
