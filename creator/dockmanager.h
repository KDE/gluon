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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef GLUON_CREATOR_DOCKMANAGER_H
#define GLUON_CREATOR_DOCKMANAGER_H

#include "gluoncreator_macros.h"

#include <core/singleton.h>

class QAction;
class QDockWidget;
class KXmlGuiWindow;

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT DockManager : public GluonCore::Singleton<DockManager>
    {
            Q_OBJECT
            GLUON_SINGLETON( DockManager )
        public:
            void addDock( QDockWidget* dock, Qt::DockWidgetArea area, Qt::Orientation orient );
            void removeDock( QDockWidget* dock );

            KXmlGuiWindow* mainWindow();
            void setMainWindow( KXmlGuiWindow* window );

        public Q_SLOTS:
            void setDocksEnabled( bool enabled );
            void setDocksLocked( bool locked );
            void updateDockActions();

        private:
            ~DockManager();

            class DockManagerPrivate;
            DockManagerPrivate* const d;
    };
}

#endif // GLUON_CREATOR_DOCKMANAGER_H
