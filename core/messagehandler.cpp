/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#include "messagehandler.h"

#include <QtCore/QHash>
#include "gluonobject.h"
#include <QScriptValue>
#include <QScriptEngine>

using namespace GluonCore;

template<> MessageHandler* Singleton<MessageHandler>::m_instance = 0;

class MessageHandler::Private
{
    public:
        QMultiHash<QString, GluonObject*> subscribedObjects;
        QMultiHash<QString, QScriptValue> subscribedFunctions;
        QHash<qint64, QScriptValue> functionObjects;

};

void MessageHandler::subscribe(const QString& message, GluonObject* receiver)
{
    d->subscribedObjects.insert(message, receiver);
}

void MessageHandler::subscribe(const QString& message, const QScriptValue& receiver, const QScriptValue& thisObject )
{
    d->subscribedFunctions.insert(message, receiver);
    d->functionObjects.insert(receiver.objectId(), thisObject);
}

void MessageHandler::publish(const QString& message)
{
    QMultiHash<QString, GluonObject*>::iterator oitr;
    for(oitr = d->subscribedObjects.find(message); oitr != d->subscribedObjects.end() && oitr.key() == message; ++oitr)
    {
        oitr.value()->handleMessage(message);
    }

    QMultiHash<QString, QScriptValue>::iterator fitr;
    for(fitr = d->subscribedFunctions.find(message); fitr != d->subscribedFunctions.end() && fitr.key() == message; ++fitr)
    {
        fitr.value().call(d->functionObjects.value(fitr.value().objectId()), QScriptValueList() << message);
    }

    emit publishMessage(message);
}

MessageHandler::MessageHandler() : d(new Private)
{

}

MessageHandler::~MessageHandler()
{
    delete d;
}

#include "messagehandler.moc"
