/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "authentication.h"
#include "atticamanager.h"

#include <core/singleton.h>

#include <QtCore/QDebug>

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON( Authentication )

class Authentication::Private
{
    public:
    Private()
        : m_initialized( false )
        , m_loggedIn( false )
    {
    }

    bool m_initialized;
    bool m_loggedIn;
    QString m_username;
    QString m_password;
    Attica::PostJob* m_registerJob;
    Attica::PostJob* m_checkLoginJob;
    Attica::PostJob* m_checkLogoutJob;
};

Authentication::Authentication()
    : d( new Private() )
{
    init();
}

Authentication::~Authentication()
{
}

void Authentication::init()
{
    if( !AtticaManager::instance()->isProviderValid() )
    {
        connect( AtticaManager::instance(), SIGNAL( gotProvider() ), SLOT( finishInit() ) );
        connect( AtticaManager::instance(), SIGNAL( failedToFetchProvider() ), SIGNAL( initFailed() ) );
    }
}

bool Authentication::isInitialized()
{
    return d->m_initialized;
}

QString Authentication::username()
{
    return d->m_username;
}

QString Authentication::password()
{
    return d->m_password;
}

void Authentication::onRegisterClicked( const QString& username, const QString& password, const QString& mail,
                                        const QString& firstName, const QString& lastName )
{
    // here we assume that all data has been checked in onRegisterDataChanged()

    if( AtticaManager::instance()->isProviderValid() )
    {
        d->m_registerJob = AtticaManager::instance()->provider().registerAccount( username, password, mail, firstName, lastName );
        connect( d->m_registerJob, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( onRegisterAccountFinished( Attica::BaseJob* ) ) );
        d->m_registerJob->start();
    }
}

bool Authentication::login( const QString& username, const QString& password )
{
    d->m_username = username;
    d->m_password = password;

    if( AtticaManager::instance()->isProviderValid() )
    {
        d->m_checkLoginJob = AtticaManager::instance()->provider().checkLogin( d->m_username, d->m_password );
        connect( d->m_checkLoginJob, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( checkLoginResult( Attica::BaseJob* ) ) );
        d->m_checkLoginJob->start();
        return true;
    }

    return false;
}

bool Authentication::logout( )
{
    d->m_username.clear();
    d->m_password.clear();

    if( AtticaManager::instance()->isProviderValid() )
    {
        if( AtticaManager::instance()->provider().saveCredentials( d->m_username, d->m_password ) )
        {
            d->m_loggedIn = false;
            emit loggedOut();
            return true;
        }
        else
        {
            emit logoutFailed();
            return false;
        }
    }

    return false;
}

bool Authentication::isLoggedIn()
{
    return d->m_loggedIn;
}

bool Authentication::hasCredentials()
{
    return AtticaManager::instance()->provider().hasCredentials();
}

void Authentication::finishInit()
{
    AtticaManager::instance()->provider().loadCredentials( d->m_username, d->m_password );
    d->m_initialized = true;
    emit initialized();
}

void Authentication::showRegisterError( const Attica::Metadata& metadata )
{
    if( metadata.error() == Attica::Metadata::NetworkError )
    {
        emit registrationFailed();
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

void Authentication::onRegisterAccountFinished( Attica::BaseJob* job )
{
    Attica::PostJob* postJob = static_cast<Attica::PostJob*>( job );

    if( postJob->metadata().error() == Attica::Metadata::NoError )
    {
        AtticaManager::instance()->provider().saveCredentials( d->m_username, d->m_password );
        emit registered();
    }
    else
    {
        // Note: It is worth to invoke this error status later
        // qDebug() << "register error:" << postJob->metadata().error() << "statusCode:" << postJob->metadata().statusCode();
        showRegisterError( postJob->metadata() );
    }
}

void Authentication::checkLoginResult( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = qobject_cast<Attica::PostJob*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        if( AtticaManager::instance()->provider().saveCredentials( d->m_username, d->m_password ) )
        {
            d->m_loggedIn = true;
            emit loggedIn();
        }
        else
        {
            d->m_loggedIn = false;
            emit loginSaveCredentialsFailed();
        }
    }
    else
    {
        d->m_loggedIn = false;
        emit loginFailed();
    }
}

#include "authentication.moc"
