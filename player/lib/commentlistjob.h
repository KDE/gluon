/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUONPLAYER_COMMENTLISTJOB_H
#define GLUONPLAYER_COMMENTLISTJOB_H

#include <QtCore/QDateTime>

namespace Attica
{
    class Comment;
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class CommentItem : public QObject
    {
            Q_OBJECT
        public:
            CommentItem( const QString& id, const QString& subject, const QString& text,
                        const QString& user, const QDateTime& dateTime, int score, QObject* parent = 0 );
            virtual ~CommentItem();

            QString id() const;
            QString subject() const;
            QString text() const;
            QString user() const;
            QDateTime dateTime() const;
            int score() const;

        private:
            class Private;
            Private* const d;
    };

    class CommentListJob : public QObject
    {
            Q_OBJECT
        public:
            CommentListJob( Attica::Provider* provider, const QString& id, int page, int pageSize,
                                          QObject* parent = 0 );
            CommentListJob( Attica::Provider* provider, const QString& id, const QString& parentId,
                                          const QString& subject, const QString& message, QObject* parent = 0 );
            virtual ~CommentListJob();

        Q_SIGNALS:
            void commentListFetchFinished( QList<CommentItem*> comments );
            void commentListFetchFailed();
            void commentListUploadFinished();
            void commentListUploadFailed();

        private Q_SLOTS:
            void fetchCommentList();
            void uploadCommentList();
            void processFetchedCommentList( Attica::BaseJob* job );
            void uploadCommentListFinished( Attica::BaseJob* job );

        private:
            void addChildren(CommentItem *parentOcsComment, const Attica::Comment& parentComment);

            class Private;
            Private* const d;
    };
}

#endif // GLUONPLAYER_COMMENTLISTJOB_H
