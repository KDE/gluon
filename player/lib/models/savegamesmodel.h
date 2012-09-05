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

#ifndef GLUON_PLAYER_SAVEGAMESMODEL_H
#define GLUON_PLAYER_SAVEGAMESMODEL_H

#include "lib/gluon_player_export.h"

#include <QtCore/QAbstractItemModel>

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT SaveGamesModel : public QAbstractItemModel
    {
        Q_OBJECT
        
        public:
            SaveGamesModel( GluonEngine::ProjectMetaData* metaData, const QString& userName, QObject* parent = 0 );
            virtual ~SaveGamesModel();
    };
}


#endif