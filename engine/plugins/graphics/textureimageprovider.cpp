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

#include "textureimageprovider.h"

#include <core/resourcemanager.h>

#include <engine/game.h>

#include <graphics/texture.h>
#include <graphics/defaults.h>

using namespace GluonEngine;

TextureImageProvider::TextureImageProvider()
    : QQuickImageProvider( QQuickImageProvider::Image )
{

}

TextureImageProvider::~TextureImageProvider()
{

}

QImage TextureImageProvider::requestImage( const QString& id, QSize* size, const QSize& requestedSize )
{
    GluonCore::GluonObject* obj = Game::instance()->gameProject()->findGlobalItemByName( id );
    if( !obj )
        return defaultImage();

    GluonEngine::Asset* asset = qobject_cast<GluonEngine::Asset*>( obj );
    if( !asset )
        return defaultImage();

    if( !asset->data()->hasText() )
    {
        asset->load();
        if( !asset->data()->hasText() )
            return defaultImage();
    }


    GluonGraphics::Texture* tex = GluonCore::ResourceManager::instance()->resource< GluonGraphics::Texture >( asset->data()->text() );
    *size = tex->image().size();
    if( requestedSize.isValid() )
    {
        return tex->image().scaled( requestedSize );
    }
    else
    {
        return tex->image();
    }
}

QImage TextureImageProvider::defaultImage()
{
    return GluonCore::ResourceManager::instance()->resource< GluonGraphics::Texture >( GluonGraphics::Defaults::Texture )->image();
}
