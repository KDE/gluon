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

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QMultiHash>

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace GluonEngine
{
    class GameObject;
    class Component;

    class GameObjectPrivate
    {
        public:
            GameObjectPrivate();
            GameObjectPrivate( const GameObjectPrivate& other );
            ~GameObjectPrivate();

            QString description;
            bool enabled;
            bool initialized;

            Eigen::Vector3f position;
            Eigen::Vector3f scale;
            Eigen::Quaternionf orientation;

            Eigen::Vector3f worldPosition;
            Eigen::Vector3f worldScale;
            Eigen::Quaternionf worldOrientation;

            Eigen::Affine3f transform;
            bool transformInvalidated;

            GameObject* parentGameObject;
            QList<GameObject*> children;
            QList<Component*> components;
            QMultiHash<int, Component*> componentTypes;
            QList<GameObject*> objectsToDelete;
    };
}

#endif // GLUON_ENGINE_GAMEOBJECTPRIVATE_H
