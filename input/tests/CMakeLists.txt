cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${Gluon_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${GLUON_INPUT_INCLUDES})

########### next target ###############

GLUON_UNIT_TESTS(
    "${GLUON_INPUT_LIBS}"   # libraries arguement
    "gluoninput"            # modulename argument
    # Source files without the extension
    inputbuffertest
    inputdevicetest
)
