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

#include "scenedockplugin.h"

#include <KLocalizedString>

#include "scenedock.h"

using namespace Gluon::Creator;


Gluon::Creator::SceneDockPlugin::SceneDockPlugin(QObject* parent, const QList< QVariant >& params)
    : DockPlugin(parent, params)
{

}


Gluon::Creator::SceneDockPlugin::~SceneDockPlugin()
{

}

Dock* Gluon::Creator::SceneDockPlugin::createDock(KXmlGuiWindow* parent)
{
    return new SceneDock(i18n("Scene"), parent);
}

GLUON_CREATOR_PLUGIN_EXPORT(SceneDockPlugin)
