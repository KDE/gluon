/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_GAMECONTENTJOB_H
#define GLUONPLAYER_GAMECONTENTJOB_H

#include "abstractjob.h"

class QNetworkReply;

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class GameContentJob : public AbstractJob
    {
        Q_OBJECT
    public:
        GameContentJob(Attica::Provider* provider, const QString& id, const QString& fileName,
                             const QString& destinationDir = QString(), QObject* parent = 0);
        virtual ~GameContentJob();

        virtual void start();

    Q_SIGNALS:
        void downloadStarted();
        void downloadFinished();
        void downloadFailed();

        void uploadFinished();
        void uploadFailed();

    private Q_SLOTS:
        void startDownload();
        void processDownloadLink(Attica::BaseJob* baseJob);
        void downloadComplete(QNetworkReply *reply);

        void startUpload();
        void uploadComplete(Attica::BaseJob* baseJob);

    private:
        class Private;
        Private* const d;
    };
}

#endif // GLUONPLAYER_GAMECONTENTJOB_H
