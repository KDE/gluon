/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "btcharacterscriptable.h"

#include "character.h"
#include "engine/gameobject.h"

using namespace GluonEngine;

btCharacterScriptable::btCharacterScriptable(QObject * parent)
	: GluonSmarts::btCharacter()
    , m_time(0)
{
    this->setParent(parent);
}

btCharacterScriptable::~btCharacterScriptable()
{
}

QVector3D btCharacterScriptable::position() const
{
    Character * character = qobject_cast< Character* >(this->parent());
    return character->gameObject()->position();
}

void btCharacterScriptable::setPosition(const QVector3D& newPosition)
{
    Character * character = qobject_cast< Character* >(this->parent());
    character->gameObject()->setPosition(newPosition);
}

QQuaternion btCharacterScriptable::orientation() const
{
    Character * character = qobject_cast< Character* >(this->parent());
    return character->gameObject()->orientation();
}

void btCharacterScriptable::setOrientation(const QQuaternion& newOrientation)
{
    Character * character = qobject_cast< Character* >(this->parent());
    character->gameObject()->setOrientation(newOrientation);
}

GluonSmarts::btPerception* btCharacterScriptable::perception()
{
    return GluonSmarts::btCharacter::perception();
}

int btCharacterScriptable::time()
{
    return m_time;
}

void btCharacterScriptable::setTime(int time)
{
    m_time = time;
}

 

