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

#ifndef GLUON_PLAYER_GAMEITEMSMODEL_H
#define GLUON_PLAYER_GAMEITEMSMODEL_H

#include "lib/gluon_player_export.h"

#include "gameviewitem.h"

#include <QtCore/QAbstractListModel>

namespace Attica
{
    class BaseJob;
}

namespace GluonPlayer
{
    class GameDetailItem;

    /**
     *\brief Model which contains a list of the installed games
     *
     * This model can be used to obtain a list of all the installed games
     * Use the different roles of the model to obtain required properties.
     *
     */

    class GLUON_PLAYER_EXPORT GameItemsModel : public QAbstractListModel
    {
            Q_OBJECT
            Q_PROPERTY( int downloadableCount READ downloadableCount NOTIFY downloadableCountChanged )
            Q_PROPERTY( int upgradableCount READ upgradableCount NOTIFY upgradableCountChanged )

        public:
            enum GameItemsModelRoles
            {
                ProjectNameRole = Qt::UserRole + 1,
                ProjectDescriptionRole,
                ProjectDirPathRole,
                ProjectFilePathRole,
                ScreenshotUrlsRole,
                StatusRole,
                ProjectIDRole,

                // Downloadable Game item roles
                ProjectNameDownloadableRole,
                ProjectDescriptionDownloadableRole,
                ProjectDirPathDownloadableRole,
                ProjectFilePathDownloadableRole,
                ScreenshotUrlsDownloadableRole,
                StatusDownloadableRole,
                ProjectIDDownloadableRole,
            };

            explicit GameItemsModel( QObject* parent = 0 );
            virtual ~GameItemsModel();

            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;

            int downloadableCount() const;
            int upgradableCount() const;

            GameViewItem* installedGameInfo( int row );

        Q_SIGNALS:
            void downloadableCountChanged();
            void upgradableCountChanged();

        protected Q_SLOTS:
            void processFetchedGameList ();

        private:
            void fetchGamesList();

            class Private;
            Private* const d;
    };
}

#endif // GLUON_PLAYER_GAMEITEMSMODEL_H
