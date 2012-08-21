/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 * Copyright (C) 2012 Shreya Pandit <shreya@shreyapandit.com>
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
#include <core/gluon_global.h>
#include <QDebug>
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
    newComment = 0;
    d->m_columnNames << tr( "Author" ) << tr( "Title" ) << tr( "Body" ) << tr( "DateTime" ) << tr( "Rating" );

    loadData();     // Load comments stored locally
    updateData();   // Fetch latest comments from the web service
    connect(this, SIGNAL(increment()),this,SLOT(calculateNewStuff()));
    QHash<int, QByteArray> roles;
    roles[AuthorRole] = "author";
    roles[TitleRole] = "title";
    roles[BodyRole] = "body";
    roles[DateTimeRole] = "dateTime";
    roles[RatingRole] = "rating";
    roles[DepthRole] = "depth";
    roles[ParentIdRole] = "parentId";
    setRoleNames( roles );
}

void CommentItemsModel::calculateNewStuff()
{
    newComment++;
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
    checkLast();
    emit newNotifications(newComment);
    beginResetModel();
    treeTraversal(d->m_rootNode);
    endResetModel();
    d->m_isOnline = true;
    saveData();     //Save data before exiting
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
    newComment->setProperty( "Id", comment->id().toInt() );
    newComment->setProperty( "Author", comment->user() );
    newComment->setProperty( "Title", comment->subject() );
    newComment->setProperty( "Body", comment->text() );
    newComment->setProperty( "DateTime", comment->dateTime().toString() );
    newComment->setProperty( "Rating", comment->score() );
    newComment->setProperty( "Depth", parent->property("Depth").toInt() + 1 );
    newComment->setProperty( "ParentId", parent->name() );
    d->m_nodes.append(newComment);
    commentsList.append(comment);
    
    foreach( QObject *child, comment->children() ) {
        addComment( static_cast<CommentItem*>(child), newComment );
    }

    return newComment;
}

void CommentItemsModel::checkLast()
{
     foreach(GluonCore::GluonObject* obj ,d->m_nodes) {qDebug()<<"comments in order are"<< obj->property("Body").toString();}
 
    if ((lastcachedDateTime < QDateTime::fromString(d->m_nodes.at(d->m_nodes.count()-1)->property("DateTime").toString(),Qt::TextDate) ) && (lastCachedText != d->m_nodes.at(d->m_nodes.count()-1)->property("Body").toString())) 
      {	
	if(d->m_nodes.at(d->m_nodes.count()-1)->property("ParentId").toString().toInt())
	  {
	    qDebug()<<"Aha! A new child comment, having title" <<d->m_nodes.at(d->m_nodes.count()-1)->property("Title").toString();
	    foreach( CommentItem *testParent, commentsList ) 
	    {
	     if( testParent->id().toInt() == d->m_nodes.at(d->m_nodes.count()-1)->property("ParentId").toString().toInt()){qDebug()<<" parent subject as "<<testParent->subject();}
	      
	    }
	  }
	qDebug()<<"Newest comment has date time"<< commentsList.at(commentsList.count()-1)->dateTime();
	emit increment() ;
      }
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
    return QDateTime::fromString(go1->property( "DateTime" ).toString())  < QDateTime::fromString(go2->property( "DateTime" ).toString());
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
    foreach(GluonCore::GluonObject* obj ,d->m_nodes) {qDebug()<<"comments in order are"<< obj->property("Body").toString();}
    lastcachedDateTime = QDateTime::fromString(d->m_nodes.at(d->m_nodes.count()-1)->property("DateTime").toString(),Qt::TextDate); 
    lastCachedText = d->m_nodes.at(d->m_nodes.count()-1)->property("Body").toString(); 
    qDebug()<<"Last cached comment has body"<<d->m_nodes.at(d->m_nodes.count()-1)->property("Body").toString();	//"dddmmmdyyyy"
}

void CommentItemsModel::saveData()
{
    qDebug() << "Saving data!";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );
    QString filename = gluonDir.absoluteFilePath( "comments.gdl" );

    GluonCore::GDLSerializer::instance()->write( QUrl::fromLocalFile( filename ), GluonCore::GluonObjectList() << d->m_rootNode );
}


CommentItemsModel::~CommentItemsModel()
{
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
    updateData();
}

#include "commentitemsmodel.moc"
