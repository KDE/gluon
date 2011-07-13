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

#include "gameprojectprivate.h"

#include "savable.h"

#include <core/gluonobject.h>
#include <core/debughelper.h>

#include <QtCore/QStringList>
#include <QtCore/QDir>

using namespace GluonEngine;

GameProjectPrivate::GameProjectPrivate()
    : entryPoint( 0 )
    , icon( 0 )
    , screenshot( 0 )
    , userName( "user" )
{
}

GameProjectPrivate::GameProjectPrivate( const GameProjectPrivate& other )
    : QSharedData( other )
    , description( other.description )
    , homepage( other.homepage )
    , mediaInfo( other.mediaInfo )
    , filename( other.filename )
    , dirname( other.dirname )
    , entryPoint( other.entryPoint )
    , icon( other.icon )
    , screenshot( other.screenshot )
    , userName( other.userName )
{
}

GameProjectPrivate::~GameProjectPrivate()
{
}

bool
GameProjectPrivate::saveChildren( const GluonCore::GluonObject* parent )
{
    DEBUG_FUNC_NAME
    if( !parent )
    {
        DEBUG_TEXT( QString( "Object child was null!" ) );
        return false;
    }

    for( int i = 0; i < parent->children().size(); ++i )
    {
        GluonCore::GluonObject* child = parent->child( i );
        if( child && Savable::saveToFile( child ) )
        {
            DEBUG_TEXT2( "Saved object named %1", child->name() );
        }

        // Recurse!
        saveChildren( qobject_cast<const GluonCore::GluonObject*>( child ) );
    }
    return true;
}
