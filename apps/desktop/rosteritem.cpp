/*
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
 */


#include "rosteritem.h"
#include <QXmppPresence.h>
#include <QString>

class RosterItem::Private
{
    public:
        Private()
        {
        }

        QString name;
        QString statusText;
        int presenceType;
        int statusType;
};

RosterItem::RosterItem(const QString& bareJid, QObject* parent)
    : QObject( parent )
    , d( new Private )
{
    d->statusText = "Offline";
}

void RosterItem::setName(const QString& name)
{
    d->name = name;
}

QString RosterItem::name()
{
    return d->name;
}

void RosterItem::setStatusText(const QString& statusText)
{
    d->statusText = statusText;
}

QString RosterItem::statusText()
{
    return d->name;
}

void RosterItem::setPresence(const QXmppPresence &presence)
{
    // determine status text
    QString statusText = presence.statusText();
    if (statusText.isEmpty()) {
        if(presence.type() == QXmppPresence::Available)
            statusText = "Available";
        else if(presence.type() == QXmppPresence::Unavailable)
            statusText = "Offline";
    }

    // store data
    d->statusText = statusText;
    d->presenceType = static_cast<int>(presence.type());
    d->statusType = static_cast<int>(presence.availableStatusType());

    // update icon
    QString icon;
    if (presence.type() == QXmppPresence::Available) {
        switch (presence.availableStatusType())
        {
        case QXmppPresence::Online:
        case QXmppPresence::Chat:
            icon = "green";
            break;
        case QXmppPresence::Away:
        case QXmppPresence::XA:
            icon = "orange";
            break;
        case QXmppPresence::DND:
            icon = "red";
            break;
        case QXmppPresence::Invisible:
            icon = "gray";
            break;
        }
    } else {
        icon = "gray";
    }
}