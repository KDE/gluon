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
#include <player/lib/ocsnewgameprovider.h>

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
             SLOT( updateUiFromGameProject( GluonEngine::GameProject* ) ) );
    connect( GluonPlayer::OcsProvider::instance(), SIGNAL( loggedIn() ), SLOT( loginSuccessful() ) );
    connect( GluonPlayer::OcsProvider::instance(), SIGNAL( loginFailed() ), SLOT( loginFailed() ) );
    connect( d->ui.loginButton, SIGNAL( clicked() ), SLOT( doLogin() ) );
    connect( d->ui.createUpdateButton, SIGNAL( clicked( bool ) ), SLOT( createOrUpdateGame() ) );

    setWidget( &d->widget );
}

DistributionDock::~DistributionDock()
{
    delete d;
}

void DistributionDock::updateUiFromGameProject( GluonEngine::GameProject* gameProject )
{
    QString id = gameProject->property( "id" ).toString();

    d->ui.idEdit->setText( id );

    if( !id.isEmpty() )
    {
        d->ui.createUpdateButton->setText( i18n( "Update" ) );
    }
    else
    {
        d->ui.createUpdateButton->setText( i18n( "Create" ) );
    }
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
    d->ui.detailsTab->setEnabled( true );
}

void DistributionDock::loginFailed()
{
    d->ui.loginButton->setEnabled( true );
}

void DistributionDock::createOrUpdateGame()
{
    if( d->ui.idEdit->text().isEmpty() )
    {
        GluonPlayer::OcsNewGameProvider* newGameProvider = GluonPlayer::OcsProvider::instance()->addNewGame(
                    d->ui.gameNameEdit->text() );
        connect( newGameProvider, SIGNAL( finished( QString ) ), SLOT( newGameUploadFinished( QString ) ) );
        connect( newGameProvider, SIGNAL( failed() ), SLOT( newGameUploadFailed() ) );
        d->ui.createUpdateButton->setText( i18n( "Uploading" ) );
        d->ui.createUpdateButton->setEnabled( false );
    }
    else
    {

    }
}

void DistributionDock::newGameUploadFinished( const QString& id )
{
    d->ui.idEdit->setText( id );
    GluonEngine::Game::instance()->gameProject()->setProperty( "id", id );
    d->ui.createUpdateButton->setEnabled( true );
    updateUiFromGameProject( GluonEngine::Game::instance()->gameProject() );
}

void DistributionDock::newGameUploadFailed()
{
    d->ui.createUpdateButton->setText( i18n("Create") );
    d->ui.createUpdateButton->setEnabled( true );
}

#include "distributiondock.moc"
