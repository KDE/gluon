/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUON_SMARTS_BTNODEMODEL_H
#define GLUON_SMARTS_BTNODEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QVariant>
#include <QtCore/QModelIndex>

class btEditorNodeType;

class btnodemodel : public QAbstractTableModel
{
        Q_OBJECT
        Q_PROPERTY( QString name READ name WRITE setName )
        Q_PROPERTY( QString description READ description WRITE setDescription )
        Q_PROPERTY( QString classname READ classname WRITE setClassname )

    public:
        explicit btnodemodel( btEditorNodeType* nodetype, QObject* parent = 0 );
        int rowCount( const QModelIndex& parent = QModelIndex() ) const;
        int columnCount( const QModelIndex& parent = QModelIndex() ) const;
        QVariant data( const QModelIndex& index, int role ) const;
        QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        Qt::ItemFlags flags( const QModelIndex& index ) const;
        bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );

        bool insertRows( int position, int rows, const QModelIndex& index = QModelIndex() );
        bool removeRows( int position, int rows, const QModelIndex& index = QModelIndex() );

        QString name() const;
        void setName( QString name );

        QString description() const;
        void setDescription( QString description );

        QString classname() const;
        void setClassname( QString classname );

    Q_SIGNALS:
        void updatePropertyWidget();

    private:
        btEditorNodeType*      node;
};

#endif // GLUON_SMARTS_BTNODEMODEL_H
