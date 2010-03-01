/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License version 2 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#ifndef GLUON_CREATOR_QUATERNIONPROPERTYWIDGETITEM_H
#define GLUON_CREATOR_QUATERNIONPROPERTYWIDGETITEM_H

#include "widgets/propertywidgetitem.h"

namespace GluonCreator {

    class QuaternionPropertyWidgetItem : public PropertyWidgetItem
    {
        Q_OBJECT
        public:
            QuaternionPropertyWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);
            ~QuaternionPropertyWidgetItem();

            virtual QList<QString> supportedDataTypes() const;
            virtual PropertyWidgetItem* instantiate();

        public slots:
            void setEditValue(const QVariant& value);
            void valueChanged(QVariant value);
            void valueChanged(double value);

        private:
            class QuaternionPropertyWidgetItemPrivate;
            QuaternionPropertyWidgetItemPrivate* d;
    };

}

#endif // GLUON_CREATOR_QUATERNIONPROPERTYWIDGETITEM_H
