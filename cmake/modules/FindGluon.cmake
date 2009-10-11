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

if (GLUON_LIBRARY AND GLUON_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_FOUND TRUE)
endif (GLUON_LIBRARY AND GLUON_INCLUDE_DIR)

if (Gluon_FIND_REQUIRED)
    set(_gluonReq "REQUIRED")
endif (Gluon_FIND_REQUIRED)

find_package(KAL ${_gluonReq})

if (APPLE)
# KCL doesn't build on Apple yet - just ignore it
set(KCL_INCLUDES "")
set(KCLENGINE_H "")
else (APPLE)
find_package(KCL ${_gluonReq})
set(KCLENGINE_H gluon/kcl/kclengine.h)
endif (APPLE)

find_package(KGL ${_gluonReq})


find_path(GLUON_INCLUDE_DIR
    NAMES
    gluon/kgl/kglengine.h
    gluon/kal/kalengine.h
    ${KCLENGINE_H}
    PATHS
    ${INCLUDE_INSTALL_DIR}
)

set(GLUON_INCLUDES
    ${GLUON_INCLUDE_DIR}
    ${KAL_INCLUDES}
    ${KCL_INCLUDES}
    ${KGL_INCLUDES}
    CACHE STRING "Includes needed to use gluon"
)

find_library(GLUON_LIBRARY NAMES gluon
    PATHS
    ${LIB_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Gluon DEFAULT_MSG GLUON_LIBRARY GLUON_INCLUDE_DIR)
