/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "serviceprovider.h"

#include "commentslistjob.h"
#include "commentuploadjob.h"
#include "gamedetaillistjob.h"
#include "gamedownloadjob.h"
#include "gameuploadjob.h"
#include "ratingjob.h"
#include "addgamejob.h"
#include "categorylistjob.h"
#include "editgamejob.h"
#include "licensejob.h"
#include "gamedetailsjob.h"
#include "personselfjob.h"

#include <core/directoryprovider.h>

#include <attica/content.h>
#include <attica/listjob.h>
#include <attica/provider.h>
#include <attica/providermanager.h>

#include <QtCore/QDir>
#include <QtCore/QDebug>

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

    connect( &d->manager, SIGNAL(defaultProvidersLoaded()), SLOT(providersUpdated()) );
    d->manager.addProviderFile(QUrl("http://www.gamingfreedom.org/providers.xml"));
}

void ServiceProvider::providersUpdated()
{
    if( !d->manager.providers().isEmpty() )
    {
        d->provider = d->manager.providerByUrl( QUrl( "http://www.gamingfreedom.org/v1/" ) );

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
    else
    {
        emit initializeFailed();
    }
}

void ServiceProvider::loadCredentials()
{
    if( !d->ready )
    {
        return;
    }

    if( !d->provider.isValid() )
    {
        qDebug() << "PROVIDER NOT VALID";
        emit initializeFailed();
        return;
    }

    if( d->provider.hasCredentials() )
    {
        d->provider.loadCredentials( d->username, d->password );
    }

    emit initializationFinished();
}

CommentsListJob* ServiceProvider::fetchCommentList( const QString& id, int page, int pageSize )
{
    return new CommentsListJob( &d->provider, id, page, pageSize );
}

CommentUploadJob* ServiceProvider::uploadComment( const QString& id, const QString& parentId,
        const QString& subject, const QString& message )
{
    return new CommentUploadJob( &d->provider, id, parentId, subject, message );
}

bool ServiceProvider::hasCredentials() const
{
    if( d->provider.isValid() )
    {
        return d->provider.hasCredentials();
    }
    else
    {
        return false;
    }
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
        connect( this, SIGNAL(initializationFinished()), SLOT(doLogin()) );
    }

    return true;
}

void ServiceProvider::doLogin()
{
    Attica::PostJob* job = d->provider.checkLogin( d->username, d->password );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(checkLoginResult(Attica::BaseJob*)) );
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
            const QString errMessage = "Error saving credentials";
            qDebug() << errMessage;
            d->loggedIn = false;
            emit loginFailed(errMessage);
        }
    }
    else
    {
        qDebug() << "Login error " << job->metadata().error() << job->metadata().message();
        d->loggedIn = false;
        emit loginFailed(job->metadata().message());
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
        connect( this, SIGNAL(initializationFinished()), SLOT(doLogout()) );
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

void ServiceProvider::registerAccount( const QString& username, const QString& password, const QString& mail,
                                        const QString& firstName, const QString& lastName )
{
    if( isReady() )
    {
        Attica::PostJob *registerJob = d->provider.registerAccount( username, password, mail, firstName, lastName );
        connect( registerJob, SIGNAL(finished(Attica::BaseJob*)), SLOT(onRegisterAccountFinished(Attica::BaseJob*)) );
        registerJob->start();
    }
}

void ServiceProvider::showRegisterError( const Attica::Metadata& metadata )
{
    if( metadata.error() == Attica::Metadata::NetworkError )
    {
        emit registrationFailed(999);
    }
    else
    {
        /*
        # 100 - successful / valid account
        # 101 - please specify all mandatory fields
        # 102 - please specify a valid password
        # 103 - please specify a valid login
        # 104 - login already exists
        # 105 - email already taken
        */
        // TODO: Looks like more correct place for this stuff is in libattica,
        // for example metadata().statusString() or smth like that.
        // So here will be only showRegisterHint("dialog-close", statusString);
        // no switch.
        // QWidget* widgetToHighlight = 0;
        
        emit registrationFailed(metadata.statusCode());
        
        QString hint;
        switch( metadata.statusCode() )
        {
            case 100:
                hint = tr( "Registration succeeded." );
                break;
            case 101:
                hint = tr( "Failed to register new account: please specify all mandatory fields." );
            case 102:
                hint = tr( "Failed to register new account: invalid password." );
                break;
            case 103:
                hint = tr( "Failed to register new account: invalid username." );
                break;
            case 104:
                hint = tr( "Failed to register new account: the requested username is already taken." );
                break;
            case 105:
                hint = tr( "Failed to register new account: the specified email address is already taken." );
                break;
            case 106:
                hint = tr( "Failed to register new account: the specified email address is invalid." );
            default:
                hint = tr( "Failed to register new account." );
                break;
        }
        qDebug() << hint;
    }
}

void ServiceProvider::onRegisterAccountFinished( Attica::BaseJob* job )
{
    Attica::PostJob* postJob = static_cast<Attica::PostJob*>( job );

    if( postJob->metadata().error() == Attica::Metadata::NoError )
    {
        d->provider.saveCredentials( d->username, d->password );
        emit registrationFinished();
    }
    else
    {
        // Note: It is worth to invoke this error status later
        // qDebug() << "register error:" << postJob->metadata().error() << "statusCode:" << postJob->metadata().statusCode();
        showRegisterError( postJob->metadata() );
    }
}

PersonSelfJob* ServiceProvider::personSelf()
{
	return new PersonSelfJob( &d->provider );
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

AddGameJob* ServiceProvider::addGame( const QString& gameName, const QString& categoryId )
{
    return new AddGameJob( &d->provider, categoryId, gameName );
}

CategoryListJob* ServiceProvider::fetchCategories()
{
    return new CategoryListJob( &d->provider );
}

EditGameJob* ServiceProvider::editGame( const QString& id )
{
    return new EditGameJob( &d->provider, id );
}

LicenseJob* ServiceProvider::fetchLicenses()
{
    return new LicenseJob( &d->provider );
}

GameDetailsJob* ServiceProvider::fetchOneGame( const QString& id )
{
    return new GameDetailsJob( &d->provider, id );
}

#include "serviceprovider.moc"
