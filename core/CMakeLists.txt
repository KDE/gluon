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
set(GLUON_VERSION_MINOR     69      CACHE STRING "Gluon Minor Version")
set(GLUON_VERSION_PATCH     0       CACHE STRING "Gluon Patch Version")
set(GLUON_VERSION_STRING    "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}" CACHE STRING "Gluon Version String")
set(GLUON_VERSION_NAME      "X-Ray" CACHE STRING "Gluon Version Name")

set(INCLUDE_INSTALL_DIR     ${CMAKE_INSTALL_PREFIX}/include             CACHE PATH "The subdirectory relative to the install prefix where header files will be installed.")
set(LIB_INSTALL_DIR         ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}    CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed.")
set(SHARE_INSTALL_DIR       ${CMAKE_INSTALL_PREFIX}/share               CACHE PATH "The subdiractory relative to the install prefix where data and other files will be installed.")

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
    gluonobject.cpp
    gluonobjectfactory.cpp
    gluonobjectprivate.cpp
)

qt4_automoc(${GluonCore_SRCS})
add_library(GluonCore SHARED ${GluonCore_SRCS})

target_link_libraries(GluonCore ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

set(GLUON_CORE_LIBS
    GluonCore
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    CACHE PATHS "Libraries required for Gluon Core"
)

set_target_properties(GluonCore PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

install(TARGETS GluonCore DESTINATION ${LIB_INSTALL_DIR})

install(
    FILES
    debughelper.h
    gdlhandler.h
    gluonobject.h
    gluonobjectfactory.h
    gluonobjectprivate.h
    singleton.h
    gluon_core_export.h
	gluonvarianttypes.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/core
    COMPONENT Devel
)

install(
    FILES
    cmake/FindGluon.cmake
    cmake/FindGluonCore.cmake
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/cmake
    COMPONENT Devel
)
