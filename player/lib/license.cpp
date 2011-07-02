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

#include "license.h"

#include <attica/provider.h>

using namespace GluonPlayer;

class LicenseItem::Private
{
    public:
        Private() { }

        QString id;
        QString licenseName;
        QString licenseWebsite;
};

LicenseItem::LicenseItem( const QString& id, const QString& licenseName, const QString& licenseWebsite, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->id = id;
    d->licenseName = licenseName;
    d->licenseWebsite = licenseWebsite;
}

LicenseItem::~LicenseItem()
{
    delete d;
}

QString LicenseItem::licenseName() const
{
    return d->licenseName;
}

QString LicenseItem::id() const
{
    return d->id;
}

QString LicenseItem::licenseWebsite() const
{
    return d->licenseWebsite;
}

class License::Private
{
    public:
        Private() { }

        Attica::Provider* provider;
};

License::License( Attica::Provider* provider, QObject* parent )
    : QObject( parent ), d( new Private() )
{
    d->provider = provider;
}

License::~License()
{
    delete d;
}

void License::fetchLicenses()
{
    Attica::ListJob<Attica::License> *job = d->provider->requestLicenses();
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedLicenses( Attica::BaseJob* ) ) );
    job->start();
}

void License::processFetchedLicenses( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::License> *licensesJob = static_cast<Attica::ListJob<Attica::License> *>( job );

    QList<LicenseItem*> licenseList;

    if( licensesJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( Attica::License license, licensesJob->itemList() )
        {
            LicenseItem* newLicense = new LicenseItem( QString::number( license.id() ), license.name(), license.url().toString(), this );
            licenseList.append( newLicense );
        }

        emit licensesFetched( licenseList );
    }
    else
    {
        emit failed();
    }
}

#include "license.moc"
