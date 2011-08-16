cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CREATOR_INCLUDES}
)

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_CREATOR_LIBS}"   # libraries arguement
    "gluoncreator"            # modulename argument

    # Source files without the extension
)
