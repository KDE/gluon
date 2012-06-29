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

void GameSave::debugPrint( QObject* obj)
{
    for(int i = 0; i < obj->metaObject()->propertyCount(); i++)
    {
        QMetaProperty property = obj->metaObject()->property( i );
        cout << property.name() << ": " << property.read( obj ).toString().toUtf8().constData() << ' ';
    }
    cout << endl;
    foreach ( QObject *ob, obj->children() )
        debugPrint( ob );
}

void GameSave::save()
{
    GluonCore::GluonObject *obj = GluonEngine::Game::instance()->currentScene()->sceneContents();
    bool pause_flag = Game::instance()->isPaused();
    if( !pause_flag )
        Game::instance()->setPause( true );
    QString dir = QDir::homePath().append( "/Desktop/" );
    QString savefile = QFileDialog::getSaveFileName(0, tr("Save Game"), dir, tr("Save Files (*.gs)"));
    QUrl filename(savefile);
    QList<GluonObject*> objectlist;
    objectlist.append( obj );
    AchievementsManager am;
    am.readFromProject( Game::instance()->gameProject()->achievements() );
    if( am.achievementsCount() > 0 )
        am.save(dir);
    if( !GluonCore::GDLSerializer::instance()->write( filename, objectlist) )
        qDebug() << "Error in writing to: " << filename.toString();
    if( ! pause_flag )
        Game::instance()->setPause( false );
    scenegraph();
}

void GameSave::load()
{
    //TODO: Give developer option to present list of saved slots to choose from.
    QList<GluonObject*> objectlist;
    QString dir = QDir::homePath().append( "/Desktop/" );
    QString savefile = QFileDialog::getOpenFileName(0, tr("Load Game"), dir, tr("Save Files (*.gs)"));
    QUrl filename( savefile );
    GluonEngine::Game::instance()->loadScene( filename );
    AchievementsManager am;
    am.load(dir);
}

void GameSave::scenegraph()
{
    SceneGraph *scene = new SceneGraph();
    scene->debugprint( scene->getRoot() );
}


#include "gamesave.moc"