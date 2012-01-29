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

#include "commentsmodel.h"

#include "lib/serviceprovider.h"
#include "lib/commentslistjob.h"
#include "lib/commentuploadjob.h"

#include <engine/gameproject.h>

#include <core/gluonobject.h>
#include <core/gdlserializer.h>
#include <core/gluon_global.h>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

using namespace GluonCore;
using namespace GluonPlayer;

class CommentsModel::Private
{
    public:
    Private()
    {
    }

    GluonCore::GluonObject* m_rootNode;
    bool m_isOnline;
    QString m_gameId;
    QList<GluonObject*> flatComments;
};

CommentsModel::CommentsModel( QObject* parent )
    : QAbstractItemModel( parent )
    , d(new Private)
{
    d->m_rootNode = new GluonObject( "" );
    d->m_rootNode->setProperty("Depth", -1);
    d->m_isOnline = false;

    QHash<int, QByteArray> roleNames;
    roleNames[AuthorRole] = "AuthorRole";
    roleNames[TitleRole] = "TitleRole";
    roleNames[BodyRole] = "BodyRole";
    roleNames[DateTimeRole] = "DateTimeRole";
    roleNames[RatingRole] = "RatingRole";
    roleNames[DepthRole] = "DepthRole";
    roleNames[ParentIdRole] = "ParentIdRole";
    setRoleNames(roleNames);
}

void CommentsModel::processFetchedComments()
{
    QList<CommentItem*> list = qobject_cast<CommentsListJob*>(sender())->data().value< QList<CommentItem*> >();
    qDebug() << list.count() << " comments Successfully Fetched from the server!";
    foreach(CommentItem *comment, list) {
        addComment(comment, d->m_rootNode);
    }
    d->m_isOnline = true;
    reset();
}

GluonObject* CommentsModel::addComment( CommentItem* comment, GluonObject* parent )
{
    GluonObject* newComment = new GluonObject( comment->id(), parent );
    newComment->setProperty( "Author", comment->user() );
    newComment->setProperty( "Title", comment->subject() );
    newComment->setProperty( "Body", comment->text() );
    newComment->setProperty( "DateTime", comment->dateTime().toString() );
    newComment->setProperty( "Rating", comment->score() );
    newComment->setProperty( "Depth", parent->property("Depth").toInt() + 1 );
    newComment->setProperty( "ParentId", parent->name() );
    d->flatComments.append( newComment );

    foreach( QObject *child, comment->children() ) {
        addComment( static_cast<CommentItem*>(child), newComment );
    }

    return newComment;
}

void CommentsModel::loadData()
{
    // TODO: ~/.gluon/games/$gamebundle/* will be used later
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );

    GluonCore::GluonObjectList list;
    if( !GluonCore::GDLSerializer::instance()->read( gluonDir.absoluteFilePath( "comments.gdl" ), list ) )
        return;

    d->m_rootNode = list.at( 0 );
}

void CommentsModel::saveData()
{
    qDebug() << "Saving data!";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath( GluonEngine::projectSuffix + "/games/" );
    gluonDir.cd( GluonEngine::projectSuffix + "/games/" );
    QString filename = gluonDir.absoluteFilePath( "comments.gdl" );

    GluonCore::GDLSerializer::instance()->write( QUrl::fromLocalFile( filename ), GluonCore::GluonObjectList() << d->m_rootNode );
}

CommentsModel::~CommentsModel()
{
    saveData();     //Save data before exiting
    delete d->m_rootNode;
}

QVariant CommentsModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() >= rowCount())
        return QVariant();

    switch (role) {
        case AuthorRole:
            return d->flatComments.at(index.row())->property( "Author" );
        case TitleRole:
            return d->flatComments.at(index.row())->property( "Title" );
        case BodyRole:
            return d->flatComments.at(index.row())->property( "Body" );
        case DateTimeRole:
            return d->flatComments.at(index.row())->property( "DateTime" );
        case RatingRole:
            return d->flatComments.at(index.row())->property( "Rating" );
        case DepthRole:
            return d->flatComments.at(index.row())->property( "Depth" );
        case ParentIdRole:
            return d->flatComments.at(index.row())->property( "ParentId" );
    }

    return QVariant();
}

int CommentsModel::columnCount( const QModelIndex& /* parent */ ) const
{
    return 1;
}

int CommentsModel::rowCount( const QModelIndex& parent ) const
{
    return d->flatComments.count();
}

QModelIndex CommentsModel::parent( const QModelIndex& child ) const
{
    return QModelIndex();
}

QModelIndex CommentsModel::index( int row, int column, const QModelIndex& parent ) const
{
    return createIndex( row, column );
}

bool CommentsModel::isOnline()
{
    return d->m_isOnline;
}

void CommentsModel::uploadComment( const QString &parentId, const QString& subject, const QString& message )
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

void CommentsModel::updateData()
{
    clear();
    CommentsListJob *commentListJob = ServiceProvider::instance()->fetchCommentList(d->m_gameId, 0, 0);
    connect(commentListJob, SIGNAL(succeeded()), SLOT(processFetchedComments()));
    connect(commentListJob, SIGNAL(failed()), SIGNAL(commentListFetchFailed()));
    commentListJob->start();
}

void CommentsModel::uploadCommentFinished()
{
    updateData();
}

QString CommentsModel::gameId() const
{
    return d->m_gameId;
}

void CommentsModel::setGameId( const QString& id )
{
    d->m_gameId = id;
    updateData();   // Fetch latest comments from the web serviceprovider
    emit gameIdChanged();
}

void CommentsModel::clear()
{
    if (d->m_rootNode) {
        qDeleteAll(d->m_rootNode->children());
    }
    d->flatComments.clear();
}

#include "commentsmodel.moc"
