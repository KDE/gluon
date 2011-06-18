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

#include <core/gluonobject.h>
#include <core/referencecounter.h>

namespace GluonEngine
{
    /**
     * Saves a simple score. Create via StatisticsAsset::createStatistic().
     */
    class Statistic : public GluonCore::GluonObject, public GluonCore::ReferenceCounter
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::Statistic )

            /** The current score in the game */
            Q_PROPERTY( qlonglong score READ score WRITE setScore )
        public:
            Q_INVOKABLE Statistic( QObject* parent = 0 );
            virtual ~Statistic();

            qlonglong score() const;

        public slots:
            void setScore( qlonglong score );

            /** increase score by one */
            void increase();

            /** decrease score by one */
            void decrease();

            /** add delta to the current score */
            void add( qlonglong delta );

            /** subtract delta from the current score */
            void sub( qlonglong delta );

        private:
            class StatisticPrivate;
            StatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Statistic* )

#endif //GLUON_ENGINE_STATISTIC_H

