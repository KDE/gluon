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

#include "materialasset.h"

#include <graphics/material.h>
#include <graphics/materialinstance.h>
#include <graphics/engine.h>

#include <core/gdlhandler.h>

#include <QtGui/QAction>

REGISTER_OBJECTTYPE( GluonEngine, MaterialAsset )

using namespace GluonEngine;

class MaterialAsset::MaterialAssetPrivate
{
    public:
        MaterialAssetPrivate() : material( 0 ) {}
        ~MaterialAssetPrivate() {}

        QPixmap icon;

        GluonGraphics::Material* material;

        QList<QAction*> actions;
};

MaterialAsset::MaterialAsset( QObject* parent )
    : Asset( parent )
    , d( new MaterialAssetPrivate )
{
    QAction* newInstance = new QAction( "New instance", 0 );
    connect( newInstance, SIGNAL(triggered(bool)), SLOT(createInstance()) );
    d->actions.append( newInstance );
}

MaterialAsset::~MaterialAsset()
{
    // TODO: MaterialAsset needs to clean up after itself. This needs loading process fixes though.
    //if(d->material)
    //    GluonGraphics::Engine::instance()->destroyMaterial(name());
    qDeleteAll( d->actions );
    delete d;
}

QIcon MaterialAsset::icon() const
{
    if( d->icon.isNull() )
        return GluonEngine::Asset::icon();

    return QIcon( d->icon );
}

const QStringList MaterialAsset::supportedMimeTypes() const
{
    QStringList types;

    types << "application/x-gluon-material";

    return types;
}

void MaterialAsset::load()
{
    if( !file().isEmpty() )
    {
        if( !d->material )
            d->material = GluonGraphics::Engine::instance()->createMaterial( name() );

        if( d->material->load( file() ) )
        {
            d->material->build();
            mimeData()->setText( name() );

            Asset::load();
            return;
        }
    }

    debug( "Error loading material: %1", name() );
}

const QList<AssetTemplate*> MaterialAsset::templates()
{
    QList<AssetTemplate*> templates;
    templates.append( new AssetTemplate( "Material", "material_template.gml", "material", this ) );
    templates.append( new AssetTemplate( "Animated Sprite Material", "animatedsprite_template.gml", "material", this ) );
    return templates;
}

QList<QAction*> MaterialAsset::actions()
{
    return d->actions;
}

void MaterialAsset::setName( const QString& newName )
{
    if( d->material )
    {
        GluonGraphics::Engine::instance()->removeMaterial( name() );
        GluonGraphics::Engine::instance()->addMaterial( newName, d->material );
    }
    GluonEngine::Asset::setName( newName );
}

bool MaterialAsset::shouldSerializeChildren() const
{
    return true;
}

void MaterialAsset::sanitize()
{
    GluonCore::GluonObject::sanitize();

    if( !d->material )
        d->material = GluonGraphics::Engine::instance()->createMaterial( name() );

    QObjectList allChildren = children();
    foreach( QObject * child, allChildren )
    {
        GluonGraphics::MaterialInstance* instance = qobject_cast<GluonGraphics::MaterialInstance*>( child );
        if( instance && d->material )
            instance->setMaterial( d->material );
    }
}

void MaterialAsset::createInstance()
{
    if( !isLoaded() )
        return;

    GluonGraphics::MaterialInstance* instance = new GluonGraphics::MaterialInstance( this );
    instance->setName( "New Instance" );
    instance->setPropertiesFromMaterial();
    instance->setMaterial( d->material );

    emit instanceCreated(instance);
}

Q_EXPORT_PLUGIN2( gluon_asset_material, GluonEngine::MaterialAsset )

#include "materialasset.moc"
