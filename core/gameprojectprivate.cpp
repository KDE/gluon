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
#include "gluonobject.h"
#include "debughelper.h"

#include <QtCore/QStringList>

using namespace GluonCore;

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

GluonObject *
GameProjectPrivate::findItemByNameInObject(QStringList qualifiedName, GluonObject * parentObject)
{
    DEBUG_FUNC_NAME
    GluonObject * foundChild = NULL;
    QString lookingFor(qualifiedName[0]);
    qualifiedName.removeFirst();

    DEBUG_TEXT(QString("Looking for object of name %1 in the object %2").arg(lookingFor).arg(parentObject->name()));
    foreach(QObject * child, parentObject->children())
    {
        if(qobject_cast<GluonObject*>(child)->name() == lookingFor)
        {
            foundChild = qobject_cast<GluonObject*>(child);
            break;
        }
    }

    // checking for nullity to guard against trying to go into non-existent sub-trees
    if(foundChild != NULL)
    {
        if(qualifiedName.count() > 0)
        {
            DEBUG_TEXT(QString("Found child, recursing..."));
            return findItemByNameInObject(qualifiedName, foundChild);
        }
        else
        {
            DEBUG_TEXT(QString("Found child!"));
        }
    }
    else
    {
        DEBUG_TEXT("Did not find child! Bailing out");
    }

    return foundChild;
}

bool
GameProjectPrivate::saveChildren(const GluonObject* parent)
{
    DEBUG_FUNC_NAME
    if(!parent)
    {
        DEBUG_TEXT(QString("Object child was null!"));
        return false;
    }

    for(int i = 0; i < parent->children().size(); ++i)
    {
        GluonObject *child = parent->child(i);
        // Meh, dynamic_cast is slow, but at least it's going to be calling something that does
        // disk IO, so it's not the slowest thing there
        if(child->inherits("Gluon::Savable"))
        {
            DEBUG_TEXT(QString("Saving object named %1").arg(qobject_cast<const GluonObject*>(child)->name()));
            //TODO: Fix this
            //Savable::saveToFile(dynamic_cast<Gluon::Asset*>(child));
        }

        // Recurse, wooh!
        saveChildren(qobject_cast<const GluonObject*>(child));
    }
    return true;
}
