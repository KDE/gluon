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

#ifndef GLUON_CREATOR_DOCKPLUGINLOADER_H
#define GLUON_CREATOR_DOCKPLUGINLOADER_H

#include "gluoncreator_macros.h"

#include <QtCore/QObject>
#include <KPluginInfo>
#include <core/singleton.h>

class KXmlGuiWindow;
namespace GluonCreator
{
    class Plugin;

    class GLUONCREATOR_EXPORT PluginManager : public GluonCore::Singleton<PluginManager>
    {
            Q_OBJECT
        public:
            QList<KPluginInfo> pluginInfos() const;

        public slots:
            void loadPlugins();
            void setMainWindow(KXmlGuiWindow* window);

        signals:
            void pluginLoaded(Plugin * plugin);

        private:
            friend class GluonCore::Singleton<PluginManager>;

            PluginManager();
            ~PluginManager();
            Q_DISABLE_COPY(PluginManager)

            class PluginManagerPrivate;
            PluginManagerPrivate * const d;
    };
}

#endif // GLUON_CREATOR_DOCKPLUGINLOADER_H
