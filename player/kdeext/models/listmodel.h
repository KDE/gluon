/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUONPLAYER_LISTMODEL_H
#define GLUONPLAYER_LISTMODEL_H

#include <KDE/KIcon>
#include <KDE/KDebug>

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QVariant>
#include <QtCore/QAbstractListModel>

/**
 *\brief Model which contains a list of the main entries
 *
 * This model can be used to obtain a list of all the main entires
 * Use the different columns of the model to obtain required properties.
 *
 */
class ListModel : public QAbstractListModel
{
    public:
        explicit ListModel( QObject* parent = 0 );
        virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
        virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
        virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
        virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        // virtual bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() );

        void appendPair( QPair< QString, KIcon* > pair );
        void appendPair( QList< QPair< QString, KIcon* > > pairList );
        void removePair( QPair< QString, KIcon* > pair );
        void clearPair( );

    private:
        QList< QPair< QString, KIcon* > > m_list;
};

#endif // GLUONPLAYER_LISTMODEL_H
