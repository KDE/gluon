cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_SMARTS_INCLUDE_DIRS}
)

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_SMARTS_LIBS}"   # libraries arguement
    "gluonsmarts"            # modulename argument

    # Source files without the extension
)

