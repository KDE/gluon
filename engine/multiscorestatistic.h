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

#ifndef GLUON_ENGINE_MULTISCORESTATISTIC_H
#define GLUON_ENGINE_MULTISCORESTATISTIC_H

#include "gluon_engine_export.h"

#include "statistic.h"

namespace GluonEngine
{
    /**
     * With this class you can save multiple scores of one statistic. Use
     * StatisticAsset::createMultiScoreStatistic to create objects of this class.
     */
    class GLUON_ENGINE_EXPORT MultiScoreStatistic : public Statistic
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::MultiScoreStatistic )

            /**
             * The maximum number of scores you want to save. Set this to 0
             * to save an unlimited number of scores. If the number of scores
             * exceeds the limited, the worst scores will be deleted.
             */
            Q_PROPERTY( int maximumScoreCount READ maximumScoreCount WRITE setMaximumScoreCount )

        public:
            Q_INVOKABLE MultiScoreStatistic( QObject* parent = 0 );
            virtual ~MultiScoreStatistic();

            /**
             * The current maximum number of saved scores
             *
             * @return Maximum number of saved scores
             * @see setMaximumScoreCount
             */
            Q_INVOKABLE int maximumScoreCount() const;

            /**
             * Set the maximum number of saved scores
             *
             * @param count The new maximum
             * @see maximumScoreCount
             */
            Q_INVOKABLE void setMaximumScoreCount( int count );

            /**
             * Get the number of scores currently saved
             *
             * @return number of scores
             */
            Q_INVOKABLE int scoreCount() const;

            /**
             * Get a score
             *
             * @param index The position of the score
             * @return The selected score
             */
            Q_INVOKABLE qlonglong scoreAt( int index ) const;

            /**
             * Return the highest score. Same as scoreAt(0).
             *
             * @return the highest score
             * @see scoreAt
             */
            Q_INVOKABLE qlonglong highScore() const;

            /**
             * Adds the score to the score list, if it is high enough
             *
             * @param score The score you want to add
             */
            Q_INVOKABLE void addScore( qlonglong score );

            /** Reimplemented from Statistic::commitScore. */
            Q_INVOKABLE virtual void commitScore();

        private:
            class MultiScoreStatisticPrivate;
            MultiScoreStatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::MultiScoreStatistic* )

#endif // GLUON_ENGINE_MULTISCORESTATISTIC_H
