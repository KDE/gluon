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
     * The use case of this statistic class are statistics where each defined
     * event should give the player only once in a game a score increase.
     * An example would be a game where you get points for visiting a number
     * of special places. Here, the player should only get points if he visits
     * a place the first time.
     */
    class GLUON_ENGINE_EXPORT TasksStatistic : public AbstractStatistic
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::TasksStatistic )
        public:
            Q_INVOKABLE TasksStatistic( QObject* parent = 0 );
            virtual ~TasksStatistic();

            /** How many accomplished tasks do you have? */
            Q_INVOKABLE qlonglong count() const;

            /** Is the task at index accomplished? */
            Q_INVOKABLE bool isAccomplished( qlonglong index ) const;

            /** Mark index as accomplished */
            Q_INVOKABLE void accomplished( qlonglong index );

            /** Mark index as not accomplished */
            Q_INVOKABLE void notAccomplished( qlonglong index );

            /** Mark all indexes as not accomplished */
            Q_INVOKABLE void reset();

            /** Save the accomplished tasks to the database */
            Q_INVOKABLE void commitTasks();

        private:
            class TasksStatisticPrivate;
            TasksStatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::TasksStatistic* )

#endif // GLUON_ENGINE_TASKSSTATISTIC_H
