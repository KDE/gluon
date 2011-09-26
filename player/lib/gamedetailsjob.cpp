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

#include "gamedetailsjob.h"

#include "serviceprovider.h"

#include <attica/itemjob.h>
#include <attica/content.h>
#include <attica/provider.h>
#include <attica/downloaditem.h>

#include <QtCore/QStringList>
#include <QtCore/QDebug>

using namespace GluonPlayer;

class GameDetailsJob::Private
{
    public:
        QString id;
        GameDetailItem *gameDetails;
};

GameDetailsJob::GameDetailsJob( Attica::Provider* provider, const QString& id,  QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
}

GameDetailsJob::~GameDetailsJob()
{
    delete d;
}

void GameDetailsJob::startSocialService()
{
    Attica::ItemJob<Attica::Content> *job = provider()->requestContent (d->id);
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGameDetails( Attica::BaseJob* ) ) );
    job->start();
}

void GameDetailsJob::processFetchedGameDetails( Attica::BaseJob* job )
{
    qDebug() << "Game list successfully fetched from the server!";


    Attica::ItemJob<Attica::Content> *contentJob = static_cast<Attica::ItemJob<Attica::Content> *>( job );
    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        Attica::Content content = contentJob->result();
        d->gameDetails = new GameDetailItem( content.name(), content.description(), content.version(),
                content.attribute("typeid"), content.homePageEntry( 0 ).url().toString(),
                content.license(), content.changelog(), "", "", QStringList(),
                content.rating(), GameDetailItem::Downloadable, content.id() );

        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant GameDetailsJob::data()
{
    return QVariant::fromValue( d->gameDetails );
}

Q_DECLARE_METATYPE( GluonPlayer::GameDetailItem* )

#include "gamedetailsjob.moc"
