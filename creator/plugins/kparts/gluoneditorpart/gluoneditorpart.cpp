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

#include "gluoneditorpart.h"

#include <graphics/renderwidget.h>
#include <graphics/viewport.h>
#include <graphics/engine.h>

#include <engine/gameproject.h>
#include <engine/game.h>

#include <input/inputmanager.h>

#include <kdemacros.h>
#include <kparts/genericfactory.h>
#include <KDE/KUrl>
#include <KDE/KActionCollection>
#include <KDE/KAction>

#include <QtGui/QWidget>
#include <QtCore/QThread>
#include <QtCore/QTimer>

using namespace GluonCreator;
using namespace GluonGraphics;

class GluonEditorPart::GluonEditorPartPrivate
{
    public:
        GluonGraphics::RenderWidget* widget;
        GluonEngine::GameProject* project;

        bool autoplay;
};

GluonCreator::GluonEditorPart::GluonEditorPart( QWidget* /* parentWidget */, QObject* parent, const QVariantList& args )
    : ReadWritePart( parent )
    , d( new GluonEditorPartPrivate )
{
    KComponentData data( "gluoneditorpart", "gluoncreator" );
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

    QActionGroup* group = new QActionGroup( actionCollection() );
    group->setExclusive( true );

    KAction* solid = new KAction( KIcon( "draw-polyline" ), i18nc( "Draw type", "Solid" ), actionCollection() );
    solid->setCheckable( true );
    solid->setChecked( true );
    connect( solid, SIGNAL( triggered( bool ) ), SLOT( setSolid() ) );
    group->addAction( solid );
    actionCollection()->addAction( "toggleSolidAction", solid );

    KAction* wire = new KAction( KIcon( "draw-line" ), i18n( "Wireframe" ), actionCollection() );
    wire->setCheckable( true );
    connect( wire, SIGNAL( triggered( bool ) ), SLOT( setWireframe() ) );
    group->addAction( wire );
    actionCollection()->addAction( "toggleWireframeAction", wire );

    KAction* points = new KAction( KIcon( "edit-node" ), i18n( "Points" ), actionCollection() );
    points->setCheckable( true );
    connect( points, SIGNAL( triggered( bool ) ), SLOT( setPoints() ) );
    group->addAction( points );
    actionCollection()->addAction( "togglePointsAction", points );

    KAction* select = new KAction( KIcon( "edit-select" ), i18nc( "General select", "Select" ), actionCollection() );
    select->setCheckable( true );
    connect( select, SIGNAL( triggered( bool ) ), SLOT( setSelect() ) );
    group->addAction( select );
    actionCollection()->addAction( "toggleSelectAction", select );

    KAction* translate = new KAction( KIcon( "transform-move" ), i18n( "Translate" ), actionCollection() );
    translate->setCheckable( true );
    connect( translate, SIGNAL( triggered( bool ) ), SLOT( setTranslate() ) );
    group->addAction( translate );
    actionCollection()->addAction( "toggleTranslateAction", translate );

    KAction* rotate = new KAction( KIcon( "transform-rotate" ), i18n( "Rotate" ), actionCollection() );
    rotate->setCheckable( true );
    connect( rotate, SIGNAL( triggered( bool ) ), SLOT( setRotate() ) );
    group->addAction( rotate );
    actionCollection()->addAction( "toggleRotateAction", rotate );

    KAction* scale = new KAction( KIcon( "transform-scale" ), i18n( "Scale" ), actionCollection() );
    scale->setCheckable( true );
    connect( scale, SIGNAL( triggered( bool ) ), SLOT( setScale() ) );
    group->addAction( scale );
    actionCollection()->addAction( "toggleScaleAction", scale );

    KAction* snap = new KAction( KIcon( "snap-orto" ), i18n( "Snap" ), actionCollection() );
    snap->setCheckable( true );
    connect( snap, SIGNAL( triggered( bool ) ), SLOT( setSnap() ) );
    group->addAction( snap );
    actionCollection()->addAction( "toggleSnapAction", snap );

    setXMLFile( "gluoneditorpartui.rc" );
}

GluonCreator::GluonEditorPart::~GluonEditorPart()
{
    GluonEngine::Game::instance()->stopGame();
    delete d;
}

bool GluonCreator::GluonEditorPart::openFile()
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

void GluonEditorPart::startGame()
{
    d->widget->setFocus();
    GluonEngine::Game::instance()->runGame();
}

void GluonEditorPart::setSolid()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void GluonEditorPart::setWireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void GluonEditorPart::setPoints()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
}

void GluonEditorPart::setSelect()
{
}

void GluonEditorPart::setTranslate()
{
}

void GluonEditorPart::setRotate()
{
}

void GluonEditorPart::setScale()
{
}

void GluonEditorPart::setSnap()
{
}

void GluonEditorPart::newViewport( Viewport* viewport )
{
    disconnect( GluonGraphics::Engine::instance()->currentViewport(), 0, this, SLOT( redraw() ) );
    connect( viewport, SIGNAL( viewportSizeChanged( int, int, int, int ) ), SLOT( redraw() ) );
}

void GluonEditorPart::redraw()
{
    GluonEngine::Game::instance()->drawAll();
}

K_PLUGIN_FACTORY( GluonEditorPartFactory, registerPlugin<GluonEditorPart>(); )
K_EXPORT_PLUGIN( GluonEditorPartFactory( "GluonEditorPart", "GluonEditorPart" ) )
