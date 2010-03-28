/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
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
#include <engine/gameobject.h>
#include <engine/component.h>

using namespace GluonCreator;

class NewObjectCommand::NewObjectCommandPrivate
{
    public:
        GluonCore::GluonObject *object;
        GluonCore::GluonObject *parent;
        bool applied;
};

NewObjectCommand::NewObjectCommand(GluonCore::GluonObject* newObject) : d(new NewObjectCommandPrivate)
{
    d->object = newObject;
    d->parent = qobject_cast<GluonCore::GluonObject*>(newObject->parent());
    d->applied = true;
}

NewObjectCommand::~NewObjectCommand()
{
    if (!d->applied)
        delete d->object;
}

void
NewObjectCommand::undo()
{
    d->applied = false;
    d->parent->removeChild(d->object);

    GluonEngine::GameObject *obj = qobject_cast<GluonEngine::GameObject*>(d->object);
    if (obj)
        obj->parentGameObject()->removeChild(obj);

    GluonEngine::Component *comp = qobject_cast<GluonEngine::Component*>(d->object);
    if (comp)
        comp->gameObject()->removeComponent(comp);
}

void
NewObjectCommand::redo()
{
    d->applied = true;
    d->object->setParent(d->parent);

    GluonEngine::GameObject *gobjParent = qobject_cast< GluonEngine::GameObject* >(d->parent);
    GluonEngine::GameObject *obj = qobject_cast<GluonEngine::GameObject*>(d->object);
    if (obj && gobjParent)
        gobjParent->addChild(obj);

    GluonEngine::Component *comp = qobject_cast<GluonEngine::Component*>(d->object);
    if (comp && gobjParent)
        gobjParent->addComponent(comp);

}

