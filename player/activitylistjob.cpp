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

#include "activitylistjob.h"
#include "models/personitem.h"
#include "models/activityitem.h"

#include <attica/provider.h>
#include <attica/listjob.h>
#include <attica/person.h>
#include <attica/activity.h>

using namespace GluonPlayer;

class ActivityListJob::Private
{
    public:
        Private()
        {
        }

        QList<ActivityItem*> activityList;
};

//specify here new filters eventually
ActivityListJob::ActivityListJob( Attica::Provider* provider )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
}

ActivityListJob::~ActivityListJob()
{
    delete d;
}

void ActivityListJob::startSocialService()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::ListJob<Attica::Activity> *job = provider()->requestActivities( );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedActivityList(Attica::BaseJob*)) );
    job->start();
}

void ActivityListJob::processFetchedActivityList( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Activity> *activityJob = static_cast<Attica::ListJob<Attica::Activity> *>( job );
    if( activityJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Activity & activity, activityJob->itemList() )
        {
            ActivityItem* newActivity = new ActivityItem( activity.id(), activity.associatedPerson().firstName(), activity.associatedPerson().lastName(), activity.message(), this );
            d->activityList.append( newActivity );
        }

        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant ActivityListJob::data()
{
    return QVariant::fromValue( d->activityList );
}
