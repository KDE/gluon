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
#include <QGraphicsGridLayout>

#include <KIcon>
#include <Plasma/IconWidget>

using namespace GluonPlayer;

GamesViewItem::GamesViewItem(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags), m_iconWidget(0)
{

}

void GamesViewItem::setModelIndex(const QModelIndex &index)
{
    m_index = index;

    QGraphicsGridLayout *layout = new QGraphicsGridLayout();
    
    m_iconWidget = new Plasma::IconWidget(KIcon("gluon_creator"), 
           index.data().toString(), this);
    m_iconWidget->setDrawBackground(true);
    m_iconWidget->setOrientation(Qt::Horizontal);
    m_iconWidget->setGeometry(geometry());
    m_iconWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    
    layout->addItem(m_iconWidget, 0, 0);
    setLayout(layout);

    connect(m_iconWidget, SIGNAL(activated()), SLOT(iconClicked()));
}


QModelIndex GamesViewItem::modelIndex() const
{
    return m_index;
}

void GamesViewItem::iconClicked()
{
    emit activated(m_index);
}

#include "gamesviewitem.moc"
