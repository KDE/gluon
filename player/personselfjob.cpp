 
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
 
#include "personselfjob.h"
 
#include "serviceprovider.h"
 
#include <attica/itemjob.h>
#include <attica/person.h>
#include <attica/provider.h>
 
#include <QtCore/QStringList>
#include <QtCore/QDebug>
 
using namespace GluonPlayer;
 
class PersonSelfJob::Private
{
    public:
        PersonSelf *personData;
};
 
PersonSelfJob::PersonSelfJob( Attica::Provider* provider, QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
        
}
 
PersonSelfJob::~PersonSelfJob()
{
    delete d;
}
 
void PersonSelfJob::startSocialService()
{
    Attica::ItemJob<Attica::Person> *job = provider()->requestPersonSelf();
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedPersonSelf(Attica::BaseJob*)) );
    job->start();
}
 
void PersonSelfJob::processFetchedPersonSelf( Attica::BaseJob* job )
{
 
    Attica::ItemJob<Attica::Person> *personJob = static_cast<Attica::ItemJob<Attica::Person> *>( job );
    if( personJob->metadata().error() == Attica::Metadata::NoError )
    {
        Attica::Person person = personJob->result();
        d->personData = new PersonSelf( person.id(), person.firstName(), person.lastName() );
                
                qDebug() << "person/self -> success";
 
        emitSucceeded();
    }
    //let's assume that if there's an ocs error it will be surely come from authentication needed
    else if( personJob->metadata().error() == Attica::Metadata::OcsError )
        {
                qDebug() << "person/self -> auth needed (fail)";
                emitFailed();
        }
    else
    {
                qDebug() << "person/self -> unknown (fail)";
        emitFailed();
    }
}
 
void PersonSelfJob::start()
{
        startSocialService();
}
 
QVariant PersonSelfJob::data()
{
    return QVariant::fromValue( d->personData );
}