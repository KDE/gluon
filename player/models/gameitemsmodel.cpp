/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "gameitemsmodel.h"

#include <QtCore/QDir>
#include <QtCore/QHash>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QMultiMap>

#include <core/directoryprovider.h>
//#include <engine/gameproject.h>

#include "serviceprovider.h"
#include "gamedetaillistjob.h"

using namespace GluonPlayer;

class GameItemsModel::Private
{
    public:
    Private()
    {
    }

    QMultiMap<GameViewItem::Status, GameViewItem*> m_gameViewItems;
};

GameItemsModel::GameItemsModel( QObject* parent )
    : QAbstractListModel( parent )
    , d( new Private )
{
    /*
    QDir m_dir;
    m_dir.cd( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/games" );
    QStringList gameDirNameList = m_dir.entryList( QStringList() << QString( '*' + GluonEngine::projectSuffix ), QDir::Dirs | QDir::NoDotAndDotDot );
    foreach( const QString & gameDirName, gameDirNameList )
    {
        QDir gameDir = m_dir;
        gameDir.cd( gameDirName );
        QStringList gluonProjectFiles = gameDir.entryList( QStringList( GluonEngine::projectFilename ) );
        if( !gluonProjectFiles.isEmpty() )
        {
            QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
            GameViewItem* gameViewItem = new GameViewItem( projectFileName, GameViewItem::Installed );
            d->m_gameViewItems.insertMulti( GameViewItem::Installed, gameViewItem );
        }
    }

    fetchGamesList();
    */
}

QHash<int, QByteArray> GameItemsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ProjectNameRole] = "projectName";
    roles[ProjectDescriptionRole] = "projectDescription";
    roles[ProjectFilePathRole] = "projectFilePath";
    roles[ProjectDirPathRole] = "projectDirPath";
    roles[ScreenshotUrlsRole] = "screenshotUrls";
    roles[StatusRole] = "status";
    roles[ProjectIDRole] = "projectId";

    // Downloadable Game item roles
    roles[ProjectNameDownloadableRole] = "projectNameDownloadable";
    roles[ProjectDescriptionDownloadableRole] = "projectDescriptionDownloadable";
    roles[ProjectFilePathDownloadableRole] = "projectFilePathDownloadable";
    roles[ProjectDirPathDownloadableRole] = "projectDirPathDownloadable";
    roles[ScreenshotUrlsDownloadableRole] = "screenshotUrlsDownloadable";
    roles[StatusDownloadableRole] = "statusDownloadable";
    roles[ProjectIDDownloadableRole] = "projectIdDownloadable";
    return roles;
}

GameItemsModel::~GameItemsModel()
{
}

QVariant GameItemsModel::data( const QModelIndex& index, int role ) const
{
    if( index.row() < 0 || index.row() > d->m_gameViewItems.values().count() )
        return QVariant();

    switch( role )
    {
        case Qt::UserRole:
            break;
        case ProjectNameRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectName();
        case ProjectDescriptionRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectDescription();
        case ProjectDirPathRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectDirPath();
        case Qt::DisplayRole:
        case ProjectFilePathRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectFilePath();
        case ScreenshotUrlsRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->screenshotUrls();
        case StatusRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->status();
        case ProjectIDRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectId();

            // Downloadable Game item roles
        case ProjectNameDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectName();
        case ProjectDescriptionDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectDescription();
        case ProjectDirPathDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectDirPath();
        case ProjectFilePathDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectFilePath();
        case ScreenshotUrlsDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->screenshotUrls();
        case StatusDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->status();
        case ProjectIDDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectId();
        default:
            break;
    }

    return QVariant();
}

int GameItemsModel::downloadableCount() const
{
    return d->m_gameViewItems.values( GameViewItem::Downloadable ).count();
}

int GameItemsModel::upgradableCount() const
{
    return d->m_gameViewItems.values( GameViewItem::Upgradable ).count();
}

GameViewItem* GameItemsModel::installedGameInfo(int row)
{
    if( row < 0 || row >= d->m_gameViewItems.values().count() )
        return 0;

    return d->m_gameViewItems.values( GameViewItem::Installed ).at( row );
}

int GameItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_gameViewItems.values( GameViewItem::Installed ).count();
}

int GameItemsModel::columnCount( const QModelIndex& /* parent */ ) const
{
    return 1;
}

QVariant GameItemsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( section == 0 )
    {
        return QString( "Game" );
    }

    return QAbstractItemModel::headerData( section, orientation, role );
}

void GameItemsModel::fetchGamesList()
{
    GameDetailListJob *gameDetailListJob = ServiceProvider::instance()->fetchGames();
    connect(gameDetailListJob, SIGNAL(succeeded()), SLOT(processFetchedGameList()));
    gameDetailListJob->start();
}

void GameItemsModel::processFetchedGameList()
{
    beginResetModel();
    QList<GameDetailItem*> list = qobject_cast<GameDetailListJob*>(sender())->data().value< QList<GameDetailItem*> > ();
    foreach(GameDetailItem *c, list) {
        GameViewItem* gameViewItem = new GameViewItem( c->gameName(), c->gameDescription(), "",
                    GameViewItem::Downloadable, c->id() );
        d->m_gameViewItems.insertMulti( GameViewItem::Downloadable, gameViewItem );
    }
    endResetModel();
    emit downloadableCountChanged();
}

 
