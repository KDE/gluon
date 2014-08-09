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
 
#include "activitymodel.h"
#include <player/activitylistjob.h>
#include <player/postactivityjob.h>
 
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
 
class ActivityModel::Private
{
    public:
    Private()
    {
    }
    
    QStringList m_columnNames;
    QList<ActivityItem*> m_nodes;
};
 
ActivityModel::ActivityModel( QObject* parent )
    : QAbstractListModel( parent )
    , d(new Private)
{
    d->m_columnNames << tr( "Id" ) << tr( "Firstname" ) << tr( "Lastname" );
    
    fetchActivities ();
}

QHash<int, QByteArray> ActivityModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "personid";
    roles[FirstnameRole] = "firstname";
    roles[LastnameRole] = "lastname";
    roles[MessageRole] = "message";
    return roles;
}

/*
 * Getting generic by nickname people
 */
void ActivityModel::fetchActivities( )
{
    clear();
    ActivityListJob *activityListJob = ServiceProvider::instance()->requestActivities();
    connect(activityListJob, SIGNAL(succeeded()), SLOT(processFetchedActivity()));
    connect(activityListJob, SIGNAL(failed()), SIGNAL(activityListFetchFailed()));
    activityListJob->start();
}
 
void ActivityModel::processFetchedActivity()
{
    beginResetModel();
    d->m_nodes = qobject_cast<ActivityListJob*>(sender())->data().value< QList<ActivityItem*> >();
    endResetModel();
    qDebug() << d->m_nodes.count() << " activities Successfully Fetched from the server!";
}

void ActivityModel::postActivity( const QString& message  )
{
    clear();
    PostActivityJob *activityListJob = ServiceProvider::instance()->postActivity( message );
    connect(activityListJob, SIGNAL(succeeded()), SLOT(processPostedActivity()));
    connect(activityListJob, SIGNAL(failed()), SIGNAL(activityPostFailed()));
    activityListJob->start();
}
 
void ActivityModel::processPostedActivity()
{
    fetchActivities();
}

ActivityModel::~ActivityModel()
{
}

QVariant ActivityModel::data( const QModelIndex& index, int role ) const
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
        case MessageRole:
            return d->m_nodes.at(index.row())->message();
    }
 
    return QVariant();
}
 
int ActivityModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_nodes.count();
}
 
QVariant ActivityModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return d->m_columnNames.at( section );
 
    return QVariant();
}

Qt::ItemFlags ActivityModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;
 
    return QAbstractItemModel::flags( index );
}
 
void ActivityModel::clear()
{
    d->m_nodes.clear();
}
