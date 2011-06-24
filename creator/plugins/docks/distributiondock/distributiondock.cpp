/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "distributiondock.h"
#include "ui_distributiondock.h"

#include <engine/game.h>

#include <player/lib/ocsprovider.h>

#include <KDE/KLocalizedString>

#include <QtGui/QPushButton>

using namespace GluonCreator;

class DistributionDock::DistributionDockPrivate
{
    public:
        DistributionDockPrivate() { }

        QString currentGameId;
        QWidget widget;
        Ui::DistributionDock ui;
};

DistributionDock::DistributionDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : d( new DistributionDockPrivate() )
{
    setObjectName( "Distribution Dock" );

    d->ui.setupUi( &d->widget );

    connect( GluonEngine::Game::instance(), SIGNAL( currentProjectChanged( GluonEngine::GameProject* ) ),
             SLOT( currentProjectChanged( GluonEngine::GameProject* ) ) );
    connect( GluonPlayer::OcsProvider::instance(), SIGNAL( loggedIn() ), SLOT( loginSuccessful() ) );
    connect( GluonPlayer::OcsProvider::instance(), SIGNAL( loginFailed() ), SLOT( loginFailed() ) );
    connect( d->ui.loginButton, SIGNAL( clicked() ), SLOT( doLogin() ) );

    setWidget( &d->widget );
}

DistributionDock::~DistributionDock()
{
    delete d;
}

void DistributionDock::currentProjectChanged( GluonEngine::GameProject* gameProject )
{
    QString id = gameProject->property( "id" ).toString();
}

void DistributionDock::doLogin()
{
    d->ui.loginButton->setEnabled( false );
    d->ui.loginButton->setText( i18n( "Logging in" ) );
    GluonPlayer::OcsProvider::instance()->login( d->ui.usernameEdit->text(), d->ui.passwordEdit->text() );
}

void DistributionDock::loginSuccessful()
{
    d->ui.loginButton->setText( i18n( "Logged In" ) );
}

void DistributionDock::loginFailed()
{
    d->ui.loginButton->setEnabled( true );
}

#include "distributiondock.moc"
