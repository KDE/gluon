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

#include "project.h"
#include "projectprivate.h"

using namespace Gluon;

Project::Project(QObject * parent)
    : GluonObject(parent)
{
    d = new ProjectPrivate;
}

Project::Project(const Project &other, QObject * parent)
    : GluonObject(parent)
    , d(other.d)
{
}

Project::~Project()
{
}

// Property setter-getters

void
Project::setFile(QUrl newFile)
{
    d->file = newFile;
}

QUrl
Project::file() const
{
    return d->file;
}

void
Project::setLevels(QList<GameObject *> newLevels)
{
    d->levels = newLevels;
}

QList<GameObject *>
Project::levels() const
{
    return d->levels;
}

void
Project::setAssets(QList<Asset *> newAssets)
{
    d->assets = newAssets;
}

QList<Asset *>
Project::assets() const
{
    return d->assets;
}

void
Project::setPrefabs(QList<Prefab *> newPrefabs)
{
    d->prefabs = newPrefabs;
}

QList<Prefab *>
Project::prefabs() const
{
    return d->prefabs;
}

#include "project.moc"
