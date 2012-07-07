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

#include "scenegraphprivate.h"
#include "scenegraph.h"

#include "scenegraphobject.h"
#include "gameproject.h"

#include <core/gdlserializer.h>

using namespace GluonEngine;

SceneGraphPrivate::SceneGraphPrivate( SceneGraph* sg, bool r )
    : g( sg )
{
    root = new GluonEngine::SceneGraphObject();
    root->setMember( GluonEngine::Game::instance()->currentScene()->sceneContents() );
    ref = r;
    initHelper();
}

SceneGraphPrivate::SceneGraphPrivate( SceneGraph* sg, GluonEngine::GameObject* obj, bool r )
    :g( sg )
{
    root = new GluonEngine::SceneGraphObject();
    root->setMember( obj );
    ref = r;
    initHelper();
}

void SceneGraphPrivate::initHelper()
{
    tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
    if( !ref )
    {
        // This is just to ensure reference graphs don't have references again.
        GluonCore::GluonObjectList objects;
        if( GluonCore::GDLSerializer::instance()->read( GluonEngine::Game::instance()->currentScene()->absolutePath(), objects, 0 ) )
            this->refgraph = new GluonEngine::SceneGraph( qobject_cast< GameObject*>( objects.at( 0 ) ), true );
    }
}


SceneGraphPrivate::~SceneGraphPrivate()
{
}