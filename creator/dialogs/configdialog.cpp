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

#include "configdialog.h"
#include <KPluginSelector>
#include <lib/pluginmanager.h>

using namespace Gluon::Creator;


Gluon::Creator::ConfigDialog::ConfigDialog(QWidget* parent, const QString& name, KConfigSkeleton* config): KConfigDialog(parent, name, config)
{
    QList<KPluginInfo> infos = PluginManager::instance()->pluginInfos();

    m_plugins = new KPluginSelector();
    m_plugins->addPlugins(infos, KPluginSelector::ReadConfigFile, i18n("Docks"), QString("dock"));
    m_plugins->addPlugins(infos, KPluginSelector::ReadConfigFile, i18n("Tools"), QString("tool"));
    m_plugins->addPlugins(infos, KPluginSelector::ReadConfigFile, i18n("Other"), QString());

    addPage(m_plugins, i18n("Plugins"), "gluon");
    connect(m_plugins, SIGNAL(changed(bool)), SLOT(enableButtonApply(bool)));
}

Gluon::Creator::ConfigDialog::~ConfigDialog()
{

}

void Gluon::Creator::ConfigDialog::accept()
{
    m_plugins->save();
    PluginManager::instance()->loadPlugins();
    QDialog::accept();
}
