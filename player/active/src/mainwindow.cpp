/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2012 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright 2011 Sebastian Kügler <sebas@kde.org>
 * Copyright 2011 Marco Martin <mart@kde.org>
 * Copyright 2011 Laszlo Papp <lpapp@kde.org>
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

#include "mainwindow.h"

#include <lib/gamemetadata.h>
#include <lib/gamemanager.h>
#include <lib/models/commentsmodel.h>
#include <lib/serviceprovider.h>
#include <lib/models/allgameitemsmodel.h>
#include <lib/models/gameitem.h>

#include <engine/game.h>
#include <input/inputmanager.h>
#include <graphics/renderwidget.h>

#include <kdeclarativeview.h>

#include <QtDeclarative/QtDeclarative>

MainWindow::MainWindow()
{
    declarativeView()->setPackageName("org.kde.gluon.player");

    declarativeView()->rootContext()->setContextProperty( "installedGamesModel",
                                                          GluonPlayer::GameManager::instance()->installedGamesModel() );
    declarativeView()->rootContext()->setContextProperty( "downloadableGamesModel",
                                                          GluonPlayer::GameManager::instance()->downloadableGamesModel() );
    declarativeView()->rootContext()->setContextProperty( "serviceProvider",
                                                          GluonPlayer::ServiceProvider::instance() );
    declarativeView()->rootContext()->setContextProperty( "mainWindow",
                                                          this );
    qmlRegisterType<GluonPlayer::GameMetadata>( "org.kde.gluon.player", 1, 0, "GameMetadata" );
    qmlRegisterType<GluonPlayer::CommentsModel>( "org.kde.gluon.player", 1, 0, "CommentsModel" );
    qmlRegisterUncreatableType<GluonPlayer::GameItem>( "org.kde.gluon.player", 1, 0, "GameItem", "To be used only for enums" );
}

void MainWindow::playGame(const QString& gameId)
{
    GluonPlayer::AllGameItemsModel *model
        = qobject_cast<GluonPlayer::AllGameItemsModel*>(GluonPlayer::GameManager::instance()->allGamesModel());
    const QString projectPath = model->data(gameId, GluonPlayer::AllGameItemsModel::UriRole).toString();
    openProject(projectPath);
}

void MainWindow::openProject(const QString& projectPath)
{
    if( projectPath.isEmpty() )
    {
        return;
    }

    m_projectPath = projectPath;

    GluonGraphics::RenderWidget *widget = new GluonGraphics::RenderWidget( this );
    setCentralWidget( widget );
    widget->setFocus();
    connect( GluonEngine::Game::instance(), SIGNAL(painted(int)), widget, SLOT(updateGL()) );
    GluonInput::InputManager::instance()->setFilteredObject( widget );

    QTimer::singleShot( 100, this, SLOT(startGame()) );
}

void MainWindow::startGame()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();
    GluonEngine::GameProject *project = new GluonEngine::GameProject( this );
    project->loadFromFile(m_projectPath);
    GluonEngine::Game::instance()->setGameProject( project );
    GluonEngine::Game::instance()->setCurrentScene( project->entryPoint() );

    GluonEngine::Game::instance()->runGame();
    QApplication::instance()->exit();
}

#include "mainwindow.moc"
