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
#include "views/achievementsview.h"
#include "lib/models/commentsmodel.h"
#include "lib/models/highscoresmodel.h"

using namespace GluonKDEPlayer;

GameDetailsOverlay::GameDetailsOverlay( QString gameId, QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_backButton( new KPushButton( this ) )
    , m_tabWidget( new KTabWidget( this ) )
    , m_highScoresView( new QTableView( this ) )
    , m_achievementsView( new AchievementsView( this ) )
    , m_commentsView( new QListView( this ) )
    , m_commentsDelegate( new CommentItemsViewDelegate(m_commentsView, this ) )
    , m_commentsModel( new GluonPlayer::CommentsModel( gameId ) )
    , m_highScoresModel( new GluonPlayer::HighScoresModel( gameId ) )
    , m_contentLayout( new QGridLayout( this ) )
    , m_newCommentForm( new NewCommentForm( this ) )
{
    m_backButton->setIcon( KIcon( "go-previous-view" ) );
    m_backButton->setText( i18n( "Back" ) );
    m_backButton->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    connect( m_backButton, SIGNAL( clicked() ), SIGNAL( back() ) );

    m_highScoresView->setModel( m_highScoresModel );
    m_commentsView->setItemDelegate( m_commentsDelegate );
    connect(m_commentsDelegate, SIGNAL( commentReplyClicked( QModelIndex ) ), SLOT( showReplyForm( QModelIndex ) ));
    m_commentsView->setModel( m_commentsModel );

    m_tabWidget->addTab( m_highScoresView, KIcon( "games-highscores" ), i18n( "High Scores" ) );
    m_tabWidget->addTab( m_achievementsView, KIcon( "games-endturn" ), i18n( "Achievements" ) );
    m_tabWidget->addTab( m_commentsView, KIcon( "text-plain" ), i18n( "Comments" ) );

    m_contentLayout->addWidget( m_backButton, 0, 0, 1, 2 );
    m_contentLayout->addWidget( m_tabWidget, 1, 0, 1, 2 );
    setContentsMargins( 10, 15, 10, 15 );
    setLayout(m_contentLayout);
}

GameDetailsOverlay::~GameDetailsOverlay()
{
    /* delete m_commentsModel;
    delete m_highScoresModel; */
}

void GameDetailsOverlay::addNewUserComment( QModelIndex parentIndex, QString title, QString body )
{
    m_commentsModel->uploadComment( parentIndex, title, body );
    m_contentLayout->removeWidget( m_newCommentForm );
    // connect( m_commentsModel, SIGNAL( addCommentFailed() ), SLOT( showComments() ) );
}

void GameDetailsOverlay::showReplyForm( const QModelIndex& index )
{
    // hideComments();
    // m_contentLayout->addItem( form );
    // form->setParentIndex( parentItem->modelIndex() );

    m_newCommentForm->setParentIndex( index );
    connect( m_newCommentForm, SIGNAL( accepted( QModelIndex, QString, QString ) ),
             SLOT( addNewUserComment( QModelIndex, QString, QString ) ) );
    connect( m_newCommentForm, SIGNAL( canceled() ), SLOT( cancelNewComment() ) );

    m_contentLayout->addWidget( m_newCommentForm, 0, 0, 1, 2 );
}

