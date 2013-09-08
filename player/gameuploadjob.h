/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_PLAYER_GAMEUPLOADJOB_H
#define GLUON_PLAYER_GAMEUPLOADJOB_H

#include "abstractsocialservicesjob.h"

#include "gluon_player_export.h"

class QNetworkReply;

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT GameUploadJob : public AbstractSocialServicesJob
    {
            Q_OBJECT
        public:
            GameUploadJob( Attica::Provider* provider, const QString& id, const QString& fileName, QObject* parent = 0 );
            virtual ~GameUploadJob();

            virtual QVariant data();
            void setApiKey( const QString& apiKey );

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void uploadComplete( Attica::BaseJob* baseJob );
            void uploadFileToDataServerDone( QNetworkReply* reply );
            void updateDistributionServerWithDownloadUrlDone();
            void updateDistributionServerWithDownloadUrlFailed();

        private:
            void uploadFileToDataServer();
            void uploadFileUsingAttica();
            void updateDistributionServerWithDownloadUrl( const QString& url );

            class Private;
            Private* const d;
    };
}

#endif // GLUON_PLAYER_GAMEUPLOADJOB_H
