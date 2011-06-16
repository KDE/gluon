#include "btparallelnode.h"

#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include "btnode.h"

REGISTER_NODETYPE(btParallelNode)

btParallelNode::btParallelNode()
{
	this->setCurrentChildStatus(Running);
	m_runningNodesStatus = new QList<btNode::status>();
	m_conditionStatus = new QList<btNode::status>();
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
	if(this->currentChildStatus() == None)
	{
		return Running;
	}
		
	return this->currentChildStatus();
}

void btParallelNode::appendingChild(int index)
{	
	//m_runningNodesStatus->insert(index, btNode::None);
	
	m_nodesIndex[this->child(index)] = index;
}

void btParallelNode::removingChild(int index)
{
	//m_runningNodesStatus->removeAt(index);
	m_nodesIndex.remove(this->child(index));
}

void btParallelNode::childrenAdded()
{	
	int count = this->childCount();
    if(count > 0)
	{
        if(this->property("conditions").isValid())
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
	for (int i = 0; i < this->childCount(); i++)
	{
		if(m_runningNodesStatus->value(i) == btNode::Running && m_runningNodesStatus->value(i) != m_conditionStatus->value(i))
        {
            fulfilled = Running;
        }
		
        if(m_runningNodesStatus->value(i) != btNode::Running && m_runningNodesStatus->value(i) != m_conditionStatus->value(i))
		{
			this->resetRunningNodesStatus();
			return Failed;
		}
	}
    
	if(fulfilled == Succeeded)
    {
		this->resetRunningNodesStatus();
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

