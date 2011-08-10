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

#include "codewidgetkpart.h"
#include <kdemacros.h>
#include <kparts/genericfactory.h>


using namespace GluonCreator;

K_PLUGIN_FACTORY( CodeWidgetFactory, registerPlugin<CodeWidgetKpart>(); ) // produce a factory
K_EXPORT_PLUGIN( CodeWidgetFactory( "Code Editor", "Code Editor" ) )


GluonCreator::CodeWidgetKpart::CodeWidgetKpart( QWidget* parentWidget, QObject* parent, const QVariantList& ) : KParts::ReadWritePart( parent )

//CodeWidgetKpart::CodeWidgetKpart( QWidget *parentWidget, QObject *parent, const QVariantList& )
  //  : KParts::ReadWritePart( parent )

{
    KGlobal::locale()->insertCatalog( "gluoncreator" );
    setComponentData( CodeWidgetFactory::componentData() );

    main = new NodeEditor();
    setWidget( main );
}

GluonCreator::CodeWidgetKpart::~CodeWidgetKpart()
{

}


