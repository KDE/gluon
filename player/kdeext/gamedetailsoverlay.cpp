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

#include "gamedetailsoverlay.h"
#include "views/highscoresview.h"
#include "views/achievementsview.h"
#include "views/commentsview.h"
#include "lib/models/commentsmodel.h"
#include "lib/models/highscoresmodel.h"

GameDetailsOverlay::GameDetailsOverlay( QString gameId, QWidget* parent, Qt::WindowFlags wFlags )
    : Overlay( parent, wFlags )
    , m_backButton( new KPushButton( this ) )
    , m_tabWidget( new KTabWidget( this ) )
    , m_highScoresView( new HighScoresView( this ) )
    , m_achievementsView( new AchievementsView( this ) )
    , m_commentsView( new CommentsView( this ) )
    // , m_commentsModel( new GluonPlayer::CommentsModel( gameId ) )
    , m_highScoresModel( new GluonPlayer::HighScoresModel( gameId ) )
{

    m_backButton->setIcon( KIcon( "go-previous-view" ) );
    m_backButton->setText( i18n( "Back" ) );
    m_backButton->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    connect( m_backButton, SIGNAL( clicked() ), SIGNAL( back() ) );

    m_highScoresView->setModel( m_highScoresModel );
    // m_commentsView->setModel( m_commentsModel );

    m_tabWidget->addTab( m_highScoresView, KIcon( "games-highscores" ), i18n( "High Scores" ) );
    m_tabWidget->addTab( m_achievementsView, KIcon( "games-endturn" ), i18n( "Achievements" ) );
    m_tabWidget->addTab( m_commentsView, KIcon( "text-plain" ), i18n( "Comments" ) );

    m_contentLayout = static_cast<QGridLayout*>( layout() );
    m_contentLayout->addWidget( m_backButton, 0, 0, 1, 2 );
    m_contentLayout->addWidget( m_tabWidget, 1, 0, 1, 2 );
}

GameDetailsOverlay::~GameDetailsOverlay()
{
    delete m_commentsModel;
    delete m_highScoresModel;
}
