/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef GLUON_CREATOR_PROPERTYWIDGETITEM_H
#define GLUON_CREATOR_PROPERTYWIDGETITEM_H

#include "gluoncreator_macros.h"
#include "propertywidgetitemfactory.h"

#include <QtCore/QVariant>
#include <QtGui/QWidget>

namespace GluonCreator
{
    /**
    * The Property Widget Item is a class which will take an object and the name
    * of a property, and provide functionality for editing this property's value,
    * at the same time updating it in the object containing the project
    */
    class GLUONCREATOR_EXPORT PropertyWidgetItem : public QWidget
    {
        Q_OBJECT
        public:
            PropertyWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);
            virtual ~PropertyWidgetItem();

            QWidget* editWidget();
            
            virtual QList<QString> supportedDataTypes() const = 0;
            virtual PropertyWidgetItem* instantiate() = 0;
            
            const QString typeName() const;

        public slots:
            virtual void setEditObject(QObject * editThis);
            virtual void setEditProperty(const QString& propertyName);
            virtual void setEditWidget(QWidget *widget);
            virtual void setEditValue(const QVariant& value);
            virtual void valueChanged(QVariant);

        signals:
            void propertyChanged(const QString& propertyName, const QVariant& oldValue, const QVariant& newValue);

        private:
            class PropertyWidgetItemPrivate;
            PropertyWidgetItemPrivate *d;
    };
}

#endif				// GLUON_CREATOR_PROPERTYWIDGETITEM_H
