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
#include <qscriptclass.h>
#include <qscriptvalueiterator.h>

REGISTER_OBJECTTYPE( GluonEngine, ScriptingComponent )

using namespace GluonEngine;

ScriptingComponent::ScriptingComponent( QObject* parent )
    : Component( parent )
    , d( new ScriptingComponentPrivate )
{
}

ScriptingComponent::ScriptingComponent( const ScriptingComponent& other )
    : d( other.d )
{
}

ScriptingComponent::~ScriptingComponent()
{
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
	//DEBUG_FUNC_NAME
    d->scriptingAsset = newAsset;
}

void ScriptingComponent::scriptAssetUpdated()
{
    disconnect( this, SLOT( scriptAssetUpdated() ) );
    setScript( this->script() );
}

QScriptValue ScriptingComponent::scriptObject()
{
    return d->scriptObject;
}

void ScriptingComponent::initialize()
{
	if(!d->scriptingAsset)
		return;
	
	if(!d->scriptingAsset->isLoaded())
		d->scriptingAsset->load();
	
	if(!d->scriptingAsset->isLoaded())
		return;
	
	if(!d->scriptObject.isValid())
	{
		//connect( newAsset, SIGNAL( dataChanged() ), this, SLOT( scriptAssetUpdated() ) );
		d->scriptObject = ScriptingEngine::instance()->instantiateClass( d->scriptingAsset );

		// Set the convenience objects - this allows users to work in a consistent manner, as this needs to be done a lot
		// Technically it could be done by object hierarchy, but consistency is a Good Thing(TM)
		QScriptEngine::QObjectWrapOptions wrapOptions = QScriptEngine::AutoCreateDynamicProperties | QScriptEngine::ExcludeDeleteLater | QScriptEngine::PreferExistingWrapperObject;
		QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership;

		QScriptValue component = ScriptingEngine::instance()->scriptEngine()->newQObject( this, ownership, wrapOptions );
		d->scriptObject.setProperty( "Component", component );

		QScriptValue gameObj = ScriptingEngine::instance()->scriptEngine()->newQObject( gameObject(), ownership, wrapOptions );
		d->scriptObject.setProperty( "GameObject", gameObj );

		QScriptValue sceneObj = ScriptingEngine::instance()->scriptEngine()->newQObject( gameObject()->scene(), ownership, wrapOptions );
		d->scriptObject.setProperty( "Scene", sceneObj );

		QScriptValue gameProjectObj = ScriptingEngine::instance()->scriptEngine()->newQObject( GluonEngine::Game::instance()->gameProject(), ownership, wrapOptions );
		d->scriptObject.setProperty( "GameProject", gameProjectObj );

		QScriptValue game = ScriptingEngine::instance()->scriptEngine()->newQObject( GluonEngine::Game::instance(), ownership, wrapOptions );
		d->scriptObject.setProperty( "Game", game );

		// Lastly, get the functions out so they're easy to call
		d->initializeFunction = d->scriptObject.property( "initialize" );
		d->startFunction = d->scriptObject.property( "start" );
		d->updateFunction = d->scriptObject.property( "update" );
		d->drawFunction = d->scriptObject.property( "draw" );
		d->stopFunction = d->scriptObject.property( "stop" );
		d->cleanupFunction = d->scriptObject.property( "cleanup" );
	}
	
    if( !d->scriptObject.isValid() )
        debug( "Warning: No scripting asset has been chosen" );

    if( d->initializeFunction.isFunction() )
    {
        d->initializeFunction.call( d->scriptObject );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            // This needs to be mapped...
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
            // This needs to be mapped...
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::start();
}

void ScriptingComponent::update( int elapsedMilliseconds )
{
    if( d->updateFunction.isFunction() )
    {
        d->updateFunction.call( d->scriptObject, QScriptValueList() << elapsedMilliseconds );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            // This needs to be mapped...
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::update( elapsedMilliseconds );
}

void ScriptingComponent::draw( int timeLapse )
{
    if( d->drawFunction.isFunction() )
    {
        d->drawFunction.call( d->scriptObject, QScriptValueList() << timeLapse );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            // This needs to be mapped...
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::draw();
}

void ScriptingComponent::stop()
{
    if( d->stopFunction.isFunction() )
    {
        d->stopFunction.call( d->scriptObject );
        if( ScriptingEngine::instance()->scriptEngine()->uncaughtException().isValid() )
            // This needs to be mapped...
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
            // This needs to be mapped...
            debug( QString( "%1: %2" )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtException().toString() )
                   .arg( ScriptingEngine::instance()->scriptEngine()->uncaughtExceptionBacktrace().join( " " ) ) );
    }
    GluonEngine::Component::cleanup();
}

#include "scriptingcomponent.moc"
