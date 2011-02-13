/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "highscoresmodel.h"

#include "core/gluonobject.h"
#include "core/gdlhandler.h"
#include "core/gluon_global.h"

#include "engine/gameproject.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QTextStream>

using namespace GluonCore;
using namespace GluonPlayer;

static const char serviceURI[] = "gamingfreedom.org";

HighScoresModel::HighScoresModel( QString gameId, QObject* parent )
    : QAbstractTableModel( parent )
    , m_gameId( gameId )
    , m_rootNode( new GluonObject( "HighScores" ) )
{
    loadData();
}

HighScoresModel::~HighScoresModel()
{
    saveData();
}

int HighScoresModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return m_rootNode->children().count();
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
                return m_rootNode->child( index.row() )->name();
                break;
            case HighScoreColumn:
                return m_rootNode->child( index.row() )->property( "HighScore" );
                break;
            case LevelColumn:
                return m_rootNode->child( index.row() )->property( "Level" );
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

Qt::ItemFlags HighScoresModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


void HighScoresModel::loadData()
{
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/" + QString( serviceURI ) );
    gluonDir.cd( GluonEngine::projectSuffix + "/" + QString( serviceURI ) );

    QList<GluonObject*> highScores = GluonCore::GDLHandler::instance()->parseGDL( gluonDir.absoluteFilePath( "highscores.gdl" ) );
    m_rootNode = highScores.at( 0 );
}

void HighScoresModel::saveData()
{
    qDebug() << "Saving high scores data!";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/" + QString( serviceURI ) );
    gluonDir.cd( GluonEngine::projectSuffix + "/" + QString( serviceURI ) );
    QString filename = gluonDir.absoluteFilePath( "highscores.gdl" );

    QFile dataFile( filename );
    if( !dataFile.open( QIODevice::WriteOnly ) )
    {
        qDebug() << "Cannot open the high scores file!";
        return;
    }

    QList<const GluonObject*> highScores;
    highScores.append( m_rootNode );
    QTextStream dataWriter( &dataFile );
    dataWriter << GluonCore::GDLHandler::instance()->serializeGDL( highScores );
    dataFile.close();
    qDebug() << "Saved!";
}

#include "highscoresmodel.moc"
