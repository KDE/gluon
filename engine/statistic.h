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

#ifndef GLUON_ENGINE_STATISTIC_H
#define GLUON_ENGINE_STATISTIC_H

#include <engine/gluon_engine_export.h>

#include <engine/abstractstatistic.h>

namespace GluonEngine
{
    /**
     * Saves a simple score. Create via StatisticsAsset::createStatistic().
     */
    class GLUON_ENGINE_EXPORT Statistic : public AbstractStatistic
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::Statistic )

            /**
             * The current score in the game. Call commitScore() to compare
             * it with the high score and, if it is better, save it.
             */
            Q_PROPERTY( qlonglong score READ score WRITE setScore )
        public:
            Q_INVOKABLE Statistic( QObject* parent = 0 );
            virtual ~Statistic();

            /**
             * Get the current score
             *
             * @return The current score
             */
            Q_INVOKABLE qlonglong score() const;

            /**
             * Change the score value
             *
             * @param score The new score
             */
            Q_INVOKABLE void setScore( qlonglong score );

            /**
             * Increase score by one
             */
            Q_INVOKABLE void increase();

            /**
             * Decrease score by one
             */
            Q_INVOKABLE void decrease();

            /**
             * Add delta to the current score
             *
             * @param delta The value that should be added to the current score
             */
            Q_INVOKABLE void add( qlonglong delta );

            /**
             * Subtract delta from the current score
             *
             * @param delta The value that should be subtracted from the current score
             */
            Q_INVOKABLE void sub( qlonglong delta );

            /**
             * Set the score to 0. Same as setScore(0)
             *
             * @see setScore
             */
            Q_INVOKABLE void reset();

            /**
             * If the current score is higher than the high score,
             * replace it and write it to the database.
             */
            Q_INVOKABLE virtual void commitScore();

        private:
            class StatisticPrivate;
            StatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Statistic* )

#endif //GLUON_ENGINE_STATISTIC_H
