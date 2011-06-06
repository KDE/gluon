/******************************************************************************
 * This file is part of the Gluon Development Platform
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


#include "vcstoolplugin.h"
#include "vcstool.h"

#include <creator/lib/gluoncreator_macros.h>

#include <KDE/KLocalizedString>

using namespace GluonCreator;

VcsToolPlugin::VcsToolPlugin( QObject* parent, const QList< QVariant >& params )
    : ToolPlugin( parent, params )
{

}

VcsToolPlugin::~VcsToolPlugin()
{

}

QWidget* VcsToolPlugin::createTool( KXmlGuiWindow* parent )
{
    QWidget* tool = new VcsTool( i18n( "Version Control System" ), parent );
    return tool;
}

GLUON_CREATOR_PLUGIN_EXPORT( VcsToolPlugin )
