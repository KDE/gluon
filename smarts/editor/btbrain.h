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

#ifndef GLUON_SMARTS_BTBRAIN_H
#define GLUON_SMARTS_BTBRAIN_H

#include <QtCore/QObject>

class btEditorNodeType;
class btTreeModel;

class btBrain : public QObject
{
        Q_OBJECT;
        Q_PROPERTY( QString name READ name WRITE setName );

    public:
        btBrain( QObject* parent = 0 );
        ~btBrain();

        btTreeModel* newBehaviorTree();
        btTreeModel* newBehaviorTree( QString treeName );
        void deleteBehaviorTree( btTreeModel* behaviorTree );
        btEditorNodeType* findNodeTypeByName( QString name );

        QList<btEditorNodeType*> nodeTypes;
        QList<btTreeModel*> behaviorTrees;

        void setName( QString name );
        QString name() const;

        void addBehaviorTree( btTreeModel* newTree );
        void addNodeType( btEditorNodeType* newNodeType );
        void removeNodeType( btEditorNodeType* nodeType , int row );
    Q_SIGNALS:
        void behaviorTreeAdded( btTreeModel* newTree );
        void nodeTypeAdded( btEditorNodeType* newNodeType );
        void nodeTypeDeleted( int row );

    private:
        QString m_name;
};

#endif // GLUON_SMARTS_BTBRAIN_H
