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

#ifndef GLUON_GLUONOBJECTFACTORY_H
#define GLUON_GLUONOBJECTFACTORY_H

#include <common/ksingleton.h>
#include <QtCore/QSharedData>
#include <QtCore/QHash>
#include <QtCore/QMetaType>

namespace Gluon
{

class Asset;
    class GluonObject;
    class Component;
    class GluonObjectFactory : public KSingleton<GluonObjectFactory>
    {
        Q_OBJECT
        
        public:
            void registerObjectType(GluonObject * newObjectType);
            GluonObject * instantiateObjectByName(const QString& objectTypeName);
            
            void loadPlugins();
            QList<Component*> pluggedComponents() const;
            QList<Asset*> pluggedAssets() const;
            
        private:
            QList<GluonObject*> m_pluggedComponents;
            
            QHash<QString, GluonObject*> objectTypes;
    };
}

template<class T>
class GluonObjectRegistration
{
    
    public:
        GluonObjectRegistration(T* newObjectType)
        {
            Gluon::GluonObjectFactory::instance()->registerObjectType(newObjectType);
            if(newObjectType->metaObject())
                qRegisterMetaType<T*>();//(newObjectType->metaObject()->className() + ' ' + '*');
        }
};

#define REGISTER_OBJECTTYPE(NEWOBJECTTYPE) \
GluonObjectRegistration<NEWOBJECTTYPE> NEWOBJECTTYPE ## _GluonObjectRegistration_(new NEWOBJECTTYPE()); \
Q_DECLARE_METATYPE(NEWOBJECTTYPE *);

    
#endif				// GLUON_GLUONOBJECTFACTORY_H
