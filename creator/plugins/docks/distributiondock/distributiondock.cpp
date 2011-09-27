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

#include <player/lib/serviceprovider.h>
#include <player/lib/addgamejob.h>
#include <player/lib/categorylistjob.h>
#include <player/lib/editgamejob.h>
#include <player/lib/gamedetaillistjob.h>
#include <player/lib/licensejob.h>
#include <player/lib/gamedetailsjob.h>

#include <KDE/KLocalizedString>

#include <QtGui/QPushButton>
#include <QtCore/QStateMachine>
#include <QtCore/QHistoryState>

using namespace GluonCreator;

class DistributionDock::DistributionDockPrivate
{
    public:
        DistributionDockPrivate()
        {
            editGameJob = 0;
        }

        QString currentGameId;
        QWidget widget;
        Ui::DistributionDock ui;
        QStringList categoryIds;
        GluonPlayer::EditGameJob* editGameJob;
        QStateMachine machine;
        QStringList licenseIds;

        QState* loggedOutState;
        QState* loggingInState;
        QState* loggedInState;
        QState* fetchingState;
        QState* editingState;
        QState* createState;
        QState* updateState;
        QState* uploadingState;
        QHistoryState* stateBeforeUploading;
        QState* uploadFinishedState;
};

DistributionDock::DistributionDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QDockWidget( title, parent, flags ), d( new DistributionDockPrivate() )
{
    setObjectName( "Distribution Dock" );

    d->ui.setupUi( &d->widget );

    initGuiStates();

    updateCategories();
    updateLicenses();
    loadCredentials();

    setWidget( &d->widget );
}

DistributionDock::~DistributionDock()
{
    delete d;
}

void DistributionDock::updateUiFromGameProject()
{
    if( !GluonEngine::Game::instance()->gameProject() )
        return;

    QString id = GluonEngine::Game::instance()->gameProject()->property( "id" ).toString();
    d->ui.idEdit->setText( id );

    if( id.isEmpty() )
    {
        emit switchToCreateMode();
    }
    else
    {
        GluonPlayer::GameDetailsJob* gameDetailsJob = GluonPlayer::ServiceProvider::instance()->fetchOneGame( id );
        connect( gameDetailsJob, SIGNAL( succeeded() ), SLOT( gameDetailsFetched() ) ) ;
        gameDetailsJob->start();
    }
}

void DistributionDock::doLogin()
{
    GluonPlayer::ServiceProvider::instance()->login( d->ui.usernameEdit->text(), d->ui.passwordEdit->text() );
}

void DistributionDock::createOrUpdateGame()
{
    if( d->ui.idEdit->text().isEmpty() )
    {
        GluonPlayer::AddGameJob* addGameJob = GluonPlayer::ServiceProvider::instance()->addGame(
                    d->ui.gameNameEdit->text(), d->categoryIds.at( d->ui.categoryList->currentIndex() ) );
        connect( addGameJob, SIGNAL( succeeded() ), SLOT( newGameUploadFinished() ) );
        connect( addGameJob, SIGNAL( failed() ), SLOT( newGameUploadFailed() ) );
        addGameJob->start();
    }
    else
    {
        d->editGameJob = GluonPlayer::ServiceProvider::instance()->editGame(
                                  d->ui.idEdit->text() );
        connect( d->editGameJob, SIGNAL( succeeded() ), SLOT( editGameFinished() ) );
        connect( d->editGameJob, SIGNAL( failed() ), SLOT( editGameFailed() ) );

        d->editGameJob->setName( d->ui.gameNameEdit->text() );
        d->editGameJob->setCategory( d->categoryIds.at( d->ui.categoryList->currentIndex() ) );
        d->editGameJob->setChangelog( d->ui.changelogEdit->toPlainText() );
        d->editGameJob->setDescription( d->ui.descriptionEdit->toPlainText() );
        d->editGameJob->setHomepage( d->ui.homepageEdit->text() );
        d->editGameJob->setVersion( d->ui.versionEdit->text() );
        d->editGameJob->setLicense( d->licenseIds.at( d->ui.licenseList->currentIndex() ) );
        d->editGameJob->start();
    }
}

