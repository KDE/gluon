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

#ifndef GLUON_SMARTS_BTNODETYPESMODELNODE_H
#define GLUON_SMARTS_BTNODETYPESMODELNODE_H

#include <QVariant>
#include <QList>
#include <QString>
class btEditorNodeType;

class btNodeTypesModelNode
{
    public:
        explicit btNodeTypesModelNode( btEditorNodeType* data = 0, btNodeTypesModelNode* parent = 0 );
        ~btNodeTypesModelNode();

        void appendChild( btNodeTypesModelNode* child );
        btNodeTypesModelNode* child( int row );
        int childCount() const;
        int columnCount() const;
        QVariant data( int column ) const;
        int row() const;
        btNodeTypesModelNode* parent();

        btEditorNodeType* nodeType() const;
        void setNodeType( btEditorNodeType* nodeType );

        void setName( QString name );
        QString name() const;

        void deleteChild( int row );

    private:
        QString m_name;
        btEditorNodeType* nodeData;
        QList<btNodeTypesModelNode*> children;
        btNodeTypesModelNode* parentNode;
};

#endif // GLUON_SMARTS_BTNODETYPESMODELNODE_H
