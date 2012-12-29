cmake_minimum_required(VERSION 2.8)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gdl
)

set(GLUON_CORE_INCLUDE_DIRS
    ${QT_INCLUDES}
    CACHE INTERNAL "Includes required for Gluon Core"
)

add_subdirectory(examples)

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
    bindings/qtscript_QQuaternion.cpp
    bindings/qtscript_QVector2D.cpp
    bindings/qtscript_QVector3D.cpp
    bindings/qtscript_QVector4D.cpp

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
    gluon_core_export.h
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

qt4_automoc(${GluonCore_SRCS})

if(APPLE)
    add_library(GluonCore SHARED ${GluonCore_SRCS} ${GluonCore_HEADERS})
else()
    add_library(GluonCore SHARED ${GluonCore_SRCS})
endif()

target_link_libraries(GluonCore ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSCRIPT_LIBRARY})

set(GLUON_CORE_LIBS
    GluonCore
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTSCRIPT_LIBRARY}
    CACHE INTERNAL "Libraries required for Gluon Core"
)

set_target_properties(GluonCore PROPERTIES BUILD_WITH_INSTALL_RPATH 1 VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_CORE_LIB)

if(APPLE)
    #hack for being able to set headers as public in a osx framework
    list(APPEND GluonCore_HEADERS
        ${GluonCore_HEADERS}
    )

    set_target_properties(GluonCore PROPERTIES FRAMEWORK TRUE)
    set_target_properties(GluonCore PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonCore PROPERTIES PUBLIC_HEADER "${GluonCore_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER core)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

install(TARGETS GluonCore
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT gluoncore
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluoncore
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluoncore
    FRAMEWORK DESTINATION ${LIB_INSTALL_DIR} COMPONENT gluoncore
)

install(FILES ${GluonCore_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/core
    COMPONENT gluoncore
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
