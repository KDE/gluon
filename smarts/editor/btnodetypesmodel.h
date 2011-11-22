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

#ifndef BTNODETYPESMODEL_H
#define BTNODETYPESMODEL_H

#include <QAbstractListModel>
#include <QList>
class btBrain;
class btEditorNodeType;
class btNodeTypesModelNode;

class btNodeTypesModel : public QAbstractItemModel
{
        Q_OBJECT
    public:
        explicit btNodeTypesModel( btBrain* brain, QObject* parent = 0 );
        ~btNodeTypesModel();

        QMimeData* mimeData( const QModelIndexList& indexes ) const;
        QStringList mimeTypes() const;
        Qt::DropActions supportedDropActions() const;

        QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
        Qt::ItemFlags flags( const QModelIndex& index ) const;
        QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

        QModelIndex index( int row, int column, const QModelIndex& parent ) const;
        QModelIndex parent( const QModelIndex& child ) const;

        int rowCount( const QModelIndex& index ) const;
        int columnCount( const QModelIndex& index ) const;

        btNodeTypesModelNode* nodeFromIndex( const QModelIndex& index ) const;

        bool removeRows( int row, int count, const QModelIndex& index = QModelIndex() );
        bool insertRows( int row, int count, const QModelIndex& parent );

    public Q_SLOTS:
        void newBehaviorTreeTypeAdded( btEditorNodeType* newType );


    private:
        btEditorNodeType* nodeTypeFromIndex( const QModelIndex& index ) const;
        btNodeTypesModelNode* rootNode;

        btNodeTypesModelNode* nodeAction;
        btNodeTypesModelNode* nodeCondition;
        btNodeTypesModelNode* nodeComposite;
        btNodeTypesModelNode* nodeDecorator;
        btNodeTypesModelNode* nodeReference;
        btBrain* m_brain;
};

#endif // BTNODETYPESMODEL_H
