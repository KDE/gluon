/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "commentsviewitem.h"

#include "lib/models/commentsmodel.h"

CommentsViewItem::CommentsViewItem( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_author( 0 )
    , m_title( 0 )
    , m_body( 0 )
    , m_dateTime( 0 )
    , m_rating( 0 )
    , m_replyButton( 0 )
    , m_layout( 0 )
    , m_depth( 0 )
    , m_replyEnabled( false )
{
    //setOwnedByLayout(false);
}

CommentsViewItem::~CommentsViewItem()
{
}

void CommentsViewItem::setModelIndex( const QModelIndex& index )
{
    m_index = index;
    layoutWidgets();
    setToolTips();
}

QModelIndex CommentsViewItem::modelIndex() const
{
    //Convert Persistent to normal model index and return
    return m_index.sibling( m_index.row(), m_index.column() );
}

int CommentsViewItem::depth()
{
    return m_depth;
}

void CommentsViewItem::setDepth( int newDepth )
{
    m_depth = newDepth;
    setContentsMargins( m_depth * 20, 0, 0, 0 );
}

int CommentsViewItem::rowInLayout()
{
    return m_rowInLayout;
}

void CommentsViewItem::setRowInLayout( int row )
{
    m_rowInLayout = row;
}

bool CommentsViewItem::replyEnabled()
{
    return m_replyEnabled;
}

void CommentsViewItem::setReplyEnabled( bool enabled )
{
    m_replyEnabled = enabled;
}

void CommentsViewItem::hoverEnterEvent( QHoverEvent* event )
{
    if( m_replyEnabled )
    {
        m_replyButton->setVisible( true );
    }
    event->accept();
}

void CommentsViewItem::hoverLeaveEvent( QHoverEvent* event )
{
    if( m_replyEnabled )
    {
        m_replyButton->setVisible( false );
    }
    event->accept();
}


void CommentsViewItem::layoutWidgets()
{
    m_layout = new QGridLayout();

    m_author = new GameTextLabel( this );
    m_author->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::AuthorColumn ).data().toString() );

    m_title = new GameTextLabel( this );
    m_title->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::TitleColumn ).data().toString() );
    m_title->setAlignment( Qt::AlignRight );

    m_body = new GameTextLabel( this );
    m_body->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::BodyColumn ).data().toString() );

    m_dateTime = new GameTextLabel( this );
    m_dateTime->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::DateTimeColumn ).data().toString() );

    m_rating = new GameTextLabel( this );
    m_rating->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::RatingColumn ).data().toString() );

    m_replyButton = new KPushButton( this );
    m_replyButton->setVisible( false );
    m_replyButton->setIcon( KIcon( "edit-undo" ) );
    connect( m_replyButton, SIGNAL( clicked() ), SIGNAL( replyClicked() ) );

    m_layout->addWidget( m_title, 0, 0 );
    m_layout->addWidget( m_author, 0, 1 );
    m_layout->addWidget( m_body, 1, 0, 1, 2 );
    m_layout->addWidget( m_dateTime, 2, 0 );
    m_layout->addWidget( m_rating, 2, 1 );
    m_layout->addWidget( m_replyButton, 2, 2 );

    setLayout( m_layout );
}

void CommentsViewItem::setToolTips()
{
}

