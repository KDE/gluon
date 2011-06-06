/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#include "propertywidgetitemfactory.h"
#include "nullpropertywidgetitem.h"
#include "enumpropertywidgetitem.h"
#include "gluonobjectpropertywidgetitem.h"

#include <core/debughelper.h>
#include <core/gluonobjectfactory.h>

#include <QtCore/QMetaClassInfo>

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( PropertyWidgetItemFactory )

PropertyWidgetItem*
PropertyWidgetItemFactory::create( const QObject* object, const QString& type, QWidget* parent )
{
    DEBUG_BLOCK

    // First check if there's any PIW which supports the type
    QList<QString> pwiKeys = piwTypes.keys();
    foreach( const QString & thisType, pwiKeys )
    {
        if( thisType == type )
        {
            PropertyWidgetItem* item = piwTypes[thisType]->instantiate();
            item->setParent( parent );
            return item;
        }
    }

    QString str = type.section( "::", 0, -2 );
    QString typeStr = type.section( "::", -1 );
    const QMetaObject* mo;
    if( str.compare( "Qt" ) && !str.isEmpty() )
    {
        mo = GluonCore::GluonObjectFactory::instance()->objectTypes().value( str );
    }
    else
    {
        mo = object->metaObject();
    }
    // Check whether we've got an item which uses an enum to grab its value
    //         if (mo->enumeratorCount() > 0)
    //         {
    //             for (int i = 0; i < mo->enumeratorCount(); ++i)
    //             {
    //                 DEBUG_TEXT(QString("Enumerator found: %1").arg(mo->enumerator(i).name()));
    //             }
    //
    if( mo && mo->indexOfEnumerator( typeStr.toUtf8() ) > -1 )
    {
        return new EnumPropertyWidgetItem( type, parent );
    }
    else
    {
        mo = QtMetaObject::get();
        if( mo && mo->indexOfEnumerator( type.toUtf8() ) > -1 )
        {
            return new EnumPropertyWidgetItem( type, parent );
        }
    }

    // Then see if it's a reference type inheriting GluonObject...
    QString typeTruncated = type.left( type.length() - 1 );
    foreach( const QString & thisType, GluonCore::GluonObjectFactory::instance()->objectTypeNames() )
    {
        if( thisType == typeTruncated )
        {
            return new GluonObjectPropertyWidgetItem( typeTruncated, parent );
        }
    }

    // Finally, throw back a Null item if we've got nothing...
    DEBUG_TEXT( QString( "Attempting to instantiate unknown property widget item of type %1" ).arg( type ) );

    return new NullPropertyWidgetItem( parent );
}

void
PropertyWidgetItemFactory::registerNewPIW( PropertyWidgetItem* newPIW )
{
    if( newPIW )
    {
        foreach( const QString & type, newPIW->supportedDataTypes() )
        {
            piwTypes[type] = newPIW;
        }
    }
}

