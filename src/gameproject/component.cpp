/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "component.h"
#include "componentprivate.h"
#include "gameobject.h"

#include <QString>

using namespace Gluon;

Component::Component(QObject * parent)
    : QObject(parent)
{
    d = new ComponentPrivate;
}

Component::Component(const Component &other, QObject * parent)
    : QObject(parent)
    , d(other.d)
{
}

Component::~Component()
{
}

// Property getter-setters

void
Component::setName(QString newName)
{
    d->name = newName;
}

QString
Component::name() const
{
    return d->name;
}

void
Component::setDescription(QString newDescription)
{
    d->description = newDescription;
}

QString
Component::description() const
{
    return d->description;
}

void
Component::setEnabled(bool newEnabled)
{
    d->enabled = newEnabled;
}

bool
Component::enabled() const
{
    return d->enabled;
}

GameObject *
Component::gameObject()
{
    return d->gameObject;
}

void
Component::setGameObject(GameObject * newGameObject)
{
    d->gameObject = newGameObject;
}

#include "component.moc"
