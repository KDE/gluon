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

#ifndef GLUON_ENGINE_TASKSSTATISTIC_H
#define GLUON_ENGINE_TASKSSTATISTIC_H

#include "gluon_engine_export.h"
#include "abstractstatistic.h"

namespace GluonEngine
{
    /**
     * This statistics class is used for a statistic where each defined event
     * should only give the player a score increase once per game.
     * An example would be a game where you get points for visiting a number
     * of special places. The player should only get points if a place is
     * visited for the first time.
     */
    class GLUON_ENGINE_EXPORT TasksStatistic : public AbstractStatistic
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::TasksStatistic )

        public:
            Q_INVOKABLE TasksStatistic( QObject* parent = 0 );
            virtual ~TasksStatistic();

            /**
             * Get the number of accomplished tasks of this user
             *
             * @return The number of accomplished tasks
             */
            Q_INVOKABLE qlonglong count() const;

            /**
             * Check whether one task is accomplished
             *
             * @param index The task to check
             * @return true, if the task is accomplished, false otherwise
             * @see setAccomplishedStatus, markAsAccomplished, markAsNotAccomplished
             */
            Q_INVOKABLE bool isAccomplished( qlonglong index ) const;

            /**
             * Mark a task as accomplished
             *
             * @param index the accomplished task
             * @see markAsNotAccomplished, setAccomplishedStatus, isAccomplished
             */
            Q_INVOKABLE void markAsAccomplished( qlonglong index );

            /**
             * Mark a task as not accomplished
             *
             * @param index the not accomplished task
             * @see markAsAccomplished, setAccomplishedStatus, isAccomplished
             */
            Q_INVOKABLE void markAsNotAccomplished( qlonglong index );

            /**
             * Set whether the task is accomplished or not
             *
             * @param index the task you want to change
             * @param status true, if the task should be marked as accomplished,
             *               false, if the task should be marked as not accomplished
             * @see markAsAccomplished, markAsNotAccomplished, isAccomplished
             */
            Q_INVOKABLE void setAccomplishedStatus( qlonglong index, bool status );

            /**
             * Mark all indexes as not accomplished
             */
            Q_INVOKABLE void reset();

            /**
             * Save the accomplished tasks to the database
             */
            Q_INVOKABLE void commitTasks();

        private:
            class TasksStatisticPrivate;
            TasksStatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::TasksStatistic* )

#endif // GLUON_ENGINE_TASKSSTATISTIC_H
