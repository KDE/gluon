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

#include "scriptingcomponentprivate.h"
#include "scriptingengine.h"

#include "game.h"
#include "gameobject.h"

using namespace GluonEngine;

ScriptingComponent::ScriptingComponentPrivate::ScriptingComponentPrivate( ScriptingComponent* qq )
    : q( qq ), scriptingAsset( 0 )
{
}

ScriptingComponent::ScriptingComponentPrivate::~ScriptingComponentPrivate()
{
}

void ScriptingComponent::ScriptingComponentPrivate::updateScriptObject()
{
    QScriptEngine* engine = ScriptingEngine::instance()->scriptEngine();

    scriptObject = ScriptingEngine::instance()->instantiateClass( scriptingAsset );

    // Set the convenience objects - this allows users to work in a consistent manner, as this needs to be done a lot
    // Technically it could be done by object hierarchy, but consistency is a Good Thing(TM)
    QScriptEngine::QObjectWrapOptions wrapOptions = QScriptEngine::AutoCreateDynamicProperties | QScriptEngine::ExcludeDeleteLater | QScriptEngine::PreferExistingWrapperObject;
    QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership;

    QScriptValue component = engine->newQObject( q, ownership, wrapOptions );
    scriptObject.setProperty( "Component", component );

    QScriptValue gameObj = engine->newQObject( q->gameObject(), ownership, wrapOptions );
    scriptObject.setProperty( "GameObject", gameObj );

    QScriptValue sceneObj = engine->newQObject( q->gameObject()->scene(), ownership, wrapOptions );
    scriptObject.setProperty( "Scene", sceneObj );

    QScriptValue gameProjectObj = engine->newQObject( GluonEngine::Game::instance()->gameProject(), ownership, wrapOptions );
    scriptObject.setProperty( "GameProject", gameProjectObj );

    QScriptValue debugFunc = engine->newFunction( debug );
    scriptObject.setProperty( "debug", debugFunc );

    // Lastly, get the functions out so they're easy to call
    initializeFunction = scriptObject.property( "initialize" );
    startFunction = scriptObject.property( "start" );
    updateFunction = scriptObject.property( "update" );
    drawFunction = scriptObject.property( "draw" );
    stopFunction = scriptObject.property( "stop" );
    cleanupFunction = scriptObject.property( "cleanup" );
}

QScriptValue ScriptingComponent::ScriptingComponentPrivate::debug( QScriptContext* context, QScriptEngine* /* engine */ )
{
    QScriptValue callee = context->callee();
    if( context->argumentCount() == 1 )
    {
        Component* comp = qobject_cast< GluonEngine::Component* >( context->thisObject().property( "Component" ).toQObject() );
        if( comp )
            comp->debug( context->argument( 0 ).toString() );
    }
    else if( context->argumentCount() == 2 )
    {
        Component* comp = qobject_cast< GluonEngine::Component* >( context->thisObject().property( "Component" ).toQObject() );
        if( comp )
            comp->debug( context->argument( 0 ).toString(), context->argument( 1 ).toString() );
    }
    return QScriptValue();
}
