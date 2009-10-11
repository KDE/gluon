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

#ifndef GLUON_GAMEOBJECT_H
#define GLUON_GAMEOBJECT_H

#include "gluonobject.h"
#include <QSharedData>
#include "gluonvarianttypes.h"
#include "gluonobjectfactory.h"

namespace Gluon
{
    class GameObjectPrivate;
    class Component;
    
    class GameObject : public GluonObject
    {
        Q_OBJECT
        Q_PROPERTY(QString description READ description WRITE setDescription)
        
        /*Q_PROPERTY(Eigen::Vector3d position READ position WRITE setPosition)
        Q_PROPERTY(Eigen::Vector3d scale READ scale WRITE setScale)
        Q_PROPERTY(Eigen::Vector3d rotationAxis READ rotationAxis WRITE setRotationAxis)*/
        Q_PROPERTY(float rotation READ rotation WRITE setRotation)
        
        public:
            GameObject(QObject * parent = 0);
            GameObject(const GameObject &other, QObject * parent = 0);
            ~GameObject();
            
            GameObject * instantiate();
            void sanitize();
            void Start();
            void Update(int elapsedMilliseconds);
            /**
             * Draw the GameObject onto the scene
             * @param   int timeLapse   The number of milliseconds which has passed since the last update
             */
            void Draw(int timeLapse = 0);
            /**
             * Run a command on all the components in this GameObject
             */
            void RunCommand(const QString &functionName);
            void RunCommandInChildren(const QString &functionName);
            
            // ----------------------------------------------------------------
            // Component management
            
            Component * findComponent(const QString &name) const;
            Component * findComponentByType(const QString &typeName) const;
            Component * findComponentInChildren(const QString &name) const;
            Component * findComponentInChildrenByType(const QString &typeName) const;
            QList<Component *> findComponentsInChildren(const QString &name) const;
            QList<Component *> findComponentsInChildrenByType(const QString &typeName) const;
            void addComponent(Component * addThis);
            bool removeComponent(Component * removeThis);
            
            // ----------------------------------------------------------------
            // GameObject tree management
            
            GameObject * child(int index) const;
            GameObject * child(const QString &name) const;
            void addChild(GameObject * addThis);
            bool removeChild(GameObject * removeThis);
            
            void setParentGameObject(GameObject * newParent);
            GameObject * parentGameObject();
            
            // ----------------------------------------------------------------
            // Property getter-setters
            
            void setDescription(const QString &newDescription);
            QString description() const;
            
            void setPosition(Eigen::Vector3d newPosition);
            Eigen::Vector3d position() const;
            void setScale(Eigen::Vector3d newScale);
            Eigen::Vector3d scale() const;
            void setRotationAxis(Eigen::Vector3d newRotationAxis);
            Eigen::Vector3d rotationAxis() const;
            void setRotation(float newRotation);
            float rotation() const;
            
        private:
            QSharedDataPointer<GameObjectPrivate> d;
    };
}


#endif				// GLUON_GAMEOBJECT_H
