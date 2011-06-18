/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef GLUONENGINE_PREFABINSTANCE_H
#define GLUONENGINE_PREFABINSTANCE_H

#include "gameobject.h"
#include "prefab.h"

namespace GluonEngine
{
    /**
     * Prefab instances should be created in game logic by calling the
     * GluonEngine::Prefab::createInstance method rather than instantiating this class directly.
     * 
     * However, should you for some reason wish to do so anyway, the correct workflow is to create
     * the instance, and then set the prefabLink property to the Instance in question.
     * 
     * Note that this will bypass the caching methods in Prefab, which can be used to ensure
     * performant instancing, as it is able to pre-create a number of instances, and keep those
     * instances handy for recreation on destruction.
     */
    class PrefabInstance : public GameObject
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::PrefabInstance )
            /**
             * The prefab link property describes which Prefab this instance is an instance of.
             * Setting the property will immediately delete all existing children and rebuild the
             * child object hierarchy so that the instance represents the GameObject hierarchy
             * stored in the new Prefab it points to.
             */
            Q_PROPERTY( GluonEngine::Prefab* prefabLink READ prefabLink WRITE setPrefabLink )

        public:
            PrefabInstance( QObject* parent = 0 );
            PrefabInstance( const PrefabInstance& other );
            virtual ~PrefabInstance();

            void setPrefabLink( Prefab* newPrefab );
            Prefab* prefabLink() const;

            /**
             * Store the changes to properties on this Prefab instance and all its children back
             * into the linked Prefab. This will propagate the changes out into the other instances
             * of this Prefab, as long as the properties have not changed locally in the other
             * instances.
             */
            Q_INVOKABLE void storeChanges() const;

            /**
             * Revert all changes in this instance back to those stored in the linked Prefab,
             * without destroying the stored objects.
             */
            Q_INVOKABLE void revertChanges();

            /**
             * Clean out the current instance and recreate all the children
             */
            void rebuildInstance();

            /**
             * Prefab instances cannot have their name reset for any reason, as that should only
             * happen from the Prefab original. As such, this function does nothing other than
             * return.
             * @param  newName  The name you intend to use, but which will be ignored
             */
            Q_SLOT void setName(const QString& newName);

            /*
             * Reimplemented from GameObject
             */
            virtual void addChild( GameObject* child );
            virtual void addChild( GluonObject* child );
            virtual void addChildAt( GluonObject* child, int position );
            virtual bool removeChild( GameObject* child );
            virtual bool removeChild( GluonObject* child );
            Q_INVOKABLE virtual void addComponent( GluonEngine::Component* addThis );
            Q_INVOKABLE virtual bool removeComponent( GluonEngine::Component* removeThis );

        protected Q_SLOTS:
            void childNameChanged( const QString& oldName, const QString& newName);

        private:
            class Private;
            Private* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::PrefabInstance* );

#endif // GLUONENGINE_PREFABINSTANCE_H
