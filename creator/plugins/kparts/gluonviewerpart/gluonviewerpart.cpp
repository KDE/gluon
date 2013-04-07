/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "gluonviewerpart.h"

#include <graphics/renderwidget.h>
#include <graphics/viewport.h>
#include <graphics/manager.h>

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

class GluonViewerPart::GluonViewerPartPrivate
{
    public:
        GluonViewerPartPrivate() : project(0), autoplay( false ), forceLoad( false ) { }

        GluonGraphics::RenderWidget* widget;
        GluonEngine::GameProject* project;

        bool autoplay;
        bool forceLoad;
};

GluonCreator::GluonViewerPart::GluonViewerPart( QWidget* /* parentWidget */, QObject* parent, const QVariantList& args )
    : ReadOnlyPart( parent ),
      d( new GluonViewerPartPrivate )
{
    KComponentData data( "gluonviewerpart", "gluoncreator" );
    setComponentData( data );

    d->widget = new GluonGraphics::RenderWidget();
    setWidget( d->widget );

    GluonGraphics::Manager::instance()->initialize();
    connect( GluonEngine::Game::instance(), SIGNAL(painted(int)), d->widget, SLOT(update()) );

    foreach( const QVariant & arg, args )
    {
        QString keyValue = arg.toString();
        if( keyValue == "autoplay" )
            d->autoplay = true;

        if( keyValue == "forceLoad" )
            d->forceLoad = true;
    }

    QActionGroup* group = new QActionGroup( actionCollection() );
    group->setExclusive( true );

    KAction* solid = new KAction( KIcon( "draw-polyline" ), i18nc( "Draw type", "Solid" ), actionCollection() );
    solid->setCheckable( true );
    solid->setChecked( true );
    connect( solid, SIGNAL(triggered(bool)), SLOT(setSolid()) );
    group->addAction( solid );
    actionCollection()->addAction( "toggleSolidAction", solid );

    KAction* wire = new KAction( KIcon( "draw-line" ), i18n( "Wireframe" ), actionCollection() );
    wire->setCheckable( true );
    connect( wire, SIGNAL(triggered(bool)), SLOT(setWireframe()) );
    group->addAction( wire );
    actionCollection()->addAction( "toggleWireframeAction", wire );

    KAction* points = new KAction( KIcon( "edit-node" ), i18n( "Points" ), actionCollection() );
    points->setCheckable( true );
    connect( points, SIGNAL(triggered(bool)), SLOT(setPoints()) );
    group->addAction( points );
    actionCollection()->addAction( "togglePointsAction", points );

    setXMLFile( "gluonviewerpartui.rc" );
    GluonInput::InputManager::instance()->setFilteredObject( d->widget );
}

GluonCreator::GluonViewerPart::~GluonViewerPart()
{
    GluonEngine::Game::instance()->stopGame();
    delete d;
}

bool GluonCreator::GluonViewerPart::openFile()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    if( !GluonEngine::Game::instance()->gameProject() || d->forceLoad )
    {
        d->project = new GluonEngine::GameProject();
        d->project->loadFromFile( url() );

        GluonEngine::Game::instance()->setGameProject( d->project );
        GluonEngine::Game::instance()->setCurrentScene( d->project->entryPoint() );
    }
    else
    {
        d->project = GluonEngine::Game::instance()->gameProject();
    }

    if( d->autoplay )
    {
        QTimer::singleShot( 100, this, SLOT(startGame()) );
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
}

void GluonViewerPart::setWireframe()
{
}

void GluonViewerPart::setPoints()
{
}

void GluonViewerPart::newViewport( Viewport* viewport )
{
}

void GluonViewerPart::redraw()
{
    GluonEngine::Game::instance()->drawAll();
}

K_PLUGIN_FACTORY( GluonViewerPartFactory, registerPlugin<GluonViewerPart>(); )
K_EXPORT_PLUGIN( GluonViewerPartFactory( "GluonViewerPart", "GluonViewerPart" ) )
