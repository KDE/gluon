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

#include "meshrenderercomponent.h"

#include <engine/gameobject.h>
#include <engine/asset.h>
#include <engine/game.h>

#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/filemesh.h>
#include <graphics/materialinstance.h>
#include <graphics/texture.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>

REGISTER_OBJECTTYPE( GluonEngine, MeshRendererComponent )

using namespace GluonEngine;

class MeshRendererComponent::Private
{
    public:
        Private()
            : item( 0 ), material( 0 ), mesh( 0 )
        {
        }

        GluonGraphics::Entity* item;
        GluonGraphics::MaterialInstance* material;
        GluonEngine::Asset* mesh;
};

MeshRendererComponent::MeshRendererComponent( QObject* parent )
    : Component( parent ), d( new Private )
{

}

MeshRendererComponent::~MeshRendererComponent()
{
    if( d->material )
    {
        d->material->deref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->deref();
    }

    if( d->mesh )
        d->mesh->deref();

    delete d;
}

QString MeshRendererComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void MeshRendererComponent::initialize()
{
    if( !d->mesh )
        return;

    d->mesh->load();
    if( !d->item )
    {
        d->item = GluonGraphics::Engine::instance()->createItem( d->mesh->data()->text() );
    }

    if( d->material )
    {
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->load();

        Asset* texture = 0;
        if( d->material->property( "texture0" ).type() == QVariant::String )
        {
            QString theName( d->material->property( "texture0" ).toString() );
            texture = gameProject()->findChild<Asset*>( theName );
            if( !texture )
                debug( QString( "Texture failed to load - attempted to load texture named %1 (searched for %2)" ).arg( theName ).arg( theName ) );
        }
        else
            texture = qobject_cast<Asset*>( GluonCore::GluonObjectFactory::instance()->wrappedObject( d->material->property( "texture0" ) ) );

        if( texture )
            texture->load();
        d->item->setMaterialInstance( d->material );
    }
}

void MeshRendererComponent::start()
{
}

void MeshRendererComponent::draw( int /* timeLapse */ )
{
    if( d->item )
    {
        d->item->setTransform( gameObject()->transform() );
    }
}

void MeshRendererComponent::cleanup()
{
    if( d->item )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->item );
        d->item = 0;
    }
}

Asset*
MeshRendererComponent::mesh()
{
    return d->mesh;
}

GluonGraphics::MaterialInstance*
MeshRendererComponent::material()
{
    return d->material;
}

void
MeshRendererComponent::setMesh( Asset* mesh )
{
    if( d->mesh )
        d->mesh->deref();

    d->mesh = mesh;

    if( d->mesh )
    {
        d->mesh->ref();
    }
}

void MeshRendererComponent::setMaterial( GluonGraphics::MaterialInstance* material )
{
    if( d->material )
    {
        d->material->deref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->deref();
    }
    d->material = material;
    if( d->material )
    {
        d->material->ref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->ref();
    }

    if( d->item )
    {
        if( material )
        {
            d->item->setMaterialInstance( material );
        }
        else
        {
            d->item->setMaterialInstance( GluonGraphics::Engine::instance()->material( "default" )->instance( "default" ) );
        }
    }
}

void MeshRendererComponent::setMaterial( const QString& path )
{
    setMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findGlobalItemByName( path ) ) );
}

Q_EXPORT_PLUGIN2( gluon_component_meshrenderer, GluonEngine::MeshRendererComponent );

#include "meshrenderercomponent.moc"
