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

#include <QMimeData>
#include "bteditornodetype.h"
#include "btnodetypesmodelnode.h"
#include "btnodetypesmodel.h"
#include "btbrain.h"
#include <qmessagebox.h>
#include <QDebug>
#include <QIcon>

btNodeTypesModel::btNodeTypesModel(btBrain *brain, QObject* parent)
        :QAbstractItemModel(parent)
{
    m_brain = brain;
    rootNode = new btNodeTypesModelNode();
    rootNode->setName("Root node");

    nodeAction = new btNodeTypesModelNode();
    nodeAction->setName(tr("Action"));
    btEditorNodeType* nodeActionType = new btEditorNodeType();
    nodeActionType->setChildType(btNodeType::ActionNodeType);
    nodeAction->setNodeType(nodeActionType);
    rootNode->appendChild(nodeAction);

    nodeCondition = new btNodeTypesModelNode();
    nodeCondition->setName(tr("Condition"));
    btEditorNodeType* nodeConditionType = new btEditorNodeType();
    nodeConditionType->setChildType(btNodeType::ConditionNodeType);
    nodeCondition->setNodeType(nodeConditionType);
    rootNode->appendChild(nodeCondition);

    nodeComposite = new btNodeTypesModelNode();
    nodeComposite->setName(tr("Composite"));
    btEditorNodeType* nodeCompositeType = new btEditorNodeType();
    nodeCompositeType->setChildType(btNodeType::CompositeNodeType);
    nodeComposite->setNodeType(nodeCompositeType);
    rootNode->appendChild(nodeComposite);
    ///fixme delete these new btEditorNodeTypes
    nodeDecorator = new btNodeTypesModelNode();
    nodeDecorator->setName(tr("Decorator"));
    btEditorNodeType* nodeDecoratorType = new btEditorNodeType();
    nodeDecoratorType->setChildType(btNodeType::DecoratorNodeType);
    nodeDecorator->setNodeType(nodeDecoratorType);
    rootNode->appendChild(nodeDecorator);

    nodeReference = new btNodeTypesModelNode();
    nodeReference->setName(tr("Reference"));
    btEditorNodeType* nodeReferenceType = new btEditorNodeType();
    nodeReferenceType->setChildType(btNodeType::ReferenceNodeType);
    nodeReference->setNodeType(nodeReferenceType);
    rootNode->appendChild(nodeReference);
    btNodeTypesModelNode *node;
    foreach(btNodeType *nodeType, brain->nodeTypes)
    {
        switch(nodeType->type())
        {
            case btNodeType::ActionNodeType:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeAction);
                break;
            case btNodeType::ConditionNodeType:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeCondition);
                break;
            case btNodeType::CompositeNodeType:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeComposite);
                break;
            case btNodeType::DecoratorNodeType:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeDecorator);
                break;
            case btNodeType::ReferenceNodeType:
                node = new btNodeTypesModelNode(qobject_cast<btEditorNodeType*>(nodeType), nodeReference);
                break;
            default:
                break;
        }
        node->setName(nodeType->name());
    }
}

btNodeTypesModel::~btNodeTypesModel()
{
    delete(rootNode);
}

void btNodeTypesModel::newBehaviorTreeTypeAdded(btEditorNodeType* newType)
{
    btNodeTypesModelNode *node;
    QModelIndex parent;
    switch(newType->type())
    {
        case btNodeType::ActionNodeType:
            node = new btNodeTypesModelNode(newType, nodeAction);
            parent = createIndex(nodeAction->row(), 0, node);
            break;
        case btNodeType::ConditionNodeType:
            node = new btNodeTypesModelNode(newType, nodeCondition);
            parent = createIndex(nodeCondition->row(), 0, node);
            break;
        case btNodeType::CompositeNodeType:
            node = new btNodeTypesModelNode(newType, nodeComposite);
            parent = createIndex(nodeComposite->row(), 0, node);
            break;
        case btNodeType::DecoratorNodeType:
            node = new btNodeTypesModelNode(newType, nodeDecorator);
            parent = createIndex(nodeDecorator->row(), 0, node);
            break;
        case btNodeType::ReferenceNodeType:
            node = new btNodeTypesModelNode(newType, nodeReference);
            parent = createIndex(nodeReference->row(), 0, node);
            break;
        default:
            break;
    }
    node->setName(newType->name());
    emit dataChanged(parent, parent);
}

QVariant btNodeTypesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootNode->data(section);

    return QVariant();
}

QVariant btNodeTypesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    btNodeTypesModelNode *node = static_cast<btNodeTypesModelNode*>(index.internalPointer());
    if (role == Qt::DecorationRole){
        btNodeType::nodeType type;
        if(node->nodeType()->type() == btNodeType::UnusableNodeType){
            type = node->nodeType()->childType();
        }else{
            type = node->nodeType()->type();
        }
        switch(type){
            case btNodeType::ReferenceNodeType:
            return QIcon(":/images/reference.png");
            case btNodeType::CompositeNodeType:
                return QIcon(":/images/sequence.png");
            case btNodeType::DecoratorNodeType:
                return QIcon(":/images/decorator.png");
            case btNodeType::ActionNodeType:
                return QIcon(":/images/behavior.png");
            case btNodeType::ConditionNodeType:
                return QIcon(":/images/selector.png");
            default:
                break;
        }
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    return node->data(index.column());
}

