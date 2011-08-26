#include "btactionnode.h"

btActionNode::btActionNode(QObject* parent)
{
    setNodeType(btNodeType::ActionNodeType);
}

btActionNode::~btActionNode()
{
}

bool btActionNode::run()
{
	return false;
}

#include "btactionnode.moc"