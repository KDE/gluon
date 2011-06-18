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

#include "statistic.h"

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, Statistic )

class Statistic::StatisticPrivate
{
    public:
        StatisticPrivate() : score(0) {}

        qlonglong score;
};

Statistic::Statistic(QObject* parent)
    : GluonObject(parent)
    , d( new StatisticPrivate() )
{
}

Statistic::~Statistic()
{
    delete d;
}

qlonglong Statistic::score() const
{
    return d->score;
}

void Statistic::setScore(qlonglong score)
{
    d->score = score;
}

void Statistic::increase()
{
    ++(d->score);
}

void Statistic::decrease()
{
    --(d->score);
}

void Statistic::add(qlonglong delta)
{
    d->score += delta;
}

void Statistic::sub(qlonglong delta)
{
    d->score -= delta;
}

#include "statistic.moc"

