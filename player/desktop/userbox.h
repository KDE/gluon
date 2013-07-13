/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef USERBOX_H
#define USERBOX_H

#include <attica/providermanager.h>
#include <attica/provider.h>
#include <QDeclarativeItem>

#include <player/lib/personselfjob.h>

class UserBox : public QDeclarativeItem
{
        Q_OBJECT
    public:
        UserBox();
        virtual ~UserBox();
    
    public Q_SLOTS:
		void loadedUserData();
		Q_INVOKABLE QString username();
		Q_INVOKABLE QString firstname();
		Q_INVOKABLE QString lastname();
    
    private:
		
		GluonPlayer::PersonSelfJob* job;
        Attica::ProviderManager m_manager;
        Attica::Provider m_provider;
		
		QString m_username;
		QString m_firstname;
		QString m_lastname;
		
	signals:
		void dataLoaded();
};

#endif // USERBOX_H

