/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#ifndef GLUONPLAYER_INSTALLEDGAMESMODEL_H
#define GLUONPLAYER_INSTALLEDGAMESMODEL_H

#include <QtGui/QSortFilterProxyModel>

#include "../gluon_player_export.h"

namespace GluonPlayer
{

    class GLUON_PLAYER_EXPORT InstalledGamesModel : public QSortFilterProxyModel
    {
            Q_OBJECT
            Q_PROPERTY(QObject* sourceModel READ sourceModel WRITE setSourceModel NOTIFY sourceModelChanged)

        public:
            InstalledGamesModel( QObject* parent = 0 );
            explicit InstalledGamesModel( QAbstractItemModel *sourceModel, QObject* parent = 0 );
            Q_INVOKABLE QVariant gameData( int gameIndex, QByteArray role );

            virtual void setSourceModel(QObject* sourceModel);

        Q_SIGNALS:
            void sourceModelChanged();

        protected:
            virtual bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const;
    };

}

#endif // GLUONPLAYER_INSTALLEDGAMESMODEL_H
