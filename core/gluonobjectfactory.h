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

#include <QtCore/QSharedData>
#include <QtCore/QHash>
#include <QtCore/QMetaType>

#include "singleton.h"
#include "gluon_core_export.h"
#include "debughelper.h"

namespace GluonCore
{
    class GluonObject;

    class GLUON_CORE_EXPORT GluonObjectFactory : public Singleton<GluonObjectFactory>
    {
            Q_OBJECT

        public:
            template<class T>
            void registerObjectType()
            {
                DEBUG_BLOCK
                
                int typeID = qRegisterMetaType<T*>(T::staticMetaObject.className() + '*');
                DEBUG_TEXT(QString("Registering object type %1 with typeID %2").arg(T::staticMetaObject.className()).arg(typeID));
                
                m_objectTypes[T::staticMetaObject.className()] = &(T::staticMetaObject);
                m_objectTypeIDs[T::staticMetaObject.className()] = typeID;
                
                // Yeah, i'd like to do this using a virtual static function, but those don't exist in C++ :P
                T object;
                QString mimetypenames;
                foreach(const QString &mimetype, object.supportedMimeTypes())
                {
                    mimetypenames.append(' ' + mimetype);
                    m_mimeTypes[mimetype] = T::staticMetaObject.className();
                }
                if(mimetypenames.length() > 0)
                {
                    DEBUG_TEXT(QString("Added mimetypes %1 to the index").arg(mimetypenames));
                }
            };
            GluonObject * instantiateObjectByName(const QString& objectTypeName);
            GluonObject * instantiateObjectByMimetype(const QString& objectMimeType);

            /**
             * This somewhat odd looking function is the final product of a long winded
             * mission to try and wrap objects in a suitable QVariant, so as to
             * not get the wrong type when getting it back from the property view
             * @param original The original value of the property
             * @param newValue The new value of the reference property
             * @return The object wrapped in a suitably typed QVariant
             */
            QVariant wrapObject(const QVariant &original, GluonObject* newValue);
            QVariant wrapObject(const QString &type, GluonObject* newValue);
            GluonObject* wrappedObject(const QVariant &wrappedObject);

            void loadPlugins();

            QStringList objectTypeNames() const;
            QStringList objectMimeTypes() const;
            QHash<QString, const QMetaObject*> objectTypes() const;
            const QHash<QString, int> objectTypeIDs() const;
            
        private:
            QHash<QString, const QMetaObject*> m_objectTypes;
            QHash<QString, QString> m_mimeTypes;
            QHash<QString, int> m_objectTypeIDs;
    };
}

template<class T>
class GLUON_CORE_EXPORT GluonObjectRegistration
{
    public:
        GluonObjectRegistration()
        {
            GluonCore::GluonObjectFactory::instance()->registerObjectType<T>();
        }
};

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
        return QVariant::fromValue<NAMESPACE :: NEWOBJECTTYPE*>(qobject_cast<NAMESPACE :: NEWOBJECTTYPE*>(wrapThis));\
    }\

//Q_DECLARE_METATYPE(NAMESPACE :: NEWOBJECTTYPE *);

#endif  // GLUON_CORE_GLUONOBJECTFACTORY_H
