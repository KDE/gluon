/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GLUON_CREATOR_PROPERTIESDOCK_H
#define GLUON_CREATOR_PROPERTIESDOCK_H

#include <creator/selectionmanager.h>

#include <QtGui/QDockWidget>

namespace GluonEngine
{
    class Component;
}

class QUndoCommand;
namespace GluonCreator
{
    class PropertiesDock : public QDockWidget
    {
            Q_OBJECT
        public:
            explicit PropertiesDock( const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0 );
            ~PropertiesDock();

        public slots:
            void selectionChanged( SelectionManager::SelectionList selection );
            void propertyChanged( QObject* object, QString property, QVariant oldValue, QVariant newValue );
            void propertyWidgetChanged( GluonCore::GluonObject* parent );

        private:
            class PropertiesDockPrivate;
            PropertiesDockPrivate* const d;
    };

}

#endif // GLUON_CREATOR_PROPERTIESDOCK_H
