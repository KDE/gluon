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

#include "gamesviewitem.h"
#include "lib/models/gamesmodel.h"

GamesViewItem::GamesViewItem( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_preview( 0 )
    , m_gameName( 0 )
    , m_gameDescription( 0 )
    , m_playButton( 0 )
    , m_layout( 0 )
{
}

void GamesViewItem::setModelIndex( const QModelIndex& index )
{
    m_index = index;
    layoutWidgets();
    setToolTips();
}

void GamesViewItem::layoutWidgets()
{
    m_layout = new QGridLayout();

    m_preview = new QLabel( this );
    // m_preview->setPixmap( KIcon( "gluon_creator" ) );
    // m_preview->setAcceptHoverEvents( false );
    // m_preview->setContentsMargins( 0, 0, 0, 0 );
    // m_preview->setAcceptedMouseButtons( Qt::NoButton );
    // m_preview->setFocusPolicy( Qt::NoFocus );
    // m_preview->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );

    m_gameName = new QLabel( this );
    m_gameName->setText( m_index.sibling( m_index.row(), GluonPlayer::GamesModel::NameColumn ).data().toString() );

    m_gameDescription = new QLabel( this );
    m_gameDescription->setText( m_index.sibling( m_index.row(), GluonPlayer::GamesModel::DescriptionColumn ).data().toString() );

    m_playButton = new QLabel( this );
    // m_playButton->setPixmap( KIcon( "media-playback-start" ) );
    // m_playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    connect( m_playButton, SIGNAL( activated() ), SLOT( playGameActivated() ) );

    m_layout->addWidget( m_preview, 0, 0, 2, 1 );
    m_layout->addWidget( m_gameName, 0, 1 );
    m_layout->addWidget( m_gameDescription, 1, 1 );
    m_layout->addWidget( m_playButton, 0, 2, 2, 1 );
    setLayout( m_layout );
}

void GamesViewItem::setToolTips()
{
    // Plasma::ToolTipContent data;
    // data.setImage( m_preview->icon() );
    // data.setMainText( m_gameName->text() );
    // data.setSubText( i18n( "Click here to Start the game" ) );
    // Plasma::ToolTipManager::self()->setContent( m_playButton, data );
}

QModelIndex GamesViewItem::modelIndex() const
{
    return m_index;
}

void GamesViewItem::playGameActivated()
{
    emit gameToPlaySelected( m_index );
}

void GamesViewItem::mousePressEvent( QMouseEvent* event )
{
    Q_UNUSED( event );
    emit gameSelected( m_index );
}

#include "gamesviewitem.moc"
