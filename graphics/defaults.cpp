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

#include "defaults.h"

#include <core/directoryprovider.h>
#include <core/resourcemanager.h>

#include "rendertarget.h"
#include "material.h"
#include "spritemesh.h"
#include "texture.h"
#include "materialinstance.h"
#include "backend.h"
#include "world.h"

using namespace GluonGraphics;

const QString Defaults::World( "_defaultWorld" );
const QString Defaults::RenderTarget( "_defaultRenderTarget" );
const QString Defaults::Material( "_defaultMaterial" );
const QString Defaults::MaterialInstance( "_defaultMaterialInstance" );
const QString Defaults::SpriteMesh( "_defaultSpriteMesh" );
const QString Defaults::Texture( "_defaultTexture" );

void Defaults::initialize()
{
    if( !GluonCore::ResourceManager::instance()->hasResource< GluonGraphics::World >( Defaults::World ) )
    {
        GluonCore::ResourceManager::instance()->createResource< GluonGraphics::World >( Defaults::World );
    }

    if( !GluonCore::ResourceManager::instance()->hasResource< GluonGraphics::SpriteMesh >( Defaults::SpriteMesh ) )
    {
        GluonGraphics::SpriteMesh* defaultSpriteMesh = GluonCore::ResourceManager::instance()->createResource< GluonGraphics::SpriteMesh >( Defaults::SpriteMesh );
        defaultSpriteMesh->initialize();
    }

    if( !GluonCore::ResourceManager::instance()->hasResource< GluonGraphics::Texture >( Defaults::Texture ) )
    {
        GluonGraphics::Texture* defaultTexture = GluonCore::ResourceManager::instance()->createResource< GluonGraphics::Texture >( Defaults::Texture );
        defaultTexture->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/defaults/default.png" );
    }

    if( !GluonCore::ResourceManager::instance()->hasResource< GluonGraphics::Material >( Defaults::Material ) )
    {
        GluonGraphics::Material* defaultMaterial = GluonCore::ResourceManager::instance()->createResource< GluonGraphics::Material >( Defaults::Material );
        defaultMaterial->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/defaults/default.gluonmaterial" );
        defaultMaterial->build();

        GluonGraphics::MaterialInstance* defaultInstance = defaultMaterial->createInstance( Defaults::MaterialInstance );
        defaultInstance->setProperty( "texture0", Defaults::Texture );
    }

    if( !GluonCore::ResourceManager::instance()->hasResource< GluonGraphics::RenderTarget >( Defaults::RenderTarget ) )
    {
        GluonCore::ResourceManager::instance()->addResource< GluonGraphics::RenderTarget >( Defaults::RenderTarget, Backend::currentBackend()->createRenderTarget() );
    }
}
