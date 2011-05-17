/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "ocsprovider.h"

#include "ocscommentsprovider.h"

#include <attica/content.h>
#include <attica/listjob.h>
#include <attica/provider.h>
#include <attica/providermanager.h>

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON (OcsProvider)

class OcsProvider::Private
{
public:
    Private() : ready (false) {
    }

    bool ready;
    bool loggedIn;
    Attica::ProviderManager manager;
    Attica::Provider provider;
    QString username;
    QString password;
};

OcsProvider::OcsProvider() : d (new Private())
{
    init();
}

bool OcsProvider::isReady() const
{
    return d->ready;
}

void OcsProvider::init()
{
    if (d->ready) {
        return;
    }
    connect (&d->manager, SIGNAL (defaultProvidersLoaded()), SLOT (providersUpdated()));
    d->manager.loadDefaultProviders();
}

void OcsProvider::providersUpdated()
{
    if (!d->manager.providers().isEmpty()) {
        d->provider = d->manager.providerByUrl (QUrl ("https://api.opendesktop.org/v1/"));
        if (!d->provider.isValid()) {
            emit failedToInitialize();
        } else {
            d->ready = true;
            loadCredentials();
        }
    }
}

void OcsProvider::loadCredentials()
{
    if (!d->ready) {
        return;
    }

    if (d->provider.hasCredentials()) {
        d->provider.loadCredentials(d->username, d->password);
    }

    emit providerInitialized();
}

OcsCommentsProvider* OcsProvider::fetchComments (const QString& id, int page, int pageSize)
{
    if (d->ready) {
        return new OcsCommentsProvider (&d->provider, id, page, pageSize);
    } else {
        return 0;
    }
}

OcsCommentsProvider* OcsProvider::uploadComment (const QString& id, const QString& parentId,
        const QString& subject, const QString& message)
{
    if (d->ready && d->loggedIn) {
        return new OcsCommentsProvider (&d->provider, id, parentId, subject, message);
    } else {
        return 0;
    }
}

bool OcsProvider::hasCredentials()
{
    return d->provider.hasCredentials();
}

bool OcsProvider::isLoggedIn()
{
    return d->loggedIn;
}

bool OcsProvider::login (const QString& username, const QString& password)
{
    if (!d->ready || d->loggedIn) {
        return false;
    }

    d->username = username;
    d->password = password;

    Attica::PostJob* job = d->provider.checkLogin (d->username, d->password);
    connect (job, SIGNAL (finished (Attica::BaseJob*)), SLOT (checkLoginResult (Attica::BaseJob*)));
    job->start();
    return true;
}

void OcsProvider::checkLoginResult (Attica::BaseJob* baseJob)
{
    Attica::PostJob* job = qobject_cast<Attica::PostJob*> (baseJob);

    if (job->metadata().error() == Attica::Metadata::NoError) {
        if (d->provider.saveCredentials (d->username, d->password)) {
            d->loggedIn = true;
            emit loggedIn();
        } else {
            d->loggedIn = false;
            emit loginFailed();
        }
    } else {
        d->loggedIn = false;
        emit loginFailed();
    }
}

bool OcsProvider::logout()
{
    if (!d->ready) {
        return false;
    }

    d->username.clear();
    d->password.clear();
    d->loggedIn = false;
    d->provider.saveCredentials(d->username, d->password);
    return true;
}

QString OcsProvider::username()
{
    return d->username;
}

QString OcsProvider::password()
{
    return d->password;
}

#include "ocsprovider.moc"
