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

#include "ocsgamedetailsprovider.h"
#include "ocsprovider.h"

#include <attica/listjob.h>
#include <attica/content.h>
#include <attica/provider.h>
#include <attica/downloaditem.h>

#include <QtCore/QStringList>
#include <QtCore/QDebug>

using namespace GluonPlayer;

class OcsGameDetails::Private
{
    public:
        Private()   { }

        QString gameName;
        QString gameDescription;
        QString projectDirName;
        QString projectFileName;
        QStringList screenshotUrls;
        int rating;
        Status status;
        QString id;
};

OcsGameDetails::OcsGameDetails( const QString& gameName, const QString& gameDescription,
                                const QString& projectDirName, const QString& projectFileName,
                                const QStringList& screenshotUrls, int rating, Status status, const QString id,
                                QObject* parent ) : QObject( parent ), d( new Private() )
{
    d->gameName = gameName;
    d->gameDescription = gameDescription;
    d->projectDirName = projectDirName;
    d->projectFileName = projectFileName;
    d->screenshotUrls = screenshotUrls;
    d->rating = rating;
    d->status = status;
    d->id = id;
}

OcsGameDetails::~OcsGameDetails()
{
    delete d;
}

QString OcsGameDetails::gameDescription() const
{
    return d->gameDescription;
}

QString OcsGameDetails::gameName() const
{
    return d->gameName;
}

QString OcsGameDetails::id() const
{
    return d->id;
}

QString OcsGameDetails::projectDirName() const
{
    return d->projectDirName;
}

QString OcsGameDetails::projectFileName() const
{
    return d->projectFileName;
}

QStringList OcsGameDetails::screenshotUrls() const
{
    return d->screenshotUrls;
}

OcsGameDetails::Status OcsGameDetails::status() const
{
    return d->status;
}

int GluonPlayer::OcsGameDetails::rating() const
{
    return d->rating;
}

class OcsGameDetailsProvider::Private
{
    public:
        Private() : provider( 0 ) { }

        Attica::Provider* provider;
        QString id;
};

OcsGameDetailsProvider::OcsGameDetailsProvider( Attica::Provider* provider, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
}

OcsGameDetailsProvider::OcsGameDetailsProvider( Attica::Provider* provider, const QString& id, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
    d->id = id;
}

void OcsGameDetailsProvider::fetchGameList()
{
    QStringList gluonGamesCategories;
    gluonGamesCategories << "4400" << "4410" << "4420" << "4430" << "4440";
    Attica::Category::List categories;

    foreach( const QString & gluonCategory, gluonGamesCategories )
    {
        Attica::Category category;
        category.setId( gluonCategory );
        categories.append( category );
    }

    Attica::ListJob<Attica::Content> *job = d->provider->searchContents( categories );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameList( Attica::BaseJob* ) ) );
    job->start();
}

void OcsGameDetailsProvider::processFetchedGameList( Attica::BaseJob* job )
{
    qDebug() << "Game List Successfully Fetched from the server!";
    QList<OcsGameDetails*> list;

    Attica::ListJob<Attica::Content> *contentJob = static_cast<Attica::ListJob<Attica::Content> *>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( Attica::Content content, contentJob->itemList() )
        {
            OcsGameDetails* details = new OcsGameDetails( content.name(), content.description(), "", "",
                    QStringList(), content.rating(), OcsGameDetails::Downloadable,
                    content.id() );
            list.append( details );
        }

        emit gameListFetched( list );
    }
    else
    {
        emit failedToFetchGameList();
    }
}

void OcsGameDetailsProvider::fetchGameDetails()
{
    Attica::ItemJob<Attica::Content> *job = d->provider->requestContent( d->id );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
    job->start();
}

void OcsGameDetailsProvider::processFetchedGameDetails( Attica::BaseJob* job )
{
    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content>*>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        Attica::Content content = contentJob->result();
        OcsGameDetails* details = new OcsGameDetails( content.name(), content.description(), "", "",
                QStringList(), content.rating(), OcsGameDetails::Downloadable,
                content.id() );
        gameDetailsFetched( details );
    }
    else
    {
        emit failedToFetchGameDetails( d->id );
    }
}


#include "ocsgamedetailsprovider.moc"
