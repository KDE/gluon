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

using namespace GluonKDEPlayer;

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
                m_gamesViewItems.append(new GamesViewItem(project.name(), project.description()));
                project.property( "id" );
        }
    }
}

QVariant GameItemsModel::data( const QModelIndex& index, int role ) const
{
    if( role == Qt::UserRole )
    {
        return QVariant::fromValue( m_gamesViewItems.at( index.row() ) );
    }

    return QVariant();
}

int GameItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return m_gamesViewItems.count();
}

QVariant GameItemsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( section == 0 )
    {
        return QString( "Game" );
    }

    return QAbstractItemModel::headerData( section, orientation, role );
}
