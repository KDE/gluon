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

#ifndef GLUON_ENGINE_ACHIEVEMENT_H
#define GLUON_ENGINE_ACHIEVEMENT_H

#include "gluon_engine_export.h"

#include <core/gluonobject.h>
#include <core/referencecounter.h>

namespace GluonEngine
{
    class AbstractStatistic;
    class Asset;

    /**
     * The Achievement class is connected to one statistic. If the statistic reaches a
     * certain score, achieved() returns true.
     * If you assign a TasksStatistic to the statistic property, you will get two new
     * properties (useSelection and Selection) which you can use to define which task
     * indices should count towards the score. The selection is defined as a string
     * containing numbers or ranges of numbers (like 5-10) separated with commas.
     * If the minimum score is higher than the selection count, other task indices are
     * used for the difference.
     */
    class GLUON_ENGINE_EXPORT Achievement : public GluonCore::GluonObject, public GluonCore::ReferenceCounter
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::Achievement )

            /**
             * The statistic the achievement is connected to
             */
            Q_PROPERTY( GluonEngine::AbstractStatistic* statistic READ statistic WRITE setStatistic )

            /**
             * The score you need to get the achievement
             */
            Q_PROPERTY( qlonglong minimumScore READ minimumScore WRITE setMinimumScore )

            /**
             * An icon that represents the achievement.
             */
            Q_PROPERTY( GluonEngine::Asset* icon READ icon WRITE setIcon );

            /**
             * The achievement is only shown if this achievement is achieved.
             */
            Q_PROPERTY( GluonEngine::Achievement* dependency READ dependency WRITE setDependency )

        public:
            Q_INVOKABLE Achievement( QObject* parent = 0 );
            virtual ~Achievement();

            /**
             * Get the statistic that is currently connected to this achievement.
             * @return The statistic, or 0, if no statistic is connected to the achievement.
             * @see setStatistic
             */
            AbstractStatistic* statistic() const;

            /**
             * Set the statistic this achievement is connected to.
             * @param statistic The statistic, or 0, if this achievement should be connected to no statistic.
             * @see statistic
             */
            void setStatistic( AbstractStatistic* statistic );

            /**
             * Get the minimum score the user has to get to have this achievement achieved.
             * @returns The minimum score, which is 0 by default.
             * @see setMinimumScore
             */
            qlonglong minimumScore() const;

            /**
             * Set the minimum score the user has to get to have this achievement achieved.
             * @param score the new minimum score
             * @see minimumScore
             */
            void setMinimumScore( qlonglong score );

            /**
             * Get the icon which represents the achievement.
             * @return An asset which contains an icon, or 0, if no such icon asset is set.
             * @see setIcon
             */
            Asset* icon();

            /**
             * Set the icon which represents the achievement.
             * @param icon An asset that contains a file which can be shown by QIcon, or 0.
             * @see icon
             */
            void setIcon( Asset* icon );

            // TODO: make more dependencies possible
            /**
             * Get the dependency for this achievement.
             * @returns The dependency, if there is one, or 0.
             * @see setDependency
             */
            Achievement* dependency() const;

            /**
             * Set the dependency for this achievement.
             * @param dependency An achievement that should be used as dependency, or 0, if this achievement
             *                   should not have a dependency.
             * @see dependency
             */
            void setDependency( Achievement* dependency );

            /**
             * Get the current score of the user. The current score depends on the statistic.
             * @return The current score or 0, if the statistic property is not set.
             * @see statistic, setStatistic
             */
            qlonglong currentScore() const;

            /**
             * Check whether the achievement has a dependency.
             * @returns true if the achievement has a dependency, otherwise return false.
             * @see setDependency, dependency
             */
            bool hasDependency() const;

            /**
             * Check whether the dependency achievement is achieved.
             * @return Achieved status of the dependency, or true, if there is no dependency
             * @see setDependency, dependency
             */
            bool dependencySatisfied() const;

            /**
             * Check whether the statistic has achieved the goal.
             * @returns true, if the current score is equal or greater than the minimum score, otherwise false.
             * @see currentScore, minimumScore, setMinimumScore
             */
            bool achieved() const;

            /** Reimplemented from GluonCore::GluonObject::sanitize() */
            virtual void sanitize();

        private:
            class AchievementPrivate;
            AchievementPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Achievement* )

#endif //GLUON_ENGINE_ACHIEVEMENT_H
