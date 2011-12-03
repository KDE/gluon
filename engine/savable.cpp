/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "savable.h"

#include "asset.h"

#include <core/gluonobject.h>
#include <core/debughelper.h>
#include <core/gluon_global.h>
#include <core/metainfo.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QtCore/QDebug>

using namespace GluonEngine;

bool Savable::saveToFile( GluonCore::GluonObject* object )
{
    DEBUG_BLOCK

    if( !object )
    {
        DEBUG_TEXT( "Asset was NULL!" )
        return false;
    }

    Savable* savableObject = dynamic_cast<Savable*>( object );
    if( !savableObject )
    {
        return false;
    }

    if( !savableObject->savableDirty )
    {
        return true;
    }

    QString file = Asset::fullyQualifiedFileName( object );
    object->setProperty( "file", file );

    // Make all the directories requires up to this file
    QDir::current().mkpath( file.section( '/', 0, -2 ) );

    // Perform the save
    QFile* savableFile = new QFile( file );
    if( !savableFile->open( QIODevice::WriteOnly ) )
    {
        DEBUG_TEXT2( "Could not write to file %1", object->property( "file" ).value<QUrl>().toString() )
        delete savableFile;
        return false;
    }

    savableObject->writeContents( savableFile );
    savableFile->close();

    delete savableFile;

    // Remember to undirty yourself
    if( savableObject )
        savableObject->savableDirty = false;
    return true;
}
