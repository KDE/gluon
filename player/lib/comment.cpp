/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "comment.h"

#include "serviceprovider.h"

#include <attica/listjob.h>
#include <attica/comment.h>
#include <attica/provider.h>

#include <QtCore/QDebug>

using namespace GluonPlayer;

class CommentItem::Private
{
    public:
        Private()
            : score( 0 )
        {
        }

        ~Private()
        {
        }

        QString id;
        QString subject;
        QString text;
        QString user;
        QDateTime dateTime;
        int score;
};

CommentItem::CommentItem( const QString& id, const QString& subject, const QString& text, const QString& user,
                          const QDateTime& dateTime, int score, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->id = id;
    d->subject = subject;
    d->text = text;
    d->user = user;
    d->dateTime = dateTime;
    d->score = score;
}

CommentItem::~CommentItem()
{
    delete d;
}

QDateTime CommentItem::dateTime() const
{
    return d->dateTime;
}

QString CommentItem::id() const
{
    return d->id;
}

int CommentItem::score() const
{
    return d->score;
}

QString CommentItem::subject() const
{
    return d->subject;
}

QString CommentItem::text() const
{
    return d->text;
}

QString CommentItem::user() const
{
    return d->user;
}

class Comment::Private
{
    public:
        Private()
            : provider( 0 )
            , page( 0 )
            , pageSize( 0 )
        {
        }

        ~Private()
        {
        }

        Attica::Provider* provider;
        QString id;
        int page;
        int pageSize;
        QString parentId;
        QString subject;
        QString message;
};

Comment::Comment( Attica::Provider* provider, const QString& id,
                  int page, int pageSize, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->provider = provider;
    d->id = id;
    d->page = page;
    d->pageSize = pageSize;
}

Comment::Comment( Attica::Provider* provider, const QString& id, const QString& parentId,
                  const QString& subject, const QString& message, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->provider = provider;
    d->id = id;
    d->parentId = parentId;
    d->subject = subject;
    d->message = message;
}

Comment::~Comment()
{
    delete d;
}

void Comment::processFetchedComments( Attica::BaseJob* job )
{
    QList<CommentItem*> list;

    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment> *>( job );

    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Comment & comment, commentsJob->itemList() )
        {
            CommentItem* newComment = new CommentItem( comment.id(), comment.subject(), comment.text(),
                    comment.user(), comment.date(), comment.score(), this );
            list.append( newComment );

            if( comment.childCount() )
            {
                addChildren( newComment, comment );
            }
        }

        emit commentsFetched( list );
    }
    else
    {
        emit failedToFetchComments();
    }
}

void Comment::addChildren( CommentItem* parentCommentItem, const Attica::Comment& parentComment )
{
    foreach( const Attica::Comment & comment, parentComment.children() )
    {
        CommentItem* newComment = new CommentItem( comment.id(), comment.subject(),
                comment.text(), comment.user(),
                comment.date(), comment.score(),
                parentCommentItem );
        newComment->setParent( parentCommentItem );

        if( comment.children().count() )
        {
            addChildren( newComment, comment );
        }
    }
}

void Comment::uploadCommentsFinished( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment>*>( job );

    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        qDebug() << "ERROR:" << commentsJob->metadata().error();
        emit commentUploaded();
    }
    else
    {
        emit failedToUploadComment();
    }
}

void Comment::fetchComments()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::ListJob<Attica::Comment> *job = d->provider->requestComments( Attica::Comment::ContentComment,
                                            d->id, "0", d->page, d->pageSize );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedComments( Attica::BaseJob* ) ) );
    job->start();
}

void Comment::uploadComments()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::PostJob* job = d->provider->addNewComment( Attica::Comment::ContentComment, d->id, "0", d->parentId,
                           d->subject, d->message );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( uploadCommentsFinished( Attica::BaseJob* ) ) );
    job->start();
}

#include "comment.moc"
