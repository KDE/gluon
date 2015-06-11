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

#include <core/log.h>
#include <core/gluonobjectfactory.h>
#include <graphics/renderwindow.h>
#include <graphics/defaults.h>
#include <engine/gameproject.h>
#include <engine/game.h>
#include <engine/scene.h>
#include <engine/gameobject.h>
#include <engine/component.h>

int main(int argc, char** argv)
{
    QGuiApplication app{ argc, argv };
    app.setApplicationName("Gluon Components Example");
    app.setApplicationVersion(GluonCore::Global::versionString());

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    auto project = new GluonEngine::GameProject{ };

    auto scene = new GluonEngine::Scene{ project };
    project->addChild( scene );
    project->setEntryPoint( scene );

    GluonEngine::Game::instance()->setGameProject( project );

    scene->sceneContents()->setName( "Scene" );
    DEBUG() << scene->sceneContents();

    auto gameObject = new GluonEngine::GameObject{ scene->sceneContents() };
    gameObject->setName( "Sprite" );
    scene->sceneContents()->addChild( gameObject );
    auto component = static_cast< GluonEngine::Component* >( GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( "GluonEngine::SpriteRendererComponent" ) );
    gameObject->addComponent( component );

    gameObject = new GluonEngine::GameObject{ scene->sceneContents() };
    gameObject->setName( "Camera" );
    scene->sceneContents()->addChild( gameObject );
    component = static_cast< GluonEngine::Component* >( GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( "GluonEngine::CameraControllerComponent" ) );
    component->setProperty("active", true);
    gameObject->addComponent( component );
    gameObject->setPosition( 0.0, 0.0, 10.0 );

    auto window = new GluonGraphics::RenderWindow{ };
    window->show();

    QObject::connect( window, &QWindow::visibleChanged, GluonEngine::Game::instance(), &GluonEngine::Game::stopGame );
    QObject::connect( GluonEngine::Game::instance(), &GluonEngine::Game::painted, window, &GluonGraphics::RenderWindow::render );

    GluonGraphics::Defaults::initialize();

    app.processEvents();

    GluonEngine::Game::instance()->runGame();
}
