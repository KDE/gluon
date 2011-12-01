cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    project(GluonCoreTest)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDE_DIRS}
)

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_CORE_LIBS}"    # libraries arguement
    "gluoncore"             # modulename argument

    # Source files without the extension
    #gdlhandlertest
    gluonobjecttest
    metainfotest
)
