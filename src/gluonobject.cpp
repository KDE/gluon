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
#include <QtCore/QVariant>
#include <QtCore/QPointF>
#include <QtGui/QColor>
#include <Eigen/Geometry>

#include <QtCore/QDebug>
#include <QMetaClassInfo>

using namespace Gluon;

REGISTER_OBJECTTYPE(GluonObject)

GluonObject::GluonObject(QObject * parent)
{
    d = new GluonObjectPrivate();
}

GluonObject::~GluonObject()
{
}

GluonObject *
GluonObject::instantiate()
{
    return new GluonObject(this);
}

void
GluonObject::sanitize()
{
    GluonObject * theChild = 0;
    foreach(QObject * child, this->children())
    {
        if(child->inherits("GluonObject"))
        {
            theChild = qobject_cast<GluonObject*>(child);
            theChild->sanitize();
        }
    }
}

QString
GluonObject::name() const
{
    return d->name;
}

void
GluonObject::setName(const QString &newName)
{
    d->name = newName;
}

QString
GluonObject::toGDL() const
{
    QString serializedObject;
    qDebug() << "Serializing " << this->name();
    
    serializedObject += propertiesToGDL();
    
    // Run through all the children to get them as well
    foreach(QObject* child, children())
    {
        GluonObject* theChild = qobject_cast<GluonObject*>(child);
        if(theChild)
            serializedObject += theChild->toGDL();
    }
    
    return serializedObject;
}

QString
GluonObject::propertiesToGDL() const
{
    QString serializedObject;

    // Get all the normally defined properties
    const QMetaObject *metaobject = this->metaObject();
    int count = metaobject->propertyCount();
    for(int i = 0; i < count; ++i)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        const QString theName(metaproperty.name());
        serializedObject += this->getStringFromProperty(theName);
    }
    
    // Then get all the dynamic ones (in case any such exist)
    QList<QByteArray> propertyNames = dynamicPropertyNames();
    foreach(QByteArray propName, propertyNames)
    {
        const QString theName(propName);
        serializedObject += this->getStringFromProperty(theName);
    }
    
    return serializedObject;
}

void
GluonObject::setPropertyFromString(const QString &propertyName, const QString &propertyValue)
{
    QVariant value;

    // propertyValue format is type(value)
    QRegExp rx("(\\w+)\\((.+)\\)");
    int pos = rx.indexIn(propertyValue);

    QString theTypeName = rx.cap(1);
    QString theValue = rx.cap(2);
    qDebug() << "  Setting property" << propertyName << "of type" << theTypeName << "to value" << theValue;

    if(theTypeName == "string") {
        value = theValue;
    } else if(theTypeName == "bool") {
        value = theValue.toFloat();
    } else if(theTypeName == "float") {
        value = theValue.toFloat();
    } else if(theTypeName == "int") {
        value = theValue.toInt();
    } else if(theTypeName == "vector2d") {
        float x = 0.0f, y = 0.0f;
        //, z = 0.0f;
        QStringList splitValues = theValue.split(";");
        if(splitValues.length() > 0)
        {
            x = splitValues.at(0).toFloat();
            y = splitValues.at(1).toFloat();
            //z = splitValues.at(2).toFloat();
        }
        value = QPointF(x, y);
    } else if(theTypeName == "rgba") {
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
    } else {
        // If all else fails, pass the value through verbatim
        value = propertyValue;
    }

    this->setProperty(propertyName.toUtf8(), value);
}

QString
GluonObject::getStringFromProperty(const QString &propertyName) const
{
    QString value;

    return value;
}

#include "gluonobject.moc"
