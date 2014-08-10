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

#include "projectinspectorplugin.h"

#include <QtWidgets/QAction>
#include <KXmlGui/KActionCollection>
#include <KI18n/KLocalizedString>
#include "projectinspectorwindow.h"

using namespace GluonCreator;

class ProjectInspectorPlugin::Private
{
    public:
};

ProjectInspectorPlugin::ProjectInspectorPlugin(QObject* parent, const QList< QVariant >& params)
    : ToolPlugin(parent, params), d( new Private )
{
    //setComponentData( KGlobal::mainComponent() ); TODO: Plugins
    setXMLFile( "gluoncreator_toolplugin_projectinspectorui.rc", true );
}

ProjectInspectorPlugin::~ProjectInspectorPlugin()
{
}

void ProjectInspectorPlugin::showWindow()
{
    ProjectInspectorWindow window;
    window.exec();
}

void ProjectInspectorPlugin::initialize()
{
    QAction* showAction = new QAction( i18nc( "Show the Project Inspector window", "Project Inspector..." ), this );
    connect( showAction, SIGNAL(triggered(bool)), SLOT(showWindow()) );
    actionCollection()->addAction( "show_projectinspector", showAction );
}

GLUON_CREATOR_PLUGIN_EXPORT( ProjectInspectorPlugin )
