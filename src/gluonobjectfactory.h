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
#include <QSharedData>

namespace Gluon
{
    class GluonObject;
    class GluonObjectFactoryPrivate;
    
    class GluonObjectFactory : public KSingleton<GluonObjectFactory>
    {
        public:
            void registerObjectType(GluonObject * newObjectType);
            GluonObject * instantiateObjectByName(QString objectTypeName);
            
        private:
            QSharedDataPointer<GluonObjectFactoryPrivate> d;
    };

    template<class T>
    class GluonObjectRegistration
    {
        
        public:
            Registration(T* newObjectType)
            {
                GluonObjectFactory::instance()->registerObjectType(newObjectType);
            }
    };
}

#define REGISTER_OBJECTTYPE(NEWOBJECTTYPE) \
Gluon::GluonObjectRegistration<Gluon::NEWOBJECTTYPE> NEWOBJECTTYPE ## _registration_(new Gluon::NEWOBJECTTYPE());
    
#endif				// GLUON_GLUONOBJECTFACTORY_H
