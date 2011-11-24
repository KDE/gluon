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

#include "btcharacter.h"

#include <QtCore/QDebug>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QFileInfo>

#include <sys/stat.h>

btCharacter::btCharacter(QObject* parent)
    : QObject(parent)
    , m_thinksBeforeSaving(10)
    , m_thinksDone(0)
    , m_behaviortree(0)
    , m_position(QVector3D())
    , m_orientation(QQuaternion())
    , m_perception(new btPerception(this))
{
	m_nodesStatusQueue.enqueue(btNode::None);
}

btCharacter::~btCharacter()
{
	this->clearExecution();
}

void btCharacter::setBehaviorTree(btNode* behaviorTree)
{
	this->clearExecution();
	
	m_behaviortree = behaviorTree;
	
	QStack<btNode*>* currentNodeStack = new QStack<btNode*>();
	currentNodeStack->push(m_behaviortree);
	
	QStack<int> currentChildStack = QStack<int>();
	currentChildStack.push(0);
	
	m_currentChildStackQueue.enqueue(currentChildStack);
	
	QPair<QStack<btNode*>*, QStack<btNode*>*> pair;
	pair.first = currentNodeStack;
	pair.second = NULL;
	m_currentNodeStackQueue.enqueue(pair);
	
	m_nodesProbabilities.clear();
	initProbabilityHash(m_behaviortree);
	
	btBrain * brain = qobject_cast<btBrain*>(m_behaviortree->parent());
	this->setFile(brain->getFile());
}

