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

#include <QtWidgets/QStyle>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

using namespace GluonPlayer;

class AchievementsModel::AchievementsModelPrivate
{
    public:
        AchievementsModelPrivate() : achievementsManager( 0 ), hiddenAchievements(0) {}
        ~AchievementsModelPrivate() { delete achievementsManager; }

        QStringList headerList;
        QString projectDir;
        GluonEngine::AchievementsManager* achievementsManager;
        int hiddenAchievements;
};

AchievementsModel::AchievementsModel( GluonEngine::ProjectMetaData* metaData, const QString& userName, QObject* parent)
    : QAbstractTableModel(parent)
    , d( new AchievementsModelPrivate() )
{
    d->headerList << tr("Achievement") << tr("Progress") << tr("Achieved");
    d->achievementsManager = new GluonEngine::AchievementsManager(this);

    if( metaData )
    {
        d->projectDir = metaData->projectDir();
        QString achievementsDirectory = GluonCore::DirectoryProvider::instance()->userDirectory("data");
        achievementsDirectory.append( '/' + userName + '/' + metaData->projectName() );
        d->achievementsManager->load( achievementsDirectory );
        qDebug() << "Achievements count:" << d->achievementsManager->achievementsCount();
        if( d->achievementsManager->achievementsCount() == 0 )
        {
            achievementsDirectory = metaData->projectDir() + "/.cache";
            d->achievementsManager->load( achievementsDirectory );
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "metaData is NULL, so the model will be empty.";
    }

    // check for hidden achievements
    for( int i=0; i<d->achievementsManager->achievementsCount(); ++i )
    {
        if( d->achievementsManager->isHidden( i ) && !d->achievementsManager->isPastThreshold( i ) )
            d->hiddenAchievements++;
    }

}

QHash<int, QByteArray> AchievementsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "qtDisplayRole";
    roles[Qt::DecorationRole] = "qtDecorationRole";
    roles[Qt::ToolTipRole] = "qtToolTipRole";
    return roles;
}

AchievementsModel::~AchievementsModel()
{
    delete d;
}

int AchievementsModel::rowCount( const QModelIndex& parent ) const
{
    if( !parent.isValid() )
        return d->achievementsManager->achievementsCount() - d->hiddenAchievements;

    return 0;
}

int AchievementsModel::columnCount( const QModelIndex& parent ) const
{
    if( !parent.isValid() )
        return 3;

    return 0;
}

QVariant AchievementsModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    switch( index.column() )
    {
        case NameColumn:
            if( role == Qt::DisplayRole )
            {
                if( d->achievementsManager->dependencySatisfied( index.row() ) )
                    return d->achievementsManager->achievementName( index.row() );
                else
                    return tr("Unknown");
            }
            if( role == Qt::DecorationRole )
                if( d->achievementsManager->dependencySatisfied( index.row() ) )
                    return QIcon( d->projectDir + '/' + d->achievementsManager->achievementIcon( index.row() ) );

            break;
        case ProgressColumn:
            if( role == Qt::DisplayRole )
            {
                if( d->achievementsManager->dependencySatisfied( index.row() ) )
                    return QString("%1/%2").arg( d->achievementsManager->currentScore( index.row()) )
                                           .arg( d->achievementsManager->minimumScore( index.row()) );
                else
                    return "0/0";
            }
            break;
        case AchievedColumn:
            if( role == Qt::DecorationRole )
            {
                if( d->achievementsManager->dependencySatisfied( index.row() )
                        && d->achievementsManager->achievementAchieved( index.row() ) )
                    return qApp->style()->standardIcon( QStyle::SP_DialogYesButton );
                else
                    return qApp->style()->standardIcon( QStyle::SP_DialogNoButton );
            }
            if( role == Qt::ToolTipRole )
            {
                if( d->achievementsManager->dependencySatisfied( index.row() ) )
                    return d->achievementsManager->achievementAchieved( index.row() ) ? tr("yes") : tr("no");
                else
                    return tr("no");
            }
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

Qt::ItemFlags AchievementsModel::flags(const QModelIndex& index) const
{
    if( d->achievementsManager->achievementAchieved(index.row()) )
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable;
}

const GluonEngine::AchievementsManager* AchievementsModel::achievementsManager() const
{
    return d->achievementsManager;
}

QString AchievementsModel::projectDir() const
{
    return d->projectDir;
}

 
