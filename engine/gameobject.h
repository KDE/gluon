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

        Q_PROPERTY(Eigen::Vector3f position READ position WRITE setPosition)
        Q_PROPERTY(Eigen::Vector3f scale READ scale WRITE setScale)
        Q_PROPERTY(Eigen::Quaternionf orientation READ orientation WRITE setOrientation)

        //Q_PROPERTY(Eigen::Vector3f rotationAxis READ rotationAxis WRITE setRotationAxis)
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

            Q_INVOKABLE Component * findComponent(const QString &name) const;
            Q_INVOKABLE Component * findComponentByType(const QString &typeName) const;
            Q_INVOKABLE Component * findComponentInChildren(const QString &name) const;
            Q_INVOKABLE Component * findComponentInChildrenByType(const QString &typeName) const;
            Q_INVOKABLE QList<Component *> findComponentsInChildren(const QString &name) const;
            Q_INVOKABLE QList<Component *> findComponentsInChildrenByType(const QString &typeName) const;
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

            Q_INVOKABLE GameObject * parentGameObject();

            // ----------------------------------------------------------------
            // Property getter-setters

            void setDescription(const QString &newDescription);
            QString description() const;


            Q_INVOKABLE Eigen::Vector3f position() const;
            Q_INVOKABLE Eigen::Vector3f worldPosition() const;


            Q_INVOKABLE Eigen::Vector3f scale() const;
            Q_INVOKABLE Eigen::Vector3f worldScale() const;

            Q_INVOKABLE Eigen::Quaternionf orientation() const;
            Q_INVOKABLE Eigen::Quaternionf worldOrientation() const;

            Q_INVOKABLE Eigen::Transform3f transform() const;

        public slots:
            void setParentGameObject(GameObject * newParent);

            //Transformation
            void setPosition(const Eigen::Vector3f& newPosition);
            void setPosition(float x, float y, float z);
            //void translate(Eigen::Vector3f translation, TransformSpace ts = TS_LOCAL);
            //void translate(float x, float y, float z, TransformSpace ts = TS_LOCAL);

            void setScale(const Eigen::Vector3f& newScale);
            void setScale(float x, float y, float z);
            //void scaleRelative(Eigen::Vector3f scaling, TransformSpace ts = TS_LOCAL);
            //void scaleRelative(float x, float y, float z, TransformSpace ts = TS_LOCAL);

            void setOrientation(const Eigen::Quaternionf& newOrientation);
            //void rotate(Eigen::Quaternionf rotation, TransformSpace ts = TS_LOCAL);

            void updateTransform();
            void invalidateTransform();

        private:
            QSharedDataPointer<GameObjectPrivate> d;
    };
}


#endif  // GLUON_ENGINE_GAMEOBJECT_H