void btCharacter::think()
{
	//local variables used in think
	btProbSelectorNode * probSelector = NULL;
	btParallelNode * parallel = NULL;
	btNode* currentParent = NULL;
	QStack<QList<ProbNode*> > visitedProbChildrenStack;
	QStack<btNode*>* currentNodeStack = NULL;
	QStack<int> currentChildStack;
	btNode::status nodeStatus;
	int currentChildIndex = 0;
	
	QPair<QStack<btNode*>*, QStack<btNode*>*> currentChildParentStackPair;
	
	//retrieve a execution stack
	currentChildParentStackPair = m_currentNodeStackQueue.dequeue();
	currentNodeStack = currentChildParentStackPair.first;
	currentChildStack = m_currentChildStackQueue.dequeue();
	nodeStatus = m_nodesStatusQueue.dequeue();
	
	//retrieve the executing node
	btNode* currentNode = currentNodeStack->top();
	
	//check if it s possible to set parent, and set it if possible
	if(currentNodeStack->count() > 1)
	{
		currentParent = currentNodeStack->at(currentNodeStack->count() - 2);
	}
	
	//check if it s possible to set current child, and set it if possible
	if(currentChildStack.count() > 0)
	{
		currentChildIndex = currentChildStack.pop();
	}
	
	if (QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
	{
		//if the current node is a probselector, cast it
		probSelector = qobject_cast<btProbSelectorNode*>(currentNode);
		
		//and set the probnodes if we have run it before
		if(m_visitedProbChildrenHash.contains(currentNodeStack))
		{
			probSelector->setVisitedProbNodes(m_visitedProbChildrenHash[currentNodeStack].pop());
		}
	}
	else if (QString(currentNode->metaObject()->className()) == "btParallelNode")
	{
		//if the current node is a parallel, cast it
		parallel = qobject_cast<btParallelNode*>(currentNode);
		
		//if it is the first time, create execution stacks, child stacks etc. for each child and add them to the queue
		if(nodeStatus == btNode::None)
		{			
			QList<btNode::status>* childStatus = new QList<btNode::status>();
			
			for(int i = 0; i < parallel->childCount(); i++)
			{
				QStack<btNode*>* newStack = new QStack<btNode*>();
				newStack->push(parallel);
				newStack->push(parallel->child(i));
				QPair<QStack<btNode*>*, QStack<btNode*>*> pair;
				pair.first = newStack;
				pair.second = currentNodeStack;
				m_currentNodeStackQueue.enqueue(pair);
				
				childStatus->append(btNode::Running);
				m_nodesStatusQueue.enqueue(btNode::None);
				
				m_parallelNodeStatusHash.insert(newStack, childStatus);
				
				QStack<int> childStack = QStack<int>();
				childStack.push(0);
				m_currentChildStackQueue.append(childStack);
			}

			m_parallelNodeStatusHash.insert(currentNodeStack, childStatus);
			nodeStatus = btNode::Running;
		}
		
		//check if termination conditions is fulfilled, return btNode::Running if not
		parallel->setRunningNodesStatus(m_parallelNodeStatusHash.value(currentNodeStack));
		nodeStatus = parallel->conditionsFulfilled();
	}	
	
	//restore the execution state of the current executing node
	currentNode->setCurrentChildIndex(currentChildIndex);
	currentNode->setCurrentChildStatus(nodeStatus);
	currentNode->setParentNode(currentParent);
	
	//qDebug() << currentNode->name();
	//run the node
	nodeStatus = currentNode->run(this);
    
	//handle the status messsage
	switch (nodeStatus)
	{
		case btNode::RunningChild:
            qDebug() << currentNode->name() <<  ": running child";
			//when running child, push the child and child index onto the stacks
			currentNodeStack->push(currentNode->currentChild());
			currentChildStack.push(currentNode->currentChildIndex());
			currentChildStack.push(0);
			
			//enqueue the stacks and status
			m_currentNodeStackQueue.enqueue(currentChildParentStackPair);
			m_currentChildStackQueue.enqueue(currentChildStack);
			
			m_nodesStatusQueue.enqueue(btNode::None);
			
			//if current node is a probselector, then save the probnodes
			if(probSelector)
			{
				m_visitedProbChildrenHash[currentNodeStack].push(probSelector->visitedProbNodes());
			}
			
			//add to runs
			m_nodesProbabilities[currentNode->currentChild()].runs++;
			break;
		case btNode::Failed:
		case btNode::Succeeded:
            if(nodeStatus == btNode::Failed)
            {
                qDebug() << currentNode->name() << ": failed";
            }
            else
            {
                qDebug() << currentNode->name() << ": succeeded";
            }
			//calculate probs
			if(nodeStatus == btNode::Succeeded)
			{
				probability * p = & m_nodesProbabilities[currentNode];
				p->succeeds++;
                if(p->runs == 0)
                    p->runs++;
				p->prob = (double)(p->succeeds / p->runs);
			}
			
			//when the node fails or succeeds
			if(currentNodeStack->count() > 1)
			{	
				//if there is more than one node in the stack, pop it
				currentNodeStack->pop();
			}
			else
			{	
				//else if count == 0 then push a 0 on it
				if(currentChildStack.count() == 0)
				{
					currentChildStack.push(0);
				}
				
				//if the node is the root, reset status
				if(currentNode == m_behaviortree)
					nodeStatus = btNode::None;
			}	
			
			if(QString(currentNode->metaObject()->className()) == "btProbSelectorNode")
			{				
				//if probselector then remove the probnodes for this stack
				if(m_visitedProbChildrenHash[currentNodeStack].count() == 0)
					m_visitedProbChildrenHash.remove(currentNodeStack);
			}
			
			if(currentParent != NULL && QString(currentParent->metaObject()->className()) == "btParallelNode")
			{
				//if the parent is a parallel, set the status for that parallel.
				parallel = qobject_cast<btParallelNode*>(currentParent);
				QList<btNode::status>* m_parallelNodeStatus = m_parallelNodeStatusHash.value(currentNodeStack);
				m_parallelNodeStatus->replace(parallel->childNodeIndex(currentNode), nodeStatus);
				m_parallelNodeStatusHash.remove(currentNodeStack, m_parallelNodeStatus);
				
				if(m_parallelNodeStatusHash.count(currentNodeStack) == 0)
				{
					//remove the stack if there is no other node status in the hash
					delete currentNodeStack;
					currentNodeStack = NULL;					
				}
			}
			
			if(QString(currentNode->metaObject()->className()) == "btParallelNode")
			{				
				//if parallel stop the children and remove the node status list from the hash
				stopParallelExecution(currentNode, currentNodeStack);
				
				if(currentNodeStack)
				{
					QList<btNode::status>* status = m_parallelNodeStatusHash.value(currentNodeStack);
					m_parallelNodeStatusHash.remove(currentNodeStack, m_parallelNodeStatusHash.value(currentNodeStack));
					delete status;
				}
			}
			
			if(currentNodeStack)
			{				
				//if node stack is not deleted, enqueue it again
				m_currentNodeStackQueue.enqueue(currentChildParentStackPair);
				m_currentChildStackQueue.enqueue(currentChildStack);
				m_nodesStatusQueue.enqueue(nodeStatus);
			}			
			break;
		case btNode::Running:
            qDebug() << currentNode->name() <<  ": still running";
			//enqueue stack and stuff
			currentChildIndex = currentNode->currentChildIndex();			
			m_currentNodeStackQueue.enqueue(currentChildParentStackPair);
			currentChildStack.push(currentChildIndex);
			m_currentChildStackQueue.enqueue(currentChildStack);
			m_nodesStatusQueue.enqueue(nodeStatus);
			break;
	}
	
	if(m_thinksBeforeSaving == m_thinksDone)
	{
		this->saveProbabilities();
		m_thinksDone = 0;
	}
	else
	{
		m_thinksDone++;
	}
}

void btCharacter::stopParallelExecution(btNode * currentNode, QStack<btNode*>* parentStack)
{    
    qDebug() <<"stopping parallel";
    QStack<QPair<QStack<btNode*>*, QStack<btNode*>*> >  * nodeStacksForTermination = new QStack<QPair<QStack<btNode*>*, QStack<btNode*>*> >();
	
	findParallelsForTermination(currentNode, parentStack, nodeStacksForTermination);

	while(!nodeStacksForTermination->empty())
    {		
        int counter = m_currentNodeStackQueue.count();
        Q_UNUSED(counter)
		
        QPair<QStack<btNode*>*, QStack<btNode*>*> terminationPair = nodeStacksForTermination->pop();
		
        int index = m_currentNodeStackQueue.indexOf(terminationPair);
        m_currentNodeStackQueue.removeOne(terminationPair);
        qDebug() <<"stopping stack";

        QList<btNode::status>* status = m_parallelNodeStatusHash.value(terminationPair.first);
        QStack<btNode*>* tmp = terminationPair.first;
        while (m_parallelNodeStatusHash.contains(tmp)) 
        {
            m_parallelNodeStatusHash.remove(tmp, m_parallelNodeStatusHash.value(tmp));
        }
        
        m_visitedProbChildrenHash.remove(tmp);
        
        if(QString(tmp->last()->metaObject()->className()) == QString("btParallelNode"))
        {
            delete status;
        }
        
        delete tmp;
        
        m_nodesStatusQueue.removeAt(index);
        m_currentChildStackQueue.removeAt(index);
    }
	
	qDebug() << "stopped parallel";
}

void btCharacter::findParallelsForTermination(btNode * currentNode, QStack<btNode*>* parentStack, QStack<QPair<QStack<btNode*>*, QStack<btNode*>*> > * stack)
{
    for(int i = 0; i < m_currentNodeStackQueue.count(); i++)
    {
        QPair<QStack<btNode*>*, QStack<btNode*>*> pair =  m_currentNodeStackQueue.value(i);
        if(pair.first->front() == currentNode && pair.second == parentStack)
        {
            
            qDebug() << "found " << pair.first->last()->name();
            stack->push(pair);
			
            if(QString(pair.first->top()->metaObject()->className()) == QString("btParallelNode"))
            {
                findParallelsForTermination(pair.first->last(), pair.first, stack);
            }
        }
    }
}

void btCharacter::clearExecution()
{
	for (int i = 0; i < m_currentNodeStackQueue.count(); i++)
	{
		delete m_currentNodeStackQueue.at(i).first;
	}
	m_currentNodeStackQueue.clear();
	m_currentChildStackQueue.clear();
	
	qDeleteAll(m_visitedProbChildrenHash.keys());
	m_visitedProbChildrenHash.clear();
	
	qDeleteAll(m_parallelNodeStatusHash.values());
	qDeleteAll(m_parallelNodeStatusHash.keys());
	
	m_parallelNodeStatusHash.clear();
}

QVector3D btCharacter::position() const
{
    return m_position;
}

void btCharacter::setPosition(const QVector3D& newPosition)
{
    m_position = newPosition;
}

QQuaternion btCharacter::orientation() const
{
    return m_orientation;
}

void btCharacter::setOrientation(const QQuaternion& newOrientation)
{
    m_orientation = newOrientation;
}

btPerception* btCharacter::perception()
{
    return m_perception;
}

void btCharacter::saveProbabilities()
{	
	QString m_xmlData = "";
	QFile file(m_filename);
	
	QXmlStreamWriter* xmlWriter = new QXmlStreamWriter(&m_xmlData);
	xmlWriter->setAutoFormatting(true);
	
	if(!file.exists())
		xmlWriter->writeStartDocument("1.0");
	
	this->saveNodeProbabilities(m_behaviortree, xmlWriter);
	
	file.open(QIODevice::Append | QIODevice::Text);
	QByteArray byteFileContents(m_xmlData.toUtf8());
	file.write(byteFileContents);
	file.close();
}

void btCharacter::initProbabilityHash(btNode * node)
{
	m_nodesProbabilities[node] = probability();
	
	for(int i = 0; i < node->childCount(); i++)
	{
		initProbabilityHash(node->child(i));
	}
}

void btCharacter::saveNodeProbabilities(btNode * node, QXmlStreamWriter * xmlWriter)
{
	xmlWriter->writeStartElement("behaviornode");
	xmlWriter->writeAttribute("name", node->name());
	xmlWriter->writeAttribute("description", node->description());
	xmlWriter->writeAttribute("probability", QString("%1").arg(m_nodesProbabilities[node].prob));
	
	int count = node->childCount();

	for (int i = 0; i < count; i++)
	{
		saveNodeProbabilities(node->child(i), xmlWriter);
	}
	
	xmlWriter->writeEndElement();
}

void btCharacter::setFile(QString file)
{
	QFileInfo info(file);
	QString path = info.path();
	QString name = info.fileName();
	
	int insert = name.lastIndexOf(".") - 1;
	
	m_filename = name.insert(insert, "-probabilities");
}

#include "btcharacter.moc"
