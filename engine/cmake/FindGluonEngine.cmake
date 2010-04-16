# - Try to find Gluon Engine
#
# Once done this will define
#  GLUON_ENGINE_FOUND - system has Gluon Engine
#  GLUON_ENGINE_INCLUDES - all include directories required for Gluon Engine, use it with KDE4_INCLUDES
#  GLUON_ENGINE_INCLUDE_DIR - the Gluon Engine include directory
#  GLUON_ENGINE_LIBRARY - the Gluon Engine library
#  GLUON_ENGINE_LIBS - All libraries required for Gluon Engine
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUON_ENGINE_LIBRARY AND GLUON_ENGINE_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_ENGINE_FOUND TRUE)
endif (GLUON_ENGINE_LIBRARY AND GLUON_ENGINE_INCLUDE_DIR)

if (GluonEngine_FIND_REQUIRED)
    set(_gluonEngineReq "REQUIRED")
endif (GluonEngine_FIND_REQUIRED)

find_package(GluonCore ${_gluonEngineReq})

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/share/gluon/cmake)

find_path(GLUON_ENGINE_INCLUDE_DIR
    NAMES
    engine/gluon_engine_export.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
    PATH_SUFFIXES
    gluon
)

set(GLUON_ENGINE_INCLUDES
    ${GLUON_CORE_INCLUDES}
    ${GLUON_ENGINE_INCLUDE_DIR}
    CACHE PATHS "Includes needed for Gluon Engine"
)

find_library(GLUON_ENGINE_LIBRARY
    NAMES
    GluonEngine
    PATHS
    ${LIB_INSTALL_DIR}
)

set(GLUON_ENGINE_LIBS
    ${GLUON_CORE_LIBS}
    ${GLUON_ENGINE_LIBRARY}
    CACHE PATHS "Libraries needed for Gluon Engine"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonEngine DEFAULT_MSG GLUON_ENGINE_LIBRARY GLUON_ENGINE_INCLUDE_DIR)
