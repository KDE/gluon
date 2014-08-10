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

// #include <graphics/renderwidget.h> TODO: readd after graphics is ported
#include <graphics/viewport.h>
#include <graphics/manager.h>

#include <engine/gameproject.h>
#include <engine/game.h>

//#include <input/inputmanager.h> TODO: after Input

#include <KI18n/KLocalizedString>
#include <KXmlGui/KActionCollection>
#include <KCoreAddons/KPluginFactory>

#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtCore/QTimer>

using namespace GluonCreator;
using namespace GluonGraphics;

class GluonViewerPart::GluonViewerPartPrivate
{
    public:
        GluonViewerPartPrivate() : project(0), autoplay( false ), forceLoad( false ) { }

        //GluonGraphics::RenderWidget* widget; TODO: after Graphics
        QWidget* widget;
        GluonEngine::GameProject* project;

        bool autoplay;
        bool forceLoad;
};

GluonCreator::GluonViewerPart::GluonViewerPart( QWidget* /* parentWidget */, QObject* parent, const QVariantList& args )
    : ReadOnlyPart( parent ),
      d( new GluonViewerPartPrivate )
{
    // TODO: Learn hwo to create good kparts
    //KComponentData data( "gluonviewerpart", "gluoncreator" );
    //setComponentData( data );

    d->widget = new QWidget(); //new GluonGraphics::RenderWidget(); TODO: after graphics
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

    QAction* solid = new QAction( QIcon::fromTheme( "draw-polyline" ), i18nc( "Draw type", "Solid" ), actionCollection() );
    solid->setCheckable( true );
    solid->setChecked( true );
    connect( solid, SIGNAL(triggered(bool)), SLOT(setSolid()) );
    group->addAction( solid );
    actionCollection()->addAction( "toggleSolidAction", solid );

    QAction* wire = new QAction( QIcon::fromTheme( "draw-line" ), i18n( "Wireframe" ), actionCollection() );
    wire->setCheckable( true );
    connect( wire, SIGNAL(triggered(bool)), SLOT(setWireframe()) );
    group->addAction( wire );
    actionCollection()->addAction( "toggleWireframeAction", wire );

    QAction* points = new QAction( QIcon::fromTheme( "edit-node" ), i18n( "Points" ), actionCollection() );
    points->setCheckable( true );
    connect( points, SIGNAL(triggered(bool)), SLOT(setPoints()) );
    group->addAction( points );
    actionCollection()->addAction( "togglePointsAction", points );

    setXMLFile( "gluonviewerpartui.rc" );
    //GluonInput::InputManager::instance()->setFilteredObject( d->widget );
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
