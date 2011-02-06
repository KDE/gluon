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
    , m_preview( new KSqueezedTextLabel )
    , m_gameName( new KSqueezedTextLabel( this ) )
    , m_gameDescription( new KSqueezedTextLabel( this ) )
    // , m_playButton( new KPushButton( this ) )
    , m_layout( new QGridLayout() )
{
}

void GamesViewItem::setModelIndex( const QModelIndex& index )
{
    m_index = index;
    layoutWidgets();
}

void GamesViewItem::layoutWidgets()
{
    m_preview->setPixmap(KIcon( "gluon-creator").pixmap(32, 32));
    m_gameName->setText( m_index.sibling( m_index.row(), GluonPlayer::GamesModel::NameColumn ).data().toString() );
    m_gameDescription->setText( m_index.sibling( m_index.row(), GluonPlayer::GamesModel::DescriptionColumn ).data().toString() );

    // m_playButton->setIcon( KIcon( "media-playback-start" ) );
    // m_playButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::MinimumExpanding );
    // connect( m_playButton, SIGNAL( activated() ), SLOT( playGameActivated() ) );

    m_layout->addWidget( m_preview, 0, 0, 2, 1 );
    m_layout->addWidget( m_gameName, 0, 1 );
    m_layout->addWidget( m_gameDescription, 1, 1 );
    // m_layout->addWidget( m_playButton, 0, 2, 2, 1 );
    setLayout( m_layout );
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
    Q_UNUSED( event )
    emit gameSelected( m_index );
}
