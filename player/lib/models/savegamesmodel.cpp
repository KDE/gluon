/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
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

#include "savegamesmodel.h"

#include <engine/projectmetadata.h>

using namespace GluonPlayer;

class SaveGamesModel::SaveGamesModelPrivate
{
    public:
        SaveGamesModelPrivate() {}
        ~SaveGamesModelPrivate() {}
        QString saveGamesDirectory;
};

SaveGamesModel::SaveGamesModel( GluonEngine::ProjectMetaData* metaData, const QString& userName, QObject* parent )
    : QAbstractItemModel( parent )
{
    
}

SaveGamesModel::~SaveGamesModel()
{
}

#include "savegamesmodel.moc"