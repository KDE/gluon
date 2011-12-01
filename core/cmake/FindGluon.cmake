# - Try to find the Gluon libraries.
#
# Once done this will define
#  GLUON_FOUND - The Gluon libraries were found
#  GLUON_LIBS - All libraries necessary to compile a Gluon application
#  GLUON_INCLUDE_DIRS - All include directories required for the Gluon libraries
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the COPYING-CMAKE-SCRIPTS file from Gluon's Source tree.

if(GLUON_LIBS AND GLUON_INCLUDE_DIRS)
    # Already in cache, be silent
    set(GLUON_FOUND TRUE)
endif(GLUON_LIBS AND GLUON_INCLUDE_DIRS)

if(Gluon_FIND_REQUIRED)
    set(_gluonReq "REQUIRED")
endif(Gluon_FIND_REQUIRED)

find_package(GluonCore ${_gluonReq})
find_package(GluonAudio ${_gluonReq})
find_package(GluonInput ${_gluonReq})
find_package(GluonGraphics ${_gluonReq})
find_package(GluonEngine ${_gluonReq})

set(GLUON_INCLUDE_DIRS
    ${GLUON_CORE_INCLUDE_DIRS}
    ${GLUON_AUDIO_INCLUDE_DIRS}
    ${GLUON_INPUT_INCLUDE_DIRS}
    ${GLUON_GRAPHICS_INCLUDE_DIRS}
    ${GLUON_ENGINE_INCLUDE_DIRS}
)

set(GLUON_LIBS
    ${GLUON_CORE_LIBS}
    ${GLUON_AUDIO_LIBS}
    ${GLUON_INPUT_LIBS}
    ${GLUON_GRAPHICS_LIBS}
    ${GLUON_ENGINE_LIBS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Gluon DEFAULT_MSG GLUON_INCLUDE_DIRS GLUON_LIBS)
