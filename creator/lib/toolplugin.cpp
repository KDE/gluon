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

#include "toolplugin.h"

#include <KDE/KXmlGuiWindow>
#include <KDE/KActionCollection>

#include <QtGui/QWidget>
#include <QtGui/QAction>

using namespace GluonCreator;

class ToolPlugin::Private
{
    public:
    Private()
        : m_tool( 0 )
    {
    }

    QWidget* m_tool;
};

ToolPlugin::ToolPlugin( QObject* parent, const QList< QVariant >& params )
    : Plugin( parent, params )
    , d( new Private() )
{

}

ToolPlugin::~ToolPlugin()
{

}

void ToolPlugin::load( KXmlGuiWindow* mainWindow )
{
    mainWindow->insertChildClient( this );

    d->m_tool = createTool( mainWindow );

    QString xml = QString( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<kpartgui name=\"gluoncreator_toolplugin_%1\" version=\"1\">" ).arg( d->m_tool->objectName() );
    xml.append( "<MenuBar><Menu name=\"tools\"><Menu name=\"versionControlSystem\">" );
    // xml.append(<text>&amp;Tools</text>);
    // xml.append(<text>&amp;Version Control System</text>);
    // xml.append(<DefineGroup name="tools_operations" append="tools_operations" />);
    foreach( QAction * action, d->m_tool->actions() )
    {
        xml.append( QString( "<Action name=\"%1Action\" />" ).arg( action->objectName() ) );
        actionCollection()->addAction( QString( "%1Action" ).arg( action->objectName() ), action );
    }
    xml.append( "</Menu></Menu></MenuBar></kpartgui>" );

    setXML( xml );
}

void ToolPlugin::unload( KXmlGuiWindow* /* mainWindow */ )
{
    actionCollection()->removeAction( actionCollection()->action( QString( "%1Action" ).arg( d->m_tool->objectName() ) ) );
    parentClient()->removeChildClient( this );
}
