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

#include <KDE/KTitleWidget>
#include <KDE/KLocalizedString>
#include <KDE/KIcon>

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtCore/QModelIndex>
#include <QtCore/QEvent>

class GamesViewItem : public QWidget
{
        Q_OBJECT
    public:
        GamesViewItem( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );

        virtual void setModelIndex( const QModelIndex& index );
        QModelIndex modelIndex() const;

    protected slots:
        void playGameActivated();

    signals:
        void gameToPlaySelected( const QModelIndex& index );
        void gameSelected( const QModelIndex& index );

    protected:
        void layoutWidgets();
        void setToolTips();
        virtual void mousePressEvent( QMouseEvent* event );

        QModelIndex m_index;
        KTitleWidget* m_preview;
        QLabel* m_gameName;
        QLabel* m_gameDescription;
        KTitleWidget* m_playButton;
        QGridLayout* m_layout;
};

#endif // GAMESVIEWITEM_H
