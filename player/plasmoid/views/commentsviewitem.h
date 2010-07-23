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

#ifndef COMMENTSVIEWITEM_H
#define COMMENTSVIEWITEM_H

#include <QGraphicsWidget>
#include <QModelIndex>

class QGraphicsGridLayout;
class QGraphicsSceneMouseEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

namespace Plasma
{
    class IconWidget;
    class Label;
}

class CommentsViewItem : public QGraphicsWidget
{
        Q_OBJECT

    public:
        CommentsViewItem(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);
        virtual ~CommentsViewItem();

        virtual void setModelIndex(const QModelIndex &index);
        QModelIndex modelIndex() const;

    protected:
        QModelIndex m_index;
        Plasma::IconWidget *m_author;
        Plasma::Label *m_title;
        Plasma::Label *m_body;
        Plasma::Label *m_dateTime;
        Plasma::Label *m_rating;    //TODO Use a stars widget
        QGraphicsGridLayout *m_layout;

        void layoutWidgets();
        void setToolTips();

};

#endif // COMMENTSVIEWITEM_H
