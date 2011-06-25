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

#include <QtGui/QStyle>
#include <QtGui/QApplication>
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
    GluonEngine::GameProject* gameProject = GluonEngine::Game::instance()->gameProject();
    d->headerList << tr("Achievement") << tr("Achieved");
    if( gameProject )
        d->achievements = gameProject->achievements();
    else
        qDebug() << Q_FUNC_INFO << "No GameProject open!";
}

AchievementsModel::~AchievementsModel()
{
    delete d;
}

int AchievementsModel::rowCount( const QModelIndex& /*parent*/ ) const
{
    return d->achievements.count();
}

int AchievementsModel::columnCount( const QModelIndex& /*parent*/ ) const
{
    return 2;
}

QVariant AchievementsModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    GluonEngine::Achievement* achievement = d->achievements.at( index.row() );
    switch( index.column() )
    {
        case 0:
            if( role == Qt::DisplayRole )
                return achievement->name();

            break;
        case 1:
            if( role == Qt::DecorationRole )
            {
                if( achievement->achieved() )
                    return qApp->style()->standardIcon( QStyle::SP_DialogYesButton );
                else
                    return qApp->style()->standardIcon( QStyle::SP_DialogNoButton );
            }
            if( role == Qt::ToolTipRole )
                return achievement->achieved() ? tr("yes") : tr("no");

            break;
        default:
            return QVariant();
    }
    return QVariant();
}

QVariant AchievementsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation != Qt::Horizontal || role != Qt::DisplayRole )
        return QVariant();

    return d->headerList.at(section);
}

#include "achievementsmodel.moc"
