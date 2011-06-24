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

#include "ocsgameuploadprovider.h"

#include <attica/postjob.h>
#include <attica/provider.h>

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>

using namespace GluonPlayer;

class OcsGameUploadProvider::Private
{
    public:
        Private() : provider( 0 )   { }

        Attica::Provider* provider;
        QString id;
        QString fileName;
};


OcsGameUploadProvider::OcsGameUploadProvider( Attica::Provider* provider, const QString& id,
        const QString& fileName, QObject* parent ) : QObject( parent ), d( new Private )
{
    d->provider = provider;
    d->id = id;
    d->fileName = fileName;
}

OcsGameUploadProvider::~OcsGameUploadProvider()
{
    delete d;
}

void OcsGameUploadProvider::startUpload()
{
    QFile file( d->fileName );

    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Failed to open file " << d->fileName;
        emit failed( d->id );
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

void OcsGameUploadProvider::uploadComplete( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = static_cast<Attica::PostJob*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        emit finished( d->id );
    }
    else
    {
        emit failed( d->id );
    }
}

#include "ocsgameuploadprovider.moc"
