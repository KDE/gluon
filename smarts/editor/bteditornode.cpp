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

#include "bteditornode.h"

#include "bttreemodel.h"
#include "projectparser.h"
#include "btreferencenode.h"
#include "btdecoratornode.h"
#include "btglobal.h"

#include <QtCore/QXmlStreamWriter>

btEditorNode::btEditorNode(btNodeType *type, btNode *parent)
    : btNode(type, parent)
{
}

btEditorNode::~btEditorNode()
{
    qDeleteAll(m_decorators);
}

void btEditorNode::toXml(QXmlStreamWriter* xmlWriter, QList<btTreeModel *> behaviorTrees)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    xmlWriter->writeStartElement("behaviornode");

    xmlWriter->writeAttribute("name", name());
    xmlWriter->writeAttribute("description", description());

    btNodeType * nodeType = type();
    const QMetaObject * mo = nodeType->metaObject();

    for (int i = 0; i < mo->propertyCount(); i++)
    {
        QMetaProperty moProperty = mo->property(i);
        QString propertyName = moProperty.name();

        if (propertyName == "objectName")
        {
            continue;
        }

        if (propertyName == "className")
        {
            if (nodeType->type() == btNodeType::ReferenceNodeType)
            {
                xmlWriter->writeAttribute("nodetype", "[reference]");
            }
            else
            {
                xmlWriter->writeAttribute("nodetype", nodeType->property(moProperty.name()).toString());
            }
        }
    }

    if (nodeType->type() == btNodeType::ReferenceNodeType)
    {
        btReferenceNode * btRefNode = qobject_cast<btReferenceNode*>(nodeType);
        xmlWriter->writeStartElement("property");
        xmlWriter->writeAttribute("name", "reference");

        for (int i = 0; i < behaviorTrees.count(); i ++)
        {
            if (btRefNode->referenceBehaviorTree() == behaviorTrees.at(i))
            {
                xmlWriter->writeAttribute("value",  QVariant(i).toString());
                break;
            }
        }

        if (decoratorCount() > 0)
        {
            foreach(btNodeType* node, decorators())
            {
                btDecoratorNode* decorator = qobject_cast<btDecoratorNode*>(node);
                decorator->toDataXml(xmlWriter);
            }
        }

        xmlWriter->writeEndElement();
    }
    else
    {
        for (int i = 0; i < nodeType->dynamicPropertyNames().count(); i++)
        {
            QString propertyName(nodeType->dynamicPropertyNames().at(i));

            xmlWriter->writeStartElement("property");
            xmlWriter->writeAttribute("name", propertyName);

            QVariant value = nodeType->property(propertyName.toUtf8());

            if (value.type() == QVariant::List)
            {
                xmlWriter->writeAttribute("value", "");
                QVariantList list = qvariant_cast<QVariantList>(value);

                foreach(const QVariant &v, list)
                {
                    xmlWriter->writeStartElement("item");

                    xmlWriter->writeAttribute("value", v.toString());

                    xmlWriter->writeEndElement(); //item
                }

            }
            else if (value.type() == QVariant::UserType)
            {
                xmlWriter->writeAttribute("value", "");

                if (propertyName == "weights")
                {
                    double totalProbability = 0.0;

                    btChildWeights list = value.value<btChildWeights>();

                    foreach(const QVariant &v, list.childWeightList)
                    {
                        totalProbability += v.toDouble();
                    }

                    foreach(const QVariant &v, list.childWeightList)
                    {
                        QVariant prob = v.toDouble()/totalProbability;

                        xmlWriter->writeStartElement("item");

                        xmlWriter->writeAttribute("value", prob.toString());
                        xmlWriter->writeAttribute("editorvalue", v.toString());

                        xmlWriter->writeEndElement(); //item
                    }
                }
                else if (propertyName == "conditions")
                {
                    btParallelConditions list = value.value<btParallelConditions>();

                    foreach(const QVariant &v, list.parallelConditions)
                    {
                        QVariant condition = v.toDouble();

                        xmlWriter->writeStartElement("item");

                        xmlWriter->writeAttribute("value", condition.toString());
                        xmlWriter->writeAttribute("editorvalue", v.toString());

                        xmlWriter->writeEndElement(); //item
                    }
                }
            }
            else
            {
                xmlWriter->writeAttribute("value", value.toString());
            }

            xmlWriter->writeEndElement(); //property
        }

        for (int i = 0; i < decoratorCount(); i++)
        {
            qobject_cast<btEditorNodeType*>(decorators().at(i))->toDataXml(xmlWriter);
        }
        for (int i = 0; i < childCount(); i++)
        {
            qobject_cast<btEditorNode*>(child(i))->toXml(xmlWriter, behaviorTrees);
        }
    }

    xmlWriter->writeEndElement(); //behaviornode
}

QVariant btEditorNode::headerData(int column) const
{
    if (column == 0)
        return tr("Name");
    else if (column == 1)
        return tr("Description");
    else if (column == 2)
        return tr("Type");

    return QVariant();
}

QVariant btEditorNode::data(int column) const
{
    switch (column)
    {
    case 0:
        return name();
        break;
    case 1:
        if ( !decorators().isEmpty() )
            return QString("%1 (%2)").arg(description()).arg(decoratorCount());
        else
            return description();
        break;
    case 2:
        return type()->name();
        break;
    default:
        return QVariant();
        break;
    }
    return QVariant();
}

void btEditorNode::addDecorator(btNodeType* decorator)
{
    m_decorators.append(decorator);
    decorator->setParentNode(this);
}

void btEditorNode::moveDecorator(int move, btNodeType * decorator)
{
    if (m_decorators.indexOf(decorator) > -1)
    {
        int orgIndex = m_decorators.indexOf(decorator);
        m_decorators.removeAt(orgIndex);
        int index = orgIndex + move;
        if (index < 0)
        {
            m_decorators.insert(0, decorator);
        }
        else if (index > m_decorators.count()-1)
        {
            m_decorators.append(decorator);
        }
        else
        {
            m_decorators.insert(index, decorator);
        }

    }
}

void btEditorNode::removeDecorator(btNodeType* decorator) {
    m_decorators.removeAll(decorator);
}
int btEditorNode::decoratorCount() const {
    return m_decorators.count();
}
QList<btNodeType*> btEditorNode::decorators() const {
    return m_decorators;
}

void btEditorNode::emitUpdatePropertyWidget()
{
    emit updatePropertyWidget(this);
}

#include "bteditornode.moc"
