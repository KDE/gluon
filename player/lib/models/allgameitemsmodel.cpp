/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "allgameitemsmodel.h"

#include "gameitem.h"

#include <player/lib/serviceprovider.h>
#include <player/lib/gamedetail.h>
#include <player/lib/rating.h>

#include <core/directoryprovider.h>
#include <engine/gameproject.h>

#include <QtCore/QHash>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtGui/QFileSystemModel>

using namespace GluonPlayer;

class AllGameItemsModel::Private
{
    public:
        Private()
        {
        }

        QList<GameItem*> gameItems;
        QHash<QString, int> listIndexForId;
        QFileSystemModel fsModel;
};

AllGameItemsModel::AllGameItemsModel( QObject* parent )
    : QAbstractListModel( parent )
    , d( new Private() )
{
    d->fsModel.setNameFilters( QStringList( '*' + GluonEngine::projectSuffix ) );
    connect( &d->fsModel, SIGNAL( directoryLoaded( QString ) ), SLOT( directoryLoaded( QString ) ) );
    d->fsModel.setRootPath( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/games" );

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "GameName";
    roles[GameDescriptionRole] = "GameDescription";
    roles[RatingRole] = "Rating";
    roles[StatusRole] = "Status";
    roles[IDRole] = "Id";
    setRoleNames( roles );

    fetchGamesList();
}

AllGameItemsModel::~AllGameItemsModel()
{
}

void AllGameItemsModel::addGameItemToList( GameItem* gameItem )
{
    QString id = gameItem->id();

    if( d->listIndexForId.contains( id ) )
    {
        qFatal( "Fatal: List already contains the game" );
    }

    int gameCount = d->gameItems.count();
    beginInsertRows( QModelIndex(), gameCount, gameCount );
    d->listIndexForId.insert( id, gameCount );
    d->gameItems.append( gameItem );
    endInsertRows();
}

GameItem* AllGameItemsModel::gameItemForId( const QString& id )
{
    if( d->listIndexForId.contains( id ) )
    {
        return d->gameItems.at( d->listIndexForId.value( id ) );
    }

    return 0;
}

void AllGameItemsModel::directoryLoaded( const QString& path )
{
    //TODO: Use standard gluon game dir
    if( QDir( path ) != QDir( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/games" ) )
        return;

    QModelIndex parentIndex = d->fsModel.index( path ); //QFSModel puts "/" as root, obtain parent to our games path

    QStringList deletedGames;
    foreach( const GameItem * gameItem, d->gameItems )
    {
        if( (gameItem->status() & GameItem::Local) == GameItem::Local )   //If Game is Local or Installed
        {
            deletedGames.append( gameItem->id() );
        }
    }

    //Find all .gluon dirs
    for( int i = 0; i < d->fsModel.rowCount( parentIndex ); ++i )
    {
        QString gameDirPath = d->fsModel.filePath( d->fsModel.index( i, 0, parentIndex ) );
        deletedGames.removeOne( addGameFromDirectory( gameDirPath ) );
    }

    //Remove the local games that were not found in the games dir
    foreach( const QString & id, deletedGames )
        removeGameFromList( id );


    fetchGamesList();   //FIXME: Preferably do this only the first time
}

QString AllGameItemsModel::addGameFromDirectory( const QString& directoryPath )
{
    QString id;
    QDir gameDir( directoryPath );
    QStringList gluonProjectFiles = gameDir.entryList( QStringList( GluonEngine::projectFilename ) );

    if( !gluonProjectFiles.isEmpty() )
    {
        QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
        GluonEngine::GameProject project;
        project.loadFromFile( projectFileName );
        id = project.property( "id" ).toString();

        if( d->listIndexForId.contains( id ) )
        {
            GameItem* gameItem = new GameItem( project.name(),  project.description(), 0,
                                               GluonPlayer::GameItem::Installed, id, this );
            addOrUpdateGameFromFetchedGameItem( gameItem );
        }
        else
        {
            GameItem* gameItem = new GameItem( project.name(),  project.description(), 0,
                                               GluonPlayer::GameItem::Installed, id, this );
            addGameItemToList( gameItem );
            fetchAndUpdateExistingGameItem( gameItem ); //New game on disk, fetch social info from OCS server
        }
    }
    else
    {
        qWarning() << "No " << GluonEngine::projectFilename << " in " << directoryPath;
    }

    return id;
}

void AllGameItemsModel::updateExistingGameItem( const GameItem* newGameItem )
{
    /* TODO: Right now, if information such as game name exist both on file system
        and on the server, its assumed that the server is "correct".
        However, in case the user is the owner of the game, we should ask
    */
    GameItem* existingGameItem = gameItemForId( newGameItem->id() );

    if( existingGameItem )
    {
        if( newGameItem->status() == GameItem::Downloadable )
        {
            existingGameItem->setRating( newGameItem->rating() );
            existingGameItem->setGameName( newGameItem->gameName() );
            existingGameItem->setGameDescription( newGameItem->gameDescription() );
        }
        else if( existingGameItem->status() != GameItem::Downloadable )
        {
            existingGameItem->setGameName( newGameItem->gameName() );
            existingGameItem->setGameDescription( newGameItem->gameDescription() );
        }

        existingGameItem->setStatus( GameItem::Status( existingGameItem->status() | newGameItem->status() ) );

        int row = d->gameItems.indexOf( existingGameItem );
        dataChanged( index( row ), index( row ) );
    }
}

void AllGameItemsModel::addOrUpdateGameFromFetchedGameItem( GameItem* gameItem )
{
    QString id = gameItem->id();

    if( d->listIndexForId.contains( id ) )
    {
        updateExistingGameItem( gameItem );
    }
    else
    {
        addGameItemToList( gameItem );
    }
}

void AllGameItemsModel::removeGameFromList( const QString& id )
{
    GameItem* oldGameItem = gameItemForId( id );

    if( oldGameItem )
    {
        int oldGameRow = d->gameItems.indexOf( oldGameItem );
        beginRemoveRows(QModelIndex(), oldGameRow, oldGameRow);
        d->gameItems.removeAt( oldGameRow );
        d->listIndexForId.remove( id );
        delete oldGameItem;

        QHash<QString, int>::iterator iterator;
        iterator = d->listIndexForId.begin();

        /*After removing the GameItem from the list, all items below it will shift up.
            Hence update the list indexes in d->listIndexForId accordingly */
        do
        {
            if( iterator.value() >= oldGameRow )
                --iterator.value();
            ++iterator;
        }
        while( iterator != d->listIndexForId.end() );

        endRemoveRows();
    }
}

QVariant AllGameItemsModel::data( const QModelIndex& index, int role ) const
{
    if( index.row() < 0 || index.row() > d->gameItems.count() )
        return QVariant();

    switch( role )
    {
        case Qt::UserRole:
            break;
        case Qt::DisplayRole:
        case GameNameRole:
            return d->gameItems.at( index.row() )->gameName();
        case GameDescriptionRole:
            return d->gameItems.at( index.row() )->gameDescription();
        case RatingRole:
            return d->gameItems.at( index.row() )->rating();
        case StatusRole:
            return d->gameItems.at( index.row() )->status();
        case IDRole:
            return d->gameItems.at( index.row() )->id();
        default:
            break;
    }

    return QVariant();
}

bool AllGameItemsModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    switch( role )
    {
        case RatingRole:
            Rating* ratingProvider =
                ServiceProvider::instance()->setRating( d->gameItems.at( index.row() )->id(), value.toUInt() );
            connect( ratingProvider, SIGNAL( finished( QString ) ), SLOT( ratingUploadFinished( QString ) ) );
            return true;
    }

    return false;
}

int AllGameItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->gameItems.count();
}

int AllGameItemsModel::columnCount( const QModelIndex& /* parent */ ) const
{
    return 1;
}

QVariant AllGameItemsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( section == 0 )
    {
        return QString( "Game" );
    }

    return QAbstractItemModel::headerData( section, orientation, role );
}

