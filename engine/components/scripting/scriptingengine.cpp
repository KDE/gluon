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

#include <QtScript>
// #include <QScriptEngineDebugger>
#include "scriptingasset.h"
#include "scriptingcomponent.h"

namespace GluonEngine
{
    class ScriptingEngine::Private
    {
        public:
            Private()
            {
                engine = new QScriptEngine();
                engine->importExtension("jsmoke.qtcore");
                engine->importExtension("jsmoke.qtgui");
                engine->importExtension("jsmoke.qtopengl");

                QScriptValue extensionObject = engine->globalObject();
            }

            QScriptEngine* engine;
//             QScriptEngineDebugger* debugger;

            // A QScriptValue per instance of a script, the key being a pointer to the scripted component using it
            QHash<ScriptingComponent*, QScriptValue> scriptInstances;
    };
}

using namespace GluonEngine;

template<> GLUON_ENGINE_EXPORT ScriptingEngine *GluonCore::Singleton<ScriptingEngine>::m_instance = 0;

ScriptingEngine::ScriptingEngine(QObject* parent)
    : d(new Private())
{
    Q_UNUSED(parent)
}

ScriptingEngine::~ScriptingEngine()
{
    delete(d);
}

bool
ScriptingEngine::registerAsset(ScriptingAsset* asset)
{
}

bool
ScriptingEngine::unregisterAsset(ScriptingAsset* asset)
{
    
}

bool
ScriptingEngine::isRegistered(ScriptingAsset* asset)
{

}

QScriptValue
ScriptingEngine::instantiateClass(ScriptingAsset* asset) const
{

}

QString
ScriptingEngine::className(ScriptingAsset* asset) const
{

}

QScriptEngine*
ScriptingEngine::scriptEngine() const
{

}

#include "scriptingengine.moc"
