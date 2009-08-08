# - Try to find KAL
#
# Once done this will define
#  KAL_FOUND - system has KAL
#  KAL_INCLUDES - all include directories required for KAL, use it with KDE4_INCLUDES
#  KAL_INCLUDE_DIR - the KAL include directory
#  KAL_LIBRARY - the KAL library
#
# Copyright (C) 2009 Guillaume Martres
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (KAL_LIBRARY AND KAL_INCLUDE_DIR)
  # Already in cache, be silent
  set(KAL_FOUND TRUE)
endif (KAL_LIBRARY AND KAL_INCLUDE_DIR)

if (KAL_FIND_REQUIRED)
    set(_kalReq "REQUIRED")
endif (KAL_FIND_REQUIRED)

find_package(OpenAL ${_kalReq})
find_package(Alut ${_kalReq})
find_package(SndFile ${_kalReq})
find_package(OggVorbis ${_kalReq})

find_path(KAL_INCLUDE_DIR
    NAMES
    gluon/kal/kalengine.h
    PATHS
    ${INCLUDE_INSTALL_DIR}
)

set(KAL_INCLUDES
    ${KAL_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}
    CACHE STRING "Includes needed to use KAL"
)

find_library(KAL_LIBRARY NAMES kal
    PATHS
    ${LIB_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(KAL DEFAULT_MSG KAL_LIBRARY KAL_INCLUDE_DIR)
