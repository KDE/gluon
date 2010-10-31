/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "sceneprivate.h"
#include "scene.h"
#include "gameobject.h"

#include <core/debughelper.h>
#include <core/gdlhandler.h>

#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/qtextstream.h>

using namespace GluonEngine;

ScenePrivate::ScenePrivate(Scene *q)
{
    this->q = q;

    sceneContentsLoaded = false;
    sceneContentsStarted = false;
    sceneContents = new GameObject(q);
    sceneContents->setName(q->name());
}

ScenePrivate::ScenePrivate::~ScenePrivate()
{
}

void
ScenePrivate::unloadContents()
{
    if (sceneContentsLoaded)
        qDeleteAll(sceneContents->children());
    sceneContentsLoaded = false;
}

void
ScenePrivate::loadContents(const QUrl &file)
{
    DEBUG_BLOCK
    if (file.isEmpty()) {
        sceneContentsLoaded = true;
        return;
    }

    QFile *sceneFile = new QFile(file.toLocalFile());
    if (!sceneFile->exists()) {
        DEBUG_TEXT(QString("File %1 does not exist, aborting scene load").arg(file.toLocalFile()));
        return;
    }

    if (!sceneFile->open(QIODevice::ReadOnly)) {
        DEBUG_TEXT(QString("Failed to load scene contents as %1 could not be opened for reading").arg(file.toLocalFile()))
        return;
    }

    QTextStream sceneReader(sceneFile);
    QList<GluonCore::GluonObject *> theContents = GluonCore::GDLHandler::instance()->parseGDL(sceneReader.readAll(), q);
    sceneFile->close();
    delete sceneFile;

    if (sceneContents)
        delete sceneContents;
    /*sceneContents = new GameObject(q);
    foreach(GluonObject * child, theContents)
        sceneContents->addChild(child);*/
    if (theContents.count() > 0)
        sceneContents = qobject_cast<GluonEngine::GameObject *>(theContents.at(0));
    if (!sceneContents)
        sceneContents = new GluonEngine::GameObject(q);

    sceneContents->sanitize();
    sceneContentsLoaded = true;
    q->savableDirty = false;

    sceneContents->setName(q->name());
}

void
ScenePrivate::saveContents(const QUrl &file)
{
    QList<const GluonCore::GluonObject *> scene;
    foreach (const QObject *item, sceneContents->children()) {
        scene.append(qobject_cast<const GluonCore::GluonObject*>(item));
    }

    QFile *sceneFile = new QFile(file.toLocalFile());
    if (!sceneFile->open(QIODevice::WriteOnly))
        return;

    QTextStream sceneWriter(sceneFile);
    sceneWriter << GluonCore::GDLHandler::instance()->serializeGDL(scene);
    sceneWriter.flush();
    sceneFile->close();
    delete sceneFile;
    q->savableDirty = false;
}