void AllGameItemsModel::fetchGamesList()
{
    GameDetail* gameDetailsProvider = ServiceProvider::instance()->fetchGames();
    connect( gameDetailsProvider, SIGNAL( gameListFetched( QList<GameDetailItem*> ) ),
             SLOT( processFetchedGamesList( QList<GameDetailItem*> ) ) );
}

void AllGameItemsModel::processFetchedGamesList( QList< GameDetailItem* > gamesList )
{
    foreach( GameDetailItem * c, gamesList )
    {
        GameItem* gameItem = new GameItem( c->gameName(), c->gameDescription(), c->rating(), GameItem::Downloadable,
                                           c->id(), this );

        addOrUpdateGameFromFetchedGameItem( gameItem );
    }
}

void AllGameItemsModel::fetchAndUpdateExistingGameItem( const GameItem* gameItem )
{
    if( gameItem->id().isEmpty() )
        return;

    GameDetail* gameDetailsProvider = ServiceProvider::instance()->fetchOneGame( gameItem->id() );
    connect( gameDetailsProvider, SIGNAL( gameDetailsFetched( GameDetailItem* ) ),
             SLOT( processFetchedGameDetails( GameDetailItem* ) ) );
}

void AllGameItemsModel::processFetchedGameDetails( GameDetailItem* gameDetails )
{
    GameItem* gameItem = new GameItem( gameDetails->gameName(), gameDetails->gameDescription(), gameDetails->rating(),
                                       GameItem::Downloadable, gameDetails->id(), this );
    addOrUpdateGameFromFetchedGameItem( gameItem );
}


void AllGameItemsModel::ratingUploadFinished( const QString& id )
{
    fetchAndUpdateExistingGameItem( gameItemForId( id ) );
}

#include "allgameitemsmodel.moc"
