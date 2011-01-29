/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#ifndef GLUON_CREATOR_SCENEMODEL_H
#define GLUON_CREATOR_SCENEMODEL_H

#include <gluoncreator_macros.h>

#include <QtCore/QAbstractItemModel>

namespace GluonEngine
{
    class GameObject;
    class Component;
}

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT SceneModel : public QAbstractItemModel
    {
            Q_OBJECT
        public:
            SceneModel( QObject* parent = 0 );
            ~SceneModel();

            GluonEngine::GameObject* rootGameObject();

            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual QModelIndex parent( const QModelIndex& child ) const;
            virtual QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
            virtual Qt::DropActions supportedDropActions() const;
            virtual Qt::ItemFlags flags( const QModelIndex& index ) const;

            virtual QStringList mimeTypes() const;
            virtual QMimeData* mimeData( const QModelIndexList& indexes ) const;
            virtual bool dropMimeData( const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent );

            virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );

            virtual bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() );
            virtual bool insertRows( int row, const QList<GluonEngine::GameObject*> &children, const QModelIndex& parent = QModelIndex() );

            virtual bool removeRows( int row, int count, const QModelIndex& parent = QModelIndex() );

        public Q_SLOTS:
            void setRootGameObject( GluonEngine::GameObject* obj );
            void deleteGameObject( GluonEngine::GameObject* obj );
            void deleteComponent( GluonEngine::Component* component );

        private:
            class SceneModelPrivate;
            SceneModelPrivate* const d;
    };
}

#endif // GLUON_CREATOR_SCENEMODEL_H
