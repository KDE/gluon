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

#include "gluon_engine_export.h"

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

            /**
             * Save the achievements information into this directory
             * @param directory The directory where the data should be saved
             * @see load
             */
            void save( const QString& directory );

            /**
             * Load the achievements from this directory. If no data is found,
             * achievementsCount returns 0.
             * @param directory The directory where the data can be found
             * @see save
             */
            void load( const QString& directory );

            /**
             * Read the achievements information from the achievement list.
             * @param achievements A list of achievements
             */
            void readFromProject( const QList<Achievement*>& achievements );

            /**
             * Delete all user specific information from the achievement.
             */
            void makeTemplate();

            /**
             * Get the number of achievements this manager contains.
             * @returns The number of achievements
             */
            int achievementsCount() const;

            /**
             * Get the path of the achievement at index. Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @return The path where you can find the achievement
             * @see achievementsCount
             */
            QString achievementPath( int index ) const;

            /**
             * Get the name of the achievement at index. Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @return The name of the achievement
             * @see achievementsCount
             */
            QString achievementName( int index ) const;

            /**
             * Get the description of the achievement at index. Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @return The description of the chosen achievement
             */
            QString achievementDescription( int index ) const;

            /**
             * Get the icon of the achievement. Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @return the relative path of the file used as icon
             * @see achievementsCount
             */
            QString achievementIcon( int index ) const;

            /**
             * The score you need to get the achievement. Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @return The minimum score
             * @see achievementsCount
             */
            qlonglong minimumScore( int index ) const;

            /**
             * The current score of the statistic. Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @return The current score
             * @see achievementsCount
             */
            qlonglong currentScore( int index ) const;

            /**
             * Check whether the user has the dependency achievement achieved? Index must
             * be a valid index position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @returns true if the dependency is satisfied, false otherwise
             * @see achievementsCount
             */
            bool dependencySatisfied( int index ) const;

            /**
             * Check whether the user has the achievement at index? Index must be a valid index
             * position, i.e. between 0 and achievementsCount()-1.
             * @param index A valid index
             * @returns true if the achieved is achieved, false otherwise
             * @see achievementsCount
             */
            bool achievementAchieved( int index ) const;
    };
}

#endif // GLUON_ENGINE_ACHIEVEMENTSMANAGER_H
