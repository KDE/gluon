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

#include "statisticscomponent.h"

REGISTER_OBJECTTYPE( GluonEngine, StatisticsComponent )

using namespace GluonEngine;

class StatisticsComponent::StatisticsComponentPrivate
{
    public:
        StatisticsComponentPrivate() : statistic(0) {}
        ~StatisticsComponentPrivate() {}

        Statistic* statistic;
};

StatisticsComponent::StatisticsComponent( QObject* parent )
    : GluonEngine::Component(parent)
    , d( new StatisticsComponentPrivate )
{
}

StatisticsComponent::~StatisticsComponent()
{
    delete d;
}

QString StatisticsComponent::category() const
{
    return QString( "Statistics" );
}

Statistic* StatisticsComponent::statistic() const
{
    return d->statistic;
}

void StatisticsComponent::setStatistic( Statistic* statistic )
{
    d->statistic = statistic;
}

Q_EXPORT_PLUGIN2( gluon_component_statistics, GluonEngine::StatisticsComponent );

#include "statisticscomponent.moc"
