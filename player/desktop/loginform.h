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

#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <attica/providermanager.h>
#include <attica/provider.h>

class LoginForm : public QObject
{
        Q_OBJECT

    public:
        LoginForm();
        virtual ~LoginForm();
	
    protected slots:
        Q_INVOKABLE void doLogin(QString m_username, QString m_password);
        void doLogout();
        void loginDone();
        void logoutDone();
        void loginFailed();
        void initDone();
        void initFailed();
        void loadCredentials();

    private:
        void initialize();

        bool m_loggedIn;

        Attica::ProviderManager m_manager;
        Attica::Provider m_provider;
};

#endif // LOGINFORM_H
