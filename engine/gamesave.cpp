/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
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

#include "gamesave.h"
#include "gamesaveprivate.h"

#include "gameobject.h"
#include "game.h"
#include "scenegraph.h"
#include "gameproject.h"
#include "component.h"

#include <core/gluonobject.h>
#include <core/gdlserializer.h>

#include <QDebug>

using namespace GluonEngine;

GLUON_DEFINE_SINGLETON( GameSave )

GameSave::GameSave( QObject *parent ) : GluonCore::GluonObject( parent )
    , g( new GameSavePrivate( this ) )
{
}

GameSave::~GameSave()
{
}

void GameSave::save()
{
    bool pause = Game::instance()->isPaused();
    if( !pause )
        Game::instance()->setPause( true );
    partialSave();
    if( ! pause )
        Game::instance()->setPause( false );
}

void GameSave::load()
{
    partialLoad();
}

void GameSave::partialSave()
{
    GluonEngine::SceneGraph *scene = new GluonEngine::SceneGraph();
    QString savefile = g->saveGamesDirectory + GluonEngine::Game::instance()->gameProject()->name() + ".gluonsave";
    QUrl savefilename( savefile );
    if( ! GluonCore::GDLSerializer::instance()->write( savefilename, GluonCore::GluonObjectList() << scene->forSave() ) )
        qDebug() << "Couldn't save to preset location";
    serializeComponents( GluonEngine::Game::instance()->currentScene()->sceneContents() );
}

void GameSave::partialLoad()
{
    QString loadfile = g->saveGamesDirectory + GluonEngine::Game::instance()->gameProject()->name() + ".gluonsave";
    QUrl loadfilename( loadfile );
    GluonCore::GluonObjectList objects;
    GluonEngine::GameProject* project = GluonEngine::Game::instance()->gameProject();
    if( GluonCore::GDLSerializer::instance()->read( loadfilename, objects, project, 0 ) )
    {
        GluonEngine::GameObject* load = qobject_cast<GluonEngine::GameObject*>( objects.at( 0 )->child( 0 ) );
        load->setParentGameObject( 0 );
        GluonEngine::SceneGraph *scene = new GluonEngine::SceneGraph( load );
        scene->setRefGraph( objects.at( 0 )->property( "refers" ).toUrl() );
        load = scene->forLoad();
        GluonEngine::Game::instance()->loadScene( load );
        restoreComponents( load );
    }
}

void GameSave::restoreComponents( GluonEngine::GameObject* object )
{
    for( int i = 0; i < object->components().count(); i++ )
        object->components().at( i )->restore();
    for( int i = 0; i < object->childCount(); i++ )
        restoreComponents( object->childGameObject( i ) );
}

void GameSave::serializeComponents( GluonEngine::GameObject* object )
{
    for( int i = 0; i < object->components().count(); i++ )
        object->components().at( i )->serialize();
    for( int i = 0; i < object->childCount(); i++ )
        serializeComponents( object->childGameObject( i ) );
}

#include "gamesave.moc"