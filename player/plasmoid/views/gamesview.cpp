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

#include "gamesview.h"
#include "gamesviewitem.h"

#include <Plasma/ItemBackground>

#include <QtGui/QGraphicsLinearLayout>
#include <QtCore/QModelIndex>

GamesView::GamesView( QGraphicsItem* parent, Qt::WindowFlags wFlags )
    : AbstractItemView( parent, wFlags )
    , m_itemBackground( new Plasma::ItemBackground( this ) )
{
}

void GamesView::setModel( QAbstractItemModel* model )
{
    AbstractItemView::setModel( model );

    for( int i = 0; i < m_model->rowCount(); ++i )
    {
        GamesViewItem* item = new GamesViewItem( this );
        item->setModelIndex( m_model->index( i, 0 ) );
        item->setAcceptHoverEvents( true );
        item->installEventFilter( this );
        connect( item, SIGNAL(gameToPlaySelected(QModelIndex)), SIGNAL(gameToPlaySelected(QModelIndex)) );
        connect( item, SIGNAL(gameSelected(QModelIndex)), SIGNAL(gameSelected(QModelIndex)) );
        m_contentLayout->addItem( item );
    }
}

bool GamesView::eventFilter( QObject* obj, QEvent* event )
{
    if( event->type() == QEvent::GraphicsSceneHoverEnter )
    {
        QGraphicsItem* item = qobject_cast<QGraphicsItem*> ( obj );
        m_itemBackground->setTargetItem( item );
    }

    return QObject::eventFilter( obj, event );
}

#include "gamesview.moc"
