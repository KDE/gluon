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

#ifndef GLUONCREATOR_PROPERTYWIDGETCONTAINER_H
#define GLUONCREATOR_PROPERTYWIDGETCONTAINER_H

#include <QtGui/QWidget>
#include <QtCore/QString>

namespace GluonCore
{
    class GluonObject;
}

namespace GluonCreator
{
    class PropertyWidgetItem;
    class PropertyWidgetContainer : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(bool expanded READ expanded WRITE setExpanded)
        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled)
        Q_PROPERTY(QString title READ title WRITE setTitle)
        
        public:
            PropertyWidgetContainer(GluonCore::GluonObject* theObject, QWidget* parent = 0, Qt::WindowFlags f = 0);
            ~PropertyWidgetContainer();
            
            void setObject(GluonCore::GluonObject* theObject);
            
            bool expanded() const;
            void setExpanded(const bool& newExpanded);
            Q_SLOT void toggleExpanded();
            
            bool enabled() const;
            Q_SLOT void setEnabled(const bool& newEnabled);
            
            QString title() const;
            void setTitle(const QString& newTitle);
            
            void addDefaultMenuItems();
            void addMenuItem(QAction* menuItem);
            void removeMenuItem(QAction* menuItem);
            
        Q_SIGNALS:
            void propertyChanged(QObject* object, const QString& property, const QVariant& oldValue, const QVariant& newValue);
            
        private:
            class PropertyWidgetContainerPrivate;
            PropertyWidgetContainerPrivate* d;
    };
}

#endif // GLUONCREATOR_PROPERTYWIDGETCONTAINER_H
