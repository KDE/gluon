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

#include "qtquickasset.h"

#include <graphics/manager.h>
#include <graphics/rendertarget.h>

REGISTER_OBJECTTYPE( GluonEngine, QtQuickAsset )

using namespace GluonEngine;

class QtQuickAsset::Private
{
    public:
        Private() : renderer( 0 ) { }

        GluonGraphics::QtQuickRenderer* renderer;
};

QtQuickAsset::QtQuickAsset( QObject* parent )
    : Asset( parent ), d( new Private )
{
}

QtQuickAsset::~QtQuickAsset()
{
    if( d->renderer )
    {
        GluonGraphics::Manager::instance()->destroyResource< GluonGraphics::QtQuickRenderer >( name() );
        d->renderer = 0;
    }
    delete d;
}

const QStringList QtQuickAsset::supportedMimeTypes() const
{
    return QStringList() << "text/x-qml";
}

void QtQuickAsset::load()
{
    if( isLoaded() )
        return;

    if( !file().isEmpty() )
    {
        d->renderer = GluonGraphics::Manager::instance()->createResource< GluonGraphics::QtQuickRenderer >( name() );

        if( d->renderer->load( absolutePath() ) )
        {
            mimeData()->setText( name() );
            setLoaded( true );
            return;
        }
    }

    debug( "Error loading QtQuick file: %1", name() );
}

void QtQuickAsset::unload()
{
    if( d->renderer )
    {
        GluonGraphics::RenderTarget* parent = dynamic_cast< GluonGraphics::RenderTarget* >( d->renderer->parentItem() );
        if( parent )
            parent->removeChild( d->renderer );

        GluonGraphics::Manager::instance()->destroyResource< GluonGraphics::QtQuickRenderer >( name() );
        d->renderer = 0;

        setLoaded( false );
    }
}

void QtQuickAsset::reload()
{
    GluonGraphics::RenderTarget* parent = dynamic_cast< GluonGraphics::RenderTarget* >( d->renderer->parentItem() );

    GluonEngine::Asset::reload();

    if( parent )
        parent->addChild( d->renderer );
}

void QtQuickAsset::setName( const QString& newName )
{
    if( d->renderer )
    {
        GluonGraphics::Manager::instance()->removeResource< GluonGraphics::QtQuickRenderer >( name() );
        GluonGraphics::Manager::instance()->addResource< GluonGraphics::QtQuickRenderer >( newName, d->renderer );
    }
    GluonEngine::Asset::setName( newName );
}

GluonGraphics::Texture* QtQuickAsset::texture() const
{
    return d->renderer;
}

GluonGraphics::QtQuickRenderer* QtQuickAsset::renderer() const
{
    return d->renderer;
}

Q_EXPORT_PLUGIN2( gluon_asset_qtquick, GluonEngine::QtQuickAsset )

#include "qtquickasset.moc"
