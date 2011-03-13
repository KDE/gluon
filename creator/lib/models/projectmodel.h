/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUON_CREATOR_PROJECTMODEL_H
#define GLUON_CREATOR_PROJECTMODEL_H

#include "gluoncreator_macros.h"

#include <QtCore/QAbstractItemModel>

namespace GluonCore
{
    class GluonObject;
}
namespace GluonEngine
{
    class GameProject;
    class GameObject;
}

namespace GluonCreator
{

    class GLUONCREATOR_EXPORT ProjectModel : public QAbstractItemModel
    {
            Q_OBJECT
        public:
            ProjectModel( QObject* parent = 0 );
            ~ProjectModel();

            GluonEngine::GameProject* project();

            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual QModelIndex parent( const QModelIndex& child ) const;
            virtual QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
            QModelIndex objectToIndex( GluonCore::GluonObject* object ) const;
            int objectRow( GluonCore::GluonObject* object ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

            virtual Qt::DropActions supportedDropActions() const;
            virtual Qt::ItemFlags flags( const QModelIndex& index ) const;
            virtual QStringList mimeTypes() const;
            virtual QMimeData* mimeData( const QModelIndexList& indexes ) const;
            virtual bool dropMimeData( const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent );
            virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );
            virtual bool removeRows( int row, int count, const QModelIndex& parent );

            void addChild( QObject* newChild, QModelIndex& parent );

        public Q_SLOTS:
            void setProject( GluonEngine::GameProject* project );

        private:
            class ProjectModelPrivate;
            ProjectModelPrivate* const d;

    };

}

#endif // GLUON_CREATOR_PROJECTMODEL_H
