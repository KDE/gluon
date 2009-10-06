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

#include "gluonobject.h"
#include "gluonobjectprivate.h"
#include <QVariant>

using namespace Gluon;

GluonObject::GluonObject(QObject * parent)
{
}

GluonObject::~GluonObject()
{
}

QString
GluonObject::name() const
{
    return d->name;
}

void
GluonObject::setName(QString newName)
{
    d->name = newName;
}

void
GluonObject::setPropertyFromString(QString propertyName, QString propertyValue)
{
    QVariant value;
    
    if(propertyValue.toLower().startsWith("qstring("))
        value = propertyValue.mid(8, propertyValue.length() - 9);
    else if(propertyValue.toLower().startsWith("float("))
        value = propertyValue.mid(6, propertyValue.length() - 7).toFloat();
    else if(propertyValue.toLower().startsWith("int("))
        value = propertyValue.mid(4, propertyValue.length() - 5).toInt();
    else
        // If all else fails, pass the value through verbatim
        value = propertyValue;
    
    this->setProperty(propertyName.toUtf8(), value);
;}
