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
#include <player/lib/ocscategoryprovider.h>

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
        QStringList categoryIds;
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

    updateCategories();
    loadCredentials();

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

    if( id.isEmpty() )
    {
        switchToCreateMode();
    }
    else
    {
        switchToUpdateMode();
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
    d->ui.gameTab->setEnabled( true );
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
                    d->ui.gameNameEdit->text(), d->categoryIds.at( d->ui.categoryList->currentIndex() ) );
        connect( newGameProvider, SIGNAL( finished( QString ) ), SLOT( newGameUploadFinished( QString ) ) );
        connect( newGameProvider, SIGNAL( failed() ), SLOT( newGameUploadFailed() ) );
        d->ui.createUpdateButton->setText( i18n( "Uploading" ) );
        d->ui.createUpdateButton->setEnabled( false );
    }
    else
    {
        /*TODO
        Category
        Name
        Version
        Content files+
        Homepage+
        Screenshots1,2,3
        Desc
        Changelog
        Accept donations
        License
        Ensure no copyright violation
        */
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
    switchToCreateMode();
    d->ui.createUpdateButton->setEnabled( true );
}

void DistributionDock::updateCategories()
{
    GluonPlayer::OcsCategoryProvider* provider = GluonPlayer::OcsProvider::instance()->fetchCategories();

    connect( provider, SIGNAL( categoriesFetched( QList<GluonPlayer::OcsCategory*> ) ),
             SLOT( categoriesFetched( QList<GluonPlayer::OcsCategory*> ) ) );
}

void DistributionDock::categoriesFetched( QList <GluonPlayer::OcsCategory*> categories )
{
    d->ui.categoryList->clear();
    d->categoryIds.clear();

    foreach( GluonPlayer::OcsCategory * category, categories )
    {
        QString categoryString = category->categoryName();

        /*Maybe we should just store some IDs in a settings file?
        Or if we care we're gonna prefix each categ with Gluon, thats fine*/
        if( categoryString.startsWith( "Gluon", Qt::CaseInsensitive ) )
        {
            d->categoryIds.append( category->id() );
            d->ui.categoryList->addItem( categoryString );
        }
    }
}

void DistributionDock::loadCredentials()
{
    GluonPlayer::OcsProvider* provider = GluonPlayer::OcsProvider::instance();

    if( provider->hasCredentials() )
    {
        d->ui.usernameEdit->setText( provider->username() );
        d->ui.passwordEdit->setText( provider->password() );
    }
    else
    {
        connect( provider, SIGNAL( providerInitialized() ), SLOT( loadCredentials() ) );
    }
}

void DistributionDock::switchToCreateMode()
{
    d->ui.createUpdateButton->setText( i18n( "Create" ) );
    d->ui.detailsGroupBox->setEnabled( false );
}

void DistributionDock::switchToUpdateMode()
{
    d->ui.createUpdateButton->setText( i18n( "Update" ) );
    d->ui.detailsGroupBox->setEnabled( true );
}


#include "distributiondock.moc"
