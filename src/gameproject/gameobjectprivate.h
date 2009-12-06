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

#ifndef GLUON_GAMEOBJECTPRIVATE_H
#define GLUON_GAMEOBJECTPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QList>
#include <QtCore/QString>
#include <Eigen/Geometry>

namespace Gluon
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
            
            Eigen::Vector3f position;
            Eigen::Vector3f scale;
            Eigen::Vector3f rotationAxis;
            float rotation;
            
            Eigen::Vector3f positionGlobal;
            Eigen::Vector3f scaleGlobal;
            Eigen::Vector3f rotationAxisGlobal;
            float rotationGlobal;

            Eigen::Transform<float, 3> transformMatrix;
            
            GameObject * parentGameObject;
            QList<GameObject *> children;
            QList<Component *> components;
    };
}

#endif // GLUON_GAMEOBJECTPRIVATE_H
