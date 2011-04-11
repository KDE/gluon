cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    project(GluonCoreTest)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(GluonCoreTest_SRCS
    main.cpp
    testgluoncore.cpp
)

set(GluonCoreTest_HDRS
    testgluoncore.h
)

qt4_automoc(${GluonCoreTest_SRCS})

add_executable(GluonCoreTest ${GluonCoreTest_SRCS})
target_link_libraries(GluonCoreTest GluonCore ${QT_QTTEST_LIBRARY} ${GLUON_CORE_LIBS})
