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

#include "ocsratingprovider.h"

#include <attica/postjob.h>
#include <attica/provider.h>

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>

using namespace GluonPlayer;

class OcsRatingProvider::Private
{
public:
    Private() : provider(0)   { }

    Attica::Provider *provider;
    QString id;
    uint rating;
};


OcsRatingProvider::OcsRatingProvider (Attica::Provider* provider, const QString& id,
                                              uint rating, QObject* parent) : QObject (parent), d(new Private)
{
    d->provider = provider;
    d->id = id;
    d->rating = rating;
}

OcsRatingProvider::~OcsRatingProvider()
{
    delete d;
}


void OcsRatingProvider::startRatingUpload()
{
    Attica::PostJob *job = d->provider->voteForContent(d->id, d->rating);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(ratingUploadComplete(Attica::BaseJob*)));
    job->start();
}

void OcsRatingProvider::ratingUploadComplete (Attica::BaseJob* baseJob)
{
    Attica::PostJob *job = static_cast<Attica::PostJob*>(baseJob);
    if (job->metadata().error() == Attica::Metadata::NoError) {
        emit finished();
    } else {
        emit failed();
    }
}

#include "ocsratingprovider.moc"
