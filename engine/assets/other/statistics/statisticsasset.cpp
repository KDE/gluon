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

#include "statisticsasset.h"

#include <core/gdlserializer.h>
#include <engine/statistic.h>
#include <engine/tasksstatistic.h>
#include <engine/multiscorestatistic.h>
#include <engine/booleanstatistic.h>

REGISTER_OBJECTTYPE( GluonEngine, StatisticsAsset )

using namespace GluonEngine;

class StatisticsAsset::StatisticsAssetPrivate
{
    public:
        StatisticsAssetPrivate() {}
        ~StatisticsAssetPrivate() {}
};

StatisticsAsset::StatisticsAsset(QObject* parent)
    : Asset(parent)
    , d( new StatisticsAssetPrivate() )
{
    savableDirty = true;
}

StatisticsAsset::~StatisticsAsset()
{
    delete d;
}

void StatisticsAsset::writeContents(QIODevice* device)
{
    GluonCore::GluonObjectList objects;
    foreach( QObject* child, children() )
    {
        Statistic* statistic = qobject_cast<Statistic*>(child);
        if( statistic )
            objects.append( statistic );
    }
    GluonCore::GDLSerializer::instance()->write( device, objects );
}

void StatisticsAsset::load()
{
    if( isLoaded() )
        return;

    // As long as we don't unload correctly, make sure we don't load the objects two times
    foreach( QObject* child, children() )
    {
        Statistic* statistic = qobject_cast<Statistic*>(child);
        if( statistic )
            return;
    }

    // Make sure that we don't get into an endless recursion...
    setLoaded( true );

    GluonCore::GluonObjectList list;
    if( !GluonCore::GDLSerializer::instance()->read( absolutePath(), list, gameProject(), this ) )
    {
        setLoaded( false );
        return;
    }

    foreach( GluonCore::GluonObject* object, list )
    {
        AbstractStatistic* statistic = qobject_cast<AbstractStatistic*>(object);
        if( statistic )
            statistic->setParent(this);
    }

    GluonEngine::Asset::load();
}

void StatisticsAsset::unload()
{
    if( !isLoaded() )
        return;

    // This is causing a crash when saving & closing creator
//     QObjectList childList( children() );
//     foreach( QObject* child, childList )
//     {
//         AbstractStatistic* statistic = qobject_cast<AbstractStatistic*>(child);
//         if( statistic )
//             statistic->deleteLater();
//     }

    GluonEngine::Asset::unload();
}

void StatisticsAsset::setFile(const QString& newFile)
{
    GluonEngine::Asset::setFile( newFile );

    if( isLoaded() )
        reload();
}

void StatisticsAsset::createStatistic()
{
    Statistic* newStatistic = new Statistic(this);
    newStatistic->setName(tr("New Statistic"));
    savableDirty = true;
}

void StatisticsAsset::createTasksStatistic()
{
    TasksStatistic* newStatistic = new TasksStatistic(this);
    newStatistic->setName(tr("New Tasks Statistic"));
    savableDirty = true;
}

void StatisticsAsset::createMultiScoreStatistic()
{
    MultiScoreStatistic* newStatistic = new MultiScoreStatistic(this);
    newStatistic->setName(tr("New Multi-Score Statistic"));
    savableDirty = true;
}

void StatisticsAsset::createBooleanStatistic()
{
    BooleanStatistic* newStatistic = new BooleanStatistic(this);
    newStatistic->setName( tr("New Boolean Statistic") );
    savableDirty = true;
}

void StatisticsAsset::populateMetaInfo(GluonCore::MetaInfo* info)
{
    info->setDefaultExtension( "gluonstatistics" );
}

bool StatisticsAsset::shouldSerializeChildren() const
{
    return false;
}
