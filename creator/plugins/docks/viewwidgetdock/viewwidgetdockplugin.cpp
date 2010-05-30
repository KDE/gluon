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

#include "viewwidgetdockplugin.h"
#include "viewwidgetdock.h"

#include <gluoncreator_macros.h>
#include <KLocalizedString>

using namespace GluonCreator;

ViewWidgetDockPlugin::ViewWidgetDockPlugin(QObject* parent, const QList< QVariant >& params) : DockPlugin(parent, params)
{

}

ViewWidgetDockPlugin::~ViewWidgetDockPlugin()
{

}

QDockWidget* ViewWidgetDockPlugin::createDock(KXmlGuiWindow* parent)
{
    ViewWidgetDock *dock = new ViewWidgetDock(i18n("View"), parent);
    parent->setCentralWidget(dock);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    return dock;
}

GLUON_CREATOR_PLUGIN_EXPORT(ViewWidgetDockPlugin)
