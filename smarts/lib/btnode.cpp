#include "btnode.h"

#include <QtCore/QDebug>

btNode::btNode()
{
	m_name = "";
	m_description = "";
	m_className = "";
	m_type = btNode::UnusableNodeType;
	m_currentChildStatus = btNode::None;
	m_currentChildIndex = 0;
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
