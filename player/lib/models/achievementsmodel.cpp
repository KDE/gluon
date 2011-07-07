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

#include "achievementsmodel.h"

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/achievement.h>
#include <engine/achievementsmanager.h>
#include <engine/projectmetadata.h>
#include <core/directoryprovider.h>

#include <QtCore/QDebug>

using namespace GluonPlayer;

class AchievementsModel::AchievementsModelPrivate
{
    public:
        AchievementsModelPrivate() : achievementsManager( 0 ), metaData( 0 ) {}
        ~AchievementsModelPrivate() { delete achievementsManager; }

        QStringList headerList;
        GluonEngine::AchievementsManager* achievementsManager;
        GluonEngine::ProjectMetaData* metaData;
};

AchievementsModel::AchievementsModel( GluonEngine::ProjectMetaData* metaData, const QString& userName, QObject* parent)
    : QAbstractTableModel(parent)
    , d( new AchievementsModelPrivate() )
{
    d->metaData = metaData;
    d->headerList << "Achievement" << "Progress" << "Achieved?";
    d->achievementsManager = new GluonEngine::AchievementsManager(this);
    QString achievementsDirectory = GluonCore::DirectoryProvider::instance()->userDirectory("data");
    achievementsDirectory.append( "/" + userName + "/" + metaData->projectName() );
    d->achievementsManager->load( achievementsDirectory );
    qDebug() << "Achievements count: " << d->achievementsManager->achievementsCount();
    if( d->achievementsManager->achievementsCount() == 0 )
    {
        achievementsDirectory = metaData->projectDir() + "/Cache";
        d->achievementsManager->load( achievementsDirectory );
    }
}

AchievementsModel::~AchievementsModel()
{
    delete d;
}

int AchievementsModel::rowCount(const QModelIndex& /*parent*/) const
{
    return d->achievementsManager->achievementsCount();
}

int AchievementsModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 3;
}

QVariant AchievementsModel::data(const QModelIndex& index, int role) const
{
    if( !index.isValid() )
        return QVariant();


    if( index.column() == 0 && role == Qt::DecorationRole && d->achievementsManager->dependencySatisfied(index.row()) )
        return QIcon( d->metaData->projectDir() + "/" + d->achievementsManager->achievementIcon(index.row()) );

    if( index.column() == 0 && role == Qt::DisplayRole )
        if( d->achievementsManager->dependencySatisfied(index.row()) )
            return d->achievementsManager->achievementName(index.row());
        else
            return "Unknown";

    if( index.column() == 1 && role == Qt::DisplayRole )
        if( d->achievementsManager->dependencySatisfied(index.row()) )
            return QString("%1/%2").arg( d->achievementsManager->currentScore(index.row()) )
                                   .arg( d->achievementsManager->minimumScore(index.row()) );
        else
            return "0/0";

    if( index.column() == 2 && role == Qt::DisplayRole )
        if( d->achievementsManager->dependencySatisfied(index.row()) )
            return d->achievementsManager->achievementAchieved(index.row()) ? "yes" : "no";
        else
            return "no";

    return QVariant();
}

QVariant AchievementsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation != Qt::Horizontal || role != Qt::DisplayRole )
        return QVariant();

    return d->headerList[section];
}

Qt::ItemFlags AchievementsModel::flags(const QModelIndex& index) const
{
    if( d->achievementsManager->achievementAchieved(index.row()) )
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable;
}

const GluonEngine::ProjectMetaData* AchievementsModel::metaData() const
{
    return d->metaData;
}

const GluonEngine::AchievementsManager* AchievementsModel::achievementsManager() const
{
    return d->achievementsManager;
}

#include "achievementsmodel.moc"
