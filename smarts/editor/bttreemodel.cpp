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

#include "bttreemodel.h"

#include "bteditornode.h"
#include "bteditornodetype.h"
#include "btbrain.h"
#include "btdecoratornode.h"
#include "btreferencenode.h"
#include "btglobal.h"

#include <QtGui/QIcon>
#include <QtGui/QMessageBox>
#include <QtGui/QTreeView>
#include <QtCore/QMimeData>
#include <QtCore/QDebug>

btTreeModel::btTreeModel(QObject* parent, btBrain* containingBrain)
        : QAbstractItemModel(parent)
{
    m_rootNode = new btEditorNode();
    brain = containingBrain;
    moving = false;
    this->setSupportedDragActions(Qt::MoveAction);
}

btTreeModel::~btTreeModel()
{
    delete(m_rootNode);
}

void btTreeModel::setRootNode(btEditorNode *newRoot)
{
    delete(m_rootNode);
    m_rootNode = newRoot;
    reset();
}

btEditorNode * btTreeModel::rootNode() const
{
    return m_rootNode;
}

QModelIndex btTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // If we don't have a root node, we need to return an empty QModelIndex
    if (!m_rootNode)
        return QModelIndex();

    // We shouldn't allow for less-than-zero values for row and column...
    if (row < 0 ||column < 0)
        return QModelIndex();

    btEditorNode *parentNode = nodeFromIndex(parent);

    // Don't allow for the creation of indexes for anything bigger than what exists
    if (row >= parentNode->childCount() || column >= parentNode->columnCount())
    {
        return QModelIndex();
    }
    //if(column == 0)
    return createIndex(row, column, parentNode->child(row));

    //return createIndex(row, column, 0);
}

btEditorNode *btTreeModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<btEditorNode*>(index.internalPointer());
    else
        return m_rootNode;
}

int btTreeModel::rowCount(const QModelIndex &parent) const
{
    btEditorNode *parentNode = nodeFromIndex(parent);
    if (!parentNode)
        return 0;
    return parentNode->childCount();
}

int btTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QModelIndex btTreeModel::parent(const QModelIndex &child) const
{
    btEditorNode *node = nodeFromIndex(child);
    if (!node)
        return QModelIndex();

    btEditorNode *parentNode = qobject_cast<btEditorNode*>(node->parent());
    if (!parentNode)
        return QModelIndex();

    if (parentNode == m_rootNode)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);
}

QVariant btTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    btEditorNode *node = nodeFromIndex(index);
    if (!node)
        return QVariant();

    // icon stuff
    if (role == Qt::DecorationRole) {
        if (index.column() == 0) {
            btEditorNodeType::nodeType type;
            type = node->type()->type();
            switch (type) {
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
    }
    //icon stuff

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 2) {
            return node->type()->name();
        }
        return node->data(index.column());
    }
    else if (role == Qt::ToolTipRole)
    {
        QString tip;
        tip = "<html>";
        tip += tr("Decorators: %1").arg(node->decoratorCount());
        tip += "<table>";

        for (int i = 0; i < node->decoratorCount(); i++)
        {
            tip += "<tr><td>" + node->decorators().at(i)->name() + "</td><td>" + node->decorators().at(i)->description() + "</td></tr>";
        }

        tip += "</table>";
        tip += "</html>";
        return tip;
    }
    else
        return QVariant();
}

bool btTreeModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
    Q_UNUSED(value)
    Q_UNUSED(role)
    if (index == QModelIndex())
        return false;

    emit dataChanged(index, index);
    return true;
}

QVariant btTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if (role == Qt::DisplayRole)
        return m_rootNode->headerData(section);

    return QVariant();
}

Qt::ItemFlags btTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
    Qt::ItemFlags thisIndexFlags;

    if (index.isValid())
        thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    //else
    //thisIndexFlags = Qt::ItemIsEnabled | Qt::ItemIsDropEnabled | defaultFlags;

    return thisIndexFlags;
}

QStringList btTreeModel::mimeTypes() const
{
    QStringList types;
    types << "application/bt.nodetype";
    return types;
}

