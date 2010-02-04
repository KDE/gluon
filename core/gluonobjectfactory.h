/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

            void loadPlugins();

            QStringList objectTypeNames() const;
            QStringList objectMimeTypes() const;
            QHash<QString, GluonObject*> objectTypes() const;
            const QHash<QString, int> objectTypeIDs() const;
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
            if(newObjectType->metaObject())
            {
                int typeID = qRegisterMetaType<T*>(newObjectType->metaObject()->className() + '*');
                GluonCore::GluonObjectFactory::instance()->registerObjectType(newObjectType, typeID);
            }
        }
};

#define REGISTER_OBJECTTYPE(NAMESPACE,NEWOBJECTTYPE) \
namespace NAMESPACE { GluonObjectRegistration<NEWOBJECTTYPE> NEWOBJECTTYPE ## _GluonObjectRegistration_(new NEWOBJECTTYPE()); }\
Q_DECLARE_METATYPE(NAMESPACE :: NEWOBJECTTYPE *);


#endif  // GLUON_CORE_GLUONOBJECTFACTORY_H
