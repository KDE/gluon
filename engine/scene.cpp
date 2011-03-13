/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "scene.h"
#include "gameobject.h"
#include "sceneprivate.h"
#include "filelocation.h"
#include "gameproject.h"

#include "core/gdlhandler.h"
#include "game.h"
#include <QAction>

REGISTER_OBJECTTYPE( GluonEngine, Scene )

using namespace GluonEngine;

Scene::Scene( QObject* parent )
    : Asset( parent )
    , d( new ScenePrivate( this ) )
{
    savableDirty = false;
}

Scene::~Scene()
{
    delete d;
}

void
Scene::setFile( const QUrl& newFile )
{
    if( !savableDirty )
        d->unloadContents();
    GluonEngine::Asset::setFile( newFile );
}

void Scene::setName( const QString& newName )
{
    sceneContents()->setName( newName );
    GluonCore::GluonObject::setName( newName );
}

void Scene::resetScene()
{
    if( !d->sceneContentsLoaded )
        return;

    if(Game::instance()->isRunning())
    {
        sceneContents()->stop();
        sceneContents()->cleanup();
    }
    d->loadContents( FileLocation( qobject_cast<GameProject*>( gameProject() ), file() ).location() );
    if(Game::instance()->isRunning())
    {
        sceneContents()->initialize();
        sceneContents()->start();
    }
}

QString
Scene::contentsToGDL()
{
    return GluonCore::GDLHandler::instance()->toGDL(sceneContents());
}

GameObject *
Scene::sceneContents()
{
    if( !d->sceneContentsLoaded && !savableDirty )
        d->loadContents( FileLocation( qobject_cast<GameProject*>( gameProject() ), file() ).location() );
    return d->sceneContents;
}

QList< QAction* > Scene::actions()
{
    QList<QAction*> actions;
    QAction* setEntryPoint = new QAction("Set as entry point", this);
    connect(setEntryPoint, SIGNAL(triggered(bool)), this, SLOT(setEntryPoint()));
    actions.append(setEntryPoint);
    return actions;
}

void Scene::setEntryPoint()
{
    GluonEngine::GameProject* project = Game::instance()->gameProject();
    project->setEntryPoint(this);
}

#include "scene.moc"
