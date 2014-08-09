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

#include "declinefriendjob.h"

#include <attica/provider.h>
#include <attica/content.h>

using namespace GluonPlayer;

class DeclineFriendJob::Private
{
    public:
        QString to;
};

DeclineFriendJob::DeclineFriendJob( Attica::Provider* provider, const QString& to, QObject* parent )
    : AbstractSocialServicesJob( provider )
    , d( new Private )
{
    d->to = to;
}

DeclineFriendJob::~DeclineFriendJob()
{
    delete d;
}

void DeclineFriendJob::startSocialService( )
{
    Attica::PostJob *job = provider()->declineFriendship( d->to );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(declineFriendComplete(Attica::BaseJob*)) );
    job->start();
}

void DeclineFriendJob::declineFriendComplete( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = static_cast<Attica::PostJob*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        emitSucceeded();
    }
    else
    {
        qDebug() << job->metadata().error();
        emitFailed();
    }
}

QVariant DeclineFriendJob::data()
{
    return d->to;
}
 
