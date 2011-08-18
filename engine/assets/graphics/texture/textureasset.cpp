/******************************************************************************
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

#include "textureasset.h"

#include <graphics/engine.h>

#include <QtGui/QImageReader>

REGISTER_OBJECTTYPE( GluonEngine, TextureAsset )

using namespace GluonEngine;

class TextureAsset::TextureAssetPrivate
{
    public:
        TextureAssetPrivate()
            : texture( 0 )
        {}
        ~TextureAssetPrivate() {}

        QPixmap icon;
        GluonGraphics::Texture* texture;
};

TextureAsset::TextureAsset( QObject* parent )
    : Asset( parent )
    , d( new TextureAssetPrivate )
{
}

TextureAsset::~TextureAsset()
{
    d->texture = 0;
    delete d;
}

// QIcon TextureAsset::icon() const
// {
//     if( d->icon.isNull() )
//         return GluonEngine::Asset::icon();
//
//     return QIcon( d->icon );
// }

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
            d->texture = GluonGraphics::Engine::instance()->createTexture( name() );

        if( !d->texture )
        {
            debug( QString( "Error creating texture %1" ).arg( name() ) );
            return;
        }

        if( d->texture->load( file() ) )
        {
            mimeData()->setText( name() );
            //d->icon = QPixmap::fromImage(d->texture->image().scaled(QSize(128, 128), Qt::KeepAspectRatio));
            setLoaded( true );
            return;
        }
    }

    debug( "Error loading texture: %1", name() );
}

void TextureAsset::setName( const QString& newName )
{
    GluonGraphics::Engine::instance()->removeTexture( name() );
    if( d->texture )
        GluonGraphics::Engine::instance()->addTexture( newName, d->texture );
    GluonEngine::Asset::setName( newName );
}

GluonGraphics::Texture* TextureAsset::texture() const
{
    return GluonGraphics::Engine::instance()->texture( name() );
}


Q_EXPORT_PLUGIN2( gluon_asset_texture, GluonEngine::TextureAsset )

#include "textureasset.moc"
