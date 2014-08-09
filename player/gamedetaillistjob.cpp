/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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
    qDebug() << "fetching games...";
    Attica::ListJob<Attica::Content> *job = provider()->searchContents( QList<Attica::Category>() );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedGameList(Attica::BaseJob*)) );
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
            GameDetailItem* details = new GameDetailItem( content.name(), content.description(), content.version(), content.summary(), content.attribute("preview1"),
                    content.attribute("typeid"), content.attribute("typename"), content.homePageEntry( 0 ).url().toString(),
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