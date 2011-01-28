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


#ifndef GLUONCORE_MESSAGEHANDLER_H
#define GLUONCORE_MESSAGEHANDLER_H

#include "singleton.h"
#include "gluon_core_export.h"

class QScriptValue;
namespace GluonCore 
{
    class GluonObject;
    
    /**
     * Handle sending of messages between objects.
     * 
     * The message handler class provides facilities for
     * sending simple messages between objects. Objects can
     * subscribe to messages and other objects can publish
     * messages.
     */
    class GLUON_CORE_EXPORT MessageHandler : public Singleton<MessageHandler>
    {
        Q_OBJECT
        public:
            /**
             * Subscribe to a message.
             * This will call the handleMessage() methos on receiver
             * every time the message is being published.
             * 
             * \param message The message to subscribe to.
             * \param receiver The object to receive the message.
             */
            Q_INVOKABLE void subscribe(const QString& message, GluonObject* receiver);
            /**
             * Subscribe to a message.
             * This overload is meant to be called from script. call()
             * will be called on receiver with thisObject as the this object 
             * of that function.
             * 
             * \param message The message to subscribe to.
             * \param receiover A QtScript function that will be called whenever
             * message is published.
             * \param thisObject The "this" object to use when calling receiver.
             */
            Q_INVOKABLE void subscribe(const QString& message, const QScriptValue& receiver, const QScriptValue& thisObject);
            
        public Q_SLOTS:
            /**
             * Publish a message.
             * 
             * \param message The message that needs to be published.
             */
            void publish(const QString& message);
        
        Q_SIGNALS:
            /**
             * A message has just been published.
             */
            void publishMessage(const QString& message);
            
        private:
            friend class Singleton<MessageHandler>;
            MessageHandler();
            ~MessageHandler();
            
            Q_DISABLE_COPY(MessageHandler)
            
            class Private;
            Private * const d;
    };

}

#endif // GLUONCORE_MESSAGEHANDLER_H
