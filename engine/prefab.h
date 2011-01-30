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

#include "core/gluonobject.h"
#include "asset.h"

namespace GluonEngine
{

class GameObject;

    class PrefabInstance;
    class PrefabPrivate;
    class Prefab : public Asset
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset );
            GLUON_OBJECT( GluonEngine::Prefab );

        public:
            Q_INVOKABLE Prefab( QObject* parent = 0 );
            Prefab( const Prefab& other, QObject* parent = 0 );
            ~Prefab();

            Q_INVOKABLE PrefabInstance* createInstance(GluonEngine::GameObject* attachTo);
            Q_INVOKABLE PrefabInstance* createInstance();

            const QList<PrefabInstance*> instances() const;
            bool addInstance(GluonEngine::PrefabInstance* addThis);
            bool removeInstance(GluonEngine::PrefabInstance* removeThis);

            void setGameObject(GameObject* newGameObject);
            GameObject* gameObject() const;

        private:
            PrefabPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Prefab )
Q_DECLARE_METATYPE( GluonEngine::Prefab* )

#endif  // GLUON_ENGINE_PREFAB_H
