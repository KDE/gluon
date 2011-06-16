#include "btnodetypesmodelnode.h"
#include "bteditornodetype.h"
#include <QDebug>

btNodeTypesModelNode::btNodeTypesModelNode(btEditorNodeType *data, btNodeTypesModelNode *parent)
{
    this->nodeData = data;
    this->parentNode = parent;
    if(parentNode)
        parentNode->appendChild(this);
}

btNodeTypesModelNode::~btNodeTypesModelNode()
{
    qDeleteAll(children);
}

void btNodeTypesModelNode::appendChild(btNodeTypesModelNode *child)
{
    children.append(child);
}

btNodeTypesModelNode *btNodeTypesModelNode::child(int row)
{
    return children.value(row);
}

int btNodeTypesModelNode::childCount() const
{
    return children.count();
}

int btNodeTypesModelNode::row() const
{
    if(parentNode)
        return parentNode->children.indexOf(const_cast<btNodeTypesModelNode*>(this));
    return 0;
}

int btNodeTypesModelNode::columnCount() const
{
    return 1;
}

QVariant btNodeTypesModelNode::data(int column) const
{
    switch(column)
    {
        case 0:
            return m_name;
            break;
        case 1:
            return nodeData->type();
            break;
        default:
            return m_name;
            break;
    }
    
}

btNodeTypesModelNode *btNodeTypesModelNode::parent()
{
    return parentNode;
}

void btNodeTypesModelNode::deleteChild(int row)
{
    children.removeAt(row);
    qDebug("btNodeTypesModelNode::deleteChild");
}

btEditorNodeType *btNodeTypesModelNode::nodeType() const { return nodeData; }
void btNodeTypesModelNode::setNodeType(btEditorNodeType *nodeType) { nodeData = nodeType; }

void btNodeTypesModelNode::setName(QString name) { m_name = name; }
QString btNodeTypesModelNode::name() const { return m_name; }
