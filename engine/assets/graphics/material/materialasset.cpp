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

#include "materialasset.h"

#include <core/metainfo.h>
#include <graphics/material.h>
#include <graphics/materialinstance.h>
#include <graphics/manager.h>

#include <QtGui/QAction>

REGISTER_OBJECTTYPE( GluonEngine, MaterialAsset )

using namespace GluonEngine;

class MaterialAsset::Private
{
    public:
        Private() : material( 0 ) { }

        GluonGraphics::Material* material;
        QList<QAction*> actions;
};

MaterialAsset::MaterialAsset( QObject* parent )
    : Asset( parent ), d( new Private )
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

const QStringList MaterialAsset::supportedMimeTypes() const
{
    QStringList types;

    types << "application/x-gluon-material";

    return types;
}

void MaterialAsset::load()
{
    if( isLoaded() )
        return;

    if( !file().isEmpty() )
    {
        if( !d->material )
            d->material = GluonGraphics::Manager::instance()->createResource< GluonGraphics::Material >( name() );

        if( d->material->load( absolutePath() ) )
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
        GluonGraphics::Manager::instance()->removeResource< GluonGraphics::Material >( name() );
        GluonGraphics::Manager::instance()->addResource< GluonGraphics::Material >( newName, d->material );
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
        d->material = GluonGraphics::Manager::instance()->createResource< GluonGraphics::Material >( name() );

    QObjectList allChildren = children();
    foreach( QObject * child, allChildren )
    {
        GluonGraphics::MaterialInstance* instance = qobject_cast< GluonGraphics::MaterialInstance* >( child );
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
    instance->setMaterial( d->material );

    emit instanceCreated(instance);
}

Q_EXPORT_PLUGIN2( gluon_asset_material, GluonEngine::MaterialAsset )

#include "materialasset.moc"
