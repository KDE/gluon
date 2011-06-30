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

#include "ocscommentsprovider.h"

#include "ocsprovider.h"

#include <attica/listjob.h>
#include <attica/comment.h>
#include <attica/provider.h>

#include <QtCore/QDebug>

using namespace GluonPlayer;

class OcsComment::Private
{
public:
    Private()
        : score(0)
    {
    }

    QString id;
    QString subject;
    QString text;
    QString user;
    QDateTime dateTime;
    int score;
};

OcsComment::OcsComment(const QString& id, const QString& subject, const QString& text, const QString& user,
                        const QDateTime& dateTime, int score, QObject* parent)
    : QObject (parent)
    , d(new Private())
{
    d->id = id;
    d->subject = subject;
    d->text = text;
    d->user = user;
    d->dateTime = dateTime;
    d->score = score;
}

OcsComment::~OcsComment()
{
    delete d;
}

QDateTime OcsComment::dateTime() const
{
    return d->dateTime;
}

QString OcsComment::id() const
{
    return d->id;
}

int OcsComment::score() const
{
    return d->score;
}

QString OcsComment::subject() const
{
    return d->subject;
}

QString OcsComment::text() const
{
    return d->text;
}

QString OcsComment::user() const
{
    return d->user;
}

class OcsCommentsProvider::Private
{
public:
    Private()
        : provider(0)
        , page(0)
        , pageSize(0)
    {
    }

    Attica::Provider *provider;
    QString id;
    int page;
    int pageSize;
    QString parentId;
    QString subject;
    QString message;
};

OcsCommentsProvider::OcsCommentsProvider(Attica::Provider* provider, const QString& id,
                                          int page, int pageSize, QObject* parent)
    : QObject (parent)
    , d(new Private())
{
    d->provider = provider;
    d->id = id;
    d->page = page;
    d->pageSize = pageSize;
}

OcsCommentsProvider::OcsCommentsProvider(Attica::Provider* provider, const QString& id, const QString& parentId,
                                          const QString& subject, const QString& message, QObject* parent)
    : QObject (parent)
    , d(new Private())
{
    d->provider = provider;
    d->id = id;
    d->parentId = parentId;
    d->subject = subject;
    d->message = message;
}

OcsCommentsProvider::~OcsCommentsProvider()
{
    delete d;
}

void OcsCommentsProvider::processFetchedComments(Attica::BaseJob* job)
{
    QList<OcsComment*> list;

    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment> *>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError ) {
        foreach(const Attica::Comment& comment, commentsJob->itemList()) {
            OcsComment *newComment = new OcsComment(comment.id(), comment.subject(), comment.text(),
                                                    comment.user(), comment.date(), comment.score(), this);
            list.append(newComment);
            if (comment.childCount()) {
                addChildren(newComment, comment);
            }
        }

        emit commentsFetched(list);
    } else {
        emit failedToFetchComments();
    }
}

void OcsCommentsProvider::addChildren(OcsComment* parentOcsComment, const Attica::Comment& parentComment)
{
    foreach (const Attica::Comment& comment, parentComment.children()) {
        OcsComment *newComment = new OcsComment(comment.id(), comment.subject(),
                                                comment.text(), comment.user(),
                                                comment.date(), comment.score(),
                                                parentOcsComment);
        newComment->setParent(parentOcsComment);
        if (comment.children().count()) {
            addChildren(newComment, comment);
        }
    }
}

void OcsCommentsProvider::uploadCommentsFinished(Attica::BaseJob* job)
{
    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment>*>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError ) {
        qDebug() << "ERROR " << commentsJob->metadata().error();
        emit commentUploaded();
    } else {
        emit failedToUploadComment();
    }
}

void OcsCommentsProvider::fetchComments()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::ListJob<Attica::Comment> *job = d->provider->requestComments(Attica::Comment::ContentComment,
                                                                        d->id, "0", d->page, d->pageSize);
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedComments(Attica::BaseJob*)));
    job->start();
}

void OcsCommentsProvider::uploadComments()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::PostJob* job = d->provider->addNewComment( Attica::Comment::ContentComment, d->id, "0", d->parentId,
                                                     d->subject, d->message );
    connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(uploadCommentsFinished(Attica::BaseJob*)));
    job->start();
}

#include "ocscommentsprovider.moc"
