 
/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include "models/personitem.h"
#include "getfriendsjob.h"

#include <QtCore/QObject>

#include <attica/provider.h>
#include <attica/listjob.h>
#include <attica/person.h>

using namespace GluonPlayer;

class GetFriendsJob::Private
{
    public:
        Private()
        {
        }

        QString id;
        QList<PersonItem*> personsList;
};

//specify here new filters eventually
GetFriendsJob::GetFriendsJob( Attica::Provider* provider, const QString& id)
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
}

GetFriendsJob::~GetFriendsJob()
{
    delete d;
}

void GetFriendsJob::startSocialService()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::ListJob<Attica::Person> *job = provider()->requestFriends( d->id );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedPersonList(Attica::BaseJob*)) );
    job->start();
}

void GetFriendsJob::processFetchedPersonList( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Person> *personsJob = static_cast<Attica::ListJob<Attica::Person> *>( job );
    if( personsJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Person & person, personsJob->itemList() )
        {
            PersonItem* newPerson = new PersonItem( person.id(), person.firstName(), person.lastName(), this );
            d->personsList.append( newPerson );
        }

        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant GetFriendsJob::data()
{
    return QVariant::fromValue( d->personsList );
}
