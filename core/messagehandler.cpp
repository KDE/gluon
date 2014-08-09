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

#include "gluonobject.h"

#include <QtCore/QHash>
#include <QtCore/QPointer>
#include <QtScript/QScriptValue>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( MessageHandler )

struct JSFunctionBinding
{
    QScriptValue receiver;
    QScriptValue thisObject;
};

class MessageHandler::Private
{
    public:
        QMultiHash<QString, QPointer<GluonObject> > subscribedObjects;
        QMultiHash<QString, JSFunctionBinding > subscribedFunctions;
};

void MessageHandler::subscribe( const QString& message, GluonObject* receiver )
{
    d->subscribedObjects.insert( message, QPointer<GluonObject>( receiver ) );
}

void MessageHandler::subscribe( const QString& message, const QScriptValue& receiver, const QScriptValue& thisObject )
{
    d->subscribedFunctions.insert( message, JSFunctionBinding{ receiver, thisObject } );
}

void MessageHandler::unsubscribe( const QString& message, GluonObject* receiver )
{
    d->subscribedObjects.remove( message, QPointer<GluonObject>( receiver ) );
}

void MessageHandler::unsubscribe( const QString& message, const QScriptValue& receiver, const QScriptValue&  thisObject )
{
    JSFunctionBinding binding{ receiver, thisObject };
    QMultiHash<QString, JSFunctionBinding>::iterator itr;
    for( itr = d->subscribedFunctions.find( message ); itr != d->subscribedFunctions.end() && itr.key() == message; ++itr )
    {
        if( itr.value().receiver.equals( receiver ) && itr.value().thisObject.strictlyEquals( thisObject ) )
            break;
    }

    if( itr != d->subscribedFunctions.end() && itr.key() == message )
    {
        d->subscribedFunctions.erase( itr );
    }
}

void MessageHandler::publish( const QString& message )
{
    QMultiHash<QString, QPointer<GluonObject> >::const_iterator oitr;
    for( oitr = d->subscribedObjects.constFind( message ); oitr != d->subscribedObjects.constEnd() && oitr.key() == message; ++oitr )
    {
        oitr.value().data()->handleMessage( message );
    }

    QMultiHash<QString, JSFunctionBinding>::iterator fitr;
    for( fitr = d->subscribedFunctions.find( message ); fitr != d->subscribedFunctions.end() && fitr.key() == message; ++fitr )
    {
        fitr.value().receiver.call( fitr.value().thisObject, QScriptValueList() << message );
    }

    emit publishMessage( message );
}

MessageHandler::MessageHandler( QObject* parent )
    : GluonCore::Singleton< GluonCore::MessageHandler >( parent ), d( new Private )
{

}

MessageHandler::~MessageHandler()
{
    delete d;
}
