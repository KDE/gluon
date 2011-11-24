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

#ifndef GLUON_SMARTS_BTPROBSELECTORNODE_H
#define GLUON_SMARTS_BTPROBSELECTORNODE_H

#include <QObject>

#include "btlib.h"


class BT_LIB_EXPORT btProbSelectorNode : public btNode
{
        Q_OBJECT

    public:
        Q_INVOKABLE btProbSelectorNode( QObject* parent = 0 );
        ~btProbSelectorNode();

        btNode::status run( btCharacter* self );
        void appendingChild( int index );
        void removingChild( int index );
        void childrenAdded();
        void resetProbNodes();
        void setVisitedProbNodes( QList<ProbNode*> probNodes );
        QList<ProbNode*> visitedProbNodes();

    private:
        QList<ProbNode*> m_probStats;
        QList<ProbNode*> m_visitedProbStats;
};

#endif // GLUON_SMARTS_BTPROBSELECTORNODE_H
