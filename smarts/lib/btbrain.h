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

#include "gluon_smarts_export.h"

#include "btperceptioninfo.h"

#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtXml/QDomNode>

class btNode;
Q_DECLARE_METATYPE( QList<btPerceptionInfo*> );

class GLUON_SMARTS_EXPORT btBrain : public QObject
{
        Q_OBJECT

        Q_PROPERTY( QString name READ name WRITE setName )
        Q_PROPERTY( QString description READ description WRITE setDescription )
        Q_PROPERTY( QList<btPerceptionInfo*> perceptionInfos READ perceptionInfos WRITE setPerceptionInfos )

    public:
        btBrain( QString data, QString file, QObject* parent = 0 );
        ~btBrain();

        btNode* getBehaviorTree( int index );
        int behaviorTreesCount();

        QString name();
        void setName( QString name );
        QString description();
        void setDescription( QString description );
        /**
         * The perception information currently available in the game
         */
        QList<btPerceptionInfo*> perceptionInfos() const;
        void setPerceptionInfos( const QList<btPerceptionInfo*>& newPerceptionInfos );
        btPerceptionInfo* perceptionInfo( const QString& name ) const;
        void addPerceptionInfo( btPerceptionInfo* newPercpetionInfo );
        QString getFile();

    private:
        QHash<int, btNode*> m_behaviorTrees;
        QList<btPerceptionInfo*> m_perceptionInfos;

        QString m_name;
        QString m_description;

        void parseNodeTypes( QDomNode xNode );
        void parseBehaviorTrees( QDomNode xNode, btNode* node ); //, int nodeIndex);

        QString m_file;
};

#endif // GLUON_SMARTS_BTBRAIN_H
