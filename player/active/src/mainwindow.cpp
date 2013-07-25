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
#include <lib/models/commentitemsmodel.h>
#include <lib/serviceprovider.h>
#include <lib/models/allgameitemsmodel.h>
#include <lib/models/gameitem.h>
#include <lib/gamedownloadjob.h>

#include <engine/game.h>
#include <input/inputmanager.h>
#include <graphics/renderwidget.h>

#include <Plasma/Package>

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeView>

MainWindow::MainWindow()
{
    QDeclarativeView *view = new QDeclarativeView(this);
    view->rootContext()->setContextProperty( "installedGamesModel",
                                                          GluonPlayer::GameManager::instance()->installedGamesModel() );
    view->rootContext()->setContextProperty( "downloadableGamesModel",
                                                          GluonPlayer::GameManager::instance()->downloadableGamesModel() );
    view->rootContext()->setContextProperty( "serviceProvider",
                                                          GluonPlayer::ServiceProvider::instance() );
    view->rootContext()->setContextProperty( "mainWindow",
                                                          this );
    qmlRegisterType<GluonPlayer::GameMetadata>( "org.kde.gluon.playercomponents", 1, 0, "GameMetadata" );
    qmlRegisterType<GluonPlayer::CommentItemsModel>( "org.kde.gluon.playercomponents", 1, 0, "CommentItemsModel" );
    qmlRegisterUncreatableType<GluonPlayer::GameItem>( "org.kde.gluon.playercomponents", 1, 0, "GameItem", "To be used only for enums" );
    qmlRegisterUncreatableType<GluonPlayer::GameDownloadJob>( "org.kde.gluon.playercomponents", 1, 0, "GameDownloadJob", "Get an instance from serviceProvider" );

    m_kdeclarative.setDeclarativeEngine(view->engine());
    m_kdeclarative.initialize();
    m_kdeclarative.setupBindings();

    Plasma::Package *package = new Plasma::Package(QString(), "org.kde.gluon.player", Plasma::PackageStructure::load("Plasma/Generic"));
    view->setSource(QUrl(package->filePath("mainscript")));
    setCentralWidget(view);
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
