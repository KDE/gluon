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


namespace Gluon
{
    class GluonObject;
    class Component;
    
    namespace Creator
    {
        class PropertyWidget : public QScrollArea
        {
            Q_OBJECT;
            
            public:
                PropertyWidget(QObject * parent = 0);
                ~PropertyWidget();
                
                GluonObject * object() const;
                void setObject(GluonObject * theObject);
                void clear();
                
            private:
                GluonObject * m_object;
                
                QWidget * createSubobjectPropertyView();
                
                void setupPropertyView();
                void appendToPropertyView(QGridLayout *layout, qint32 & row, QObject * name, QString description, QString value, QVariant options);
                void appendToPropertyView(QGridLayout *layout, qint32 & row, QObject * name, QString description, QString value);
                void appendObjectToPropertyView (QGridLayout * layout, qint32 &row, GluonObject * node);
                void appendSubobjectToPropertyView (QGridLayout *layout, qint32 &row, GluonObject * node);
                void appendMetaObjectToPropertyView (QGridLayout * layout, qint32 &row, QObject * object);
        };
    }
}

#endif				// GLUON_CREATOR_PROPERTYWIDGET_H
