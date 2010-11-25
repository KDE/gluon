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

#include "overlay.h"

#include <QAbstractItemModel>

Overlay::Overlay( QWidget* parent, Qt::WindowFlags wFlags )
    : QWidget( parent, wFlags )
    , m_contentLayout( new QGridLayout( ) )
    , m_contentWidget( new QWidget( this ) )
{
    QGridLayout* layout = new QGridLayout();
    setLayout( layout );
    setContentsMargins( 10, 15, 10, 15 );

    m_contentWidget->setLayout( m_contentLayout );
}

void Overlay::keyPressEvent( QKeyEvent* event )
{
    QWidget::keyPressEvent( event );
}

void Overlay::wheelEvent( QWheelEvent* event )
{
    QWidget::wheelEvent( event );
}

void Overlay::resizeEvent( QResizeEvent* event )
{
}

#include "overlay.moc"
