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
#include <QXmppRosterManager.h>
#include <QXmppPresence.h>
#include <QXmppUtils.h>
#include <QtWidgets/QMessageBox>

#include "xmppclient.h"

/**
 * Attempts a connection to server when created.
 * Connection is not logged. See login() for logging.
 */
XmppClient::XmppClient(QObject *parent)
    : QXmppClient(parent)
{
    m_host = "myhost.io";
    
    //client is not ready
    ready = false;
    setLogged(false);
    registering = false;
    
    bool check = false;
    Q_UNUSED(check);
    
    //just do something when connected
    check = connect(this, SIGNAL(connected()), SLOT(connectedSuccess()));
    Q_ASSERT(check);
    check = connect(this, SIGNAL(disconnected()), SLOT(disconnectedSuccess()));
    Q_ASSERT(check);
    check = connect(this, SIGNAL(messageReceived(QXmppMessage)), SLOT(onMessageReceived(QXmppMessage)));
    Q_ASSERT(check);
    check = connect(this, SIGNAL(presenceReceived(QXmppPresence)), SLOT(onPresenceReceived(QXmppPresence)));
    Q_ASSERT(check);
    check = connect(this, SIGNAL(iqReceived(QXmppIq)), SLOT(onIqReceived(QXmppIq)));
    Q_ASSERT(check);
    
    check = connect(&this->rosterManager(), SIGNAL(rosterReceived()), SLOT(rosterReceived()));
    Q_ASSERT(check);

    /// Then QXmppRoster::presenceChanged() is emitted whenever presence of someone
    /// in roster changes
    check = connect(&this->rosterManager(), SIGNAL(presenceChanged(QString,QString)), SLOT(presenceChanged(QString,QString)));
    Q_ASSERT(check);
    
    
    logger()->setLoggingType(QXmppLogger::StdoutLogging);
    
    //setting in case of direct initialization
    if(m_instance==NULL){
        m_instance = this;
    }
}

XmppClient::~XmppClient()
{

}

//FIXME: except from C++11 this should be not thread safe
//       still not sure though
XmppClient* XmppClient::getInstance(void)
{
    if(m_instance == NULL) m_instance = new XmppClient();
    return m_instance;
}

bool XmppClient::isReady()
{
    return ready;
}

//get logged
bool XmppClient::logged()
{
    return m_logged;
}

//set logged
void XmppClient::setLogged(bool logged)
{
    m_logged = logged;
    emit loggedChanged();
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
    m_name = name;
    m_username = username;
    m_email = email;
    m_password = password;
    //setting register status
    registering = true;
    
    configuration().setHost(m_host);
    configuration().setUseNonSASLAuthentication (false);
    configuration().setUseSASLAuthentication (false);
    connectToServer(configuration());

}

void XmppClient::onCreateAccountReady(){
    //register request
    QXmppRegisterIq iq;
    //creating a custom form, used to send xml data
    QXmppDataForm::Field field_name;
    field_name.setKey("name");
    field_name.setValue(m_name);
    field_name.setLabel("Full Name");
    field_name.setRequired(true);
    
    QXmppDataForm::Field field_username;
    field_username.setKey("username");
    field_username.setValue(m_username);
    field_username.setLabel("Username");
    field_username.setRequired(true);
    
    QXmppDataForm::Field field_email;
    field_email.setKey("email");
    field_email.setValue(m_email);
    field_email.setLabel("Email");
    field_email.setRequired(true);
    
    QXmppDataForm::Field field_password;
    field_password.setKey("password");
    field_password.setValue(m_password);
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

void XmppClient::login(QString username, QString password)
{
    qDebug() << "xmppClient: trying to login with " << username << "and " << password;
    
    //if already connected, jsut disconnects (used also to switch from anonymous login to auth login)
    if(logged() == true || ready == true){
        disconnectFromServer();
    }
    
    connectToServer(username+"@"+m_host, password);
}

/**
 * Called in case of success connection (not necessarily log in) to server
 */
void XmppClient::connectedSuccess()
{   
    //TODO: move this on received iq handling
    
    //if we're registering a user, we're also logged anonymous
    if(registering == true){
        onCreateAccountReady();
    } else { //else we're logged auth, yeah FIXME: check iqs properly
        setLogged(true);
        ready = true;
        emit loggedIn();
    }
}

/**
 * Called in case of success connection (not necessarily log in) to server
 */
void XmppClient::onMessageReceived(const QXmppMessage &message)
{
    emit newMessage(message.from(), message.state(), message.body());
}

/**
 * Send a text message through xmpp protocol
 */
void XmppClient::sendConversationMessage(QString body, QString to){
    sendPacket(QXmppMessage("", to, body));
}
/**
 * Send a status message for people in a conversation
 * e.g. active when the two people are doing nothing,
 *      composing when one of them is writing a message
 *      gone when one of them goes away (closes the chat window)
 */
void XmppClient::sendStatusMessage(QString to, QString s)
{
    QXmppMessage message("", to, "");
    if(s=="active"){
        message.setState(QXmppMessage::Active);
    } else if(s=="composing"){
        message.setState(QXmppMessage::Composing);
    } else if(s=="gone"){
        message.setState(QXmppMessage::Gone);
    } else {
        qDebug() << "XmppClient: unrecognized sending status";
    }
    
    sendPacket(message);
}

/**
 * Called in case of success connection (not necessarily log in) to server
 */
void XmppClient::onPresenceReceived(const QXmppPresence &presence)
{
    QString status;
    // update presence
    if (presence.type() == QXmppPresence::Available) {
        switch (presence.availableStatusType())
        {
        case QXmppPresence::Online:
        case QXmppPresence::Chat:
            status = "online";
            break;
        case QXmppPresence::Away:
        case QXmppPresence::XA:
            status = "away";
            break;
        case QXmppPresence::DND:
            status = "busy";
            break;
        case QXmppPresence::Invisible:
            status = "offline";
            break;
        }
    } else {
        status = "offline";
    }
    
    emit accountChangedPresence(QXmppUtils::jidToUser(presence.from()), status);
}

void XmppClient::rosterReceived()
{
    //TODO: try to remove me, if everything works, time has come
    //kept here just for syntax
    //this is going to be removed soon
}

void XmppClient::logout()
{
    //qxmpp call
    disconnectFromServer();
    //qml property
    setLogged(false);
    //signal
    emit loggedOut();
}

void XmppClient::presenceChanged(const QString& bareJid,
                                 const QString& resource)
{
    qDebug("xmppClient:: Presence changed %s/%s", qPrintable(bareJid), qPrintable(resource));
}

void XmppClient::disconnectedSuccess()
{
    qDebug() << "xmppClient: disconnected!";
}

void XmppClient::addSubscription(const QString& jid)
{
    QXmppPresence subscribed;
    subscribed.setTo(jid+"@"+m_host);
    subscribed.setType(QXmppPresence::Subscribed);
    sendPacket(subscribed);

    // reciprocal subscription
    QXmppPresence subscribe;
    subscribe.setTo(jid+"@"+m_host);
    subscribe.setType(QXmppPresence::Subscribe);
    sendPacket(subscribe);
}

void XmppClient::onIqReceived(const QXmppIq& iq)
{
    if(registering){
        disconnectFromServer();
        registering = false;
    } else {
        qDebug() << "xmppClient: unknown xmpp Iq received!";
    }
}

XmppClient * XmppClient::m_instance = 0;