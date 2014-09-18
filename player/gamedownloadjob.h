/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#ifndef GLUONPLAYER_GAMEDOWNLOADJOB_H
#define GLUONPLAYER_GAMEDOWNLOADJOB_H

#include "abstractsocialservicesjob.h"

#include "gluon_player_export.h"

namespace Attica
{
    class Provider;
    class BaseJob;
}

class QNetworkReply;

namespace GluonPlayer
{

    class GLUON_PLAYER_EXPORT GameDownloadJob : public AbstractSocialServicesJob
    {
            Q_OBJECT

        public:
            GameDownloadJob( Attica::Provider* provider, const QString& id, const QString& destinationDir,
                             QObject* parent = 0 );
            virtual ~GameDownloadJob();

            virtual QVariant data();

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void processDownloadLink( Attica::BaseJob* baseJob );
            void downloadComplete( QNetworkReply* reply );
            void updateDownloadProgress( qint64 bytesReceived, qint64 bytesTotal );

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONPLAYER_GAMEDOWNLOADJOB_H
