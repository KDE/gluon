/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef GLUON_ENGINE_ABSTRACTPREFABINSTANCE
#define GLUON_ENGINE_ABSTRACTPREFABINSTANCE

#include "gluon_engine_export.h"

#include "gameobject.h"

namespace GluonEngine
{
    /**
     * AbstractPrefabInstance is the common base class of all GameObjects in a Prefab,
     * i.e. the base class of PrefabInstance and PrefabInstanceChild.
     */
    class GLUON_ENGINE_EXPORT AbstractPrefabInstance : public GameObject
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::AbstractPrefabInstance )

        public:
            AbstractPrefabInstance( QObject* parent = 0 );
            virtual ~AbstractPrefabInstance();

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

        public slots:
            /**
             * Store the changes to properties on this Prefab instance object and all its children back
             * into the linked Prefab. This will propagate the changes out into the other instances
             * of this Prefab, as long as the properties have not changed locally in the other
             * instances.
             * In this implementation, storeChanges just emits the instanceStored signal
             */
            virtual void storeChanges();

            /**
             * Revert all changes in this instance object back to those stored in the linked Prefab,
             * without destroying the stored objects.
             * In this implementation, revertChanges just emits the instanceReverted signal
             */
            virtual void revertChanges();

            /** call this if one of the properties or components of this object has changed */
            void gameObjectChanged();

            /**
             * Returns true if one of the properties or components of this object or of a child object
             * has changed.
             */
            bool hasGameObjectChanged() const;

        Q_SIGNALS:
            /** One of the properties or components of this object or of a child object has changed */
            void instanceChanged();

            /** All changes of this object and its child objects were reverted */
            void instanceReverted();

            /** All changes of this object and its children were applied to the connected prefab */
            void instanceStored();

        protected Q_SLOTS:
            void childNameChanged( const QString& oldName, const QString& newName );
            void parentReverted();
            void parentStored();

        protected:
            bool isInstantiationCompleted() const;
            void setInstantiationCompleted( bool completed );

        private:
            class Private;
            Private* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::AbstractPrefabInstance* );

#endif // GLUON_ENGINE_ABSTRACTPREFABINSTANCE
