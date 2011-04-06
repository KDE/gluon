/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUONPLAYER_GAMEITEMSMODEL_H
#define GLUONPLAYER_GAMEITEMSMODEL_H

#include "gluon_player_export.h"

#include "gameviewitem.h"

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
            enum GameItemsModelRoles {
                GameNameRole = Qt::UserRole + 1,
                GameDescriptionRole,
                ProjectDirNameRole,
                ProjectFileNameRole,
                ScreenshotUrlsRole,
                StatusRole,
                IDRole,

                // Downloadable Game item roles
                GameNameDownloadableRole,
                GameDescriptionDownloadableRole,
                ProjectDirNameDownloadableRole,
                ProjectFileNameDownloadableRole,
                ScreenshotUrlsDownloadableRole,
                StatusDownloadableRole,
                IDDownloadableRole,
            };

            explicit GameItemsModel( QObject* parent = 0 );
            virtual ~GameItemsModel() {}

            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;

			int downloadableCount() const;
			int upgradableCount() const;

		signals:
			void downloadableCountChanged();
			void upgradableCountChanged();

        protected slots:
            void providersUpdated();
            void processFetchedGamesList( Attica::BaseJob* job);

        private:
            void fetchGamesList();

            QMultiMap<GameViewItem::Status, GameViewItem*> m_gameViewItems;


    };
}

#endif // GLUONPLAYER_GAMEITEMSMODEL_H
