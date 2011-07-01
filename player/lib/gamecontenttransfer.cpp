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

#include "gamecontenttransfer.h"

#include <attica/itemjob.h>
#include <attica/downloaditem.h>
#include <attica/postjob.h>
#include <attica/provider.h>

#include <QtNetwork/QNetworkReply>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <QDebug>

#include "archive/extractor.h"

using namespace GluonPlayer;

class GameContentTransfer::Private
{
    public:
        Private()
            : provider( 0 )
        {
        }

        Attica::Provider* provider;
        QString id;
        QString destinationDir;
        QString fileName;
};


GameContentTransfer::GameContentTransfer( Attica::Provider* provider, const QString& id,
        const QString& fileName, const QString& destinationDir, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->provider = provider;
    d->id = id;
    d->fileName = fileName;
}

GameContentTransfer::~GameContentTransfer()
{
    delete d;
}

void GameContentTransfer::startDownload()
{
    Attica::ItemJob<Attica::DownloadItem> *job = d->provider->downloadLink( d->id );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processDownloadLink( Attica::BaseJob* ) ) );
    job->start();
}

void GameContentTransfer::processDownloadLink( Attica::BaseJob* baseJob )
{
    Attica::ItemJob<Attica::DownloadItem>* job = static_cast<Attica::ItemJob<Attica::DownloadItem>*>( baseJob );
    Attica::DownloadItem item = job->result();

    QFileInfo info( item.url().path() );
    d->fileName = info.fileName();

    if( d->fileName.isEmpty() )
    {
        emit downloadFailed();
        return;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager( this );
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( downloadComplete( QNetworkReply* ) ) );
    QNetworkReply* reply = manager->get( QNetworkRequest( item.url() ) );
    connect( reply, SIGNAL( downloadProgress( qint64, qint64 ) ), SLOT( updateDownloadProgress( qint64, qint64 ) ) );
    emit startedDownload();
}

void GameContentTransfer::downloadComplete( QNetworkReply* reply )
{
    QDir destDir( d->destinationDir );
    QFile file( destDir.filePath( d->fileName ) );
    file.open( QIODevice::WriteOnly );
    file.write( reply->readAll() );
    file.close();
    reply->deleteLater();

    Extractor extractor( destDir.filePath( d->fileName ), d->destinationDir );
    extractor.start();
    emit downloadFinished();
}

void GameContentTransfer::updateDownloadProgress( qint64 bytesReceived, qint64 bytesTotal )
{
    emit downloadProgress( bytesReceived, bytesTotal );
    qDebug() << ( bytesReceived * 100 ) / bytesTotal << "% done " << bytesReceived << " of " << bytesTotal;
}

void GameContentTransfer::startUpload()
{
    QFile file( d->fileName );

    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Failed to open file:" << d->fileName;
        emit uploadFailed();
        return;
    }

    QByteArray contents;
    contents.append( file.readAll() );
    file.close();

    QFileInfo fileInfo( d->fileName );
    Attica::PostJob* job = d->provider->setDownloadFile( d->id, fileInfo.fileName(), contents );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( uploadComplete( Attica::BaseJob* ) ) );
    job->start();
}

void GameContentTransfer::uploadComplete( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = static_cast<Attica::PostJob*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        emit uploadFinished();
    }
    else
    {
        emit uploadFailed();
    }
}

#include "gamecontenttransfer.moc"
