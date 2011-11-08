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

#ifndef BTNODE_H
#define BTNODE_H

#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QList>

class btCharacter;

class BT_LIB_EXPORT btNode : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(nodeType type READ type WRITE setType)
    Q_PROPERTY(QString className READ className WRITE setClassName )
    Q_ENUMS(nodeType)
	Q_ENUMS(status)
public:
	enum nodeType
    {
        UnusableNodeType = 0,
        ActionNodeType,
        CompositeNodeType,
        ConditionNodeType,
        ReferenceNodeType,
        DecoratorNodeType
    };
	
	enum status
	{
		Failed = 0,
		Succeeded,
		Running,
		RunningChild,
		None
	};
	
	Q_INVOKABLE btNode(QObject* parent = 0);
	~btNode();
	
	void setName(QString name);
	QString name();
	void setDescription(QString description);
	QString description();
	void setClassName(QString classname);
	QString className();
	void setType(nodeType type);
	nodeType type();
	
	Q_INVOKABLE int childCount();
	void appendChild(btNode* child);
	void insertChild(int index, btNode* child);
	void removeChild(int index);
	void removeChild(btNode* child);
    int childIndex(btNode * child);
	Q_INVOKABLE btNode* child(int index);
	Q_INVOKABLE btNode* currentChild();
	Q_INVOKABLE int currentChildIndex();
	Q_INVOKABLE void setCurrentChildIndex(int index);
	Q_INVOKABLE int nextChildIndex();
	void doneParsingChildren();
	
	Q_INVOKABLE status runChild(int index);
	Q_INVOKABLE status runChild();
	
	Q_INVOKABLE void setCurrentChildStatus(status nodeStatus);
	Q_INVOKABLE status currentChildStatus();
	
	void setParentNode(btNode* parent);
	Q_INVOKABLE btNode* parentNode();
	
	virtual status run(btCharacter * self);
	virtual void childrenAdded(){};
	virtual void appendingChild(int index){};
	virtual void removingChild(int index){};
	
private:
	QString m_name;
	QString m_description;
	QString m_className;
	nodeType m_type;
	btNode* m_parent;
	int m_currentChildIndex;
	status m_currentChildStatus;
	QList<btNode*> m_children;
};

#endif
