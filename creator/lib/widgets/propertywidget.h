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

#ifndef GLUON_CREATOR_PROPERTYWIDGET_H
#define GLUON_CREATOR_PROPERTYWIDGET_H

#include <QtGui/QWidget>
#include <QGridLayout>
#include <QScrollArea>

#include "gluoncreatorlib_macros.h"

namespace Gluon
{
    class GluonObject;
    class Component;

    namespace Creator
    {
        class GLUONCREATORLIB_EXPORT PropertyWidget : public QScrollArea
        {
            Q_OBJECT;

            public:
                PropertyWidget(QWidget* parent = 0);
                ~PropertyWidget();

                GluonObject * object() const;
                void clear();

                void setObject(Gluon::GluonObject* object);
                void appendObject(Gluon::GluonObject* obj, bool useColor = false);

            signals:
                void propertyChanged(const QString& property, const QVariant& oldValue, const QVariant& newValue);
                
            private:
                class PropertyWidgetPrivate;
                PropertyWidgetPrivate *d;

                void appendMetaObject(QObject* object, QGridLayout* layout);
        };
    }
}

#endif				// GLUON_CREATOR_PROPERTYWIDGET_H
