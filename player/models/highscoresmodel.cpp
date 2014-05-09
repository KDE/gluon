/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <shaan7in@gmail.com>
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

#include "highscoresmodel.h"

#include "allgameitemsmodel.h"
#include "../gamemanager.h"

#include <gluon_global.h>

#include <engine/gameproject.h>

#include <core/gluonobject.h>
#include <core/gdlserializer.h>

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QTextStream>

using namespace GluonCore;
using namespace GluonPlayer;

class HighScoresModel::Private
{
    public:
    Private()
    {
    }

    QString m_gameId;
    GluonCore::GluonObject* m_rootNode;
};

HighScoresModel::HighScoresModel( QString gameId, QObject* parent )
    : QAbstractTableModel( parent )
    , d(new Private)
{
    d->m_gameId = gameId;
    d->m_rootNode = new GluonObject( "HighScores" );

    loadData();
}

HighScoresModel::~HighScoresModel()
{
    saveData();
}

int HighScoresModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_rootNode->children().count();
}

int HighScoresModel::columnCount( const QModelIndex& /* parent */ ) const
{
    return 3;
}

QVariant HighScoresModel::data( const QModelIndex& index, int role ) const
{
    if( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        switch( index.column() )
        {
            case NameColumn:
                return d->m_rootNode->child( index.row() )->name();
                break;
            case HighScoreColumn:
                return d->m_rootNode->child( index.row() )->property( "HighScore" );
                break;
            case LevelColumn:
                return d->m_rootNode->child( index.row() )->property( "Level" );
                break;
        }
    }
    return QVariant();
}

QVariant HighScoresModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( role == Qt::DisplayRole && orientation == Qt::Horizontal )
    {
        switch( section )
        {
            case NameColumn:
                return QString( "Name" );
                break;
            case HighScoreColumn:
                return QString( "High Score" );
                break;
            case LevelColumn:
                return QString( "Level" );
                break;
        }
    }

    return QVariant();
}

Qt::ItemFlags HighScoresModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags( index ) | Qt::ItemIsEditable;
}


void HighScoresModel::loadData()
{
    // TODO: ~/.gluon/games/$gamebundle/* will be used later
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );

    GluonCore::GluonObjectList list;
    if( GluonCore::GDLSerializer::instance()->read( gluonDir.absoluteFilePath( "highscores.gdl" ), list ) )
        d->m_rootNode = list.at( 0 );
}

void HighScoresModel::saveData()
{
    if (d->m_gameId.isEmpty()) {
        qDebug() << "Failed to save the high scores data for empty game id.";
        return;
    }

    qDebug() << "Saving high scores data!";

    AllGameItemsModel *model = qobject_cast<AllGameItemsModel*>(GameManager::instance()->allGamesModel());
    QString gameCachePath = model->data(d->m_gameId, AllGameItemsModel::CacheUriRole).toUrl().toLocalFile();

    QDir gameCacheDir;
    gameCacheDir.mkpath( gameCachePath );
    gameCacheDir.cd( gameCachePath );
    QString filename = gameCacheDir.absoluteFilePath( "highscores.gdl" );

    GluonCore::GDLSerializer::instance()->write( QUrl::fromLocalFile( filename ), GluonCore::GluonObjectList() << d->m_rootNode );
}

 
