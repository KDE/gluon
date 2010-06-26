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

            // A QString with the name of the class represented by a ScriptAsset
            QHash<const ScriptingAsset*, QString> classNames;
            // A QScriptValue per instance of a script, the key being a pointer to the scripted component using it
            QHash<const ScriptingComponent*, QScriptValue> scriptInstances;

            // Contains the full code of all scripts including class wrapping
            // We are going to have a problem with debugging... bugger :P
            QString script;
            void buildScript();
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

QScriptSyntaxCheckResult
ScriptingEngine::registerAsset(const ScriptingAsset* asset)
{
    // Why can't i create my own QScriptSyntaxCheckResult instances and set the values?!

    // Gah, this is really dumb... 
    if(!asset)
        return d->engine->checkSyntax(QString(')'));
    // This is even dumberer...
    if(d->classNames.contains(asset))
        return d->engine->checkSyntax(QString('}'));
    
    // Check the script for syntax
    QScriptSyntaxCheckResult result = d->engine->checkSyntax(asset->data()->text());
    if(result.state() == QScriptSyntaxCheckResult::Valid)
    {
        // Fix up the asset's name so as to be useable as a class name
        QString className(asset->fullyQualifiedName().replace(' ', QString()).replace('/', '_'));
        // Add that to the classes listing
        d->classNames.insert(asset, className);
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
    for(i = classNames.constBegin(); i != classNames.constEnd(); ++i)
    {
        // Build the bit of script to add
        script.append(QString("function %2() {\n%1}\n").arg(i.key()->data()->text()).arg(i.value()));
        /// \TODO Add all those lines to the reverse map...
    }
}

bool
ScriptingEngine::unregisterAsset(const ScriptingAsset* asset) const
{
    
}

bool
ScriptingEngine::isRegistered(const ScriptingAsset* asset) const
{
    return d->classNames.contains(asset);
}

QScriptValue
ScriptingEngine::instantiateClass(const ScriptingAsset* asset) const
{
    // Ensure the asset exists...
    if(d->classNames.contains(asset))
        return QScriptValue(d->engine, QString("new %1").arg(d->classNames.value(asset)));
    // If we've got this far, that means we should be returning an invalid QScriptValue
    return QScriptValue();
}

QScriptValue
ScriptingEngine::instantiateClass(const QString& className) const
{
    return QScriptValue(d->engine, QString("new %1").arg(className));
}

QString
ScriptingEngine::className(const ScriptingAsset* asset) const
{
    return d->classNames.value(asset);
}

QScriptEngine*
ScriptingEngine::scriptEngine() const
{
    return instance()->d->engine;
}


#include "scriptingengine.moc"
