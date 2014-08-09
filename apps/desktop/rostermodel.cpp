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

#include <QXmppRosterManager.h>
 
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
    
    //connecting roster updates from qxmpp to model
    connect(&d->m_xmpp->rosterManager(), SIGNAL(rosterReceived()), SLOT(updateRoster()));
    connect(&d->m_xmpp->rosterManager(), SIGNAL(presenceChanged(QString,QString)), SLOT(presenceChanged(QString,QString)));
    
    //then updating roster
    updateRoster();
}

QHash<int, QByteArray> RosterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[StatusTextRole] = "statusText";
    roles[StatusTypeRole] = "statusType";
    roles[PresenceTypeRole] = "presenceType";
    return roles;
}

/* TODO: fix this to work with the model
RosterItem* RosterModel::getOrCreateItem(const QString& bareJid)
{
    for(int i=0; i<d->m_nodes.count(); i++){
        if(d->m_nodes.at(i)->name()
    }
    
    if(m_jidRosterItemMap.contains(bareJid)) {
        return m_jidRosterItemMap[bareJid];
    } else {
        rosterItem* item = new rosterItem(bareJid);
        m_jidRosterItemMap[bareJid] = item;
        appendRow(item);
        return item;
    }
}

void RosterModel::updatePresence(const QString& bareJid, const QMap<QString, QXmppPresence>& presences)
{
    rosterItem *item = getOrCreateItem(bareJid);
    if (!presences.isEmpty())
        item->setPresence(*presences.begin());
    else
        item->setPresence(QXmppPresence(QXmppPresence::Unavailable));
}

void RosterModel::updateRosterEntry(const QString& bareJid, const QXmppRosterIq::Item& rosterEntry)
{
    getOrCreateItem(bareJid)->setName(rosterEntry.name());
}
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
    /* TODO: fix changing presence
    if(bareJid == d->m_xmpp->configuration().jidBare())
        return;
    
    QString jid = bareJid + "/" + resource;
    QMap<QString, QXmppPresence> presences = d->m_xmpp->rosterManager().
                                             getAllPresencesForBareJid(bareJid);
    m_rosterItemModel.updatePresence(bareJid, presences);

    QXmppPresence& pre = presences[resource];
    */
}

RosterModel::~RosterModel()
{
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
 
void RosterModel::clear()
{
    d->m_nodes.clear();
}
