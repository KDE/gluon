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
#include "models/gamesmodel.h"

#include <QModelIndex>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsGridLayout>

#include <KIcon>
#include <Plasma/IconWidget>
#include <Plasma/Label>

using namespace GluonPlayer;

GamesViewItem::GamesViewItem(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent, wFlags), m_preview(0), m_gameName(0), m_gameStats(0), m_layout(0)
{

}

void GamesViewItem::setModelIndex(const QModelIndex &index)
{
    m_index = index;
    layoutWidgets();
}

void GamesViewItem::layoutWidgets()
{
    m_layout = new QGraphicsGridLayout();

    m_preview = new Plasma::IconWidget(this);
    m_preview->setIcon(KIcon("gluon_creator"));
    m_preview->setAcceptHoverEvents(false);
    m_preview->setContentsMargins(0, 0, 0, 0);
    m_preview->setAcceptedMouseButtons(Qt::NoButton);
    m_preview->setFocusPolicy(Qt::NoFocus);
    m_preview->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    
    m_gameName = new Plasma::Label(this);
    m_gameName->setText(m_index.sibling(m_index.row(), GamesModel::Description).data().toString());
    
    m_gameStats = new Plasma::Label(this);
    m_gameStats->setText(m_index.data().toString());
    
    m_layout->addItem(m_preview, 0, 0, 2, 1);
    m_layout->addItem(m_gameName, 0, 1);
    m_layout->addItem(m_gameStats, 1, 1);
    setLayout(m_layout);
}

QModelIndex GamesViewItem::modelIndex() const
{
    return m_index;
}

void GamesViewItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit activated(m_index);
    QGraphicsItem::mousePressEvent(event);
}

#include "gamesviewitem.moc"
