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

#include "gluoncreatorlib_macros.h"

#include <QtCore/QObject>
#include <KPluginInfo>
#include <common/ksingleton.h>

class KXmlGuiWindow;
namespace Gluon
{

  namespace Creator
  {

    class Plugin;

    class GLUONCREATORLIB_EXPORT PluginManager : public KSingleton<PluginManager>
    {
        friend class KSingleton<PluginManager>;

        Q_OBJECT
        public:
            QList<KPluginInfo> pluginInfos() const;

        public slots:
            void loadPlugins();
            void setMainWindow(KXmlGuiWindow* window);

        signals:
            void pluginLoaded(Plugin * plugin);

        private:
            PluginManager() { }
            ~PluginManager() { }
            Q_DISABLE_COPY(PluginManager)

            QHash<QString, Plugin*> m_loadedPlugins;
            KXmlGuiWindow* m_mainWindow;
    };

  }

}

#endif // GLUON_CREATOR_DOCKPLUGINLOADER_H