Qt::ItemFlags btNodeTypesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
    Qt::ItemFlags thisIndexFlags;
    
    if (index.isValid())
    {
        btNodeTypesModelNode *node = static_cast<btNodeTypesModelNode*>(index.internalPointer());
        if(node->nodeType()->type() != btNodeType::UnusableNodeType)
            thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
        else
            thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    }
    else
        thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    
    return thisIndexFlags;
}

/*QModelIndex btNodeTypesModel::index(int row, int column, const QModelIndex &parent) const
{
    btNodeTypesModelNode *parentNode;
    
    if(!parent.isValid())
        parentNode = rootNode;
    else
        parentNode = static_cast<btNodeTypesModelNode*>(parent.internalPointer());

    btNodeTypesModelNode *childNode = parentNode->child(row);
    if(childNode)
        return createIndex(row, column, childNode);
    else
        return QModelIndex();
}*/

// new index taken from bttreemodel

btNodeTypesModelNode *btNodeTypesModel::nodeFromIndex(const QModelIndex &index) const
{
    if(index.isValid())
        return static_cast<btNodeTypesModelNode*>(index.internalPointer());
    else
        return rootNode;
}

QModelIndex btNodeTypesModel::index(int row, int column, const QModelIndex &parent) const
{
    // If we don't have a root node, we need to return an empty QModelIndex
    if(!rootNode)
        return QModelIndex();

    // We shouldn't allow for less-than-zero values for row and column...
    if(row < 0 ||column < 0)
        return QModelIndex();

    btNodeTypesModelNode *parentNode = nodeFromIndex(parent);

    // Don't allow for the creation of indexes for anything bigger than what exists
    if(row >= parentNode->childCount() || column >= parentNode->columnCount())
        return QModelIndex();
    //if(column == 0)
        return createIndex(row, column, parentNode->child(row));

    //return createIndex(row, column, 0);
}

// new index taken from bttreemodel

QModelIndex btNodeTypesModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    btNodeTypesModelNode *childNode = static_cast<btNodeTypesModelNode*>(child.internalPointer());
    btNodeTypesModelNode *parentNode = childNode->parent();

	if(!parentNode)
		return QModelIndex();
	
    if (parentNode == rootNode)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);
}

int btNodeTypesModel::rowCount(const QModelIndex &index) const
{
    btNodeTypesModelNode *node;

    if (!index.isValid())
        node = rootNode;
    else
        node = static_cast<btNodeTypesModelNode*>(index.internalPointer());

    return node->childCount();
}

int btNodeTypesModel::columnCount(const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<btNodeTypesModelNode*>(index.internalPointer())->columnCount();
    else
        return rootNode->columnCount();
}

btEditorNodeType *btNodeTypesModel::nodeTypeFromIndex(const QModelIndex &index) const
{
    /*if(index.isValid())
        return static_cast<btNodeType*>(nodeTypes.at(index.row()));
    else*/
        return 0;
}

Qt::DropActions btNodeTypesModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

QStringList btNodeTypesModel::mimeTypes() const
{
    QStringList types;
    types << "application/bt.nodetype";
    return types;
}

QMimeData* btNodeTypesModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    
    foreach(QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            btNodeTypesModelNode *node = static_cast<btNodeTypesModelNode*>(index.internalPointer());
            if(node->nodeType())
            {
                stream << node->name();
                stream << node->nodeType()->name();
            }
        }
    }
    mimeData->setData("application/bt.nodetype", encodedData);
    return mimeData;
}

bool btNodeTypesModel::insertRows(int row, int count, const QModelIndex &parent)
{
    btNodeTypesModelNode* selectedNode = static_cast<btNodeTypesModelNode*>(parent.internalPointer());

    if(selectedNode->parent() == 0){
        QString nodeTypeName = "";
        switch(selectedNode->nodeType()->childType()){
        case btNodeType::ActionNodeType:
            nodeTypeName = tr("New Action Node");
            break;
        case btNodeType::CompositeNodeType:
            nodeTypeName = tr("New Composite Node");
            break;
        case btNodeType::ConditionNodeType:
            nodeTypeName = tr("New Condition Node");
            break;
        case btNodeType::DecoratorNodeType:
            nodeTypeName = tr("New Decorator Node");
            break;
        case btNodeType::ReferenceNodeType:
            nodeTypeName = tr("New Reference Node");
            break;
        case btNodeType::UnusableNodeType:
            qDebug("UnusableNodeType");
            break;
        default:
            break;
        }

        beginInsertRows(parent, row, row);
        ///fixme check memory
        ///fixme change this HACK to something useful
        if(count == 1){ ///ugly hack never do this, change when up to it
            btEditorNodeType* insertedNode = new btEditorNodeType();
            insertedNode->setNodeType(selectedNode->nodeType()->childType());
            insertedNode->setName(nodeTypeName);

            m_brain->addNodeType(insertedNode);

            // this also inserts the node insertedNode as a child of selectedNode
            btNodeTypesModelNode* insertedModelNode = new btNodeTypesModelNode(insertedNode,selectedNode);

            insertedModelNode->setName(nodeTypeName);
        }

        endInsertRows();
        emit dataChanged(parent,parent);
        return true;
    }
    return false;
}

bool btNodeTypesModel::removeRows ( int row, int count, const QModelIndex &index)
{
    btNodeTypesModelNode* selectedNode = static_cast<btNodeTypesModelNode*>(index.internalPointer());
    btNodeTypesModelNode* parentNode = selectedNode->parent();

    beginRemoveRows(index, row, row+count-1);
    parentNode->deleteChild(row);

    endRemoveRows();
    emit dataChanged(index,index);
    return true;
}

#include "btnodetypesmodel.moc"
