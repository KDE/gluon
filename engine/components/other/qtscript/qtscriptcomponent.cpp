/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "qtscriptcomponent.h"

#include <QtScript/QScriptEngine>

#include <gameobject.h>
#include <core/debughelper.h>

REGISTER_OBJECTTYPE(GluonEngine, QtScriptComponent)

using namespace GluonEngine;

class QtScriptComponent::QtScriptComponentPrivate
{
    public:
        QtScriptComponentPrivate() { }

        QString code;
        QScriptEngine engine;

        QScriptValue script;
};

QtScriptComponent::QtScriptComponent ( QObject* parent ) : Component ( parent )
{
    d = new QtScriptComponentPrivate;
}

QtScriptComponent::QtScriptComponent ( const QtScriptComponent& other )
    : Component ( other ),
    d(other.d)
{
}

QtScriptComponent::~QtScriptComponent()
{

}

GluonCore::GluonObject* QtScriptComponent::instantiate()
{
    return new QtScriptComponent(this);
}

void QtScriptComponent::start()
{
    d->script = d->engine.evaluate(code());
    QScriptValue object = d->engine.newQObject(gameObject());
    d->engine.globalObject().setProperty("gameObject", object);

    QScriptValue startFunc = d->engine.globalObject().property("start");
    if(startFunc.isFunction())
        startFunc.call();
}

void QtScriptComponent::draw ( int timeLapse )
{
    QScriptValue drawFunc = d->engine.globalObject().property("draw");
    if(drawFunc.isFunction())
        drawFunc.call(QScriptValue(), QScriptValueList() << timeLapse);
}

void QtScriptComponent::update ( int elapsedMilliseconds )
{
    QScriptValue updateFunc = d->engine.globalObject().property("update");
    if(updateFunc.isFunction())
        updateFunc.call(QScriptValue(), QScriptValueList() << elapsedMilliseconds);
}

QString QtScriptComponent::code()
{
    return d->code;
}

void QtScriptComponent::setCode(const QString& code)
{
    d->code = code;
}

Q_EXPORT_PLUGIN2(gluon_component_qtscript, GluonEngine::QtScriptComponent);

#include "qtscriptcomponent.moc"
