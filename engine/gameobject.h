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

#ifndef GLUON_ENGINE_GAMEOBJECT_H
#define GLUON_ENGINE_GAMEOBJECT_H

#include <QtCore/QSharedData>

#include <core/gluonobject.h>
#include <core/gluonvarianttypes.h>
#include <core/gluonobjectfactory.h>

#include "gluon_engine_export.h"

namespace GluonEngine
{
    class GameObjectPrivate;
    class Component;

    class GLUON_ENGINE_EXPORT GameObject : public GluonCore::GluonObject
    {
        Q_OBJECT
        Q_PROPERTY(QString description READ description WRITE setDescription)

        Q_PROPERTY(QVector3D position READ position WRITE setPosition)
        Q_PROPERTY(QVector3D scale READ scale WRITE setScale)
        Q_PROPERTY(QQuaternion orientation READ orientation WRITE setOrientation)

        //Q_PROPERTY(QVector3D rotationAxis READ rotationAxis WRITE setRotationAxis)
        //Q_PROPERTY(float rotation READ rotation WRITE setRotation)

        public:
            enum TransformSpace
            {
                TS_LOCAL,
                TS_WORLD,
            };

            GameObject(QObject * parent = 0);
            GameObject(const GameObject &other, QObject * parent = 0);
            ~GameObject();

            GluonCore::GluonObject* instantiate();

            void sanitize();
            void start();
            void update(int elapsedMilliseconds);
            /**
             * Draw the GameObject onto the scene
             * @param   int timeLapse   The number of milliseconds which has passed since the last update
             */
            void draw(int timeLapse = 0);
            void stop();
            /**
             * Run a command on all the components in this GameObject
             */
            void runCommand(const QString &functionName);
            void runCommandInChildren(const QString &functionName);

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

            GameObject * childGameObject(int index) const;
            GameObject * childGameObject(const QString &name) const;
            void addChild(GluonCore::GluonObject * child);
            void addChild(GameObject * addThis);
            bool removeChild(GluonObject * child);
            bool removeChild(GameObject * removeThis);
            int childCount() const;
            int childIndex(GameObject* child) const;

            void setParentGameObject(GameObject * newParent);
            GameObject * parentGameObject();

            // ----------------------------------------------------------------
            // Property getter-setters

            void setDescription(const QString &newDescription);
            QString description() const;

            void setPosition(const QVector3D& newPosition);
            void setPosition(float x, float y, float z);
            QVector3D position() const;
            QVector3D worldPosition() const;

            void setScale(const QVector3D& newScale);
            void setScale(float x, float y, float z);
            QVector3D scale() const;
            QVector3D worldScale() const;

            void setOrientation(const QQuaternion& newOrientation);
            QQuaternion orientation() const;
            QQuaternion worldOrientation() const;

            //TODO: Implement
            //void translate(QVector3D translation, TransformSpace ts = TS_LOCAL);
            //void translate(float x, float y, float z, TransformSpace ts = TS_LOCAL);
            //void scaleRelative(QVector3D scaling, TransformSpace ts = TS_LOCAL);
            //void scaleRelative(float x, float y, float z, TransformSpace ts = TS_LOCAL);
            //void rotate(QQuaternion rotation, TransformSpace ts = TS_LOCAL);

            void updateTransform();
            void invalidateTransform();
            QMatrix4x4 transform() const;

        private:
            QSharedDataPointer<GameObjectPrivate> d;
    };
}


#endif  // GLUON_ENGINE_GAMEOBJECT_H
