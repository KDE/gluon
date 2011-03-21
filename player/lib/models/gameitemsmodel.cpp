/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "core/gluon_global.h"
#include "engine/gameproject.h"

#include <QtCore/QHash>
#include <QtCore/QByteArray>

using namespace GluonPlayer;

GameViewItem::GameViewItem(const QString& gameName, const QString& gameDescription,
                            const QString& projectDirName, const QString& projectFileName, const QString& id)
    : m_gameName(gameName)
    , m_gameDescription(gameDescription)
    , m_projectDirName(projectDirName)
    , m_projectFileName(projectFileName)
    , m_id(id)
{
}

QString GameViewItem::gameName() const
{
    return m_gameName;
}

QString GameViewItem::gameDescription() const
{
    return m_gameDescription;
}

QString GameViewItem::projectDirName() const
{
    return m_projectDirName;
}

QString GameViewItem::projectFileName() const
{
    return m_projectFileName;
}

QVariantList GameViewItem::screenshotUrls() const
{
    QVariantList screenshots;
    foreach(const QUrl &url, m_screenshotUrls)
        screenshots.append(qVariantFromValue(url));
    return screenshots;
}

QString GameViewItem::id() const
{
    return m_id;
}

GameItemsModel::GameItemsModel( QObject* parent )
    : QAbstractListModel( parent )
{
    QDir m_dir;
    m_dir.cd( GluonCore::Global::dataDirectory() + "/gluon/games" );
    QStringList gameDirNameList = m_dir.entryList( QStringList() << QString("*" + GluonEngine::projectSuffix), QDir::Dirs | QDir::NoDotAndDotDot );
    foreach( const QString& gameDirName, gameDirNameList)
    {
        QDir gameDir = m_dir;
        gameDir.cd( gameDirName );
        QStringList gluonProjectFiles = gameDir.entryList( QStringList( GluonEngine::projectFilename ) );
        if( !gluonProjectFiles.isEmpty() )
        {
            QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
            GluonEngine::GameProject project;
            project.loadFromFile( projectFileName );
            GameViewItem gameViewItem(project.name(), project.description(),
                                        gameDir.path(), projectFileName, project.property("id").toString());
            m_gameViewItems.append(gameViewItem);
        }
    }

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "gameName";
    roles[GameDescriptionRole] = "gameDescription";
    roles[ProjectFileNameRole] = "projectFileName";
    roles[ProjectDirNameRole] = "projectDirName";
    roles[ScreenshotUrlsRole] = "screenshotUrls";
    roles[IDRole] = "id";
    setRoleNames(roles);
}

QVariant GameItemsModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() < 0 || index.row() > m_gameViewItems.count())
        return QVariant();

    switch (role) {
    case Qt::UserRole:
        break;
    case GameNameRole:
        return m_gameViewItems.at( index.row() ).gameName();
    case GameDescriptionRole:
        return m_gameViewItems.at( index.row() ).gameDescription();
    case ProjectDirNameRole:
        return m_gameViewItems.at( index.row() ).projectDirName();
    case Qt::DisplayRole:
    case ProjectFileNameRole:
        return m_gameViewItems.at( index.row() ).projectFileName();
    case ScreenshotUrlsRole:
        return m_gameViewItems.at( index.row() ).screenshotUrls();
    case IDRole:
        return m_gameViewItems.at( index.row() ).id();
    default:
        break;
    }

    return QVariant();
}

int GameItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return m_gameViewItems.count();
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

#include "gameitemsmodel.moc"
