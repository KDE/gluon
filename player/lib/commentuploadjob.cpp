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

#include "commentuploadjob.h"

#include <attica/provider.h>
#include <attica/postjob.h>
#include <attica/comment.h>

#include <QDebug>

using namespace GluonPlayer;

class CommentUploadJob::Private
{
    public:
        QString id;
        QString parentId;
        QString subject;
        QString message;
};

CommentUploadJob::CommentUploadJob( Attica::Provider* provider, const QString& id, const QString& parentId,
                                    const QString& subject, const QString& message )
    : AbstractSocialServicesJob( provider )
    , d( new Private() )
{
    d->id = id;
    d->parentId = parentId;
    d->subject = subject;
    d->message = message;
}

CommentUploadJob::~CommentUploadJob()
{
    delete d;
}

void CommentUploadJob::startSocialService()
{
    //Attica uses some weird stuff called id2 which can be "0" for our uses
    Attica::PostJob* job = provider()->addNewComment( Attica::Comment::ContentComment, d->id, "0", d->parentId,
                           d->subject, d->message );
    connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( uploadCommentFinished( Attica::BaseJob* ) ) );
    job->start();
}

void CommentUploadJob::uploadCommentFinished( Attica::BaseJob* job )
{
    Attica::PostJob* commentsJob = static_cast<Attica::PostJob*>( job );
    if( commentsJob->metadata().error() == Attica::Metadata::NoError )
    {
        qDebug() << "ERROR:" << commentsJob->metadata().error();
        emitSucceeded();
    }
    else
    {
        emitFailed();
    }
}

QVariant CommentUploadJob::data()
{
    return GluonPlayer::AbstractSocialServicesJob::data();
}

#include "commentuploadjob.moc"
