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

#include <QScriptEngine>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON(ScriptEngine)

void qtscript_initialize_com_trolltech_qt_gui_bindings( QScriptValue& );
class ScriptEngine::Private
{
    public:
        Private()
            : engine(new QScriptEngine())
        {
            DEBUG_FUNC_NAME
            DEBUG_TEXT2( "Available extensions: %1", engine->availableExtensions().join( ", " ) );
            engine->importExtension( "jsmoke.qtcore" );
            engine->importExtension( "jsmoke.qtgui" );
            engine->importExtension( "jsmoke.qtopengl" );
            DEBUG_TEXT2( "Imported extensions: %1", engine->importedExtensions().join( ", " ) );

            qScriptRegisterMetaType( engine, gluonObjectToScriptValue, gluonObjectFromScriptValue );

            QScriptValue extensionObject = engine->globalObject();
            qtscript_initialize_com_trolltech_qt_gui_bindings( extensionObject );

            QScriptValue objectFactory = engine->newQObject( GluonObjectFactory::instance());
            extensionObject.setProperty("ObjectFactory", objectFactory );
        }
        ~Private()
        {
            delete(engine);;
        }
        
        QScriptEngine* engine;
};

