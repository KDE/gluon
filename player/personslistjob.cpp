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

#include "personslistjob.h"

#include <attica/provider.h>
#include <attica/listjob.h>
#include <attica/person.h>

using namespace GluonPlayer;

class PersonItem::Private
{
    public:
        Private()
        {
        }

        QString id;
        QString firstname;
        QString lastname;
};

PersonItem::PersonItem( const QString& id, const QString& firstname, const QString& lastname, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->id = id;
    d->firstname = firstname;
    d->lastname = lastname;
}

PersonItem::~PersonItem()
{
    delete d;
}

QString PersonItem::id() const
{
    return d->id;
}

QString PersonItem::firstname() const
{
    return d->firstname;
}

QString PersonItem::lastname() const
{
    return d->lastname;
}

class PersonsListJob::Private
{
    public:
        Private()
            : page( 0 )
            , pageSize( 0 )
        {
        }

        QString id;
        int page;
        int pageSize;
        QList<PersonItem*> personsList;
};

//specify here new filters eventually
PersonsListJob::PersonsListJob( Attica::Provider* provider, const QString& id, int page, int pageSize )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
    d->page = page;
    d->pageSize = pageSize;
}

PersonsListJob::~PersonsListJob()
{
    delete d;
}

void PersonsListJob::startSocialService()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::ListJob<Attica::Person> *job = provider()->requestPersonSearchByName( d->id );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedCommentList(Attica::BaseJob*)) );
    job->start();
}

void PersonsListJob::processFetchedPersonList( Attica::BaseJob* job )
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

QVariant PersonsListJob::data()
{
    return QVariant::fromValue( d->personsList );
}
