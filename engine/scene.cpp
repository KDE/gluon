/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    if(!d->sceneContentsStarted)
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
    if(d->sceneContentsStarted)
    {
        sceneContents()->stop();
        d->sceneContentsStarted = false;
    }
}

void
Scene::setFile(const QUrl &newFile)
{
    if(!savableDirty)
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
    if(!d->sceneContentsLoaded && !savableDirty)
        d->loadContents(FileLocation(qobject_cast<GameProject*>(gameProject()), file()).location());
    return d->sceneContents;
}

#include "scene.moc"
