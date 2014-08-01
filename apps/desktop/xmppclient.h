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

#include <QXmppClient.h>

class XmppClient : public QXmppClient
{
    Q_OBJECT

public:
    XmppClient(QObject *parent = 0);
    Q_INVOKABLE void createAccount(QString name, QString username, QString email, QString password);
    Q_INVOKABLE bool isReady();
    ~XmppClient();

public slots:
    void connectedSuccess();

private:
    bool ready;
};

#endif // XMPPCLIENT_H

