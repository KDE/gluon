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

#include "gamedetail.h"

#include "serviceprovider.h"

#include <attica/listjob.h>
#include <attica/content.h>
#include <attica/provider.h>
#include <attica/downloaditem.h>

#include <QtCore/QStringList>
#include <QtCore/QDebug>

using namespace GluonPlayer;

class GameDetailItem::Private
{
    public:
        Private()
        {
        }

        QString gameName;
        QString gameDescription;
        QString projectDirName;
        QString projectFileName;
        QStringList screenshotUrls;
        int rating;
        Status status;
        QString id;
};

GameDetailItem::GameDetailItem( const QString& gameName, const QString& gameDescription,
                                const QString& projectDirName, const QString& projectFileName,
                                const QStringList& screenshotUrls, int rating,
                                GluonPlayer::GameDetailItem::Status status,
                                const QString id, QObject* parent )
    : QObject( parent )
    , d( new Private() )
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

GameDetailItem::~GameDetailItem()
{
    delete d;
}

QString GameDetailItem::gameDescription() const
{
    return d->gameDescription;
}

QString GameDetailItem::gameName() const
{
    return d->gameName;
}

QString GameDetailItem::id() const
{
    return d->id;
}

QString GameDetailItem::projectDirName() const
{
    return d->projectDirName;
}

QString GameDetailItem::projectFileName() const
{
    return d->projectFileName;
}

QStringList GameDetailItem::screenshotUrls() const
{
    return d->screenshotUrls;
}

GameDetailItem::Status GameDetailItem::status() const
{
    return d->status;
}

int GameDetailItem::rating() const
{
    return d->rating;
}

class GameDetail::Private
{
    public:
        Private()
            : provider( 0 )
        {
        }

        Attica::Provider* provider;
        QString id;
};

GameDetail::GameDetail( Attica::Provider* provider, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->provider = provider;
}

GameDetail::GameDetail( Attica::Provider* provider, const QString& id, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
    d->id = id;
}

void GameDetail::fetchGameList()
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
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGamesList( Attica::BaseJob* ) ) );
    job->start();
}

void GameDetail::processFetchedGamesList( Attica::BaseJob* job )
{
    qDebug() << "Game list successfully fetched from the server!";
    QList<GameDetailItem*> list;

    Attica::ListJob<Attica::Content> *contentJob = static_cast<Attica::ListJob<Attica::Content> *>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Content & content, contentJob->itemList() )
        {
            GameDetailItem* details = new GameDetailItem( content.name(), content.description(), "", "",
                    QStringList(), content.rating(), GameDetailItem::Downloadable,
                    content.id() );
            list.append( details );
            //Uncomment to test download, downloads to install dir/games/id
            //ServiceProvider::instance()->downloadGame(details->id());
        }

        emit gameListFetched( list );
    }
    else
    {
        emit failedToFetchGameList();
    }
}

void GameDetail::fetchGameDetails()
{
    Attica::ItemJob<Attica::Content> *job = d->provider->requestContent( d->id );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
    job->start();
}

void GameDetail::processFetchedGameDetails( Attica::BaseJob* job )
{
    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content>*>( job );

    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        Attica::Content content = contentJob->result();
        GameDetailItem* details = new GameDetailItem( content.name(), content.description(), "", "",
                                              QStringList(), content.rating(), GameDetailItem::Downloadable,
                                              content.id() );
        emit gameDetailsFetched( details );
    }
    else
    {
        emit failedToFetchGameDetails( d->id );
    }
}


#include "gamedetail.moc"
