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
 
#ifndef GLUON_PLAYER_PERSONSMODEL_H
#define GLUON_PLAYER_PERSONSMODEL_H
 
#include "../gluon_player_export.h"
 
#include <attica/providermanager.h>
#include <attica/provider.h>
#include <attica/person.h>
 
#include <QtCore/QAbstractListModel>
 
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
    class PersonItem;
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
    class GLUON_PLAYER_EXPORT PersonsModel : public QAbstractListModel
    {
            Q_OBJECT
            //Q_PROPERTY( QString gameId READ gameId WRITE setGameId NOTIFY gameIdChanged )
 
        public:
            enum Roles
            {
                IdRole = Qt::UserRole,
                FirstnameRole,
                LastnameRole
            };
 
            /**
             * @param gameId The game ID which will be used to perform the lookup in the online
             * service
             */
            explicit PersonsModel( QObject* parent = 0 );
            virtual ~PersonsModel();
 
            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
            virtual Qt::ItemFlags flags( const QModelIndex& index ) const;
            QHash<int, QByteArray> roleNames() const;
            
            Q_INVOKABLE void searchByName(const QString& name);
 
        private Q_SLOTS:
            //void addCommentFinished( Attica::BaseJob* job );
            void processFetchedPersons();
            //void uploadCommentFinished();
 
        Q_SIGNALS:
            void personListFetchFailed();
 
        private:
            void clear();
 
            class Private;
            Private* const d;
    };
}
 
#endif // GLUON_PLAYER_PERSONSMODEL_H