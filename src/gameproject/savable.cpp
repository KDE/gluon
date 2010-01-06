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
#include "gdlhandler.h"
#include "asset.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>

using namespace Gluon;

Savable::~Savable()
{
}

bool
Savable::saveToFile(QString fileContents) const
{
    const Asset * asset = dynamic_cast<const Asset*>(this);
    if(!asset)
        return false;
    
    QFile *savableFile = new QFile(asset->file().toLocalFile());
    if(!savableFile->open(QIODevice::WriteOnly))
        return false;
    
    QTextStream fileWriter(savableFile);
    fileWriter << fileContents;
    savableFile->close();
    
    delete(savableFile);
    return true;
}
