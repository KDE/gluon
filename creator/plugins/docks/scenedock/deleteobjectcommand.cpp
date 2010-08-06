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

#include <core/debughelper.h>

using namespace GluonCreator;

class DeleteObjectCommand::DeleteObjectCommandPrivate
{
    public:
        DeleteObjectCommandPrivate() : object(0), parent(0), applied(false) { }
        
        GluonEngine::GameObject *object;
        GluonEngine::GameObject *parent;
        bool applied;
};

DeleteObjectCommand::DeleteObjectCommand(GluonEngine::GameObject *object, GluonEngine::GameObject *parent)
    : QUndoCommand(), d(new DeleteObjectCommandPrivate)
{
    d->object = object;
    d->parent = parent;

    setText("GluonCreator::DeleteObjectCommand");
}

DeleteObjectCommand::~DeleteObjectCommand()
{
    if(!d->applied)
        delete d->object;
    
    delete d;
}

GluonEngine::GameObject* DeleteObjectCommand::associatedObject() const
{
    return d->object;
}

void DeleteObjectCommand::undo()
{
    if(d->parent)
    {
        if(d->parent->childIndex(d->object) == -1)
            d->parent->addChild(d->object);
    }
    
    d->applied = true;
}

void DeleteObjectCommand::redo()
{
    if(d->parent)
    {
        if(d->parent->childIndex(d->object) != -1)
            d->parent->removeChild(d->object);
    }
    
    d->applied = false;
}

