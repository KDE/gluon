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

#include "gluon_player_export.h"

#include <QtCore/QStringList>

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT GameItem : public QObject
    {
            Q_OBJECT
            Q_ENUMS( Status )
        public:
            enum Status
            {
                Downloadable,
                Installed,
                Upgradable
            };

            explicit GameItem( const QString& gameName, const QString& description,
                                   const Status& status, const QString& id, QObject* parent = 0 );
            GameItem( const GameItem& other, QObject* parent = 0 );
            virtual ~GameItem();

            QString gameName() const;
            QString gameDescription() const;
            Status status() const;
            QString id() const;

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONPLAYER_GAMEITEM_H