void DistributionDock::newGameUploadFinished( )
{
    QString id = qobject_cast<GluonPlayer::AddGameJob*>( sender() )->data().toString();
    d->ui.idEdit->setText( id );
    GluonEngine::Game::instance()->gameProject()->setProperty( "id", id );
    updateUiFromGameProject();
    emit gameUploadFinished();
}

void DistributionDock::newGameUploadFailed()
{
    emit gameUploadFinished();  //TODO: Separate for failed
}

void DistributionDock::editGameFinished( )
{
    emit gameUploadFinished();
}

void DistributionDock::editGameFailed( )
{
    emit gameUploadFinished();  //TODO: Separate for failed
}

void DistributionDock::updateCategories()
{
    GluonPlayer::CategoryListJob* categoryListJob = GluonPlayer::ServiceProvider::instance()->fetchCategories();
    connect( categoryListJob, SIGNAL( succeeded() ), SLOT( categoriesFetched() ) );
    categoryListJob->start();
}

void DistributionDock::categoriesFetched()
{
    QList<GluonPlayer::CategoryItem*> categories =
        qobject_cast<GluonPlayer::CategoryListJob*>( sender() )->data().value< QList<GluonPlayer::CategoryItem*> >();
    d->ui.categoryList->clear();
    d->categoryIds.clear();

    foreach( GluonPlayer::CategoryItem * category, categories )
    {
        QString categoryString = category->name();

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
    GluonPlayer::ServiceProvider* provider = GluonPlayer::ServiceProvider::instance();

    if( provider->hasCredentials() )
    {
        d->ui.usernameEdit->setText( provider->username() );
        d->ui.passwordEdit->setText( provider->password() );
    }
    else
    {
        connect( provider, SIGNAL( initializationFinished() ), SLOT( loadCredentials() ) );
    }
}

void DistributionDock::initEditGameProvider()
{
    if( d->editGameJob )
        return;

    d->editGameJob = GluonPlayer::ServiceProvider::instance()->editGame(
                              d->ui.idEdit->text() );
    connect( d->editGameJob, SIGNAL( succeeded() ), SLOT( editGameFinished() ) );
    connect( d->editGameJob, SIGNAL( failed() ), SLOT( editGameFailed() ) );
    d->editGameJob->start();
}

void DistributionDock::initGuiStates()
{
    d->loggedOutState = new QState();
    d->loggingInState = new QState();
    d->loggedInState = new QState();
    d->fetchingState = new QState( d->loggedInState );
    d->editingState = new QState( d->loggedInState );
    d->loggedInState->setInitialState( d->fetchingState );
    d->createState = new QState( d->editingState );
    d->updateState = new QState( d->editingState );
    d->editingState->setInitialState( d->createState );
    d->uploadingState = new QState( d->loggedInState );
    d->stateBeforeUploading = new QHistoryState( d->editingState );
    d->uploadFinishedState = new QState( d->loggedInState );

    d->uploadFinishedState->addTransition( d->stateBeforeUploading );

    d->machine.addState( d->loggedOutState );
    d->machine.addState( d->loggingInState );
    d->machine.addState( d->loggedInState );
    d->machine.addState( d->fetchingState );
    d->machine.addState( d->editingState );
    d->machine.addState( d->createState );
    d->machine.addState( d->updateState );
    d->machine.addState( d->uploadingState );
    d->machine.addState( d->uploadFinishedState );

    d->machine.setInitialState( d->loggedOutState );

    d->loggedOutState->assignProperty( d->ui.loginButton, "text", i18n( "Login" ) );
    d->loggedOutState->assignProperty( d->ui.loginPage, "enabled", true );
    d->loggedOutState->assignProperty( d->ui.stackedWidget, "currentIndex", d->ui.stackedWidget->indexOf( d->ui.loginPage ) );

    d->loggingInState->assignProperty( d->ui.loginButton, "text", i18n( "Logging In" ) );
    d->loggingInState->assignProperty( d->ui.loginPage, "enabled", false );

    d->loggedInState->assignProperty( d->ui.stackedWidget, "currentIndex", d->ui.stackedWidget->indexOf( d->ui.gamePage ) );

    d->fetchingState->assignProperty( d->ui.basicGroupBox, "enabled", false );
    d->fetchingState->assignProperty( d->ui.detailsGroupBox, "enabled", false );

    d->editingState->assignProperty( d->ui.gamePage, "enabled", true );

    d->createState->assignProperty( d->ui.basicGroupBox, "enabled", true );
    d->createState->assignProperty( d->ui.detailsGroupBox, "enabled", false );
    d->createState->assignProperty( d->ui.createUpdateButton, "text", i18n( "Create" ) );

    d->updateState->assignProperty( d->ui.basicGroupBox, "enabled", true );
    d->updateState->assignProperty( d->ui.detailsGroupBox, "enabled", true );
    d->updateState->assignProperty( d->ui.createUpdateButton, "text", i18n( "Update" ) );

    d->uploadingState->assignProperty( d->ui.createUpdateButton, "text", i18n( "Uploading" ) );
    d->uploadingState->assignProperty( d->ui.gamePage, "enabled", false );

    d->loggedOutState->addTransition( d->ui.loginButton, SIGNAL( clicked() ), d->loggingInState );
    d->loggingInState->addTransition( GluonPlayer::ServiceProvider::instance(), SIGNAL( loginFinished() ), d->loggedInState );
    d->loggingInState->addTransition( GluonPlayer::ServiceProvider::instance(), SIGNAL( loginFailed() ), d->loggedOutState );
    d->fetchingState->addTransition( this, SIGNAL( switchToCreateMode() ), d->createState );
    d->fetchingState->addTransition( this, SIGNAL( switchToUpdateMode() ), d->updateState );
    d->editingState->addTransition( d->ui.createUpdateButton, SIGNAL( clicked() ), d->uploadingState );
    d->editingState->addTransition( GluonEngine::Game::instance(), SIGNAL( currentProjectChanged( GluonEngine::GameProject* ) ),
                                    d->fetchingState );
    d->uploadingState->addTransition( this, SIGNAL( gameUploadFinished() ), d->uploadFinishedState );

    connect( d->loggingInState, SIGNAL( entered() ), this, SLOT( doLogin() ) );
    connect( d->fetchingState, SIGNAL( entered() ), this, SLOT( updateUiFromGameProject() ) );
    connect( d->uploadingState, SIGNAL( entered() ), this, SLOT( createOrUpdateGame() ) );
    connect( d->editingState, SIGNAL( entered() ), SLOT( initEditGameProvider() ) );

    d->machine.start();
}

void DistributionDock::gameDetailsFetched( )
{
    GluonPlayer::GameDetailItem* gameDetails =
        qobject_cast<GluonPlayer::GameDetailsJob*>( sender() )->data().value<GluonPlayer::GameDetailItem*>();
    d->ui.categoryList->setCurrentIndex( d->categoryIds.indexOf( gameDetails->category() ) );
    d->ui.gameNameEdit->setText( gameDetails->gameName() );
    d->ui.versionEdit->setText( gameDetails->version() );
    d->ui.homepageEdit->setText( gameDetails->homePage() );
    d->ui.licenseList->setCurrentIndex( d->licenseIds.indexOf( gameDetails->license() ) );
    d->ui.descriptionEdit->setPlainText( gameDetails->gameDescription() );
    d->ui.changelogEdit->setPlainText( gameDetails->changelog() );

    emit switchToUpdateMode();
}

void DistributionDock::updateLicenses()
{
    GluonPlayer::LicenseJob* licenseJob = GluonPlayer::ServiceProvider::instance()->fetchLicenses();
    connect( licenseJob, SIGNAL( succeeded() ), SLOT( licensesFetched() ) );
    licenseJob->start();
}

void DistributionDock::licensesFetched()
{
    QList<GluonPlayer::LicenseItem*> licenses =
        qobject_cast<GluonPlayer::LicenseJob*>( sender() )->data().value< QList<GluonPlayer::LicenseItem*> >();
    d->ui.licenseList->clear();
    d->licenseIds.clear();

    foreach( GluonPlayer::LicenseItem * license, licenses )
    {
        d->licenseIds.append( license->id() );
        d->ui.licenseList->addItem( license->licenseName() );
    }
}

//FIXME: Ideally these should not be needed.
//But putting them in headers in player/lib doesn't work

Q_DECLARE_METATYPE( QList<GluonPlayer::CategoryItem*> )
Q_DECLARE_METATYPE( GluonPlayer::GameDetailItem* )
Q_DECLARE_METATYPE( QList<GluonPlayer::LicenseItem*> )

#include "distributiondock.moc"
