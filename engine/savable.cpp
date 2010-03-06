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

#include "savable.h"

#include <core/gluonobject.h>
#include <core/debughelper.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QtCore/QVariant>

using namespace GluonEngine;

bool
Savable::saveToFile(GluonCore::GluonObject * object)
{
    DEBUG_BLOCK
    if(!object)
    {
        DEBUG_TEXT("Asset was NULL!");
        return false;
    }
    Savable * savableObject = dynamic_cast<Savable*>(object);
    if(!savableObject)
    {
        DEBUG_TEXT("Attempted to save an object which does not inherit Savable!");
        return false;
    }

    // Make sure the filename is populated and is sane
    if(object->property("file").value<QUrl>().isEmpty())
        object->setProperty("file", QVariant::fromValue<QUrl>( QUrl( QString("Scenes/%1.gdl").arg(object->fullyQualifiedName().replace('/', ' ').replace('\\', ' ').replace(':', ' ') ) ) ) );

    // Create appropriate folders
    if(!QDir::current().exists("Scenes"))
        QDir::current().mkdir("Scenes");

    // Perform the save
    QFile *savableFile = new QFile(object->property("file").value<QUrl>().toLocalFile());
    if(!savableFile->open(QIODevice::WriteOnly))
    {
        DEBUG_TEXT(QString("Could not write to file %1").arg(object->property("file").value<QUrl>().toString()))
        return false;
    }

    QTextStream fileWriter(savableFile);
    fileWriter << savableObject->contentsToGDL();
    savableFile->close();

    delete(savableFile);

    // Remember to undirty yourself
    if(savableObject)
        savableObject->savableDirty = false;
    return true;
}
