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

#include "dockplugin.h"
#include "widgets/dock.h"
#include <KXmlGuiWindow>
#include <KActionCollection>
#include <KStandardDirs>

using namespace Gluon::Creator;

/*class DockPlugin::DockPluginPrivate
{
    public:
        DockPluginPrivate() { showAction = 0; }
        
        KAction* showAction;
};*/

Gluon::Creator::DockPlugin::DockPlugin(QObject* parent, const QList< QVariant >& params) : Plugin(parent, params)
{
    //d = new DockPluginPrivate;
}

Gluon::Creator::DockPlugin::~DockPlugin()
{
    //delete d;
}


void Gluon::Creator::DockPlugin::initialize(KXmlGuiWindow* mainwindow)
{
    mainwindow->insertChildClient(this);

    Dock* dockWidget = createDock(mainwindow);
    mainwindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    actionCollection()->addAction("show" + dockWidget->objectName() + "Action", dockWidget->toggleViewAction());

    setXMLFile(KStandardDirs::locate("appdata", "gluon_creator_dockplugin_" + dockWidget->objectName().toLower() + "ui.rc"));
}

#include "dockplugin.moc"