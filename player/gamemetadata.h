/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <shaan7in@gmail.com>
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


#ifndef GLUONPLAYER_GAMEMETADATA_H
#define GLUONPLAYER_GAMEMETADATA_H

#include <QtCore/QObject>

namespace GluonPlayer
{
    class GameMetadata : public QObject
    {
            Q_OBJECT
            Q_PROPERTY( QString gameId READ gameId WRITE setGameId NOTIFY gameIdChanged )
            Q_PROPERTY( QString gameName READ gameName NOTIFY gameNameChanged )
            Q_PROPERTY( QString gameDescription READ gameDescription NOTIFY gameDescriptionChanged )

        public:
            explicit GameMetadata( QObject* parent = 0 );
            virtual ~GameMetadata();

            QString gameId() const;
            void setGameId( const QString& gameId );

            QString gameName() const;
            QString gameDescription() const;

        signals:
            void gameIdChanged();
            void gameNameChanged();
            void gameDescriptionChanged();

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONPLAYER_GAMEMETADATA_H
