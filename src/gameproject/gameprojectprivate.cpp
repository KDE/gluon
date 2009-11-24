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

using namespace Gluon;

GameProjectPrivate::GameProjectPrivate()
{
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