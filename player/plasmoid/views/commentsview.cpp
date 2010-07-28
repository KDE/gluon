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

#include "commentsview.h"
#include "commentsviewitem.h"

#include <Plasma/ItemBackground>

#include <QDebug>
#include <QTreeView>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <models/commentsmodel.h>

CommentsView::CommentsView(QGraphicsItem* parent, Qt::WindowFlags wFlags)
        : AbstractItemView(parent, wFlags), m_rootWidget(0)
{
    m_itemBackground = new Plasma::ItemBackground(this);
}

void CommentsView::setModel(QAbstractItemModel* model)
{
    AbstractItemView::setModel(model);

    m_rootWidget = new QGraphicsWidget(this);
    for (int i = 0; i < m_model->rowCount(); i++) {
        addComment(m_model->index(i, 0), m_rootWidget, 0);
    }
}

CommentsViewItem* CommentsView::addComment(const QModelIndex& index, QGraphicsWidget *parent, int depth)
{
    CommentsViewItem *item = new CommentsViewItem(parent);
    item->setParent(parent);
    item->setDepth(depth);
    item->setModelIndex(index);
    item->setAcceptHoverEvents(true);
    item->installEventFilter(this);
    connect(item, SIGNAL(replyClicked()), this, SLOT(showReply()));
    item->setRowInLayout(m_contentLayout->count());
    m_contentLayout->addItem(item);

    if (m_model->hasChildren(index)) {   //There are one or more children
        for (int i = 0; i < m_model->rowCount(index); i++) {
            addComment(index.child(i, 0), item, depth + 1);
        }
    }

    return item;
}

bool CommentsView::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::GraphicsSceneHoverEnter) {
        QGraphicsItem *item = qobject_cast<QGraphicsItem*> (obj);
        m_itemBackground->setTargetItem(item);
    }

    return QObject::eventFilter(obj, event);
}

void CommentsView::showReply()
{
    CommentsViewItem *item = qobject_cast<CommentsViewItem*>(sender());
    QModelIndex parentIndex = item->modelIndex();
    int row = m_model->rowCount(parentIndex);
    if (!m_model->insertRow(row, parentIndex)) {
        qDebug() << "Can't insert new comment";
        return;
    }

    m_model->setData(m_model->index(row, GluonPlayer::CommentsModel::AuthorColumn, parentIndex),
                     "New Author");
    m_model->setData(m_model->index(row, GluonPlayer::CommentsModel::TitleColumn, parentIndex),
                     "New Title");
    m_model->setData(m_model->index(row, GluonPlayer::CommentsModel::BodyColumn, parentIndex),
                     "New Body");
    m_model->setData(m_model->index(row, GluonPlayer::CommentsModel::DateTimeColumn, parentIndex),
                     "NDateTime");
    m_model->setData(m_model->index(row, GluonPlayer::CommentsModel::RatingColumn, parentIndex),
                     "5");

    CommentsViewItem *toDelete;

    while (m_contentLayout->count() > 0) {
        toDelete = dynamic_cast<CommentsViewItem*>(m_contentLayout->itemAt(0));
        m_contentLayout->removeAt(0);
        toDelete->deleteLater();
        m_contentLayout->invalidate();
    }

    for (int i = 0; i < m_model->rowCount(); i++) {
        addComment(m_model->index(i, 0), m_rootWidget, 0);
    }
}
