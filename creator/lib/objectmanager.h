/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_CREATOR_OBJECTMANAGER_H
#define GLUON_CREATOR_OBJECTMANAGER_H

#include "gluoncreator_macros.h"

#include <core/singleton.h>

#include <QDebug>

namespace GluonCore
{
    class GluonObject;
}

namespace GluonEngine
{
    class Asset;
    class GameObject;
    class Scene;
    class Component;
}

namespace GluonCreator
{

    class GLUONCREATOR_EXPORT ObjectManager : public GluonCore::Singleton<ObjectManager>
    {
            Q_OBJECT
        public Q_SLOTS:
            GluonEngine::Component* createNewComponent( const QString& type, GluonEngine::GameObject* parent );
            GluonEngine::Scene* createNewScene();
            GluonEngine::GameObject* createNewGameObject();
            GluonEngine::Asset* createNewAsset( const QString& fileName, const QString& className = QString(), const QString& name = QString() );
            void deleteGameObject( GluonEngine::GameObject* object );
            void changeProperty( GluonCore::GluonObject* object, QString& property, QVariant& oldValue, QVariant& newValue );
            QString humanifyClassName( const QString& fixThis, bool justRemoveNamespace = false ) const;
            void watchCurrentAssets();
            void assetDirty( const QString &file );
            void assetDeleted( const QString &file );
            void assetDeleted( GluonEngine::Asset* asset );

        Q_SIGNALS:
            void newObject( GluonCore::GluonObject* );
            void newScene( GluonEngine::Scene* );
            void newGameObject( GluonEngine::GameObject* );
            void newComponent( GluonEngine::Component* );

        private:
            friend class GluonCore::Singleton<ObjectManager>;

            ObjectManager();
            ~ObjectManager();
            void setupAsset( GluonEngine::Asset* asset, const QString& fileName, const QString& name );
            Q_DISABLE_COPY( ObjectManager )

            int m_objectId;
            int m_sceneId;
            QHash<QString, GluonEngine::Asset*> m_assets;
    };

}

#endif // GLUON_CREATOR_OBJECTMANAGER_H
