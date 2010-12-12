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

#include "scriptingengine.h"

#include "scriptingasset.h"
#include "scriptingcomponent.h"

#include <QtScript>
// #include <QScriptEngineDebugger>

void qtscript_initialize_com_trolltech_qt_gui_bindings( QScriptValue& );
namespace GluonEngine
{
    class ScriptingEngine::Private
    {
        public:
            Private()
            {
                DEBUG_FUNC_NAME
                DEBUG_TEXT2( "Available extensions: %1", engine->availableExtensions().join( ", " ) );
                engine = new QScriptEngine();
                engine->importExtension( "jsmoke.qtcore" );
                engine->importExtension( "jsmoke.qtgui" );
                engine->importExtension( "jsmoke.qtopengl" );

                qScriptRegisterMetaType( engine, gluonObjectToScriptValue, gluonObjectFromScriptValue );
                qScriptRegisterMetaType( engine, gameObjectToScriptValue, gameObjectFromScriptValue );

                DEBUG_TEXT2( "Imported extensions: %1", engine->importedExtensions().join( ", " ) );

                QScriptValue extensionObject = engine->globalObject();
                qtscript_initialize_com_trolltech_qt_gui_bindings( extensionObject );
            }

            QScriptEngine* engine;
            //             QScriptEngineDebugger* debugger;

            // A QString with the name of the class represented by a ScriptAsset
            QHash<const ScriptingAsset*, QString> classNames;
            // A QScriptValue per script class definition
            QHash<const ScriptingAsset*, QScriptValue> scriptInstances;

            // Contains the full code of all scripts including class wrapping
            // We are going to have a problem with debugging...
            QString script;
            void buildScript();
    };
}

using namespace GluonEngine;

template<> GLUON_ENGINE_EXPORT ScriptingEngine* GluonCore::Singleton<ScriptingEngine>::m_instance = 0;

ScriptingEngine::ScriptingEngine( QObject* parent )
    : d( new Private() )
{
    Q_UNUSED( parent )
}

ScriptingEngine::~ScriptingEngine()
{
    delete d;
}

QScriptSyntaxCheckResult
ScriptingEngine::registerAsset( const ScriptingAsset* asset )
{
    DEBUG_BLOCK
    // Own QScriptSyntaxCheckResult instances and set the values?!

    // Dumb...
    if( !asset )
    {
        DEBUG_TEXT( "Asset is empty" );
        return d->engine->checkSyntax( QString( ')' ) );
    }
    // This is even dumberer...
    if( d->classNames.contains( asset ) )
    {
        DEBUG_TEXT( "Asset is already registered" );
        return d->engine->checkSyntax( QString( '}' ) );
    }

    // Check the script for syntax
    QScriptSyntaxCheckResult result = d->engine->checkSyntax( asset->data()->text() );
    if( result.state() == QScriptSyntaxCheckResult::Valid )
    {
        // Fix up the asset's name so as to be useable as a class name
        QString className( asset->fullyQualifiedName().replace( ' ', QString() ).replace( '/', '_' ) );
        // Add that to the classes listing
        d->classNames.insert( asset, className );
        // Build the new code
        d->buildScript();
    }

    return result;
}

void
ScriptingEngine::Private::buildScript()
{
    script.clear();

    QHash<const ScriptingAsset*, QString>::const_iterator i;
    for( i = classNames.constBegin(); i != classNames.constEnd(); ++i )
    {
        // Build the bit of script to add
        QString tmpScript = QString( "function %2(){\n%1}\n" ).arg( i.key()->data()->text() ).arg( i.value() );
        scriptInstances.insert( i.key(), engine->evaluate( tmpScript, i.key()->file().toLocalFile(), 0 ) );
        /// \TODO Add all those lines to the reverse map...
    }
}

bool
ScriptingEngine::unregisterAsset( const ScriptingAsset* asset ) const
{
    if( !asset )
        return false;
    if( !d->classNames.contains( asset ) )
        return false;

    d->classNames.remove( asset );
    d->scriptInstances.remove( asset );
    d->buildScript();

    return true;
}

bool
ScriptingEngine::isRegistered( const ScriptingAsset* asset ) const
{
    return d->classNames.contains( asset );
}

QScriptValue
ScriptingEngine::instantiateClass( const ScriptingAsset* asset ) const
{
    DEBUG_BLOCK
    // Ensure the asset exists...
    if( d->scriptInstances.contains( asset ) )
    {
        //QScriptValue val = d->scriptInstances[asset].construct();
        QScriptValue val = d->engine->globalObject().property( d->classNames[asset] );

        QScriptValue instance = val.construct();
        if( d->engine->hasUncaughtException() )
        {
            DEBUG_TEXT2( "Exception on class instantiation: %1", d->engine->uncaughtExceptionBacktrace().join( " --> " ) );
        }

        return instance;
    }
    // If we have got this far, that means we should be returning an invalid QScriptValue
    return QScriptValue();
}

QScriptValue
ScriptingEngine::instantiateClass( const QString& className ) const
{
    DEBUG_BLOCK
    QScriptValue val = d->engine->globalObject().property( className );

    QScriptValue instance = val.construct();
    if( d->engine->hasUncaughtException() )
    {
        DEBUG_TEXT2( "Exception on class instantiation: %1", d->engine->uncaughtExceptionBacktrace().join( " --> " ) );
    }

    return instance;
}

QString
ScriptingEngine::className( const ScriptingAsset* asset ) const
{
    return d->classNames.value( asset );
}

QScriptEngine *
ScriptingEngine::scriptEngine() const
{
    return instance()->d->engine;
}

QScriptValue gluonObjectToScriptValue( QScriptEngine* engine, GluonCore::GluonObject* const& in )
{
    return engine->newQObject( in );
}

void gluonObjectFromScriptValue( const QScriptValue& object, GluonCore::GluonObject* &out )
{
    out = qobject_cast<GluonCore::GluonObject*>( object.toQObject() );
}

QScriptValue gameObjectToScriptValue( QScriptEngine* engine, GluonEngine::GameObject* const& in )
{
    return engine->newQObject( in );
}

void gameObjectFromScriptValue( const QScriptValue& object, GluonEngine::GameObject* &out )
{
    out = qobject_cast<GluonEngine::GameObject*>( object.toQObject() );
}

#include "scriptingengine.moc"
