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

#include "models/gameitemsmodel.h"

#include <core/gluon_global.h>
#include <engine/gameproject.h>

#include <QtCore/QHash>
#include <QtCore/QByteArray>

using namespace GluonQMLPlayer;

GameItemsModel::GameItemsModel( QObject* parent )
    : QAbstractListModel( parent )
{
    QDir m_dir;
    m_dir.cd( GluonCore::Global::dataDirectory() + "/gluon/games" );
    QStringList gameDirNameList;
    gameDirNameList = m_dir.entryList( QDir::Dirs | QDir::NoDotAndDotDot );
    foreach( const QString& gameDirName, gameDirNameList)
    {
        QDir gameDir = m_dir;
        gameDir.cd( gameDirName );
        QStringList gluonProjectFiles = gameDir.entryList( QStringList( QString( "*%1" ).arg( GluonEngine::projectSuffix ) ) );
        QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
        if( !gluonProjectFiles.isEmpty() )
        {
                GluonEngine::GameProject project;
                project.loadFromFile( projectFileName );
                m_gameNames.append(project.name());
                m_gameDescriptions.append(project.description());
                m_projectFileNames.append( projectFileName );
                m_ids.append(project.property( "id" ).toString());
        }
    }

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "gamename";
    roles[GameDescriptionRole] = "gamedescription";
    roles[ProjectFileNameRole] = "projectfilename";
    roles[IDRole] = "id";
    setRoleNames(roles);
}

QVariant GameItemsModel::data( const QModelIndex& index, int role ) const
{
    switch (role) {
    case Qt::UserRole:
        break;
    case GameNameRole:
        return m_gameNames.at( index.row() );
    case GameDescriptionRole:
        return m_gameDescriptions.at( index.row() );
    case ProjectFileNameRole:
        return m_projectFileNames.at( index.row() );
    case IDRole:
        return m_ids.at( index.row() );
    default:
        break;
    }

    return QVariant();
}

int GameItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return m_ids.count();
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
