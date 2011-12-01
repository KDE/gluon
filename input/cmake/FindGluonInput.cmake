# - Try to find Gluon Input
#
# Once done this will define
#   GLUON_INPUT_FOUND - system has Gluon Input
#   GLUON_INPUT_INCLUDE_DIR - the Gluon Input include directory
#   GLUON_INPUT_INCLUDE_DIRS - all include directories required for Gluon Input
#   GLUON_INPUT_LIBRARY - The Gluon Input library location
#   GLUON_INPUT_LIBS - All libraries necessary for Gluon Input to work
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_INPUT_LIBRARY AND GLUON_INPUT_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_INPUT_FOUND TRUE)
endif (GLUON_INPUT_LIBRARY AND GLUON_INPUT_INCLUDE_DIR)

if (GluonInput_FIND_REQUIRED)
    set(_gluonInputReq "REQUIRED")
endif (GluonInput_FIND_REQUIRED)

find_package(GluonCore ${_gluonInputReq})

set(CMAKE_MODULE_PATH ${SHARE_INSTALL_DIR}/gluon/cmake)

if(MAC)
    find_library(IOKIT_LIBRARY NAMES IOKit)
    message(STATUS "Found IOKit:" ${IOKIT_LIBRARY})

    find_library(COREFOUNDATION_LIBRARY NAMES CoreFoundation)
    message(STATUS "Found CoreFoundation:" ${COREFOUNDATION_LIBRARY})
endif(MAC)

find_path(GLUON_INPUT_INCLUDE_DIR
    NAMES
    input/gluon_input_export.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_INPUT_INCLUDE_DIRS
    ${GLUON_CORE_INCLUDE_DIRS}
    ${GLUON_INPUT_INCLUDE_DIR}
)

find_library(GLUON_INPUT_LIBRARY
    NAMES
    GluonInput
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_INPUT_LIBS
    ${GLUON_CORE_LIBS}
    ${GLUON_INPUT_LIBRARY}
    ${IOKIT_LIBRARY}
    ${COREFOUNDATION_LIBRARY}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonInput DEFAULT_MSG GLUON_INPUT_LIBRARY GLUON_INPUT_INCLUDE_DIR)
