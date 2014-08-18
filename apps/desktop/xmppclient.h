/*
 * Copyright (C) 2014 Gluon Project
 * written by Claudio Desideri
 *
 * This file is a part of Gloun Project.
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
 */


#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

//qt
#include <QQuickItem>
//qxmpp
#include <QXmppClient.h>
#include <QXmppMessage.h>
#include <QXmppPresence.h>
#include <QXmppIq.h>

class XmppClient : public QXmppClient
{
    Q_OBJECT
    Q_PROPERTY(bool logged READ logged NOTIFY loggedChanged)

public:
    XmppClient(QObject *parent = 0);
    Q_INVOKABLE void createAccount(QString name, QString username, QString email, QString password);
    Q_INVOKABLE bool isReady();
    Q_INVOKABLE bool logged();
    Q_INVOKABLE void setLogged(bool logged);
    Q_INVOKABLE void login(QString username, QString password);
    Q_INVOKABLE void addSubscription(const QString& jid);
    Q_INVOKABLE void logout();
    Q_INVOKABLE void sendConversationMessage(QString body, QString to);
    //simple singleton implementation
    static XmppClient * getInstance(void);
    ~XmppClient();

public slots:
    void connectedSuccess();
    void onMessageReceived(const QXmppMessage &message);
    void onPresenceReceived(const QXmppPresence &presence);
    void rosterReceived();
    void presenceChanged(const QString& bareJid, const QString& resource);
    void onCreateAccountReady();
    void disconnectedSuccess();
    void onIqReceived(const QXmppIq& iq);

signals:
    void loggedIn();
    void loggedOut();
    void loggedChanged();
    void newMessage(QString from, int state, QString body);
    
private:
    //simple singleton pointer set to null
    static XmppClient * m_instance;
    //others
    bool ready;
    bool m_logged;
    bool registering;
    QString m_host;
    QString m_name;
    QString m_username;
    QString m_email;
    QString m_password;
};

#endif // XMPPCLIENT_H

