/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef COMMENTSVIEWITEM_H
#define COMMENTSVIEWITEM_H

#include <KDE/KPushButton>
#include <KDE/KIcon>
#include <KDE/KTitleWidget>

#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include <QtGui/QHoverEvent>
#include <QtCore/QPersistentModelIndex>

class CommentsViewItem : public QWidget
{
        Q_OBJECT
    public:
        explicit CommentsViewItem( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
        virtual ~CommentsViewItem();

        virtual void setModelIndex( const QModelIndex& index );
        QModelIndex modelIndex() const;
        int depth();
        void setDepth( int newDepth );
        int rowInLayout();
        void setRowInLayout( int row );
        bool replyEnabled();
        void setReplyEnabled( bool enabled );

    signals:
        void replyClicked();

    protected:
        void hoverEnterEvent( QHoverEvent* event );
        void hoverLeaveEvent( QHoverEvent* event );

        void layoutWidgets();
        void setToolTips();

        QPersistentModelIndex m_index;
        KTitleWidget* m_author;
        QLabel* m_title;
        QLabel* m_body;
        QLabel* m_dateTime;
        QLabel* m_rating;    //TODO Use a stars widget

        KTitleWidget *m_replyButton;
        QGridLayout* m_layout;
        int m_depth;
        int m_rowInLayout;

    private:
        bool m_replyEnabled;
};

#endif // COMMENTSVIEWITEM_H
