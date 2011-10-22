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

#include "btnodetypesmodelnode.h"
#include "bteditornodetype.h"
#include <QDebug>

btNodeTypesModelNode::btNodeTypesModelNode(btEditorNodeType *data, btNodeTypesModelNode *parent)
{
    this->nodeData = data;
    this->parentNode = parent;
    if (parentNode)
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
    if (parentNode)
        return parentNode->children.indexOf(const_cast<btNodeTypesModelNode*>(this));
    return 0;
}

int btNodeTypesModelNode::columnCount() const
{
    return 1;
}

QVariant btNodeTypesModelNode::data(int column) const
{
    switch (column)
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

btEditorNodeType *btNodeTypesModelNode::nodeType() const {
    return nodeData;
}
void btNodeTypesModelNode::setNodeType(btEditorNodeType *nodeType) {
    nodeData = nodeType;
}

void btNodeTypesModelNode::setName(QString name) {
    m_name = name;
}
QString btNodeTypesModelNode::name() const {
    return m_name;
}
