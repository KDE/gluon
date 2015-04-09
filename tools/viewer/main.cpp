/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2015 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QtCore/QCommandLineParser>
#include <QtCore/QFileInfo>
#include <QtGui/QGuiApplication>

#include <gluon_global.h>

#include <core/gluonobjectfactory.h>
#include <graphics/renderwindow.h>
#include <graphics/defaults.h>
#include <engine/gameproject.h>
#include <engine/game.h>

int main(int argc, char** argv)
{
    QGuiApplication app{ argc, argv };
    app.setApplicationName("Gluon Viewer");
    app.setApplicationVersion(GluonCore::Global::versionString());

    QCommandLineParser parser;
    parser.setApplicationDescription("An application for viewing Gluon Projects");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument( "project", "The project to view." );

    parser.process(app);

    if( parser.positionalArguments().size() != 1 )
        parser.showHelp( 1 );

    QString file = parser.positionalArguments().at(0);
    QFileInfo fileInfo{ file };

    if( !fileInfo.exists() )
        parser.showHelp( 2 );

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    auto project = new GluonEngine::GameProject{ };
    project->loadFromFile( fileInfo.absoluteFilePath() );

    GluonEngine::Game::instance()->setGameProject( project );

    auto window = new GluonGraphics::RenderWindow{ };
    window->show();

    QObject::connect( window, &QWindow::visibleChanged, GluonEngine::Game::instance(), &GluonEngine::Game::stopGame );

    GluonGraphics::Defaults::initialize();

    app.processEvents();

    GluonEngine::Game::instance()->runGame();
}
