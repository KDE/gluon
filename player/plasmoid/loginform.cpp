/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include <player/lib/serviceprovider.h>

#include <Plasma/LineEdit>
#include <Plasma/PushButton>
#include <Plasma/Label>
#include <Plasma/BusyWidget>
#include <KDE/KLineEdit>

#include <QtGui/QGraphicsLinearLayout>
#include <QtCore/QDebug>

LoginForm::LoginForm( QGraphicsItem* parent, Qt::WindowFlags wFlags )
    : Overlay( parent, wFlags )
    , m_usernameEdit( new Plasma::LineEdit( this ) )
    , m_passwordEdit( new Plasma::LineEdit( this ) )
    , m_loginButton( new Plasma::PushButton( this ) )
    , m_busyWidget( new Plasma::BusyWidget( this ) )
    , m_usernameLabel( new Plasma::Label( this ) )
{
    m_usernameEdit->nativeWidget()->setClickMessage( i18nc( "The name of the user", "Username" ) );
    m_passwordEdit->nativeWidget()->setClickMessage( i18n( "Password" ) );
    m_passwordEdit->nativeWidget()->setPasswordMode( true );
    m_loginButton->setIcon( KIcon( "network-connect" ) );
    m_loginButton->setText( i18n( "Login" ) );
    m_loginButton->setEnabled( false );

    m_busyWidget->hide();
    m_usernameLabel->setText( i18n( "Not Logged In" ) );

    QGraphicsLinearLayout* layout1 = new QGraphicsLinearLayout( m_contentLayout );
    layout1->addItem( m_busyWidget );
    layout1->addItem( m_usernameLabel );

    m_contentLayout->addItem( layout1 );
    m_contentLayout->addItem( m_usernameEdit );
    m_contentLayout->addItem( m_passwordEdit );
    m_contentLayout->addItem( m_loginButton );

    connect( m_loginButton, SIGNAL(clicked()), SLOT(doLogin()) );

    GluonPlayer::ServiceProvider *serviceProvider = GluonPlayer::ServiceProvider::instance();
    connect(serviceProvider, SIGNAL(providerInitialized()), SLOT(initDone()));
    connect(serviceProvider, SIGNAL(failedToInitialize()), SLOT(initFailed()));
    connect(serviceProvider, SIGNAL(loggedIn()), SLOT(loginDone()));
    connect(serviceProvider, SIGNAL(loginFailed()), SLOT(loginFailed()));

    initialize();
}

void LoginForm::initialize()
{
    GluonPlayer::ServiceProvider::instance()->init();
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
    if( m_usernameEdit->text().isEmpty() || m_passwordEdit->text().isEmpty() )
    {
        return;
    }

    m_loginButton->setEnabled( false );
    m_busyWidget->show();
    GluonPlayer::ServiceProvider::instance()->login(m_usernameEdit->text(), m_passwordEdit->text());
    connect(GluonPlayer::ServiceProvider::instance(), SIGNAL(loggedIn()), SLOT(loginDone()));
    m_usernameLabel->setText( i18n( "Logging in" ) );
}

void LoginForm::loginDone()
{
    m_busyWidget->hide();
    m_usernameLabel->setText(
        i18nc( "Logged in as <user name>", "Logged in as %1", GluonPlayer::ServiceProvider::instance()->username() ) );
    m_loginButton->setEnabled( true );
}

void LoginForm::loginFailed()
{
    m_busyWidget->hide();
    m_usernameLabel->setText( i18n( "Login Failed" ) );
    m_loginButton->setEnabled( true );
}

void LoginForm::loadCredentials()
{
    m_usernameEdit->setText( GluonPlayer::ServiceProvider::instance()->username() );
    m_passwordEdit->setText( GluonPlayer::ServiceProvider::instance()->password() );
}

#include "loginform.moc"
