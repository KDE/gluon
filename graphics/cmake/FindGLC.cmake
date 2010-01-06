# - Try to find SndFile
# Once done this will define
#
#  GLC_FOUND - system has GLC
#  GLC_INCLUDE_DIRS - the GLC include directory
#  GLC_LIBRARIES - Link these to use GLC
#
#  Copyright © 2009 Guillaume Martres
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if (GLC_LIBRARIES AND GLC_INCLUDE_DIRS)
  # in cache already
  set(GLC_FOUND TRUE)
else (GLC_LIBRARIES AND GLC_INCLUDE_DIRS)

  find_path(GLC_INCLUDE_DIR
    NAMES
      GL/glc.h
    PATHS
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
  )

  find_library(GLC_LIBRARY
    NAMES
      GLC
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  set(GLC_INCLUDE_DIRS
    ${GLC_INCLUDE_DIR}
  )
  set(GLC_LIBRARIES
    ${GLC_LIBRARY}
  )

  INCLUDE(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set GLC_FOUND to TRUE if
  # all listed variables are TRUE
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLC DEFAULT_MSG GLC_LIBRARY GLC_INCLUDE_DIR)

  # show the GLC_INCLUDE_DIRS and GLC_LIBRARIES variables only in the advanced view
  mark_as_advanced(GLC_INCLUDE_DIRS GLC_LIBRARIES)

endif (GLC_LIBRARIES AND GLC_INCLUDE_DIRS)
