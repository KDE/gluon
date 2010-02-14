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

#include "propertywidgetitem.h"

namespace GluonCreator {

    class QuaternionPropertyWidgetItem : public PropertyWidgetItem
    {
        Q_OBJECT
        public:
            QuaternionPropertyWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);
            ~QuaternionPropertyWidgetItem();

        public slots:
            void setEditValue(const QVariant& value);
            void xValueChanged(double value);
            void yValueChanged(double value);
            void zValueChanged(double value);
            void angleValueChanged(double value);

        private:
            class QuaternionPropertyWidgetItemPrivate;
            QuaternionPropertyWidgetItemPrivate* d;
    };

}

#endif // GLUON_CREATOR_QUATERNIONPROPERTYWIDGETITEM_H
