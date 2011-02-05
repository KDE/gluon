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

#include "listmodel.h"

ListModel::ListModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

QVariant ListModel::data( const QModelIndex& index, int role ) const
{
    switch ( role )
    {
    case Qt::DecorationRole:
        return m_list.at(index.row()).second->pixmap(32, 32);
    case Qt::DisplayRole:
        return m_list.at(index.row()).first;
    }

    return QVariant();
}

int ListModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return 1;
}

int ListModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return m_list.count();
}

QVariant ListModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( section == 0 )
    {
        return QString( "Game" );
    }

    return QAbstractListModel::headerData( section, orientation, role );
}

void ListModel::appendPair( QPair< QString, KIcon* > pair)
{
    m_list.append(pair);
    reset();
}

void ListModel::appendPair( QList< QPair< QString, KIcon* > > pairList)
{
    m_list.append(pairList);
    reset();
}

void ListModel::removePair( QPair< QString, KIcon* > pair)
{
    m_list.removeOne(pair);
    reset();
}

void ListModel::clearPair( )
{
    m_list.clear( );
    reset();
}

// bool ListModel::insertRows( int row, int count, const QModelIndex& parent )
// {
    // if( count != 1 )  //Don't support more than one row at a time
    // {
        // qDebug() << "Can insert only one comment at a time";
        // return false;
    // }

    // if( row != rowCount( parent ) )
    // {
        // qDebug() << "Can only add a comment to the end of existing comments";
        // return false;
    // }

    // beginInsertRows( parent, row, row );
    // m_list.append( parent.internalPointer() );
    // endInsertRows();
    // return true;
// }

