# - Try to find the Gluon Core library.
#
# Once done this will define
#  GLUON_CORE_FOUND - The Gluon Core library was found
#  GLUON_CORE_LIBRARY - The Gluon Core library location
#  GLUON_CORE_INCLUDES - all include directories required for the Gluon Core library
#  GLUON_CORE_INCLUDE_DIR - the Gluon Core include directory
#
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the COPYING-CMAKE-SCRIPTS file from Gluon's Source tree.

if (GLUON_CORE_LIBRARY AND GLUON_CORE_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUON_CORE_FOUND TRUE)
endif (GLUON_CORE_LIBRARY AND GLUON_CORE_INCLUDE_DIR)

if (GluonCore_FIND_REQUIRED)
    set(_gluonCoreReq "REQUIRED")
endif (GluonCore_FIND_REQUIRED)

find_path(GLUON_CORE_INCLUDE_DIR
    NAMES
    gluon/core/singleton.h
    PATHS
    ${CMAKE_INSTALL_PREFIX}/includes
)

set(GLUON_CORE_INCLUDES
    ${GLUON_CORE_INCLUDE_DIR}
    CACHE STRING "Includes required for Gluon Core"
)

#find_path(GLUON_CORE_LIBRARY
#    NAMES
#
#)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonCore DEFAULT_MSG GLUON_CORE_INCLUDES)
