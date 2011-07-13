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

#include "game.h"
#include "scriptingasset.h"
#include "scriptingcomponent.h"

#include <core/gluonobjectfactory.h>
#include <core/scriptengine.h>

#include <QtScript>
// #include <QScriptEngineDebugger>

namespace GluonEngine
{
    class ScriptingEngine::Private
    {
        public:
            Private()
                : theEngine( 0 )
            {
            }

            void resetEngine()
            {
                theEngine = 0;
                GluonCore::ScriptEngine::instance()->resetEngine();
            }
            QScriptEngine* engine()
            {
                if( !theEngine )
                {
                    theEngine = GluonCore::ScriptEngine::instance()->scriptEngine();

                    QScriptEngine::QObjectWrapOptions wrapOptions = QScriptEngine::AutoCreateDynamicProperties | QScriptEngine::ExcludeDeleteLater | QScriptEngine::PreferExistingWrapperObject;
                    QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership;
                    QScriptValue game = ScriptingEngine::instance()->scriptEngine()->newQObject( GluonEngine::Game::instance(), ownership, wrapOptions );
                    theEngine->globalObject().setProperty( "Game", game );
                }
                if( !theEngine )
                {
                    DEBUG_BLOCK
                    DEBUG_TEXT( "Somehow we do not have a scripting engine. This will cause crashes!" )
                }
                return theEngine;
            }
            QScriptEngine* theEngine;
            //             QScriptEngineDebugger* debugger;

            // A QString with the name of the class represented by a ScriptAsset
            QHash<const ScriptingAsset*, QString> classNames;
            // A QScriptValue per script class definition
            QHash<const ScriptingAsset*, QScriptValue> scriptInstances;

            // Contains the full code of all scripts including class wrapping
            // We are going to have a problem with debugging...
            QString script;
            void buildScript();
            void appendScript( const ScriptingAsset* asset, QString name );
    };
}

using namespace GluonEngine;

GLUON_DEFINE_SINGLETON( ScriptingEngine )

ScriptingEngine::ScriptingEngine( QObject* /* parent */ )
    : d( new Private() )
{
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
        DEBUG_TEXT( "Asset is empty" )
        return d->engine()->checkSyntax( QString( ')' ) );
    }
    // This is even dumberer...
    if( d->classNames.contains( asset ) )
    {
        DEBUG_TEXT( "Asset is already registered" )
        return d->engine()->checkSyntax( QString( '}' ) );
    }

    // Check the script for syntax
    QScriptSyntaxCheckResult result = d->engine()->checkSyntax( asset->data()->text() );
    if( result.state() == QScriptSyntaxCheckResult::Valid )
    {
        // Fix up the asset's name so as to be useable as a class name
        QString className( asset->fullyQualifiedName().remove( ' ' ).replace( '/', '_' ).replace( '-', '_' ) );
        // Add that to the classes listing
        d->classNames.insert( asset, className );
        // Build the new code
        d->appendScript( asset, className );
        //d->buildScript();
    }
    else
    {
        asset->debug( QString( "This script didn't pass the syntax checker (%2)\n" )
                      .arg( asset->fullyQualifiedName() )
                      .arg( result.errorMessage() ) );
    }

    return result;
}

void
ScriptingEngine::Private::buildScript()
{
    script.clear();
    resetEngine();

    QHash<const ScriptingAsset*, QString>::const_iterator i;
    for( i = classNames.constBegin(); i != classNames.constEnd(); ++i )
    {
        appendScript( i.key(), i.value() );
    }
}

void
ScriptingEngine::Private::appendScript( const GluonEngine::ScriptingAsset* asset, QString name )
{
    // Build the bit of script to add
    QString tmpScript = QString( "%2 = function() {\n%1};\n" ).arg( asset->data()->text() ).arg( name );
    QUrl tmpUrl = asset->file();
    QScriptValue evaluated = engine()->evaluate( tmpScript, tmpUrl.toLocalFile(), 0 );
    scriptInstances.insert( asset, evaluated );
    /// \TODO Add all those lines to the reverse map...
}

bool
ScriptingEngine::unregisterAsset( const ScriptingAsset* asset )
{
    if( !asset )
        return false;
    if( !d->classNames.contains( asset ) )
        return false;

    d->classNames.remove( asset );
    d->scriptInstances.remove( asset );
    if( d->scriptInstances.count() < 1 )
        d->resetEngine();
    else
        QTimer::singleShot(0, this, SLOT(buildScript()));

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
        QScriptValue val = d->engine()->globalObject().property( d->classNames.value( asset ) );

        QScriptValue instance = val.construct();
        if( d->engine()->hasUncaughtException() )
        {
            QScriptValue exception = d->engine()->uncaughtException();
            asset->debug( QString( "Exception on class instantiation: %2\n at %1" )
                          .arg( d->engine()->uncaughtExceptionBacktrace().join( " --> " ) )
                          .arg( exception.toString() ) );
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
    QScriptValue val = d->engine()->globalObject().property( className );

    QScriptValue instance = val.construct();
    if( d->engine()->hasUncaughtException() )
    {
        const ScriptingAsset* asset = d->classNames.key( className );
        QScriptValue exception = d->engine()->uncaughtException();
        asset->debug( QString( "Exception on class instantiation: %2\n at %1" )
                      .arg( d->engine()->uncaughtExceptionBacktrace().join( " --> " ) )
                      .arg( exception.toString() ) );
    }

    return instance;
}

QString
ScriptingEngine::className( const ScriptingAsset* asset ) const
{
    return d->classNames.value( asset );
}

QScriptEngine*
ScriptingEngine::scriptEngine() const
{
    return d->engine();
}

#include "scriptingengine.moc"
