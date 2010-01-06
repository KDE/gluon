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
#include "gluonobject.h"
#include "asset.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QDir>

using namespace Gluon;

Savable::~Savable()
{
}

bool
Savable::saveToFile(Asset* asset)
{
    if(!asset)
        return false;
    
    // Make sure the filename is populated and is sane
    if(asset->file().isEmpty())
        asset->setFile( QUrl( QString("Scenes/%1.gdl").arg(asset->fullyQualifiedName()) ) );
    
    // Create appropriate folders
    if(!QDir::current().exists("Scenes"))
        QDir::current().mkdir("Scenes");
    
    // Perform the save
    QFile *savableFile = new QFile(asset->file().toLocalFile());
    if(!savableFile->open(QIODevice::WriteOnly))
        return false;
    
    QTextStream fileWriter(savableFile);
    fileWriter << asset->toGDL();
    savableFile->close();
    
    delete(savableFile);
    return true;
}
