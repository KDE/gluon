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

#include "gamedetailsoverlay.h"
#include "views/highscoresview.h"
#include "views/achievementsview.h"
#include "views/commentsview.h"
#include "models/commentsmodel.h"
#include "models/highscoresmodel.h"

GameDetailsOverlay::GameDetailsOverlay( QString gameId, QWidget* parent, Qt::WindowFlags wFlags )
    : Overlay( parent, wFlags )
{
    m_tabWidget = new QTabWidget( this );

    m_backButton = new QLabel( this );
    // m_backButton->setPixmap( QIcon( "go-previous-view" ) );
    m_backButton->setText( tr( "Back" ) );

    // m_backButton->setOrientation( Qt::Horizontal );
    // m_backButton->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    connect( m_backButton, SIGNAL( activated() ), SIGNAL( back() ) );

    m_highScoresModel = new GluonPlayer::HighScoresModel( gameId );
    m_highScoresView = new HighScoresView( this );
    m_highScoresView->setModel( m_highScoresModel );

    m_achievementsView = new AchievementsView( this );

    m_commentsModel = new GluonPlayer::CommentsModel( gameId );
    m_commentsView = new CommentsView( this );
    m_commentsView->setModel( m_commentsModel );

    m_tabWidget->addTab( m_highScoresView, QIcon( "games-highscores" ), tr( "High Scores" ) );
    m_tabWidget->addTab( m_achievementsView, QIcon( "games-endturn" ), tr( "Achievements" ) );
    m_tabWidget->addTab( m_commentsView, QIcon( "text-plain" ), tr( "Comments" ) );

    QGridLayout* layout = new QGridLayout( );
    layout->addWidget( m_backButton );
    layout->addWidget( m_tabWidget );
    setLayout( layout );
}

GameDetailsOverlay::~GameDetailsOverlay()
{
    delete m_commentsModel;
    delete m_highScoresModel;
}

#include "gamedetailsoverlay.moc"
