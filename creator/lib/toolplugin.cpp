/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "toolplugin.h"

#include <KDE/KXmlGuiWindow>
#include <KDE/KActionCollection>
#include <KDE/KStandardDirs>

#include <QtGui/QWidget>

using namespace GluonCreator;

ToolPlugin::ToolPlugin( QObject* parent, const QList< QVariant >& params )
    : Plugin( parent, params )
    , m_tool(0)
{

}

ToolPlugin::~ToolPlugin()
{

}

void ToolPlugin::load( KXmlGuiWindow* mainWindow )
{
    mainWindow->insertChildClient( this );

    m_tool = createTool( mainWindow );

    if (!m_tool->actions().isEmpty())
        actionCollection()->addAction( QString( "show%1Action" ).arg( m_tool->objectName() ), m_tool->actions().first() );

    QString xml = QString( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<kpartgui name=\"gluoncreator_toolkplugin_%1\" version=\"1\">" ).arg( m_tool->objectName() );
    xml += QString( "<MenuBar><Menu name=\"settings\"><Menu name=\"tools\"><Action name=\"show%1Action\" /></Menu></Menu></MenuBar></kpartgui>" ).arg( m_tool->objectName() );

    setXML( xml );
}

void ToolPlugin::unload( KXmlGuiWindow* /* mainWindow */ )
{
    actionCollection()->removeAction( actionCollection()->action( QString( "show%1Action" ).arg( m_tool->objectName() ) ) );
    parentClient()->removeChildClient( this );
}
