/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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


#ifndef GLUONPLAYER_GAMEDOWNLOADMANAGER_H
#define GLUONPLAYER_GAMEDOWNLOADMANAGER_H

#include "gluon_player_export.h"
#include <gluon/core/singleton.h>

#include <attica/content.h>
#include <attica/listjob.h>

#include <QStringList>
#include <QHash>

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT GameDownloadManager : public GluonCore::Singleton<GameDownloadManager>
    {
            Q_OBJECT
        public:
            GameDownloadManager();
            bool addDownload ( const QString &id );

        protected slots:
            void providersUpdated();
            void processFetchedGameDetails ( Attica::BaseJob* job );

        private:
            bool alreadyDownloading;
            QString m_id;
    };

}

#endif // GLUONPLAYER_GAMEDOWNLOADMANAGER_H
