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

#ifndef GLUON_ENGINE_GAMEOBJECTPRIVATE_H
#define GLUON_ENGINE_GAMEOBJECTPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QList>
#include <QtCore/QString>

#include <QtGui/QMatrix4x4>

namespace GluonEngine
{
    class GameObject;
    class Component;

    class GameObjectPrivate : public QSharedData
    {
        public:
            GameObjectPrivate();
            GameObjectPrivate(const GameObjectPrivate &other);
            ~GameObjectPrivate();

            QString description;

            QVector3D position;
            QVector3D scale;
            QQuaternion orientation;

            QVector3D worldPosition;
            QVector3D worldScale;
            QQuaternion worldOrientation;

            QMatrix4x4 transform;
            bool transformInvalidated;

            GameObject * parentGameObject;
            QList<GameObject *> children;
            QList<Component *> components;
    };
}

#endif // GLUON_ENGINE_GAMEOBJECTPRIVATE_H
