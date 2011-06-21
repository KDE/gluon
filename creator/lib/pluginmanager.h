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

#ifndef GLUON_CREATOR_PLUGINMANAGER_H
#define GLUON_CREATOR_PLUGINMANAGER_H

#include "gluoncreator_macros.h"

#include <core/singleton.h>

#include <KDE/KPluginInfo>

#include <QtCore/QHash>

class KXmlGuiWindow;

namespace GluonCreator
{
    class Plugin;

    class GLUONCREATOR_EXPORT PluginManager : public GluonCore::Singleton<PluginManager>
    {
            Q_OBJECT
            GLUON_SINGLETON( PluginManager )
        public:
            QList<KPluginInfo> pluginInfos() const;
            QHash<QString, Plugin*> loadedPlugins();

        public Q_SLOTS:
            void loadPlugins();
            void setMainWindow( KXmlGuiWindow* window );

        Q_SIGNALS:
            void pluginLoaded( Plugin* plugin );

        private:
            ~PluginManager();

            class PluginManagerPrivate;
            PluginManagerPrivate* const d;
    };
}

#endif // GLUON_CREATOR_DOCKPLUGINLOADER_H
