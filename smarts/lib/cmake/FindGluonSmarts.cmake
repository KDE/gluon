# - Try to find Gluon Smarts
#
# Once done this will define
#   GLUON_SMARTS_FOUND - system has Gluon Smarts
#   GLUON_SMARTS_INCLUDE_DIR - the Gluon Smarts include directory
#   GLUON_SMARTS_INCLUDE_DIRS - all include directories required for Gluon Smarts
#   GLUON_SMARTS_LIBRARY - The Gluon Smarts library location
#   GLUON_SMARTS_LIBS - All libraries necessary for Gluon Smarts to work
#
# Copyright (C) 2011 Laszlo Papp
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_SMARTS_LIBRARY AND GLUON_SMARTS_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_SMARTS_FOUND TRUE)
endif (GLUON_SMARTS_LIBRARY AND GLUON_SMARTS_INCLUDE_DIR)

if (GluonSmarts_FIND_REQUIRED)
    set(_gluonSmartsReq "REQUIRED")
endif (GluonSmarts_FIND_REQUIRED)

find_package(GluonCore ${_gluonSmartsReq})

set(CMAKE_MODULE_PATH ${SHARE_INSTALL_DIR}/gluon/cmake)

find_path(GLUON_SMARTS_INCLUDE_DIR
    NAMES
    smarts/lib/btlib.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_SMARTS_INCLUDE_DIRS
    ${GLUON_CORE_INCLUDE_DIRS}
    ${GLUON_SMARTS_INCLUDE_DIR}
)

find_library(GLUON_SMARTS_LIBRARY
    NAMES
    GluonSmarts
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_SMARTS_LIBS
    ${GLUON_CORE_LIBS}
    ${GLUON_SMARTS_LIBRARY}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonSmarts DEFAULT_MSG GLUON_SMARTS_LIBRARY GLUON_SMARTS_INCLUDE_DIR)
