cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    project(GluonTest)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(KDE4 REQUIRED)
find_package(Qt4 4.6 REQUIRED)

include_directories(${QT_INCLUDES})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core)

#include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(GluonTest_SRCS
    main.cpp
    comparison.cpp
    GDLHandler.cpp
)

set(GluonTest_HDRS
    TestGluonCore.h
)

qt4_automoc(${GluonTest_HDRS})

kde4_add_executable(GluonTest ${GluonTest_SRCS})
target_link_libraries(GluonTest GluonCore ${QT_QTTEST_LIBRARY})
