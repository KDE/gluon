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

#include "abstractstatistic.h"

#include <engine/gameproject.h>
#include <engine/databasemanager.h>
#include <core/directoryprovider.h>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, AbstractStatistic )

class AbstractStatistic::AbstractStatisticPrivate
{
    public:
        AbstractStatisticPrivate() 
            : isDatabaseOpen(false)
            , id(0)
            , value(0)
        {
        }

        ~AbstractStatisticPrivate() 
        {
        }

        QString userName;
        bool isDatabaseOpen;
        int id;
        QString database;

        qlonglong value;
        QList<qlonglong> array;
};

AbstractStatistic::AbstractStatistic(QObject* parent)
    : GluonObject(parent)
    , d( new AbstractStatisticPrivate )
{
}

AbstractStatistic::~AbstractStatistic()
{
    delete d;
}

bool AbstractStatistic::isDatabaseOpen() const
{
    return d->isDatabaseOpen;
}

void AbstractStatistic::initialize()
{
    if( d->isDatabaseOpen )
        return;

    GameProject* p = qobject_cast<GameProject*>(gameProject());
    if( !p )
        return;

    QString path = GluonCore::DirectoryProvider::instance()->userDirectory("data");
    QString gameName = p->name();
    QString statisticName = name();

    if( d->userName.isEmpty() )
        d->userName = p->userName();
    connect(p, SIGNAL(nameChanged(QString,QString)), this, SLOT(invalidate()) );
    d->database = DatabaseManager::instance()->openStatisticDatabase(path, d->userName, gameName);
    if( d->database.isEmpty() )
        return;

    d->id = DatabaseManager::instance()->statisticEntry(d->database, statisticName);
    if( d->id == -1 )
        return;

    d->isDatabaseOpen = true;

    d->value = DatabaseManager::instance()->statisticScore(d->database, d->id);
    d->array = DatabaseManager::instance()->statisticArray(d->database, d->id);
}

void AbstractStatistic::cleanup()
{

}

void AbstractStatistic::setName(const QString& newName)
{
    GluonCore::GluonObject::setName(newName);
    d->isDatabaseOpen = false;
}

void AbstractStatistic::invalidate()
{
    d->isDatabaseOpen = false;
}

qlonglong AbstractStatistic::value() const
{
    return d->value;
}

void AbstractStatistic::setValue(qlonglong value)
{
    d->value = value;
}

QList< qlonglong > AbstractStatistic::array() const
{
    return d->array;
}

void AbstractStatistic::setArray( const QList< qlonglong >& list )
{
    d->array = list;
}

void AbstractStatistic::arrayAppend( qlonglong value )
{
    d->array.append( value );
}

void AbstractStatistic::removeAt(int index)
{
    d->array.removeAt(index);
}

void AbstractStatistic::commit()
{
    if( !d->isDatabaseOpen )
        return;

    DatabaseManager::instance()->setStatisticScore(d->database, d->id, d->value);
    DatabaseManager::instance()->setStatisticArray(d->database, d->id, d->array);
}

#include "abstractstatistic.moc"
