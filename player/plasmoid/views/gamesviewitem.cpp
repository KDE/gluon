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

#include "gamesviewitem.h"
#include "lib/models/gameitemsmodel.h"

#include <KDE/KIcon>
#include <KDE/Plasma/IconWidget>
#include <KDE/Plasma/Label>
#include <KDE/Plasma/ToolTipManager>
#include <KDE/Plasma/ToolTipContent>

GamesViewItem::GamesViewItem( QGraphicsItem* parent, Qt::WindowFlags wFlags )
    : QGraphicsWidget( parent, wFlags )
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
    m_layout = new QGraphicsGridLayout();

    m_preview = new Plasma::IconWidget( this );
    m_preview->setIcon( KIcon( "gluon_creator" ) );
    m_preview->setAcceptHoverEvents( false );
    m_preview->setContentsMargins( 0, 0, 0, 0 );
    m_preview->setAcceptedMouseButtons( Qt::NoButton );
    m_preview->setFocusPolicy( Qt::NoFocus );
    m_preview->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );

    m_gameName = new Plasma::Label( this );
    m_gameName->setText( m_index.data( GluonPlayer::GameItemsModel::GameNameRole ).toString() );

    m_gameDescription = new Plasma::Label( this );
    m_gameDescription->setText( m_index.data( GluonPlayer::GameItemsModel::GameDescriptionRole ).toString() );

    m_playButton = new Plasma::IconWidget( this );
    m_playButton->setIcon( KIcon( "media-playback-start" ) );
    m_playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    connect( m_playButton, SIGNAL( activated() ), SLOT( playGameActivated() ) );

    m_layout->addItem( m_preview, 0, 0, 2, 1 );
    m_layout->addItem( m_gameName, 0, 1 );
    m_layout->addItem( m_gameDescription, 1, 1 );
    m_layout->addItem( m_playButton, 0, 2, 2, 1 );
    setLayout( m_layout );
}

void GamesViewItem::setToolTips()
{
    Plasma::ToolTipContent data;
    data.setImage( m_preview->icon() );
    data.setMainText( m_gameName->text() );
    data.setSubText( i18n( "Click here to Start the game" ) );
    Plasma::ToolTipManager::self()->setContent( m_playButton, data );
}

QModelIndex GamesViewItem::modelIndex() const
{
    return m_index;
}

void GamesViewItem::playGameActivated()
{
    emit gameToPlaySelected( m_index );
}

void GamesViewItem::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    Q_UNUSED( event )
    emit gameSelected( m_index );
}

#include "gamesviewitem.moc"
