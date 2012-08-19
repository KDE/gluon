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

#include "interfacerenderercomponent.h"
#include <asset.h>

#include <graphics/manager.h>
#include <graphics/rendertarget.h>
#include <graphics/qtquickrenderer.h>

REGISTER_OBJECTTYPE( GluonEngine, InterfaceRendererComponent )

using namespace GluonEngine;

class InterfaceRendererComponent::Private
{
    public:
        Private() : renderer( 0 ) { }

        GluonGraphics::QtQuickRenderer* renderer;
        Asset* asset;
};

InterfaceRendererComponent::InterfaceRendererComponent( QObject* parent )
    : Component( parent ), d( new Private )
{

}

InterfaceRendererComponent::~InterfaceRendererComponent()
{
    delete d;
}

QString InterfaceRendererComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void InterfaceRendererComponent::initialize()
{
    d->asset->load();
    d->renderer = GluonGraphics::Manager::instance()->resource< GluonGraphics::QtQuickRenderer >( d->asset->data()->text() );
    GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->addChild( d->renderer );
}

void InterfaceRendererComponent::cleanup()
{
    GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->removeChild( d->renderer );
}

Asset* InterfaceRendererComponent::qtQuickFile() const
{
    return d->asset;
}

void InterfaceRendererComponent::setQtQuickFile( Asset* asset )
{
    d->asset = asset;
}

Q_EXPORT_PLUGIN2( gluon_component_interfacerenderer, GluonEngine::InterfaceRendererComponent );

#include "interfacerenderercomponent.moc"
