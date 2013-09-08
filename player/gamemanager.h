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


#ifndef GLUONPLAYER_GAMEMANAGER_H
#define GLUONPLAYER_GAMEMANAGER_H

#include <core/singleton.h>

namespace GluonPlayer
{
    class GameManager : public GluonCore::Singleton<GameManager>
    {
            Q_OBJECT
            Q_PROPERTY( QObject* allGamesModel READ allGamesModel CONSTANT )
            Q_PROPERTY( QObject* downloadableGamesModel READ downloadableGamesModel CONSTANT )
            Q_PROPERTY( QObject* installedGamesModel READ installedGamesModel CONSTANT )
            GLUON_SINGLETON( GameManager )

        public:
            QObject* allGamesModel() const;
            QObject* downloadableGamesModel() const;
            QObject* installedGamesModel() const;

        private:
            class Private;
            Private * const d;
    };
}

#endif // GLUONPLAYER_GAMEMANAGER_H
