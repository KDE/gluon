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
 
#include "personsmodel.h"
 
#include "serviceprovider.h"
#include <personslistjob.h>
#include <getfriendsjob.h>
 
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
 
class PersonsModel::Private
{
    public:
    Private()
    {
    }
    
    QStringList m_columnNames;
    QList<PersonItem*> m_nodes;
    QList<PersonItem*> m_friends;
};
 
PersonsModel::PersonsModel( QObject* parent )
    : QAbstractListModel( parent )
    , d(new Private)
{
    d->m_columnNames << tr( "Id" ) << tr( "Firstname" ) << tr( "Lastname" );
    
    fetchFriends();
}

QHash<int, QByteArray> PersonsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "personid";
    roles[FirstnameRole] = "firstname";
    roles[LastnameRole] = "lastname";
    roles[IsFriend] = "isfriend";
    return roles;
}

/*
 * Getting self friends
 */
void PersonsModel::fetchFriends( )
{
    GetFriendsJob *friendsListJob = ServiceProvider::instance()->fetchFriends();
    if(friendsListJob){
        connect(friendsListJob, SIGNAL(succeeded()), SLOT(processFetchedFriends()));
        connect(friendsListJob, SIGNAL(failed()), SIGNAL(personListFetchFailed()));
        friendsListJob->start();
    }
}
 
void PersonsModel::processFetchedFriends()
{
    d->m_friends = qobject_cast<GetFriendsJob*>(sender())->data().value< QList<PersonItem*> >();
    qDebug() << d->m_friends.count() << " self friends successfully fetched from the server!";
}

/*
 * Getting generic by nickname people
 */
void PersonsModel::searchByName( const QString& name )
{
    clear();
    PersonsListJob *personListJob = ServiceProvider::instance()->fetchPersonsByName(name);
    connect(personListJob, SIGNAL(succeeded()), SLOT(processFetchedPersons()));
    connect(personListJob, SIGNAL(failed()), SIGNAL(personListFetchFailed()));
    personListJob->start();
}
 
void PersonsModel::processFetchedPersons()
{
    beginResetModel();
    d->m_nodes = qobject_cast<PersonsListJob*>(sender())->data().value< QList<PersonItem*> >();
    endResetModel();
    qDebug() << d->m_nodes.count() << " persons Successfully Fetched from the server!";
    
    if(!d->m_friends.empty()){
        qDebug() << "ci sono gli amici";
    }
}

PersonsModel::~PersonsModel()
{
}

QVariant PersonsModel::data( const QModelIndex& index, int role ) const
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
        case IsFriend:
            return d->m_nodes.at(index.row())->isFriend();
    }
 
    return QVariant();
}
 
int PersonsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_nodes.count();
}
 
QVariant PersonsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return d->m_columnNames.at( section );
 
    return QVariant();
}
 
Qt::ItemFlags PersonsModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;
 
    return QAbstractItemModel::flags( index );
}
 
void PersonsModel::clear()
{
    d->m_nodes.clear();
}
