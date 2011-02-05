/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *****************************************************************************/

#include "itemsviewbasedelegate.h"

ItemsViewBaseDelegate::ItemsViewBaseDelegate(QAbstractItemView *itemView, QObject * parent)
        : KWidgetItemDelegate(itemView, parent)
        , m_itemView( itemView )
        , m_preview( KIcon( "gluon_creator" ) )
        , m_gameName( new QLabel( m_itemView) )
        , m_gameDescription( new QLabel( m_itemView ) )
{
}

ItemsViewBaseDelegate::~ItemsViewBaseDelegate()
{
}

bool ItemsViewBaseDelegate::eventFilter(QObject *watched, QEvent *event)
{
   if (event->type() == QEvent::MouseButtonDblClick) {
       return true;
   }

   return KWidgetItemDelegate::eventFilter(watched, event);
}

