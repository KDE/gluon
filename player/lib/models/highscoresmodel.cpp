/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include <engine/gameproject.h>

#include <core/gluonobject.h>
#include <core/gdlhandler.h>
#include <core/gluon_global.h>

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

    if( QFile::exists( gluonDir.absoluteFilePath( "highscores.gdl" ) ) )
        d->m_rootNode = GluonCore::GDLHandler::instance()->parseGDL( gluonDir.absoluteFilePath( "highscores.gdl" ) ).at( 0 );
    else
        qDebug() << "File does not exist: " << gluonDir.absoluteFilePath( "highscores.gdl" );
}

void HighScoresModel::saveData()
{
    qDebug() << "Saving high scores data!";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );
    QString filename = gluonDir.absoluteFilePath( "highscores.gdl" );

    QFile dataFile( filename );
    if( !dataFile.open( QIODevice::WriteOnly ) )
    {
        qDebug() << "Cannot open the high scores file!";
        return;
    }

    QList<const GluonObject*> highScores;
    highScores.append( d->m_rootNode );
    QTextStream dataWriter( &dataFile );
    dataWriter << GluonCore::GDLHandler::instance()->serializeGDL( highScores );
    dataFile.close();
    qDebug() << "Saved!";
}

#include "highscoresmodel.moc"
