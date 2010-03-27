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

#ifndef GLUON_CREATOR_PROPERTIESDOCK_H
#define GLUON_CREATOR_PROPERTIESDOCK_H

#include <widgets/dock.h>

#include <selectionmanager.h>

namespace GluonEngine
{
    class Component;
}

namespace GluonCreator
{

    class PropertiesDock : public Dock
    {
            Q_OBJECT
        public:
            explicit PropertiesDock(const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0);
            ~PropertiesDock();

            QAbstractItemView* view();
            QAbstractItemModel* model();

        public slots:
            void setSelection(GluonCore::GluonObject* obj = 0);
            void selectionChanged(SelectionManager::SelectionList selection);
            void newComponent(GluonEngine::Component* comp);
            void propertyChanged(QObject* object, QString property, QVariant oldValue, QVariant newValue);

        private:
            class PropertiesDockPrivate;
            PropertiesDockPrivate *d;
    };

}

#endif // GLUON_CREATOR_PROPERTIESDOCK_H
