/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_CREATOR_PROPERTYWIDGETITEM_H
#define GLUON_CREATOR_PROPERTYWIDGETITEM_H

#include "lib/gluoncreator_macros.h"

#include "propertywidgetitemfactory.h"

#include <QtCore/QVariant>
#include <QtGui/QWidget>

namespace GluonCreator
{
    struct QtMetaObject : private QObject
    {
        public:
            static const QMetaObject* get()
            {
                return &static_cast<QtMetaObject*>( 0 )->staticQtMetaObject;
            }
    };

    /**
    * The Property Widget Item is a class which will take an object and the name
    * of a property, and provide functionality for editing this property's value,
    * at the same time updating it in the object containing the project
    */
    class GLUONCREATOR_EXPORT PropertyWidgetItem : public QWidget
    {
            Q_OBJECT
        public:
            explicit PropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~PropertyWidgetItem();
	    virtual void update(QVariant newValue){}		//CALLING THIS WOULD CALL UPDATE ON ANY PROPERTY THAT INHERITS THIS
            QWidget* editWidget() const;
            QObject* editObject() const;
            QString editProperty() const;


            virtual QStringList supportedDataTypes() const = 0;
            virtual PropertyWidgetItem* instantiate() = 0;

            const QString typeName() const;

        public Q_SLOTS:
            virtual void setEditObject( QObject* editThis );
            virtual void setEditProperty( const QString& propertyName );
            virtual void setEditWidget( QWidget* widget );
            virtual void setEditValue( const QVariant& value );
            virtual void valueChanged( QVariant );

        Q_SIGNALS:
            void propertyChanged( QObject* object, const QString& propertyName, const QVariant& oldValue, const QVariant& newValue );

        private:
            class PropertyWidgetItemPrivate;
            PropertyWidgetItemPrivate* d;
    };
}

#endif // GLUON_CREATOR_PROPERTYWIDGETITEM_H
