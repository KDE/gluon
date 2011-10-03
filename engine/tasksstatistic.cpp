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

#include "tasksstatistic.h"

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, TasksStatistic )

class TasksStatistic::TasksStatisticPrivate
{
    public:
        TasksStatisticPrivate() {}
        ~TasksStatisticPrivate() {}

        QList<qlonglong> array;
};

TasksStatistic::TasksStatistic(QObject* parent)
    : AbstractStatistic(parent)
    , d( new TasksStatisticPrivate() )
{
}

TasksStatistic::~TasksStatistic()
{
    delete d;
}

qlonglong TasksStatistic::count() const
{
    return d->array.count();
}

bool TasksStatistic::isAccomplished( qlonglong index ) const
{
    return d->array.contains( index );
}

void TasksStatistic::markAsAccomplished( qlonglong index )
{
    setAccomplishedStatus( index, true );
}

void TasksStatistic::markAsNotAccomplished( qlonglong index )
{
    setAccomplishedStatus( index, false );
}

void TasksStatistic::setAccomplishedStatus( qlonglong index, bool status )
{
    if( status )
    {
        if( d->array.contains( index ) )
            return;

        QMutableListIterator<qlonglong> i( d->array );
        while( i.hasNext() )
        {
            qlonglong val = i.next();
            if( val > index )
            {
                i.insert( index );
                return;
            }
        }
        d->array.append( index );
    }
    else
    {
        d->array.removeAll( index );
    }
}

void TasksStatistic::reset()
{
    d->array.clear();
}

void TasksStatistic::commitTasks()
{
    if( d->array.count() > value() )
    {
        setArray( d->array );
        setValue( d->array.count() );
        commit();
    }
}

#include "tasksstatistic.moc"
