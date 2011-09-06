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

#include "gamedetaillistjob.h"

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
        QString version;
        QString category;
        QString homePage;
        QString license;
        QString changelog;
        QString projectDirName;
        QString projectFileName;
        QStringList screenshotUrls;
        int rating;
        Status status;
        QString id;
};

GameDetailItem::GameDetailItem( const QString& gameName, const QString& gameDescription, const QString& version,
                                const QString& category, const QString& homePage, const QString& license,
                                const QString& changelog, const QString& projectDirName, const QString& projectFileName,
                                const QStringList& screenshotUrls, int rating, GluonPlayer::GameDetailItem::Status status,
                                const QString id, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->gameName = gameName;
    d->gameDescription = gameDescription;
    d->version = version;
    d->category = category;
    d->homePage = homePage;
    d->license = license;
    d->changelog = changelog;
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

QString GameDetailItem::version() const
{
    return d->version;
}

QString GameDetailItem::category() const
{
    return d->category;
}

QString GameDetailItem::homePage() const
{
    return d->homePage;
}

QString GameDetailItem::license() const
{
    return d->license;
}

QString GameDetailItem::changelog() const
{
    return d->changelog;
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

class GameDetailListJob::Private
{
    public:
        QList<GameDetailItem*> gameDetailList;
};

GameDetailListJob::GameDetailListJob( Attica::Provider* provider, QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{

}

GameDetailListJob::~GameDetailListJob()
{
    delete d;
}

void GameDetailListJob::startSocialService()
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

    Attica::ListJob<Attica::Content> *job = provider()->searchContents( categories );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameList( Attica::BaseJob* ) ) );
    job->start();
}

void GameDetailListJob::processFetchedGameList( Attica::BaseJob* job )
{
    qDebug() << "Game list successfully fetched from the server!";

    d->gameDetailList.clear();

    Attica::ListJob<Attica::Content> *contentJob = static_cast<Attica::ListJob<Attica::Content> *>( job );
    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Content & content, contentJob->itemList() )
        {
            GameDetailItem* details = new GameDetailItem( content.name(), content.description(), content.version(),
                    content.attribute("typeid"), content.homePageEntry( 0 ).url().toString(),
                    content.license(), content.changelog(), "", "", QStringList(),
                    content.rating(), GameDetailItem::Downloadable, content.id() );
            d->gameDetailList.append( details );
        }

        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant GameDetailListJob::data()
{
    return QVariant::fromValue( d->gameDetailList );
}

Q_DECLARE_METATYPE( QList<GluonPlayer::GameDetailItem*> )

#include "gamedetaillistjob.moc"
