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

#include "highscoresviewitem.h"
#include "lib/models/highscoresmodel.h"

HighScoresViewItem::HighScoresViewItem( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_playerName( 0 )
    , m_score( 0 )
{
}

HighScoresViewItem::~HighScoresViewItem()
{
}

void HighScoresViewItem::setModelIndex( const QModelIndex& index )
{
    m_index = index;
    layoutWidgets();
}

QModelIndex HighScoresViewItem::modelIndex() const
{
    return m_index;
}

void HighScoresViewItem::layoutWidgets()
{
    m_playerName = new QLabel( this );
    m_playerName->setText( m_index.sibling( m_index.row(), GluonPlayer::HighScoresModel::NameColumn ).data().toString() );

    m_score = new QLabel( this );
    m_score->setText( m_index.sibling( m_index.row(), GluonPlayer::HighScoresModel::HighScoreColumn ).data().toString() );

    m_level = new QLabel( this );
    m_level->setText( m_index.sibling( m_index.row(), GluonPlayer::HighScoresModel::LevelColumn ).data().toString() );

    m_layout = new QGridLayout();
    m_layout->addWidget( m_playerName );
    m_layout->addWidget( m_score );
    m_layout->addWidget( m_level );
    setLayout( m_layout );
}
