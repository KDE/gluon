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
#include "gameproject.h"

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
    
    // Make sure the GameProject is set... Iterate upwards until you either reach
    // the first GameProject instance, or you run into a parent which is null
    QObject * currentParent = this->parent();
    while(currentParent)
    {
        if(qobject_cast<GameProject*>(currentParent))
        {
            setGameProject(qobject_cast<GameProject*>(currentParent));
            break;
        }
        currentParent = currentParent->parent();
    }
    
    // Run through all properties, check whether they are set to the correct
    // value. If they should be pointing to something, make them!
    // (e.g. GameObject(Projectname.Something))
    // This step is only possible if a gameProject is available. Otherwise
    // you will be unable to find the other objects!
    if(gameProject())
    {
        QStringList objectTypeNames = GluonObjectFactory::instance()->objectTypeNames();
        
        qDebug() << "Sanitizing properties in" << this->name();
        const QMetaObject *metaobject = this->metaObject();
        if(metaobject == NULL)
            return;
        int count = metaobject->propertyCount();
        for(int i = 0; i < count; ++i)
        {
            QMetaProperty metaproperty = metaobject->property(i);
            
            // This is really only relevant if the property value is a string.
            // If it is not, what happens below is irrelevant
            if(metaproperty.type() != QVariant::String)
                continue;
            
            const QString theName(metaproperty.name());
            if(theName == "objectName" || theName == "name")
                continue;
            
            QString theValue(metaproperty.read(this).toString());
            // Yes, i know this is O(n*m) but it does not happen during gameplay
            foreach(const QString &name, objectTypeNames)
            {
                // Reset the value of this property to be a reference to GluonObjct
                // instance by that name, found in the project
                if(theValue.startsWith(name + '(') && theValue.endsWith(')'))
                {
                    QString theReferencedName = theValue.mid(name.length() + 2, theValue.length() - (name.length() + 3));
                    QVariant theReferencedObject;
                    theReferencedObject.setValue<GluonObject*>(gameProject()->findItemByName(theReferencedName));
                    this->setProperty(metaproperty.name(), theReferencedObject);
                    break;
                }
            }
        }
        
        // Then get all the dynamic ones (in case any such exist)
        QList<QByteArray> propertyNames = dynamicPropertyNames();
        foreach(QByteArray propName, propertyNames)
        {
            const QString theName(propName);
            if(theName == "objectName" || theName == "name")
                continue;
            
            // This is really only relevant if the property value is a string.
            // If it is not, what happens below is irrelevant
            if(property(propName).type() != QVariant::String)
                continue;
            
            QString theValue(property(propName).toString());
            // Yes, i know this is O(n*m) but it does not happen during gameplay
            foreach(const QString &name, objectTypeNames)
            {
                // Reset the value of this property to be a reference to GluonObjct
                // instance by that name, found in the project
                if(theValue.startsWith(name + '(') && theValue.endsWith(')'))
                {
                    QString theReferencedName = theValue.mid(name.length() + 2, theValue.length() - (name.length() + 3));
                    QVariant theReferencedObject;
                    theReferencedObject.setValue<GluonObject*>(gameProject()->findItemByName(theReferencedName));
                    this->setProperty(propName, theReferencedObject);
                    break;
                }
            }
        }
    }
}

GameProject *
GluonObject::gameProject() const
{
    return d->gameProject;
}

void
GluonObject::setGameProject(GameProject * newGameProject)
{
    d->gameProject = newGameProject;
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
GluonObject::toGDL(int indentLevel) const
{
    QString serializedObject;
    qDebug() << "Serializing object named" << this->name();

    QString indentChars(indentLevel * 4, ' ');

    // Only jump to net line in case we are inside another object
    if(indentLevel > 0)
        serializedObject += '\n';
    
    QString minimalClassName(this->metaObject()->className());
    if(QString(this->metaObject()->className()).startsWith(QString("Gluon::")))
        minimalClassName = minimalClassName.right(minimalClassName.length() - 7);
    serializedObject += QString("%1{ %2(%3)").arg(indentChars).arg(minimalClassName).arg(this->name());
    
    serializedObject += propertiesToGDL(indentLevel + 1);
    
    // Run through all the children to get them as well
    foreach(QObject* child, children())
    {
        GluonObject* theChild = qobject_cast<GluonObject*>(child);
        if(theChild)
            serializedObject += theChild->toGDL(indentLevel + 1);
    }
    
    return QString("%1\n%2}").arg(serializedObject).arg(indentChars);
}

QString
GluonObject::propertiesToGDL(int indentLevel) const
{
    QString serializedObject;

    QString indentChars(indentLevel * 4, ' ');
    
    // Get all the normally defined properties
    const QMetaObject *metaobject = this->metaObject();
    int count = metaobject->propertyCount();
    for(int i = 0; i < count; ++i)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        const QString theName(metaproperty.name());
        if(theName == "objectName" || theName == "name")
            continue;
        serializedObject += this->getStringFromProperty(theName, indentChars);
    }
    
    // Then get all the dynamic ones (in case any such exist)
    QList<QByteArray> propertyNames = dynamicPropertyNames();
    foreach(QByteArray propName, propertyNames)
    {
        const QString theName(propName);
        serializedObject += this->getStringFromProperty(theName, indentChars);
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
GluonObject::getStringFromProperty(const QString &propertyName, const QString &indentChars) const
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
    
    if(value.isEmpty())
        return QString();
    
    return QString("\n%1%2 %3").arg(indentChars).arg(propertyName).arg(value);
}

#include "gluonobject.moc"
