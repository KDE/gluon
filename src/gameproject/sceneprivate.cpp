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

#include "sceneprivate.h"
#include "scene.h"
#include "gdlhandler.h"

#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/qtextstream.h>

using namespace Gluon;

ScenePrivate::ScenePrivate(Scene* q)
{
    this->q = q;
}

ScenePrivate::ScenePrivate::~ScenePrivate()
{
}

void
ScenePrivate::unloadContents()
{
    qDeleteAll(sceneContents);
}

void
ScenePrivate::loadContents(const QUrl& file)
{
    QFile *sceneFile = new QFile(file.toLocalFile());
    if(!sceneFile->open(QIODevice::ReadOnly))
        return;
    
    QTextStream sceneReader(sceneFile);
    sceneContents = GDLHandler::instance()->parseGDL(sceneReader.readAll(), q);
    sceneFile->close();
    delete(sceneFile);
}

void
ScenePrivate::saveContents(const QUrl& file)
{
    QList<const GluonObject*> scene;
    foreach(const GluonObject &item, sceneContents)
        scene.append(&item);
    
    QFile *sceneFile = new QFile(file.toLocalFile());
    if(!sceneFile->open(QIODevice::WriteOnly))
        return;
    
    QTextStream sceneWriter(sceneFile);
    sceneWriter << GDLHandler::instance()->serializeGDL(scene);
    sceneWriter.flush();
    sceneFile->close();
    delete(sceneFile);
}
