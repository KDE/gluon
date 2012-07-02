/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "glxtexturedata.h"
#include <GL/gl.h>

using namespace GluonGraphics::GLX;

class GLXTextureData::Private
{
    public:
        GLuint glTexture;
};

GLXTextureData::GLXTextureData() : d( new Private )
{
    glGenTextures(1, &d->glTexture);
}

GLXTextureData::GLXTextureData( unsigned int texture ) : d( new Private )
{
    d->glTexture = texture;
}

GLXTextureData::~GLXTextureData()
{
    glDeleteTextures(1, &d->glTexture);
}

void GLXTextureData::bind( unsigned int unit )
{
    glActiveTexture( GL_TEXTURE0 + unit );
    glBindTexture( GL_TEXTURE_2D, d->glTexture );
}

void GLXTextureData::release()
{
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void GLXTextureData::setData( int width, int height, void* data )
{
    glBindTexture( GL_TEXTURE_2D, d->glTexture );
    glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void GLXTextureData::setTexture(unsigned int texture)
{
    d->glTexture = texture;
}
