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

#include <QtGui/QStyle>
#include <QtGui/QApplication>
#include <QtCore/QDebug>

using namespace GluonPlayer;

class AchievementsModel::AchievementsModelPrivate
{
    public:
        AchievementsModelPrivate() : achievementsManager( 0 ) {}
        ~AchievementsModelPrivate() { delete achievementsManager; }

        QStringList headerList;
        GluonEngine::AchievementsManager* achievementsManager;
};

AchievementsModel::AchievementsModel( GluonEngine::ProjectMetaData* metaData, const QString& userName, QObject* parent)
    : QAbstractTableModel(parent)
    , d( new AchievementsModelPrivate() )
{
    d->headerList << tr("Achievement") << tr("Achieved");
    d->achievementsManager = new GluonEngine::AchievementsManager(this);
    QString achievementsDirectory = GluonCore::DirectoryProvider::instance()->userDirectory("data");
    achievementsDirectory.append( "/" + userName + "/" + metaData->projectName() );
    d->achievementsManager->load( achievementsDirectory );
    qDebug() << "Achievements count: " << d->achievementsManager->achievementsCount();
    if( d->achievementsManager->achievementsCount() == 0 )
    {
        achievementsDirectory = metaData->projectDir() + "/.cache";
        d->achievementsManager->load( achievementsDirectory );
    }

    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "qtDisplayRole";
    roles[Qt::DecorationRole] = "qtDecorationRole";
    roles[Qt::ToolTipRole] = "qtToolTipRole";
    setRoleNames(roles);
}

AchievementsModel::~AchievementsModel()
{
    delete d;
}

int AchievementsModel::rowCount( const QModelIndex& /*parent*/ ) const
{
    return d->achievementsManager->achievementsCount();
}

int AchievementsModel::columnCount( const QModelIndex& /*parent*/ ) const
{
    return 2;
}

QVariant AchievementsModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    switch( index.column() )
    {
        case 0:
            if( role == Qt::DisplayRole )
                return d->achievementsManager->achievementName( index.row() );

            break;
        case 1:
            if( role == Qt::DecorationRole )
            {
                if( d->achievementsManager->achievementAchieved( index.row() ) )
                    return qApp->style()->standardIcon( QStyle::SP_DialogYesButton );
                else
                    return qApp->style()->standardIcon( QStyle::SP_DialogNoButton );
            }
            if( role == Qt::ToolTipRole )
                return d->achievementsManager->achievementAchieved( index.row() ) ? tr("yes") : tr("no");

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
