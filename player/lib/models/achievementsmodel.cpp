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

#include <QtCore/QDebug>

using namespace GluonPlayer;

class AchievementsModel::AchievementsModelPrivate
{
    public:
        AchievementsModelPrivate() {}
        ~AchievementsModelPrivate() {}

        QList<GluonEngine::Achievement*> achievements;
        QStringList headerList;
};

AchievementsModel::AchievementsModel(QObject* parent)
    : QAbstractTableModel(parent)
    , d( new AchievementsModelPrivate() )
{
    GluonEngine::GameProject* p = GluonEngine::Game::instance()->gameProject();
    d->headerList << "Achievement" << "Achieved?";
    if( p )
        d->achievements = p->achievements();
    else
        qDebug() << "AchievementsModel: no GameProject open!"; 
}

AchievementsModel::~AchievementsModel()
{
    delete d;
}

int AchievementsModel::rowCount(const QModelIndex& /*parent*/) const
{
    return d->achievements.count();
}

int AchievementsModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 2;
}

QVariant AchievementsModel::data(const QModelIndex& index, int role) const
{
    if( !index.isValid() || role != Qt::DisplayRole )
        return QVariant();

    GluonEngine::Achievement* achievement = d->achievements[index.row()];
    if( index.column() == 0 )
        return achievement->name();

    else
        return achievement->achieved() ? "yes" : "no";
}

QVariant AchievementsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation != Qt::Horizontal || role != Qt::DisplayRole )
        return QVariant();

    return d->headerList[section];
}

#include "achievementsmodel.moc"
