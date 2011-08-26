cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    project(GluonCore)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 4.6 REQUIRED)

if ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
   set(_Init_LIB_SUFFIX 64)
elseif ("${QT_QTCORE_LIBRARY}" MATCHES lib32)
   set(_Init_LIB_SUFFIX 32)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib64)

set(LIB_SUFFIX		${_Init_LIB_SUFFIX}                      CACHE INTERNAL      "The suffix of the system-wide library path")

set(BIN_INSTALL_DIR     bin              CACHE INTERNAL "The subdirectory relative to the install prefix where binary files will be installed.")
set(INCLUDE_INSTALL_DIR include          CACHE INTERNAL "The subdirectory relative to the install prefix where header files will be installed.")
set(LIB_INSTALL_DIR     lib${LIB_SUFFIX} CACHE INTERNAL "The subdirectory relative to the install prefix where libraries will be installed.")
set(SHARE_INSTALL_DIR   share            CACHE INTERNAL "The subdiractory relative to the install prefix where data and other files will be installed.")

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( GLUON_ARCHITECTURE "64" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( GLUON_ARCHITECTURE "32" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gluon_global.h.in ${CMAKE_CURRENT_BINARY_DIR}/gluon_global.h)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gdl
)

set(GLUON_CORE_INCLUDES
    ${QT_INCLUDES}
    CACHE INTERNAL "Includes required for Gluon Core"
)

add_subdirectory(examples)

set(GluonCore_SRCS
    directoryprovider.cpp
    debughelper.cpp
    gdlhandler.cpp
    gluonobject.cpp
    gluonobjectfactory.cpp
    messagehandler.cpp
    metainfo.cpp
    referencecounter.cpp
    scriptengine.cpp

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
)

set(GluonCore_HEADERS
    debughelper.h
    gdlhandler.h
    gluon_core_export.h
    gluonobject.h
    gluonobjectfactory.h
    gluonvarianttypes.h
    messagehandler.h
    metainfo.h
    referencecounter.h
    scriptengine.h
    singleton.h

    ${CMAKE_CURRENT_BINARY_DIR}/gluon_global.h
)

set(GluonCore_GDL_HEADERS
    gdl/gdlparser.h
    gdl/gdllexer.h
    gdl/gdldefaultvisitor.h
    gdl/gdlvisitor.h
    gdl/gdlast.h
    gdl/gdlast-fwd.h
    gdl/kdev-pg-list.h
    gdl/kdev-pg-allocator.h
    gdl/kdev-pg-char-sets.h
    gdl/kdev-pg-token-stream.h
    gdl/kdev-pg-memory-pool.h
    gdl/kdev-pg-location-table.h
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

install(FILES ${GluonCore_GDL_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/core/gdl
    COMPONENT gluoncore
)

if(BUILD_GLUON_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
