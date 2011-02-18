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

#include "commentsmodel.h"

#include "player/lib/atticamanager.h"

#include "core/gluonobject.h"
#include "core/gdlhandler.h"
#include "core/gluon_global.h"

#include "engine/gameproject.h"

#include <attica/comment.h>
#include <attica/listjob.h>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QDir>

using namespace GluonCore;
using namespace GluonPlayer;

CommentsModel::CommentsModel( QString gameId, QObject* parent )
    : QAbstractItemModel( parent )
    , m_rootNode( new GluonObject( "Comment" ) )
    , m_isOnline( false )
    , m_gameId( gameId )
{
    m_columnNames << tr("Author") << tr("Title") << tr("Body") << tr("DateTime") << tr("Rating");

    loadData();     // Load comments stored locally
    updateData();   // Fetch latest comments from the web service
}

void CommentsModel::updateData()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        providersUpdated();
    }
    else
    {
        connect( AtticaManager::instance(), SIGNAL( gotProvider() ), SLOT( providersUpdated() ) );
    }
}

void CommentsModel::providersUpdated()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        Attica::ListJob<Attica::Comment> *job =
            AtticaManager::instance()->provider().requestComments( Attica::Comment::ContentComment,
                    m_gameId, "0", 0, 100 );
        connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedComments( Attica::BaseJob* ) ) );
        job->start();
    }
    else
    {
        qDebug() << "No providers found.";
    }
}

void CommentsModel::processFetchedComments( Attica::BaseJob* job )
{
    qDebug() << "Comments Successfully Fetched from the server!";

    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment> *>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        //No error, try to remove exising comments (if any)
        //and add new comments

        if( m_rootNode )
        {
            qDeleteAll( m_rootNode->children() );
        }

        for( int i = 0; i < commentsJob->itemList().count(); ++i )
        {
            Attica::Comment p( commentsJob->itemList().at( i ) );
            addComment( p, m_rootNode );
        }

        m_isOnline = true;
        reset();    //Reset the model to notify views to reload comments
    }
    else
    {
        qDebug() << "Could not fetch information";
    }
}

void CommentsModel::addCommentFinished( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment>*>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        updateData();
    }
    else
    {
        emit addCommentFailed();
    }
}

GluonObject* CommentsModel::addComment( Attica::Comment comment, GluonObject* parent )
{
    GluonObject* newComment = new GluonObject( comment.id(), parent );
    newComment->setProperty( "Author", comment.user() );
    newComment->setProperty( "Title", comment.subject() );
    newComment->setProperty( "Body", comment.text() );
    newComment->setProperty( "DateTime", comment.date().toString() );
    newComment->setProperty( "Rating", comment.score() );

    foreach( const Attica::Comment& child, comment.children() )
    {
        addComment( child, newComment );
    }

    return newComment;
}


void CommentsModel::loadData()
{
    // TODO: ~/.gluon/games/$gamebundle/* will be used later
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );

    if( QFile::exists(gluonDir.absoluteFilePath( "comments.gdl" )) )
        m_rootNode = GluonCore::GDLHandler::instance()->parseGDL( gluonDir.absoluteFilePath( "comments.gdl" ) ).at( 0 );
    else
        qDebug() << "File does not exist: " << gluonDir.absoluteFilePath( "comments.gdl" );
}

void CommentsModel::saveData()
{
    qDebug() << "Saving data!";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );
    QString filename = gluonDir.absoluteFilePath( "comments.gdl" );

    QFile dataFile( filename );
    if( !dataFile.open( QIODevice::WriteOnly ) )
        qDebug() << "Cannot open the comments file!";

    QList<const GluonObject*> comments;
    comments.append( m_rootNode );
    QTextStream dataWriter( &dataFile );
    dataWriter << GluonCore::GDLHandler::instance()->serializeGDL( comments );
    dataFile.close();
    qDebug() << "Saved";
}

CommentsModel::~CommentsModel()
{
    saveData();     //Save data before exiting
    delete m_rootNode;
}

QVariant CommentsModel::data( const QModelIndex& index, int role ) const
{
    if( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        GluonObject* node;
        node = static_cast<GluonObject*>( index.internalPointer() );

        return node->property( m_columnNames.at(index.column()).toUtf8() );
    }
    else if ( role >= Qt::UserRole )
    {
        GluonObject* node;
        node = static_cast<GluonObject*>( index.internalPointer() );

        return node->property( m_columnNames.at(role - Qt::UserRole).toUtf8() );
    }
    return QVariant();
}

int CommentsModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return 5;
}

int CommentsModel::rowCount( const QModelIndex& parent ) const
{
    GluonObject* parentItem;
    if( parent.column() > 0 )
        return 0;

    if( !parent.isValid() )
        parentItem = m_rootNode;
    else
        parentItem = static_cast<GluonObject*>( parent.internalPointer() );

    return parentItem->children().count();
}

QModelIndex CommentsModel::parent( const QModelIndex& child ) const
{
    if( !child.isValid() )
        return QModelIndex();

    GluonObject* childItem = static_cast<GluonObject*>( child.internalPointer() );
    GluonObject* parentItem = qobject_cast<GluonObject*> ( childItem->parent() );

    if( parentItem == m_rootNode )
        return QModelIndex();

    GluonObject* grandParentItem = qobject_cast<GluonObject*>( parentItem->parent() );
    if( !grandParentItem )
        return QModelIndex();

    return createIndex( grandParentItem->children().indexOf( parentItem ), 0, parentItem );
}

QModelIndex CommentsModel::index( int row, int column, const QModelIndex& parent ) const
{
    if( !hasIndex( row, column, parent ) )
        return QModelIndex();

    GluonObject* parentItem;

    if( !parent.isValid() )
        parentItem = m_rootNode;
    else
        parentItem = static_cast<GluonObject*>( parent.internalPointer() );

    GluonObject* childItem = parentItem->child( row );
    if( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}

QVariant CommentsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return m_columnNames.at( section );

    return QVariant();
}

Qt::ItemFlags CommentsModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags( index );
}

bool CommentsModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if( index.isValid() && role == Qt::EditRole )
    {
        GluonObject* node;
        node = static_cast<GluonObject*>( index.internalPointer() );

        node->setProperty( m_columnNames.at(index.column()).toUtf8(), value );
        emit dataChanged( index, index );
        return true;
    }

    return false;
}

bool CommentsModel::insertRows( int row, int count, const QModelIndex& parent )
{
    if( count != 1 )  // Do not support more than one row at a time
    {
        qDebug() << "Can insert only one comment at a time";
        return false;
    }
    if( row != rowCount( parent ) )
    {
        qDebug() << "Can only add a comment to the end of existing comments";
        return false;
    }

    beginInsertRows( parent, row, row );
    GluonObject* parentNode;
    parentNode = static_cast<GluonObject*>( parent.internalPointer() );

    GluonObject* newNode = new GluonObject( "Comment", parentNode );
    parentNode->addChild( newNode );
    endInsertRows();

    return true;
}

bool CommentsModel::isOnline()
{
    return m_isOnline;
}

void CommentsModel::uploadComment( const QModelIndex& parentIndex, const QString& subject, const QString& message )
{
    GluonObject* parentNode = static_cast<GluonObject*>( parentIndex.internalPointer() );
    Attica::PostJob* job =
        AtticaManager::instance()->provider().addNewComment( Attica::Comment::ContentComment,
                "128637", "0", parentNode->name(), subject,
                message );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( addCommentFinished( Attica::BaseJob* ) ) );
    job->start();
}

#include "commentsmodel.moc"
