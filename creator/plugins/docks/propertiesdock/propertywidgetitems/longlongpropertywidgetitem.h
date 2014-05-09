/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef GLUON_CREATOR_LONGLONGPROPERTYWIDGETITEM_H
#define GLUON_CREATOR_LONGLONGPROPERTYWIDGETITEM_H

#include <creator/widgets/propertywidgetitem.h>

namespace GluonCreator
{
    class LongLongPropertyWidgetItem : public PropertyWidgetItem
    {
            Q_OBJECT

        public:
            explicit LongLongPropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            ~LongLongPropertyWidgetItem();

            virtual QStringList supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public Q_SLOTS:
            virtual void setEditProperty( const QString& propertyName );
            virtual void setEditValue( const QVariant& value );

        private Q_SLOTS:
            void doubleValueChanged( double value );
    };
}

#endif //GLUON_CREATOR_LONGLONGPROPERTYWIDGETITEM_H
