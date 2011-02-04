/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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
#include "loginform.h"
#include "views/gamesview.h"

GamesOverlay::GamesOverlay( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_view( new QListView( this ) )
    , m_model( new ListModel( m_view ) )
    , m_gamesView( new GamesView( this ) )
    , m_loginForm( new LoginForm( this ) )
    , m_gridLayout( new QGridLayout( this ) )
    , m_stackedWidget( new QStackedWidget( this ) )
    , m_availableView( new QLabel( i18n( "Coming soon!" ), this ) )
{
    // connect( m_gamesView, SIGNAL( gameToPlaySelected( QModelIndex ) ), SIGNAL( gameToPlaySelected( QModelIndex ) ) );
    // connect( m_gamesView, SIGNAL( gameSelected( QModelIndex ) ), SIGNAL( gameSelected( QModelIndex ) ) );

    // m_tabWidget->addTab( m_gamesView, KIcon( "applications-games" ), i18n( "Installed" ) );

    m_view->setModel(m_model);
    m_model->appendPair(qMakePair(QString("Login"), new KIcon( "network-connect" )));
    m_model->appendPair(qMakePair(QString("Installed"), new KIcon( "applications-games" )));
    m_model->appendPair(qMakePair(QString("Available"), new KIcon( "get-hot-new-stuff" )));
    m_model->appendPair(qMakePair(QString("Community"), new KIcon( "" )));

    m_gridLayout->addWidget( m_view, 0, 0 );
    m_gridLayout->setColumnStretch( 0, 1 );

    m_stackedWidget->addWidget(m_loginForm);
    m_stackedWidget->addWidget(m_gamesView);
    m_stackedWidget->addWidget(m_availableView);
    // m_stackedWidget->addWidget();
    m_gridLayout->addWidget( m_stackedWidget, 0, 1 );
    m_gridLayout->setColumnStretch( 1, 3 );
    setLayout( m_gridLayout );

    connect( m_view->selectionModel(), SIGNAL( currentChanged ( const QModelIndex & current, const QModelIndex & previous ) ),
           SLOT( selectionChanged( const QModelIndex & current, const QModelIndex & previous ) ) );
}

GamesView* GamesOverlay::gamesView()
{
    return m_gamesView;
}

void GamesOverlay::selectionChanged( const QModelIndex & current, const QModelIndex & previous )
{
    Q_UNUSED( previous )
    m_stackedWidget->setCurrentIndex( current.row( ) );
}
