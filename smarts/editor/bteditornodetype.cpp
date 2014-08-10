/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#include "bteditornodetype.h"

#include "btglobal.h"
#include "projectparser.h"
#include "nodetypefactory.h"
#include "bteditornode.h"

#include <QtWidgets/QRadioButton>
#include <QtCore/QXmlStreamWriter>

btEditorNodeType::btEditorNodeType(QObject * parent)
    : btNodeType(parent)
{
    setNodeType(btNodeType::UnusableNodeType);
}

void btEditorNodeType::setChildType(nodeType type) {
    m_childtype = type;
}

btNodeType::nodeType btEditorNodeType::childType() const
{
    if (m_childtype)
        return m_childtype;
    else
        return UnusableNodeType;
}


btEditorNodeType * btEditorNodeType::copy()
{
    btEditorNodeType * copyNode = nodeTypeFactory::instance()->newObject(type());

    const QMetaObject * mo = metaObject();

    for (int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();

        if (propertyName == "objectName")
        {
            continue;
        }
        copyNode->setProperty(propertyName.toUtf8(), property(moProperty.name()));
    }

    for (int i = 0; i < dynamicPropertyNames().count(); i++)
    {
        QString propertyName(dynamicPropertyNames().at(i));
        copyNode->setProperty(propertyName.toUtf8(), property(propertyName.toUtf8()));
    }

    QHashIterator<QString, QString> i(getPropertyDescriptions());
    while (i.hasNext())
    {
        i.next();
        copyNode->setPropertyDescription(i.key(), i.value());
    }

    return copyNode;

}

void btEditorNodeType::toNodeTypeXml(QXmlStreamWriter* xmlWriter)
{
    if (type() == btNodeType::ReferenceNodeType)
        return;

    xmlWriter->writeStartElement("nodetype");

    const QMetaObject * mo = metaObject();

    for (int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();

        if (propertyName == "objectName")
        {
            continue;
        }

        if (propertyName == "name")
        {
            xmlWriter->writeAttribute("name", property(moProperty.name()).toString());
        }
        else if (propertyName == "description")
        {
            xmlWriter->writeAttribute("description", property(moProperty.name()).toString());
        }
        else if (propertyName == "className")
        {
            xmlWriter->writeAttribute("className", property(moProperty.name()).toString());
        }
    }

    switch (type())
    {
    case btNodeType::ActionNodeType:
        xmlWriter->writeAttribute("category", "action");
        break;
    case btNodeType::CompositeNodeType:
        xmlWriter->writeAttribute("category", "composite");
        break;
    case btNodeType::ConditionNodeType:
        xmlWriter->writeAttribute("category", "condition");
        break;
    case btNodeType::DecoratorNodeType:
        xmlWriter->writeAttribute("category", "decorator");
        break;
    case btNodeType::UnusableNodeType:
        xmlWriter->writeAttribute("category", "unusable");
        break;
    default:
        break;
    }

    for (int i = 0; i < dynamicPropertyNames().count(); i++)
    {
        QString propertyName(dynamicPropertyNames().at(i));

        xmlWriter->writeStartElement("property");

        xmlWriter->writeAttribute("name", propertyName);
        xmlWriter->writeAttribute("description", getPropertyDescription(propertyName));
        xmlWriter->writeAttribute("datatype", property(propertyName.toUtf8()).toString());

        xmlWriter->writeEndElement();
    }

    xmlWriter->writeEndElement();
}

void btEditorNodeType::toDataXml(QXmlStreamWriter* xmlWriter)
{
    Q_UNUSED(xmlWriter)
}

void btEditorNodeType::initProperties()
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    foreach(const QString &name, dynamicPropertyNames())
    {
        int typeId = QMetaType::type(property(name.toUtf8()).toString().toUtf8());
        QVariant dataType;
        switch (typeId)
        {
        case QVariant::Int:
            dataType = 0;
            break;
        case QVariant::Double:
            dataType = 0.00;
            break;
        case QVariant::String:
            dataType = "";
            break;
        case QVariant::List:
            dataType = QVariant(QVariant::List);
            break;
        default:
            if (typeId == QMetaType::type("btChildWeights"))
            {
                btChildWeights cw;
                dataType.setValue(cw);
                break;
            }
            else if (typeId == QMetaType::type("btParallelConditions"))
            {
                btParallelConditions pc;
                dataType.setValue(pc);
                break;
            }
            dataType = QVariant(QVariant::Invalid);
            break;
        }
        setProperty(name.toUtf8(), dataType);
    }
}

