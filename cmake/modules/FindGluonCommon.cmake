# - Try to find Gluon's common files
#
# Once done this will define
#  GLUONCOMMON_FOUND - system has Gluon common files
#  GLUONCOMMON_INCLUDES - all include directories required for Gluon's common files, use it with KDE4_INCLUDES
#  GLUONCOMMON_INCLUDE_DIR - the Gluon common include directory
#
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GLUONCOMMON_LIBRARY AND GLUONCOMMON_INCLUDE_DIR)
  # Already in cache, be silent
  set(GLUONCOMMON_FOUND TRUE)
endif (GLUONCOMMON_LIBRARY AND GLUONCOMMON_INCLUDE_DIR)

if (GluonCommon_FIND_REQUIRED)
    set(_gluonCommonReq "REQUIRED")
endif (GluonCommon_FIND_REQUIRED)

find_path(GLUONCOMMON_INCLUDE_DIR
    NAMES
    gluon/common/ksingleton.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
)

set(GLUONCOMMON_INCLUDES
    ${GLUONCOMMON_INCLUDE_DIR}
    CACHE STRING "Common files for Gluon"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GluonCommon DEFAULT_MSG GLUONCOMMON_INCLUDE_DIR)
