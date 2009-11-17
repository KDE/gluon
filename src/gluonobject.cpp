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

GluonObject::GluonObject(QObject * parent) : QObject(parent)
{
    d = new GluonObjectPrivate();
}

GluonObject::GluonObject(const QString& name, QObject* parent): QObject(parent)
{
    d = new GluonObjectPrivate();
    d->name = name;
}

GluonObject::~GluonObject()
{
}

GluonObject *
GluonObject::instantiate()
{
    if(QString(this->metaObject()->className()) != QString("Gluon::GluonObject"))
        qDebug() << "Missing instantiate() implementation in" << this->metaObject()->className();
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

void GluonObject::addChild(GluonObject* child)
{
    child->setParent(this);
}

GluonObject* GluonObject::child(int index) const
{
    return qobject_cast<GluonObject*>(children().at(index));
}

GluonObject* GluonObject::child(const QString& name) const
{
    foreach(QObject *child, children())
    {
        GluonObject *obj = qobject_cast<GluonObject*>(child);
        if(obj && obj->name() == name) return obj;
    }
    return 0;
}

bool GluonObject::removeChild(GluonObject* child)
{
    child->setParent(0);
    return true;
}

QString
GluonObject::toGDL() const
{
    QString serializedObject;
    qDebug() << "Serializing object named" << this->name();

    QString minimalClassName(this->metaObject()->className());
    if(QString(this->metaObject()->className()).startsWith(QString("Gluon::")))
        minimalClassName = minimalClassName.right(minimalClassName.length() - 7);
    serializedObject += "{ " + minimalClassName + '(' + this->name() + ")";

    serializedObject += propertiesToGDL();

    // Run through all the children to get them as well
    foreach(QObject* child, children())
    {
        GluonObject* theChild = qobject_cast<GluonObject*>(child);
        if(theChild)
            serializedObject += theChild->toGDL();
    }

    return serializedObject + "}\n";
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
        if(theName == "objectName" || theName == "name")
            continue;
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

    QVariant theValue = this->property(propertyName.toUtf8());

    QColor theColor;
    switch(theValue.type())
    {
        case QVariant::String:
            value = "string(" + theValue.toString() + ')';
            break;
        case QVariant::Bool:
            value = QString("bool(%1)").arg(theValue.toBool());
            break;
        case QVariant::Double:
            value = QString("float(%1)").arg(theValue.toDouble());
            break;
        case QVariant::Int:
            value = QString("int(%1)").arg(theValue.toInt());
            break;
        case QVariant::PointF:
            value = QString("vector2d(%1;%2)").arg(theValue.toPointF().x()).arg(theValue.toPointF().y());
            break;
        case QVariant::Color:
            theColor = theValue.value<QColor>();
            value = QString("rgba(%1;%2;%3;%4)").arg(theColor.red()).arg(theColor.green()).arg(theColor.blue()).arg(theColor.alpha());
            break;
        default:
            value = theValue.toString();
            break;
    }

    return QString("\n%1 %2").arg(propertyName).arg(value);
}

#include "gluonobject.moc"
