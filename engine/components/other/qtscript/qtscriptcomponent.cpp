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

void QtScriptComponent::start()
{
    DEBUG_FUNC_NAME
    if (!d->script) return;

    d->script->load();

    if (d->script->data()->hasText())
    {
        d->engine.evaluate(d->script->data()->text(), gameObject()->name());
        if (d->engine.uncaughtException().isValid())
        {
            qDebug() << d->engine.uncaughtException().toString();
            qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
            return;
        }

        QScriptValue component = d->engine.newQObject(this);
        d->engine.globalObject().setProperty("Component", component);

        QScriptValue gameObj = d->engine.newQObject(gameObject());
        d->engine.globalObject().setProperty("GameObject", gameObj);

        QScriptValue game = d->engine.newQObject(Game::instance());
        d->engine.globalObject().setProperty("Game", game);

        d->updateFunc = d->engine.globalObject().property("update");
        d->drawFunc = d->engine.globalObject().property("draw");

        QScriptValue startFunc = d->engine.globalObject().property("start");
        if (startFunc.isFunction())
        {
            startFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
            {
                qDebug() << d->engine.uncaughtException().toString();
                qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
            }
        }
    }
}

void QtScriptComponent::draw(int timeLapse)
{
    d->drawFunc.call(QScriptValue(), QScriptValueList() << timeLapse);
    if (d->engine.uncaughtException().isValid())
    {
        qDebug() << d->engine.uncaughtException().toString();
        qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
    }
}

void QtScriptComponent::update(int elapsedMilliseconds)
{
   d->updateFunc.call(QScriptValue(), QScriptValueList() << elapsedMilliseconds);
    if (d->engine.uncaughtException().isValid())
    {
        qDebug() << d->engine.uncaughtException().toString();
        qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
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

Q_EXPORT_PLUGIN2(gluon_component_qtscript, GluonEngine::QtScriptComponent);

#include "qtscriptcomponent.moc"
