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

#ifndef GLUON_ENGINE_GAMEOBJECT_H
#define GLUON_ENGINE_GAMEOBJECT_H

#include "gluon_engine_export.h"

#include <core/gluonobject.h>
#include <core/gluonvarianttypes.h>
#include <core/gluonobjectfactory.h>

#include <QtCore/QSharedData>
#include <QtScript/QScriptEngine>

namespace GluonEngine
{

    class Scene;

    class GameObjectPrivate;
    class Component;

    /**
     * \brief Represents the scene tree, third level of the GameObject hierarchy
     *
     * A GameObject is in essence just a translation object, meaning that it has a
     * position, a rotation and an orientation in 3D space. However, it also importantly
     * includes simple logic for attaching other bits of logic, as represented by the
     * Component class, which then attach more functionality to the GameObject.
     *
     * It is the third level of the GameObject hierarchy, and it can be seen as the
     * structure which makes up a scene tree (see also the Scene documentation).
     *
     * During the course of a game being played, the lifetime of a GameObject is like so:
     *
     * # GameObject is constructed on Scene load, and initialize() is called
     * # start() is called when game is started, or the current scene changes to the one containing this GameObject
     * # update() and draw() are called consecutively, at staggered intervals depending on which gameloop is used
     * # stop() is called when the game is stopped, or the current scene changes away
     * # cleanup() is called when the GameObject is destroyed
     */
    class GLUON_ENGINE_EXPORT GameObject : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::GameObject )
            /**
             * A little piece of text explaining what this GameObject is supposed
             * to do. Consider this a place for putting in documentation on what
             * a specific GameObject is used for in the game. Many books have been
             * written about the value of documentation, and so here shall just be
             * said: Use it. Documentation is good for your sanity when you return
             * to your work only a few days after first making it.
             */
            Q_PROPERTY( QString description READ description WRITE setDescription )
            /**
             * This decides whether the GameObject and its children are included
             * in the update and draw calls. This allows you to construct objects
             * in a game which do not get updated - you may wish to keep objects
             * around which are temoprarily not used, as destroying and re-creating
             * objects is more expensive than disabling and enabling them.
             */
            Q_PROPERTY( bool enabled READ enabled WRITE setEnabled )

            /**
             * The object position relative to its parent. If this is a top level
             * object in a scene, this is relative to the world origin (0, 0, 0)
             */
            Q_PROPERTY( QVector3D position READ position WRITE setPosition )
            /**
             * The scale of the object, relative to its parent object. If this is a
             * top level object in a scene, this is relative to the scale 1, 1, 1
             */
            Q_PROPERTY( QVector3D scale READ scale WRITE setScale )
            /**
             * The orientation of the object in the world (the rotation of the object
             * and the axis around which it is rotated, represented by a Quaternion),
             * relative to its parent. If this is a top level object in the world, it
             * is relative to a rotation of 0 around the Z axis (the axis pointing out
             * of the screen). This is also the default for all object.
             */
            Q_PROPERTY( QQuaternion orientation READ orientation WRITE setOrientation )

        public:
            enum TransformSpace
            {
                TS_LOCAL,
                TS_WORLD,
            };

            Q_INVOKABLE GameObject( QObject* parent = 0 );
            GameObject( const GameObject& other, QObject* parent = 0 );
            ~GameObject();

            /**
             * Function used on instantiation to fix the parent/child relationship.
             * Used specifically by GDLHandler in the parseGDL() function. If you do
             * not work on GDLHandler, it is unlikely you will need this function.
             * @see GDLHandler::parseGDL
             */
            void sanitize();

            /**
             * Initialize to a functional state
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
            Q_INVOKABLE void update( int elapsedMilliseconds );
            /**
             * Draw the GameObject onto the scene
             * By convention, this should not change GameObjects, but rather, only objects needed
             * for correct operation.
             *
             * @param   int timeLapse   The number of milliseconds which has passed since the last update
             */
            Q_INVOKABLE void draw( int timeLapse = 0 );
            /**
             * The game loop or scene is stopping. Do anything necessary.
             */
            Q_INVOKABLE void stop();
            /**
             * The object has served its purpose. Clean up.
             */
            Q_INVOKABLE void cleanup();

            /**
             * Destroy the object. The object will continue existing until just before
             * the next update call.
             */
            Q_INVOKABLE void destroy();

            /**
             * Returns true if initialize() was called on this object.
             **/
            bool isInitialized() const;

            /**
             * Run a command on all the components in this GameObject.
             *
             * @param   functionName    The name of the function you wish to call
             */
            void runCommand( const QString& functionName );
            /**
             * Run a command on all the components in this GameObject and all the
             * children of the GameObject.
             *
             * @param   functionName    The name of the function you wish to call
             */
            void runCommandInChildren( const QString& functionName );

            // ----------------------------------------------------------------
            // Component management

            Q_INVOKABLE Component* findComponent( const QString& name ) const;
            Q_INVOKABLE Component* findComponentByType( const QString& typeName ) const;
            Q_INVOKABLE Component* findComponentByType( int type ) const;
            Q_INVOKABLE QList<Component*> findComponentsByType( const QString& typeName ) const;
            Q_INVOKABLE QList<Component*> findComponentsByType( int type ) const;
            Q_INVOKABLE Component* findComponentInChildren( const QString& name ) const;
            Q_INVOKABLE Component* findComponentInChildrenByType( const QString& typeName ) const;
            Q_INVOKABLE QList<Component*> findComponentsInChildren( const QString& name ) const;
            Q_INVOKABLE QList<Component*> findComponentsInChildrenByType( const QString& typeName ) const;
            Q_INVOKABLE QList<Component*> findComponentsInChildrenByType( int type ) const;
            Q_INVOKABLE void addComponent( GluonEngine::Component* addThis );
            Q_INVOKABLE bool removeComponent( GluonEngine::Component* removeThis );
            Q_INVOKABLE QList<Component*> components() const;

            // ----------------------------------------------------------------
            // GameObject tree management

            /**
             * Get the Scene this GameObject is contained within. This will return null in three
             * possible instances:
             *
             * - The GameObject is stored as part of a Prefab
             * - The GameObject is in an unparented tree (such as in-game created items)
             * - The GameObject is in the middle of a move (should be very rare)
             *
             * @return  The Scene this GameObject belongs to, or null if it is not contained within a scene
             */
            Scene* scene() const;
            GameObject* childGameObject( int index ) const;
            GameObject* childGameObject( const QString& name ) const;
            void addChild( GluonCore::GluonObject* child );
            void addChild( GameObject* addThis );
            void addChildAt( GameObject* child, int index );
            bool removeChild( GluonObject* child );
            bool removeChild( GameObject* removeThis );
            int childCount() const;
            int childIndex( GameObject* child ) const;

            Q_INVOKABLE GameObject* parentGameObject();

            // ----------------------------------------------------------------
            // Property getter-setters

            void setDescription( const QString& newDescription );
            QString description() const;

            Q_INVOKABLE bool enabled() const;
            Q_INVOKABLE void setEnabled( bool newEnabled );

            Q_INVOKABLE QVector3D position() const;
            Q_INVOKABLE QVector3D worldPosition() const;


            Q_INVOKABLE QVector3D scale() const;
            Q_INVOKABLE QVector3D worldScale() const;

            Q_INVOKABLE QQuaternion orientation() const;
            Q_INVOKABLE QQuaternion worldOrientation() const;

            Q_INVOKABLE QMatrix4x4 transform() const;

        public slots:
            void setParentGameObject( GameObject* newParent );

            //Transformation
            /**
             * Set the position of the object
             * Note that this position is relative to the object's parent.
             * E.g.: setPosition(QVector3D(0, 0, 0)) set the object at the
             * parent's pivot.
             *
             * @param newPosition The new position of the object
             */
            void setPosition( const QVector3D& newPosition );
            /**
             * Set the position of the object
             *
             * @see setPosition(const QVector3D& newPosition)
             *
             * @param x The X-axis component of the new position of the object
             * @param y The Y-axis component of the new position of the object
             * @param z The Z-axis component of the new position of the object
             */
            void setPosition( float x, float y, float z );

            /**
             * Set the position of the object. This will not change the z-
             * position.
             *
             * @see setPosition(const QVector3D& newPosition)
             *
             * @param x The X-axis component of the new position of the object
             * @param y The Y-axis component of the new position of the object
             */
            void setPosition( float x, float y );

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
            void translate( const QVector3D& translation, GluonEngine::GameObject::TransformSpace ts = TS_LOCAL );
            /**
             * Translate the object relative to its current position.
             *
             * @see translate(const QVector3D& translation)
             *
             * @param x The X-axis component of the translation
             * @param y The Y-axis component of the translation
             * @param z The Z-axis component of the translation
             * @param ts The transform space to use.
             */
            void translate( float x, float y, float z, TransformSpace ts = TS_LOCAL );

            /**
             * Translate the object relative to its current position. This will
             * not change the z-position.
             *
             * @see translate(const QVector3D& translation)

             * @param x The X-axis component of the translation
             * @param y The Y-axis component of the translation
             * @param ts The transform space to use.
             */
            void translate( float x, float y, TransformSpace ts = TS_LOCAL );

            /**
             * Set the object's scale
             *
             * @param newScale The new scale of the object
             */
            void setScale( const QVector3D& newScale );
            void setScale( float x, float y, float z );
            void scaleRelative( QVector3D scaling, TransformSpace ts = TS_LOCAL );
            void scaleRelative( float x, float y, float z, TransformSpace ts = TS_LOCAL );

            /**
             * Set the object's orientation.
             * For many reasons, orientation is handled by Quaternions,
             *
             * @param newOrientation The new orientation of the object
             */
            void setOrientation( const QQuaternion& newOrientation );
            void orient( QQuaternion rotation, TransformSpace ts = TS_LOCAL );
            void rotate( float angle, const QVector3D& axis, TransformSpace ts = TS_LOCAL );

            void updateTransform();
            void invalidateTransform();
            void removeLater( GluonEngine::GameObject* remove );

        protected:
            /**
             * Sanitize a cloned object.
             * Note: This initializes/starts the object if the game is running.
             */
            virtual void postCloneSanitize();
        private:
            GameObjectPrivate* const d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameObject )
Q_DECLARE_METATYPE( GluonEngine::GameObject* )

#endif  // GLUON_ENGINE_GAMEOBJECT_H
