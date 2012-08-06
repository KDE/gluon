/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#include "newobjectcommand.h"
#include <QDebug>
#include <engine/gameobject.h>
#include <engine/component.h>

using namespace GluonCreator;

class NewObjectCommand::NewObjectCommandPrivate
{
    public:
        GluonCore::GluonObject* parent;
        bool applied;
};

NewObjectCommand::NewObjectCommand( GluonCore::GluonObject* newObject ) : d( new NewObjectCommandPrivate )
{
    setObject( newObject );
    childInUse = newObject;
    d->parent = qobject_cast<GluonCore::GluonObject*>( newObject->parent() );
    d->applied = true;

    setCommandName( "NewObjectCommand" );
}

NewObjectCommand::~NewObjectCommand()
{
    if( !d->applied )
        delete object();

    delete d;
}

void NewObjectCommand::undo()
{
    setCommandDirection( "undo" );
    d->applied = false;
    GluonCore::GluonObject* obj = object();
    if( obj )
    {	
	if(GluonEngine::GameObject* obj = qobject_cast<GluonEngine::GameObject*>( object() ))
 	{   
	    if( obj->parentGameObject()->childIndex( obj ) != -1 )	
		obj->parentGameObject()->removeChild( obj );
	}
	else
	{
	    childInUse->removeChild(childInUse);
	}
    }

    GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( object() );
    if( comp )
        comp->gameObject()->removeComponent( comp );
    AbstractUndoCommand::undo();	
}

void NewObjectCommand::redo()
{
    qDebug()<<"Redo New Command"; 
    setCommandDirection( "redo" );
    d->applied = true;
    object()->setParent( d->parent );

    GluonEngine::GameObject* gameObjectParent = qobject_cast< GluonEngine::GameObject* >( d->parent );
    GluonEngine::GameObject* gameObject = qobject_cast<GluonEngine::GameObject*>( object() );
    if( gameObject && gameObjectParent )
        gameObjectParent->addChild( gameObject );

    GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( object() );
    if( comp && gameObjectParent )
        gameObjectParent->addComponent( comp );
    AbstractUndoCommand::redo();
}

