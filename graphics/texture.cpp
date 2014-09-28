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

#include <QtCore/QUrl>
#include <QtGui/QImage>

#include <core/log.h>

#include "math.h"
#include "backend.h"
#include "texturedata.h"

using namespace GluonGraphics;

class Texture::Private
{
    public:
        QImage image;
        TextureData* data;
};

Texture::Texture( QObject* parent )
    : QObject( parent ), d( new Private )
{
    d->data = Backend::currentBackend()->createTextureData();
}

Texture::Texture(TextureData* data, QObject* parent)
    : QObject(parent), d( new Private )
{
    d->data = data;
}


Texture::~Texture()
{
    delete d->data;
    delete d;
}

bool Texture::load( const QString& path )
{
    //TODO: Add support for non-2D textures and non-RGBA colour formats.
    if( !d->image.load( path ) )
    {
        ERROR_NC() << "Failed to load texture " << path;
        return false;
    }

    //Ensure we have 32-bit RGBA data
    if( d->image.format() != QImage::Format_RGBA8888 )
        d->image = d->image.convertToFormat( QImage::Format_RGBA8888 );


    d->image = d->image.mirrored();

    if( d->image.isNull() )
    {
        ERROR_NC() << "Failed to load texture " << path;
        return false;
    }

    //Finally, load it into GPU memory.
    d->data->setData( d->image.width(), d->image.height(), d->image.bits() );

    return true;
}

QImage Texture::image() const
{
    return d->image;
}

TextureData* Texture::data() const
{
    return d->data;
}
