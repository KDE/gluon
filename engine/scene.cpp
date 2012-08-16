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
#include "game.h"

#include <core/metainfo.h>
#include <core/gdlserializer.h>

#include <QtGui/QAction>
#include <QDebug>
#include <QMetaClassInfo>
#include <QMetaProperty>

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
Scene::setFile( const QString& newFile )
{
    if( !savableDirty )
        d->unloadContents();
    GluonEngine::Asset::setFile( newFile );
}

void Scene::setName( const QString& newName )
{
    if( d->sceneContents )
        d->sceneContents->setName( newName );
    GluonCore::GluonObject::setName( newName );
}

void Scene::loadScene( QUrl filename )
{
    if( !d->sceneContentsLoaded )
        return;

    if( Game::instance()->isRunning() )
    {
        sceneContents()->stop();
        sceneContents()->cleanup();
    }
    
    d->loadContents( filename );

    if( Game::instance()->isRunning() )
    {
        sceneContents()->initialize();
        sceneContents()->start();
    }
}

void Scene::loadScene( GluonEngine::GameObject* newSceneContents )
{
    if( !d->sceneContentsLoaded )
        return;

    if( Game::instance()->isRunning() )
    {
        sceneContents()->stop();
        sceneContents()->cleanup();
    }
    
    d->loadContents( newSceneContents );
    
    if( Game::instance()->isRunning() )
    {
        sceneContents()->initialize();
    }
}

void Scene::resetScene()
{
    if( !d->sceneContentsLoaded )
        return;

    if( Game::instance()->isRunning() )
    {
        sceneContents()->stop();
        sceneContents()->cleanup();
    }
    d->loadContents( absolutePath() );
    emit Game::instance()->currentSceneChanged( this );
    if( Game::instance()->isRunning() )
    {
        sceneContents()->initialize();
        sceneContents()->start();
    }
}

void Scene::writeContents(QIODevice* device)
{
    GluonCore::GDLSerializer::instance()->write( device, GluonCore::GluonObjectList() << sceneContents() );
}

GameObject*
Scene::sceneContents()
{
    if( !d->sceneContentsLoaded && !savableDirty )
        d->loadContents( absolutePath() );
    return d->sceneContents;
}

QList< QAction* > Scene::actions()
{
    QList<QAction*> actions;
    QAction* setEntryPoint = new QAction( "Set as entry point", this );
    connect( setEntryPoint, SIGNAL(triggered(bool)), this, SLOT(setEntryPoint()) );
    actions.append( setEntryPoint );
    return actions;
}

void Scene::setEntryPoint()
{
    GluonEngine::GameProject* project = Game::instance()->gameProject();
    project->setEntryPoint( this );
}

void Scene::populateMetaInfo( GluonCore::MetaInfo* info )
{
    info->setDefaultExtension( "gluonscene" );
}

#include "scene.moc"
