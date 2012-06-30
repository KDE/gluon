/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "textureasset.h"

#include <QtGui/QImageReader>

#include <graphics/manager.h>
#include <graphics/texture.h>

REGISTER_OBJECTTYPE( GluonEngine, TextureAsset )

using namespace GluonEngine;

class TextureAsset::Private
{
    public:
        Private() : texture( 0 ) { }

        GluonGraphics::Texture* texture;
};

TextureAsset::TextureAsset( QObject* parent )
    : Asset( parent ), d( new Private )
{
}

TextureAsset::~TextureAsset()
{
    if( d->texture )
    {
        GluonGraphics::Manager::instance()->destroyResource< GluonGraphics::Texture >( name() );
        d->texture = 0;
    }
    delete d;
}

const QStringList TextureAsset::supportedMimeTypes() const
{
    QList<QByteArray> supported = QImageReader::supportedImageFormats();

    QStringList supportedTypes;
    foreach( const QByteArray & type, supported )
    {
        supportedTypes << QString( "image/%1" ).arg( QString( type ) );
    }

    return supportedTypes;
}

void TextureAsset::load()
{
    if( !file().isEmpty() )
    {
        if( !d->texture )
            d->texture = GluonGraphics::Manager::instance()->createResource< GluonGraphics::Texture >( name() );

        if( d->texture->load( absolutePath() ) )
        {
            mimeData()->setText( name() );
            setLoaded( true );
            return;
        }
    }

    debug( "Error loading texture: %1", name() );
}

void TextureAsset::setName( const QString& newName )
{
    GluonGraphics::Manager::instance()->removeResource< GluonGraphics::Texture >( name() );
    if( d->texture )
        GluonGraphics::Manager::instance()->addResource< GluonGraphics::Texture >( newName, d->texture );
    GluonEngine::Asset::setName( newName );
}

GluonGraphics::Texture* TextureAsset::texture() const
{
    return GluonGraphics::Manager::instance()->resource< GluonGraphics::Texture >( name() );
}

Q_EXPORT_PLUGIN2( gluon_asset_texture, GluonEngine::TextureAsset )

#include "textureasset.moc"
