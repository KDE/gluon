cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt4 REQUIRED)
find_package(Eigen2 REQUIRED)

include_directories(${QT_INCLUDES})
include_directories(${EIGEN2_INCLUDE_DIR})

set(GLUON_VERSION_MAJOR 0)
set(GLUON_VERSION_MINOR 60)
set(GLUON_VERSION_PATCH 0)
set(GLUON_VERSION "${GLUON_VERSION_MAJOR}.${GLUON_VERSION_MINOR}.${GLUON_VERSION_PATCH}")

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

set(GluonCore_SRCS
)

qt4_automoc(${GluonCore_SRCS})
add_library(GluonCore ${GluonCore_SRCS})

set_target_properties(GluonCore PROPERTIES VERSION ${GLUON_VERSION} SOVERSION ${GLUON_VERSION})

install(
    FILES
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
    DESTINATION ${CMAKE_MODULE_PATH}
    COMPONENT Devel
)