bool btTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("application/bt.nodetype"))
        return false;

    if (column > 0)
        return false;

    // We only do the parent thing here - we accept no drops in empty space at all
    if (!parent.isValid())
        return false;

    btEditorNode* parentNode = static_cast<btEditorNode*>(parent.internalPointer());

    // We do not allow dropping on Actions and References
    if (/* parentNode->type()->type() == btNodeType::ActionNodeType    ||
        parentNode->type()->type() == btNodeType::ReferenceNodeType ||*/
        parentNode->type()->type() == btNodeType::ConditionNodeType )
    {
        emit dataChanged(parent, parent);
        return false;
    }

    if (action == Qt::MoveAction)
    {
        moving = true;

        QByteArray encodedData = data->data("application/bt.nodetype");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        btEditorNode * node = NULL;
        btEditorNode* oldParentNode = NULL;

        while (!stream.atEnd())
        {
            quint64 nodeMemAdress;
            stream >> nodeMemAdress;
            node =  reinterpret_cast<btEditorNode*>(nodeMemAdress);
            stream >> nodeMemAdress;
            oldParentNode = reinterpret_cast<btEditorNode*>(nodeMemAdress);
        }

        if (node)
        {
            if (row == -1 && column  == -1)
            {
                if (oldParentNode->type()->className() == "[parallel]")
                {
                    btParallelConditions list = oldParentNode->type()->property("conditions").value<btParallelConditions>();
                    list.parallelConditions.removeAt(oldParentNode->children().indexOf(node));

                    QVariant v;
                    v.setValue(list);
                    parentNode->type()->setProperty("conditions", v);
                }
                oldParentNode->removeChild(node);
                parentNode->appendChild(node);
            }
            else
            {
                if (oldParentNode != parentNode)
                {
                    oldParentNode->removeChild(node);
                    foreach(const QString &name, parentNode->type()->dynamicPropertyNames())
                    {
                        if (parentNode->type()->property(name.toUtf8()).type() == QVariant::UserType && name == "weights")
                        {
                            node->type()->setProperty("probability", 0.5);
                        }
                        else if (parentNode->type()->property(name.toUtf8()).type() == QVariant::UserType && name == "conditions")
                        {
                            btParallelConditions list = parentNode->type()->property(name.toUtf8()).value<btParallelConditions>();
                            list.parallelConditions.append(1.0);

                            QVariant v;
                            v.setValue(list);
                            parentNode->type()->setProperty(name.toUtf8(), v);
                        }
                    }
                }
                else
                {
                    foreach(const QString &name, parentNode->type()->dynamicPropertyNames())
                    {
                        if (parentNode->type()->property(name.toUtf8()).type() == QVariant::UserType && name == "weights")
                        {
                            if (parentNode->children().indexOf(node) > -1)
                            {
                                btChildWeights list = parentNode->type()->property(name.toUtf8()).value<btChildWeights>();
                                node->type()->setProperty("probability", list.childWeightList[parentNode->children().indexOf(node)].toDouble());
                            }
                            break;
                        }
                    }
                    parentNode->removeChild(node);

                }

                parentNode->insertChild(row, node);
            }

            this->reset();
            emit dataChanged(parent, parent);

            return true;
        }
        else
        {
            return false;
        }

    }

    QByteArray encodedData = data->data("application/bt.nodetype");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QHash<QString,QString> nodeTypes;

    while (!stream.atEnd())
    {
        QString nodeType;
        QString btType;
        stream >> nodeType;
        stream >> btType;
        nodeTypes.insert(nodeType, btType);
    }


    int rows = 0;
    QList<btNodeType*> theNodeTypes;
    QHashIterator<QString, QString> i(nodeTypes);
    while (i.hasNext())
    {
        i.next();
        btEditorNodeType* brainNodeType = qobject_cast<btEditorNodeType*>(brain->findNodeTypeByName(i.value()));
        btNodeType *theNodeType = brainNodeType->copy();

        ((btEditorNodeType*)theNodeType)->initProperties();
        ((btEditorNodeType*)theNodeType)->connectChangeProperty(brainNodeType);

        theNodeType->setName(i.key());
        theNodeType->setParent(this);
        theNodeTypes.append(theNodeType);
        if (theNodeType->type() != btNodeType::DecoratorNodeType)
            ++rows;
    }

    // Yes, this is kinda nasty - but we may well be dropping decorators, which are not true children
    if (rows > 0)
        beginInsertRows(parent, parentNode->childCount(), parentNode->childCount() + rows - 1);

    foreach(btNodeType* theNodeType, theNodeTypes)
    {
        // Figure out whether the dropped item is a special case (decorators are added to the parent item directly, rather than added as children)
        if (theNodeType->type() == btNodeType::DecoratorNodeType)
        {
            parentNode->addDecorator(qobject_cast<btDecoratorNode*>(theNodeType));
        }
        else
        {
            if (theNodeType->type() == btNodeType::ReferenceNodeType)
            {
                btReferenceNode * referenceNodeType = qobject_cast<btReferenceNode*>(brain->findNodeTypeByName(theNodeType->name()));
                btReferenceNode * newRefNode = qobject_cast<btReferenceNode*>(theNodeType);
                newRefNode->setReferenceBehaviorTree(referenceNodeType->referenceBehaviorTree());
            }

            btEditorNode *newChild = new btEditorNode(theNodeType, parentNode);
            newChild->setName(tr("New %1").arg(theNodeType->name()));
            newChild->setDescription(theNodeType->description());

            foreach(const QString &name, parentNode->type()->dynamicPropertyNames())
            {
                if (parentNode->type()->property(name.toUtf8()).type() == QVariant::UserType)
                {
                    if (name == "weights")
                    {
                        btChildWeights cw = parentNode->type()->property(name.toUtf8()).value<btChildWeights>();
                        cw.childWeightList.append(0.5);
                        QVariant v;
                        v.setValue(cw);
                        parentNode->type()->setProperty(name.toUtf8(), v);
                        emit addRemoveBTNode();
                        break;
                    }
                    else if (name == "conditions")
                    {
                        btParallelConditions pc = parentNode->type()->property(name.toUtf8()).value<btParallelConditions>();
                        pc.parallelConditions.append(1.0);
                        QVariant v;
                        v.setValue(pc);
                        parentNode->type()->setProperty(name.toUtf8(), v);
                        emit addRemoveBTNode();
                        break;
                    }
                }
            }
        }
    }

    if (rows > 0)
        endInsertRows();
    else
    {
        emit dataChanged(parent, parent);//Update the view for the parent node we have (likely) just added a decorator to
        emit addRemoveBTNode(); //used for updateing the property widget
    }

    return true;
}

