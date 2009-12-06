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

#include <gameobject.h>
#include <scene.h>
#include <KLocalizedString>
#include <game.h>
#include <gameproject.h>
#include "selectionmanager.h"

using namespace Gluon::Creator;

template<> GLUONCREATORLIB_EXPORT ObjectManager* KSingleton<ObjectManager>::m_instance = 0;

Gluon::GameObject* Gluon::Creator::ObjectManager::createNewObject()
{
    Gluon::GameObject *newObj = new Gluon::GameObject();
    newObj->setName(i18n("New Object %1").arg(m_objectId++));

    SelectionManager::SelectionList selection = SelectionManager::instance()->selection();
    if(selection.size() > 0)
    {
        GameObject* obj = qobject_cast<GameObject*>(selection.at(0));
        if(obj) obj->addChild(newObj);
    }

    if(newObj->parentGameObject() == 0)
    {
        Gluon::Game::instance()->currentScene()->sceneContents()->addChild(newObj);
    }

    emit newObject(newObj);
    return newObj;
}

Gluon::Scene* Gluon::Creator::ObjectManager::createNewScene()
{
    Gluon::Scene *newScn = new Gluon::Scene();
    newScn->setName(i18n("New Scene %1").arg(m_sceneId++));
    Gluon::Game::instance()->gameProject()->addChild(newScn);
    emit newScene(newScn);
    return newScn;
}
