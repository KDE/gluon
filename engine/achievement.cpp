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

#include <engine/abstractstatistic.h>
#include <engine/statistic.h>
#include <engine/tasksstatistic.h>
#include <engine/assets/graphics/texture/textureasset.h>

#include <QtCore/QVariant>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, Achievement )

class Achievement::AchievementPrivate
{
    public:
        AchievementPrivate() : statistic(0), minimumScore(0), thresholdScore(0),
                               icon(0), hidden(false), dependency(0) {}
        ~AchievementPrivate() {}

        AbstractStatistic* statistic;
        qlonglong minimumScore;
        qlonglong thresholdScore;
        TextureAsset* icon;
        bool hidden;
        Achievement* dependency;

        QList<qlonglong> parseSelection( QString selection );
};

QList<qlonglong> Achievement::AchievementPrivate::parseSelection( QString selection )
{
    QList<qlonglong> result;
    selection.remove(" ");
    // Must be like "2,5-10,12"
    QRegExp regExp("\\d+(-\\d+)?(,\\d+(-\\d+)?)*");
    if( !regExp.exactMatch( selection ) )
        return result;

    QStringList stringList = selection.split(",");
    foreach( const QString& string, stringList )
    {
        if( string.contains("-") )
        {
            QStringList startEnd = string.split("-");
            bool ok1, ok2;
            qlonglong start = startEnd[0].toLongLong(&ok1);
            qlonglong end = startEnd[1].toLongLong(&ok2);
            if( !ok1 || !ok2 )
                return QList<qlonglong>();

            for( qlonglong i = start; i <= end; ++i )
                if( !result.contains(i) )
                    result.append(i);
        }
        else
        {
            bool ok;
            qlonglong number = string.toLongLong(&ok);
            if( !ok )
                return QList<qlonglong>();

            if( !result.contains(number) )
                result.append(number);
        }
    }
    return result;
}

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

    if( !statistic )
        return;

    TasksStatistic* tasksStatistic = qobject_cast<TasksStatistic*>(statistic);
    if( tasksStatistic )
    {
        if( !property( "useSelection" ).isValid() )
        {
            setProperty( "useSelection", false );
            setProperty( "selection", QString("") );
        }
    }
    else
    {
        setProperty( "useSelection", QVariant() );
        setProperty( "selection", QVariant() );
    }
}

qlonglong Achievement::minimumScore() const
{
    return d->minimumScore;
}

void Achievement::setMinimumScore(qlonglong score)
{
    d->minimumScore = score;
}

qlonglong Achievement::thresholdScore() const
{
    return d->thresholdScore;
}

void Achievement::setThresholdScore( qlonglong thresholdScore )
{
    d->thresholdScore = thresholdScore;
}

TextureAsset* Achievement::icon()
{
    return d->icon;
}

void Achievement::setIcon( TextureAsset* icon )
{
    if( d->icon )
        d->icon->deref();
    if( icon )
        icon->ref();
    d->icon = icon;
}

bool Achievement::isHidden()
{
    return d->hidden;
}

void Achievement::setHidden(bool hide)
{
    d->hidden = hide;
}

Achievement* Achievement::dependency() const
{
    return d->dependency;
}

void Achievement::setDependency( Achievement* dependency )
{
    if( d->dependency )
        d->dependency->deref();
    if( dependency )
        dependency->ref();
    d->dependency = dependency;
}

qlonglong Achievement::currentScore() const
{
    if( !d->statistic )
        return 0;

    d->statistic->initialize();

    TasksStatistic* tasksStatistic = qobject_cast<TasksStatistic*>(d->statistic);
    if( tasksStatistic && property( "useSelection" ).toBool() )
    {
        QString selection = property( "selection" ).toString();
        QList<qlonglong> selectionList = d->parseSelection(selection);
        if( !selectionList.isEmpty() )
        {
            QList<qlonglong> accomplishedList = tasksStatistic->array();
            int accomplished = 0;
            foreach( qlonglong task, selectionList )
                if( accomplishedList.contains(task) )
                    ++accomplished;
            int result = accomplished;
            if( minimumScore() > selectionList.count() && d->statistic->value() > selectionList.count() )
                result += qMin( minimumScore(), d->statistic->value() ) - selectionList.count();
            return result;
        }
    }
    return d->statistic->value();
}

bool Achievement::madeProgress() const
{
    return ( currentScore() > d->thresholdScore );
}

bool Achievement::hasDependency() const
{
    return d->dependency;
}

bool Achievement::dependencySatisfied() const
{
    if( !d->dependency )
        return true;

    return d->dependency->achieved();
}

bool Achievement::achieved() const
{
    if( !d->statistic )
        return false;

    d->statistic->initialize();

    if( currentScore() >= d->minimumScore && dependencySatisfied() )
        return true;

    return false;
}

#include "achievement.moc"
