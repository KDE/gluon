/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <>
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

#include "scene.h"
#include "gameobject.h"
#include "sceneprivate.h"
#include "filelocation.h"
#include "gameproject.h"

REGISTER_OBJECTTYPE(GluonEngine, Scene)

using namespace GluonEngine;

Scene::Scene(QObject * parent)
        : Asset(parent)
{
    d = new ScenePrivate(this);
    savableDirty = false;
}

Scene::~Scene()
{
    delete(d);
}

void
Scene::startAll()
{
    if (!d->sceneContentsStarted)
    {
        sceneContents()->start();
        d->sceneContentsStarted = true;
    }
}
void
Scene::updateAll(int elapsedMilliseconds)
{
    sceneContents()->update(elapsedMilliseconds);
}
void
Scene::drawAll(int timeLapse)
{
    sceneContents()->draw(timeLapse);
}

void
Scene::stopAll()
{
    if (d->sceneContentsStarted)
    {
        sceneContents()->stop();
        d->sceneContentsStarted = false;
    }
}

void
Scene::setFile(const QUrl &newFile)
{
    if (!savableDirty)
        d->unloadContents();
    GluonEngine::Asset::setFile(newFile);
}

void Scene::setName(const QString& newName)
{
    sceneContents()->setName(newName);
    GluonCore::GluonObject::setName(newName);
}


QString
Scene::contentsToGDL()
{
    return sceneContents()->toGDL();
}

GameObject*
Scene::sceneContents()
{
    if (!d->sceneContentsLoaded && !savableDirty)
        d->loadContents(FileLocation(qobject_cast<GameProject*>(gameProject()), file()).location());
    return d->sceneContents;
}

#include "scene.moc"
