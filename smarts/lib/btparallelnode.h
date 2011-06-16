#ifndef BTPARALLELNODE_H
#define BTPARALLELNODE_H

#include "btlib.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QQueue>
#include <QtCore/QHash>

class btParallelNode : public btNode
{
    Q_OBJECT
	
public:
    Q_INVOKABLE btParallelNode();
	~btParallelNode();
	
	btNode::status run(btCharacter *self);
	
	void appendingChild(int index);
	void removingChild(int index);
	void childrenAdded();
	
	btNode::status conditionsFulfilled();
	
	void resetRunningNodesStatus();
	void setRunningNodesStatus(QList<btNode::status>* nodeStatus);
	
	int childNodeIndex(btNode* childNode);
private:
	QList<btNode::status>* m_runningNodesStatus;
	QList<btNode::status>* m_conditionStatus;
	QHash<btNode*, int> m_nodesIndex;
};


#endif // BTPARALLELNODE_H
