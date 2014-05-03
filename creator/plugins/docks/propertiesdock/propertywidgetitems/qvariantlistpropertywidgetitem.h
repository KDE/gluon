/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Dan Leinir Turthra Jensen <admin@leinir.dk>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef GLUONCREATOR_QVARIANTLISTPROPERTYWIDGETITEM_H
#define GLUONCREATOR_QVARIANTLISTPROPERTYWIDGETITEM_H

#include <creator/widgets/propertywidgetitem.h>

class QMenu;
class QToolButton;
class QLabel;
namespace GluonCreator
{
    class QVariantListPropertyWidgetItem : public GluonCreator::PropertyWidgetItem
    {
        Q_OBJECT

        public:
            explicit QVariantListPropertyWidgetItem( QWidget* parent = 0, Qt::WindowFlags f = 0 );
            virtual ~QVariantListPropertyWidgetItem();

            virtual QStringList supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public Q_SLOTS:
            virtual void setEditValue(const QVariant& value);

        private:
            void addItem( QVariant value );
            Q_SLOT void showAdditionMenu();
            Q_SLOT void addItem();
            Q_SLOT void removeClicked();
            void valueHasChanged();

            // We need slots for each of the types of object - could do the factory thing,
            // but we're being simplistic here. Refactor later if needed.
            Q_SLOT void spinValueChanged( int newValue );
            Q_SLOT void dspinValueChanged( double newValue );
            Q_SLOT void textValueChanged( QString newValue );

            QWidget* listItems;
            QToolButton* addButton;
            QLabel* countLabel;

            QMenu* additionMenu;

            QMap<QToolButton*, QWidget*> editorItems;
            QMap<QWidget*, QVariant> values;
            QList<QWidget*> itemOrder;

            // We cannot simply use the QVariant type list, as we are limited in the amount of
            // types we support.
            /// TODO: Refactor the PWI class to enable us to get only the editor widget, so we can do this properly
            enum ValueTypes
            {
                UnknownType = -1,
                Integer = 0,
                Float,
                String,
            };
    };
}

#endif // GLUONCREATOR_QVARIANTLISTPROPERTYWIDGETITEM_H
