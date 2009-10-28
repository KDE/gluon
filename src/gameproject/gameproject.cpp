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

#include "gameproject.h"
#include "gameprojectprivate.h"

using namespace Gluon;

REGISTER_OBJECTTYPE(GameProject)

GameProject::GameProject(QObject * parent)
{
    d = new GameProjectPrivate;
}

GameProject::GameProject(const GameProject &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
}

GameProject::~GameProject()
{
}

/******************************************************************************
 * Property Getter-setters
 *****************************************************************************/

QString
GameProject::description() const
{
    return d->description;
}
void
GameProject::setDescription(QString newDescription)
{
    d->description = newDescription;
}

QUrl
GameProject::homepage() const
{
    return d->homepage;
}
void
GameProject::setHomepage(QUrl newHomepage)
{
    d->homepage = newHomepage;
}

QList<QUrl>
GameProject::mediaInfo() const
{
    return d->mediaInfo;
}
void
GameProject::setMediaInfo(QList<QUrl> newMediaInfo)
{
    d->mediaInfo = newMediaInfo;
}

QUrl
GameProject::filename() const
{
    return d->filename;
}
void
GameProject::setFilename(QUrl newFilename)
{
    d->filename = newFilename;
}

QList<GameObject*>
GameProject::scenes() const
{
    return d->scenes;
}
void
GameProject::setScenes(QList<GameObject*> newScenes)
{
    d->scenes = newScenes;
}

QList<Asset*>
GameProject::assets() const
{
    return d->assets;
}
void
GameProject::setAssets(QList<Asset*> newAssets)
{
    d->assets = newAssets;
}

QList<Prefab*>
GameProject::prefabs() const
{
    return d->prefabs;
}
void
GameProject::setPrefabs(QList<Prefab*> newPrefabs)
{
    d->prefabs = newPrefabs;
}

GameObject *
GameProject::entryPoint() const
{
    return d->entryPoint;
}
void
GameProject::setEntryPoint(GameObject * newEntryPoint)
{
    d->entryPoint = newEntryPoint;
}

#include "gameproject.moc"
