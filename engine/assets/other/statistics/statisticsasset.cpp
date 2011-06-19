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

#include <engine/statistic.h>
#include <core/gdlhandler.h>

#include <QtGui/QAction>

REGISTER_OBJECTTYPE( GluonEngine, StatisticsAsset )

using namespace GluonEngine;

class StatisticsAsset::StatisticsAssetPrivate
{
    public:
        StatisticsAssetPrivate() {}
        ~StatisticsAssetPrivate() {}

        QList<QAction*> actions;
};

StatisticsAsset::StatisticsAsset(QObject* parent)
    : Asset(parent)
    , d( new StatisticsAssetPrivate() )
{
    QAction* newStatistic = new QAction( tr("New Statistic"), this );
    connect( newStatistic, SIGNAL(triggered()), this, SLOT(createStatistic()) );
    d->actions.append(newStatistic);
    savableDirty = true;
}

StatisticsAsset::~StatisticsAsset()
{
    delete d;
}

QString StatisticsAsset::contentsToGDL()
{
    /* Due to a bug in GDL, it can't handle more than one top level
     * item. This workaround creates a temporary object which takes
     * the statistics as children.
     * TODO: remove as soon as the GDL bug is fixed
     */
    GluonCore::GluonObject object;
    object.setName( "temporaryObject" );
    foreach( QObject* child, children() )
    {
        Statistic* obj = qobject_cast<Statistic*>(child);
        if( obj )
            obj->setParent(&object);
    }
    QString result = GluonCore::GDLHandler::instance()->toGDL(&object);
    foreach( QObject* child, object.children() )
    {
        Statistic* obj = qobject_cast<Statistic*>(child);
        if( obj )
            obj->setParent(this);
    }
    return result;
}

const QList< AssetTemplate* > StatisticsAsset::templates()
{
    QList< AssetTemplate* > templates;
    templates.append( new AssetTemplate( tr("Statistics Asset"), "statistics_template.gluonstatistics", "statistics", this ) );
    return templates;
}

QList< QAction* > StatisticsAsset::actions() const
{
    return d->actions;
}

void StatisticsAsset::setFile(const QUrl& newFile)
{
    /* This function will extract the statistic instances
     * from the file only the first time. If it would read
     * the file every time this function is called, it would
     * add the same instance multiple times. If I try do delete
     * all statistics before, gluon creator crashes.
     */
    GluonEngine::Asset::setFile(newFile);
    foreach( QObject* child, children() )
    {
        Statistic* statistic = qobject_cast<Statistic*>(child);
        if( statistic )
            return;
    }
    QList<GluonCore::GluonObject*> list = GluonCore::GDLHandler::instance()->parseGDL(file(), 0);
    if( list.isEmpty() )
        return;

    GluonCore::GluonObject* tmpObj = list.at(0);
    foreach( QObject* child, tmpObj->children() )
    {
        Statistic* statistic = qobject_cast<Statistic*>(child);
        if( statistic )
            statistic->setParent(this);
    }
    delete tmpObj;
}

void StatisticsAsset::createStatistic()
{
    Statistic* newStatistic = new Statistic(this);
    newStatistic->setName(tr("New Statistic"));
    savableDirty = true;
}

void StatisticsAsset::populateMetaInfo(GluonCore::MetaInfo* info)
{
    info->setDefaultExtension( "gluonstatistics" );
}

Q_EXPORT_PLUGIN2( gluon_asset_statistics, GluonEngine::StatisticsAsset )

#include "statisticsasset.moc"
