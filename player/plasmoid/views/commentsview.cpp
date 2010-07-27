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

    connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(reactToCommentsInserted(QModelIndex, int, int)));
    connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
            this, SLOT(updateComments(QModelIndex, QModelIndex)));
}

CommentsViewItem* CommentsView::addComment(const QModelIndex& index, QGraphicsWidget *parent, int depth)
{
    CommentsViewItem *item = new CommentsViewItem(parent);
    item->setParent(parent);
    item->setDepth(depth);
    item->setModelIndex(index);
    m_commentFromIndex[index] = item;
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
}

void CommentsView::reactToCommentsInserted(const QModelIndex& parent, int start, int end)
{
    CommentsViewItem *parentComment = m_commentFromIndex[parent];
    QModelIndex index = parent.child(start, 0);
    CommentsViewItem *item = new CommentsViewItem(parentComment);
    item->setParent(parentComment);
    item->setDepth(parentComment->depth() + 1);
    m_commentFromIndex[index] = item;
    item->setAcceptHoverEvents(true);
    item->installEventFilter(this);
    connect(item, SIGNAL(replyClicked()), this, SLOT(showReply()));
    item->setRowInLayout(parentComment->rowInLayout() + 1);

    //FIXME: This isn't perfect, gotta fix this next
    m_contentLayout->insertItem(item->rowInLayout(), item);
}

void CommentsView::updateComments(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    /*Updation occurs only at a new comment,
    Existing comments can't be edited.

    Each cell updation calls this function once,
    but we want to set the model index only when
    all columns are updated (inserted)*/

    if (bottomRight.column() < GluonPlayer::CommentsModel::RatingColumn)
        return;

    CommentsViewItem *commentItem = m_commentFromIndex[topLeft.sibling(topLeft.row(), 0)];
    if (commentItem) {
        commentItem->setModelIndex(topLeft.sibling(topLeft.row(), 0));
    }
}
