/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) <year> <author> <email@example.com>
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

#include "viewitem.h"

#include <QModelIndex>
#include <QGraphicsSceneMouseEvent>
#include <qpainter.h>

using namespace GluonPlayer;

ViewItem::ViewItem(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags)
{

}

void ViewItem::setModelIndex(const QModelIndex &index)
{
    m_index = index;
}


QModelIndex ViewItem::modelIndex() const
{
    return m_index;
}

void ViewItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_index.isValid()) {
        emit(activated(m_index));
    }
    QGraphicsItem::mousePressEvent(event);
}

void ViewItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawText(boundingRect(), Qt::AlignLeft, m_index.data().toString());
}

#include "viewitem.moc"