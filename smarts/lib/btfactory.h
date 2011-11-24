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

#ifndef GLUON_SMARTS_BTFACTORY_H
#define GLUON_SMARTS_BTFACTORY_H

#include "btlib_export.h"

#include <QtCore/QHash>
#include <QtXml/QDomNode>

class btNode;
class btBrain;

class GLUON_SMARTS_EXPORT btFactory : public QObject
{
        Q_OBJECT

    public:
        static btFactory* instance();

        btNode* newObject( QString className );
        btNode* newObject( QDomNode xmlNode, btNode* parentNode, btBrain* brain );

        btNode* createRootNode( QDomNode xmlNode, btBrain* brain );

        void addProperty( btNode* node, QDomNode xNode, btBrain* brain );
        void initNodeType( QDomNode xmlNode );

        btNode* getRegisteredNodeType( QString className );

        void registerNodeType( btNode* newType );
        void registerNodeType( btNode* newType, QString className );

    private:
        btFactory();

        QHash<QString, btNode*> m_nodeTypes;
};

template<class T>
class GLUON_SMARTS_EXPORT Registration
{

    public:
        Registration( T* newNode )
        {
            btFactory::instance()->registerNodeType( newNode );
        }
};

#define REGISTER_NODETYPE(NEWNODE) \
    Registration<NEWNODE> NEWNODE ## _registration_(new NEWNODE());

#endif // GLUON_SMARTS_BTFACTORY_H
