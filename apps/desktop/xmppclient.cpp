/*
 * Copyright (C) 2008-2014 Gluon Project
 * written by Claudio Desideri
 *
 * This file is a part of Gluon Project.
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


#include <QCoreApplication>
#include <QDebug>

#include <QXmppLogger.h>
#include <QXmppMessage.h>
#include <QXmppRegisterIq.h>
#include <QXmppDataForm.h>
#include <QXmppIq.h>

#include "xmppclient.h"

/**
 * Attempts a connection to server when created.
 * Connection is not logged. See login() for logging.
 */
XmppClient::XmppClient(QObject *parent)
    : QXmppClient(parent)
{
    //client is not ready
    ready = false;
    
    //just do something when connected
    bool check = connect(this, SIGNAL(connected()), SLOT(connectedSuccess()));
    Q_ASSERT(check);
    Q_UNUSED(check);
    
    logger()->setLoggingType(QXmppLogger::StdoutLogging);
    configuration().setHost("myhost.io");
    configuration().setUseNonSASLAuthentication (false);
    configuration().setUseSASLAuthentication (false);
    connectToServer(configuration());
}

XmppClient::~XmppClient()
{

}

bool XmppClient::isReady()
{
    return ready;
}

/**
 * This function creates an account of the specified server.
 * @param name        the name of the account
 * @param username    the username of the account, used also to login
 * @param email       a valid email (this won't be validated, nor be crucial to account signup)
 * @param password    the registered account password
 * 
 * @return void
 */
void XmppClient::createAccount(QString name, QString username, QString email, QString password)
{
    //checking if xmpp client is ready
    if(!isReady()){
        qDebug() << "Aborting xmppClient::createAccount. Client not ready.";
        return;
    }
    
    //register request
    QXmppRegisterIq iq;
    //creating a custom form, used to send xml data
    QXmppDataForm::Field field_name;
    field_name.setKey("name");
    field_name.setValue(name);
    field_name.setLabel("Full Name");
    field_name.setRequired(true);
    
    QXmppDataForm::Field field_username;
    field_username.setKey("username");
    field_username.setValue(username);
    field_username.setLabel("Username");
    field_username.setRequired(true);
    
    QXmppDataForm::Field field_email;
    field_email.setKey("email");
    field_email.setValue(email);
    field_email.setLabel("Email");
    field_email.setRequired(true);
    
    QXmppDataForm::Field field_password;
    field_password.setKey("password");
    field_password.setValue(password);
    field_password.setLabel("Password");
    field_password.setRequired(true);
    
    QXmppDataForm form;
    form.setType(QXmppDataForm::Submit);
    
    QList< QXmppDataForm::Field > l;
    l.append(field_name);
    l.append(field_username);
    l.append(field_email);
    l.append(field_password);
    
    form.setFields(l);
    
    //set iq to use form
    iq.setForm(form);
    iq.setType(QXmppIq::Set);
    
    //sendpacket will handle the iq safely
    sendPacket(iq);
}

/**
 * Called in case of success connection (not necessarily log in) to server
 */
void XmppClient::connectedSuccess()
{
    qDebug() << "xmppClient: connected()!";
    ready = true;
}

