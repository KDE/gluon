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

#include "commentsviewitem.h"

#include <models/commentsmodel.h>

#include <KIcon>
#include <Plasma/IconWidget>
#include <Plasma/Label>

#include <QGraphicsGridLayout>

CommentsViewItem::CommentsViewItem( QGraphicsItem* parent, Qt::WindowFlags wFlags )
    : QGraphicsWidget( parent, wFlags )
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

void CommentsViewItem::hoverEnterEvent( QGraphicsSceneHoverEvent* event )
{
    if( m_replyButton && m_replyEnabled )
    {
        m_replyButton->setVisible( true );
    }
    QGraphicsItem::hoverEnterEvent( event );
}

void CommentsViewItem::hoverLeaveEvent( QGraphicsSceneHoverEvent* event )
{
    if( m_replyButton && m_replyEnabled )
    {
        m_replyButton->setVisible( false );
    }
    QGraphicsWidget::hoverLeaveEvent( event );
}


void CommentsViewItem::layoutWidgets()
{
    m_layout = new QGraphicsGridLayout();

    m_author = new Plasma::IconWidget( this );
    m_author->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::AuthorColumn ).data().toString() );

    m_title = new Plasma::Label( this );
    m_title->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::TitleColumn ).data().toString() );
    m_title->setAlignment( Qt::AlignRight );

    m_body = new Plasma::Label( this );
    m_body->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::BodyColumn ).data().toString() );

    m_dateTime = new Plasma::Label( this );
    m_dateTime->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::DateTimeColumn ).data().toString() );

    m_rating = new Plasma::Label( this );
    m_rating->setText( m_index.sibling( m_index.row(), GluonPlayer::CommentsModel::RatingColumn ).data().toString() );

    m_replyButton = new Plasma::IconWidget( this );
    m_replyButton->setVisible( false );
    m_replyButton->setIcon( KIcon( "edit-undo" ) );
    connect( m_replyButton, SIGNAL( activated() ), SIGNAL( replyClicked() ) );

    m_layout->addItem( m_title, 0, 0 );
    m_layout->addItem( m_author, 0, 1 );
    m_layout->addItem( m_body, 1, 0, 1, 2 );
    m_layout->addItem( m_dateTime, 2, 0 );
    m_layout->addItem( m_rating, 2, 1 );
    m_layout->addItem( m_replyButton, 2, 2 );

    setLayout( m_layout );
}

void CommentsViewItem::setToolTips()
{
}

