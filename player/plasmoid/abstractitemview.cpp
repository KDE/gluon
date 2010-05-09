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
#include <QPainter>
#include <KDebug>
#include <QGraphicsSceneEvent>

using namespace GluonPlayer;

AbstractItemView::AbstractItemView(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags), m_model(0)
{
    m_background.setImagePath("widgets/translucentbackground");
    m_background.setEnabledBorders(Plasma::FrameSvg::AllBorders);
}

QAbstractItemModel* AbstractItemView::model() const
{
    return m_model;
}

void AbstractItemView::setModel(QAbstractItemModel* model)
{
    m_model = model;
}

void AbstractItemView::keyPressEvent(QKeyEvent* event)
{
    QGraphicsItem::keyPressEvent(event);
}

void AbstractItemView::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    QGraphicsItem::wheelEvent(event);
}

void AbstractItemView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    m_background.paintFrame(painter);
}

void AbstractItemView::resizeEvent(QGraphicsSceneResizeEvent* event)
{
    m_background.resizeFrame(event->newSize());
}

#include "abstractitemview.moc"
