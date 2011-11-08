/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "btcomponents-testapp.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QUrl>

#include <core/gluonobjectfactory.h>
#include <engine/gameproject.h>
#include <engine/game.h>
#include <core/gdlhandler.h>

btcomponentstestapp::btcomponentstestapp()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();
}

btcomponentstestapp::~btcomponentstestapp()
{}

void
btcomponentstestapp::run(QUrl gdlFile)
{
    GluonEngine::GameProject *gameProject = new GluonEngine::GameProject(QCoreApplication::instance());
    gameProject->loadFromFile(gdlFile);
    
    GluonEngine::Game::instance()->setParent(QCoreApplication::instance());
    GluonEngine::Game::instance()->setGameProject(gameProject);
    
    //qDebug() << "The gameProject turned into GDL:" << gameProject->toGDL();
    
    // Run the game at severely reduced speed (one frame per second) so we can
    // actually see what's happening
    GluonEngine::Game::instance()->runGameFixedTimestep(1);
}

#include "btcomponents-testapp.moc"
