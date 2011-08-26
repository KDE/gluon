/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "bteditorpart.h"

#include <graphics/renderwidget.h>
#include <graphics/viewport.h>
#include <graphics/engine.h>

#include <engine/gameproject.h>
#include <engine/game.h>

#include <input/inputmanager.h>

#include <kdemacros.h>
#include <kparts/genericfactory.h>
#include <KDE/KActionCollection>
#include <KDE/KAction>

#include <QtGui/QWidget>
#include <QtCore/QTimer>

using namespace GluonCreator;
using namespace GluonGraphics;

class btEditorPart::btEditorPartPrivate
{
    public:
        GluonGraphics::RenderWidget* widget;
        GluonEngine::GameProject* project;

        bool autoplay;
};

GluonCreator::btEditorPart::btEditorPart( QWidget* /* parentWidget */, QObject* parent, const QVariantList& args )
    : ReadWritePart( parent )
    , d( new btEditorPartPrivate )
{
    KComponentData data( "bteditorpart", "gluoncreator" );
    setComponentData( data );

    d->autoplay = true;
    d->widget = new GluonGraphics::RenderWidget();
    setWidget( d->widget );

    connect( GluonGraphics::Engine::instance(), SIGNAL( currentViewportChanging( Viewport* ) ),
             SLOT( newViewport( Viewport* ) ) );
    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), d->widget, SLOT( updateGL() ) );

    newViewport( GluonGraphics::Engine::instance()->currentViewport() );

    foreach( const QVariant & arg, args )
    {
        QString keyValue = arg.toString();
        if( keyValue == "autoplay=false" )
            d->autoplay = false;
    }


    main=new bteditor();
    setWidget (main);

    setXMLFile( "gluon_bteditor.rc" );

}

GluonCreator::btEditorPart::~btEditorPart()
{
    GluonEngine::Game::instance()->stopGame();
    delete d;
}

bool GluonCreator::btEditorPart::openFile()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    d->project = new GluonEngine::GameProject();
    d->project->loadFromFile( url() );

    GluonEngine::Game::instance()->setGameProject( d->project );
    GluonEngine::Game::instance()->setCurrentScene( d->project->entryPoint() );

    if( d->autoplay )
    {
        QTimer::singleShot( 100, this, SLOT( startGame() ) );
    }

    return true;
}

void btEditorPart::startGame()
{
    d->widget->setFocus();
    GluonEngine::Game::instance()->runGame();
}

void btEditorPart::setSolid()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void btEditorPart::setWireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void btEditorPart::setPoints()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
}

void btEditorPart::setSelect()
{
}

void btEditorPart::setTranslate()
{
}

void btEditorPart::setRotate()
{
}

void btEditorPart::setScale()
{
}

void btEditorPart::setSnap()
{
}

void btEditorPart::newViewport( Viewport* viewport )
{
    disconnect( GluonGraphics::Engine::instance()->currentViewport(), 0, this, SLOT( redraw() ) );
    connect( viewport, SIGNAL( viewportSizeChanged( int, int, int, int ) ), SLOT( redraw() ) );
}

void btEditorPart::redraw()
{
    GluonEngine::Game::instance()->drawAll();
}

K_PLUGIN_FACTORY( btEditorPartFactory, registerPlugin<btEditorPart>(); )
K_EXPORT_PLUGIN( btEditorPartFactory( "btEditorPart", "btEditorPart" ) )
