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
#include <QColor>

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
    
    QString theTypeName = propertyValue.left(propertyValue.indexOf('(')).toLower();
    QString theValue = propertyValue.mid(theTypeName.length(), propertyValue.length() - theTypeName.length() - 1);
    
    if(theTypeName == "qstring")
        value = theValue;
    else if(theTypeName == "qcolor")
    {
        int r = 0, g = 0, b = 0, a = 0;
        QStringList splitValues = theValue.split(";");
        if(splitValues.length() > 0)
            r = splitValues[0].toInt();
        if(splitValues.length() > 1)
            g = splitValues[1].toInt();
        if(splitValues.length() > 2)
            b = splitValues[2].toInt();
        if(splitValues.length() > 3)
            a = splitValues[3].toInt();
        value = QColor(r, g, b, a);
    }
    else if(theTypeName == "bool")
        value = theValue.toFloat();
    else if(theTypeName == "float")
        value = theValue.toFloat();
    else if(theTypeName == "int")
        value = theValue.toInt();
    else
        // If all else fails, pass the value through verbatim
        value = propertyValue;
    
    this->setProperty(propertyName.toUtf8(), value);
}

QString
GluonObject::getStringFromProperty(QString propertyName)
{
    QString value;
    
    return value;
}
