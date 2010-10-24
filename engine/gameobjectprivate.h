/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
            bool enabled;

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
            QMultiHash<int, Component*> componentTypes;
            QList<GameObject *> objectsToDelete;
    };
}

#endif // GLUON_ENGINE_GAMEOBJECTPRIVATE_H
