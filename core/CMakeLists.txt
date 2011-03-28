cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonCore)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 4.6 REQUIRED)

set(_Init_LIB_SUFFIX "")
if ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
   set(_Init_LIB_SUFFIX 64)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib64)
if ("${QT_QTCORE_LIBRARY}" MATCHES lib32)
   set(_Init_LIB_SUFFIX 32)
endif ("${QT_QTCORE_LIBRARY}" MATCHES lib32)

set(LIB_SUFFIX		    ${_Init_LIB_SUFFIX} CACHE STRING "The suffix of the system-wide library path")

set(GLUON_VERSION_MAJOR     0       CACHE STRING "Gluon Major Version")
set(GLUON_VERSION_MINOR     71      CACHE STRING "Gluon Minor Version")
set(GLUON_VERSION_PATCH     0       CACHE STRING "Gluon Patch Version")
set(GLUON_VERSION_STRING    "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}" CACHE STRING "Gluon Version String")
set(GLUON_VERSION_NAME      "Electron" CACHE STRING "Gluon Version Name")

set(INCLUDE_INSTALL_DIR     ${CMAKE_INSTALL_PREFIX}/include             CACHE PATH "The subdirectory relative to the install prefix where header files will be installed.")
set(LIB_INSTALL_DIR         ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}    CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed.")
set(SHARE_INSTALL_DIR       ${CMAKE_INSTALL_PREFIX}/share               CACHE PATH "The subdiractory relative to the install prefix where data and other files will be installed.")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gluon_global.h.in ${CMAKE_CURRENT_BINARY_DIR}/gluon_global.h)

include_directories(${QT_INCLUDES})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(GLUON_CORE_INCLUDES
    ${QT_INCLUDES}
    CACHE PATHS "Includes required for Gluon Core"
)

set(GluonCore_SRCS
    debughelper.cpp
    gdlhandler.cpp
    messagehandler.cpp
    metainfo.cpp
    gluonobject.cpp
    gluonobjectfactory.cpp
    scriptengine.cpp

    bindings/com_trolltech_qt_gui_init.cpp
    bindings/qtscript_QVector2D.cpp
    bindings/qtscript_QVector3D.cpp
    bindings/qtscript_QVector4D.cpp
    bindings/qtscript_QColor.cpp
    bindings/qtscript_QQuaternion.cpp
)

set(GluonCore_HEADERS
    debughelper.h
    gdlhandler.h
    metainfo.h
    messagehandler.h
    gluonobject.h
    gluonobjectfactory.h
    singleton.h
    scriptengine.h
    gluon_core_export.h
    gluonvarianttypes.h

    ${CMAKE_CURRENT_BINARY_DIR}/gluon_global.h
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
    CACHE PATHS "Libraries required for Gluon Core"
)

set_target_properties(GluonCore PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_CORE_LIB)

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

install(TARGETS GluonCore RUNTIME DESTINATION bin LIBRARY DESTINATION ${LIB_INSTALL_DIR} ARCHIVE DESTINATION ${LIB_INSTALL_DIR} FRAMEWORK DESTINATION ${LIB_INSTALL_DIR})

install(
    FILES
    ${GluonCore_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/core
    COMPONENT Devel
)
