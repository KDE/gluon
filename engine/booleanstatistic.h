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

#ifndef GLUON_ENGINE_BOOLEANSTATISTIC_H
#define GLUON_ENGINE_BOOLEANSTATISTIC_H

#include "gluon_engine_export.h"

#include "abstractstatistic.h"

namespace GluonEngine
{
    /**
     * A statistic that can only have two values, 0 and 1. Useful if you want to
     * create an achievement that only tracks a single event, like "kill boss X"
     * or "Finish the game". Use StatisticsAsset::createBooleanStatistic() to
     * create objects of this class.
     */
    class GLUON_ENGINE_EXPORT BooleanStatistic : public AbstractStatistic
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::BooleanStatistic )

            /**
             * The current state of the statistic. Remember to call commit() to
             * save it.
             */
            Q_PROPERTY( bool checked READ isChecked WRITE setChecked );
        public:
            Q_INVOKABLE BooleanStatistic( QObject* parent = 0 );
            virtual ~BooleanStatistic();

            Q_INVOKABLE bool isChecked();
            Q_INVOKABLE void setChecked( bool checked );

            /** set the statistic to 1 */
            Q_INVOKABLE void check();

            /** if the check state is "true", save the statistic to the database */
            Q_INVOKABLE void commit();

        private:
            class BooleanStatisticPrivate;
            BooleanStatisticPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::BooleanStatistic* )

#endif // GLUON_ENGINE_BOOLEANSTATISTIC_H
