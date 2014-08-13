/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_CORE_GLUONOBJECTFACTORY_H
#define GLUON_CORE_GLUONOBJECTFACTORY_H

#include "gluoncore_export.h"

#include "singleton.h"
#include "debughelper.h"
#include "privatepointer.h"

#include <QtCore/QHash>
#include <QtCore/QStringList>
#include <QtCore/QJsonObject>
#include <QtScript/QScriptEngine>

namespace GluonCore
{
    class GluonObject;
    class GluonObjectFactory;

    /**
     * \brief Create and manipulate GluonObjects by reference and name
     *
     * The GluonObjectFactory provides functionality not just for creating objects,
     * but also assists in extending QVariant with functionality for handling objects
     * with inherited classes.
     */
    class GLUONCORE_EXPORT GluonObjectFactory : public Singleton<GluonObjectFactory>
    {
            Q_OBJECT
            GLUON_SINGLETON( GluonObjectFactory )
        public:
            void registerObjectType( const QJsonObject& metaData, GluonObject* object );

            /**
             * Create a new object with the class name indicated by the passed string
             *
             * @param   objectTypeName  The name of the class you want an instance of
             * @return  An object of the appropriate type, or null if no such class was found in the factory
             */
            Q_INVOKABLE GluonCore::GluonObject* instantiateObjectByName( const QString& objectTypeName );
            /**
             * Create a new object which is capable of handling the passed mime type
             *
             * @param   objectMimeType  The string representation of the mimetype you wish to be able to handle
             * @return  An object of the appropriate type, or null if there is no suitable class in the factory
             */
            GluonObject* instantiateObjectByMimetype( const QString& objectMimeType );

            /**
             * Request a reload of the factory's plugins
             */
            void loadPlugins();

            /**
             * A list of all the names of the classes in the factory
             *
             * @return The list of all the classes the factory can accept
             */
            QStringList objectTypeNames() const;
            /**
             * A list of all the mimetypes supported by the factory
             *
             * @return  The list of all supported mimetypes
             */
            QStringList objectMimeTypes() const;
            /**
             * A hash containing all the metaobjects of all the classes in the factory.
             * The key is the class name, and the value is the metaobject.
             *
             * @return  The hash as described
             */
            QHash<QString, const QMetaObject*> objectTypes() const;

            QJsonObject metaData( const QString& type ) const;

        GLUON_PRIVATE_POINTER;
    };
}

/**
 * Use this macro to register a class with the GluonObjectFactory.
 * It adds a number of functions used by GluonObjectFactory, so please note that you should not
 * be adding functions with the following signatures to your class:
 *
 * GluonCore::GluonObject *instantiate();
 *
 * Please make sure to insert this macro at the very top of the file containing your
 * implementation. As an example, the following is the code used to register GluonObject
 * itself into the factory:
 *
\code
REGISTER_OBJECTTYPE(GluonCore, GluonObject);
\endcode
 *
 * @see GLUON_OBJECT
 */
#define REGISTER_OBJECTTYPE(NAMESPACE,NEWOBJECTTYPE) \
    GluonCore::GluonObject * \
    NAMESPACE::NEWOBJECTTYPE::instantiate()\
    {\
        return new NAMESPACE :: NEWOBJECTTYPE();\
    }\
    QScriptValue NAMESPACE::NEWOBJECTTYPE::objectToScriptValue( QScriptEngine* engine, NAMESPACE :: NEWOBJECTTYPE* const& in )\
    {\
        return engine->newQObject( in );\
    }\
    void NAMESPACE::NEWOBJECTTYPE::objectFromScriptValue( const QScriptValue& object, NAMESPACE :: NEWOBJECTTYPE* &out )\
    {\
        out = qobject_cast<NAMESPACE :: NEWOBJECTTYPE*>( object.toQObject() );\
    }\
    void NAMESPACE::NEWOBJECTTYPE::registerOnScriptEngine( QScriptEngine* engine ) const\
    {\
        QScriptValue objectClass = engine->scriptValueFromQMetaObject<NAMESPACE :: NEWOBJECTTYPE>();\
        engine->globalObject().setProperty(NAMESPACE :: NEWOBJECTTYPE::staticMetaObject.className(), objectClass);\
        qScriptRegisterMetaType( engine, NAMESPACE::NEWOBJECTTYPE::objectToScriptValue, NAMESPACE::NEWOBJECTTYPE::objectFromScriptValue );\
    }

#endif  // GLUON_CORE_GLUONOBJECTFACTORY_H
