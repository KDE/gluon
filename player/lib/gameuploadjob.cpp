/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright 2010 Artur Duque de Souza <asouza@kde.org>
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

#include "gameuploadjob.h"

#include "editgamejob.h"
#include "serviceprovider.h"

#include <attica/postjob.h>
#include <attica/provider.h>

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>

using namespace GluonPlayer;

//this is quite pointless now
static const QString s_dataServerUrl = "http://gamingfreedom.org/v1/";

class GameUploadJob::Private
{
    public:
        Private()
        {
        }

        ~Private()
        {
        }

        QString id;
        QString fileName;
        QString apiKey;
};

GameUploadJob::GameUploadJob( Attica::Provider* provider, const QString& id, const QString& fileName, QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
    d->fileName = fileName;
}

GameUploadJob::~GameUploadJob()
{
    delete d;
}

void GameUploadJob::startSocialService()
{
    QFile file( d->fileName );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Failed to open file:" << d->fileName;
        emitFailed();
        return;
    }

    qint64 size = file.size();
    file.close();

    //Check if the file is greater than 700K
    //If greater, upload to data.gamingfreedom.org
    //else upload to opendesktop.org using attica

    if (size > 716800) {         // 700 * 1024
        uploadFileToDataServer();
    } else {
        uploadFileToDataServer();       //Workaround as Provider::setDownloadFile is faulty
        //uploadFileUsingAttica();
    }
}

void GameUploadJob::uploadComplete( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = static_cast<Attica::PostJob*>( baseJob );
    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant GameUploadJob::data()
{
    return d->id;
}

void GameUploadJob::uploadFileUsingAttica()
{
    QFile file( d->fileName );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Failed to open file:" << d->fileName;
        emitFailed();
        return;
    }

    QByteArray contents;
    contents.append( file.readAll() );
    file.close();

    QFileInfo fileInfo( d->fileName );
    Attica::PostJob* job = provider()->setDownloadFile( d->id, fileInfo.fileName(), contents );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(uploadComplete(Attica::BaseJob*)) );
    job->start();
}

void GameUploadJob::uploadFileToDataServer()
{
    QFile file( d->fileName );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Failed to open file:" << d->fileName;
        emitFailed();
        return;
    }

    qDebug() << "UPLOADING " << d->fileName << " WITHOUT API ";
    QByteArray buffer;

    QByteArray boundary("----------");
    boundary += QString::number(QDateTime::currentMSecsSinceEpoch()).toAscii();

    const QByteArray contentKey = "localfile";        //equivalent to <input type="file" name="localfile" />
    const QByteArray mimetype = "application/octet-stream";

    const QByteArray data = file.readAll();
    const QByteArray fileSize = QString("%1").arg(data.size()).toAscii();

    // Add the HTTP POST with the content of the file
    QByteArray str;

    str += "--";
    str += boundary;
    str += "\r\n";
    str += "Content-Disposition: form-data; name=\"";
    str += contentKey;
    str += "\"; ";
    str += "filename=\"";
    str += QFile::encodeName(QFileInfo(d->fileName).fileName());
    str += "\"\r\n";
    str += "Content-Length: ";
    str += fileSize;
    str += "\r\n";
    str += "Content-Type: ";
    str +=  mimetype;
    str += "\r\n\r\n";

    buffer.append(str);
    buffer.append(data);
    buffer.append("\r\n");
	buffer.append("--");
	buffer.append(boundary);
	buffer.append("--\r\n");

    // Add the HTTP POST with the API key
	
	/* Just no for now. No api key is required on gluon ocs server for now.
    QString apikeyData;

    apikeyData += "--";
    apikeyData += boundary;
    apikeyData += "\r\n";
    apikeyData += "Content-Disposition: form-data; name=\"apikey\"\r\n\r\n";
    apikeyData += d->apiKey.toAscii();
    apikeyData += "\r\n";
    apikeyData += "--";
    apikeyData += boundary;
    apikeyData += "--\r\n";

    buffer.append(apikeyData);
	*/
	QString username = ServiceProvider::instance()->username();
	QString password = ServiceProvider::instance()->password();
	QString serverUrl = ServiceProvider::instance()->serverUrl();
	
    QNetworkRequest request;
    request.setUrl(QUrl("http://"+username+":"+password+"@"+serverUrl+"content/uploaddownload/"+d->id));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QByteArray("multipart/form-data; boundary=" + boundary));
    request.setHeader(QNetworkRequest::ContentLengthHeader, buffer.length());
	
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(uploadFileToDataServerDone(QNetworkReply*)));
    manager->post(request, buffer);
}

void GameUploadJob::uploadFileToDataServerDone(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        emitSucceeded();
    } else {
        emitFailed();
    }
}

/*
 * For now, internal gluon ocs server will handle these kind of things.
 * Don't want to mess further in order to avoid adding complexity
 */
void GameUploadJob::updateDistributionServerWithDownloadUrl(const QString &url)
{
    const QString completeUrl = s_dataServerUrl + url;

    EditGameJob *editJob = ServiceProvider::instance()->editGame(d->id);
    editJob->setDownloadType("1");
    editJob->setDownloadPrice("0");
    editJob->setDownloadLink(completeUrl);
    editJob->setDownloadName("Game Archive");
    connect(editJob, SIGNAL(succeeded()), SLOT(updateDistributionServerWithDownloadUrlDone()));
    connect(editJob, SIGNAL(failed()), SLOT(updateDistributionServerWithDownloadUrlFailed()));
    editJob->start();
}

void GameUploadJob::updateDistributionServerWithDownloadUrlDone()
{
    emitSucceeded();
}

void GameUploadJob::updateDistributionServerWithDownloadUrlFailed()
{
    emitFailed();
}

void GameUploadJob::setApiKey(const QString& apiKey)
{
    d->apiKey = apiKey;
}

#include "gameuploadjob.moc"