void btEditorNodeType::appendingChild(int index)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");

    foreach(const QString &name, dynamicPropertyNames())
    {
        if (property(name.toUtf8()).type() == QVariant::UserType && name == "weights")
        {
            btChildWeights list = property(name.toUtf8()).value<btChildWeights>();

            if (parentNode()->child(index)->type()->property("probability").isValid())
            {
                list.childWeightList.insert(index, parentNode()->child(index)->type()->property("probability").toDouble());
                parentNode()->child(index)->type()->setProperty("probability", QVariant::Invalid);
            }

            QVariant v;
            v.setValue(list);
            setProperty(name.toUtf8(), v);
            break;
        }
    }
}

void btEditorNodeType::removingChild(int index)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    btEditorNodeType * childNodeType = qobject_cast<btEditorNodeType*>(parentNode()->child(index)->type());
    childNodeType->disconnectChangeProperty();
    foreach(const QString &name, dynamicPropertyNames())
    {
        if (property(name.toUtf8()).type() == QVariant::UserType && name == "weights")
        {
            btChildWeights list = property(name.toUtf8()).value<btChildWeights>();
            list.childWeightList.removeAt(index);
            QVariant v;
            v.setValue(list);
            setProperty(name.toUtf8(), v);
            break;
        }
        else if (property(name.toUtf8()).type() == QVariant::UserType && name == "conditions")
        {
            btParallelConditions list = property(name.toUtf8()).value<btParallelConditions>();
            list.parallelConditions.removeAt(index);
            QVariant v;
            v.setValue(list);
            setProperty(name.toUtf8(), v);
            break;
        }
    }
}

void btEditorNodeType::changeProbability(double value)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");

    foreach(const QString &name, parentNode()->parentNode()->type()->dynamicPropertyNames())
    {
        if (parentNode()->parentNode()->type()->property(name.toUtf8()).type() == QVariant::UserType && name == "weights")
        {
            btChildWeights list = parentNode()->parentNode()->type()->property(name.toUtf8()).value<btChildWeights>();
            list.childWeightList[parentNode()->parentNode()->children().indexOf(parentNode())] = value;
            QVariant v;
            v.setValue(list);
            parentNode()->parentNode()->type()->setProperty(name.toUtf8(), v);
            break;
        }
    }
}

void btEditorNodeType::changeProperty(QString propertyName, QVariant value)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");

    int typeId = QMetaType::type(value.toString().toUtf8());
    QVariant dataType;
    switch (typeId)
    {
    case QVariant::Int:
        dataType = 0;
        break;
    case QVariant::Double:
        dataType = 0.00;
        break;
    case QVariant::String:
        dataType = "";
        break;
    case QVariant::List:
        dataType = QVariant(QVariant::List);
        break;
    default:
        /*if(typeId == QMetaType::type("btChildWeights"))
        {
            btChildWeights ch;

            for (int i = 0; i < parentNode()->childCount(); i++) {
                ch.childWeightList.append(0.5);
            }

            dataType.setValue(ch);
            break;
        }*/
        dataType = QVariant(QVariant::Invalid);
        break;
    }

    setProperty(propertyName.toUtf8(), dataType);
}

void btEditorNodeType::disconnectChangeProperty()
{
    disconnect(m_sender, SIGNAL(propertyChanged(QString,QVariant)), this, SLOT(changeProperty(QString,QVariant)));
    disconnect(m_sender, SIGNAL(propertyDescriptionChanged(QString,QString,QString)), this, SLOT(changePropertyDescription(QString,QString,QString)));
    disconnect(m_sender, SIGNAL(nameChanged(QString)), this, SLOT(changeName(QString)));
    disconnect(m_sender, SIGNAL(descriptionChanged(QString)), this, SLOT(changeDescription(QString)));
    disconnect(m_sender, SIGNAL(classNameChanged(QString)), this, SLOT(changeClassName(QString)));
}

