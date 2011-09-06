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

#include "threadDocument.h"
#include "graphDocument.h"
#include <QMutex>
#include <KDebug>
#include <KLocale>
#include <QWaitCondition>

ThreadDocument::ThreadDocument( QWaitCondition& docCondition, QMutex& mutex, QObject* parent ):
    QThread( parent ),
    _docCondition( docCondition ), _mutex( mutex )
{
    _graphDocument = 0;
    // _loading = false;
    // _name = i18n("Untitled0");
}

ThreadDocument::~ThreadDocument()
{
}


void ThreadDocument::releaseDocument()
{
    if( _graphDocument )
        _graphDocument->deleteLater();
    _graphDocument = 0;
}

void ThreadDocument::createEmptyDocument()
{
    releaseDocument();
    _graphDocument = new GraphDocument( i18n( "Untitled" ), 800, 600 );
    _docCondition.wakeAll();
    kDebug() << "Waking All";
}

void ThreadDocument::loadDocument( const QString& name )
{
    createEmptyDocument();
    if( name.isEmpty() )
    {
        _graphDocument->addGraph( i18n( "Untitled0" ) );
    }
    else
    {
        _graphDocument->loadFromInternalFormat( name );
    }
    _docCondition.wakeAll();
}

void ThreadDocument::setGraphDocument( GraphDocument* doc )
{
    releaseDocument();
    _graphDocument = doc;
    doc->moveToThread( this );
    _docCondition.wakeAll();
}

void ThreadDocument::run()
{
    loadDocument();
    exec();
}

