/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "scriptengine.h"

#include "gluonobjectfactory.h"
#include "gluonobject.h"
#include "messagehandler.h"

#include <QtScript/QScriptEngine>

void qtscript_initialize_com_trolltech_qt_gui_bindings( QScriptValue& );
namespace GluonCore
{
    class ScriptEngine::Private
    {
        public:
            Private()
                : engine(0)
            {}
            ~Private()
            {}

            QScriptEngine* engine;
    };
}

using namespace GluonCore;

GLUON_DEFINE_SINGLETON(ScriptEngine)

ScriptEngine::ScriptEngine(QObject* /* parent */ )
    : d(new Private())
{
}

ScriptEngine::~ScriptEngine()
{
    delete(d);
}

QScriptEngine* ScriptEngine::scriptEngine()
{
    DEBUG_BLOCK
    if(QCoreApplication::instance() && !d->engine)
    {
        d->engine = new QScriptEngine(this);
        d->engine->importExtension( "jsmoke.qtcore" );
        d->engine->importExtension( "jsmoke.qtgui" );
        d->engine->importExtension( "jsmoke.qtopengl" );

        QScriptValue extensionObject = d->engine->globalObject();
        qtscript_initialize_com_trolltech_qt_gui_bindings( extensionObject );

        QScriptEngine::QObjectWrapOptions wrapOptions = QScriptEngine::AutoCreateDynamicProperties | QScriptEngine::ExcludeDeleteLater | QScriptEngine::PreferExistingWrapperObject;
        QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership;

        QScriptValue objectFactory = d->engine->newQObject( GluonObjectFactory::instance(), ownership, wrapOptions);
        extensionObject.setProperty("ObjectFactory", objectFactory );

        QScriptValue messageHandler = d->engine->newQObject( MessageHandler::instance(), ownership, wrapOptions);
        extensionObject.setProperty("MessageHandler", messageHandler);

        // Finally, register all the objects in the factory...
        QHash<QString, const QMetaObject*> types = GluonObjectFactory::instance()->objectTypes();
        QHash<QString, const QMetaObject*>::const_iterator i;
        for( i = types.constBegin(); i != types.constEnd(); ++i)
        {
            QObject* obj = i.value()->newInstance();
            if(qobject_cast<GluonCore::GluonObject*>(obj))
            {
                qobject_cast<GluonCore::GluonObject*>(obj)->registerOnScriptEngine(d->engine);;
            }
            delete(obj);
        }
    }
    return d->engine;
}

void ScriptEngine::resetEngine()
{
    if(d->engine)
    {
        delete(d->engine);
        d->engine = 0;
    }
}

#include "scriptengine.moc"