void btEditorNodeType::connectChangeProperty(btEditorNodeType* sender)
{
    m_sender = sender;
    connect(m_sender, SIGNAL(propertyChanged(QString,QVariant)), this, SLOT(changeProperty(QString,QVariant)));
    connect(m_sender, SIGNAL(propertyDescriptionChanged(QString,QString,QString)), this, SLOT(changePropertyDescription(QString,QString,QString)));
    connect(m_sender, SIGNAL(nameChanged(QString)), this, SLOT(changeName(QString)));
    connect(m_sender, SIGNAL(descriptionChanged(QString)), this, SLOT(changeDescription(QString)));
    connect(m_sender, SIGNAL(classNameChanged(QString)), this, SLOT(changeClassName(QString)));
}

void btEditorNodeType::emitPropertyChangedSignal(QString propertyName, QVariant value)
{
    emit propertyChanged(propertyName, value);
}

void btEditorNodeType::emitPropertyDescriptionChangedSignal(QString propertyName, QString oldPropertyName , QString description)
{
    emit propertyDescriptionChanged(propertyName, oldPropertyName, description);
}

void btEditorNodeType::changePropertyDescription(QString propertyName, QString oldPropertyName , QString description)
{
    if (propertyName.isEmpty() && description.isEmpty())
    {
        removePropertyDescription(oldPropertyName);
    }
    else if (oldPropertyName.isEmpty())
    {
        setPropertyDescription(propertyName, description);
    }
    else
    {
        setPropertyDescription(propertyName, oldPropertyName, description);
    }
}

void btEditorNodeType::removeActionTriggered()
{
    btEditorNode * node = qobject_cast<btEditorNode*>(parentNode());
    node->removeDecorator(this);
    node->emitUpdatePropertyWidget();
}

void btEditorNodeType::moveUpAction()
{
    btEditorNode * node = qobject_cast<btEditorNode*>(parentNode());
    node->moveDecorator(-1, this);
    node->emitUpdatePropertyWidget();
}

void btEditorNodeType::moveDownAction()
{
    btEditorNode * node = qobject_cast<btEditorNode*>(parentNode());
    node->moveDecorator(1, this);
    node->emitUpdatePropertyWidget();
}

void btEditorNodeType::emitNameChanged(QString name)
{
    emit nameChanged(name);
}

void btEditorNodeType::emitClassNameChanged(QString className)
{
    emit classNameChanged(className);
}

void btEditorNodeType::emitDescriptionChanged(QString description)
{
    emit descriptionChanged(description);
}

void btEditorNodeType::changeName(QString name)
{
    setName(name);
    emit nameChanged(name);
}

void btEditorNodeType::changeDescription(QString description)
{
    setDescription(description);
    emit descriptionChanged(description);
}

void btEditorNodeType::changeClassName(QString className)
{
    setClassName(className);
    emit classNameChanged(className);
}

void btEditorNodeType::changeCondition(bool state)
{
    Q_UNUSED(state)
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    QRadioButton * radioButton = qobject_cast<QRadioButton*>(QObject::sender());

    foreach(const QString &name, parentNode()->parentNode()->type()->dynamicPropertyNames())
    {
        if (parentNode()->parentNode()->type()->property(name.toUtf8()).type() == QVariant::UserType && name == "conditions")
        {
            btParallelConditions list = parentNode()->parentNode()->type()->property(name.toUtf8()).value<btParallelConditions>();
            double value = 0;
            if (radioButton->text() == "Succeeded")
            {
                value = 1;
            }
            else if (radioButton->text() == "Failed")
            {
                value = 0;
            }
            else
            {
                value = -1;
            }

            list.parallelConditions[parentNode()->parentNode()->children().indexOf(parentNode())] = value;

            QVariant v;
            v.setValue(list);
            parentNode()->parentNode()->type()->setProperty(name.toUtf8(), v);
            break;
        }
    }
}

 
