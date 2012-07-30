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

#include "gameobject.h"
#include "game.h"
#include "achievementsmanager.h"
#include "scenegraph.h"
#include <engine/gameproject.h>
#include "component.h"
#include <core/gluonobject.h>
#include <core/gdlserializer.h>

#include <QList>
#include <QtCore/QMetaProperty>
#include <QDir>
#include <QFileDialog>
#include <QObject>
#include <QDebug>

#include <iostream>

using namespace std;

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, GameSave )

GameSave::GameSave()
{
}

GameSave::~GameSave()
{
}

void GameSave::save()
{
    GluonCore::GluonObject *obj = GluonEngine::Game::instance()->currentScene()->sceneContents();
    bool pause_flag = Game::instance()->isPaused();
    if( !pause_flag )
        Game::instance()->setPause( true );
    QString dir = QDir::homePath().append( "/Desktop/" );
    QString savefile = QFileDialog::getSaveFileName(0, tr("Save Game"), dir, tr("Save Files (*.gluonsave)"));
    QUrl filename( savefile );
    QList<GluonObject*> objectlist;
    objectlist.append( obj );
    AchievementsManager am;
    am.readFromProject( Game::instance()->gameProject()->achievements() );
    if( am.achievementsCount() > 0 )
        am.save(dir);
    if( !GluonCore::GDLSerializer::instance()->write( filename, objectlist ) )
        qDebug() << "Error in writing to: " << filename.toString();
    if( ! pause_flag )
        Game::instance()->setPause( false );

    //These are only for testing purposes.
    partialSave();
}

void GameSave::load()
{
    //TODO: Give developer option to present list of saved slots to choose from.
    QList<GluonObject*> objectlist;
    QString dir = QDir::homePath().append( "/Desktop" );
    QString savefile = QFileDialog::getOpenFileName( 0, tr("Load Game"), dir, tr( "Save Files (*.gluonsave)" ) );
    QUrl filename( savefile );
//     GluonEngine::Game::instance()->loadScene( filename );
    partialLoad();
    AchievementsManager am;
    am.load( dir );
}

void GameSave::partialSave()
{
    GluonEngine::SceneGraph *scene = new GluonEngine::SceneGraph();
    QUrl filename( "/home/vsrao/Desktop/savefile.txt" );
    QList<GluonObject*> objectlist;
    objectlist.append( scene->forSave() );
    GluonCore::GDLSerializer::instance()->write( filename, objectlist );
    serializeComponents( GluonEngine::Game::instance()->currentScene()->sceneContents() );
}

void GameSave::partialLoad()
{
    QUrl filename( "/home/vsrao/Desktop/savefile.txt" );
    GluonCore::GluonObjectList objects;
    GluonEngine::GameProject* project = GluonEngine::Game::instance()->gameProject();
    if( GluonCore::GDLSerializer::instance()->read( filename, objects, project, 0 ) )
    {
        GluonEngine::GameObject* load = qobject_cast<GluonEngine::GameObject*>( objects.at( 0 )->child( 0 ) );
        load->setParentGameObject( 0 );
        load->setParent( 0 );
        GluonEngine::SceneGraph *scene = new GluonEngine::SceneGraph( load );
        scene->setRefGraph( objects.at( 0 )->property( "refers" ).toUrl() );
        load = scene->forLoad();
        GluonEngine::Scene *newscene = new GluonEngine::Scene();
        newscene->loadScene( load );
        GluonEngine::Game::instance()->setCurrentScene( newscene );
        QList<GluonObject*> objectlist;
        objectlist.append( load );
        QUrl loadfilename( "/home/vsrao/Desktop/loadfile.txt" );
        GluonCore::GDLSerializer::instance()->write( loadfilename, objectlist );
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