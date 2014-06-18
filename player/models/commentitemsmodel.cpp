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
 
#include "commentitemsmodel.h"
 
#include "allgameitemsmodel.h"
#include "gamemanager.h"
 
#include "serviceprovider.h"
#include <commentslistjob.h>
#include <commentuploadjob.h>
 
#include <engine/gameproject.h>
 
#include <core/gluonobject.h>
#include <core/gdlserializer.h>
#include <gluon_global.h>
 
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
    d->m_rootNode = new GluonObject( "Comment", this );
    d->m_isOnline = false;
    d->m_gameId = gameId;
    d->m_columnNames << tr( "Author" ) << tr( "Title" ) << tr( "Body" ) << tr( "DateTime" ) << tr( "Rating" );
 
    loadData();     // Load comments stored locally
    updateData();   // Fetch latest comments from the web service
    
}

QHash<int, QByteArray> CommentItemsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AuthorRole] = "author";
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";
    roles[DateTimeRole] = "dateTime";
    roles[RatingRole] = "rating";
    roles[DepthRole] = "depth";
    roles[ParentIdRole] = "parentId";
    return roles;
}

void CommentItemsModel::updateData()
{
    clear();
    CommentsListJob *commentListJob = ServiceProvider::instance()->fetchCommentList(d->m_gameId, 0, 0);
    connect(commentListJob, SIGNAL(succeeded()), SLOT(processFetchedComments()));
    connect(commentListJob, SIGNAL(failed()), SIGNAL(commentListFetchFailed()));
    commentListJob->start();
}
 
void CommentItemsModel::processFetchedComments()
{
    QList<CommentItem*> list = qobject_cast<CommentsListJob*>(sender())->data().value< QList<CommentItem*> >();
    qDebug() << list.count() << " comments Successfully Fetched from the server!";
    foreach(CommentItem *comment, list) {
        addComment(comment, d->m_rootNode);
    }
 
    beginResetModel();
    treeTraversal(d->m_rootNode);
    endResetModel();
    d->m_isOnline = true;
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
 
GluonObject* CommentItemsModel::addComment( CommentItem* comment, GluonObject* parent )
{
    GluonObject* newComment = new GluonObject( comment->id(), parent );
    newComment->setProperty( "Author", comment->user() );
    newComment->setProperty( "Title", comment->subject() );
    newComment->setProperty( "Body", comment->text() );
    newComment->setProperty( "DateTime", comment->dateTime().toString() );
    newComment->setProperty( "Rating", comment->score() );
    newComment->setProperty( "Depth", parent->property("Depth").toInt() + 1 );
    newComment->setProperty( "ParentId", parent->name() );
 
    foreach( QObject *child, comment->children() ) {
        addComment( static_cast<CommentItem*>(child), newComment );
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
    AllGameItemsModel *model = qobject_cast<AllGameItemsModel*>(GameManager::instance()->allGamesModel());
    QString gameCachePath = model->data(d->m_gameId, AllGameItemsModel::CacheUriRole).toUrl().toLocalFile();
 
    GluonCore::GluonObjectList list;
    if( gameCachePath.isEmpty() || !GluonCore::GDLSerializer::instance()->read( QUrl( gameCachePath + "/comments.gdl" ), list ) )
        return;
 
    d->m_rootNode = list.at( 0 );
    treeTraversal( d->m_rootNode );
    qSort( d->m_nodes.begin(), d->m_nodes.end(), dateTimeLessThan );
}
 
void CommentItemsModel::saveData()
{
    if (d->m_gameId.isEmpty()) {
        qDebug() << "Failed to save the comment data for empty game id.";
        return;
    }
 
    qDebug() << "Saving data!";
 
    AllGameItemsModel *model = qobject_cast<AllGameItemsModel*>(GameManager::instance()->allGamesModel());
    QString gameCachePath = model->data(d->m_gameId, AllGameItemsModel::CacheUriRole).toUrl().toLocalFile();
 
    QDir gameCacheDir;
    gameCacheDir.mkpath( gameCachePath );
    gameCacheDir.cd( gameCachePath );
    QString filename = gameCacheDir.absoluteFilePath( "comments.gdl" );
 
    GluonCore::GDLSerializer::instance()->write( QUrl::fromLocalFile(filename), GluonCore::GluonObjectList() << d->m_rootNode );
}
 
CommentItemsModel::~CommentItemsModel()
{
    saveData();     //Save data before exiting
}
 
QVariant CommentItemsModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() >= rowCount())
        return QVariant();
 
    switch (role) {
        case AuthorRole:
            return d->m_nodes.at(index.row())->property( "Author" );
        case TitleRole:
            return d->m_nodes.at(index.row())->property( "Title" );
        case BodyRole:
            return d->m_nodes.at(index.row())->property( "Body" );
        case DateTimeRole:
            return d->m_nodes.at(index.row())->property( "DateTime" );
        case RatingRole:
            return d->m_nodes.at(index.row())->property( "Rating" );
        case DepthRole:
            return d->m_nodes.at(index.row())->property( "Depth" );
        case ParentIdRole:
            return d->m_nodes.at(index.row())->property( "ParentId" );
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
 
void CommentItemsModel::uploadComment( const QModelIndex& parentIndex, const QString& subject, const QString& message )
{
    uploadComment(d->m_nodes.at(parentIndex.row())->name(), subject, message);
}
 
void CommentItemsModel::uploadComment( const QString &parentId, const QString& subject, const QString& message )
{
    if( d->m_gameId.isEmpty() )
    {
        qDebug() << "Invalid game id, can't upload comment";
        return;
    } else {
        qDebug() << "id: " << parentId << " | subject:" << subject << " | message:" << message << "\n";
    }
    CommentUploadJob *commentsUploadJob = ServiceProvider::instance()->uploadComment(d->m_gameId,
                                                                                   parentId,
                                                                                   subject, message);
    connect(commentsUploadJob, SIGNAL(succeeded()), SLOT(uploadCommentFinished()));
    connect(commentsUploadJob, SIGNAL(failed()), SIGNAL(addCommentFailed()));
    commentsUploadJob->start();
}
 
QString CommentItemsModel::gameId() const
{
    return d->m_gameId;
}
 
void CommentItemsModel::setGameId( const QString& id )
{
    if (id.isEmpty())
        return;
    d->m_gameId = id;
    updateData();   // Fetch latest comments from the web serviceprovider
    emit gameIdChanged();
}
 
void CommentItemsModel::clear()
{
    if (d->m_rootNode) {
        qDeleteAll(d->m_rootNode->children());
    }
    d->m_nodes.clear();
}
 
void CommentItemsModel::uploadCommentFinished()
{
    qDebug() << "upload comment went well";
    updateData();
}
