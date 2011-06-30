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

#include <player/lib/serviceprovider.h>
#include <player/lib/gamedetail.h>

#include <core/directoryprovider.h>
#include <engine/gameproject.h>

#include <QtCore/QDir>
#include <QtCore/QHash>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QMultiMap>

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
    , d( new Private() )
{
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
            GluonEngine::GameProject project;
            project.loadFromFile( projectFileName );
            GameViewItem* gameViewItem = new GameViewItem( project.name(), project.description(), gameDir.path(), projectFileName,
                    GameViewItem::Installed, project.property( "id" ).toString() );
            d->m_gameViewItems.insertMulti( GameViewItem::Installed, gameViewItem );
        }
    }

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "gameName";
    roles[GameDescriptionRole] = "gameDescription";
    roles[ProjectFileNameRole] = "projectFileName";
    roles[ProjectDirNameRole] = "projectDirName";
    roles[ScreenshotUrlsRole] = "screenshotUrls";
    roles[StatusRole] = "status";
    roles[IDRole] = "id";

    // Downloadable Game item roles
    roles[GameNameDownloadableRole] = "gameNameDownloadable";
    roles[GameDescriptionDownloadableRole] = "gameDescriptionDownloadable";
    roles[ProjectFileNameDownloadableRole] = "projectFileNameDownloadable";
    roles[ProjectDirNameDownloadableRole] = "projectDirNameDownloadable";
    roles[ScreenshotUrlsDownloadableRole] = "screenshotUrlsDownloadable";
    roles[StatusDownloadableRole] = "statusDownloadable";
    roles[IDDownloadableRole] = "idDownloadable";
    setRoleNames( roles );

    fetchGamesList();
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
        case GameNameRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->gameName();
        case GameDescriptionRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->gameDescription();
        case ProjectDirNameRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectDirName();
        case Qt::DisplayRole:
        case ProjectFileNameRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->projectFileName();
        case ScreenshotUrlsRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->screenshotUrls();
        case StatusRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->status();
        case IDRole:
            return d->m_gameViewItems.values( GameViewItem::Installed ).at( index.row() )->id();

            // Downloadable Game item roles
        case GameNameDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->gameName();
        case GameDescriptionDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->gameDescription();
        case ProjectDirNameDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectDirName();
        case ProjectFileNameDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->projectFileName();
        case ScreenshotUrlsDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->screenshotUrls();
        case StatusDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->status();
        case IDDownloadableRole:
            return d->m_gameViewItems.values( GameViewItem::Downloadable ).at( index.row() )->id();
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
    GameDetail *gameDetail = ServiceProvider::instance()->fetchGames();
    connect(gameDetail, SIGNAL(gameDetailsFetched (QList<GameDetailItem*>)),
            SLOT(processFetchedGamesList(QList<GameDetailItem*>)));
}

void GameItemsModel::processFetchedGamesList(QList< GameDetailItem* > comments)
{
    foreach(GameDetailItem *c, comments) {
        GameViewItem* gameViewItem = new GameViewItem( c->gameName(), c->gameDescription(), "", "",
                    GameViewItem::Downloadable, c->id() );
        d->m_gameViewItems.insertMulti( GameViewItem::Downloadable, gameViewItem );
    }
    reset();
    emit downloadableCountChanged();
}

#include "gameitemsmodel.moc"
