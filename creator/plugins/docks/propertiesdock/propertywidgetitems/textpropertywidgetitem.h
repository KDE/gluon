/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUON_CREATOR_TEXTPROPERTYWIDGETITEM_H
#define GLUON_CREATOR_TEXTPROPERTYWIDGETITEM_H

#include <creator/lib/widgets/propertywidgetitem.h>

namespace GluonCreator
{
    class TextPropertyWidgetItem : public PropertyWidgetItem
    {
            Q_OBJECT
        public:
            explicit TextPropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            ~TextPropertyWidgetItem();

            virtual QStringList supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public Q_SLOTS:
            void setEditValue( const QVariant& value );

        private Q_SLOTS:
            void textEdited( QString value );
    };
}


#endif // GLUON_CREATOR_TEXTPROPERTYWIDGETITEM_H
