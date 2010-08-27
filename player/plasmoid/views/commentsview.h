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

#ifndef COMMENTSVIEW_H
#define COMMENTSVIEW_H

#include "abstractitemview.h"
#include <QMultiHash>
#include <QPersistentModelIndex>

class QGraphicsLinearLayout;
class CommentsViewItem;

namespace Plasma
{
    class ItemBackground;
    class Frame;
}

class CommentsView : public AbstractItemView
{
        Q_OBJECT

    public:
        CommentsView(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);
        virtual void setModel(QAbstractItemModel* model);

    protected:
        Plasma::ItemBackground *m_itemBackground;

        bool eventFilter(QObject *obj, QEvent *event);
        CommentsViewItem* addComment(const QModelIndex& index, QGraphicsWidget *parent, int depth);

    private:
        QGraphicsWidget *m_rootWidget;
        QGraphicsLinearLayout *m_commentsLayout;
        Plasma::Frame *m_commentsFrame;
        bool m_isOnline;

    protected slots:
        void showReply();
        void removeComments();
        void loadComments();
        void reloadComments();
        void addNewUserComment(QModelIndex parentIndex, QString title, QString body);
        void cancelNewComment();
        void hideComments();
        void showComments();
};

#endif // COMMENTSVIEW_H
