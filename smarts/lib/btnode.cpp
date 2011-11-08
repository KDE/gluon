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

#include "btnode.h"

#include <QtCore/QDebug>

btNode::btNode(QObject* parent)
    : QObject(parent)
    , m_name("")
    , m_description("")
    , m_className("")
    , m_type(btNode::UnusableNodeType)
    , m_currentChildIndex(0)
    , m_currentChildStatus(btNode::None)
{
}

btNode::~btNode()
{
	qDeleteAll(m_children);
	m_children.clear();
}

void btNode::setName(QString name)
{
	m_name = name;
}

QString btNode::name()
{
	return m_name;
}

void btNode::setDescription(QString description)
{
	m_description = description;
}

QString btNode::description()
{
	return m_description; 
}

void btNode::setClassName(QString className)
{
	m_className = className;
}

QString btNode::className()
{
	return m_className;
}
	
void btNode::setType(btNode::nodeType type)
{
	m_type = type;
}

btNode::nodeType btNode::type()
{
	return m_type;
}

int btNode::childCount()
{
	return m_children.count();
}

void btNode::appendChild(btNode* child) 
{
	m_children.append(child);
	//has to be in the list, before this function is called
	this->appendingChild(m_children.count()-1);
}

btNode* btNode::child(int index)
{
	return m_children[index];
}

btNode::status btNode::run(btCharacter * self)
{
    qDebug() << "The btNode " << this->className() << " has either not been registered or implemented";
	return btNode::Failed;
}

void btNode::setCurrentChildStatus(status nodeStatus)
{
	m_currentChildStatus = nodeStatus;
}

btNode::status btNode::currentChildStatus()
{
	return m_currentChildStatus;
}

btNode* btNode::currentChild()
{
	return m_children[m_currentChildIndex];
}

void btNode::setCurrentChildIndex(int index)
{
	m_currentChildIndex = index;
}

int btNode::currentChildIndex()
{
	return m_currentChildIndex;
}

btNode::status btNode::runChild()
{
	return btNode::RunningChild;
}

btNode::status btNode::runChild(int index)
{
	m_currentChildIndex = index;
	return btNode::RunningChild;
}

btNode* btNode::parentNode()
{
	return m_parent;
}

void btNode::setParentNode(btNode* parent)
{
	m_parent = parent;
}

void btNode::removeChild(int index)
{
	this->removingChild(index);
	m_children.removeAt(index);
}

void btNode::removeChild(btNode* child)
{
	for (int i = 0; i < m_children.count(); i++)
	{
		if(m_children.at(i) == child)
		{
			this->removeChild(i);
		}
	}
}

void btNode::doneParsingChildren()
{
	this->childrenAdded();
}

int btNode::nextChildIndex()
{
	if(m_currentChildStatus == btNode::None)
		return m_currentChildIndex;
	return ++m_currentChildIndex;
}
	
void btNode::insertChild(int index, btNode* child)
{
	m_children.insert(index, child);
    this->appendingChild(index);
}

int btNode::childIndex(btNode * child)
{
    for (int i = 0; i < m_children.count(); i++)
    {
        if(m_children.at(i) == child)
        {
            return i;
        }
    }
    
    return -1;
}

#include "btnode.moc"
