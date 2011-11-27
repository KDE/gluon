/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *****************************************************************************/

#ifndef GLUON_COMMENTITEMSVIEWDELEGATE_H
#define GLUON_COMMENTITEMSVIEWDELEGATE_H

#include <KDE/KIcon>
#include <KDE/KWidgetItemDelegate>
#include <KDE/KSqueezedTextLabel>
#include <KDE/KPushButton>
#include <KDE/KLocalizedString>

#include <QtGui/QAbstractItemView>
#include <QtGui/QImage>

#include <QtCore/QList>
#include <QtCore/QModelIndex>

namespace GluonKDEPlayer
{
    class CommentItemsViewDelegate: public KWidgetItemDelegate
    {
            Q_OBJECT
        public:
            explicit CommentItemsViewDelegate( QAbstractItemView* itemView, QObject* parent = 0 );
            virtual ~CommentItemsViewDelegate();

            // paint the item at index with all its attributes shown
            virtual void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;

            // get the list of widgets
            virtual QList<QWidget*> createItemWidgets() const;

            // update the widgets
            virtual void updateItemWidgets( const QList<QWidget*> widgets,
                                            const QStyleOptionViewItem& option,
                                            const QPersistentModelIndex& index ) const;

            virtual QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const;

        signals:
            void commentReplyClicked( const QModelIndex& index );

        protected slots:
            bool eventFilter( QObject* watched, QEvent* event );
            void slotReplyClicked();

        protected:
            QSize m_buttonSize;
    };
}

#endif