bool btTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    btEditorNode* parentNode = static_cast<btEditorNode*>(parent.internalPointer());

    if (parentNode == NULL)
        return false;

    if (!moving)
    {
        beginRemoveRows(parent, position, position+rows-1);
        parentNode->removeChild(position);
        endRemoveRows();
        return true;
    }
    else
    {
        moving = false;
        return false;
    }
}

void btTreeModel::setName(QString name) {
    m_name = name;
}
QString btTreeModel::name() const {
    return m_name;
}

void btTreeModel::setDescription(QString description)
{
    m_description = description;
}

QString btTreeModel::description() const
{
    return m_description;
}

void btTreeModel::updateTreeModel()
{
    emit dataChanged(QModelIndex(),QModelIndex());
}

Qt::DropActions btTreeModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

QMimeData* btTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach(const QModelIndex& index, indexes)
    {
        if (index.isValid())
        {
            btEditorNode * node = nodeFromIndex(index);
            if (node)
            {
                quint64 nodeMemAdress = reinterpret_cast<quint64>(node);
                stream <<  nodeMemAdress;

                nodeMemAdress = reinterpret_cast<quint64>(node->parent());
                stream << nodeMemAdress;
            }
        }
    }
    mimeData->setData("application/bt.nodetype", encodedData);
    return mimeData;
}

#include "bttreemodel.moc"
