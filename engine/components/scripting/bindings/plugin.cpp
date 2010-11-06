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
#include <QtScript/QScriptExtensionPlugin>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

void qtscript_initialize_com_trolltech_qt_gui_bindings( QScriptValue& );

class com_trolltech_qt_gui_ScriptPlugin : public QScriptExtensionPlugin
{
    public:
        QStringList keys() const;
        void initialize( const QString& key, QScriptEngine* engine );
};

QStringList com_trolltech_qt_gui_ScriptPlugin::keys() const
{
    QStringList list;
    list << QLatin1String( "qt" );
    list << QLatin1String( "qt.gui" );
    return list;
}

void com_trolltech_qt_gui_ScriptPlugin::initialize( const QString& key, QScriptEngine* engine )
{
    if( key == QLatin1String( "qt" ) )
    {
    }
    else if( key == QLatin1String( "qt.gui" ) )
    {
        QScriptValue extensionObject = engine->globalObject();
        qtscript_initialize_com_trolltech_qt_gui_bindings( extensionObject );
    }
    else
    {
        Q_ASSERT_X( false, "com_trolltech_qt_gui::initialize", qPrintable( key ) );
    }
}

Q_EXPORT_STATIC_PLUGIN( com_trolltech_qt_gui_ScriptPlugin )
Q_EXPORT_PLUGIN2( qtscript_com_trolltech_qt_gui, com_trolltech_qt_gui_ScriptPlugin )
