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

#include "ocsgamedownloadprovider.h"

#include <attica/itemjob.h>
#include <attica/downloaditem.h>
#include <attica/provider.h>

#include <QtNetwork/QNetworkReply>
#include <QtCore/QFile>
#include <QtCore/QDir>

#include <QDebug>

#include "archive/extractor.h"

using namespace GluonPlayer;

class OcsGameDownloadProvider::Private
{
public:
    Private() : provider(0)   { }

    Attica::Provider *provider;
    QString id;
    QString destinationDir;
    QString fileName;
};

OcsGameDownloadProvider::OcsGameDownloadProvider (Attica::Provider *provider, const QString& id,
                                                  const QString& destinationDir, QObject* parent)
                                                    : QObject (parent), d(new Private)
{
    d->provider = provider;
    d->id = id;
    d->destinationDir = destinationDir;
}

OcsGameDownloadProvider::~OcsGameDownloadProvider()
{
    delete d;
}

void OcsGameDownloadProvider::startDownload()
{
    Attica::ItemJob<Attica::DownloadItem> *job = d->provider->downloadLink(d->id);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processDownloadLink(Attica::BaseJob*)));
    job->start();
}

void OcsGameDownloadProvider::processDownloadLink (Attica::BaseJob* baseJob)
{
    Attica::ItemJob<Attica::DownloadItem>* job = static_cast<Attica::ItemJob<Attica::DownloadItem>*>(baseJob);
    Attica::DownloadItem item = job->result();

    QFileInfo info(item.url().path());
    d->fileName = info.fileName();
    if (d->fileName.isEmpty()) {
        emit failed();
        return;
    }
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadComplete(QNetworkReply*)));
    QNetworkReply *reply = manager->get(QNetworkRequest(item.url()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(updateDownloadProgress(qint64,qint64)));
    emit startedDownload();
}

void OcsGameDownloadProvider::downloadComplete (QNetworkReply* reply)
{
    QDir destDir(d->destinationDir);
    QFile file(destDir.filePath(d->fileName));
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();

    Extractor extractor(destDir.filePath(d->fileName), d->destinationDir);
    extractor.start();
    emit finished();
}

void OcsGameDownloadProvider::updateDownloadProgress (qint64 bytesReceived, qint64 bytesTotal)
{
    downloadProgress(bytesReceived, bytesTotal);
    qDebug() << (bytesReceived*100)/bytesTotal << "% done " << bytesReceived << " of " << bytesTotal;
}

#include "ocsgamedownloadprovider.moc"


