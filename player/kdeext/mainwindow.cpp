/*****************************************************************************
 * This file is part of the Gluon Development Platform                       *
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>                     *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License along   *
 * with this program; if not, write to the Free Software Foundation, Inc.,   *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
 *****************************************************************************/

#include "mainwindow.h"

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/renderwidget.h>
#include <player/models/gamesmodel.h>

#include <KPushButton>
#include <KFileDialog>
#include <KUrl>
#include <KLocalizedString>

#include <QtGui/QStatusBar>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QLabel>
#include <QTimer>

using namespace GluonPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        MainWindowPrivate() {}

        GluonEngine::GameProject* project;
        GluonGraphics::RenderWidget* widget;

        KRecentFilesAction* recentFiles;

        QAbstractItemModel* model;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

MainWindow::MainWindow(const QString& filename )
    : KMainWindow()
    , d( new MainWindowPrivate )
{
}

MainWindow::~MainWindow ( )
{
}
