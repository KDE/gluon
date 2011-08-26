#include "nodetypefactory.h"

#include "bteditornodetype.h"
#include "btactionnode.h"
#include "btcompositenode.h"
#include "btconditionnode.h"
#include "btdecoratornode.h"
#include "btunusablenode.h"
#include "btreferencenode.h"

nodeTypeFactory::nodeTypeFactory()
{
}


nodeTypeFactory* nodeTypeFactory::instance()
{
    static nodeTypeFactory * factoryInstance;
    if(factoryInstance == NULL)
    {
        factoryInstance = new nodeTypeFactory();
    }

    return factoryInstance;
}

btEditorNodeType * nodeTypeFactory::newObject(QString typeCategory)
{
    btEditorNodeType * newNode = 0;

    if(typeCategory == "action")
    {
        newNode = new btActionNode(this);
    }
    else if(typeCategory == "condition")
    {
        newNode = new btConditionNode();
    }
    else if(typeCategory == "composite")
    {
        newNode = new btCompositeNode();
    }
    else if(typeCategory == "decorator")
    {
        newNode = new btDecoratorNode();
    }
    else if(typeCategory == "reference")
    {
        newNode = new btDecoratorNode();
    }
    else
    {
        newNode = new btUnusableNode();
    }

    return newNode;
}

btEditorNodeType * nodeTypeFactory::newObject(btNodeType::nodeType type)
{
    btEditorNodeType * newNode = 0;
    switch(type)
    {
    case btNodeType::ActionNodeType:
        newNode = new btActionNode();
        break;
    case btNodeType::CompositeNodeType:
        newNode = new btCompositeNode();
        break;
    case btNodeType::ConditionNodeType:
        newNode = new btConditionNode();
        break;
    case btNodeType::DecoratorNodeType:
        newNode = new btDecoratorNode();
        break;
    case btNodeType::UnusableNodeType:
        newNode = new btUnusableNode();
        break;
    case btNodeType::ReferenceNodeType:
        newNode = new btReferenceNode();
        break;
    default:
        newNode = new btUnusableNode();
        break;
    }

    return newNode;
}


#include "nodetypefactory.moc"
