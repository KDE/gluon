#include "btreferencenode.h"

btReferenceNode::btReferenceNode()
{
    setNodeType(btNodeType::ReferenceNodeType);
}

btReferenceNode::~btReferenceNode()
{
}

bool btReferenceNode::run()
{
	return false;
}

void btReferenceNode::setReferenceBehaviorTree(btTreeModel * treeModel)
{
    m_reference = treeModel;
}

btTreeModel * btReferenceNode::referenceBehaviorTree()
{
    return m_reference;
}

#include "btreferencenode.moc"
