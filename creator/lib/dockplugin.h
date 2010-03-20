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

#ifndef GLUON_CREATOR_DOCKPLUGIN_H
#define GLUON_CREATOR_DOCKPLUGIN_H

#include <KXmlGuiWindow>

#include "plugin.h"

class KAction;
namespace GluonCreator
{

    class Dock;

    class GLUONCREATOR_EXPORT DockPlugin : public Plugin
    {
            Q_OBJECT
        public:
            DockPlugin(QObject* parent, const QList<QVariant>& params);
            virtual ~DockPlugin();

            virtual void load(KXmlGuiWindow* mainWindow);
            virtual void unload(KXmlGuiWindow* mainWindow);

        protected:
            virtual Dock* createDock(KXmlGuiWindow* parent) = 0;

            Dock* m_dock;
    };

}

#endif // GLUON_CREATOR_DOCKPLUGIN_H
