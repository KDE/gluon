/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "gamesoverlay.h"

#include <QtCore/QDebug>

using namespace GluonKDEPlayer;

GamesOverlay::GamesOverlay( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_view( new QListView( this ) )
    , m_model( new ListModel( m_view ) )
    , m_gamesView( new QListView( this ) )
    , m_gamesDelegate( new ItemsViewDelegate( m_gamesView, this ) )
    , m_gameItemsModel( new GluonPlayer::GameItemsModel( m_gamesView ) )
    , m_loginForm( new LoginForm( this ) )
    , m_gridLayout( new QGridLayout( this ) )
    , m_stackedWidget( new QStackedWidget( this ) )
    , m_availableView( new KSqueezedTextLabel( i18n( "Coming soon!" ), this ) )
    , m_communityView( new KSqueezedTextLabel( i18n( "Community. Under development!" ), this ) )
    , m_gameDetailsOverlay( 0 )
{
    m_view->setModel( m_model );
    m_model->appendPair( qMakePair( i18n( "Login" ), new KIcon( "network-connect" ) ) );
    m_stackedWidget->addWidget( m_loginForm );

    m_model->appendPair( qMakePair( i18n( "Installed" ), new KIcon( "applications-games" ) ) );
    m_gamesView->setItemDelegate( m_gamesDelegate );
    connect( m_gamesDelegate, SIGNAL( gameToPlaySelected( QModelIndex ) ), SIGNAL( gameToPlaySelected( QModelIndex ) ) );
    connect( m_gamesDelegate, SIGNAL( gameSelected( QModelIndex ) ), SLOT( showGameDetails( QModelIndex ) ) );
    m_gamesView->setModel( m_gameItemsModel );
    m_stackedWidget->addWidget( m_gamesView );

    m_model->appendPair( qMakePair( i18nc( "The list of the games that can be downloaded", "Available" ), new KIcon( "get-hot-new-stuff" ) ) );
    m_stackedWidget->addWidget( m_availableView );

    m_model->appendPair( qMakePair( i18n( "Community" ), new KIcon( "system-users" ) ) );
    m_stackedWidget->addWidget( m_communityView );

    m_gridLayout->addWidget( m_view, 0, 0 );
    m_gridLayout->setColumnStretch( 0, 1 );

    m_gridLayout->addWidget( m_stackedWidget, 0, 1 );
    m_gridLayout->setColumnStretch( 1, 3 );
    setLayout( m_gridLayout );

    connect( m_view->selectionModel(), SIGNAL( currentChanged( const QModelIndex&, const QModelIndex& ) ),
             SLOT( selectionChanged( const QModelIndex&, const QModelIndex& ) ) );
}

GamesOverlay::~GamesOverlay()
{
    delete m_model;
    delete m_gameItemsModel;
}

QListView* GamesOverlay::gamesView()
{
    return m_gamesView;
}

void GamesOverlay::selectionChanged( const QModelIndex& current, const QModelIndex& /* previous */ )
{
    m_stackedWidget->setCurrentIndex( current.row( ) );
}

void GamesOverlay::backToGames()
{
    m_stackedWidget->removeWidget( m_gameDetailsOverlay );
    delete m_gameDetailsOverlay;
    m_gameDetailsOverlay = 0;
    m_stackedWidget->setCurrentIndex( m_stackedWidget->indexOf( m_gamesView ) );
}

void GamesOverlay::showGameDetails( const QModelIndex& index )
{
    QString userName = "user";

    if( m_gameDetailsOverlay )
    {
        m_stackedWidget->removeWidget( m_gameDetailsOverlay );
        delete m_gameDetailsOverlay;
        m_gameDetailsOverlay = 0;
    }

    m_gameDetailsOverlay = new GameDetailsOverlay( m_gameItemsModel->installedGameInfo(index.row())->metaData(), userName, this );
    m_stackedWidget->addWidget( m_gameDetailsOverlay );
    m_stackedWidget->setCurrentIndex( m_stackedWidget->count() - 1 );
    connect( m_gameDetailsOverlay, SIGNAL( back() ), SLOT( backToGames() ) );
}
