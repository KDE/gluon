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

Dock* ViewWidgetDockPlugin::createDock(KXmlGuiWindow* parent)
{
    return new ViewWidgetDock(i18n("View"), parent);
}

GLUON_CREATOR_PLUGIN_EXPORT(ViewWidgetDockPlugin)
