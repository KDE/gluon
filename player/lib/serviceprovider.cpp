/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "serviceprovider.h"

#include "commentslistjob.h"
#include "commentuploadjob.h"
#include "gamedetaillistjob.h"
#include "gamedownloadjob.h"
#include "gameuploadjob.h"
#include "ratingjob.h"

#include <core/directoryprovider.h>

#include <attica/content.h>
#include <attica/listjob.h>
#include <attica/provider.h>
#include <attica/providermanager.h>

#include <QtCore/QDir>

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON( ServiceProvider )

class ServiceProvider::Private
{
    public:
        Private()
            : ready( false )
            , loggedIn( false )
        {
        }

        ~Private()
        {
        }

        bool ready;
        bool loggedIn;
        Attica::ProviderManager manager;
        Attica::Provider provider;
        QString username;
        QString password;
};


ServiceProvider::ServiceProvider( QObject* parent )
    : GluonCore::Singleton< GluonPlayer::ServiceProvider >( parent )
    , d( new Private )
{
    init();
}

ServiceProvider::~ServiceProvider()
{
    delete d;
}

bool ServiceProvider::isReady() const
{
    return d->ready;
}

void ServiceProvider::init()
{
    if( d->ready )
    {
        return;
    }
    connect( &d->manager, SIGNAL( defaultProvidersLoaded() ), SLOT( providersUpdated() ) );
    d->manager.loadDefaultProviders();
}

void ServiceProvider::providersUpdated()
{
    if( !d->manager.providers().isEmpty() )
    {
        d->provider = d->manager.providerByUrl( QUrl( "https://api.opendesktop.org/v1/" ) );
        if( !d->provider.isValid() )
        {
            emit initializeFailed();
        }
        else
        {
            d->ready = true;
            loadCredentials();
        }
    }
}

void ServiceProvider::loadCredentials()
{
    if( !d->ready )
    {
        return;
    }

    if( d->provider.hasCredentials() )
    {
        d->provider.loadCredentials( d->username, d->password );
    }

    emit initializeFinished();
}

CommentsListJob* ServiceProvider::fetchCommentList( const QString& id, int page, int pageSize )
{
    CommentsListJob* commentListJob = new CommentsListJob( &d->provider, id, page, pageSize );
    connect( this, SIGNAL( commentListFetchStarting() ), commentListJob, SIGNAL( commentListFetchStarting() ) );

    if( d->ready )
    {
        emit commentListFetchStarting();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), commentListJob, SIGNAL( commentListFetchStarting() ) );
    }

    return commentListJob;
}

CommentUploadJob* ServiceProvider::uploadComment( const QString& id, const QString& parentId,
        const QString& subject, const QString& message )
{
    return new CommentUploadJob( &d->provider, id, parentId, subject, message );
}

bool ServiceProvider::hasCredentials() const
{
    return d->provider.hasCredentials();
}

bool ServiceProvider::isLoggedIn() const
{
    return d->loggedIn;
}

bool ServiceProvider::login( const QString& username, const QString& password )
{
    if( d->loggedIn )
    {
        return false;
    }

    d->username = username;
    d->password = password;

    if( d->ready )
    {
        doLogin();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), SLOT( doLogin() ) );
    }
    return true;
}

void ServiceProvider::doLogin()
{
    Attica::PostJob* job = d->provider.checkLogin( d->username, d->password );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( checkLoginResult( Attica::BaseJob* ) ) );
    job->start();
}

void ServiceProvider::checkLoginResult( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = qobject_cast<Attica::PostJob*> ( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        if( d->provider.saveCredentials( d->username, d->password ) )
        {
            d->loggedIn = true;
            emit loginFinished();
        }
        else
        {
            d->loggedIn = false;
            emit loginFailed();
        }
    }
    else
    {
        d->loggedIn = false;
        emit loginFailed();
    }
}

bool ServiceProvider::logout()
{
    if( !d->loggedIn )
    {
        return false;
    }

    if( d->ready )
    {
        doLogout();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), SLOT( doLogout() ) );
    }

    return true;
}

void ServiceProvider::doLogout()
{
    d->username.clear();
    d->password.clear();
    d->loggedIn = false;
    d->provider.saveCredentials( d->username, d->password );
}

QString ServiceProvider::username() const
{
    return d->username;
}

QString ServiceProvider::password() const
{
    return d->password;
}

GameDetailListJob* ServiceProvider::fetchGames()
{
    return new GameDetailListJob( &d->provider );
}

GameDownloadJob* ServiceProvider::downloadGame( const QString& id )
{
    QString path( "gluon/games" );
    QDir destinationDir( GluonCore::DirectoryProvider::instance()->dataDirectory() );
    if( !destinationDir.exists( path ) )
    {
        destinationDir.mkpath( path );
    }
    destinationDir.cd( path );

    return new GameDownloadJob( &d->provider, id, destinationDir.path() );
}

GameUploadJob* ServiceProvider::uploadGame( const QString& id, const QString& path )
{
    return new GameUploadJob( &d->provider, id, path );
}

RatingJob* ServiceProvider::setRating( const QString& id, uint rate )
{
    return new RatingJob( &d->provider, id, rate );
}

#include "serviceprovider.moc"
