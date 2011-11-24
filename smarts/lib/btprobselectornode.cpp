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

#include "btprobselectornode.h"

#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtCore/QHash>

#include <cmath>

REGISTER_NODETYPE(btProbSelectorNode)

btProbSelectorNode::btProbSelectorNode(QObject* parent)
    : btNode(parent)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

btProbSelectorNode::~btProbSelectorNode()
{
	qDeleteAll(m_probStats);
	m_probStats.clear();
	
	qDeleteAll(m_visitedProbStats);
	m_visitedProbStats.clear();
}

btNode::status btProbSelectorNode::run(btCharacter *self)
{
	if(currentChildStatus() == Succeeded)
	{
		resetProbNodes();
		return Succeeded;
	}
	
	foreach(ProbNode * node, m_visitedProbStats)
	{
		node->visited = true;
	}
	
	float maxProbability = 0.0f;
	
	QHash<ProbNode*, int> unvisitedNodes;
	for(int i = 0; i <  m_probStats.count(); i++)
    {
        if(!m_probStats[i]->visited)
        {
            unvisitedNodes.insert(m_probStats[i], i);
			maxProbability += m_probStats[i]->probability;
        }
    }
	
	float randNum = 0;
	
	if(maxProbability == 0.0f)
		randNum = 0;
	else
		randNum = fmodf(((float)qrand()/RAND_MAX), maxProbability);

	QList<int> values = unvisitedNodes.values();
	float start = 0.0f;
	
    for(int i = 0; i < values.count(); i++)
    {
        ProbNode * node = unvisitedNodes.key(values[i]);
        
        if(node->visited == false)
        {
            if(start < randNum && randNum <= (node->probability + start))
            {				
                m_visitedProbStats.append(node);
                return runChild(unvisitedNodes[node]);
            }
            start += node->probability;
        }
    }
 
    resetProbNodes();
    return Failed;
}

void btProbSelectorNode::appendingChild(int index)
{
    ProbNode *newNode = new ProbNode();
    //qDebug() << "prob stat insert at: " << index;
    m_probStats.insert(index,newNode);
}

void btProbSelectorNode::removingChild(int index)
{
    m_probStats.removeAt(index);
}

void btProbSelectorNode::childrenAdded()
{
    int count = m_probStats.count();
    int i = 0;
    if(count > 0)
	{
		
        if(property("weights").isValid())
		{
            QList<QVariant> probs = property("weights").toList();
			// qDebug() << "probs.count(): " << probs.count();
            foreach(ProbNode *node, m_probStats)
			{
                node->visited = false;
                node->probability = probs.at(i).toDouble();
                i++;
            }
        }
		else
		{
            foreach(ProbNode *node, m_probStats)
			{
                node->probability = (1.0 / count);
            }
        }
        
        resetProbNodes();
    }
}

void btProbSelectorNode::resetProbNodes()
{
	m_visitedProbStats.clear();
	foreach(ProbNode *node, m_probStats)
	{
        node->visited = false;
    }
}

void btProbSelectorNode::setVisitedProbNodes(QList<ProbNode*> probNodes)
{
	m_visitedProbStats = probNodes;
}

QList<ProbNode*> btProbSelectorNode::visitedProbNodes()
{
	return m_visitedProbStats;
}

#include "btprobselectornode.moc"

