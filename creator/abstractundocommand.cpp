/*****************************************************************************
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

#include "abstractundocommand.h"

#include "selectionmanager.h"

#include <engine/savable.h>

using namespace GluonCreator;

class AbstractUndoCommand::AbstractUndoCommandPrivate
{
    public:
        GluonCore::GluonObject* object;
        QString commandName;
        QString commandDirection;

        GluonEngine::Savable* savableObject;
        bool oldSavable;
};

AbstractUndoCommand::AbstractUndoCommand( QUndoCommand* parent )
    : QUndoCommand( parent ),
      d( new AbstractUndoCommandPrivate )
{
    d->savableObject = SelectionManager::instance()->savableContext();
    if(d->savableObject)
        d->oldSavable = d->savableObject->savableDirty;
}

AbstractUndoCommand::~AbstractUndoCommand()
{
}

int AbstractUndoCommand::id() const
{
    return -1;
}

void AbstractUndoCommand::redo()
{
    if(d->savableObject)
        d->savableObject->savableDirty = true;
    QUndoCommand::redo();
}

void AbstractUndoCommand::undo()
{
    if(d->savableObject)
        d->savableObject->savableDirty = d->oldSavable;
    QUndoCommand::undo();
}

QString
AbstractUndoCommand::commandName() const
{
    return d->commandName;
}

QString
AbstractUndoCommand::commandDirection() const
{
    return d->commandDirection;
}

GluonCore::GluonObject*
AbstractUndoCommand::object() const
{
    return d->object;
}

void
AbstractUndoCommand::setCommandName( const QString& name )
{
    d->commandName = name;
}

void
AbstractUndoCommand::setCommandDirection( const QString& direction )
{
    d->commandDirection = direction;
}

void
AbstractUndoCommand::setObject( GluonCore::GluonObject* obj )
{
    d->object = obj;
}
