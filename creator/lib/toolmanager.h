/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinu.us>
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

#ifndef GLUONCREATOR_TOOLMANAGER_H
#define GLUONCREATOR_TOOLMANAGER_H

#include "gluoncreator_macros.h"

#include "core/singleton.h"

class KXmlGuiWindow;

namespace GluonCreator
{
    class GLUONCREATOR_EXPORT ToolManager : public GluonCore::Singleton<ToolManager>
    {
            Q_OBJECT
        public:
            // void addTool( QDockWidget* dock, Qt::DockWidgetArea area, Qt::Orientation orient );
            // void removeTool( QDockWidget* dock );

            KXmlGuiWindow* mainWindow();
            void setMainWindow( KXmlGuiWindow* window );

        public Q_SLOTS:
            // void setToolssEnabled( bool enabled );

        private:
            friend class GluonCore::Singleton<ToolManager>;

            ToolManager();
            virtual ~ToolManager();
            Q_DISABLE_COPY( ToolManager )

            class Private;
            Private* const d;
    };
}

#endif // GLUONCREATOR_TOOLMANAGER_H
