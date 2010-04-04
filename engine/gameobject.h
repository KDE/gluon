/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <>
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
            GLUON_OBJECT(GluonEngine::GameObject);
            Q_PROPERTY(QString description READ description WRITE setDescription)
            Q_PROPERTY(bool enabled READ enabled WRITE setEnabled)

            Q_PROPERTY(QVector3D position READ position WRITE setPosition)
            Q_PROPERTY(QVector3D scale READ scale WRITE setScale)
            Q_PROPERTY(QQuaternion orientation READ orientation WRITE setOrientation)

        public:
            enum TransformSpace
            {
                TS_LOCAL,
                TS_WORLD,
            };

            GameObject(QObject * parent = 0);
            GameObject(const GameObject &other, QObject * parent = 0);
            ~GameObject();

            void sanitize();
            
            /**
             * Initialize to a workable state
             */
            Q_INVOKABLE void initialize();
            /**
             * The game loop or scene is starting. Do anything necessary.
             */
            Q_INVOKABLE void start();
            /**
             * Update the object and any children.
             * Note that by convention any changes made to GameObjects should
             * be done in this phase, not during draw().
             *
             * @param int elapsedMilliseconds The time elapsed since the last update
             */
            Q_INVOKABLE void update(int elapsedMilliseconds);
            /**
             * Draw the GameObject onto the scene
             * By convention, this should not change GameObjects but only objects needed
             * for correct operation.
             *
             * @param   int timeLapse   The number of milliseconds which has passed since the last update
             */
            Q_INVOKABLE void draw(int timeLapse = 0);
            /**
             * The game loop or scene is stopping. Do anything necessary.
             */
            Q_INVOKABLE void stop();
            /**
             * The object has served its purpose. Clean up.
             */
            Q_INVOKABLE void cleanup();
            
            /**
             * Destroy the object.
             */
            Q_INVOKABLE void destroy();
            
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
            void addChildAt(GameObject* child, int index);
            bool removeChild(GluonObject * child);
            bool removeChild(GameObject * removeThis);
            int childCount() const;
            int childIndex(GameObject* child) const;

            Q_INVOKABLE GameObject * parentGameObject();

            // ----------------------------------------------------------------
            // Property getter-setters

            void setDescription(const QString &newDescription);
            QString description() const;

            Q_INVOKABLE bool enabled() const;
            Q_INVOKABLE void setEnabled(bool newEnabled);
            
            Q_INVOKABLE QVector3D position() const;
            Q_INVOKABLE QVector3D worldPosition() const;


            Q_INVOKABLE QVector3D scale() const;
            Q_INVOKABLE QVector3D worldScale() const;

            Q_INVOKABLE QQuaternion orientation() const;
            Q_INVOKABLE QQuaternion worldOrientation() const;

            Q_INVOKABLE QMatrix4x4 transform() const;

        public slots:
            void setParentGameObject(GameObject * newParent);

            //Transformation
            /**
             * Set the position of the object
             * Note that this position is relative to the object's parent.
             * E.g.: setPosition(QVector3D(0, 0, 0)) set the object at the
             * parent's pivot.
             *
             * @param newPosition The new position of the object
             */
            void setPosition(const QVector3D& newPosition);
            /**
             * Set the position of the object
             *
             * @see setPosition(const QVector3D& newPosition)
             *
             * @param x The X-axis component of the new position of the object
             * @param y The Y-axis component of the new position of the object
             * @param z The Z-axis component of the new position of the object
             */
            void setPosition(float x, float y, float z);
            /**
             * Translate the object relative to its current position.
             * This moves the object so that its new position will be equal to
             * position + translation. So translating by QVector3D(1, 0, 0) would
             * move the object one unit to the right.
             *
             * @param translation The amount to translate the object by
             * @param ts The transform space to use. If transform space is TS_LOCAL,
             * the object will move in local space, if transform space is TS_WORLD,
             * the object will move in world space.
             */
            void translate(const QVector3D& translation, GluonEngine::GameObject::TransformSpace ts = TS_LOCAL);
            /**
             * Translate the object relative to its current position.
             *
             * @see translate(const QVector3D& translation)
             *
             * @param x The X-axis component of the translation
             * @param y The Y-axis component of the translation
             * @param z The Z-axis component of the translation
             */
            void translate(float x, float y, float z, TransformSpace ts = TS_LOCAL);

            /**
             * Set the object's scale
             *
             * @param newScale The new scale of the object
             */
            void setScale(const QVector3D& newScale);
            void setScale(float x, float y, float z);
            void scaleRelative(QVector3D scaling, TransformSpace ts = TS_LOCAL);
            void scaleRelative(float x, float y, float z, TransformSpace ts = TS_LOCAL);

            /**
             * Set the object's orientation.
             * Due to many reasons, orientation is handled by Quaternions,
             *
             * @param newOrientation The new orientation of the object
             */
            void setOrientation(const QQuaternion& newOrientation);
            void orient(QQuaternion rotation, TransformSpace ts = TS_LOCAL);

            void updateTransform();
            void invalidateTransform();

        private:
            QSharedDataPointer<GameObjectPrivate> d;
    };
}

Q_DECLARE_METATYPE(GluonEngine::GameObject)
Q_DECLARE_METATYPE(GluonEngine::GameObject*)

#endif  // GLUON_ENGINE_GAMEOBJECT_H
