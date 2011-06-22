/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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
#include "ocsgamedetailsprovider.h"
#include "ocsgamedownloadprovider.h"
#include "ocsgameuploadprovider.h"
#include "ocsratingprovider.h"

#include <core/directoryprovider.h>

#include <attica/content.h>
#include <attica/listjob.h>
#include <attica/provider.h>
#include <attica/providermanager.h>

#include <QtCore/QDir>

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON (OcsProvider)

class OcsProvider::Private
{
public:
    Private() : ready (false), loggedIn(false) {
    }

    bool ready;
    bool loggedIn;
    Attica::ProviderManager manager;
    Attica::Provider provider;
    QString username;
    QString password;
};


OcsProvider::OcsProvider( QObject* parent )
    : Singleton< GluonPlayer::OcsProvider >( parent ), d (new Private())
{
    init();
}

OcsProvider::~OcsProvider()
{
    delete d;
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
    OcsCommentsProvider *commentsProvider = new OcsCommentsProvider(&d->provider, id, page, pageSize);

    if (d->ready) {
        commentsProvider->fetchComments();
    } else {
        connect(this, SIGNAL(providerInitialized()), commentsProvider, SLOT(fetchComments()));
    }

    return commentsProvider;
}

OcsCommentsProvider* OcsProvider::uploadComment (const QString& id, const QString& parentId,
        const QString& subject, const QString& message)
{
    OcsCommentsProvider *commentsProvider = new OcsCommentsProvider(&d->provider, id, parentId, subject, message);

    if (d->ready && d->loggedIn) {
        commentsProvider->uploadComments();
    } else {
        connect(this, SIGNAL(providerInitialized()), commentsProvider, SLOT(uploadComments()));
    }

    return commentsProvider;
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
    if (d->loggedIn) {
        return false;
    }

    d->username = username;
    d->password = password;

    if (d->ready) {
        doLogin();
    } else {
        connect(this, SIGNAL(providerInitialized()), SLOT(doLogin()));
    }
    return true;
}

void OcsProvider::doLogin()
{
    Attica::PostJob* job = d->provider.checkLogin (d->username, d->password);
    connect (job, SIGNAL (finished (Attica::BaseJob*)), SLOT (checkLoginResult (Attica::BaseJob*)));
    job->start();
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
    if (!d->loggedIn) {
        return false;
    }

    if (d->ready) {
        doLogout();
    } else {
        connect(this, SIGNAL(providerInitialized()), SLOT(doLogout()));
    }

    return true;
}

void OcsProvider::doLogout()
{
    d->username.clear();
    d->password.clear();
    d->loggedIn = false;
    d->provider.saveCredentials(d->username, d->password);
}

QString OcsProvider::username()
{
    return d->username;
}

QString OcsProvider::password()
{
    return d->password;
}

OcsGameDetailsProvider* OcsProvider::fetchGames()
{
    OcsGameDetailsProvider *gameDetailsProvider = new OcsGameDetailsProvider(&d->provider);

    if (d->ready) {
        gameDetailsProvider->fetchGameList();
    } else {
        connect(this, SIGNAL(providerInitialized()), gameDetailsProvider, SLOT(fetchGameList()));
    }

    return gameDetailsProvider;
}

OcsGameDownloadProvider* OcsProvider::downloadGame (const QString& id)
{
    QString path("gluon/games");
    QDir destinationDir(GluonCore::DirectoryProvider::instance()->dataDirectory());
    if (!destinationDir.exists(path)) {
        destinationDir.mkpath(path);
    }
    destinationDir.cd(path);

    OcsGameDownloadProvider *gameDownloadProvider = new OcsGameDownloadProvider(&d->provider, id,
                                                                                destinationDir.path());

    if (d->ready) {
        gameDownloadProvider->startDownload();
    } else {
        connect(this, SIGNAL(providerInitialized()), gameDownloadProvider, SLOT(startDownload()));
    }

    return gameDownloadProvider;
}

OcsGameUploadProvider* OcsProvider::uploadGame (const QString& id, const QString& path)
{
    OcsGameUploadProvider *gameUploadProvider = new OcsGameUploadProvider(&d->provider, id, path);

    if (d->ready) {
        gameUploadProvider->startUpload();
    } else {
        connect(this, SIGNAL(providerInitialized()), gameUploadProvider, SLOT(startUpload()));
    }

    return gameUploadProvider;
}

OcsRatingProvider* OcsProvider::setRating (const QString& id, uint rating)
{
    OcsRatingProvider *ratingProvider = new OcsRatingProvider(&d->provider, id, rating);

    if (d->ready) {
        ratingProvider->startRatingUpload();
    } else {
        connect(this, SIGNAL(providerInitialized()), ratingProvider, SLOT(startRatingUpload()));
    }

    return ratingProvider;
}

#include "ocsprovider.moc"
