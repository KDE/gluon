 
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
 
#ifndef SINGLEUSER_H
#define SINGLEUSER_H
 
#include <attica/providermanager.h>
#include <attica/provider.h>
#include <QQuickItem>
 
class SingleUser : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
 
    public:
        SingleUser();
        virtual ~SingleUser();
        
//         void setImage(const QUrl &url);
//         QUrl image() const;
        
        Q_INVOKABLE void addFriend();
        Q_INVOKABLE void acceptFriendship();
        Q_INVOKABLE void declineFriendship();
        
        Q_INVOKABLE QString username() const;
        Q_INVOKABLE QString name() const;
        Q_INVOKABLE QString surname() const;
        
        Q_INVOKABLE void setUsername(const QString &username);
        Q_INVOKABLE void setName(const QString &name);
        Q_INVOKABLE void setSurname(const QString &surname);
        
    signals:
        void usernameChanged();
        void nameChanged();
        void surnameChanged();
        void friendRequestSent();
        void friendRequestFailed();
        void friendRequestAccepted();
        void friendRequestDeclined();
        void unknownError();
        
    private:
        QString m_username;
        QString m_name;
        QString m_surname;
        bool isFriend;
};
 
#endif // SINGLEUSER_H 

