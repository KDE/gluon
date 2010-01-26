cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 REQUIRED)
find_package(Eigen2 REQUIRED)

include_directories(${QT_INCLUDES})
include_directories(${EIGEN2_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(GLUON_VERSION_MAJOR 0)
set(GLUON_VERSION_MINOR 60)
set(GLUON_VERSION_PATCH 0)
set(GLUON_VERSION_STRING "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}")

set(GluonCore_SRCS
    debughelper.cpp
    gdlhandler.cpp
    gluonobject.cpp
    gluonobjectfactory.cpp
    gluonobjectprivate.cpp
)

qt4_automoc(${GluonCore_SRCS})
add_library(GluonCore ${GluonCore_SRCS})

set_target_properties(GluonCore PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING})

install(TARGETS GluonCore DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
install(
    FILES
    debughelper.h
    gdlhandler.h
    gluonobject.h
    gluonobjectfactory.h
    gluonobjectprivate.h
    singleton.h
    gluon_core_export.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/core
    COMPONENT Devel
)

install(
    FILES
    cmake/FindGluonCore.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/gluon/cmake
    COMPONENT Devel
)

install(
    FILES
    cmake/FindGluon.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/modules
    COMPONENT Devel
)
