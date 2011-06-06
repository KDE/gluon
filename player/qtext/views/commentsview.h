/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#include <QtGui/QGridLayout>
#include <QtCore/QMultiHash>
#include <QtCore/QPersistentModelIndex>

class CommentsViewItem;

class CommentsView : public AbstractItemView
{
        Q_OBJECT
    public:
        explicit CommentsView( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
        virtual void setModel( QAbstractItemModel* model );

    protected slots:
        void showReply();
        void removeComments();
        void loadComments();
        void reloadComments();
        void addNewUserComment( QModelIndex parentIndex, QString title, QString body );
        void cancelNewComment();
        void hideComments();
        void showComments();

    protected:
        bool eventFilter( QObject* obj, QEvent* event );
        CommentsViewItem* addComment( const QModelIndex& index, QWidget* parent, int depth );

        QWidget* m_itemBackground;

    private:
        QWidget* m_rootWidget;
        QWidget* m_commentsFrame;
        QGridLayout* m_commentsLayout;
        bool m_isOnline;
};

#endif // COMMENTSVIEW_H
