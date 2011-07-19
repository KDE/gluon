cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    project(GluonCoreTest)
endif()

set(CMAKE_MODULE_PATH ${Gluon_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
)

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

########### next target ###############

#Set the library variable that is needed for the testing
set(GLUON_TEST_LIBS ${GLUON_CORE_LIBS})

GLUON_UNIT_TESTS(
    "gluoncore" # modulename argument
    gluonobjecttest
)
