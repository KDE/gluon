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

#ifndef GLUON_PLAYER_COMMENTSMODEL_H
#define GLUON_PLAYER_COMMENTSMODEL_H

#include "lib/gluon_player_export.h"

#include <QtCore/QAbstractItemModel>

namespace GluonCore
{
    class GluonObject;
};

namespace GluonPlayer
{
    class CommentItem;

    /**
     *\brief Model which contains a list of comments
     *
     * This model can be used to obtain comments on a particular game.
     * The model looks for local data and if available loads it at startup.
     * After this, the model tries to fetch comments from the online server,
     * and if successful, uses those comments.
     * Upon exit, the model saves the fetched comments (if any) to a local file.
     *
     */
    class GLUON_PLAYER_EXPORT CommentsModel : public QAbstractItemModel
    {
            Q_OBJECT
        public:
            enum Column
            {
                AuthorRole = Qt::UserRole,
                TitleRole,
                BodyRole,
                DateTimeRole,
                RatingRole
            };

            /**
             * @param gameId The game ID which will be used to perform the lookup in the online
             * service
             */
            explicit CommentsModel( QString gameId, QObject* parent = 0 );
            virtual ~CommentsModel();
            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual QModelIndex parent( const QModelIndex& child ) const;
            virtual QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
            virtual Qt::ItemFlags flags( const QModelIndex& index ) const;
            virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );
            virtual bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() );

            /**
             * check if we are connected to the online service
             * @return true if connected, false otherwise
             */

            bool isOnline();

            /**
             * used to add and upload a new comment to the server.
             * If successful, the model reloads the comments and hence shows the new one
             * If unsuccessful, the model emits addCommentFailed()
             * @param   parentIndex     the index of the parent comment
             * @param   subject         the subject (title) of the comment
             * @param   message         the message (body) of the comment
             */
            void uploadComment( const QModelIndex& parentIndex, const QString& subject, const QString& message );

        Q_SIGNALS:
            /** signal which is emitted when the comment failed to be added
             */
            void addCommentFailed();
            void commentListFetchFailed();

        private Q_SLOTS:
            void processFetchedComments();
            void uploadCommentFinished();

        private:
            GluonCore::GluonObject* addComment( CommentItem *comment, GluonCore::GluonObject* parent );
            void updateData();
            void loadData();
            void saveData();

            class Private;
            Private* const d;
    };
}

#endif // GLUON_PLAYER_COMMENTSMODEL_H
