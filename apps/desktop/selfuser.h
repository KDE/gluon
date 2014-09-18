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
 
#ifndef SELFUSER_H
#define SELFUSER_H
 
#include <attica/providermanager.h>
#include <attica/provider.h>
#include <QQuickItem>
 
class SelfUser : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
        Q_PROPERTY(bool logged READ logged WRITE setLogged NOTIFY loggedChanged)
 
    public:
        SelfUser();
        virtual ~SelfUser();
        
    protected slots:
        //login logout methods
        Q_INVOKABLE void doLogin(QString m_username, QString m_password);
        Q_INVOKABLE void doLogout();
        
        Q_INVOKABLE QString username();
        Q_INVOKABLE void setUsername(QString username);
        
        Q_INVOKABLE bool logged();
        Q_INVOKABLE void setLogged(bool logged);
        
        void loginDone();
        void logoutDone();
        void loginFailed();
        
        //registration methods
        Q_INVOKABLE void addUser(QString login, QString password, QString password2, QString firstname, QString lastname, QString email);
        void registrationComplete();
        void registrationFailed(int errorcode);
    
    signals:
        //login logout
        void loginCompleted();
        void loginFail();
        void logoutCompleted();
        
        //qml
        void usernameChanged();
        void loggedChanged();
        
        //registration
        void registrationProcessCompleted(QString message);
    
    private:
        bool m_logged;
        QString m_username;
 
        Attica::ProviderManager m_manager;
        Attica::Provider m_provider;
};
 
#endif // LOGINFORM_H 
