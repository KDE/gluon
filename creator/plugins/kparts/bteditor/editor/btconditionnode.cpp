#include "btconditionnode.h"

btConditionNode::btConditionNode()
{
    setNodeType(btNodeType::ConditionNodeType);
}

btConditionNode::~btConditionNode()
{
}

bool btConditionNode::run()
{
	return false;
}

#include "btconditionnode.moc"