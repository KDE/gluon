/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef GLUONENGINE_PREFABINSTANCECHILD_H
#define GLUONENGINE_PREFABINSTANCECHILD_H

#include "gameobject.h"

namespace GluonEngine
{
    class PrefabInstance;
    class PrefabPrivate;

    /**
     * Speaking generally, this class should never be instanatiated manually. It will for all
     * intents and purposes work like a GameObject, and as such you should be usin that in stead.
     * The class is used by the Prefab system to contain children of a Prefab instance. To find out
     * how that system works, please see the documentation on GluonEngine::Prefab
     */
    class PrefabInstanceChild : public GluonEngine::GameObject
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::PrefabInstanceChild )

        public:
            PrefabInstanceChild( QObject* parent = 0 );
            PrefabInstanceChild( const PrefabInstanceChild& other );
            virtual ~PrefabInstanceChild();

            /**
             * Get the root of the instance hierarchy - that is, the actual PrefabInstance rather
             * than a child inside the tree of GameObjects represented by the Prefab. Use this to
             * perform actions which should work on the entire instance, such as
             * PrefabInstance::storeChanges() and PrefabInstance::revertChanges()
             * @see storeChanges(), revertChanges()
             */
            Q_INVOKABLE GluonEngine::PrefabInstance* parentInstance();

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

        protected:
            friend class PrefabInstance;
            friend class PrefabPrivate;
            /**
             * Clear this prefab instance child and reclone it from the passed GameObject.
             * This will recursively clone the GameObject, by creating PrefabInstanceChild instances
             * for each child GameObject (and copying all properties and cloning all Components
             * attached to the GameObject)
             * @param gameObject The GameObject you wish to clone
             */
            void cloneFromGameObject(GluonEngine::GameObject* gameObject);

            /**
             * Reset all changes on the instance child and all the attached Components
             */
            void resetProperties();
        private:
            class Private;
            Private* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::PrefabInstanceChild* );

#endif // GLUONENGINE_PREFABINSTANCECHILD_H
