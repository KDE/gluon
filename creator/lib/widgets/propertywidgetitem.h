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

#include <QtGui/QWidget>
#include <QtCore/QVariant>

#include "gluoncreatorlib_macros.h"

namespace Gluon
{
    namespace Creator
    {
        /**
         * The Property Widget Item is a class which will take an object and the name
         * of a property, and provide functionality for editing this property's value,
         * at the same time updating it in the object containing the project
         */
        class GLUONCREATORLIB_EXPORT PropertyWidgetItem : public QWidget
        {
            Q_OBJECT;

            public:
                PropertyWidgetItem(QObject * parent = 0, Qt::WindowFlags f = 0);
                ~PropertyWidgetItem();

                void setEditObject(QObject * editThis);
                void setEditProperty(QString propertyName);

            private Q_SLOTS:
                void propertyChanged(QVariant value);
                void propertyChanged(int value);
                void propertyChanged(double value);
                void propertyChanged(QString value);

            private:
                void setupPropertyWidget();

                QObject * editedObject;
                QString propertyName;

                QWidget *createLineEdit (QVariant value);
                QWidget *createSpinBox (QVariant value);
                QWidget *createDoubleSpinBox (QVariant value);

                QWidget * editWidget;
        };
    }
}

#endif				// GLUON_CREATOR_PROPERTYWIDGETITEM_H
