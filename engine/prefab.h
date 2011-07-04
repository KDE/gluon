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

#ifndef GLUON_ENGINE_PREFAB_H
#define GLUON_ENGINE_PREFAB_H

#include "asset.h"
#include "savable.h"

#include <core/gluonobject.h>

namespace GluonEngine
{
    class GameObject;
    class PrefabInstance;
    class PrefabPrivate;

    /**
     * A Prefab is a GameObject hierarchy stored as an Asset, and any number of instances can be
     * created, which are linked clones of the stored GameObject. The effect of the link is such
     * that any changes made in the Prefab (property changes and changing the hierarchy itself by
     * adding or removing GameObjects or Components) are propagated to the instances of the Prefab,
     * though this will only happen in the case where those properties are not changed in the
     * instances.
     * 
     * Note that changes to the stored GameObject hierarchy (specifically removal of GameObjects)
     * will be propagated even though there are changes to the properties of those GameObjects in
     * the instance. As this is a destructive action, please take care when performing that action.
     */
    class GLUON_ENGINE_EXPORT Prefab : public Asset, public GluonEngine::Savable
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::Prefab )
            /**
             * The number of instances to create upon loading the GameObject hieararchy from file
             */
            Q_PROPERTY(int preCacheSize READ preCacheSize WRITE setPreCacheSize)
            /**
             * The additional number of instances to add to the cache, relative to the preCacheSize
             * property value. The total size of the cache is thus the number of pre-cached
             * instances plus the additional cache size.
             */
            Q_PROPERTY(int additionalCacheSize READ additionalCacheSize WRITE setAdditionalCacheSize)

        public:
            Q_INVOKABLE Prefab( QObject* parent = 0 );
            Prefab( const Prefab& other, QObject* parent = 0 );
            virtual ~Prefab();

            /**
             * Return a GDL representation of the scene's contents (that is, the GluonObject
             * hierarchy which makes up the scene tree)
             *
             * @return  A GDL representation of the scene tree
             */
            virtual QString contentsToGDL();

            /**
             * Create an instance of this Prefab, and attach the Instance as a child of the passed
             * GameObject instance.
             * @param attachTo The GameObject which should be set as parent of the new instance
             * @return The new instance of the Prefab's stored GameObject hierarchy
             */
            Q_INVOKABLE PrefabInstance* createInstance( GluonEngine::GameObject* attachTo );
            /**
             * Create an instance of this Prefab, on which there is no parent set. This should only
             * be done rarely, and as such you should only use this very rarely.
             * In particular it might seem like a good idea to use this to perform pre-caching of
             * instances, but this functionality is already available in the Prefab class, which
             * can be set to create a number of instances on load, and further set to store a
             * set of instances upon their destruction.
             */
            Q_INVOKABLE PrefabInstance* createInstance();

            void setGameObject( GameObject* newGameObject );
            GameObject* gameObject() const;

            /**
             * The list of instances currently linked with this Prefab
             */
            const QList<PrefabInstance*> instances() const;

            int preCacheSize() const;
            void setPreCacheSize(int newPreCacheSize);
            int additionalCacheSize() const;
            void setAdditionalCacheSize(int newAdditionalCacheSize);

            static void cloneObjectProperties(const QObject* cloneFrom, QObject* setPropertiesOn);
        protected:
            friend class PrefabInstance;
            /**
             * Add a new instance to this Prefab's list of instances. This function is normally only
             * used by the PrefabInstance class when setting the prefab link.
             * @param addThis The instance to be added to this Prefab
             */
            bool addInstance( GluonEngine::PrefabInstance* addThis );
            /**
             * Remove this instance from this Prefab's list of instances. This function is normally
             * only used by the PrefabInstance class when setting the prefab link.
             */
            bool removeInstance( GluonEngine::PrefabInstance* removeThis );

            /**
             * Update the GameObject stored in this Prefab to conform to the structure represented
             * by the passed instance. This will cause all linked instances to also be updated, in
             * the following manner:
             * 
             * If there are property changes, all properties that do not have local changes are
             * updated with the new values.
             * 
             * If there are structural changes, they are propagated to the linked objects,
             * discarding changes to the children that are deleted, and new objects and components
             * are added to the children where appropriate.
             */
            void updateFromInstance( const GluonEngine::PrefabInstance* updateFrom );
        private:
            PrefabPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Prefab* )

#endif  // GLUON_ENGINE_PREFAB_H
