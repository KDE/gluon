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

#include "btparallelnode.h"

#include "btnode.h"

#include <QtCore/QVariant>

using namespace GluonSmarts;

REGISTER_NODETYPE(btParallelNode)

btParallelNode::btParallelNode(QObject* parent)
    : btNode(parent)
	, m_runningNodesStatus(new QList<btNode::status>())
	, m_conditionStatus(new QList<btNode::status>())
{
	setCurrentChildStatus(Running);
}

btParallelNode::~btParallelNode()
{
	delete m_runningNodesStatus;
	delete m_conditionStatus;
	
	qDeleteAll(m_nodesIndex.keys());
	m_nodesIndex.clear();
}

btNode::status btParallelNode::run(btCharacter *self)
{	
	if(currentChildStatus() == None)
	{
		return Running;
	}
		
	return currentChildStatus();
}

void btParallelNode::appendingChild(int index)
{	
	//m_runningNodesStatus->insert(index, btNode::None);
	
	m_nodesIndex[child(index)] = index;
}

void btParallelNode::removingChild(int index)
{
	//m_runningNodesStatus->removeAt(index);
	m_nodesIndex.remove(child(index));
}

void btParallelNode::childrenAdded()
{	
	int count = childCount();
    if(count > 0)
	{
        if(property("conditions").isValid())
		{
            QList<QVariant> conditions = property("conditions").toList();
			
			for	(int i = 0; i < count; i++)
			{
				if(conditions[i].toDouble() == 1.0)
				{
					m_conditionStatus->append(btNode::Succeeded);
				}
				else if(conditions[i].toDouble() == 0.0)
				{
					m_conditionStatus->append(btNode::Failed);
				}
				else
                {
                    m_conditionStatus->append(btNode::Running);
                }

			}
        }
		else
		{
            for (int i = 0; i < count; i++)
			{
				m_conditionStatus->append(btNode::Succeeded);
            }
        }
    }
}

btNode::status btParallelNode::conditionsFulfilled()
{
	btNode::status fulfilled = Succeeded;
    bool terminate = false;
    Q_UNUSED(terminate)
	for (int i = 0; i < childCount(); i++)
	{
		if(m_runningNodesStatus->value(i) == btNode::Running && m_runningNodesStatus->value(i) != m_conditionStatus->value(i))
        {
            fulfilled = Running;
        }
		
        if(m_runningNodesStatus->value(i) != btNode::Running && m_runningNodesStatus->value(i) != m_conditionStatus->value(i))
		{
			resetRunningNodesStatus();
			return Failed;
		}
	}
    
	if(fulfilled == Succeeded)
    {
		resetRunningNodesStatus();
    }
	
	return fulfilled;
}

void btParallelNode::resetRunningNodesStatus()
{
	m_runningNodesStatus = NULL;
}

void btParallelNode::setRunningNodesStatus(QList<btNode::status>* nodeStatus)
{
	m_runningNodesStatus = nodeStatus;
}

int btParallelNode::childNodeIndex(btNode* childNode)
{	
	return m_nodesIndex[childNode];
}

#include "btparallelnode.moc"

