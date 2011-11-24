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

#ifndef GLUON_SMARTS_BTNODETYPE_H
#define GLUON_SMARTS_BTNODETYPE_H

#include "../lib/gluon_smarts_export.h"

#include <QtCore/QMetaProperty>

#include "btnode.h"
#include "btcharacter.h"

class GLUON_SMARTS_EXPORT btNodeType : public QObject
{
        Q_OBJECT
        Q_PROPERTY( QString name READ name WRITE setName )
        Q_PROPERTY( QString description READ description WRITE setDescription )
        Q_PROPERTY( nodeType type READ type WRITE setNodeType )
        Q_PROPERTY( QString className READ className WRITE setClassName )
        Q_ENUMS( nodeType )

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

        Q_INVOKABLE btNodeType( QObject* parent = 0 );
        ~btNodeType();

        virtual void appendingChild( int index )
        {
            Q_UNUSED( index )
        };
        virtual void removingChild( int index )
        {
            Q_UNUSED( index )
        };
        virtual void childrenAdded() {};

        virtual void setName( QString name );
        virtual QString name() const;
        virtual void setDescription( QString description );
        virtual QString description() const;
        virtual nodeType type() const;

        virtual void setNodeType( nodeType type );
        virtual bool run( btCharacter* self );
        virtual btNodeType* copy();
        virtual QString className() const;
        virtual void setClassName( QString className );

        void setPropertyDescription( QString propertyName, QString description );
        void setPropertyDescription( QString newPropertyName, QString oldPropertyName, QString description );
        void removePropertyDescription( QString propertyName );
        QString getPropertyDescription( QString propertyName );
        QHash<QString, QString> getPropertyDescriptions();

        void setParentNode( btNode* node );
        /**
         * ParentNode() returns the node which contains the list of childnodes relevant to you.
         * @return the parent node
         */
        btNode* parentNode();

    private:

        QString m_name;
        QString m_description;
        QString m_className;
        btNode* m_parent;
        nodeType m_type;
        QHash<QString, QString> m_propertiesDescriptions;
};

#endif // GLUON_SMARTS_BTNODETYPE_H
