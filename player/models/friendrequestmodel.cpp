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
 
#include "friendrequestmodel.h"
#include <player/friendrequestlistjob.h>
 
#include "serviceprovider.h"
 
#include <core/gluonobject.h>
#include <core/gdlserializer.h>
#include <gluon_global.h>
 
#include <attica/listjob.h>
 
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QDir>
 
using namespace GluonCore;
using namespace GluonPlayer;
 
class FriendRequestModel::Private
{
    public:
    Private()
    {
    }
    
    QStringList m_columnNames;
    QList<PersonItem*> m_nodes;
};
 
FriendRequestModel::FriendRequestModel( QObject* parent )
    : QAbstractListModel( parent )
    , d(new Private)
{
    d->m_columnNames << tr( "Id" ) << tr( "Firstname" ) << tr( "Lastname" );
    
    fetchRequests();
}

QHash<int, QByteArray> FriendRequestModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "personid";
    roles[FirstnameRole] = "firstname";
    roles[LastnameRole] = "lastname";
    return roles;
}

/*
 * Getting generic by nickname people
 */
void FriendRequestModel::fetchRequests( )
{
    clear();
    FriendRequestListJob *personListJob = ServiceProvider::instance()->requestReceivedInvitations();
    connect(personListJob, SIGNAL(succeeded()), SLOT(processFetchedFriendRequest()));
    connect(personListJob, SIGNAL(failed()), SIGNAL(personListFetchFailed()));
    personListJob->start();
}
 
void FriendRequestModel::processFetchedFriendRequest()
{
    beginResetModel();
    d->m_nodes = qobject_cast<FriendRequestListJob*>(sender())->data().value< QList<PersonItem*> >();
    endResetModel();
    qDebug() << d->m_nodes.count() << " FriendRequest Successfully Fetched from the server!";
}

FriendRequestModel::~FriendRequestModel()
{
}

QVariant FriendRequestModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() >= rowCount())
        return QVariant();
 
    switch (role) {
        case IdRole:
            return d->m_nodes.at(index.row())->id();
        case FirstnameRole:
            return d->m_nodes.at(index.row())->firstname();
        case LastnameRole:
            return d->m_nodes.at(index.row())->lastname();
    }
 
    return QVariant();
}
 
int FriendRequestModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_nodes.count();
}
 
QVariant FriendRequestModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return d->m_columnNames.at( section );
 
    return QVariant();
}
 
Qt::ItemFlags FriendRequestModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;
 
    return QAbstractItemModel::flags( index );
}
 
void FriendRequestModel::clear()
{
    d->m_nodes.clear();
}
