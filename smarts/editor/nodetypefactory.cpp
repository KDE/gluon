/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
