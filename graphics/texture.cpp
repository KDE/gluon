/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

#include "texture.h"

#include "glheaders.h"

#include <QtCore/QUrl>
#include <QtGui/QImage>
#include <QtOpenGL/QGLContext>

#include "math.h"

using namespace GluonGraphics;

class Texture::TexturePrivate
{
    public:
        TexturePrivate()
            : glTexture( 0 )
        { }
        uint glTexture;
        QImage image;
};

Texture::Texture( QObject* parent )
    : QObject( parent ),
      d( new TexturePrivate )
{

}

Texture::Texture( const Texture& other, QObject* parent )
    : QObject( parent )
    , d( other.d )
{

}

Texture::~Texture()
{
    glDeleteTextures( 1, &d->glTexture );
    delete d;
}

bool Texture::load( const QUrl& url )
{
#ifdef __GNUC__
#warning Todo: Add support for non-2D textures and non-RGBA colour formats. Also, find a way \
around the nasty const_cast .
#endif

    if( !QGLContext::currentContext() || !QGLContext::currentContext()->isValid() )
        return false;

    QGLContext* context = const_cast<QGLContext*>( QGLContext::currentContext() );

    if( d->glTexture )
        context->deleteTexture( d->glTexture );

    d->image.load( url.toLocalFile() );

    d->glTexture = context->bindTexture( d->image );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
#if !defined(GLUON_GRAPHICS_GLES) && !defined(QT_OPENGL_ES)
    glTexParameterf( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE );
#endif

    if( d->glTexture != 0 )
        return true;

    return false;
}

uint Texture::glTexture() const
{
    return d->glTexture;
}

QImage Texture::image() const
{
    return d->image;
}

#include "texture.moc"
