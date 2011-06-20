/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_ALLGAMEITEMSMODEL_H
#define GLUONPLAYER_ALLGAMEITEMSMODEL_H

#include "gluon_player_export.h"

#include <QtCore/QAbstractListModel>
#include <QtCore/QStringList>
#include <QtCore/QMultiMap>
#include <QtCore/QDir>

namespace Attica
{
    class BaseJob;
}

namespace GluonPlayer
{
    class OcsGameDetails;

    class GLUON_PLAYER_EXPORT AllGameItemsModel : public QAbstractListModel
    {
            Q_OBJECT

        public:
            enum GameItemsModelRoles
            {
                GameNameRole = Qt::UserRole + 1,
                GameDescriptionRole,
                StatusRole,
                IDRole
            };

            explicit AllGameItemsModel( QObject* parent = 0 );
            virtual ~AllGameItemsModel();

            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;

        protected Q_SLOTS:
            void processFetchedGamesList (QList<OcsGameDetails*> comments);

        private:
            void fetchGamesList();

            class Private;
            Private* const d;
    };
}

#endif // GLUONPLAYER_ALLGAMEITEMSMODEL_H
