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

#include "multiscorestatistic.h"

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, MultiScoreStatistic )

class MultiScoreStatistic::MultiScoreStatisticPrivate
{
    public:
        MultiScoreStatisticPrivate() : maximumScoreCount(10) {}
        ~MultiScoreStatisticPrivate() {}

        int maximumScoreCount;
};

MultiScoreStatistic::MultiScoreStatistic(QObject* parent)
    : Statistic(parent)
    , d( new MultiScoreStatisticPrivate() )
{
}

MultiScoreStatistic::~MultiScoreStatistic()
{
    delete d;
}

int MultiScoreStatistic::maximumScoreCount() const
{
    return d->maximumScoreCount;
}

void MultiScoreStatistic::setMaximumScoreCount( int count )
{
    if( count < 0 )
        return;

    d->maximumScoreCount = count;
}

int MultiScoreStatistic::scoreCount() const
{
    return array().count();
}

qlonglong MultiScoreStatistic::scoreAt(int index) const
{
    return array().value( index );
}

qlonglong MultiScoreStatistic::highScore() const
{
    return scoreAt(0);
}

void MultiScoreStatistic::addScore(qlonglong score)
{
    QList<qlonglong> tmpArray = array();
    bool inserted = false;
    for( QList<qlonglong>::iterator iter = tmpArray.begin(); iter != tmpArray.end(); ++iter )
    {
        if( *iter < score )
        {
            tmpArray.insert( iter, score );
            inserted = true;
            break;
        }
    }
    if( !inserted )
        tmpArray.append( score );

    if( d->maximumScoreCount != 0 )
        while( tmpArray.count() > d->maximumScoreCount )
            tmpArray.removeLast();

    setArray(tmpArray);
    setValue(tmpArray[0]);
    commit();
}

void MultiScoreStatistic::commitScore()
{
    addScore( score() );
}

#include "multiscorestatistic.moc"
