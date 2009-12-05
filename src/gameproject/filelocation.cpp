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

#include "filelocation.h"
#include "filelocationprivate.h"
#include "gameproject.h"
#include <qfileinfo.h>

using namespace Gluon;

FileLocation::FileLocation(GameProject* parent, const QUrl &relativeUrl)
{
    d = new FileLocationPrivate;
    d->gameProject = parent;
    d->url = relativeUrl;
    
}

FileLocation::FileLocation(const FileLocation &other)
    : d(other.d)
{
}

FileLocation::~FileLocation()
{
    delete(d);
}

QUrl
FileLocation::location() const
{
    #warning This may well make better sense using KIOSlaves... we should consider this very seriously for the possibility of allowing remote content
    
    // Don't attempt to use the gameProject if it doesn't exist yet - fall back
    if(!d->gameProject)
        return d->url;
    
    return QUrl(QFileInfo(d->gameProject->filename().toLocalFile()).canonicalPath() + d->url.toString());
}
