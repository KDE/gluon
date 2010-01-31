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

#include <KLocalizedString>

#include <core/debughelper.h>
#include <core/gameproject.h>
#include <engine/gameobject.h>
#include <engine/scene.h>
#include <engine/game.h>

#include "selectionmanager.h"

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT ObjectManager* GluonCore::Singleton<ObjectManager>::m_instance = 0;

GluonEngine::GameObject* ObjectManager::createNewObject()
{
    DEBUG_FUNC_NAME
    GluonEngine::GameObject *newObj = new GluonEngine::GameObject();
    newObj->setName(i18n("New Object %1").arg(m_objectId++));
    DEBUG_TEXT(QString("Creating object: %1").arg(newObj->name()));

    SelectionManager::SelectionList selection = SelectionManager::instance()->selection();
    if(selection.size() > 0)
    {
        GluonEngine::GameObject* obj = qobject_cast<GluonEngine::GameObject*>(selection.at(0));
        if(obj)
        {
            DEBUG_TEXT(QString("Item %1 selected in Scene tree - assign new object as child").arg(obj->fullyQualifiedName()));
            obj->addChild(newObj);
        }
    }

    if(newObj->parentGameObject() == 0)
    {
        DEBUG_TEXT(QString("No parent game object yet - assign as child to Scene root"));
        GluonEngine::Game::instance()->currentScene()->sceneContents()->addChild(newObj);
    }

    // Remember to mark the current scene dirty
    GluonEngine::Game::instance()->currentScene()->savableDirty = true;

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
