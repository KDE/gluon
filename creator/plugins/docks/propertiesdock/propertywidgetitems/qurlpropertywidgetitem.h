/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef GLUONCREATOR_QURLPROPERTYWIDGETITEM_H
#define GLUONCREATOR_QURLPROPERTYWIDGETITEM_H

#include "creator/lib/widgets/propertywidgetitem.h"


namespace GluonCreator {

class QUrlPropertyWidgetItem : public GluonCreator::PropertyWidgetItem
{
    Q_OBJECT
    public:
        explicit QUrlPropertyWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);
        ~QUrlPropertyWidgetItem();

        virtual GluonCreator::PropertyWidgetItem* instantiate();
        virtual QList< QString > supportedDataTypes() const;

    public slots:
        virtual void setEditValue(const QVariant& value);
        void urlValueChanged();
};

}

#endif // GLUONCREATOR_QURLPROPERTYWIDGETITEM_H
