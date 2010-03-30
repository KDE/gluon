/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "filelocation.h"
#include "filelocationprivate.h"

#include "gameproject.h"
#include <qfileinfo.h>

#include "core/debughelper.h"

using namespace GluonEngine;

FileLocation::FileLocation(GluonEngine::GameProject* parent, const QUrl &relativeUrl)
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
    #ifdef __GNUC__
    #warning This may well make better sense using KIOSlaves... we should consider this very seriously for the possibility of allowing remote content
    #endif

    // Bah, this am not workey... needs more thinkings
    return d->url;

    // Don't attempt to use the gameProject if it doesn't exist yet - fall back
    if (!d->gameProject)
        return d->url;

    return QUrl(QFileInfo(d->gameProject->filename().toLocalFile()).canonicalPath() + d->url.toLocalFile());
}
