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
 
#include "rostermodel.h"
#include "rosteritem.h"
#include "xmppclient.h"

#include <QtCore/QStringList>
#include <QtCore/QDebug>

#include <QXmppClient.h>
#include <QXmppRosterManager.h>
#include <QXmppPresence.h>

class RosterModel::Private
{
    public:
    Private()
    {
    }
    
    QStringList m_columnNames;
    QList<RosterItem*> m_nodes;
    XmppClient * m_xmpp;
};

RosterModel::RosterModel( QObject* parent )
    : QAbstractListModel( parent )
    , d(new Private)
{
    d->m_columnNames << tr( "Name" ) << tr( "StatusText" ) << tr( "StatusType" ) << tr( "PresenceType" );
    
    //retrieving xmpp singleton
    d->m_xmpp = XmppClient::getInstance();
    
    //xmpp client
    connect(d->m_xmpp, SIGNAL(loggedOut()), SLOT(onLoggedOut()));
    //roster
    connect(&d->m_xmpp->rosterManager(), SIGNAL(rosterReceived()), SLOT(updateRoster()));
    connect(&d->m_xmpp->rosterManager(), SIGNAL(presenceChanged(QString,QString)), SLOT(presenceChanged(QString,QString)));
    
    //then updating roster
    updateRoster();
}

/**
 * roles override
 */
QHash<int, QByteArray> RosterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[StatusTextRole] = "statusText";
    roles[StatusTypeRole] = "statusType";
    roles[PresenceTypeRole] = "presenceType";
    roles[PresenceRole] = "presence";
    return roles;
}

/**
 * Look in the list if we have RosterItem(bareJid) contact.
 * If we don't, create a new RosterItem and add it.
 * 
 * Complexity is linear for now, but we're usually check short lists.
 * 
 * @param   bareJid The user we're looking for
 * @return  The item we were looking for
 */
RosterItem* RosterModel::getOrCreateItem(const QString& bareJid)
{
    //look in the list
    for(int i=0; i<d->m_nodes.count(); i++){
        if(d->m_nodes.at(i)->name() == bareJid){
            return d->m_nodes.at(i);
        }
    }
    
    //if not found, add it and return
    RosterItem* item = new RosterItem(bareJid);
    d->m_nodes.append(item);
    return item;
}

/**
 * Find the position of the item named bareJid
 * 
 * @return position of item or -1 if not found
 */
int RosterModel::positionOfItem(const QString& bareJid)
{
    //look in the list
    for(int i=0; i<d->m_nodes.count(); i++){
        if(d->m_nodes.at(i)->name() == bareJid){
            return i;
        }
    }
    
    return -1;
}

/**
 * Update contact status in chat.
 * e.g. Offline, Available, Busy
 * 
 * @param   bareJid     contact jabber id
 * @param   presences   all presences for contact
 */
void RosterModel::updatePresence(const QString& bareJid, const QMap<QString, QXmppPresence>& presences)
{
    RosterItem * item = getOrCreateItem(bareJid);
    int position = positionOfItem(bareJid);
    
    if(position != -1 ){ //this is very unlikely to happen since the object is created anyway
        if (!presences.isEmpty()){
            item->setPresence(*presences.begin());
            qDebug() << "RosterModel: presence set to online for " << bareJid;
            dataHasChanged();
        } else {
            item->setPresence(QXmppPresence(QXmppPresence::Unavailable));
            qDebug() << "RosterModel: presence set to offline for " << bareJid;
            dataHasChanged();
        }
    }
}

/**
 * Update name of the contact
 */
void RosterModel::updateRosterEntry(const QString& bareJid, const QXmppRosterIq::Item& rosterEntry)
{
    if(!rosterEntry.name().isEmpty()){
        getOrCreateItem(bareJid)->setName(rosterEntry.name());
    }
}

/**
 * Only updates roster (contact being in list or not),
 * not presences (chat status, names).
 */
void RosterModel::updateRoster()
{
    clear();
    beginResetModel();
    
    QStringList jidsList = d->m_xmpp->rosterManager().getRosterBareJids();
    
    for (int i=0; i<jidsList.count(); i++) {
        QString bareJid = jidsList.at(i);
        qDebug() << bareJid;
        
        RosterItem * ri = new RosterItem(bareJid);
        //adding node to model
        d->m_nodes.append(ri);
    }
    
    endResetModel();
}

void RosterModel::presenceChanged(const QString& bareJid, const QString& resource)
{
    if(bareJid == d->m_xmpp->configuration().jidBare())
        return;
    
    QString jid = bareJid + "/" + resource;
    QMap<QString, QXmppPresence> presences = d->m_xmpp->rosterManager().getAllPresencesForBareJid(bareJid);
    updatePresence(bareJid, presences);
}

RosterModel::~RosterModel()
{
}

/**
 * Call it when model has changed data internally.
 * TODO: update only actually changed cells
 */
void RosterModel::dataHasChanged()
{
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(QModelIndex()) -1,0);

    QVector<int> changedRoles;
    changedRoles.append(StatusTypeRole);
    changedRoles.append(StatusTextRole);
    changedRoles.append(PresenceRole);
    emit dataChanged(topLeft, bottomRight, changedRoles);
}

QVariant RosterModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() >= rowCount())
        return QVariant();
 
    switch (role) {
        case NameRole:
            return d->m_nodes.at(index.row())->name();
        case StatusTextRole:
            return d->m_nodes.at(index.row())->statusText();
        case StatusTypeRole:
            return d->m_nodes.at(index.row())->statusType();
        case PresenceTypeRole:
            return d->m_nodes.at(index.row())->presenceType();
        case PresenceRole:
            return d->m_nodes.at(index.row())->presence();
    }
 
    return QVariant();
}

int RosterModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return d->m_nodes.count();
}
 
QVariant RosterModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return d->m_columnNames.at( section );
 
    return QVariant();
}

Qt::ItemFlags RosterModel::flags( const QModelIndex& index ) const
{
    if( !index.isValid() )
        return Qt::ItemIsEnabled;
 
    return QAbstractItemModel::flags( index );
}

void RosterModel::onLoggedOut()
{
    beginResetModel();
    clear();
    endResetModel();
}

void RosterModel::clear()
{
    d->m_nodes.clear();
}
