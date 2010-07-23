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

#include "commentsviewitem.h"
#include <Plasma/IconWidget>
#include <models/commentsmodel.h>
#include <Plasma/Label>
#include <QGraphicsGridLayout>

CommentsViewItem::CommentsViewItem(QGraphicsItem* parent, Qt::WindowFlags wFlags)
        : QGraphicsWidget(parent, wFlags), m_author(0), m_title(0), m_body(0), m_dateTime(0),
        m_rating(0), m_layout(0)
{

}

void CommentsViewItem::setModelIndex(const QModelIndex& index)
{
    m_index = index;
    layoutWidgets();
    setToolTips();
}

QModelIndex CommentsViewItem::modelIndex() const
{
    return m_index;
}

void CommentsViewItem::layoutWidgets()
{
    m_layout = new QGraphicsGridLayout();

    m_author = new Plasma::IconWidget(this);
    m_author->setText(m_index.sibling(m_index.row(), GluonPlayer::CommentsModel::AuthorColumn).data().toString());

    m_title = new Plasma::Label(this);
    m_title->setText(m_index.sibling(m_index.row(), GluonPlayer::CommentsModel::TitleColumn).data().toString());

    m_body = new Plasma::Label(this);
    m_body->setText(m_index.sibling(m_index.row(), GluonPlayer::CommentsModel::BodyColumn).data().toString());

    m_dateTime = new Plasma::Label(this);
    m_dateTime->setText(m_index.sibling(m_index.row(), GluonPlayer::CommentsModel::DateTimeColumn).data().toString());

    m_rating = new Plasma::Label(this);
    m_rating->setText(m_index.sibling(m_index.row(), GluonPlayer::CommentsModel::RatingColumn).data().toString());

    m_layout->addItem(m_author, 0, 0);
    m_layout->addItem(m_title, 0, 1);
    m_layout->addItem(m_body, 1, 0, 1, 2);
    m_layout->addItem(m_dateTime, 2, 0);
    m_layout->addItem(m_rating, 2, 1);

    setLayout(m_layout);
}

void CommentsViewItem::setToolTips()
{

}

CommentsViewItem::~CommentsViewItem()
{

}
