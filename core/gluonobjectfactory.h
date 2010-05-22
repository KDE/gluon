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

namespace GluonCore
{
    class GluonObject;

    class GLUON_CORE_EXPORT GluonObjectFactory : public Singleton<GluonObjectFactory>
    {
            Q_OBJECT

        public:
            void registerObjectType(GluonObject * newObjectType, int typeID);
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

            void loadPlugins();

            QStringList objectTypeNames() const;
            QStringList objectMimeTypes() const;
            QHash<QString, GluonObject*> objectTypes() const;
            const QHash<QString, int> objectTypeIDs() const;
            
            static const QString libraryInstallPath();
            static const QString dataInstallPath();
        private:
            QHash<QString, GluonObject*> m_objectTypes;
            QHash<QString, QString> m_mimeTypes;
            QHash<QString, int> m_objectTypeIDs;
    };
}

template<class T>
class GLUON_CORE_EXPORT GluonObjectRegistration
{
    public:
        GluonObjectRegistration(T* newObjectType)
        {
            if (newObjectType->metaObject())
            {
                int typeID = qRegisterMetaType<T*>(newObjectType->metaObject()->className() + '*');
                GluonCore::GluonObjectFactory::instance()->registerObjectType(newObjectType, typeID);
            }
        }
};

#define REGISTER_OBJECTTYPE(NAMESPACE,NEWOBJECTTYPE) \
    namespace NAMESPACE { GluonObjectRegistration<NEWOBJECTTYPE> NEWOBJECTTYPE ## _GluonObjectRegistration_(new NEWOBJECTTYPE()); }\
    GluonCore::GluonObject * \
    NAMESPACE::NEWOBJECTTYPE::instantiate()\
    {\
        return new NAMESPACE :: NEWOBJECTTYPE();\
    }\
    QVariant \
    NAMESPACE::NEWOBJECTTYPE::toVariant(GluonCore::GluonObject *wrapThis)\
    {\
        return QVariant::fromValue<NAMESPACE :: NEWOBJECTTYPE*>(qobject_cast<NAMESPACE :: NEWOBJECTTYPE*>(wrapThis));\
    }\

//Q_DECLARE_METATYPE(NAMESPACE :: NEWOBJECTTYPE *);

#endif  // GLUON_CORE_GLUONOBJECTFACTORY_H
