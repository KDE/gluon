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

#ifndef GLUON_SMARTS_BTEDITORNODETYPE_H
#define GLUON_SMARTS_BTEDITORNODETYPE_H

#include "../common/btnodetype.h"

class QXmlStreamWriter;

class btEditorNodeType : public btNodeType
{
        Q_OBJECT
        Q_PROPERTY( btNodeType::nodeType childType READ childType WRITE setChildType )
    public:


        btEditorNodeType( QObject* parent = 0 );

        void appendingChild( int index );
        void removingChild( int index );

        btEditorNodeType* copy();
        btNodeType::nodeType childType() const;
        void setChildType( btNodeType::nodeType );

        void toNodeTypeXml( QXmlStreamWriter* xmlWriter );
        virtual void toDataXml( QXmlStreamWriter* xmlWriter );

        void initProperties();

        void disconnectChangeProperty();
        void connectChangeProperty( btEditorNodeType* sender );

        void emitPropertyChangedSignal( QString propertyName, QVariant value );
        void emitPropertyDescriptionChangedSignal( QString propertyName, QString oldPropertyName , QString description );
        void emitNameChanged( QString name );
        void emitClassNameChanged( QString className );
        void emitDescriptionChanged( QString description );

    Q_SIGNALS:
        void propertyChanged( QString propertyName, QVariant value );
        void propertyDescriptionChanged( QString propertyName, QString oldPropertyName , QString description );
        void nameChanged( QString name );
        void descriptionChanged( QString description );
        void classNameChanged( QString className );

    public Q_SLOTS:
        void changeProbability( double value );
        void changeProperty( QString propertyName, QVariant value );
        void changePropertyDescription( QString propertyName, QString oldPropertyName , QString description );
        void changeName( QString name );
        void changeDescription( QString description );
        void changeClassName( QString className );
        void changeCondition( bool state );

        //used for moving decoratos up and down
        void removeActionTriggered();
        void moveUpAction();
        void moveDownAction();

    private:
        btNodeType::nodeType m_type;
        btNodeType::nodeType m_childtype;
        btEditorNodeType* m_sender;
};

#endif // GLUON_SMARTS_BTEDITORNODETYPE_H
