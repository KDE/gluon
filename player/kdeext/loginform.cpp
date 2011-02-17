/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "loginform.h"

#include <player/lib/authentication.h>

#include <KDE/KLocale>
#include <KDE/KLocalizedString>
#include <KDE/KDebug>

#include <attica/provider.h>

#include <QtGui/QGridLayout>

LoginForm::LoginForm( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_usernameEdit( new KLineEdit( this ) )
    , m_passwordEdit( new KLineEdit( this ) )
    , m_loginButton( new KPushButton( this ) )
    , m_usernameLabel( new QLabel( this ) )
    , m_passwordLabel( new QLabel( this ) )
    , m_usernameFeedbackLabel( new QLabel( this ) )
    , m_rememberMeCheckBox( new QCheckBox( this ) )
    , m_loggedIn(false)
{
    m_usernameLabel->setText( i18n( "Username" ) );
    m_passwordLabel->setText( i18n( "Password" ) );
    m_loginButton->setIcon( KIcon( "network-connect" ) );
    m_loginButton->setText( i18n( "Login" ) );
    m_loginButton->setEnabled( true );

    m_passwordEdit->setEchoMode( QLineEdit::Password );
    m_passwordEdit->setPasswordMode( true );

    m_usernameFeedbackLabel->setText( i18n( "Not Logged In" ) );

    QGridLayout* m_contentLayout = new QGridLayout();

    m_contentLayout->addWidget( m_usernameLabel, 0, 0, 1, 2 );
    m_contentLayout->addWidget( m_usernameEdit, 1, 0, 1, 2 );
    m_contentLayout->addWidget( m_passwordLabel, 2, 0, 1, 2 );
    m_contentLayout->addWidget( m_passwordEdit, 3, 0, 1, 2 );
    m_contentLayout->addWidget( m_loginButton, 4, 0 );
    m_contentLayout->addWidget( m_rememberMeCheckBox, 4, 1 );
    m_contentLayout->addWidget( m_usernameFeedbackLabel, 5, 0, 1, 2 );
    setLayout(m_contentLayout);

    connect( m_loginButton, SIGNAL( clicked() ), SLOT( doLogin() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( initialized() ), SLOT( initDone() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( initFailed() ), SLOT( initFailed() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( loggedIn() ), SLOT( loginDone() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( loggedOut() ), SLOT( logoutDone() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( loginFailed() ), SLOT( loginFailed() ) );

    initialize();
}

LoginForm::~LoginForm()
{
}

void LoginForm::initialize()
{
    GluonPlayer::Authentication::instance()->init();
}

void LoginForm::initDone()
{
    loadCredentials();
    m_loginButton->setEnabled( true );
}

void LoginForm::initFailed()
{
   kDebug() << "Initialization failed";
}

void LoginForm::doLogin()
{
    if( m_loggedIn ) {
        doLogout();
        return;
    }

    if( m_usernameEdit->text().isEmpty() || m_passwordEdit->text().isEmpty())
    {
        return;
    }

    m_loginButton->setEnabled( false );
    m_usernameFeedbackLabel->setText( i18n( "Logging in" ) );
    GluonPlayer::Authentication::instance()->login( m_usernameEdit->text(), m_passwordEdit->text() );
    // Note: the login result should be checked
}

void LoginForm::doLogout()
{
    if( m_loggedIn == false)
        return;

    m_loginButton->setEnabled( false );
    m_usernameFeedbackLabel->setText( i18n( "Logging out" ) );
    GluonPlayer::Authentication::instance()->logout( );
    // Note: the login result should be checked
}

void LoginForm::loginDone()
{
    m_usernameFeedbackLabel->setText(
        i18nc( "Logged in as <user name>", "Logged in as %1", GluonPlayer::Authentication::instance()->username() ) );
    m_loginButton->setEnabled( true );
    m_loginButton->setText( i18n( "Logout" ) );
    m_loggedIn = true;
    m_usernameEdit->setVisible( false );
    m_passwordEdit->setVisible( false );
    m_rememberMeCheckBox->setVisible( false );
}

void LoginForm::logoutDone()
{
    m_usernameFeedbackLabel->setText( i18n( "Not Logged In" ) );
    m_loginButton->setEnabled( true );
    m_loginButton->setText( i18n( "Login" ) );
    m_loggedIn = false;
    m_usernameEdit->setText("");
    m_usernameEdit->setVisible( true );
    m_passwordEdit->setText("");
    m_passwordEdit->setVisible( true );
    m_rememberMeCheckBox->setVisible( true );
}

void LoginForm::loginFailed()
{
    m_usernameFeedbackLabel->setText( i18n( "Login Failed" ) );
    m_loginButton->setEnabled( true );
}

void LoginForm::loadCredentials()
{
    m_usernameEdit->setText( GluonPlayer::Authentication::instance()->username() );
    m_passwordEdit->setText( GluonPlayer::Authentication::instance()->password() );
}
