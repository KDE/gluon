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

#include "glxbuffer.h"

#include <GL/gl.h>
#include <GL/glext.h>

#include "glxfunctions.h"

using namespace GluonGraphics::GLX;

class GLXBuffer::Private
{
    public:
        Private() : buffer( 0 ), size( 0 ), timesBound( 0 ) { }

        BufferType type;

        GLenum target;
        GLenum usage;
        GLuint buffer;

        int size;

        uint timesBound;
};

GLXBuffer::GLXBuffer() : d( new Private )
{

}

GLXBuffer::~GLXBuffer()
{
    if( d->buffer )
        destroy();

    delete d;
}

void GLXBuffer::initialize( Buffer::BufferType type, Buffer::UpdateMode mode )
{
    d->type = type;
    d->target = type == Vertex ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
    d->usage = mode == Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

    glGenBuffersARB(1, &d->buffer);
}

void GLXBuffer::destroy()
{
    glDeleteBuffersARB(1, &d->buffer);
    d->buffer = 0;
}

void GLXBuffer::setSize( int size )
{
    if( !d->buffer )
        return;

    bind();

    char* data = 0;
    if( d->size > 0 )
    {
        data = new char[ d->size ];
        glGetBufferSubDataARB( d->target, 0, d->size, data );
    }

    glBufferDataARB( d->target, size, 0, d->usage );

    if( data != 0 )
    {
        glBufferSubDataARB( d->target, 0, d->size, data );
        delete[] data;
    }

    release();
    d->size = size;
}

void GLXBuffer::setData( void* data, int size, int offset )
{
    if( !d->buffer )
        return;

    bind();

    if( offset + size > d->size )
    {
        setSize( offset + size );
    }

    glBufferSubDataARB( d->target, offset, size, data );
    release();
}

void GLXBuffer::bind()
{
    if( !d->buffer )
        return;

    if( d->timesBound > 0 )
    {
        d->timesBound++;
        return;
    }

    glBindBufferARB( d->target, d->buffer );
    d->timesBound = 1;
}

void GLXBuffer::release()
{
    if( d->timesBound > 0 )
    {
        d->timesBound--;

        if( d->timesBound == 0 )
            glBindBufferARB( d->target, 0 );
    }
}
