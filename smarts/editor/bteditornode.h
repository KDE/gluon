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

#ifndef _BTEDITORNODE_H_
#define _BTEDITORNODE_H_

#include <QObject>

#include "../common/btnode.h"

class btTreeModel;
class QXmlStreamWriter;

class btEditorNode : public btNode 
{
    Q_OBJECT
    
public:    
    
    btEditorNode(btNodeType *type = 0, btNode *parent = 0);
    ~btEditorNode();
    
    void toXml(QXmlStreamWriter* xmlWriter, QList<btTreeModel *> behaviorTrees);
    
    QVariant data(int column) const;
    QVariant headerData(int column) const;
    
    void addDecorator(btNodeType* decorator);
    void removeDecorator(btNodeType* decorator);
    void moveDecorator(int move, btNodeType * decorator);
    int decoratorCount() const;
    QList<btNodeType*> decorators() const;
    
    void emitUpdatePropertyWidget();
    
Q_SIGNALS:
    void updatePropertyWidget(btEditorNode* node);
    
private:    
    QList<btNodeType*> m_decorators;
};

#endif
