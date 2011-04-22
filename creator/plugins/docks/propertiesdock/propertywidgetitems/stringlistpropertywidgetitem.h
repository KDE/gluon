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

#ifndef GLUONCREATOR_STRINGLISTRPROPERTYWIDGETITEM_H
#define GLUONCREATOR_STRINGLISTRPROPERTYWIDGETITEM_H

#include "widgets/propertywidgetitem.h"

class QLineEdit;
class QToolButton;
class QLabel;

namespace GluonCreator
{
    class StringListPropertyWidgetItem : public GluonCreator::PropertyWidgetItem
    {
            Q_OBJECT
        public:
            explicit StringListPropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~StringListPropertyWidgetItem();

            virtual QStringList supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public Q_SLOTS:
            virtual void setEditValue( const QVariant& value );

        private:
            void addItem( QString value );
            Q_SLOT void addItem();
            Q_SLOT void removeClicked();
            Q_SLOT void leValueChanged( QString newValue );
            void valueHasChanged();

            QWidget* listItems;
            QToolButton* addButton;
            QLabel* countLabel;

            QMap<QToolButton*, QLineEdit*> textEditorItems;
            QMap<QLineEdit*, QString> stringValues;
            QList<QLineEdit*> itemOrder;

            bool isStringList;
            bool isList;
    };
}

#endif // GLUONCREATOR_STRINGLISTRPROPERTYWIDGETITEM_H
