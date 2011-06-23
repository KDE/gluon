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

#include "achievement.h"

#include "abstractstatistic.h"
#include "statistic.h"

#include <QtCore/QVariant>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, Achievement )

class Achievement::AchievementPrivate
{
    public:
        AchievementPrivate() : statistic(0), minimumScore(0) {}
        ~AchievementPrivate() {}

        AbstractStatistic* statistic;
        qlonglong minimumScore;
};

Achievement::Achievement( QObject* parent )
    : GluonObject( parent )
    , d( new AchievementPrivate )
{
}

Achievement::~Achievement()
{
    delete d;
}

AbstractStatistic* Achievement::statistic() const
{
    return d->statistic;
}

void Achievement::setStatistic( AbstractStatistic* statistic )
{
    if( d->statistic )
        d->statistic->deref();

    if( statistic )
        statistic->ref();

    d->statistic = statistic;
}

qlonglong Achievement::minimumScore() const
{
    return d->minimumScore;
}

void Achievement::setMinimumScore(qlonglong score)
{
    d->minimumScore = score;
}

bool Achievement::achieved() const
{
    if( !d->statistic )
        return false;

    if( d->statistic->value() >= d->minimumScore )
        return true;

    return false;
}

#include "achievement.moc"
