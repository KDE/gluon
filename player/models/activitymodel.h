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
 
#ifndef GLUON_PLAYER_ACTIVITYMODEL_H
#define GLUON_PLAYER_ACTIVITYMODEL_H
 
#include "../gluon_player_export.h"
 
#include <attica/providermanager.h>
#include <attica/provider.h>
#include <attica/activity.h>
 
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
    class ActivityItem;
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
    class GLUON_PLAYER_EXPORT ActivityModel : public QAbstractListModel
    {
            Q_OBJECT
            Q_PROPERTY( bool empty READ empty WRITE setEmpty NOTIFY emptyChanged )
 
        public:
            enum Roles
            {
                IdRole = Qt::UserRole,
                FirstnameRole,
                LastnameRole,
                MessageRole
            };
            
            explicit ActivityModel( QObject* parent = 0 );
            virtual ~ActivityModel();
 
            virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
            virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
            virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
            virtual Qt::ItemFlags flags( const QModelIndex& index ) const;
            QHash<int, QByteArray> roleNames() const;
            
            bool empty();
            void setEmpty(bool empty);
            
            Q_INVOKABLE void postActivity( const QString& message );
            
        public Q_SLOTS:
            Q_INVOKABLE void fetchActivities( );
            
        private Q_SLOTS:
            void processFetchedActivity();
            void processPostedActivity();
 
        Q_SIGNALS:
            void activityListFetchFailed();
            void activityPostFailed();
            
            void emptyChanged();
 
        private:
            void clear();
 
            class Private;
            Private* const d;
    };
}
 
#endif // GLUON_PLAYER_ACTIVITYMODEL_H