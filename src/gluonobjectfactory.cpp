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

#include "gluonobjectfactory.h"
#include "gluonobject.h"

#include <QDebug>

using namespace Gluon;

template<> GluonObjectFactory* KSingleton<GluonObjectFactory>::m_instance = 0;

void
GluonObjectFactory::registerObjectType(GluonObject * newObjectType)
{
    if(newObjectType)
    {
        qDebug() << "Registering object type" << newObjectType->metaObject()->className();
        objectTypes[newObjectType->metaObject()->className()] = newObjectType;
    }
}

GluonObject *
GluonObjectFactory::instantiateObjectByName(const QString& objectTypeName)
{
    QString fullObjectTypeName = QString("Gluon::") + objectTypeName;
    if(objectTypes.find(fullObjectTypeName) != objectTypes.end())
    {
        return objectTypes.value(fullObjectTypeName)->instantiate();
    }
    return 0;
}
