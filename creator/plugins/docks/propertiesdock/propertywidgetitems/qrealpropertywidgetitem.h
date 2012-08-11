/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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
#ifndef QREALPROPERTYWIDGETITEM_H
#define QREALPROPERTYWIDGETITEM_H
#include <QDebug>
#include <creator/lib/widgets/propertywidgetitem.h>

class QDoubleSpinBox;

namespace GluonCreator
{
    class QRealPropertyWidgetItem : public PropertyWidgetItem
    {
            Q_OBJECT
        public:
            explicit QRealPropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            ~QRealPropertyWidgetItem();
	    void update(){qDebug()<< "In update of qreal!";}
            virtual QStringList supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public Q_SLOTS:
            virtual void setEditProperty( const QString& value );
            virtual void setEditValue( const QVariant& value );

        private Q_SLOTS:
            void qrealValueChanged( double value );

    };
}

#endif
