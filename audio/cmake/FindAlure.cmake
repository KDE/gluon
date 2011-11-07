# - Try to find Alure
# Once done this will define
#
#  ALURE_FOUND - system has Alure
#  ALURE_INCLUDE_DIRS - the Alure include directory
#  ALURE_LIBRARIES - Link these to use Alure
#
#  Copyright © 2011 Laszlo Papp <lpapp@kde.org>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if (ALURE_LIBRARY AND ALURE_INCLUDE_DIR)
  # Already in cache, be silent
  set(ALURE_FOUND TRUE)
endif (ALURE_LIBRARY AND ALURE_INCLUDE_DIR)

find_path(ALURE_INCLUDE_DIR
    NAMES
      alure.h
      PATH_SUFFIXES AL OpenAL
    PATHS
      /usr/include
      /usr/local/include
      /opt/local/include
      /sw/include
  )

if(NOT ALURE_MIN_VERSION)
  set(ALURE_MIN_VERSION "1.2")
endif(NOT ALURE_MIN_VERSION)

set(ALURE_VERSION "<1.2")
set(ALURE_VERSION_OK FALSE)
if(ALURE_INCLUDE_DIR)
    file(READ ${ALURE_INCLUDE_DIR}/alure.h ALURE_VERSION_CONTENT)
    string(REGEX MATCH "ALURE_VERSION_STRING \".*\"\n" ALURE_VERSION_MATCH "${ALURE_VERSION_CONTENT}")
    if(ALURE_VERSION_MATCH)
        string(REGEX REPLACE "ALURE_VERSION_STRING \"(.*)\"\n" "\\1" ALURE_VERSION ${ALURE_VERSION_MATCH})
        if(NOT ALURE_VERSION STRLESS "${ALURE_MIN_VERSION}")
            set(ALURE_VERSION_OK TRUE)
        endif(NOT ALURE_VERSION STRLESS "${ALURE_MIN_VERSION}")
    endif(ALURE_VERSION_MATCH)
    if(NOT ALURE_VERSION_OK)
        if(Alure_FIND_REQUIRED)
            message(FATAL_ERROR "Alure version ${ALURE_VERSION} is too old. Please install ${ALURE_MIN_VERSION} or newer.")
        else(Alure_FIND_REQUIRED)
            message(STATUS "Alure version ${ALURE_VERSION} is too old. Please install ${ALURE_MIN_VERSION} or newer.")
        endif(Alure_FIND_REQUIRED)
    endif(NOT ALURE_VERSION_OK)
endif(ALURE_INCLUDE_DIR)


  find_library(ALURE_LIBRARY
    NAMES
      alure ALURE32
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  set(ALURE_INCLUDE_DIRS
      ${ALURE_INCLUDE_DIR}
  )
  set(ALURE_LIBRARIES
      ${ALURE_LIBRARY}
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set ALURE_FOUND to TRUE if
  # all listed variables are TRUE
  find_package_handle_standard_args(Alure DEFAULT_MSG ALURE_LIBRARY ALURE_INCLUDE_DIR)

  # show the ALURE_INCLUDE_DIRS and ALURE_LIBRARIES variables only in the advanced view
  mark_as_advanced(ALURE_INCLUDE_DIRS ALURE_LIBRARIES)
