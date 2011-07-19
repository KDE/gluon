cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${Gluon_SOURCE_DIR}/cmake/)
include(GluonMacros)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${GLUON_AUDIO_INCLUDES})

########### next target ###############

#Set the library variable that is needed for the testing
set(GLUON_TEST_LIBS ${GLUON_AUDIO_LIBS})

GLUON_UNIT_TESTS(
    "gluonaudio" #modulename argument
    soundtest
)
