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

#include "gamesoverlay.h"
#include "views/gamesview.h"
#include "loginform.h"

#include <Plasma/TabBar>
#include <Plasma/Label>
#include <KDE/KIcon>

#include <QtGui/QGraphicsLinearLayout>

GamesOverlay::GamesOverlay( QGraphicsItem* parent, Qt::WindowFlags wFlags )
    : QGraphicsWidget( parent, wFlags )
    , m_tabBar( new Plasma::TabBar( this ) )
    , m_gamesView( new GamesView( this ) )
    , m_loginForm( new LoginForm( this ) )
{
    connect( m_gamesView, SIGNAL( gameToPlaySelected( QModelIndex ) ), SIGNAL( gameToPlaySelected( QModelIndex ) ) );
    connect( m_gamesView, SIGNAL( gameSelected( QModelIndex ) ), SIGNAL( gameSelected( QModelIndex ) ) );
    m_tabBar->addTab( KIcon( "applications-games" ), i18n( "Installed" ), m_gamesView );

    Plasma::Label* m_tempLabel = new Plasma::Label( this );
    m_tempLabel->setText( i18n( "Coming Soon!" ) );
    m_tabBar->addTab( KIcon( "get-hot-new-stuff" ), i18nc( "The games that can be downloaded", "Available" ), m_tempLabel );

    m_tabBar->addTab( KIcon( "network-connect" ), i18n( "Login" ), m_loginForm );

    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout( Qt::Vertical );
    layout->addItem( m_tabBar );
    setLayout( layout );
}

GamesView* GamesOverlay::gamesView()
{
    return m_gamesView;
}

#include "gamesoverlay.moc"
