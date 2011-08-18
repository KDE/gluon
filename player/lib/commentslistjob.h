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

#ifndef GLUONPLAYER_COMMENTSLISTJOB_H
#define GLUONPLAYER_COMMENTSLISTJOB_H

#include "abstractsocialservicesjob.h"

#include <QList>

namespace Attica
{
    class BaseJob;
    class Comment;
}

class QDateTime;

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

    class CommentsListJob : public AbstractSocialServicesJob
    {
            Q_OBJECT

        public:
            CommentsListJob( Attica::Provider* provider, const QString& id, int page, int pageSize );
            virtual ~CommentsListJob();

            virtual QVariant data();

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void processFetchedCommentList( Attica::BaseJob* job );

        private:
            void addChildren( CommentItem* parentCommentItem, const Attica::Comment& parentComment );

            class Private;
            Private* const d;
    };

}

#endif // GLUONPLAYER_COMMENTSLISTJOB_H
