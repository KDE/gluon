/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
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

#include "dockplugin.h"
#include "widgets/dock.h"
#include <KXmlGuiWindow>
#include <KActionCollection>
#include <KStandardDirs>
#include <KDebug>

using namespace GluonCreator;

DockPlugin::DockPlugin(QObject* parent, const QList< QVariant >& params) : Plugin(parent, params)
{

}

DockPlugin::~DockPlugin()
{

}


void DockPlugin::load(KXmlGuiWindow* mainwindow)
{
    mainwindow->insertChildClient(this);

    m_dock = createDock(mainwindow);
    mainwindow->addDockWidget(Qt::LeftDockWidgetArea, m_dock);

    actionCollection()->addAction(QString("show%1Action").arg(m_dock->objectName()), m_dock->toggleViewAction());

    QString xml = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<kpartgui name=\"gluoncreator_dockplugin_%1\" version=\"1\">").arg(m_dock->objectName());
    xml += QString("<MenuBar><Menu name=\"settings\"><Menu name=\"docks\"><Action name=\"show%1Action\" /></Menu></Menu></MenuBar></kpartgui>").arg(m_dock->objectName());

    setXML(xml);
}

void DockPlugin::unload(KXmlGuiWindow* mainWindow)
{
    mainWindow->removeDockWidget(m_dock);
    actionCollection()->removeAction(actionCollection()->action(QString("show%1Action").arg(m_dock->objectName())));
    parentClient()->removeChildClient(this);
}

#include "dockplugin.moc"
