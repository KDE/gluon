/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

        signals:
            void newObject(GluonCore::GluonObject*);
            void newScene(GluonEngine::Scene*);
            void newGameObject(GluonEngine::GameObject*);
            void newComponent(GluonEngine::Component*);

        private:
            friend class GluonCore::Singleton<ObjectManager>;

            ObjectManager()
            {
                m_objectId = 0;
                m_sceneId = 0;
            }
            ~ObjectManager() { }
            Q_DISABLE_COPY(ObjectManager)

            int m_objectId;
            int m_sceneId;
    };

}

#endif // GLUON_CREATOR_OBJECTMANAGER_H
