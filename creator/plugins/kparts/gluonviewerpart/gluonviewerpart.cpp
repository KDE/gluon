/*
*****************************************************************************
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

#include "gluonviewerpart.h"

#include "input/inputmanager.h"

#include <graphics/renderwidget.h>
#include <graphics/viewport.h>
#include <graphics/engine.h>
#include <engine/gameproject.h>
#include <engine/game.h>

#include <QtGui/QWidget>
#include <kdemacros.h>
#include <kparts/genericfactory.h>
#include <KDE/KUrl>
#include <QtCore/QThread>
#include <QTimer>
#include <KActionCollection>
#include <kaction.h>

using namespace GluonCreator;
using namespace GluonGraphics;

class GluonViewerPart::GluonViewerPartPrivate
{
    public:
        GluonGraphics::RenderWidget* widget;
        GluonEngine::GameProject* project;

        bool autoplay;
};

GluonCreator::GluonViewerPart::GluonViewerPart( QWidget* parentWidget, QObject* parent, const QVariantList& args )
    : ReadOnlyPart( parent ),
      d( new GluonViewerPartPrivate )
{
    Q_UNUSED( parentWidget )

    KComponentData data( "gluonviewerpart", "gluoncreator" );
    setComponentData( data );

    d->autoplay = true;
    d->widget = new GluonGraphics::RenderWidget();
    setWidget( d->widget );

    connect( GluonGraphics::Engine::instance(), SIGNAL( currentViewportChanged( Viewport* ) ),
             this, SLOT( newViewport( Viewport* ) ) );
    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), d->widget, SLOT( updateGL() ) );

    newViewport( GluonGraphics::Engine::instance()->currentViewport() );

    foreach( const QVariant & arg, args )
    {
        QString keyValue = arg.toString();
        if( keyValue == "autoplay=false" )
            d->autoplay = false;
    }

    QActionGroup* group = new QActionGroup( actionCollection() );
    group->setExclusive( true );

    KAction* solid = new KAction( KIcon( "draw-polyline" ), i18n( "Solid" ), actionCollection() );
    solid->setCheckable( true );
    solid->setChecked( true );
    connect( solid, SIGNAL( triggered( bool ) ), this, SLOT( setSolid() ) );
    group->addAction( solid );
    actionCollection()->addAction( "toggleSolidAction", solid );

    KAction* wire = new KAction( KIcon( "draw-line" ), i18n( "Wireframe" ), actionCollection() );
    wire->setCheckable( true );
    connect( wire, SIGNAL( triggered( bool ) ), this, SLOT( setWireframe() ) );
    group->addAction( wire );
    actionCollection()->addAction( "toggleWireframeAction", wire );

    KAction* points = new KAction( KIcon( "edit-node" ), i18n( "Points" ), actionCollection() );
    points->setCheckable( true );
    connect( points, SIGNAL( triggered( bool ) ), this, SLOT( setPoints() ) );
    group->addAction( points );
    actionCollection()->addAction( "togglePointsAction", points );

    setXMLFile( "gluonviewerpartui.rc" );
    GluonInput::InputManager::instance()->setFilteredObject(d->widget);
}

GluonCreator::GluonViewerPart::~GluonViewerPart()
{
    GluonEngine::Game::instance()->stopGame();
    delete d;
}

bool GluonCreator::GluonViewerPart::openFile()
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

void GluonViewerPart::startGame()
{
    d->widget->setFocus();
    GluonEngine::Game::instance()->runGame();
}

void GluonViewerPart::setSolid()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void GluonViewerPart::setWireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void GluonViewerPart::setPoints()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
}

void GluonViewerPart::newViewport( Viewport* viewport )
{
    disconnect( 0, 0, this, SLOT( redraw() ) );
    connect( viewport, SIGNAL( viewportSizeChanged(int, int, int, int) ),
             this, SLOT( redraw() ) );
}

void GluonViewerPart::redraw()
{
    GluonEngine::Game::instance()->drawAll();
}

K_PLUGIN_FACTORY( GluonViewerPartFactory, registerPlugin<GluonViewerPart>(); )
K_EXPORT_PLUGIN( GluonViewerPartFactory( "GluonViewerPart", "GluonViewerPart" ) )

// #include "gluonviewerpart.moc"
