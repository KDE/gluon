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

#include <attica/provider.h>

#include <QDebug>

LoginForm::LoginForm( QWidget* parent, Qt::WindowFlags wFlags )
    : Overlay( parent, wFlags )
    , m_usernameLineEdit( new QLineEdit( this ) )
    , m_passwordLineEdit( new QLineEdit( this ) )
    , m_loginButton( new QPushButton( this ) )
    , m_busyWidget( new QProgressBar( this ) )
    , m_usernameLabel( new QLabel( this ) )
    , m_passwordLabel( new QLabel( this ) )
    , m_rememberMeCheckBox( new QCheckBox( this ) )
{
    m_usernameLabel->setText( tr( "Username" ) );
    m_passwordLabel->setText( tr( "Password" ) );
    m_loginButton->setIcon( QIcon( "network-connect" ) );
    m_loginButton->setText( tr( "Login" ) );
    m_loginButton->setEnabled( false );
    m_passwordLineEdit->setEchoMode( QLineEdit::Password );

    m_busyWidget->hide();

    QGridLayout* layout1 = static_cast<QGridLayout*>( layout() );
    layout1->addWidget( m_usernameLabel, 0, 0 );
    layout1->addWidget( m_passwordLabel, 0, 1 );
    layout1->addWidget( m_usernameLineEdit, 1, 0 );
    layout1->addWidget( m_passwordLineEdit, 1, 1 );
    layout1->addWidget( m_loginButton, 2, 0 );
    layout1->addWidget( m_rememberMeCheckBox, 2, 1 );
    // layout1->addWidget( m_busyWidget );

    // m_contentLayout->addItem( layout1 );
    // m_contentLayout->addItem( m_usernameLineEdit );
    // m_contentLayout->addItem( m_passwordLineEdit );
    // m_contentLayout->addItem( m_loginButton );

    connect( m_loginButton, SIGNAL( clicked() ), SLOT( doLogin() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( initialized() ), SLOT( initDone() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( initFailed() ), SLOT( initFailed() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( loggedIn() ), SLOT( loginDone() ) );
    connect( GluonPlayer::Authentication::instance(), SIGNAL( loginFailed() ), SLOT( loginFailed() ) );

    initialize();
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
    qDebug() << "Initialization failed";
}

void LoginForm::doLogin()
{
    if( m_usernameLineEdit->text().isEmpty() )
    {
        qDebug() << "Empty username";
        return;
    }

    if( m_passwordLineEdit->text().isEmpty() )
    {
        qDebug() << "Empty password";
        return;
    }

    m_loginButton->setEnabled( false );
    m_busyWidget->show();
    GluonPlayer::Authentication::instance()->login( m_usernameLineEdit->text(), m_passwordLineEdit->text() );
    // Note: the login result should be checked
    m_resultLabel->setText( tr( "Logging in" ) );
}

void LoginForm::loginDone()
{
    m_busyWidget->hide();
    m_resultLabel->setText( tr( QString( "Logged in as %1" ).arg( GluonPlayer::Authentication::instance()->username() ).toAscii() ) );
    m_loginButton->setEnabled( true );
}

void LoginForm::loginFailed()
{
    m_busyWidget->hide();
    m_resultLabel->setText( tr( "Login Failed" ) );
    m_loginButton->setEnabled( true );
}

void LoginForm::loadCredentials()
{
    m_usernameLineEdit->setText( GluonPlayer::Authentication::instance()->username() );
    m_passwordLineEdit->setText( GluonPlayer::Authentication::instance()->password() );
}

#include "loginform.moc"
