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

#include "gameprivate.h"
#include "game.h"
#include "scene.h"

#include <core/debughelper.h>

using namespace GluonEngine;

GamePrivate::GamePrivate( Game* qq )
    : q( qq )
    , gameRunning( false )
    , gamePaused( false )
    , currentScene( 0 )
    , newScene( 0 )
    , resetScene( false )
    , gameProject( 0 )
{
}

GamePrivate::GamePrivate( const GamePrivate& other )
    : QSharedData( other )
    , time( other.time )
    , gameRunning( other.gameRunning )
    , gamePaused( other.gamePaused )
    , currentScene( other.currentScene )
    , newScene( 0 )
    , resetScene( other.resetScene )
    , gameProject( other.gameProject )
{
}

GamePrivate::~GamePrivate()
{
}

void GamePrivate::performSceneChange()
{
    if( currentScene )
    {
        q->stopAll();
        q->cleanupAll();
    }

    currentScene = newScene;
    newScene = 0;

    if( gameRunning )
    {
        q->initializeAll();
        q->startAll();
    }

    emit q->currentSceneChanged( currentScene );
}

QList<const GluonCore::GluonObject*>
GamePrivate::listAllChildren( const GluonCore::GluonObject* root ) const
{
    QList<const GluonCore::GluonObject*> list;
    if( root )
    {
        list.append( root );
        foreach( const QObject * child, root->children() )
        {
            list.append( listAllChildren( qobject_cast<const GluonCore::GluonObject*>( child ) ) );
        }
    }
    return list;
}

Scene*
GamePrivate::findSceneInChildren( QObject* object )
{
    DEBUG_BLOCK
    foreach( QObject * child, object->children() )
    {
        DEBUG_TEXT2( "Checking child %1", qobject_cast<GluonCore::GluonObject*>( child )->fullyQualifiedName() )
        Scene* scene = qobject_cast<Scene*>( child );
        if( scene )
            return scene;
        else
        {
            Scene* foundChild = findSceneInChildren( child );
            if( foundChild )
                return foundChild;
        }
    }
    return NULL;
}
