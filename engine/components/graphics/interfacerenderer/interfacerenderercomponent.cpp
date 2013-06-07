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
#include "textureimageprovider.h"

#include <QDeclarativeContext>
#include <QDeclarativeEngine>

#include <core/messagehandler.h>
#include <graphics/manager.h>
#include <graphics/rendertarget.h>
#include <graphics/qtquickrenderer.h>
#include <input/inputmanager.h>

#include <engine/asset.h>
#include <engine/game.h>
#include <engine/gameobject.h>

REGISTER_OBJECTTYPE( GluonEngine, InterfaceRendererComponent )

using namespace GluonEngine;

class InterfaceRendererComponent::Private
{
    public:
        Private( InterfaceRendererComponent* qq ) : q( qq ), renderer( 0 ), asset( 0 ) { }
        void setRenderer( const QString& name );

        InterfaceRendererComponent* q;

        GluonGraphics::QtQuickRenderer* renderer;
        Asset* asset;
};

InterfaceRendererComponent::InterfaceRendererComponent( QObject* parent )
    : Component( parent ), d( new Private( this ) )
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
    if( d->asset )
    {
        d->asset->load();
        d->setRenderer( d->asset->data()->text() );
    }
}

void InterfaceRendererComponent::cleanup()
{
    d->setRenderer( QString() );
}

Asset* InterfaceRendererComponent::qtQuickFile() const
{
    return d->asset;
}

void InterfaceRendererComponent::setQtQuickFile( Asset* asset )
{
    d->asset = asset;
    if( asset )
        d->setRenderer( asset->data()->text() );
}

void InterfaceRendererComponent::sendEvent(QEvent* event)
{
    if( Game::instance()->isRunning() && !Game::instance()->isPaused() )
        d->renderer->deliverEvent( event );
}

void InterfaceRendererComponent::Private::setRenderer(const QString& name)
{
    if( renderer )
    {
        GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->removeChild( renderer );
        disconnect( GluonInput::InputManager::instance(), SIGNAL(eventFiltered(QEvent*)), q, SLOT(sendEvent(QEvent*)) );
    }

    renderer = GluonGraphics::Manager::instance()->resource< GluonGraphics::QtQuickRenderer >( name );

    if( renderer )
    {
        GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->addChild( renderer );
        connect( GluonInput::InputManager::instance(), SIGNAL(eventFiltered(QEvent*)), q, SLOT(sendEvent(QEvent*)) );

        QDeclarativeContext* context = renderer->context();
        context->setContextProperty( "Game", Game::instance() );
        context->setContextProperty( "GameProject", q->gameProject() );
        context->setContextProperty( "Scene", q->gameObject()->scene() );
        context->setContextProperty( "GameObject", q->gameObject() );
        context->setContextProperty( "Component", q );

        if( !context->engine()->imageProvider( "texture" ) )
            context->engine()->addImageProvider( "texture", new TextureImageProvider() );
    }
}

Q_EXPORT_PLUGIN2( gluon_component_interfacerenderer, GluonEngine::InterfaceRendererComponent );

 
