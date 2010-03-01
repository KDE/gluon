# - Try to find Gluon
#
# Once done this will define
#  GLUON_FOUND - system has Gluon
#  GLUON_INCLUDES - all include directories required for Gluon, use it with KDE4_INCLUDES
#  GLUON_INCLUDE_DIR - the Gluon include directory
#  GLUON_LIBRARY - the Gluon library
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_CREATOR_LIBRARY AND GLUON_CREATOR_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_CREATOR_FOUND TRUE)
endif (GLUON_CREATOR_LIBRARY AND GLUON_CREATOR_INCLUDE_DIR)

if (GluonCreator_FIND_REQUIRED)
  set(_gluonCreatorReq "REQUIRED")
endif (GluonCreator_FIND_REQUIRED)

find_package(GluonCore ${_gluonCreatorReq})

set(CMAKE_MODULE_PATH ${SHARE_INSTALL_DIR}/gluon/cmake)

find_package(KDE4 ${_gluonCreatorReq})
find_package(GluonEngine ${_gluonCreatorReq})

find_path(GLUON_CREATOR_INCLUDE_DIR
    NAMES
    creator/gluoncreator_macros.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_CREATOR_INCLUDES
    ${GLUON_CREATOR_INCLUDE_DIR}
    ${GLUON_CORE_INCLUDES}
    ${GLUON_ENGINE_INCLUDES}
    ${KDE4_INCLUDES}
    CACHE PATHS "Include files required for Gluon Creator"
)

find_library(GLUON_CREATOR_LIBRARY
    NAMES
    GluonCreator
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_CREATOR_LIBS
    ${KDE4_KDEUI_LIBS}
    ${GLUON_CORE_LIBS}
    ${GLUON_ENGINE_LIBS}
    ${GLUON_CREATOR_LIBRARY}
    CACHE PATHS "Libraries required for Gluon Creator"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonCreator DEFAULT_MSG GLUON_CREATOR_LIBRARY GLUON_CREATOR_INCLUDE_DIR)
