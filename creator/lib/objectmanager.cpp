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

#include "objectmanager.h"

#include <engine/gameobject.h>
#include <engine/scene.h>
#include <KLocalizedString>
#include <engine/game.h>
#include <core/gameproject.h>
#include "selectionmanager.h"

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT ObjectManager* GluonCore::Singleton<ObjectManager>::m_instance = 0;

GluonEngine::GameObject* ObjectManager::createNewObject()
{
    GluonEngine::GameObject *newObj = new GluonEngine::GameObject();
    newObj->setName(i18n("New Object %1").arg(m_objectId++));

    SelectionManager::SelectionList selection = SelectionManager::instance()->selection();
    if(selection.size() > 0)
    {
        GluonEngine::GameObject* obj = qobject_cast<GluonEngine::GameObject*>(selection.at(0));
        if(obj) obj->addChild(newObj);
    }

    if(newObj->parentGameObject() == 0)
    {
        GluonEngine::Game::instance()->currentScene()->sceneContents()->addChild(newObj);
    }

    emit newObject(newObj);
    return newObj;
}

GluonEngine::Scene* ObjectManager::createNewScene()
{
    GluonEngine::Scene *newScn = new GluonEngine::Scene();
    newScn->setName(i18n("New Scene %1").arg(m_sceneId++));
    GluonEngine::Game::instance()->gameProject()->addChild(newScn);
    emit newScene(newScn);
    return newScn;
}

#include "objectmanager.moc"
