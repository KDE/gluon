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
#include "viewitem.h"

#include <QModelIndex>
#include <QGraphicsLinearLayout>

using namespace GluonPlayer;

GamesView::GamesView(QGraphicsItem* parent, Qt::WindowFlags wFlags): AbstractItemView(parent, wFlags)
{
    m_layout = new QGraphicsLinearLayout(Qt::Horizontal);
    setLayout(m_layout);
}

void GluonPlayer::GamesView::rowsInserted(const QModelIndex& parent, int first, int last)
{
    for (int i=first; i<=last; i++) {
        ViewItem *item = new ViewItem(this);
        item->setModelIndex(m_model->index(i, 0, parent));
        m_layout->addItem(item);
    }
}

#include "gamesview.moc"