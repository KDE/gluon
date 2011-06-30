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

#include "serviceprovider.h"

#include "comment.h"
#include "gamedetail.h"
#include "gamedownload.h"
#include "gameupload.h"
#include "rating.h"

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
    : Singleton< GluonPlayer::ServiceProvider >( parent )
    , d( new Private() )
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
            emit failedToInitialize();
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

    emit providerInitialized();
}

Comment* ServiceProvider::fetchComments( const QString& id, int page, int pageSize )
{
    Comment* commentsProvider = new Comment( &d->provider, id, page, pageSize );

    if( d->ready )
    {
        commentsProvider->fetchComments();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), commentsProvider, SLOT( fetchComments() ) );
    }

    return commentsProvider;
}

Comment* ServiceProvider::uploadComment( const QString& id, const QString& parentId,
                                         const QString& subject, const QString& message )
{
    Comment* commentsProvider = new Comment( &d->provider, id, parentId, subject, message );

    if( d->ready && d->loggedIn )
    {
        commentsProvider->uploadComments();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), commentsProvider, SLOT( uploadComments() ) );
    }

    return commentsProvider;
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
            emit loggedIn();
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

GameDetail* ServiceProvider::fetchGames()
{
    GameDetail* gameDetail = new GameDetail( &d->provider );

    if( d->ready )
    {
        gameDetail->fetchGameList();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), gameDetail, SLOT( fetchGameList() ) );
    }

    return gameDetail;
}

GameDownload* ServiceProvider::downloadGame( const QString& id )
{
    QString path( "gluon/games" );
    QDir destinationDir( GluonCore::DirectoryProvider::instance()->dataDirectory() );
    if( !destinationDir.exists( path ) )
    {
        destinationDir.mkpath( path );
    }
    destinationDir.cd( path );

    GameDownload* gameDownload = new GameDownload( &d->provider, id, destinationDir.path() );

    if( d->ready )
    {
        gameDownload->startDownload();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), gameDownload, SLOT( startDownload() ) );
    }

    return gameDownload;
}

GameUpload* ServiceProvider::uploadGame( const QString& id, const QString& path )
{
    GameUpload* gameUpload = new GameUpload( &d->provider, id, path );

    if( d->ready )
    {
        gameUpload->startUpload();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), gameUpload, SLOT( startUpload() ) );
    }

    return gameUpload;
}

Rating* ServiceProvider::setRating( const QString& id, uint rate )
{
    Rating* rating = new Rating( &d->provider, id, rate );

    if( d->ready )
    {
        rating->startRatingUpload();
    }
    else
    {
        connect( this, SIGNAL( providerInitialized() ), rating, SLOT( startRatingUpload() ) );
    }

    return rating;
}

#include "serviceprovider.moc"
