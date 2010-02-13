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

#include "gameobjectprivate.h"


using namespace GluonEngine;

GameObjectPrivate::GameObjectPrivate()
{
    parentGameObject = 0;
    position = QVector3D();
    scale = QVector3D(1,1,1);
    orientation = QQuaternion(0,0,0,1);

    transform = QMatrix4x4();
    transformInvalidated = true;
}

GameObjectPrivate::GameObjectPrivate(const GameObjectPrivate &other)
    : QSharedData(other)
    , description(other.description)
    , position(other.position)
    , scale(other.scale)
    , orientation(other.orientation)
    , parentGameObject(other.parentGameObject)
{
    transform = QMatrix4x4();
    transformInvalidated = true;
}

GameObjectPrivate::~GameObjectPrivate()
{
}
