/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GAMESVIEWITEM_H
#define GAMESVIEWITEM_H

// #include <KDE/KPushButton>
#include <KDE/KLocalizedString>
#include <KDE/KIcon>
#include <KDE/KSqueezedTextLabel>

#include <QtGui/QGridLayout>
#include <QtGui/QToolTip>
#include <QtCore/QModelIndex>
#include <QtCore/QEvent>

namespace GluonKDEPlayer
{
    class GamesViewItem : public QWidget
    {
        Q_OBJECT
        public:
            GamesViewItem( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
            GamesViewItem( const GamesViewItem& other, QWidget* parent = 0 );
            GamesViewItem( QString gameName, QString gameDescription, QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
            virtual ~GamesViewItem() {}

            virtual void setModelIndex( const QModelIndex& index );
            QModelIndex modelIndex() const;

        signals:
            void gameSelected( const QModelIndex& index );

        protected:
            void layoutWidgets(const QString& gameName, const QString& gameDescription);
            virtual void mousePressEvent( QMouseEvent* event );

            QModelIndex m_index;
            KSqueezedTextLabel* m_preview;
            KSqueezedTextLabel* m_gameName;
            KSqueezedTextLabel* m_gameDescription;
            QGridLayout* m_layout;
    };
}

Q_DECLARE_METATYPE( GluonKDEPlayer::GamesViewItem )
Q_DECLARE_METATYPE( GluonKDEPlayer::GamesViewItem* )

#endif // GAMESVIEWITEM_H
