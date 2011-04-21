/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "plasmaapplet.h"
#include "gamesoverlay.h"
#include "views/gamesview.h"
#include "gamedetailsoverlay.h"

#include <lib/models/gameitemsmodel.h>

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/renderwidget.h>
#include <graphics/rendertarget.h>
#include <input/inputmanager.h>

#include <QtGui/QFileDialog>
#include <QtGui/QGraphicsSceneResizeEvent>
#include <QtGui/QGraphicsLinearLayout>
#include <QtCore/QTimer>

using namespace GluonPlayer;
using namespace GluonGraphics;

PlasmaApplet::PlasmaApplet( QObject* parent, const QVariantList& args )
    : Plasma::Applet( parent, args )
    , m_viewportWidth( 0 )
    , m_viewportHeight( 0 )
    , m_project( 0 )
    , m_gamesOverlay( 0 )
    , m_gameDetailsOverlay( 0 )
    , m_renderer(0)
{
    setHasConfigurationInterface( true );
    setAspectRatioMode( Plasma::IgnoreAspectRatio );
    setBackgroundHints( Plasma::Applet::NoBackground );
    setMinimumSize( 200, 200 );
    resize( 500, 500 );
}

PlasmaApplet::~PlasmaApplet()
{
    kDebug() << "QUIT";

    if( m_gameFileName.isEmpty() )
    {
        return;
    }

    GluonEngine::Game::instance()->stopGame();
    GluonEngine::Game::instance()->cleanupAll();
}

void PlasmaApplet::init()
{
    m_gameItemsModel = new GameItemsModel( this );
    m_layout = new QGraphicsLinearLayout( Qt::Vertical );
    setLayout( m_layout );
    showGames();
}

void PlasmaApplet::setProject( const QModelIndex& index )
{
    m_gameFileName = index.data().toString();
    m_gamesOverlay->hide();
    openProject();
}

void PlasmaApplet::openProject()
{
    if( m_gameFileName.isEmpty() )
    {
        return;
    }

    setBusy( true );

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    m_renderer = new RenderWidget();
    connect(GluonEngine::Game::instance(), SIGNAL(painted(int)), m_renderer, SLOT(updateGL()));

    GluonInput::InputManager::instance()->setFilteredObject(m_renderer);

    m_project = new GluonEngine::GameProject();
    m_project->loadFromFile( m_gameFileName );

    GluonEngine::Game::instance()->setGameProject( m_project );
    GluonEngine::Game::instance()->setCurrentScene( m_project->entryPoint() );

    startGame();
}

void PlasmaApplet::doPaint()
{
//     update();
}

void PlasmaApplet::paintInterface(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRect& contentsRect)
{
//     if(m_renderer)
//     {
//         m_renderer->paintGL();
//         if(GluonGraphics::Engine::instance()->mainRenderTarget())
//         {
//             QImage framebuffer = GluonGraphics::Engine::instance()->mainRenderTarget()->framebufferObject()->toImage();
//             painter->drawImage(0, 0, framebuffer);
//         }
//     }
    Plasma::Applet::paintInterface(painter, option, contentsRect);
}

void PlasmaApplet::startGame()
{
    setBusy( false );
    m_renderer->show();
    m_renderer->setFocus();
    GluonEngine::Game::instance()->runGame();

    delete m_renderer;
    m_renderer = 0;
    showGames();
}

void PlasmaApplet::showGames()
{
    if( !m_gamesOverlay )
    {
        m_gamesOverlay = new GamesOverlay( this );
        m_gamesOverlay->gamesView()->setModel( m_gameItemsModel );
        m_gamesOverlay->setGeometry( geometry() );
        connect( m_gamesOverlay, SIGNAL( gameToPlaySelected( QModelIndex ) ), SLOT( setProject( QModelIndex ) ) );
        connect( m_gamesOverlay, SIGNAL( gameSelected( QModelIndex ) ), SLOT( showGameDetails( QModelIndex ) ) );
    }

    if( m_gameDetailsOverlay )
    {
        m_gameDetailsOverlay->hide();
        m_layout->removeItem( m_gameDetailsOverlay );
        m_gameDetailsOverlay->deleteLater();
        m_gameDetailsOverlay = 0;
    }

    m_layout->addItem( m_gamesOverlay );
    m_gamesOverlay->show();
}

void PlasmaApplet::showGameDetails( const QModelIndex& index )
{
    QString id = index.data( GluonPlayer::GameItemsModel::IDRole ).toString();
    if( id.isEmpty() )
    {
        return;
    }
    //TODO: the game details should be according to the game selected
    m_gameDetailsOverlay = new GameDetailsOverlay( id, this );
    m_gamesOverlay->hide();
    m_layout->removeItem( m_gamesOverlay );
    m_gameDetailsOverlay->show();
    m_layout->addItem( m_gameDetailsOverlay );
    connect( m_gameDetailsOverlay, SIGNAL( back() ), SLOT( showGames() ) );
}

void PlasmaApplet::resizeEvent(QGraphicsSceneResizeEvent* event)
{
    if(m_renderer)
        m_renderer->resize(event->newSize().width(), event->newSize().height());
    Plasma::Applet::resizeEvent(event);
}

#include "plasmaapplet.moc"
