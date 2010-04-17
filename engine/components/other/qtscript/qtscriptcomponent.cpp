/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <>
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

#include "qtscriptcomponent.h"

#include <QtScript/QScriptEngine>
#include <QtCore/QDebug>

#include <gameobject.h>
#include <core/debughelper.h>
#include <game.h>
#include <engine/asset.h>
#include <QMimeData>

#include <core/gluonobject.h>

REGISTER_OBJECTTYPE(GluonEngine, QtScriptComponent)

using namespace GluonEngine;

void qtscript_initialize_com_trolltech_qt_gui_bindings(QScriptValue &);
class QtScriptComponent::QtScriptComponentPrivate
{
    public:
        QtScriptComponentPrivate()
        {
            QScriptValue extensionObject = engine.globalObject();
            qtscript_initialize_com_trolltech_qt_gui_bindings(extensionObject);
            script = 0;
        }

        QScriptEngine engine;

        QScriptValue drawFunc;
        QScriptValue updateFunc;

        GluonEngine::Asset* script;
};

QtScriptComponent::QtScriptComponent(QObject* parent) : Component(parent)
{
    d = new QtScriptComponentPrivate;
    
    qScriptRegisterMetaType(&d->engine, gluonObjectToScriptValue, gluonObjectFromScriptValue);
    qScriptRegisterMetaType(&d->engine, gameObjectToScriptValue, gameObjectFromScriptValue);
}

QtScriptComponent::QtScriptComponent(const QtScriptComponent& other)
        : Component(other),
        d(other.d)
{
}

QtScriptComponent::~QtScriptComponent()
{
    delete d;
}

void QtScriptComponent::initialize()
{
    if (!d->script) return;

    d->script->load();

    if (d->script->data()->hasText())
    {
        d->engine.evaluate(d->script->data()->text(), gameObject()->name());
        if (d->engine.uncaughtException().isValid())
        {
            debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
            return;
        }

        QScriptValue component = d->engine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
        d->engine.globalObject().setProperty("Component", component);

        QScriptValue gameObj = d->engine.newQObject(gameObject(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
        d->engine.globalObject().setProperty("GameObject", gameObj);

        QScriptValue game = d->engine.newQObject(Game::instance(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
        d->engine.globalObject().setProperty("Game", game);

        d->updateFunc = d->engine.globalObject().property("update");
        d->drawFunc = d->engine.globalObject().property("draw");
        
        QScriptValue initFunc = d->engine.globalObject().property("initialize");
        if (initFunc.isFunction())
        {
            initFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
        }
    }
}

void QtScriptComponent::start()
{
    if(d->script)
    {
        QScriptValue startFunc = d->engine.globalObject().property("start");
        if (startFunc.isFunction())
        {
            startFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
        }
    }
}

void QtScriptComponent::draw(int timeLapse)
{
    if(d->drawFunc.isFunction())
    {
        d->drawFunc.call(QScriptValue(), QScriptValueList() << timeLapse);
        if (d->engine.uncaughtException().isValid())
            debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
    }
}

void QtScriptComponent::update(int elapsedMilliseconds)
{
    if(d->updateFunc.isFunction())
    {
        d->updateFunc.call(QScriptValue(), QScriptValueList() << elapsedMilliseconds);
        if (d->engine.uncaughtException().isValid())
            debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
    }
}

void QtScriptComponent::stop()
{
    if(d->script)
    {
        QScriptValue stopFunc = d->engine.globalObject().property("stop");
        if (stopFunc.isFunction())
        {
            stopFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
        }
    }
}

void QtScriptComponent::cleanup()
{
    if(d->script)
    {
        QScriptValue cleanupFunc = d->engine.globalObject().property("cleanup");
        if (cleanupFunc.isFunction())
        {
            cleanupFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
        }
    }
}

Asset* QtScriptComponent::script()
{
    return d->script;
}

void QtScriptComponent::setScript(Asset* asset)
{
    d->script = asset;
}

QScriptValue gluonObjectToScriptValue(QScriptEngine *engine, const pGluonObject &in)
{ 
    return engine->newQObject(in); 
}

void gluonObjectFromScriptValue(const QScriptValue &object, pGluonObject &out)
{ 
    out = qobject_cast<GluonCore::GluonObject*>(object.toQObject()); 
}

QScriptValue gameObjectToScriptValue(QScriptEngine *engine, const pGameObject &in)
{ 
    return engine->newQObject(in); 
}

void gameObjectFromScriptValue(const QScriptValue &object, pGameObject &out)
{ 
    out = qobject_cast<GameObject*>(object.toQObject()); 
}

Q_EXPORT_PLUGIN2(gluon_component_qtscript, GluonEngine::QtScriptComponent);

#include "qtscriptcomponent.moc"
