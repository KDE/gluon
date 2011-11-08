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

#ifndef BTPARALLELNODE_H
#define BTPARALLELNODE_H

#include "btlib.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QQueue>
#include <QtCore/QHash>

class btParallelNode : public btNode
{
    Q_OBJECT
	
public:
    Q_INVOKABLE btParallelNode(QObject* parent = 0);
	~btParallelNode();
	
	btNode::status run(btCharacter *self);
	
	void appendingChild(int index);
	void removingChild(int index);
	void childrenAdded();
	
	btNode::status conditionsFulfilled();
	
	void resetRunningNodesStatus();
	void setRunningNodesStatus(QList<btNode::status>* nodeStatus);
	
	int childNodeIndex(btNode* childNode);
private:
	QList<btNode::status>* m_runningNodesStatus;
	QList<btNode::status>* m_conditionStatus;
	QHash<btNode*, int> m_nodesIndex;
};


#endif // BTPARALLELNODE_H
