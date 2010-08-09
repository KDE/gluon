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
        public slots:
            GluonEngine::Component* createNewComponent(const QString& type, GluonEngine::GameObject* parent);
            GluonEngine::Scene* createNewScene();
            GluonEngine::GameObject* createNewGameObject();
            GluonEngine::Asset* createNewAsset(const QString& fileName);
	    void deleteGameObject(GluonEngine::GameObject* object);
	    void changeProperty(GluonCore::GluonObject* object,QString& property, QVariant& oldValue, QVariant& newValue);
            QString humanifyClassName(const QString& fixThis, bool justRemoveNamespace = false) const;

        signals:
            void newObject(GluonCore::GluonObject*);
            void newScene(GluonEngine::Scene*);
            void newGameObject(GluonEngine::GameObject*);
            void newComponent(GluonEngine::Component*);

        private:
            friend class GluonCore::Singleton<ObjectManager>;

            ObjectManager();
            ~ObjectManager();
            Q_DISABLE_COPY(ObjectManager)

            int m_objectId;
            int m_sceneId;
    };

}

#endif // GLUON_CREATOR_OBJECTMANAGER_H
