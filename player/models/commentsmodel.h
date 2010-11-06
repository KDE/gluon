/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_COMMENTSMODEL_H
#define GLUONPLAYER_COMMENTSMODEL_H

#include "gluon_player_export.h"

#include <attica/providermanager.h>
#include <attica/provider.h>

#include <QAbstractItemModel>
#include <QStringList>


namespace Attica
{
    class BaseJob;
}

namespace GluonCore
{
    class GluonObject;
};

namespace GluonPlayer
{

    /**
     *\brief Model which contains a list of comments
     *
     * This model can be used to obtain comments on a particular game.
     * The model looks for local data, and if available loads it at startup.
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
                AuthorColumn,
                TitleColumn,
                BodyColumn,
                DateTimeColumn,
                RatingColumn
            };

            CommentsModel( QObject* parent = 0 );
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
             * returns the column name of a specific column as a string
             * @param   col     the required column
             * @return the column name as string
             */
            QString columnName( const Column col ) const;

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

        private:
            GluonCore::GluonObject* rootNode;
            QStringList m_columnNames;
            bool m_isOnline;

            void updateData();
            void loadData();
            void saveData();

            GluonCore::GluonObject* addComment( Attica::Comment comment, GluonCore::GluonObject* parent );

        private slots:
            void providersUpdated();
            void processFetchedComments( Attica::BaseJob* );
            void addCommentFinished( Attica::BaseJob* job );

        signals:
            /** signal which is emitted when the comment failed to be added
             */
            void addCommentFailed();
    };
}

#endif // GLUONPLAYER_COMMENTSMODEL_H
