/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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
#include "configdialog.h"
#include "lib/pluginmanager.h"

#include <KDE/KPluginSelector>

using namespace GluonCreator;


ConfigDialog::ConfigDialog( QWidget* parent, const QString& name, KConfigSkeleton* config ): KConfigDialog( parent, name, config )
{
    QList<KPluginInfo> plugins = PluginManager::instance()->pluginInfos();

    m_plugins = new KPluginSelector();
    m_plugins->addPlugins( plugins, KPluginSelector::ReadConfigFile, i18n( "Docks" ), QString( "dock" ) );
    m_plugins->addPlugins( plugins, KPluginSelector::ReadConfigFile, i18n( "Tools" ), QString( "tool" ) );
    m_plugins->addPlugins( plugins, KPluginSelector::ReadConfigFile, i18n( "Others" ), QString() );

    addPage( m_plugins, i18n( "Plugins" ), "gluon" );
    connect( m_plugins, SIGNAL(changed(bool)), SLOT(enableButtonApply(bool)) );
}

ConfigDialog::~ConfigDialog()
{

}

void ConfigDialog::accept()
{
    m_plugins->save();
    PluginManager::instance()->loadPlugins();
    QDialog::accept();
}
