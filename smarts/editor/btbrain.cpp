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

#include "btbrain.h"
#include "bttreemodel.h"
#include "btnodetypesmodel.h"
#include "bteditornodetype.h"
#include "bteditornode.h"
#include "btcompositenode.h"
#include "btconditionnode.h"
#include <QtCore/qtextstream.h>
#include "btreferencenode.h"
#include "btglobal.h"


btBrain::btBrain(QObject *parent)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    btCompositeNode *compositeNode = new btCompositeNode();
    compositeNode->setName("Sequence");
    compositeNode->setDescription("A sequence of behaviors, launched in order (fails if one fails)");
    compositeNode->setClassName("[sequence]");
    nodeTypes.append(compositeNode);

    compositeNode = new btCompositeNode();
    compositeNode->setName("Selector");
    compositeNode->setDescription("A collection of behaviors which are launched in order, until one succeeds (only fails if all fails)");
    compositeNode->setClassName("[selector]");
    nodeTypes.append(compositeNode);

    compositeNode = new btCompositeNode();
    compositeNode->setName("Probability Selector");
    compositeNode->setDescription("A collection of behaviors which are launched due to a probability, until one succeeds (only fails if all fails)");
    compositeNode->setClassName("[probselector]");
    compositeNode->setProperty("weights", QVariant("btChildWeights"));
    nodeTypes.append(compositeNode);

    compositeNode = new btCompositeNode();
    compositeNode->setName("Parallel");
    compositeNode->setDescription("A collection of behaviors which are launched in parallel, and fails or succeeds according a set of conditions");
    compositeNode->setClassName("[parallel]");
    compositeNode->setProperty("conditions", QVariant("btParallelConditions"));
    nodeTypes.append(compositeNode);
}

btBrain::~btBrain()
{
    qDeleteAll(nodeTypes);
    qDeleteAll(behaviorTrees);

    behaviorTrees.clear();
    nodeTypes.clear();
}

btEditorNodeType *btBrain::findNodeTypeByName(QString name)
{
    foreach(btNodeType *nodeType, nodeTypes)
    if (nodeType->name() == name)
        return qobject_cast<btEditorNodeType*>(nodeType);
    return 0;
}

btTreeModel *btBrain::newBehaviorTree(QString treeName)
{
    // First create the new BT
    btTreeModel *newTree = new btTreeModel(this, this);
    this->behaviorTrees.append(newTree);
    newTree->setName(treeName);
    // We set the root node to be a sequence, as this is the fastest to choose that it should simply run the first child node (no selection, just runs children in sequence)
    btEditorNode *btRootNode = new btEditorNode(this->findNodeTypeByName("Sequence"));
    newTree->setRootNode(btRootNode);
    btRootNode->setParent(newTree);

    // Add a real top level node, which should be a selector as per Alex' defintion of behavior trees
    btEditorNode *topNode = new btEditorNode(this->findNodeTypeByName("Selector"), btRootNode);
    topNode->setName(tr("Top Behavior"));
    topNode->setDescription(topNode->type()->description());

    // Then add it to the list of referenced NodeTypes...
    btReferenceNode *newType = new btReferenceNode();
    newType->setName(newTree->name());
    newType->setDescription(tr("A reference to the behavior tree named %1").arg(newTree->name()));
    newType->setNodeType(btNodeType::ReferenceNodeType);
    newType->setReferenceBehaviorTree(newTree);
    newType->setClassName("[reference]");

    // add the new type to the brain
    addNodeType(newType);

    // Finally inform those around us of this wonderful occurrence
    emit behaviorTreeAdded(newTree);
    emit nodeTypeAdded(newType);

    return newTree;
}

btTreeModel *btBrain::newBehaviorTree() {
    return newBehaviorTree(tr("New Tree"));
}

void btBrain::deleteBehaviorTree(btTreeModel *behaviorTree)
{
    behaviorTrees.removeAll(behaviorTree);
    delete behaviorTree;
}

void btBrain::setName(QString name) {
    m_name = name;
}
QString btBrain::name() const {
    return m_name;
}

void btBrain::addBehaviorTree(btTreeModel* newTree)
{
    behaviorTrees.append(newTree);
    emit behaviorTreeAdded(newTree);
}

void btBrain::addNodeType(btEditorNodeType* newNodeType)
{
    nodeTypes.append(newNodeType);
    ///fixme: with this double entries are added
    //emit nodeTypeAdded(newNodeType);
}

void btBrain::removeNodeType(btEditorNodeType* nodeType, int row)
{
    nodeTypes.removeAll(nodeType);
    emit nodeTypeDeleted(row);
}

#include "btbrain.moc"
