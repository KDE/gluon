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


#ifndef ROSTERITEM_H
#define ROSTERITEM_H

#include <QObject>
#include "QXmppPresence.h"

/*
 * IMPLEMENTA DPOINTER CLASS E AGGIUSTA L'ITEM, FAI IL MODEL E FAI FUNZIONARE STA CEPPA DE CHATTE
 */

class RosterItem : public QObject
{
    public:

        RosterItem(const QString& bareJid, QObject* parent = 0);

        void setPresence(const QXmppPresence &presence);
        void setName(const QString& name);
        QString name();
        void setStatusText(const QString& statusText);
        QString statusText();
        int presenceType();
        int statusType();
        
        
    private:
        class Private;
        Private* const d;
};
#endif // ROSTERITEM_H
