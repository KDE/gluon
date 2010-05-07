/******************************************************************************
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

#include "mainwindow.h"

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/glwidget.h>
#include <graphics/fpscounter.h>
#include <player/models/gamesmodel.h>

#include <QtGui/QFileDialog>
#include <QtGui/QStatusBar>
#include <QtGui/QApplication>
#include <QtGui/QListView>

using namespace GluonPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        QString fileName;

        GluonEngine::GameProject *project;

        GluonGraphics::GLWidget *widget;

        QString title;
};

GluonPlayer::MainWindow::MainWindow(int argc, char** argv, QWidget* parent, Qt::WindowFlags flags)
        : QMainWindow(parent, flags)
{
    d = new MainWindowPrivate;

    if (argc > 1)
    {
        d->fileName = argv[1];
    }

    QListView *view = new QListView();
    view->setModel(new GamesModel(view));
    setCentralWidget(view);
}

void MainWindow::openProject(const QString& fileName)
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    d->project = new GluonEngine::GameProject();
    d->project->loadFromFile(QUrl(fileName));

    setWindowFilePath(fileName);
    d->title = windowTitle();

    GluonEngine::Game::instance()->setGameProject(d->project);
    GluonEngine::Game::instance()->setCurrentScene(d->project->entryPoint());

    d->widget = new GluonGraphics::GLWidget(this);
    setCentralWidget(d->widget);
    connect(GluonEngine::Game::instance(), SIGNAL(painted(int)), d->widget, SLOT(updateGL()));
    connect(GluonEngine::Game::instance(), SIGNAL(painted(int)), SLOT(updateTitle()));

    GluonEngine::Game::instance()->runGame();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    GluonEngine::Game::instance()->stopGame();
    QWidget::closeEvent(event);
}

void MainWindow::updateTitle()
{
    QString fps = d->widget->fpsCounter()->fpsString();

    setWindowTitle(d->title + QString(" (%1 FPS)").arg(fps));
}

#include "mainwindow.moc"
