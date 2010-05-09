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

#include <QModelIndex>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <KIcon>
#include <Plasma/IconWidget>

using namespace GluonPlayer;

GamesViewItem::GamesViewItem(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags)
{
}

void GamesViewItem::setModelIndex(const QModelIndex &index)
{
    m_index = index;

    Plasma::IconWidget *item = new Plasma::IconWidget(KIcon("gluon_creator"), 
           index.data().toString(), this);
    item->setDrawBackground(true);
    item->setOrientation(Qt::Horizontal);
    item->setGeometry(geometry());
    connect(item, SIGNAL(activated()), SLOT(iconClicked()));
}


QModelIndex GamesViewItem::modelIndex() const
{
    return m_index;
}

void GamesViewItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
}

void GamesViewItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void GamesViewItem::iconClicked()
{
    emit activated(m_index);
}

#include "gamesviewitem.moc"
