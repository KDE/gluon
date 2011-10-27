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

#include "commentitemsmodel.h"

#include "atticamanager.h"

#include <engine/gameproject.h>

#include <core/gluonobject.h>
#include <core/gdlserializer.h>
#include <core/gluon_global.h>

#include <attica/listjob.h>

#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QDir>

using namespace GluonCore;
using namespace GluonPlayer;

class CommentItemsModel::Private
{
    public:
    Private()
    {
    }

    GluonCore::GluonObject* m_rootNode;
    QStringList m_columnNames;
    bool m_isOnline;
    QString m_gameId;
    QList<GluonCore::GluonObject*> m_nodes;
};

CommentItemsModel::CommentItemsModel( QString gameId, QObject* parent )
    : QAbstractListModel( parent )
    , d(new Private)
{
    d->m_rootNode = new GluonObject( "Comment" );
    d->m_isOnline = false;
    d->m_gameId = gameId;
    d->m_columnNames << tr( "Author" ) << tr( "Title" ) << tr( "Body" ) << tr( "DateTime" ) << tr( "Rating" );

    loadData();     // Load comments stored locally
    updateData();   // Fetch latest comments from the web service

    QHash<int, QByteArray> roles;
    roles[AuthorRole] = "author";
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";
    roles[DateTimeRole] = "dateTime";
    roles[RatingRole] = "rating";
    setRoleNames( roles );
}

void CommentItemsModel::updateData()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        providersUpdated();
    }
    else
    {
        connect( AtticaManager::instance(), SIGNAL(gotProvider()), SLOT(providersUpdated()) );
    }
}

void CommentItemsModel::providersUpdated()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        Attica::ListJob<Attica::Comment> *job =
            AtticaManager::instance()->provider().requestComments( Attica::Comment::ContentComment,
                    d->m_gameId, "0", 0, 100 );
        connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedComments(Attica::BaseJob*)) );
        job->start();
    }
    else
    {
        qDebug() << "No providers found.";
    }
}

void CommentItemsModel::processFetchedComments( Attica::BaseJob* job )
{
    qDebug() << "Comments Successfully Fetched from the server!";

    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment> *>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        //No error, try to remove exising comments (if any)
        //and add new comments

        for( int i = 0; i < commentsJob->itemList().count(); ++i )
        {
            Attica::Comment p( commentsJob->itemList().at( i ) );
            addComment( p, d->m_rootNode );
        }

        d->m_isOnline = true;
        reset();    //Reset the model to notify views to reload comments
    }
    else
    {
        qDebug() << "Could not fetch information";
    }
}

void CommentItemsModel::addCommentFinished( Attica::BaseJob* job )
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

GluonObject* CommentItemsModel::addComment( Attica::Comment comment, GluonObject* parent )
{
    GluonObject* newComment = new GluonObject( comment.id(), parent );
    newComment->setProperty( "Author", comment.user() );
    newComment->setProperty( "Title", comment.subject() );
    newComment->setProperty( "Body", comment.text() );
    newComment->setProperty( "DateTime", comment.date().toString() );
    newComment->setProperty( "Rating", comment.score() );

    foreach( const Attica::Comment & child, comment.children() )
    {
        addComment( child, newComment );
    }

    return newComment;
}

void CommentItemsModel::treeTraversal( GluonCore::GluonObject* obj )
{
    if( !obj )
        return;

    foreach( QObject * child, obj->children() )
    {
        GluonObject* gobj = qobject_cast<GluonObject*>( child );
        if( gobj )
        {
            gobj->dumpObjectTree();
            d->m_nodes.append( gobj );
            treeTraversal( gobj );
        }
    }
}

bool dateTimeLessThan( GluonCore::GluonObject* go1, GluonCore::GluonObject* go2 )
{
    return go1->property( "DateTime" ).toString() < go2->property( "DateTime" ).toString();
}

void CommentItemsModel::loadData()
{
    // TODO: ~/.gluon/games/$gamebundle/* will be used later
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );

    GluonCore::GluonObjectList list;
    if( !GluonCore::GDLSerializer::instance()->read( QUrl( gluonDir.absoluteFilePath( "comments.gdl" ) ), list ) )
        return;

    d->m_rootNode = list.at( 0 );
    treeTraversal( d->m_rootNode );
    qSort( d->m_nodes.begin(), d->m_nodes.end(), dateTimeLessThan );
}

void CommentItemsModel::saveData()
{
    qDebug() << "Saving data!";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );
    QString filename = gluonDir.absoluteFilePath( "comments.gdl" );

    GluonCore::GDLSerializer::instance()->write( QUrl( filename ), GluonCore::GluonObjectList() << d->m_rootNode );
}

CommentItemsModel::~CommentItemsModel()
{
    saveData();     //Save data before exiting
}

QVariant CommentItemsModel::data( const QModelIndex& index, int role ) const
{
    if( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        GluonObject* node;
        node = static_cast<GluonObject*>( index.internalPointer() );

        return node->property( d->m_columnNames.at( index.column() ).toUtf8() );
    }
    else if( role >= Qt::UserRole )
    {
        return d->m_nodes.at( index.row() )->property( d->m_columnNames.at( role - Qt::UserRole ).toUtf8() );
    }
    return QVariant();
}

int CommentItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_nodes.count();
}

QVariant CommentItemsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return d->m_columnNames.at( section );

    return QVariant();
}

Qt::ItemFlags CommentItemsModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags( index );
}

bool CommentItemsModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if( index.isValid() && role == Qt::EditRole )
    {
        GluonObject* node;
        node = static_cast<GluonObject*>( index.internalPointer() );

        node->setProperty( d->m_columnNames.at( index.column() ).toUtf8(), value );
        emit dataChanged( index, index );
        return true;
    }

    return false;
}

bool CommentItemsModel::insertRows( int row, int count, const QModelIndex& parent )
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

bool CommentItemsModel::isOnline()
{
    return d->m_isOnline;
}

void CommentItemsModel::uploadComment( const QModelIndex& parentIndex, const QString& subject, const QString& message )
{
    GluonObject* parentNode = static_cast<GluonObject*>( parentIndex.internalPointer() );
    Attica::PostJob* job =
        AtticaManager::instance()->provider().addNewComment( Attica::Comment::ContentComment,
                d->m_gameId, "0", parentNode->name(), subject,
                message );
    connect( job, SIGNAL(finished(Attica::BaseJob*)), SLOT(addCommentFinished(Attica::BaseJob*)) );
    job->start();
}

#include "commentitemsmodel.moc"
