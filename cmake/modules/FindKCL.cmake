# - Try to find KCL
#
# Once done this will define
#  KCL_FOUND - system has KCL
#  KCL_INCLUDES - all include directories required for KCL, use it with KDE4_INCLUDES
#  KCL_INCLUDE_DIR - the KCL include directory
#  KCL_LIBRARY - the KCL library
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (KCL_LIBRARY AND KCL_INCLUDE_DIR)
  # Already in cache, be silent
  set(KCL_FOUND TRUE)
endif (KCL_LIBRARY AND KCL_INCLUDE_DIR)

find_path(KCL_INCLUDE_DIR
    NAMES
    gluon/kcl/kclengine.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
)

set(KCL_INCLUDES
    ${KCL_INCLUDE_DIR}
    CACHE STRING "Includes needed to use KCL"
)

find_library(KCL_LIBRARY NAMES kcl
    PATHS
    ${LIB_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(KCL DEFAULT_MSG KCL_LIBRARY KCL_INCLUDE_DIR)
