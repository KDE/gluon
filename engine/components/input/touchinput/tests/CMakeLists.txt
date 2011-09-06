cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_ENGINE_INCLUDES}
)

########### next target ###############

set(GLUON_COMPONENTS_INPUT_TOUCHINPUT
    ${GLUON_ENGINE_LIBS}
    gluon_component_touchinput
)

GLUON_UNIT_TESTS(
    "${GLUON_COMPONENTS_INPUT_TOUCHINPUT}"      # libraries arguement
    "gluonengine"                               # modulename argument

    # Source files without the extension
    touchinputcomponenttest
)
