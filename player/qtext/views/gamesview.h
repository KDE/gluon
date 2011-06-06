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

#ifndef GAMESVIEW_H
#define GAMESVIEW_H

#include "abstractitemview.h"

#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include <QtCore/QModelIndex>

class QAbstractItemModel;

class GamesView : public AbstractItemView
{
        Q_OBJECT
    public:
        explicit GamesView( QWidget* parent = 0, Qt::WindowFlags wFlags = 0 );
        virtual void setModel( QAbstractItemModel* model );

    protected:
        QLabel* m_itemBackground;

        bool eventFilter( QObject* obj, QEvent* event );

    signals:
        void gameToPlaySelected( const QModelIndex& index );
        void gameSelected( const QModelIndex& index );
};

#endif // GAMESVIEW_H
