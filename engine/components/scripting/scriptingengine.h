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

#ifndef GLUONENGINE_SCRIPTINGENGINE_H
#define GLUONENGINE_SCRIPTINGENGINE_H

#include "gluon_engine_export.h"
#include "gameobject.h"

#include <core/singleton.h>

#include <QScriptValue>
#include <QScriptEngine>

namespace GluonEngine
{
    class ScriptingAsset;
    class GLUON_ENGINE_EXPORT ScriptingEngine : public GluonCore::Singleton<ScriptingEngine>
    {
            Q_OBJECT

        public Q_SLOTS:
            /**
             * Register the passed asset with the engine, thus allowing people to instantiate the classes it represents
             * @param   asset   The asset to be registered
             * @return The check result returned by the engine upon checking the syntax of the script
             */
            QScriptSyntaxCheckResult registerAsset( const GluonEngine::ScriptingAsset* asset );
            /**
             * Unregister the passed asset with the engine
             * @param   asset   The asset to unregister
             * @return  True if the asset was successfully unregistered. False is returned when the asset is not registered, or if the passed asset was not valid
             */
            bool unregisterAsset( const GluonEngine::ScriptingAsset* asset ) const;
            /**
             * Check whether an asset is registered with the engine.
             * @param   asset   The asset to check on
             * @return True if asset is registered with the engine, false if not
             */
            bool isRegistered( const GluonEngine::ScriptingAsset* asset ) const;

            /**
             * Get the class name for the class represented by the passed asset
             * @return A string containing the class name of a specified asset
             */
            QString className( const GluonEngine::ScriptingAsset* asset ) const;
            /**
             * Return a QtScript instance of the class represented by the passed asset
             * @param   asset   The asset representing the class you wish to get an instance of
             * @return An instance of the class, or an invalid QScriptValue if the asset did not represent a valid class
             */
            QScriptValue instantiateClass( const GluonEngine::ScriptingAsset* asset ) const;
            /**
             * Return a QtScript instance of the class named className
             * @param   className   The name of the class you wish to instantiate an instance of
             * @return  An instance of the class, or an invalid QScriptValue if there is no class registered with the passed name
             */
            QScriptValue instantiateClass( const QString& className ) const;

            QScriptEngine* scriptEngine() const;

        private:
            friend class GluonCore::Singleton<ScriptingEngine>;

            ScriptingEngine( QObject* parent = 0 );
            ~ScriptingEngine();

            Q_DISABLE_COPY( ScriptingEngine );

            class Private;
            Private* d;
    };
}

QScriptValue GLUON_ENGINE_EXPORT gameObjectToScriptValue( QScriptEngine* engine, GluonEngine::GameObject* const& in );
void GLUON_ENGINE_EXPORT gameObjectFromScriptValue( const QScriptValue& object, GluonEngine::GameObject *&out );
QScriptValue GLUON_ENGINE_EXPORT gluonObjectToScriptValue( QScriptEngine* engine, GluonCore::GluonObject* const& in );
void GLUON_ENGINE_EXPORT gluonObjectFromScriptValue( const QScriptValue& object, GluonCore::GluonObject*& out );

#endif // GLUONENGINE_SCRIPTINGENGINE_H
