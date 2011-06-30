/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef GLUON_ENGINE_ACHIEVEMENTSMANAGER_H
#define GLUON_ENGINE_ACHIEVEMENTSMANAGER_H

#include <engine/gluon_engine_export.h>

#include <engine/savable.h>

#include <QtCore/QObject>

namespace GluonEngine
{
    class Achievement;

    /**
     * The AchievementsManager class creates and reads a file, which includes
     * all Achievements of a game and if the user has achieved these. It can
     * be used to display the achievements of a user without creating the
     * whole project.
     * Additionally, a template file without user information can be saved, so
     * that you can show the existing achievements even if the user never played
     * the game.
     * In the future, this class might be used to sync the local achievements with
     * achievements saved on a server.
     */
    class GLUON_ENGINE_EXPORT AchievementsManager : public QObject
    {
            Q_OBJECT
        public:
            AchievementsManager( QObject* parent = 0 );
            virtual ~AchievementsManager();

            /** Load the achievements from this directory */
            void load( const QString& directory );

            /** Read the achievements information from the achievement list */
            void readFromProject( const QList<Achievement*>& achievements );

            /** Delete all user specific information from the achievement */
            void makeTemplate();

            /** Save the achievements information into this directory */
            void save( const QString& directory );

            /** Number of achievements saved in this class */
            int achievementsCount() const;

            /** Get the path of the achievement at index */
            QString achievementPath( int index ) const;

            /** Get the name of the achievement at index */
            QString achievementName( int index ) const;

            /** Get the icon of the achievement */
            QString achievementIcon( int index ) const;

            /** The score you need to get the achievement */
            qlonglong minimumScore( int index ) const;

            /** The current score of the statistic */
            qlonglong currentScore( int index ) const;

            /** Has the user the achievement at index? */
            bool achievementAchieved( int index ) const;
    };
}

#endif // GLUON_ENGINE_ACHIEVEMENTSMANAGER_H
