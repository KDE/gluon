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

#include "glxrendertarget.h"

#include <GL/gl.h>
#include <QColor>

#include "glxtexturedata.h"
#include "glxfunctions.h"

using namespace GluonGraphics::GLX;

class GLXRenderTarget::Private
{
    public:
        Private() :
            bound( false ),
            fbo( 0 ),
            previous( 0 ),
            imageBuffer( 0 ),
            depthBuffer( 0 ),
            textureData( 0 )
        { }

        bool bound;
        GLuint fbo;
        GLuint previous;

        GLuint imageBuffer;
        GLuint depthBuffer;

        GLXTextureData* textureData;
};

GLXRenderTarget::GLXRenderTarget( QObject* parent )
    : GluonGraphics::RenderTarget( parent ), d( new Private )
{
    glGenFramebuffersEXT( 1, &d->fbo );
}

GLXRenderTarget::~GLXRenderTarget()
{
    glDeleteFramebuffersEXT( 1, &d->fbo );
}

void GLXRenderTarget::bind()
{
    if( d->bound )
        return;

    int current;
    glGetIntegerv( GL_FRAMEBUFFER_BINDING, &current );
    if( current > 0 )
        d->previous = current;

    glBindFramebufferEXT( GL_FRAMEBUFFER, d->fbo );

    QColor bgColor = backgroundColor();
    glClearColor( bgColor.redF(), bgColor.greenF(), bgColor.blueF(), bgColor.alphaF() );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    d->bound = true;
}

void GLXRenderTarget::release()
{
    glBindFramebufferEXT( GL_FRAMEBUFFER, d->previous );
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    d->previous = 0;
    d->bound = false;
}

void GLXRenderTarget::resizeImpl()
{
    if( d->bound )
        return;

    if( d->imageBuffer != 0 )
        glDeleteTextures( 1, &d->imageBuffer );

    glGenTextures( 1, &d->imageBuffer );
    glBindTexture( GL_TEXTURE_2D, d->imageBuffer );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width(), height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if( d->textureData )
        d->textureData->setTexture( d->imageBuffer );

    if( d->depthBuffer != 0 )
        glDeleteRenderbuffersEXT( 1, &d->depthBuffer );

    glGenRenderbuffersEXT( 1, &d->depthBuffer );
    glBindRenderbufferEXT( GL_RENDERBUFFER, d->depthBuffer );
    glRenderbufferStorageEXT( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width(), height() );

    glBindFramebufferEXT( GL_FRAMEBUFFER, d->fbo );
    glFramebufferTexture2DEXT( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, d->imageBuffer, 0 );
    glFramebufferRenderbufferEXT( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, d->depthBuffer );
    glBindFramebufferEXT( GL_FRAMEBUFFER, 0 );

    glBindRenderbufferEXT( GL_RENDERBUFFER, 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

GluonGraphics::TextureData* GLXRenderTarget::textureData()
{
    if( !d->textureData )
        d->textureData = new GLXTextureData( d->imageBuffer );

    return d->textureData;
}
