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

#ifndef GLUON_SMARTS_BTNODE_H
#define GLUON_SMARTS_BTNODE_H

#include "../lib/btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QList>

class QString;
class QVariant;
class btNodeType;
class btCharacter;

class GLUON_SMARTS_EXPORT btNode : public QObject
{
        Q_OBJECT;
        Q_PROPERTY( QString name READ name WRITE setName );
        Q_PROPERTY( QString description READ description WRITE setDescription );

    public:
        explicit btNode( btNodeType* type = 0, btNode* parent = 0 );
        ~btNode();

        bool runBehavior( btCharacter* self );

        virtual void appendChild( btNode* child );
        virtual void insertChild( int pos, btNode* child );
        virtual void removeChild( int row );
        virtual void removeChild( btNode* child );
        virtual void doneParsingChildren();

        virtual btNode* child( int row );
        virtual QList<btNode*> children();
        virtual int childCount() const;
        virtual btNode* parentNode();
        virtual void setParentNode( btNode* node );


        virtual int columnCount() const;
        virtual int row() const;

        virtual void setName( QString name );
        virtual QString name() const;
        virtual void setDescription( QString description );
        virtual QString description() const;
        virtual void setType( btNodeType* newType );
        virtual btNodeType* type() const;

        /*    virtual void addDecorator(btNodeType* decorator);
            virtual void removeDecorator(btNodeType* decorator);
            virtual void
            virtual int decoratorCount() const;
            QList<btNodeType*> decorators() const;*/

    private:
        btNodeType* m_type;

        btNode* m_parent;
        QList<btNode*> m_children;

        QString m_name;
        QString m_description;
        QList<QVariant> nodeData;
        //QList<btNodeType*> m_decorators;

        bool run( btCharacter* self );
};

#endif // GLUON_SMARTS_BTNODE_H
