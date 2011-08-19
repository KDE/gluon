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

#include "commentslistjob.h"

#include <attica/provider.h>
#include <attica/listjob.h>
#include <attica/comment.h>

using namespace GluonPlayer;

class CommentItem::Private
{
    public:
        Private()
            : score( 0 )
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
    , d( new Private )
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

class CommentsListJob::Private
{
    public:
        Private()
            : page( 0 )
            , pageSize( 0 )
        {
        }

        QString id;
        int page;
        int pageSize;
        QString parentId;
        QString subject;
        QString message;
        QList<QObject*> commentsList;
};

CommentsListJob::CommentsListJob( Attica::Provider* provider, const QString& id, int page, int pageSize )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
    d->page = page;
    d->pageSize = pageSize;
}

CommentsListJob::~CommentsListJob()
{
    delete d;
}

void CommentsListJob::startSocialService()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::ListJob<Attica::Comment> *job = provider()->requestComments( Attica::Comment::ContentComment,
                                            d->id, "0", d->page, d->pageSize );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedCommentList( Attica::BaseJob* ) ) );
    job->start();
}

void CommentsListJob::processFetchedCommentList( Attica::BaseJob* job )
{
    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment> *>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        foreach( const Attica::Comment & comment, commentsJob->itemList() )
        {
            CommentItem* newComment = new CommentItem( comment.id(), comment.subject(), comment.text(),
                    comment.user(), comment.date(), comment.score(), this );
            d->commentsList.append( newComment );
            if( comment.childCount() )
            {
                addChildren( newComment, comment );
            }
        }

        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant CommentsListJob::data()
{
    return QVariant::fromValue( d->commentsList );
}

void CommentsListJob::addChildren( CommentItem* parentCommentItem, const Attica::Comment& parentComment )
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

Q_DECLARE_METATYPE( QList<QObject*> )

#include "commentslistjob.moc"
