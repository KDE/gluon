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

#include "gamedownloadjob.h"

#include "archive/extractor.h"

#include <attica/provider.h>
#include <attica/downloaditem.h>

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtNetwork/QNetworkReply>

#include <QtCore/QDebug>

using namespace GluonPlayer;

class GameDownloadJob::Private
{
    public:
        QString id;
        QString fileName;
        QString destinationDir;
        QString finalDownloadLocation;
};

GameDownloadJob::GameDownloadJob( Attica::Provider* provider, const QString& id, const QString& destinationDir,
                             QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
    d->destinationDir = destinationDir;
}

GameDownloadJob::~GameDownloadJob()
{
    delete d;
}

void GameDownloadJob::startSocialService()
{
    Attica::ItemJob<Attica::DownloadItem> *job = provider()->downloadLink( d->id );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processDownloadLink( Attica::BaseJob* ) ) );
    job->start();
}

void GameDownloadJob::processDownloadLink( Attica::BaseJob* baseJob )
{
    Attica::ItemJob<Attica::DownloadItem>* job = static_cast<Attica::ItemJob<Attica::DownloadItem>*>( baseJob );
    Attica::DownloadItem item = job->result();

    QFileInfo info( item.url().path() );
    d->fileName = info.fileName();
    if( d->fileName.isEmpty() )
    {
        emitFailed();
        return;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager( this );
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( downloadComplete( QNetworkReply* ) ) );
    QNetworkReply* reply = manager->get( QNetworkRequest( item.url() ) );
    connect( reply, SIGNAL( downloadProgress(qint64,qint64)), SLOT(updateDownloadProgress(qint64,qint64)) );
}

void GameDownloadJob::downloadComplete( QNetworkReply* reply )
{
    QDir destDir( d->destinationDir );
    QFile file( destDir.filePath( d->fileName ) );
    d->finalDownloadLocation = file.fileName();
    file.open( QIODevice::WriteOnly );
    file.write( reply->readAll() );
    file.close();
    reply->deleteLater();

    Extractor extractor( destDir.filePath( d->fileName ), d->destinationDir );
    extractor.start();

    emitSucceeded();
}

void GameDownloadJob::updateDownloadProgress( qint64 bytesReceived, qint64 bytesTotal )
{
    qDebug() << ( bytesReceived * 100 ) / bytesTotal << "% done " << bytesReceived << " of " << bytesTotal;
}

QVariant GameDownloadJob::data()
{
    return QVariant( d->finalDownloadLocation );
}

#include "gamedownloadjob.moc"
