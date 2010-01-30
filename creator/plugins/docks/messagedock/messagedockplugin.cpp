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

#include "messagedockplugin.h"

#include "messagedock.h"

#include <gluoncreator_macros.h>
#include <KLocalizedString>

using namespace GluonCreator;

MessageDockPlugin::MessageDockPlugin(QObject* parent, const QList< QVariant >& params) : DockPlugin(parent, params)
{

}

MessageDockPlugin::~MessageDockPlugin()
{

}

Dock* MessageDockPlugin::createDock(KXmlGuiWindow* parent)
{
    return new MessageDock(i18n("Messages"), parent);
}

GLUON_CREATOR_PLUGIN_EXPORT(MessageDockPlugin)