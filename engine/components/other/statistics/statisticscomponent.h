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

#ifndef GLUON_ENGINE_STATISTICSCOMPONENT
#define GLUON_ENGINE_STATISTICSCOMPONENT

#include <engine/component.h>
#include <engine/abstractstatistic.h>

namespace GluonEngine
{
    /**
     * Connect a game object to a statistic, so that the statistic can be changed
     * through scripting.
     */
    class StatisticsComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::StatisticsComponent )
            Q_INTERFACES( GluonEngine::Component )

            /**
             * The statistic which this component is connected to. The statistic
             * should be a sub class of AbstractStatistic.
             */
            Q_PROPERTY( GluonEngine::AbstractStatistic* statistic READ statistic WRITE setStatistic )

            Q_CLASSINFO( "org.gluon.category", "Social Integration" )
            Q_CLASSINFO( "org.gluon.icon", "text-mathml" )

        public:
            Q_INVOKABLE StatisticsComponent( QObject* parent = 0 );
            virtual ~StatisticsComponent();

            /** Reimplemented from Component::category() */
            virtual QString category() const;

            /** Reimplemented from Component::initialize() */
            virtual void initialize();

            /** Reimplemented from Component::cleanup() */
            virtual void cleanup();
            AbstractStatistic* statistic() const;

        public Q_SLOTS:
            void setStatistic( AbstractStatistic* statistic );

        private:
            class StatisticsComponentPrivate;
            StatisticsComponentPrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::StatisticsComponent* )

#endif //GLUON_ENGINE_STATISTICSCOMPONENT
