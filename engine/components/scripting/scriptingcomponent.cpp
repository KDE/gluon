/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "scriptingcomponent.h"
#include "scriptingcomponentprivate.h"
#include "scriptingengine.h"

#include "game.h"
#include "gameobject.h"
#include "scene.h"

#include <core/messagehandler.h>
#include <core/gdlserializer.h>
#include <core/directoryprovider.h>
#include <QDebug>
#include <qdir.h>

REGISTER_OBJECTTYPE( GluonEngine, ScriptingComponent )

using namespace GluonEngine;

ScriptingComponent::ScriptingComponent( QObject* parent )
    : Component( parent )
    , d( new ScriptingComponentPrivate( this ) )
{
}

ScriptingComponent::~ScriptingComponent()
{
    if( d->scriptingAsset )
        d->scriptingAsset->deref();

    delete d;
}

QString
ScriptingComponent::category() const
{
    return QString( "Game Logic" );
}

ScriptingAsset* ScriptingComponent::script() const
{
    return d->scriptingAsset;
}

void ScriptingComponent::setScript( GluonEngine::ScriptingAsset* newAsset )
{
    if( d->scriptingAsset )
    {
        disconnect( d->scriptingAsset, SIGNAL(dataChanged()), this, SLOT(scriptAssetUpdated()) );
        d->scriptingAsset->deref();
    }

    d->scriptingAsset = newAsset;
    if( d->scriptingAsset )
    {
        connect( newAsset, SIGNAL(dataChanged()), SLOT(scriptAssetUpdated()) );
        d->scriptingAsset->ref();
    }
}

void ScriptingComponent::scriptAssetUpdated()
{
    d->updateScriptObject();
}

QScriptValue ScriptingComponent::scriptObject()
{
    return d->scriptObject;
}

void ScriptingComponent::initialize()
{
    if( !d->scriptingAsset )
        return;

    if( !d->scriptingAsset->isLoaded() )
        d->scriptingAsset->load();

    if( !d->scriptingAsset->isLoaded() )
        return;

    if( !d->scriptObject.isValid() )
    {
        d->updateScriptObject();
    }

    if( !d->scriptObject.isValid() )
        debug( "Warning: No scripting asset has been chosen" );

    if( d->initializeFunction.isFunction() )
    {
        d->initializeFunction.call( d->scriptObject );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::initialize();
}

void ScriptingComponent::start()
{
    if( d->startFunction.isFunction() )
    {
        d->startFunction.call( d->scriptObject );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
        {
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
        }
    }
    GluonEngine::Component::start();
}

void ScriptingComponent::update( int elapsedMilliseconds )
{
    if( d->updateFunction.isFunction() )
    {
        d->updateFunction.call( d->scriptObject, QScriptValueList() << elapsedMilliseconds );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
        {
            d->updateFunction = QScriptValue();
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
        }
    }
    GluonEngine::Component::update( elapsedMilliseconds );
}

void ScriptingComponent::draw( int timeLapse )
{
    if( d->drawFunction.isFunction() )
    {
        d->drawFunction.call( d->scriptObject, QScriptValueList() << timeLapse );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
        {
            d->drawFunction = QScriptValue();
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
        }
    }
    GluonEngine::Component::draw();
}

void ScriptingComponent::stop()
{
    if( d->stopFunction.isFunction() )
    {
        d->stopFunction.call( d->scriptObject );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::stop();
}

void ScriptingComponent::cleanup()
{
    if( d->cleanupFunction.isFunction() )
    {
        d->cleanupFunction.call( d->scriptObject );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::cleanup();
}

void ScriptingComponent::restore()
{
    if( d->restoreFunction.isFunction() )
    {
        QScriptValue object = restoreComponent();
        d->restoreFunction.call( d->scriptObject, QScriptValueList() << object );
    }
}

void ScriptingComponent::serialize()
{
    if( d->serializeFunction.isFunction() )
    {
        QScriptEngine* engine = ScriptingEngine::instance()->scriptEngine();
        GluonCore::GluonObject* obj = new GluonCore::GluonObject( gameObject()->name() );
        QScriptValue persistenceObject = engine->newQObject( obj, QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties );
        persistenceObject = d->serializeFunction.call( d->scriptObject, QScriptValueList() << persistenceObject );
        serializeComponent( obj );
    }
}

QScriptValue ScriptingComponent::restoreComponent()
{
    QString dir = GluonCore::DirectoryProvider::instance()->saveGamesDirectory();
    dir += gameObject()->name() + QString( ".gluonsave" );
    GluonCore::GluonObjectList list;
    QUrl filename( dir );
    if( ! GluonCore::GDLSerializer::instance()->read( filename, list ) )
        return 0;
    QScriptEngine* engine = ScriptingEngine::instance()->scriptEngine();
    QScriptValue object = engine->newQObject( list.at( 0 ), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties );
    return object;
}

void ScriptingComponent::serializeComponent( GluonCore::GluonObject* obj )
{
    QString dir = GluonCore::DirectoryProvider::instance()->saveGamesDirectory();
    dir += gameObject()->name() + QString( ".gluonsave" );
    QUrl filename( dir );
    GluonCore::GDLSerializer::instance()->write( filename, GluonCore::GluonObjectList() << obj );
}

#include "scriptingcomponent.moc"
