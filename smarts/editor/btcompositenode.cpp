#include "btcompositenode.h"

btCompositeNode::btCompositeNode()
{
    setNodeType(btNodeType::CompositeNodeType);
}


btCompositeNode::~btCompositeNode()
{
}

bool btCompositeNode::run()
{
	return false;
}

#include "btcompositenode.moc"