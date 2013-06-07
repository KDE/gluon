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

// This file adapted from QtScript bindings generator code

#include <QtQml/QJSEngine>
#include <QtQml/QJSValue>

// QScriptValue qtscript_create_Vector2f_class( QScriptEngine* engine );
// QScriptValue qtscript_create_Vector3f_class( QScriptEngine* engine );
// QScriptValue qtscript_create_Vector4f_class( QScriptEngine* engine );
// QScriptValue qtscript_create_QColor_class( QScriptEngine* engine );
// QScriptValue qtscript_create_Quaternionf_class( QScriptEngine* engine );
// QScriptValue qtscript_create_QSizeF_class( QScriptEngine* engine );

QJSValue qtscript_create_QVector2D_class( QJSEngine* engine );
QJSValue qtscript_create_QVector3D_class( QJSEngine* engine );
QJSValue qtscript_create_QVector4D_class( QJSEngine* engine );
QJSValue qtscript_create_QColor_class( QJSEngine* engine );
QJSValue qtscript_create_QQuaternion_class( QJSEngine* engine );
QJSValue qtscript_create_QSizeF_class( QJSEngine* engine );

static const char* const qtscript_com_trolltech_qt_gui_class_names[] =
{
    "Vector2f"
    , "Vector3f"
    , "Vector4f"
    , "QColor"
    , "Quaternionf"
    , "QSizeF"
};

typedef QJSValue( *QtBindingCreator )( QJSEngine* engine );
static const QtBindingCreator qtscript_com_trolltech_qt_gui_class_functions[] =
{
    qtscript_create_Vector2f_class
    , qtscript_create_Vector3f_class
    , qtscript_create_Vector4f_class
    , qtscript_create_QColor_class
    , qtscript_create_Quaternionf_class
    , qtscript_create_QSizeF_class
};

void qtscript_initialize_com_trolltech_qt_gui_bindings( QJSValue& extensionObject )
{
    QJSEngine* engine = extensionObject.engine();
    for( int i = 0; i < 6; ++i )
    {
        extensionObject.setProperty( qtscript_com_trolltech_qt_gui_class_names[i],
                                     qtscript_com_trolltech_qt_gui_class_functions[i]( engine ) );
    }
}
