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

#include "highscoresview.h"
#include "highscoresviewitem.h"

#include <lib/models/highscoresmodel.h>

HighScoresView::HighScoresView( QWidget* parent, Qt::WindowFlags wFlags )
    : AbstractItemView( parent, wFlags )
    , m_model( 0 )
{
}

HighScoresView::~HighScoresView()
{
}

void HighScoresView::setModel( QAbstractItemModel* model )
{
    AbstractItemView::setModel( model );

    for( int i = 0; i < model->rowCount(); ++i )
    {
        HighScoresViewItem* item = new HighScoresViewItem( this );
        item->setModelIndex( model->index( i, 0 ) );
        // item->setAcceptHoverEvents( true );
        item->installEventFilter( this );
        m_contentLayout->addWidget( item );
    }
}

bool HighScoresView::eventFilter( QObject* obj, QEvent* event )
{
    if( event->type() == QEvent::HoverEnter )
    {
        QWidget* item = qobject_cast<QWidget*> ( obj );
        // m_itemBackground->setTargetItem( item );
    }

    return QObject::eventFilter( obj, event );
}
