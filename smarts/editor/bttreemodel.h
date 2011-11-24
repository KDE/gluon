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

#ifndef GLUON_SMARTS_BTTREEMODEL_H
#define GLUON_SMARTS_BTTREEMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QString>

class btEditorNode;
class btBrain;

class btTreeModel : public QAbstractItemModel
{
        Q_OBJECT
        Q_PROPERTY( QString name READ name WRITE setName )
        Q_PROPERTY( QString description READ description WRITE setDescription )

    public:
        explicit btTreeModel( QObject* parent = 0, btBrain* containingBrain = 0 );
        ~btTreeModel();

        void setRootNode( btEditorNode* newRoot );
        btEditorNode* rootNode() const;

        QModelIndex index( int row, int column, const QModelIndex& parent ) const;
        QModelIndex parent( const QModelIndex& child ) const;

        int rowCount( const QModelIndex& parent ) const;
        int columnCount( const QModelIndex& parent ) const;
        QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
        QVariant data( const QModelIndex& index, int role ) const;
        bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );

        Qt::ItemFlags flags( const QModelIndex& index ) const;
        Qt::DropActions supportedDropActions() const;
        QStringList mimeTypes() const;
        bool dropMimeData( const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent );
        QMimeData* mimeData( const QModelIndexList& indexes ) const;

        bool removeRows( int position, int rows, const QModelIndex& parent );

        QString name() const;
        void setName( QString name );

        QString description() const;
        void setDescription( QString description );

    public Q_SLOTS:
        void updateTreeModel();

    Q_SIGNALS:
        void addRemoveBTNode();

    private:
        bool moving;

        QString m_name;
        QString m_description;

        btEditorNode* nodeFromIndex( const QModelIndex& index ) const;

        btEditorNode* m_rootNode;
        btBrain* brain;
};

#endif // GLUON_SMARTS_BTTREEMODE_H
