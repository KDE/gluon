#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QVector2D_class(QScriptEngine *engine);
QScriptValue qtscript_create_QVector3D_class(QScriptEngine *engine);
QScriptValue qtscript_create_QVector4D_class(QScriptEngine *engine);
QScriptValue qtscript_create_QColor_class(QScriptEngine *engine);
QScriptValue qtscript_create_QQuaternion_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_gui_class_names[] = {
    "QVector2D"
    , "QVector3D"
    , "QVector4D"
    , "QColor"
    , "QQuaternion"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_gui_class_functions[] = {
    qtscript_create_QVector2D_class
    , qtscript_create_QVector3D_class
    , qtscript_create_QVector4D_class
    , qtscript_create_QColor_class
    , qtscript_create_QQuaternion_class
};

void qtscript_initialize_com_trolltech_qt_gui_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 5; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_gui_class_names[i],
            qtscript_com_trolltech_qt_gui_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
