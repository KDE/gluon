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

#include "abstractitemview.h"

#include <QAbstractItemModel>

using namespace GluonPlayer;

AbstractItemView::AbstractItemView(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags), m_model(0)
{
}

QAbstractItemModel* AbstractItemView::model() const
{
    return m_model;
}

void AbstractItemView::setModel(QAbstractItemModel* model)
{
    m_model = model;
    
    connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), 
            SLOT(rowsInserted(QModelIndex,int,int)));
}

void AbstractItemView::keyPressEvent(QKeyEvent* event)
{
    QGraphicsItem::keyPressEvent(event);
}

void AbstractItemView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
}

void AbstractItemView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void AbstractItemView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void AbstractItemView::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    QGraphicsItem::wheelEvent(event);
}

void AbstractItemView::rowsInserted(const QModelIndex& parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
}

#include "abstractitemview.moc"