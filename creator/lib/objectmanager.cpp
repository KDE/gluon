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

#include "objectmanager.h"

#include <KLocalizedString>

#include <core/debughelper.h>
#include <engine/gameproject.h>
#include <engine/gameobject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/component.h>

#include "selectionmanager.h"
#include "newobjectcommand.h"
#include "historymanager.h"

#include <KMimeType>
#include <QFileInfo>
#include <QDir>

using namespace GluonCreator;

template<> GLUONCREATOR_EXPORT ObjectManager* GluonCore::Singleton<ObjectManager>::m_instance = 0;

GluonEngine::Asset* ObjectManager::createNewAsset(const QString &fileName)
{
    DEBUG_BLOCK
    KMimeType::Ptr type = KMimeType::findByFileContent(fileName);
    DEBUG_TEXT(QString("Creating asset for file %1 of mimetype %2").arg(fileName).arg(type->name()));

    GluonCore::GluonObject* newasset = GluonCore::GluonObjectFactory::instance()->instantiateObjectByMimetype(type->name());
    if (newasset)
    {
        GluonEngine::Asset* newChild = static_cast<GluonEngine::Asset*>(newasset);
        
        QFileInfo theFileInfo(fileName);

        GluonEngine::Game::instance()->gameProject()->addChild(newChild);
        newChild->setName(theFileInfo.fileName());

        if (!QDir::current().exists("Assets"))
            QDir::current().mkdir("Assets");
            
        DEBUG_TEXT(QString("Copying file to %1").arg(newChild->fullyQualifiedFileName()));
        QUrl newLocation(QString("Assets/%1").arg(newChild->fullyQualifiedFileName()));
        QFile(fileName).copy(newLocation.toLocalFile());
        newChild->setFile(newLocation);
        newChild->load();
        
        HistoryManager::instance()->addCommand(new NewObjectCommand(newasset));
        return newChild;
    }
    
    return 0;
}

GluonEngine::Component* ObjectManager::createNewComponent(const QString& type, GluonEngine::GameObject* parent)
{
    DEBUG_BLOCK
    GluonCore::GluonObject* newObj = GluonCore::GluonObjectFactory::instance()->instantiateObjectByName(type);
    if (newObj)
    {
        GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>(newObj);
        parent->addComponent(comp);

        // Initialize the component
        comp->initialize();

        emit newComponent(comp);

        HistoryManager::instance()->addCommand(new NewObjectCommand(comp));

        return comp;
    }
    return 0;
}

GluonEngine::GameObject* ObjectManager::createNewGameObject()
{
    DEBUG_FUNC_NAME
    GluonEngine::GameObject *newObj = new GluonEngine::GameObject();
    newObj->setName(i18n("New Object %1", m_objectId++));
    DEBUG_TEXT(QString("Creating object: %1").arg(newObj->name()));

    SelectionManager::SelectionList selection = SelectionManager::instance()->selection();
    if (selection.size() > 0)
    {
        GluonEngine::GameObject* obj = qobject_cast<GluonEngine::GameObject*>(selection.at(0));
        if (obj)
        {
            DEBUG_TEXT(QString("Item %1 selected in Scene tree - assign new object as child").arg(obj->fullyQualifiedName()));
            obj->addChild(newObj);
        }
    }

    if (newObj->parentGameObject() == 0)
    {
        DEBUG_TEXT(QString("No parent game object yet - assign as child to Scene root"));
        GluonEngine::Game::instance()->currentScene()->sceneContents()->addChild(newObj);
    }

    emit newGameObject(newObj);

    HistoryManager::instance()->addCommand(new NewObjectCommand(newObj));

    return newObj;
}

GluonEngine::Scene* ObjectManager::createNewScene()
{
    GluonEngine::Scene *newScn = new GluonEngine::Scene();
    newScn->setName(i18n("New Scene %1", m_sceneId++));
    newScn->setGameProject(GluonEngine::Game::instance()->gameProject());
    GluonEngine::Game::instance()->gameProject()->addChild(newScn);

    emit newScene(newScn);

    HistoryManager::instance()->addCommand(new NewObjectCommand(newScn));

    return newScn;
}

ObjectManager::ObjectManager()
{
    m_objectId = 0;
    m_sceneId = 0;
}

ObjectManager::~ObjectManager()
{

}

#include "objectmanager.moc"
