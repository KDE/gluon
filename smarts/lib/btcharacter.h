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

#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QMultiHash>
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <QQuaternion>

#include "btlib.h"
#include "btlib_export.h"

#include "btperception.h"

struct ProbNode;
class btPerception;
class QXmlStreamWriter;

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition)
    Q_PROPERTY(QQuaternion orientation READ orientation WRITE setOrientation)
    
    public:
        btCharacter(QObject* parent = 0);
        ~btCharacter();
        
        void setBehaviorTree(btNode* behaviorTree);
        
        void think();

        /**
        * The character's position in the world
        */
		
        virtual QVector3D position() const;
        virtual void setPosition(const QVector3D& newPosition);
        
        /**
         * The character's orientation in the world.
         */
        virtual QQuaternion orientation() const;
        virtual void setOrientation(const QQuaternion& newOrientation);
    
        /**
         * Accessor for the character's perception system
         */
        virtual btPerception* perception();
    private:
		struct probability
		{
			double prob;
			int runs;
			int succeeds;
			
			probability()
			{
				runs = 0;
				succeeds = 0;
				prob = 0.0;
			}
		};
		void saveProbabilities();
		void saveNodeProbabilities(btNode * node, QXmlStreamWriter * xmlWriter);
		void initProbabilityHash(btNode * node); 
		QString m_filename;
		QHash<btNode*, probability> m_nodesProbabilities;
		void setFile(QString file);
		int m_thinksBeforeSaving;
		int m_thinksDone;
	
        void stopParallelExecution(btNode * currentNode, QStack<btNode*>* parentStack);
        void findParallelsForTermination(btNode * currentNode, QStack<btNode*>* parentStack, QStack<QPair<QStack<btNode*>*, QStack<btNode*>*> > * stack);
        void clearExecution();
        
        btNode* m_behaviortree;
        
        //used for scheduler exectution
        QQueue<btNode::status> m_nodesStatusQueue;
        QQueue<QPair<QStack<btNode*>*, QStack<btNode*>*> > m_currentNodeStackQueue;
        QQueue<QStack<int> > m_currentChildStackQueue;
        
        //used for probselectors
        QHash<QStack<btNode*>*, QStack<QList<ProbNode*> > > m_visitedProbChildrenHash;
        
        //used for parallels
        QMultiHash<QStack<btNode*>*, QList<btNode::status>* > m_parallelNodeStatusHash;
        
        QVector3D m_position;
        QQuaternion m_orientation;
        btPerception* m_perception;
};

#endif // _BTCHARACTER_H_
