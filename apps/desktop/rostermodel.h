/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2014 Claudio Desideri <happy.snizzo@gmail.com>
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
 
#ifndef ROSTERMODEL_H
#define ROSTERMODEL_H

//xmpp
#include <QXmppPresence.h>
#include <QXmppRosterIq.h>

#include <QtCore/QAbstractListModel>
class RosterItem;

class RosterModel : public QAbstractListModel
{
        Q_OBJECT

    public:
        enum Roles
        {
            NameRole = Qt::UserRole,
            StatusTextRole,
            StatusTypeRole,
            PresenceTypeRole,
            PresenceRole
        };

        explicit RosterModel( QObject* parent = 0 );
        virtual ~RosterModel();

        virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
        virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
        virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        virtual Qt::ItemFlags flags( const QModelIndex& index ) const;
        QHash<int, QByteArray> roleNames() const;
        
        RosterItem* getOrCreateItem(const QString& bareJid);
        int positionOfItem(const QString& bareJid);
        void updatePresence(const QString& bareJid, const QMap<QString, QXmppPresence>& presences);
        void updateRosterEntry(const QString& bareJid, const QXmppRosterIq::Item& rosterEntry);
        void dataHasChanged();

    private Q_SLOTS:
        void updateRoster();
        void onLoggedOut();
        void presenceChanged(const QString& bareJid, const QString& resource);

    private:
        void clear();

        class Private;
        Private* const d;
};
 
#endif // ROSTERMODEL_H