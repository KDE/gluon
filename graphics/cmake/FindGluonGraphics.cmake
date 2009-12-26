# - Try to find KGL
#
# Once done this will define
#  KGL_FOUND - system has KGL
#  KGL_INCLUDES - all include directories required for KGL, use it with KDE4_INCLUDES
#  KGL_INCLUDE_DIR - the KGL include directory
#  KGL_LIBRARY - the KGL library
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (KGL_LIBRARY AND KGL_INCLUDE_DIR)
  # Already in cache, be silent
  set(KGL_FOUND TRUE)
endif (KGL_LIBRARY AND KGL_INCLUDE_DIR)

if (KGL_FIND_REQUIRED)
    set(_kglReq "REQUIRED")
endif (KGL_FIND_REQUIRED)

find_package(OpenGL ${_kglReq})
find_package(GLEW ${_kglReq})
find_package(Eigen2 ${_kglReq})

find_package(GluonCommon ${_kglReq})

find_path(KGL_INCLUDE_DIR
    NAMES
    gluon/kgl/kglengine.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
)

set(KGL_INCLUDES
    ${GLUON_COMMON_INCLUDE_DIR}
    ${KGL_INCLUDE_DIR}
    ${EIGEN2_INCLUDE_DIR}
    CACHE STRING "Includes needed to use KGL"
)

find_library(KGL_LIBRARY NAMES kgl
    PATHS
    ${LIB_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(KGL DEFAULT_MSG KGL_LIBRARY KGL_INCLUDE_DIR)
