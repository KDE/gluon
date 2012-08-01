/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
    qDebug()<< "IN UNDO OF ADD NEW OBJECT";
    d->applied = false;
  //  if( d->parent->children().indexOf( object() ) != -1 )
        d->parent->removeChild( object() );

    GluonEngine::GameObject* obj = qobject_cast<GluonEngine::GameObject*>( object() );
    if( obj )
    {
        if( obj->parentGameObject()->childIndex( obj ) != -1 )		// if item matches true
            obj->parentGameObject()->removeChild( obj );
    }

    GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( object() );
    if( comp )
        comp->gameObject()->removeComponent( comp );
    AbstractUndoCommand::undo();
}

void NewObjectCommand::redo()
{
    setCommandDirection( "redo" );
    qDebug()<< "IN REDO OF ADD NEW OBJECT";
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

