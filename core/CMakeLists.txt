gluon_include_directories( GluonCore
    ${QT_INCLUDES}
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/gdl )

set(GluonCore_SRCS
    axisalignedbox.cpp
    directoryprovider.cpp
    debughelper.cpp
    gluonobject.cpp
    gluonobjectfactory.cpp
    messagehandler.cpp
    metainfo.cpp
    referencecounter.cpp
    scriptengine.cpp
    gdlserializer.cpp

    bindings/com_trolltech_qt_gui_init.cpp
    bindings/qtscript_QColor.cpp
    bindings/qtscript_QSizeF.cpp
    bindings/qtscript_Quaternionf.cpp
    bindings/qtscript_Vector2f.cpp
    bindings/qtscript_Vector3f.cpp
    bindings/qtscript_Vector4f.cpp

    gdl/gdllexer.cpp
    gdl/gdlparser.cpp
    gdl/gdlvisitor.cpp
    gdl/gdldefaultvisitor.cpp
    gdl/objecttreebuilder.cpp
    gdl/writer.cpp
)

set(GluonCore_HEADERS
    axisalignedbox.h
    debughelper.h
    gluoncore_export.h
    gluonobject.h
    gluonobjectfactory.h
    gluonvarianttypes.h
    messagehandler.h
    metainfo.h
    referencecounter.h
    scriptengine.h
    singleton.h
    gdlserializer.h
)

gluon_add_library(GluonCore SHARED
    SOURCES ${GluonCore_SRCS}
    HEADERS ${GluonCore_HEADERS}
    LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSCRIPT_LIBRARY}
)

gluon_add_subdirectories(examples tests)