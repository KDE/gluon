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

#include "gameprojectprivate.h"

#include "savable.h"

#include <core/gluonobject.h>
#include <core/debughelper.h>

#include <QtCore/QStringList>

using namespace GluonEngine;

GameProjectPrivate::GameProjectPrivate()
{
    entryPoint = NULL;
}

GameProjectPrivate::GameProjectPrivate(const GameProjectPrivate &other)
    : QSharedData(other)
    , description(other.description)
    , homepage(other.homepage)
    , mediaInfo(other.mediaInfo)
    , filename(other.filename)
    , entryPoint(other.entryPoint)
{
}

GameProjectPrivate::~GameProjectPrivate()
{
}

bool
GameProjectPrivate::saveChildren(const GluonCore::GluonObject* parent)
{
    DEBUG_FUNC_NAME
    if(!parent)
    {
        DEBUG_TEXT(QString("Object child was null!"));
        return false;
    }

    for(int i = 0; i < parent->children().size(); ++i)
    {
        GluonCore::GluonObject *child = parent->child(i);
        // Meh, inherits is slow, but at least it's going to be calling something that does
        // disk IO, so it's not the slowest thing there
        if(child->inherits("GluonCore::Savable"))
        {
            DEBUG_TEXT(QString("Saving object named %1").arg(qobject_cast<const GluonCore::GluonObject*>(child)->name()));
            Savable::saveToFile(qobject_cast<GluonCore::GluonObject*>(child));
        }

        // Recurse, wooh!
        saveChildren(qobject_cast<const GluonCore::GluonObject*>(child));
    }
    return true;
}
