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

#ifndef GLUONCREATOR_GLUONOBJECTPROPERTYWIDGETITEM_H
#define GLUONCREATOR_GLUONOBJECTPROPERTYWIDGETITEM_H

#include "propertywidgetitem.h"

class QPushButton;
class QLabel;
namespace GluonCore
{
    class GluonObject;
}

namespace GluonCreator
{
    class GluonObjectPWIPrivate;
    class GluonObjectPropertyWidgetItem : public PropertyWidgetItem
    {
            Q_OBJECT
        public:
            explicit GluonObjectPropertyWidgetItem(const QString &typeName, QWidget* parent = 0, Qt::WindowFlags f = 0);
            ~GluonObjectPropertyWidgetItem();

            virtual PropertyWidgetItem* instantiate();
            virtual QList< QString > supportedDataTypes() const;

            void setTypeName(const QString &typeName);
            QString typeName() const;

        public slots:
            void browseForItems();
            void setEditValue(const QVariant& value);
            void objectValueChanged(GluonCore::GluonObject * value);

        private:
            GluonObjectPWIPrivate * d;
    };
}

#endif // GLUONCREATOR_GLUONOBJECTPROPERTYWIDGETITEM_H
