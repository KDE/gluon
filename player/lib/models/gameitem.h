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

#ifndef GLUONPLAYER_GAMEITEM_H
#define GLUONPLAYER_GAMEITEM_H

#include "lib/gluon_player_export.h"

#include <QtCore/QStringList>

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT GameItem : public QObject
    {
            Q_OBJECT
            Q_ENUMS( Status )
        public:
            /**
             * Enumerations that describe the status of a game
             */
            enum Status
            {
                Downloadable                    = 1,    ///Game is available on the OCS server
                Local                           = 2,    ///Game is present on the local filesystem
                Installed                       = Downloadable | Local, ///Game was installed from the OCS server
                //TODO: Implement the following roles:
                //Upgradable                      = 4 | Installed,        ///Game's new version is available on the OCS server
                //OwnedByUser                     = 8 | Downloadable      ///Game's owner on the OCS server is the current user
            };

            explicit GameItem( const QString& gameName, const QString& description, int rating,
                               const Status& status, const QString& id, QObject* parent = 0 );
            virtual ~GameItem();

            QString gameName() const;
            void setGameName( const QString& gameName );
            QString gameDescription() const;
            void setGameDescription( const QString& gameDescription );
            int rating() const;
            void setRating( int rating );
            Status status() const;
            void setStatus( Status status );
            QString id() const;

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONPLAYER_GAMEITEM_H
