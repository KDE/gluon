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

#include "gluon_core_export.h"

#include "singleton.h"
#include "debughelper.h"

#include <QtScript/QScriptEngine>
#include <QtCore/QHash>
#include <QtCore/QStringList>

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
    class GLUON_CORE_EXPORT GluonObjectFactory : public Singleton<GluonObjectFactory>
    {
            Q_OBJECT
            GLUON_SINGLETON( GluonObjectFactory )
        public:
            template<class T>
            void registerObjectType()
            {
                DEBUG_BLOCK

                int typeID = qRegisterMetaType<T*>( );
                //Workaround Qt bug http://bugreports.qt.nokia.com/browse/QTBUG-2393
                //Register each class with his class name without the namespace too.
                QString name( QString( T::staticMetaObject.className() ).split( "::" ).at( 1 ) );
                qRegisterMetaType<T*>( ( name + '*' ).toLatin1().constData() );

                DEBUG_TEXT( QString( "Registering object type %1 with typeID %2" ).arg( T::staticMetaObject.className() ).arg( typeID ) )

                m_objectTypes[T::staticMetaObject.className()] = &( T::staticMetaObject );
                m_objectTypeIDs[T::staticMetaObject.className()] = typeID;

                // Yeah, i'd like to do this using a virtual static function, but those don't exist in C++ :P
                T object;
                QString mimetypenames;
                foreach( const QString & mimetype, object.supportedMimeTypes() )
                {
                    mimetypenames.append( ' ' + mimetype );
                    m_mimeTypes[mimetype] = T::staticMetaObject.className();
                }
                if( mimetypenames.length() > 0 )
                {
                    DEBUG_TEXT( QString( "Added mimetypes %1 to the index" ).arg( mimetypenames ) )
                }
            };

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
             * Wrap the passed GluonObject in a QVariant of the same type as the
             * passed QVariant. This enables a property to retain its type when
             * changing its value along a class inheritance chain.
             *
             * @param original The original value of the property
             * @param newValue The new value of the reference property
             * @return The object wrapped in a suitably typed QVariant
             */
            QVariant wrapObject( const QVariant& original, GluonObject* newValue );
            /**
             * Wrap the passed GluonObject in a QVariant of the named type. This
             * enables a property to retain its type when changing its value along
             * a class inheritance chain.
             *
             * @param   type        The name of the type the QVariant should be
             * @param   newValue    The object you wish to have wrapped in a QVariant of the specified type
             * @return  The appropriate QVariant, or an invalid QVariant if the type was not found in the factory
             */
            QVariant wrapObject( const QString& type, GluonObject* newValue );
            /**
             * Get the GluonObject wrapped inside the passed QVariant
             *
             * @param   wrappedObject   A GluonObject wrapped inside a QVariant
             * @return  The GluonObject wrapped by the QVariant, or null if there is no valid GluonObject inside it
             */
            GluonObject* wrappedObject( const QVariant& wrappedObject );

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
            /**
             * A hash containing the QMetaType object IDs for all the classes registered in
             * the factory. The key is the class name, and the value is the ID
             *
             * @return  The hash as described
             */
            const QHash<QString, int> objectTypeIDs() const;

        private:
            QHash<QString, const QMetaObject*> m_objectTypes;
            QHash<QString, QString> m_mimeTypes;
            QHash<QString, int> m_objectTypeIDs;
    };
}

/// \cond GluonObjectRegistration
/**
 * \brief Convenience - do not use directly
 * A convenience class used for object registration, which should not be used directly
 */
template<class T>
class GluonObjectRegistration
{
    public:
        GluonObjectRegistration()
        {
            GluonCore::GluonObjectFactory::instance()->registerObjectType<T>();
        }
};

/// \endcond

/**
 * Use this macro to register a class with the GluonObjectFactory.
 * It adds a number of functions used by GluonObjectFactory, so please note that you should not
 * be adding functions with the following signatures to your class:
 *
 * GluonCore::GluonObject *instantiate();
 *
 * GluonCore::GluonObject *fromVariant(const QVariant &wrappedObject);
 *
 * QVariant toVariant(GluonCore::GluonObject *wrapThis);
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
    GluonObjectRegistration<NAMESPACE :: NEWOBJECTTYPE> NAMESPACE ## NEWOBJECTTYPE ## _GluonObjectRegistration;\
    GluonCore::GluonObject * \
    NAMESPACE::NEWOBJECTTYPE::instantiate()\
    {\
        return new NAMESPACE :: NEWOBJECTTYPE();\
    }\
    GluonCore::GluonObject * \
    NAMESPACE::NEWOBJECTTYPE::fromVariant(const QVariant &wrappedObject) \
    {\
        return wrappedObject.value< NAMESPACE :: NEWOBJECTTYPE* >();\
    }\
    QVariant \
    NAMESPACE::NEWOBJECTTYPE::toVariant(GluonCore::GluonObject *wrapThis)\
    {\
        return QVariant::fromValue<NAMESPACE :: NEWOBJECTTYPE *>(qobject_cast<NAMESPACE :: NEWOBJECTTYPE*>(wrapThis));\
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

//Q_DECLARE_METATYPE(NAMESPACE :: NEWOBJECTTYPE *);

#endif  // GLUON_CORE_GLUONOBJECTFACTORY_H
