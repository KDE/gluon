# - Try to find BTLib
#
# Once done this will define
#  BTLIB_FOUND - system has BTLIB
#  BTLIBL_INCLUDES - all include directories required for BTLIB
#  BTLIB_INCLUDE_DIR - the BTLIB include directory
#  BTLIB_LIBRARY - the BTLIB library

if (BTLIB_LIBRARY AND BTLIB_INCLUDE_DIR)
  # Already in cache, be silent
  set(BTLIBL_FOUND TRUE)
endif (BTLIB_LIBRARY AND BTLIB_INCLUDE_DIR)

find_path(BTLIB_INCLUDE_DIR
    NAMES
    gluon/btlib/btfactory.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
)

set(BTLIB_INCLUDES
    ${BTLIB_INCLUDE_DIR}
    CACHE STRING "Includes needed to use btlib"
)

find_library(BTLIB_LIBRARY NAMES btlib
    PATHS
    ${LIB_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BTLIB DEFAULT_MSG BTLIB_LIBRARY BTLIB_INCLUDE_DIR)
