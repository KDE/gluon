/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "abstractsocialservicesjob.h"

#include <attica/provider.h>
#include "serviceprovider.h"

using namespace GluonPlayer;

class AbstractSocialServicesJob::Private
{
    public:
        Private() : provider( 0 ) { }
        ~Private();

        Attica::Provider* provider;
};

AbstractSocialServicesJob::AbstractSocialServicesJob( Attica::Provider* provider )
    : AbstractJob()
    , d( new Private() )
{
    d->provider = provider;
}

void AbstractSocialServicesJob::startImplementation()
{
    if( d->provider->isValid() )
    {
        startSocialService();
    }
    else
    {
        connect( GluonPlayer::ServiceProvider::instance(), SIGNAL( initializeFinished() ), SLOT( startSocialService() ) );
    }
}

Attica::Provider* AbstractSocialServicesJob::provider()
{
    return d->provider;
}

#include "abstractsocialservicesjob.moc"
