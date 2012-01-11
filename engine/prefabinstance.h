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

#include "abstractprefabinstance.h"
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
    class GLUON_ENGINE_EXPORT PrefabInstance : public AbstractPrefabInstance
    {
            Q_OBJECT
            /**
             * The prefab link property describes which Prefab this instance is an instance of.
             * Setting the property will immediately delete all existing children and rebuild the
             * child object hierarchy so that the instance represents the GameObject hierarchy
             * stored in the new Prefab it points to.
             */
            Q_PROPERTY( GluonEngine::Prefab* prefabLink READ prefabLink WRITE setPrefabLink )

            GLUON_OBJECT( GluonEngine::PrefabInstance )

        public:
            Q_INVOKABLE PrefabInstance( QObject* parent = 0 );
            virtual ~PrefabInstance();

            void setPrefabLink( Prefab* newPrefab );
            Prefab* prefabLink() const;

            /**
             * Clean out the current instance and recreate all the children
             */
            void rebuildInstance();

        public slots:
            /**
             * Reimplementation of AbstractPrefabInstance::storeChanges
             */
            virtual void storeChanges();

            /**
             * Reimplementation of AbstractPrefabInstance::revertChanges
             */
            virtual void revertChanges();

        private:
            class Private;
            Private* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::PrefabInstance* )

#endif // GLUONENGINE_PREFABINSTANCE_H
