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

#include "btfactory.h"

#include "btnode.h"
#include "btbrain.h"
#include "btselectornode.h"
#include "btsequencenode.h"
#include "btprobselectornode.h"
#include "btparallelnode.h"

#include "btglobal.h"

#include <QtCore/QDebug>

btFactory::btFactory()
{
    m_nodeTypes["[selector]"] = new btSelectorNode();
    m_nodeTypes["[selector]"]->setType(btNode::CompositeNodeType);
    m_nodeTypes["[sequence]"] = new btSequenceNode();
    m_nodeTypes["[sequence]"]->setType(btNode::CompositeNodeType);
	m_nodeTypes["[probselector]"] = new btProbSelectorNode();
    m_nodeTypes["[probselector]"]->setType(btNode::CompositeNodeType);
	m_nodeTypes["[probselector]"]->setProperty("weights", "btChildWeights");
	m_nodeTypes["[parallel]"] = new btParallelNode();
    m_nodeTypes["[parallel]"]->setType(btNode::CompositeNodeType);
    m_nodeTypes["[parallel]"]->setProperty("conditions", "btParallelConditions");
}

btFactory* btFactory::instance()
{
    static btFactory* m_instance;
    
    if(m_instance == 0)
    {
        m_instance = new btFactory();
    }
    
    return m_instance;
}

btNode* btFactory::newObject(QDomNode xmlNode, btNode* parentNode, btBrain* brain)
{
    if(xmlNode.attributes().namedItem("nodetype").nodeValue() == "[reference]")
    {
        this->addProperty(parentNode, xmlNode.childNodes().at(0), brain);
        return NULL;
    }
	
	btNode* nodeType = m_nodeTypes[xmlNode.attributes().namedItem("nodetype").nodeValue()];
    btNode* newBTNode = qobject_cast<btNode*>(nodeType->metaObject()->newInstance());
    newBTNode->setType(nodeType->type());
    foreach(const QString &name ,nodeType->dynamicPropertyNames())
    {
        newBTNode->setProperty(name.toUtf8(),nodeType->property(name.toUtf8()));
    }
    
    if(!xmlNode.attributes().namedItem("name").isNull())
    {
        newBTNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    }
    if(!xmlNode.attributes().namedItem("description").isNull())
    {
        newBTNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    }
    if(!xmlNode.attributes().namedItem("nodetype").isNull())
    {
        newBTNode->setClassName(xmlNode.attributes().namedItem("nodetype").nodeValue());
    }
    
    parentNode->appendChild(newBTNode);
    newBTNode->setParentNode(parentNode);
    
    return newBTNode;
}
                               
btNode* btFactory::newObject(QString className)
{
	btNode* newBTNode = qobject_cast<btNode*>(m_nodeTypes[className]->metaObject()->newInstance());
    if(!newBTNode)
        newBTNode = new btNode();
    return newBTNode;
}
                               

void btFactory::registerNodeType(btNode* newType)
{
    m_nodeTypes[newType->metaObject()->className()] = newType;
}

void btFactory::registerNodeType(btNode * newType, QString className)
{
    m_nodeTypes[className] = newType;
}

btNode* btFactory::getRegisteredNodeType(QString className)
{
    return m_nodeTypes[className];
}

void btFactory::initNodeType(QDomNode xmlNode)
{
    QDomNamedNodeMap nodeTypeAttributes = xmlNode.attributes();
    btNode* nodeType = btFactory::instance()->getRegisteredNodeType(nodeTypeAttributes.namedItem("className").nodeValue());
    
    if(!nodeType)
    {
        nodeType = new btNode();
        nodeType->setType(btNode::UnusableNodeType);
        btFactory::instance()->registerNodeType(nodeType, nodeTypeAttributes.namedItem("className").nodeValue());
    }
    else
    {
        QString typeCategory = nodeTypeAttributes.namedItem("category").nodeValue();
    
        if(typeCategory == "action")
        {
            nodeType->setType(btNode::ActionNodeType);
        }
        else if(typeCategory == "condition")
        {
            nodeType->setType(btNode::ConditionNodeType);
        }
        else if(typeCategory == "composite")
        {
            nodeType->setType(btNode::CompositeNodeType);
        }
        else if(typeCategory == "decorator")
        {
            nodeType->setType(btNode::DecoratorNodeType);
        }
        else if(typeCategory == "reference")
        {
            nodeType->setType(btNode::ReferenceNodeType);
        }
        else
        {
            nodeType->setType(btNode::UnusableNodeType);
        }
    }
    
    nodeType->setName(nodeTypeAttributes.namedItem("name").nodeValue());
    nodeType->setDescription(nodeTypeAttributes.namedItem("description").nodeValue());
    nodeType->setClassName(nodeTypeAttributes.namedItem("className").nodeValue());
    
    for(int j = 0; j < xmlNode.childNodes().count(); j++)
    {
        QDomNode currentProperty = xmlNode.childNodes().at(j);
        QDomNamedNodeMap propertyAttributes = currentProperty.attributes();
        nodeType->setProperty(propertyAttributes.namedItem("name").nodeValue().toUtf8(), propertyAttributes.namedItem("datatype").nodeValue());
    }    
    
}

void btFactory::addProperty(btNode* node, QDomNode xNode ,btBrain* brain)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
	qRegisterMetaType<btParallelConditions>("btParallelConditions");
    
    if(xNode.attributes().namedItem("name").nodeValue() == "reference")
    {
        btNode* currentParent = node;
        if(xNode.hasChildNodes())
        {
            for (int i = 0; i < xNode.childNodes().count(); i++)
            {
                currentParent = btFactory::instance()->newObject(xNode.childNodes().at(i), currentParent, brain);
            }
        }
		
        currentParent->appendChild(brain->getBehaviorTree(xNode.attributes().namedItem("value").nodeValue().toInt()));
        
        return;
    }
    
    int typeId = QMetaType::type(node->property(xNode.attributes().namedItem("name").nodeValue().toUtf8()).toString().toUtf8());
    QVariant dataType;
    
    if(typeId == QVariant::List)
    {
        QVariantList list =  qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
        
        for(int i = 0; i < xNode.childNodes().count(); i++)
        {
            QDomNamedNodeMap attributes = xNode.childNodes().at(i).attributes();
            if(!attributes.namedItem("value").isNull())
                list.append(attributes.namedItem("value").nodeValue());
        }
        
        dataType = list;
    }
    else if(typeId == QMetaType::type("btChildWeights") || typeId == QMetaType::type("btParallelConditions"))
    {
        QVariantList list;
        
        for(int i = 0; i < xNode.childNodes().count(); i++)
        {
            QDomNamedNodeMap attributes = xNode.childNodes().at(i).attributes();
            if(!attributes.namedItem("value").isNull())
			{
				list.append(attributes.namedItem("value").nodeValue().toDouble());
			}
        }
        
        dataType = list;
    }
    else 
    {
        dataType = xNode.attributes().namedItem("value").nodeValue();
        dataType.convert((QVariant::Type)typeId);
    }
    
    node->setProperty(xNode.attributes().namedItem("name").nodeValue().toUtf8(), dataType);
    
}

btNode* btFactory::createRootNode(QDomNode xmlNode, btBrain* brain)
{
	btNode* newRootNode = (btNode*)this->m_nodeTypes["[sequence]"]->metaObject()->newInstance();
    newRootNode->setParent(brain);
    
    newRootNode->setName(xmlNode.attributes().namedItem("name").nodeValue());
    newRootNode->setDescription(xmlNode.attributes().namedItem("description").nodeValue());
    
    return newRootNode;
}

#include "btfactory.moc"
