#ifndef BTPROBSELECTORNODE_H
#define BTPROBSELECTORNODE_H

#include <QObject>

#include "btlib.h"


class BT_LIB_EXPORT btProbSelectorNode : public btNode
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btProbSelectorNode();
	~btProbSelectorNode();
	
	btNode::status run(btCharacter *self);
    void appendingChild(int index);
    void removingChild(int index);
    void childrenAdded();
	void resetProbNodes();
	void setVisitedProbNodes(QList<ProbNode*> probNodes);
	QList<ProbNode*> visitedProbNodes();
	
private:
    QList<ProbNode*> m_probStats;
	QList<ProbNode*> m_visitedProbStats;
};

#endif //BTPROBSELECTORNODE_H
