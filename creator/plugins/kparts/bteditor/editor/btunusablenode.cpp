#include "btunusablenode.h"

btUnusableNode::btUnusableNode()
{
    setNodeType(btNodeType::UnusableNodeType);
}

btUnusableNode::~btUnusableNode()
{
}

bool btUnusableNode::run()
{
	return false;
}

#include "btunusablenode.moc"