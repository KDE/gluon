/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUONCREATOR_INTVECTORPROPERTYWIDGETITEM_H
#define GLUONCREATOR_INTVECTORPROPERTYWIDGETITEM_H

#include <creator/widgets/propertywidgetitem.h>

class QSpinBox;
class QToolButton;
class QLabel;

namespace GluonCreator
{
    class IntVectorPropertyWidgetItem : public GluonCreator::PropertyWidgetItem
    {
            Q_OBJECT
        public:
            explicit IntVectorPropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~IntVectorPropertyWidgetItem();

            virtual QStringList supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public Q_SLOTS:
            virtual void setEditValue( const QVariant& value );

        private:
            void addItem( int value );
            Q_SLOT void addItem();
            Q_SLOT void removeClicked();
            Q_SLOT void spinValueChanged( int newValue );
            void valueHasChanged();

            QWidget* listItems;
            QToolButton* addButton;
            QLabel* countLabel;

            QMap<QToolButton*, QSpinBox*> intEditorItems;
            QMap<QSpinBox*, int> intValues;
            QList<QSpinBox*> itemOrder;

            bool isList;
    };
}

#endif // GLUONCREATOR_INTVECTORPROPERTYWIDGETITEM_H
