/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "deleteobjectcommand.h"

#include <engine/gameobject.h>

using namespace GluonCreator;

class DeleteObjectCommand::DeleteObjectCommandPrivate
{
    public:
        DeleteObjectCommandPrivate() : parent( 0 ), index( -1 ), applied( false ) { }

        GluonCore::GluonObject* parent;
        int index;
        bool applied;
};

DeleteObjectCommand::DeleteObjectCommand( GluonCore::GluonObject* object )
    : d( new DeleteObjectCommandPrivate )
{
    Q_ASSERT( object );
    setObject( object );

    d->parent = qobject_cast< GluonCore::GluonObject* >( object->parent() );
    Q_ASSERT( d->parent );

    setCommandName( "DeleteObjectCommand" );
}

DeleteObjectCommand::~DeleteObjectCommand()
{
    if( !d->applied )
        delete object();

    delete d;
}

void DeleteObjectCommand::undo()
{
    setCommandDirection( "undo" );

    if( d->parent->children().indexOf( object() ) == -1 )
    {
        if( d->index != -1 )
        {
            d->parent->addChildAt( object(), d->index );
        }
        else
        {
            d->parent->addChild( object() );
        }
    }

    d->applied = true;
    AbstractUndoCommand::undo();
}

void DeleteObjectCommand::redo()
{
    setCommandDirection( "redo" );

    d->index = d->parent->children().indexOf( object() );
    if( d->index != -1 )
        d->parent->removeChild( object() );

    d->applied = false;
    AbstractUndoCommand::redo();
}

